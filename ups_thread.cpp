#include "globalvar.h"
#include "ups_thread.h"
#include "ups_struct.h"
#include "ups_modbus_service.h"
#include "ups_snmp_service.h"

// ------------------------------------------------------------------
UPS_THREAD::UPS_THREAD(QObject * parent) : QThread(parent)
{
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
	service_jbus = NULL;
	service_snmp = NULL;
}

// ------------------------------------------------------------------
UPS_THREAD::~UPS_THREAD()
{
}

// ------------------------------------------------------------------
void UPS_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void UPS_THREAD::run()
{
	switch(m_setup.ups.type)
	{
		case UPS_TYPE_MODBUS_POWERWARE:
		case UPS_TYPE_MODBUS_APC:
			service_jbus = new UPS_MODBUS_SERVICE(this);
			break;

		case UPS_TYPE_SNMP_POWERWARE:
		case UPS_TYPE_SNMP_APC:
			service_snmp = new UPS_SNMP_SERVICE(this);
			break;

		default:
			service_jbus = NULL;
			service_snmp = NULL;
	}

	if(service_jbus)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service_jbus, SLOT(setMain(bool)));
		connect(this, SIGNAL(sigRefreshState()), service_jbus, SLOT(onRefreshUps()));
		connect(this, SIGNAL(sigStartMonitor()), service_jbus, SLOT(startMonitor()));
		connect(this, SIGNAL(sigStopMonitor()), service_jbus, SLOT(stopMonitor()));
		connect(this, SIGNAL(sigOnSyncToSlave(QVariantMap,QVariantMap,QVariantMap)), service_jbus, SLOT(onSyncToSlave(QVariantMap,QVariantMap,QVariantMap)));
		connect(this, SIGNAL(sigNeedSyncToSlave()), service_jbus, SLOT(syncToSlave()));
		connect(service_jbus, SIGNAL(sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap)), this, SLOT(syncToSlave(QVariantMap,QVariantMap,QVariantMap)));
		connect(service_jbus, SIGNAL(sigUpsState(QVariantMap)), this, SLOT(refreshState(QVariantMap)));
		connect(service_jbus, SIGNAL(sigState(AskuBinStateSet)), this, SIGNAL(sigState(AskuBinStateSet)));

		service_jbus->init();

		exec();

		delete service_jbus;
		service_jbus = NULL;
	}
	else if(service_snmp)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service_snmp, SLOT(onChangedMain(bool)));
		connect(this, SIGNAL(sigRefreshState()), service_snmp, SLOT(onRefreshUps()));
		connect(this, SIGNAL(sigStartMonitor()), service_snmp, SLOT(startMonitor()));
		connect(this, SIGNAL(sigStopMonitor()), service_snmp, SLOT(stopMonitor()));
		connect(this, SIGNAL(sigOnSyncToSlave(QVariantMap,QVariantMap,QVariantMap)), service_snmp, SLOT(onSyncToSlave(QVariantMap,QVariantMap,QVariantMap)));
		connect(this, SIGNAL(sigNeedSyncToSlave()), service_snmp, SLOT(syncToSlave()));
		connect(service_snmp, SIGNAL(sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap)), this, SLOT(syncToSlave(QVariantMap,QVariantMap,QVariantMap)));
		connect(service_snmp, SIGNAL(sigUpsState(QVariantMap)), this, SLOT(refreshState(QVariantMap)));
		connect(service_snmp, SIGNAL(sigState(AskuBinStateSet,AskuValueSet)), this, SIGNAL(sigState(AskuBinStateSet,AskuValueSet)));

		service_snmp->init();

		exec();

		delete service_snmp;
		service_snmp = NULL;
	}
}

// ------------------------------------------------------------------
void UPS_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void UPS_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 UPS_THREAD::state()
{
	return ELEM_NOT;
}

