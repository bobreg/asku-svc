#include "globalvar.h"
#include "dasd_thread.h"
#include "dasd_service.h"

// ------------------------------------------------------------------
DASD_THREAD::DASD_THREAD(QObject * parent) : QThread(parent)
{
	service = NULL;
}

// ------------------------------------------------------------------
DASD_THREAD::~DASD_THREAD()
{
}

// ------------------------------------------------------------------
void DASD_THREAD::csleep(unsigned long msec)
{
	msleep(msec);
}

// ------------------------------------------------------------------
void DASD_THREAD::run()
{
	service = new DASD_SERVICE(this);
	if(service)
	{
		connect(this, SIGNAL(sigConnectedGpr()), service, SLOT(setConnectedGpr()));
		connect(this, SIGNAL(sigDisconnectedGpr()), service, SLOT(setDisconnectedGpr()));

		connect(this, SIGNAL(sigResetTables()), service, SLOT(resetTables()));
		connect(this, SIGNAL(sigToggleMain()), service, SLOT(toggleMain()));
		connect(this, SIGNAL(sigToggleRipch()), service, SLOT(toggleRipch()));
		connect(this, SIGNAL(sigToggleImitatorPeriod()), service, SLOT(toggleImitatorPeriod()));
		connect(this, SIGNAL(sigToggleAzimuthSource()), service, SLOT(toggleAzimuthSource()));
		connect(this, SIGNAL(sigToggleAzimuthMode()), service, SLOT(toggleAzimuthMode()));
		connect(this, SIGNAL(sigToggleAzimuthPeriod()), service, SLOT(toggleAzimuthPeriod()));
		connect(this, SIGNAL(sigToggleAzimuthLir1Load()), service, SLOT(toggleAzimuthLir1Load()));
		connect(this, SIGNAL(sigToggleAzimuthLir2Load()), service, SLOT(toggleAzimuthLir2Load()));
		connect(this, SIGNAL(sigToggleAzimuthSerialLoad()), service, SLOT(toggleAzimuthSerialLoad()));
		connect(this, SIGNAL(sigToggleBlockZu()), service, SLOT(toggleBlockZu()));
		connect(this, SIGNAL(sigToggleBlockSwitch()), service, SLOT(toggleBlockSwitch()));
		connect(this, SIGNAL(sigToggleBlockYY()), service, SLOT(toggleBlockYY()));
		connect(this, SIGNAL(sigToggleVaruBan()), service, SLOT(toggleVaruBan()));
		connect(this, SIGNAL(sigToggleTestSin()), service, SLOT(toggleTestSin()));
		connect(this, SIGNAL(sigToggleStrobeEnable()), service, SLOT(toggleStrobeEnable()));
		connect(this, SIGNAL(sigToggleBlockAvto()), service, SLOT(toggleBlockAvto()));
		connect(this, SIGNAL(sigToggleImpulsePrd()), service, SLOT(toggleImpulsePrd()));
		connect(this, SIGNAL(sigToggleTimerSource()), service, SLOT(toggleTimerSource()));
		connect(this, SIGNAL(sigToggleSharuSource()), service, SLOT(toggleSharuSource()));
		connect(this, SIGNAL(sigToggleErrorZu1()), service, SLOT(toggleErrorZu1()));
		connect(this, SIGNAL(sigToggleErrorZu2()), service, SLOT(toggleErrorZu2()));
		connect(this, SIGNAL(sigToggleSkrOn()), service, SLOT(toggleSkrOn()));
		connect(this, SIGNAL(sigToggleSkrAlwaysOn()), service, SLOT(toggleSkrAlwaysOn()));
		connect(this, SIGNAL(sigTogglePilotOn()), service, SLOT(togglePilotOn()));
		connect(this, SIGNAL(sigTogglePilotAlwaysOn()), service, SLOT(togglePilotAlwaysOn()));
		connect(this, SIGNAL(sigToggleGshOn()), service, SLOT(toggleGshOn()));
		connect(this, SIGNAL(sigToggleGshAlwaysOn()), service, SLOT(toggleGshAlwaysOn()));
		connect(this, SIGNAL(sigToggleZuOn()), service, SLOT(toggleZuOn()));
		connect(this, SIGNAL(sigToggleZuAlwaysOn()), service, SLOT(toggleZuAlwaysOn()));
		connect(this, SIGNAL(sigToggleTimerLoad()), service, SLOT(toggleTimerLoad()));
		connect(this, SIGNAL(sigSetMain(bool)), service, SLOT(setMain(bool)));
		connect(this, SIGNAL(sigSetRipch(bool)), service, SLOT(setRipch(bool)));
		connect(this, SIGNAL(sigSetAzimuthSource(quint32)), service, SLOT(setCmdActiveSensor(quint32)));
		connect(this, SIGNAL(sigSetOverview(quint32)), service, SLOT(setCmdOverview(quint32)));
		connect(this, SIGNAL(sigSetLir1Offset(quint32)), service, SLOT(setLir1Offset(quint32)));
		connect(this, SIGNAL(sigSetLir2Offset(quint32)), service, SLOT(setLir2Offset(quint32)));
		connect(this, SIGNAL(sigSetLirOffsets(quint32,quint32)), service, SLOT(setLirOffsets(quint32,quint32)));
		connect(this, SIGNAL(sigSetSharu1Code(quint32)), service, SLOT(setSharu1Code(quint32)));
		connect(this, SIGNAL(sigSetSharu2Code(quint32)), service, SLOT(setSharu2Code(quint32)));
		connect(this, SIGNAL(sigSetSharuCodes(quint32,quint32)), service, SLOT(setSharuCodes(quint32,quint32)));
		connect(this, SIGNAL(sigSetSyncrOutput(quint32)), service, SLOT(setSyncrOutput(quint32)));
		connect(this, SIGNAL(sigSetImpulsePrd(quint32)), service, SLOT(setImpulsePrd(quint32)));
		connect(this, SIGNAL(sigSetAmpDelayPilotParam(quint32,quint32)), service, SLOT(setAmpDelayPilotParam(quint32,quint32)));
		connect(this, SIGNAL(sigSetStepDopler(quint32)), service, SLOT(setStepDopler(quint32)));
		connect(this, SIGNAL(sigSetFreqDeviation(quint32)), service, SLOT(setFreqDeviation(quint32)));
		connect(this, SIGNAL(sigSetDump(quint32)), service, SLOT(setDump(quint32)));

		connect(this, SIGNAL(sigStartMonitor()), service, SLOT(startMonitor()));
		connect(this, SIGNAL(sigStopMonitor()), service, SLOT(stopMonitor()));
		connect(this, SIGNAL(sigSetMonitorRate(quint32)), service, SLOT(setMonitorRate(quint32)));

		connect(this, SIGNAL(sigSetDisableTotal(bool)), service, SLOT(setDisableTotal(bool)));
		connect(this, SIGNAL(sigSetDisableDynamic(AskuSektorTable)), service, SLOT(setDisableDynamic(AskuSektorTable)));
		connect(this, SIGNAL(sigSetTemperature(double)), service, SLOT(setTemperature(double)));

		connect(this, SIGNAL(sigRefreshTables(quint32, bool)), service, SLOT(refreshTables(quint32, bool)));
		connect(this, SIGNAL(sigSaveTableRipch(QVariantMap, bool)), service, SLOT(saveTableRipch(QVariantMap, bool)));
		connect(this, SIGNAL(sigSaveTableMode(QVariantMap, bool)), service, SLOT(saveTableMode(QVariantMap, bool)));
		connect(this, SIGNAL(sigSaveTableSwitch(QVariantMap, bool)), service, SLOT(saveTableSwitch(QVariantMap, bool)));
		connect(this, SIGNAL(sigSaveTableDisable(QVariantMap, bool)), service, SLOT(saveTableDisable(QVariantMap, bool)));

		connect(this, SIGNAL(sigUpdateSkrPilot()), service, SLOT(updateSkrPilot()));

		connect(this, SIGNAL(sigSetPrmOn(bool)), service, SLOT(setPrmOn(bool)));
		connect(this, SIGNAL(sigSetPrmGsh(bool)), service, SLOT(setPrmGSH(bool)));
		connect(this, SIGNAL(sigSetPrmZu(bool)), service, SLOT(setPrmZU(bool)));
		connect(this, SIGNAL(sigSetPrmPilot(bool)), service, SLOT(setPrmPILOT(bool)));
		connect(this, SIGNAL(sigSetPrmSkr(bool)), service, SLOT(setPrmSKR(bool)));
		connect(this, SIGNAL(sigSetPrmSharu1Code(quint32)), service, SLOT(setPrmSharu1Code(quint32)));
		connect(this, SIGNAL(sigSetPrmSharu2Code(quint32)), service, SLOT(setPrmSharu2Code(quint32)));

		connect(this, SIGNAL(sigRefreshSetPrm()), service, SLOT(refreshSetPrm()));
		connect(service, SIGNAL(sigRefreshSetPrmInfo(QVariantMap)), this, SLOT(refreshSetPrmInfo(QVariantMap)));

		connect(service, SIGNAL(sigDumpRegisters(DEVICE_REGISTERS)), this, SLOT(dumpRegisters(DEVICE_REGISTERS)));
		connect(service, SIGNAL(sigRefreshRegisters(DEVICE_REGISTERS)), this, SLOT(refreshRegisters(DEVICE_REGISTERS)));
		connect(service, SIGNAL(sigStatusMessage(QString)), this, SLOT(statusMessage(QString)));

		connect(service, SIGNAL(sigTableRipch(QVariantMap, qint32)), this, SLOT(tableRipch(QVariantMap, qint32)));
		connect(service, SIGNAL(sigTableMode(QVariantMap, qint32)), this, SLOT(tableMode(QVariantMap, qint32)));
		connect(service, SIGNAL(sigTableSwitch(QVariantMap, qint32)), this, SLOT(tableSwitch(QVariantMap, qint32)));
		connect(service, SIGNAL(sigTableDisable(QVariantMap, qint32)), this, SLOT(tableDisable(QVariantMap, qint32)));
		connect(service, SIGNAL(sigTablesResults(QString)), this, SLOT(tablesResults(QString)));

		connect(service, SIGNAL(sigChangedAzimuthSource(quint32)), this, SIGNAL(sigChangedAzimuthSource(quint32)));
		connect(service, SIGNAL(sigChangedOffsets(quint32,quint32,quint32)), this, SIGNAL(sigFlushSettings()));

		connect(service, SIGNAL(sigStateLocal(AskuBinStateSet,AskuValueSet)), this, SIGNAL(sigStateLocal(AskuBinStateSet,AskuValueSet)));
		connect(service, SIGNAL(sigStateOther(AskuBinStateSet,AskuValueSet)), this, SIGNAL(sigStateOther(AskuBinStateSet,AskuValueSet)));

		connect(this, SIGNAL(sigOnSyncToSlave(QVariantMap,QVariantMap,QVariantMap)), service, SLOT(onSyncToSlave(QVariantMap,QVariantMap,QVariantMap)));
		connect(this, SIGNAL(sigNeedSyncToSlave()), service, SLOT(syncToSlave()));
		connect(service, SIGNAL(sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap)), this, SLOT(syncToSlave(QVariantMap,QVariantMap,QVariantMap)));

		service->init();

		exec();

		delete service;
		service = NULL;
	}
}

// ------------------------------------------------------------------
void DASD_THREAD::start()
{
	QThread::start();
}

// ------------------------------------------------------------------
void DASD_THREAD::quit()
{
	QThread::quit();
	wait();
}

// ------------------------------------------------------------------
quint8 DASD_THREAD::state()
{
	if(!service || !service->isInitialized())
		return ELEM_NOT;
	else if(service->isErrorDevice())
		return ELEM_AVAR;
	else if(service->isLoadedTables()) 
		return ELEM_NORMA;
	else
		return ELEM_ERROR;
}

// ------------------------------------------------------------------
quint8 DASD_THREAD::stateAzSensor1()
{
	if(!service || !service->isInitialized() || service->isErrorDevice())
		return ELEM_NOT;
	else if(service->isAz1SensorOk()) 
		return ELEM_NORMA;
	else
		return ELEM_AVAR;
}

// ------------------------------------------------------------------
quint8 DASD_THREAD::stateAzSensor2()
{
	if(!service || !service->isInitialized() || service->isErrorDevice())
		return ELEM_NOT;
	else if(service->isAz2SensorOk()) 
		return ELEM_NORMA;
	else
		return ELEM_AVAR;
}

// ------------------------------------------------------------------
quint8 DASD_THREAD::stateSensorSerial()
{
	if(!service || !service->isInitialized() || service->isErrorDevice())
		return ELEM_NOT;
	else if(service->isSerialSensorOk()) 
		return ELEM_NORMA;
	else
		return ELEM_AVAR;
}

// ------------------------------------------------------------------
