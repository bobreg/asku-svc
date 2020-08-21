#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "vrl.h"

// ------------------------------------------------------------------
VRL::VRL(QObject * parent) : VRL_THREAD(parent)
{
}

// ------------------------------------------------------------------
VRL::~VRL()
{
}

// ------------------------------------------------------------------
void VRL::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
void VRL::onConnectedGpr()
{
	emit sigConnectedGpr();
}

// ------------------------------------------------------------------
void VRL::onDisconnectedGpr()
{
	emit sigDisconnectedGpr();
}

// ------------------------------------------------------------------
void VRL::cmdSetMainVRL(quint32 n_vrl)
{
	emit sigSetMainVRL(n_vrl);
}

// ------------------------------------------------------------------
void VRL::cmdSetDisableReconfVRL(bool on)
{
	emit sigSetDisableReconf(on);
}

// ------------------------------------------------------------------
void VRL::cmdDisableTotal(bool on)
{
	emit sigSetDisableTotal(on);
}

// ------------------------------------------------------------------
void VRL::cmdDisableDynamic(AskuSektorTable data)
{
	Q_UNUSED(data);
}

// ------------------------------------------------------------------
qint32 VRL::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogVrlError("VRL: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogVrlError("VRL: empty command");
		return result;
	}

	LogVrlInfo("Command: %s", qPrintable(command));

	if(command == "refreshVrl")
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
qint32 VRL::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogVrlError("VRL: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();

	if(infoType == "VRL_SLAVE_SYNC")
	{
		if(data.contains("Config") || data.contains("State") || data.contains("Koeff"))
		{
			QVariantMap config = data["Config"].toMap();
			QVariantMap state  = data["State"].toMap();
			QVariantMap koeff  = data["Koeff"].toMap();
			emit sigOnSyncToSlave(config, state, koeff);
		}

		result = AskuModule::CommandSuccess;
	}

	return result;
}

// ------------------------------------------------------------------
void VRL::refreshState(QVariantMap info)
{
	QVariantMap data;
	data["InfoType"] = "VRL_INFO";
	data["ModuleTo"] = "dialog_vrl";
	data["ModuleFrom"] = "vrl";
	data["GprId"] = IDGPR();
	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void VRL::syncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff)
{
	LogVrlInfo("VRL::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "VRL_SLAVE_SYNC";
	data["ModuleTo"] = "vrl";
	data["ModuleFrom"] = "vrl";
	data["GprId"] = IDGPR();
	if(!config.isEmpty())
		data["Config"] = config;
	if(!state.isEmpty())
		data["State"] = state;
	if(!koeff.isEmpty())
		data["Koeff"] = koeff;

	emit sendInfoMessage(data, idAskuModuleSvc);
}

// ------------------------------------------------------------------
