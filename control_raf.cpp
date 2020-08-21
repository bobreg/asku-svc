#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "control.h"
#include "viewer.h"

// ----------------------------------------------------------------------------
AskuCommandList::AskuCommandList() : QList<AskuOnOffCommand>()
{
	clear();
}

// ----------------------------------------------------------------------------
AskuOnOffCommand AskuCommandList::operator[](QString device)
{
	for(AskuCommandList::const_iterator cmd = constBegin(); cmd != constEnd(); ++cmd)
		if((*cmd).device == device)
			return (*cmd);
	return AskuOnOffCommand();
}

// ----------------------------------------------------------------------------
AskuOnOffCommand & AskuCommandList::operator[](int i)
{
	return QList::operator[](i);
}
// ----------------------------------------------------------------------------
const AskuOnOffCommand & AskuCommandList::operator[](int i) const
{
	return QList::operator[](i);
}

// ----------------------------------------------------------------------------
void AskuCommandList::setStatus(QString st)
{
	for(qint32 i = 0; i < count(); i++)
	{
		QList::operator[](i).status = st;
	}
}

// ----------------------------------------------------------------------------
AskuRlkRafMessage::AskuRlkRafMessage()
{
	clear();
}

// ----------------------------------------------------------------------------
QVariantList AskuRlkRafMessage::toList()
{
	QVariantList list;
	for(qint32 i = 0; i < count(); i++)
		list << operator[](i).toList();
	return list;
}

// ----------------------------------------------------------------------------
AskuOnOffRaf::AskuOnOffRaf()
{
	m_OnOffRafInterval = 100;
	m_OnOffRafMultiplier = 1000 / m_OnOffRafInterval;
	m_OnOffRafCounter = 0;
	m_OnOffRafCounterFinish = 0;
	m_OnOffRafStatus = 0;

	m_timeOn << AskuOnOffCommand("start", 0, "Включение РАФ");
	m_timeOn << AskuOnOffCommand("drive", 0, "Включение БЭП", "БЭП включен", "БЭП не включен");
	m_timeOn << AskuOnOffCommand("vrl", 32, "Включение МВРЛ", "МВРЛ включен", "МВРЛ не включен");
	m_timeOn << AskuOnOffCommand("pumi", 30, "Включение ПУМ", "ПУМ включен", "ПУМ не включен");
	m_timeOn << AskuOnOffCommand("prd", 32, "Включение УМИ", "УМИ включены", "УМИ не включены");
	m_timeOn << AskuOnOffCommand("finish", 60, "", "Успешно", "Ошибка");

	m_timeOff << AskuOnOffCommand("start", 0, "Отключение РАФ");
	m_timeOff << AskuOnOffCommand("vrl", 0, "Отключение МВРЛ", "МВРЛ отключен", "МВРЛ не отключен");
	m_timeOff << AskuOnOffCommand("prd", 0, "Отключение УМИ", "УМИ отключены", "УМИ не отключены");
	m_timeOff << AskuOnOffCommand("pumi", 0, "Отключение ПУМ", "ПУМ отключен", "ПУМ не отключен");
	m_timeOff << AskuOnOffCommand("drive", 0, "Отключение БЭП", "БЭП отключен", "БЭП не отключен");
	m_timeOff << AskuOnOffCommand("finish", 30, "", "Успешно", "Ошибка");
}

// ----------------------------------------------------------------------------
void AskuGprControl::onRafOffFinish()
{
	AddSwitchMes("АСКУ", "Отключение режима РАФ завершено");
}

// ----------------------------------------------------------------------------
void AskuGprControl::onRafOnFinish()
{
	AddSwitchMes("АСКУ", "Включение режима РАФ завершено");
}

// ----------------------------------------------------------------------------
void AskuGprControl::rafOnOffTimeout()
{
	if(m_OnOffRafStatus > 0)
	{
		m_OnOffRafCounter++;
//		qDebug("rafOn %d", m_OnOffRafCounter);

		for(qint32 i = 0; i < m_timeOn.count(); i++)
		{
			AskuOnOffCommand & cmd = m_timeOn[i];

			if(m_OnOffRafCounter >= (cmd.time * m_OnOffRafMultiplier))
			{
				if(cmd.device == "start" && cmd.status == "off")
				{
					m_rafMessages << AskuRafMessage(cmd.textCommand, QString("start"), QString().arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
					m_rafMessagesUpdated = QDateTime::currentDateTime();

					cmdSetRaf();

					cmdSetResetAvarComm();
					cmdSetResetAvarPrd1();
					cmdSetResetAvarPrd2();
					cmdSetResetAvarPrm();
					cmdSetResetAvarBep();
					cmdSetResetAvarSvo();

					cmd.status = "on";
				}
				if(cmd.device == "drive")
				{
					if(cmd.status == "off")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						//command drive on
						cmdSetBepOn();
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["drive_on"] == ELEM_NORMA)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "on";
						}
					}
				}
				if(cmd.device == "vrl")
				{
					if(cmd.status == "off")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						cmdSetVrl1();	//command vrl on
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["vrl"] == ELEM_NORMA)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "on";
						}
					}
				}
				if(cmd.device == "pumi")
				{
					if(cmd.status == "off")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						//command pumi on
						cmdSetPumi1();
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["pum1_on"] == ELEM_NORMA || m_kvit["pum2_on"] == ELEM_NORMA)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "on";
						}
					}
				}
				if(cmd.device == "prd")
				{
					if(cmd.status == "off")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						//command prd on
						cmdSetPrdOn();
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["prd1_on"] == ELEM_NORMA && m_kvit["prd2_on"] == ELEM_NORMA)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "on";
						}
					}
				}
				if(cmd.device == "prd1")
				{
					if(cmd.status == "off")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						//command prd1 on
						cmdSetPrd1On();
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["prd1_on"] == ELEM_NORMA)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "on";
						}
					}
				}
				if(cmd.device == "prd2")
				{
					if(cmd.status == "off")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						//command prd2 on
						cmdSetPrd2On();
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["prd2_on"] == ELEM_NORMA)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "on";
						}
					}
				}
				if(cmd.device == "finish" && cmd.status == "off")
				{
					if(m_kvit["drive_on"] == ELEM_NORMA && 
						m_kvit["prd1_on"] == ELEM_NORMA && 
						m_kvit["prd2_on"] == ELEM_NORMA &&
						(m_kvit["pum1_on"] == ELEM_NORMA || m_kvit["pum2_on"] == ELEM_NORMA) &&
						m_kvit["vrl"] == ELEM_NORMA)
						m_rafMessages << AskuRafMessage(cmd.textKvit, QString("complete"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
					else
					{
						m_rafMessages << AskuRafMessage(cmd.textError, QString("error"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						for(qint32 j = 0; j < m_timeOn.count(); j++)
						{
							AskuOnOffCommand & err = m_timeOn[j];
							if(err.device != "finish" && err.device != "start" && err.status == "wait")
								m_rafMessages << AskuRafMessage(err.textError, QString("error"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						}
					}
					m_rafMessagesUpdated = QDateTime::currentDateTime();
					m_OnOffRafStatus = 0;
					onRafOnFinish();
					cmd.status = "on";
				}
			}
		}
	}
	else if(m_OnOffRafStatus < 0)
	{
		m_OnOffRafCounter++;
//		qDebug("rafOff %d", m_OnOffRafCounter);

		for(qint32 i = 0; i < m_timeOff.count(); i++)
		{
			AskuOnOffCommand & cmd = m_timeOff[i];

			if(m_OnOffRafCounter >= (cmd.time * m_OnOffRafMultiplier))
			{
				if(cmd.device == "start" && cmd.status == "on")
				{
					m_rafMessages << AskuRafMessage(cmd.textCommand, QString("start"), QString().arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
					m_rafMessagesUpdated = QDateTime::currentDateTime();
					cmd.status = "off";
				}
				if(cmd.device == "drive")
				{
					if(cmd.status == "on")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						//command drive off
						cmdSetBepOff();
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["drive_on"] == ELEM_NOT)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "off";
						}
					}
				}
				if(cmd.device == "vrl")
				{
					if(cmd.status == "on")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						cmdSetVrlOff();	//command vrl off
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["vrl"] == ELEM_NOT)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "off";
						}
					}
				}
				if(cmd.device == "pumi")
				{
					if(cmd.status == "on")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						//command pumi off
						cmdSetPumiOff();
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["pum1_on"] == ELEM_NOT && m_kvit["pum2_on"] == ELEM_NOT)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "off";
						}
					}
				}
				if(cmd.device == "prd")
				{
					if(cmd.status == "on")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						//command prd off
						cmdSetPrdOff();
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["prd1_on"] == ELEM_NOT && m_kvit["prd2_on"] == ELEM_NOT)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "off";
						}
					}
				}
				if(cmd.device == "prd1")
				{
					if(cmd.status == "on")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						//command prd1 off
						cmdSetPrd1Off();
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["prd1_on"] == ELEM_NOT)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "off";
						}
					}
				}
				if(cmd.device == "prd2")
				{
					if(cmd.status == "on")
					{
						m_rafMessages << AskuRafMessage(cmd.textCommand, QString("command"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						m_rafMessagesUpdated = QDateTime::currentDateTime();
						//command prd2 off
						cmdSetPrd2Off();
						cmd.status = "wait";
					}
					else if(cmd.status == "wait")
					{
						if(m_kvit["prd2_on"] == ELEM_NOT)
						{
							m_rafMessages << AskuRafMessage(cmd.textKvit, QString("ticket"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
							m_rafMessagesUpdated = QDateTime::currentDateTime();
							cmd.status = "off";
						}
					}
				}
				if(cmd.device == "finish" && cmd.status == "on")
				{
					if(m_kvit["drive_on"] == ELEM_NOT && 
						m_kvit["prd1_on"] == ELEM_NOT && 
						m_kvit["prd2_on"] == ELEM_NOT &&
						(m_kvit["pum1_on"] == ELEM_NOT && m_kvit["pum2_on"] == ELEM_NOT) &&
						m_kvit["vrl"] == ELEM_NOT)
						m_rafMessages << AskuRafMessage(cmd.textKvit, QString("complete"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
					else
					{
						m_rafMessages << AskuRafMessage(cmd.textError, QString("error"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						for(qint32 j = 0; j < m_timeOff.count(); j++)
						{
							AskuOnOffCommand & err = m_timeOff[j];
							if(err.device != "finish" && err.device != "start" && err.status == "wait")
								m_rafMessages << AskuRafMessage(err.textError, QString("error"), QString("%1с").arg(m_OnOffRafCounter / m_OnOffRafMultiplier));
						}
					}
					m_rafMessagesUpdated = QDateTime::currentDateTime();
					m_OnOffRafStatus = 0;
					cmd.status = "off";
					onRafOffFinish();
					cmdSetTest();
				}
			}
		}
	}

	makeRafOnOffMessage();

	if(m_OnOffRafStatus == 0) 
		m_onOffTimer->stop();
}

// ----------------------------------------------------------------------------
