#include "../common/logger.h"
#include <QFile>
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "dasd_service.h"
#include "dasd_device.h"
#include "dasd_thread.h"

// ------------------------------------------------------------------
DASD_SERVICE::DASD_SERVICE(DASD_THREAD *p)
{
	parent = p;

	qRegisterMetaType<DEVICE_REGISTERS>("DEVICE_REGISTERS");

#if QT_VERSION >= 0x050000
	tableModeName    = QDir::toNativeSeparators(m_setup.path.tables + QString("/") + m_setup.module.fileMode);
	tableRipchName   = QDir::toNativeSeparators(m_setup.path.tables + QString("/") + m_setup.module.fileRipch);
	tableSwitchName  = QDir::toNativeSeparators(m_setup.path.tables + QString("/") + m_setup.module.fileSwitch);
	tableDisableName = QDir::toNativeSeparators(m_setup.path.tables + QString("/") + m_setup.module.fileDisable);
	tableNchmName    = QDir::toNativeSeparators(m_setup.path.tables + QString("/") + m_setup.module.fileNchm);
#else
	tableModeName    = QDir::convertSeparators(m_setup.path.tables + QString("/") + m_setup.module.fileMode);
	tableRipchName   = QDir::convertSeparators(m_setup.path.tables + QString("/") + m_setup.module.fileRipch);
	tableSwitchName  = QDir::convertSeparators(m_setup.path.tables + QString("/") + m_setup.module.fileSwitch);
	tableDisableName = QDir::convertSeparators(m_setup.path.tables + QString("/") + m_setup.module.fileDisable);
	tableNchmName    = QDir::convertSeparators(m_setup.path.tables + QString("/") + m_setup.module.fileNchm);
#endif

	initialized = false;
	fixedError = false;
	isAvarFref = false;
	isAvarFrefFixed = false;
	loadTablesComplete = false;
	allowPchVoi = true;
	allowPchCtrl = allowPchMain = false;

	checkedErrorZu = false;
	startupParameters = false;

	memset(&devRegs,0,sizeof(devRegs));
	memset(&tables,0,sizeof(tables));

	time1Counter = time2Counter = 0;

	rx0buffer.clear();
	rx1buffer.clear();
	tx0buffer.clear();

	waitTemperature = 0;

	cmdSetMain = 0;
	cmdSetRipch = 0;
	cmdSetImitator = 0;
	cmdSetActiveSensor = 0;

	m_timeChangedMain = QDateTime::currentDateTime();

	offsetLir1 = m_setup.module.lir1_offset;
	offsetLir2 = m_setup.module.lir2_offset;

	isPrmActive = isPrmSkr = isPrmPilot = isPrmGsh = isPrmZu = false;
	codePrmSharu1 = codePrmSharu2 = 0;

	activeSensor = 0;

	isMonitoring = false;
	monitoringRate = 10;
	monitoringCounter = 0;

	regAzimuthCtrl.dword = 0xffffffff;

//SKRPS
	regAzimuthPRL.dword = 0xffffffff;
	azSKR		= m_setup.skrps.skr_azimuth;
	strobeSKR	= m_setup.skrps.skr_strobe;
	azPS		= m_setup.skrps.ps_azimuth;
	strobePS	= m_setup.skrps.ps_strobe;
	periodSKRPS = m_setup.skrps.period;
	countSKRPS = 0;
	needNowSKRPS = false;
	wasSetSKR = wasSetPS = false;
	preLock = false;
	setChangeSKR = true;//false
	setChangePS = true;//false
}

// ------------------------------------------------------------------
bool DASD_SERVICE::init()
{
	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

#ifdef Q_OS_WIN32
	device = new DASD_DEVICE_WIN();
#else
	device = new DASD_DEVICE_LINUX();
#endif

	if(device)
	{
		if(!device->open())
		{
			QString errString = errorString();
			emit sigStatusMessage(errString);
			onChangedState();
			timer->start(100);
		}
		else
		{
			initialized = true;
			QString errString = errorString();
			emit sigStatusMessage(errString);
			onChangedState();
			timer->start(100);
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------
DASD_SERVICE::~DASD_SERVICE()
{
	if(timer)
	{
		timer->stop();
		delete timer;
		timer = NULL;
	}
	if(device)
	{
		if(initialized)
		{
			setShutdown();
			device->close();
		}
		delete device;
		device = NULL;
	}
}

// ------------------------------------------------------------------
QString DASD_SERVICE::errorString()
{
	QString retString;

	switch(device->error())
	{
		case DASD_DEVICE::NoError:
			retString+=QString("0 Готов");
			break;

		case DASD_DEVICE::ErrorNoDeviceDriver:
			retString+=QString("1 Нет драйвера");
			break;

		case DASD_DEVICE::ErrorNoDeviceBoard:
			retString+=QString("2 Нет устройства");
			break;

		case DASD_DEVICE::ErrorInitDevice:
			retString+=QString("3 Ошибка инициализации");
			break;

		case DASD_DEVICE::ErrorReadWrite:
			retString+=QString("4 Ошибка чтения записи");
			break;

		case DASD_DEVICE::ErrorNotInitialized:
			retString+=QString("5 Не инициализировано");
			break;

		case DASD_DEVICE::ErrorInvalidParameter:
			retString+=QString("6 Неверный параметр");
			break;
	}

	return retString;
}

// ------------------------------------------------------------------
void DASD_SERVICE::timeout()
{
	if(!initialized)
	{
		loadTables();
		timer->stop();
		return;
	}

	if(!loadTablesComplete)
	{
		loadTables();
		writeTables();

		loadTablesComplete = true;
		emit sigLoadTablesComplete();
	}

	if(!checkedErrorZu)
		checkErrorZu();

	if(!startupParameters)
		checkStartupParameters();

	readRegisters();
	processCommands();
	processSkrPs();
	checkSensors();
	checkFref();
	monitoring();
	onChangedState();
}

// ------------------------------------------------------------------
void DASD_SERVICE::readRegisters()
{
	read_device_mem(ADRESS_PACK_1,&devRegs.pack1,sizeof(devRegs.pack1));
	read_device_mem(ADRESS_PACK_2,&devRegs.pack2,sizeof(devRegs.pack2));
	read_device_mem(ADRESS_PACK_3,&devRegs.pack3,sizeof(devRegs.pack3));
}

// ------------------------------------------------------------------
void DASD_SERVICE::setConnectedGpr()
{
}

// ------------------------------------------------------------------
void DASD_SERVICE::setDisconnectedGpr()
{
	clearOtherState();
}

// ------------------------------------------------------------------
void DASD_SERVICE::monitoring()
{
	if(isMonitoring)
	{
		if(!monitoringCounter)
			setDump(1);

		monitoringCounter++;

		if(monitoringCounter > monitoringRate)
			monitoringCounter = 0;
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setShutdown()
{
	if(!initialized)
		return;

	setMain(false);
	setPrmSKR(false);
	setPrmPILOT(false);
	setPrmGSH(false);
	setPrmZU(false);
}

// ------------------------------------------------------------------
void DASD_SERVICE::resetTables()
{
	loadTablesComplete = false;
//DEBUG
	loadTables();
	writeTables();
}

// ------------------------------------------------------------------
bool DASD_SERVICE::read_device_mem(quint32 adress, void* buffer, quint32 length)
{
	quint32 tempbuffer[1024];
	quint32 read_length;
	quint32 pointer = 0;

	do
	{
		if(sizeof(tempbuffer) < (length - pointer))
			read_length = sizeof(tempbuffer);
		else
			read_length = (length - pointer);

		device->read_mem(adress+pointer, tempbuffer, read_length);
	
		if(checkError())
			return false;

		memcpy(((unsigned char*)buffer) + pointer, tempbuffer, read_length);

		pointer += read_length;

	}while(pointer < length);

	return true;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::write_device_mem(quint32 adress, void* buffer, quint32 length)
{
	quint32 tempbuffer[1024];
	quint32 write_length;
	quint32 pointer = 0;

	do
	{
		if(sizeof(tempbuffer) < (length - pointer))
			write_length = sizeof(tempbuffer);
		else
			write_length = (length - pointer);

		memcpy(tempbuffer, ((unsigned char*)buffer) + pointer, write_length);

		device->write_mem(adress+pointer, tempbuffer, write_length);
	
		if(checkError())
			return false;

		pointer += write_length;

	}while(pointer < length);

	return true;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::read_device_port(quint32 address, quint16* value)
{
	quint16 tempvalue;

	device->read_port(address,&tempvalue);

	if(checkError())
		return false;

	*value = tempvalue;
	return true;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::write_device_port(quint32 address, quint16* value)
{
	quint16 tempvalue = *value;

	device->write_port(address,&tempvalue);

	if(checkError())
		return false;

	return true;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::checkError()
{
	DASD_DEVICE::ErrorCode errcode = device->error();

	if(errcode != DASD_DEVICE::NoError)
	{
		if(!fixedError)
		{
			QString errString = errorString();
			fixedError = true;
			emit sigStatusMessage(errString);
			onChangedState();
		}
	}
	else
	{
		if(fixedError)
		{
			QString errString = errorString();
			fixedError = false;
			emit sigStatusMessage(errString);
			onChangedState();
		}
	}

	return fixedError;
}

// ------------------------------------------------------------------
void DASD_SERVICE::setCmdMain(bool on)
{
	if(on)
		cmdSetMain = 1;
	else
		cmdSetMain = 2;
}

// ------------------------------------------------------------------
void DASD_SERVICE::setCmdRipch(bool on)
{
	if(on)
		cmdSetRipch = 1;
	else
		cmdSetRipch = 2;
}

// ------------------------------------------------------------------
void DASD_SERVICE::setCmdImitator(bool on)
{
	if(on)
		cmdSetImitator = 1;
	else
		cmdSetImitator = 2;
}

// ------------------------------------------------------------------
void DASD_SERVICE::setCmdActiveSensor(quint32 sensor)
{
	switch(sensor)
	{
		case 0:
			cmdSetActiveSensor = 1;
			break;
		case 1:
			cmdSetActiveSensor = 2;
			break;
		case 2:
			cmdSetActiveSensor = 3;
			break;
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::processCommands()
{
	if(cmdSetStartSkr)
	{
		if(cmdSetStartSkr == 1)
		{
			cmdSetStartSkr = 2;
		}
		else if(cmdSetStartSkr == 2)
		{
			setRegSkrAllOn(CommandOn);
			cmdSetStartSkr = 3;
		}
		if(cmdSetStartSkr == 3)
		{
			cmdSetStartSkr = 4;
		}
		else if(cmdSetStartSkr == 4)
		{
			setRegSkrAllOn(CommandOff);
			cmdSetStartSkr = 0;
		}
	}

	if(cmdSetMain)
	{
		if(cmdSetMain == 1)
		{
			setRegMain(CommandOn);
			cmdSetStartSkr = 1;
		}
		else if(cmdSetMain == 2)
		{
			setRegMain(CommandOff);
			cmdSetStartSkr = 0;
		}

		cmdSetMain = 0;
	}

	if(cmdSetRipch)
	{
		if(cmdSetRipch == 1)
		{
			setRegRipch(CommandOn);
		}
		else if(cmdSetRipch == 2)
		{
			setRegRipch(CommandOff);
		}

		cmdSetRipch = 0;
	}

	if(cmdSetImitator)
	{
		REG_AZIMUTH_CONTROL az_control;

		if(!read_device_mem(ADRESS_AZIMUTH_CONTROL, &az_control, sizeof(az_control)))
			return;

		if(cmdSetImitator == 1)
		{
			az_control.bits.source = 3;
		}
		else if(cmdSetImitator==2)
		{
			az_control.bits.source = activeSensor;
		}

		if(write_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control,sizeof(az_control)))
		{
			cmdSetImitator = 0;
		}
	}

	if(cmdSetActiveSensor)
	{
		REG_AZIMUTH_CONTROL az_control;

		if(!read_device_mem(ADRESS_AZIMUTH_CONTROL, &az_control, sizeof(az_control)))
			return;

		if(cmdSetActiveSensor == 1)
		{
			az_control.bits.source = 0;
			activeSensor = 0;
		}
		else if(cmdSetActiveSensor == 2)
		{
			az_control.bits.source = 1;
			activeSensor = 1;
		}
		else if(cmdSetActiveSensor == 3)
		{
			az_control.bits.source = 2;
			activeSensor = 2;
		}

		if(write_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control,sizeof(az_control)))
		{
			cmdSetActiveSensor = 0;
		}
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setMain(bool on)
{
//	qDebug("COMMAND: main %d", on);
	setRegMain(on ? CommandOn : CommandOff);
	allowPchMain = on;
	allowPchCtrl = on;
	m_timeChangedMain = QDateTime::currentDateTime();
	verifyRipch();
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRipch(bool on)
{
//	qDebug("COMMAND: ripch %d", on);
//	setRegRipch(on ? CommandOn : CommandOff);
	allowPchCtrl = on;
	verifyRipch();
}

// ------------------------------------------------------------------
void DASD_SERVICE::setDisableTotal(bool on)
{
	allowPchVoi = !on;
	verifyRipch();
}

// ------------------------------------------------------------------
void DASD_SERVICE::verifyRipch()
{
	bool on = (allowPchVoi && allowPchCtrl && allowPchMain);
	if(devRegs.pack1.rf_former.bits.allow_pch != on)
		setCmdRipch(on);
		
}

// ------------------------------------------------------------------
void DASD_SERVICE::setDisableDynamic(AskuSektorTable data)
{
	bool result = false;
	if(devTables.setDynamic(data))
	{
		LogModuleInfo("changed dynamic table");
		if(devTables.prepareDynamic() && devTables.combineDisableSwitchDynamic())
			if(writeSwitchTable())
				result = true;

		if(!result)
			LogModuleError("writeSwitchTable error!");
	}
	else
		LogModuleInfo("no change dynamic table");
}

// ------------------------------------------------------------------
void DASD_SERVICE::setTemperature(double value)
{
	bool result = false;

//	LogModuleInfo("set temperature %7.3f", value);
	if(devTables.setTemperature(value) && devTables.isLoadedRipch())
	{
		if(devTables.prepareRipch())
			if(writeRipchTable())
				result = true;

		if(!result)
			LogModuleError("writeRipchTable error!");
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setCmdOverview(quint32 number)
{
	bool result = false;

	LogModuleInfo("setCmdOverview %d", number);
	if(devTables.setSurvey(number) && devTables.isLoadedSwitch())
	{
		if(devTables.prepareSwitch() && devTables.combineDisableSwitchDynamic())
			if(writeSwitchTable())
				result = true;

		if(!result)
			LogModuleError("writeSwitchTable error!");
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::checkSensors()
{
	if(devRegs.pack1.az_control.bits.source == 0 && !isAz1SensorOk() && isAz2SensorOk())
		setCmdActiveSensor(1);
	else if(devRegs.pack1.az_control.bits.source == 1 && isAz1SensorOk() && !isAz2SensorOk())
		setCmdActiveSensor(0);

	if(regAzimuthCtrl.dword != devRegs.pack1.az_control.dword)
		emit sigChangedAzimuthSource(devRegs.pack1.az_control.bits.source);

	regAzimuthCtrl.dword = devRegs.pack1.az_control.dword;
}

// ------------------------------------------------------------------
void DASD_SERVICE::checkFref()
{
	if(devRegs.pack1.state.bits.avar_sync && !isAvarFref)
	{
		isAvarFref = true;
	}
	else if(devRegs.pack1.state.bits.avar_sync && !isAvarFrefFixed)
	{
		isAvarFrefFixed = true;
	}
	else if(!devRegs.pack1.state.bits.avar_sync && isAvarFref)
	{
		isAvarFref = false;
	}
	else if(!devRegs.pack1.state.bits.avar_sync && isAvarFrefFixed)
	{
		isAvarFrefFixed = false;
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::checkErrorZu()
{
	toggleErrorZu1();
	toggleErrorZu2();

	checkedErrorZu = true;
}

// ------------------------------------------------------------------
void DASD_SERVICE::checkStartupParameters()
{
	setFreqDeviation(m_setup.module.freq_deviation);
	startupParameters = true;
}

// ------------------------------------------------------------------
void DASD_SERVICE::processSkrPs()
{
	if(regAzimuthPRL.dword == 0xffffffff)
	{
		regAzimuthPRL.dword = devRegs.pack1.azimuth.dword;
		countSKRPS = 0;
		return;
	}

	bool newObzor = false;
	bool preObzor = false;
	bool instantOff = false;
	bool needPreSKR = false;
	bool needPrePS = false;
	bool thisObzSKRPS = false;
	bool nextObzSKRPS = false;
	qint32 setSKR = 0;
	qint32 setPS = 0;

	if(devRegs.pack1.azimuth.bits.azimuth < 0x01fff && regAzimuthPRL.bits.azimuth > 0x01fff)
		newObzor = true;

	if(devRegs.pack1.azimuth.bits.azimuth > 0x03000)
		preObzor = true;

	if(azSKR < 2)
		needPreSKR=true;

	if(azPS  < 2)
		needPrePS =true;

	if(newObzor)
		countSKRPS++;

	if(periodSKRPS)
	{
		if((periodSKRPS - countSKRPS) < 2)
			nextObzSKRPS = true;

		if((periodSKRPS == 1) || (countSKRPS == periodSKRPS))
			thisObzSKRPS = true;

		if(needNowSKRPS && !nextObzSKRPS && !thisObzSKRPS)
		{
			needNowSKRPS = false;
			countSKRPS = periodSKRPS - 1;
			nextObzSKRPS = true;
		}
	}
	else
	{
		instantOff = true;
	}

	if(countSKRPS >= periodSKRPS)
		countSKRPS = 0;

	if(newObzor)
		preLock = false;

	if(!instantOff)
	{
		if(preObzor && !preLock)
		{
			preLock = true;

			if(nextObzSKRPS)
			{
				if(needPreSKR)	//need preset
				{
					setSKR=1;
				}
				if(needPrePS)	//need preset
				{
					setPS=1;
				}
			}
			else
			{
				if(needPreSKR)	//need preset
				{
					setSKR=-1;
				}
				if(needPrePS)	//need preset
				{
					setPS=-1;
				}
			}
		}

		if(newObzor)
		{
			if(thisObzSKRPS)
			{
				if(!needPreSKR)	//need preset
				{
					setSKR = 1;
				}
				if(!needPrePS)	//need preset
				{
					setPS = 1;
				}
			}
			else
			{
				if(!needPreSKR)	//need preset
				{
					setSKR = -1;
				}
				if(!needPrePS)	//need preset
				{
					setPS = -1;
				}
			}
		}
	}
	else
	{
		setSKR = -1;
		setPS = -1;
	}

	if(setSKR == 1)
	{
		if(!wasSetSKR || setChangeSKR)
		{
			registerSetSKR(true);
		}
	}
	else if(setSKR == -1)
	{
		if(wasSetSKR || setChangeSKR)
		{
			registerSetSKR(false);
		}
	}

	if(setPS == 1)
	{
		if(!wasSetPS || setChangePS)
		{
			registerSetPS(true);
		}
	}
	else if(setPS == -1)
	{
		if(wasSetPS || setChangePS)
		{
			registerSetPS(false);
		}
	}

	regAzimuthPRL.dword = devRegs.pack1.azimuth.dword;
}

// ------------------------------------------------------------------
void DASD_SERVICE::registerSetSKR(bool on)
{
	wasSetSKR = on;
	setChangeSKR = false;

	if(!initialized)
		return;

	if(isPrmActive)
		return;

	//...SKR
	REG_SKR skr;
	skr.bits.azimuth_on = azSKR * 256;
	skr.bits.azimuth_off = (azSKR + strobeSKR) * 256;
	skr.bits.always_on = 0;
	skr.bits.set_on = on;

	write_device_mem(ADRESS_SKR,&skr.dword,sizeof(skr));
}

// ------------------------------------------------------------------
void DASD_SERVICE::registerSetPS(bool on)
{
	wasSetPS = on;
	setChangePS = false;

	if(!initialized)
		return;

	if(isPrmActive)
		return;

	//...PS
	REG_PILOT pilot;
	pilot.bits.azimuth_on = azPS * 256;
	pilot.bits.azimuth_off = (azPS + strobePS) * 256;
	pilot.bits.always_on = 0;
	pilot.bits.set_on = on;

	write_device_mem(ADRESS_PILOT,&pilot.dword,sizeof(pilot));
}

// ------------------------------------------------------------------
void DASD_SERVICE::updateSkrPilot()
{
	azSKR		= m_setup.skrps.skr_azimuth;
	strobeSKR	= m_setup.skrps.skr_strobe;
	azPS		= m_setup.skrps.ps_azimuth;
	strobePS	= m_setup.skrps.ps_strobe;
	periodSKRPS = m_setup.skrps.period;
	setChangeSKR = true;
	setChangePS = true;
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegMain(CommandType cmd)
{
	REG_CONTROL control;

	if(!read_device_mem(ADRESS_CONTROL,&control,sizeof(control)))
		return;

	switch(cmd)
	{
		case CommandOff:
			control.bits.main = 0;
			break;
		case CommandOn:
			control.bits.main = 1;
			break;
		case CommandToggle:
			control.bits.main = !control.bits.main;
			break;
	}

	write_device_mem(ADRESS_CONTROL,&control,sizeof(control));

}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegRipch(CommandType cmd)
{
	REG_COMMON_RF_FORMER rf_former;

	if(!read_device_mem(ADRESS_COMMON_RF_FORMER,&rf_former,sizeof(rf_former)))
		return;

	switch(cmd)
	{
		case CommandOff:
			rf_former.bits.allow_pch = 0;
			break;
		case CommandOn:
			rf_former.bits.allow_pch = 1;
			break;
		case CommandToggle:
			rf_former.bits.allow_pch = !rf_former.bits.allow_pch;
			break;
	}

	write_device_mem(ADRESS_COMMON_RF_FORMER,&rf_former,sizeof(rf_former));
}

// ------------------------------------------------------------------
void DASD_SERVICE::setAmpDelayPilotParam(quint32 parameter, quint32 value)
{
	REG_AMP_DELAY_PILOT amp_delay_pilot;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_AMP_DELAY_PILOT,&amp_delay_pilot.dword,sizeof(amp_delay_pilot)))
	{
		switch(parameter)
		{
			case 0:
				amp_delay_pilot.bits.amplitude = value;
				break;
			case 1:
				amp_delay_pilot.bits.delay = value;
				break;
		}
		write_device_mem(ADRESS_AMP_DELAY_PILOT,&amp_delay_pilot.dword,sizeof(amp_delay_pilot));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setStepDopler(quint32 value)
{
	REG_STEP_DOPLER step_dopler;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_STEP_DOPLER,&step_dopler.dword,sizeof(step_dopler)))
	{
		step_dopler.bits.step = value;
		write_device_mem(ADRESS_STEP_DOPLER,&step_dopler.dword,sizeof(step_dopler));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setFreqDeviation(quint32 value)
{
	REG_FREQ_DEVIATION freq_deviation;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_FREQ_DEVIATION,&freq_deviation.dword,sizeof(freq_deviation)))
	{
		freq_deviation.dword = value;
		write_device_mem(ADRESS_FREQ_DEVIATION,&freq_deviation.dword,sizeof(freq_deviation));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setLir1Offset(quint32 value)
{
	REG_OFFSET offset;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_OFFSET,&offset.dword,sizeof(offset)))
	{
		offset.bits.azimuth1 = value;
		offsetLir1 = m_setup.module.lir1_offset = value;
		write_device_mem(ADRESS_OFFSET,&offset.dword,sizeof(offset));
		emit sigChangedOffsets(offsetLir1,offsetLir2);
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setLir2Offset(quint32 value)
{
	REG_OFFSET offset;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_OFFSET,&offset.dword,sizeof(offset)))
	{
		offset.bits.azimuth2 = value;
		offsetLir2 = m_setup.module.lir2_offset = value;
		write_device_mem(ADRESS_OFFSET,&offset.dword,sizeof(offset));
		emit sigChangedOffsets(offsetLir1,offsetLir2);
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setLirOffsets(quint32 offset1, quint32 offset2)
{
	if(!initialized)
		return;

	REG_OFFSET offset;

	if(read_device_mem(ADRESS_OFFSET, &offset.dword, sizeof(offset)))
	{
		offset.bits.azimuth1 = offset1;
		offset.bits.azimuth2 = offset2;

		offsetLir1 = m_setup.module.lir1_offset = offset1;
		offsetLir2 = m_setup.module.lir2_offset = offset2;

		write_device_mem(ADRESS_OFFSET, &offset.dword, sizeof(offset));

		emit sigChangedOffsets(offsetLir1, offsetLir2);
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setSharu1Code(quint32 code)
{
	REG_SHARU_CONTROL sharu_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_SHARU_CONTROL,&sharu_control.dword,sizeof(sharu_control)))
	{
		sharu_control.bits.code_s = code;
		write_device_mem(ADRESS_SHARU_CONTROL,&sharu_control.dword,sizeof(sharu_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setSharu2Code(quint32 code)
{
	REG_SHARU_CONTROL sharu_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_SHARU_CONTROL,&sharu_control.dword,sizeof(sharu_control)))
	{
		sharu_control.bits.code_d = code;
		write_device_mem(ADRESS_SHARU_CONTROL,&sharu_control.dword,sizeof(sharu_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setSharuCodes(quint32 code1, quint32 code2)
{
	REG_SHARU_CONTROL sharu_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_SHARU_CONTROL,&sharu_control.dword,sizeof(sharu_control)))
	{
		sharu_control.bits.code_s = code1;
		sharu_control.bits.code_d = code2;
		write_device_mem(ADRESS_SHARU_CONTROL,&sharu_control.dword,sizeof(sharu_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setSharuSource(quint32 source)
{
	REG_SHARU_CONTROL sharu_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_SHARU_CONTROL,&sharu_control.dword,sizeof(sharu_control)))
	{
		sharu_control.bits.source = source;
		write_device_mem(ADRESS_SHARU_CONTROL,&sharu_control.dword,sizeof(sharu_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setSyncrOutput(quint32 value)
{
	REG_SYNCR syncr;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_SYNCR,&syncr.dword,sizeof(syncr)))
	{
		syncr.bits.output = value;
		write_device_mem(ADRESS_SYNCR,&syncr.dword,sizeof(syncr));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setImpulsePrd(quint32 value)
{
	REG_COMMON_RF_FORMER rf_former;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_COMMON_RF_FORMER, &rf_former.dword, sizeof(rf_former)))
	{
		rf_former.bits.impulse = value;
		write_device_mem(ADRESS_COMMON_RF_FORMER,&rf_former.dword,sizeof(rf_former));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setPrmGSH(bool on)
{
	isPrmGsh = on;

	if(isPrmActive)
	{
		if(on)
		{
			setRegGshAlwaysOn(CommandOn);
			setRegGshOn(CommandOn);
		}
		else
		{
			setRegGshOn(CommandOff);
			setRegGshAlwaysOn(CommandOff);
		}
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setPrmZU(bool on)
{
	isPrmZu = on;

	if(isPrmActive)
	{
		if(on)
		{
			setRegZuAlwaysOn(CommandOn);
			setRegZuOn(CommandOn);
		}
		else
		{
			setRegZuOn(CommandOff);
			setRegZuAlwaysOn(CommandOff);
		}
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setPrmPILOT(bool on)
{
	isPrmPilot = on;

	if(isPrmActive)
	{
		if(on)
		{
			setRegPilotAlwaysOn(CommandOn);
			setRegPilotOn(CommandOn);
		}
		else
		{
			setRegPilotOn(CommandOff);
			setRegPilotAlwaysOn(CommandOff);
		}
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setPrmSKR(bool on)
{
	isPrmSkr = on;

	if(isPrmActive)
	{
		if(on)
		{
			setRegSkrAlwaysOn(CommandOn);
			setRegSkrOn(CommandOn);
		}
		else
		{
			setRegSkrOn(CommandOff);
			setRegSkrAlwaysOn(CommandOff);
		}
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setPrmSharu1Code(quint32 code)
{
	codePrmSharu1 = code;

	if(isPrmActive)
		setSharu1Code(code);
}

// ------------------------------------------------------------------
void DASD_SERVICE::setPrmSharu2Code(quint32 code)
{
	codePrmSharu2 = code;

	if(isPrmActive)
		setSharu2Code(code);
}

// ------------------------------------------------------------------
void DASD_SERVICE::setPrmOn(bool on)
{
	if(on)
	{
		isPrmActive = true;

		setPrmGSH(isPrmGsh);
		setPrmZU(isPrmZu);
		setPrmPILOT(isPrmPilot);
		setPrmSKR(isPrmSkr);

		setSharu1Code(codePrmSharu1);
		setSharu2Code(codePrmSharu2);
		setSharuSource(1);
	}
	else
	{
		setRegSkrOn(CommandOff);
		setRegSkrAlwaysOn(CommandOff);

		setRegPilotOn(CommandOff);
		setRegPilotAlwaysOn(CommandOff);

		setRegZuOn(CommandOff);
		setRegZuAlwaysOn(CommandOff);

		setRegGshOn(CommandOff);
		setRegGshAlwaysOn(CommandOff);

		setSharuSource(0);
		setSharu1Code(0);
		setSharu2Code(0);

		isPrmActive = false;
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::refreshSetPrm()
{
	QVariantMap setPrmInfo;

	setPrmInfo["active"] = isPrmActive;
	setPrmInfo["skr"] = isPrmSkr;
	setPrmInfo["pilot"] = isPrmPilot;
	setPrmInfo["gsh"] = isPrmGsh;
	setPrmInfo["zu"] = isPrmZu;
	setPrmInfo["sharu1"] = codePrmSharu1;
	setPrmInfo["sharu2"] = codePrmSharu2;

	emit sigRefreshSetPrmInfo(setPrmInfo);
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegSkrAllOn(CommandType cmd)
{
	REG_SKR skr;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_SKR,&skr.dword,sizeof(skr)))
	{
		switch(cmd)
		{
			case CommandOff:
				skr.bits.set_on = 0;
				skr.bits.always_on = 0;
				break;
			case CommandOn:
				skr.bits.set_on = 1;
				skr.bits.always_on = 1;
				break;
			case CommandToggle:
				skr.bits.set_on = !skr.bits.set_on;
				break;
		}
		write_device_mem(ADRESS_SKR,&skr.dword,sizeof(skr));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegSkrOn(CommandType cmd)
{
	REG_SKR skr;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_SKR,&skr.dword,sizeof(skr)))
	{
		switch(cmd)
		{
			case CommandOff:
				skr.bits.set_on = 0;
				break;
			case CommandOn:
				skr.bits.set_on = 1;
				break;
			case CommandToggle:
				skr.bits.set_on = !skr.bits.set_on;
				break;
		}
		write_device_mem(ADRESS_SKR,&skr.dword,sizeof(skr));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegSkrAlwaysOn(CommandType cmd)
{
	REG_SKR skr;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_SKR,&skr.dword,sizeof(skr)))
	{
		switch(cmd)
		{
			case CommandOff:
				skr.bits.always_on = 0;
				break;
			case CommandOn:
				skr.bits.always_on = 1;
				break;
			case CommandToggle:
				skr.bits.always_on = !skr.bits.always_on;
				break;
		}
		write_device_mem(ADRESS_SKR,&skr.dword,sizeof(skr));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegPilotOn(CommandType cmd)
{
	REG_PILOT pilot;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_PILOT,&pilot.dword,sizeof(pilot)))
	{
		switch(cmd)
		{
			case CommandOff:
				pilot.bits.set_on = 0;
				break;
			case CommandOn:
				pilot.bits.set_on = 1;
				break;
			case CommandToggle:
				pilot.bits.set_on = !pilot.bits.set_on;
				break;
		}
		write_device_mem(ADRESS_PILOT,&pilot.dword,sizeof(pilot));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegPilotAlwaysOn(CommandType cmd)
{
	REG_PILOT pilot;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_PILOT,&pilot.dword,sizeof(pilot)))
	{
		switch(cmd)
		{
			case CommandOff:
				pilot.bits.always_on = 0;
				break;
			case CommandOn:
				pilot.bits.always_on = 1;
				break;
			case CommandToggle:
				pilot.bits.always_on = !pilot.bits.always_on;
				break;
		}
		write_device_mem(ADRESS_PILOT,&pilot.dword,sizeof(pilot));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegGshOn(CommandType cmd)
{
	REG_GSH gsh;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_GSH,&gsh.dword,sizeof(gsh)))
	{
		switch(cmd)
		{
			case CommandOff:
				gsh.bits.set_on = 0;
				break;
			case CommandOn:
				gsh.bits.set_on = 1;
				break;
			case CommandToggle:
				gsh.bits.set_on = !gsh.bits.set_on;
				break;
		}
		write_device_mem(ADRESS_GSH,&gsh.dword,sizeof(gsh));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegGshAlwaysOn(CommandType cmd)
{
	REG_GSH gsh;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_GSH,&gsh.dword,sizeof(gsh)))
	{
		switch(cmd)
		{
			case CommandOff:
				gsh.bits.always_on = 0;
				break;
			case CommandOn:
				gsh.bits.always_on = 1;
				break;
			case CommandToggle:
				gsh.bits.always_on = !gsh.bits.always_on;
				break;
		}
		write_device_mem(ADRESS_GSH,&gsh.dword,sizeof(gsh));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegZuOn(CommandType cmd)
{
	REG_ZU zu;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_ZU,&zu.dword,sizeof(zu)))
	{
		switch(cmd)
		{
			case CommandOff:
				zu.bits.set_on = 0;
				break;
			case CommandOn:
				zu.bits.set_on = 1;
				break;
			case CommandToggle:
				zu.bits.set_on = !zu.bits.set_on;
				break;
		}
		write_device_mem(ADRESS_ZU,&zu.dword,sizeof(zu));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::setRegZuAlwaysOn(CommandType cmd)
{
	REG_ZU zu;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_ZU,&zu.dword,sizeof(zu)))
	{
		switch(cmd)
		{
			case CommandOff:
				zu.bits.always_on = 0;
				break;
			case CommandOn:
				zu.bits.always_on = 1;
				break;
			case CommandToggle:
				zu.bits.always_on = !zu.bits.always_on;
				break;
		}
		write_device_mem(ADRESS_ZU,&zu.dword,sizeof(zu));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleMain()
{
	setRegMain(CommandToggle);
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleRipch()
{
//	setRegRipch(CommandToggle);
	allowPchCtrl = !allowPchCtrl;
	verifyRipch();
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleAzimuthSource()
{
	REG_AZIMUTH_CONTROL az_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control)))
	{
		az_control.bits.source = az_control.bits.source + 1;
		write_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleAzimuthMode()
{
	REG_CONTROL control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_CONTROL,&control.dword,sizeof(control)))
	{
		control.bits.regime = control.bits.regime + 1;
		write_device_mem(ADRESS_CONTROL,&control.dword,sizeof(control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleAzimuthPeriod()
{
	REG_AZIMUTH_CONTROL az_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control)))
	{
		az_control.bits.im_period = az_control.bits.im_period + 1;
		write_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleAzimuthLir1Load()
{
	REG_AZIMUTH_CONTROL az_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control)))
	{
		az_control.bits.load_lir_1 = !az_control.bits.load_lir_1;
		write_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleAzimuthLir2Load()
{
	REG_AZIMUTH_CONTROL az_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control)))
	{
		az_control.bits.load_lir_2 = !az_control.bits.load_lir_2;
		write_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleAzimuthSerialLoad()
{
	REG_AZIMUTH_CONTROL az_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control)))
	{
		az_control.bits.load_serial = !az_control.bits.load_serial;
		write_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleBlockZu()
{
	REG_COMMON_RF_FORMER rf_former;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_COMMON_RF_FORMER, &rf_former.dword, sizeof(rf_former)))
	{
		rf_former.bits.block_zu = !rf_former.bits.block_zu;
		write_device_mem(ADRESS_COMMON_RF_FORMER,&rf_former.dword,sizeof(rf_former));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleBlockSwitch()
{
	REG_COMMON_RF_FORMER rf_former;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_COMMON_RF_FORMER, &rf_former.dword, sizeof(rf_former)))
	{
		rf_former.bits.block_switch = !rf_former.bits.block_switch;
		write_device_mem(ADRESS_COMMON_RF_FORMER,&rf_former.dword,sizeof(rf_former));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleBlockYY()
{
	REG_COMMON_RF_FORMER rf_former;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_COMMON_RF_FORMER, &rf_former.dword, sizeof(rf_former)))
	{
		rf_former.bits.block_yy11 = !rf_former.bits.block_yy11;
		write_device_mem(ADRESS_COMMON_RF_FORMER,&rf_former.dword,sizeof(rf_former));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleVaruBan()
{
	REG_COMMON_RF_FORMER rf_former;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_COMMON_RF_FORMER, &rf_former.dword, sizeof(rf_former)))
	{
		rf_former.bits.no_write_varu = !rf_former.bits.no_write_varu;
		write_device_mem(ADRESS_COMMON_RF_FORMER,&rf_former.dword,sizeof(rf_former));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleTestSin()
{
	REG_COMMON_RF_FORMER rf_former;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_COMMON_RF_FORMER, &rf_former.dword, sizeof(rf_former)))
	{
		rf_former.bits.test_sin = !rf_former.bits.test_sin;
		write_device_mem(ADRESS_COMMON_RF_FORMER,&rf_former.dword,sizeof(rf_former));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleStrobeEnable()
{
	REG_COMMON_RF_FORMER rf_former;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_COMMON_RF_FORMER, &rf_former.dword, sizeof(rf_former)))
	{
		rf_former.bits.strobe_enable = !rf_former.bits.strobe_enable;
		write_device_mem(ADRESS_COMMON_RF_FORMER,&rf_former.dword,sizeof(rf_former));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleBlockAvto()
{
	REG_CONTROL control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_CONTROL,&control.dword,sizeof(control)))
	{
		control.bits.block_avto = !control.bits.block_avto;
		write_device_mem(ADRESS_CONTROL,&control.dword,sizeof(control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleImpulsePrd()
{
	REG_COMMON_RF_FORMER rf_former;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_COMMON_RF_FORMER, &rf_former.dword, sizeof(rf_former)))
	{
		rf_former.bits.impulse = rf_former.bits.impulse + 1;
		write_device_mem(ADRESS_COMMON_RF_FORMER,&rf_former.dword,sizeof(rf_former));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleTimerSource()
{
	REG_TIMER_CONTROL timer_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_TIMER_CONTROL,&timer_control.dword,sizeof(timer_control)))
	{
		timer_control.bits.source = timer_control.bits.source + 1;
		write_device_mem(ADRESS_TIMER_CONTROL,&timer_control.dword,sizeof(timer_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleSharuSource()
{
	REG_SHARU_CONTROL sharu_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_SHARU_CONTROL,&sharu_control.dword,sizeof(sharu_control)))
	{
		sharu_control.bits.source = sharu_control.bits.source + 1;
		write_device_mem(ADRESS_SHARU_CONTROL,&sharu_control.dword,sizeof(sharu_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleErrorZu1()
{
	REG_ERR_ZU error_zu;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_ERR_ZU,&error_zu.dword,sizeof(error_zu)))
	{
		error_zu.bits_w.reset_s = 1;
		write_device_mem(ADRESS_ERR_ZU,&error_zu.dword,sizeof(error_zu));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleErrorZu2()
{
	REG_ERR_ZU error_zu;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_ERR_ZU,&error_zu.dword,sizeof(error_zu)))
	{
		error_zu.bits_w.reset_d = 1;
		write_device_mem(ADRESS_ERR_ZU,&error_zu.dword,sizeof(error_zu));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleTimerLoad()
{
	REG_TIMER_STATE timer_state;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_TIMER_STATE,&timer_state.dword,sizeof(timer_state)))
	{
		timer_state.bits.load_on = timer_state.bits.load_on + 1;
		write_device_mem(ADRESS_TIMER_STATE,&timer_state.dword,sizeof(timer_state));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleImitatorPeriod()
{
	REG_AZIMUTH_CONTROL az_control;

	if(!initialized)
		return;

	if(read_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control)))
	{
		az_control.bits.im_period = az_control.bits.im_period + 1;
		write_device_mem(ADRESS_AZIMUTH_CONTROL,&az_control.dword,sizeof(az_control));
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleZuAlwaysOn()
{
	setRegZuAlwaysOn(CommandToggle);
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleZuOn()
{
	setRegZuOn(CommandToggle);
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleGshAlwaysOn()
{
	setRegGshAlwaysOn(CommandToggle);
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleGshOn()
{
	setRegGshOn(CommandToggle);
}

// ------------------------------------------------------------------
void DASD_SERVICE::togglePilotAlwaysOn()
{
	setRegPilotAlwaysOn(CommandToggle);
}

// ------------------------------------------------------------------
void DASD_SERVICE::togglePilotOn()
{
	setRegPilotOn(CommandToggle);
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleSkrAlwaysOn()
{
	setRegSkrAlwaysOn(CommandToggle);
}

// ------------------------------------------------------------------
void DASD_SERVICE::toggleSkrOn()
{
	setRegSkrOn(CommandToggle);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isInitialized()
{
	return initialized;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isErrorDevice()
{
	return fixedError;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isLoadedTables()
{
	return loadTablesComplete;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isDeviceOk()
{
	return (devRegs.pack1.version.dword != 0xFFFFFFFF);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isFrefOk()
{
	return (isAvarFrefFixed == false);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isModeMaster()
{
	return (devRegs.pack1.state.bits.main == 1);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isAntennaGpsOk()
{
	return (devRegs.pack1.timer_state.bits.antenna_ok == 1);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isAz1SensorOk()
{
	return (devRegs.pack1.lir1_sensor.bits.parity_error == 0 && devRegs.pack1.lir1_sensor.bits.line_detect_error == 0);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isAz2SensorOk()
{
	return (devRegs.pack1.lir2_sensor.bits.parity_error == 0 && devRegs.pack1.lir2_sensor.bits.line_detect_error == 0);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isSerialSensorOk()
{
	return (devRegs.pack1.serial_sensor.bits.parity_error == 0 && devRegs.pack1.serial_sensor.bits.line_detect_error == 0);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::is123GF01Ok()
{
	return (devRegs.pack1.rf_former.bits.avar_block_gf == 0);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isSvchSwitchSOk()
{
	return (devRegs.pack1.state.bits.avar_switch_s == 0);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isSvchSwitchDOk()
{
	return (devRegs.pack1.state.bits.avar_switch_d == 0);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isZuSOk()
{
	return (devRegs.pack1.err_zu.bits.avar_s == 0);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isZuDOk()
{
	return (devRegs.pack1.err_zu.bits.avar_d == 0);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isZuSCtrlOk()
{
	return (devRegs.pack1.err_zu.bits.link_s == 0);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::isZuDCtrlOk()
{
	return (devRegs.pack1.err_zu.bits.link_d == 0);
}

// ------------------------------------------------------------------
bool DASD_SERVICE::periodOk()
{
	return ((devRegs.pack1.state.bits.azim_source == 0 && isAz1SensorOk()) || 
		(devRegs.pack1.state.bits.azim_source == 1 && isAz2SensorOk()));
}

// ------------------------------------------------------------------
double DASD_SERVICE::periodValue()
{
	return ((double)devRegs.pack1.mai_period.bits.time_nord / 1000.0);
}

// ------------------------------------------------------------------
void DASD_SERVICE::setDump(quint32 info)
{
	switch(info)
	{
		case 0:
			//dump registers
			emit sigDumpRegisters(devRegs);
			break;
		case 1:
			//refresh registers
			emit sigRefreshRegisters(devRegs);
			break;
		case 1000:
			//dump table ripch
			break;
		case 1001:
			//dump table mode
			break;
		case 1002:
			//dump table disable
			break;
		case 1003:
			//dump table switch
			break;
		case 1004:
			//dump table nchm
			break;
	}
}

// ------------------------------------------------------------------
void DASD_SERVICE::startMonitor()
{
	isMonitoring = true;
	monitoringCounter = 0;

	emit sigStatusMessage(errorString());
}

// ------------------------------------------------------------------
void DASD_SERVICE::stopMonitor()
{
	isMonitoring = false;
	monitoringCounter = 0;
}

// ------------------------------------------------------------------
void DASD_SERVICE::setMonitorRate(quint32 rate)
{
	monitoringRate = rate;
}

// ------------------------------------------------------------------
void DASD_SERVICE::refreshTables(quint32 what, bool files)
{
	bool result;

	if(what == 0 || what == 1)
	{
		if(files)
			if(devTables.loadRipch(tableRipchName) != AskuTableFile::NoError)
				result = true;

		if(!devTables.prepareTables())
			result = true;

		if(devTables.isLoadedRipch())
			emit sigTableRipch(devTables.tableRipch(), RIPCH_TABLE_SAMPLE_COUNT);
		else
			emit sigTableRipch(QVariantMap(), 0);
	}
	if(what == 0 || what == 2)
	{
		if(files)
			if(devTables.loadMode(tableModeName) != AskuTableFile::NoError)
				result = true;

		if(!devTables.prepareTables())
			result = true;

		if(devTables.isLoadedMode())
			emit sigTableMode(devTables.tableMode(), MODE_TABLE_IMPULSE_COUNT);
		else
			emit sigTableMode(QVariantMap(), 0);
	}
	if(what == 0 || what == 3)
	{
		if(files)
			if(devTables.loadSwitch(tableSwitchName) != AskuTableFile::NoError)
				result = true;

		if(!devTables.prepareTables())
			result = true;

		if(devTables.isLoadedSwitch())
			emit sigTableSwitch(devTables.tableSwitch(), SWITCH_TABLE_SEGMENT_COUNT / 8);
		else
			emit sigTableSwitch(QVariantMap(), 0);
	}
	if(what == 0 || what == 4)
	{
		if(files)
			if(devTables.loadDisable(tableDisableName) != AskuTableFile::NoError)
				result = true;

		if(!devTables.prepareTables())
			result = true;

		if(devTables.isLoadedDisable())
			emit sigTableDisable(devTables.tableDisable(), DISABLE_TABLE_SEGMENT_COUNT / 8);
		else
			emit sigTableDisable(QVariantMap(), 0);
	}

	Q_UNUSED(result);
}

// ------------------------------------------------------------------
void DASD_SERVICE::saveTableRipch(QVariantMap mapdata, bool save)
{
	bool result = false;

	devTables.setRipch(mapdata);

	if(save)
		devTables.saveRipch(tableRipchName);

	if(devTables.prepareRipch())
		if(writeRipchTable())
			result = true;

	if(!result)
		LogModuleError("writeRipchTable error!");
}

// ------------------------------------------------------------------
void DASD_SERVICE::saveTableMode(QVariantMap mapdata, bool save)
{
	bool result = false;

	devTables.setMode(mapdata);

	if(save)
		devTables.saveMode(tableModeName);

	if(devTables.prepareMode())
		if(writeModeTable())
			result = true;

	if(!result)
		LogModuleError("writeModeTable error!");
}

// ------------------------------------------------------------------
void DASD_SERVICE::saveTableSwitch(QVariantMap mapdata, bool save)
{
	bool result = false;

	devTables.setSwitch(mapdata);

	if(save)
		devTables.saveSwitch(tableSwitchName);

	if(devTables.prepareSwitch() && devTables.combineDisableSwitchDynamic())
		if(writeSwitchTable())
			result = true;

	if(!result)
		LogModuleError("writeSwitchTable error!");
}

// ------------------------------------------------------------------
void DASD_SERVICE::saveTableDisable(QVariantMap mapdata, bool save)
{
	bool result = false;
	devTables.setDisable(mapdata);

	if(save)
		devTables.saveDisable(tableDisableName);

	if(devTables.prepareDisable() && devTables.combineDisableSwitchDynamic())
		if(writeSwitchTable())
			result = true;

	if(!result)
		LogModuleError("writeSwitchTable error!");
}

// ------------------------------------------------------------------
bool DASD_SERVICE::loadTables()
{
	bool result = false;

	if(devTables.loadRipch(tableRipchName) != AskuTableFile::NoError) result = true;
	if(devTables.loadMode(tableModeName) != AskuTableFile::NoError) result = true;
	if(devTables.loadSwitch(tableSwitchName) != AskuTableFile::NoError) result = true;
	if(devTables.loadDisable(tableDisableName) != AskuTableFile::NoError) result = true;
	if(devTables.loadNchm(tableNchmName) != AskuTableFile::NoError) result = true;

	if(!devTables.prepareTables()) result = true;

	return result;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::writeTables()
{
	bool result = false;
	if(!writeRipchTable()) result = true;
	if(!writeModeTable()) result = true;
	if(!writeSwitchTable()) result = true;
//	if(!writeNchmTable()) result = true;
	if(result)
	{
		LogModuleError("DASD: error write tables");
	}
	else
	{
		LogModuleInfo("DASD: write tables OK");
	}
	return result;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::writeRipchTable()
{
	if(!initialized || !devTables.isLoadedRipch())
		return false;

	if(!write_device_mem(ADRESS_RIPCH_TABLE, devTables.data_ripch(), sizeof(RIPCH_TABLE)))
		return false;

	parent->csleep(10);

	RIPCH_TABLE ripchTableControl;
	if(!read_device_mem(ADRESS_RIPCH_TABLE, &ripchTableControl, sizeof(RIPCH_TABLE)))
		return false;

	unsigned int *t1 = (unsigned int*)devTables.data_ripch();
	unsigned int *t2 = (unsigned int*)&ripchTableControl;

//	qDebug("ripch_table size = %X", (unsigned int)sizeof(RIPCH_TABLE));
	LogModuleBinary("ripch_table size = %X", sizeof(RIPCH_TABLE));
	for(unsigned int a = 0; a < sizeof(RIPCH_TABLE) / sizeof(unsigned int); a++)
	{
//	    if(*(t1 + a) != *(t2 + a))
//	    qDebug("%08X:  %08X -- %08X", (unsigned int)(ADRESS_RIPCH_TABLE + a * sizeof(unsigned int)), *(t1 + a), *(t2 + a));
	    LogModuleBinary("%08X:  %08X -- %08X %c", (unsigned int)(ADRESS_RIPCH_TABLE + a * sizeof(unsigned int)), *(t1 + a), *(t2 + a), *(t1 + a) != *(t2 + a) ? '!':' ');
	}

	if(memcmp(devTables.data_ripch(), &ripchTableControl, sizeof(RIPCH_TABLE)))
	{
//		qDebug("fail: ripch_table_not_equal!");
		LogModuleError("fail: ripch_table_not_equal");
		return false;
	}

	return true;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::writeSwitchTable()
{
	if(!initialized || !devTables.isLoadedSwitch() || !devTables.isLoadedDisable())
		return false;

	if(!write_device_mem(ADRESS_SWITCH_TABLE, devTables.data_switch(), sizeof(SWITCH_TABLE)))
		return false;

	parent->csleep(10);

	SWITCH_TABLE switchTableControl;
	if(!read_device_mem(ADRESS_SWITCH_TABLE, &switchTableControl, sizeof(SWITCH_TABLE)))
		return false;

	unsigned int *t1 = (unsigned int*)devTables.data_switch();
	unsigned int *t2 = (unsigned int*)&switchTableControl;

//	qDebug("switch_table size = %X", sizeof(SWITCH_TABLE));
	LogModuleBinary("switch_table size = %X", (unsigned int)sizeof(SWITCH_TABLE));
	for(unsigned int a = 0; a < sizeof(SWITCH_TABLE) / sizeof(unsigned int); a++)
	{
//	    if(*(t1 + a) != *(t2 + a))
//	    qDebug("%08X:  %08X -- %08X", (unsigned int)(ADRESS_SWITCH_TABLE + a * sizeof(unsigned int)), *(t1 + a), *(t2 + a));
	    LogModuleBinary("%08X:  %08X -- %08X %c", (unsigned int)(ADRESS_SWITCH_TABLE + a * sizeof(unsigned int)), *(t1 + a), *(t2 + a), *(t1 + a) != *(t2 + a) ? '!':' ');
	}

	if(memcmp(devTables.data_switch(), &switchTableControl, sizeof(SWITCH_TABLE)))
	{
//		qDebug("fail: switch_table_not_equal!");
		LogModuleError("fail: switch_table_not_equal");
		return false;
	}

	return true;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::writeModeTable()
{
	if(!initialized || !devTables.isLoadedMode())
		return false;

	if(!write_device_mem(ADRESS_MODE_TABLE, devTables.data_mode(), sizeof(MODE_TABLE)))
		return false;

	parent->csleep(10);

	MODE_TABLE modeTableControl;
	if(!read_device_mem(ADRESS_MODE_TABLE, &modeTableControl, sizeof(MODE_TABLE)))
		return false;

	unsigned int *t1 = (unsigned int*)devTables.data_mode();
	unsigned int *t2 = (unsigned int*)&modeTableControl;

//	qDebug("mode_table size = %X", sizeof(MODE_TABLE));
	LogModuleBinary("mode_table size = %X", (unsigned int)sizeof(MODE_TABLE));
	for(unsigned int a = 0; a < sizeof(MODE_TABLE) / sizeof(unsigned int); a++)
	{
//	    if(*(t1 + a) != *(t2 + a))
//	    qDebug("%08X:  %08X -- %08X", (unsigned int)(ADRESS_MODE_TABLE + a * sizeof(unsigned int)), *(t1 + a), *(t2 + a));
	    LogModuleBinary("%08X:  %08X -- %08X %c", (unsigned int)(ADRESS_MODE_TABLE + a * sizeof(unsigned int)), *(t1 + a), *(t2 + a), *(t1 + a) != *(t2 + a) ? '!':' ');
	}

	if(memcmp(devTables.data_mode(), &modeTableControl, sizeof(MODE_TABLE)))
	{
//		qDebug("fail: mode_table_not_equal!");
		LogModuleError("fail: mode_table_not_equal");
		return false;
	}

	return true;
}

// ------------------------------------------------------------------
bool DASD_SERVICE::writeNchmTable()
{
	if(!initialized || !devTables.isLoadedNchm())
		return false;

	if(!write_device_mem(ADRESS_NCHM_TABLE, devTables.data_nchm(), sizeof(NCHM_TABLE)))
		return false;

	parent->csleep(10);

	NCHM_TABLE nchmTableControl;
	if(!read_device_mem(ADRESS_NCHM_TABLE, &nchmTableControl, sizeof(NCHM_TABLE)))
		return false;

	unsigned int *t1 = (unsigned int*)devTables.data_nchm();
	unsigned int *t2 = (unsigned int*)&nchmTableControl;

//	qDebug("nchm_table size = %X", (unsigned int)sizeof(NCHM_TABLE));
	LogModuleBinary("nchm_table size = %X", (unsigned int)sizeof(NCHM_TABLE));
	for(unsigned int a = 0; a < sizeof(NCHM_TABLE) / sizeof(unsigned int); a++)
	{
//	    if(*(t1 + a) != *(t2 + a))
//	    qDebug("%08X:  %08X -- %08X", (unsigned int)(ADRESS_NCHM_TABLE + a * sizeof(unsigned int)), *(t1 + a), *(t2 + a));
	    LogModuleBinary("%08X:  %08X -- %08X %c", (unsigned int)(ADRESS_NCHM_TABLE + a * sizeof(unsigned int)), *(t1 + a), *(t2 + a), *(t1 + a) != *(t2 + a) ? '!':' ');
	}

	if(memcmp(devTables.data_nchm(), &nchmTableControl, sizeof(NCHM_TABLE)))
	{
//		qDebug("fail: nchm_table_not_equal!");
		LogModuleError("fail: nchm_table_not_equal");
		return false;
	}

	return true;
}

// ------------------------------------------------------------------
/*void DASD_SERVICE::checkCState()
{
	emit checkState(&devState);
}
*/
// ------------------------------------------------------------------
/*void DASD_SERVICE::checkTemperature()
{
	if(!waitTemperature)
		emit sigTemperature((qreal)(signed char)devPower.t_board);
	waitTemperature++;
	if(waitTemperature > 10)
		waitTemperature = 0;
}
*/
// ------------------------------------------------------------------
void DASD_SERVICE::onChangedState()
{
	if(!isInitialized())
		bDasdLocalState["DASD"] = ELEM_NOT;
	else if(isErrorDevice() || !isDeviceOk() || !isFrefOk())
		bDasdLocalState["DASD"] = ELEM_AVAR;
	else if(!isLoadedTables()) 
		bDasdLocalState["DASD"] = ELEM_ERROR;
	else
		bDasdLocalState["DASD"] = ELEM_NORMA;

	bool isDeviceOk = (bDasdLocalState["DASD"] == ELEM_NORMA || bDasdLocalState["DASD"] == ELEM_ERROR);

	if(!isDeviceOk)
		bDasdLocalState["dasd_master"] = ELEM_NOT;
	else if(!isModeMaster())
		bDasdLocalState["dasd_master"] = ELEM_NOT;
	else
		bDasdLocalState["dasd_master"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["AzSensor1"] = ELEM_NOT;
	else if(!isAz1SensorOk())
		bDasdLocalState["AzSensor1"] = ELEM_AVAR;
	else
		bDasdLocalState["AzSensor1"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["AzSensor2"] = ELEM_NOT;
	else if(!isAz2SensorOk())
		bDasdLocalState["AzSensor2"] = ELEM_AVAR;
	else
		bDasdLocalState["AzSensor2"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["AzSensorMain"] = 0;
	else if(devRegs.pack1.az_control.bits.source == 0)
		bDasdLocalState["AzSensorMain"] = 1;
	else if(devRegs.pack1.az_control.bits.source == 1)
		bDasdLocalState["AzSensorMain"] = 2;
	else
		bDasdLocalState["AzSensorMain"] = 0;

	if(!isDeviceOk)
		bDasdLocalState["AntennaGps"] = ELEM_NOT;
	else if(!isAntennaGpsOk())
		bDasdLocalState["AntennaGps"] = ELEM_AVAR;
	else
		bDasdLocalState["AntennaGps"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["123GF01"] = ELEM_NOT;
	else if(!is123GF01Ok())
		bDasdLocalState["123GF01"] = ELEM_AVAR;
	else
		bDasdLocalState["123GF01"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["ZG"] = ELEM_NOT;
	else if(!is123GF01Ok())
		bDasdLocalState["ZG"] = ELEM_AVAR;
	else if(allowPchMain)
		bDasdLocalState["ZG"] = ELEM_NORMA;
	else
		bDasdLocalState["ZG"] = ELEM_NOT;

	if(!isDeviceOk)
		bDasdLocalState["SWITCH_D"] = ELEM_NOT;
	else if(!isSvchSwitchSOk())
		bDasdLocalState["SWITCH_D"] = ELEM_AVAR;
	else
		bDasdLocalState["SWITCH_D"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["SWITCH_S"] = ELEM_NOT;
	else if(!isSvchSwitchDOk())
		bDasdLocalState["SWITCH_S"] = ELEM_AVAR;
	else
		bDasdLocalState["SWITCH_S"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["ZU_S"] = ELEM_NOT;
	else if(!isZuSOk())
		bDasdLocalState["ZU_S"] = ELEM_AVAR;
	else
		bDasdLocalState["ZU_S"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["ZU_D"] = ELEM_NOT;
	else if(!isZuDOk())
		bDasdLocalState["ZU_D"] = ELEM_AVAR;
	else
		bDasdLocalState["ZU_D"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["ZU_S_CTRL"] = ELEM_NOT;
	else if(!isZuSCtrlOk())
		bDasdLocalState["ZU_S_CTRL"] = ELEM_AVAR;
	else
		bDasdLocalState["ZU_S_CTRL"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["ZU_D_CTRL"] = ELEM_NOT;
	else if(!isZuDCtrlOk())
		bDasdLocalState["ZU_D_CTRL"] = ELEM_AVAR;
	else
		bDasdLocalState["ZU_D_CTRL"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["ZG"] = ELEM_NOT;
	else if(bDasdLocalState["123GF01"] == ELEM_AVAR)
		bDasdLocalState["ZG"] = ELEM_AVAR;
	else if(bDasdLocalState["DASD"] == ELEM_ERROR)
		bDasdLocalState["ZG"] = ELEM_ERROR;
	else
		bDasdLocalState["ZG"] = ELEM_NORMA;

	if(!isDeviceOk)
		bDasdLocalState["period"] = ELEM_NOT;
	else if(!periodOk())
		bDasdLocalState["period"] = ELEM_AVAR;
	else
		bDasdLocalState["period"] = ELEM_NORMA;

	if(isDeviceOk && (timeDiff(m_timeChangedMain) > 15000))
		bDasdLocalState["periodValid"] = ELEM_NORMA;
	else
		bDasdLocalState["periodValid"] = ELEM_NOT;
	bDasdLocalMeasure["period"] = periodValue();

	emit sigStateLocal(bDasdLocalState, bDasdLocalMeasure);
	syncToSlave();
}

// ------------------------------------------------------------------
void DASD_SERVICE::clearLocalState()
{
	bDasdLocalState.clear(ELEM_NOT);
	bDasdLocalMeasure.clear();
	emit sigStateLocal(bDasdLocalState, bDasdLocalMeasure);
	syncToSlave();
}

// ------------------------------------------------------------------
void DASD_SERVICE::clearOtherState()
{
	bDasdOtherState.clear(ELEM_NOT);
	bDasdOtherMeasure.clear();
	emit sigStateOther(bDasdOtherState, bDasdOtherMeasure);
}

// ------------------------------------------------------------------
void DASD_SERVICE::syncToSlave()
{
	emit sigSyncToSlave(QVariantMap(), bDasdLocalState.toMap(), bDasdLocalMeasure.toMap());
}

// ------------------------------------------------------------------
void DASD_SERVICE::onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure)
{
//	LogModuleInfo("DASD_SERVICE::onSyncToSlave processed");

	Q_UNUSED(config);

	bDasdOtherState.fromMap(state);
	bDasdOtherMeasure.fromMap(measure);

//	qDebug() << "onSyncToSlave";
//	qDebug() << bDasdOtherState.toMap();
//	qDebug() << bDasdOtherMeasure.toMap();
//	qDebug() << "-------------";

	emit sigStateOther(bDasdOtherState, bDasdOtherMeasure);
}

// ------------------------------------------------------------------
