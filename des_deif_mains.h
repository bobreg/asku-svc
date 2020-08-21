#ifndef __DES_DEIF_MAINS_H__
#define __DES_DEIF_MAINS_H__

#include "modbus_packet.h"
#include "modbus_device.h"
#include "modbus_service.h"
#include "des_struct.h"
#include "des_service.h"

//-----------------------------------------------------------------------------

class DEIF_MAINS_DEVICE : public MODBUS_DEVICE
{
	DeifMainsState m_deifMainsState;

public:

	enum tagDeifMainsDeviceCounter
	{
		DEIF_MAINS_DEVICE_MAX_COUNTER_02 = 6,
		DEIF_MAINS_DEVICE_MAX_COUNTER_03 = 6,
		DEIF_MAINS_DEVICE_MAX_COUNTER_04 = 6
	};

	DEIF_MAINS_DEVICE(MODBUS_SERVICE *parent, quint32 address = 0, qint32 connection = -1);
	virtual ~DEIF_MAINS_DEVICE();

	DeifMainsState & state() {
		return m_deifMainsState;
	}

	bool isActualState();
	bool isInfoCollected();

	virtual void onConnected();
	virtual void onDisconnected();

	void setControl1(quint16 value);
	void setControl2(quint16 value);
	void setTB(bool on);
	void setMB(bool on);
	void setMode(quint32 mode);
	void setReset();

	void setRegisters02();
	void updateRegs02();
	void setRegisters03();
	void updateRegs03();
	void setRegisters04();
	void updateRegs04();
	void updateCommands();

	virtual void processPacket(const ModbusPacket & packet);
	virtual bool processCommands();
	virtual bool processQuery();
};

//-----------------------------------------------------------------------------

#endif // __DES_DEIF_MAINS_H__
