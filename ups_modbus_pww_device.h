#ifndef __UPS_MODBUS_POWERWARE_DEVICE_H__
#define __UPS_MODBUS_POWERWARE_DEVICE_H__

#include "modbus_packet.h"
#include "modbus_device.h"
#include "modbus_service.h"
#include "ups_struct.h"
#include "ups_modbus_service.h"
#include "ups_modbus_pww_struct.h"

//-----------------------------------------------------------------------------

#define POWERWARE_REG_02										0
#define POWERWARE_REG_02_On_Battery								1
#define POWERWARE_REG_02_On_Bypass								10
#define POWERWARE_REG_02_System_Normal							11
#define POWERWARE_REG_02_Ups_Off								16
#define POWERWARE_REG_02_Inverter_AC_over_voltage				144
#define POWERWARE_REG_02_Inverter_AC_under_voltage				145
#define POWERWARE_REG_02_Inverter_under_or_over_frequency		146
#define POWERWARE_REG_02_Bypass_AC_over_voltage					147
#define POWERWARE_REG_02_Bypass_AC_under_voltage				148
#define POWERWARE_REG_02_Bypass_under_or_over_frequency			149
#define POWERWARE_REG_02_Input_AC_over_voltage					150
#define POWERWARE_REG_02_Input_AC_under_voltage					151
#define POWERWARE_REG_02_Input_under_or_over_frequency			152
#define POWERWARE_REG_02_Output_AC_over_voltage					153
#define POWERWARE_REG_02_Output_AC_under_voltage				154
#define POWERWARE_REG_02_Output_under_or_over_frequency			155
#define POWERWARE_REG_02_Remote_emergency_power_off				156
#define POWERWARE_REG_02_Building_Alarm_6						158
#define POWERWARE_REG_02_Building_Alarm_5						159
#define POWERWARE_REG_02_Building_Alarm_4						160
#define POWERWARE_REG_02_Building_Alarm_3						161
#define POWERWARE_REG_02_Building_Alarm_2						162
#define POWERWARE_REG_02_Building_Alarm_1						163
#define POWERWARE_REG_02_Charger_logic_power_fail				166
#define POWERWARE_REG_02_Charger_over_voltage_or_current		167
#define POWERWARE_REG_02_Inverter_over_temperature				168
#define POWERWARE_REG_02_Output_overload						169
#define POWERWARE_REG_02_Inverter_output_over_current			171
#define POWERWARE_REG_02_DC_link_over_voltage					172
#define POWERWARE_REG_02_DC_link_under_voltage					173
#define POWERWARE_REG_02_Rectifier_failed						174
#define POWERWARE_REG_02_Inverter_fault							175
#define POWERWARE_REG_02_Battery_contactor_fail					176
#define POWERWARE_REG_02_Bypass_breaker_fail					177
#define POWERWARE_REG_02_Static_switch_failure					180
#define POWERWARE_REG_02_Battery_current_limit					191
#define POWERWARE_REG_02_Output_current_over_100				194
#define POWERWARE_REG_02_Shutdown_imminent						199
#define POWERWARE_REG_02_Battery_low							200
#define POWERWARE_REG_02_Utility_fail							201
#define POWERWARE_REG_02_Battery_DC_over_voltage				212
#define POWERWARE_REG_02_Power_supply_failure					214
#define POWERWARE_REG_02_Rectifier_current_over_125				219
#define POWERWARE_REG_02_Bypass_not_available					249
#define POWERWARE_REG_02_Battery_contactor_open					251
#define POWERWARE_REG_02_Inverter_contactor_open				252
#define POWERWARE_REG_02_Battery_totally_discharged				270
#define POWERWARE_REG_02_Loss_of_redundancy						276
#define POWERWARE_REG_02_Output_breaker_open					281
#define POWERWARE_REG_02_Check_battery_flag						293
#define POWERWARE_REG_02_Greater_than_106_overload_on_phase_A	303
#define POWERWARE_REG_02_Greater_than_106_overload_on_phase_B	304
#define POWERWARE_REG_02_Greater_than_106_overload_on_phase_C	305
#define POWERWARE_REG_02_Greater_than_125_overload_on_phase_A	306
#define POWERWARE_REG_02_Greater_than_125_overload_on_phase_B	307
#define POWERWARE_REG_02_Greater_than_125_overload_on_phase_C	308
#define POWERWARE_REG_02_Greater_than_150_overload_on_phase_A	309
#define POWERWARE_REG_02_Greater_than_150_overload_on_phase_B	310
#define POWERWARE_REG_02_Greater_than_150_overload_on_phase_C	311
#define POWERWARE_REG_02_UPS_On_Battery							312
#define POWERWARE_REG_02_UPS_On_Bypass							313
#define POWERWARE_REG_02_Load_Dumped_Load_Power_Off				314
#define POWERWARE_REG_02_Low_Battery_Shutdown					318
#define POWERWARE_REG_02_Bypass_Failure							332
#define POWERWARE_REG_02_Battery_Test_failed					335
#define POWERWARE_REG_02_Fuse_Failure							336
#define POWERWARE_REG_02_Fan_Failure							337
#define POWERWARE_REG_02_Site_Wiring_Fault						338
#define POWERWARE_REG_02_Batteries_Disconnected					343
#define POWERWARE_REG_02_Input_Breaker_Failed					361

//-----------------------------------------------------------------------------

#define POWERWARE_REG_04										0
#define POWERWARE_REG_04_INPUT_CURRENT_PHASE_A					19
#define POWERWARE_REG_04_INPUT_CURRENT_PHASE_B					20
#define POWERWARE_REG_04_INPUT_CURRENT_PHASE_C					21
#define POWERWARE_REG_04_OUTPUT_TRUE_POWER						22
#define POWERWARE_REG_04_INPUT_TRUE_POWER						23
#define POWERWARE_REG_04_OUTPUT_APPARENT_POWER					24
#define POWERWARE_REG_04_INPUT_APPARENT_POWER					25
#define POWERWARE_REG_04_OUTPUT_POWER_FACTOR					26
#define POWERWARE_REG_04_INPUT_POWER_FACTOR						27
#define POWERWARE_REG_04_OUTPUT_FREQUENCY						28
#define POWERWARE_REG_04_INPUT_FREQUENCY						29
#define POWERWARE_REG_04_BYPASS_FREQUENCY						31
#define POWERWARE_REG_04_BATTERY_CURRENT						33
#define POWERWARE_REG_04_BATTERY_VOLTAGE						34
#define POWERWARE_REG_04_BATTERY_LEFT							35
#define POWERWARE_REG_04_BATTERY_TIME_REMAINING					36
#define POWERWARE_REG_04_BYPASS_VOLTS_PHASE_A					54
#define POWERWARE_REG_04_BYPASS_VOLTS_PHASE_B					55
#define POWERWARE_REG_04_BYPASS_VOLTS_PHASE_C					56
#define POWERWARE_REG_04_INPUT_VOLTS_PHASE_A					57
#define POWERWARE_REG_04_INPUT_VOLTS_PHASE_B					58
#define POWERWARE_REG_04_INPUT_VOLTS_PHASE_C					59
#define POWERWARE_REG_04_LOAD_CURRENT_PHASE_A					66
#define POWERWARE_REG_04_LOAD_CURRENT_PHASE_B					67
#define POWERWARE_REG_04_LOAD_CURRENT_PHASE_C					68
#define POWERWARE_REG_04_LOAD_CURRENT_PHASE_A_BAR_CHART			69
#define POWERWARE_REG_04_LOAD_CURRENT_PHASE_B_BAR_CHART			70
#define POWERWARE_REG_04_LOAD_CURRENT_PHASE_C_BAR_CHART			71
#define POWERWARE_REG_04_OUTPUT_VOLTS_A							79
#define POWERWARE_REG_04_OUTPUT_VOLTS_B							80
#define POWERWARE_REG_04_OUTPUT_VOLTS_C							81

//-----------------------------------------------------------------------------

class POWERWARE_MODBUS_DEVICE : public MODBUS_DEVICE
{
	PowerwareState m_powerwareState;

public:

	enum tagPowerwareDeviceCounter
	{
		POWERWARE_MODBUS_DEVICE_MAX_COUNTER_02 = 6,
		POWERWARE_MODBUS_DEVICE_MAX_COUNTER_04 = 6,
	};

	POWERWARE_MODBUS_DEVICE(UPS_MODBUS_SERVICE *parent, quint32 address = 0, qint32 connection = -1);
	virtual ~POWERWARE_MODBUS_DEVICE();

	PowerwareState & state() {
		return m_powerwareState;
	}

	bool isActualState();
	bool isInfoCollected();

	virtual void onConnected();
	virtual void onDisconnected();

	void setRegisters02();
	void updateRegs02();
	void setRegisters04();
	void updateRegs04();

	virtual void processPacket(const ModbusPacket & packet);
	virtual bool processCommands();
	virtual bool processQuery();
};

//-----------------------------------------------------------------------------

#endif // __UPS_MODBUS_POWERWARE_DEVICE_H__
