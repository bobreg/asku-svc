#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "ups.h"

// ------------------------------------------------------------------
UPS::UPS(QObject * parent) : UPS_THREAD(parent)
{
}

// ------------------------------------------------------------------
UPS::~UPS()
{
}

// ------------------------------------------------------------------
void UPS::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
void UPS::onConnectedGpr()
{
	emit sigConnectedGpr();
}

// ------------------------------------------------------------------
void UPS::onDisconnectedGpr()
{
	emit sigDisconnectedGpr();
}

// ------------------------------------------------------------------
qint32 UPS::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogUpsError("UPS: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogUpsError("UPS: empty command");
		return result;
	}

	LogUpsInfo("Command: %s", qPrintable(command));

	if(command == "refreshUps")
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
qint32 UPS::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogUpsError("UPS: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();
	if(infoType == "UPS_SLAVE_SYNC")
	{
		if(data.contains("Config") || data.contains("State") || data.contains("Measure"))
		{
			QVariantMap config  = data["Config"].toMap();
			QVariantMap state   = data["State"].toMap();
			QVariantMap measure = data["Measure"].toMap();
			emit sigOnSyncToSlave(config, state, measure);
		}

		result = AskuModule::CommandSuccess;
	}

	return result;
}

// ------------------------------------------------------------------
void UPS::refreshState(QVariantMap info)
{
	QVariantMap data;
	data["InfoType"] = "UPS_INFO";
	data["ModuleTo"] = "dialog_upses";
	data["ModuleFrom"] = "ups";
	data["GprId"] = IDGPR();
	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void UPS::syncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure)
{
	LogUpsInfo("UPS::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "UPS_SLAVE_SYNC";
	data["ModuleTo"] = "ups";
	data["ModuleFrom"] = "ups";
	data["GprId"] = IDGPR();
	if(!config.isEmpty())
		data["Config"] = config;
	if(!state.isEmpty())
		data["State"] = state;
	if(!measure.isEmpty())
		data["Measure"] = measure;

	emit sendInfoMessage(data, idAskuModuleSvc);
}

// ------------------------------------------------------------------
