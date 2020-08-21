#include <qjson/parser.h>
#include <qjson/serializer.h>
#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "pos_service.h"
#include "pos_thread.h"

// ------------------------------------------------------------------
AskuPosAlarm::AskuPosAlarm(quint32 timeout, quint32 delay)
{
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));

	m_avar = false;
	m_main = false;
	m_connected = false;

    m_state = ELEM_NOT;
	m_timeout = timeout;
	m_delay = delay;
}

// ------------------------------------------------------------------
AskuPosAlarm::~AskuPosAlarm()
{
	if(m_timer)
	{
		m_timer->stop();
		delete m_timer;
		m_timer = NULL;
	}
}

// ------------------------------------------------------------------
void AskuPosAlarm::setMain(bool main)
{
	m_main = main;

	if(m_main && m_connected)
	{
		if(!m_avar)
			m_timer->start(m_delay);
	}
}

// ------------------------------------------------------------------
void AskuPosAlarm::setConnected(bool connected)
{
	m_connected = connected;
	if(!connected)
	{
		m_avar = false;
		m_state = ELEM_NOT;
		m_timer->stop();
	}
}

// ------------------------------------------------------------------
void AskuPosAlarm::timeout()
{
	m_timer->stop();

	if(!m_connected)
		m_state = ELEM_NOT;
	else if(m_avar)
		m_state = ELEM_AVAR;
	else
		m_state = ELEM_NORMA;
}

// ------------------------------------------------------------------
void AskuPosAlarm::acivate()
{
	m_avar = true;
}

// ------------------------------------------------------------------
POS_SERVICE::POS_SERVICE(POS_THREAD *p)
{
	parent = p;
	network = NULL;
	timer = NULL;
	pingTimer = NULL;

	m_isInitialized = false;
	m_isConnected = false;
	m_counterState = 0;

	m_cmdMain = false;

	m_portOur = m_setup.pos.port;
	m_haPos = m_setup.pos.ip;
	m_idPos = -1;
}

// ------------------------------------------------------------------
bool POS_SERVICE::init()
{
	network = new TcpNetwork(this, QString("POS_TCP"));
	if(network)
	{
		connect(network, SIGNAL(sigConnected(qint32,QHostAddress,quint16)), this, SLOT(onConnected(qint32,QHostAddress,quint16)));
		connect(network, SIGNAL(sigDisconnected(qint32)), this, SLOT(onDisconnected(qint32)));
		connect(network, SIGNAL(dataArrived(qint32, QByteArray)), this, SLOT(onDataArrived(qint32, QByteArray)));

		LogPosInfo("PosService started");
		m_isInitialized = network->init(m_haPos, m_portOur);
	}

	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
	timer->start(1000);

	pingTimer = new QTimer(this);
	connect(pingTimer,SIGNAL(timeout()),this,SLOT(pingTimeout()));

	return false;
}

// ------------------------------------------------------------------
POS_SERVICE::~POS_SERVICE()
{
	if(pingTimer)
	{
		pingTimer->stop();
		delete pingTimer;
		pingTimer = NULL;
	}
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
bool POS_SERVICE::isInitialized()
{
	return m_isInitialized;
}

// ------------------------------------------------------------------
void POS_SERVICE::setMain(bool main)
{
	if(main != m_cmdMain)
	{
		m_cmdMain = main;
	}
}

// ------------------------------------------------------------------
void POS_SERVICE::timeout()
{
	if(m_counterState > 0)
		m_counterState--;
	else if(m_counterState < 0)
		m_counterState++;
	else
	{
		if(m_isConnected)
			bPosState["ObSost"] = ELEM_AVAR;
		else
			bPosState["ObSost"] = ELEM_NOT;

		emit sigState(bPosState);
	}
}

// ------------------------------------------------------------------
void POS_SERVICE::pingTimeout()
{
	sendPing();
}

// ------------------------------------------------------------------
void POS_SERVICE::onConnected(qint32 id, QHostAddress address, quint16 port)
{
	Q_UNUSED(address);
	Q_UNUSED(port);
    flag_connect_osv_perim = true;
	TcpNetworkConnection *c = network->connectionInfo(id);
	if(c)
	{
		if(c->peerAddress() == m_haPos) //pos net
		{
			if(m_idPos == -1)
			{
				LogPosInfo("POS: id=%d connection", id);
				//pos connected
				m_idPos = c->id();
				m_counterState = -STATEPOS_MAX_TIMEOUT;
				m_isConnected = true;
				LogPosInfo("POS: connected");
				bPosState["connected"] = ELEM_NORMA;
//-----------чел---
                bPosState["stateKsb"] = ELEM_NORMA;
                bPosState["alarm"] = ELEM_NORMA;
                bPosState["portal"] = ELEM_NORMA;
                bPosState["perimetr"] = ELEM_NORMA;
                bPosState["dolphin"] = ELEM_NORMA;
                bPosState["gatePerimetr"] = ELEM_NORMA;
                bPosState["gateCase"] = ELEM_NORMA;
                bPosState["fireCase"] = ELEM_NORMA;
                bPosState["fireAlarmCase"] = ELEM_NORMA;
                bPosState["gateDes"] = ELEM_NORMA;
                bPosState["fireDes"] = ELEM_NORMA;
                bPosState["fireAlarmDes"] = ELEM_NORMA;
                emit sigState(bPosState);
                emit sigEventToLog("КСБ", "Соединение успешно установлено", "event");
//-----------чел---
				sendPing();
				pingTimer->start(5000);
			}

			m_dataPos.clear();
			m_idPos = id;
		}
	}
}

// ------------------------------------------------------------------
void POS_SERVICE::onDisconnected(qint32 id)
{
	if(m_idPos == id) //pos net
	{
		pingTimer->stop();

//-----------чел---
        emit sigEventToLog("КСБ", "Соединение сброшено", "alert");
//-----------чел---

		m_idPos = -1;
		m_dataPos.clear();

		LogPosInfo("POS: id=%d disconnection", id);
		//pos disconnected
		LogPosInfo("POS: disconnected");
		m_isConnected = false;
		m_counterState = 0;
		bPosState["connected"] = ELEM_AVAR;
		clearPos();
	}
}

// ------------------------------------------------------------------
void POS_SERVICE::onDataArrived(qint32 id, QByteArray data)
{
	LogPosBinary("POS: recv con%d: %s", id, LogArray(data));

	if(m_idPos == id) //pos net
	{
		LogPosBinary("POS: processed: %s", qPrintable(QString(data)));
		m_dataPos.append(data);
		while(m_dataPos.parse())
		{
			QVariantMap message = m_dataPos.nextPendingMessage().toMap();
			if(!message.isEmpty())
				processMessage(message);
		}
	}
}

// ------------------------------------------------------------------
bool POS_SERVICE::processMessage(const QVariantMap & message)
{
	if(message.isEmpty())
		return true;

	if(!message.contains("command"))
	{
		LogPosError("POS_SERVICE: invalid message - \"command\" is missing");
		return true;
	}

	QString command = message["command"].toString();

	if(command == "pingAnswer")
	{
		return processPingAnswer(message);
	}
	else if(command == "alert")
	{
		return processAlert(message);
	}
	else if(command == "alertPassed")
	{
		return processAlertPassed(message);
	}
	else if(command == "event")
	{
		return processEvent(message);
	}
//-----------чел---
    else if(command == "relay"){
        return processRelay(message);
    }
//-----------чел---
	else
	{
		LogPosError("POS_SERVICE: unknown command type \"%s\"", qPrintable(command));
		return true;
	}

	return false;
}

// ------------------------------------------------------------------
bool POS_SERVICE::processPingAnswer(const QVariantMap & message)
{
    if(message["alertsCount"] == 0){
//-----------чел---
        bPosState["stateKsb"] = ELEM_NORMA;
        bPosState["alarm"] = ELEM_NORMA;
        /*
        bPosState["alarm"] = ELEM_NORMA;
        bPosState["portal"] = ELEM_NORMA;
        bPosState["perimetr"] = ELEM_NORMA;
        bPosState["dolphin"] = ELEM_NORMA;
        bPosState["gatePerimetr"] = ELEM_NORMA;
        bPosState["gateCase"] = ELEM_NORMA;
        bPosState["fireCase"] = ELEM_NORMA;
        bPosState["fireAlarmCase"] = ELEM_NORMA;
        bPosState["gateDes"] = ELEM_NORMA;
        bPosState["fireDes"] = ELEM_NORMA;
        bPosState["fireAlarmDes"] = ELEM_NORMA;
        */
    }else{
        bPosState["stateKsb"] = ELEM_AVAR;
        bPosState["alarm"] = ELEM_AVAR;
    }
    emit sigState(bPosState);
    m_counterState = STATEPOS_MAX_TIMEOUT;
//-----------чел---
	return false;
}

// ------------------------------------------------------------------
bool POS_SERVICE::processAlert(const QVariantMap & message)
{

    //Если появилась тревога, то создадим объект тревоги или события и добавим его
    //в список тревог которые могут быть записаны в лог
    //этим занимается отдельная функция
    if(MapEventToLog.contains(message["alertId"].toUInt()) != true){
        PosEventToLog temp;
        temp.name = message["sensor"].toString();
        temp.type = "alert";
        temp.state = true;
        temp.lastState = false;
        temp.zone = message["zone"].toString();
        MapEventToLog.insert(message["alertId"].toUInt(), temp);
    }
	quint32 zoneId = message["zoneId"].toUInt();
	quint32 sensorId = message["sensorId"].toUInt();
    quint32 alertId = message["alertId"].toUInt();
    pos_Accord_AlertId_SensorId.insert(alertId, sensorId);
    bPosState["alarm"] = ELEM_AVAR;
    if(zoneId == 2)	//УРЛК
    {
        switch(sensorId)
        {
        case 5:	//Дверь УРЛК
            bPosState["gateCase"] = ELEM_AVAR;
            break;

        case 6:	//Пожарная тревога УРЛК
            bPosState["fireCase"] = ELEM_AVAR;
            break;

        case 7:	//Неисправность пожарной сигнализации УРЛК
            bPosState["fireAlarmCase"] = ELEM_AVAR;
            break;
        }
        //-----------чел---
    } else if(zoneId == 1){  // Периметр
        switch(sensorId)
        {
        case 1:  // Ворота
            bPosState["portal"] = ELEM_AVAR;
            break;

        case 2:	 // Нарушение периметра
            bPosState["perimetr"] = ELEM_AVAR;
            break;

        case 3:	 // Датчик вскрытия дельфина
            bPosState["dolphin"] = ELEM_AVAR;
            break;

        case 4:	 // Калитка вход
            bPosState["gatePerimetr"] = ELEM_AVAR;
            break;
        }
    } else if(zoneId == 3){  // ДЭС
        switch(sensorId)
        {
        case 8:	 // Дверь вход
            bPosState["gateDes"] = ELEM_AVAR;
            break;

        case 9:	 // Пожарная тревога
            bPosState["fireDes"] = ELEM_AVAR;
            break;

        case 10:  // Неисправность пожарной сигнализации
            bPosState["fireAlarmDes"] = ELEM_AVAR;
            break;
        }
    }
    emit sigState(bPosState);
    //-----------чел---
    m_counterState = STATEPOS_MAX_TIMEOUT;
    return false;
}

// ------------------------------------------------------------------
bool POS_SERVICE::processAlertPassed(const QVariantMap & message)
{
    qint32 sensorId_passed = pos_Accord_AlertId_SensorId[message["alertId"].toUInt()];
    pos_Accord_AlertId_SensorId.remove(message["alertId"].toUInt());
    MapEventToLog[message["alertId"].toUInt()].state = false;
    switch (sensorId_passed) {
    case 1:
        bPosState["portal"] = ELEM_NORMA;
        break;
    case 2:
        bPosState["perimetr"] = ELEM_NORMA;
        break;
    case 3:
        bPosState["dolphin"] = ELEM_NORMA;
        break;
    case 4:
        bPosState["gatePerimetr"] = ELEM_NORMA;
        break;
    case 5:
        bPosState["gateCase"] = ELEM_NORMA;
        break;
    case 6:
        bPosState["fireCase"] = ELEM_NORMA;
        break;
    case 7:
        bPosState["fireAlarmCase"] = ELEM_NORMA;
        break;
    case 8:
        bPosState["gateDes"] = ELEM_NORMA;
        break;
    case 9:
        bPosState["fireDes"] = ELEM_NORMA;
        break;
    case 10:
        bPosState["fireAlarmDes"] = ELEM_NORMA;
        break;
    default:
        break;
    }
    emit sigState(bPosState);
    m_counterState = STATEPOS_MAX_TIMEOUT;
	return false;
}

// ------------------------------------------------------------------
bool POS_SERVICE::processEvent(const QVariantMap & message)
{
    PosEventToLog temp;
    temp.type = "event";
    temp.Operator = message["operator"].toString();
    temp.event = message["event"].toString();
    MapEventToLog.insert(message["eventId"].toUInt(), temp);
	m_counterState = STATEPOS_MAX_TIMEOUT;
	return false;
}

// ------------------------------------------------------------------

//-----------чел---

bool POS_SERVICE::processRelay(const QVariantMap & message)
{
    m_counterState = STATEPOS_MAX_TIMEOUT;
    if(message["mode"] == "open"){
        emit sigOsvPerimetrOn();                  // кинем сигнал для включения света
    }else if(message["mode"] == "close"){
        emit sigOsvPerimetrOff();
    }
    emit sigState(bPosState);
    return false;
}

//-----------чел---

void POS_SERVICE::clearPos()
{
	bPosState.clear(ELEM_NOT);
	bPosState["ObSost"] = ELEM_NOT;

	emit sigState(bPosState);
}

// ------------------------------------------------------------------
void POS_SERVICE::sendToPos(const QVariantMap & message)
{
	QJson::Serializer serializer;
	QByteArray json = serializer.serialize(message);

	LogPosBinary("POS: send con%d: %s", m_idPos, LogArray(json));

	if(!json.isEmpty())
	{
		if(m_idPos != -1) //pos net
		{
			if(network)
			{
				network->sendReply(m_idPos, json);
			}
		}
	}
}

// ------------------------------------------------------------------
void POS_SERVICE::sendPing()
{
	QVariantMap message;
	message["command"] = "ping";
	message["id"] = m_lastMsgId++;
	sendToPos(message);
    updateLogFromMapEvent();
}
// ------------------------------------------------------------------
//-----------чел---
//отправка состояния изменения реле
void POS_SERVICE::sendStateRelay(bool state_relay_osv_perim){
    QVariantMap message;
    if(last_state_relay_osv_perim != state_relay_osv_perim || flag_connect_osv_perim == true){
        message["command"] = "relay";
        message["id"] = m_lastMsgId++;
        message["relayExternalId"] = 88;
        message["mode"] = state_relay_osv_perim == true ? "opened" : "closed";

        bPosState["lighting"] = state_relay_osv_perim == true ? ELEM_NORMA : ELEM_NOT;
        emit sigState(bPosState);
        sendToPos(message);
        last_state_relay_osv_perim = state_relay_osv_perim;
        flag_connect_osv_perim = false;
    }
}
//отправка логов в зависимости от флагов событий
void POS_SERVICE::updateLogFromMapEvent(){
//    for(QMap<quint32, PosEventToLog>::iterator i = MapEventToLog.begin(); i != MapEventToLog.end(); ++i){
//        qDebug() << i.key() << i.value().type << i.value().state << i.value().lastState;
//    }
    QString messageToLog;
    for(QMap<quint32, PosEventToLog>::iterator i = MapEventToLog.begin(); i != MapEventToLog.end(); ++i){
        if(i.value().type == "event"){
            messageToLog = i.value().event;
            messageToLog += " . ";
            messageToLog += i.value().Operator;
            emit sigEventToLog("КСБ", messageToLog, "event");
            MapEventToLog.remove(i.key());
            messageToLog = "";
        }else if(i.value().type == "alert"){
            if((i.value().lastState == false) && (i.value().state == true)){
                i.value().lastState = true;
                messageToLog = i.value().zone;
                messageToLog += " . ";
                messageToLog += i.value().name;
                emit sigEventToLog("КСБ", messageToLog, "alert");
                messageToLog = "";
            }
            else if(i.value().state == false && i.value().lastState == true){
                messageToLog = "Сброс тревоги . ";
                messageToLog += i.value().zone;
                messageToLog += " . ";
                messageToLog += i.value().name;
                emit sigEventToLog("КСБ", messageToLog, "norma");
                messageToLog = "";
                MapEventToLog.remove(i.key());
            }
        }
    }
}

//-----------чел---
// ------------------------------------------------------------------


