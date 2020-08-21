#include "globalvar.h"
#include "avt_thread.h"
#include "avt_service.h"

// ------------------------------------------------------------------
AVT_THREAD::AVT_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
	qRegisterMetaType<AskuValueSet>("AskuValueSet");
}

// ------------------------------------------------------------------
AVT_THREAD::~AVT_THREAD()
{
}

// ------------------------------------------------------------------
void AVT_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void AVT_THREAD::run()
{
	service = new AVT_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(setMain(bool)));
		connect(this, SIGNAL(sigSetErase()), service, SLOT(setErase()));
		connect(service, SIGNAL(sigState(AskuBinStateSet,AskuValueSet)), this, SIGNAL(sigState(AskuBinStateSet,AskuValueSet)));

		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void AVT_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void AVT_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 AVT_THREAD::state()
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

