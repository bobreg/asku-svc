#include "globalvar.h"
#include "pos_thread.h"
#include "pos_service.h"

// ------------------------------------------------------------------
POS_THREAD::POS_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
	qRegisterMetaType<AskuValueSet>("AskuValueSet");
}

// ------------------------------------------------------------------
POS_THREAD::~POS_THREAD()
{
}

// ------------------------------------------------------------------
void POS_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void POS_THREAD::run()
{
	service = new POS_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(setMain(bool)));
		connect(service, SIGNAL(sigState(AskuBinStateSet)), this, SIGNAL(sigState(AskuBinStateSet)));
        connect(service, SIGNAL(sigOsvPerimetrOn()), this, SIGNAL(sigOsvPerimetrOn()));
        connect(service, SIGNAL(sigOsvPerimetrOff()), this, SIGNAL(sigOsvPerimetrOff()));
        connect(service, SIGNAL(sigEventToLog(QString,QString,QString)), this, SIGNAL(sigEventToLog(QString,QString,QString)));
        connect(this, SIGNAL(perim_light_on_off(bool)), service, SLOT(sendStateRelay(bool)));
		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void POS_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void POS_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 POS_THREAD::state()
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

