#include "../common/logger.h"
#include "globalvar.h"
#include "modbus_device.h"
#include "modbus_service.h"


// ------------------------------------------------------------------
template<>
QString ModbusRegisterMap::toString(quint32 address, quint32 count)
{
	QStringList list;
	if(address == 0 && count == 0)
	{
		QMutableMapIterator<quint32, ModbusRegister> i(*this);
		while(i.hasNext())
		{
			i.next();
//			cout << i.key() << ": " << i.value() << endl;
			list << QString("0x%2 i%3 c%4 : (%5)-%1").arg(i.value().name()).arg((quint16)i.value().value(), 4, 16, QChar('0')).arg((int)i.value().isInitialized()).arg((int)i.value().isChanged()).arg(i.key());
		}
	}
	else
	{
		for(quint32 i = 0; i < count; i++)
		{
			ModbusRegister reg = value(address + i);
			list << QString("0x%2 i%3 c%4 : (%5)-%1").arg(reg.name()).arg((quint16)reg, 4, 16, QChar('0')).arg((int)reg.isInitialized()).arg((int)reg.isChanged()).arg(address + i);
		}
	}
	return list.join("\n");
}

// ------------------------------------------------------------------
template<>
QByteArray ModbusRegisterMap::toByteArray(quint32 address, quint32 count)
{
	QByteArray buffer;
	buffer.resize(count * sizeof(quint16));
	buffer.fill(0);
	quint16 *values =(quint16*)(char*)buffer.data();

	for(quint32 i = 0; i < count; i++)
		values[i] = value(address + i);

	return buffer;
}

// ------------------------------------------------------------------
template<>
void ModbusRegisterMap::setPacket(const ModbusPacket & packet, quint32 address, quint32 count1)
{
	Q_UNUSED(count1);

	QByteArray buffer;
	buffer.resize(packet.bytes());
	buffer.fill(0);
	quint16 *values =(quint16*)(char*)buffer.data();

	quint32 count = packet.bytes() / sizeof(quint16);

	packet.getResponce((ModbusPacket::Type)packet.type(), (quint16*)(char*)buffer.data(), count);

	for(quint32 i = 0; i < count; i++)
		operator[](address + i) = values[i];
}

// ------------------------------------------------------------------
template<>
QString ModbusDiscreteMap::toString(quint32 address, quint32 count)
{
	QStringList list;
	if(address == 0 && count == 0)
	{
		QMutableMapIterator<quint32, ModbusDiscrete> i(*this);
		while(i.hasNext())
		{
			i.next();
//			cout << i.key() << ": " << i.value() << endl;
			list << QString("0x%2 i%3 c%4 : (%5)-%1").arg(i.value().name()).arg((bool)i.value().value()).arg((int)i.value().isInitialized()).arg((int)i.value().isChanged()).arg(i.key());
		}
	}
	else
	{
		for(quint32 i = 0; i < count; i++)
		{
			ModbusDiscrete reg = value(address + i);
			list << QString("0x%2 i%3 c%4 : (%5)-%1").arg(reg.name()).arg((bool)reg).arg((int)reg.isInitialized()).arg((int)reg.isChanged()).arg(address + i);
		}
	}
	return list.join("\n");
}

// ------------------------------------------------------------------
template<>
void ModbusDiscreteMap::setPacket(const ModbusPacket & packet, quint32 address, quint32 count)
{
	QByteArray buffer;

	buffer.resize(sizeof(bool)*count);
	buffer.fill(0);
	bool *values =(bool*)(char*)buffer.data();

	packet.getResponce((ModbusPacket::Type)packet.type(), (bool*)(char*)buffer.data(), count);

	for(quint32 i = 0; i < count; i++)
		operator[](address + i) = values[i];
}

// ------------------------------------------------------------------
ModbusRegisterList::ModbusRegisterList()
{
	clear();
}

// ------------------------------------------------------------------
MODBUS_DEVICE::MODBUS_DEVICE(MODBUS_SERVICE * p, quint32 address, qint32 connection)
{
	parent = p;
	m_address = address;
	m_connection = connection;

	m_connected = false;
	m_needRefresh02 = false;
	m_needRefresh03 = false;
	m_needRefresh04 = false;
	m_counter02 = 0;
	m_counter03 = 0;
	m_counter04 = 0;
	m_queryPacket = 0;
	m_status = DEVICE_INIT;
}

// ------------------------------------------------------------------
MODBUS_DEVICE::~MODBUS_DEVICE()
{
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::setAddress(quint16 address)
{
	m_address = address;
}

// ------------------------------------------------------------------
quint16 MODBUS_DEVICE::address()
{
	return m_address;
}



// ------------------------------------------------------------------
bool MODBUS_DEVICE::isConnectionDependent()
{
	return (m_connection >= 0);
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::setConnectionDependent(bool on, qint32 connection)
{
	if(on)
		m_connection = connection;
	else
		m_connection = -1;
}

// ------------------------------------------------------------------
qint32 MODBUS_DEVICE::connection()
{
	return m_connection;
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::onConnectedDevice()
{
	m_connected = true;
	m_needRefresh02 = true;
	m_needRefresh03 = true;
	m_needRefresh04 = true;
	m_queryPacket = 0;

	onConnected();
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::onDisconnectedDevice()
{
	m_connected = false;
	m_counter02 = 0;
	m_counter03 = 0;
	m_counter04 = 0;
	m_needRefresh02 = true;
	m_needRefresh03 = true;
	m_needRefresh04 = true;
	m_queryPacket = 0;

	onDisconnected();
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::onAnswer02(qint32 value)
{
	if(!m_counter02)
		m_needRefresh02 = true;
	m_counter02 = value;
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::onAnswer03(qint32 value)
{
	if(!m_counter03)
		m_needRefresh03 = true;
	m_counter03 = value;
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::onAnswer04(qint32 value)
{
	if(!m_counter04)
		m_needRefresh04 = true;
	m_counter04 = value;
}

//------------------------------------------------------------------------------
void MODBUS_DEVICE::checkResponce()
{
	if(m_counter02)
	{
		m_counter02--;
		if(!m_counter02)
			m_needRefresh02 = true;
	}
	if(m_counter03)
	{
		m_counter03--;
		if(!m_counter03)
			m_needRefresh03 = true;
	}
	if(m_counter04)
	{
		m_counter04--;
		if(!m_counter04)
			m_needRefresh04 = true;
	}
}

//------------------------------------------------------------------------------
void MODBUS_DEVICE::checkDeviceState()
{
	switch(m_status)
	{
		case DEVICE_INIT:
			m_status = m_connected ? DEVICE_OK : DEVICE_FAIL;
//			emit sigAnswer(nv,connected);
			break;

		case DEVICE_OK:
			if(!m_connected || (m_counter02 == 0 && m_counter03 == 0 && m_counter04 == 0))
			{
				if(m_status != DEVICE_FAIL)
				{
					m_status = DEVICE_FAIL;
//					emit sigAnswer(nv,false);
				}
			}
			break;

		case DEVICE_FAIL:
			if(m_connected && (m_counter02 > 0 || m_counter03 > 0 || m_counter04 > 0))
			{
				if(m_status != DEVICE_OK)
				{
					m_status = DEVICE_OK;
//					emit sigAnswer(nv,true);
				}
			}
			break;
	}
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::onConnected()
{
	
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::onDisconnected()
{
	
}

// ------------------------------------------------------------------
bool MODBUS_DEVICE::isConnected()
{
	return m_connected;
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::request02(quint32 number, quint32 offset, quint32 count)
{
	LogModbusInfo("MODBUS_DEVICE[%d] request02: reg=%04X(%d) (%s) cnt=%d", address(), number, number, qPrintable(regs02[number + offset].name()), count);

	ModbusPacket pkt;
	pkt.refRead(ModbusPacket::RequestDiscrete, address(), number, count);

	sendToDevice(pkt.toByteArray());
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::request03(quint32 number, quint32 offset, quint32 count)
{
	LogModbusInfo("MODBUS_DEVICE[%d] request03: reg=%04X(%d) (%s) cnt=%d", address(), number, number, qPrintable(regs03[number + offset].name()), count);

	ModbusPacket pkt;
	pkt.refRead(ModbusPacket::RequestHolding, address(), number, count);

	sendToDevice(pkt.toByteArray());
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::request04(quint32 number, quint32 offset, quint32 count)
{
	LogModbusInfo("MODBUS_DEVICE[%d] request04: reg=%04X(%d) (%s) cnt=%d", address(), number, number, qPrintable(regs04[number + offset].name()), count);

	ModbusPacket pkt;
	pkt.refRead(ModbusPacket::RequestRegisters, address(), number, count);

	sendToDevice(pkt.toByteArray());
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::control10(quint32 number, quint32 offset, quint32 count)
{
	LogModbusInfo("MODBUS_DEVICE[%d] control10: reg=%04X(%d) value1=%04X (%s)", address(), number, number, (quint16)regs10[offset], qPrintable(regs10[offset].name()));

	QByteArray buffer = regs10.toByteArray(offset, count);
	if(buffer.size() == (int)(count * sizeof(quint16)))
	{
		ModbusPacket pkt;
		pkt.refWrite(ModbusPacket::CommandMultiRegisters, address(), number, (unsigned short*)(char*)buffer.data(), count);

		sendToDevice(pkt.toByteArray());
	}
	else
	{
		LogModbusError("MODBUS_DEVICE: control10: error making packet");
	}
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::sendToDevice(QByteArray data)
{
	LogModbusBinary("MODBUS_DEVICE[%d]: write: %s", address(), LogArray(data));

	if(parent)
		parent->sendToDevice(data, m_connection);
}

// ------------------------------------------------------------------
void MODBUS_DEVICE::processPacket(const ModbusPacket & packet)
{
	Q_UNUSED(packet);
}

// ------------------------------------------------------------------
bool MODBUS_DEVICE::processCommands()
{
	return false;
}

// ------------------------------------------------------------------
bool MODBUS_DEVICE::processQuery()
{
	return false;
}

// ------------------------------------------------------------------
bool MODBUS_DEVICE::isActualState()
{
	return false;
}

//------------------------------------------------------------------------------
bool MODBUS_DEVICE::isInfoCollected()
{
	return false;
}

//------------------------------------------------------------------------------
