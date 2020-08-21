#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "ups_service.h"
#include "ups_thread.h"

// ------------------------------------------------------------------
UPS_SERVICE::UPS_SERVICE(UPS_THREAD *p)
{
	parent = p;
}

// ------------------------------------------------------------------
bool UPS_SERVICE::init()
{
	return false;
}

// ------------------------------------------------------------------
UPS_SERVICE::~UPS_SERVICE()
{
}

// ------------------------------------------------------------------
void UPS_SERVICE::onChangedMain(bool main)
{
	m_upsConfig.main = main;
	syncToSlave();
	onRefreshUps();
}

// ------------------------------------------------------------------
void UPS_SERVICE::startMonitor()
{
	m_upsConfig.monitor = true;
	syncToSlave();
}

// ------------------------------------------------------------------
void UPS_SERVICE::stopMonitor()
{
	m_upsConfig.monitor = false;
	syncToSlave();
}

// ------------------------------------------------------------------
void UPS_SERVICE::onRefreshUps()
{
}

// ------------------------------------------------------------------
void UPS_SERVICE::onConnected()
{
}

// ------------------------------------------------------------------
void UPS_SERVICE::onDisconnected()
{
}

// ------------------------------------------------------------------
void UPS_SERVICE::onConnectedPort(qint32 port)
{
	Q_UNUSED(port);
}

// ------------------------------------------------------------------
void UPS_SERVICE::onDisconnectedPort(qint32 port)
{
	Q_UNUSED(port);
}

// ------------------------------------------------------------------
bool UPS_SERVICE::onQuery()
{
	return false;
}

// ------------------------------------------------------------------
bool UPS_SERVICE::onLive()
{
	return false;
}

// ------------------------------------------------------------------
void UPS_SERVICE::onChangedDeviceState()
{
	updateState();
	onRefreshUps();
}

// ------------------------------------------------------------------
void UPS_SERVICE::onChangedPortState()
{
	updateState();
	onRefreshUps();
}

// ------------------------------------------------------------------
void UPS_SERVICE::updateState()
{
}

// ------------------------------------------------------------------
void UPS_SERVICE::syncToSlave()
{
	if(m_upsConfig.main)
		emit sigSyncToSlave(m_upsConfig.toMap());
}

// ------------------------------------------------------------------
void UPS_SERVICE::onSyncToSlave(QVariantMap data)
{
	if(!m_upsConfig.main)
	{
		UpsConfig m_masterConfig(data);
		if(m_masterConfig.main)
		{
			LogUpsInfo("UPS_SERVICE::onSyncToSlave processed");
			m_upsConfig.monitor = m_masterConfig.monitor;
//			qDebug() << "upsMasterConfig accepted";
		}
	}
}

// ------------------------------------------------------------------
