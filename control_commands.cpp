#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "control.h"
#include "viewer.h"

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetMainObr(quint32 setObr, bool oper)
{
	if(setObr == 1)
		AddSwitchMes(oper ? "Оператор" : "АСКУ", "Назначение основным комплекта Обработка-I");
	if(setObr == 2)
		AddSwitchMes(oper ? "Оператор" : "АСКУ", "Назначение основным комплекта Обработка-II");

	if(m_changeCmd != cmdOk)
	{
		LogCtrlInfo("Control: операция не завершена - переключить нельзя!");
		return;
	}

	if(m_mainGpr == NUM_GPR())
	{
		if(setObr == NUM_GPR())
		{
			LogCtrlInfo("Control: хмм. комплект уже основной!");
		}
		else
		{
			if(!m_isWorkGpr)
			{
				LogCtrlInfo("Control: сосед не отвечает - переключить нельзя!");
			}
			else
			{
				m_changeCmd = cmdStartSwitchMain;
				m_mainGpr = NUM_OTHER_GPR();
				LogCtrlInfo("Control: ушел в резерв, послал команду на другой комплект стать основным gpr=%d cmd=%d", m_mainGpr, m_changeCmd);
				setMain(false);
			}
		}
	}
	else
	{
		if(setObr == NUM_GPR())
		{
			if(m_isWorkGpr)
			{
//				LogCtrlInfo("Control: послал команду стать резерв gpr=%d cmd=%d", m_mainGpr, m_changeCmd);
//				m_changeCmd = cmdStartSwitchSlave;
			}
			else
			{
				LogCtrlInfo("Control: сосед не отвечает - становлюсь основным!");
				m_changeCmd = cmdOk;
				m_mainGpr = NUM_GPR();
				setMain(true);
			}
		}
	}
}
/*
// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetKits1On(bool oper)
{
	cmdSetMainObr(1, oper);
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetKits2On(bool oper)
{
	cmdSetMainObr(2, oper);
}
*/
// ----------------------------------------------------------------------------
qint32 AskuGprControl::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("GprControl: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogError("GprControl: empty command");
		return result;
	}

	LogInfo("Command: %s", qPrintable(command));

	if(command == "version")
	{
		QTimer::singleShot(0, this, SLOT(refreshVersion()));
		result = AskuModule::CommandSuccess;
	}
	else if(command == "refreshControl")
	{
		QTimer::singleShot(0, this, SLOT(refreshControl()));
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setTest")
	{
		cmdSetTest(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setRgdv")
	{
		cmdSetRgdv(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setRaf")
	{
		cmdSetRaf(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setRgdvOff")
	{
		cmdSetTest(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setRgdvOn")
	{
		cmdSetRgdv(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setRafOff")
	{
		cmdSetRafOff(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setRafOn")
	{
		cmdSetRafOn(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "monitorModule")
	{
		if(parameters.count() == 0)
		{
			emit setMonitorModule(0, 0);
			result = AskuModule::CommandSuccess;
		}
		else if(parameters.count() == 2)
		{
			bool ok1 = false, ok2 = false;
			quint32 value1 = parameters[0].toUInt(&ok1,10);
			quint32 value2 = parameters[1].toUInt(&ok2,10);

			if(ok1 && ok2)
			{
				emit setMonitorModule(value1, value2);
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
	else if(command == "resetAvarPrd1")
	{
		cmdSetResetAvarPrd1(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "resetAvarPrd2")
	{
		cmdSetResetAvarPrd2(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "resetAvarPrm")
	{
		cmdSetResetAvarPrm(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "resetAvarBep")
	{
		cmdSetResetAvarBep(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "resetAvarSvo")
	{
		cmdSetResetAvarSvo(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "resetAvarComm")
	{
		cmdSetResetAvarComm(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setObr1")
	{
		cmdSetMainObr(1, true);
		makeControlPanelMessage();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setObr2")
	{
		cmdSetMainObr(2, true);
		makeControlPanelMessage();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setObrResOff")
	{
		cmdSetObrResOff(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setObrResOn")
	{
		cmdSetObrResOn(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setAzimuth1")
	{
		cmdSetAzimuth1(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setAzimuth2")
	{
		cmdSetAzimuth2(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setOverview1")
	{
		cmdSetOverview1(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setOverview2")
	{
		cmdSetOverview2(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setBepOff")
	{
		cmdSetBepOff(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setBepOn")
	{
		cmdSetBepOn(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setBep1On")
	{
		cmdSetBep1On(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setBep2On")
	{
		cmdSetBep2On(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrdOff")
	{
		cmdSetPrdOff(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrdOn")
	{
		cmdSetPrdOn(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrd1Off")
	{
		cmdSetPrd1Off(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrd1On")
	{
		cmdSetPrd1On(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrd2Off")
	{
		cmdSetPrd2Off(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrd2On")
	{
		cmdSetPrd2On(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPumi1")
	{
		cmdSetPumi1(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPumiOff")
	{
		cmdSetPumiOff(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPumi2")
	{
		cmdSetPumi2(true);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setVrl1")
	{
		cmdSetVrl1();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setVrlOff")
	{
		cmdSetVrlOff();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setVrl2")
	{
		cmdSetVrl2();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setVrlResOff")
	{
		cmdSetVrlResOff();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setVrlResOn")
	{
		cmdSetVrlResOn();
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
void AskuGprControl::refreshVersion()
{
	makeVersionMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::refreshControl()
{
	if(m_mainGpr == NUM_GPR())
	{
		makeMessage();
		makeControlPanelMessage();
		makeRafOnOffMessage();
		emit needRefreshAll();
	}
}

// ----------------------------------------------------------------------------
void AskuGprControl::refreshPanel()
{
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::checkOverview()
{
	if(m_setup.module.lastMode == 1)
		cmdSetOverview2();
	else
		cmdSetOverview1();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetRaf(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Команда: Режим - РАФ");
	setRegime(RegRaf);
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetRgdv(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Команда: Режим - РГДВ");
	setRegime(RegRgdv);
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetTest(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Команда: Режим - ТЕСТ");
	setRegime(RegTest);
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetRafOff(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Отключение режима РАФ");

	m_OnOffRafStatus = -1;
	m_OnOffRafCounter = 0;
	m_OnOffRafCounterFinish = m_timeOff["finish"].time * m_OnOffRafMultiplier;
	m_timeOff.setStatus("on");
	m_rafMessages.clear();
	m_rafMessagesUpdated = QDateTime::currentDateTime();
	m_onOffTimer->start(100);
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetRafOn(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение режима РАФ");

	m_OnOffRafStatus = 1;
	m_OnOffRafCounter = 0;
	m_OnOffRafCounterFinish = m_timeOn["finish"].time * m_OnOffRafMultiplier;
	m_timeOn.setStatus("off");
	m_rafMessages.clear();
	m_rafMessagesUpdated = QDateTime::currentDateTime();
	m_onOffTimer->start(100);
}

// ----------------------------------------------------------------------------
void AskuGprControl::onTimeMeasurePower()
{
	emit cmdMeasurePower();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetBep1On(bool oper, bool no_howl)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение БЭП 1");

//	if(m_commands["drive"] == "off")
	if(m_commands["bep"] == "off")
	{
		if(!no_howl)
		{
			emit setHowl1On();
			emit setHowl2On();
		}

		if(m_BepStartTimer)
			m_BepStartTimer->start(!no_howl ? 30000 : 0);
	}
//	else if(m_commands["drive"] == "2")
//	{
//	}
	else
	{
//		emit setBep1On();
		emit setBepOn();
	}

//	m_commands["drive"] = "1";
	m_commands["bep"] = "on";
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetBep2On(bool oper, bool no_howl)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение БЭП 2");

//	if(m_commands["drive"] == "off")
	if(m_commands["bep"] == "off")
	{
		if(!no_howl)
		{
			emit setHowl1On();
			emit setHowl2On();
		}

		if(m_BepStartTimer)
			m_BepStartTimer->start(!no_howl ? 30000 : 0);
	}
//	else if(m_commands["drive"] == "1")
//	{
//	}
	else
	{
//		emit setBep2On();
		emit setBepOn();
	}

//	m_commands["drive"] = "2";
	m_commands["on"] = "on";
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetBepOn(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение БЭП");

	emit setHowl1On();
	emit setHowl2On();

	if(m_BepStartTimer)
		m_BepStartTimer->start(30000);

	m_commands["bep"] = "on";
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::onTimeBepStart()
{
//	AddSwitchMes("АСКУ", "Включение БЭП (команда)");

//	if(m_commands["drive"] == 1)
//		emit setBep1On();
//	else if(m_commands["drive"] == 2)
//		emit setBep2On();

	if(m_commands["bep"] == "on")
		emit setBepOn();

	emit setHowl1Off();
	emit setHowl2Off();

	if(m_BepStartTimer)
		m_BepStartTimer->stop();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetBepOff(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Отключение БЭП");

	emit setHowl1Off();
	emit setHowl2Off();
	emit setBepOff();

	if(m_BepStartTimer)
		m_BepStartTimer->stop();

	m_commands["bep"] = "off";
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetResetAvarPrd1(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Сброс аварии ПРД1");
	emit setResetAvarPrd1();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetResetAvarPrd2(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Сброс аварии ПРД2");
	emit setResetAvarPrd2();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetResetAvarPrm(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Сброс аварии ПРМ");
	emit setResetAvarPrm();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetResetAvarBep(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Сброс аварии БЭП");
	emit setResetAvarBep();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetResetAvarSvo(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Сброс аварии СВО");
	emit setResetAvarSvo();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetResetAvarComm(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Сброс аварии ОБЩ");
	emit setResetAvarComm();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetPrdOff(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Отключение УМИ");

	m_commands["prd"] = "off";

	m_commands["prd1"] = "off";
	emit setPrd1Off();
	emit setSvo1Off();
	m_commands["prd2"] = "off";
	emit setPrd2Off();
	emit setSvo2Off();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetPrdOn(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение УМИ");

	m_commands["prd"] = "on";

	m_commands["prd1"] = "on";
	emit setPrd1On();
	emit setSvo1On();
	m_commands["prd2"] = "on";
	emit setPrd2On();
	emit setSvo2On();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetPrd1Off(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Отключение ПРД1");

	m_commands["prd1"] = "off";
	emit setPrd1Off();
	emit setSvo1Off();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetPrd1On(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение ПРД1");

	m_commands["prd1"] = "on";
	emit setPrd1On();
	emit setSvo1On();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetPrd2Off(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Отключение ПРД2");

	m_commands["prd2"] = "off";
	emit setPrd2Off();
	emit setSvo2Off();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetPrd2On(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение ПРД2");

	m_commands["prd2"] = "on";
	emit setPrd2On();
	emit setSvo2On();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetPumiOff(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Отключение ПУМ");

	m_commands["pumi"] = "off";
	emit setPumiOff();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetPumi1(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение ПУМ-I");

	m_commands["pumi"] = "1";
	emit setPumi1();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetPumi2(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение ПУМ-II");

	m_commands["pumi"] = "2";
	emit setPumi2();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetAzimuth1(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Назначение основным азимутального датчика I");

	m_commands["azsens"] = "1";
	emit setAzimuthSource(0);
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetAzimuth2(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Назначение основным азимутального датчика II");

	m_commands["azsens"] = "2";
	emit setAzimuthSource(1);
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetOverview1(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Назначение режима обзора I");

	m_commands["overview"] = "1";
	m_setup.module.lastMode = 0;
	emit setOverview(0);
	makeControlPanelMessage();
	emit sigFlushSettings();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetOverview2(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Назначение режима обзора II");

	m_commands["overview"] = "2";
	m_setup.module.lastMode = 1;
	emit setOverview(1);
	makeControlPanelMessage();
	emit sigFlushSettings();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetObrResOff(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Отключено автоматическое резервирование комплектов");

	m_commands["resobr"] = "off";
	emit setObrResOff();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetObrResOn(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включено автоматическое резервирование комплектов");

	m_commands["resobr"] = "on";
	emit setObrResOn();
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetVrl1(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Назначение основновным Обработка-I МВРЛ-К Н");

	m_commands["vrl"] = "1";
//	emit setVrl1();
	emit setMainVrl(1);
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetVrlOff(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Назначение резервным Обработка-I,II МВРЛ-К Н");

	m_commands["vrl"] = "off";
//	emit setVrlOff();
	emit setMainVrl(0);
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetVrl2(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Назначение основновным Обработка-II МВРЛ-К Н");

	m_commands["vrl"] = "2";
//	emit setVrl2();
	emit setMainVrl(2);
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetVrlResOff(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Отключено автоматическое резервирование Обработки МВРЛ-К Н");

	m_commands["resvrl"] = "off";
//	emit setVrlResOff();
	emit setReconfVrl(true);
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::cmdSetVrlResOn(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включено автоматическое резервирование Обработки МВРЛ-К Н");

	m_commands["resvrl"] = "on";
//	emit setVrlResOn();
	emit setReconfVrl(false);
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::onControlKvit(AskuBinStateSet kvit)
{
	m_kvit = kvit;

	if(m_regime == RegRgdv)
		setStatusRgdv(m_kvit["status_rgdv"]);

	if(m_regime == RegRaf)
		setStatusRaf(m_kvit["status_raf"]);
}

// ----------------------------------------------------------------------------
void AskuGprControl::onButtonDrive(quint32 drive)
{
	m_commands["bep"] = (drive == 1 || drive == 2) ? QString::number(drive) : "off";
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::onButtonPum(quint32 pum)
{
	m_commands["pumi"] = (pum == 1 || pum == 2) ? QString::number(pum) : "off";
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::onButtonPrd(bool on)
{
	m_commands["prd"] = on ? "on" : "off";
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::onButtonPrd1(bool on)
{
	m_commands["prd1"] = on ? "on" : "off";
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
void AskuGprControl::onButtonPrd2(bool on)
{
	m_commands["prd2"] = on ? "on" : "off";
	makeControlPanelMessage();
}

// ----------------------------------------------------------------------------
