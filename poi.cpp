#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "poi.h"

// ------------------------------------------------------------------
POI::POI(QObject * parent) : POI_THREAD(parent)
{
}

// ------------------------------------------------------------------
POI::~POI()
{
}

// ------------------------------------------------------------------
void POI::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
void POI::onResetKoeff()
{
	emit sigResetKoeff();
}

// ------------------------------------------------------------------
void POI::onConnectedGpr()
{
	emit sigConnectedGpr();
}

// ------------------------------------------------------------------
void POI::onDisconnectedGpr()
{
	emit sigDisconnectedGpr();
}

// ------------------------------------------------------------------
qint32 POI::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogPoiError("POI: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogPoiError("POI: empty command");
		return result;
	}

	LogPoiInfo("Command: %s", qPrintable(command));

	if(command == "refreshPoi")
	{
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "startMonitor")
	{
//		emit sigStartMonitor();
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "stopMonitor")
	{
//		emit sigStopMonitor();
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
qint32 POI::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogPoiError("POI: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();

	if(infoType == "POI_SLAVE_SYNC")
	{
		if(data.contains("Config") || data.contains("State") || data.contains("Koeff") || data.contains("Pilot"))
		{
			QVariantMap config = data["Config"].toMap();
			QVariantMap state  = data["State"].toMap();
			QVariantMap koeff  = data["Koeff"].toMap();
			QVariantMap pilot  = data["Pilot"].toMap();
			emit sigOnSyncToSlave(config, state, koeff, pilot);
		}

		result = AskuModule::CommandSuccess;
	}

	return result;
}

// ------------------------------------------------------------------
void POI::syncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff, QVariantMap pilot)
{
	LogPoiInfo("POI::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "POI_SLAVE_SYNC";
	data["ModuleTo"] = "poi";
	data["ModuleFrom"] = "poi";
	data["GprId"] = IDGPR();
	if(!config.isEmpty())
		data["Config"] = config;
	if(!state.isEmpty())
		data["State"] = state;
	if(!koeff.isEmpty())
		data["Koeff"] = koeff;
	if(!pilot.isEmpty())
		data["Pilot"] = pilot;

	emit sendInfoMessage(data, idAskuModuleSvc);
}

// ------------------------------------------------------------------
