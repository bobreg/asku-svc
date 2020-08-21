#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "des.h"

// ------------------------------------------------------------------
DES::DES(QObject * parent) : DES_THREAD(parent)
{
}

// ------------------------------------------------------------------
DES::~DES()
{
}

// ------------------------------------------------------------------
void DES::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
qint32 DES::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("DES: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogError("DES: empty command");
		return result;
	}

	LogInfo("Command: %s", qPrintable(command));

	if(command == "refreshDes")
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
	if(command == "setEngine1Off")
	{
		emit sigSetEngine(0, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setEngine1On")
	{
		emit sigSetEngine(0, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setEngine2Off")
	{
		emit sigSetEngine(1, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setEngine2On")
	{
		emit sigSetEngine(1, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setEngine3Off")
	{
		emit sigSetEngine(2, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setEngine3On")
	{
		emit sigSetEngine(2, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setEngine4Off")
	{
		emit sigSetEngine(3, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setEngine4On")
	{
		emit sigSetEngine(3, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setGB1Off")
	{
		emit sigSetPosGB(0, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setGB1On")
	{
		emit sigSetPosGB(0, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setGB2Off")
	{
		emit sigSetPosGB(1, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setGB2On")
	{
		emit sigSetPosGB(1, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setGB3Off")
	{
		emit sigSetPosGB(2, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setGB3On")
	{
		emit sigSetPosGB(2, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setGB4Off")
	{
		emit sigSetPosGB(3, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setGB4On")
	{
		emit sigSetPosGB(3, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setMB1Off")
	{
		emit sigSetPosMB(0, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setMB1On")
	{
		emit sigSetPosMB(0, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setMB2Off")
	{
		emit sigSetPosMB(1, false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setMB2On")
	{
		emit sigSetPosMB(1, true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "resetMains1")
	{
		emit sigSetMainsReset(0);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "resetMains2")
	{
		emit sigSetMainsReset(1);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "resetDg1")
	{
		emit sigSetDgReset(0);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "resetDg2")
	{
		emit sigSetDgReset(1);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "resetDg3")
	{
		emit sigSetDgReset(2);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "resetDg4")
	{
		emit sigSetDgReset(3);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setAutoMode")
	{
		emit sigSetMainsMode(0, 0);
		emit sigSetMainsMode(1, 0);
		emit sigSetDgMode(0, 0);
		emit sigSetDgMode(1, 0);
		emit sigSetDgMode(2, 0);
		emit sigSetDgMode(3, 0);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setSemiAutoMode")
	{
		emit sigSetMainsMode(0, 1);
		emit sigSetMainsMode(1, 1);
		emit sigSetDgMode(0, 1);
		emit sigSetDgMode(1, 1);
		emit sigSetDgMode(2, 1);
		emit sigSetDgMode(3, 1);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setTestMode")
	{
		emit sigSetMainsMode(0, 2);
		emit sigSetMainsMode(1, 2);
		emit sigSetDgMode(0, 2);
		emit sigSetDgMode(1, 2);
		emit sigSetDgMode(2, 2);
		emit sigSetDgMode(3, 2);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setManualMode")
	{
		emit sigSetMainsMode(0, 3);
		emit sigSetMainsMode(1, 3);
		emit sigSetDgMode(0, 3);
		emit sigSetDgMode(1, 3);
		emit sigSetDgMode(2, 3);
		emit sigSetDgMode(3, 3);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setBlockMode")
	{
		emit sigSetMainsMode(0, 4);
		emit sigSetMainsMode(1, 4);
		emit sigSetDgMode(0, 4);
		emit sigSetDgMode(1, 4);
		emit sigSetDgMode(2, 4);
		emit sigSetDgMode(3, 4);
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
qint32 DES::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("DES: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();
	if(infoType == "DES_SLAVE_SYNC")
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
void DES::refreshState(QVariantMap info)
{
	QVariantMap data;
	data["InfoType"] = "DES_INFO";
	data["ModuleTo"] = "dialog_deses";
	data["ModuleFrom"] = "des";
	data["GprId"] = IDGPR();
	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DES::syncToSlave(QVariantMap config)
{
	LogInfo("DES::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "DES_SLAVE_SYNC";
	data["ModuleTo"] = "des";
	data["ModuleFrom"] = "des";
	data["GprId"] = IDGPR();
	data["Config"] = config;

	emit sendInfoMessage(data, idAskuModuleSvc);
}

// ------------------------------------------------------------------
