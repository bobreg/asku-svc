#ifndef __UPS_SNMP_PWW_DEVICE_H__
#define __UPS_SNMP_PWW_DEVICE_H__

#include "snmp_oids.h"
#include "snmp_device.h"
#include "snmp_service.h"
#include "ups_struct.h"
#include "ups_snmp_pww_struct.h"
#include "ups_snmp_service.h"

//-----------------------------------------------------------------------------

class PWW_SNMP_DEVICE : public SNMP_DEVICE
{
	UpsPwwState m_upsState;

public:

	PWW_SNMP_DEVICE(UPS_SNMP_SERVICE *parent, const QHostAddress & address = QHostAddress(), const QString & community = QString(), quint32 version = 1);
	virtual ~PWW_SNMP_DEVICE();

	UpsPwwState & state() {
		return m_upsState;
	}

	bool isActualState();
	bool isInfoCollected();

	virtual void onConnected();
	virtual void onDisconnected();

	virtual void processResults();

	QVariant translateValue(const QString & key, const QVariant & value);
};

//-----------------------------------------------------------------------------

#endif // __UPS_SNMP_PWW_DEVICE_H__
