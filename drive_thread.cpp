#include "globalvar.h"
#include "drive_thread.h"
#include "drive_service.h"

// ------------------------------------------------------------------
DRIVE_THREAD::DRIVE_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
}

// ------------------------------------------------------------------
DRIVE_THREAD::~DRIVE_THREAD()
{
}

// ------------------------------------------------------------------
void DRIVE_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void DRIVE_THREAD::run()
{
	service = new DRIVE_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(setMain(bool)));
		connect(this, SIGNAL(sigSetServo(quint32)), service, SLOT(setServo(quint32)));
		connect(this, SIGNAL(sigSetOverride(quint32)), service, SLOT(setOverride(quint32)));
		connect(this, SIGNAL(sigSetSpeed(double)), service, SLOT(setSpeed(double)));
		connect(this, SIGNAL(sigSetReset()), service, SLOT(setReset()));
		connect(this, SIGNAL(sigSetManual(bool)), service, SLOT(setManual(bool)));
		connect(this, SIGNAL(sigRefreshState()), service, SLOT(onRefreshDrive()));
		connect(this, SIGNAL(sigStartMonitor()), service, SLOT(startMonitor()));
		connect(this, SIGNAL(sigStopMonitor()), service, SLOT(stopMonitor()));
		connect(this, SIGNAL(sigOnSyncToSlave(QVariantMap,QVariantMap,QVariantMap)), service, SLOT(onSyncToSlave(QVariantMap,QVariantMap,QVariantMap)));
		connect(this, SIGNAL(sigNeedSyncToSlave()), service, SLOT(syncToSlave()));
		connect(service, SIGNAL(sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap)), this, SLOT(syncToSlave(QVariantMap,QVariantMap,QVariantMap)));
		connect(service, SIGNAL(sigDriveState(QVariantMap)), this, SLOT(refreshState(QVariantMap)));
		connect(service, SIGNAL(sigState(AskuBinStateSet)), this, SIGNAL(sigState(AskuBinStateSet)));
		connect(service, SIGNAL(sigButtonServo(quint32)), this, SIGNAL(sigButtonServo(quint32)));
		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void DRIVE_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void DRIVE_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 DRIVE_THREAD::state()
{
	return ELEM_NOT;
}

