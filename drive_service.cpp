#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "drive_service.h"
#include "drive_thread.h"
#include "drive_vector.h"

// ------------------------------------------------------------------
DRIVE_SERVICE::DRIVE_SERVICE(DRIVE_THREAD *p) : MODBUS_SERVICE(NULL)
{
	parent = p;
}

// ------------------------------------------------------------------
bool DRIVE_SERVICE::init()
{
	LogDriveInfo("DriveService started");

	vector[0] = new VECTOR_DEVICE(this, m_setup.drive.address1);
	vector[1] = new VECTOR_DEVICE(this, m_setup.drive.address2);

	vector[0]->setSpeedPosition(false);
	vector[1]->setSpeedPosition(false);

	addDevice(vector[0]);
	addDevice(vector[1]);

	addConnection(m_setup.com1.ip, m_setup.drive.port1);
	addConnection(m_setup.com2.ip, m_setup.drive.port2);

	updateState();
	startConnect(10000);

	return MODBUS_SERVICE::init();
}

// ------------------------------------------------------------------
DRIVE_SERVICE::~DRIVE_SERVICE()
{
	if(vector[1])
	{
		removeDevice(vector[1]);
		delete vector[1];
		vector[1] = NULL;
	}
	if(vector[0])
	{
		removeDevice(vector[0]);
		delete vector[0];
		vector[0] = NULL;
	}
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::onChangedMain(bool main)
{
	if(main && !m_driveConfig.first)
		QTimer::singleShot(10000, this, SLOT(setFirstCommands()));

	m_driveConfig.main = main;
//	LogInfo("DRIVE_SERVICE::onChangedMain");

	syncToSlave();
	onRefreshDrive();
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::setServo(quint32 drive)
{
	m_driveConfig.start = drive ? true : false;
//	m_driveConfig.first = true;
	m_driveConfig.override = drive;
	LogDriveInfo("DRIVE_SERVICE::setServo");

	syncToSlave();

	if(drive == DRIVE_CMD_ON_1)
	{
		vector[0]->setReset();
		vector[0]->setStart(false);
		vector[1]->setReset();
		vector[1]->setStart(false);
	}
	else if(drive == DRIVE_CMD_ON_2)
	{
		vector[1]->setReset();
		vector[1]->setStart(false);
		vector[0]->setReset();
		vector[0]->setStart(false);
	}
	else if(drive == DRIVE_CMD_ON)
	{
		vector[0]->setReset();
		vector[1]->setReset();
		vector[0]->setStart(false);
		vector[1]->setStart(false);
	}
	else /*if(drive == DRIVE_CMD_OFF)*/
	{
		LogDriveInfo("DRIVE::setStop!!");
		vector[0]->setStop();
		vector[1]->setStop();
		vector[0]->setReset();
		vector[1]->setReset();
	}
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::setOverride(quint32 n_drive)
{
	m_driveConfig.override = n_drive;

	if(m_driveConfig.separate)
		return;

//	LogInfo("DRIVE_SERVICE::setOverride");
	syncToSlave();

	if(n_drive == 1)
	{
		vector[0]->setReserveOverride(1);
		vector[1]->setReserveOverride(1);
	}
	if(n_drive == 2)
	{
		vector[0]->setReserveOverride(2);
		vector[1]->setReserveOverride(2);
	}

	m_driveConfig.override = 0;
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::setSpeed(double speed)
{
	m_driveConfig.speed = speed;
//	m_driveConfig.first = true;
//	LogInfo("DRIVE_SERVICE::setSpeed");
	syncToSlave();

	vector[0]->setSpeed(speed * 60.0 / 360.0 * 100.0);
	vector[1]->setSpeed(speed * 60.0 / 360.0 * 100.0);
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::setReset()
{
	m_driveConfig.reset = true;
//	LogInfo("DRIVE_SERVICE::setReset");
	syncToSlave();

	vector[0]->setReset();
	vector[1]->setReset();

	m_driveConfig.reset = false;
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::setManual(bool manual)
{
	m_driveConfig.manual = manual;
//	LogInfo("DRIVE_SERVICE::setManual");
	syncToSlave();
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::startMonitor()
{
	m_driveConfig.monitor = true;
//	LogInfo("DRIVE_SERVICE::startMonitor");
	syncToSlave();
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::stopMonitor()
{
	m_driveConfig.monitor = false;
//	LogInfo("DRIVE_SERVICE::stopMonitor");
	syncToSlave();
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::onRefreshDrive()
{
	if(!m_driveConfig.main || !m_driveConfig.monitor)
		return;

	QVariantMap info;

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

	VectorState & state1 = vector[0]->state();
	VectorState & state2 = vector[1]->state();

	bool work1 = vector[0]->isActualState();
	bool work2 = vector[1]->isActualState();

	info["editVersion1"] = work1 ? state1.State.strVersion() : " ";
	info["editSerial1"]  = work1 ? QString::number(state1.State.RegSerial.Serial()) : " ";
	info["editTime1"]    = work1 ? QString::number(state1.State.RegWorkHours.Hours()) : " ";
	info["editConfig1"]  = work1 ? QString::number(state1.State.RegFWConf.Config()) : " ";
	info["editAzimuth1"] = work1 ? QString::number(state1.State.RegPosition.RealValue()) : " ";
	info["editSpeed1"]   = work1 ? QString::number(state1.State.RegSpeed.RealValue()) : " ";
	info["editMoment1"]  = work1 ? QString::number(state1.State.RegMoment.RealValue()) : " ";
	info["editCurrent1"] = work1 ? QString::number(state1.State.RegCurrent.RealValue()) : " ";
	info["editVoltage1"] = work1 ? QString::number(state1.State.RegVoltage.RealValue()) : " ";

	info["editWarn1"]     = work1 ? QString::number(state1.State.RegState.Bits.Warning) : " ";
	info["editAlarm1"]    = work1 ? QString::number(state1.State.RegState.Bits.Fail) : " ";
	info["editReady1"]    = work1 ? QString::number(state1.State.RegState.Bits.Ready) : " ";
	info["editWork1"]     = work1 ? QString::number(state1.State.RegState.Bits.WorkingAlg) : " ";
	info["editHeat1"]     = work1 ? QString::number(state1.State.RegOverheat.Bits.Sensor1 || state1.State.RegOverheat.Bits.Sensor2 || state1.State.RegOverheat.Bits.Sensor3 || state1.State.RegOverheat.Bits.Sensor4 || state1.State.RegOverheat.Bits.Invertor) : " ";
	info["editInvertor1"] = work1 ? QString::number(state1.State.RegState.Bits.InvertorOn) : " ";
	info["editDist1"]     = work1 ? QString::number(state1.State.RegState.Bits.NoLocal) : " ";
	info["editSensor1"]   = work1 ? QString::number(state1.State.RegHardware.Bits.SensorIncBreak || state1.State.RegHardware.Bits.ErrorIndexLabel) : " ";
	info["editPwrReady1"] = work1 ? QString::number(state1.State.RegState.Bits.PowerReady) : " ";
	info["editBan1"]      = work1 ? QString::number(state1.State.RegState.Bits.NoLocal) : " ";
	info["editMain1"]     = work1 ? QString::number(state1.State.RegState.Bits.Main) : " ";

	info["editVersion2"] = work2 ? state2.State.strVersion() : " ";
	info["editSerial2"]  = work2 ? QString::number(state2.State.RegSerial.Serial()) : " ";
	info["editTime2"]    = work2 ? QString::number(state2.State.RegWorkHours.Hours()) : " ";
	info["editConfig2"]  = work2 ? QString::number(state2.State.RegFWConf.Config()) : " ";
	info["editAzimuth2"] = work2 ? QString::number(state2.State.RegPosition.RealValue()) : " ";
	info["editSpeed2"]   = work2 ? QString::number(state2.State.RegSpeed.RealValue()) : " ";
	info["editMoment2"]  = work2 ? QString::number(state2.State.RegMoment.RealValue()) : " ";
	info["editCurrent2"] = work2 ? QString::number(state2.State.RegCurrent.RealValue()) : " ";
	info["editVoltage2"] = work2 ? QString::number(state2.State.RegVoltage.RealValue()) : " ";

	info["editWarn2"]     = work2 ? QString::number(state2.State.RegState.Bits.Warning) : " ";
	info["editAlarm2"]    = work2 ? QString::number(state2.State.RegState.Bits.Fail) : " ";
	info["editReady2"]    = work2 ? QString::number(state2.State.RegState.Bits.Ready) : " ";
	info["editWork2"]     = work2 ? QString::number(state2.State.RegState.Bits.WorkingAlg) : " ";
	info["editHeat2"]     = work2 ? QString::number(state2.State.RegOverheat.Bits.Sensor1 || state2.State.RegOverheat.Bits.Sensor2 || state2.State.RegOverheat.Bits.Sensor3 || state2.State.RegOverheat.Bits.Sensor4 || state2.State.RegOverheat.Bits.Invertor) : " ";
	info["editInvertor2"] = work2 ? QString::number(state2.State.RegState.Bits.InvertorOn) : " ";
	info["editDist2"]     = work2 ? QString::number(state2.State.RegState.Bits.NoLocal) : " ";
	info["editSensor2"]   = work2 ? QString::number(state2.State.RegHardware.Bits.SensorIncBreak || state2.State.RegHardware.Bits.ErrorIndexLabel) : " ";
	info["editPwrReady2"] = work2 ? QString::number(state2.State.RegState.Bits.PowerReady) : " ";
	info["editBan2"]      = work2 ? QString::number(state2.State.RegState.Bits.NoLocal) : " ";
	info["editMain2"]     = work2 ? QString::number(state2.State.RegState.Bits.Main) : " ";

	info["checkManual"]  = m_driveConfig.manual;
	info["pushSetSpeed"] = m_driveConfig.manual ? 0 : -1;
	info["spinSpeed"]    = (double)(m_driveConfig.manual ? -1.0 : (m_driveConfig.speed));

	if(m_driveConfig.separate)
	{
		info["pushOn"]       = -1;
		info["pushOff"]      = -1;
		info["pushSet1"]     = m_driveConfig.manual ? (work1 ? state1.State.RegState.Bits.InvertorOn : -1) : -1;
		info["pushSet2"]     = m_driveConfig.manual ? (work2 ? state2.State.RegState.Bits.InvertorOn : -1) : -1;
	}
	else
	{
		info["pushOn"]       = m_driveConfig.manual ? (m_driveConfig.start) : -1;
		info["pushOff"]      = m_driveConfig.manual ? (!m_driveConfig.start) : -1;
		info["pushSet1"]     = m_driveConfig.manual ? (work1 ? state1.State.RegState.Bits.Main : -1) : -1;
		info["pushSet2"]     = m_driveConfig.manual ? (work2 ? state2.State.RegState.Bits.Main : -1) : -1;
	}

	emit sigDriveState(info);
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::onConnected()
{
	vector[0]->onConnectedDevice();
	vector[1]->onConnectedDevice();

	startQuery(180);
	startLive(5000);
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::onDisconnected()
{
	stopQuery();
	stopLive();

	vector[0]->onDisconnectedDevice();
	vector[1]->onDisconnectedDevice();
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::onConnectedPort(qint32 port)
{
    Q_UNUSED(port);

/*	if(port == vector[0]->connection())
		vector[0]->onConnectedDevice();

	if(port == vector[1]->connection())
		vector[1]->onConnectedDevice();*/
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::onDisconnectedPort(qint32 port)
{
    Q_UNUSED(port);

/*	if(port == vector[0]->connection())
		vector[0]->onDisconnectedDevice();

	if(port == vector[1]->connection())
		vector[1]->onDisconnectedDevice();*/
}

// ------------------------------------------------------------------
bool DRIVE_SERVICE::onQuery()
{
	if(vector[0]->processCommands())
		return true;

	if(vector[1]->processCommands())
		return true;

	quint32 device = nextQueryDevice();

	if(vector[device]->processQuery())
		return true;

	return false;
}

// ------------------------------------------------------------------
bool DRIVE_SERVICE::onLive()
{
	if(m_driveConfig.first)
	{
		vector[0]->updateCommands();
		vector[1]->updateCommands();
	}

	return false;
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::onChangedDeviceState()
{
	updateState();
	onRefreshDrive();
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::onChangedPortState()
{
	updateState();
	onRefreshDrive();
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::syncToSlave()
{
	if(m_driveConfig.main)
		emit sigSyncToSlave(m_driveConfig.toMap(), bDriveState.toMap(), QVariantMap());
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure)
{
	if(!m_driveConfig.main)
	{
		DriveConfig m_masterConfig(config);
		if(m_masterConfig.main && m_masterConfig.first)
		{
			LogDriveInfo("DRIVE_SERVICE::onSyncToSlave processed");
			setOverride(m_masterConfig.override);
			setSpeed(m_masterConfig.speed);
			setServo(m_masterConfig.start ? (m_masterConfig.override == 1 ? DRIVE_CMD_ON_1 : (m_masterConfig.override == 2 ? DRIVE_CMD_ON_2 : DRIVE_CMD_OFF)) : DRIVE_CMD_OFF);
			setManual(m_masterConfig.manual);
			m_driveConfig.manual = m_masterConfig.manual;
			m_driveConfig.monitor = m_masterConfig.monitor;
//			m_driveConfig.start = m_masterConfig.start;
//			m_driveConfig.speed = m_masterConfig.speed;
//			qDebug() << "driveMasterConfig accepted";
		}

		if(bDriveState.fromMap(state))
		{
//			qDebug() << bDriveState.dump();
			emit sigState(bDriveState);
		}

		Q_UNUSED(measure);
	}
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::verifyFirstCommands()
{
	if(m_driveConfig.main && !m_driveConfig.first)
	{
		VectorState & state1 = vector[0]->state();
		VectorState & state2 = vector[1]->state();

		bool work1 = vector[0]->isActualState();
		bool work2 = vector[1]->isActualState();

		bool invertor1 = work1 && state1.State.RegState.Bits.InvertorOn;
		bool invertor2 = work2 && state2.State.RegState.Bits.InvertorOn;

		LogInfo("DRIVE_SERVICE:: firstCommands:: w1=%d  w2=%d  i1=%d  i2=%d", work1, work2, invertor1, invertor2);

		if(work1 || work2)
		{
			setOverride(invertor1 ? 1 : (invertor2 ? 2 : 0));
			setSpeed(m_setup.module.lastMode == 1 ? m_setup.drive.speed2 : m_setup.drive.speed1);
			setServo(invertor1 ? DRIVE_CMD_ON_1 : (invertor2 ? DRIVE_CMD_ON_2 : DRIVE_CMD_OFF));
			emit sigButtonServo(invertor1 ? 1 : (invertor2 ? 2 : 0));
		}

		m_driveConfig.first = true;

		syncToSlave();
	}
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::setFirstCommands()
{
	if(m_driveConfig.main && !m_driveConfig.first)
	{
		m_driveConfig.first = true;
		syncToSlave();
	}
}

// ------------------------------------------------------------------
