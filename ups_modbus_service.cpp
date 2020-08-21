#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "ups_thread.h"
#include "ups_modbus_service.h"
#include "ups_modbus_pww_device.h"

// ------------------------------------------------------------------
UPS_MODBUS_SERVICE::UPS_MODBUS_SERVICE(UPS_THREAD *p) : MODBUS_SERVICE(p)
{
	LogUpsInfo("UPS_MODBUS_SERVICE: modbus/jbus UPS type selected");
}

// ------------------------------------------------------------------
bool UPS_MODBUS_SERVICE::init()
{
	LogUpsInfo("UpsService started");

	powerware[0] = new POWERWARE_MODBUS_DEVICE(this, m_setup.ups.address, 0);
	powerware[1] = 0;

	addDevice(powerware[0]);

	addConnection(m_setup.com1.ip, m_setup.ups.port);
	setSeparateConnections(true);

	updateState();
	startConnect(10000);

	return MODBUS_SERVICE::init();
}

// ------------------------------------------------------------------
UPS_MODBUS_SERVICE::~UPS_MODBUS_SERVICE()
{
	if(powerware[1])
	{
		removeDevice(powerware[1]);
		delete powerware[1];
		powerware[1] = NULL;
	}
	if(powerware[0])
	{
		removeDevice(powerware[0]);
		delete powerware[0];
		powerware[0] = NULL;
	}
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::onChangedMain(bool main)
{
	m_upsConfig.main = main;
	syncToSlave();
	onRefreshUps();
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::startMonitor()
{
	m_upsConfig.monitor = true;
	syncToSlave();
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::stopMonitor()
{
	m_upsConfig.monitor = false;
	syncToSlave();
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::onRefreshUps()
{
	if(!m_upsConfig.main || !m_upsConfig.monitor)
		return;

	QVariantMap info;
/*
	info["port1Opened"]  = QString::number(m_portState[MODBUS_PORT_1].State.Bits.Opened);
	info["port1Active"]  = QString::number(m_portState[MODBUS_PORT_1].State.Bits.Active);
	info["port1Fail"]    = QString::number(m_portState[MODBUS_PORT_1].State.Bits.Fail);
	info["port1NoData"]  = QString::number(m_portState[MODBUS_PORT_1].State.Bits.NoData);
	info["port1BadData"] = QString::number(m_portState[MODBUS_PORT_1].State.Bits.BadData);

	info["port2Opened"]  = QString::number(m_portState[MODBUS_PORT_2].State.Bits.Opened);
	info["port2Active"]  = QString::number(m_portState[MODBUS_PORT_2].State.Bits.Active);
	info["port2Fail"]    = QString::number(m_portState[MODBUS_PORT_2].State.Bits.Fail);
	info["port2NoData"]  = QString::number(m_portState[MODBUS_PORT_2].State.Bits.NoData);
	info["port2BadData"] = QString::number(m_portState[MODBUS_PORT_2].State.Bits.BadData);

	PowerwareState & state1 = powerware[0]->state();
	PowerwareState & state2 = powerware[1]->state();

	bool work1 = powerware[0]->isActualState();
	bool work2 = powerware[1]->isActualState();

	info["upsWork1"]   = work1 ? "Установлена" : "НЕТ";
	info["upsWork2"]   = work2 ? "Установлена" : "НЕТ";

	QString strState1, strState2;

	if(!work1)
		strState1 = " ";
	else if(state1.State.RegState.Bits.Ups_Off)
		strState1 = "ОТКЛЮЧЕН";
	else if(state1.State.RegState.Bits.On_Bypass)
		strState1 = "БАЙПАС";
	else if(state1.State.RegState.Bits.On_Battery)
		strState1 = "НА БАТАРЕЯХ";
	else if(state1.State.RegState.Bits.System_Normal)
		strState1 = "НОРМА";
	else
		strState1 = "---";

	if(!work2)
		strState2 = " ";
	else if(state2.State.RegState.Bits.Ups_Off)
		strState2 = "ОТКЛЮЧЕН";
	else if(state2.State.RegState.Bits.On_Bypass)
		strState2 = "БАЙПАС";
	else if(state2.State.RegState.Bits.On_Battery)
		strState2 = "НА БАТАРЕЯХ";
	else if(state2.State.RegState.Bits.System_Normal)
		strState2 = "НОРМА";
	else
		strState2 = "---";

	info["upsRegime1"] = strState1;
	info["upsRegime2"] = strState2;
*/
	emit sigUpsState(info);
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::onConnected()
{
	startQuery(500);
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::onDisconnected()
{
	stopQuery();
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::onConnectedPort(qint32 port)
{
	if(port == powerware[0]->connection())
		powerware[0]->onConnectedDevice();

	if(port == powerware[1]->connection())
		powerware[1]->onConnectedDevice();
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::onDisconnectedPort(qint32 port)
{
	if(port == powerware[0]->connection())
		powerware[0]->onDisconnectedDevice();

	if(port == powerware[1]->connection())
		powerware[1]->onDisconnectedDevice();
}

// ------------------------------------------------------------------
bool UPS_MODBUS_SERVICE::onQuery()
{
	quint32 device = nextQueryDevice();

	if(powerware[device]->processQuery())
		return true;

	return false;
}

// ------------------------------------------------------------------
bool UPS_MODBUS_SERVICE::onLive()
{
	return false;
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::onChangedDeviceState()
{
	updateState();
	onRefreshUps();
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::onChangedPortState()
{
	updateState();
	onRefreshUps();
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::syncToSlave()
{
	if(m_upsConfig.main)
		emit sigSyncToSlave(m_upsConfig.toMap());
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::onSyncToSlave(QVariantMap data)
{
	if(!m_upsConfig.main)
	{
		UpsConfig m_masterConfig(data);
		if(m_masterConfig.main)
		{
			LogUpsInfo("UPS_MODBUS_SERVICE::onSyncToSlave processed");
			m_upsConfig.monitor = m_masterConfig.monitor;
//			qDebug() << "upsMasterConfig accepted";
		}
	}
}

// ------------------------------------------------------------------
