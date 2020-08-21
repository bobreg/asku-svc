#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "control_raf.h"

// ----------------------------------------------------------------------------

enum AskuRegime {
	RegInit = 0,
	RegTest = 1,
	RegRgdv = 2,
	RegRaf = 3
};

// ----------------------------------------------------------------------------

enum AskuSwitchCommands {
	cmdOk = 0,
	cmdStartSwitchMain = 1,
	cmdSwitchedMain = 2,
	cmdStartSwitchSlave = 3,
	cmdSwitchedSlave = 4
};

// ----------------------------------------------------------------------------
enum AskuWaitTimeouts {
	INIT_WAIT_TIMEOUT = 10,
	CONTROL_GPR_TIMEOUT = 20,
	CONTROL_PPV_TIMEOUT = 10,
	CONTROL_RMO_TIMEOUT = 20,
	CONTROL_SOI_TIMEOUT = 30,
	CONTROL_PWM_TIMEOUT = 10,
	CONTROL_AVT_TIMEOUT = 10
};

// ----------------------------------------------------------------------------

class AskuGprControl : public QObject, public AskuOnOffRaf
{
Q_OBJECT

	QTimer *m_syncTimer;
	QTimer *m_BepStartTimer;
	QTimer *m_powerTimer;

	qint32 m_numGpr;
	qint32 m_numCtrl;
	bool m_isMain;
	quint32 m_mainGpr;
	quint32 m_mainGprOther;
	bool m_isWorkGpr;
	bool m_isWorkPpv;
	bool m_isWorkRmo;
	bool m_isWorkSoi;
	bool m_isWorkPwm;
	bool m_isWorkAvt;
	quint32 m_changeCmd;
	quint32 m_stamp;
	quint32 m_recvStamp;
	quint32 m_counterGpr;
	quint32 m_counterPpv;
	quint32 m_counterRmo;
	quint32 m_counterSoi;
	quint32 m_counterPwm;
	quint32 m_counterAvt;
	quint32 m_initCounter;
	
	AskuRegime m_regime;
	AskuRlkCommandSet m_commands;
	AskuBinStateSet m_kvit;
	AskuRlkRafMessage m_rafMessages;
	QDateTime m_rafMessagesUpdated;

	void verifyStatus();

public:
	AskuGprControl(qint32 numGpr, QObject * parent = NULL);
	~AskuGprControl();

	bool mainGpr();
	AskuRegime regime();

	qint32 processControlCommand(QVariantMap data);
	qint32 processSyncControl(quint32 idGpr, quint32 idModule, QVariantMap data);
	qint32 processSyncControlGpr(quint32 id, QVariantMap sync);
	qint32 processSyncControlPpv(quint32 id, QVariantMap sync);
	qint32 processSyncControlPwm(quint32 id, QVariantMap sync);
	qint32 processSyncControlAvt(quint32 id, QVariantMap sync);
	qint32 processSyncControlRmo(quint32 id, QVariantMap sync);
	qint32 processSyncControlSoi(quint32 id, QVariantMap sync);
	qint32 processInfo(quint32 id, QVariantMap data);

	static QString regimeName(AskuRegime regime);

protected slots:
	void rafOnOffTimeout();
	void syncTimeout();
	void checkOverview();

	void onConnectedGpr();
	void onDisconnectedGpr();

	void onTimeBepStart();

	void makeMessage();
	void makeControlPanelMessage();
	void makeRafOnOffMessage();
	void makeSyncMessage();
	void makeVersionMessage();

public slots:
	void start();
	void stop();

	void refreshVersion();
	void refreshControl();
	void refreshPanel();

	void cmdChangeKits();
	void cmdSetMainObr(quint32 setObr, bool oper = false);

	void prepareToQuit();
	void setMain(bool isMain);
	void setRegime(AskuRegime reg);

	void setStatusRgdv(QString state, QString text = QString());
	void setStatusRaf(QString state, QString text = QString());

	void cmdSetRafOff(bool oper = false);
	void cmdSetRafOn(bool oper = false);
	void cmdSetRaf(bool oper = false);
	void cmdSetRgdv(bool oper = false);
	void cmdSetTest(bool oper = false);

	void cmdSetBepOn(bool oper = false);
	void cmdSetBepOff(bool oper = false);
	void cmdSetBep1On(bool oper = false, bool no_howl = false);
	void cmdSetBep2On(bool oper = false, bool no_howl = false);

	void cmdSetResetAvarPrd1(bool oper = false);
	void cmdSetResetAvarPrd2(bool oper = false);
	void cmdSetResetAvarPrm(bool oper = false);
	void cmdSetResetAvarBep(bool oper = false);
	void cmdSetResetAvarSvo(bool oper = false);
	void cmdSetResetAvarComm(bool oper = false);

	void cmdSetPrdOff(bool oper = false);
	void cmdSetPrdOn(bool oper = false);
	void cmdSetPrd1Off(bool oper = false);
	void cmdSetPrd1On(bool oper = false);
	void cmdSetPrd2Off(bool oper = false);
	void cmdSetPrd2On(bool oper = false);
	void cmdSetPumiOff(bool oper = false);
	void cmdSetPumi1(bool oper = false);
	void cmdSetPumi2(bool oper = false);

	void cmdSetAzimuth1(bool oper = false);
	void cmdSetAzimuth2(bool oper = false);

	void cmdSetOverview1(bool oper = false);
	void cmdSetOverview2(bool oper = false);

	void cmdSetObrResOff(bool oper = false);
	void cmdSetObrResOn(bool oper = false);

	void cmdSetVrl1(bool oper = false);
	void cmdSetVrlOff(bool oper = false);
	void cmdSetVrl2(bool oper = false);
	void cmdSetVrlResOff(bool oper = false);
	void cmdSetVrlResOn(bool oper = false);

	void onRafOffFinish();
	void onRafOnFinish();

	void onChangedAzimuthSource(quint32 source);
	void onChangedHour();

	void onControlKvit(AskuBinStateSet kvit);

	void onButtonDrive(quint32 on);
	void onButtonPum(quint32 pum);
	void onButtonPrd(bool on);
	void onButtonPrd1(bool on);
	void onButtonPrd2(bool on);

	void onTimeMeasurePower();

	void onReadyToCheckMode(bool on);

signals:
	void changedMain(bool main);
	void changedRegime(AskuRegime regime);

	void sigConnectedGpr();
	void sigDisconnectedGpr();
	void sigConnectedAvt();
	void sigDisconnectedAvt();
	void sigConnectedPwm();
	void sigDisconnectedPwm();
	void sigConnectedPpv();
	void sigDisconnectedPpv();
	void sigConnectedRmo();
	void sigDisconnectedRmo();
	void sigConnectedSoi();
	void sigDisconnectedSoi();

	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendSyncMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void needRefreshAll();
	void cmdMeasurePower();
	void sigFlushSettings();
	void sigRefreshState();


	void setMonitorModule(quint32 n_prd, quint32 n_module);

	void setResetAvarPrd1();
	void setResetAvarPrd2();
	void setResetAvarPrm();
	void setResetAvarBep();
	void setResetAvarSvo();
	void setResetAvarComm();
	
	void setMainObr1();
	void setMainObr2();

	void setObrResOff();
	void setObrResOn();

	void setAzimuthSource(quint32 source);
	void setOverview(quint32 number);

	void setBepOff();
	void setBepOn();
	void setBep1On();
	void setBep2On();

	void setPrd1Off();
	void setPrd1On();

	void setPrd2Off();
	void setPrd2On();

	void setPumi1();
	void setPumiOff();
	void setPumi2();

//	void setVrl1();
//	void setVrlOff();
//	void setVrl2();
//	void setVrlResOff();
//	void setVrlResOn();
	void setMainVrl(quint32 n_vrl);
	void setReconfVrl(bool on);

	void setHowl1On();
	void setHowl1Off();
	void setHowl2On();
	void setHowl2Off();

	void setSvo1On();
	void setSvo2On();
	void setSvo1Off();
	void setSvo2Off();
};

// ----------------------------------------------------------------------------

#endif //__CONTROL_H__