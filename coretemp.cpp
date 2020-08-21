#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "coretemp.h"

// ------------------------------------------------------------------
CORETEMP::CORETEMP(QObject * parent) : CORETEMP_THREAD(parent)
{
}

// ------------------------------------------------------------------
CORETEMP::~CORETEMP()
{
}

// ------------------------------------------------------------------
void CORETEMP::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
void CORETEMP::onConnectedGpr()
{
	emit sigConnectedGpr();
}

// ------------------------------------------------------------------
void CORETEMP::onDisconnectedGpr()
{
	emit sigDisconnectedGpr();
}

// ------------------------------------------------------------------
qint32 CORETEMP::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogCoreError("CORETEMP: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogCoreError("CORETEMP: empty command");
		return result;
	}

	LogCoreInfo("Command: %s", qPrintable(command));

	if(command == "refreshCoreTemp")
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
qint32 CORETEMP::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogCoreError("CORETEMP: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();
	if(infoType == "CORETEMP_SLAVE_SYNC")
	{
		if(data.contains("Config") || data.contains("State") || data.contains("Measure"))
		{
			QVariantMap config = data["Config"].toMap();
			QVariantMap state = data["State"].toMap();
			QVariantMap measure = data["Measure"].toMap();
			emit sigOnSyncToSlave(config, state, measure);
		}

		result = AskuModule::CommandSuccess;
	}

	return result;
}

// ------------------------------------------------------------------
void CORETEMP::refreshState(QVariantMap info)
{
	Q_UNUSED(info);
/*	QVariantMap data;
	data["InfoType"] = "CORETEMP_INFO";
	data["ModuleTo"] = "dialog_CORETEMP";
	data["ModuleFrom"] = "CORETEMP";
	data["GprId"] = IDGPR();
	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);*/
}

// ------------------------------------------------------------------
void CORETEMP::syncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure)
{
	LogCoreInfo("CORETEMP::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "CORETEMP_SLAVE_SYNC";
	data["ModuleTo"] = "coretemp";
	data["ModuleFrom"] = "coretemp";
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
