#ifndef __UPS_MODBUS_SERVICE_H__
#define __UPS_MODBUS_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/tcpnetwork.h"
#include "../common/stateset.h"
#include "modbus_service.h"
#include "ups_struct.h"

//-----------------------------------------------------------------------------

class UPS_THREAD;
class MODBUS_DEVICE;

//-----------------------------------------------------------------------------

class UPS_MODBUS_SERVICE : public MODBUS_SERVICE
{
	Q_OBJECT

	UPS_THREAD *parent;
	UpsConfig m_upsConfig;
	AskuBinStateSet bUpsState;
	bool isMonitoring;

	MODBUS_DEVICE *powerware[UPS_MAX_N_DEVICES];

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
	void onSyncToSlave(QVariantMap data);

signals:
	void sigChangedState();
	void sigUpsState(QVariantMap info);
	void sigSyncToSlave(QVariantMap data);

public:
	UPS_MODBUS_SERVICE(UPS_THREAD * parent);
	virtual ~UPS_MODBUS_SERVICE();

	bool init();

	virtual void onChangedDeviceState();
	virtual void onChangedPortState();

signals:
	void sigState(AskuBinStateSet state);
};

//-----------------------------------------------------------------------------

#endif // __UPS_MODBUS_SERVICE_H__
