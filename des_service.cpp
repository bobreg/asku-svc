#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "des_service.h"
#include "des_thread.h"
#include "des_deif_mains.h"
#include "des_deif_dg.h"

// ------------------------------------------------------------------
DES_SERVICE::DES_SERVICE(DES_THREAD *p) : MODBUS_SERVICE(NULL)
{
	parent = p;
}

// ------------------------------------------------------------------
bool DES_SERVICE::init()
{
	LogDesInfo("DesService started");

	deif_mains[0] = new DEIF_MAINS_DEVICE(this, m_setup.des.mains_address1);
	deif_mains[1] = NULL;
	deif_dg[0] = new DEIF_DG_DEVICE(this, m_setup.des.dg_address1);
	deif_dg[1] = new DEIF_DG_DEVICE(this, m_setup.des.dg_address2);
	deif_dg[2] = NULL;
	deif_dg[3] = NULL;

	addDevice(deif_mains[0]);
	addDevice(deif_dg[0]);
	addDevice(deif_dg[1]);

	addConnection(m_setup.des.ip, m_setup.des.port);
	setSingleConnection(true);

	updateState();
	startConnect(10000);

	return MODBUS_SERVICE::init();
}

// ------------------------------------------------------------------
DES_SERVICE::~DES_SERVICE()
{
	if(deif_dg[3])
	{
		removeDevice(deif_dg[3]);
		delete deif_dg[3];
		deif_dg[3] = NULL;
	}
	if(deif_dg[2])
	{
		removeDevice(deif_dg[2]);
		delete deif_dg[2];
		deif_dg[2] = NULL;
	}
	if(deif_dg[1])
	{
		removeDevice(deif_dg[1]);
		delete deif_dg[1];
		deif_dg[1] = NULL;
	}
	if(deif_dg[0])
	{
		removeDevice(deif_dg[0]);
		delete deif_dg[0];
		deif_dg[0] = NULL;
	}
	if(deif_mains[1])
	{
		removeDevice(deif_mains[1]);
		delete deif_mains[1];
		deif_mains[1] = NULL;
	}
	if(deif_mains[0])
	{
		removeDevice(deif_mains[0]);
		delete deif_mains[0];
		deif_mains[0] = NULL;
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::onChangedMain(bool main)
{
	if(main)
	{
		bool need = false;
		for(qint32 i = 0; i < N_DES_DGS; i++)
			if(!m_desConfig.Dgs[i].first)
				need = true;
		for(qint32 j = 0; j < N_DES_MNS; j++)
			if(!m_desConfig.Mns[j].first)
				need = true;
		if(need)
			QTimer::singleShot(10000, this, SLOT(setFirstCommands()));
	}

	m_desConfig.main = main;
	syncToSlave();
	onRefreshDes();
}

// ------------------------------------------------------------------
void DES_SERVICE::startMonitor()
{
	m_desConfig.monitor = true;
	syncToSlave();
}

// ------------------------------------------------------------------
void DES_SERVICE::stopMonitor()
{
	m_desConfig.monitor = false;
	syncToSlave();
}

// ------------------------------------------------------------------
void DES_SERVICE::setEngine(quint32 n_dgs, bool on)
{
	if(n_dgs < N_DES_DGS)
	{
		m_desConfig.Dgs[n_dgs].runDG = on;
		m_desConfig.Dgs[n_dgs].first = true;
		syncToSlave();

		if(deif_dg[n_dgs])
			deif_dg[n_dgs]->setEngine(on);
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::setPosGB(quint32 n_dgs, bool on)
{
	if(n_dgs < N_DES_DGS)
	{
		m_desConfig.Dgs[n_dgs].posGB = on;
		m_desConfig.Dgs[n_dgs].first = true;
		syncToSlave();

		if(deif_dg[n_dgs])
			deif_dg[n_dgs]->setGB(on);
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::setPosMB(quint32 n_mns, bool on)
{
	if(n_mns < N_DES_MNS)
	{
		m_desConfig.Mns[n_mns].posMB = on;
		m_desConfig.Mns[n_mns].first = true;
		syncToSlave();

		if(deif_mains[n_mns])
			deif_mains[n_mns]->setMB(on);
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::setPosTB(quint32 n_mns, bool on)
{
	if(n_mns < N_DES_MNS)
	{
		m_desConfig.Mns[n_mns].posTB = on;
		m_desConfig.Mns[n_mns].first = true;
		syncToSlave();

		if(deif_mains[n_mns])
			deif_mains[n_mns]->setTB(on);
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::setMainsReset(quint32 n_mns)
{
	if(n_mns < N_DES_MNS)
	{
//		m_desConfig.Mns[n_mns].reset = true;
		syncToSlave();

		if(deif_mains[n_mns])
			deif_mains[n_mns]->setReset();

//		m_desConfig.Mns[n_mns].reset = false;
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::setDgReset(quint32 n_dgs)
{
	if(n_dgs < N_DES_DGS)
	{
//		m_desConfig.Dgs[n_dgs].reset = true;
		syncToSlave();

		if(deif_dg[n_dgs])
			deif_dg[n_dgs]->setReset();

//		m_desConfig.Dgs[n_dgs].reset = false;
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::setMainsMode(quint32 n_mns, quint32 mode)
{
	if(n_mns < N_DES_MNS)
	{
		m_desConfig.Mns[n_mns].regAuto     = (mode == 0);
		m_desConfig.Mns[n_mns].regSemiAuto = (mode == 1);
		m_desConfig.Mns[n_mns].regTest     = (mode == 2);
		m_desConfig.Mns[n_mns].regManual   = (mode == 3);
		m_desConfig.Mns[n_mns].regBlock    = (mode == 4);
		m_desConfig.Mns[n_mns].first = true;

		syncToSlave();

		if(deif_mains[n_mns])
			deif_mains[n_mns]->setMode(mode);
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::setDgMode(quint32 n_dgs, quint32 mode)
{
	if(n_dgs < N_DES_DGS)
	{
		m_desConfig.Dgs[n_dgs].regAuto     = (mode == 0);
		m_desConfig.Dgs[n_dgs].regSemiAuto = (mode == 1);
		m_desConfig.Dgs[n_dgs].regTest     = (mode == 2);
		m_desConfig.Dgs[n_dgs].regManual   = (mode == 3);
		m_desConfig.Dgs[n_dgs].regBlock    = (mode == 4);
		m_desConfig.Dgs[n_dgs].first = true;

		syncToSlave();

		if(deif_dg[n_dgs])
			deif_dg[n_dgs]->setMode(mode);
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::onRefreshDes()
{
	if(!m_desConfig.main || !m_desConfig.monitor)
		return;

	QVariantMap info;

	info["port1Opened"]  = QString::number(m_portState[MODBUS_PORT_1].State.Bits.Opened);
	info["port1Active"]  = QString::number(m_portState[MODBUS_PORT_1].State.Bits.Active);
	info["port1Fail"]    = QString::number(m_portState[MODBUS_PORT_1].State.Bits.Fail);
	info["port1NoData"]  = QString::number(m_portState[MODBUS_PORT_1].State.Bits.NoData);
	info["port1BadData"] = QString::number(m_portState[MODBUS_PORT_1].State.Bits.BadData);

	DeifMainsState & stateMn1 = deif_mains[0]->state();
	DeifDgState & stateDg1 = deif_dg[0]->state();
	DeifDgState & stateDg2 = deif_dg[1]->state();

	bool workMn1 = deif_mains[0]->isActualState();
	bool workDg1 = deif_dg[0]->isActualState();
	bool workDg2 = deif_dg[1]->isActualState();

	info["mnWork1"] = workMn1 ? "Установлена" : "НЕТ";
	info["dgWork1"] = workDg1 ? "Установлена" : "НЕТ";
	info["dgWork2"] = workDg2 ? "Установлена" : "НЕТ";

	QString strStateMn1, strStateDg1, strStateDg2;

	if(!workMn1)
		strStateMn1 = " ";
	else if(stateMn1.State.RegState.Bits.Block_mode)
		strStateMn1 = "БЛОКИРОВКА/ОТКЛ";
	else if(stateMn1.State.RegState.Bits.Test_mode)
		strStateMn1 = "ТЕСТИРОВАНИЕ";
	else if(stateMn1.State.RegState.Bits.Manual_mode)
		strStateMn1 = "РУЧНОЙ";
	else if(stateMn1.State.RegState.Bits.SemiAuto_mode)
		strStateMn1 = "ПОЛУАВТОМАТ";
	else if(stateMn1.State.RegState.Bits.Auto_mode)
		strStateMn1 = "АВТОМАТИЧЕСКИЙ";
	else
		strStateMn1 = "---";

	if(!workDg1)
		strStateDg1 = " ";
	else if(stateDg1.State.RegState.Bits.Block_mode)
		strStateDg1 = "БЛОКИРОВКА/ОТКЛ";
	else if(stateDg1.State.RegState.Bits.Test_mode)
		strStateDg1 = "ТЕСТИРОВАНИЕ";
	else if(stateDg1.State.RegState.Bits.Manual_mode)
		strStateDg1 = "РУЧНОЙ";
	else if(stateDg1.State.RegState.Bits.SemiAuto_mode)
		strStateDg1 = "ПОЛУАВТОМАТ";
	else if(stateDg1.State.RegState.Bits.Auto_mode)
		strStateDg1 = "АВТОМАТИЧЕСКИЙ";
	else
		strStateDg1 = "---";

	if(!workDg2)
		strStateDg2 = " ";
	else if(stateDg2.State.RegState.Bits.Block_mode)
		strStateDg2 = "БЛОКИРОВКА/ОТКЛ";
	else if(stateDg2.State.RegState.Bits.Test_mode)
		strStateDg2 = "ТЕСТИРОВАНИЕ";
	else if(stateDg2.State.RegState.Bits.Manual_mode)
		strStateDg2 = "РУЧНОЙ";
	else if(stateDg2.State.RegState.Bits.SemiAuto_mode)
		strStateDg2 = "ПОЛУАВТОМАТ";
	else if(stateDg2.State.RegState.Bits.Auto_mode)
		strStateDg2 = "АВТОМАТИЧЕСКИЙ";
	else
		strStateDg2 = "---";

	info["mnRegime1"] = strStateMn1;
	info["dgRegime1"] = strStateDg1;
	info["dgRegime2"] = strStateDg2;

	info["checkRegime1"] = m_desConfig.Mns[0].regAuto;
	info["checkRegime2"] = m_desConfig.Mns[0].regSemiAuto;
	info["checkRegime3"] = m_desConfig.Mns[0].regTest;
	info["checkRegime4"] = m_desConfig.Mns[0].regManual;
	info["checkRegime5"] = m_desConfig.Mns[0].regBlock;

	info["pushOffMB1"] = !m_desConfig.Mns[0].regAuto ? (!m_desConfig.Mns[0].posMB) : -1;
	info["pushOnMB1"]  = !m_desConfig.Mns[0].regAuto ? (m_desConfig.Mns[0].posMB) : -1;

	info["pushOffGB1"] = !m_desConfig.Dgs[0].regAuto ? (!m_desConfig.Dgs[0].posGB) : -1;
	info["pushOnGB1"]  = !m_desConfig.Dgs[0].regAuto ? (m_desConfig.Dgs[0].posGB) : -1;

	info["pushOffGB2"] = !m_desConfig.Dgs[1].regAuto ? (!m_desConfig.Dgs[1].posGB) : -1;
	info["pushOnGB2"]  = !m_desConfig.Dgs[1].regAuto ? (m_desConfig.Dgs[1].posGB) : -1;

	info["pushOffEngine1"] = !m_desConfig.Dgs[0].regAuto ? (!m_desConfig.Dgs[0].runDG) : -1;
	info["pushOnEngine1"]  = !m_desConfig.Dgs[0].regAuto ? (m_desConfig.Dgs[0].runDG) : -1;

	info["pushOffEngine2"] = !m_desConfig.Dgs[1].regAuto ? (!m_desConfig.Dgs[1].runDG) : -1;
	info["pushOnEngine2"]  = !m_desConfig.Dgs[1].regAuto ? (m_desConfig.Dgs[1].runDG) : -1;

	emit sigDesState(info);
}

// ------------------------------------------------------------------
void DES_SERVICE::onConnected()
{
	startQuery(500);

	deif_mains[0]->onConnectedDevice();
	deif_dg[0]->onConnectedDevice();
	deif_dg[1]->onConnectedDevice();
}

// ------------------------------------------------------------------
void DES_SERVICE::onDisconnected()
{
	stopQuery();

	deif_mains[0]->onDisconnectedDevice();
	deif_dg[0]->onDisconnectedDevice();
	deif_dg[1]->onDisconnectedDevice();
}

// ------------------------------------------------------------------
bool DES_SERVICE::onQuery()
{
	if(deif_mains[0]->processCommands())
		return true;

	if(deif_dg[0]->processCommands())
		return true;

	if(deif_dg[1]->processCommands())
		return true;


	quint32 device = nextQueryDevice();
//	qDebug() << "device = " << device;
	switch(device)
	{
		case 0:
			if(deif_mains[0]->processQuery())
				return true;
			break;
		case 1:
			if(deif_dg[0]->processQuery())
				return true;
			break;
		case 2:
			if(deif_dg[1]->processQuery())
				return true;
			break;
	}

	return false;
}

// ------------------------------------------------------------------
bool DES_SERVICE::onLive()
{
	return false;
}

// ------------------------------------------------------------------
void DES_SERVICE::onChangedDeviceState()
{
	updateState();
	onRefreshDes();
}

// ------------------------------------------------------------------
void DES_SERVICE::onChangedPortState()
{
	updateState();
	onRefreshDes();
}

// ------------------------------------------------------------------
void DES_SERVICE::syncToSlave()
{
	if(m_desConfig.main)
		emit sigSyncToSlave(m_desConfig.toMap());
}

// ------------------------------------------------------------------
void DES_SERVICE::onSyncToSlave(QVariantMap data)
{
	if(!m_desConfig.main)
	{
		DesConfig m_masterConfig(data);
		if(m_masterConfig.main)
		{
			LogDesInfo("DES_SERVICE::onSyncToSlave processed");
			m_desConfig.monitor = m_masterConfig.monitor;

			for(qint32 i = 0; i < N_DES_MNS; i++)
			{
				m_desConfig.Mns[i].regAuto = m_masterConfig.Mns[i].regAuto;
				m_desConfig.Mns[i].regSemiAuto = m_masterConfig.Mns[i].regSemiAuto;
				m_desConfig.Mns[i].regTest = m_masterConfig.Mns[i].regTest;
				m_desConfig.Mns[i].regManual = m_masterConfig.Mns[i].regManual;
				m_desConfig.Mns[i].regBlock = m_masterConfig.Mns[i].regBlock;
				m_desConfig.Mns[i].posTB = m_masterConfig.Mns[i].posTB;
				m_desConfig.Mns[i].posMB = m_masterConfig.Mns[i].posMB;
			}

			for(qint32 i = 0; i < N_DES_DGS; i++)
			{
				m_desConfig.Dgs[i].regAuto = m_masterConfig.Dgs[i].regAuto;
				m_desConfig.Dgs[i].regSemiAuto = m_masterConfig.Dgs[i].regSemiAuto;
				m_desConfig.Dgs[i].regTest = m_masterConfig.Dgs[i].regTest;
				m_desConfig.Dgs[i].regManual = m_masterConfig.Dgs[i].regManual;
				m_desConfig.Dgs[i].regBlock = m_masterConfig.Dgs[i].regBlock;
				m_desConfig.Dgs[i].posGB = m_masterConfig.Dgs[i].posGB;
				m_desConfig.Dgs[i].runDG = m_masterConfig.Dgs[i].runDG;
			}

//		qDebug() << "desMasterConfig accepted";
		}
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::verifyFirstCommands()
{
	if(m_desConfig.main)
	{
		bool was = false;
		for(qint32 i = 0; i < N_DES_MNS; i++)
		{
			if(!m_desConfig.Mns[i].first && deif_mains[i])
			{
				DeifMainsState & state = deif_mains[i]->state();
				bool work = deif_mains[i]->isActualState();

				if(work && state.State.RegState.Bits.TB_position)
				{
					m_desConfig.Mns[i].posTB = true;
					m_desConfig.Mns[i].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.MB_position)
				{
					m_desConfig.Mns[i].posMB = true;
					m_desConfig.Mns[i].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.Block_mode)
				{
					m_desConfig.Mns[i].regBlock = true;
					m_desConfig.Mns[i].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.Test_mode)
				{
					m_desConfig.Mns[i].regTest = true;
					m_desConfig.Mns[i].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.Manual_mode)
				{
					m_desConfig.Mns[i].regManual = true;
					m_desConfig.Mns[i].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.SemiAuto_mode)
				{
					m_desConfig.Mns[i].regSemiAuto = true;
					m_desConfig.Mns[i].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.Auto_mode)
				{
					m_desConfig.Mns[i].regAuto = true;
					m_desConfig.Mns[i].first = true;
					was = true;
				}
			}
		}
		for(qint32 j = 0; j < N_DES_DGS; j++)
		{
			if(!m_desConfig.Dgs[j].first && deif_dg[j])
			{
				DeifDgState & state = deif_dg[j]->state();
				bool work = deif_dg[j]->isActualState();

				if(work && state.State.RegState.Bits.GB_position)
				{
					m_desConfig.Dgs[j].posGB = true;
					m_desConfig.Dgs[j].first = true;
					was = true;
				}
				if(work && state.State.RegState2.Bits.Engine_running)
				{
					m_desConfig.Dgs[j].runDG = true;
					m_desConfig.Dgs[j].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.Block_mode)
				{
					m_desConfig.Dgs[j].regBlock = true;
					m_desConfig.Dgs[j].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.Test_mode)
				{
					m_desConfig.Dgs[j].regTest = true;
					m_desConfig.Dgs[j].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.Manual_mode)
				{
					m_desConfig.Dgs[j].regManual = true;
					m_desConfig.Dgs[j].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.SemiAuto_mode)
				{
					m_desConfig.Dgs[j].regSemiAuto = true;
					m_desConfig.Dgs[j].first = true;
					was = true;
				}
				if(work && state.State.RegState.Bits.Auto_mode)
				{
					m_desConfig.Dgs[j].regAuto = true;
					m_desConfig.Dgs[j].first = true;
					was = true;
				}
			}
		}
		if(was)
			syncToSlave();
	}
}

// ------------------------------------------------------------------
void DES_SERVICE::setFirstCommands()
{
	if(m_desConfig.main)
	{
		bool was = false;
		for(qint32 i = 0; i < N_DES_DGS; i++)
			if(!m_desConfig.Dgs[i].first)
			{
				m_desConfig.Dgs[i].first = true;
				was = true;
			}
		for(qint32 j = 0; j < N_DES_MNS; j++)
			if(!m_desConfig.Mns[j].first)
			{
				m_desConfig.Mns[j].first = true;
				was = true;
			}
		if(was)
			syncToSlave();
	}
}

// ------------------------------------------------------------------
