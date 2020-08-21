#include "globalvar.h"
#include "voi_thread.h"
#include "voi_service.h"

// ------------------------------------------------------------------
VOI_THREAD::VOI_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
}

// ------------------------------------------------------------------
VOI_THREAD::~VOI_THREAD()
{
}

// ------------------------------------------------------------------
void VOI_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void VOI_THREAD::run()
{
	service = new VOI_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(setMain(bool)));
		connect(this, SIGNAL(sigConnectedGpr()), service, SLOT(setConnectedGpr()));
		connect(this, SIGNAL(sigDisconnectedGpr()), service, SLOT(setDisconnectedGpr()));
		connect(this, SIGNAL(sigUpdateSkrPilot()), service, SLOT(setControlSektor()));
		connect(service, SIGNAL(sigStateLocal(AskuBinStateSet)), this, SIGNAL(sigStateLocal(AskuBinStateSet)));
		connect(service, SIGNAL(sigStateOther(AskuBinStateSet)), this, SIGNAL(sigStateOther(AskuBinStateSet)));
		connect(service, SIGNAL(sigDisableTotal(bool)), this, SIGNAL(sigDisableTotal(bool)));
		connect(service, SIGNAL(sigDisableDynamic(AskuSektorTable)), this, SIGNAL(sigDisableDynamic(AskuSektorTable)));
		connect(this, SIGNAL(sigOnSyncToSlave(QVariantMap,QVariantMap)), service, SLOT(onSyncToSlave(QVariantMap,QVariantMap)));
		connect(this, SIGNAL(sigNeedSyncToSlave()), service, SLOT(syncToSlave()));
		connect(service, SIGNAL(sigSyncToSlave(QVariantMap,QVariantMap)), this, SLOT(syncToSlave(QVariantMap,QVariantMap)));

		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void VOI_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void VOI_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 VOI_THREAD::state()
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
