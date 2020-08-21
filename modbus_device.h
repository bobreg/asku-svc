#ifndef __MODBUS_DEVICE_H__
#define __MODBUS_DEVICE_H__

#include <QObject>
#include <QMap>
#include "modbus_packet.h"

//-----------------------------------------------------------------------------
/*
class ModbusBitsRegister
{
	quint16 m_value;

public:
	ModbusBitsRegister(quint16 val = 0) {
		m_value = val;
	}

	quint16 value() {
		return m_value;
	}

	operator unsigned short() {
		return m_value;
	}

	operator quint16() {
		return m_value;
	}

	bool operator[](quint32 bit) {
		return (m_value & (1 << bit));
	}

	void setBit(quint32 bit) {
		m_value |= (1 << bit);
	}

	void clrBit(quint32 bit) {
		m_value &= ~(1 << bit);
	}
};
*/
//-----------------------------------------------------------------------------

typedef struct _tagModbusRegisterRegion
{
	quint32 address;
	quint32 count;
	quint32 readFunction;
	quint32 writeFunction;
	bool changed;
}ModbusRegisterRegion;

//-----------------------------------------------------------------------------

template <typename T>
class ModbusTemplate
{
	T m_value;
	bool m_initialized;
	bool m_changed;
	QString m_name;

public:
	ModbusTemplate(QString name = QString(), T value = (T)0, bool initialized = false, bool changed = false)
	{
		m_name = name;
		m_value = value;
		m_initialized = initialized;
		m_changed = changed;
	}

	ModbusTemplate<T> & operator=(T value)
	{
		if(m_value != value)
			m_changed = true;
		if(!m_initialized)
			m_initialized = true;
		m_value = value;
		return *this;
	}

	ModbusTemplate<T> & operator=(const ModbusTemplate<T> & reg)
	{
		if(m_value != reg.m_value)
			m_changed = true;
		if(!m_initialized)
			m_initialized = true;
		m_value = reg.m_value;
		return *this;
	}

	operator T() const {
		return m_value;
	}

	bool isChanged() {
		return m_changed;
	}

	bool isInitialized() {
		return m_initialized;
	}

	void reset() {
		m_initialized = false;
		m_changed = false;
		m_value = (T)0;
	}

	void update() {
		m_changed = true;
	}

	void respond() {
		m_changed = false;
	}

	QString name() {
		return m_name;
	}

	T value() {
		return m_value;
	}

	void setValue(T value, bool changed = true) {
		m_value = value;
		m_changed = changed;
	}

};

//-----------------------------------------------------------------------------

typedef ModbusTemplate<unsigned short> ModbusRegister;
typedef ModbusTemplate<unsigned short> ModbusHolding;
typedef ModbusTemplate<bool> ModbusDiscrete;
typedef ModbusTemplate<unsigned short> ModbusControl;

//-----------------------------------------------------------------------------

#define DEFINE_REGISTER(a) a, #a

//-----------------------------------------------------------------------------

template <class T>
class ModbusTemplateMap : public QMap<quint32, T>
{
public:
	ModbusTemplateMap()
	{
		this->clear();
	}

	void addRegister(quint32 address, QString name = QString())
	{
		this->insert(address, T(name));
	}

	void removeRegister(quint32 address)
	{
		if(this->contains(address))
			this->remove(address);
	}

	void reset()
	{
		QMutableMapIterator<quint32, T> i(*this);
		while(i.hasNext())
		{
			i.next();
			i.value().reset();
		}
	}

	QByteArray toByteArray(quint32 address, quint32 count = 1);
	void setPacket(const ModbusPacket & packet, quint32 address, quint32 count);

	QString toString(quint32 address = 0, quint32 count = 0);
};

//-----------------------------------------------------------------------------

typedef ModbusTemplateMap<ModbusDiscrete> ModbusDiscreteMap;
typedef ModbusTemplateMap<ModbusHolding> ModbusHoldingMap;
typedef ModbusTemplateMap<ModbusRegister> ModbusRegisterMap;
typedef ModbusTemplateMap<ModbusControl> ModbusControlMap;

//-----------------------------------------------------------------------------

class ModbusRegisterList : public QList<ModbusRegisterRegion>
{
public:
	ModbusRegisterList();
};

//-----------------------------------------------------------------------------

class MODBUS_SERVICE;

//-----------------------------------------------------------------------------

class MODBUS_DEVICE
{
public:
	enum MODBUS_DEVICE_STATUS {
		DEVICE_INIT = 0,
		DEVICE_OK = 1,
		DEVICE_FAIL = 2
	};

protected:
	MODBUS_SERVICE *parent;

	ModbusDiscreteMap regs02;
	ModbusHoldingMap regs03;
	ModbusRegisterMap regs04;
	ModbusControlMap regs10;
	ModbusRegisterList reglist;

	quint16 m_address;
	qint32 m_connection;

	bool m_connected;
	bool m_needRefresh02;
	bool m_needRefresh03;
	bool m_needRefresh04;
	qint32 m_counter02;
	qint32 m_counter03;
	qint32 m_counter04;
	quint32 m_queryPacket;

	MODBUS_DEVICE_STATUS m_status;

	void sendToDevice(QByteArray data);

public:
	MODBUS_DEVICE(MODBUS_SERVICE * parent, quint32 address = 0, qint32 connection = -1);
	virtual ~MODBUS_DEVICE();

	void setAddress(quint16 address);
	quint16 address();

	bool isConnectionDependent();
	void setConnectionDependent(bool on, qint32 connection = -1);
	qint32 connection();

	void onConnectedDevice();
	void onDisconnectedDevice();
	bool isConnected();

	void onAnswer02(qint32 value);
	void onAnswer03(qint32 value);
	void onAnswer04(qint32 value);
	void checkResponce();

	void checkDeviceState();

	virtual void onConnected();
	virtual void onDisconnected();

	void request02(quint32 number, quint32 offset, quint32 count);
	void request03(quint32 number, quint32 offset, quint32 count);
	void request04(quint32 number, quint32 offset, quint32 count);
	void control10(quint32 number, quint32 offset, quint32 count);

	virtual void processPacket(const ModbusPacket & packet);
	virtual bool processCommands();
	virtual bool processQuery();

	virtual bool isActualState();
	virtual bool isInfoCollected();
};

//-----------------------------------------------------------------------------

#endif // __MODBUS_DEVICE_H__
