#include "globalvar.h"
#include "vospd_thread.h"
#include "vospd_service.h"

// ------------------------------------------------------------------
VOSPD_THREAD::VOSPD_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
	qRegisterMetaType<AskuValueSet>("AskuValueSet");
}

// ------------------------------------------------------------------
VOSPD_THREAD::~VOSPD_THREAD()
{
}

// ------------------------------------------------------------------
void VOSPD_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void VOSPD_THREAD::run()
{
	service = new VOSPD_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(setMain(bool)));
		connect(service, SIGNAL(sigState(AskuBinStateSet,AskuValueSet)), this, SIGNAL(sigState(AskuBinStateSet,AskuValueSet)));
		connect(this, SIGNAL(sigChangedAzimuthSource(quint32)), service, SLOT(onChangedAzimuthSource(quint32)));

		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void VOSPD_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void VOSPD_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 VOSPD_THREAD::state()
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

