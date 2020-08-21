#ifndef __UPS_SNMP_APC_DEVICE_H__
#define __UPS_SNMP_APC_DEVICE_H__

#include "snmp_oids.h"
#include "snmp_device.h"
#include "snmp_service.h"
#include "ups_struct.h"
#include "ups_snmp_apc_struct.h"
#include "ups_snmp_service.h"

//-----------------------------------------------------------------------------

class APC_SNMP_DEVICE : public SNMP_DEVICE
{
	UPS_SNMP_SERVICE *m_parent;

//	UpsApcState m_upsState;

// -- translating values --
	QMap<int, QString> upsBasicBatteryStatusValues;
	QMap<int, QString> upsAdvBatteryReplaceIndicatorValues;
	QMap<int, QString> upsAdvInputLineFailCauseValues;
	QMap<int, QString> upsBasicOutputStatusValues;
	QMap<int, QString> upsAdvTestDiagnosticSheduleValues;
	QMap<int, QString> upsAdvTestDiagnosticsResultsValues;
	QMap<int, QString> upsAdvTestCalibrationResultsValues;
	QMap<int, QString> upsCommStatusValues;
	QMap<int, QString> upsBasicStateOutputStateValues;
	QMap<int, QString> upsAdvStateAbnormalConditionsValues;
	QMap<int, QString> upsAdvStateSmartUPSSpecificFaultsValues;
// -----------------------

public:

	APC_SNMP_DEVICE(UPS_SNMP_SERVICE *parent, const QHostAddress & address = QHostAddress(), const QString & community = QString(), quint32 version = 1);
	virtual ~APC_SNMP_DEVICE();

//	UpsApcState & state() {
//		return m_upsState;
//	}

	bool isActualState();
	bool isInfoCollected();

	virtual void onConnected();
	virtual void onDisconnected();

	virtual void processResults();

	virtual QVariant translateValue(const QString & key, const QVariant & value);
};

//-----------------------------------------------------------------------------

#endif // __UPS_SNMP_APC_DEVICE_H__
