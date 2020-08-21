#include "../common/logger.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "globalvar.h"
#include "canalasku.h"

//--------------------------------------------------------------
CanalAsku::CanalAsku(QObject * parent) : CanalAskuThread(parent)
{
	connect(this, SIGNAL(readyData(CanalAskuData*)), this, SLOT(onReadyData(CanalAskuData*)));

	m_canalAskuConfig.monitor = false;
	m_canalAskuConfig.update = false;
	m_canalAskuConfig.first = false;

	elk1b.Byte = elk2b.Byte = elk3b.Byte = elk4b.Byte = elk5b.Byte = elk6b.Byte = elk7b.Byte = elk8b.Byte = elk9b.Byte = 
	elk10b.Byte = elk11b.Byte = elk12b.Byte = elk13b.Byte = elk14b.Byte = elk15b.Byte = elk16b.Byte = elk17b.Byte = elk18b.Byte = elk19b.Byte = elk34b.Byte = 0;
	elk2021b.Value = elk2223b.Value = elk2425b.Value = elk2627b.Value = elk2829b.Value = elk3031b.Value = elk3233b.Value = 0;

	prd1b[0].Byte = prd2b[0].Byte = prd3b[0].Byte = prd4b[0].Byte = prd5b[0].Byte = prd6b[0].Byte = prd7b[0].Byte = prd8b[0].Byte = prd9b[0].Byte = prd10b[0].Byte = prd11b[0].Byte = prd12b[0].Byte = 0;
	prd1b[1].Byte = prd2b[1].Byte = prd3b[1].Byte = prd4b[1].Byte = prd5b[1].Byte = prd6b[1].Byte = prd7b[1].Byte = prd8b[1].Byte = prd9b[1].Byte = prd10b[1].Byte = prd11b[1].Byte = prd12b[1].Byte = 0;

	elkBPU.Byte = 0;
	prdBPU1b[0].Byte = prdBPU2b[0].Byte = prdBPU3b[0].Byte = prdBPU4b[0].Byte = prdBPU5b[0].Byte = prdBPU6b[0].Byte = 0;
	prdBPU1b[1].Byte = prdBPU2b[1].Byte = prdBPU3b[1].Byte = prdBPU4b[1].Byte = prdBPU5b[1].Byte = prdBPU6b[1].Byte = 0;

	memset(paramUMI, 0, sizeof(paramUMI));

	memset(&elkCmd, 0, sizeof(elkCmd));
	memset(&prdCmd, 0, sizeof(prdCmd));

	m_commands_prd.clear();
	m_commands_elk.clear();

	m_selectors_prd.clear();
	m_selectors_prd["N_PRD"] = CA_N_TRANSMITTERS;
	m_selectors_prd["N_UMI"] = CA_N_MODULES_UMI;

	QVariantList listPrd, listUmi;
	qint32 p, u;

	for(p = 0; p < CA_N_TRANSMITTERS; p++)
		setCheckModules(p, -1);

	setCheckSvch(-1);

	listPrd << (QStringList() << "ВСЕ" << "all");

	for(p = 1; p <= CA_N_TRANSMITTERS; p++)
		listPrd << (QStringList() << QString("ПРД %1").arg(p) << QString("prd%1").arg(p));

	listUmi << (QStringList() << "ВСЕ" << "all");
	if(CA_N_MODULES_UMI == 32)
	{
		listUmi << (QStringList() << "УМИ 1-16" << "half1");
		listUmi << (QStringList() << "УМИ 17-32" << "half2");
	}

	for(u = 1; u <= CA_N_MODULES_UMI; u++)
		listUmi << (QStringList() << QString("УМИ %1").arg(u) << QString("umi%1").arg(u));

	m_selectors_prd["SelectPrd"] = listPrd;
	m_selectors_prd["SelectUmi"] = listUmi;

	cnl["OY2_MODULES_UMI"] = CA_N_MODULES_UMI;
	cnl["OY3_MODULES_UMI"] = CA_N_MODULES_UMI;

	loadPhaseFile();
}

//--------------------------------------------------------------
CanalAsku::~CanalAsku()
{
	quit();
}

//---------------------------------------------------------------------------------
void CanalAsku::onChangedMain(bool on)
{
	setMain(on);

	if(on)
	{
		m_canalAskuConfig.main = true;
//		m_canalAskuConfig.first = false;
		setCheckSvch(0);
//DDD		setCheckModules(0, 30000);
//DDD		setCheckModules(1, 30000);

		putSvchOff();

		if(ISGPR1())
			putSvch1On();
		if(ISGPR2())
			putSvch2On();
	}
	else
	{
		m_canalAskuConfig.main = false;
//		m_canalAskuConfig.first = false;
		setCheckSvch(-1);
		setCheckModules(0, -1);
		setCheckModules(1, -1);
	}
}

// ------------------------------------------------------------------
void CanalAsku::onConnectedGpr()
{
//	emit sigConnectedGpr();
}

// ------------------------------------------------------------------
void CanalAsku::onDisconnectedGpr()
{
//	emit sigDisconnectedGpr();
}

// ----------------------------------------------------------------------------
qint32 CanalAsku::prdToInt(QString strPrd)
{
	qint32 n_prd = -1;

	if(strPrd == "all")
		n_prd = 0;
	else if(strPrd == "prd1")
		n_prd = 1;
	else if(strPrd == "prd2")
		n_prd = 2;

	return n_prd;
}

// ----------------------------------------------------------------------------
qint32 CanalAsku::moduleToInt(QString strModule)
{
	qint32 n_module = -1;

	if(strModule == "all")
		n_module = 0;
	else if(strModule == "half1")
		n_module = CA_N_MODULES_UMI+1;
	else if(strModule == "half2")
		n_module = CA_N_MODULES_UMI+2;
	else if(strModule.startsWith("umi"))
	{
		bool ok = false;
		n_module = strModule.mid(3).toUInt(&ok);
		if(!ok || n_module < 1 || n_module > CA_N_MODULES_UMI)
			n_module = -1;
	}

	return n_module;
}

// ----------------------------------------------------------------------------
QString CanalAsku::moduleUmiSerial(quint8 hi, quint8 mi, quint8 lo)
{
	quint32 value_hi = ((quint32)hi & 0x000000FF) << 16;
	quint32 value_mi = ((quint32)mi & 0x000000FF) << 8;
	quint32 value_lo = ((quint32)lo & 0x000000FF);
	quint32 value = value_hi | value_mi | value_lo;
	return QString("%1").arg(value, 6, 10, QChar('0'));
}

// ----------------------------------------------------------------------------
qint32 CanalAsku::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("CanalAsku: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogError("CanalAsku: empty command");
		return result;
	}

	LogInfo("Command: %s", qPrintable(command));

	if(command == "refreshPhase")
	{
		QTimer::singleShot(0, this, SLOT(refreshPrdSelectorsPhase()));
		result = AskuModule::CommandSuccess;
	}
	else if(command == "refreshPhaseValues")
	{
//		QTimer::singleShot(0, this, SLOT(refreshPhase()));
		setNeedUpdatePhase();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "startMonitorPhase")
	{
		startMonitorPhase();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "stopMonitorPhase")
	{
		stopMonitorPhase();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPhaseMap")
	{
		QVariantMap map = data["Map"].toMap();

		if(map.isEmpty())
		{
			LogError("CanalAsku: empty phase map");
			result = AskuModule::CommandInvalidParameter;
		}
		else
		{
			setPhaseMap(map);
			result = AskuModule::CommandSuccess;
		}
	}
	else if(command == "refreshCtrlPrd")
	{
		if(parameters.count() == 0)
		{
			QTimer::singleShot(0, this, SLOT(refreshPrdSelectorsCtrlPrd()));
			result = AskuModule::CommandSuccess;
		}
		else if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "refreshCtrlElk")
	{
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "startPhasing")
	{
		if(parameters.count() == 3)
		{
			bool ok = false;
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);
			bool n_avto = parameters[2].toUInt(&ok);

			if(n_prd >= 0 && n_module >= 0 && ok)
			{
				slotStartPhasing(n_prd, n_module, n_avto);
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
	else if(command == "stopPhasing")
	{
		slotStopPhasing();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setPrdPowerOff")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdPower(false, n_prd);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdPowerOn")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdPower(true, n_prd);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdPumiOff")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdPumi(false, false);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdPumi1")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdPumi(true, false);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdPumi2")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdPumi(false, true);
				slotPrdRefresh(n_prd, n_module);
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
    else if(command == "setPrdHotResOff")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotHotRes(false);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdHotResOn")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotHotRes(true);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdModule380vOff")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdPower380Module(false, n_prd, n_module);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdModule380vOn")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdPower380Module(true, n_prd, n_module);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdModulePowerOff")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdPowerModule(false, n_prd, n_module);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdModulePowerOn")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdPowerModule(true, n_prd, n_module);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdModuleSvchOff")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdSVChModule(false, n_prd, n_module);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdModuleSvchOn")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdSVChModule(true, n_prd, n_module);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setPrdModuleReset")
	{
		if(parameters.count() == 2)
		{
			qint32 n_prd = prdToInt(parameters[0]);
			qint32 n_module = moduleToInt(parameters[1]);

			if(n_prd >= 0 && n_module >= 0)
			{
				slotPrdResetModule(n_prd, n_module);
				slotPrdRefresh(n_prd, n_module);
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
	else if(command == "setElkOsvRpuOff")
	{
		putOffRpuLight();
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkOsvRpuOn")
	{
		putOnRpuLight();
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkOsvPerimOff")
	{
		putOffPerimLight();
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkOsvPerimOn")
	{
		putOnPerimLight();
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkFireOff")
	{
		putOffFire();
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkFireOn")
	{
		putOnFire();
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkGuardOff")
	{
		putOffSafe();
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkGuardOn")
	{
		putOnSafe();
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkCondOff")
	{
		putOffNoCond();
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkCondOn")
	{
		putOnNoCond();
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkTestHowl")
	{
		putOnHowl1();
		putOnHowl2();
		QTimer::singleShot(15000, this, SLOT(putOffHowl1()));
		QTimer::singleShot(15000, this, SLOT(putOffHowl2()));
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkTestHowl1")
	{
		putOnHowl1();
		QTimer::singleShot(15000, this, SLOT(putOffHowl1()));
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkTestHowl2")
	{
		putOnHowl2();
		QTimer::singleShot(15000, this, SLOT(putOffHowl2()));
		slotElkRefresh();
		result = AskuModule::CommandSuccess;
	}
	else if(command == "setElkReset")
	{
		putResetElk();
		slotElkRefresh();
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
qint32 CanalAsku::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("CanalAsku: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();
	if(infoType == "RS485_SLAVE_SYNC")
	{
		if(data.contains("Config") || data.contains("State") || data.contains("Measure"))
		{
			QVariantMap config = data["Config"].toMap();
			QVariantMap state = data["State"].toMap();
			QVariantMap measure = data["Measure"].toMap();
			onSyncToSlave(config, state, measure);
		}

		result = AskuModule::CommandSuccess;
	}

	return result;
}

//---------------------------------------------------------------------------------
void CanalAsku::refreshPhase()
{
	QVariantMap data;
	data["InfoType"] = "PHASE_MODULES_INFO";
	data["ModuleTo"] = "dialog_phase";
	data["ModuleFrom"] = "canalasku";
	data["GprId"] = IDGPR();

	QVariantList prds;

	for(int n_prd = 0; n_prd < CA_N_TRANSMITTERS; n_prd++)
	{
		QVariantList modules;

		for(int n_module = 0; n_module < CA_N_MODULES_UMI; n_module++)
		{
			QVariantMap module;

			module["n_prd"] = n_prd;
			module["n_module"] = n_module;
			module["valid"] = true;//mainWgt->canalASKU->ca_device_state_dc[n_prd][n_module].getCurrentState();
			module["phase_set"] = paramUMI[n_prd][n_module].v5.phase_set;
			module["serial"] = moduleUmiSerial(paramUMI[n_prd][n_module].v5.serial_hi, paramUMI[n_prd][n_module].v5.serial_mi, paramUMI[n_prd][n_module].v5.serial_lo);
			module["phase_def"] = paramUMI[n_prd][n_module].v5.phase_def;

			modules << module;
		}

		prds << QVariant(modules);
	}

	data["Info"] = prds;

	emit sendInfoMessage(data, idAskuModuleGui);
}

//---------------------------------------------------------------------------------
void CanalAsku::makeMonitorPhase(CanalAskuData *cdata)
{
	if(!isMain())
	{
		m_canalAskuConfig.update = false;
		return;
	}

	if(!m_canalAskuConfig.monitor)
		return;
	
	QVariantMap data;
	data["InfoType"] = "PHASE_MODULES_INFO";
	data["ModuleTo"] = "dialog_phase";
	data["ModuleFrom"] = "canalasku";
	data["GprId"] = IDGPR();

	QVariantList prds;

	for(int n_prd = 0; n_prd < CA_N_TRANSMITTERS; n_prd++)
	{
		QVariantList modules;

		for(int n_module = 0; n_module < CA_N_MODULES_UMI; n_module++)
		{
			QVariantMap module;

			if(/*isUpdatePhase ||*/ cdata->getUpdatedUmi(CA_TRANSMITTER1 + n_prd, n_module))
			{
				module["n_prd"] = n_prd;
				module["n_module"] = n_module;
				module["valid"] = cdata->getParamUmiError(CA_TRANSMITTER1 + n_prd, n_module) == CA_NO_ERROR;
				module["phase_set"] = paramUMI[n_prd][n_module].v5.phase_set;
				module["serial"] = moduleUmiSerial(paramUMI[n_prd][n_module].v5.serial_hi, paramUMI[n_prd][n_module].v5.serial_mi, paramUMI[n_prd][n_module].v5.serial_lo);
				module["phase_def"] = paramUMI[n_prd][n_module].v5.phase_def;
			}

			modules << module;
		}

		prds << QVariant(modules);
	}

	data["Info"] = prds;

	emit sendInfoMessage(data, idAskuModuleGui);

	m_canalAskuConfig.update = false;
}


// ----------------------------------------------------------------------------
void CanalAsku::refreshPrdSelectorsPhase()
{
	makePrdSelectorsMessage("dialog_phase");
}

// ----------------------------------------------------------------------------
void CanalAsku::refreshPrdSelectorsCtrlPrd()
{
	makePrdSelectorsMessage("dialog_control_prd");
}

// ----------------------------------------------------------------------------
void CanalAsku::refreshPrdButtons()
{
	makePrdButtonsMessage();
}

// ----------------------------------------------------------------------------
void CanalAsku::refreshElkButtons()
{
	makeElkButtonsMessage();
}

// ----------------------------------------------------------------------------
void CanalAsku::makePrdSelectorsMessage(QString moduleTo)
{
	if(!isMain())
		return;

	QVariantMap data;

	data["InfoType"] = "ASKU_CONTROL_PRD_SELECTORS";
	data["ModuleTo"] = moduleTo;//"dialog_control_prd";
	data["ModuleFrom"] = "control";
	data["Selectors"] = m_selectors_prd;

//	qDebug() << data;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ----------------------------------------------------------------------------
void CanalAsku::makePrdButtonsMessage()
{
	if(!isMain())
		return;

	QVariantMap data;

	data["InfoType"] = "ASKU_CONTROL_PRD_BUTTONS";
	data["ModuleTo"] = "dialog_control_prd";
	data["ModuleFrom"] = "control";
	data["CommandSet"] = m_commands_prd;

//	qDebug() << data;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ----------------------------------------------------------------------------
void CanalAsku::makeElkButtonsMessage()
{
	if(!isMain())
		return;

	QVariantMap data;

	data["InfoType"] = "ASKU_CONTROL_ELK_BUTTONS";
	data["ModuleTo"] = "dialog_control_elk";
	data["ModuleFrom"] = "control";
	data["CommandSet"] = m_commands_elk;

//	qDebug() << data;

	emit sendInfoMessage(data, idAskuModuleGui);
}

//---------------------------------------------------------------------------------
void CanalAsku::startMonitorPhase()
{
	m_canalAskuConfig.monitor = true;
}

//---------------------------------------------------------------------------------
void CanalAsku::stopMonitorPhase()
{
	m_canalAskuConfig.monitor = false;
}

//---------------------------------------------------------------------------------
void CanalAsku::setNeedUpdatePhase()
{
	if(isMain())
		m_canalAskuConfig.update = true;
}

// ------------------------------------------------------------------
bool CanalAsku::isAllPrds(int n_prd)
{
	return (n_prd == 0);
}

// ------------------------------------------------------------------
bool CanalAsku::isExactPrd(int n_prd, int p)
{
	return (n_prd == p);
}

// ------------------------------------------------------------------
bool CanalAsku::isAllModules(int n_module)
{
	return n_module == 0;
}

// ------------------------------------------------------------------
bool CanalAsku::isHalf1Modules(int n_module)
{
	return (n_module == (CA_N_MODULES_UMI+1));
}

// ------------------------------------------------------------------
bool CanalAsku::isHalf2Modules(int n_module)
{
	return (n_module == (CA_N_MODULES_UMI+2));
}

// ------------------------------------------------------------------
bool CanalAsku::isHalfModules(int n_module)
{
	return isHalf1Modules(n_module) || isHalf2Modules(n_module);
}

// ------------------------------------------------------------------
bool CanalAsku::isExactModule(int n_module, int m)
{
	return n_module == (m+1);
}

// ------------------------------------------------------------------
bool CanalAsku::isHalf1Module(int m)
{
	int minm = 1;
	int maxm = CA_N_MODULES_UMI;
	int halfm = maxm/2;
	return ((m+1) >= minm && (m+1) <= halfm);
}

// ------------------------------------------------------------------
bool CanalAsku::isHalf2Module(int m)
{
	int maxm = CA_N_MODULES_UMI;
	int halfm = maxm/2;
	return ((m+1) > halfm && (m+1) <= maxm);
}

// ------------------------------------------------------------------
bool CanalAsku::isHalfModule(int n_module, int m)
{
	return (isHalf1Modules(n_module) && isHalf1Module(m)) || (isHalf2Modules(n_module) && isHalf2Module(m));
}

// ------------------------------------------------------------------
bool CanalAsku::isExactPrds(int n_prd)
{
	return !isAllPrds(n_prd);
}

// ------------------------------------------------------------------
bool CanalAsku::isExactModules(int n_module)
{
	return (!isAllModules(n_module) && !isHalf1Modules(n_module) && !isHalf2Modules(n_module));
}

// ------------------------------------------------------------------
void CanalAsku::slotElkRefresh()
{
	bool on = false, active = true;

	EUV_COMMAND euvCmd = elkCmd;

//	on = euvCmd.b1.BitsN.vklRpuLight;
//	m_commands_elk["osv_rpu"] = /*active ? (on ? "on" : "off") : "na"*/ "disable";

	on = euvCmd.b1.BitsN.vklPerimLight;
	m_commands_elk["osv_perim"] = active ? (on ? "on" : "off") : "na";

	on = euvCmd.b1.BitsN.vklFire;
	m_commands_elk["fire"] = active ? (on ? "on" : "off") : "na";

	on = euvCmd.b1.BitsN.vklSafe;
	m_commands_elk["guard"] = active ? (on ? "on" : "off") : "na";

	on = euvCmd.b1.BitsN.vklBlockCond;
	m_commands_elk["cond"] = active ? (on ? "on" : "off") : "na";

	QTimer::singleShot(0, this, SLOT(refreshElkButtons()));
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdRefresh(int n_prd, int n_module)
{
	m_commands_prd["n_prd"] = n_prd;
	m_commands_prd["n_module"] = n_module;

//	qDebug("slotPrdRefresh n_prd=%d n_mod=%d", n_prd, n_module);
	PRD_COMMAND xmtCmd = prdCmd;

	bool on = false, active = false;
	int t, m;
	int nVkl[CA_N_TRANSMITTERS], nVkl1[CA_N_TRANSMITTERS], nVkl2[CA_N_TRANSMITTERS];

	if(isAllPrds(n_prd))
	{
		active = (xmtCmd.prd[0].b1.BitsN.vkl380 == xmtCmd.prd[1].b1.BitsN.vkl380);
		on = xmtCmd.prd[0].b1.BitsN.vkl380;
	}
	else if(isExactPrd(n_prd,1))
	{
		active = true;
		on = xmtCmd.prd[0].b1.BitsN.vkl380;
	}
	else if(isExactPrd(n_prd,2))
	{
		active = true;
		on = xmtCmd.prd[1].b1.BitsN.vkl380;
	}

	m_commands_prd["p380v"] = active ? (on ? "on" : "off") : "na";

//	emit sigPrdPowerState(on, active);


	if(isAllPrds(n_prd))
	{
		active = (xmtCmd.prd[0].b2.BitsN.vklPumi1 || xmtCmd.prd[1].b2.BitsN.vklPumi1 || xmtCmd.prd[0].b2.BitsN.vklPumi2 || xmtCmd.prd[1].b2.BitsN.vklPumi2);
		on = (xmtCmd.prd[0].b2.BitsN.vklPumi2 || xmtCmd.prd[1].b2.BitsN.vklPumi2);
	}
	else if(isExactPrd(n_prd,1))
	{
		active = (xmtCmd.prd[0].b2.BitsN.vklPumi1 || xmtCmd.prd[0].b2.BitsN.vklPumi2);
		on = (xmtCmd.prd[0].b2.BitsN.vklPumi2);
	}
	else if(isExactPrd(n_prd,2))
	{
		active = (xmtCmd.prd[1].b2.BitsN.vklPumi1 || xmtCmd.prd[1].b2.BitsN.vklPumi2);
		on = (xmtCmd.prd[1].b2.BitsN.vklPumi2);
	}

	m_commands_prd["pumi"] = active ? (on ? "2" : "1") : "off";
//	emit sigPrdPumiState(on, active);


	if(isAllPrds(n_prd))
	{
		active = (xmtCmd.prd[0].b2.BitsN.vklHotRes == xmtCmd.prd[1].b2.BitsN.vklHotRes);
		on = (xmtCmd.prd[0].b2.BitsN.vklHotRes || xmtCmd.prd[1].b2.BitsN.vklHotRes);
	}
	else if(isExactPrd(n_prd,1))
	{
		active = true;
		on = (xmtCmd.prd[0].b2.BitsN.vklHotRes);
	}
	else if(isExactPrd(n_prd,2))
	{
		active = true;
		on = (xmtCmd.prd[1].b2.BitsN.vklHotRes);
	}

	m_commands_prd["hotres"] = active ? (on ? "on" : "off") : "na";
//	emit sigPrdHotResState(on, active);


	for(t = 0; t < CA_N_TRANSMITTERS; t++)
	{
		nVkl[t] = nVkl1[t] = nVkl2[t] = 0;

		for(m = 0; m < CA_N_MODULES_UMI; m++)
		{
			if(xmtCmd.prd[t].b3.module[m].BitsN.vklUmi)
			{
				nVkl[t]++;
				if(isHalf1Module(m))
					nVkl1[t]++;
				if(isHalf2Module(m))
					nVkl2[t]++;
			}
		}
	}

	if(isAllPrds(n_prd))
	{
		if(isAllModules(n_module))
		{
			active = ((nVkl[0] == 0) && (nVkl[1] == 0)) || ((nVkl[0] == CA_N_MODULES_UMI) && (nVkl[1] == CA_N_MODULES_UMI));
			on = (nVkl[0] == CA_N_MODULES_UMI) && (nVkl[1] == CA_N_MODULES_UMI);
		}
		else if(isHalf1Modules(n_module))
		{
			active = ((nVkl1[0] == 0) && (nVkl1[1] == 0)) || ((nVkl1[0] == (CA_N_MODULES_UMI/2)) && (nVkl1[1] == (CA_N_MODULES_UMI/2)));
			on = (nVkl1[0] == (CA_N_MODULES_UMI/2)) && (nVkl1[1] == (CA_N_MODULES_UMI/2));
		}
		else if(isHalf2Modules(n_module))
		{
			active = ((nVkl2[0] == 0) && (nVkl2[1] == 0)) || ((nVkl2[0] == (CA_N_MODULES_UMI/2)) && (nVkl2[1] == (CA_N_MODULES_UMI/2)));
			on = (nVkl2[0] == (CA_N_MODULES_UMI/2)) && (nVkl2[1] == (CA_N_MODULES_UMI/2));
		}
		else
		{
			active = (xmtCmd.prd[0].b3.module[n_module-1].BitsN.vklUmi == xmtCmd.prd[1].b3.module[n_module-1].BitsN.vklUmi);
			on = xmtCmd.prd[0].b3.module[n_module-1].BitsN.vklUmi;
		}
	}
	else if(isExactPrd(n_prd,1))
	{
		if(isAllModules(n_module))
		{
			active = (nVkl[0] == 0) || (nVkl[0] == CA_N_MODULES_UMI);
			on = (nVkl[0] == CA_N_MODULES_UMI);
		}
		else if(isHalf1Modules(n_module))
		{
			active = (nVkl1[0] == 0) || (nVkl1[0] == (CA_N_MODULES_UMI/2));
			on = (nVkl1[0] == (CA_N_MODULES_UMI/2));
		}
		else if(isHalf2Modules(n_module))
		{
			active = (nVkl2[0] == 0) || (nVkl2[0] == (CA_N_MODULES_UMI/2));
			on = (nVkl2[0] == (CA_N_MODULES_UMI/2));
		}
		else
		{
			active = true;
			on = xmtCmd.prd[0].b3.module[n_module-1].BitsN.vklUmi;
		}
	}
	else if(isExactPrd(n_prd,2))
	{
		if(isAllModules(n_module))
		{
			active = (nVkl[1] == 0) || (nVkl[1] == CA_N_MODULES_UMI);
			on = (nVkl[1] == CA_N_MODULES_UMI);
		}
		else if(isHalf1Modules(n_module))
		{
			active = (nVkl1[1] == 0) || (nVkl1[1] == (CA_N_MODULES_UMI/2));
			on = (nVkl1[1] == (CA_N_MODULES_UMI/2));
		}
		else if(isHalf2Modules(n_module))
		{
			active = (nVkl2[1] == 0) || (nVkl2[1] == (CA_N_MODULES_UMI/2));
			on = (nVkl2[1] == (CA_N_MODULES_UMI/2));
		}
		else
		{
			active = true;
			on = xmtCmd.prd[1].b3.module[n_module-1].BitsN.vklUmi;
		}
	}

	m_commands_prd["m380v"] = active ? (on ? "on" : "off") : "na";
//	emit sigPrdModule380State(on, active);


	for(t = 0; t < CA_N_TRANSMITTERS; t++)
	{
		nVkl[t] = nVkl1[t] = nVkl2[t] = 0;

		for(m = 0; m < CA_N_MODULES_UMI; m++)
		{
			if(xmtCmd.prd[t].b3.module[m].BitsN.vklPower)
			{
				nVkl[t]++;
				if(isHalf1Module(m))
					nVkl1[t]++;
				if(isHalf2Module(m))
					nVkl2[t]++;
			}
		}
	}

	if(isAllPrds(n_prd))
	{
		if(isAllModules(n_module))
		{
			active = ((nVkl[0] == 0) && (nVkl[1] == 0)) || ((nVkl[0] == CA_N_MODULES_UMI) && (nVkl[1] == CA_N_MODULES_UMI));
			on = (nVkl[0] == CA_N_MODULES_UMI) && (nVkl[1] == CA_N_MODULES_UMI);
		}
		else if(isHalf1Modules(n_module))
		{
			active = ((nVkl1[0] == 0) && (nVkl1[1] == 0)) || ((nVkl1[0] == (CA_N_MODULES_UMI/2)) && (nVkl1[1] == (CA_N_MODULES_UMI/2)));
			on = (nVkl1[0] == (CA_N_MODULES_UMI/2)) && (nVkl1[1] == (CA_N_MODULES_UMI/2));
		}
		else if(isHalf2Modules(n_module))
		{
			active = ((nVkl2[0] == 0) && (nVkl2[1] == 0)) || ((nVkl2[0] == (CA_N_MODULES_UMI/2)) && (nVkl2[1] == (CA_N_MODULES_UMI/2)));
			on = (nVkl2[0] == (CA_N_MODULES_UMI/2)) && (nVkl2[1] == (CA_N_MODULES_UMI/2));
		}
		else
		{
			active = (xmtCmd.prd[0].b3.module[n_module-1].BitsN.vklPower == xmtCmd.prd[1].b3.module[n_module-1].BitsN.vklPower);
			on = xmtCmd.prd[0].b3.module[n_module-1].BitsN.vklPower;
		}
	}
	else if(isExactPrd(n_prd,1))
	{
		if(isAllModules(n_module))
		{
			active = (nVkl[0] == 0) || (nVkl[0] == CA_N_MODULES_UMI);
			on = (nVkl[0] == CA_N_MODULES_UMI);
		}
		else if(isHalf1Modules(n_module))
		{
			active = (nVkl1[0] == 0) || (nVkl1[0] == (CA_N_MODULES_UMI/2));
			on = (nVkl1[0] == (CA_N_MODULES_UMI/2));
		}
		else if(isHalf2Modules(n_module))
		{
			active = (nVkl2[0] == 0) || (nVkl2[0] == (CA_N_MODULES_UMI/2));
			on = (nVkl2[0] == (CA_N_MODULES_UMI/2));
		}
		else
		{
			active = true;
			on = xmtCmd.prd[0].b3.module[n_module-1].BitsN.vklPower;
		}
	}
	else if(isExactPrd(n_prd,2))
	{
		if(isAllModules(n_module))
		{
			active = (nVkl[1] == 0) || (nVkl[1] == CA_N_MODULES_UMI);
			on = (nVkl[1] == CA_N_MODULES_UMI);
		}
		else if(isHalf1Modules(n_module))
		{
			active = (nVkl1[1] == 0) || (nVkl1[1] == (CA_N_MODULES_UMI/2));
			on = (nVkl1[1] == (CA_N_MODULES_UMI/2));
		}
		else if(isHalf2Modules(n_module))
		{
			active = (nVkl2[1] == 0) || (nVkl2[1] == (CA_N_MODULES_UMI/2));
			on = (nVkl2[1] == (CA_N_MODULES_UMI/2));
		}
		else
		{
			active = true;
			on = xmtCmd.prd[1].b3.module[n_module-1].BitsN.vklPower;
		}
	}

	m_commands_prd["power"] = active ? (on ? "on" : "off") : "na";
//	emit sigPrdModuleState(on, active);


	for(t = 0; t < CA_N_TRANSMITTERS; t++)
	{
		nVkl[t] = nVkl1[t] = nVkl2[t] = 0;

		for(m = 0; m < CA_N_MODULES_UMI; m++)
		{
			if(xmtCmd.prd[t].b3.module[m].BitsN.vklSVCh)
			{
				nVkl[t]++;
				if(isHalf1Module(m))
					nVkl1[t]++;
				if(isHalf2Module(m))
					nVkl2[t]++;
			}
		}
	}

	if(isAllPrds(n_prd))
	{
		if(isAllModules(n_module))
		{
			active = ((nVkl[0] == 0) && (nVkl[1] == 0)) || ((nVkl[0] == CA_N_MODULES_UMI) && (nVkl[1] == CA_N_MODULES_UMI));
			on = (nVkl[0] == CA_N_MODULES_UMI) && (nVkl[1] == CA_N_MODULES_UMI);
		}
		else if(isHalf1Modules(n_module))
		{
			active = ((nVkl1[0] == 0) && (nVkl1[1] == 0)) || ((nVkl1[0] == (CA_N_MODULES_UMI/2)) && (nVkl1[1] == (CA_N_MODULES_UMI/2)));
			on = (nVkl1[0] == (CA_N_MODULES_UMI/2)) && (nVkl1[1] == (CA_N_MODULES_UMI/2));
		}
		else if(isHalf2Modules(n_module))
		{
			active = ((nVkl2[0] == 0) && (nVkl2[1] == 0)) || ((nVkl2[0] == (CA_N_MODULES_UMI/2)) && (nVkl2[1] == (CA_N_MODULES_UMI/2)));
			on = (nVkl2[0] == (CA_N_MODULES_UMI/2)) && (nVkl2[1] == (CA_N_MODULES_UMI/2));
		}
		else
		{
			active = (xmtCmd.prd[0].b3.module[n_module-1].BitsN.vklSVCh == xmtCmd.prd[1].b3.module[n_module-1].BitsN.vklSVCh);
			on = xmtCmd.prd[0].b3.module[n_module-1].BitsN.vklSVCh;
		}
	}
	else if(isExactPrd(n_prd,1))
	{
		if(isAllModules(n_module))
		{
			active = (nVkl[0] == 0) || (nVkl[0] == CA_N_MODULES_UMI);
			on = (nVkl[0] == CA_N_MODULES_UMI);
		}
		else if(isHalf1Modules(n_module))
		{
			active = (nVkl1[0] == 0) || (nVkl1[0] == (CA_N_MODULES_UMI/2));
			on = (nVkl1[0] == (CA_N_MODULES_UMI/2));
		}
		else if(isHalf2Modules(n_module))
		{
			active = (nVkl2[0] == 0) || (nVkl2[0] == (CA_N_MODULES_UMI/2));
			on = (nVkl2[0] == (CA_N_MODULES_UMI/2));
		}
		else
		{
			active = true;
			on = xmtCmd.prd[0].b3.module[n_module-1].BitsN.vklSVCh;
		}
	}
	else if(isExactPrd(n_prd,2))
	{
		if(isAllModules(n_module))
		{
			active = (nVkl[1] == 0) || (nVkl[1] == CA_N_MODULES_UMI);
			on = (nVkl[1] == CA_N_MODULES_UMI);
		}
		else if(isHalf1Modules(n_module))
		{
			active = (nVkl1[1] == 0) || (nVkl1[1] == (CA_N_MODULES_UMI/2));
			on = (nVkl1[1] == (CA_N_MODULES_UMI/2));
		}
		else if(isHalf2Modules(n_module))
		{
			active = (nVkl2[1] == 0) || (nVkl2[1] == (CA_N_MODULES_UMI/2));
			on = (nVkl2[1] == (CA_N_MODULES_UMI/2));
		}
		else
		{
			active = true;
			on = xmtCmd.prd[1].b3.module[n_module-1].BitsN.vklSVCh;
		}
	}

	m_commands_prd["svch"] = active ? (on ? "on" : "off") : "na";
//	emit sigPrdSVChState(on, active);
/*
	int current, saved;
	if(isAllPrds(n_prd) || isAllModules(n_module) || isHalfModules(n_module))
	{
		active = false;
		current = saved = 0;
	}
	else if(!mainWgt->canalASKU->ca_device_state_dc[n_prd-1][n_module-1].getCurrentState())
	{
		active = false;
		current = saved = 0;
	}
	else
	{
		active = true;
		current = mainWgt->canalASKU->param_umi[n_prd-1][n_module-1].v4.phase_set;
		saved = 1;
	}

	emit sigPrdPhaseValues(current, saved, active);

	if(isExactPrds(n_prd) && isExactModules(n_module))
	{
		s_prd = n_prd;
		s_module = n_module;
		mainWgt->setMonitorPhase(n_prd-1, n_module-1);
	}
	else
	{
		s_prd = s_module = -1;
		mainWgt->setMonitorPhase();
	}
*/

	QTimer::singleShot(0, this, SLOT(refreshPrdButtons()));
}

// ------------------------------------------------------------------
/*void CanalAsku::slotPrdRefresh(int n_prd, int n_module)
{
	m_commands_prd["n_prd"] = n_prd;
	m_commands_prd["n_module"] = n_module;

	slotPrdRefresh();
}
*/
// ------------------------------------------------------------------
