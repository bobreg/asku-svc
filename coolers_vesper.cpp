#include "../common/logger.h"
#include "globalvar.h"
#include "coolers.h"
#include "coolers_struct.h"
#include "coolers_vesper.h"
#include "coolers_service.h"

//------------------------------------------------------------------------------
VESPER_DEVICE::VESPER_DEVICE(MODBUS_SERVICE * p, quint32 address, quint32 type) : MODBUS_DEVICE(p, address)
{
	setType(type);

	if(m_vesperState.Type == VESPER_TYPE_E3_8100)
	{
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_STATE));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_FAILURE));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_SOFT));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_FREQUENCY));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_OUT_FREQUENCY));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_OUT_CURRENT));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_OUT_VOLTAGE));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_MF_INPUT));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_WARNING));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_MF_OUTPUT));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_DC_VOLTAGE));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_MOMENT));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_TIMEWORK));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_OUT_POWER));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8100_REG_03_CONNECTION));

		regs10.addRegister(DEFINE_REGISTER(VESPER_8100_REG_10_CONTROL));
		regs10.addRegister(DEFINE_REGISTER(VESPER_8100_REG_10_SET_FREQ));
	}
	else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_STATE));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_ERROR_CODE));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_MF_IN_OUT));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_FREQUENCY));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_OUT_FREQUENCY));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_OUT_VOLTAGE));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_DC_VOLTAGE));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_OUT_CURRENT));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_MOMENT));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_PID_FEEDBACK));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_PID_INPUT));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_AIN_VOLTAGE));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_AI2_VOLTAGE));
		regs03.addRegister(DEFINE_REGISTER(VESPER_8300_REG_03_KBD_VOLTAGE));

		regs10.addRegister(DEFINE_REGISTER(VESPER_8300_REG_10_CONTROL));
		regs10.addRegister(DEFINE_REGISTER(VESPER_8300_REG_10_SET_FREQ));
	}
	else
	{
		return;
	}

	LogCoolerInfo("VESPER_DEVICE: register pack 03\n%s", qPrintable(regs03.toString()));
	LogCoolerInfo("VESPER_DEVICE: register pack 10\n%s", qPrintable(regs10.toString()));
}

//------------------------------------------------------------------------------
VESPER_DEVICE::~VESPER_DEVICE()
{
	
}

//------------------------------------------------------------------------------
void VESPER_DEVICE::setType(quint32 type)
{
	LogCoolerInfo("VESPER_DEVICE: set type %d", type);
	m_vesperState.Type = type;
}

//------------------------------------------------------------------------------
void VESPER_DEVICE::setFrequency(quint16 value)
{
	LogCoolerInfo("VESPER_DEVICE[%d]: freq = %04X", address(), value);
	if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
		regs10[VESPER_8300_REG_10_SET_FREQ] = value;
		regs10[VESPER_8300_REG_10_SET_FREQ].update();
	}
	else if(m_vesperState.Type == VESPER_TYPE_E3_8100)
	{
		regs10[VESPER_8100_REG_10_SET_FREQ] = value;
		regs10[VESPER_8100_REG_10_SET_FREQ].update();
	}
}

//------------------------------------------------------------------------------
void VESPER_DEVICE::setControl(quint16 value)
{
	LogCoolerInfo("VESPER_DEVICE[%d]: control = %04X", address(), value);
	if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
		regs10[VESPER_8300_REG_10_CONTROL] = value;
		regs10[VESPER_8300_REG_10_CONTROL].update();
	}
	else if(m_vesperState.Type == VESPER_TYPE_E3_8100)
	{
		regs10[VESPER_8100_REG_10_CONTROL] = value;
		regs10[VESPER_8100_REG_10_CONTROL].update();
	}
}

//------------------------------------------------------------------------------
void VESPER_DEVICE::setReset()
{
	LogCoolerInfo("VESPER_DEVICE[%d] reset", address());

	if(m_vesperState.Type == VESPER_TYPE_E3_8100)
	{
		m_vesperState.Control_8100.RegControl.Bits.resetErr = 1;
		setControl(m_vesperState.Control_8100.RegControl._Data);
		m_vesperState.Control_8100.RegControl.Bits.resetErr = 0;
	}
	else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
		m_vesperState.Control_8300.RegControl.Bits.resetErr = 1;
		setControl(m_vesperState.Control_8300.RegControl._Data);
		m_vesperState.Control_8300.RegControl.Bits.resetErr = 0;
	}
}

//------------------------------------------------------------------------------
void VESPER_DEVICE::updateControls()
{
	if(m_vesperState.Type == VESPER_TYPE_E3_8100)
	{
		if(m_vesperState.Control_8100.RegFrequency.freq() > 0.0)
		{
			m_vesperState.Control_8100.RegControl.Bits.start = 1;
			m_vesperState.Control_8100.RegControl.Bits.reverse = 0;
		}
		else
		{
			m_vesperState.Control_8100.RegControl.Bits.start = 0;
			m_vesperState.Control_8100.RegControl.Bits.reverse = 0;
		}

		setFrequency(m_vesperState.Control_8100.RegFrequency._Data);
		setControl(m_vesperState.Control_8100.RegControl._Data);
	}
	else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
		if(m_vesperState.Control_8300.RegFrequency.freq() > 0.0)
		{
			m_vesperState.Control_8300.RegControl.Bits.start = 1;
			m_vesperState.Control_8300.RegControl.Bits.reverse = 0;
		}
		else
		{
			m_vesperState.Control_8300.RegControl.Bits.start = 0;
			m_vesperState.Control_8300.RegControl.Bits.reverse = 0;
		}

		setFrequency(m_vesperState.Control_8300.RegFrequency._Data);
		setControl(m_vesperState.Control_8300.RegControl._Data);
	}
}

//------------------------------------------------------------------------------
void VESPER_DEVICE::setStart(bool reverse)
{
	LogCoolerInfo("VESPER_DEVICE[%d] start rev = %d", address(), reverse);

	if(m_vesperState.Type == VESPER_TYPE_E3_8100)
	{
		m_vesperState.Control_8100.RegControl.Bits.start = 1;
		m_vesperState.Control_8100.RegControl.Bits.reverse = reverse;
		setControl(m_vesperState.Control_8100.RegControl._Data);
	}
	else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
		m_vesperState.Control_8300.RegControl.Bits.start = 1;
		m_vesperState.Control_8300.RegControl.Bits.reverse = reverse;
		setControl(m_vesperState.Control_8300.RegControl._Data);
	}
}

//------------------------------------------------------------------------------
void VESPER_DEVICE::setStop()
{
	LogCoolerInfo("VESPER_DEVICE[%d] stop", address());

	if(m_vesperState.Type == VESPER_TYPE_E3_8100)
	{
		m_vesperState.Control_8100.RegControl.Bits.start = 0;
		m_vesperState.Control_8100.RegControl.Bits.reverse = 0;
		setControl(m_vesperState.Control_8100.RegControl._Data);
	}
	else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
		m_vesperState.Control_8300.RegControl.Bits.start = 0;
		m_vesperState.Control_8300.RegControl.Bits.reverse = 0;
		setControl(m_vesperState.Control_8300.RegControl._Data);
	}
}

//------------------------------------------------------------------------------
void VESPER_DEVICE::updateCommands()
{
	if(m_vesperState.Type == VESPER_TYPE_E3_8100)
	{
		regs10[VESPER_8100_REG_10_SET_FREQ].update();
		regs10[VESPER_8100_REG_10_CONTROL].update();
	}
	else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
//		regs10[VESPER_8300_REG_10_SET_FREQ].update();
		regs10[VESPER_8300_REG_10_CONTROL].update();
		updateFrequency();
	}
}

// ------------------------------------------------------------------
void VESPER_DEVICE::updateFrequency()
{
	if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
		if(m_vesperState.Control_8300.RegControl.Bits.start && isInfoCollected() && isActualState())
		{
			if((quint16)regs10[VESPER_8300_REG_10_SET_FREQ] != (quint16)regs03[VESPER_8300_REG_03_FREQUENCY])
			{
				LogCoolerInfo("VESPER_DEVICE::updateFrequency freq set=%04X freq device=%04X", (quint16)regs10[VESPER_8300_REG_10_SET_FREQ], (quint16)regs03[VESPER_8300_REG_03_FREQUENCY]);
				regs10[VESPER_8300_REG_10_SET_FREQ].update();
			}
		}
	}
}

// ------------------------------------------------------------------
void VESPER_DEVICE::onConnected()
{
}

// ------------------------------------------------------------------
void VESPER_DEVICE::onDisconnected()
{
	updateRegs03();
}

//------------------------------------------------------------------------------
void VESPER_DEVICE::processPacket(const ModbusPacket & packet)
{
	ModbusPacket::Type t = (ModbusPacket::Type)packet.type();

	unsigned char d = packet.device();
	unsigned short c = packet.bytes();

	if(d != address())
		return;

	LogCoolerBinary("VESPER_DEVICE[%d]: read: %s", address(), LogArray(packet.toByteArray()));

	switch(t)
	{
		case ModbusPacket::ResponseHolding:

			switch(c / sizeof(quint16))
			{
			case 4:
				if(m_vesperState.Type == VESPER_TYPE_E3_8100)
					regs03.setPacket(packet, VESPER_8100_REG_03_STATE, 4);
				else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
					regs03.setPacket(packet, VESPER_8300_REG_03_STATE, 4);
				break;
			default:
				LogCoolerError("VESPER_DEVICE[%d] responce ERROR length!!", address());
				break;
			}

			onAnswer03(VESPER_DEVICE_MAX_COUNTER_03);
			updateRegs03();
			break;

		case ModbusPacket::RecieptMultiRegisters:
			LogCoolerInfo("VESPER_DEVICE[%d] command accepted!!", address());
			onAnswer03(VESPER_DEVICE_MAX_COUNTER_03);
			updateRegs03();
			break;

		case ModbusPacket::Error:
			LogCoolerError("VESPER_DEVICE[%d] responce ERROR!!", address());
			break;

		default:
			LogCoolerError("VESPER_DEVICE[%d] unrequested packet", address());
			break;
	}
}

//------------------------------------------------------------------------------
bool VESPER_DEVICE::processCommands()
{
//	LogCoolerInfo("VESPER_DEVICE[%d] process commands", address());

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

			if(m_vesperState.Type == VESPER_TYPE_E3_8100)
			{
				switch(i.key())
				{
					case VESPER_8100_REG_10_CONTROL:
						i.value().setValue(m_vesperState.Control_8100.RegControl._Data, false);
/*						break;
					case VESPER_8100_REG_10_SET_FREQ:
						i.value().setValue(m_vesperState.Control_8100.RegFrequency._Data, false);
						break;*/
				}
			}
			else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
			{
				switch(i.key())
				{
					case VESPER_8300_REG_10_CONTROL:
						i.value().setValue(m_vesperState.Control_8300.RegControl._Data, false);
						break;
/*					case VESPER_8300_REG_10_SET_FREQ:
						i.value().setValue(m_vesperState.Control_8300.RegFrequency._Data, false);
						break;*/
				}
			}

			break;
		}
	}

	return wasCommand;
}

//------------------------------------------------------------------------------
bool VESPER_DEVICE::processQuery()
{
	switch(m_queryPacket)
	{
		case 0:
			if(m_vesperState.Type == VESPER_TYPE_E3_8100)
				request03(VESPER_8100_REG_03_STATE, 0, 4);//4 (from 0x20)
			else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
				request03(VESPER_8300_REG_03_STATE, 0, 4);//4 (from 0x120)
			m_queryPacket = 1;
			break;

		case 1:
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
void VESPER_DEVICE::setRegisters03()
{
	QMutableMapIterator<quint32, ModbusRegister> i(regs03);
	while(i.hasNext())
	{
		i.next();

		if(m_vesperState.Type == VESPER_TYPE_E3_8100)
		{
			switch(i.key())
			{
			case VESPER_8100_REG_03_STATE:
				m_vesperState.State_8100.RegState._Data = i.value();
				break;
			case VESPER_8100_REG_03_FREQUENCY:
				m_vesperState.State_8100.RegFrequency._Data = i.value();
				break;
			case VESPER_8100_REG_03_FAILURE:
				m_vesperState.State_8100.RegFailure._Data = i.value();
				break;
			case VESPER_8100_REG_03_SOFT:
				m_vesperState.State_8100.RegSoftware._Data = i.value();
				break;
			case VESPER_8100_REG_03_WARNING:
				m_vesperState.State_8100.RegWarning._Data = i.value();
				break;
			case VESPER_8100_REG_03_MF_INPUT:
				m_vesperState.State_8100.RegMFInput._Data = i.value();
				break;
			case VESPER_8100_REG_03_MF_OUTPUT:
				m_vesperState.State_8100.RegMFOutput._Data = i.value();
				break;
			case VESPER_8100_REG_03_CONNECTION:
				m_vesperState.State_8100.RegConnection._Data = i.value();
				break;
			case VESPER_8100_REG_03_OUT_FREQUENCY:
				m_vesperState.State_8100.RegOutFrequency._Data = i.value();
				break;
			case VESPER_8100_REG_03_OUT_CURRENT:
				m_vesperState.State_8100.RegOutCurrent._Data = i.value();
				break;
			case VESPER_8100_REG_03_OUT_VOLTAGE:
				m_vesperState.State_8100.RegOutVoltage._Data = i.value();
				break;
			case VESPER_8100_REG_03_OUT_POWER:
				m_vesperState.State_8100.RegOutPower._Data = i.value();
				break;
			case VESPER_8100_REG_03_DC_VOLTAGE:
				m_vesperState.State_8100.RegDCVoltage._Data = i.value();
				break;
			case VESPER_8100_REG_03_MOMENT:
				m_vesperState.State_8100.RegOutMoment._Data = i.value();
				break;
			case VESPER_8100_REG_03_TIMEWORK:
				m_vesperState.State_8100.RegTimework._Data = i.value();
				break;
			}

			if(m_status == DEVICE_OK && isInfoCollected())
			{
				m_vesperState.State_8100.Updated = QDateTime::currentDateTime();
			}
			else
			{
				m_vesperState.State_8100.Updated = QDateTime();
			}
		}
		else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
		{
			switch(i.key())
			{
			case VESPER_8300_REG_03_STATE:
				m_vesperState.State_8300.RegState._Data = i.value();
				break;
			case VESPER_8300_REG_03_ERROR_CODE:
				m_vesperState.State_8300.RegErrorCode._Data = i.value();
				break;
			case VESPER_8300_REG_03_MF_IN_OUT:
				m_vesperState.State_8300.RegMFInOut._Data = i.value();
				break;
			case VESPER_8300_REG_03_FREQUENCY:
				m_vesperState.State_8300.RegFrequency._Data = i.value();
				break;
			case VESPER_8300_REG_03_OUT_FREQUENCY:
				m_vesperState.State_8300.RegOutFrequency._Data = i.value();
				break;
			case VESPER_8300_REG_03_OUT_VOLTAGE:
				m_vesperState.State_8300.RegOutVoltage._Data = i.value();
				break;
			case VESPER_8300_REG_03_DC_VOLTAGE:
				m_vesperState.State_8300.RegDCVoltage._Data = i.value();
				break;
			case VESPER_8300_REG_03_OUT_CURRENT:
				m_vesperState.State_8300.RegOutCurrent._Data = i.value();
				break;
			case VESPER_8300_REG_03_MOMENT:
				m_vesperState.State_8300.RegOutMoment._Data = i.value();
				break;
			case VESPER_8300_REG_03_PID_FEEDBACK:
				break;
			case VESPER_8300_REG_03_PID_INPUT:
				break;
			case VESPER_8300_REG_03_AIN_VOLTAGE:
				break;
			case VESPER_8300_REG_03_AI2_VOLTAGE:
				break;
			case VESPER_8300_REG_03_KBD_VOLTAGE:
				break;
			}

			if(m_status == DEVICE_OK && isInfoCollected())
			{
				m_vesperState.State_8300.Updated = QDateTime::currentDateTime();
			}
			else
			{
				m_vesperState.State_8300.Updated = QDateTime();
			}
		}
	}
}

//------------------------------------------------------------------------------
void VESPER_DEVICE::updateRegs03()
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
bool VESPER_DEVICE::isActualState()
{
	qint64 timeUpdated = TimeUndefined;

	if(m_vesperState.Type == VESPER_TYPE_E3_8100)
	{
		if(!m_vesperState.State_8100.Updated.isNull())
			timeUpdated = timeDiff(m_vesperState.State_8100.Updated);
	}
	else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
		if(!m_vesperState.State_8300.Updated.isNull())
			timeUpdated = timeDiff(m_vesperState.State_8300.Updated);
	}
		
	return ((timeUpdated <= 10000) && (timeUpdated >= -10000) && (timeUpdated != TimeUndefined));
}

//------------------------------------------------------------------------------
bool VESPER_DEVICE::isInfoCollected()
{
	if(m_vesperState.Type == VESPER_TYPE_E3_8100)
	{
		return (
			regs03[VESPER_8100_REG_03_STATE].isInitialized()
		);
	}
	else if(m_vesperState.Type == VESPER_TYPE_E3_8300)
	{
		return (
			regs03[VESPER_8300_REG_03_STATE].isInitialized()
		);
	}
	else
	{
		return false;
	}
}

//------------------------------------------------------------------------------
