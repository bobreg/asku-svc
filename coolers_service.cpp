#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "coolers_service.h"
#include "coolers_thread.h"
#include "coolers_vesper.h"

// ------------------------------------------------------------------
COOLERS_SERVICE::COOLERS_SERVICE(COOLERS_THREAD *p) : MODBUS_SERVICE(NULL)
{
	parent = p;
}

// ------------------------------------------------------------------
bool COOLERS_SERVICE::init()
{
	LogCoolerInfo("CoolersService started");

	vesper[0] = new VESPER_DEVICE(this, m_setup.coolers.address1, VESPER_TYPE_E3_8300);
	vesper[1] = new VESPER_DEVICE(this, m_setup.coolers.address2, VESPER_TYPE_E3_8300);
	vesper[2] = new VESPER_DEVICE(this, m_setup.coolers.address3, VESPER_TYPE_E3_8300);
	vesper[3] = new VESPER_DEVICE(this, m_setup.coolers.address4, VESPER_TYPE_E3_8300);

	addDevice(vesper[0]);
	addDevice(vesper[1]);
	addDevice(vesper[2]);
	addDevice(vesper[3]);

	addConnection(m_setup.com1.ip, m_setup.coolers.port1);
	addConnection(m_setup.com2.ip, m_setup.coolers.port2);

	updateState();
	startConnect(10000);

	return MODBUS_SERVICE::init();
}

// ------------------------------------------------------------------
COOLERS_SERVICE::~COOLERS_SERVICE()
{
	if(vesper[3])
	{
		removeDevice(vesper[3]);
		delete vesper[3];
		vesper[3] = NULL;
	}
	if(vesper[2])
	{
		removeDevice(vesper[2]);
		delete vesper[2];
		vesper[2] = NULL;
	}
	if(vesper[1])
	{
		removeDevice(vesper[1]);
		delete vesper[1];
		vesper[1] = NULL;
	}
	if(vesper[0])
	{
		removeDevice(vesper[0]);
		delete vesper[0];
		vesper[0] = NULL;
	}
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::onChangedMain(bool main)
{
	if(main)
	{
		bool need = false;
		for(qint32 i = 0; i < N_COOLERS; i++)
			if(!m_coolerConfig.Vesper[i].first)
				need = true;
		if(need)
			QTimer::singleShot(10000, this, SLOT(setFirstCommands()));
	}

	m_coolerConfig.main = main;
	syncToSlave();
	onRefreshCoolers();
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::setTemperature(quint32 n_cooler, bool on, double temp)
{
	if(n_cooler < VESPER_N_DEVICES)
	{
		if(calcFreq(n_cooler, on, temp))
		{
//			m_coolerConfig.Vesper[n_cooler].prdon = on;
//			m_coolerConfig.Vesper[n_cooler].temp = temp;
			syncToSlave();
		}
	}
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::setExtTemperature(double temp)
{
	m_coolerConfig.exttemp = temp;
//	if(calcFreq())
//	syncToSlave();
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::setReset()
{
	m_coolerConfig.reset = true;
	syncToSlave();

	vesper[0]->setReset();
	vesper[1]->setReset();
	vesper[2]->setReset();
	vesper[3]->setReset();

	m_coolerConfig.reset = false;
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::setManual(bool manual)
{
	m_coolerConfig.manual = manual;
	syncToSlave();
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::setOn(quint32 n_cooler, bool on)
{
	if(n_cooler < VESPER_N_DEVICES)
	{
		m_coolerConfig.Vesper[n_cooler].first = true;
		m_coolerConfig.Vesper[n_cooler].start = on;
		syncToSlave();

		if(on)
			vesper[n_cooler]->setStart(false);
		else
			vesper[n_cooler]->setStop();
	}
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::setFreq(quint32 n_cooler, double freq)
{
	if(n_cooler < VESPER_N_DEVICES)
	{
		m_coolerConfig.Vesper[n_cooler].freq = freq;
		m_coolerConfig.Vesper[n_cooler].freqUpdated = QDateTime::currentDateTime();
		vesper[n_cooler]->setFrequency(freq * 100.0);
	}
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::startMonitor()
{
	m_coolerConfig.monitor = true;
	syncToSlave();
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::stopMonitor()
{
	m_coolerConfig.monitor = false;
	syncToSlave();
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::onRefreshCoolers()
{
	if(!m_coolerConfig.main || !m_coolerConfig.monitor)
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

	VesperState & state1 = vesper[0]->state();
	VesperState & state2 = vesper[1]->state();
	VesperState & state3 = vesper[2]->state();
	VesperState & state4 = vesper[3]->state();

	bool work1 = vesper[0]->isActualState();
	bool work2 = vesper[1]->isActualState();
	bool work3 = vesper[2]->isActualState();
	bool work4 = vesper[3]->isActualState();

	info["vesper11Active"] = work1 ? QString::number(state1.State_8300.RegState.Bits.Ready) : " ";
	info["vesper11Fail"]   = work1 ? QString::number(state1.State_8300.RegState.Bits.Fail) : " ";
	info["vesper11Start"]  = work1 ? QString::number(state1.State_8300.RegState.Bits.Rotation) : " ";
	info["vesper11Freq"]   = work1 ? QString::number(state1.State_8300.RegFrequency.freq(),'f',1) : " ";
	info["vesper11Error"]  = work1 ? QString::number(state1.State_8300.RegErrorCode.errorCode()) : " ";

	info["vesper12Active"] = work2 ? QString::number(state2.State_8300.RegState.Bits.Ready) : " ";
	info["vesper12Fail"]   = work2 ? QString::number(state2.State_8300.RegState.Bits.Fail) : " ";
	info["vesper12Start"]  = work2 ? QString::number(state2.State_8300.RegState.Bits.Rotation) : " ";
	info["vesper12Freq"]   = work2 ? QString::number(state2.State_8300.RegFrequency.freq(),'f',1) : " ";
	info["vesper12Error"]  = work2 ? QString::number(state2.State_8300.RegErrorCode.errorCode()) : " ";

	info["vesper21Active"] = work3 ? QString::number(state3.State_8300.RegState.Bits.Ready) : " ";
	info["vesper21Fail"]   = work3 ? QString::number(state3.State_8300.RegState.Bits.Fail) : " ";
	info["vesper21Start"]  = work3 ? QString::number(state3.State_8300.RegState.Bits.Rotation) : " ";
	info["vesper21Freq"]   = work3 ? QString::number(state3.State_8300.RegFrequency.freq(),'f',1) : " ";
	info["vesper21Error"]  = work3 ? QString::number(state3.State_8300.RegErrorCode.errorCode()) : " ";

	info["vesper22Active"] = work4 ? QString::number(state4.State_8300.RegState.Bits.Ready) : " ";
	info["vesper22Fail"]   = work4 ? QString::number(state4.State_8300.RegState.Bits.Fail) : " ";
	info["vesper22Start"]  = work4 ? QString::number(state4.State_8300.RegState.Bits.Rotation) : " ";
	info["vesper22Freq"]   = work4 ? QString::number(state4.State_8300.RegFrequency.freq(),'f',1) : " ";
	info["vesper22Error"]  = work4 ? QString::number(state4.State_8300.RegErrorCode.errorCode()) : " ";

	info["manualCheckBox"] = m_coolerConfig.manual;
	info["pushSetFreq"] = m_coolerConfig.manual ? 0 : -1;
	info["pushOn1"] = m_coolerConfig.manual ? (m_coolerConfig.Vesper[0].start || m_coolerConfig.Vesper[1].start) : -1;
	info["pushOn2"] = m_coolerConfig.manual ? (m_coolerConfig.Vesper[2].start || m_coolerConfig.Vesper[3].start) : -1;
	info["pushOff1"] = m_coolerConfig.manual ? (!(m_coolerConfig.Vesper[0].start || m_coolerConfig.Vesper[1].start)) : -1;
	info["pushOff2"] = m_coolerConfig.manual ? (!(m_coolerConfig.Vesper[2].start || m_coolerConfig.Vesper[3].start)) : -1;

	info["vesperSlider1"] = (qint32)(m_coolerConfig.manual ? -1 : (m_coolerConfig.Vesper[0].freq));
	info["vesperSlider2"] = (qint32)(m_coolerConfig.manual ? -1 : (m_coolerConfig.Vesper[2].freq));

	info["tenv"] = m_coolerConfig.exttemp == -255.0         ? " - " : QString("%1").arg(m_coolerConfig.exttemp, 0, 'f', 1);
	info["tprd1"] = m_coolerConfig.Vesper[0].temp == -255.0 ? " - " : QString("%1").arg(m_coolerConfig.Vesper[0].temp, 0, 'f', 1);
	info["tprd2"] = m_coolerConfig.Vesper[2].temp == -255.0 ? " - " : QString("%1").arg(m_coolerConfig.Vesper[2].temp, 0, 'f', 1);

	info["onprd1"] = m_coolerConfig.Vesper[0].prdon ? "1" : "0";
	info["onprd2"] = m_coolerConfig.Vesper[2].prdon ? "1" : "0";

	emit sigCoolersState(info);
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::onConnected()
{
	startQuery(180);
	startLive(5000);

	vesper[0]->onConnectedDevice();
	vesper[1]->onConnectedDevice();
	vesper[2]->onConnectedDevice();
	vesper[3]->onConnectedDevice();
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::onDisconnected()
{
	stopQuery();
	stopLive();

	vesper[0]->onDisconnectedDevice();
	vesper[1]->onDisconnectedDevice();
	vesper[2]->onDisconnectedDevice();
	vesper[3]->onDisconnectedDevice();
}

// ------------------------------------------------------------------
bool COOLERS_SERVICE::onQuery()
{
	if(vesper[0]->processCommands())
		return true;

	if(vesper[1]->processCommands())
		return true;

	if(vesper[2]->processCommands())
		return true;

	if(vesper[3]->processCommands())
		return true;

	quint32 device = nextQueryDevice();

	if(vesper[device]->processQuery())
		return true;

	return false;
}

// ------------------------------------------------------------------
bool COOLERS_SERVICE::onLive()
{
	if(m_coolerConfig.Vesper[0].first)
		vesper[0]->updateCommands();
	if(m_coolerConfig.Vesper[1].first)
		vesper[1]->updateCommands();
	if(m_coolerConfig.Vesper[2].first)
		vesper[2]->updateCommands();
	if(m_coolerConfig.Vesper[3].first)
		vesper[3]->updateCommands();

	return false;
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::onChangedDeviceState()
{
	updateState();
	onRefreshCoolers();
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::onChangedPortState()
{
	updateState();
	onRefreshCoolers();
}

// ------------------------------------------------------------------
double COOLERS_SERVICE::freqFromExternalT()
{
	double Text = m_coolerConfig.exttemp;
	double Freq;

	if(Text == -255.0)
		Freq = 50.0;
	else if(Text < 5.0)
		Freq = 10.0;
	else if(Text < 15.0)
		Freq = 25.0;
	else if(Text < 20.0)
		Freq = 40.0;
	else if(Text < 25.0)
		Freq = 50.0;
	else
		Freq = 50.0;

	return Freq;
}

// ------------------------------------------------------------------
bool COOLERS_SERVICE::calcFreq(quint32 n_vesper, bool on, double temperature)
{
	bool cmd = false;

	static QString strOld[4]; 
	QString strNow = QString("Status=%8    Text=%1 Tvesp%2=%3 VespOn%2=%4 Freq=%5       on=%6 temp=%7")
		.arg(m_coolerConfig.exttemp)
		.arg(n_vesper)
		.arg(m_coolerConfig.Vesper[n_vesper].temp, 4, 'f', 1)
		.arg(m_coolerConfig.Vesper[n_vesper].start)
		.arg(m_coolerConfig.Vesper[n_vesper].freq, 4, 'f', 1)
		.arg(on)
		.arg(temperature, 4, 'f', 1)
		.arg(m_coolerConfig.Vesper[n_vesper].status);
	if(strOld[n_vesper] != strNow)
	{
		LogCtrlInfo("%s: %s",
		qPrintable(QDateTime::currentDateTime().toString("HH:mm:ss")), 
		qPrintable(strNow));
		strOld[n_vesper] = strNow;
	}

	m_coolerConfig.Vesper[n_vesper].prdon = on;
	m_coolerConfig.Vesper[n_vesper].temp = temperature;

	if(m_coolerConfig.main && !m_coolerConfig.manual && m_coolerConfig.Vesper[n_vesper].first)
	{
		if(m_coolerConfig.Vesper[n_vesper].status < 0)
		{
			if(on)
			{
				if(temperature > 40.0)
					m_coolerConfig.Vesper[n_vesper].status = 1;	//starting
				else if(temperature < 25.0)
					m_coolerConfig.Vesper[n_vesper].status = 2;	//stopping
				else
					m_coolerConfig.Vesper[n_vesper].status = 3;	//controlling
			}
			else
			{
				m_coolerConfig.Vesper[n_vesper].status = 2;	//stopping
			}
		}
	}
	else
	{
		m_coolerConfig.Vesper[n_vesper].status = -1;
		return cmd;
	}

	double Freq = 0;

	switch(m_coolerConfig.Vesper[n_vesper].status)
	{
		case 1:			//starting

			Freq = freqFromExternalT();

			if(m_coolerConfig.Vesper[n_vesper].freq != Freq)
			{
				setFreq(n_vesper, Freq);
				cmd = true;
			}
//			if(!m_coolerConfig.Vesper[n_vesper].start)
			{
				setOn(n_vesper, true);
				cmd = true;
			}

			m_coolerConfig.Vesper[n_vesper].status = 3;	//control
			break;

		case 2:		//stopping
			if(m_coolerConfig.Vesper[n_vesper].start)
			{
				setOn(n_vesper, false);
				cmd = true;
			}

			m_coolerConfig.Vesper[n_vesper].status = 4;	//wait for start
			break;

		case 3:		//control
			if(on)
			{
				if(temperature < 25.0)
				{
					m_coolerConfig.Vesper[n_vesper].status = 2;	//stopping
				}
				else if(temperature < 35.0 && timeDiff(m_coolerConfig.Vesper[n_vesper].freqUpdated) >= 600000) //10 min
				{
					m_coolerConfig.Vesper[n_vesper].status = 7;	//deforcing
				}
				else if(temperature > 45.0 && timeDiff(m_coolerConfig.Vesper[n_vesper].freqUpdated) >= 600000) //10 min
				{
					m_coolerConfig.Vesper[n_vesper].status = 5;	//forcing next
				}
				else if(temperature > 50.0 && m_coolerConfig.Vesper[n_vesper].freq < 50.0)
				{
					m_coolerConfig.Vesper[n_vesper].status = 6;	//forcing extra
				}
			}
			else
			{
				m_coolerConfig.Vesper[n_vesper].status = 2;	//stopping
			}
			break;

		case 4:		//wait for start
			if(on && temperature > 40.0)
			{
				m_coolerConfig.Vesper[n_vesper].status = 1;	//starting
			}
			break;

		case 5:		//forcing
			Freq = m_coolerConfig.Vesper[n_vesper].freq + 5.0;

			if(Freq > 50.0)
				Freq = 50.0;

			if(m_coolerConfig.Vesper[n_vesper].freq != Freq)
			{
				setFreq(n_vesper, Freq);
				setOn(n_vesper, true);
				cmd = true;
			}

			m_coolerConfig.Vesper[n_vesper].status = 3;	//control

			break;

		case 6:		//forcing extra
			Freq = 50.0;

			if(m_coolerConfig.Vesper[n_vesper].freq != Freq)
			{
				setFreq(n_vesper, Freq);
				setOn(n_vesper, true);
				cmd = true;
			}

			m_coolerConfig.Vesper[n_vesper].status = 3;	//control
			break;

		case 7:		//deforcing
			Freq = m_coolerConfig.Vesper[n_vesper].freq - 5.0;

			if(Freq <= 0.0)
			{
				m_coolerConfig.Vesper[n_vesper].status = 2;	//stopping
				break;
			}
			else if(m_coolerConfig.Vesper[n_vesper].freq != Freq)
			{
				setFreq(n_vesper, Freq);
				setOn(n_vesper, true);
				cmd = true;
			}

			m_coolerConfig.Vesper[n_vesper].status = 3;	//control
			break;
	}
	return cmd;
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::syncToSlave()
{
	if(m_coolerConfig.main)
		emit sigSyncToSlave(m_coolerConfig.toMap());
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::onSyncToSlave(QVariantMap data)
{
	if(!m_coolerConfig.main)
	{
		CoolersConfig m_masterConfig(data);
		if(m_masterConfig.main)
		{
			LogCoolerInfo("COOLERS_SERVICE::onSyncToSlave processed");
			setManual(m_masterConfig.manual);
//			m_coolerConfig.manual = m_masterConfig.manual;
			m_coolerConfig.monitor = m_masterConfig.monitor;
			m_coolerConfig.exttemp = m_masterConfig.exttemp;
			for(qint32 i = 0; i < N_COOLERS; i++)
			{
				if(m_masterConfig.Vesper[i].first)
				{
					setFreq(i, m_masterConfig.Vesper[i].freq);
					setOn(i, m_masterConfig.Vesper[i].start);
//					m_coolerConfig.Vesper[i].start = m_masterConfig.Vesper[i].start;
//					m_coolerConfig.Vesper[i].freq = m_masterConfig.Vesper[i].freq;
					m_coolerConfig.Vesper[i].temp = m_masterConfig.Vesper[i].temp;
					m_coolerConfig.Vesper[i].prdon = m_masterConfig.Vesper[i].prdon;
				}
			}
//		qDebug() << "coolersMasterConfig accepted";
		}
	}
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::verifyFirstCommands()
{
	if(m_coolerConfig.main)
	{
		for(qint32 i = 0; i < N_COOLERS; i++)
		{
			if(!m_coolerConfig.Vesper[i].first)
			{
				VesperState & state = vesper[i]->state();
				bool work = vesper[i]->isActualState();

				if(work && state.State_8300.RegState.Bits.Rotation)
				{
					setFreq(i, m_setup.coolers.frequency);
					setOn(i, true);
				}
			}
		}
	}
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::setFirstCommands()
{
	if(m_coolerConfig.main)
	{
		bool was = false;
		for(qint32 i = 0; i < N_COOLERS; i++)
			if(!m_coolerConfig.Vesper[i].first)
			{
				m_coolerConfig.Vesper[i].first = true;
				was = true;
			}
		if(was)
			syncToSlave();
	}
}

// ------------------------------------------------------------------
