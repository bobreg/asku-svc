#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "coolers.h"
#include "viewer.h"

// ------------------------------------------------------------------
COOLERS::COOLERS(QObject * parent) : COOLERS_THREAD(parent)
{
}

// ------------------------------------------------------------------
COOLERS::~COOLERS()
{
}

// ------------------------------------------------------------------
void COOLERS::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
void COOLERS::onSetTemperature(quint32 n_cooler, bool on, double temperature)
{
	emit sigSetTemperature(n_cooler, on, temperature);
}

// ------------------------------------------------------------------
void COOLERS::onSetExtTemperature(double temperature)
{
	emit sigSetExtTemperature(temperature);
}

// ------------------------------------------------------------------
void COOLERS::onSetReset()
{
	emit sigSetReset();
}

// ------------------------------------------------------------------
void COOLERS::cmdSetSvo1On(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение СВО1");
	onSetOn(0, true);
}

// ------------------------------------------------------------------
void COOLERS::cmdSetSvo2On(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Включение СВО2");
	onSetOn(1, true);
}

// ------------------------------------------------------------------
void COOLERS::cmdSetSvo1Off(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Отключение СВО1");
	onSetOn(0, false);
}

// ------------------------------------------------------------------
void COOLERS::cmdSetSvo2Off(bool oper)
{
	AddSwitchMes(oper ? "Оператор" : "АСКУ", "Отключение СВО2");
	onSetOn(1, false);
}

// ------------------------------------------------------------------
void COOLERS::onSetOn(quint32 n_prd, bool on)
{
	if(n_prd == 0)
	{
		emit sigSetOn(0, on);
		emit sigSetOn(1, on);

		emit sigSetFreq(0, m_setup.coolers.frequency);
		emit sigSetFreq(1, m_setup.coolers.frequency);
	}
	if(n_prd == 1)
	{
		emit sigSetOn(2, on);
		emit sigSetOn(3, on);

		emit sigSetFreq(2, m_setup.coolers.frequency);
		emit sigSetFreq(3, m_setup.coolers.frequency);
	}

	emit sigRefreshState();
}

// ------------------------------------------------------------------
qint32 COOLERS::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("COOLERS: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogError("COOLERS: empty command");
		return result;
	}

	LogInfo("Command: %s", qPrintable(command));

	if(command == "refreshCoolers")
	{
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "startMonitor")
	{
		emit sigStartMonitor();
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "stopMonitor")
	{
		emit sigStopMonitor();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setAvtoSvo")
	{
		emit sigSetManual(false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setManualSvo")
	{
		emit sigSetManual(true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "resetSvo")
	{
		emit sigSetReset();
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setFreqSvo")
	{
		if(parameters.count() == 2)
		{
			bool ok1 = false, ok2 = false;
			double freq1 = parameters[0].toDouble(&ok1);
			double freq2 = parameters[1].toDouble(&ok2);

			if(ok1 && ok2)
			{
				emit sigSetFreq(0, freq1);
				emit sigSetFreq(1, freq1);
				emit sigSetFreq(2, freq2);
				emit sigSetFreq(3, freq2);
				emit sigRefreshState();
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
	if(command == "setSvo1On")
	{
		emit sigSetOn(0, true);
		emit sigSetOn(1, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setSvo1Off")
	{
		emit sigSetOn(0, false);
		emit sigSetOn(1, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setSvo2On")
	{
		emit sigSetOn(2, true);
		emit sigSetOn(3, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setSvo2Off")
	{
		emit sigSetOn(2, false);
		emit sigSetOn(3, false);
		emit sigRefreshState();
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

// ------------------------------------------------------------------
qint32 COOLERS::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("COOLERS: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();
	if(infoType == "COOLERS_SLAVE_SYNC")
	{
		if(data.contains("Config"))
		{
			QVariantMap values = data["Config"].toMap();
			emit sigOnSyncToSlave(values);
		}

		result = AskuModule::CommandSuccess;
	}

	return result;
}

// ------------------------------------------------------------------
void COOLERS::refreshState(QVariantMap info)
{
	QVariantMap data;
	data["InfoType"] = "COOLERS_INFO";
	data["ModuleTo"] = "dialog_coolers";
	data["ModuleFrom"] = "coolers";
	data["GprId"] = IDGPR();
	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void COOLERS::syncToSlave(QVariantMap config)
{
	LogInfo("COOLERS::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "COOLERS_SLAVE_SYNC";
	data["ModuleTo"] = "coolers";
	data["ModuleFrom"] = "coolers";
	data["GprId"] = IDGPR();
	data["Config"] = config;

	emit sendInfoMessage(data, idAskuModuleSvc);
}

// ------------------------------------------------------------------
