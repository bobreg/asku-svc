#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "dasd.h"

// ------------------------------------------------------------------
DASD::DASD(QObject * parent) : DASD_THREAD(parent)
{
	qRegisterMetaType<AskuBinStateSet>("AskuBinStateSet");
	qRegisterMetaType<AskuValueSet>("AskuValueSet");
	qRegisterMetaType<AskuSektorTable>("AskuSektorTable");
}

// ------------------------------------------------------------------
DASD::~DASD()
{
}

// ------------------------------------------------------------------
QString DASD::stringBits(quint32 data, quint32 bits)
{
	QString tmp;
	for(qint32 i = bits - 1; i >= 0; i--)
		if(data & (1 << i))
			tmp += "1";
		else
			tmp += "0";
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringNum10(quint32 data)
{
	QString tmp;
	tmp.sprintf("%2d", data);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringNum4_10(quint32 data)
{
	QString tmp;
	tmp.sprintf("%2.3f", (double)data/1000.f);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringNum4(quint32 data)
{
	QString tmp;
	tmp.sprintf("0x%04X", data);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringNum3(quint32 data)
{
	QString tmp;
	tmp.sprintf("0x%03X", data);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringNum2(quint32 data)
{
	QString tmp;
	tmp.sprintf("0x%02X", data);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringNum(quint32 data)
{
	QString tmp;
	tmp.sprintf("0x%08X", data);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringNum64(quint32 data_low, quint32 data_high)
{
	QString tmp;
	tmp.sprintf("0x%08X%08X", data_high, data_low);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringFloat(quint8 data, double koeff)
{
	QString tmp;
	tmp.sprintf("%2.3f", (double)data * koeff);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringFloat1(quint32 data, double koeff)
{
	QString tmp;
	tmp.sprintf("%2.3f", (double)data * koeff);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringFloat1s(quint32 data, double koeff)
{
	QString tmp;
	double value = data * koeff;
	if(value > 180) value -= 360;
	tmp.sprintf("%2.3f", value);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringFloat2(double data)
{
	QString tmp;
	tmp.sprintf("%2.2f",data);
	return tmp;
}

// ------------------------------------------------------------------
QString DASD::stringVersion(quint32 data)
{
	REG_VERSION ver;
	ver.dword = data;
	QString tmp;
	tmp.sprintf("%02X.%02X.%02X %02X",ver.bits.day,ver.bits.month,ver.bits.year,ver.bits.version);
	return tmp;
}

// ------------------------------------------------------------------
qint32 DASD::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogModuleError("DASD: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogModuleError("DASD: empty command");
		return result;
	}

	bool ok = false;
	quint32 numGpr = data["ToGprId"].toUInt(&ok);
	if(ok && numGpr != IDGPR())
	{
		LogModuleError("DASD: success but not mine");
		result = AskuModule::CommandSuccess;
		return result;
	}

	LogModuleError("Command: %s", qPrintable(command));

	if(command == "resetTables")
	{
		emit sigResetTables();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleMain")
	{
		emit sigToggleMain();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleRipch")
	{
		emit sigToggleRipch();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleImitatorPeriod")
	{
		emit sigToggleImitatorPeriod();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleAzimuthSource")
	{
		emit sigToggleAzimuthSource();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleAzimuthMode")
	{
		emit sigToggleAzimuthMode();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleAzimuthPeriod")
	{
		emit sigToggleAzimuthPeriod();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleAzimuthLir1Load")
	{
		emit sigToggleAzimuthLir1Load();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleAzimuthLir2Load")
	{
		emit sigToggleAzimuthLir2Load();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleAzimuthSerialLoad")
	{
		emit sigToggleAzimuthSerialLoad();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleBlockZu")
	{
		emit sigToggleBlockZu();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleBlockSwitch")
	{
		emit sigToggleBlockSwitch();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleVaruBan")
	{
		emit sigToggleVaruBan();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleBlockAvto")
	{
		emit sigToggleBlockAvto();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleImpulsePrd")
	{
		emit sigToggleImpulsePrd();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setImpulsePrd")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok = false;
			quint32 value = parameters[0].toUInt(&ok,16);

			if(ok)
			{
				emit sigSetImpulsePrd(value);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "toggleTimerSource")
	{
		emit sigToggleTimerSource();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleSharuSource")
	{
		emit sigToggleSharuSource();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleErrorZu1")
	{
		emit sigToggleErrorZu1();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleErrorZu2")
	{
		emit sigToggleErrorZu2();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleSkrOn")
	{
		emit sigToggleSkrOn();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleSkrAlwaysOn")
	{
		emit sigToggleSkrAlwaysOn();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "togglePilotOn")
	{
		emit sigTogglePilotOn();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "togglePilotAlwaysOn")
	{
		emit sigTogglePilotAlwaysOn();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleGshOn")
	{
		emit sigToggleGshOn();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleGshAlwaysOn")
	{
		emit sigToggleGshAlwaysOn();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleZuOn")
	{
		emit sigToggleZuOn();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleZuAlwaysOn")
	{
		emit sigToggleZuAlwaysOn();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "toggleTimerLoad")
	{
		emit sigToggleTimerLoad();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setMain")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			if(parameters[0] == "true" || parameters[0] == "1")
			{
				emit sigSetMain(true);
				result = AskuModule::CommandSuccess;
			}
			else if(parameters[0] == "false" || parameters[0] == "0")
			{
				emit sigSetMain(false);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setRipch")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			if(parameters[0] == "true" || parameters[0] == "1")
			{
				emit sigSetRipch(true);
				result = AskuModule::CommandSuccess;
			}
			else if(parameters[0] == "false" || parameters[0] == "0")

			{
				emit sigSetRipch(false);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setLir1Offset")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok = false;
			quint32 offset = parameters[0].toUInt(&ok,16);
			if(ok)
			{
				emit sigSetLir1Offset(offset);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setLir2Offset")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok = false;
			quint32 offset = parameters[0].toUInt(&ok,16);

			if(ok)
			{
				emit sigSetLir2Offset(offset);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setLirOffsets")
	{
		if(parameters.count() < 2)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok1 = false, ok2 = false;
			quint32 offset1 = parameters[0].toUInt(&ok1,16);
			quint32 offset2 = parameters[1].toUInt(&ok2,16);

			if(ok1 && ok2)
			{
				emit sigSetLirOffsets(offset1, offset2);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setSharu1Code")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok = false;
			quint32 code = parameters[0].toUInt(&ok,16);
			if(ok)
			{
				emit sigSetSharu1Code(code);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setSharu2Code")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok = false;
			quint32 code = parameters[0].toUInt(&ok,16);

			if(ok)
			{
				emit sigSetSharu2Code(code);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setSharuCodes")
	{
		if(parameters.count() < 2)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok1 = false, ok2 = false;
			quint32 code1 = parameters[0].toUInt(&ok1,16);
			quint32 code2 = parameters[1].toUInt(&ok2,16);

			if(ok1 && ok2)
			{
				emit sigSetSharuCodes(code1, code2);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setSyncrOutput")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok = false;
			quint32 value = parameters[0].toUInt(&ok,16);

			if(ok)
			{
				emit sigSetSyncrOutput(value);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setAmpDelayPilot")
	{
		if(parameters.count() < 2)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok1 = false, ok2 = false;
			quint32 value1 = parameters[0].toUInt(&ok1,16);
			quint32 value2 = parameters[1].toUInt(&ok2,16);

			if(ok1 && ok2)
			{
				emit sigSetAmpDelayPilotParam(0, value1);
				emit sigSetAmpDelayPilotParam(1, value2);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setDelayPilot")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok1 = false;
			quint32 value1 = parameters[0].toUInt(&ok1,16);

			if(ok1)
			{
				emit sigSetAmpDelayPilotParam(0, value1);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setAmpPilot")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok1 = false;
			quint32 value1 = parameters[0].toUInt(&ok1,16);

			if(ok1)
			{
				emit sigSetAmpDelayPilotParam(1, value1);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setStepDopler")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok1 = false;
			quint32 value1 = parameters[0].toInt(&ok1);

			if(ok1)
			{
				emit sigSetStepDopler(value1);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setFreqDeviation")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok1 = false;
			quint32 value1 = parameters[0].toInt(&ok1);

			if(ok1)
			{
				setFreqDeviation(value1);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "startMonitor")
	{
		emit sigStartMonitor();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setMonitorRate")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok = false;
			quint32 value = parameters[0].toUInt(&ok);

			if(ok)
			{
				emit sigSetMonitorRate(value);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "stopMonitor")
	{
		emit sigStopMonitor();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "dumpRegisters")
	{
		emit sigSetDump(0);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "refreshRegisters" || command == "resetModule")
	{
		emit sigSetDump(1);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "commandList")
	{
		QStringList list;
		commandList(list);
		result = AskuModule::CommandSuccess;
	}
	else if(command == "refreshTables")
	{
		quint32 value = 0;
		bool ok = true;

		if(parameters.count() > 0)
			value = parameters[0].toUInt(&ok);

		if(!ok)
		{
			result = AskuModule::CommandInvalidParameter;
		}
		else
		{
			emit sigRefreshTables(value, false);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "refreshTablesFromFile")
	{
		quint32 value = 0;
		bool ok = true;

		if(parameters.count() > 0)
			value = parameters[0].toUInt(&ok);

		if(!ok)
		{
			result = AskuModule::CommandInvalidParameter;
		}
		else
		{
			emit sigRefreshTables(value, true);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "saveTableRipch")
	{
		QVariantMap mapdata = data["TableData"].toMap();
		if(mapdata.isEmpty())
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			emit sigSaveTableRipch(mapdata, false);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "saveFileTableRipch")
	{
		QVariantMap mapdata = data["TableData"].toMap();
		if(mapdata.isEmpty())
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			emit sigSaveTableRipch(mapdata, true);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "saveTableMode")
	{
		QVariantMap mapdata = data["TableData"].toMap();
		if(mapdata.isEmpty())
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			emit sigSaveTableMode(mapdata, false);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "saveFileTableMode")
	{
		QVariantMap mapdata = data["TableData"].toMap();
		if(mapdata.isEmpty())
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			emit sigSaveTableMode(mapdata, true);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "saveTableSwitch")
	{
		QVariantMap mapdata = data["TableData"].toMap();
		if(mapdata.isEmpty())
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			emit sigSaveTableSwitch(mapdata, false);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "saveFileTableSwitch")
	{
		QVariantMap mapdata = data["TableData"].toMap();
		if(mapdata.isEmpty())
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			emit sigSaveTableSwitch(mapdata, true);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "saveTableDisable")
	{
		QVariantMap mapdata = data["TableData"].toMap();
		if(mapdata.isEmpty())
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			emit sigSaveTableDisable(mapdata, false);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "saveFileTableDisable")
	{
		QVariantMap mapdata = data["TableData"].toMap();
		if(mapdata.isEmpty())
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			emit sigSaveTableDisable(mapdata, true);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "refreshSkrPilot")
	{
		QTimer::singleShot(0,this,SLOT(refreshSkrPilot()));
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setSkrPilot")
	{
		quint32 azSKR = 0, azPS = 0, period = 0;
		bool okSKR = true, okPS = true, okPeriod = true;

		if(parameters.count() > 0)
			azSKR = parameters[0].toUInt(&okSKR);
		if(parameters.count() > 1)
			azPS = parameters[1].toUInt(&okPS);
		if(parameters.count() > 2)
			period = parameters[2].toUInt(&okPeriod);

		if(!okSKR || !okPS || !okPeriod)
		{
			result = AskuModule::CommandInvalidParameter;
		}
		else
		{
			setSkrPilot(azSKR, azPS, period);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "refreshSetPrm")
	{
		emit sigRefreshSetPrm();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrmOn")
	{
		quint32 isPrmOn = 0;
		bool ok = true;

		if(parameters.count() > 0)
			isPrmOn = parameters[0].toUInt(&ok);

		if(!ok)
		{
			result = AskuModule::CommandInvalidParameter;
		}
		else
		{
			emit sigSetPrmOn((bool)isPrmOn);
			result = AskuModule::CommandSuccess;
		}

		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrmGsh")
	{
		quint32 isPrmGsh = 0;
		bool ok = true;

		if(parameters.count() > 0)
			isPrmGsh = parameters[0].toUInt(&ok);

		if(!ok)
		{
			result = AskuModule::CommandInvalidParameter;
		}
		else
		{
			emit sigSetPrmGsh((bool)isPrmGsh);
			result = AskuModule::CommandSuccess;
		}

		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrmZu")
	{
		quint32 isPrmZu = 0;
		bool ok = true;

		if(parameters.count() > 0)
			isPrmZu = parameters[0].toUInt(&ok);

		if(!ok)
		{
			result = AskuModule::CommandInvalidParameter;
		}
		else
		{
			emit sigSetPrmZu((bool)isPrmZu);
			result = AskuModule::CommandSuccess;
		}

		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrmPilot")
	{
		quint32 isPrmPilot = 0;
		bool ok = true;

		if(parameters.count() > 0)
			isPrmPilot = parameters[0].toUInt(&ok);

		if(!ok)
		{
			result = AskuModule::CommandInvalidParameter;
		}
		else
		{
			emit sigSetPrmPilot((bool)isPrmPilot);
			result = AskuModule::CommandSuccess;
		}

		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrmSkr")
	{
		quint32 isPrmSkr = 0;
		bool ok = true;

		if(parameters.count() > 0)
			isPrmSkr = parameters[0].toUInt(&ok);

		if(!ok)
		{
			result = AskuModule::CommandInvalidParameter;
		}
		else
		{
			emit sigSetPrmSkr((bool)isPrmSkr);
			result = AskuModule::CommandSuccess;
		}

		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrmSharu1Code")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok = false;
			quint32 code = parameters[0].toUInt(&ok);
			if(ok)
			{
				emit sigSetPrmSharu1Code(code);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
		}
	}
	else if(command == "setPrmSharu2Code")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			bool ok = false;
			quint32 code = parameters[0].toUInt(&ok);

			if(ok)
			{
				emit sigSetPrmSharu2Code(code);
				result = AskuModule::CommandSuccess;
			}
			else
			{
				result = AskuModule::CommandInvalidParameter;
			}
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
void DASD::dumpRegisters(DEVICE_REGISTERS devRegs)
{
	QVariantMap data;

	data["InfoType"] = "DASD_REGISTERS";
	data["ModuleTo"] = "asku-gui";
	data["ModuleFrom"] = "dasd";

	QVariantMap regs;

	regs["REG_VERSION"] = stringNum(devRegs.pack1.version.dword);
	regs["REG_CONTROL"] = stringNum(devRegs.pack1.control.dword);
	regs["REG_STATE"]   = stringNum(devRegs.pack1.state.dword);

	data["Registers"] = regs;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::refreshRegisters(DEVICE_REGISTERS devRegs)
{
	QVariantMap data;

	data["InfoType"] = "DASD_DIALOG_REGISTERS";
	data["ModuleTo"] = "dialog_dasd";
	data["ModuleFrom"] = "dasd";
	data["GprId"] = IDGPR();

	QVariantMap vals;

	vals["labelVersion"] = stringVersion(devRegs.pack1.version.dword);

	vals["labelModuleCtrl"]  = stringNum(devRegs.pack1.control.dword);
	vals["labelModuleCtrl1"] = stringBits(devRegs.pack1.control.bits.main,1);
	vals["labelModuleCtrl2"] = stringBits(devRegs.pack1.control.bits.regime,2);
	vals["labelModuleCtrl3"] = stringBits(devRegs.pack1.control.bits.block_avto,1);
	vals["labelModuleCtrl4"] = stringBits(devRegs.pack1.control.bits.is_observer,1);

	vals["labelModuleState"]  = stringNum(devRegs.pack1.state.dword);
	vals["labelModuleState1"] = stringBits(devRegs.pack1.state.bits.main,1);
	vals["labelModuleState2"] = stringBits(devRegs.pack1.state.bits.azim_source,2);
	vals["labelModuleState3"] = stringBits(devRegs.pack1.state.bits.avar_switch_s,1);
	vals["labelModuleState4"] = stringBits(devRegs.pack1.state.bits.avar_switch_d,1);
	vals["labelModuleState5"] = stringBits(devRegs.pack1.state.bits.pch_on,1);
	vals["labelModuleState6"] = stringBits(devRegs.pack1.state.bits.ind_switch_s,1);
	vals["labelModuleState7"] = stringBits(devRegs.pack1.state.bits.ind_switch_d,1);
	vals["labelModuleState8"] = stringBits(devRegs.pack1.state.bits.n_observe,2);
	vals["labelModuleState17"] = stringBits(devRegs.pack1.state.bits.avar_sync,1);

	vals["labelFormerCtrl"]  = stringNum(devRegs.pack1.rf_former.dword);
	vals["labelFormerCtrl1"] = stringBits(devRegs.pack1.rf_former.bits.allow_pch,1);
	vals["labelFormerCtrl2"] = stringBits(devRegs.pack1.rf_former.bits.block_zu,1);
	vals["labelFormerCtrl3"] = stringBits(devRegs.pack1.rf_former.bits.block_switch,1);
//	vals["labelFormerCtrl4"] = stringBits(devRegs.pack1.rf_former.bits.block_yy11,1);
	vals["labelFormerCtrl5"] = stringBits(devRegs.pack1.rf_former.bits.no_write_varu,1);
//	vals["labelFormerCtrl6"] = stringBits(devRegs.pack1.rf_former.bits.test_sin,1);
//	vals["labelFormerCtrl7"] = stringBits(devRegs.pack1.rf_former.bits.reserved1,1);
//	vals["labelFormerCtrl8"] = stringBits(devRegs.pack1.rf_former.bits.strobe_enable,1);
	vals["labelFormerCtrl9"] = stringBits(devRegs.pack1.rf_former.bits.error_crc,1);
	vals["labelFormerCtrl10"] = stringBits(devRegs.pack1.rf_former.bits.error_parity,1);
	vals["labelFormerCtrl11"] = stringBits(devRegs.pack1.rf_former.bits.error_stop,1);
	vals["labelFormerCtrl12"] = stringBits(devRegs.pack1.rf_former.bits.error_compare,1);
	vals["labelFormerCtrl13"] = stringBits(devRegs.pack1.rf_former.bits.avar_block_gf,1);
	vals["labelFormerCtrl14"] = stringBits(devRegs.pack1.rf_former.bits.is_ref_freq,1);
//	vals["labelFormerCtrl15"] = stringBits(devRegs.pack1.rf_former.bits.allow_yy,1);
	vals["labelFormerCtrl16"] = stringBits(devRegs.pack1.rf_former.bits.error_timeout,1);
	vals["spinFormerCtrl17"] = QString::number(devRegs.pack1.rf_former.bits.impulse);
//	vals["labelFormerCtrl25"] = stringBits(devRegs.pack1.rf_former.bits.main_yy_1,1);
//	vals["labelFormerCtrl26"] = stringBits(devRegs.pack1.rf_former.bits.main_yy_2,1);
//	vals["labelFormerCtrl27"] = stringBits(devRegs.pack1.rf_former.bits.reserved2,2);
	vals["labelFormerCtrl29"] = stringBits(devRegs.pack1.rf_former.bits.err_ctrl_zu_s,1);
	vals["labelFormerCtrl30"] = stringBits(devRegs.pack1.rf_former.bits.err_ctrl_zu_d,1);
	vals["labelFormerCtrl31"] = stringBits(devRegs.pack1.rf_former.bits.ant_key_rf_enable,1);
	vals["labelFormerCtrl32"] = stringBits(devRegs.pack1.rf_former.bits.rf_enable_indicator,1);

	vals["labelAzimCtrl"]  = stringNum(devRegs.pack1.az_control.dword);
	vals["labelAzimCtrl1"] = stringBits(devRegs.pack1.az_control.bits.source,2);
	vals["labelAzimCtrl3"] = stringBits(devRegs.pack1.az_control.bits.im_period,3);
	vals["labelAzimCtrl4"] = stringBits(devRegs.pack1.az_control.bits.load_lir_1,1);
	vals["labelAzimCtrl5"] = stringBits(devRegs.pack1.az_control.bits.load_lir_2,1);
	vals["labelAzimCtrl6"] = stringBits(devRegs.pack1.az_control.bits.load_serial,1);

	vals["labelTimerCtrl"]  = stringNum(devRegs.pack1.timer_control.dword);
	vals["labelTimerCtrl1"] = stringBits(devRegs.pack1.timer_control.bits.source,2);

	vals["labelTimerState"]  = stringNum(devRegs.pack1.timer_state.dword);
	vals["labelTimerState1"] = stringBits(devRegs.pack1.timer_state.bits.antenna_ok,1);
	vals["labelTimerState2"] = stringBits(devRegs.pack1.timer_state.bits.load_on,1);

	vals["labelSharuCtrl"]  = stringNum(devRegs.pack1.sharu_control.dword);
	vals["labelSharuCtrl1"] = stringNum10(devRegs.pack1.sharu_control.bits.code_s);
	vals["labelSharuCtrl2"] = stringNum10(devRegs.pack1.sharu_control.bits.code_d);
	vals["labelSharuCtrl3"] = stringBits(devRegs.pack1.sharu_control.bits.source,2);

	vals["labelErrorZu"]  = stringNum(devRegs.pack1.err_zu.dword);
	vals["labelErrorZu1"] = stringNum2(devRegs.pack1.err_zu.bits.avar_s);
	vals["labelErrorZu1S1"] = stringBits(devRegs.pack1.err_zu.bits1.avar_s_kz1,1);
	vals["labelErrorZu1S2"] = stringBits(devRegs.pack1.err_zu.bits1.avar_s_kz2,1);
	vals["labelErrorZu1S3"] = stringBits(devRegs.pack1.err_zu.bits1.avar_s_hh1,1);
	vals["labelErrorZu1S4"] = stringBits(devRegs.pack1.err_zu.bits1.avar_s_hh2,1);
	vals["labelErrorZu1S5"] = stringBits(devRegs.pack1.err_zu.bits1.avar_s_a80v,1);
	vals["labelErrorZu1S6"] = stringBits(devRegs.pack1.err_zu.bits1.avar_s_a5v,1);
	vals["labelErrorZu1Link"] = stringBits(devRegs.pack1.err_zu.bits.link_s,1);
	vals["labelErrorZu2"] = stringNum2(devRegs.pack1.err_zu.bits.avar_d);
	vals["labelErrorZu2D1"] = stringBits(devRegs.pack1.err_zu.bits1.avar_d_kz1,1);
	vals["labelErrorZu2D2"] = stringBits(devRegs.pack1.err_zu.bits1.avar_d_kz2,1);
	vals["labelErrorZu2D3"] = stringBits(devRegs.pack1.err_zu.bits1.avar_d_hh1,1);
	vals["labelErrorZu2D4"] = stringBits(devRegs.pack1.err_zu.bits1.avar_d_hh2,1);
	vals["labelErrorZu2D5"] = stringBits(devRegs.pack1.err_zu.bits1.avar_d_a80v,1);
	vals["labelErrorZu2D6"] = stringBits(devRegs.pack1.err_zu.bits1.avar_d_a5v,1);
	vals["labelErrorZu2Link"] = stringBits(devRegs.pack1.err_zu.bits.link_d,1);

	vals["labelAzimuth"]  = stringNum(devRegs.pack1.azimuth.dword);
	vals["labelAzimuth1"] = stringFloat1(devRegs.pack1.azimuth.bits.azimuth,360.0/16384);
	vals["labelAzimuth2"] = stringNum10(devRegs.pack1.azimuth.bits.sektor);

	vals["labelPeriod"]  = stringNum(devRegs.pack1.mai_period.dword);
	vals["labelPeriod1"] = stringNum4_10(devRegs.pack1.mai_period.bits.time_mai);
	vals["labelPeriod2"] = stringNum4_10(devRegs.pack1.mai_period.bits.time_nord);

	vals["labelSensorOffset"]  = stringNum(devRegs.pack1.sensor_offset.dword);
	vals["labelSensorOffset1"] = stringNum4(devRegs.pack1.sensor_offset.bits.azimuth1);
	vals["labelSensorOffset2"] = stringNum4(devRegs.pack1.sensor_offset.bits.azimuth2);

	vals["labelOffset"]  = stringNum(devRegs.pack1.offset.dword);
	vals["labelOffset31"] = stringBits(devRegs.pack1.offset.bits.ready,1);
	vals["spinOffset1"] = QString::number(devRegs.pack1.offset.bits.azimuth1);
	vals["spinOffset2"] = QString::number(devRegs.pack1.offset.bits.azimuth2);

	vals["labelLir1AzimSensor"]  = stringNum(devRegs.pack1.lir1_sensor.dword);
	vals["labelLir1AzimSensor1"] = stringFloat1(devRegs.pack1.lir1_sensor.bits.azimuth,360.0/16384);
	vals["labelLir1AzimSensor17"] = stringBits(devRegs.pack1.lir1_sensor.bits.imitator,1);
	vals["labelLir1AzimSensor18"] = stringBits(devRegs.pack1.lir1_sensor.bits.active_comp,1);
	vals["labelLir1AzimSensor19"] = stringBits(devRegs.pack1.lir1_sensor.bits.active_sensor,1);
	vals["labelLir1AzimSensor31"] = stringBits(devRegs.pack1.lir1_sensor.bits.parity_error,1);
	vals["labelLir1AzimSensor32"] = stringBits(devRegs.pack1.lir1_sensor.bits.line_detect_error,1);

	vals["labelLir2AzimSensor"]  = stringNum(devRegs.pack1.lir2_sensor.dword);
	vals["labelLir2AzimSensor1"] = stringFloat1(devRegs.pack1.lir2_sensor.bits.azimuth,360.0/16384);
	vals["labelLir2AzimSensor17"] = stringBits(devRegs.pack1.lir2_sensor.bits.imitator,1);
	vals["labelLir2AzimSensor18"] = stringBits(devRegs.pack1.lir2_sensor.bits.active_comp,1);
	vals["labelLir2AzimSensor19"] = stringBits(devRegs.pack1.lir2_sensor.bits.active_sensor,1);
	vals["labelLir2AzimSensor31"] = stringBits(devRegs.pack1.lir2_sensor.bits.parity_error,1);
	vals["labelLir2AzimSensor32"] = stringBits(devRegs.pack1.lir2_sensor.bits.line_detect_error,1);

	vals["labelSKR"]  = stringNum(devRegs.pack1.skr.dword);
	vals["labelSKR1"] = stringFloat1(devRegs.pack1.skr.bits.azimuth_on,360.0/16384);
	vals["labelSKR2"] = stringFloat1(devRegs.pack1.skr.bits.azimuth_off,360.0/16384);
	vals["labelSKR3"] = stringBits(devRegs.pack1.skr.bits.always_on,1);
	vals["labelSKR4"] = stringBits(devRegs.pack1.skr.bits.set_on,1);

	vals["labelPS"]  = stringNum(devRegs.pack1.pilot.dword);
	vals["labelPS1"] = stringFloat1(devRegs.pack1.pilot.bits.azimuth_on,360.0/16384);
	vals["labelPS2"] = stringFloat1(devRegs.pack1.pilot.bits.azimuth_off,360.0/16384);
	vals["labelPS3"] = stringBits(devRegs.pack1.pilot.bits.always_on,1);
	vals["labelPS4"] = stringBits(devRegs.pack1.pilot.bits.set_on,1);

	vals["labelGSH"]  = stringNum(devRegs.pack1.gsh.dword);
	vals["labelGSH1"] = stringFloat1(devRegs.pack1.gsh.bits.azimuth_on,360.0/16384);
	vals["labelGSH2"] = stringFloat1(devRegs.pack1.gsh.bits.azimuth_off,360.0/16384);
	vals["labelGSH3"] = stringBits(devRegs.pack1.gsh.bits.always_on,1);
	vals["labelGSH4"] = stringBits(devRegs.pack1.gsh.bits.set_on,1);

	vals["labelZU"]  = stringNum(devRegs.pack1.zu.dword);
	vals["labelZU1"] = stringFloat1(devRegs.pack1.zu.bits.azimuth_on,360.0/16384);
	vals["labelZU2"] = stringFloat1(devRegs.pack1.zu.bits.azimuth_off,360.0/16384);
	vals["labelZU3"] = stringBits(devRegs.pack1.zu.bits.always_on,1);
	vals["labelZU4"] = stringBits(devRegs.pack1.zu.bits.set_on,1);

	vals["labelTime1"] = stringNum10(devRegs.pack1.time.bits.second);
	vals["labelTime2"] = stringNum10(devRegs.pack1.time.bits.minute);
	vals["labelTime3"] = stringNum10(devRegs.pack1.time.bits.hour);
	vals["labelTime4"] = stringBits(devRegs.pack1.time.bits.sure_msv_int,1);
	vals["labelTime5"] = stringBits(devRegs.pack1.time.bits.sure_kd_int,1);
	vals["labelTime6"] = stringBits(devRegs.pack1.time.bits.sure_kd_main,1);
	vals["labelTime7"] = stringBits(devRegs.pack1.time.bits.sure_main,1);

	vals["labelDate1"] = stringNum10(devRegs.pack1.date.bits.day);
	vals["labelDate2"] = stringNum10(devRegs.pack1.date.bits.month);
	vals["labelDate3"] = stringNum10(devRegs.pack1.date.bits.year+2000);

	vals["labelTimer"] = stringNum(devRegs.pack1.timer.dword);
	vals["labelTimer1"] = stringBits(devRegs.pack1.timer.bits.no_pps,1);

	vals["spinFreqDeviation1"] = QString::number((int)devRegs.pack2.freq_deviation.dword);

	vals["labelStepDopler"]   = stringNum(devRegs.pack1.step_dopler.dword);
	vals["spinStepDopler1"] = QString::number((int)devRegs.pack1.step_dopler.bits.step);

	vals["labelAmpDelayPilot"]   = stringNum(devRegs.pack1.amp_delay.dword);
	vals["spinAmpDelayPilot1"] = QString::number(devRegs.pack1.amp_delay.bits.amplitude);
	vals["spinAmpDelayPilot2"] = QString::number(devRegs.pack1.amp_delay.bits.delay);

	vals["labelSyncr"]   = stringNum(devRegs.pack1.syncr.dword);
	vals["spinSyncr1"] = QString::number(devRegs.pack1.syncr.bits.output);

	vals["labelAzimSerial"]  = stringNum(devRegs.pack1.serial_sensor.dword);
	vals["labelAzimSerial1"] = stringFloat1(devRegs.pack1.serial_sensor.bits.azimuth,360.0/16384);
	vals["labelAzimSerial17"] = stringBits(devRegs.pack1.serial_sensor.bits.imitator,1);
	vals["labelAzimSerial18"] = stringBits(devRegs.pack1.serial_sensor.bits.active_comp,1);
	vals["labelAzimSerial19"] = stringBits(devRegs.pack1.serial_sensor.bits.active_sensor,1);
	vals["labelAzimSerial31"] = stringBits(devRegs.pack1.serial_sensor.bits.parity_error,1);
	vals["labelAzimSerial32"] = stringBits(devRegs.pack1.serial_sensor.bits.line_detect_error,1);

	vals["labelRX0"]  = stringNum(devRegs.pack1.rx0_state.dword);
	vals["labelRX0_1"] = stringNum3(devRegs.pack1.rx0_state.bits.r_adress);
	vals["labelRX0_2"] = stringNum3(devRegs.pack1.rx0_state.bits.l_adress);
	vals["labelRX0_3"] = stringNum10(devRegs.pack1.rx0_state.bits.count);
	vals["labelRX0_4"] = stringBits(devRegs.pack1.rx0_state.bits.empty,1);
	vals["labelRX0_5"] = stringBits(devRegs.pack1.rx0_state.bits.overflow,1);

	vals["labelTX0"]  = stringNum(devRegs.pack1.tx0_control.dword);
	vals["labelTX0_1"] = stringNum3(devRegs.pack1.tx0_control.bits.adress);
	vals["labelTX0_2"] = stringNum3(devRegs.pack1.tx0_control.bits.count);
/*
	int nNGr, nNMin, nEGr, nEMin, nH;
	float fNSec, fESec;
	NormalToGeo(devRegs.pack2.latitude.value, &nNGr, &nNMin, &fNSec);
	NormalToGeo(devRegs.pack2.longitude.value, &nEGr, &nEMin, &fESec);
	nH = (int)devRegs.pack2.altitude.value;

	vals["labelGeo1_1"] = QString::number(nNGr);
	vals["labelGeo1_2"] = QString::number(nNMin);
	vals["labelGeo1_3"] = stringFloat2(fNSec);
	vals["labelGeo2_1"] = QString::number(nEGr);
	vals["labelGeo2_2"] = QString::number(nEMin);
	vals["labelGeo2_3"] = stringFloat2(fESec);
	vals["labelGeo3"] = QString::number(nH);
*/
	data["Values"] = vals;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::commandList(QStringList list)
{
	QVariantMap data;

	data["InfoType"] = "DASD_COMMAND_LIST";
	data["ModuleTo"] = "asku-gui";
	data["ModuleFrom"] = "dasd";
	data["Commands"] = list;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::statusMessage(QString message)
{
	QVariantMap data;

	data["InfoType"] = "DASD_STATUS_MESSAGE";
	data["ModuleTo"] = "dialog_dasd";
	data["ModuleFrom"] = "dasd";
	data["GprId"] = IDGPR();
	data["Message"] = message;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::tableRipch(QVariantMap table, qint32 maxRow)
{
	QVariantMap data;

	data["InfoType"] = "DASD_RIPCH_TABLE";
	data["ModuleTo"] = "dialog_dasd_tables";
	data["ModuleFrom"] = "dasd";
	data["GprId"] = IDGPR();

	if(!table.isEmpty())
	{
		data["TableData"] = table;
		data["TableMaxRow"] = maxRow;
	}

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::tableMode(QVariantMap table, qint32 maxRow)
{
	QVariantMap data;

	data["InfoType"] = "DASD_MODE_TABLE";
	data["ModuleTo"] = "dialog_dasd_tables";
	data["ModuleFrom"] = "dasd";
	data["GprId"] = IDGPR();

	if(!table.isEmpty())
	{
		data["TableData"] = table;
		data["TableMaxRow"] = maxRow;
	}

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::tableSwitch(QVariantMap table, qint32 maxRow)
{
	QVariantMap data;

	data["InfoType"] = "DASD_SWITCH_TABLE";
	data["ModuleTo"] = "dialog_dasd_tables";
	data["ModuleFrom"] = "dasd";
	data["GprId"] = IDGPR();

	if(!table.isEmpty())
	{
		data["TableData"] = table;
		data["TableMaxRow"] = maxRow;
	}

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::tableDisable(QVariantMap table, qint32 maxRow)
{
	QVariantMap data;

	data["InfoType"] = "DASD_DISABLE_TABLE";
	data["ModuleTo"] = "dialog_dasd_tables";
	data["ModuleFrom"] = "dasd";
	data["GprId"] = IDGPR();

	if(!table.isEmpty())
	{
		data["TableData"] = table;
		data["TableMaxRow"] = maxRow;
	}

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::tablesResults(QString message)
{
	QVariantMap data;

	data["InfoType"] = "DASD_TABLES_MESSAGE";
	data["ModuleTo"] = "dialog_dasd_tables";
	data["ModuleFrom"] = "dasd";
	data["GprId"] = IDGPR();
	data["Message"] = message;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::refreshSkrPilot()
{
	QVariantMap data;

	data["InfoType"] = "DASD_SKRPILOT_INFO";
	data["ModuleTo"] = "dialog_skrpilot";
	data["ModuleFrom"] = "dasd";
	data["GprId"] = IDGPR();

	QVariantMap skrplt;

	quint32 azSkr = m_setup.skrps.skr_azimuth;
	quint32 azPs  = m_setup.skrps.ps_azimuth;

	if(m_setup.skrps.offset)
	{
		azSkr += 32;
		if(azSkr >= 64)
			azSkr -= 64;

		azPs += 32;
		if(azPs >= 64)
			azPs -= 64;
	}

	skrplt["azSkr"] = azSkr;
	skrplt["azPs"] = azPs;
	skrplt["Period"] = m_setup.skrps.period;

	data["Info"] = skrplt;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::setSkrPilot(quint32 azSKR, quint32 azPS, quint32 period)
{
	if(m_setup.skrps.offset)
	{
		azSKR += 32;
		if(azSKR >= 64)
			azSKR -= 64;

		azPS += 32;
		if(azPS >= 64)
			azPS -= 64;
	}

	m_setup.skrps.skr_azimuth = azSKR;
	m_setup.skrps.ps_azimuth  = azPS;
	m_setup.skrps.period = period;

	emit sigUpdateSkrPilot();
	QTimer::singleShot(0, this, SIGNAL(sigFlushSettings()));
}

// ------------------------------------------------------------------
void DASD::setFreqDeviation(quint32 value)
{
	m_setup.module.freq_deviation = value;
	emit sigSetFreqDeviation(value);
	QTimer::singleShot(0, this, SIGNAL(sigFlushSettings()));
}

// ------------------------------------------------------------------
void DASD::refreshSetPrmInfo(QVariantMap setPrmInfo)
{
	QVariantMap data;

	data["InfoType"] = "DASD_SETPRM_INFO";
	data["ModuleTo"] = "dialog_setprm";
	data["ModuleFrom"] = "dasd";
	data["GprId"] = IDGPR();
	data["Info"] = setPrmInfo;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void DASD::onChangedMain(bool on)
{
	emit sigSetMain(on);
}

// ------------------------------------------------------------------
void DASD::onConnectedGpr()
{
	emit sigConnectedGpr();
}

// ------------------------------------------------------------------
void DASD::onDisconnectedGpr()
{
	emit sigDisconnectedGpr();
}

// ------------------------------------------------------------------
void DASD::onSetReset()
{
	emit sigToggleErrorZu1();
	emit sigToggleErrorZu2();
}

// ------------------------------------------------------------------
qint32 DASD::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogModuleError("DASD: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();

	if(infoType == "DASD_SLAVE_SYNC")
	{
		if(data.contains("Config") || data.contains("State") || data.contains("Measure"))
		{
			QVariantMap config = data["Config"].toMap();
			QVariantMap state = data["State"].toMap();
			QVariantMap measure  = data["Measure"].toMap();
			emit sigOnSyncToSlave(config, state, measure);
		}

		result = AskuModule::CommandSuccess;
	}

	return result;
}

// ------------------------------------------------------------------
void DASD::syncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure)
{
	LogModuleInfo("DASD::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "DASD_SLAVE_SYNC";
	data["ModuleTo"] = "dasd";
	data["ModuleFrom"] = "dasd";
	data["GprId"] = IDGPR();
	if(!config.isEmpty())
		data["Config"] = config;
	if(!state.isEmpty())
		data["State"] = state;
	if(!measure.isEmpty())
		data["Measure"] = measure;

//	qDebug() << "syncToSlave";
//	qDebug() << config;
//	qDebug() << state;
//	qDebug() << measure;
//	qDebug() << "-----------";

	emit sendInfoMessage(data, idAskuModuleSvc);
}

// ------------------------------------------------------------------
