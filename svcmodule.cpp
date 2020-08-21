#include "globalvar.h"
#include "svcmodule.h"
#include "svcapplication.h"
#include "canalasku.h"
#include "dasd.h"
#include "algorithm.h"
#include "control.h"
#include "voi.h"
#include "poi.h"
#include "vrl.h"
#include "drive.h"
#include "coolers.h"
#include "ups.h"
#include "des.h"
#include "coretemp.h"
#include "powermeter.h"
#include "avtomatica.h"
#include "pos.h"
#include "vospd.h"
#include "viewer.h"

//----------------------------------------------------------------------------------------------------------------
AskuSvcModule::AskuSvcModule(AskuSvcApplication * parent, quint32 idGpr) : AskuModule(parent, idGpr, "AskuModuleSvc", idAskuModuleSvc)
{
	canalAsku = NULL;

	if(ISGPR())
	{
		connect(parent, SIGNAL(prepareToQuit()), this, SLOT(prepareToQuit()));
		connect(this, SIGNAL(flushSettings()), parent, SLOT(flushSettings()));

		mViewer = new AskuViewer(this);
		if(mViewer)
		{
			connect(mViewer, SIGNAL(sendControlAnswer(QVariantMap,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32)));
			connect(mViewer, SIGNAL(sendInfoMessage(QVariantMap,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32)));
		}

		AddStartStopMes("АСКУ", "--------- Инициализация ---------");
		AddStartStopMes("АСКУ", "Версия ПО АСКУ: " + qApp->applicationVersion());

		init(MY_GPR_PORT());
		init(OTHER_GPR_IP(), OTHER_GPR_PORT());

		mAlgorithm = new AskuAlgorithm(IDGPR(), this);
		if(mAlgorithm)
		{
			connect(mAlgorithm, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mAlgorithm, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));
		}

		mControl = new AskuGprControl(IDGPR(), this);
		if(mControl)
		{
			connect(mControl, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mControl, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));
			connect(mControl, SIGNAL(sendSyncMessage(QVariantMap,qint32,qint32)), this, SLOT(sendSyncMessage(QVariantMap,qint32,qint32)));

			connect(mControl, SIGNAL(changedMain(bool)), mAlgorithm, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(sigConnectedGpr()), mAlgorithm, SLOT(onConnectedGpr()));
			connect(mControl, SIGNAL(sigDisconnectedGpr()), mAlgorithm, SLOT(onDisconnectedGpr()));
			connect(mControl, SIGNAL(sigConnectedPpv()), mAlgorithm, SLOT(onConnectedPpv()));
			connect(mControl, SIGNAL(sigDisconnectedPpv()), mAlgorithm, SLOT(onDisconnectedPpv()));
			connect(mControl, SIGNAL(sigConnectedRmo()), mAlgorithm, SLOT(onConnectedRmo()));
			connect(mControl, SIGNAL(sigDisconnectedRmo()), mAlgorithm, SLOT(onDisconnectedRmo()));
			connect(mControl, SIGNAL(sigConnectedSoi()), mAlgorithm, SLOT(onConnectedSoi()));
			connect(mControl, SIGNAL(sigDisconnectedSoi()), mAlgorithm, SLOT(onDisconnectedSoi()));
			connect(mControl, SIGNAL(changedRegime(AskuRegime)), mAlgorithm, SLOT(onChangedRegime(AskuRegime)));
			connect(mControl, SIGNAL(sigRefreshState()), mAlgorithm, SLOT(refreshState()));
			connect(mControl, SIGNAL(sigFlushSettings()), this, SIGNAL(flushSettings()));

			connect(mAlgorithm, SIGNAL(cmdSetResetAvarBep(bool)), mControl, SLOT(cmdSetResetAvarBep(bool)));
			connect(mAlgorithm, SIGNAL(cmdSetResetAvarSvo(bool)), mControl, SLOT(cmdSetResetAvarSvo(bool)));
			connect(mAlgorithm, SIGNAL(cmdSetPrdOff(bool)), mControl, SLOT(cmdSetPrdOff(bool)));
			connect(mAlgorithm, SIGNAL(cmdChangeKits()), mControl, SLOT(cmdChangeKits()));
			connect(mAlgorithm, SIGNAL(controlKvit(AskuBinStateSet)), mControl, SLOT(onControlKvit(AskuBinStateSet)));

			connect(mViewer, SIGNAL(changedHour()), mControl, SLOT(onChangedHour()));
		}

		canalAsku = new CanalAsku(this);
		if(canalAsku)
		{
			connect(canalAsku, SIGNAL(sendControlAnswer(QVariantMap,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32)));
			connect(canalAsku, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));

			connect(canalAsku, SIGNAL(sigState(AskuBinStateSet)), mAlgorithm, SLOT(onStateCanalAsku(AskuBinStateSet)));
			connect(canalAsku, SIGNAL(sigDataAsku(AskuSignalSet, AskuValueSet)), mAlgorithm, SLOT(onDataAsku(AskuSignalSet, AskuValueSet)));
			connect(canalAsku, SIGNAL(sigButtonPum(quint32)), mControl, SLOT(onButtonPum(quint32)));
			connect(canalAsku, SIGNAL(sigButtonPrd(bool)), mControl, SLOT(onButtonPrd(bool)));
			connect(canalAsku, SIGNAL(sigButtonPrd1(bool)), mControl, SLOT(onButtonPrd1(bool)));
			connect(canalAsku, SIGNAL(sigButtonPrd2(bool)), mControl, SLOT(onButtonPrd2(bool)));
			connect(canalAsku, SIGNAL(sigReadyToCheckMode(bool)), mControl, SLOT(onReadyToCheckMode(bool)));

			connect(mControl, SIGNAL(changedMain(bool)), canalAsku, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(needRefreshAll()), canalAsku, SLOT(needSyncToSlave()));
			connect(mControl, SIGNAL(sigConnectedGpr()), canalAsku, SLOT(onConnectedGpr()));
			connect(mControl, SIGNAL(sigDisconnectedGpr()), canalAsku, SLOT(onDisconnectedGpr()));

			connect(mControl, SIGNAL(setMonitorModule(quint32,quint32)), canalAsku, SLOT(setMonitoredModule(quint32,quint32)));
			connect(mControl, SIGNAL(setResetAvarPrd1()), canalAsku, SLOT(putResetPrd1()));
			connect(mControl, SIGNAL(setResetAvarPrd2()), canalAsku, SLOT(putResetPrd2()));
			connect(mControl, SIGNAL(setResetAvarComm()), canalAsku, SLOT(putResetElk()));

			connect(mControl, SIGNAL(setPrd1Off()),  canalAsku, SLOT(putPrdOff1()));
			connect(mControl, SIGNAL(setPrd1On()),   canalAsku, SLOT(putPrdOn1()));

			connect(mControl, SIGNAL(setPrd2Off()),  canalAsku, SLOT(putPrdOff2()));
			connect(mControl, SIGNAL(setPrd2On()),   canalAsku, SLOT(putPrdOn2()));

			connect(mControl, SIGNAL(setPumi1()),    canalAsku, SLOT(putPumi1On()));
			connect(mControl, SIGNAL(setPumiOff()),  canalAsku, SLOT(putPumiOff()));
			connect(mControl, SIGNAL(setPumi2()),    canalAsku, SLOT(putPumi2On()));

			connect(mControl, SIGNAL(setHowl1On()),  canalAsku, SLOT(putOnHowl1()));
			connect(mControl, SIGNAL(setHowl1Off()), canalAsku, SLOT(putOffHowl1()));
			connect(mControl, SIGNAL(setHowl2On()),  canalAsku, SLOT(putOnHowl2()));
			connect(mControl, SIGNAL(setHowl2Off()), canalAsku, SLOT(putOffHowl2()));
		}

		mDASD = new DASD(this);
		if(mDASD)
		{
			connect(mDASD, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mDASD, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));

			connect(mDASD, SIGNAL(sigStateLocal(AskuBinStateSet,AskuValueSet)), mAlgorithm, SLOT(onStateLocalDasd(AskuBinStateSet,AskuValueSet)));
			connect(mDASD, SIGNAL(sigStateOther(AskuBinStateSet,AskuValueSet)), mAlgorithm, SLOT(onStateOtherDasd(AskuBinStateSet,AskuValueSet)));
			connect(mDASD, SIGNAL(sigChangedAzimuthSource(quint32)), mControl, SLOT(onChangedAzimuthSource(quint32)));
			connect(mDASD, SIGNAL(sigFlushSettings()), this, SIGNAL(flushSettings()));

			connect(mControl, SIGNAL(changedMain(bool)), mDASD, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(sigConnectedGpr()), mDASD, SLOT(onConnectedGpr()));
			connect(mControl, SIGNAL(sigDisconnectedGpr()), mDASD, SLOT(onDisconnectedGpr()));
			connect(mControl, SIGNAL(needRefreshAll()), mDASD, SIGNAL(sigNeedSyncToSlave()));

			connect(mControl, SIGNAL(setResetAvarPrm()), mDASD, SLOT(onSetReset()));
			connect(mControl, SIGNAL(setAzimuthSource(quint32)), mDASD, SIGNAL(sigSetAzimuthSource(quint32)));
			connect(mControl, SIGNAL(setOverview(quint32)), mDASD, SIGNAL(sigSetOverview(quint32)));

			connect(mAlgorithm, SIGNAL(setExtTemperature(double)), mDASD, SIGNAL(sigSetTemperature(double)));
		}

		mVOI = new VOI(this);
		if(mVOI)
		{
			connect(mVOI, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mVOI, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));

			connect(mVOI, SIGNAL(sigStateLocal(AskuBinStateSet)), mAlgorithm, SLOT(onStateLocalVoi(AskuBinStateSet)));
			connect(mVOI, SIGNAL(sigStateOther(AskuBinStateSet)), mAlgorithm, SLOT(onStateOtherVoi(AskuBinStateSet)));
			connect(mVOI, SIGNAL(sigDisableTotal(bool)), mDASD, SIGNAL(sigSetDisableTotal(bool)));
			connect(mVOI, SIGNAL(sigDisableDynamic(AskuSektorTable)), mDASD, SIGNAL(sigSetDisableDynamic(AskuSektorTable)));

			connect(mControl, SIGNAL(changedMain(bool)), mVOI, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(sigConnectedGpr()), mVOI, SLOT(onConnectedGpr()));
			connect(mControl, SIGNAL(sigDisconnectedGpr()), mVOI, SLOT(onDisconnectedGpr()));
			connect(mControl, SIGNAL(needRefreshAll()), mVOI, SIGNAL(sigNeedSyncToSlave()));

			connect(mDASD, SIGNAL(sigUpdateSkrPilot()), mVOI, SIGNAL(sigUpdateSkrPilot()));
		}

		mPOI = new POI(this);
		if(mPOI)
		{
			connect(mPOI, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mPOI, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));

			connect(mPOI, SIGNAL(sigStateLocal(AskuBinStateSet)), mAlgorithm, SLOT(onStateLocalPoi(AskuBinStateSet)));
			connect(mPOI, SIGNAL(sigKoeffLocal(AskuValueSet)), mAlgorithm, SLOT(onKoeffLocalPoi(AskuValueSet)));
			connect(mPOI, SIGNAL(sigPilotLocal(AskuValueSet)), mAlgorithm, SLOT(onPilotLocalPoi(AskuValueSet)));
			connect(mPOI, SIGNAL(sigTransmitterLocal(AskuValueSet)), mAlgorithm, SLOT(onTransmitterLocalPoi(AskuValueSet)));
			connect(mPOI, SIGNAL(sigStateOther(AskuBinStateSet)), mAlgorithm, SLOT(onStateOtherPoi(AskuBinStateSet)));
			connect(mPOI, SIGNAL(sigKoeffOther(AskuValueSet)), mAlgorithm, SLOT(onKoeffOtherPoi(AskuValueSet)));
			connect(mPOI, SIGNAL(sigPilotOther(AskuValueSet)), mAlgorithm, SLOT(onPilotOtherPoi(AskuValueSet)));
			connect(mPOI, SIGNAL(sigTransmitterOther(AskuValueSet)), mAlgorithm, SLOT(onTransmitterOtherPoi(AskuValueSet)));

			connect(mControl, SIGNAL(changedMain(bool)), mPOI, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(setResetAvarPrm()), mPOI, SLOT(onResetKoeff()));
			connect(mControl, SIGNAL(sigConnectedGpr()), mPOI, SLOT(onConnectedGpr()));
			connect(mControl, SIGNAL(sigDisconnectedGpr()), mPOI, SLOT(onDisconnectedGpr()));
			connect(mControl, SIGNAL(needRefreshAll()), mPOI, SIGNAL(sigNeedSyncToSlave()));

			connect(mAlgorithm, SIGNAL(setExtTemperature(double)), mPOI, SIGNAL(sigSetTemperature(double)));
		}

		mVRL = new VRL(this);
		if(mVRL)
		{
			connect(mVRL, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mVRL, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));

			connect(mVRL, SIGNAL(sigState(AskuBinStateSet)), mAlgorithm, SLOT(onStateVrl(AskuBinStateSet)));

			connect(mControl, SIGNAL(changedMain(bool)), mVRL, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(sigConnectedGpr()), mVRL, SLOT(onConnectedGpr()));
			connect(mControl, SIGNAL(sigDisconnectedGpr()), mVRL, SLOT(onDisconnectedGpr()));
			connect(mControl, SIGNAL(needRefreshAll()), mVRL, SIGNAL(sigNeedSyncToSlave()));

			connect(mControl, SIGNAL(setMainVrl(quint32)), mVRL, SIGNAL(sigSetMainVRL(quint32)));
			connect(mControl, SIGNAL(setReconfVrl(bool)), mVRL, SIGNAL(sigSetDisableReconf(bool)));
			connect(mVOI, SIGNAL(sigDisableTotal(bool)), mVRL, SLOT(cmdDisableTotal(bool)));
			connect(mVOI, SIGNAL(sigDisableDynamic(AskuSektorTable)), mVRL, SLOT(cmdDisableDynamic(AskuSektorTable)));
		}

		mDRIVE = new DRIVE(this);
		if(mDRIVE)
		{
			connect(mDRIVE, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mDRIVE, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));

			connect(mDRIVE, SIGNAL(sigState(AskuBinStateSet)), mAlgorithm, SLOT(onStateDrive(AskuBinStateSet)));
			connect(mDRIVE, SIGNAL(sigButtonServo(quint32)), mControl, SLOT(onButtonDrive(quint32)));

			connect(mControl, SIGNAL(changedMain(bool)), mDRIVE, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(sigConnectedGpr()), mDRIVE, SLOT(onConnectedGpr()));
			connect(mControl, SIGNAL(sigDisconnectedGpr()), mDRIVE, SLOT(onDisconnectedGpr()));
			connect(mControl, SIGNAL(needRefreshAll()), mDRIVE, SIGNAL(sigNeedSyncToSlave()));

			connect(mControl, SIGNAL(setResetAvarBep()), mDRIVE, SLOT(onSetReset()));
			connect(mControl, SIGNAL(setBep1On()), mDRIVE, SLOT(onSetServo1On()));
			connect(mControl, SIGNAL(setBep2On()), mDRIVE, SLOT(onSetServo2On()));
			connect(mControl, SIGNAL(setBepOff()), mDRIVE, SLOT(onSetServoOff()));
			connect(mControl, SIGNAL(setBepOn()), mDRIVE, SLOT(onSetServoOn()));
			connect(mControl, SIGNAL(setOverview(quint32)), mDRIVE, SLOT(onSetOverview(quint32)));
			connect(mControl, SIGNAL(needRefreshAll()), mDRIVE, SIGNAL(sigNeedSyncToSlave()));
		}

		mCOOLERS = new COOLERS(this);
		if(mCOOLERS)
		{
			connect(mCOOLERS, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mCOOLERS, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));
			connect(mCOOLERS, SIGNAL(sigState(AskuBinStateSet)), mAlgorithm, SLOT(onStateCoolers(AskuBinStateSet)));
			connect(mControl, SIGNAL(changedMain(bool)), mCOOLERS, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(setResetAvarSvo()), mCOOLERS, SLOT(onSetReset()));
			connect(mControl, SIGNAL(needRefreshAll()), mCOOLERS, SIGNAL(sigNeedSyncToSlave()));
//			connect(mControl, SIGNAL(setSvo1Off()), mCOOLERS, SLOT(cmdSetSvo1Off()));
//			connect(mControl, SIGNAL(setSvo1On()),  mCOOLERS, SLOT(cmdSetSvo1On()));
//			connect(mControl, SIGNAL(setSvo2Off()), mCOOLERS, SLOT(cmdSetSvo2Off()));
//			connect(mControl, SIGNAL(setSvo2On()),  mCOOLERS, SLOT(cmdSetSvo2On()));
			connect(mAlgorithm, SIGNAL(setPrdTemperature(quint32,bool,double)), mCOOLERS, SLOT(onSetTemperature(quint32,bool,double)));
			connect(mAlgorithm, SIGNAL(setExtTemperature(double)), mCOOLERS, SLOT(onSetExtTemperature(double)));
		}

		mUPS = new UPS(this);
		if(mUPS)
		{
			connect(mUPS, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mUPS, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));

			connect(mUPS, SIGNAL(sigState(AskuBinStateSet,AskuValueSet)), mAlgorithm, SLOT(onStateUps(AskuBinStateSet,AskuValueSet)));

			connect(mControl, SIGNAL(changedMain(bool)), mUPS, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(sigConnectedGpr()), mUPS, SLOT(onConnectedGpr()));
			connect(mControl, SIGNAL(sigDisconnectedGpr()), mUPS, SLOT(onDisconnectedGpr()));
			connect(mControl, SIGNAL(needRefreshAll()), mUPS, SIGNAL(sigNeedSyncToSlave()));
		}

		mCORE = new CORETEMP(this);
		if(mCORE)
		{
			connect(mCORE, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mCORE, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));

			connect(mCORE, SIGNAL(sigStateLocal(AskuBinStateSet,AskuValueSet)), mAlgorithm, SLOT(onStateLocalCoreTemp(AskuBinStateSet,AskuValueSet)));
			connect(mCORE, SIGNAL(sigStateOther(AskuBinStateSet,AskuValueSet)), mAlgorithm, SLOT(onStateOtherCoreTemp(AskuBinStateSet,AskuValueSet)));

			connect(mControl, SIGNAL(changedMain(bool)), mCORE, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(sigConnectedGpr()), mCORE, SLOT(onConnectedGpr()));
			connect(mControl, SIGNAL(sigDisconnectedGpr()), mCORE, SLOT(onDisconnectedGpr()));
			connect(mControl, SIGNAL(needRefreshAll()), mCORE, SIGNAL(sigNeedSyncToSlave()));
		}

		mDES = new DES(this);
		if(mDES)
		{
			connect(mDES, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mDES, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));
			connect(mDES, SIGNAL(sigState(AskuBinStateSet)), mAlgorithm, SLOT(onStateDes(AskuBinStateSet)));
			connect(mControl, SIGNAL(changedMain(bool)), mDES, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(needRefreshAll()), mDES, SIGNAL(sigNeedSyncToSlave()));
		}

		mPWM = new PowerMeter(this);
		if(mPWM)
		{
			connect(mPWM, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mPWM, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));
			connect(mPWM, SIGNAL(sendControlCommand(QVariantMap,qint32,qint32)), this, SLOT(sendControlCommand(QVariantMap,qint32,qint32)));

			connect(mPWM, SIGNAL(sigState(AskuBinStateSet,AskuValueSet)), mAlgorithm, SLOT(onStatePwm(AskuBinStateSet,AskuValueSet)));

			connect(mControl, SIGNAL(changedMain(bool)), mPWM, SLOT(onChangedMain(bool)));
			connect(mControl, SIGNAL(sigConnectedPwm()), mPWM, SLOT(onConnected()));
			connect(mControl, SIGNAL(sigDisconnectedPwm()), mPWM, SLOT(onDisconnected()));

			connect(mControl, SIGNAL(cmdMeasurePower()), mPWM, SLOT(cmdMeasure()));
		}

		mAVT = new Avtomatica(this);
		if(mAVT)
		{
			connect(mAVT, SIGNAL(sendControlAnswer(QVariantMap,qint32,qint32)), this, SLOT(sendControlAnswer(QVariantMap,qint32,qint32)));
			connect(mAVT, SIGNAL(sendInfoMessage(QVariantMap,qint32,qint32)), this, SLOT(sendInfoMessage(QVariantMap,qint32,qint32)));
			connect(mAVT, SIGNAL(sigState(AskuBinStateSet,AskuValueSet)), mAlgorithm, SLOT(onStateAvt(AskuBinStateSet,AskuValueSet)));
			connect(mControl, SIGNAL(sigConnectedAvt()), mAVT, SLOT(onConnected()));
			connect(mControl, SIGNAL(sigDisconnectedAvt()), mAVT, SLOT(onDisconnected()));
			connect(mControl, SIGNAL(changedMain(bool)), mAVT, SLOT(onChangedMain(bool)));
			connect(mAVT, SIGNAL(sendControlCommand(QVariantMap,qint32,qint32)), this, SLOT(sendControlCommand(QVariantMap,qint32,qint32)));
		}

		mPOS = new POS(this);
		if(mPOS)
		{
// см. сюды
            connect(mPOS, SIGNAL(sigState(AskuBinStateSet)), mAlgorithm, SLOT(onStatePos(AskuBinStateSet)));
            connect(mPOS, SIGNAL(sigOsvPerimetrOn()), canalAsku, SLOT(putOnPerimLight()));
            connect(mPOS, SIGNAL(sigOsvPerimetrOff()), canalAsku, SLOT(putOffPerimLight()));
			connect(mControl, SIGNAL(changedMain(bool)), mPOS, SLOT(onChangedMain(bool)));
            connect(mAlgorithm, SIGNAL(perim_light_on_off(bool)), mPOS, SIGNAL(perim_light_on_off(bool)));
            connect(mPOS, SIGNAL(sigEventToLog(QString,QString,QString)), this, SLOT(eventFromPosToLog(QString,QString,QString)));
		}

		mVOSPD = new VOSPD(this);
		if(mVOSPD)
		{
			connect(mVOSPD, SIGNAL(sigState(AskuBinStateSet,AskuValueSet)), mAlgorithm, SLOT(onStateVospd(AskuBinStateSet,AskuValueSet)));
			connect(mControl, SIGNAL(changedMain(bool)), mVOSPD, SLOT(onChangedMain(bool)));
			connect(mDASD, SIGNAL(sigChangedAzimuthSource(quint32)), mVOSPD, SLOT(onChangedAzimuthSource(quint32)));
		}

		if(mControl)
			mControl->start();

		if(mAlgorithm)
			mAlgorithm->start();

		if(mVOI)
			mVOI->start();

		if(mPOI)
			mPOI->start();

		if(mVRL)
			mVRL->start();

		if(mDRIVE)
			mDRIVE->start();

		if(mCOOLERS)
			mCOOLERS->start();

		if(mUPS)
			mUPS->start();

		if(mDES)
			mDES->start();

		if(mCORE)
			mCORE->start();

		if(mVOSPD)
			mVOSPD->start();

		if(mDASD)
			mDASD->start();

		if(mPWM)
			mPWM->start();

		if(mAVT)
			mAVT->start();

		if(mPOS)
			mPOS->start();

		if(canalAsku)
			canalAsku->start();

		AddStartStopMes("АСКУ", "--------- Начало работы ---------");
	}
}

//----------------------------------------------------------------------------------------------------------------
AskuSvcModule::~AskuSvcModule()
{
	if(mPOS)
	{
		mPOS->quit();
		delete mPOS;
	}
	if(mVOSPD)
	{
		mVOSPD->quit();
		delete mVOSPD;;
	}
	if(mAVT)
	{
		mAVT->stop();
		delete mAVT;
	}
	if(mPWM)
	{
		mPWM->stop();
		delete mPWM;
	}
	if(mControl)
	{
		mControl->stop();
		delete mControl;
	}
	if(mAlgorithm)
	{
		mAlgorithm->stop();
		delete mAlgorithm;
	}
	if(mDASD)
	{
		mDASD->quit();
		delete mDASD;
	}
	if(mVRL)
	{
		mVRL->quit();
		delete mVRL;
	}
	if(mVOI)
	{
		mVOI->quit();
		delete mVOI;
	}
	if(mCORE)
	{
		mCORE->quit();
		delete mCORE;
	}
	if(mDES)
	{
		mDES->quit();
		delete mDES;
	}
	if(mUPS)
	{
		mUPS->quit();
		delete mUPS;
	}
	if(mCOOLERS)
	{
		mCOOLERS->quit();
		delete mCOOLERS;
	}
	if(mDRIVE)
	{
		mDRIVE->quit();
		delete mDRIVE;
	}
	if(mPOI)
	{
		mPOI->quit();
		delete mPOI;
	}
	if(canalAsku)
	{
		canalAsku->quit();
		delete canalAsku;
	}
	destroy();
	if(mViewer)
	{
		mViewer->quit();
		delete mViewer;
	}
}

//----------------------------------------------------------------------------------------------------------------
void AskuSvcModule::prepareToQuit()
{
	AddStartStopMes("АСКУ", "------- Завершение работы -------");

	if(mControl)
		mControl->prepareToQuit();
}

//----------------------------------------------------------------------------------------------------------------
void AskuSvcModule::processMessage(AskuMessage & message, qint32 idModule, qint32 idConnection)
{
	Q_UNUSED(idConnection);
	QString type = message.getType();
	quint32 idGpr = message.getId();
	qint32 processed = CommandNotFound;
	QString module;
	QString command;

	if(type == "Hello")
	{
//		LogInfo("recv Hello");
		sendStartup(idConnection);
		processed = CommandSuccess;
	}
	else if(type == "Startup")
	{
//		LogInfo("recv Startup");
		if(idModule == idAskuModuleSvc)
			QTimer::singleShot(0, mControl, SLOT(refreshControl()));
		processed = CommandSuccess;
	}
	else if(type == "ByeBye")
	{
//		LogInfo("recv ByeBye");
		processed = CommandSuccess;
	}
	else if(type == "ControlCommand")
	{
		if(message.hasData())
		{
			processed = CommandNotModule;

			QVariantMap map = message.getDataMap().value("Data").toMap();
			module = map["ModuleTo"].toString();

			if(module == "dasd")
			{
				if(mDASD != NULL)
				{
					command = map["Command"].toString();
					processed = mDASD->processControlCommand(map);
				}
			}
			else if(module == "voi")
			{
				if(mVOI != NULL)
				{
					command = map["Command"].toString();
					processed = mVOI->processControlCommand(map);
				}
			}
			else if(module == "algorithm")
			{
				if(mAlgorithm != NULL)
				{
					command = map["Command"].toString();
					processed = mAlgorithm->processControlCommand(map);
				}
			}
			else if(module == "control")
			{
				if(mControl != NULL)
				{
					command = map["Command"].toString();
					processed = mControl->processControlCommand(map);
				}
			}
			else if(module == "canalasku")
			{
				if(canalAsku != NULL)
				{
					command = map["Command"].toString();
					processed = canalAsku->processControlCommand(map);
				}
			}
			else if(module == "viewer")
			{
				if(mViewer != NULL)
				{
					command = map["Command"].toString();
					processed = mViewer->processControlCommand(map);
				}
			}
			else if(module == "coolers")
			{
				if(mCOOLERS != NULL)
				{
					command = map["Command"].toString();
					processed = mCOOLERS->processControlCommand(map);
				}
			}
			else if(module == "drive")
			{
				if(mDRIVE != NULL)
				{
					command = map["Command"].toString();
					processed = mDRIVE->processControlCommand(map);
				}
			}
			else if(module == "ups")
			{
				if(mUPS != NULL)
				{
					command = map["Command"].toString();
					processed = mUPS->processControlCommand(map);
				}
			}
			else if(module == "des")
			{
				if(mDES != NULL)
				{
					command = map["Command"].toString();
					processed = mDES->processControlCommand(map);
				}
			}
			else if(module == "vrl")
			{
				if(mVRL != NULL)
				{
					command = map["Command"].toString();
					processed = mVRL->processControlCommand(map);
				}
			}
			else if(module == "poi")
			{
				if(mPOI != NULL)
				{
					command = map["Command"].toString();
					processed = mPOI->processControlCommand(map);
				}
			}
			else if(module == "pwm")
			{
				if(mPWM != NULL)
				{
					command = map["Command"].toString();
					processed = mPWM->processControlCommand(map);
				}
			}
			else if(module == "avt")
			{
				if(mAVT != NULL)
				{
					command = map["Command"].toString();
					processed = mAVT->processControlCommand(map);
				}
			}
			else if(module == "coretemp")
			{
				if(mCORE != NULL)
				{
					command = map["Command"].toString();
					processed = mCORE->processControlCommand(map);
				}
			}
			else if(module == "svc_module")
			{
				command = map["Command"].toString();
				processed = processControlCommand(map);
			}
		}
		else
		{
			processed = CommandInvalid;
		}
	}
	else if(type == "ControlAnswer")
	{
		processed = CommandSuccess;
	}
	else if(type == "InfoMessage")
	{
//		LogInfo("recv InfoMessage");

		if(message.hasData())
		{
			processed = CommandNotModule;

			QVariantMap map = message.getDataMap().value("Data").toMap();
			module = map["ModuleTo"].toString();

			if(module == "dialog_control_panel" || module == "control")
			{
				if(mControl)
				{
					command = map["InfoType"].toString();
					processed = mControl->processInfo(idGpr, map);
				}
			}
			else if(module == "dasd")
			{
				if(mDASD)
				{
					command = map["InfoType"].toString();
					processed = mDASD->processInfo(map);
				}
			}
			else if(module == "voi")
			{
				if(mVOI)
				{
					command = map["InfoType"].toString();
					processed = mVOI->processInfo(map);
				}
			}
			else if(module == "drive")
			{
				if(mDRIVE)
				{
					command = map["InfoType"].toString();
					processed = mDRIVE->processInfo(map);
				}
			}
			else if(module == "coolers")
			{
				if(mCOOLERS)
				{
					command = map["InfoType"].toString();
					processed = mCOOLERS->processInfo(map);
				}
			}
			else if(module == "ups")
			{
				if(mUPS)
				{
					command = map["InfoType"].toString();
					processed = mUPS->processInfo(map);
				}
			}
			else if(module == "des")
			{
				if(mDES)
				{
					command = map["InfoType"].toString();
					processed = mDES->processInfo(map);
				}
			}
			else if(module == "vrl")
			{
				if(mVRL)
				{
					command = map["InfoType"].toString();
					processed = mVRL->processInfo(map);
				}
			}
			else if(module == "poi")
			{
				if(mPOI)
				{
					command = map["InfoType"].toString();
					processed = mPOI->processInfo(map);
				}
			}
			else if(module == "pwm")
			{
				if(mPWM)
				{
					command = map["InfoType"].toString();
					processed = mPWM->processInfo(map);
				}
			}
			else if(module == "coretemp")
			{
				if(mCORE)
				{
					command = map["Command"].toString();
					processed = mCORE->processInfo(map);
				}
			}
			else if(module == "avt")
			{
				if(mAVT)
				{
					command = map["InfoType"].toString();
					processed = mAVT->processInfo(map);
				}
			}
			else if(module == "canalasku")
			{
				if(canalAsku)
				{
					command = map["InfoType"].toString();
					processed = canalAsku->processInfo(map);
				}
			}
		}
		else
		{
			processed = CommandInvalid;
		}
	}
	else if(type == "SyncMessage")
	{
		if(message.hasData())
		{
			processed = CommandNotModule;

			QVariantMap map = message.getDataMap().value("Data").toMap();
			module = map["ModuleTo"].toString();

			if(module == "control")
			{
				if(mControl != NULL)
				{
					command = map["Sync"].toString();
					processed = mControl->processSyncControl(idGpr, idModule, map);
				}
			}
		}
		else
		{
			processed = CommandInvalid;
		}
	}

	switch(processed)
	{
		case CommandSuccess:
			//LogInfo("Control: \"%s\" processed \"%s\"", qPrintable(module), qPrintable(command));
			break;
		case CommandNotModule:
			LogError("Control: unknown module \"%s\"", qPrintable(module));
			break;
		case CommandNotFound:
			LogError("Control: unknown \"%s\" command \"%s\"", qPrintable(module), qPrintable(command));
			break;
		case CommandInvalid:
			LogError("Control: invalid \"%s\" command \"%s\"", qPrintable(module), qPrintable(command));
			break;
		case CommandNotEnoughParameters:
			LogError("Control: not enough parameters \"%s\" command \"%s\"", qPrintable(module), qPrintable(command));
			break;
		case CommandInvalidParameter:
			LogError("Control: invalid parameter \"%s\" command \"%s\"", qPrintable(module), qPrintable(command));
			break;
	}
}

//----------------------------------------------------------------------------------------------------------------
qint32 AskuSvcModule::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("AskuSvcModule: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogError("AskuSvcModule: empty command");
		return result;
	}

	bool ok = false;
	quint32 numGpr = data["ToGprId"].toUInt(&ok);
	if(ok && numGpr != IDGPR())
	{
		LogError("AskuSvcModule: success but not mine");
		result = AskuModule::CommandSuccess;
		return result;
	}

	LogError("Command: %s", qPrintable(command));

	if(command == "refreshLogger")
	{
		QTimer::singleShot(0, this, SLOT(makeLoggerMessage()));
		result = AskuModule::CommandSuccess;
	}
	if(command == "setLogger")
	{
		bool console = false;
		bool file = false;
		LogLevels levels = 0;

		bool ok1 = false;
		bool ok2 = false;
		bool ok3 = false;

		if(parameters.count() == 3)
		{
			console = (bool)parameters[0].toUInt(&ok1);
			file    = (bool)parameters[1].toUInt(&ok2);
			levels  = (qulonglong)parameters[2].toULongLong(&ok3,16);

			if(ok1 && ok2 && ok3)
			{
				if(globalLog)
				{
					globalLog->setLogOutConsole(console);
					globalLog->setLogOutFile(file);
					globalLog->setLogLevel(levels);
				}

				m_globaldata.log.level = levels;
				m_globaldata.log.console = console;
				m_globaldata.log.file = file;

				QTimer::singleShot(0, this, SIGNAL(flushSettings()));

				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
		else
		{
			result = AskuModule::CommandInvalidParameter;
		}
	}

	QVariantMap answer;

	switch(result)
	{
		case AskuModule::CommandNotFound:
			answer["Result"] = QString("NotFound");
			break;
		case AskuModule::CommandSuccess:
			answer["Result"] = QString("Success");
			break;
		case AskuModule::CommandInvalid:
			answer["Result"] = QString("Invalid");
			break;
		case AskuModule::CommandNotEnoughParameters:
			answer["Result"] = QString("NotEnoughParameters");
			break;
		case AskuModule::CommandInvalidParameter:
			answer["Result"] = QString("InvalidParameter");
			break;
	}

	answer["ModuleTo"] = data["ModuleFrom"];
	answer["ModuleFrom"] = data["ModuleTo"];
	answer["WasCommand"] = data["Command"];

	sendControlAnswer(answer, idAskuModuleGui);

	return result;
}

//----------------------------------------------------------------------------------------------------------------
void AskuSvcModule::makeLoggerMessage()
{
	QVariantMap data;

	data["InfoType"] = "ASKU_MODULE_LOGGER";
	data["ModuleTo"] = "dialog_logger";
	data["ModuleFrom"] = "svc_module";
	data["GprId"] = IDGPR();

	QVariantMap vals;
	if(globalLog)
	{
		vals["console"] = QString::number(globalLog->getLogOutConsole());
		vals["file"] = QString::number(globalLog->getLogOutFile());
		vals["levels"] = QString::number((qulonglong)globalLog->getLogLevel(),16);
	}
	data["Logger"] = vals;

	sendInfoMessage(data, idAskuModuleGui);
}

//----------------------------------------------------------------------------------------------------------------

void AskuSvcModule::eventFromPosToLog(QString sourse, QString message, QString type){
    if(type == "alert"){
        AddAvarMes(sourse, message);
    }else if(type == "norma"){
        AddNormaMes(sourse, message);
    }else if(type == "event"){
        AddSimpleMes(sourse, message);
    }
}
