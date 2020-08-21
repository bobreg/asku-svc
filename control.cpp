#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "control.h"
#include "viewer.h"

// ----------------------------------------------------------------------------
AskuGprControl::AskuGprControl(qint32 numGpr, QObject * parent) : QObject(parent)
{
	m_numGpr = numGpr;
	m_numCtrl = -1;
	m_isMain = false;
	m_regime = RegInit;
	m_isWorkGpr = false;
	m_isWorkPpv = false;
	m_isWorkRmo = false;
	m_isWorkSoi = false;
	m_isWorkPwm = false;
	m_isWorkAvt = false;
	m_changeCmd = cmdOk;
	m_mainGpr = 0;
	m_mainGprOther = 0;
	m_stamp = 0;
	m_recvStamp = 0;
	m_counterGpr = 0;
	m_counterPpv = 0;
	m_counterRmo = 0;
	m_counterSoi = 0;
	m_counterPwm = 0;
	m_counterAvt = 0;
	m_initCounter = 1;

	m_commands.clear();
	m_commands["regime"] = "reg_init";
	m_commands["raf"] = "off";
	m_commands["rgdv"] = "off";
	m_commands["obr"] = "off";
	m_commands["resobr"] = "on";
	m_commands["drive"] = "off";
	m_commands["azsens"] = "off";
	m_commands["overview"] = "off";
	m_commands["prd"] = "off";
	m_commands["prd1"] = "off";
	m_commands["prd2"] = "off";
	m_commands["pumi"] = "off";
	m_commands["vrl"] = "off";
	m_commands["resvrl"] = "on";
	m_commands["ind_raf"] = "not";
	m_commands["ind_raf_text"] = "Включен";
	m_commands["ind_rgdv"] = "not";
	m_commands["ind_rgdv_text"] = "Готов";

	m_syncTimer = new QTimer(this);
	connect(m_syncTimer, SIGNAL(timeout()), this, SLOT(syncTimeout()));

	m_onOffTimer = new QTimer(this);
	connect(m_onOffTimer, SIGNAL(timeout()), this, SLOT(rafOnOffTimeout()));

	m_BepStartTimer = new QTimer(this);
	connect(m_BepStartTimer, SIGNAL(timeout()), this, SLOT(onTimeBepStart()));

	m_powerTimer = new QTimer(this);
	connect(m_powerTimer, SIGNAL(timeout()), this, SLOT(onTimeMeasurePower()));
}

// ----------------------------------------------------------------------------
AskuGprControl::~AskuGprControl()
{
	if(m_powerTimer)
	{
		m_powerTimer->stop();
		delete m_powerTimer;
		m_powerTimer = 0;
	}
	if(m_BepStartTimer)
	{
		m_BepStartTimer->stop();
		delete m_BepStartTimer;
		m_BepStartTimer = 0;
	}
	if(m_onOffTimer)
	{
		m_onOffTimer->stop();
		delete m_onOffTimer;
		m_onOffTimer = 0;
	}
	if(m_syncTimer)
	{
		m_syncTimer->stop();
		delete m_syncTimer;
		m_syncTimer = 0;
	}
}

// ----------------------------------------------------------------------------
QString AskuGprControl::regimeName(AskuRegime regime)
{
	QString str;

	switch(regime)
	{
		case RegInit:
			str = "ИНИТ";
			break;
		case RegTest:
			str = "ТЕСТ";
			break;
		case RegRgdv:
			str = "РГДВ";
			break;
		case RegRaf:
			str = "РАФ";
			break;
	}

	return str;
}

// ----------------------------------------------------------------------------
void AskuGprControl::syncTimeout()
{
//	LogInfo("syncTimeout");
	verifyStatus();
	makeSyncMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::onChangedHour()
{
	AddSimpleMes("",QString("----- Обработка-%1 --- Режим %2 -----").arg(NUM_GPR()).arg(regimeName(m_regime)));
}

// ----------------------------------------------------------------------------
void AskuGprControl::onConnectedGpr()
{
//	if(m_mainGpr == NUM_GPR())
//		QTimer::singleShot(0, this, SLOT(refreshControl()));

	QTimer::singleShot(5000, this, SIGNAL(needRefreshAll()));
}

// ----------------------------------------------------------------------------
void AskuGprControl::onDisconnectedGpr()
{
}

// ----------------------------------------------------------------------------
void AskuGprControl::onReadyToCheckMode(bool on)
{
	if(m_isMain)
	{
		if(m_regime == RegInit)
		{
			LogInfo("GprControl::onReadyToCheckMode  on = %d", on);

			if(on)
				setRegime(RegRaf);
			else
				setRegime(RegTest);
		}
		emit sigRefreshState();
	}
}

// ----------------------------------------------------------------------------
void AskuGprControl::onChangedAzimuthSource(quint32 source)
{
	if(source == 0)
		m_commands["azsens"] = "1";
	else if(source == 1)
		m_commands["azsens"] = "2";
	else
		m_commands["azsens"] = "off";

	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::verifyStatus()
{
//	qDebug("verifyStatus");

	if(m_counterPpv)
	{
		if(!m_isWorkPpv)
		{
			m_isWorkPpv = true;
			emit sigConnectedPpv();
			AddSimpleMes("АСКУ","Установлена связь с ППВ");
		}

		m_counterPpv--;
	}
	else
	{
		if(m_isWorkPpv)
		{
			m_isWorkPpv = false;
			emit sigDisconnectedPpv();
			AddSimpleMes("АСКУ","Разрыв связи с ППВ");
		}
	}

	if(m_counterRmo)
	{
		if(!m_isWorkRmo)
		{
			m_isWorkRmo = true;
			emit sigConnectedRmo();
			AddSimpleMes("АСКУ","Установлена связь с ДТ");
		}

		m_counterRmo--;
	}
	else
	{
		if(m_isWorkRmo)
		{
			m_isWorkRmo = false;
			emit sigDisconnectedRmo();
			AddSimpleMes("АСКУ","Разрыв связи с ДТ");
		}
	}

	if(m_counterSoi)
	{
		if(!m_isWorkSoi)
		{
			m_isWorkSoi = true;
			emit sigConnectedSoi();
			AddSimpleMes("АСКУ","Установлена связь с ТЦ СОИ");
		}

		m_counterSoi--;
	}
	else
	{
		if(m_isWorkSoi)
		{
			m_isWorkSoi = false;
			emit sigDisconnectedSoi();
			AddSimpleMes("АСКУ","Разрыв связи с ТЦ СОИ");
		}
	}

	if(m_counterPwm)
	{
		if(!m_isWorkPwm)
		{
			m_isWorkPwm = true;
			emit sigConnectedPwm();
			AddSimpleMes("АСКУ","Установлена связь с сервисом измерителя мощности");
			if(m_powerTimer)
				m_powerTimer->start(10000);
		}

		m_counterPwm--;
	}
	else
	{
		if(m_isWorkPwm)
		{
			m_isWorkPwm = false;
			emit sigDisconnectedPwm();
			AddSimpleMes("АСКУ","Разрыв связи с сервисом измерителя мощности");
			if(m_powerTimer)
				m_powerTimer->stop();
		}
	}

	if(m_counterAvt)
	{
		if(!m_isWorkAvt)
		{
			m_isWorkAvt = true;
			emit sigConnectedAvt();
			AddSimpleMes("АСКУ","Установлена связь с сервисом опроса ЗАО");
//			if(m_avtTimer)
//				m_avtTimer->start(10000);
		}

		m_counterAvt--;
	}
	else
	{
		if(m_isWorkAvt)
		{
			m_isWorkAvt = false;
			emit sigDisconnectedAvt();
			AddSimpleMes("АСКУ","Разрыв связи с сервисом опроса ЗАО");
//			if(m_avtTimer)
//				m_avtTimer->stop();
		}
	}

	if(m_counterGpr)
	{
		if(!m_isWorkGpr)
		{
			m_isWorkGpr = true;
			LogCtrlInfo("Control: connected other gpr");
			onConnectedGpr();
			emit sigConnectedGpr();
			AddSimpleMes("АСКУ","Установлена связь со смежным комплектом");
		}

		m_counterGpr--;
	}
	else
	{
		if(m_isWorkGpr)
		{
			m_isWorkGpr = false;
			onDisconnectedGpr();
			emit sigDisconnectedGpr();
			AddSimpleMes("АСКУ","Разрыв связи со смежным комплектом");

			if(m_mainGpr != NUM_GPR())
			{
				LogCtrlInfo("Control: disconnected other gpr");
				m_mainGpr = NUM_GPR();
				setMain(true);
			}

			if(m_changeCmd != cmdOk)
				m_changeCmd = cmdOk;
		}
	}

	if(m_initCounter)
	{
		m_initCounter++;
		if(m_initCounter > INIT_WAIT_TIMEOUT)
		{
			if(!m_isWorkGpr)
			{
				m_mainGpr = NUM_GPR();
				LogCtrlInfo("Control: начальная инициализация - режим основной");
				setMain(true);
				m_changeCmd = cmdOk;
			}
			else
			{
				m_mainGpr = NUM_OTHER_GPR();
				LogCtrlInfo("Control: начальная инициализация - режим резервный");
				setMain(false);
				m_changeCmd = cmdOk;
			}

			m_initCounter = 0;
			return;
		}
	}
}

// ----------------------------------------------------------------------------
qint32 AskuGprControl::processSyncControlGpr(quint32 id, QVariantMap sync)
{
	Q_UNUSED(id);

	qint32 result = AskuModule::CommandNotFound;

	quint32 changeCmd = sync["command"].toUInt();
	quint32 mainGpr = m_mainGprOther = sync["main"].toUInt();

	quint32 tnOsnGpr = 0;
	quint32 changed = 0;

	m_counterGpr = CONTROL_GPR_TIMEOUT;

//	qDebug("changeCmd = %d otherChangeCmd = %d   mainGpr = %d otherMainGpr = %d", m_changeCmd, changeCmd, m_mainGpr, mainGpr);

	if(m_changeCmd != cmdOk || changeCmd != cmdOk)
	{
		switch(changeCmd)
		{
			case cmdStartSwitchMain:

				if(m_mainGpr != NUM_GPR())
				{
					LogCtrlInfo("Control: cmd: перехожу в основной gpr=%d old=%d cmd=%d", mainGpr, m_mainGpr, changeCmd);
					m_mainGpr = mainGpr;
					m_changeCmd = cmdSwitchedMain;
//					m_timeToReserve = 0;
					setMain(true);
				}
				else
				{
					LogCtrlInfo("Control: cmd: хмм... комплект уже основной gpr=%d old=%d cmd=%d", mainGpr, m_mainGpr, changeCmd);
					m_mainGpr = mainGpr;
					m_changeCmd = cmdSwitchedMain;
//					m_timeToReserve = 0;
//					setMain(true);
					LogCtrlInfo("Control: операция завершена");
				}
				break;

			case cmdSwitchedMain:
			
				if(mainGpr == NUM_OTHER_GPR())
				{
					LogCtrlInfo("Control: cmd: соседний переключился в осн! Операция завершена");
					m_changeCmd = cmdOk;
				}
				else
				{
					LogCtrlInfo("Control: cmd: соседний всё ещё резервный!");
				}
				break;

			case cmdStartSwitchSlave:

				if(m_mainGpr == NUM_GPR())
				{
					LogCtrlInfo("Control: cmd: перехожу в резерв gpr=%d old=%d cmd=%d", mainGpr, m_mainGpr, changeCmd);
					m_mainGpr = NUM_OTHER_GPR();
					m_changeCmd = cmdSwitchedSlave;
					setMain(false);
				}
				else
				{
					LogCtrlInfo("Control: cmd: хмм.. комплект уже в резерве gpr=%d old=%d cmd=%d", mainGpr, m_mainGpr, changeCmd);
					m_mainGpr = NUM_OTHER_GPR();
					m_changeCmd = cmdSwitchedSlave;
//					m_changeCmd = cmdOk;
//					setMain(false);
					LogCtrlInfo("Control: операция завершена");
				}
				break;

			case cmdSwitchedSlave:

				if(m_mainGpr == NUM_OTHER_GPR())
				{
					LogCtrlInfo("Control: cmd: сосед переключился в резерв! перехожу в основной gpr=%d old=%d cmd=%d", mainGpr, m_mainGpr, changeCmd);
					m_mainGpr = mainGpr;
					m_changeCmd = cmdOk;
//					timeToReserve = 0;
					setMain(true);
					LogCtrlInfo("Control: операция завершена");
				}
				else
				{
					LogCtrlInfo("Control: cmd: сосед переключился в резерв! хмм... а комплект уже основной gpr=%d old=%d cmd=%d", mainGpr, m_mainGpr, changeCmd);
					m_mainGpr = mainGpr;
					m_changeCmd = cmdOk;
//					timeToReserve = 0;
					setMain(true);
					LogCtrlInfo("Control: операция завершена");
				}
				break;

			case cmdOk:

				if((m_changeCmd == cmdStartSwitchMain) || (m_changeCmd == cmdStartSwitchSlave))
				{
					LogCtrlInfo("Control: повтор команды");
					break;
				}
				LogCtrlInfo("Control: операция завершена");
				m_changeCmd = cmdOk;
				break;
		}
	}
	else
	{
        if(ISGPR1())
        {
            switch(m_mainGpr)
            {
                case 0: //our init
                {
                    switch(mainGpr)
                    {
                        case 0: //1 - init  2 - init
                            tnOsnGpr = 1; // set OSN
                            changed = 1;
                            break;
                        case 1: //1 - init  2 - REZ
                            tnOsnGpr = 2; // set REZ  !!!
                            changed = 1;
                            break;
                        case 2: //1 - init  2 - OSN
                            tnOsnGpr = 2; // set REZ
                            changed = 1;
                            break;
                    }
                    break;
                }
                case 1: //our OSN
                {
                    switch(mainGpr)
                    {
                        case 0: //1 - OSN  2 - init
                            tnOsnGpr = 1; // set OSN
                            break;
                        case 1: //1 - OSN  2 - REZ
                            tnOsnGpr = 1; // set OSN
                            break;
                        case 2: //1 - OSN  2 - OSN
                            tnOsnGpr = 1; // set REZ
                            break;
                    }
                    break;
                }
                case 2: //our REZ
                {
                    switch(mainGpr)
                    {
                        case 0: //1 - REZ  2 - init
                            tnOsnGpr = 1; // set OSN
                            changed = 1;
                            break;
                        case 1: //1 - REZ  2 - REZ
                            tnOsnGpr = 1; // set OSN
                            changed = 1;
                            break;
                        case 2: //1 - REZ  2 - OSN
                            tnOsnGpr = 2; // set REZ
                            break;
                    }
                    break;
                }
            }
        }
        else if(ISGPR2())
        {
            switch(m_mainGpr)
            {
                case 0: //our init
                {
                    switch(mainGpr)
                    {
                        case 0: //1 - init  2 - init
                            tnOsnGpr = 1; // set REZ
                            changed = 1;
                            break;
                        case 1: //1 - OSN  2 - init
                            tnOsnGpr = 1; // set REZ
                            changed = 1;
                            break;
                        case 2: //1 - rez  2 - init
                            tnOsnGpr = 1; // set REZ
                            changed = 1;
                            break;
                    }
                    break;
                }
                case 1: //our REZ
                {
                    switch(mainGpr)
                    {
                        case 0: //1 - init  2 - REZ
                            tnOsnGpr = 2; // set OSN !!!
                            changed = 1;
                            break;
                        case 1: //1 - OSN  2 - REZ
                            tnOsnGpr = 1; // set REZ
                            break;
                        case 2: //1 - rez  2 - REZ
                            tnOsnGpr = 1; // set REZ
                            break;
                    }
                    break;
                }
                case 2: //our OSN
                {
                    switch(mainGpr)
                    {
                        case 0: //1 - init  2 - OSN
                            tnOsnGpr = 2; // set OSN
                            break;
                        case 1: //1 - OSN  2 - OSN
                            tnOsnGpr = 1; // set REZ
                            changed = 1;
                            break;
                        case 2: //1 - REZ  2 - OSN
                            tnOsnGpr = 2; // set OSN
                            break;
                    }
                    break;
                }
            }
        }

//		qDebug("alg: changed = %d  tsosn = %d", changed, tnOsnGpr);

		if(changed && !m_initCounter)
		{
			LogCtrlInfo("Control: изменение основного по сообщению sync gpr=%d old=%d sw=%d", mainGpr, m_mainGpr, tnOsnGpr);

			m_mainGpr = tnOsnGpr;

/*			if(m_changeCmd == cmdOk)
			{
				if((tnOsnGpr == 2 && ISGPR1()) || (tnOsnGpr == 1 && ISGPR2()))
					m_changeCmd = cmdStartSwitchMain;
				else
					m_changeCmd = cmdStartSwitchSlave;
			}
*/
			setMain(m_mainGpr == NUM_GPR());
			
		}
	}

	result = AskuModule::CommandSuccess;
	return result;
}

// ----------------------------------------------------------------------------
qint32 AskuGprControl::processSyncControlSoi(quint32 id, QVariantMap sync)
{
	Q_UNUSED(id);
	Q_UNUSED(sync);

	qint32 result = AskuModule::CommandSuccess;
	m_counterSoi = CONTROL_SOI_TIMEOUT;
	return result;
}

// ----------------------------------------------------------------------------
qint32 AskuGprControl::processSyncControlRmo(quint32 id, QVariantMap sync)
{
	Q_UNUSED(id);
	Q_UNUSED(sync);

	qint32 result = AskuModule::CommandSuccess;
	if(FROM_RMO(id))
		m_counterRmo = CONTROL_RMO_TIMEOUT;
	return result;
}

// ----------------------------------------------------------------------------
qint32 AskuGprControl::processSyncControlPpv(quint32 id, QVariantMap sync)
{
	Q_UNUSED(id);
	Q_UNUSED(sync);

	qint32 result = AskuModule::CommandSuccess;
	m_counterPpv = CONTROL_PPV_TIMEOUT;
	return result;
}

// ----------------------------------------------------------------------------
qint32 AskuGprControl::processSyncControlPwm(quint32 id, QVariantMap sync)
{
	Q_UNUSED(id);
	Q_UNUSED(sync);

	qint32 result = AskuModule::CommandSuccess;
	m_counterPwm = CONTROL_PWM_TIMEOUT;
	return result;
}

// ----------------------------------------------------------------------------
qint32 AskuGprControl::processSyncControlAvt(quint32 id, QVariantMap sync)
{
	Q_UNUSED(id);
	Q_UNUSED(sync);

	qint32 result = AskuModule::CommandSuccess;
	m_counterAvt = CONTROL_AVT_TIMEOUT;
	return result;
}

// ----------------------------------------------------------------------------
qint32 AskuGprControl::processSyncControl(quint32 idGpr, quint32 idModule, QVariantMap data)
{
	qint32 result = AskuModule::CommandInvalid;

	if(data.isEmpty())
	{
		LogError("processSyncControl: empty sync data!");
		return result;
	}

	QVariantMap sync = data["Sync"].toMap();

//qDebug() << "-------------------";
//qDebug() << idGpr << idModule;

	if(FROM_LOCAL_GPR(idGpr))
	{
		if(idModule == idAskuModuleGui)
			result = processSyncControlRmo(idGpr, sync);
		else
		{
			LogCtrlError("Control: sync message from local gpr but invalid module");
			result = AskuModule::CommandInvalid;
		}
	}
	else if(FROM_OTHER_GPR(idGpr))
	{
		if(idModule == idAskuModuleSvc)
			result = processSyncControlGpr(idGpr, sync);
		else if(idModule == idAskuModuleGui)
			result = processSyncControlRmo(idGpr, sync);
		else
		{
			LogCtrlError("Control: sync message from other gpr but invalid module");
			result = AskuModule::CommandInvalid;
		}
	}
	else if(FROM_PPV(idGpr))
	{
		if(idModule == idAskuModulePwm)
			result = processSyncControlPwm(idGpr, sync);
		else if(idModule == idAskuModuleGui)
			result = processSyncControlPpv(idGpr, sync);
		else if(idModule == idAskuModuleAvt)
			result = processSyncControlAvt(idGpr, sync);
		else
		{
			LogCtrlError("Control: sync message from ppv but invalid module");
			result = AskuModule::CommandInvalid;
		}
	}
	else if(FROM_RMO(idGpr))
	{
		if(idModule == idAskuModuleGui)
			result = processSyncControlRmo(idGpr, sync);
		else
		{
			LogCtrlError("Control: sync message from rmo but invalid module");
			result = AskuModule::CommandInvalid;
		}
	}
	else if(FROM_SOI(idGpr))
	{
		if(idModule == idAskuModuleGui)
			result = processSyncControlSoi(idGpr, sync);
		else
		{
			LogCtrlError("Control: sync message from soi but invalid module");
			result = AskuModule::CommandInvalid;
		}
	}
	else
	{
		if(idModule == idAskuModuleGui)
			result = processSyncControlRmo(idGpr, sync);
		else
		{
			LogCtrlError("Control: unknown sync message");
			result = AskuModule::CommandInvalid;
		}
	}
//qDebug() << "-------------------";

	return result;
}

// ------------------------------------------------------------------
qint32 AskuGprControl::processInfo(quint32 idGpr, QVariantMap data)
{
	Q_UNUSED(idGpr);

	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("AskuGprControl: empty info data!");
		return result;
	}

	if(m_mainGpr != NUM_GPR())
	{
		QString infoType = data["InfoType"].toString();
		if(infoType == "ASKU_CONTROL")
		{
			const QVariantMap & reg = data["RegimeSet"].toMap();

			if(!reg.isEmpty())
			{
				AskuRegime new_reg = (AskuRegime)(reg["regime"].toUInt());
				if(m_regime != new_reg)
				{
					setRegime(new_reg);
				}
			}

			result = AskuModule::CommandSuccess;
		}
		else if(infoType == "ASKU_CONTROL_PANEL")
		{
			if(data.contains("CommandSet"))
			{
				QVariantMap values = data["CommandSet"].toMap();
				m_commands = values;
//				verifyCommands();
			}
	
			if(data.contains("RafStatusSet"))
			{
				QVariantMap values = data["RafStatusSet"].toMap();
//				m_rafstatus = values;
//				updateRafStatus();
			}

			if(data.contains("MessageSet"))
			{
				QVariantList valueslist = data["MessageSet"].toList();
//				m_rafMessages = valueslist;
//				updateRafMessage();
			}

			result = AskuModule::CommandSuccess;
		}
	}

	return result;
}

// ----------------------------------------------------------------------------
void AskuGprControl::start()
{
	if(m_syncTimer)
		m_syncTimer->start(500);

	QTimer::singleShot(0, this, SLOT(checkOverview()));
}

// ----------------------------------------------------------------------------
void AskuGprControl::stop()
{
	if(m_syncTimer)
		m_syncTimer->stop();
}

// ----------------------------------------------------------------------------
void AskuGprControl::prepareToQuit()
{
	if(m_isMain)
	{
		LogCtrlInfo("Control: cmd: перехожу в резерв old=%d cmd=%d", m_mainGpr, m_changeCmd);
		m_mainGpr = NUM_OTHER_GPR();
		m_changeCmd = cmdSwitchedSlave;
		setMain(false);
		makeSyncMessage();
	}
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdChangeKits()
{
	if(m_isMain && m_isWorkGpr && m_commands["resobr"] == "on")
	{
		AddSwitchMes("АСКУ", "Переключение по аварии комплекта");
		LogCtrlInfo("Control: cmd: перехожу в резерв old=%d cmd=%d", m_mainGpr, m_changeCmd);
		m_mainGpr = NUM_OTHER_GPR();
		m_changeCmd = cmdSwitchedSlave;
		setMain(false);
		makeSyncMessage();
	}
}

// ----------------------------------------------------------------------------
void AskuGprControl::setMain(bool isMain)
{
	AddSwitchMes("АСКУ", isMain ? "Режим - Основной" : "Режим - Резервный");
	LogCtrlInfo("-------------------------------------------------------------------");
	if(isMain)
	{
		LogCtrlInfo("Control: set main gpr");
	}
	else
	{
		LogCtrlInfo("Control: set slave gpr");
	}
	LogCtrlInfo("-------------------------------------------------------------------");

	m_setup.main.main = m_isMain = isMain;
	m_commands["obr"] = m_mainGpr ? QString::number(m_mainGpr) : "off";

	emit changedMain(m_isMain);
	QTimer::singleShot(0, this, SLOT(refreshControl()));
}

// ----------------------------------------------------------------------------
void AskuGprControl::setRegime(AskuRegime regime)
{
	if(m_regime != regime)
	{
		m_regime = regime;

		switch(m_regime)
		{
			case RegRaf:
				AddSwitchMes("АСКУ", "------------------ РАФ ------------------");
				m_commands["regime"] = "reg_raf";
				m_commands["ind_rgdv"] = "not";
				m_commands["ind_raf"] = "not";
				m_commands["rgdv"] = "disable";
				m_commands["raf"] = "on";
				break;

			case RegRgdv:
				AddSwitchMes("АСКУ", "------------------ РГДВ -----------------");
				m_commands["regime"] = "reg_rgdv";
				m_commands["ind_rgdv"] = "not";
				m_commands["ind_raf"] = "not";
				m_commands["rgdv"] = "on";
				m_commands["raf"] = "off";//disable
				break;

			case RegTest:
				AddSwitchMes("АСКУ", "------------------ ТЕСТ -----------------");
				m_commands["regime"] = "reg_test";
				m_commands["ind_rgdv"] = "not";
				m_commands["ind_raf"] = "not";
				m_commands["rgdv"] = "off";
				m_commands["raf"] = "off";
				break;

			case RegInit:
				AddSwitchMes("АСКУ", "------------------ ИНИТ -----------------");
				m_commands["regime"] = "reg_init";
				m_commands["ind_rgdv"] = "not";
				m_commands["ind_raf"] = "not";
				m_commands["rgdv"] = "off";
				m_commands["raf"] = "off";
				break;
		}

		QTimer::singleShot(0, this, SLOT(refreshControl()));
		emit changedRegime(m_regime);
	}
}

// ----------------------------------------------------------------------------
void AskuGprControl::setStatusRgdv(QString state, QString text)
{
	Q_UNUSED(text);
	bool changed = false;

	if(m_commands["rgdv"].toString() == "on")
	{
		if(m_commands["ind_rgdv"].toString() != state)
		{
			m_commands["ind_rgdv"] = state;
			changed = true;
		}
	}
	else
	{
		if(m_commands["ind_rgdv"].toString() != QString("not"))
		{
			m_commands["ind_rgdv"] = QString("not");
			changed = true;
		}
	}

	if(changed)
		QTimer::singleShot(0, this, SLOT(refreshControl()));
}

// ----------------------------------------------------------------------------
void AskuGprControl::setStatusRaf(QString state, QString text)
{
	Q_UNUSED(text);
	bool changed = false;

	if(m_commands["raf"].toString() == "on")
	{
		if(m_commands["ind_raf"].toString() != state)
		{
			m_commands["ind_raf"] = state;
			changed = true;
		}
	}
	else
	{
		if(m_commands["ind_raf"].toString() != QString("not"))
		{
			m_commands["ind_raf"] = QString("not");
			changed = true;
		}
	}

	if(changed)
		QTimer::singleShot(0, this, SLOT(refreshControl()));
}

// ----------------------------------------------------------------------------
