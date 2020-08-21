#ifndef __POS_SERVICE_H__
#define __POS_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/tcpnetwork.h"
#include "../common/stateset.h"
#include "../common/parser.h"
#include "pos_struct.h"



//-----------------------------------------------------------------------------

class POS_THREAD;

// ----------------------------------------------------------------------------

class AskuPosAlarm : public QObject
{
	Q_OBJECT

protected:
	QTimer *m_timer;

	bool m_avar;
	bool m_main;
	bool m_connected;

	quint32 m_state;
	quint32 m_timeout;
	quint32 m_delay;

protected slots:
	void timeout();

signals:
	void changed();

public:
	AskuPosAlarm(quint32 timeout, quint32 delay);
	~AskuPosAlarm();

	void setMain(bool main);
	void setConnected(bool connected);

	void acivate();
};

//-----------------------------------------------------------------------------

class POS_SERVICE : public QObject
{
	Q_OBJECT

protected:
	POS_THREAD *parent;

	bool m_isInitialized;
	bool m_isConnected;
	qint32 m_counterState;
	bool m_cmdMain;

	TcpNetwork *network;

	quint16 m_portOur;
	QHostAddress m_haPos;
	qint32 m_idPos;

	quint32 m_lastMsgId;
	AskuJsonParser m_dataPos;

	QTimer *timer;
	QTimer *pingTimer;

	AskuBinStateSet bPosState;
	QMap<QString, AskuPosAlarm> posAlarms;

//-----------чел---
    QMap<qint32, qint32> pos_Accord_AlertId_SensorId;
    bool last_state_relay_osv_perim;
    bool flag_connect_osv_perim; // флаг для того чтобы при присоединении к КСБ отправить им
                                 // состояние реле освещения внешнего периметра
    QMap <quint32, PosEventToLog> MapEventToLog;
//-----------чел---

	enum { STATEPOS_MAX_TIMEOUT = 10 };
	enum {
		preambula = 99
	};
	enum {
		commandPingLength = 3,
		answerPingLength = 4,
		answerAlarmLength = 13
	};
	enum {
		answerPing = 1,
		answerAlarm = 2
	};

	bool parseData(qint32 id, QByteArray & data);
//	bool processMessage(QByteArray message);
//	bool processPing(QByteArray message);
//	bool processAlarm(QByteArray message);
	bool processMessage(const QVariantMap & message);
	bool processPingAnswer(const QVariantMap & message);
	bool processAlert(const QVariantMap & message);
	bool processAlertPassed(const QVariantMap & message);
	bool processEvent(const QVariantMap & message);
//-----------чел---
    bool processRelay(const QVariantMap & message);
    void updateLogFromMapEvent();
//-----------чел---
	void clearPos();

	void sendToPos(const QVariantMap & data);
	void sendPing();

protected slots:
	void timeout();
	void pingTimeout();
	void onDataArrived(qint32 id, QByteArray data);
	void onConnected(qint32 id, QHostAddress address, quint16 port);
	void onDisconnected(qint32 id);

public slots:
//slots from thread
	void setMain(bool on);
//-----------чел---
    void sendStateRelay(bool);
//-----------чел---

signals:
	void sigChangedState();

public:
	POS_SERVICE(POS_THREAD * parent);
	~POS_SERVICE();

	bool init();
	bool isInitialized();

signals:
	void sigState(AskuBinStateSet state);
//-----------чел---
    void sigOsvPerimetrOn();
    void sigOsvPerimetrOff();
    void sigEventToLog(QString, QString, QString);
//-----------чел---
};

//-----------------------------------------------------------------------------

#endif // __POS_SERVICE_H__
