#include "globalvar.h"
#include "vrl_thread.h"
#include "vrl_service.h"

// ------------------------------------------------------------------
VRL_THREAD::VRL_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
}

// ------------------------------------------------------------------
VRL_THREAD::~VRL_THREAD()
{
}

// ------------------------------------------------------------------
void VRL_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void VRL_THREAD::run()
{
	service = new VRL_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(setMain(bool)));
		connect(this, SIGNAL(sigSetDisableTotal(bool)), service, SLOT(setDisableTotal(bool)));
		connect(this, SIGNAL(sigConnectedGpr()), service, SLOT(setConnectedGpr()));
		connect(this, SIGNAL(sigDisconnectedGpr()), service, SLOT(setDisconnectedGpr()));
		connect(this, SIGNAL(sigSetMainVRL(quint32)), service, SLOT(setMainVRL(quint32)));
		connect(this, SIGNAL(sigSetDisableReconf(bool)), service, SLOT(setDisableReconf(bool)));
//		connect(this, SIGNAL(sigRefreshState()), service, SLOT(onRefreshVrl()));
//		connect(this, SIGNAL(sigStartMonitor()), service, SLOT(startMonitor()));
//		connect(this, SIGNAL(sigStopMonitor()), service, SLOT(stopMonitor()));
		connect(this, SIGNAL(sigOnSyncToSlave(QVariantMap, QVariantMap, QVariantMap)), service, SLOT(onSyncToSlave(QVariantMap, QVariantMap, QVariantMap)));
		connect(this, SIGNAL(sigNeedSyncToSlave()), service, SLOT(syncToSlave()));
		connect(service, SIGNAL(sigSyncToSlave(QVariantMap, QVariantMap, QVariantMap)), this, SLOT(syncToSlave(QVariantMap, QVariantMap, QVariantMap)));
		connect(service, SIGNAL(sigVrlState(QVariantMap)), this, SLOT(refreshState(QVariantMap)));
		connect(service, SIGNAL(sigState(AskuBinStateSet)), this, SIGNAL(sigState(AskuBinStateSet)));
		connect(service, SIGNAL(sigKoeff(AskuValueSet)), this, SIGNAL(sigKoeff(AskuValueSet)));

		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void VRL_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void VRL_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 VRL_THREAD::state()
{
//	if(!service || !service->isInitialized())
		return ELEM_NOT;
/*	else if(service->isErrorDevice())
		return ELEM_AVAR;
	else if(service->isLoadedTables()) 
		return ELEM_NORMA;
	else
		return ELEM_ERROR;*/
}

// ------------------------------------------------------------------
