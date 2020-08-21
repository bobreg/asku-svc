#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "ups_thread.h"
#include "ups_snmp_service.h"
#include "ups_snmp_pww_device.h"
#include "ups_snmp_apc_device.h"

// ------------------------------------------------------------------
UPS_SNMP_SERVICE::UPS_SNMP_SERVICE(UPS_THREAD *p) : SNMP_SERVICE(p)
{
	LogUpsInfo("UPS_SNMP_SERVICE: SNMP UPS type selected");

	for(int i = 0; i < 2; i++)
		m_device[i] = NULL;
}

// ------------------------------------------------------------------
bool UPS_SNMP_SERVICE::init()
{
	LogUpsInfo("UpsSnmpService started");

	m_device[0] = new APC_SNMP_DEVICE(this, m_setup.ups.ip1, m_setup.ups.snmp_community, m_setup.ups.snmp_version);
	m_device[1] = new APC_SNMP_DEVICE(this, m_setup.ups.ip2, m_setup.ups.snmp_community, m_setup.ups.snmp_version);

	addDevice(m_device[0]);
	addDevice(m_device[1]);

	updateState();

	return SNMP_SERVICE::init();
}

// ------------------------------------------------------------------
UPS_SNMP_SERVICE::~UPS_SNMP_SERVICE()
{
	if(m_device[1])
	{
		removeDevice(m_device[1]);
		delete m_device[1];
		m_device[1] = NULL;
	}
	if(m_device[0])
	{
		removeDevice(m_device[0]);
		delete m_device[0];
		m_device[0] = NULL;
	}
}

// ------------------------------------------------------------------
void UPS_SNMP_SERVICE::onChangedMain(bool main)
{
	m_upsConfig.main = main;

	LogUpsInfo("UPS_SNMP: onChangedMain %d", main);

	if(main)
	{
		for(int i = 0; i < 2; i++)
			if(m_device[i])
				m_device[i]->queryStart();
	}
	else
	{
		for(int i = 0; i < 2; i++)
			if(m_device[i])
				m_device[i]->queryStop();
	}

	syncToSlave();
	onRefreshUps();
}

// ------------------------------------------------------------------
void UPS_SNMP_SERVICE::startMonitor()
{
	m_upsConfig.monitor = true;
	syncToSlave();
}

// ------------------------------------------------------------------
void UPS_SNMP_SERVICE::stopMonitor()
{
	m_upsConfig.monitor = false;
	syncToSlave();
}

// ------------------------------------------------------------------
void UPS_SNMP_SERVICE::onRefreshUps()
{
	if(!m_upsConfig.main || !m_upsConfig.monitor)
		return;

	QVariantMap info;
/*
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
void UPS_SNMP_SERVICE::onConnected()
{
}

// ------------------------------------------------------------------
void UPS_SNMP_SERVICE::onDisconnected()
{
}

// ------------------------------------------------------------------
void UPS_SNMP_SERVICE::onChangedDeviceState()
{
}

// ------------------------------------------------------------------
void UPS_SNMP_SERVICE::onChangedPortState()
{
}

// ------------------------------------------------------------------
void UPS_SNMP_SERVICE::onProcessSnmpResults(SNMP_DEVICE * device, const SnmpResultMap & results)
{
	QString strIndex;
	if(device == m_device[0])
		strIndex = QString("ups1@");
	if(device == m_device[1])
		strIndex = QString("ups2@");

	m_results = results;

	LogUpsInfo("SNMP: onProcessSnmpResults:  isConnected=%d  isChanged=%d", device->isConnected(), m_results.isChanged());

	if(device->isConnected())
	{
		bUpsState[strIndex + "connected"] = ELEM_NORMA;
		bUpsState[strIndex + "ObSost"] = ELEM_NORMA;
	}
	else
	{
		bUpsState[strIndex + "connected"] = ELEM_NOT;
		bUpsState[strIndex + "ObSost"] = ELEM_NOT;
	}

	for(SnmpResultMap::const_iterator it = m_results.constBegin(); it != m_results.constEnd(); ++it)
	{
		const QString & key = it.key();
		const SnmpResult & result = it.value();;

		if(!device->isConnected() || result.isNull())
		{
			bUpsState[strIndex + key] = ELEM_NOT;
			bUpsMeasure[strIndex + key] = QVariant();
		}
		else
		{
			bUpsState[strIndex + key] = ELEM_NORMA;
			bUpsMeasure[strIndex + key] = device->translateValue(key, result.value());
		}
	}

	updateState();
	onRefreshUps();
	syncToSlave();
}

// ------------------------------------------------------------------
void UPS_SNMP_SERVICE::syncToSlave()
{
	if(m_upsConfig.main)
		emit sigSyncToSlave(m_upsConfig.toMap(), bUpsState.toMap(), bUpsMeasure.toMap());
}

// ------------------------------------------------------------------
void UPS_SNMP_SERVICE::onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure)
{
	if(!m_upsConfig.main)
	{
		UpsConfig m_masterConfig(config);
		if(m_masterConfig.main)
		{
			LogUpsInfo("UPS_SNMP_SERVICE::onSyncToSlave processed");
			m_upsConfig.monitor = m_masterConfig.monitor;
//			qDebug() << "upsMasterConfig accepted";
		}

//		qDebug() << "onSyncToSlave";

		bool bState = bUpsState.fromMap(state);
		bool bMeasure = bUpsMeasure.fromMap(measure);

		if(bState || bMeasure)
			emit sigState(bUpsState, bUpsMeasure);

//		qDebug() << "-------------";
	}
}

// ------------------------------------------------------------------
