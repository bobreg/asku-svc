#include "../common/logger.h"
#include "globalvar.h"
#include "snmp_service.h"
#include "snmp_device.h"
#include "snmp_oids.h"

// ------------------------------------------------------------------
SNMP_SERVICE::SNMP_SERVICE(QObject * p)
{
	m_parent = p;
	m_inited = false;
	m_devices.clear();

	m_queryTimer = NULL;
	m_timeout = 0;

	SOCK_STARTUP;
}

// ------------------------------------------------------------------
SNMP_SERVICE::~SNMP_SERVICE()
{
	if(m_queryTimer)
	{
		m_queryTimer->stop();
		delete m_queryTimer;
		m_queryTimer = NULL;
	}

	m_devices.clear();

	SOCK_CLEANUP;
}

// ------------------------------------------------------------------
bool SNMP_SERVICE::init()
{
	m_inited = true;
	return false;
}

// ------------------------------------------------------------------
void SNMP_SERVICE::setMain(bool on)
{
	if(on)
		if(m_queryTimer)
			m_queryTimer->start(300);
}

// ------------------------------------------------------------------
void SNMP_SERVICE::addDevice(SNMP_DEVICE * device)
{
	if(!device)
		return;

	quint32 address = device->address().toIPv4Address();
	LogSnmpInfo("SNMP: add device %s", qPrintable(device->address().toString()));
	if(m_devices.contains(address))
		LogSnmpError("SNMP: error add device %s: address already in list", qPrintable(device->address().toString()));
	m_devices.insert(address, device);

	LogSnmpInfo("SNMP: init session for device %s", qPrintable(device->address().toString()));
	if(!device->init_snmp_session())
		LogSnmpError("SNMP: device %s: init session failed", qPrintable(device->address().toString()));
}

// ------------------------------------------------------------------
void SNMP_SERVICE::removeDevice(SNMP_DEVICE * device)
{
	if(!device)
		return;

	LogSnmpInfo("SNMP: close session for device %s", qPrintable(device->address().toString()));
	device->close_snmp_session();

	quint32 address = device->address().toIPv4Address();
	LogSnmpInfo("SNMP: remove device %s", qPrintable(device->address().toString()));
	if(m_devices.contains(address, device))
		m_devices.remove(address, device);
}

// ------------------------------------------------------------------
SNMP_DEVICE * SNMP_SERVICE::findDevice(const QHostAddress & hostaddr)
{
	quint32 address = hostaddr.toIPv4Address();

	if(m_devices.contains(address))
		return m_devices.find(address).value();
	else
		return NULL;
}

// ------------------------------------------------------------------
void SNMP_SERVICE::onDeviceQueryTimer()
{
	QObject * obj = (QObject*)sender();

	if(!obj)
	{
		LogSnmpError("SNMP: onDeviceQueryTimer null object");
		return;
	}

	QHostAddress address = QHostAddress(obj->property("device").toUInt());

	if(address.isNull())
	{
		LogSnmpError("SNMP: onDevice QueryTimer invalid device address");
		return;
	}

	SNMP_DEVICE * device = findDevice(address);
	if(!device)
	{
		LogSnmpError("SNMP: onDevice QueryTimer invalid device");
		return;
	}

	processDevice(device);
}

// ------------------------------------------------------------------
void SNMP_SERVICE::processDevice(SNMP_DEVICE * device)
{
	int result = 0;

	LogSnmpInfo(QString("SNMP: process device %1").arg(device->address().toString()));

	SnmpOid currOid = device->nextOid();

	if(currOid.isNull())
	{
		LogSnmpError(QString("SNMP: no oid for device %1").arg(device->address().toString()));
		return;
	}

	SnmpResultList snmpResultList;

	if(currOid.isScalar())
	{
		SnmpResult snmpResult;
		result = get_snmp_value(device->snmp_session(), currOid, &snmpResult);
		snmpResultList.append(snmpResult);
		device->processResults(result, currOid, snmpResultList);
	}
	else if(currOid.isTable())
	{
		SnmpOid lastOid;

		do
		{
			result = get_next_snmp_value(device->snmp_session(), currOid, &snmpResultList, &lastOid);

		} while(result == NoError);

		if((result == ErrorPattern || result == ErrorRepeat) && !snmpResultList.isEmpty())
			result = NoError;

		device->processResults(result, currOid, snmpResultList);
	}
}

// ------------------------------------------------------------------
// ввод значения одного скалярного параметра по oid (version, community, ipAddress)
// возврат:
//  0 - NoError
// -1 - нелегальный oid
// -2 - STAT_TIMEOUT
// -3 - STAT_ERROR
int SNMP_SERVICE::get_snmp_value(netsnmp_session *session, const SnmpOid & soid, SnmpResult * result)
{
	int ret_code = NoError;
	char char_oid[1024];

	size_t name_length = MAX_OID_LEN;
	oid name[MAX_OID_LEN];

// преобразование SnmpOid в char*
	qstrncpy(char_oid, soid.toString().toLocal8Bit().data(), sizeof(char_oid));

	if(snmp_parse_oid((char*)char_oid, name, &name_length))
	{
// Create PDU for GET request and add object names to request.
		netsnmp_pdu *pdu = snmp_pdu_create(SNMP_MSG_GET);
		snmp_add_null_var(pdu, name, name_length);

// Perform the request
		netsnmp_pdu *response = 0;
		int status = snmp_synch_response(session, pdu, &response);

		if(status == STAT_SUCCESS)
		{
			if(response->errstat == SNMP_ERR_NOERROR)
			{
				*result = SnmpResult(soid, response->variables);
			}
			else
			{
				ret_code = ErrorOther; // end
			}
		}
		else if(status == STAT_TIMEOUT)
		{
			ret_code = ErrorTimeout; // timeout
		}
		else // status == STAT_ERROR
		{
			ret_code = ErrorStatus; // error
		}

		if(response)
			snmp_free_pdu(response);
	}
	else
	{
		ret_code = ErrorInvalidOid; // нелегальный oid
	}

	if(ret_code != NoError)
	{
		*result = SnmpResult(soid);
		QString strErr = "error: " + soid.toString() + " ret_code " + QString::number(ret_code);
//		emit sigDeviceParamsError(strErr);
	}

	return ret_code;
}

// ------------------------------------------------------------------
// ввод значения одного табличного параметра по oid+last_oid (version, community, ipAddress)
// возврат:
//  0 - ок, есть следующий для данного шаблона
// -1 - нелегальный oid
// -2 - STAT_TIMEOUT
// -3 - STAT_ERROR
// -4 - новый шаблон параметра
// -5 - конец всех параметров данного устройства
int SNMP_SERVICE::get_next_snmp_value(netsnmp_session *session, const SnmpOid & soid, SnmpResultList * result, SnmpOid *last_oid)
{
	int ret_code = NoError;
	char char_oid[1024];
	SnmpOid curr_soid;

	size_t name_length = MAX_OID_LEN;
	oid name[MAX_OID_LEN];

// преобразование QString в char*
	SnmpOid os(last_oid && !last_oid->isEmpty() ? *last_oid : soid);

//	qDebug() << QString("soid=%1  last_oid=%2   os=%3").arg(soid.toString()).arg(last_oid->toString()).arg(os.toString());

	qstrncpy(char_oid, os.toString().toLocal8Bit().data(), sizeof(char_oid));

	if(snmp_parse_oid((char*)char_oid, name, &name_length))
	{
// Create PDU for GET request and add object names to request.
		netsnmp_pdu *pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);
		snmp_add_null_var(pdu, name, name_length);

// Perform the request
		netsnmp_pdu *response = 0;
		int status = snmp_synch_response(session, pdu, &response);

		if(status == STAT_SUCCESS)
		{
			netsnmp_variable_list *vars = response->variables;
// преобразование pulong в QString
			curr_soid = SnmpOid((oid*)vars->name, vars->name_length, soid.mibName());

			LogSnmpInfo(QString("curr_soid=%1   os=%2    last_oid=%3").arg(curr_soid.toString()).arg(os.toString()).arg(last_oid->toString()));

// сравнение oid с номером сервиса
			if(!curr_soid.contains(soid))
			{
				ret_code = ErrorPattern; // new pattern
			}
			else if(*last_oid == curr_soid)
			{
				ret_code = ErrorRepeat; // repeated pattern
			}
			else if(response->errstat == SNMP_ERR_NOERROR)
			{
				curr_soid.setMibNameAndTail(soid);
				if(result)
					result->push_back(SnmpResult(curr_soid, vars));
				*last_oid = curr_soid;
			}
			else
			{
				ret_code = ErrorOther; // end
			}
		}
		else if(status == STAT_TIMEOUT)
		{
			ret_code = ErrorTimeout; // timeout
		}
		else // if(status == STAT_ERROR)
		{
			ret_code = ErrorStatus; // error
		}

		if(response)
			snmp_free_pdu(response);
	}
	else
	{
		ret_code = ErrorInvalidOid; // нелегальный oid
	}

	if(ret_code < 0 && ret_code != ErrorPattern && ret_code != ErrorOther && ret_code != ErrorRepeat)
	{
		if(result)
		{
			result->clear();
			result->push_back(SnmpResult(os));
		}
		QString strErr = "error: " + os.toString() + " ret_code " + QString::number(ret_code);
//		emit sigDeviceParamsError(strErr);
	}

	return ret_code;
}

// ------------------------------------------------------------------
