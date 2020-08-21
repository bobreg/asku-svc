#ifndef __SNMP_SERVICE_H__
#define __SNMP_SERVICE_H__

// ------------------------------------------------------------------

#include <qglobal.h>

#include <QThread>
#include <QMutex>
#include <QRegExp>

#include <iostream>
#include <stdlib.h>

#include <net-snmp/net-snmp-config.h>

#include <string.h>

#if HAVE_WINSOCK_H
#include <winsock.h>
#endif

#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

#if HAVE_NETDB_H
#include <arpa/inet.h>
#endif

#include <net-snmp/utilities.h>
#include <net-snmp/net-snmp-includes.h>

#include "snmp_oids.h"
#include "snmp_device.h"

// ------------------------------------------------------------------

class SNMP_SERVICE : public QObject
{
	Q_OBJECT

protected:
	bool m_inited;
	QObject * m_parent;

	QTimer *m_queryTimer;
	qint32 m_timeout;

	QMultiMap<quint32, SNMP_DEVICE*> m_devices;

	void addDevice(SNMP_DEVICE * device);
	void removeDevice(SNMP_DEVICE * device);

	SNMP_DEVICE * findDevice(const QHostAddress & address);

	void processDevice(SNMP_DEVICE * device);

	int get_snmp_value(netsnmp_session *session, const SnmpOid & soid, SnmpResult * result);
	int get_next_snmp_value(netsnmp_session *session, const SnmpOid & soid, SnmpResultList * result_list, SnmpOid *last_oid);

public:
	enum ErrorCodes {
		NoError			=  0,
		ErrorInvalidOid		= -1,
		ErrorTimeout		= -2,
		ErrorStatus		= -3,
		ErrorPattern		= -4,
		ErrorRepeat		= -5,
		ErrorOther		= -6
	};

	SNMP_SERVICE(QObject * parent);
	~SNMP_SERVICE();

	bool init();
	bool isInited() const;

public slots:
//slots from thread
	virtual void setMain(bool on);

//slot for devices
	void onDeviceQueryTimer();
};

// ------------------------------------------------------------------

#endif // __SNMP_SERVICE_H__
