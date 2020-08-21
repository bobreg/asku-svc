#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "powermeter.h"

// ------------------------------------------------------------------
PowerMeter::PowerMeter(QObject * parent) : QObject(parent)
{
	m_main = false;
	m_connected = false;
	m_ready = false;
	m_opened = false;
	m_applied = false;
	m_processing = false;
	m_measured = false;
	m_value = 0;
	m_koeff = 1;
	m_status = 0;
	m_pwmVersion = QString();
	m_pwmName = QString();
	m_pwmSerial = QString();

	m_processTimer = new QTimer(this);
	connect(m_processTimer, SIGNAL(timeout()), this, SLOT(processTimeout()));

	LogPowerInfo("PwmService started");
}

// ------------------------------------------------------------------
PowerMeter::~PowerMeter()
{
	if(m_processTimer)
	{
		delete m_processTimer;
		m_processTimer = 0;
	}
}

// ------------------------------------------------------------------
void PowerMeter::start()
{
	
}

// ------------------------------------------------------------------
void PowerMeter::stop()
{
	
}

// ------------------------------------------------------------------
void PowerMeter::onChangedMain(bool on)
{
	m_main = on;
	if(!m_main && m_processing)
	{
		m_processing = false;
		m_processTimer->stop();
	}
}

// ------------------------------------------------------------------
void PowerMeter::processTimeout()
{
	m_processTimer->stop();
	m_processing = false;
	m_measured = false;
	m_ready = false;
	LogPowerError("PwmService: timeout measure");
	onRefreshPwm();
}

// ------------------------------------------------------------------
void PowerMeter::cmdMeasure()
{
	LogPowerInfo("PwmService: start measure");

	if(!m_connected)
	{
		LogPowerError("PwmService: error service not connected");
	}
//	else if(!m_ready)
//	{
//		LogPowerError("PwmService: error service not ready");
//	}
	else if(m_main)
	{
		m_processing = true;
		m_processTimer->start(5000);
		sendAction("measure");
	}

	onRefreshPwm();
}

// ------------------------------------------------------------------
void PowerMeter::cmdReset()
{
	LogPowerInfo("PwmService: reset");

	if(!m_connected)
	{
		LogPowerError("PwmService: error service not connected");
	}
//	else if(!m_ready)
//	{
//		LogPowerError("PwmService: error service not ready");
//	}
	else if(m_main)
	{
		sendAction("reset");
	}

	onRefreshPwm();
}

// ------------------------------------------------------------------
void PowerMeter::sendAction(QString command, QStringList parameters)
{
	QVariantMap data;
	data["ModuleTo"] = "powermeter";
	data["ModuleFrom"] = "powermeter";
	data["Command"] = command;
	if(!parameters.isEmpty())
		data["Parameters"] = parameters;

	emit sendControlCommand(data);
}

// ------------------------------------------------------------------
void PowerMeter::sendControlAction(QString command, QStringList parameters)
{
	QVariantMap data;
	data["ModuleTo"] = "pwmcontrol";
	data["ModuleFrom"] = "powermeter";
	data["Command"] = command;
	if(!parameters.isEmpty())
		data["Parameters"] = parameters;

	emit sendControlCommand(data);
}

// ------------------------------------------------------------------
qint32 PowerMeter::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogPowerError("PowerMeter: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogPowerError("PowerMeter: empty command");
		return result;
	}

	LogPowerInfo("Command: %s", qPrintable(command));

	if(command == "refreshPwm")
	{
		QTimer::singleShot(0, this, SLOT(onRefreshPwm()));
		sendControlAction("version");
		sendAction("refresh");
		result = AskuModule::CommandSuccess;
	}
	if(command == "startMonitor")
	{
//		emit sigStartMonitor();
		QTimer::singleShot(0, this, SLOT(onRefreshPwm()));
		result = AskuModule::CommandSuccess;
	}
	if(command == "stopMonitor")
	{
//		emit sigStopMonitor();
		result = AskuModule::CommandSuccess;
	}
	if(command == "measure")
	{
		cmdMeasure();
		result = AskuModule::CommandSuccess;
	}
	if(command == "resetPwm")
	{
		cmdReset();
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
qint32 PowerMeter::processInfo(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogPowerError("PowerMeter: empty info data!");
		return result;
	}

	QString infoType = data["InfoType"].toString();
	if(infoType == "APPLICATION_VERSION")
	{
		if(data.contains("Info"))
		{
			QVariantMap values = data["Info"].toMap();
			m_pwmVersion = values["version"].toString();
			onRefreshPwm();
		}

		result = AskuModule::CommandSuccess;
	}
	if(infoType == "PWM_INFO")
	{
		if(data.contains("Info"))
		{
			QVariantMap values = data["Info"].toMap();

			if(m_processing)
			{
				m_processTimer->stop();
				m_processing = false;
			}

			m_pwmName    = values["name"].toString();
			m_pwmSerial  = values["serial"].toString();
			m_ready      = values["ready"].toBool();
			m_opened     = values["opened"].toBool();
			m_applied    = values["applied"].toBool();
			m_processing = values["processing"].toBool();
			m_fault      = values["fault"].toBool();
			m_measured   = values["result"].toBool();
			m_value      = values["value"].toString().toDouble();
			m_koeff      = values["koeff"].toString().toDouble();

			onRefreshPwm();
		}

		result = AskuModule::CommandSuccess;
	}

	return result;
}

// ------------------------------------------------------------------
void PowerMeter::refreshState(QVariantMap info)
{
	QVariantMap data;
	data["InfoType"] = "PWM_INFO";
	data["ModuleTo"] = "dialog_powermeter";
	data["ModuleFrom"] = "powermeter";
	data["GprId"] = IDGPR();
	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

// ------------------------------------------------------------------
void PowerMeter::syncToSlave(QVariantMap config)
{
	LogPowerInfo("PowerMeter::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "PWM_SLAVE_SYNC";
	data["ModuleTo"] = "powermeter";
	data["ModuleFrom"] = "powermeter";
	data["GprId"] = IDGPR();
	data["Config"] = config;

	emit sendInfoMessage(data, idAskuModuleSvc);
}

// ------------------------------------------------------------------
void PowerMeter::onConnected()
{
	LogPowerInfo("PwmService: service connected");
	m_connected = true;
	sendControlAction("version");
	sendAction("refresh");
	onRefreshPwm();
}

// ------------------------------------------------------------------
void PowerMeter::onDisconnected()
{
	LogPowerInfo("PwmService: service disconnected");
	m_connected = false;
	m_opened = false;
	m_applied = false;
	m_processing = false;
	m_pwmName.clear();
	m_pwmSerial.clear();
	m_pwmVersion.clear();
	m_processTimer->stop();
	onRefreshPwm();
}

// ------------------------------------------------------------------
void PowerMeter::onRefreshPwm()
{
	algorithmPwm();

	if(!m_main)
		return;

	QVariantMap info;

	if(!m_connected)
	{
		info["Link"] = "НЕТ";
		info["Version"] = "";
		info["Status"]  = "";
		info["Value"] = "";
		info["Name"] = "";
		info["pushMeasure"] = -1;
		info["pushReset"] = -1;
	}
	else
	{
		info["Link"] = "Установлена";
		info["Version"] = m_pwmVersion;

		if(!m_opened)
			info["Status"]  = "Не подключен";
		else if(!m_applied)
			info["Status"]  = "Не настроен";
		else if(!m_ready)
			info["Status"]  = "Не готов";
		else if(m_processing)		
			info["Status"]  = "Измерение";
		else
			info["Status"]  = "Готов";

		if(m_opened && m_applied)
		{
			info["Name"] = m_pwmName.replace(",","\n");
			info["Koeff"] = QString("%1").arg(m_koeff, 0, 'f', 6);
		}
		else
		{
			info["Name"] = "";
			info["Koeff"] = "";
		}

		if(m_opened && m_applied)
		{
			if(m_processing)
			{
				info["Value"] = "...";
				info["Power"] = "...";
			}
			else if(m_measured)
			{
				info["Value"] = QString("%1").arg(m_value, 0, 'f', 6);
				info["Power"] = QString("%1").arg(calc_power(m_value, m_koeff), 0, 'f', 0);
			}
			else
			{
				info["Value"] =  "- не измерено -";
				info["Power"] =  "- не измерено -";
			}
		}
		else
		{
			info["Value"] =  "";
			info["Power"] =  "";
		}

		info["pushMeasure"] = 0;
		info["pushReset"] = 0;
	}

	refreshState(info);
}

// ------------------------------------------------------------------
void PowerMeter::algorithmPwm()
{
	if(!m_connected)
		bPwmState["connected"] = ELEM_AVAR;
	else
		bPwmState["connected"] = ELEM_NORMA;

	if(!m_connected)
		bPwmState["opened"] = ELEM_NOT;
	else if(!m_opened)
		bPwmState["opened"] = ELEM_AVAR;
	else
		bPwmState["opened"] = ELEM_NORMA;

	if(!m_connected)
		bPwmState["ObSost"] = ELEM_NOT;
	else if(!m_opened || !m_ready)
		bPwmState["ObSost"] = ELEM_AVAR;
	else if(!m_applied)
		bPwmState["ObSost"] = ELEM_ERROR;
	else 
		bPwmState["ObSost"] = ELEM_NORMA;

	if(!m_connected || !m_opened || !m_ready || !m_applied || !m_processing)
		bPwmState["measuring"] = ELEM_NOT;
	else
		bPwmState["measuring"] = ELEM_NORMA;
	
	if(!m_measured)
		bPwmState["value"].setText("") = ELEM_NOT;
	else
		bPwmState["value"].setText(QString("%1").arg(m_value, 0, 'f', 6)) = ELEM_NORMA;

	if(!m_measured)
		bPwmState["power"].setText("") = ELEM_NOT;
	else
	{
		double pwr = calc_power(m_value, m_koeff);
		bPwmState["power"].setText(QString("%1").arg(pwr, 0, 'f', 0));

		double fail = (double)m_setup.pwm.pwrFail;
		double low  = (double)m_setup.pwm.pwrLow;
		double gate = (double)m_setup.pwm.pwrGate;

		if(pwr < gate)
		{
			bPwmState["power"] = ELEM_NOT;
		}
		else if(pwr < (fail - gate))
		{
			bPwmState["power"] = ELEM_AVAR;
		}
		else if(pwr >= (fail - gate) && pwr < (fail + gate))
		{
			if(bPwmState["power"] == ELEM_AVAR)
				bPwmState["power"] = ELEM_AVAR;
			else
				bPwmState["power"] = ELEM_ERROR;
		}
		else if(pwr >= (fail + gate) && pwr < (low - gate))
		{
			bPwmState["power"] = ELEM_ERROR;
		}
		else if(pwr >= (low - gate) && pwr < (low + gate))
		{
			if(bPwmState["power"] == ELEM_ERROR)
				bPwmState["power"] = ELEM_ERROR;
			else
				bPwmState["power"] = ELEM_NORMA;
		}
		else if(pwr >= (low + gate))
		{
			bPwmState["power"] = ELEM_NORMA;
		}
		else
		{
			bPwmState["power"] = ELEM_NOT;
		}
	}
//		bPwmState["power"].setText(QString("%1").arg(calc_power(m_value, m_koeff), 0, 'f', 0)) = ELEM_NORMA;

	emit sigState(bPwmState, bPwmValue);
}

// ------------------------------------------------------------------
double PowerMeter::calc_power(double value, double koeff)
{
	return fabs(value / 1000.0) * pow(10.0, koeff / 10.0);
}

// ------------------------------------------------------------------
