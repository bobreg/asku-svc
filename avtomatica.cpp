#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "avtomatica.h"

// ------------------------------------------------------------------
Avtomatica::Avtomatica(QObject * parent) : QObject(parent)
{
	m_main = false;
	m_connected = false;
	m_ready = false;
	m_status = 0;
	m_avtVersion = QString();

	m_processTimer = new QTimer(this);
	connect(m_processTimer, SIGNAL(timeout()), this, SLOT(processTimeout()));

	LogPowerInfo("AvtService started");
}

// ------------------------------------------------------------------
Avtomatica::~Avtomatica()
{
	if(m_processTimer)
	{
		delete m_processTimer;
		m_processTimer = 0;
	}
}

// ------------------------------------------------------------------
void Avtomatica::start()
{
	
}

// ------------------------------------------------------------------
void Avtomatica::stop()
{
	
}

// ------------------------------------------------------------------
void Avtomatica::onChangedMain(bool on)
{
	m_main = on;
}

// ------------------------------------------------------------------
void Avtomatica::processTimeout()
{
	
}

// ------------------------------------------------------------------
void Avtomatica::cmdQuery()
{
	LogPowerInfo("AvtService: start measure");

	if(!m_connected)
	{
		LogPowerError("AvtService: error service not connected");
	}
	else if(m_main)
	{
		sendAction("query");
	}

	onRefreshAvt();
}

// ------------------------------------------------------------------
void Avtomatica::sendAction(QString command, QStringList parameters)
{
	QVariantMap data;
	data["ModuleTo"] = "avtomatica";
	data["ModuleFrom"] = "avtomatica";
	data["Command"] = command;
	if(!parameters.isEmpty())
		data["Parameters"] = parameters;

	emit sendControlCommand(data);
}

// ------------------------------------------------------------------
void Avtomatica::sendControlAction(QString command, QStringList parameters)
{
	QVariantMap data;
	data["ModuleTo"] = "avtcontrol";
	data["ModuleFrom"] = "avtomatica";
	data["Command"] = command;
	if(!parameters.isEmpty())
		data["Parameters"] = parameters;

	emit sendControlCommand(data);
}

// ------------------------------------------------------------------
qint32 Avtomatica::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("Avtomatica: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogError("Avtomatica: empty command");
		return result;
	}

	LogInfo("Command: %s", qPrintable(command));

	if(command == "refreshAvt")
	{
		QTimer::singleShot(0, this, SLOT(onRefreshAvt()));
		sendControlAction("version");
		sendAction("refresh");
		result = AskuModule::CommandSuccess;
	}
	if(command == "startMonitor")
	{
//		emit sigStartMonitor();
		QTimer::singleShot(0, this, SLOT(onRefreshAvt()));
		result = AskuModule::CommandSuccess;
	}
	if(command == "stopMonitor")
	{
//		emit sigStopMonitor();
		result = AskuModule::CommandSuccess;
	}
	if(command == "query")
	{
		cmdQuery();
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
qint32 Avtomatica::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("Avtomatica: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();
	if(infoType == "APPLICATION_VERSION")
	{
		if(data.contains("Info"))
		{
			QVariantMap values = data["Info"].toMap();
			m_avtVersion = values["version"].toString();
			onRefreshAvt();
		}

		result = AskuModule::CommandSuccess;
	}
	if(infoType == "AVT_INFO")
	{
		if(data.contains("Info"))
		{
			QVariantMap values = data["Info"].toMap();

			bAvtState["avt@requisites"] = stringToState(values["avt@requisites"].toString());
			bAvtValue["avt@devicename"] = values["avt@devicename"].toString();
			bAvtValue["avt@deviceserial"] = values["avt@deviceserial"].toUInt();

			bAvtState["avt@state"] = stringToState(values["avt@state"].toString());
			bAvtValue["avt@keys_actual"] = values["avt@keys_actual"].toUInt();
			bAvtValue["avt@keys_next"] = values["avt@keys_next"].toUInt();
			bAvtValue["avt@cat_unexpended"] = values["avt@cat_unexpended"].toUInt();
			bAvtValue["avt@cat_expended"] = values["avt@cat_expended"].toUInt();

			bAvtState["avt@B1_fail"] = stringToState(values["avt@B1_fail"].toString());
			bAvtState["avt@B1_link_B2"] = stringToState(values["avt@B1_link_B2"].toString());
			bAvtState["avt@B1_pult"] = stringToState(values["avt@B1_pult"].toString());

			bAvtState["avt@B2_fail"] = stringToState(values["avt@B2_fail"].toString());
			bAvtState["avt@B2_link_B3"] = stringToState(values["avt@B2_link_B3"].toString());
			bAvtState["avt@B2_uvk"] = stringToState(values["avt@B2_uvk"].toString());

			bAvtState["avt@B3_fail"] = stringToState(values["avt@B3_fail"].toString());
			bAvtState["avt@B3_link_shdu"] = stringToState(values["avt@B3_link_shdu"].toString());
			bAvtState["avt@B3_gsch"] = stringToState(values["avt@B3_gsch"].toString());
			bAvtState["avt@B3_shdu_no_connect"] = stringToState(values["avt@B3_shdu_no_connect"].toString());
			bAvtState["avt@B3_shdu_fail"] = stringToState(values["avt@B3_shdu_fail"].toString());
			bAvtState["avt@B3_shdu_not_loaded"] = stringToState(values["avt@B3_shdu_not_loaded"].toString());
			bAvtState["avt@B3_link_inter"] = stringToState(values["avt@B3_link_inter"].toString());

			onRefreshAvt();
		}

		result = AskuModule::CommandSuccess;
	}

	return result;
}

// ------------------------------------------------------------------
void Avtomatica::refreshState(QVariantMap info)
{
	QVariantMap data;
	data["InfoType"] = "AVT_INFO";
	data["ModuleTo"] = "dialog_avtomatica";
	data["ModuleFrom"] = "avtomatica";
	data["GprId"] = IDGPR();
	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void Avtomatica::syncToSlave(QVariantMap config)
{
	LogInfo("Avtomatica::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "AVT_SLAVE_SYNC";
	data["ModuleTo"] = "avtomatica";
	data["ModuleFrom"] = "avtomatica";
	data["GprId"] = IDGPR();
	data["Config"] = config;

	emit sendInfoMessage(data, idAskuModuleSvc);
}

// ------------------------------------------------------------------
void Avtomatica::onConnected()
{
	LogPowerInfo("AvtService: service connected");
	m_connected = true;
	sendControlAction("version");
	sendAction("refresh");
	onRefreshAvt();
}

// ------------------------------------------------------------------
void Avtomatica::onDisconnected()
{
	LogPowerInfo("AvtService: service disconnected");
	m_connected = false;
	m_avtVersion.clear();
	m_processTimer->stop();
	onRefreshAvt();
}

// ------------------------------------------------------------------
void Avtomatica::onRefreshAvt()
{
	algorithmAvt();

	if(!m_main)
		return;

	QVariantMap info;

	if(!m_connected)
	{
		info["Link"] = "НЕТ";
		info["Version"] = "";
		info["Status"]  = "";
		info["DeviceType"] = "";
		info["KeyActual"] = "";
		info["KeyNext"] = "";
		info["CatUnexpended"] = "";
		info["CatExpended"] = "";
		info["B1state"] = "";
		info["B1pult"] = "";
		info["B1linkB2"] = "";
		info["B2state"] = "";
		info["B2uvk"] = "";
		info["B2linkB3"] = "";
		info["B3state"] = "";
		info["B3gsch"] = "";
		info["B3link"] = "";
	}
	else
	{
		info["Link"] = "Установлена";
		info["Version"] = m_avtVersion;

		if(bAvtState["avt@state"] == ELEM_NORMA)
			info["Status"] = "Состояние получено";
		else if(bAvtState["avt@requisites"] == ELEM_NORMA)
			info["Status"] = "Реквизиты получены";
		else
			info["Status"] = "Нет ответа";

		if(bAvtState["avt@requisites"] == ELEM_NORMA)
			info["DeviceType"] = QString("%1 №%2").arg(bAvtValue["avt@devicename"].toString()).arg(bAvtValue["avt@deviceserial"].toUInt());
		else
			info["DeviceType"] = "---";

		if(bAvtState["avt@state"] == ELEM_NORMA)
		{
			info["KeyActual"] = QString("%1").arg(bAvtValue["avt@keys_actual"].toUInt());
			info["KeyNext"] = QString("%1").arg(bAvtValue["avt@keys_next"].toUInt());
			info["CatUnexpended"] = QString("%1").arg(bAvtValue["avt@cat_unexpended"].toUInt());
			info["CatExpended"] = QString("%1").arg(bAvtValue["avt@cat_expended"].toUInt());
		}
		else
		{
			info["KeyActual"] = "";
			info["KeyNext"] = "";
			info["CatUnexpended"] = "";
			info["CatExpended"] = "";
		}

		if(bAvtState["avt@state"] == ELEM_NORMA)
		{
			if(bAvtState["avt@B1_fail"] == ELEM_NORMA)
				info["B1state"] = "ИСПРАВЕН";
			else
				info["B1state"] = "НЕ ИСПРАВЕН";

			if(bAvtState["avt@B1_pult"] == ELEM_NORMA)
				info["B1pult"] = "ИСПРАВЕН";
			else
				info["B1pult"] = "НЕ ИСПРАВЕН";

			if(bAvtState["avt@B1_link_B2"] == ELEM_NORMA)
			{
				info["B1linkB2"] = "ИСПРАВЕН";

				if(bAvtState["avt@B2_fail"] == ELEM_NORMA)
					info["B2state"] = "ИСПРАВЕН";
				else
					info["B2state"] = "НЕ ИСПРАВЕН";

				if(bAvtState["avt@B2_uvk"] == ELEM_NORMA)
					info["B2uvk"] = "ИСПРАВЕН";
				else
					info["B2uvk"] = "НЕ ИСПРАВЕН";
					
				if(bAvtState["avt@B2_link_B3"] == ELEM_NORMA)
				{
					info["B2linkB3"] = "ИСПРАВЕН";

					if(bAvtState["avt@B3_fail"] == ELEM_NORMA)
						info["B3state"] = "ИСПРАВЕН";
					else
						info["B3state"] = "НЕ ИСПРАВЕН";

					if(bAvtState["avt@B3_gsch"] == ELEM_NORMA)
						info["B3gsch"] = "ИСПРАВЕН";
					else
						info["B3gsch"] = "НЕ ИСПРАВЕН";

					if(bAvtState["avt@B3_link_inter"] == ELEM_NORMA)
						info["B3link"] = "ИСПРАВЕН";
					else
						info["B3link"] = "НЕ ИСПРАВЕН";
				}
				else
				{
					info["B2linkB3"] = "НЕ ИСПРАВЕН";
					info["B3state"] = "---";
					info["B3gsch"] = "---";
					info["B3link"] = "---";
				}
			}
			else
			{
				info["B1linkB2"] = "НЕИСПРАВЕН";
				info["B2state"] = "---";
				info["B2uvk"] = "---";
				info["B2linkB3"] = "---";
				info["B3state"] = "---";
				info["B3gsch"] = "---";
				info["B3link"] = "---";
			}
		}
		else
		{
			info["B1state"] = "---";
			info["B1pult"] = "---";
			info["B1linkB2"] = "---";
			info["B2state"] = "---";
			info["B2uvk"] = "---";
			info["B2linkB3"] = "---";
			info["B3state"] = "---";
			info["B3gsch"] = "---";
			info["B3link"] = "---";
		}
	}

	refreshState(info);
}

// ------------------------------------------------------------------
void Avtomatica::algorithmAvt()
{
/*
	if(!m_connected)
		bAvtState["connected"] = ELEM_AVAR;
	else
		bAvtState["connected"] = ELEM_NORMA;

	if(!m_connected)
		bAvtState["opened"] = ELEM_NOT;
	else if(!m_opened)
		bAvtState["opened"] = ELEM_AVAR;
	else
		bAvtState["opened"] = ELEM_NORMA;

	if(!m_connected)
		bAvtState["ObSost"] = ELEM_NOT;
	else if(!m_opened || !m_ready)
		bAvtState["ObSost"] = ELEM_AVAR;
	else if(!m_applied)
		bAvtState["ObSost"] = ELEM_ERROR;
	else 
		bAvtState["ObSost"] = ELEM_NORMA;

	if(!m_connected || !m_opened || !m_ready || !m_applied || !m_processing)
		bAvtState["measuring"] = ELEM_NOT;
	else
		bAvtState["measuring"] = ELEM_NORMA;
	
	if(!m_measured)
		bAvtState["value"].setText("") = ELEM_NOT;
	else
		bAvtState["value"].setText(QString("%1").arg(m_value, 0, 'f', 6)) = ELEM_NORMA;

	if(!m_measured)
		bAvtState["power"].setText("") = ELEM_NOT;
	else
	{
		double pwr = calc_power(m_value, m_koeff);
		bAvtState["power"].setText(QString("%1").arg(pwr, 0, 'f', 0));

		double fail = (double)m_setup.pwm.pwrFail;
		double low  = (double)m_setup.pwm.pwrLow;
		double gate = (double)m_setup.pwm.pwrGate;

		if(pwr < gate)
		{
			bAvtState["power"] = ELEM_NOT;
		}
		else if(pwr < (fail - gate))
		{
			bAvtState["power"] = ELEM_AVAR;
		}
		else if(pwr >= (fail - gate) && pwr < (fail + gate))
		{
			if(bAvtState["power"] == ELEM_AVAR)
				bAvtState["power"] = ELEM_AVAR;
			else
				bAvtState["power"] = ELEM_ERROR;
		}
		else if(pwr >= (fail + gate) && pwr < (low - gate))
		{
			bAvtState["power"] = ELEM_ERROR;
		}
		else if(pwr >= (low - gate) && pwr < (low + gate))
		{
			if(bAvtState["power"] == ELEM_ERROR)
				bAvtState["power"] = ELEM_ERROR;
			else
				bAvtState["power"] = ELEM_NORMA;
		}
		else if(pwr >= (low + gate))
		{
			bAvtState["power"] = ELEM_NORMA;
		}
		else
		{
			bAvtState["power"] = ELEM_NOT;
		}
	}
//		bAvtState["power"].setText(QString("%1").arg(calc_power(m_value, m_koeff), 0, 'f', 0)) = ELEM_NORMA;
*/
	emit sigState(bAvtState, bAvtValue);
}

// ------------------------------------------------------------------
