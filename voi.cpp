#include "../common/logger.h"
#include "../common/module.h"
#include "voi.h"

// ------------------------------------------------------------------
VOI::VOI(QObject * parent) : VOI_THREAD(parent)
{
	qRegisterMetaType<AskuSektorTable>("AskuSektorTable");
}

// ------------------------------------------------------------------
VOI::~VOI()
{
}

// ------------------------------------------------------------------
void VOI::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
void VOI::onConnectedGpr()
{
	emit sigConnectedGpr();
}

// ------------------------------------------------------------------
void VOI::onDisconnectedGpr()
{
	emit sigDisconnectedGpr();
}

// ------------------------------------------------------------------
qint32 VOI::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogVoiError("VOI: empty command data!");
		return result;
	}
	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogVoiError("VOI: empty command");
		return result;
	}

	LogVoiInfo("Command: %s", qPrintable(command));
/*
	if(command == "refreshVoi")
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
*/
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
qint32 VOI::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogVoiError("VOI: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();

	if(infoType == "VOI_SLAVE_SYNC")
	{

		if(data.contains("Config") || data.contains("State"))
		{
			QVariantMap config = data["Config"].toMap();
			QVariantMap state  = data["State"].toMap();
			emit sigOnSyncToSlave(config, state);
		}

		result = AskuModule::CommandSuccess;
	}

	return result;
}

// ------------------------------------------------------------------
void VOI::syncToSlave(QVariantMap config, QVariantMap state)
{
	LogVoiInfo("VOI::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "VOI_SLAVE_SYNC";
	data["ModuleTo"] = "voi";
	data["ModuleFrom"] = "voi";
	data["GprId"] = IDGPR();
	if(!config.isEmpty())
		data["Config"] = config;
	if(!state.isEmpty())
		data["State"] = state;

//	qDebug() << "syncToSlave";
//	qDebug() << config;
//	qDebug() << state;
//	qDebug() << "-----------";

	emit sendInfoMessage(data, idAskuModuleSvc);
}

// ------------------------------------------------------------------
