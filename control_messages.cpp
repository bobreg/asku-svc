#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "control.h"
#include "viewer.h"

// ----------------------------------------------------------------------------
void AskuGprControl::makeMessage()
{
	if(m_mainGpr != NUM_GPR())
		return;

	QVariantMap data;

	data["InfoType"] = "ASKU_CONTROL";
	data["ModuleTo"] = "control";
	data["ModuleFrom"] = "control";

	QVariantMap reg;
	reg["main"] = m_mainGpr;
	reg["regime"] = m_regime;
	reg["regimeName"] = regimeName(m_regime);
	data["RegimeSet"] = reg;

//	qDebug() << data;

	emit sendInfoMessage(data, idAskuModuleSvc);
	emit sendInfoMessage(data, idAskuModuleGui);
}

// ----------------------------------------------------------------------------
void AskuGprControl::makeControlPanelMessage()
{
	if(m_mainGpr != NUM_GPR())
		return;

	QVariantMap data;

	data["InfoType"] = "ASKU_CONTROL_PANEL";
	data["ModuleTo"] = "dialog_control_panel";
	data["ModuleFrom"] = "control";
	data["CommandSet"] = m_commands;

	QVariantMap raf;
	data["RafSet"] = raf;

//	qDebug() << data;

	emit sendInfoMessage(data, idAskuModuleSvc);
	emit sendInfoMessage(data, idAskuModuleGui);
}

// ----------------------------------------------------------------------------
void AskuGprControl::makeRafOnOffMessage()
{
	if(m_mainGpr != NUM_GPR())
		return;

	QVariantMap data;

	data["InfoType"] = "ASKU_CONTROL_PANEL";
	data["ModuleTo"] = "dialog_control_panel";
	data["ModuleFrom"] = "control";

	QVariantMap raf;
	raf["status"] = m_OnOffRafStatus;
	raf["percent"] = m_OnOffRafCounterFinish != 0 ? (100 * m_OnOffRafCounter / m_OnOffRafCounterFinish) : 0;
	data["RafStatusSet"] = raf;

	QVariantMap map;
	map["updated"] = m_rafMessagesUpdated;
	map["messages"] = m_rafMessages.toList();
 
	data["MessageSet"] = map;

//	qDebug() << data;

	emit sendInfoMessage(data, idAskuModuleSvc);
	emit sendInfoMessage(data, idAskuModuleGui);
}

// ----------------------------------------------------------------------------
void AskuGprControl::makeSyncMessage()
{
	QVariantMap data;

	data["InfoType"] = "ASKU_SYNC_INFO";
	data["ModuleTo"] = "control";
	data["ModuleFrom"] = "control";

	QVariantMap info;
	info["idgpr"] = IDGPR();
	info["main"] = m_mainGpr;
	info["regime"] = m_regime;
	info["command"] = m_changeCmd;
	info["stamp"] = m_stamp++;
	data["Sync"] = info;

	emit sendSyncMessage(data, idAskuModuleSvc);

	static int a = 0;
	if(a == 0)
		emit sendSyncMessage(data, idAskuModuleGui);
	if(a++ > 10)
		a = 0;
}

// ----------------------------------------------------------------------------
void AskuGprControl::makeVersionMessage()
{
	QVariantMap data;

	data["InfoType"] = "APPLICATION_VERSION";
	data["ModuleTo"] = "dialog_about";
	data["ModuleFrom"] = "control";
	data["GprId"] = IDGPR();

	QVariantMap info;
	info["version"] = qApp->applicationVersion();
	data["Info"] = info;

	emit sendInfoMessage(data);
}

// ----------------------------------------------------------------------------
