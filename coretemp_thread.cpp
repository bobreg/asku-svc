#include "globalvar.h"
#include "coretemp_thread.h"
#include "coretemp_service.h"

// ------------------------------------------------------------------
CORETEMP_THREAD::CORETEMP_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
	qRegisterMetaType<AskuValueSet>("AskuValueSet");
}

// ------------------------------------------------------------------
CORETEMP_THREAD::~CORETEMP_THREAD()
{
}

// ------------------------------------------------------------------
void CORETEMP_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void CORETEMP_THREAD::run()
{
	service = new CORETEMP_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(onChangedMain(bool)));
		connect(this, SIGNAL(sigConnectedGpr()), service, SLOT(setConnectedGpr()));
		connect(this, SIGNAL(sigDisconnectedGpr()), service, SLOT(setDisconnectedGpr()));
		connect(this, SIGNAL(sigRefreshState()), service, SLOT(onRefreshCoreTemp()));
		connect(this, SIGNAL(sigStartMonitor()), service, SLOT(startMonitor()));
		connect(this, SIGNAL(sigStopMonitor()), service, SLOT(stopMonitor()));
		connect(this, SIGNAL(sigOnSyncToSlave(QVariantMap,QVariantMap,QVariantMap)), service, SLOT(onSyncToSlave(QVariantMap,QVariantMap,QVariantMap)));
		connect(this, SIGNAL(sigNeedSyncToSlave()), service, SLOT(syncToSlave()));
		connect(service, SIGNAL(sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap)), this, SLOT(syncToSlave(QVariantMap,QVariantMap,QVariantMap)));
		connect(service, SIGNAL(sigStateLocal(AskuBinStateSet,AskuValueSet)), this, SIGNAL(sigStateLocal(AskuBinStateSet,AskuValueSet)));
		connect(service, SIGNAL(sigStateOther(AskuBinStateSet,AskuValueSet)), this, SIGNAL(sigStateOther(AskuBinStateSet,AskuValueSet)));

		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void CORETEMP_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void CORETEMP_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 CORETEMP_THREAD::state()
{
	return ELEM_NOT;
}

