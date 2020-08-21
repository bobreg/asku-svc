#ifndef __UPS_SERVICE_H__
#define __UPS_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/stateset.h"
#include "ups_struct.h"

//-----------------------------------------------------------------------------

class UPS_THREAD;

//-----------------------------------------------------------------------------

class UPS_SERVICE : public QObject
{
	Q_OBJECT

protected:
	UPS_THREAD *parent;

	UpsConfig m_upsConfig;

	AskuBinStateSet bUpsState;
	AskuValueMap bUpsMeasure;

	bool isMonitoring;

protected:
	bool processData(QByteArray *data);
	void sendToUps(QByteArray data);

	virtual void updateState();
	void updateUpsState(quint32 n_ups);
	void updatePortState();
	void updateCommonState();

protected slots:
	virtual void onConnected();
	virtual void onDisconnected();
	virtual void onConnectedPort(qint32 port);
	virtual void onDisconnectedPort(qint32 port);
	virtual bool onQuery();
	virtual bool onLive();

public slots:
	void onChangedMain(bool main);
	void onRefreshUps();
	void startMonitor();
	void stopMonitor();
	void syncToSlave();
	void onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

signals:
	void sigChangedState();
	void sigUpsState(QVariantMap info);
	void sigSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

public:
	UPS_SERVICE(UPS_THREAD * parent);
	virtual ~UPS_SERVICE();

	bool init();

	virtual void onChangedDeviceState();
	virtual void onChangedPortState();

signals:
	void sigState(AskuBinStateSet state);
};

//-----------------------------------------------------------------------------

#endif // __UPS_SERVICE_H__
