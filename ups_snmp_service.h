#ifndef __UPS_SNMP_SERVICE_H__
#define __UPS_SNMP_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/tcpnetwork.h"
#include "../common/stateset.h"
#include "snmp_service.h"
#include "ups_struct.h"

//-----------------------------------------------------------------------------

class UPS_THREAD;
class PWW_SNMP_DEVICE;
class APC_SNMP_DEVICE;

//-----------------------------------------------------------------------------

class UPS_SNMP_SERVICE : public SNMP_SERVICE
{
	Q_OBJECT

	UPS_THREAD *parent;

	UpsConfig m_upsConfig;
	SnmpResultMap m_results;

	AskuBinStateSet bUpsState;
	AskuValueSet bUpsMeasure;

	SNMP_DEVICE *m_device[UPS_MAX_N_DEVICES];

protected:
	virtual void updateState();
	void updateUpsState(SNMP_DEVICE * device);
	void updateCommonState();

protected slots:
	virtual void onConnected();
	virtual void onDisconnected();

public slots:
	void onChangedMain(bool main);
	void onRefreshUps();
	void startMonitor();
	void stopMonitor();
	void syncToSlave();
	void onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);
	void onProcessSnmpResults(SNMP_DEVICE * device, const SnmpResultMap & results);

signals:
	void sigChangedState();
	void sigUpsState(QVariantMap info);
	void sigSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

public:
	UPS_SNMP_SERVICE(UPS_THREAD * parent);
	virtual ~UPS_SNMP_SERVICE();

	bool init();

	virtual void onChangedDeviceState();
	virtual void onChangedPortState();

signals:
	void sigState(AskuBinStateSet state, AskuValueSet measure);
};

//-----------------------------------------------------------------------------

#endif // __UPS_SNMP_SERVICE_H__
