#include "globalvar.h"
#include "des_thread.h"
#include "des_service.h"

// ------------------------------------------------------------------
DES_THREAD::DES_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
}

// ------------------------------------------------------------------
DES_THREAD::~DES_THREAD()
{
}

// ------------------------------------------------------------------
void DES_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void DES_THREAD::run()
{
	service = new DES_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(setMain(bool)));
		connect(this, SIGNAL(sigSetEngine(quint32,bool)), service, SLOT(setEngine(quint32,bool)));
		connect(this, SIGNAL(sigSetPosTB(quint32,bool)), service, SLOT(setPosTB(quint32,bool)));
		connect(this, SIGNAL(sigSetPosGB(quint32,bool)), service, SLOT(setPosGB(quint32,bool)));
		connect(this, SIGNAL(sigSetPosMB(quint32,bool)), service, SLOT(setPosMB(quint32,bool)));
		connect(this, SIGNAL(sigSetMainsReset(quint32)), service, SLOT(setMainsReset(quint32)));
		connect(this, SIGNAL(sigSetDgReset(quint32)), service, SLOT(setDgReset(quint32)));
		connect(this, SIGNAL(sigSetMainsMode(quint32,quint32)), service, SLOT(setMainsMode(quint32,quint32)));
		connect(this, SIGNAL(sigSetDgMode(quint32,quint32)), service, SLOT(setDgMode(quint32,quint32)));
		connect(this, SIGNAL(sigRefreshState()), service, SLOT(onRefreshDes()));
		connect(this, SIGNAL(sigStartMonitor()), service, SLOT(startMonitor()));
		connect(this, SIGNAL(sigStopMonitor()), service, SLOT(stopMonitor()));
		connect(this, SIGNAL(sigOnSyncToSlave(QVariantMap)), service, SLOT(onSyncToSlave(QVariantMap)));
		connect(this, SIGNAL(sigNeedSyncToSlave()), service, SLOT(syncToSlave()));
		connect(service, SIGNAL(sigSyncToSlave(QVariantMap)), this, SLOT(syncToSlave(QVariantMap)));
		connect(service, SIGNAL(sigDesState(QVariantMap)), this, SLOT(refreshState(QVariantMap)));
		connect(service, SIGNAL(sigState(AskuBinStateSet)), this, SIGNAL(sigState(AskuBinStateSet)));

		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void DES_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void DES_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 DES_THREAD::state()
{
	return ELEM_NOT;
}

