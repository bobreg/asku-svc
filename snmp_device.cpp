#include "../common/logger.h"
#include "globalvar.h"
#include "snmp_device.h"
#include "snmp_service.h"

// ------------------------------------------------------------------
SNMP_DEVICE::SNMP_DEVICE(SNMP_SERVICE * p, const QHostAddress & address, const QString & community, quint32 version)
{
	m_parent = p;
	m_address = address;
	m_community = community;
	m_version = version;

	m_connected = false;
	m_status = DEVICE_INIT;

	m_counter = 0;
	m_needRefresh = true;

	m_requests.clear();
	m_results.clear();

	m_snmp_session = NULL;

	m_queryTimer = NULL;
	m_timeout = 0;
}

// ------------------------------------------------------------------
SNMP_DEVICE::~SNMP_DEVICE()
{
}

// ------------------------------------------------------------------
void SNMP_DEVICE::setAddress(QHostAddress address)
{
	m_address = address;
}

// ------------------------------------------------------------------
QHostAddress SNMP_DEVICE::address() const
{
	return m_address;
}

// ------------------------------------------------------------------
void SNMP_DEVICE::setCommunity(const QString & community)
{
	m_community = community;
}

// ------------------------------------------------------------------
QString SNMP_DEVICE::community() const
{
	return m_community;
}

// ------------------------------------------------------------------
void SNMP_DEVICE::setVersion(quint32 version)
{
	m_version = version;
}

// ------------------------------------------------------------------
quint32 SNMP_DEVICE::version() const
{
	return m_version;
}

// ------------------------------------------------------------------
void SNMP_DEVICE::setTimeout(qint32 timeout)
{
	m_timeout = timeout;
}

// ------------------------------------------------------------------
qint32 SNMP_DEVICE::timeout()
{
	return m_timeout;
}

// ------------------------------------------------------------------
void SNMP_DEVICE::onConnectedDevice()
{
	m_connected = true;
	onConnected();
}

// ------------------------------------------------------------------
void SNMP_DEVICE::onDisconnectedDevice()
{
	m_connected = false;
	onDisconnected();
}

// ------------------------------------------------------------------
void SNMP_DEVICE::onAnswer(qint32 value)
{
	if(!m_counter)
	{
		m_needRefresh = true;
		onConnectedDevice();
	}

	m_counter = value;
}

//------------------------------------------------------------------------------
void SNMP_DEVICE::checkResponce()
{
	if(m_counter)
	{
		m_counter--;

		if(!m_counter)
		{
			m_needRefresh = true;
			onDisconnectedDevice();
		}
	}
}

//------------------------------------------------------------------------------
void SNMP_DEVICE::checkDeviceState()
{
	switch(m_status)
	{
		case DEVICE_INIT:
			m_status = m_connected ? DEVICE_OK : DEVICE_FAIL;
//			emit sigAnswer(nv,connected);
			break;

		case DEVICE_OK:
			if(!m_connected || (m_counter == 0))
			{
				if(m_status != DEVICE_FAIL)
				{
					m_status = DEVICE_FAIL;
//					emit sigAnswer(nv,false);
				}
			}
			break;

		case DEVICE_FAIL:
			if(m_connected && (m_counter > 0))
			{
				if(m_status != DEVICE_OK)
				{
					m_status = DEVICE_OK;
//					emit sigAnswer(nv,true);
				}
			}
			break;
	}
}

// ------------------------------------------------------------------
void SNMP_DEVICE::onConnected()
{
	
}

// ------------------------------------------------------------------
void SNMP_DEVICE::onDisconnected()
{
	
}

// ------------------------------------------------------------------
bool SNMP_DEVICE::isConnected()
{
	return m_connected;
}

// ------------------------------------------------------------------
bool SNMP_DEVICE::processQuery()
{
	return false;
}

// ------------------------------------------------------------------
void SNMP_DEVICE::processResults()
{
	
}

// ------------------------------------------------------------------
void SNMP_DEVICE::setOidList(const SnmpOidList & oids)
{
	int timeout = -1;

	if(m_queryTimer)
	{
		if(m_queryTimer->isActive())
			timeout = m_queryTimer->interval();

		m_queryTimer->stop();
	}

	m_requests = oids;

	if(m_queryTimer && timeout > 0)
		m_queryTimer->start(timeout);
}

// ------------------------------------------------------------------
SnmpOidList SNMP_DEVICE::getOidList()
{
	return m_requests;
}

// ------------------------------------------------------------------
bool SNMP_DEVICE::init_snmp_session()
{
	netsnmp_session session;
	snmp_sess_init(&session);

	session.peername = qstrdup((const char*)qPrintable(m_address.toString()));
	session.community = (unsigned char*)strdup((const char*)qPrintable(m_community));
	session.community_len = qstrlen((const char*)qPrintable(m_community));
	session.version = m_version;

	m_snmp_session = snmp_open(&session);

	bool result = (m_snmp_session != NULL);

	if(result && m_parent)
	{
		m_queryTimer = new QTimer(m_parent);
		if(m_queryTimer)
		{
			m_queryTimer->setSingleShot(true);
			m_queryTimer->setProperty("device", (quint32)m_address.toIPv4Address());
			m_parent->connect(m_queryTimer, SIGNAL(timeout()), m_parent, SLOT(onDeviceQueryTimer()));
		}
	}

	return result;
}

// ------------------------------------------------------------------
void SNMP_DEVICE::close_snmp_session()
{
	if(m_queryTimer)
	{
		m_queryTimer->stop();
		delete m_queryTimer;
		m_queryTimer = NULL;
	}
	if(m_snmp_session != NULL)
	{
		snmp_close(m_snmp_session);
		m_snmp_session = NULL;
	}
}

// ------------------------------------------------------------------
netsnmp_session * SNMP_DEVICE::snmp_session()
{
	return m_snmp_session;
}

// ------------------------------------------------------------------
void SNMP_DEVICE::queryStart()
{
	LogSnmpInfo("SNMP_DEVICE::queryStart");

	m_currOid = m_requests.constBegin();

	if(m_queryTimer && m_timeout >= 0)
		m_queryTimer->start(m_timeout);
}

// ------------------------------------------------------------------
void SNMP_DEVICE::queryStop()
{
	LogSnmpInfo("SNMP_DEVICE::queryStop");

	if(m_queryTimer)
		m_queryTimer->stop();

	m_currOid = m_requests.constBegin();
}

// ------------------------------------------------------------------
void SNMP_DEVICE::processResults(int result, const SnmpOid & currOid, const SnmpResultList & snmpResultList)
{
	if(!result)
	{
//		LogSnmpInfo(QString("SNMP: device %1: ResultList\n----\n%2\n----").arg(m_address.toString()).arg(snmpResultList.dump()));
		LogSnmpInfo(QString("SNMP: %1").arg(snmpResultList.dump()));

		onAnswer(5);
	}
	else
	{
		LogSnmpError(QString("SNMP: device %1: error %2 on request %3").arg(m_address.toString()).arg(result).arg(currOid.toString()));
	}

	m_results += snmpResultList;

	checkResponce();

	switchOid();
}

// ------------------------------------------------------------------
void SNMP_DEVICE::switchOid()
{
	if(!m_requests.isEmpty())
	{
		m_currOid++;

		if(m_currOid == m_requests.constEnd())
		{
			m_currOid = m_requests.constBegin();
			LogSnmpInfo(QString("SNMP: device %1: Cycle completed").arg(m_address.toString()));
			processResults();
		}
	}

	if(m_queryTimer && m_timeout >= 0)
		m_queryTimer->start(m_timeout);
}

// ------------------------------------------------------------------
SnmpOid SNMP_DEVICE::nextOid()
{
	return *m_currOid;
}

// ------------------------------------------------------------------
QVariant SNMP_DEVICE::translateValue(const QString & key, const QVariant & value)
{
	Q_UNUSED(key);
	return value;
}

// ------------------------------------------------------------------
