#ifndef _CANALASKU_H_
#define _CANALASKU_H_

//-------------------------------------------------------------------

#include <QObject>
#include <QList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "canalasku_defines.h"
#include "canalasku_struct.h"
#include "canalasku_thread.h"
#include "canalasku_phase.h"

//-------------------------------------------------------------------

class CanalAsku : public CanalAskuThread
{
	Q_OBJECT

public:
	static QString moduleUmiSerial(quint8 hi, quint8 mi, quint8 lo);
	static bool isAllPrds(int n_prd);
	static bool isExactPrd(int n_prd, int p);
	static bool isAllModules(int n_module);
	static bool isHalf1Modules(int n_module);
	static bool isHalf2Modules(int n_module);
	static bool isHalfModules(int n_module);
	static bool isExactModule(int n_module, int m);
	static bool isHalf1Module(int m);
	static bool isHalf2Module(int m);
	static bool isHalfModule(int n_module, int m);
	static bool isExactPrds(int n_prd);
	static bool isExactModules(int n_module);

protected:
	CanalAskuConfig m_canalAskuConfig;

// --
	QVariantMap getCanalAskuStateLocal();
	void setCanalAskuStateOther(const QVariantMap & state);
// --

// -- CanalAsku Data --
	EUV_1B elk1b;
	EUV_2B elk2b;
	EUV_3B elk3b;
	EUV_4B elk4b;
	EUV_5B elk5b;
	EUV_6B elk6b;
	EUV_7B elk7b;
	EUV_8B elk8b;
	EUV_9B elk9b;
	EUV_10B elk10b;
	EUV_11B elk11b;
	EUV_12B elk12b;
	EUV_13B elk13b;
	EUV_14B elk14b;
	EUV_15B elk15b;
	EUV_16B elk16b;
	EUV_17B elk17b;
	EUV_18B elk18b;
	EUV_19B elk19b;
	EUV_20B_21B elk2021b;
	EUV_22B_23B elk2223b;
	EUV_24B_25B elk2425b;
	EUV_26B_27B elk2627b;
	EUV_28B_29B elk2829b;
	EUV_30B_31B elk3031b;
	EUV_32B_33B elk3233b;
	EUV_34B elk34b;
	EUV_BPU elkBPU;

	PRD_1B prd1b[CA_N_TRANSMITTERS];
	PRD_2B prd2b[CA_N_TRANSMITTERS];
	PRD_3B prd3b[CA_N_TRANSMITTERS];
	PRD_4B prd4b[CA_N_TRANSMITTERS];
	PRD_5B prd5b[CA_N_TRANSMITTERS];
	PRD_6B prd6b[CA_N_TRANSMITTERS];
	PRD_7B prd7b[CA_N_TRANSMITTERS];
	PRD_8B prd8b[CA_N_TRANSMITTERS];
	PRD_9B prd9b[CA_N_TRANSMITTERS];
	PRD_10B prd10b[CA_N_TRANSMITTERS];
	PRD_11B prd11b[CA_N_TRANSMITTERS];
	PRD_12B prd12b[CA_N_TRANSMITTERS];
	PRD_BPU_1B prdBPU1b[CA_N_TRANSMITTERS];
	PRD_BPU_2B prdBPU2b[CA_N_TRANSMITTERS];
	PRD_BPU_3B prdBPU3b[CA_N_TRANSMITTERS];
	PRD_BPU_4B prdBPU4b[CA_N_TRANSMITTERS];
	PRD_BPU_5B prdBPU5b[CA_N_TRANSMITTERS];
	PRD_BPU_6B prdBPU6b[CA_N_TRANSMITTERS];

	PRD_PARAM_UMI paramUMI[CA_N_TRANSMITTERS][CA_N_MODULES_UMI];

// -- commands
	EUV_COMMAND elkCmd;
	PRD_COMMAND prdCmd;

	bool setCommandElk(EUV_COMMAND euvCmd);
	bool setCommandPrd(PRD_COMMAND prdCmd);

	QVariantMap m_commands_prd;
	QVariantMap m_commands_elk;
	QVariantMap m_selectors_prd;

	qint32 prdToInt(QString strPrd);
	qint32 moduleToInt(QString strModule);

// -- phase codes
	AskuPhaseCodes phaseCodes;

	void setPhaseMap(QVariantMap map);

// -- checking modules
	QDateTime m_checkModulesTime[CA_N_TRANSMITTERS];
	qint64 m_checkModules[CA_N_TRANSMITTERS];

	bool isCheckModulesTime(quint32 n_prd);
	void setCheckModules(quint32 n_prd, qint32 state);
	void checkCommandModules();

// -- checking kits
	QDateTime m_checkSvchTime;
	qint64 m_checkSvch;

	bool isCheckSvchTime();
	void setCheckSvch(qint32 state);
	void checkCommandSvch();

// -- misc
	void algChannelAsku(CanalAskuData * data);
	void makeMonitorPhase(CanalAskuData* data);
	void makeDataMaps(CanalAskuData* data);
	void checkFirstCommands(CanalAskuData * data);

// -- ChannelAsku State
	AskuBinStateSet cnl;

public:
	CanalAsku(QObject * parent);
	~CanalAsku();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

protected:
	void makePrdSelectorsMessage(QString moduleTo);
	void makePrdButtonsMessage();
	void makeElkButtonsMessage();

	void startMonitorPhase();
	void stopMonitorPhase();
	void setNeedUpdatePhase();

protected slots:
	void syncToSlave();
	void syncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

	void onReadyData(CanalAskuData* data);

	void refreshPhase();
	void refreshPrdSelectorsPhase();
	void refreshPrdSelectorsCtrlPrd();
	void refreshPrdButtons();
	void refreshElkButtons();

	void loadPhaseFile();
	void savePhaseFile();

public slots:
	void onChangedMain(bool on);

	void onConnectedGpr();
	void onDisconnectedGpr();

	void needSyncToSlave();
	void onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

//Elk Slots
	void putOnErrorANT();
	void putOffErrorANT();
	void putOnErrorRLK();
	void putOffErrorRLK();
	void putResetElk();
	void putOnRpuLight();
	void putOffRpuLight();
	void putOnPerimLight();
	void putOffPerimLight();
	void putOnFire();
	void putOffFire();
	void putOnSafe();
	void putOffSafe();
	void putOnNoCond();
	void putOffNoCond();
	void putOnHowl1();
	void putOffHowl1();
	void putOnHowl2();
	void putOffHowl2();

//Prd Slots
	void slotHotRes(bool on);
	void slotPrdPumi(bool on1, bool on2);
	void slotPrdPower(bool on, int n_prd);
	void slotPrdPower380Module(bool on, int n_prd, int n_module);
	void slotPrdPowerModule(bool on, int n_prd, int n_module);
	void slotPrdSVChModule(bool on, int n_prd, int n_module);
	void slotPrdResetModule(int n_prd, int n_module);
	void slotPrdQueryPhase(int n_prd, int n_module);
	void slotPrdSetPhase(int value, int n_prd, int n_module);
	void putPumi1On();
	void putPumiOff();
	void putPumi2On();
	void slotPrdHrOn();
	void slotPrdHrOff();
	void putSvch1On();
	void putSvchOff();
	void putSvch2On();
	void putPrdOn1();
	void putPrdOff1();
	void putResetPrd1();
	void putPrdOn2();
	void putPrdOff2();
	void putResetPrd2();
	void slotPrdRefresh(int n_prd, int n_module);
	void slotElkRefresh();

	void slotStartPhasing(int n_prd, int n_module, bool avto);
	void slotStopPhasing();

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigDataAsku(AskuSignalSet sigmap, AskuValueSet valmap);
	void sigState(AskuBinStateSet cnl);

	void sigReadyToCheckMode(bool on);

	void sigButtonPum(quint32 pum);
	void sigButtonPrd(bool on);
	void sigButtonPrd1(bool on);
	void sigButtonPrd2(bool on);
//
	void sigPrdHotResState(bool on, bool active);
	void sigPrdPumiState(bool on, bool active);
	void sigPrdPowerState(bool on, bool active);
	void sigPrdSvchState(bool on, bool active);
	void sigPrdModule380State(bool on, bool active);
	void sigPrdModuleState(bool on, bool active);
	void sigPrdSVChState(bool on, bool active);
	void sigPrdPhaseValues(int current, int saved, bool active);
};

//-------------------------------------------------------------------

#endif //_CANALASKU_H_
