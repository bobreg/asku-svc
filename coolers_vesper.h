#ifndef __COOLERS_VESPER_H__
#define __COOLERS_VESPER_H__

#include "modbus_packet.h"
#include "modbus_device.h"
#include "modbus_service.h"
#include "coolers_struct.h"
#include "coolers_service.h"

//VESPER E2-8100
//--------------

//write registers
#define VESPER_8100_REG_10_CONTROL			0x01
#define VESPER_8100_REG_10_SET_FREQ			0x02

//read registers
#define VESPER_8100_REG_03_STATE			0x20
#define VESPER_8100_REG_03_FAILURE			0x21
#define VESPER_8100_REG_03_SOFT				0x22
#define VESPER_8100_REG_03_FREQUENCY		0x23
#define VESPER_8100_REG_03_OUT_FREQUENCY	0x24
#define VESPER_8100_REG_03_OUT_CURRENT		0x27
#define VESPER_8100_REG_03_OUT_VOLTAGE		0x28
#define VESPER_8100_REG_03_MF_INPUT			0x2B
#define VESPER_8100_REG_03_WARNING			0x2C
#define VESPER_8100_REG_03_MF_OUTPUT		0x2D
#define VESPER_8100_REG_03_DC_VOLTAGE		0x31
#define VESPER_8100_REG_03_MOMENT			0x32
#define VESPER_8100_REG_03_TIMEWORK			0x35
#define VESPER_8100_REG_03_OUT_POWER		0x37
#define VESPER_8100_REG_03_CONNECTION		0x3D

//VESPER E2-8300
//--------------

//write registers
#define VESPER_8300_REG_10_CONTROL			0x0101
#define VESPER_8300_REG_10_SET_FREQ			0x0102

//read registers
#define VESPER_8300_REG_03_STATE			0x0120
#define VESPER_8300_REG_03_ERROR_CODE		0x0121
#define VESPER_8300_REG_03_MF_IN_OUT		0x0122
#define VESPER_8300_REG_03_FREQUENCY		0x0123
#define VESPER_8300_REG_03_OUT_FREQUENCY	0x0124
#define VESPER_8300_REG_03_OUT_VOLTAGE		0x0125
#define VESPER_8300_REG_03_DC_VOLTAGE		0x0126
#define VESPER_8300_REG_03_OUT_CURRENT		0x0127
#define VESPER_8300_REG_03_MOMENT			0x0129
#define VESPER_8300_REG_03_PID_FEEDBACK		0x012A
#define VESPER_8300_REG_03_PID_INPUT		0x012B
#define VESPER_8300_REG_03_AIN_VOLTAGE		0x012C
#define VESPER_8300_REG_03_AI2_VOLTAGE		0x012D
#define VESPER_8300_REG_03_KBD_VOLTAGE		0x012E


class VESPER_DEVICE : public MODBUS_DEVICE
{
	VesperState m_vesperState;

public:

	enum tagVesperDeviceCounter
	{
		VESPER_DEVICE_MAX_COUNTER_03 = 6
	};

	VESPER_DEVICE(MODBUS_SERVICE *parent, quint32 address = 0, quint32 type = 0);
	virtual ~VESPER_DEVICE();

	VesperState & state() {
		return m_vesperState;
	}

	void setType(quint32 type);

	bool isActualState();
	bool isInfoCollected();

	virtual void onConnected();
	virtual void onDisconnected();

	void setFrequency(quint16 value);
	void setControl(quint16 value);

	void setReset();
	void setStart(bool reverse);
	void setStop();
	void updateControls();

	void setRegisters03();
	void updateRegs03();
	void updateCommands();
	void updateFrequency();

	virtual void processPacket(const ModbusPacket & packet);
	virtual bool processCommands();
	virtual bool processQuery();
};


#endif // __COOLERS_VESPER_H__
