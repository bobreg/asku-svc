#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "algorithm.h"
#include "canalasku_data.h"

// ----------------------------------------------------------------------------
AskuAlgorithm::AskuAlgorithm(qint32 numGpr, QObject * parent) : QObject(parent), elements()
{
	m_numGpr = numGpr;
	m_isMain = false;
	m_isWorkGpr = false;
	m_isWorkPpv = false;
	m_isWorkRmo = false;
	m_isWorkSoi = false;
	m_regime = RegInit;

	prepareRgdv();
	prepareMessages();

	resetAvarBep = new AskuAvtoResetAvar(20000, 1000, 3);
	connect(resetAvarBep, SIGNAL(invoke()), this, SIGNAL(cmdSetResetAvarBep()));

	resetAvarSvo = new AskuAvtoResetAvar(20000, 5000, 3);
	connect(resetAvarSvo, SIGNAL(invoke()), this, SIGNAL(cmdSetResetAvarSvo()));

	overheatWarning = new AskuAvtoResetAvar(0, 60000, 1);
	connect(overheatWarning, SIGNAL(invoke()), this, SLOT(showOverheatWarning()));

	overheatCommand = new AskuAvtoResetAvar(0, 300000, 1);
	connect(overheatCommand, SIGNAL(invoke()), this, SLOT(cmdOverheatWarning()));

	m_timerBep = new QTimer(this);
	connect(m_timerBep, SIGNAL(timeout()), this, SLOT(onTimerBep()));

	m_timerProc = new QTimer(this);
	connect(m_timerProc, SIGNAL(timeout()), this, SLOT(onTimerProc()));
}

// ----------------------------------------------------------------------------
AskuAlgorithm::~AskuAlgorithm()
{
	if(resetAvarSvo)
	{
		resetAvarSvo->resetAvar();
		delete resetAvarSvo;
		resetAvarSvo = 0;
	}

	if(resetAvarBep)
	{
		resetAvarBep->resetAvar();
		delete resetAvarBep;
		resetAvarBep = 0;
	}
	if(m_timerBep)
	{
		m_timerBep->stop();
		delete m_timerBep;
		m_timerBep = NULL;
	}

	if(overheatWarning)
	{
		overheatWarning->resetAvar();
		delete overheatWarning;
		overheatWarning = 0;
	}

	if(overheatCommand)
	{
		overheatCommand->resetAvar();
		delete overheatCommand;
		overheatCommand = 0;
	}

	if(m_timerProc)
	{
		m_timerProc->stop();
		delete m_timerProc;
		m_timerProc = NULL;
	}
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::start()
{
	if(m_timerBep)
		m_timerBep->start(1000);
	if(m_timerProc)
		m_timerProc->start(1000);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::stop()
{
	if(m_timerProc)
		m_timerProc->stop();
	if(m_timerBep)
		m_timerBep->stop();
}

// ----------------------------------------------------------------------------
bool AskuAlgorithm::mainGpr()
{
	return m_isMain;
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onChangedMain(bool isMain)
{
	if(isMain != m_isMain)
	{
		m_isMain = isMain;
	}

	if(resetAvarBep)
		resetAvarBep->setMain(isMain);

	if(resetAvarSvo)
		resetAvarSvo->setMain(isMain);

	if(overheatWarning)
		overheatWarning->setMain(isMain);

	if(overheatCommand)
		overheatCommand->setMain(isMain);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onChangedRegime(AskuRegime regime)
{
	if(regime != m_regime)
	{
		m_regime = regime;
	}
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onConnectedGpr()
{
	LogInfo("AskuAlgo: connected gpr");
	m_isWorkGpr = true;
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onDisconnectedGpr()
{
	LogInfo("AskuAlgo: disconnected gpr");
	m_isWorkGpr = false;

	funSvkrOther();
	funPoiCommon();
	funPrmOther();
	fun124PP04_raf();
	fun125PK01();
	funCommonPorl();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onConnectedPpv()
{
	LogInfo("AskuAlgo: connected ppv");
	m_isWorkPpv = true;

	funPpv();
	fun125PK01();
	funCommonPorl();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onDisconnectedPpv()
{
	LogInfo("AskuAlgo: disconnected ppv");
	m_isWorkPpv = false;

	funPpv();
	fun125PK01();
	funCommonPorl();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onConnectedRmo()
{
	LogInfo("AskuAlgo: connected rmo");
	m_isWorkRmo = true;

	funRmo();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onDisconnectedRmo()
{
	LogInfo("AskuAlgo: disconnected rmo");
	m_isWorkRmo = false;

	funRmo();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onConnectedSoi()
{
	LogInfo("AskuAlgo: connected soi");
	m_isWorkSoi = true;

	funSoi();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onDisconnectedSoi()
{
	LogInfo("AskuAlgo: disconnected soi");
	m_isWorkSoi = false;

	funSoi();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onTimerBep()
{
	checkReserveBep();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onTimerProc()
{
	checkReserveProc();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::refreshState()
{
	makeMessageState(true);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::updateElements()
{
	if(elements.isUpdated(m_isMain))
		makeMessageState();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::refreshListRgdv()
{
	if(m_isMain)
	{
		elementsRgdv.makeCommonState();

		ctrlKvit["status_rgdv"] = elementsRgdv.getCommonState();
		emit controlKvit(ctrlKvit);

		makeMessageRgdv(true);
	}
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::updateElementsRgdv()
{
	elementsRgdv.makeCommonState();

	if(m_isMain && elementsRgdv.isUpdated())
	{
		ctrlKvit["status_rgdv"] = elementsRgdv.getCommonState();
		emit controlKvit(ctrlKvit);

		makeMessageRgdv();
	}
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::makeMessageRgdv(bool all)
{
	QVariantMap data;

	data["InfoType"] = "ASKU_RGDV_LIST";
	data["ModuleTo"] = "dialog_listrgdv";
	data["ModuleFrom"] = "algorithm";
	data["Info"] = elementsRgdv.makeList(all);
	data["FullSet"] = all;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::makeMessageState(bool all)
{
	QVariantMap data;

	data["InfoType"] = "ASKU_STATE_SET";
	data["ModuleTo"] = "level";
	data["ModuleFrom"] = "algorithm";
	data["StateSet"] = elements.makeMap(all);
	data["FullSet"] = all;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ----------------------------------------------------------------------------
qint32 AskuAlgorithm::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("Algorithm: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogError("Algorithm: empty command");
		return result;
	}

	LogInfo("Command: %s", qPrintable(command));

	if(command == "refreshState")
	{
		QTimer::singleShot(0, this, SLOT(refreshState()));
		result = AskuModule::CommandSuccess;
	}
	if(command == "refreshListRgdv")
	{
		QTimer::singleShot(0, this, SLOT(refreshListRgdv()));
		result = AskuModule::CommandSuccess;
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

	emit sendControlAnswer(answer, idAskuModuleGui);

	return result;
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateCanalAsku(AskuBinStateSet state)
{
	canalAsku = state;
//	qDebug() << canalAsku.dump();

	funCommunicators();

	elements["rs485_asku@comm1"] = canalAsku["Comm1"].toString();
	elements["rs485_asku@comm2"] = canalAsku["Comm2"].toString();
	elements["rs485_asku@port1"] = canalAsku["Port1"].toString();
	elements["rs485_asku@port2"] = canalAsku["Port2"].toString();
	elements["rs485_asku@oy1"] = canalAsku["OY1"].toString();
	elements["rs485_asku@oy2"] = canalAsku["OY2"].toString();
	elements["rs485_asku@oy3"] = canalAsku["OY3"].toString();
	elements["rs485_asku@line1"] = canalAsku["EL1"].toString();
	elements["rs485_asku@line2"] = canalAsku["EL2"].toString();
	elements["rs485_asku@line3"] = canalAsku["EL3"].toString();
	elements["rs485_asku@line4"] = canalAsku["EL4"].toString();
	elements["rs485_asku@line5"] = canalAsku["EL5"].toString();
	elements["base@rs485_asku"] = canalAsku["ObSost"].toString();

	updateElements();
	updateElementsRgdv();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStatePwm(AskuBinStateSet state, AskuValueSet values)
{
	Q_UNUSED(values);

	pwm = state;

//	elements["obr_base@ppv"] = pwm["connected"];
	elements["prdsys@powermeter"] = pwm["ObSost"];
	elements["zal@powermeter"] = pwm["ObSost"];
	elements["prdsys@powervalue"] = pwm["power"];

	messages["prdsys@powermeter"] = pwm["power"];
	messages["prdsys@power"] = pwm["power"];

	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateLocalDasd(AskuBinStateSet state, AskuValueSet values)
{
	localDasd = state;
	valLocalPeriod = values;

//	qDebug() << localDasd.dump();
//	qDebug() << valLocalPeriod.dump();

	funSvkrLocal();
	fun125PK01();
	fun124PP04_raf();
	funPrmLocal();
	funAntenna();
	funCommonPorl();
	checkResetPrm();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateOtherDasd(AskuBinStateSet state, AskuValueSet values)
{
	otherDasd = state;
	valOtherPeriod = values;
//	qDebug() << otherDasd.dump();
//	qDebug() << valOtherPeriod.dump();

	funSvkrOther();
	fun125PK01();
	fun124PP04_raf();
	funPrmOther();
	funAntenna();
	funCommonPorl();
	checkResetPrm();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateLocalVoi(AskuBinStateSet state)
{
	localVoi = state;
//	qDebug() << localVoi.dump();

	funSvkrLocal();
	fun125PK01();
	funMpsn();
	funCommonPorl();

	QString NVOI = QString("voi%1").arg(IDGPR() + 1);
	QString NVOIA = NVOI + QString("@");
	QString NVMVOI = QString("obr_svkr%1@voi").arg(IDGPR() + 1);

	elements[NVOI + "@error"]   = localVoi["ObSost"].toString();
	elements[NVOI + "@prl"]     = localVoi["VoiDataPrl"].toString();
	elements[NVOI + "@vrl"]     = localVoi["VoiDataVrl"].toString();
	elements[NVOI + "@nrz"]     = localVoi["VoiDataNrz"].toString();
	elements[NVOI + "@azn"]     = localVoi["VoiDataAzn"].toString();
	elements[NVOI + "@driver"]  = localVoi["ModuleDriver"].toString();
	elements[NVOI + "@d2vk028"]    = localVoi["ModuleFailure"].toString();
	elements[NVOI + "@time"]    = localVoi["ModuleTimeInvalid"].toString();
	elements[NVOI + "@ust"]     = localVoi["VoiUstError"].toString();
	elements[NVOI + "@timeazn"] = localVoi["VoiTimeAznError"].toString();
	elements[NVOI + "@nord"]    = localVoi["VoiNoNord"].toString();
	elements[NVOI + "@mai"]     = localVoi["VoiNoMai"].toString();

	elements[NVMVOI] = localVoi["ObSost"].toString();
	elements[NVMVOI].setUser(localVoi["ObSost"] != ELEM_NOT ? (localVoi["VoiStatus"] == ELEM_NORMA ? "master" : "slave") : "");

	messages[NVOIA + "data_prl"]     = localVoi["VoiDataPrl"];
	messages[NVOIA + "data_vrl"]     = localVoi["VoiDataVrl"];
	messages[NVOIA + "data_nrz"]     = localVoi["VoiDataNrz"];
	messages[NVOIA + "data_azn"]     = localVoi["VoiDataAzn"];
	messages[NVOIA + "driver"]       = localVoi["ModuleDriver"];
	messages[NVOIA + "failure"]      = localVoi["ModuleFailure"];
	messages[NVOIA + "invalid_time"] = localVoi["ModuleTimeInvalid"];
	messages[NVOIA + "nord"]         = localVoi["VoiNoNord"];
	messages[NVOIA + "mai"]          = localVoi["VoiNoMai"];
	messages[NVOIA + "ust"]          = localVoi["VoiUstError"];
	messages[NVOIA + "timeazn"]      = localVoi["VoiTimeAznError"];
	messages[NVOIA + "disable"]      = localVoi["DisableSVCH"];
	messages[NVOIA + "sost"]         = localVoi["ObSost"];

	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateOtherVoi(AskuBinStateSet state)
{
	otherVoi = state;

//	qDebug() << "VOI_OTHER_STATE\n";
//	qDebug() << otherVoi.dump();
//	qDebug() << "---------------\n";

	funSvkrOther();
	fun125PK01();
	funCommonPorl();

	QString NVOI = QString("voi%1").arg(OTHER_GPR_ID() + 1);
	QString NVOIA = NVOI + QString("@");
	QString NVMVOI = QString("obr_svkr%1@voi").arg(OTHER_GPR_ID() + 1);

	elements[NVOI + "@error"]   = otherVoi["ObSost"].toString();
	elements[NVOI + "@prl"]     = otherVoi["VoiDataPrl"].toString();
	elements[NVOI + "@vrl"]     = otherVoi["VoiDataVrl"].toString();
	elements[NVOI + "@nrz"]     = otherVoi["VoiDataNrz"].toString();
	elements[NVOI + "@azn"]     = otherVoi["VoiDataAzn"].toString();
	elements[NVOI + "@driver"]  = otherVoi["ModuleDriver"].toString();
	elements[NVOI + "@d2vk028"]    = otherVoi["ModuleFailure"].toString();
	elements[NVOI + "@time"]    = otherVoi["ModuleTimeInvalid"].toString();
	elements[NVOI + "@ust"]     = otherVoi["VoiUstError"].toString();
	elements[NVOI + "@timeazn"] = otherVoi["VoiTimeAznError"].toString();
	elements[NVOI + "@nord"]    = otherVoi["VoiNoNord"].toString();
	elements[NVOI + "@mai"]     = otherVoi["VoiNoMai"].toString();

	elements[NVMVOI] = otherVoi["ObSost"].toString();
	elements[NVMVOI].setUser(otherVoi["ObSost"] != ELEM_NOT ? (otherVoi["VoiStatus"] == ELEM_NORMA ? "master" : "slave") : "");

	messages[NVOIA + "data_prl"]     = otherVoi["VoiDataPrl"];
	messages[NVOIA + "data_vrl"]     = otherVoi["VoiDataVrl"];
	messages[NVOIA + "data_nrz"]     = otherVoi["VoiDataNrz"];
	messages[NVOIA + "data_azn"]     = otherVoi["VoiDataAzn"];
	messages[NVOIA + "driver"]       = otherVoi["ModuleDriver"];
	messages[NVOIA + "failure"]      = otherVoi["ModuleFailure"];
	messages[NVOIA + "invalid_time"] = otherVoi["ModuleTimeInvalid"];
	messages[NVOIA + "nord"]         = otherVoi["VoiNoNord"];
	messages[NVOIA + "mai"]          = otherVoi["VoiNoMai"];
	messages[NVOIA + "ust"]          = otherVoi["VoiUstError"];
	messages[NVOIA + "timeazn"]      = otherVoi["VoiTimeAznError"];
	messages[NVOIA + "disable"]      = otherVoi["DisableSVCH"];
	messages[NVOIA + "sost"]         = otherVoi["ObSost"];

	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateLocalPoi(AskuBinStateSet state)
{
	localPoi = state;
//	qDebug() << localPoi.dump();

	funSvkrLocal();
	funPoiCommon();
	fun124PP04_raf();
	fun125PK01();
	funCommonPorl();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateOtherPoi(AskuBinStateSet state)
{
	otherPoi = state;
//	qDebug() << otherPoi.dump();

	funSvkrOther();
	funPoiCommon();
	fun124PP04_raf();
	fun125PK01();
	funCommonPorl();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onKoeffLocalPoi(AskuValueSet koeff)
{
	valLocalPoiKoeff = koeff;
	qDebug() << "localKoeff:" << valLocalPoiKoeff.dump();

	funPoiKoeffLocal();
	funPoiCommon();
	fun124PP04_raf();
	fun125PK01();
	funCommonPorl();
	checkResetPrm();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onKoeffOtherPoi(AskuValueSet koeff)
{
	valOtherPoiKoeff = koeff;
	qDebug() << "otherKoeff" << valOtherPoiKoeff.dump();

	funPoiKoeffOther();
	funPoiCommon();
	fun124PP04_raf();
	fun125PK01();
	funCommonPorl();
	checkResetPrm();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onPilotLocalPoi(AskuValueSet state)
{
	valLocalPoiPilot = state;
	qDebug() << "localPilot" << valLocalPoiPilot.dump();

	funPoiPilotLocal();
	funPoiCommon();
	fun124PP04_raf();
	fun125PK01();
	funCommonPorl();
	checkResetPrm();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onPilotOtherPoi(AskuValueSet state)
{
	valOtherPoiPilot = state;
	qDebug() << "otherPilot" << valOtherPoiPilot.dump();

	funPoiPilotOther();
	funPoiCommon();
	fun124PP04_raf();
	fun125PK01();
	funCommonPorl();
	checkResetPrm();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onTransmitterLocalPoi(AskuValueSet state)
{
	Q_UNUSED(state);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onTransmitterOtherPoi(AskuValueSet state)
{
	Q_UNUSED(state);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::checkResetDrive()
{
	bool avar1 = (drives["drive1@Fail"] == ELEM_AVAR || drives["drive1@Warning"] == ELEM_AVAR) && (drives["drive1@mest"] != ELEM_MEST);
	bool avar2 = (drives["drive2@Fail"] == ELEM_AVAR || drives["drive2@Warning"] == ELEM_AVAR) && (drives["drive2@mest"] != ELEM_MEST);

	if(resetAvarBep)
		resetAvarBep->setAvar(avar1 || avar2);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::checkResetCoolers()
{
	bool avar1 = (coolers["vesper1@Fail"] == ELEM_AVAR || coolers["vesper2@Fail"] == ELEM_AVAR);
	bool avar2 = (coolers["vesper3@Fail"] == ELEM_AVAR || coolers["vesper4@Fail"] == ELEM_AVAR);

	if(resetAvarSvo)
		resetAvarSvo->setAvar(avar1 || avar2);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::checkResetPrm()
{
	
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::checkResetPrd()
{
	
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateDrive(AskuBinStateSet state)
{
	drives = state;

//	qDebug() << "STATE_DRIVE";
//	qDebug() << state.dump();
//	qDebug() << "-----------";

	funCommunicators();
	fun124YY03_raf();
	fun125YY03_raf();
	funAntenna();
	funCommonPorl();
	checkResetDrive();

	if(m_isMain)
	{
		elements["rs485_drive@comm1"] = drives["comm1"].toString();
		elements["rs485_drive@comm2"] = drives["comm2"].toString();
		elements["rs485_drive@port1"] = drives["port1"].toString();
		elements["rs485_drive@port2"] = drives["port2"].toString();
		elements["rs485_drive@device1"] = drives["device1"].toString();
		elements["rs485_drive@device2"] = drives["device2"].toString();
		elements["rs485_drive@line1"] = drives["line1"].toString();
		elements["rs485_drive@line2"] = drives["line2"].toString();
		elements["rs485_drive@line3"] = drives["line3"].toString();
		elements["rs485_drive@line4"] = drives["line4"].toString();
		elements["base@rs485_drive"] = drives["channel"].toString();

		messages["drive1@ready"]    = drives["drive1@Ready"];
		messages["drive1@warning"]  = drives["drive1@Warning"];
		messages["drive1@fail"]     = drives["drive1@Fail"];
		messages["drive1@working"]  = drives["drive1@WorkingAlg"];
		messages["drive1@invertor"] = drives["drive1@INVERTOR"];
		messages["drive1@power"]    = drives["drive1@PowerReady"];
		messages["drive1@sensor"]   = drives["drive1@SensorInc"];
		messages["drive1@main"]     = drives["drive1@Main"];

		messages["drive2@ready"]    = drives["drive2@Ready"];
		messages["drive2@warning"]  = drives["drive2@Warning"];
		messages["drive2@fail"]     = drives["drive2@Fail"];
		messages["drive2@working"]  = drives["drive2@WorkingAlg"];
		messages["drive2@invertor"] = drives["drive2@INVERTOR"];
		messages["drive2@power"]    = drives["drive2@PowerReady"];
		messages["drive2@sensor"]   = drives["drive2@SensorInc"];
		messages["drive2@main"]     = drives["drive2@Main"];

		elements["vector@ready1"] = drives["drive1@Ready"].toString() + drives["drive1@mest"].toStringMest();
		elements["vector@warning1"] = drives["drive1@Warning"].toString() + drives["drive1@mest"].toStringMest();
		elements["vector@fail1"] = drives["drive1@Fail"].toString() + drives["drive1@mest"].toStringMest();
		elements["vector@working1"] = drives["drive1@WorkingAlg"].toString() + drives["drive1@mest"].toStringMest();
		elements["vector@invertor1"] = drives["drive1@INVERTOR"].toString() + drives["drive1@mest"].toStringMest();
		elements["vector@power1"] = drives["drive1@PowerReady"].toString() + drives["drive1@mest"].toStringMest();
		elements["vector@sensor1"] = drives["drive1@SensorInc"].toString() + drives["drive1@mest"].toStringMest();
		elements["vector@main1"] = drives["drive1@Main"].toString() + drives["drive1@mest"].toStringMest();

		elements["vector@ready2"] = drives["drive2@Ready"].toString() + drives["drive2@mest"].toStringMest();
		elements["vector@warning2"] = drives["drive2@Warning"].toString() + drives["drive2@mest"].toStringMest();
		elements["vector@fail2"] = drives["drive2@Fail"].toString() + drives["drive2@mest"].toStringMest();
		elements["vector@working2"] = drives["drive2@WorkingAlg"].toString() + drives["drive2@mest"].toStringMest();
		elements["vector@invertor2"] = drives["drive2@INVERTOR"].toString() + drives["drive2@mest"].toStringMest();
		elements["vector@power2"] = drives["drive2@PowerReady"].toString() + drives["drive2@mest"].toStringMest();
		elements["vector@sensor2"] = drives["drive2@SensorInc"].toString() + drives["drive2@mest"].toStringMest();
		elements["vector@main2"] = drives["drive2@Main"].toString() + drives["drive2@mest"].toStringMest();
	}

	updateElements();

	ctrlKvit["drive1_on"] = drives["drive1@INVERTOR"];
	ctrlKvit["drive2_on"] = drives["drive2@INVERTOR"];

	if(drives["drive1@INVERTOR"] == ELEM_NORMA || drives["drive2@INVERTOR"] == ELEM_NORMA)
		ctrlKvit["drive_on"] = ELEM_NORMA;
	else
		ctrlKvit["drive_on"] = ELEM_NOT;

	emit controlKvit(ctrlKvit);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateCoolers(AskuBinStateSet state)
{
	coolers = state;

	funCommunicators();
	fun125YY04_raf();
	funPrdSys_raf();
	funCommonPorl();
	checkResetCoolers();

	elements["rs485_svo@comm1"] = coolers["comm1"].toString();
	elements["rs485_svo@comm2"] = coolers["comm2"].toString();
	elements["rs485_svo@port1"] = coolers["port1"].toString();
	elements["rs485_svo@port2"] = coolers["port2"].toString();
	elements["rs485_svo@device1"] = coolers["device1"].toString();
	elements["rs485_svo@device2"] = coolers["device2"].toString();
	elements["rs485_svo@device3"] = coolers["device3"].toString();
	elements["rs485_svo@device4"] = coolers["device4"].toString();
	elements["rs485_svo@line1"] = coolers["line1"].toString();
	elements["rs485_svo@line2"] = coolers["line2"].toString();
	elements["rs485_svo@line3"] = coolers["line3"].toString();
	elements["rs485_svo@line4"] = coolers["line4"].toString();
	elements["base@rs485_svo"] = coolers["channel"].toString();

	elements["rs485_svo@vent1"] = coolers["vesper1@Ventilator"].toString();
	elements["rs485_svo@vent2"] = coolers["vesper2@Ventilator"].toString();
	elements["rs485_svo@vent3"] = coolers["vesper1@Ventilator"].toString();
	elements["rs485_svo@vent4"] = coolers["vesper2@Ventilator"].toString();
	elements["rs485_svo@vent5"] = coolers["vesper3@Ventilator"].toString();
	elements["rs485_svo@vent6"] = coolers["vesper4@Ventilator"].toString();
	elements["rs485_svo@vent7"] = coolers["vesper3@Ventilator"].toString();
	elements["rs485_svo@vent8"] = coolers["vesper4@Ventilator"].toString();

	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateUps(AskuBinStateSet state, AskuValueSet values)
{
	ups = state;
	valUps = values;

//	qDebug() << "----";
//	qDebug() << ups.dump();
//	qDebug() << valUps.dump();
//	qDebug() << "----";

	elements["base@ups1"] = ups["ups1@ObSost"].toString();
	elements["base@ups2"] = ups["ups2@ObSost"].toString();
	elements["zal@ups1"] = ups["ups1@ObSost"].toString();
	elements["zal@ups2"] = ups["ups2@ObSost"].toString();

	messages["ups1@ups_off"]    = ups["ups1@STATUS_UPS_OFF"];
	messages["ups1@bypass"]     = ups["ups1@STATUS_BYPASS"];
	messages["ups1@on_battery"] = ups["ups1@STATUS_ON_BATTERY"];
	messages["ups1@ups_normal"] = ups["ups1@STATUS_NORMAL"];

	messages["ups2@ups_off"]    = ups["ups2@STATUS_UPS_OFF"];
	messages["ups2@bypass"]     = ups["ups2@STATUS_BYPASS"];
	messages["ups2@on_battery"] = ups["ups2@STATUS_ON_BATTERY"];
	messages["ups2@ups_normal"] = ups["ups2@STATUS_NORMAL"];

//UPS1
// Common
	elements["ups1@upsBasicIdentModel"] = ups["ups1@upsBasicIdentModel"].toString();
	elements["ups1@upsBasicIdentModel"].setText(valUps["ups1@upsBasicIdentModel"].toString());

	elements["ups1@upsAdvIdentFirmwareRevision"] = ups["ups1@upsAdvIdentFirmwareRevision"].toString();
	elements["ups1@upsAdvIdentFirmwareRevision"].setText(valUps["ups1@upsAdvIdentFirmwareRevision"].toString());

	elements["ups1@upsAdvIdentSerialNumber"] = ups["ups1@upsAdvIdentSerialNumber"].toString();
	elements["ups1@upsAdvIdentSerialNumber"].setText(valUps["ups1@upsAdvIdentSerialNumber"].toString());

	elements["ups1@upsBasicOutputStatus"] = ups["ups1@upsBasicOutputStatus"].toString();
	elements["ups1@upsBasicOutputStatus"].setText(valUps["ups1@upsBasicOutputStatus"].toString());

	elements["ups1@upsAdvInputLineFailCause"] = ups["ups1@upsAdvInputLineFailCause"].toString();
	elements["ups1@upsAdvInputLineFailCause"].setText(valUps["ups1@upsAdvInputLineFailCause"].toString());

	elements["ups1@upsBasicStateOutputState"] = ups["ups1@upsBasicStateOutputState"].toString();
	elements["ups1@upsBasicStateOutputState"].setText(valUps["ups1@upsBasicStateOutputState"].toString());

// Battery
	elements["ups1@upsBasicBatteryStatus"] = ups["ups1@upsBasicBatteryStatus"].toString();
	elements["ups1@upsBasicBatteryStatus"].setText(valUps["ups1@upsBasicBatteryStatus"].toString());

	elements["ups1@upsAdvBatteryCapacity"] = ups["ups1@upsAdvBatteryCapacity"].toString();
	elements["ups1@upsAdvBatteryCapacity"].setText(valUps["ups1@upsAdvBatteryCapacity"].toString());

	elements["ups1@upsAdvBatteryActualVoltage"] = ups["ups1@upsAdvBatteryActualVoltage"].toString();
	elements["ups1@upsAdvBatteryActualVoltage"].setText(valUps["ups1@upsAdvBatteryActualVoltage"].toString());

	elements["ups1@upsAdvBatteryCurrent"] = ups["ups1@upsAdvBatteryCurrent"].toString();
	elements["ups1@upsAdvBatteryCurrent"].setText(valUps["ups1@upsAdvBatteryCurrent"].toString());

	elements["ups1@upsAdvBatteryRunTimeRemaining"] = ups["ups1@upsAdvBatteryRunTimeRemaining"].toString();
	elements["ups1@upsAdvBatteryRunTimeRemaining"].setText(valUps["ups1@upsAdvBatteryRunTimeRemaining"].toString());

	elements["ups1@upsAdvTestDiagnosticsResults"] = ups["ups1@upsAdvTestDiagnosticsResults"].toString();
	elements["ups1@upsAdvTestDiagnosticsResults"].setText(valUps["ups1@upsAdvTestDiagnosticsResults"].toString());

	elements["ups1@upsAdvBatteryTemperature"] = ups["ups1@upsAdvBatteryTemperature"].toString();
	elements["ups1@upsAdvBatteryTemperature"].setText(valUps["ups1@upsAdvBatteryTemperature"].toString());

	elements["ups1@upsAdvBatteryReplaceIndicator"] = ups["ups1@upsAdvBatteryReplaceIndicator"].toString();
	elements["ups1@upsAdvBatteryReplaceIndicator"].setText(valUps["ups1@upsAdvBatteryReplaceIndicator"].toString());

// Input
	elements["ups1@upsPhaseInputVoltage1_1"] = ups["ups1@upsPhaseInputVoltage1_1"].toString();
	elements["ups1@upsPhaseInputVoltage1_1"].setText(valUps["ups1@upsPhaseInputVoltage1_1"].toString());

	elements["ups1@upsPhaseInputVoltage1_2"] = ups["ups1@upsPhaseInputVoltage1_2"].toString();
	elements["ups1@upsPhaseInputVoltage1_2"].setText(valUps["ups1@upsPhaseInputVoltage1_2"].toString());

	elements["ups1@upsPhaseInputVoltage1_3"] = ups["ups1@upsPhaseInputVoltage1_3"].toString();
	elements["ups1@upsPhaseInputVoltage1_3"].setText(valUps["ups1@upsPhaseInputVoltage1_3"].toString());

	elements["ups1@upsPhaseInputCurrent1_1"] = ups["ups1@upsPhaseInputCurrent1_1"].toString();
	elements["ups1@upsPhaseInputCurrent1_1"].setText(valUps["ups1@upsPhaseInputCurrent1_1"].toString());

	elements["ups1@upsPhaseInputCurrent1_2"] = ups["ups1@upsPhaseInputCurrent1_2"].toString();
	elements["ups1@upsPhaseInputCurrent1_2"].setText(valUps["ups1@upsPhaseInputCurrent1_2"].toString());

	elements["ups1@upsPhaseInputCurrent1_3"] = ups["ups1@upsPhaseInputCurrent1_3"].toString();
	elements["ups1@upsPhaseInputCurrent1_3"].setText(valUps["ups1@upsPhaseInputCurrent1_3"].toString());

	elements["ups1@upsAdvInputFrequency"] = ups["ups1@upsAdvInputFrequency"].toString();
	elements["ups1@upsAdvInputFrequency"].setText(valUps["ups1@upsAdvInputFrequency"].toString());

// Bypass
	elements["ups1@upsPhaseInputVoltage2_1"] = ups["ups1@upsPhaseInputVoltage2_1"].toString();
	elements["ups1@upsPhaseInputVoltage2_1"].setText(valUps["ups1@upsPhaseInputVoltage2_1"].toString());

	elements["ups1@upsPhaseInputVoltage2_2"] = ups["ups1@upsPhaseInputVoltage2_2"].toString();
	elements["ups1@upsPhaseInputVoltage2_2"].setText(valUps["ups1@upsPhaseInputVoltage2_2"].toString());

	elements["ups1@upsPhaseInputVoltage2_3"] = ups["ups1@upsPhaseInputVoltage2_3"].toString();
	elements["ups1@upsPhaseInputVoltage2_3"].setText(valUps["ups1@upsPhaseInputVoltage2_3"].toString());

// Output
	elements["ups1@upsPhaseOutputCurrent_1"] = ups["ups1@upsPhaseOutputCurrent_1"].toString();
	elements["ups1@upsPhaseOutputCurrent_1"].setText(valUps["ups1@upsPhaseOutputCurrent_1"].toString());

	elements["ups1@upsPhaseOutputCurrent_2"] = ups["ups1@upsPhaseOutputCurrent_2"].toString();
	elements["ups1@upsPhaseOutputCurrent_2"].setText(valUps["ups1@upsPhaseOutputCurrent_2"].toString());

	elements["ups1@upsPhaseOutputCurrent_3"] = ups["ups1@upsPhaseOutputCurrent_3"].toString();
	elements["ups1@upsPhaseOutputCurrent_3"].setText(valUps["ups1@upsPhaseOutputCurrent_3"].toString());

	elements["ups1@upsPhaseOutputVoltage_1"] = ups["ups1@upsPhaseOutputVoltage_1"].toString();
	elements["ups1@upsPhaseOutputVoltage_1"].setText(valUps["ups1@upsPhaseOutputVoltage_1"].toString());

	elements["ups1@upsPhaseOutputVoltage_2"] = ups["ups1@upsPhaseOutputVoltage_2"].toString();
	elements["ups1@upsPhaseOutputVoltage_2"].setText(valUps["ups1@upsPhaseOutputVoltage_2"].toString());

	elements["ups1@upsPhaseOutputVoltage_3"] = ups["ups1@upsPhaseOutputVoltage_3"].toString();
	elements["ups1@upsPhaseOutputVoltage_3"].setText(valUps["ups1@upsPhaseOutputVoltage_3"].toString());

	elements["ups1@upsAdvOutputFrequency"] = ups["ups1@upsAdvOutputFrequency"].toString();
	elements["ups1@upsAdvOutputFrequency"].setText(valUps["ups1@upsAdvOutputFrequency"].toString());

	elements["ups1@upsAdvOutputLoad"] = ups["ups1@upsAdvOutputLoad"].toString();
	elements["ups1@upsAdvOutputLoad"].setText(valUps["ups1@upsAdvOutputLoad"].toString());

	elements["ups1@upsPhaseOutputPercentLoad_1"] = ups["ups1@upsPhaseOutputPercentLoad_1"].toString();
	elements["ups1@upsPhaseOutputPercentLoad_1"].setText(valUps["ups1@upsPhaseOutputPercentLoad_1"].toString());

	elements["ups1@upsPhaseOutputPercentLoad_2"] = ups["ups1@upsPhaseOutputPercentLoad_2"].toString();
	elements["ups1@upsPhaseOutputPercentLoad_2"].setText(valUps["ups1@upsPhaseOutputPercentLoad_2"].toString());

	elements["ups1@upsPhaseOutputPercentLoad_3"] = ups["ups1@upsPhaseOutputPercentLoad_3"].toString();
	elements["ups1@upsPhaseOutputPercentLoad_3"].setText(valUps["ups1@upsPhaseOutputPercentLoad_3"].toString());

//UPS2
// Common
	elements["ups2@upsBasicIdentModel"] = ups["ups2@upsBasicIdentModel"].toString();
	elements["ups2@upsBasicIdentModel"].setText(valUps["ups2@upsBasicIdentModel"].toString());

	elements["ups2@upsAdvIdentFirmwareRevision"] = ups["ups2@upsAdvIdentFirmwareRevision"].toString();
	elements["ups2@upsAdvIdentFirmwareRevision"].setText(valUps["ups2@upsAdvIdentFirmwareRevision"].toString());

	elements["ups2@upsAdvIdentSerialNumber"] = ups["ups2@upsAdvIdentSerialNumber"].toString();
	elements["ups2@upsAdvIdentSerialNumber"].setText(valUps["ups2@upsAdvIdentSerialNumber"].toString());

	elements["ups2@upsBasicOutputStatus"] = ups["ups2@upsBasicOutputStatus"].toString();
	elements["ups2@upsBasicOutputStatus"].setText(valUps["ups2@upsBasicOutputStatus"].toString());

	elements["ups2@upsAdvInputLineFailCause"] = ups["ups2@upsAdvInputLineFailCause"].toString();
	elements["ups2@upsAdvInputLineFailCause"].setText(valUps["ups2@upsAdvInputLineFailCause"].toString());

	elements["ups2@upsBasicStateOutputState"] = ups["ups2@upsBasicStateOutputState"].toString();
	elements["ups2@upsBasicStateOutputState"].setText(valUps["ups2@upsBasicStateOutputState"].toString());

// Battery
	elements["ups2@upsBasicBatteryStatus"] = ups["ups2@upsBasicBatteryStatus"].toString();
	elements["ups2@upsBasicBatteryStatus"].setText(valUps["ups2@upsBasicBatteryStatus"].toString());

	elements["ups2@upsAdvBatteryCapacity"] = ups["ups2@upsAdvBatteryCapacity"].toString();
	elements["ups2@upsAdvBatteryCapacity"].setText(valUps["ups2@upsAdvBatteryCapacity"].toString());

	elements["ups2@upsAdvBatteryActualVoltage"] = ups["ups2@upsAdvBatteryActualVoltage"].toString();
	elements["ups2@upsAdvBatteryActualVoltage"].setText(valUps["ups2@upsAdvBatteryActualVoltage"].toString());

	elements["ups2@upsAdvBatteryCurrent"] = ups["ups2@upsAdvBatteryCurrent"].toString();
	elements["ups2@upsAdvBatteryCurrent"].setText(valUps["ups2@upsAdvBatteryCurrent"].toString());

	elements["ups2@upsAdvBatteryRunTimeRemaining"] = ups["ups2@upsAdvBatteryRunTimeRemaining"].toString();
	elements["ups2@upsAdvBatteryRunTimeRemaining"].setText(valUps["ups2@upsAdvBatteryRunTimeRemaining"].toString());

	elements["ups2@upsAdvTestDiagnosticsResults"] = ups["ups2@upsAdvTestDiagnosticsResults"].toString();
	elements["ups2@upsAdvTestDiagnosticsResults"].setText(valUps["ups2@upsAdvTestDiagnosticsResults"].toString());

	elements["ups2@upsAdvBatteryTemperature"] = ups["ups2@upsAdvBatteryTemperature"].toString();
	elements["ups2@upsAdvBatteryTemperature"].setText(valUps["ups2@upsAdvBatteryTemperature"].toString());

	elements["ups2@upsAdvBatteryReplaceIndicator"] = ups["ups2@upsAdvBatteryReplaceIndicator"].toString();
	elements["ups2@upsAdvBatteryReplaceIndicator"].setText(valUps["ups2@upsAdvBatteryReplaceIndicator"].toString());

// Input
	elements["ups2@upsPhaseInputVoltage1_1"] = ups["ups2@upsPhaseInputVoltage1_1"].toString();
	elements["ups2@upsPhaseInputVoltage1_1"].setText(valUps["ups2@upsPhaseInputVoltage1_1"].toString());

	elements["ups2@upsPhaseInputVoltage1_2"] = ups["ups2@upsPhaseInputVoltage1_2"].toString();
	elements["ups2@upsPhaseInputVoltage1_2"].setText(valUps["ups2@upsPhaseInputVoltage1_2"].toString());

	elements["ups2@upsPhaseInputVoltage1_3"] = ups["ups2@upsPhaseInputVoltage1_3"].toString();
	elements["ups2@upsPhaseInputVoltage1_3"].setText(valUps["ups2@upsPhaseInputVoltage1_3"].toString());

	elements["ups2@upsPhaseInputCurrent1_1"] = ups["ups2@upsPhaseInputCurrent1_1"].toString();
	elements["ups2@upsPhaseInputCurrent1_1"].setText(valUps["ups2@upsPhaseInputCurrent1_1"].toString());

	elements["ups2@upsPhaseInputCurrent1_2"] = ups["ups2@upsPhaseInputCurrent1_2"].toString();
	elements["ups2@upsPhaseInputCurrent1_2"].setText(valUps["ups2@upsPhaseInputCurrent1_2"].toString());

	elements["ups2@upsPhaseInputCurrent1_3"] = ups["ups2@upsPhaseInputCurrent1_3"].toString();
	elements["ups2@upsPhaseInputCurrent1_3"].setText(valUps["ups2@upsPhaseInputCurrent1_3"].toString());

	elements["ups2@upsAdvInputFrequency"] = ups["ups2@upsAdvInputFrequency"].toString();
	elements["ups2@upsAdvInputFrequency"].setText(valUps["ups2@upsAdvInputFrequency"].toString());

// Bypass
	elements["ups2@upsPhaseInputVoltage2_1"] = ups["ups2@upsPhaseInputVoltage2_1"].toString();
	elements["ups2@upsPhaseInputVoltage2_1"].setText(valUps["ups2@upsPhaseInputVoltage2_1"].toString());

	elements["ups2@upsPhaseInputVoltage2_2"] = ups["ups2@upsPhaseInputVoltage2_2"].toString();
	elements["ups2@upsPhaseInputVoltage2_2"].setText(valUps["ups2@upsPhaseInputVoltage2_2"].toString());

	elements["ups2@upsPhaseInputVoltage2_3"] = ups["ups2@upsPhaseInputVoltage2_3"].toString();
	elements["ups2@upsPhaseInputVoltage2_3"].setText(valUps["ups2@upsPhaseInputVoltage2_3"].toString());

// Output
	elements["ups2@upsPhaseOutputCurrent_1"] = ups["ups2@upsPhaseOutputCurrent_1"].toString();
	elements["ups2@upsPhaseOutputCurrent_1"].setText(valUps["ups2@upsPhaseOutputCurrent_1"].toString());

	elements["ups2@upsPhaseOutputCurrent_2"] = ups["ups2@upsPhaseOutputCurrent_2"].toString();
	elements["ups2@upsPhaseOutputCurrent_2"].setText(valUps["ups2@upsPhaseOutputCurrent_2"].toString());

	elements["ups2@upsPhaseOutputCurrent_3"] = ups["ups2@upsPhaseOutputCurrent_3"].toString();
	elements["ups2@upsPhaseOutputCurrent_3"].setText(valUps["ups2@upsPhaseOutputCurrent_3"].toString());

	elements["ups2@upsPhaseOutputVoltage_1"] = ups["ups2@upsPhaseOutputVoltage_1"].toString();
	elements["ups2@upsPhaseOutputVoltage_1"].setText(valUps["ups2@upsPhaseOutputVoltage_1"].toString());

	elements["ups2@upsPhaseOutputVoltage_2"] = ups["ups2@upsPhaseOutputVoltage_2"].toString();
	elements["ups2@upsPhaseOutputVoltage_2"].setText(valUps["ups2@upsPhaseOutputVoltage_2"].toString());

	elements["ups2@upsPhaseOutputVoltage_3"] = ups["ups2@upsPhaseOutputVoltage_3"].toString();
	elements["ups2@upsPhaseOutputVoltage_3"].setText(valUps["ups2@upsPhaseOutputVoltage_3"].toString());

	elements["ups2@upsAdvOutputFrequency"] = ups["ups2@upsAdvOutputFrequency"].toString();
	elements["ups2@upsAdvOutputFrequency"].setText(valUps["ups2@upsAdvOutputFrequency"].toString());

	elements["ups2@upsAdvOutputLoad"] = ups["ups2@upsAdvOutputLoad"].toString();
	elements["ups2@upsAdvOutputLoad"].setText(valUps["ups2@upsAdvOutputLoad"].toString());

	elements["ups2@upsPhaseOutputPercentLoad_1"] = ups["ups2@upsPhaseOutputPercentLoad_1"].toString();
	elements["ups2@upsPhaseOutputPercentLoad_1"].setText(valUps["ups2@upsPhaseOutputPercentLoad_1"].toString());

	elements["ups2@upsPhaseOutputPercentLoad_2"] = ups["ups2@upsPhaseOutputPercentLoad_2"].toString();
	elements["ups2@upsPhaseOutputPercentLoad_2"].setText(valUps["ups2@upsPhaseOutputPercentLoad_2"].toString());

	elements["ups2@upsPhaseOutputPercentLoad_3"] = ups["ups2@upsPhaseOutputPercentLoad_3"].toString();
	elements["ups2@upsPhaseOutputPercentLoad_3"].setText(valUps["ups2@upsPhaseOutputPercentLoad_3"].toString());

	updateElements();

	if(ups["ups1@ON_BATTERY"] == ELEM_AVAR || ups["ups2@ON_BATTERY"] == ELEM_AVAR)
		ctrlKvit["ups_on_battery"] = ELEM_AVAR;
	else
		ctrlKvit["ups_on_battery"] = ELEM_NOT;

	emit controlKvit(ctrlKvit);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateDes(AskuBinStateSet state)
{
	des = state;

	elements["rs485_des@comm1"] = des["comm"].toString();
	elements["rs485_des@port1"] = des["port"].toString();
	elements["rs485_des@device1"] = des["device1"].toString();
	elements["rs485_des@device2"] = des["device2"].toString();
	elements["rs485_des@device3"] = des["device3"].toString();
	elements["rs485_des@line1"] = des["line1"].toString();
	elements["rs485_des@line2"] = des["line2"].toString();
	elements["rs485_des@line3"] = des["line3"].toString();
	elements["base@rs485_des"] = des["channel"].toString();

	messages["des_mains@block_mode"] = des["mains1@Block_mode"];
	messages["des_dg1@block_mode"] = des["dg1@Block_mode"];
	messages["des_dg2@block_mode"] = des["dg2@Block_mode"];

	messages["des_mains@test_mode"] = des["mains1@Test_mode"];
	messages["des_dg1@test_mode"] = des["dg1@Test_mode"];
	messages["des_dg2@test_mode"] = des["dg2@Test_mode"];

	messages["des_mains@manual_mode"] = des["mains1@Manual_mode"];
	messages["des_dg1@manual_mode"] = des["dg1@Manual_mode"];
	messages["des_dg2@manual_mode"] = des["dg2@Manual_mode"];

	messages["des_mains@semiauto_mode"] = des["mains1@SemiAuto_mode"];
	messages["des_dg1@semiauto_mode"] = des["dg1@SemiAuto_mode"];
	messages["des_dg2@semiauto_mode"] = des["dg2@SemiAuto_mode"];

	messages["des_mains@auto_mode"] = des["mains1@Auto_mode"];
	messages["des_dg1@auto_mode"] = des["dg1@Auto_mode"];
	messages["des_dg2@auto_mode"] = des["dg2@Auto_mode"];

	elements["des_mains1@TB_position"] = des["mains1@TB_position"];
	elements["des_mains1@MB_position"] = des["mains1@MB_position"];
	elements["des_mains1@Block_mode"] = des["mains1@Block_mode"];
	elements["des_mains1@Test_mode"] = des["mains1@Test_mode"];
	elements["des_mains1@Manual_mode"] = des["mains1@Manual_mode"];
	elements["des_mains1@SemiAuto_mode"] = des["mains1@SemiAuto_mode"];
	elements["des_mains1@Auto_mode"] = des["mains1@Auto_mode"];
	elements["des_mains1@Unbalance_current"] = des["mains1@Unbalance_current"];
	elements["des_mains1@Unbalance_voltage"] = des["mains1@Unbalance_voltage"];
	elements["des_mains1@Phase_seq_error"] = des["mains1@Phase_seq_error"];
	elements["des_mains1@TB_open_failure"] = des["mains1@TB_open_failure"];
	elements["des_mains1@TB_close_failure"] = des["mains1@TB_close_failure"];
	elements["des_mains1@TB_pos_failure"] = des["mains1@TB_pos_failure"];
	elements["des_mains1@MB_open_failure"] = des["mains1@MB_open_failure"];
	elements["des_mains1@MB_close_failure"] = des["mains1@MB_close_failure"];
	elements["des_mains1@MB_pos_failure"] = des["mains1@MB_pos_failure"];
	elements["des_mains1@Mains_failure"] = des["mains1@Mains_failure"];
	elements["des_mains1@UL1_N_voltage"] = des["mains1@UL1_N_Generator_voltage"];
	elements["des_mains1@UL2_N_voltage"] = des["mains1@UL2_N_Generator_voltage"];
	elements["des_mains1@UL3_N_voltage"] = des["mains1@UL3_N_Generator_voltage"];
	elements["des_mains1@fL1_freq"] = des["mains1@fL1GEN_Generator_freq"];
	elements["des_mains1@fL2_freq"] = des["mains1@fL2GEN_Generator_freq"];
	elements["des_mains1@fL3_freq"] = des["mains1@fL3GEN_Generator_freq"];
	elements["des_mains1@PhiL1L2_phase"] = des["mains1@PhiL1L2_Generator_phase"];
	elements["des_mains1@PhiL2L3_phase"] = des["mains1@PhiL2L3_Generator_phase"];
	elements["des_mains1@PhiL3L1_phase"] = des["mains1@PhiL3L1_Generator_phase"];
	elements["des_mains1@IL1_current"] = des["mains1@IL1_Generator_current"];
	elements["des_mains1@IL2_current"] = des["mains1@IL2_Generator_current"];
	elements["des_mains1@IL3_current"] = des["mains1@IL3_Generator_current"];
	elements["des_mains1@P_active_power"] = des["mains1@PGEN_Generator_total_active_power"];
	elements["des_mains1@Q_reactive_power"] = des["mains1@QGEN_Generator_total_reactive_power"];
	elements["des_mains1@S_apparent_power"] = des["mains1@SGEN_Generator_total_apparent_power"];
	elements["des_mains1@E_energy_counter"] = des["mains1@EGEN_Total_energy_counter"];
	elements["des_mains1@cos_phi"] = des["mains1@Generator_cos_phi"];
	elements["des_mains1@U_supply_voltage"] = des["mains1@USUPPLY_Supply_voltage"];
	elements["des@mains1"] = des["mains1@ObSost"];

	elements["des_dg1@GB_position"] = des["dg1@GB_position"];
	elements["des_dg1@MB_position"] = des["dg1@MB_position"];
	elements["des_dg1@Block_mode"] = des["dg1@Block_mode"];
	elements["des_dg1@Test_mode"] = des["dg1@Test_mode"];
	elements["des_dg1@Manual_mode"] = des["dg1@Manual_mode"];
	elements["des_dg1@SemiAuto_mode"] = des["dg1@SemiAuto_mode"];
	elements["des_dg1@Auto_mode"] = des["dg1@Auto_mode"];
	elements["des_dg1@UL1_N_voltage"] = des["dg1@UL1_N_Generator_voltage"];
	elements["des_dg1@UL2_N_voltage"] = des["dg1@UL2_N_Generator_voltage"];
	elements["des_dg1@UL3_N_voltage"] = des["dg1@UL3_N_Generator_voltage"];
	elements["des_dg1@fL1_freq"] = des["dg1@fL1GEN_Generator_freq"];
	elements["des_dg1@fL2_freq"] = des["dg1@fL2GEN_Generator_freq"];
	elements["des_dg1@fL3_freq"] = des["dg1@fL3GEN_Generator_freq"];
	elements["des_dg1@PhiL1L2_phase"] = des["dg1@PhiL1L2_Generator_phase"];
	elements["des_dg1@PhiL2L3_phase"] = des["dg1@PhiL2L3_Generator_phase"];
	elements["des_dg1@PhiL3L1_phase"] = des["dg1@PhiL3L1_Generator_phase"];
	elements["des_dg1@IL1_current"] = des["dg1@IL1_Generator_current"];
	elements["des_dg1@IL2_current"] = des["dg1@IL2_Generator_current"];
	elements["des_dg1@IL3_current"] = des["dg1@IL3_Generator_current"];
	elements["des_dg1@P_active_power"] = des["dg1@PGEN_Generator_total_active_power"];
	elements["des_dg1@Q_reactive_power"] = des["dg1@QGEN_Generator_total_reactive_power"];
	elements["des_dg1@S_apparent_power"] = des["dg1@SGEN_Generator_total_apparent_power"];
	elements["des_dg1@E_energy_counter"] = des["dg1@EGEN_Total_energy_counter"];
	elements["des_dg1@cos_phi"] = des["dg1@Generator_cos_phi"];
	elements["des_dg1@Running_time_Absolute"] = des["dg1@Running_time_Absolute"];
	elements["des_dg1@U_supply_voltage"] = des["dg1@USUPPLY_Supply_voltage"];
	elements["des_dg1@Service_timer_1_hours"] = des["dg1@Service_timer_1_running_hours"];
	elements["des_dg1@Service_timer_1_days"] = des["dg1@Service_timer_1_running_days"];
	elements["des_dg1@Service_timer_2_hours"] = des["dg1@Service_timer_2_running_hours"];
	elements["des_dg1@Service_timer_2_days"] = des["dg1@Service_timer_2_running_days"];
	elements["des_dg1@RPM_Running_feedback"] = des["dg1@RPM_Running_feedback"];
	elements["des_dg1@EIC_comm_error"] = des["dg1@EIC_comm_error"];
	elements["des_dg1@EIC_warning"] = des["dg1@EIC_warning"];
	elements["des_dg1@EIC_shutdown"] = des["dg1@EIC_shutdown"];
	elements["des_dg1@EIC_overspeed"] = des["dg1@EIC_overspeed"];
	elements["des_dg1@EIC_coolant_temp_1"] = des["dg1@EIC_coolant_temp_1"];
	elements["des_dg1@EIC_coolant_temp_2"] = des["dg1@EIC_coolant_temp_2"];
	elements["des_dg1@EIC_oil_pressure_1"] = des["dg1@EIC_oil_pressure_1"];
	elements["des_dg1@EIC_oil_pressure_2"] = des["dg1@EIC_oil_pressure_2"];
	elements["des_dg1@EIC_oil_temperature_1"] = des["dg1@EIC_oil_temperature_1"];
	elements["des_dg1@EIC_oil_temperature_2"] = des["dg1@EIC_oil_temperature_2"];
	elements["des_dg1@Unbalance_current"] = des["dg1@Unbalance_current"];
	elements["des_dg1@Unbalance_voltage"] = des["dg1@Unbalance_voltage"];
	elements["des_dg1@Phase_seq_error"] = des["dg1@Phase_seq_error"];
	elements["des_dg1@GB_open_failure"] = des["dg1@GB_open_failure"];
	elements["des_dg1@GB_close_failure"] = des["dg1@GB_close_failure"];
	elements["des_dg1@GB_pos_failure"] = des["dg1@GB_pos_failure"];
	elements["des_dg1@MB_open_failure"] = des["dg1@MB_open_failure"];
	elements["des_dg1@MB_close_failure"] = des["dg1@MB_close_failure"];
	elements["des_dg1@MB_pos_failure"] = des["dg1@MB_pos_failure"];
	elements["des_dg1@Emergency_STOP"] = des["dg1@Emergency_STOP"];
	elements["des_dg1@Overspeed_1"] = des["dg1@Overspeed_1"];
	elements["des_dg1@Overspeed_2"] = des["dg1@Overspeed_2"];
	elements["des_dg1@Crank_failure"] = des["dg1@Crank_failure"];
	elements["des_dg1@Running_feedback_failure"] = des["dg1@Running_feedback_failure"];
	elements["des_dg1@MPU_wire_failure"] = des["dg1@MPU_wire_failure"];
	elements["des_dg1@Start_failure"] = des["dg1@Start_failure"];
	elements["des_dg1@Stop_failure"] = des["dg1@Stop_failure"];
	elements["des_dg1@Stop_coil_wire_break"] = des["dg1@Stop_coil_wire_break"];
	elements["des_dg1@Underspeed"] = des["dg1@Underspeed"];
	elements["des_dg1@Internal_comm_failure"] = des["dg1@Internal_comm_failure"];
	elements["des_dg1@Engine_heater"] = des["dg1@Engine_heater"];
	elements["des_dg1@Battery_test"] = des["dg1@Battery_test"];
	elements["des_dg1@Battery_assymmetry_1"] = des["dg1@Battery_assymmetry_1"];
	elements["des_dg1@Battery_assymmetry_2"] = des["dg1@Battery_assymmetry_2"];
	elements["des_dg1@Max_ventilation_1"] = des["dg1@Max_ventilation_1"];
	elements["des_dg1@Max_ventilation_2"] = des["dg1@Max_ventilation_2"];
	elements["des_dg1@Fuel_pump_logic"] = des["dg1@Fuel_pump_logic"];
	elements["des_dg1@Engine_running"] = des["dg1@Engine_running"];
	elements["des_dg1@Hz_V_failure"] = des["dg1@Generator_Hz_V_failure"];
	elements["des@dg1"] = des["dg1@ObSost"];

	elements["des_dg2@GB_position"] = des["dg2@GB_position"];
	elements["des_dg2@MB_position"] = des["dg2@MB_position"];
	elements["des_dg2@Block_mode"] = des["dg2@Block_mode"];
	elements["des_dg2@Test_mode"] = des["dg2@Test_mode"];
	elements["des_dg2@Manual_mode"] = des["dg2@Manual_mode"];
	elements["des_dg2@SemiAuto_mode"] = des["dg2@SemiAuto_mode"];
	elements["des_dg2@Auto_mode"] = des["dg2@Auto_mode"];
	elements["des_dg2@UL1_N_voltage"] = des["dg2@UL1_N_Generator_voltage"];
	elements["des_dg2@UL2_N_voltage"] = des["dg2@UL2_N_Generator_voltage"];
	elements["des_dg2@UL3_N_voltage"] = des["dg2@UL3_N_Generator_voltage"];
	elements["des_dg2@fL1_freq"] = des["dg2@fL1GEN_Generator_freq"];
	elements["des_dg2@fL2_freq"] = des["dg2@fL2GEN_Generator_freq"];
	elements["des_dg2@fL3_freq"] = des["dg2@fL3GEN_Generator_freq"];
	elements["des_dg2@PhiL1L2_phase"] = des["dg2@PhiL1L2_Generator_phase"];
	elements["des_dg2@PhiL2L3_phase"] = des["dg2@PhiL2L3_Generator_phase"];
	elements["des_dg2@PhiL3L1_phase"] = des["dg2@PhiL3L1_Generator_phase"];
	elements["des_dg2@IL1_current"] = des["dg2@IL1_Generator_current"];
	elements["des_dg2@IL2_current"] = des["dg2@IL2_Generator_current"];
	elements["des_dg2@IL3_current"] = des["dg2@IL3_Generator_current"];
	elements["des_dg2@P_active_power"] = des["dg2@PGEN_Generator_total_active_power"];
	elements["des_dg2@Q_reactive_power"] = des["dg2@QGEN_Generator_total_reactive_power"];
	elements["des_dg2@S_apparent_power"] = des["dg2@SGEN_Generator_total_apparent_power"];
	elements["des_dg2@E_energy_counter"] = des["dg2@EGEN_Total_energy_counter"];
	elements["des_dg2@cos_phi"] = des["dg2@Generator_cos_phi"];
	elements["des_dg2@Running_time_Absolute"] = des["dg2@Running_time_Absolute"];
	elements["des_dg2@U_supply_voltage"] = des["dg2@USUPPLY_Supply_voltage"];
	elements["des_dg2@Service_timer_1_hours"] = des["dg2@Service_timer_1_running_hours"];
	elements["des_dg2@Service_timer_1_days"] = des["dg2@Service_timer_1_running_days"];
	elements["des_dg2@Service_timer_2_hours"] = des["dg2@Service_timer_2_running_hours"];
	elements["des_dg2@Service_timer_2_days"] = des["dg2@Service_timer_2_running_days"];
	elements["des_dg2@RPM_Running_feedback"] = des["dg2@RPM_Running_feedback"];
	elements["des_dg2@EIC_comm_error"] = des["dg2@EIC_comm_error"];
	elements["des_dg2@EIC_warning"] = des["dg2@EIC_warning"];
	elements["des_dg2@EIC_shutdown"] = des["dg2@EIC_shutdown"];
	elements["des_dg2@EIC_overspeed"] = des["dg2@EIC_overspeed"];
	elements["des_dg2@EIC_coolant_temp_1"] = des["dg2@EIC_coolant_temp_1"];
	elements["des_dg2@EIC_coolant_temp_2"] = des["dg2@EIC_coolant_temp_2"];
	elements["des_dg2@EIC_oil_pressure_1"] = des["dg2@EIC_oil_pressure_1"];
	elements["des_dg2@EIC_oil_pressure_2"] = des["dg2@EIC_oil_pressure_2"];
	elements["des_dg2@EIC_oil_temperature_1"] = des["dg2@EIC_oil_temperature_1"];
	elements["des_dg2@EIC_oil_temperature_2"] = des["dg2@EIC_oil_temperature_2"];
	elements["des_dg2@Unbalance_current"] = des["dg2@Unbalance_current"];
	elements["des_dg2@Unbalance_voltage"] = des["dg2@Unbalance_voltage"];
	elements["des_dg2@Phase_seq_error"] = des["dg2@Phase_seq_error"];
	elements["des_dg2@GB_open_failure"] = des["dg2@GB_open_failure"];
	elements["des_dg2@GB_close_failure"] = des["dg2@GB_close_failure"];
	elements["des_dg2@GB_pos_failure"] = des["dg2@GB_pos_failure"];
	elements["des_dg2@MB_open_failure"] = des["dg2@MB_open_failure"];
	elements["des_dg2@MB_close_failure"] = des["dg2@MB_close_failure"];
	elements["des_dg2@MB_pos_failure"] = des["dg2@MB_pos_failure"];
	elements["des_dg2@Emergency_STOP"] = des["dg2@Emergency_STOP"];
	elements["des_dg2@Overspeed_1"] = des["dg2@Overspeed_1"];
	elements["des_dg2@Overspeed_2"] = des["dg2@Overspeed_2"];
	elements["des_dg2@Crank_failure"] = des["dg2@Crank_failure"];
	elements["des_dg2@Running_feedback_failure"] = des["dg2@Running_feedback_failure"];
	elements["des_dg2@MPU_wire_failure"] = des["dg2@MPU_wire_failure"];
	elements["des_dg2@Start_failure"] = des["dg2@Start_failure"];
	elements["des_dg2@Stop_failure"] = des["dg2@Stop_failure"];
	elements["des_dg2@Stop_coil_wire_break"] = des["dg2@Stop_coil_wire_break"];
	elements["des_dg2@Underspeed"] = des["dg2@Underspeed"];
	elements["des_dg2@Internal_comm_failure"] = des["dg2@Internal_comm_failure"];
	elements["des_dg2@Engine_heater"] = des["dg2@Engine_heater"];
	elements["des_dg2@Battery_test"] = des["dg2@Battery_test"];
	elements["des_dg2@Battery_assymmetry_1"] = des["dg2@Battery_assymmetry_1"];
	elements["des_dg2@Battery_assymmetry_2"] = des["dg2@Battery_assymmetry_2"];
	elements["des_dg2@Max_ventilation_1"] = des["dg2@Max_ventilation_1"];
	elements["des_dg2@Max_ventilation_2"] = des["dg2@Max_ventilation_2"];
	elements["des_dg2@Fuel_pump_logic"] = des["dg2@Fuel_pump_logic"];
	elements["des_dg2@Engine_running"] = des["dg2@Engine_running"];
	elements["des_dg2@Hz_V_failure"] = des["dg2@Generator_Hz_V_failure"];
	elements["des@dg2"] = des["dg2@ObSost"];

	elements["base@des"] = des["des@ObSost"].toString();

	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateVospd(AskuBinStateSet state, AskuValueSet values)
{
	vospd = state;
	valVospd = values;

//	qDebug() << "VOSPD: state" << vospd.dump();
//	qDebug() << "VOSPD: values" << valVospd.dump();

	funVospd();
	fun125PK01();
	funCommonPorl();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateAvt(AskuBinStateSet state, AskuValueSet values)
{
	Q_UNUSED(values);

	avt = state;
/*
	elements["obr_base@ppv"] = pwm["connected"];
	elements["prdsys@powermeter"] = pwm["ObSost"];
	elements["zal@powermeter"] = pwm["ObSost"];
	elements["prdsys@powervalue"] = pwm["power"];

	messages["prdsys@powermeter"] = pwm["power"];
	messages["prdsys@power"] = pwm["power"];
*/
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStatePos(AskuBinStateSet state)
{
	pos = state;
    elements["base@ksb"] = pos["stateKsb"];
    elements["status_window@common_ksb"] =pos["stateKsb"];
    elements["ksb@alarm"] = pos["alarm"];
    elements["ksb@portal"] = pos["portal"];
    elements["ksb@perimetr"] = pos["perimetr"];
    elements["ksb@dolphin"] = pos["dolphin"];
    elements["ksb@gatePerimetr"] = pos["gatePerimetr"];
    elements["ksb@gateCase"] = pos["gateCase"];
    elements["ksb@fireCase"] = pos["fireCase"];
    elements["ksb@fireAlarmCase"] = pos["fireAlarmCase"];
    elements["ksb@gateDes"] = pos["gateDes"];
    elements["ksb@fireDes"] = pos["fireDes"];
    elements["ksb@fireAlarmDes"] = pos["fireAlarmDes"];
    elements["ksb@lighting"] = pos["lighting"];
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onDataAsku(AskuSignalSet smap, AskuValueSet vmap)
{
	sigmap = smap;
	valmap = vmap;

//qDebug() << "----";
//qDebug() << smap.dump();
//qDebug() << valmap.dump();
//qDebug() << "----";

//ELK
	fun124YY08_raf();
	fun124EE02_raf();
	fun124YY03_raf();
	fun125YY03_raf();
	funCondition();
	funSensorsPT();
	funSOTR_raf();
	funCanalSOTR();

//PRD
	fun124YG02_raf();
	funPanelAvt_raf();
	fun125YY04_raf();
	fun126GG02_raf(0);
	fun126GG02_raf(1);
	funPrdSys_raf();

	funCommonPorl();

	checkResetPrd();
	funPrdTemperature();

	ctrlKvit["pum1_on"] = b125yy04["123gv02_1"];
	ctrlKvit["pum2_on"] = b125yy04["123gv02_2"];

	if((ctrlKvit["drive1_on"] == ELEM_NORMA || ctrlKvit["drive2_on"] == ELEM_NORMA) && ctrlKvit["prd1_on"] == ELEM_NORMA && ctrlKvit["prd2_on"] == ELEM_NORMA && ctrlKvit["vrl"] == ELEM_NORMA)
		ctrlKvit["status_raf"] = QString("norma");
	else if((ctrlKvit["drive1_on"] == ELEM_NORMA || ctrlKvit["drive2_on"] == ELEM_NORMA) && (ctrlKvit["prd1_on"] == ELEM_NORMA || ctrlKvit["prd2_on"] == ELEM_NORMA || ctrlKvit["vrl"] == ELEM_NORMA))
		ctrlKvit["status_raf"] = QString("error");
	else
		ctrlKvit["status_raf"] = QString("not");

	emit controlKvit(ctrlKvit);

	updateElements();
	updateElementsRgdv();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPrdTemperature()
{
	valmap["value_temperature_prd1_working"];
	valmap["value_temperature_prd2_working"];
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funRmo()
{
	if(m_isWorkRmo)
		bCommonRlk["RMO"] = ELEM_NORMA;
	else
		bCommonRlk["RMO"] = ELEM_NOT;

	elements["base@terminal"] = bCommonRlk["RMO"];
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funSoi()
{
	if(m_isWorkSoi)
		bCommonRlk["SOI"] = ELEM_NORMA;
	else
		bCommonRlk["SOI"] = ELEM_NOT;

	elements["base@tc_soi"] = bCommonRlk["SOI"];
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPpv()
{
	if(m_isWorkPpv)
		bCommonRlk["PPV"] = ELEM_NORMA;
	else
		bCommonRlk["PPV"] = ELEM_NOT;

	elements["obr_base@ppv"] = bCommonRlk["PPV"];
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::fun125PK01()
{
	if((localSvkr["ObSost"] == ELEM_AVAR && otherSvkr["ObSost"] == ELEM_AVAR) ||
		(localSvkr["ObSost"] == ELEM_AVAR && otherSvkr["ObSost"] == ELEM_NOT) ||
		(localSvkr["ObSost"] == ELEM_NOT && otherSvkr["ObSost"] == ELEM_AVAR) ||
		(bCommunicators["Communicator1"] == ELEM_AVAR && bCommunicators["Communicator2"] == ELEM_AVAR))
		b125pk01["ObSost"] = ELEM_AVAR;
	else if(localSvkr["ObSost"] == ELEM_NORMA && otherSvkr["ObSost"] == ELEM_NORMA &&
		bCommunicators["Communicator1"] == ELEM_NORMA && bCommunicators["Communicator2"] == ELEM_NORMA)
		b125pk01["ObSost"] = ELEM_NORMA;
	else
		b125pk01["ObSost"] = ELEM_ERROR;

	elements["zal@125pk01"] = b125pk01["ObSost"].toString();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funCommunicators()
{
	if(canalAsku["Port1"] == ELEM_NOT && drives["port1"] == ELEM_NOT && coolers["port1"] == ELEM_NOT)
		bCommunicators["Communicator1"] = ELEM_AVAR;
	else if(canalAsku["Port1"] == ELEM_NOT || drives["port1"] == ELEM_NOT || coolers["port1"] == ELEM_NOT)
		bCommunicators["Communicator1"] = ELEM_ERROR;
	else
		bCommunicators["Communicator1"] = ELEM_NORMA;
//	messages["126pk01@Communicator1"]= bCommunicators["Communicator1"];

	if(canalAsku["Port2"] == ELEM_NOT && drives["port2"] == ELEM_NOT && coolers["port2"] == ELEM_NOT)
		bCommunicators["Communicator2"] = ELEM_AVAR;
	else if(canalAsku["Port2"] == ELEM_NOT || drives["port2"] == ELEM_NOT || coolers["port2"] == ELEM_NOT)
		bCommunicators["Communicator2"] = ELEM_ERROR;
	else
		bCommunicators["Communicator2"] = ELEM_NORMA;
//	messages["126pk01@Communicator2"]= bCommunicators["Communicator2"];

	if(bCommunicators["Communicator1"] != ELEM_AVAR || bCommunicators["Communicator2"] != ELEM_AVAR)
		bCommunicators["Ethernet"] = ELEM_NORMA;
	else
		bCommunicators["Ethernet"] = ELEM_AVAR;


	elements["obr_base@comm1"] = bCommunicators["Communicator1"].toString();
	elements["obr_base@comm2"] = bCommunicators["Communicator2"].toString();
	elements["obr_base@ethernet"] = bCommunicators["Ethernet"].toString();

//	messages["obr_base@Communicator2"]= bCommunicators["Communicator2"];
//	messages["obr_base@Communicator1"]= bCommunicators["Communicator1"];
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funCommonPorl()
{
	if(drives["mest"] == ELEM_MEST ||
		b124yy08["mest"] == ELEM_MEST ||
		b124yg02["mest"] == ELEM_MEST)
		bCommonPrl["mest"] = ELEM_MEST;
	else
		bCommonPrl["mest"] = ELEM_NOT;

	if(b124yy03["ObSost"] == ELEM_AVAR ||
		(localSvkr["ObSost"] == ELEM_AVAR && otherSvkr["ObSost"] == ELEM_AVAR) || 
		(localSvkr["ObSost"] == ELEM_NOT && otherSvkr["ObSost"] == ELEM_AVAR) || 
		(localSvkr["ObSost"] == ELEM_AVAR && otherSvkr["ObSost"] == ELEM_NOT) || 
		pwm["power"] == ELEM_AVAR ||
		b125yy04["obSost"] == ELEM_AVAR ||
		canalAsku["ObSost"] == ELEM_AVAR ||
		coolers["channel"] == ELEM_AVAR ||
		drives["channel"] == ELEM_AVAR ||
/*		ups["channel"] == ELEM_AVAR ||*/
		(b126gg02[0]["obSost"] == ELEM_AVAR && b126gg02[1]["obSost"] == ELEM_AVAR) ||
		(bSOTR["cond1"] == ELEM_AVAR && bSOTR["cond2"] == ELEM_AVAR) ||
		(bSOTR["vent1"] == ELEM_AVAR && bSOTR["vent2"] == ELEM_AVAR) ||
		(b124pp04["obSost"] == ELEM_AVAR) ||
		b125yy03["aorls"] == ELEM_AVAR ||
		b125yy03["block_opu"] == ELEM_AVAR)
		bCommonPrl["ObSost"] = ELEM_AVAR;
	else if(b124yy03["ObSost"] == ELEM_ERROR ||
		localSvkr["ObSost"] == ELEM_AVAR || otherSvkr["ObSost"] == ELEM_AVAR || 
		localSvkr["ObSost"] == ELEM_ERROR || otherSvkr["ObSost"] == ELEM_ERROR || 
		pwm["ObSost"] == ELEM_AVAR ||
		pwm["power"] == ELEM_ERROR ||
		b125yy04["obSost"] == ELEM_ERROR ||
		canalAsku["ObSost"] == ELEM_ERROR ||
		coolers["channel"] == ELEM_ERROR ||
		drives["channel"] == ELEM_ERROR ||
		ups["channel"] == ELEM_ERROR ||
		b126gg02[0]["obSost"] == ELEM_AVAR || b126gg02[1]["obSost"] == ELEM_AVAR ||
		b126gg02[0]["obSost"] == ELEM_ERROR || b126gg02[1]["obSost"] == ELEM_ERROR ||
		bSOTR["cond1"] == ELEM_AVAR || bSOTR["cond2"] == ELEM_AVAR ||
		bSOTR["vent1"] == ELEM_AVAR || bSOTR["vent2"] == ELEM_AVAR ||
		b124pp04["obSost"] == ELEM_ERROR)
		bCommonPrl["ObSost"] == ELEM_ERROR;
	else if(drives["125sg02"] == ELEM_NORMA && 
		localSvkr["ObSost"] == ELEM_NORMA && otherSvkr["ObSost"] == ELEM_NORMA && 
		b125yy04["obSost"] == ELEM_NORMA &&
		b126gg02[0]["obSost"] == ELEM_NORMA && b126gg02[1]["obSost"] == ELEM_NORMA &&
		(bSOTR["cond1"] == ELEM_NORMA || bSOTR["cond2"] == ELEM_NORMA || 
		bSOTR["vent1"] == ELEM_NORMA || bSOTR["vent2"] == ELEM_NORMA) &&
		b124pp04["obSost"] == ELEM_NORMA &&
		b125yy03["aorls"] != ELEM_AVAR &&
		b125yy03["block_opu"] != ELEM_AVAR)
		bCommonPrl["ObSost"] = ELEM_NORMA;
	else
		bCommonPrl["ObSost"] = ELEM_NOT;

	elements["status_window@common_porl"] = bCommonPrl["ObSost"].toString() + bCommonPrl["mest"].toStringMest();
	messages["prl@obSost"] = bCommonPrl["ObSost"];

	funCommonUrlk();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funCommonUrlk()
{
	if(bCommonPrl["mest"] == ELEM_MEST || bCommonVrl["mest"] == ELEM_MEST)
		bCommonRlk["mest"] = ELEM_MEST;
	else
		bCommonRlk["mest"] = ELEM_NOT;

	if(bCommonPrl["ObSost"] == ELEM_NOT && bCommonVrl["ObSost"] == ELEM_NOT)
		bCommonRlk["ObSost"] = ELEM_NOT;
	else if(bCommonPrl["ObSost"] == ELEM_AVAR || bCommonVrl["ObSost"] == ELEM_AVAR)
		bCommonRlk["ObSost"] = ELEM_AVAR;
	else if(bCommonPrl["ObSost"] == ELEM_ERROR || bCommonVrl["ObSost"] == ELEM_ERROR)
		bCommonRlk["ObSost"] = ELEM_ERROR;
	else if(bCommonPrl["ObSost"] == ELEM_NORMA && bCommonVrl["ObSost"] == ELEM_NORMA)
		bCommonRlk["ObSost"] = ELEM_NORMA;
	else
		bCommonRlk["ObSost"] = ELEM_ERROR;

	elements["status_window@common_urlk"] = bCommonRlk["ObSost"].toString() + bCommonRlk["mest"].toStringMest();
	messages["urlk@obSost"] = bCommonRlk["ObSost"];
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funMpsn()
{
	if(localVoi["VoiDataMpsn"] == ELEM_NORMA || otherVoi["VoiDataMpsn"] == ELEM_NORMA)
		bCommonRlk["Mpsn"] = ELEM_NORMA;
	else //if(localVoi["VoiDataMpsn"] == ELEM_NOT && otherVoi["VoiDataMpsn"] == ELEM_NOT)
		bCommonRlk["Mpsn"] = ELEM_NOT;
/*	else if(localVoi["VoiDataMpsn"] == ELEM_AVAR || otherVoi["VoiDataMpsn"] == ELEM_AVAR)
		bCommonRlk["Mpsn"] = ELEM_AVAR;
	else
		bCommonRlk["Mpsn"] = ELEM_ERROR;
*/
	elements["base@mpsn"] = bCommonRlk["Mpsn"].toString();
	elements["status_window@common_mpsn"] = bCommonRlk["Mpsn"].toString();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateLocalCoreTemp(AskuBinStateSet state, AskuValueSet values)
{
	localCoreTemp = state;
	valLocalCoreTemp = values;

//	qDebug() << "state = " << state.dump();
//	qDebug() << "value = " << values.dump();

	funSvkrLocal();
	fun125PK01();
	funCommonPorl();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateOtherCoreTemp(AskuBinStateSet state, AskuValueSet values)
{
	otherCoreTemp = state;
	valOtherCoreTemp = values;

//	qDebug() << "state = " << state.dump();
//	qDebug() << "value = " << values.dump();

	funSvkrOther();
	fun125PK01();
	funCommonPorl();
	updateElements();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::prepareRgdv()
{
	elementsRgdv["rgdv"] = 							AskuRgdvItem(QString(), QString(), QString("norma"), QString("НОРМА РГДВ"));

	elementsRgdv["124yg02_1_title"] = 				AskuRgdvItem(QString("Передатчик 1"), QString(), QString("title"));
	elementsRgdv["124yg02_1_ou"] = 					AskuRgdvItem(QString("Д2ВВ056-1"), QString("Блок 124УГ02 (ПРД1)"), QString("не контр"));
	elementsRgdv["124yg02_1_mest"] = 				AskuRgdvItem(QString("Режим МЕСТ"), QString("Блок 124УГ02 (ПРД1)"));
	elementsRgdv["124yg02_1_qf_123bb01_1"] = 		AskuRgdvItem(QString("ОТКЛ QF 123ББ01(1)"), QString("Блок 124УГ02 (ПРД1)"));
	elementsRgdv["124yg02_1_qf_123bb01_2"] = 		AskuRgdvItem(QString("ОТКЛ QF 123ББ01(2)"), QString("Блок 124УГ02 (ПРД1)"));
	elementsRgdv["124yg02_1_qf_123gv02_1"] = 		AskuRgdvItem(QString("ОТКЛ QF 123ГВ02(1)"), QString("Блок 124УГ02 (ПРД1)"));
	elementsRgdv["124yg02_1_qf_chp_1"] = 			AskuRgdvItem(QString("ОТКЛ QF ЧП1"), QString("Блок 124УГ02 (ПРД1)"));
	elementsRgdv["124yg02_1_qf_chp_2"] = 			AskuRgdvItem(QString("ОТКЛ QF ЧП2"), QString("Блок 124УГ02 (ПРД1)"));
	elementsRgdv["124yg02_1_qf_vent"] = 			AskuRgdvItem(QString("ОТКЛ QF ВЕНТ ОБЩ 1"), QString("Блок 124УГ02 (ПРД1)"));
	elementsRgdv["124yg02_1_qf_prd1"] = 			AskuRgdvItem(QString("ОТКЛ QF ПРД1"), QString("Блок 124УГ02 (ПРД1)"));

	elementsRgdv["124yg02_2_title"] = 				AskuRgdvItem(QString("Передатчик 2"), QString(), QString("title"));
	elementsRgdv["124yg02_2_ou"] = 					AskuRgdvItem(QString("Д2ВВ056-2"), QString("Блок 124УГ02 (ПРД2)"), QString("не контр"));
	elementsRgdv["124yg02_2_mest"] = 				AskuRgdvItem(QString("Режим МЕСТ"), QString("Блок 124УГ02 (ПРД2)"));
	elementsRgdv["124yg02_2_qf_123bb01_3"] = 		AskuRgdvItem(QString("ОТКЛ QF 123ББ01(3)"), QString("Блок 124УГ02 (ПРД2)"));
	elementsRgdv["124yg02_2_qf_123bb01_4"] = 		AskuRgdvItem(QString("ОТКЛ QF 123ББ01(4)"), QString("Блок 124УГ02 (ПРД2)"));
	elementsRgdv["124yg02_2_qf_123gv02_2"] = 		AskuRgdvItem(QString("ОТКЛ QF 123ГВ02(2)"), QString("Блок 124УГ02 (ПРД2)"));
	elementsRgdv["124yg02_2_qf_chp_3"] = 			AskuRgdvItem(QString("ОТКЛ QF ЧП3"), QString("Блок 124УГ02 (ПРД2)"));
	elementsRgdv["124yg02_2_qf_chp_4"] = 			AskuRgdvItem(QString("ОТКЛ QF ЧП4"), QString("Блок 124УГ02 (ПРД2)"));
	elementsRgdv["124yg02_2_qf_vent"] = 			AskuRgdvItem(QString("ОТКЛ QF ВЕНТ ОБЩ 2"), QString("Блок 124УГ02 (ПРД2)"));
	elementsRgdv["124yg02_2_qf_prd2"] = 			AskuRgdvItem(QString("ОТКЛ QF ПРД2"), QString("Блок 124УГ02 (ПРД2)"));

	elementsRgdv["124yy08_title"] = 				AskuRgdvItem(QString("Электропитание"), QString(), QString("title"));
	elementsRgdv["124yy08_ou"] = 					AskuRgdvItem(QString("Д2ВВ056"), QString("Блок 124УУ08"), QString("не контр"));
	elementsRgdv["124yy08_mest"] = 					AskuRgdvItem(QString("Режим МЕСТ"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_123bb01_1"] = 			AskuRgdvItem(QString("ОТКЛ 123ББ01-1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_123bb01_2"] = 			AskuRgdvItem(QString("ОТКЛ 123ББ01-2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_123bb01_3"] = 			AskuRgdvItem(QString("ОТКЛ 123ББ01-3"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_123bb01_4"] = 			AskuRgdvItem(QString("ОТКЛ 123ББ01-4"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_27v_buf"] = 			AskuRgdvItem(QString("ОТКЛ 27В БУФ"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_cond_1"] = 			AskuRgdvItem(QString("ОТКЛ КОНДИЦИОНЕР 1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_cond_2"] = 			AskuRgdvItem(QString("ОТКЛ КООНДИЦИОНЕР 2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_kmvrl_1"] = 			AskuRgdvItem(QString("ОТКЛ МВРЛ-К Н 1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_kmvrl_2"] = 			AskuRgdvItem(QString("ОТКЛ МВРЛ-К Н 2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_124yg02"] = 			AskuRgdvItem(QString("ОТКЛ 124УГ02"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_380v_rpu"] = 			AskuRgdvItem(QString("ОТКЛ 380В РПУ АВТ"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_set_380v"] = 			AskuRgdvItem(QString("ОТКЛ СЕТЬ 380В АВТ"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_124yy03_1"] = 			AskuRgdvItem(QString("ОТКЛ 124УУ03-I"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_124yy03_2"] = 			AskuRgdvItem(QString("ОТКЛ 124УУ03-II"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_prm_1"] = 				AskuRgdvItem(QString("ОТКЛ ПРМ-I"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_prm_2"] = 				AskuRgdvItem(QString("ОТКЛ ПРМ-II"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_prd_1"] = 				AskuRgdvItem(QString("ОТКЛ ПРД-I"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_prd_2"] = 				AskuRgdvItem(QString("ОТКЛ ПРД-II"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_obr_1"] = 				AskuRgdvItem(QString("ОТКЛ АППАР ОБРАБ-I"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_obr_2"] = 				AskuRgdvItem(QString("ОТКЛ АППАР ОБРАБ-II"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_ups_1"] = 				AskuRgdvItem(QString("ОТКЛ ИБП 1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_ups_2"] = 				AskuRgdvItem(QString("ОТКЛ ИБП 2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_27v_c"] = 				AskuRgdvItem(QString("ОТКЛ 27В-Ц"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_qf_accum"] = 				AskuRgdvItem(QString("ОТКЛ АККУМ"), QString("Блок 124УУ08"));

	elementsRgdv["124yy08_p27v_gsh"] = 				AskuRgdvItem(QString("27В ГШ"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_123bb02"] = 			AskuRgdvItem(QString("27В 123ББ02"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_pit_avt"] = 			AskuRgdvItem(QString("27В ПИТ АВТ"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_howl_1"] = 			AskuRgdvItem(QString("27В РЕВУН 1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_howl_2"] = 			AskuRgdvItem(QString("27В РЕВУН 2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_prm_1"] = 			AskuRgdvItem(QString("27В ПРМ 1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_prm_2"] = 			AskuRgdvItem(QString("27В ПРМ 2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_mspd"] = 			AskuRgdvItem(QString("27В МСПД"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_zu_1"] = 			AskuRgdvItem(QString("27В ЗУ 1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_zu_2"] = 			AskuRgdvItem(QString("27В ЗУ 2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_ps_1"] = 			AskuRgdvItem(QString("27В ПС 1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_ps_2"] = 			AskuRgdvItem(QString("27В ПС 2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_123gv02_1"] = 		AskuRgdvItem(QString("27В 123ГВ02-1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_123gv02_2"] = 		AskuRgdvItem(QString("27В 123ГВ02-2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_azsens_1"] = 		AskuRgdvItem(QString("27В АЗ ДАТЧ 1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_azsens_2"] = 		AskuRgdvItem(QString("27В АЗ ДАТЧ 2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_124yy03_1"] = 		AskuRgdvItem(QString("27В 124УУ03-1"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_124yy03_2"] = 		AskuRgdvItem(QString("27В 124УУ03-2"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_p27v_opu"] = 				AskuRgdvItem(QString("27В ОПУ"), QString("Блок 124УУ08"));

	elementsRgdv["124yy08_24v_accum"] = 			AskuRgdvItem(QString("24В НАПР АККУМ"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_opu_open"] = 				AskuRgdvItem(QString("ЛЮК ОПУ ОТКРЫТ"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_block_opu"] = 			AskuRgdvItem(QString("БЛОКИР ОПУ НАРУШ"), QString("Блок 124УУ08"));
	elementsRgdv["124yy08_aorls"] = 				AskuRgdvItem(QString("АО РЛС"), QString("Блок 124УУ08"));
}

// ----------------------------------------------------------------------------
