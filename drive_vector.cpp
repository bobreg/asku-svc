#include "../common/logger.h"
#include "globalvar.h"
#include "drive.h"
#include "drive_struct.h"
#include "drive_vector.h"
#include "drive_service.h"

//------------------------------------------------------------------------------
VECTOR_DEVICE::VECTOR_DEVICE(MODBUS_SERVICE * p, quint32 address) : MODBUS_DEVICE(p, address)
{
	m_positioning = false;
	m_reserving = true;

	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_STATE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_WARNING));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_SAFE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_SAFE_MORE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_OVERHEAT));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_HARDWARE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_SOFTWARE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_LINK));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_SPEED_DISCRETE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_SPEED_NOMINAL));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_SPEED_VALUE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_SPEED_REAL_DISCRETE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_SPEED_REAL_NOMINAL));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_SPEED_REAL_VALUE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_POSITION_VALUE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_POSITION_RT_ST));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_MOMENT_VALUE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_MOMENT_DISCRETE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_FULL_MOMENT_VALUE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_FULL_MOMENT_DISCRETE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_CURRENT_VALUE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_CURRENT_NOMINAL));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_VOLTAGE_VALUE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_VOLTAGE_NOMINAL));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_FIRMWARE_CONFIG));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_VERSION));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_VERSION_DATE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_VERSION_TIME));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_SERIAL));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_PRODUCTION_DATE));
	regs03.addRegister(DEFINE_REGISTER(VECTOR_REG_03_WORKHOURS));

	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_CONTROL));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_RESET_AVAR));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_SET_SPEED_NOMINAL));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_SET_SPEED));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_SET_CURRENT));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_SET_POSITION));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_SYNC));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_ADRESS_MODBUS));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_RESERVE_OVERRIDE));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_SET_MODE));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_COR_SENSOR_TO_ROTOR));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_COR_SENSOR_TO_GEO));
	regs10.addRegister(DEFINE_REGISTER(VECTOR_REG_10_ENABLE_PROG));

	LogDriveInfo("VECTOR_DEVICE: register pack 03\n%s", qPrintable(regs03.toString()));
	LogDriveInfo("VECTOR_DEVICE: register pack 10\n%s", qPrintable(regs10.toString()));
}

//------------------------------------------------------------------------------
VECTOR_DEVICE::~VECTOR_DEVICE()
{
	
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::setSpeed(quint16 value)
{
	LogDriveInfo("VECTOR_DEVICE[%d]: speed = %04X", address(), value);
	regs10[VECTOR_REG_10_SET_SPEED] = value;
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::setPosition(quint16 value)
{
	LogDriveInfo("VECTOR_DEVICE[%d] position = %04X", address(), value);
	regs10[VECTOR_REG_10_SET_POSITION] = value;
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::setSpeedPosition(bool pos)
{
	LogDriveInfo("VECTOR_DEVICE[%d] speedposition = %d", address(), pos);
	m_positioning = pos;

	if(regs10[VECTOR_REG_10_CONTROL] & 0x0003) // started
	{
		if(m_positioning)
		{
			regs10[VECTOR_REG_10_CONTROL] = 0x0001 | 0x0008;
		}
		else
		{
			regs10[VECTOR_REG_10_CONTROL] = 0x0001;
		}
	}
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::setReset()
{
	LogDriveInfo("VECTOR_DEVICE[%d] reset", address());
	regs10[VECTOR_REG_10_RESET_AVAR] = 0x0001;
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::setStart(bool reverse)
{
	LogDriveInfo("VECTOR_DEVICE[%d] start rev = %d", address(), reverse);

	if(m_positioning)
	{
		regs10[VECTOR_REG_10_CONTROL] = 0x0001 | 0x0008;
	}
	else
	{
		if(!reverse)
			regs10[VECTOR_REG_10_CONTROL] = 0x0001;
		else
			regs10[VECTOR_REG_10_CONTROL] = 0x0002;
	}
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::setStop()
{
	LogDriveInfo("VECTOR_DEVICE[%d] stop", address());
	regs10[VECTOR_REG_10_CONTROL] = 0x0004;
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::setReserveOverride(quint16 value)
{
	if(m_reserving)
	{
		LogDriveInfo("VECTOR_DEVICE[%d] reserve override = %d", address(), value);
		regs10[VECTOR_REG_10_RESERVE_OVERRIDE] = value;
	}
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::updateCommands()
{
	if(m_positioning)
		regs10[VECTOR_REG_10_SET_POSITION].update();

	regs10[VECTOR_REG_10_SET_SPEED].update();
	regs10[VECTOR_REG_10_CONTROL].update();
}

// ------------------------------------------------------------------
void VECTOR_DEVICE::onConnected()
{
}

// ------------------------------------------------------------------
void VECTOR_DEVICE::onDisconnected()
{
	updateRegs03();
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::processPacket(const ModbusPacket & packet)
{
	ModbusPacket::Type t = (ModbusPacket::Type)packet.type();

	unsigned char d = packet.device();
	unsigned short c = packet.bytes();

	if(d != address())
		return;

	LogDriveBinary("VECTOR_DEVICE[%d]: read: %s", address(), LogArray(packet.toByteArray()));

	switch(t)
	{
		case ModbusPacket::ResponseHolding:

			switch(c / sizeof(quint16))
			{
			case 12:
				regs03.setPacket(packet, VECTOR_REG_03_STATE, 12);
				break;
			case 2:
				regs03.setPacket(packet, VECTOR_REG_03_SPEED_DISCRETE, 2);
				break;
			case 5:
				regs03.setPacket(packet, VECTOR_REG_03_SPEED_REAL_DISCRETE, 5);
				break;
			case 28:
				regs03.setPacket(packet, VECTOR_REG_03_SPEED_VALUE, 28);
				break;
			case 4:
				regs03.setPacket(packet, VECTOR_REG_03_FULL_MOMENT_VALUE-1, 4);
				break;
			case 1:
				regs03.setPacket(packet, VECTOR_REG_03_FIRMWARE_CONFIG, 1);
				break;
			case 7:
				regs03.setPacket(packet, VECTOR_REG_03_VERSION, 7);
				break;
			default:
				LogDriveError("VECTOR_DEVICE[%d] responce ERROR length!!", address());
				break;
			}

			onAnswer03(VECTOR_DEVICE_MAX_COUNTER_03);
			updateRegs03();
			break;

		case ModbusPacket::RecieptMultiRegisters:
			LogDriveInfo("VECTOR_DEVICE[%d] command accepted!!", address());
			onAnswer03(VECTOR_DEVICE_MAX_COUNTER_03);
			updateRegs03();
			break;

		case ModbusPacket::Error:
			LogDriveError("VECTOR_DEVICE[%d] responce ERROR!!", address());
			break;

		default:
			LogDriveError("VECTOR_DEVICE[%d] unrequested packet", address());
			break;
	}
}

//------------------------------------------------------------------------------
bool VECTOR_DEVICE::processCommands()
{
//	LogDriveInfo("VECTOR_DEVICE[%d] process commands", address());

	bool wasCommand = false;
	QMutableMapIterator<quint32, ModbusRegister> i(regs10);
	while(i.hasNext())
	{
		i.next();
		if(i.value().isChanged())
		{
			wasCommand = true;
			control10(i.key(), i.key(), 1);
			i.value().respond();

			switch(i.key())
			{
				case VECTOR_REG_10_RESET_AVAR:
					i.value().setValue(0, false);
					break;

				case VECTOR_REG_10_RESERVE_OVERRIDE:
					i.value().setValue(0, false);
					break;
			}
			break;
		}
	}

	return wasCommand;
}

//------------------------------------------------------------------------------
bool VECTOR_DEVICE::processQuery()
{
	switch(m_queryPacket)
	{
		case 0:
			if(!regs03[VECTOR_REG_03_FIRMWARE_CONFIG].isInitialized())
			{
				request03(VECTOR_REG_03_FIRMWARE_CONFIG, 0, 1);//1 (from 609-1)
				m_queryPacket = 1;
				break;
			}

		case 1:
			if(!regs03[VECTOR_REG_03_VERSION].isInitialized())
			{
				request03(VECTOR_REG_03_VERSION, 0, 7);//7 (from 1-1)
				m_queryPacket = 2;
				break;
			}

		case 2:
			request03(VECTOR_REG_03_STATE, 0, 12);//12 (from 20)
			m_queryPacket = 3;
			break;

		case 3:
			request03(VECTOR_REG_03_SPEED_DISCRETE, 0, 2);//2 (from 40)
			m_queryPacket = 4;
			break;

		case 4:
			request03(VECTOR_REG_03_SPEED_REAL_DISCRETE, 0, 5);//5 (from 45)
			m_queryPacket = 5;
			break;

		case 5:
			request03(VECTOR_REG_03_SPEED_VALUE, 0, 28);//28 (from 50)
			m_queryPacket = 6;
			break;

		case 6:
			request03(VECTOR_REG_03_FULL_MOMENT_VALUE - 1, 0, 4);//4 (from 100-1)
			m_queryPacket = 7;
			break;

		case 7:
			//nop
			m_queryPacket = 0;
			return false;
			break;
	}

	checkResponce();
	if(m_needRefresh03)
		updateRegs03();

	return true;
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::setRegisters03()
{
	QMutableMapIterator<quint32, ModbusHolding> i(regs03);
	while(i.hasNext())
	{
		i.next();

		switch(i.key())
		{
			case VECTOR_REG_03_STATE:
				m_vectorState.State.RegState._Data = i.value();
				break;
			case VECTOR_REG_03_WARNING:
				m_vectorState.State.RegWarning._Data = i.value();
				break;
			case VECTOR_REG_03_SAFE:
				m_vectorState.State.RegProtect._Data = i.value();
				break;
			case VECTOR_REG_03_SAFE_MORE:
				m_vectorState.State.RegProtectAdd._Data = i.value();
				break;
			case VECTOR_REG_03_OVERHEAT:
				m_vectorState.State.RegOverheat._Data = i.value();
				break;
			case VECTOR_REG_03_HARDWARE:
				m_vectorState.State.RegHardware._Data = i.value();
				break;
			case VECTOR_REG_03_SOFTWARE:
				m_vectorState.State.RegSoftware._Data = i.value();
				break;
			case VECTOR_REG_03_LINK:
				m_vectorState.State.RegLink._Data = i.value();
				break;
			case VECTOR_REG_03_SPEED_DISCRETE:
				//nop
				break;
			case VECTOR_REG_03_SPEED_NOMINAL:
				//nop
				break;
			case VECTOR_REG_03_SPEED_VALUE:
				//nop
				break;
			case VECTOR_REG_03_SPEED_REAL_DISCRETE:
				//nop
				break;
			case VECTOR_REG_03_SPEED_REAL_NOMINAL:
				//nop
				break;
			case VECTOR_REG_03_SPEED_REAL_VALUE:
				m_vectorState.State.RegSpeed._Data = i.value();
				break;
			case VECTOR_REG_03_POSITION_VALUE:
				m_vectorState.State.RegPosition._Data = i.value();
				break;
			case VECTOR_REG_03_POSITION_RT_ST:
				m_vectorState.State.RegRotStatPos._Data = i.value();
				break;
			case VECTOR_REG_03_MOMENT_VALUE:
				m_vectorState.State.RegMoment._Data = i.value();
				break;
			case VECTOR_REG_03_MOMENT_DISCRETE:
				//nop
				break;
			case VECTOR_REG_03_FULL_MOMENT_VALUE:
				//nop
				break;
			case VECTOR_REG_03_FULL_MOMENT_DISCRETE:
				//nop
				break;
			case VECTOR_REG_03_CURRENT_VALUE:
				m_vectorState.State.RegCurrent._Data = i.value();
				break;
			case VECTOR_REG_03_CURRENT_NOMINAL:
				//nop
				break;
			case VECTOR_REG_03_VOLTAGE_VALUE:
				m_vectorState.State.RegVoltage._Data = i.value();
				break;
			case VECTOR_REG_03_VOLTAGE_NOMINAL:
				//nop
				break;
			case VECTOR_REG_03_FIRMWARE_CONFIG:
				m_vectorState.State.RegFWConf._Data = i.value();
				break;
			case VECTOR_REG_03_VERSION:
				m_vectorState.State.RegVersion._Data = i.value();
				break;
			case VECTOR_REG_03_VERSION_DATE:
				m_vectorState.State.RegVersionDate._Data = i.value();
				break;
			case VECTOR_REG_03_VERSION_TIME:
				m_vectorState.State.RegVersionTime._Data = i.value();
				break;
			case VECTOR_REG_03_SERIAL:
				m_vectorState.State.RegSerial._Data = i.value();
				break;
			case VECTOR_REG_03_PRODUCTION_DATE:
				m_vectorState.State.RegProductionDate._Data = i.value();
				break;
			case VECTOR_REG_03_WORKHOURS:
				m_vectorState.State.RegWorkHours._Data = i.value();
				break;
		}
	}

	if(m_status == DEVICE_OK && isInfoCollected())
	{
		m_vectorState.State.Updated = QDateTime::currentDateTime();
	}
	else
	{
		m_vectorState.State.Updated = QDateTime();
	}
}

//------------------------------------------------------------------------------
void VECTOR_DEVICE::updateRegs03()
{
	if(!m_connected)
		regs03.reset();

	checkDeviceState();
	setRegisters03();

	m_needRefresh03 = false;

	if(parent)
		parent->onChangedDeviceState();
}

//------------------------------------------------------------------------------
bool VECTOR_DEVICE::isActualState()
{
	qint64 timeUpdated = TimeUndefined;

	if(!m_vectorState.State.Updated.isNull())
		timeUpdated = timeDiff(m_vectorState.State.Updated);

	return ((timeUpdated <= 10000) && (timeUpdated >= -10000) && (timeUpdated != TimeUndefined));
}

//------------------------------------------------------------------------------
bool VECTOR_DEVICE::isInfoCollected()
{
	return (
		regs03[VECTOR_REG_03_STATE].isInitialized() &&
		regs03[VECTOR_REG_03_SPEED_DISCRETE].isInitialized() &&
		regs03[VECTOR_REG_03_SPEED_REAL_DISCRETE].isInitialized() &&
		regs03[VECTOR_REG_03_SPEED_VALUE].isInitialized() &&
		regs03[VECTOR_REG_03_FULL_MOMENT_VALUE].isInitialized() &&
		regs03[VECTOR_REG_03_FIRMWARE_CONFIG].isInitialized() &&
		regs03[VECTOR_REG_03_VERSION].isInitialized()
	);
}

//------------------------------------------------------------------------------
