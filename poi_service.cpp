#include <qjson/parser.h>
#include <qjson/serializer.h>
#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "poi_service.h"
#include "poi_thread.h"

// ------------------------------------------------------------------
POI_SERVICE::POI_SERVICE(POI_THREAD *p)
{
	parent = p;
	network = NULL;
	timer = NULL;

	m_isInitialized = false;
	m_isConnected = false;
	m_counterState = 0;

	m_poiConfig.main = false;
	m_poiConfig.temperature = 25.0;

	m_portOur = m_setup.poi.port;
	m_haPoi = m_setup.poi.ip;

	m_idPoi = -1;
}

// ------------------------------------------------------------------
bool POI_SERVICE::init()
{
	network = new TcpNetwork(this, QString("POI_TCP"));
	if(network)
	{
		connect(network, SIGNAL(sigConnected(qint32,QHostAddress,quint16)), this, SLOT(onConnected(qint32,QHostAddress,quint16)));
		connect(network, SIGNAL(sigDisconnected(qint32)), this, SLOT(onDisconnected(qint32)));
		connect(network, SIGNAL(dataArrived(qint32, QByteArray)), this, SLOT(onDataArrived(qint32, QByteArray)));

		LogPoiInfo("PoiService started");
		m_isInitialized = network->init(m_portOur);
	}

	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
	timer->start(1000);

	return false;
}

// ------------------------------------------------------------------
POI_SERVICE::~POI_SERVICE()
{
	if(timer)
	{
		timer->stop();
		delete timer;
		timer = NULL;
	}
	if(network)
	{
		network->destroy();
		delete network;
		network = NULL;
	}
}

// ------------------------------------------------------------------
bool POI_SERVICE::isInitialized()
{
	return m_isInitialized;
}

// ------------------------------------------------------------------
void POI_SERVICE::setMain(bool main)
{
	if(main != m_poiConfig.main)
	{
		m_poiConfig.main = main;
		syncToSlave();
	}
}

// ------------------------------------------------------------------
void POI_SERVICE::setConnectedGpr()
{
}

// ------------------------------------------------------------------
void POI_SERVICE::setDisconnectedGpr()
{
	clearOtherState();
}

// ------------------------------------------------------------------
void POI_SERVICE::setTemperature(double temp)
{
	if(m_poiConfig.temperature != temp)
	{
		m_poiConfig.temperature = temp;
		sendTemperature();
	}
}

// ------------------------------------------------------------------
void POI_SERVICE::timeout()
{
	if(m_counterState > 0)
		m_counterState--;
	else if(m_counterState < 0)
		m_counterState++;
	else
	{
		if(m_isConnected)
		{
			bPoiLocalState["ObSost"] = ELEM_AVAR;
			bPoiLocalState["dsp"] = ELEM_AVAR;
		}
		else
		{
			bPoiLocalState["ObSost"] = ELEM_NOT;
			bPoiLocalState["dsp"] = ELEM_NOT;
		}

		emit sigStateLocal(bPoiLocalState);
		syncToSlave();
	}
}

// ------------------------------------------------------------------
void POI_SERVICE::onConnected(qint32 id, QHostAddress address, quint16 port)
{
	Q_UNUSED(address);
	Q_UNUSED(port);

	TcpNetworkConnection *c = network->connectionInfo(id);

	if(c && (c->peerAddress() == m_haPoi) && (m_idPoi == -1)) //poi network
	{
		//poi connected
		m_idPoi = c->id();
		m_counterState = -POI_STATEDSP_TIMEOUT;
		m_isConnected = true;
		LogPoiInfo("POI: connected poi");
		bPoiLocalState["connected"] = ELEM_NORMA;
		m_dataPoi.clear();
		m_idPoi = c->id();
	}
}

// ------------------------------------------------------------------
void POI_SERVICE::onDisconnected(qint32 id)
{
	if(m_idPoi == id) //poi network
	{
		m_idPoi = -1;
		m_dataPoi.clear();
		//poi disconnected
		LogPoiInfo("POI: disconnected poi");
		m_isConnected = false;
		m_counterState = 0;
		clearLocalState();
	}
}

// ------------------------------------------------------------------
void POI_SERVICE::onDataArrived(qint32 id, QByteArray data)
{
//	LogPoiBinary("POI: id=%d data=%s", id, qPrintable(LogArray(data)));
	LogPoiBinary("POI: recv con=%d : %s", id, LogArray(data));

	if(m_idPoi == id) //poi network
	{
		LogPoiBinary("POI: processed poi: %s", qPrintable(QString(data)));
		m_dataPoi.append(data);
		while(m_dataPoi.parse())
		{
			QVariantMap message = m_dataPoi.nextPendingMessage().toMap();
			if(!message.isEmpty())
				processMessage(message);
		}
	}
}

// ------------------------------------------------------------------
bool POI_SERVICE::processMessage(const QVariantMap & message)
{
	if(message.isEmpty())
		return true;

	QString messageType = message["name"].toString();
	if(messageType == "noise factor")
	{
		processNoiseFactor(message);
	}
	else if(messageType == "DSP state")
	{
		processDspState(message);
	}
	else if(messageType == "SHARU")
	{
		processSharu(message);
	}
	else if(messageType == "pilot")
	{
		processPilot(message);
	}
	else if(messageType == "transmitter")
	{
		processTransmitter(message);
	}
	else if(messageType == "suppression")
	{
		processSuppression(message);
	}
	else
	{
		LogPoiError("PoiService: Unknown message type \"%s\"", qPrintable(messageType));
		return true;
	}
	return false;
}

// ------------------------------------------------------------------
bool POI_SERVICE::processNoiseFactor(const QVariantMap & message)
{
	LogPoiInfo("PoiService: processNoiseFactor");

	quint32 channelCount = message["channel count"].toUInt();

	if(channelCount != 2)
	{
		LogPoiError("PoiService: invalid channel count in message (%d)", channelCount);
		return false;
	}

	QVariantList channels = message["channels"].toList();

	if((quint32)channels.count() != channelCount)
	{
		LogPoiError("PoiService: invalid channel list in message (%d)", channels.count());
		return false;
	}

	bool ok = false;
	bool valid = false;
	quint32 ticks = message["SHARU time"].toUInt(&ok);
	if(ok)
	{
		bPoiLocalKoeff["sharu_time"] = ticks;
		if(ticks)
			valid = true;
	}

	for(quint32 n = 0; n < channelCount; n++)
	{
		QString nCh = QString("%1").arg(n + 1);
		QVariantMap channel = channels[n].toMap();

		bool ok = false;
		double value;

		value = channel["self noise"].toDouble(&ok);
		if(ok && valid)
			bPoiLocalKoeff["sshr" + nCh] = value;

		value = channel["noise factor"].toDouble(&ok);
		if(ok && valid)
			bPoiLocalKoeff["ksh" + nCh] = value;

		value = channel["generator noise"].toDouble(&ok);
		if(ok && valid)
			bPoiLocalKoeff["gsh" + nCh] = value;

		value = channel["generator temperature"].toDouble(&ok);
		if(ok)
			bPoiLocalKoeff["sht" + nCh] = value;
	}

	emit sigKoeffLocal(bPoiLocalKoeff);
	syncToSlave();

	return false;
}

// ------------------------------------------------------------------
bool POI_SERVICE::processDspState(const QVariantMap & message)
{
	LogPoiInfo("PoiService: processDspState");

	m_counterState = POI_STATEDSP_TIMEOUT;

	QString state = message["state"].toString();

	if(state == "good")
	{
		bPoiLocalState["ObSost"] = ELEM_NORMA;
		bPoiLocalState["dsp"] = ELEM_NORMA;
	}
	else if(state == "bad")
	{
		bPoiLocalState["ObSost"] = ELEM_AVAR;
		bPoiLocalState["dsp"] = ELEM_AVAR;
	}

	emit sigStateLocal(bPoiLocalState);
	syncToSlave();

	return false;
}

// ------------------------------------------------------------------
bool POI_SERVICE::processSharu(const QVariantMap & message)
{
	LogPoiInfo("PoiService: processSharu");

	QVariantMap sum = message["sum"].toMap();
	QVariantMap dif = message["dif"].toMap();

	if(sum.isEmpty() || dif.isEmpty())
		return false;

	bool ok = false;
	double value;

	for(quint32 n = 0; n < 2; n++)
	{
		QString nCh = QString("%1").arg(n+1);
		QVariantMap channel;
		if(n == 0)
			channel = sum;
		if(n == 1)
			channel = dif;

		value = channel["self noise"].toDouble(&ok);
		if(ok)
			bPoiLocalKoeff["ssh" + nCh] = value;

		bool overflow  = channel["overflow"].toUInt();
		if(overflow)
			bPoiLocalState["sharu_overflow" + nCh] = ELEM_AVAR;
		else
			bPoiLocalState["sharu_overflow" + nCh] = ELEM_NORMA;

		bool underflow = channel["underflow"].toUInt();
		if(underflow)
			bPoiLocalState["sharu_underflow" + nCh] = ELEM_AVAR;
		else
			bPoiLocalState["sharu_underflow" + nCh] = ELEM_NORMA;
	}

	emit sigStateLocal(bPoiLocalState);
	emit sigKoeffLocal(bPoiLocalKoeff);
	syncToSlave();

	return false;
}

// ------------------------------------------------------------------
bool POI_SERVICE::processPilot(const QVariantMap & message)
{
	LogPoiInfo("PoiService: processPilot");

	QVariantList channels = message["value"].toList();

	quint32 channelCount = channels.count();

	if(channelCount != 24)
	{
		LogPoiError("PoiService: invalid channels count in pilot message (%d)", channelCount);
		return false;
	}

	for(quint32 n = 0; n < channelCount; n++)
	{
		QString nCh = QString("%1").arg(n + 1);
		QVariantMap channel = channels[n].toMap();

		bool ok = false;
		double value;

		value = channel["mag"].toDouble(&ok);
		if(ok)
			bPoiLocalPilot["mag" + nCh] = value;

		value = channel["sup"].toDouble(&ok);
		if(ok)
			bPoiLocalPilot["sup" + nCh] = value;
	}

	emit sigPilotLocal(bPoiLocalPilot);
	syncToSlave();

	return false;
}

// ------------------------------------------------------------------
bool POI_SERVICE::processTransmitter(const QVariantMap & message)
{
	LogPoiInfo("PoiService: processTransmitter");

	QVariantMap sample = message["sample"].toMap();
	
	bool ok = false;
	double value;

	value = sample["phase"].toDouble(&ok);
	if(ok)
		bPoiLocalTrans["phase"] = value;

	value = sample["magnitude"].toDouble(&ok);
	if(ok)
		bPoiLocalTrans["magnitude"] = value;

//	emit sigTransmitterLocal(bPoiLocalTrans);
//	syncToSlave();

	return false;
}

// ------------------------------------------------------------------
bool POI_SERVICE::processSuppression(const QVariantMap & message)
{
	LogPoiInfo("PoiService: processSuppression");

	Q_UNUSED(message);

//	TODO...

	return false;
}

// ------------------------------------------------------------------
void POI_SERVICE::setResetKoeff()
{
//	bPoiLocalKoeff = AskuValueSet();
//	bPoiLocalPilot = AskuValueSet();

	bPoiLocalKoeff.clear();
	bPoiLocalPilot.clear();
	bPoiLocalKoeff["sharu_time"] = "";

	emit sigKoeffLocal(bPoiLocalKoeff);
	emit sigPilotLocal(bPoiLocalPilot);

	syncToSlave();
}

// ------------------------------------------------------------------
void POI_SERVICE::clearLocalState()
{
	bPoiLocalTrans.clear();
	bPoiLocalKoeff.clear();
	bPoiLocalPilot.clear();
	bPoiLocalState.clear(ELEM_NOT);

	bPoiLocalState["connected"] = ELEM_AVAR;

	emit sigStateLocal(bPoiLocalState);
	emit sigKoeffLocal(bPoiLocalKoeff);
	emit sigPilotLocal(bPoiLocalPilot);

	syncToSlave();
}

// ------------------------------------------------------------------
void POI_SERVICE::clearOtherState()
{
	bPoiOtherTrans.clear();
	bPoiOtherKoeff.clear();
	bPoiOtherPilot.clear();
	bPoiOtherState.clear(ELEM_NOT);

	emit sigStateOther(bPoiOtherState);
	emit sigKoeffOther(bPoiOtherKoeff);
	emit sigPilotOther(bPoiOtherPilot);
}

// ------------------------------------------------------------------
void POI_SERVICE::sendToPoi(QVariantMap message)
{
	QJson::Serializer serializer;
	QByteArray json = serializer.serialize(message);

	if(!json.isEmpty())
	{
//		LogPoiBinary("POI: send: %s", qPrintable(QString(json)));

		if(network && m_idPoi != -1) //poi network
		{
			LogPoiBinary("POI: send poi: %s", LogArray(json));
			network->sendReply(m_idPoi, json);
		}
	}
}

// ------------------------------------------------------------------
void POI_SERVICE::sendTemperature()
{
	QVariantMap message;
	message["name"] = "temperature";
	message["temperature"] = (signed int)m_poiConfig.temperature;
	sendToPoi(message);
}

// ------------------------------------------------------------------
void POI_SERVICE::syncToSlave()
{
	emit sigSyncToSlave(m_poiConfig.toMap(), bPoiLocalState.toMap(), bPoiLocalKoeff.toMap(), bPoiLocalPilot.toMap());
}

// ------------------------------------------------------------------
void POI_SERVICE::onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff, QVariantMap pilot)
{
	if(!m_poiConfig.main)
	{
		PoiConfig m_masterConfig(config);
		if(m_masterConfig.main)
		{
			LogPoiInfo("POI_SERVICE::onSyncToSlave processed");
			setTemperature(m_masterConfig.temperature);
//			qDebug() << "poiMasterConfig accepted";
		}
	}

//	qDebug() << "onSyncToSlave";
//	qDebug() << bPoiOtherState.toMap();
//	qDebug() << bPoiOtherKoeff.toMap();
//	qDebug() << bPoiOtherPilot.toMap();
//	qDebug() << "-------------";

	if(bPoiOtherState.fromMap(state))
		emit sigStateOther(bPoiOtherState);

	if(bPoiOtherKoeff.fromMap(koeff))
		emit sigKoeffOther(bPoiOtherKoeff);

	if(bPoiOtherPilot.fromMap(pilot))
		emit sigPilotOther(bPoiOtherPilot);
}

// ------------------------------------------------------------------
