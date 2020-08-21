#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "vrl_service.h"
#include "vrl_thread.h"
#include "viewer.h"

// ------------------------------------------------------------------
VRL_SERVICE::VRL_SERVICE(VRL_THREAD *p)
{
	parent = p;
	network = NULL;
	m_timer = NULL;

	m_isInitialized = false;
	m_cmdMain = false;

	m_portVrl = m_setup.vrl1.port;
	m_portOur = m_setup.vrl1.port_listen;
	m_haVrl[0] = m_setup.vrl1.ip;
	m_haVrl[1] = m_setup.vrl2.ip;
	m_isConnected[0] = m_isConnected[1] = 0;
	m_allowReserve = true;
	m_nOsnVRL = -1;
	m_nOsnVRLState[0] = m_nOsnVRLState[1] = -1;
	m_mest[0] = m_mest[1] = -1;
	m_state[0] = m_state[1] = -1;
	m_avarStatusCounter = 0;
	m_timeoutCounter[0] = m_timeoutCounter[1] = 0;
	m_workVrl[0] = m_workVrl[1] = 0;

#ifdef FAKE_VRL
	m_fakeTimer = new QTimer(this);
	connect(m_fakeTimer, SIGNAL(timeout()), this, SLOT(fakeCommands()));
#endif
}

// ------------------------------------------------------------------
bool VRL_SERVICE::init()
{
	network = new UdpNetwork(this, QString("VRL_UDP"));
	if(network)
	{
		connect(network, SIGNAL(dataArrived(QByteArray,QHostAddress,quint16)), this, SLOT(onDataArrived(QByteArray,QHostAddress,quint16)));

		LogVrlInfo("VrlService started");
		m_isInitialized = network->init(m_portOur);
	}

	m_timer = new QTimer(this);
	connect(m_timer,SIGNAL(timeout()),this,SLOT(timeout()));
	m_timer->start(500);

#ifdef FAKE_VRL
	m_fakeTimer->start(5000);
#endif
	return false;
}

// ------------------------------------------------------------------
VRL_SERVICE::~VRL_SERVICE()
{
#ifdef FAKE_VRL
	if(m_fakeTimer)
	{
		m_fakeTimer->stop();
		delete m_fakeTimer;
		m_fakeTimer = NULL;
	}
#endif
	if(m_timer)
	{
		m_timer->stop();
		delete m_timer;
		m_timer = NULL;
	}
	if(network)
	{
		network->close();
		delete network;
		network = NULL;
	}
}

// ------------------------------------------------------------------
bool VRL_SERVICE::isInitialized()
{
	return m_isInitialized;
}

// ------------------------------------------------------------------
void VRL_SERVICE::setMain(bool main)
{
	if(main != m_cmdMain)
	{
		m_cmdMain = main;
		m_vrlConfig.main = main;
	}
}

// ------------------------------------------------------------------
void VRL_SERVICE::setConnectedGpr()
{
}

// ------------------------------------------------------------------
void VRL_SERVICE::setDisconnectedGpr()
{
}

// ------------------------------------------------------------------
void VRL_SERVICE::setAutoMainVRL()
{
	quint32 n_vrl = 0;

	if((m_workVrl[0] > 0) && (m_mest[0] == 0) && (m_state[0] != 1))
		n_vrl = 1;
	else if((m_workVrl[1] > 0) && (m_mest[1] == 0) && (m_state[1] != 1))
		n_vrl = 2;
	else 
		n_vrl = 1;

	m_vrlConfig.mainVRL = n_vrl;
	commandVRL(n_vrl == 1);
}

// ------------------------------------------------------------------
void VRL_SERVICE::setMainVRL(quint32 n_vrl)
{
	m_vrlConfig.mainVRL = n_vrl;
	commandVRL(n_vrl == 1);
}

// ------------------------------------------------------------------
void VRL_SERVICE::setDisableReconf(bool on)
{
	m_vrlConfig.reconfVRL = on;
	commandVRL();
}

// ------------------------------------------------------------------
void VRL_SERVICE::setDisableTotal(bool on)
{
	m_vrlConfig.disable = on;
	commandVRL();
}

// ------------------------------------------------------------------
void VRL_SERVICE::timeout()
{
	for(quint32 num = 0; num < 2; num++)
	{
		if(m_workVrl[num] > 0)
		{
			m_workVrl[num]--;
			if(!m_workVrl[num])
			{
				LogVrlInfo("VRL_SERVICE: timeout of complect %d", num + 1);

				clearVrl(num);

				if(num == 0)
				{
					AddAvarMes("АСКУ","Нет сообщений от Обработки МВРЛ-КН-1");
					bVrlState["vrl1@connect"] = ELEM_AVAR;
					bVrlState["vrl1@ObSost"] = ELEM_NOT;
					bVrlState["vrl1@main"] = ELEM_NOT;
					bVrlState["vrl1@obr"] = ELEM_NOT;
				}
				if(num == 1)
				{
					AddAvarMes("АСКУ","Нет сообщений от Обработки МВРЛ-КН-2");
					bVrlState["vrl2@connect"] = ELEM_AVAR;
					bVrlState["vrl2@ObSost"] = ELEM_NOT;
					bVrlState["vrl2@main"] = ELEM_NOT;
					bVrlState["vrl2@obr"] = ELEM_NOT;
				}

				verifyObSostVRL();

				if(!m_workVrl[0] && !m_workVrl[1])
				{
					m_avarStatusCounter = 0;
					m_nOsnVRL = -1;
					m_nOsnVRLState[0] = m_nOsnVRLState[1] = -1;
					m_mest[0] = m_mest[1] = -1;
					m_state[0] = m_state[1] = -1;
					//emit toggleVRL(0);
				}
			}
		}
	}
}

// ------------------------------------------------------------------
void VRL_SERVICE::sendToVRL(quint32 n_vrl, QByteArray data)
{
	if(network)
	{
		network->sendReply(data, m_haVrl[n_vrl], m_portVrl);
		LogVrlBinary("VRL: SendToVRL[%d]: %s", n_vrl, LogArray(data));
	}
}

// ------------------------------------------------------------------
void VRL_SERVICE::commandVRL(bool priority)
{
	MESSAGE_208 data;
	data.code = 208;
	data.length = sizeof(data);
	data.bits.status = m_vrlConfig.disable ? 0 : m_vrlConfig.mainVRL;
	data.bits.no_reconf = m_vrlConfig.reconfVRL;
	data.bits.unused = 0;

	QByteArray array((char*)&data, sizeof(MESSAGE_208));
	sendToVRL(priority ? 1 : 0, array);
	sendToVRL(priority ? 0 : 1, array);
}

// ------------------------------------------------------------------
#ifdef FAKE_VRL
void VRL_SERVICE::fakeCommands()
{
	MESSAGE_209 mes;
	memset(&mes, 0, sizeof(MESSAGE_209));

	mes.code = 208;
	mes.length = sizeof(MESSAGE_209);
	mes.status.bits.state1 = 0;
	mes.status.bits.state2 = 0;
	mes.status.bits.code = 1;

	mes.comp.bits.number = 1;
	processData(0, QByteArray((char*)&mes, sizeof(MESSAGE_209)));
	mes.comp.bits.number = 2;
	processData(1, QByteArray((char*)&mes, sizeof(MESSAGE_209)));
}
#endif
// ------------------------------------------------------------------
void VRL_SERVICE::onDataArrived(QByteArray data, QHostAddress haFrom, quint16 portFrom)
{
#ifdef FAKE_VRL
	Q_UNUSED(data);
	Q_UNUSED(haFrom);
	Q_UNUSED(portFrom);
//		processData(0, data);
//		processData(1, data);
#else
	if(haFrom == m_haVrl[0])
		processData(0, data);
	else if(haFrom == m_haVrl[1])
		processData(1, data);
	else
	{
		LogVrlError("VRL: onDataArrived: Unknown host %s:%d", qPrintable(haFrom.toString()), portFrom);
		LogVrlBinary("VRL: onDataArrived: %s", LogArray(data));
	}
#endif
}

// ------------------------------------------------------------------
void VRL_SERVICE::processData(quint32 n_vrl, QByteArray data)
{
	LogVrlBinary("VRL: processData[%d]: %s", n_vrl, LogArray(data));
//	LogVrlInfo("MESSAGE_209: size=%d, size_comp=%d size_status=%d size_ao=%d, size_prm=%d size_azn=%d size_umi=%d", sizeof(MESSAGE_209), sizeof(COMPLECT_VRL), sizeof(STATUS_VRL), sizeof(STATUS_AO), sizeof(STATUS_PRM), sizeof(STATUS_AZN), sizeof(STATUS_UMI));
	if(data.size() != sizeof(MESSAGE_209))
	{
		LogVrlError("VRL: Invalid message length = %d", data.size());
		return;
	}
	if((quint8)(data[0]) != 208)//209
	{
		LogVrlError("VRL: Unknown message type = %d", (quint8)data[0]);
		return;
	}
	if((quint8)(data[1]) != sizeof(MESSAGE_209))
	{
		LogVrlError("VRL: Unknown message length = %d", (quint8)data[1]);
		return;
	}
	COMPLECT_VRL cmp;
	cmp.byte = (unsigned char)data[2];
	if(cmp.bits.number != 1 && cmp.bits.number != 2)
	{
		LogVrlError("VRL: Invalid complect number = %d", cmp.bits.number);
		return;
	}
#ifdef FAKE_VRL
	MESSAGE_209 *mes = (MESSAGE_209*)data.data();
	mes->comp.bits.number = n_vrl + 1;
	mes->status.bits.state1 = 0;
	mes->status.bits.state2 = 0;
#endif
	process_209((MESSAGE_209*)data.data());
}

// ------------------------------------------------------------------
void VRL_SERVICE::process_209(MESSAGE_209 * mes)
{
	quint32 num = mes->comp.bits.number - 1;

	if(!m_workVrl[num])
	{
		LogVrlInfo("VRL_SERVICE: connected complect %d", num + 1);

		if(num == 0)
		{
			AddSwitchMes("АСКУ","Установлена связь с Обработкой МВРЛ-КН-1");
			bVrlState["vrl1@connect"] = ELEM_NORMA;
		}
		if(num == 1)
		{
			AddSwitchMes("АСКУ","Установлена связь с Обработкой МВРЛ-КН-2");
			bVrlState["vrl2@connect"] = ELEM_NORMA;
		}
	}

	m_workVrl[num] = CONNECT_MAX_TIMEOUT;

	checkReserve(mes->status.bits.code);

	if(m_nOsnVRL != (qint32)mes->status.bits.code)
	{
		if(m_nOsnVRL == -1)
			m_vrlConfig.mainVRL = mes->status.bits.code;
		else if(m_vrlConfig.mainVRL != 0 && m_vrlConfig.mainVRL != mes->status.bits.code)
			setAutoMainVRL();

		m_nOsnVRL = mes->status.bits.code;

		if(m_nOsnVRL == 0)
		{
			LogVrlInfo("VRL_SERVICE: status = %d : comp1-rez comp2-rez", m_nOsnVRL);
			AddSwitchMes("МВРЛ-КН","Обр.МВРЛ-КН-1 резервный, Обр.МВРЛ-КН-2 резервный");
//			emit toggleVRL(0);
			bVrlState["vrl1@main"] = ELEM_NOT;
			bVrlState["vrl2@main"] = ELEM_NOT;
		}
		else if(m_nOsnVRL == 1)
		{
			LogVrlInfo("VRL_SERVICE: status = %d : comp1-osn comp2-rez", m_nOsnVRL);
			AddSwitchMes("МВРЛ-КН","Обр.МВРЛ-КН-1 основной, Обр.МВРЛ-КН-2 резервный");
//			emit toggleVRL(1);
			bVrlState["vrl1@main"] = ELEM_NORMA;
			bVrlState["vrl2@main"] = ELEM_NOT;
		}
		else if(m_nOsnVRL == 2)
		{
			LogVrlInfo("VRL_SERVICE: status = %d : comp1-rez comp2-osn", m_nOsnVRL);
			AddSwitchMes("МВРЛ-КН","Обр.МВРЛ-КН-1 резервный, Обр.МВРЛ-КН-2 основной");
//			emit toggleVRL(2);
			bVrlState["vrl1@main"] = ELEM_NOT;
			bVrlState["vrl2@main"] = ELEM_NORMA;
		}
		else
		{
			LogVrlInfo("VRL_SERVICE: status = %d : comp1-reconf comp2-reconf", m_nOsnVRL);
			AddSwitchMes("МВРЛ-КН","Обр.МВРЛ-КН-1 реконфигурация, Обр.МВРЛ-КН-2 реконфигурация");
//			emit toggleVRL(0);
			bVrlState["vrl1@main"] = ELEM_MEST;
			bVrlState["vrl2@main"] = ELEM_MEST;
		}
	}

	if(m_mest[0] != mes->status.bits.mest1 && m_workVrl[0])
	{
		LogVrlInfo("VRL_SERVICE: mest1 = %d", mes->status.bits.mest1);
		if(mes->status.bits.mest1)
		{
			AddSwitchMes("МВРЛ-КН-1","Местное управление - установлено");
			bVrlState["vrl1@mest"] = ELEM_MEST;
		}
		else
		{
			if(m_mest[0] != -1)
				AddSwitchMes("МВРЛ-КН-1","Местное управление - снято");
			bVrlState["vrl1@mest"] = ELEM_NOT;
		}
		m_mest[0] = mes->status.bits.mest1;
	}

	if(m_mest[1] != mes->status.bits.mest2 && m_workVrl[1])
	{
		LogVrlInfo("VRL_SERVICE: mest2 = %d", mes->status.bits.mest2);
		if(mes->status.bits.mest2)
		{
			AddSwitchMes("МВРЛ-КН-2","Местное управление - установлено");
			bVrlState["vrl2@mest"] = ELEM_MEST;
		}
		else
		{
			if(m_mest[1] != -1)
				AddSwitchMes("МВРЛ-КН-2","Местное управление - снято");
			bVrlState["vrl2@mest"] = ELEM_NOT;
		}
		m_mest[1] = mes->status.bits.mest2;
	}

	if(m_state[0] != mes->status.bits.state1 && m_workVrl[0])
	{
		LogVrlInfo("VRL_SERVICE: status1 = %d", mes->status.bits.state1);
		switch(mes->status.bits.state1)
		{
			case 0:
				AddNormaMes("МВРЛ-КН-1","Норма комплекта");
				bVrlState["vrl1@ObSost"] = ELEM_NORMA;
				break;
			case 1:
				AddAvarMes("МВРЛ-КН-1","Отказ комплекта");
				bVrlState["vrl1@ObSost"] = ELEM_AVAR;
				break;
			case 2:
				AddErrorMes("МВРЛ-КН-1","Нет связи со смежным комплектом");
				bVrlState["vrl1@ObSost"] = ELEM_ERROR;
				break;
			case 3:
				AddErrorMes("МВРЛ-КН-1","Неисправность комплекта");
				bVrlState["vrl1@ObSost"] = ELEM_ERROR;
				break;
		}
		m_state[0] = mes->status.bits.state1;
	}

	if(m_state[1] != mes->status.bits.state2 && m_workVrl[1])
	{
		LogVrlInfo("VRL_SERVICE: status2 = %d", mes->status.bits.state2);
		switch(mes->status.bits.state2)
		{
			case 0:
				AddNormaMes("МВРЛ-КН-2","Норма комплекта");
				bVrlState["vrl2@ObSost"] = ELEM_NORMA;
				break;
			case 1:
				AddAvarMes("МВРЛ-КН-2","Отказ комплекта");
				bVrlState["vrl2@ObSost"] = ELEM_AVAR;
				break;
			case 2:
				AddErrorMes("МВРЛ-КН-2","Нет связи со смежным комплектом");
				bVrlState["vrl2@ObSost"] = ELEM_ERROR;
				break;
			case 3:
				AddErrorMes("МВРЛ-КН-2","Неисправность комплекта");
				bVrlState["vrl2@ObSost"] = ELEM_ERROR;
				break;
		}
		m_state[1] = mes->status.bits.state2;
	}

	process_panel(mes);
	process_obr(mes);
	process_subblocks(mes);
	process_vum(mes);
	process_prm(mes);
	process_azn(mes);
	process_zao(mes);

	verifyObSostVRL();
}

// ------------------------------------------------------------------
void VRL_SERVICE::startMonitor()
{
	m_vrlConfig.monitor = true;
	syncToSlave();
}

// ------------------------------------------------------------------
void VRL_SERVICE::stopMonitor()
{
	m_vrlConfig.monitor = false;
	syncToSlave();
}

// ------------------------------------------------------------------
void VRL_SERVICE::onRefreshVrl()
{
	if(!m_vrlConfig.main || !m_vrlConfig.monitor)
		return;

	QVariantMap info;

	emit sigVrlState(info);
}

// ------------------------------------------------------------------
void VRL_SERVICE::syncToSlave()
{
	if(m_vrlConfig.main)
		emit sigSyncToSlave(m_vrlConfig.toMap(), QVariantMap(), QVariantMap());
}

// ------------------------------------------------------------------
void VRL_SERVICE::onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff)
{
	Q_UNUSED(state);
	Q_UNUSED(koeff);

	if(!m_vrlConfig.main)
	{
		VrlConfig m_masterConfig(config);
		if(m_masterConfig.main)
		{
			LogVrlInfo("VRL_SERVICE::onSyncToSlave processed");
//		qDebug() << "vrlMasterConfig accepted";
		}
	}
}

// ------------------------------------------------------------------
void VRL_SERVICE::checkReserve(quint32 status)
{
	if(m_cmdMain && m_allowReserve && !m_vrlConfig.disable)
	{
		if(status == 0)
		{
//			qDebug("avarCounter=%d",m_avarStatusCounter);
			if(m_avarStatusCounter < 16)
				m_avarStatusCounter++;

			if(m_avarStatusCounter == 5)
			{
				AddSwitchMes("АСКУ","Автоматическое назначение комплекта обработки МВРЛ-К");
				//slotChangeVRL(3);
			}
			if(m_avarStatusCounter == 15)
			{
				AddSwitchMes("АСКУ","Автоматическое назначение комплекта обработки МВРЛ-К");
				//slotChangeVRL(3);
			}

			return;
		}
	}

	m_avarStatusCounter = 0;
}

// ------------------------------------------------------------------
