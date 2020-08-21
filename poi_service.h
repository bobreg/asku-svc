#ifndef __POI_SERVICE_H__
#define __POI_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/tcpnetwork.h"
#include "../common/stateset.h"
#include "../common/parser.h"
#include "poi_struct.h"

//-----------------------------------------------------------------------------

class POI_THREAD;

//-----------------------------------------------------------------------------

class POI_SERVICE : public QObject
{
	Q_OBJECT

protected:
	POI_THREAD *parent;

	bool m_isInitialized;
	bool m_isConnected;

	qint32 m_counterState;

	PoiConfig m_poiConfig;

	TcpNetwork *network;

	quint16 m_portOur;
	QHostAddress m_haPoi;
	qint32 m_idPoi;
	AskuJsonParser m_dataPoi;

	QTimer *timer;

	AskuBinStateSet bPoiLocalState;
	AskuValueSet bPoiLocalKoeff;
	AskuValueSet bPoiLocalPilot;
	AskuValueSet bPoiLocalTrans;

	AskuBinStateSet bPoiOtherState;
	AskuValueSet bPoiOtherKoeff;
	AskuValueSet bPoiOtherPilot;
	AskuValueSet bPoiOtherTrans;

	enum { POI_STATEDSP_TIMEOUT = 10 };

	bool processMessage(const QVariantMap & message);
	bool processNoiseFactor(const QVariantMap & message);
	bool processDspState(const QVariantMap & message);
	bool processSharu(const QVariantMap & message);
	bool processPilot(const QVariantMap & message);
	bool processTransmitter(const QVariantMap & message);
	bool processSuppression(const QVariantMap & message);

	void clearLocalState();
	void clearOtherState();

	void sendToPoi(QVariantMap data);

protected slots:
	void timeout();

	void onDataArrived(qint32 id, QByteArray data);
	void onConnected(qint32 id, QHostAddress address, quint16 port);
	void onDisconnected(qint32 id);

	void sendTemperature();

public slots:
//slots from thread
	void setMain(bool on);
	void setResetKoeff();

	void setConnectedGpr();
	void setDisconnectedGpr();

	void setTemperature(double temp);

	void syncToSlave();
	void onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff, QVariantMap pilot);

public:
	POI_SERVICE(POI_THREAD * parent);
	~POI_SERVICE();

	bool init();
	bool isInitialized();

signals:
	void sigSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff, QVariantMap pilot);
	void sigChangedState();

	void sigStateLocal(AskuBinStateSet state);
	void sigKoeffLocal(AskuValueSet state);
	void sigPilotLocal(AskuValueSet state);
	void sigTransmitterLocal(AskuValueSet state);

	void sigStateOther(AskuBinStateSet state);
	void sigKoeffOther(AskuValueSet state);
	void sigPilotOther(AskuValueSet state);
	void sigTransmitterOther(AskuValueSet state);
};

//-----------------------------------------------------------------------------

#endif // __POI_SERVICE_H__
