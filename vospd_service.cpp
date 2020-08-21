#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "vospd_service.h"
#include "vospd_thread.h"

// ------------------------------------------------------------------
VOSPD_SERVICE::VOSPD_SERVICE(VOSPD_THREAD *p)
{
	parent = p;
	network_tcp[0] = network_tcp[1] = NULL;
	network_udp = NULL;
	stateTimer = NULL;
	queryTimer = NULL;

	m_isInitialized[0] = m_isInitialized[1] = false;
	m_isConnected[0] = m_isConnected[1] = false;
	m_counterState[0] = m_counterState[1] = 0;

	m_cmdMain = false;
	m_azimuthSource = 0;
	m_queryState = -1;

	if(m_setup.vospd.type == 1)
	{
		m_portOur = m_setup.vospd.port;
		m_haVospd[0] = m_setup.com1.ip;
		m_haVospd[1] = m_setup.com2.ip;
	}
	else
	{
		m_portOur = m_setup.vospd.port;
		m_haVospd[0] = m_setup.vospd.ip1;
		m_haVospd[1] = m_setup.vospd.ip2;
	}
	m_idVospd[0] = m_idVospd[1] = -1;
}

// ------------------------------------------------------------------
bool VOSPD_SERVICE::init()
{
	if(m_setup.vospd.type == 1)
	{
		network_tcp[0] = new TcpNetwork(this, QString("VOSPD_TCP1"));
		if(network_tcp[0])
		{
			connect(network_tcp[0], SIGNAL(sigConnected(qint32,QHostAddress,quint16)), this, SLOT(onConnected(qint32,QHostAddress,quint16)));
			connect(network_tcp[0], SIGNAL(sigDisconnected(qint32)), this, SLOT(onDisconnected(qint32)));
			connect(network_tcp[0], SIGNAL(dataArrived(qint32, QByteArray)), this, SLOT(onDataArrived(qint32, QByteArray)));
			m_isInitialized[0] = network_tcp[0]->init(m_haVospd[0], m_portOur);
		}

		network_tcp[1] = new TcpNetwork(this, QString("VOSPD_TCP2"));
		if(network_tcp[1])
		{
			connect(network_tcp[1], SIGNAL(sigConnected(qint32,QHostAddress,quint16)), this, SLOT(onConnected(qint32,QHostAddress,quint16)));
			connect(network_tcp[1], SIGNAL(sigDisconnected(qint32)), this, SLOT(onDisconnected(qint32)));
			connect(network_tcp[1], SIGNAL(dataArrived(qint32, QByteArray)), this, SLOT(onDataArrived(qint32, QByteArray)));
			m_isInitialized[1] = network_tcp[1]->init(m_haVospd[1], m_portOur);
		}
	}
	else if(m_setup.vospd.type == 2)
	{
		network_udp = new UdpNetwork(this, QString("VOSPD_UDP"));
		if(network_udp)
		{
			connect(network_udp, SIGNAL(dataArrived(QByteArray,QHostAddress,quint16)), this, SLOT(onDataArrived(QByteArray,QHostAddress,quint16)));
			m_isInitialized[0] = m_isInitialized[1] = network_udp->init(m_portOur);
		}
	}

	LogVospdInfo("VospdService started");

	stateTimer = new QTimer(this);
	connect(stateTimer,SIGNAL(timeout()),this,SLOT(timeout()));
	stateTimer->start(1000);

	queryTimer = new QTimer(this);
	connect(queryTimer,SIGNAL(timeout()),this,SLOT(queryTimeout()));

	if(m_setup.vospd.type == 2)
	{
		queryTimer->start(2000);
	}

	return false;
}

// ------------------------------------------------------------------
VOSPD_SERVICE::~VOSPD_SERVICE()
{
	if(queryTimer)
	{
		queryTimer->stop();
		delete queryTimer;
		queryTimer = NULL;
	}
	if(stateTimer)
	{
		stateTimer->stop();
		delete stateTimer;
		stateTimer = NULL;
	}
	if(network_tcp[0])
	{
		network_tcp[0]->destroy();
		delete network_tcp[0];
		network_tcp[0] = NULL;
	}
	if(network_tcp[1])
	{
		network_tcp[1]->destroy();
		delete network_tcp[1];
		network_tcp[1] = NULL;
	}
	if(network_udp)
	{
		network_udp->close();
		delete network_udp;
		network_udp = NULL;
	}
}

// ------------------------------------------------------------------
bool VOSPD_SERVICE::isInitialized()
{
	return m_isInitialized;
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::setMain(bool main)
{
	if(main != m_cmdMain)
	{
		m_cmdMain = main;
		if(m_cmdMain)
			m_queryState = 0;
	}
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::onChangedAzimuthSource(quint32 channel)
{
	m_azimuthSource = channel;
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::timeout()
{
	if(m_counterState[0] > 1)
		m_counterState[0]--;
	else if(m_counterState[0] < -1)
		m_counterState[0]++;
	else if(m_counterState[0] != 0)
	{
		m_counterState[0] = 0;
		clearVospd(0);
	}

	if(m_counterState[1] > 1)
		m_counterState[1]--;
	else if(m_counterState[1] < -1)
		m_counterState[1]++;
	else if(m_counterState[1] != 0)
	{
		m_counterState[1] = 0;
		clearVospd(1);
	}

	emit sigState(m_VospdState, m_VospdValues);
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::queryTimeout()
{
	if(m_cmdMain && m_queryState >= 0)
	{
		switch(m_queryState)
		{
			case 0:
				sendRequestVersion(1);
				sendRequestVersion(2);
				break;

			case 1:
				sendRequestConfig(1);
				sendRequestConfig(2);
				break;

			case 2:
				sendFrameFormat(1, 1);
				sendFrameFormat(2, 1);
				break;

			case 3:
				sendRequestState(1);
				sendRequestState(2);
				break;

			case 4:
				sendRequestAngles(1);
				sendRequestAngles(2);
				break;

			case 5:
				sendRequestActSensor(1);
				sendRequestActSensor(2);
				break;
		}

		if(++m_queryState > 4)
		{
			m_queryState = 0;
		}
	}
	else
	{
		m_queryState = -1;
	}
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::onConnected(qint32 id, QHostAddress address, quint16 port)
{
	Q_UNUSED(address);
	Q_UNUSED(port);

	TcpNetwork * net = (TcpNetwork*)sender();
	if(!net)
		return;

	TcpNetworkConnection *c = net->connectionInfo(id);
	if(c)
	{
		if(c->peerAddress() == m_haVospd[0]) //vospd net
		{
			if(m_idVospd[0] == -1)
			{
				LogVospdInfo("VOSPD: id=%d connection %s", c->id(), qPrintable(c->peerAddress().toString()));
				//vospd connected
				m_idVospd[0] = c->id();
				m_counterState[0] = -STATEVOSPD_MAX_TIMEOUT;
				m_isConnected[0] = true;
				LogVospdInfo("VOSPD: connected 1");
				m_VospdState["vospd1@connected"] = ELEM_NORMA;

//				sendIpAddress(1);

				if(!queryTimer->isActive())
					queryTimer->start(1000);
			}

			m_dataVospd[0].clear();
			m_idVospd[0] = c->id();
		}
		if(c->peerAddress() == m_haVospd[1]) //vospd net
		{
			if(m_idVospd[1] == -1)
			{
				LogVospdInfo("VOSPD: id=%d connection %s", c->id(), qPrintable(c->peerAddress().toString()));
				//vospd connected
				m_idVospd[1] = c->id();
				m_counterState[1] = -STATEVOSPD_MAX_TIMEOUT;
				m_isConnected[1] = true;
				LogVospdInfo("VOSPD: connected 2");
				m_VospdState["vospd2@connected"] = ELEM_NORMA;

//				sendIpAddress(2);

				if(!queryTimer->isActive())
					queryTimer->start(1000);
			}

			m_dataVospd[1].clear();
			m_idVospd[1] = c->id();
		}
	}
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::onDisconnected(qint32 id)
{
	if(m_idVospd[0] == id) //vospd net
	{
		m_idVospd[0] = -1;
		m_dataVospd[0].clear();

		LogVospdInfo("VOSPD: id=%d disconnection", id);
		//vospd disconnected
		LogVospdInfo("VOSPD: disconnected 1");
		m_isConnected[0] = false;
		m_counterState[0] = 0;
		m_VospdState["vospd1@connected"] = ELEM_AVAR;
		clearVospd(0);
	}
	if(m_idVospd[1] == id) //vospd net
	{
		m_idVospd[1] = -1;
		m_dataVospd[1].clear();

		LogVospdInfo("VOSPD: id=%d disconnection", id);
		//vospd disconnected
		LogVospdInfo("VOSPD: disconnected 2");
		m_isConnected[1] = false;
		m_counterState[1] = 0;
		m_VospdState["vospd2@connected"] = ELEM_AVAR;
		clearVospd(1);
	}

	if(!m_isConnected[0] && !m_isConnected[1] && queryTimer != NULL)
		queryTimer->stop();
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::onDataArrived(QByteArray data, QHostAddress address, quint16 port)	//udp
{
	LogVospdBinary("VOSPD: recv from %s:%d: %s", qPrintable(address.toString()), port, LogArray(data));

	if(address == m_haVospd[0])
	{
		LogVospdBinary("VOSPD: processed: %s", qPrintable(QString(data)));
		m_dataVospd[0].append(data);
		while(m_dataVospd[0].parse())
		{
			QByteArray message = m_dataVospd[0].nextPendingMessage();
			if(!message.isEmpty())
				processMessage(0, message);
		}
	}
	else if(address == m_haVospd[1])
	{
//		LogVospdBinary("VOSPD: processed: %s", qPrintable(QString(data)));
		m_dataVospd[1].append(data);
		while(m_dataVospd[1].parse())
		{
			QByteArray message = m_dataVospd[1].nextPendingMessage();
			if(!message.isEmpty())
				processMessage(1, message);
		}
	}
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::onDataArrived(qint32 id, QByteArray data)	//tcp
{
	LogVospdBinary("VOSPD: recv con%d: %s", id, LogArray(data));

	if(sender() == network_tcp[0]) //vospd net
	{
		LogVospdBinary("VOSPD: [0] processed");
		m_dataVospd[0].append(data);
		while(m_dataVospd[0].parse())
		{
//qDebug() << "parsed 0" << endl;
			QByteArray message = m_dataVospd[0].nextPendingMessage();
			if(!message.isEmpty())
				processMessage(0, message);
		}
	}

	if(sender() == network_tcp[1]) //vospd net
	{
		LogVospdBinary("VOSPD: [1] processed");
		m_dataVospd[1].append(data);
		while(m_dataVospd[1].parse())
		{
//qDebug() << "parsed 1" << endl;
			QByteArray message = m_dataVospd[1].nextPendingMessage();
			if(!message.isEmpty())
				processMessage(1, message);
		}
	}
}

// ------------------------------------------------------------------
bool VOSPD_SERVICE::processMessage(quint32 n_vospd, const QByteArray & message)
{
	if(message.isEmpty() || message.size() < 6)
		return true;

	unsigned char type = (unsigned char)(message[3]);

	LogVospdInfo("VospdService: [%d] message type %d", n_vospd, (unsigned int)type);

/*
	RequestVersion		= 0x01,
	RequestState		= 0x02,
	SetConfig		= 0x03,
	RequestAngles		= 0x04,
	SetResetFailure		= 0x05,
	RequestConfig		= 0x06,
	SetFrameFormat		= 0x07,
	SetActiveSensor		= 0x08,
	RequestError		= 0x09,
	SetAzCorrection		= 0x0A,
	SetAzImitator		= 0x0B,
	TestCoreManch		= 0x0C,
	SetIpAddress		= 0x0D,
	RequestActSensor	= 0x0E
*/

	switch(type)
	{
		case RequestVersion:
		{
			return processVersion(n_vospd, message);
		}
		case RequestState:
		{
			return processState(n_vospd, message);
		}
		case RequestConfig:
		{
			return processConfig(n_vospd, message);
		}
		case RequestAngles:
		{
			return processAngles(n_vospd, message);
		}
		case SetFrameFormat:
		{
			return processFrameFormat(n_vospd, message);
		}
		case SetActiveSensor:
		{
			return processSetActiveSensor(n_vospd, message);
		}
		case RequestActSensor:
		{
			return processActiveSensor(n_vospd, message);
		}
		default:
		{
			LogVospdError("VospdService: [%d] Unknown message type %d", n_vospd, (unsigned int)type);
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------
bool VOSPD_SERVICE::processVersion(quint32 n_vospd, const QByteArray & message)
{
	if( (message.size() != (int)AnswerVersionLength) || ((unsigned char)message[2] != AnswerVersionLength) )
	{
		LogVospdError("VOSPD: invalid message length (recv %d != await %d", (unsigned int)(unsigned char)message[2], AnswerVersionLength);
		return true;
	}

	LogVospdInfo("VospdService: [%d] message Version", n_vospd);

	QString N_VOSPD = QString("vospd%1").arg(n_vospd + 1);

	VospdAnswerVersion msg(message);

	if(msg.Major_Top == 0 && msg.Minor_Top == 0 && msg.Patch_Top == 0)
	{
		m_VospdState[N_VOSPD + "@top_version"] = ELEM_NOT;
		m_VospdValues[N_VOSPD + "@top_version"] = QString("");
	}
	else
	{
		m_VospdState[N_VOSPD + "@top_version"] = ELEM_NORMA;
		m_VospdValues[N_VOSPD + "@top_version"] = QString("Версия ПЛИС %1.%2.%3").arg(msg.Major_Top).arg(msg.Minor_Top).arg(msg.Patch_Top);
	}


	if(msg.Major_Bot == 0 && msg.Minor_Bot == 0 && msg.Patch_Bot == 0)
	{
		m_VospdState[N_VOSPD + "@bot_version"] = ELEM_NOT;
		m_VospdValues[N_VOSPD + "@bot_version"] = QString("");
	}
	else
	{
		m_VospdState[N_VOSPD + "@bot_version"] = ELEM_NORMA;
		m_VospdValues[N_VOSPD + "@bot_version"] = QString("Версия ПЛИС %1.%2.%3").arg(msg.Major_Bot).arg(msg.Minor_Bot).arg(msg.Patch_Bot);
	}

	updateCommonState();

	m_counterState[n_vospd] = STATEVOSPD_MAX_TIMEOUT;

	return false;
}

// ------------------------------------------------------------------
bool VOSPD_SERVICE::processState(quint32 n_vospd, const QByteArray & message)
{
	if( (message.size() != (int)AnswerStatusLength) || ((unsigned char)message[2] != AnswerStatusLength) )
	{
		LogVospdError("VOSPD: invalid message length (recv %d != await %d", (unsigned int)(unsigned char)message[2], AnswerStatusLength);
		return true;
	}

	LogVospdInfo("VospdService: [%d] message Status", n_vospd);

	VospdAnswerStatus msg(message);
	updateStatus(n_vospd, msg.status);
	updateCommonState();

	m_counterState[n_vospd] = STATEVOSPD_MAX_TIMEOUT;

	return false;
}

// ------------------------------------------------------------------
bool VOSPD_SERVICE::processAngles(quint32 n_vospd, const QByteArray & message)
{
	if( (message.size() != (int)AnswerAnglesLength) || ((unsigned char)message[2] != AnswerAnglesLength) )
	{
		LogVospdError("VOSPD: invalid message length (recv %d != await %d", (unsigned int)(unsigned char)message[2], AnswerAnglesLength);
		return true;
	}

	LogVospdInfo("VospdService: [%d] message Angles", n_vospd);

	VospdAnswerAngles msg(message);
	updateAngles(n_vospd, msg);
	updateCommonState();

	m_counterState[n_vospd] = STATEVOSPD_MAX_TIMEOUT;

	return false;
}

// ------------------------------------------------------------------
bool VOSPD_SERVICE::processFrameFormat(quint32 n_vospd, const QByteArray & message)
{
	if( (message.size() != (int)AnswerStatusLength) || ((unsigned char)message[2] != AnswerStatusLength) )
	{
		LogVospdError("VOSPD: invalid message length (recv %d != await %d", (unsigned int)(unsigned char)message[2], AnswerStatusLength);
		return true;
	}

	LogVospdInfo("VospdService: [%d] message FrameFormat", n_vospd);

	VospdAnswerStatus msg(message);
	updateStatus(n_vospd, msg.status);
	updateCommonState();

	m_counterState[n_vospd] = STATEVOSPD_MAX_TIMEOUT;

	return false;
}

// ------------------------------------------------------------------
bool VOSPD_SERVICE::processActiveSensor(quint32 n_vospd, const QByteArray & message)
{
	if( (message.size() != (int)AnswerActSensorLength) || ((unsigned char)message[2] != AnswerActSensorLength) )
	{
		LogVospdError("VOSPD: invalid message length (recv %d != await %d", (unsigned int)(unsigned char)message[2], AnswerActSensorLength);
		return true;
	}

	LogVospdInfo("VospdService: [%d] message ActSensor", n_vospd);

	VospdAnswerActSensor msg(message);
	updateActSensor(n_vospd, msg.act_sensor);
	updateCommonState();

	m_counterState[n_vospd] = STATEVOSPD_MAX_TIMEOUT;

	return false;
}

// ------------------------------------------------------------------
bool VOSPD_SERVICE::processSetActiveSensor(quint32 n_vospd, const QByteArray & message)
{
	if( (message.size() != (int)AnswerStatusLength) || ((unsigned char)message[2] != AnswerStatusLength) )
	{
		LogVospdError("VOSPD: invalid message length (recv %d != await %d", (unsigned int)(unsigned char)message[2], AnswerStatusLength);
		return true;
	}

	LogVospdInfo("VospdService: [%d] message SetActSensor", n_vospd);

	VospdAnswerStatus msg(message);
	updateStatus(n_vospd, msg.status);
	updateCommonState();

	m_counterState[n_vospd] = STATEVOSPD_MAX_TIMEOUT;

	return false;
}

// ------------------------------------------------------------------
bool VOSPD_SERVICE::processConfig(quint32 n_vospd, const QByteArray & message)
{
	if( (message.size() != (int)AnswerConfigLength) || ((unsigned char)message[2] != AnswerConfigLength) )
	{
		LogVospdError("VOSPD: invalid message length (recv %d != await %d", (unsigned int)(unsigned char)message[2], AnswerConfigLength);
		return true;
	}

	LogVospdInfo("VospdService: [%d] message Config", n_vospd);

	VospdAnswerConfig msg(message);
	updateStatus(n_vospd, msg.status);
	updateConfig(n_vospd, msg.config);
	updateCorrections(n_vospd, msg.az1_cfg, msg.az2_cfg);

	m_counterState[n_vospd] = STATEVOSPD_MAX_TIMEOUT;

	return false;
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::clearVospd(quint32 n_vospd)
{
//	m_VospdState.clear(ELEM_NOT);
//	m_VospdValues.clear();

	LogInfo("VOSPD_SERVICE: [%d] clear vospd", n_vospd);

	QString N_VOSPD = QString("vospd%1@").arg(n_vospd + 1);

	AskuBinStateSet::iterator it1;
	for(it1 = m_VospdState.begin(); it1 != m_VospdState.end(); ++it1)
	{
		if(it1.key().startsWith(N_VOSPD) && !it1.key().endsWith("@connected"))
		{
			if(it1.value() != ELEM_NOT)
			{
				it1.value() = ELEM_NOT;
			}
		}
	}

	if(m_VospdState[N_VOSPD + "connected"] == ELEM_NORMA)
		m_VospdState[N_VOSPD + "bot_main"] = ELEM_AVAR;
	else if(m_VospdState[N_VOSPD + "connected"] == ELEM_NOT)
		m_VospdState[N_VOSPD + "connected"] = ELEM_AVAR;

	AskuValueSet::iterator it2;
	for(it2 = m_VospdValues.begin(); it2 != m_VospdValues.end(); ++it2)
	{
		if(it2.key().startsWith(QString("vospd%1@").arg(n_vospd + 1)))
		{
			if(it2.value() != ELEM_NOT)
			{
				it2.value() = QString("");
			}
		}
	}

	updateCommonState();
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::sendToVospd(QByteArray message, qint32 n_vospd)
{
//	LogVospdBinary("VOSPD: send: %s", qPrintable(QString(message)));

	if(m_setup.vospd.type == 1)
	{
		if(m_idVospd[0] != -1 && (n_vospd == -1 || n_vospd == 1)) //vospd net
		{
			if(network_tcp[0])
			{
				LogVospdBinary("VOSPD: [0] send con%d: %s", m_idVospd[0], LogArray(message));
				network_tcp[0]->sendReply(m_idVospd[0], message);
			}
		}

		if(m_idVospd[1] != -1 && (n_vospd == -1 || n_vospd == 2)) //vospd net
		{
			if(network_tcp[1])
			{
				LogVospdBinary("VOSPD: [1] send con%d: %s", m_idVospd[1], LogArray(message));
				network_tcp[1]->sendReply(m_idVospd[1], message);
			}
		}
	}
	else if(m_setup.vospd.type == 2)
	{

		if(n_vospd == -1 || n_vospd == 1) //vospd net
		{
			if(network_udp)
			{
				LogVospdBinary("VOSPD: send (%s:%d): %s", qPrintable(m_haVospd[0].toString()), m_portOur, qPrintable(LogArray(message)));
				network_udp->sendReply(message, m_haVospd[0], m_portOur);
			}
		}

		if(n_vospd == -1 || n_vospd == 2) //vospd net
		{
			if(network_udp)
			{
				LogVospdBinary("VOSPD: send (%s:%d): %s", qPrintable(m_haVospd[1].toString()), m_portOur, qPrintable(LogArray(message)));
				network_udp->sendReply(message, m_haVospd[1], m_portOur);
			}
		}
	}
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::sendRequestVersion(qint32 n_vospd)
{
	VospdRequestVersion message;
	sendToVospd(message, n_vospd);
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::sendRequestState(qint32 n_vospd)
{
	VospdRequestState message;
	sendToVospd(message, n_vospd);
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::sendRequestAngles(qint32 n_vospd)
{
	VospdRequestAngles message;
	sendToVospd(message, n_vospd);
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::sendFrameFormat(qint32 n_vospd, quint8 format)
{
	LogInfo("VOSPD: sendFrameFormat %d", format);
	VospdSetFrameFormat message(format);
	sendToVospd(message, n_vospd);
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::sendIpAddress(qint32 n_vospd)
{
	if(n_vospd == 1)
	{
		VospdSetIpAddress message(QHostAddress("192.0.1.110"), QHostAddress("255.255.255.0"), QHostAddress("0.0.0.0"));
		sendToVospd(message, n_vospd);
	}
	if(n_vospd == 2)
	{
		VospdSetIpAddress message(QHostAddress("192.0.1.111"), QHostAddress("255.255.255.0"), QHostAddress("0.0.0.0"));
		sendToVospd(message, n_vospd);
	}
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::sendImitator(qint32 n_vospd, bool on)
{
	VospdSetImitator message(on);
	sendToVospd(message, n_vospd);
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::sendRequestActSensor(qint32 n_vospd)
{
	VospdRequestActiveSensor message;
	sendToVospd(message, n_vospd);
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::sendRequestConfig(qint32 n_vospd)
{
	VospdRequestConfig message;
	sendToVospd(message, n_vospd);
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::sendActiveSensor(qint32 n_vospd, quint8 sensor)
{
	VospdSetActiveSensor message(sensor);
	sendToVospd(message, n_vospd);
}

// ------------------------------------------------------------------
