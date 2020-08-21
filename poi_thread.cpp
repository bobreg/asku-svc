#include "globalvar.h"
#include "poi_thread.h"
#include "poi_service.h"

// ------------------------------------------------------------------
POI_THREAD::POI_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
	qRegisterMetaType<AskuValueSet>("AskuValueSet");
}

// ------------------------------------------------------------------
POI_THREAD::~POI_THREAD()
{
}

// ------------------------------------------------------------------
void POI_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void POI_THREAD::run()
{
	service = new POI_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(setMain(bool)));
		connect(this, SIGNAL(sigResetKoeff()), service, SLOT(setResetKoeff()));
		connect(this, SIGNAL(sigConnectedGpr()), service, SLOT(setConnectedGpr()));
		connect(this, SIGNAL(sigDisconnectedGpr()), service, SLOT(setDisconnectedGpr()));
		connect(this, SIGNAL(sigSetTemperature(double)), service, SLOT(setTemperature(double)));
		connect(service, SIGNAL(sigStateLocal(AskuBinStateSet)), this, SIGNAL(sigStateLocal(AskuBinStateSet)));
		connect(service, SIGNAL(sigKoeffLocal(AskuValueSet)), this, SIGNAL(sigKoeffLocal(AskuValueSet)));
		connect(service, SIGNAL(sigPilotLocal(AskuValueSet)), this, SIGNAL(sigPilotLocal(AskuValueSet)));
		connect(service, SIGNAL(sigTransmitterLocal(AskuValueSet)), this, SIGNAL(sigTransmitterLocal(AskuValueSet)));
		connect(service, SIGNAL(sigStateOther(AskuBinStateSet)), this, SIGNAL(sigStateOther(AskuBinStateSet)));
		connect(service, SIGNAL(sigKoeffOther(AskuValueSet)), this, SIGNAL(sigKoeffOther(AskuValueSet)));
		connect(service, SIGNAL(sigPilotOther(AskuValueSet)), this, SIGNAL(sigPilotOther(AskuValueSet)));
		connect(service, SIGNAL(sigTransmitterOther(AskuValueSet)), this, SIGNAL(sigTransmitterOther(AskuValueSet)));
		connect(this, SIGNAL(sigOnSyncToSlave(QVariantMap,QVariantMap,QVariantMap,QVariantMap)), service, SLOT(onSyncToSlave(QVariantMap,QVariantMap,QVariantMap,QVariantMap)));
		connect(this, SIGNAL(sigNeedSyncToSlave()), service, SLOT(syncToSlave()));
		connect(service, SIGNAL(sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap,QVariantMap)), this, SLOT(syncToSlave(QVariantMap,QVariantMap,QVariantMap,QVariantMap)));

		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void POI_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void POI_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 POI_THREAD::state()
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

