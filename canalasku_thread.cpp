#include "../common/logger.h"
#include "globalvar.h"
#include "canalasku_thread.h"
#include "canalasku.h"

//--------------------------------------------------------------
#define NO_DEBUG

//--------------------------------------------------------------
CanalAskuThread::CanalAskuThread(QObject * parent) : QThread(parent)
{
	adress[0] = m_setup.com1.ip;
	adress[1] = m_setup.com2.ip;
	port[0] = m_setup.asku.port1;
	port[1] = m_setup.asku.port2;

	m_isMain = false;
	m_mainTimeout = 0;
	waiting = false;
	running = true;
	changedActive = false;
	n_active = 0;
	n_passive = 1;
	test_active = false;
	test_passive = false;
	n_dc_umi = 0;
	mon_dc_umi.clear();

	setMode(NormalMode);
	LogSerialInfo("CanalAskuThread: set active port 0");

	connected[0] = connected[1] = Disconnected;
	socket[0] = socket[1] = NULL;

	canalAskuData = new CanalAskuData();
	canalAskuDataOther = new CanalAskuData();
	canalAskuCommand = new CanalAskuCommand();
}

//--------------------------------------------------------------
CanalAskuThread::~CanalAskuThread()
{
	delete canalAskuData;
	delete canalAskuDataOther;
	delete canalAskuCommand;
}

//--------------------------------------------------------------
void CanalAskuThread::quit()
{
	running = false;
	wait(1000);
}

// ------------------------------------------------------------------
void CanalAskuThread::setMain(bool main)
{
	if(main != m_isMain)
	{
		m_isMain = main;
		if(m_isMain)
		{
			m_mainTimeout = 5;
			LogSerialInfo("CanalAsku: master mode");
			canalAskuCommand->flush();
		}
		else
		{
			LogSerialInfo("CanalAsku: slave mode");
			canalAskuCommand->flush();
		}
	}
}

//--------------------------------------------------------------
void CanalAskuThread::run()
{
	LogSerialInfo("CanalAskuThread: started");

	while(running)
	{
		if(connected[0] == Waiting)
			disconnectFromHost(0);

		if(!running)
			break;

		if(connected[0] == Disconnected)
			connectToHost(0);

		if(!running)
			break;

		if(connected[1] == Waiting)
			disconnectFromHost(1);

		if(!running)
			break;

		if(connected[1] == Disconnected)
			connectToHost(1);

		if(!running)
			break;

		if((connected[0] != Connected) && (connected[1] != Connected))
			msleep(500);

		if(!running)
			break;

		if((connected[0] != Connected) && (connected[1] == Connected) && (n_active == 0))
		{
			n_active = 1;
			n_passive = 0;
			LogSerialInfo("CanalAskuThread: set active port 1");
		}
		if((connected[0] == Connected) && (connected[1] != Connected) && (n_active == 1))
		{
			n_active = 0;
			n_passive = 1;
			LogSerialInfo("CanalAskuThread: set active port 0");
		}

		canalAskuData->incCount();

		if(!m_isMain || m_mainTimeout)
		{
			m_mainTimeout--;

			test_active = doListenSlave(n_active);

			if(!running)
				break;

			test_passive = doListenSlave(n_passive);

			if(!running)
				break;

			if(((connected[n_active] != Connected) || !test_active) &&
				((connected[n_passive] == Connected) && test_passive))
			{
				quint32 tmp = n_active;
				n_active = n_passive;
				n_passive = tmp;
				changedActive = true;

				LogSerialInfo("CanalAskuThread: set active port %d", n_active);
			}
			else
			{
				changedActive = false;
			}

			while(waiting && running)
				msleep(10);

			if(!running)
				break;

			continue;
		}

		if(m_mode == NormalMode)
		{
			test_active = doExchange(commTest2, n_active, n_passive);

			if(!running)
				break;

			test_passive = doExchange(commTest1, n_passive, n_active);

			if(!running)
				break;

			if(((connected[n_active] != Connected) || !test_active) &&
				((connected[n_passive] == Connected) && test_passive))
			{
				quint32 tmp = n_active;
				n_active = n_passive;
				n_passive = tmp;
				changedActive = true;

				LogSerialInfo("CanalAskuThread: set active port %d", n_active);
			}
			else
			{
				changedActive = false;
			}

			doExchange(commUpr2, n_active, n_passive);

			if(!running)
				break;

			n_dc_umi++;
			if(n_dc_umi > CA_N_MODULES_UMI)
				n_dc_umi = 1;

			doExchange(commParamUMIv4, n_active, n_passive, -1, n_dc_umi);

			if(!running)
				break;

			doExchange(commUpr2,n_active,n_passive);

			if(!running)
				break;

//mon_dc_umi
			foreach(CA_TYPE_TRM trm, mon_dc_umi.keys())
			{
				if(trm.module != n_dc_umi)
					doExchange(commParamUMIv4, n_active, n_passive, trm.transmitter, trm.module);

				if(!running)
					break;
			}

			doExchange(commUpr2, n_active, n_passive);

			if(!running)
				break;

			doExchange(commSost2, n_active, n_passive);
	
			if(!running)
				break;

			doExchange(commUpr2, n_active, n_passive);

			if(!running)
				break;

			waiting = true;

			canalAskuData->setPortActive(n_active);
			canalAskuData->setPortStatus(connected[0] == Connected, connected[1] == Connected);

			emit readyData(canalAskuData);

			LogSerialInfo("CanalAskuThread: waiting");

			while(waiting && running)
				msleep(10);

			if(!running)
				break;
		}
	}

	disconnectFromHost(0);
	disconnectFromHost(1);

	LogSerialInfo("CanalAskuThread: stopped");
}

//--------------------------------------------------------------
void CanalAskuThread::dataReady()
{
	waiting = false;
}

//--------------------------------------------------------------
QVariantMap CanalAskuThread::getCanalAskuDataLocal()				// run only in main thread
{
	return canalAskuData ? canalAskuData->toMap() : QVariantMap();
}

//--------------------------------------------------------------
void CanalAskuThread::setCanalAskuDataOther(const QVariantMap & data)		// run only in main thread
{
	if(!isMain() && canalAskuDataOther && canalAskuDataOther->fromMap(data))
	{
		canalAskuDataOther->incCount();
//qDebug() << "CANALASKU_DATA_FROM_OTHER";
//qDebug() << data;
//qDebug() << canalAskuDataOther->toMap();
		emit readyData(canalAskuDataOther);
	}
}

//--------------------------------------------------------------
void CanalAskuThread::connectToHost(quint32 nc)
{
	socket[nc] = new QTcpSocket();
	LogSerialInfo("CanalAskuThread: connect [%d] to host %s:%d", nc, qPrintable(adress[nc].toString()), port[nc]);
	socket[nc]->connectToHost(adress[nc], port[nc]);

	if(!socket[nc]->waitForConnected(1000))
	{
		LogSerialError("CanalAskuThread: connect [%d] error: %d-%s", nc, socket[nc]->error(), qPrintable(socket[nc]->errorString()));
		connected[nc] = Waiting;
	}
	else
	{
		LogSerialInfo("CanalAskuThread: connected [%d]", nc);
		connected[nc] = Connected;
	}
}

//----------------------------------------------------------------
void CanalAskuThread::disconnectFromHost(quint32 nc)
{
	if(socket[nc] != NULL)
	{
		LogSerialInfo("CanalAskuThread: disconnect [%d] from host %s:%d", nc, qPrintable(adress[nc].toString()), port[nc]);

		socket[nc]->disconnectFromHost();

		if(socket[nc]->state() != QAbstractSocket::UnconnectedState)
			socket[nc]->waitForDisconnected(1000);

		connected[nc] = Disconnected;
		socket[nc]->close();
		delete socket[nc];
		socket[nc] = NULL;
	}
}

//----------------------------------------------------------------
void CanalAskuThread::updateCommands(CanalAskuCommand *command)
{
	if(m_isMain)
		canalAskuCommand->append(command);
}

//----------------------------------------------------------------
void CanalAskuThread::setAskuState(quint8 command, qint32 numOY, qint8 nMODULE, quint8 state)
{
	switch(command)
	{
		case commSost2:
		case commSost3:
			canalAskuData->setStateError(numOY, state);
			break;

		case commTest1:
			canalAskuData->setTest1Error(numOY, state);
			break;

		case commTest2:
			canalAskuData->setTest2Error(numOY, state);
			break;

		case commParamUMIv4:
		case commParamUMIv5:
		case commParamUMIv5Group:
			if(nMODULE < 0)
				for(quint32 i = 0; i < CA_N_MODULES_UMI; i++)
					canalAskuData->setParamUmiError(numOY, i, state);
			else
				canalAskuData->setParamUmiError(numOY, nMODULE - 1, state);
			break;

		case commUpr:
		case commUpr2:
			canalAskuData->setCommandError(numOY, state);
			break;

		case commAnalog:
			break;
	}
}

//----------------------------------------------------------------
void CanalAskuThread::setAskuData(quint8 command, qint32 numOY, qint8 nMODULE, quint8* packet, quint8 packetSize)
{
	switch(command)
	{
		case commSost2:
		case commSost3:
			canalAskuData->setState(numOY, packet, packetSize);
			break;

		case commTest1:
			canalAskuData->setTest1(numOY, packet, packetSize);
			break;

		case commTest2:
			canalAskuData->setTest2(numOY, packet, packetSize);
			break;

		case commParamUMIv4:
		case commParamUMIv5:
		case commParamUMIv5Group:
			canalAskuData->setParamUmi(numOY, nMODULE - 1, packet, packetSize);
			break;

		case commUpr:
		case commUpr2:
			canalAskuData->setCommand(numOY, packet, packetSize);
			break;

		case commAnalog:
			break;
	}
}

//----------------------------------------------------------------
bool CanalAskuThread::doExchange(quint8 command, quint32 nc, quint32 ncp, qint32 ndevice, qint32 nmodule)
{
	LogSerialInfo("CanalAskuThread: doExchange[%d]  command = %02X  ndevice = %d  module = %d", nc, command, ndevice, nmodule);

	CA_TYPE_COMMAND command_data;
	quint32 replyCounter = 0;
	unsigned char c_address[CA_N_DEVICES] = {addr124YY08, addr124YG02G1, addr124YG02G2};
	unsigned char c_num_bytes[CA_N_DEVICES] = {CA_HEADER_COMMAND_N_BYTES, CA_HEADER_COMMAND_N_BYTES, CA_HEADER_COMMAND_N_BYTES};
	unsigned char num_bytes = 0;
	unsigned char *pdata = NULL;
	unsigned char xbyte = 0x01;
	char nMODULE = (char)(nmodule >= 0 ? nmodule : 0);

	for(int numOY = 0; numOY < CA_N_DEVICES; numOY++)
	{
		if(ndevice >= 0 && numOY != ndevice)
			continue;

		clear();

		num_bytes = 0;
		pdata = NULL;

		switch(command)
		{
			case commSost2:
				break;

			case commTest1:
				break;

			case commTest2:
				break;

			case commUpr2:
				if(!canalAskuCommand->extractByTime(numOY, &command_data))
					continue;

				num_bytes = c_num_bytes[numOY];
				pdata = (unsigned char*)&command_data;
				break;

			case commParamUMIv4:
				if(((c_address[numOY] != addr124YG02G1) && (c_address[numOY] != addr124YG02G2)) || nMODULE < 0) continue;

				num_bytes = 1;
				pdata = (unsigned char*)&nMODULE;
				break;

			case commAnalog:
				if(c_address[numOY] != addr124YY08) continue;

				num_bytes = 1;
				pdata = (unsigned char*)&xbyte;
				break;
		}

		QByteArray blockSend = codeCommand(c_address[numOY], command, num_bytes, pdata);
		if(blockSend.isEmpty())
		{
			LogError("CanalAskuThread:: codeCommand error - empty buffer");
			continue;
		}

		if(!socket[nc] || connected[nc] != Connected)
			continue;

		if(command == commUpr2)
			LogInfo("CanalAskuThread: Command: addr=%d: %s", c_address[numOY], LogMemory((const char*)pdata, num_bytes));

		quint32 cntRetry = 3;
		quint32 cntNoReply = 0;
		do
		{
			if(cntRetry < 3)
				LogSerialError("CanalAskuThread: retry %d", cntRetry);

			QByteArray flushed = socket[nc]->readAll();//flush

			if(flushed.size() > 0)
			{
				LogSerialBinary("CanalAskuThread: flush[%d]: %s", nc, LogArray(flushed));
			}

			if(connected[ncp] == Connected)
			{
				flushed = socket[ncp]->readAll();//flush
				if(flushed.size() > 0)
				{
					LogSerialBinary("CanalAskuThread: flush[%d]: %s", ncp, LogArray(flushed));
				}
			}

			if(socket[nc]->write(blockSend) <= 0)
			{
				LogSerialError("CanalAskuThread: write [%d] error: %d-%s", nc, socket[nc]->error(), qPrintable(socket[nc]->errorString()));
				disconnectFromHost(nc);
				setAskuState(command, numOY, nMODULE, CA_ERROR_NO_NETWORK);
				break;
			}

			LogSerialBinary("CanalAskuThread::write [%d]: %s", nc, LogArray(blockSend));

			if(!socket[nc]->waitForBytesWritten(200))
			{
				QAbstractSocket::SocketError error = socket[nc]->error();
				LogSerialError("CanalAskuThread::write [%d] error: %d-%s", nc, error, qPrintable(socket[nc]->errorString()));

				if(error == QAbstractSocket::HostNotFoundError ||
					error == QAbstractSocket::RemoteHostClosedError ||
					error == QAbstractSocket::UnknownSocketError)
				{
					disconnectFromHost(nc);
					setAskuState(command, numOY, nMODULE, CA_ERROR_NO_NETWORK);
					break;
				}
			}

			if(!socket[nc]->waitForReadyRead(200))
			{
				QAbstractSocket::SocketError error = socket[nc]->error();
				LogSerialError("CanalAskuThread::read [%d] error: %d-%s", nc, error, qPrintable(socket[nc]->errorString()));

				if(error == QAbstractSocket::SocketTimeoutError)
				{
					cntNoReply++;
					if(cntRetry <= 1 && cntNoReply >= 3)
					{
						setAskuState(command, numOY, nMODULE, CA_ERROR_NO_OS);
					}
				}
				else
				{
					disconnectFromHost(nc);
					setAskuState(command, numOY, nMODULE, CA_ERROR_NO_NETWORK);
					break;
				}
			}
			else
			{
				QByteArray blockRecv = socket[nc]->readAll();

				while(1)
				{
					if(!socket[nc]->waitForReadyRead(20))//200
						break;
					else
					{
						QByteArray blockRecv1 = socket[nc]->readAll();
						blockRecv += blockRecv1;
					}
				}

				LogSerialBinary("CanalAskuThread::read  [%d]: %s", nc, LogArray(blockRecv));

				dataReceived((unsigned char*)blockRecv.data(),blockRecv.size());

				quint8 result;

				while(1)
				{
					result = processData();

					bool wasError = false;

					if(result == CA_NO_ERROR)
					{
						if(packetAddress() != c_address[numOY])
						{
							wasError = true;
							LogSerialError("CanalAskuThread: wait for %02X address but received %02X", c_address[numOY], packetAddress());
						}
						if(packetCommand() != command)
						{
							wasError = true;
							LogSerialError("CanalAskuThread: wait for %02X command but received %02X", command, packetCommand());
						}
						if(wasError)
						{
							LogSerialError("CanalAskuThread: skip lost packet");
							continue;
						}

						char rMODULE = packetCommand() == commParamFSV ? nMODULE : packetModule();

//						if(packetCommand() == commParamFSV /*|| packetCommand() == commParamUMIv5 || packetCommand() == commParamUMIv5Group*/)
//							qDebug("rModule=%d", rMODULE);

						setAskuState(command, numOY, rMODULE, result);

						cntRetry = 1;
						replyCounter++;

						setAskuData(command, numOY, rMODULE, packet(), packetSize());
						continue;
					}

					LogSerialInfo("CanalAskuThread: our packet processing");
					break;
				}
			}
			if(socket[ncp] && socket[ncp]->waitForReadyRead(300))
			{
				flushed = socket[ncp]->readAll();
				if(flushed.size() > 0)
				{
					LogSerialBinary("CanalAskuThread::read  [%d]: %s", ncp, LogArray(flushed));
				}
			}
		}while(--cntRetry);
	}
	return (replyCounter > 0);
}

//----------------------------------------------------------------
bool CanalAskuThread::doListenSlave(quint32 ncp)
{
	if(!socket[ncp] || connected[ncp]!=Connected)
		return 0;

	QByteArray flushed;//flush
	quint32 replyCounter = 0;

	if(socket[ncp] && socket[ncp]->waitForReadyRead(300))
	{
		flushed = socket[ncp]->readAll();
		replyCounter = flushed.size();
		if(replyCounter > 0)
		{
			LogSerialBinary("CanalAskuThread::read  [%d]: %s", ncp, LogArray(flushed));
		}
	}
	return (replyCounter > 0);
}

//----------------------------------------------------------------
void CanalAskuThread::setMode(CanalAskuMode mode)
{
	LogSerialInfo("CanalAskuThread: set mode %d", (int)mode);
	m_mode = mode;
}

//----------------------------------------------------------------
void CanalAskuThread::cancelMonitored()
{
	mon_dc_umi.clear();
}

//----------------------------------------------------------------
void CanalAskuThread::addMonitoredModule(quint32 transmitter, quint32 module)
{
	CA_TYPE_TRM m(transmitter, module);

	if(mon_dc_umi.contains(m))
		mon_dc_umi[m] = mon_dc_umi[m] + 1;
	else
		mon_dc_umi.insert(m, 1);
}

//----------------------------------------------------------------
void CanalAskuThread::removeMonitoredModule(quint32 transmitter, quint32 module)
{
	CA_TYPE_TRM m(transmitter, module);

	if(mon_dc_umi.contains(m))
	{
		mon_dc_umi[m] = mon_dc_umi[m] - 1;
		if(mon_dc_umi[m] == 0)
			mon_dc_umi.remove(m);
	}
}

//----------------------------------------------------------------
void CanalAskuThread::setMonitoredModule(quint32 n_prd, quint32 n_module)
{
	if(n_prd > 0 && n_module > 0)
	{
		LogInfo("setModuleMonitoring %d %d", n_prd, n_module);
		addMonitoredModule(n_prd, n_module);
	}
	else
	{
		LogInfo("cancelModuleMonitoring");
		cancelMonitored();
	}
}

//----------------------------------------------------------------
