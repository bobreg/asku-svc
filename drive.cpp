#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "drive.h"

// ------------------------------------------------------------------
DRIVE::DRIVE(QObject * parent) : DRIVE_THREAD(parent)
{
}

// ------------------------------------------------------------------
DRIVE::~DRIVE()
{
}

// ------------------------------------------------------------------
void DRIVE::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
void DRIVE::onConnectedGpr()
{
	emit sigConnectedGpr();
}

// ------------------------------------------------------------------
void DRIVE::onDisconnectedGpr()
{
	emit sigDisconnectedGpr();
}

// ------------------------------------------------------------------
void DRIVE::onSetServo(quint32 n_drive)
{
	emit sigSetServo(n_drive);
}

// ------------------------------------------------------------------
void DRIVE::onSetOverride(quint32 n_drive)
{
	emit sigSetOverride(n_drive);
}

// ------------------------------------------------------------------
void DRIVE::onSetSpeed(double speed)
{
	emit sigSetSpeed(speed);
}

// ------------------------------------------------------------------
void DRIVE::onSetReset()
{
	emit sigSetReset();
}

// ------------------------------------------------------------------
void DRIVE::onSetServoOn()
{
	LogDriveInfo("DRIVE::Set Start Speed %3.1f", m_setup.module.lastMode == 1 ? m_setup.drive.speed2 : m_setup.drive.speed1);
	emit sigSetSpeed(m_setup.module.lastMode == 1 ? m_setup.drive.speed2 : m_setup.drive.speed1);
	emit sigSetServo(true);
}

// ------------------------------------------------------------------
void DRIVE::onSetServo1On()
{
	LogDriveInfo("DRIVE::Set Start 1 Speed %3.1f", m_setup.module.lastMode == 1 ? m_setup.drive.speed2 : m_setup.drive.speed1);
	emit sigSetSpeed(m_setup.module.lastMode == 1 ? m_setup.drive.speed2 : m_setup.drive.speed1);
//	emit sigSetServo(DRIVE_CMD_ON_1);
	emit sigSetServo(true);
}

// ------------------------------------------------------------------
void DRIVE::onSetServo2On()
{
	LogDriveInfo("DRIVE::Set Start 2 Speed %3.1f", m_setup.module.lastMode == 1 ? m_setup.drive.speed2 : m_setup.drive.speed1);
	emit sigSetSpeed(m_setup.module.lastMode == 1 ? m_setup.drive.speed2 : m_setup.drive.speed1);
//	emit sigSetServo(DRIVE_CMD_ON_2);
	emit sigSetServo(true);
}

// ------------------------------------------------------------------
void DRIVE::onSetServoOff()
{
	emit sigSetServo(false);
}

// ------------------------------------------------------------------
void DRIVE::onSetOverview(quint32 mode)
{
	LogDriveInfo("DRIVE::Set Overview Speed %3.1f", mode == 1 ? m_setup.drive.speed2 : m_setup.drive.speed1);
	emit sigSetSpeed(mode == 1 ? m_setup.drive.speed2 : m_setup.drive.speed1);
	emit sigRefreshState();
}

// ------------------------------------------------------------------
qint32 DRIVE::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogDriveError("DRIVE: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogDriveError("DRIVE: empty command");
		return result;
	}

	LogDriveInfo("Command: %s", qPrintable(command));

	if(command == "refreshDrive")
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
	if(command == "resetDrive")
	{
		emit sigSetReset();
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setAvtoDrive")
	{
		emit sigSetManual(false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setManualDrive")
	{
		emit sigSetManual(true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setDriveOn")
	{
		emit sigSetServo(true);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setDriveOff")
	{
		emit sigSetServo(false);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setDriveMain1")
	{
		emit sigSetOverride(1);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setDriveMain2")
	{
		emit sigSetOverride(2);
		emit sigRefreshState();
		result = AskuModule::CommandSuccess;
	}
	if(command == "setDriveSpeed")
	{
		if(parameters.count() == 1)
		{
			bool ok = false;
			double speed = parameters[0].toDouble(&ok);

			if(ok)
			{
				emit sigSetSpeed(speed);
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
qint32 DRIVE::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogDriveError("DRIVE: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();
	if(infoType == "DRIVE_SLAVE_SYNC")
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
void DRIVE::refreshState(QVariantMap info)
{
	QVariantMap data;
	data["InfoType"] = "DRIVE_INFO";
	data["ModuleTo"] = "dialog_drives";
	data["ModuleFrom"] = "drive";
	data["GprId"] = IDGPR();
	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DRIVE::syncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure)
{
	LogDriveInfo("DRIVE::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "DRIVE_SLAVE_SYNC";
	data["ModuleTo"] = "drive";
	data["ModuleFrom"] = "drive";
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
