#ifndef __SNMP_DEVICE_H__
#define __SNMP_DEVICE_H__

#include <QObject>
#include <QHostAddress>
#include <QString>
#include <QVariant>
#include "snmp_oids.h"

//-----------------------------------------------------------------------------

class SNMP_SERVICE;

//-----------------------------------------------------------------------------

class SNMP_DEVICE
{
public:
	enum SNMP_DEVICE_STATUS {
		DEVICE_INIT = 0,
		DEVICE_OK = 1,
		DEVICE_FAIL = 2
	};

protected:
	SNMP_SERVICE *m_parent;

	QTimer *m_queryTimer;
	qint32 m_timeout;

	QHostAddress m_address;
	QString m_community;
	quint32 m_version;

	bool m_connected;

	qint32 m_counter;
	bool m_needRefresh;

	SNMP_DEVICE_STATUS m_status;

	SnmpOidList::const_iterator m_currOid;
	SnmpOidList m_requests;
	SnmpResultMap m_results;

// --- SNMP ---
	netsnmp_session *m_snmp_session;
// -----------

public:
	SNMP_DEVICE(SNMP_SERVICE * parent, const QHostAddress & address = QHostAddress(), const QString & community = QString(), quint32 version = 1);
	virtual ~SNMP_DEVICE();

	void setAddress(QHostAddress address);
	QHostAddress address() const;

	void setCommunity(const QString & community);
	QString community() const;

	void setVersion(quint32 version);
	quint32 version() const;

	void setTimeout(qint32 timeout);
	qint32 timeout();

	void setOidList(const SnmpOidList & oids);
	SnmpOidList getOidList();

// --- SNMP ---
	bool init_snmp_session();
	void close_snmp_session();
	netsnmp_session * snmp_session();
// ------------

	void onConnectedDevice();
	void onDisconnectedDevice();
	bool isConnected();

	void queryStart();
	SnmpOid nextOid();
	void switchOid();
	void queryStop();

	void processResults(int result, const SnmpOid & currOid, const SnmpResultList & snmResultList);

	void onAnswer(qint32 value);
	void checkResponce();
	void checkDeviceState();

	virtual void onConnected();
	virtual void onDisconnected();

	virtual void processResults();
	virtual bool processQuery();

	virtual QVariant translateValue(const QString & key, const QVariant & value);
};

//-----------------------------------------------------------------------------

#endif // __DRIVE_SERVICE_H__
