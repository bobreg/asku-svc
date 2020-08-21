#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include <QObject>
#include <QTimer>
#include <QVariantMap>
#include "../common/global.h"
#include "../common/stateset.h"
#include "../common/alarmreset.h"
#include "../common/rgdvset.h"
#include "../common/messageset.h"
#include "canalasku_data.h"
#include "control.h"

// ----------------------------------------------------------------------------

class AskuAlgorithm : public QObject
{
Q_OBJECT

	qint32 m_numGpr;
	bool m_isMain;
	bool m_isWorkGpr;
	bool m_isWorkPpv;
	bool m_isWorkRmo;
	bool m_isWorkSoi;
	AskuRegime m_regime;

	AskuElementsRgdv elementsRgdv;
	AskuStateSet elements;

//from modules
	AskuBinStateSet canalAsku;
	AskuBinStateSet drives;
	AskuBinStateSet coolers;
	AskuBinStateSet ups;
	AskuBinStateSet des;
	AskuBinStateSet mvrlkn;
	AskuBinStateSet pwm;
	AskuBinStateSet avt;
	AskuBinStateSet pos;
	AskuBinStateSet vospd;

	AskuBinStateSet localDasd;
	AskuBinStateSet otherDasd;
	AskuBinStateSet localVoi;
	AskuBinStateSet otherVoi;
	AskuBinStateSet localPoi;
	AskuBinStateSet otherPoi;
	AskuBinStateSet localSvkr;
	AskuBinStateSet otherSvkr;
	AskuBinStateSet localKoeff;
	AskuBinStateSet otherKoeff;
	AskuBinStateSet localCoreTemp;
	AskuBinStateSet otherCoreTemp;

//algorithms
	AskuBinStateSet localPrm;
	AskuBinStateSet otherPrm;
	AskuBinStateSet b124yy08;
	AskuBinStateSet b124ee02;
	AskuBinStateSet b125yy03;
	AskuBinStateSet b124pp04;
	AskuBinStateSet bSOTR;
	AskuBinStateSet canalSOTR;
	AskuBinStateSet bCOND;
	AskuBinStateSet bAntenna;
	AskuBinStateSet bSensors;
	AskuBinStateSet b124yg02;
	AskuBinStateSet bPanelAvt;
	AskuBinStateSet b124yy03;
	AskuBinStateSet b125yy04;
	AskuBinStateSet b126gg02[2];
	AskuBinStateSet bCommunicators;
	AskuBinStateSet b125pk01;
	AskuBinStateSet bCommonPrl;
	AskuBinStateSet bCommonVrl;
	AskuBinStateSet bCommonRlk;
//-----

//rs485 signals & values
	AskuSignalSet sigmap;
	AskuValueSet valmap;

//koeff
	AskuValueSet valLocalPoiKoeff;
	AskuValueSet valLocalPoiPilot;
	AskuValueSet valOtherPoiKoeff;
	AskuValueSet valOtherPoiPilot;
	AskuValueSet valLocalVrlKoeff;
	AskuValueSet valOtherVrlKoeff;
	AskuValueSet valLocalCoreTemp;
	AskuValueSet valOtherCoreTemp;

//period
	AskuValueSet valLocalPeriod;
	AskuValueSet valOtherPeriod;

//ups
	AskuValueSet valUps;

//vospd
	AskuValueSet valVospd;

//Kvit for control
	AskuBinStateSet ctrlKvit;

//reset avars
	AskuAvtoResetAvar *resetAvarBep;
	AskuAvtoResetAvar *resetAvarSvo;

//PRD overheat
	AskuAvtoResetAvar *overheatWarning;
	AskuAvtoResetAvar *overheatCommand;

	QTimer *m_timerBep;
	QTimer *m_timerProc;

	AskuMessageSet messages;
	void prepareMessages();

	void prepareRgdv();

public:
	AskuAlgorithm(qint32 numGpr, QObject * parent = NULL);
	~AskuAlgorithm();

	bool mainGpr();

	void makeMessageState(bool all = false);
	void makeMessageRgdv(bool all = false);

	qint32 processControlCommand(QVariantMap data);

//Режимы работы
	void test();
	void rgdv();
	void raf();

	void funELK_raf();
	void fun124YY08_raf();
	void fun124EE02_raf();
	void fun124YY03_raf();
	void fun125YY03_raf();
	void funSensorsPT();
	void funCondition();
	void funSOTR_raf();
	void funCanalSOTR();
	void funVospd();

	void funPRD_raf();
	void fun124YG02_raf();
	void funPanelAvt_raf();
	void fun125YY04_raf();
	void fun126GG02_raf(qint32 num);
	void funPrdSys_raf();
	void funDC_UMI(quint32 n_prd, quint32 n_module);

	void funPoiKoeffLocal();
	void funPoiKoeffOther();
	void funPoiPilotLocal();
	void funPoiPilotOther();
	void funPoiCommon();
	void funSvkrCoreLocal();
	void funSvkrCoreOther();
	void funSvkrLocal();
	void funSvkrOther();
	void fun125PK01();
	void funPrmLocal();
	void funPrmOther();
	void fun124PP04_raf();
	void funAntenna();
	void funCommunicators();
	void funMpsn();
	void funMvrlKn();
	void funCommonPorl();
	void funCommonMvrl();
	void funCommonUrlk();
	void funPrdTemperature();
	void funPos();

	void funRmo();
	void funPpv();
	void funSoi();

	void checkResetDrive();
	void checkResetCoolers();
	void checkResetPrm();
	void checkResetPrd();

	void updateElements();
	void updateElementsRgdv();

private slots:
	void refreshState();
	void refreshListRgdv();

	void showOverheatWarning();
	void cmdOverheatWarning();

	void checkReserveBep();
	void checkReserveProc();

public slots:
	void start();
	void stop();

	void onTimerBep();
	void onTimerProc();

	void onChangedMain(bool isMain);
	void onChangedRegime(AskuRegime regime);

	void onConnectedGpr();
	void onDisconnectedGpr();
	void onConnectedPpv();
	void onDisconnectedPpv();
	void onConnectedRmo();
	void onDisconnectedRmo();
	void onConnectedSoi();
	void onDisconnectedSoi();

	void onDataAsku(AskuSignalSet sigmap, AskuValueSet valmap);
	void onStateCanalAsku(AskuBinStateSet state);

	void onStateDrive(AskuBinStateSet state);

	void onStateCoolers(AskuBinStateSet state);

	void onStateUps(AskuBinStateSet state, AskuValueSet values);

	void onStateDes(AskuBinStateSet state);

	void onStateVospd(AskuBinStateSet state, AskuValueSet values);

	void onStatePwm(AskuBinStateSet state, AskuValueSet values);

	void onStateAvt(AskuBinStateSet state, AskuValueSet values);

	void onStatePos(AskuBinStateSet state);

	void onStateVrl(AskuBinStateSet state);

	void onStateLocalDasd(AskuBinStateSet state, AskuValueSet values);
	void onStateOtherDasd(AskuBinStateSet state, AskuValueSet values);

	void onStateLocalVoi(AskuBinStateSet state);
	void onStateOtherVoi(AskuBinStateSet state);

	void onStateLocalPoi(AskuBinStateSet state);
	void onStateOtherPoi(AskuBinStateSet state);

	void onKoeffLocalPoi(AskuValueSet state);
	void onKoeffOtherPoi(AskuValueSet state);

	void onPilotLocalPoi(AskuValueSet state);
	void onPilotOtherPoi(AskuValueSet state);

	void onTransmitterLocalPoi(AskuValueSet state);
	void onTransmitterOtherPoi(AskuValueSet state);

	void onStateLocalCoreTemp(AskuBinStateSet state, AskuValueSet values);
	void onStateOtherCoreTemp(AskuBinStateSet state, AskuValueSet values);

signals:
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void cmdSetResetAvarBep(bool oper = false);
	void cmdSetResetAvarSvo(bool oper = false);
	void cmdSetPrdOff(bool oper = false);

	void controlKvit(AskuBinStateSet kvit);

	void setExtTemperature(double value);
	void setPrdTemperature(quint32 num, bool work, double temperature);

	void cmdChangeKits();
//-----------чел---
    void perim_light_on_off(bool);
//-----------чел---
};

// ----------------------------------------------------------------------------

#endif //__ALGORITHM_H__
