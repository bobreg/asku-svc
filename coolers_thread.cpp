#include "globalvar.h"
#include "coolers_thread.h"
#include "coolers_service.h"

// ------------------------------------------------------------------
COOLERS_THREAD::COOLERS_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
	qRegisterMetaType<ModbusPortState>("ModbusPortState");
	qRegisterMetaType<CoolersState>("CoolersState");
}

// ------------------------------------------------------------------
COOLERS_THREAD::~COOLERS_THREAD()
{
}

// ------------------------------------------------------------------
void COOLERS_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void COOLERS_THREAD::run()
{
	service = new COOLERS_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(setMain(bool)));
		connect(this, SIGNAL(sigSetExtTemperature(double)), service, SLOT(setExtTemperature(double)));
		connect(this, SIGNAL(sigSetTemperature(quint32,bool,double)), service, SLOT(setTemperature(quint32,bool,double)));
		connect(this, SIGNAL(sigSetReset()), service, SLOT(setReset()));
		connect(this, SIGNAL(sigSetManual(bool)), service, SLOT(setManual(bool)));
		connect(this, SIGNAL(sigSetOn(quint32,bool)), service, SLOT(setOn(quint32,bool)));
		connect(this, SIGNAL(sigSetFreq(quint32,double)), service, SLOT(setFreq(quint32,double)));
		connect(this, SIGNAL(sigRefreshState()), service, SLOT(onRefreshCoolers()));
		connect(this, SIGNAL(sigStartMonitor()), service, SLOT(startMonitor()));
		connect(this, SIGNAL(sigStopMonitor()), service, SLOT(stopMonitor()));
		connect(this, SIGNAL(sigOnSyncToSlave(QVariantMap)), service, SLOT(onSyncToSlave(QVariantMap)));
		connect(this, SIGNAL(sigNeedSyncToSlave()), service, SLOT(syncToSlave()));
		connect(service, SIGNAL(sigSyncToSlave(QVariantMap)), this, SLOT(syncToSlave(QVariantMap)));
		connect(service, SIGNAL(sigCoolersState(QVariantMap)), this, SLOT(refreshState(QVariantMap)));
		connect(service, SIGNAL(sigState(AskuBinStateSet)), this, SIGNAL(sigState(AskuBinStateSet)));

		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void COOLERS_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void COOLERS_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 COOLERS_THREAD::state()
{
	return ELEM_NOT;
}

