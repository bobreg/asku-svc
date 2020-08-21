#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "avt_service.h"
#include "avt_thread.h"

// ------------------------------------------------------------------
AVT_SERVICE::AVT_SERVICE(AVT_THREAD *p)
{
	parent = p;
	network = NULL;
	timer = NULL;

	m_isInitialized = false;
	m_isConnected[0] = m_isConnected[1] = false;
	m_isRequisites[0] = m_isRequisites[1] = false;
	m_counterState[0] = m_counterState[1] = 0;

	m_cmdMain = false;

	m_haAvt[0] = m_setup.n106.ip;//192.0.1.21
	m_haAvt[1] = QHostAddress();
	m_portAvt[0] = m_setup.n106.port_out;//0x????
	m_portAvt[1] = 0;
	m_portOur = m_setup.n106.port_in;//0x????
}

// ------------------------------------------------------------------
bool AVT_SERVICE::init()
{
	network = new UdpNetwork(this, QString("AVT_UDP"));
	if(network)
	{
		connect(network, SIGNAL(dataArrived(QByteArray,QHostAddress,quint16)), this, SLOT(onDataArrived(QByteArray,QHostAddress,quint16)));

		LogPoiInfo("AvtService started");
		m_isInitialized = network->init(m_portOur);
	}

	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
	timer->start(1000);

	return false;
}

// ------------------------------------------------------------------
AVT_SERVICE::~AVT_SERVICE()
{
	if(timer)
	{
		timer->stop();
		delete timer;
		timer = NULL;
	}
	if(network)
	{
		network->close();
		delete network;
		network = NULL;
	}
}

// ------------------------------------------------------------------
bool AVT_SERVICE::isInitialized()
{
	return m_isInitialized;
}

// ------------------------------------------------------------------
void AVT_SERVICE::setMain(bool main)
{
	if(main != m_cmdMain)
	{
		m_cmdMain = main;
	}
}

// ------------------------------------------------------------------
void AVT_SERVICE::setErase()
{
	sendErase(0);
}

// ------------------------------------------------------------------
void AVT_SERVICE::timeout()
{
	for(int p = 0; p < 1 /*N_AVT*/; p++)
	{
		if(!m_isRequisites[p])
		{
			sendQueryRequisites(p);
		}
		else
		{
			sendQueryState(p);
		}

		if(m_counterState[p] > 0)
			m_counterState[p]--;
		else if(m_counterState[p] < 0)
			m_counterState[p]++;
		else
		{
			bAvtState[QString("avt%1@ObSost").arg(p+1)] = ELEM_AVAR;
			emit sigState(bAvtState, bAvtParam);
		}
	}
}

// ------------------------------------------------------------------
void AVT_SERVICE::onDataArrived(QByteArray data, QHostAddress address, quint16 port)
{
	LogPoiBinary("AVT: recv from %s:%d: %s", qPrintable(address.toString()), port, LogArray(data));

	if(address == m_haAvt[0])
		processMessage(0, data);
	else if(address == m_haAvt[1])
		processMessage(1, data);
}

// ------------------------------------------------------------------
bool AVT_SERVICE::processMessage(qint32 n, QByteArray data)
{
	if(data.isEmpty())
		return true;

	AVT_ANSWER *ans = (AVT_ANSWER*)data.data();

	if(ans->error == AVT_ANSWER_NO_ERROR)
	{
		LogPoiInfo("AVT: command ok");
	}
	else if(ans->error == AVT_ANSWER_ERROR_REQUISITES)
	{
		LogPoiError("AVT: error requisites");
	}
	else if(ans->error == AVT_ANSWER_CANNOT_EXECUTE)
	{
		LogPoiError("AVT: error cannot execute");
	}

	if(ans->command == AVT_COMMAND_QUERY_REQUISITES)
	{
		return processRequisites(n, data);
	}
	else if(ans->command == AVT_COMMAND_QUERY_STATE)
	{
		return processState(n, data);
	}
	else if(ans->command == AVT_COMMAND_ERASE)
	{
		return processErase(n, data);
	}
	else
	{
		LogPoiInfo("AVT: unknown message command (%d,%d)", ans->command, ans->error);
	}

	return false;
}

// ------------------------------------------------------------------
bool AVT_SERVICE::processRequisites(qint32 n, QByteArray data)
{
	LogPoiInfo("AvtService: processRequisites");

	AVT_ANSWER_REQUISITES *ans = (AVT_ANSWER_REQUISITES*)data.data();
	if(ans->answer.error == AVT_ANSWER_NO_ERROR)
	{
		m_requisites[n] = ans->requisites;
		m_isRequisites[n] = true;
		LogPoiInfo("AVT: n%d : accepted requisites: type = %d, serial = %d", n, ans->requisites.n106_code, ans->requisites.serial);
	}
	else
	{
		LogPoiError("AVT: n%d : error process requisited = %d", n, ans->answer.error);
	}
//	emit sigState(bAvtState, bAvtValue);

	return false;
}

// ------------------------------------------------------------------
bool AVT_SERVICE::processState(qint32 n, QByteArray data)
{
	LogPoiInfo("AvtService: processState");

	AVT_ANSWER_STATE *ans = (AVT_ANSWER_STATE*)data.data();
	if(ans->answer.error == AVT_ANSWER_NO_ERROR)
	{
		if(m_isRequisites[n])
		{
			LogPoiInfo("AVT: n%d : accepted state", n);

			LogPoiInfo("AVT: B1 - Fail = %d", 		ans->state.b1.fail);
			LogPoiInfo("AVT: B1 - Link to B2 = %d", ans->state.b1.b2);
			LogPoiInfo("AVT: B1 - Pult = %d", 		ans->state.b1.pult);

			LogPoiInfo("AVT: B2 - Fail = %d", 		ans->state.b2.fail);
			LogPoiInfo("AVT: B2 - Link to B3 = %d", ans->state.b2.b3);
			LogPoiInfo("AVT: B2 - UVK = %d", 		ans->state.b2.uvk);

			if(m_requisites[n].n106_code == AVT_N106A_CODE)
			{
				LogPoiInfo("AVT: B3 - Fail = %d", 			ans->state.b3.a.fail);
				LogPoiInfo("AVT: B3 - Link to ShDU = %d", 	ans->state.b3.a.shdu);
				LogPoiInfo("AVT: B3 - GSCh = %d", 			ans->state.b3.a.gsch);

				LogPoiInfo("AVT: B3 - ShDU no connect = %d", ans->state.b3.a.shdu_noconnect);
				LogPoiInfo("AVT: B3 - ShDU Fail = %d",		 ans->state.b3.a.shdu_fail);
				LogPoiInfo("AVT: B3 - ShDU not loaded = %d", ans->state.b3.a.shdu_notloaded);
			}
			if(m_requisites[n].n106_code == AVT_N106B_CODE)
			{
				LogPoiInfo("AVT: B3 - Fail = %d", 			ans->state.b3.b.fail);
				LogPoiInfo("AVT: B3 - Link to Int = %d", 	ans->state.b3.b.inter);
				LogPoiInfo("AVT: B3 - GSCh = %d", 			ans->state.b3.b.gsch);
			}

			LogPoiInfo("AVT: Keys Actual = %d", 	ans->state.key_actual);
			LogPoiInfo("AVT: Keys Next   = %d", 	ans->state.key_next);
			LogPoiInfo("AVT: Cat unexpended = %d", 	ans->state.cat_unexpended);
			LogPoiInfo("AVT: Cat expended   = %d", 	ans->state.cat_expended);
			LogPoiInfo("AVT: CRC = %04X", 			ans->state.crc);
		}
		else
		{
			LogPoiError("AVT: n%d : state answer before requisites accepted", n);
		}
	}
	else
	{
		LogPoiError("AVT: n%d : error process state = %d", n, ans->answer.error);
	}
//	emit sigState(bAvtState);

	return false;
}

// ------------------------------------------------------------------
bool AVT_SERVICE::processErase(qint32 n, QByteArray data)
{
	LogPoiInfo("AvtService: processErase");

	AVT_ANSWER_ERASE *ans = (AVT_ANSWER_ERASE*)data.data();
	if(ans->answer.error == AVT_ANSWER_NO_ERROR)
	{
		if(m_isRequisites[n])
		{
			LogPoiInfo("AVT: n%d : accepted erase", n);
		}
		else
		{
			LogPoiError("AVT: n%d : erase answer before requisites accepted", n);
		}
	}
	else
	{
		LogPoiError("AVT: n%d : error process erase = %d", n, ans->answer.error);
	}

//	emit sigState(bAvtState);

	return false;
}

// ------------------------------------------------------------------
void AVT_SERVICE::clear(qint32 n)
{
	QString nId = QString("%1").arg(n + 1);

//	emit sigState(bPoiState[n_poi]);
}

// ------------------------------------------------------------------
void AVT_SERVICE::sendToAvt(qint32 n, QByteArray data)
{
	if(!data.isEmpty())
	{
		LogPoiBinary("AVT: n%d send: %s", n, qPrintable(LogArray(data)));

		if(network)
			network->sendReply(data, m_haAvt[n], m_portAvt[n]);
	}
}

// ------------------------------------------------------------------
void AVT_SERVICE::sendErase(qint32 n)
{
	LogPoiInfo("AVT: sendErase n%d", n);

	if(!m_isRequisites[n])
		return;

	QByteArray message;
	message.fill(0, sizeof(AVT_COMMAND));
	AVT_COMMAND *cmd = (AVT_COMMAND*)message.data();
	cmd->header.asku_code = AVT_ASKU_CODE;
	cmd->header.requsites = m_requisites[n];
	cmd->command = AVT_COMMAND_ERASE;
	sendToAvt(n, message);
}

// ------------------------------------------------------------------
void AVT_SERVICE::sendQueryRequisites(qint32 n)
{
	LogPoiInfo("AVT: sendQueryRequisites n%d", n);
	QByteArray message;
	message.fill(0, sizeof(AVT_COMMAND));
	AVT_COMMAND *cmd = (AVT_COMMAND*)message.data();
	cmd->header.asku_code = AVT_ASKU_CODE;
	cmd->command = AVT_COMMAND_QUERY_REQUISITES;
	sendToAvt(n, message);
}

// ------------------------------------------------------------------
void AVT_SERVICE::sendQueryState(qint32 n)
{
	LogPoiInfo("AVT: sendQueryState n%d", n);

	if(!m_isRequisites[n])
		return;

	QByteArray message;
	message.fill(0, sizeof(AVT_COMMAND));
	AVT_COMMAND *cmd = (AVT_COMMAND*)message.data();
	cmd->header.asku_code = AVT_ASKU_CODE;
	cmd->header.requsites = m_requisites[n];
	cmd->command = AVT_COMMAND_QUERY_STATE;
	sendToAvt(n, message);
}

// ------------------------------------------------------------------
