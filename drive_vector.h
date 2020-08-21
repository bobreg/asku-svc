#ifndef __DRIVE_VECTOR_H__
#define __DRIVE_VECTOR_H__

#include "modbus_packet.h"
#include "modbus_device.h"
#include "modbus_service.h"
#include "drive_struct.h"
#include "drive_service.h"

//write registers
#define VECTOR_REG_10_CONTROL				240
#define VECTOR_REG_10_RESET_AVAR			245
#define VECTOR_REG_10_SET_SPEED_NOMINAL		241
#define VECTOR_REG_10_SET_SPEED				242
#define VECTOR_REG_10_SET_CURRENT			244
#define VECTOR_REG_10_SET_POSITION			243
#define VECTOR_REG_10_SYNC					246
#define VECTOR_REG_10_ADRESS_MODBUS			586
#define VECTOR_REG_10_RESERVE_OVERRIDE		247
#define VECTOR_REG_10_SET_MODE				564
#define VECTOR_REG_10_COR_SENSOR_TO_ROTOR	614
#define VECTOR_REG_10_COR_SENSOR_TO_GEO		615
#define VECTOR_REG_10_ENABLE_PROG			10

//read registers
#define VECTOR_REG_03_STATE					20
#define VECTOR_REG_03_WARNING				23
#define VECTOR_REG_03_SAFE					21
#define VECTOR_REG_03_SAFE_MORE				22
#define VECTOR_REG_03_OVERHEAT				24
#define VECTOR_REG_03_HARDWARE				25
#define VECTOR_REG_03_SOFTWARE				26
#define VECTOR_REG_03_LINK					31

#define VECTOR_REG_03_SPEED_DISCRETE		40
#define VECTOR_REG_03_SPEED_NOMINAL			41
#define VECTOR_REG_03_SPEED_VALUE			50
#define VECTOR_REG_03_SPEED_REAL_DISCRETE	45
#define VECTOR_REG_03_SPEED_REAL_NOMINAL	46
#define VECTOR_REG_03_SPEED_REAL_VALUE		52

#define VECTOR_REG_03_POSITION_VALUE		47
#define VECTOR_REG_03_POSITION_RT_ST		48
#define VECTOR_REG_03_MOMENT_VALUE			75
#define VECTOR_REG_03_MOMENT_DISCRETE		76
#define VECTOR_REG_03_FULL_MOMENT_VALUE		100
#define VECTOR_REG_03_FULL_MOMENT_DISCRETE	101

#define VECTOR_REG_03_CURRENT_VALUE			57
#define VECTOR_REG_03_CURRENT_NOMINAL		58
#define VECTOR_REG_03_VOLTAGE_VALUE			55
#define VECTOR_REG_03_VOLTAGE_NOMINAL		56

#define VECTOR_REG_03_VERSION				1
#define VECTOR_REG_03_VERSION_DATE			3
#define VECTOR_REG_03_VERSION_TIME			4
#define VECTOR_REG_03_SERIAL				5
#define VECTOR_REG_03_PRODUCTION_DATE		6
#define VECTOR_REG_03_WORKHOURS				7
#define VECTOR_REG_03_FIRMWARE_CONFIG		609


class VECTOR_DEVICE : public MODBUS_DEVICE
{
	bool m_positioning;
	bool m_reserving;

	VectorState m_vectorState;

public:

	enum tagVectorDeviceCounter
	{
		VECTOR_DEVICE_MAX_COUNTER_03 = 12
	};

	VECTOR_DEVICE(MODBUS_SERVICE *parent, quint32 address = 0);
	virtual ~VECTOR_DEVICE();

	VectorState & state() {
		return m_vectorState;
	}

	bool isActualState();
	bool isInfoCollected();

	virtual void onConnected();
	virtual void onDisconnected();

	void setSpeed(quint16 value);
	void setPosition(quint16 value);
	void setSpeedPosition(bool pos);
	void setReset();
	void setStart(bool reverse);
	void setStop();
	void setReserveOverride(quint16 value);

	void setRegisters03();
	void updateRegs03();
	void updateCommands();

	virtual void processPacket(const ModbusPacket & packet);
	virtual bool processCommands();
	virtual bool processQuery();
};


#endif // __DRIVE_VECTOR_H__
