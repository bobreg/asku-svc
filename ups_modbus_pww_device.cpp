#include "../common/logger.h"
#include "globalvar.h"
#include "modbus_device.h"
#include "ups.h"
#include "ups_struct.h"
#include "ups_modbus_service.h"
#include "ups_modbus_pww_device.h"

//------------------------------------------------------------------------------
POWERWARE_MODBUS_DEVICE::POWERWARE_MODBUS_DEVICE(UPS_MODBUS_SERVICE * p, quint32 address, qint32 connection) : MODBUS_DEVICE(p, address, connection)
{
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_On_Battery));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_On_Bypass));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_System_Normal));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Ups_Off));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Inverter_AC_over_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Inverter_AC_under_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Inverter_under_or_over_frequency));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Bypass_AC_over_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Bypass_AC_under_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Bypass_under_or_over_frequency));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Input_AC_over_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Input_AC_under_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Input_under_or_over_frequency));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Output_AC_over_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Output_AC_under_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Output_under_or_over_frequency));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Remote_emergency_power_off));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Building_Alarm_6));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Building_Alarm_5));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Building_Alarm_4));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Building_Alarm_3));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Building_Alarm_2));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Building_Alarm_1));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Charger_logic_power_fail));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Charger_over_voltage_or_current));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Inverter_over_temperature));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Output_overload));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Inverter_output_over_current));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_DC_link_over_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_DC_link_under_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Rectifier_failed));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Inverter_fault));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Battery_contactor_fail));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Bypass_breaker_fail));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Static_switch_failure));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Battery_current_limit));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Output_current_over_100));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Shutdown_imminent));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Battery_low));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Utility_fail));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Battery_DC_over_voltage));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Power_supply_failure));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Rectifier_current_over_125));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Bypass_not_available));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Battery_contactor_open));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Inverter_contactor_open));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Battery_totally_discharged));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Loss_of_redundancy));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Output_breaker_open));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Check_battery_flag));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Greater_than_106_overload_on_phase_A));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Greater_than_106_overload_on_phase_B));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Greater_than_106_overload_on_phase_C));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Greater_than_125_overload_on_phase_A));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Greater_than_125_overload_on_phase_B));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Greater_than_125_overload_on_phase_C));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Greater_than_150_overload_on_phase_A));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Greater_than_150_overload_on_phase_B));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Greater_than_150_overload_on_phase_C));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_UPS_On_Battery));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_UPS_On_Bypass));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Load_Dumped_Load_Power_Off));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Low_Battery_Shutdown));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Bypass_Failure));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Battery_Test_failed));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Fuse_Failure));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Fan_Failure));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Site_Wiring_Fault));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Batteries_Disconnected));
	regs02.addRegister(DEFINE_REGISTER(POWERWARE_REG_02_Input_Breaker_Failed));

	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_INPUT_CURRENT_PHASE_A));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_INPUT_CURRENT_PHASE_B));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_INPUT_CURRENT_PHASE_C));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_OUTPUT_TRUE_POWER));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_INPUT_TRUE_POWER));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_OUTPUT_APPARENT_POWER));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_INPUT_APPARENT_POWER));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_OUTPUT_POWER_FACTOR));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_INPUT_POWER_FACTOR));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_OUTPUT_FREQUENCY));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_BYPASS_FREQUENCY));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_BATTERY_CURRENT));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_BATTERY_VOLTAGE));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_BATTERY_LEFT));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_BATTERY_TIME_REMAINING));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_BYPASS_VOLTS_PHASE_A));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_BYPASS_VOLTS_PHASE_B));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_BYPASS_VOLTS_PHASE_C));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_INPUT_VOLTS_PHASE_A));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_INPUT_VOLTS_PHASE_B));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_INPUT_VOLTS_PHASE_C));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_LOAD_CURRENT_PHASE_A));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_LOAD_CURRENT_PHASE_B));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_LOAD_CURRENT_PHASE_C));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_LOAD_CURRENT_PHASE_A_BAR_CHART));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_LOAD_CURRENT_PHASE_B_BAR_CHART));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_LOAD_CURRENT_PHASE_C_BAR_CHART));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_OUTPUT_VOLTS_A));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_OUTPUT_VOLTS_B));
	regs04.addRegister(DEFINE_REGISTER(POWERWARE_REG_04_OUTPUT_VOLTS_C));

	LogUpsInfo("POWERWARE_MODBUS_DEVICE: register pack 02\n%s", qPrintable(regs02.toString()));
	LogUpsInfo("POWERWARE_MODBUS_DEVICE: register pack 04\n%s", qPrintable(regs04.toString()));
}

//------------------------------------------------------------------------------
POWERWARE_MODBUS_DEVICE::~POWERWARE_MODBUS_DEVICE()
{
	
}

// ------------------------------------------------------------------
void POWERWARE_MODBUS_DEVICE::onConnected()
{
}

// ------------------------------------------------------------------
void POWERWARE_MODBUS_DEVICE::onDisconnected()
{
	updateRegs02();
	updateRegs04();
}

//------------------------------------------------------------------------------
void POWERWARE_MODBUS_DEVICE::processPacket(const ModbusPacket & packet)
{
	ModbusPacket::Type t = (ModbusPacket::Type)packet.type();

	unsigned char d = packet.device();
//	unsigned short c = packet.bytes();

	if(d != address())
		return;

	LogUpsBinary("POWERWARE_MODBUS_DEVICE[%d]: read: %s", address(), LogArray(packet.toByteArray()));

	switch(t)
	{
		case ModbusPacket::ResponseDiscrete:
			regs02.setPacket(packet, POWERWARE_REG_02 + 1, 362);
			onAnswer02(POWERWARE_MODBUS_DEVICE_MAX_COUNTER_02);
			updateRegs02();
			break;

		case ModbusPacket::ResponseRegisters:
			regs04.setPacket(packet, POWERWARE_REG_04 + 1, 91);
			onAnswer04(POWERWARE_MODBUS_DEVICE_MAX_COUNTER_04);
			updateRegs04();
			break;

		case ModbusPacket::Error:
			LogUpsError("POWERWARE_MODBUS_DEVICE[%d] responce ERROR!!", address());
			break;

		default:
			LogUpsError("POWERWARE_MODBUS_DEVICE[%d] unrequested packet", address());
			break;
	}
}

//------------------------------------------------------------------------------
bool POWERWARE_MODBUS_DEVICE::processCommands()
{
	return false;
}

//------------------------------------------------------------------------------
bool POWERWARE_MODBUS_DEVICE::processQuery()
{
	switch(m_queryPacket)
	{
		case 0:
			request02(POWERWARE_REG_02, 0, 362);//362 (from 0)
			m_queryPacket = 1;
			break;

		case 1:
			request04(POWERWARE_REG_04, 0, 91);//91 (from 0)
			m_queryPacket = 2;
			break;

		case 2:
			//nop
			m_queryPacket = 0;
			return false;
			break;
	}

	checkResponce();

	if(m_needRefresh02)
		updateRegs02();

	if(m_needRefresh04)
		updateRegs04();

	return true;
}

//------------------------------------------------------------------------------
void POWERWARE_MODBUS_DEVICE::setRegisters02()
{
	QMutableMapIterator<quint32, ModbusDiscrete> i(regs02);
	while(i.hasNext())
	{
		i.next();

		switch(i.key())
		{
			case POWERWARE_REG_02_On_Battery:
				m_powerwareState.State.RegState.Bits.On_Battery = i.value();
				break;
			case POWERWARE_REG_02_On_Bypass:
				m_powerwareState.State.RegState.Bits.On_Bypass = i.value();
				break;
			case POWERWARE_REG_02_System_Normal:
				m_powerwareState.State.RegState.Bits.System_Normal = i.value();
				break;
			case POWERWARE_REG_02_Ups_Off:
				m_powerwareState.State.RegState.Bits.Ups_Off = i.value();
				break;
			case POWERWARE_REG_02_Inverter_AC_over_voltage:
				m_powerwareState.State.RegState.Bits.Inverter_AC_over_voltage = i.value();
				break;
			case POWERWARE_REG_02_Inverter_AC_under_voltage:
				m_powerwareState.State.RegState.Bits.Inverter_AC_under_voltage = i.value();
				break;
			case POWERWARE_REG_02_Inverter_under_or_over_frequency:
				m_powerwareState.State.RegState.Bits.Inverter_under_or_over_frequency = i.value();
				break;
			case POWERWARE_REG_02_Bypass_AC_over_voltage:
				m_powerwareState.State.RegState.Bits.Bypass_AC_over_voltage = i.value();
				break;
			case POWERWARE_REG_02_Bypass_AC_under_voltage:
				m_powerwareState.State.RegState.Bits.Bypass_AC_under_voltage = i.value();
				break;
			case POWERWARE_REG_02_Bypass_under_or_over_frequency:
				m_powerwareState.State.RegState.Bits.Bypass_under_or_over_frequency = i.value();
				break;
			case POWERWARE_REG_02_Input_AC_over_voltage:
				m_powerwareState.State.RegState.Bits.Input_AC_over_voltage = i.value();
				break;
			case POWERWARE_REG_02_Input_AC_under_voltage:
				m_powerwareState.State.RegState.Bits.Input_AC_under_voltage = i.value();
				break;
			case POWERWARE_REG_02_Input_under_or_over_frequency:
				m_powerwareState.State.RegState.Bits.Input_under_or_over_frequency = i.value();
				break;
			case POWERWARE_REG_02_Output_AC_over_voltage:
				m_powerwareState.State.RegState.Bits.Output_AC_over_voltage = i.value();
				break;
			case POWERWARE_REG_02_Output_AC_under_voltage:
				m_powerwareState.State.RegState.Bits.Output_AC_under_voltage = i.value();
				break;
			case POWERWARE_REG_02_Output_under_or_over_frequency:
				m_powerwareState.State.RegState.Bits.Output_under_or_over_frequency = i.value();
				break;
			case POWERWARE_REG_02_Remote_emergency_power_off:
				m_powerwareState.State.RegState.Bits.Remote_emergency_power_off = i.value();
				break;
			case POWERWARE_REG_02_Building_Alarm_6:
				m_powerwareState.State.RegState.Bits.Building_Alarm_6 = i.value();
				break;
			case POWERWARE_REG_02_Building_Alarm_5:
				m_powerwareState.State.RegState.Bits.Building_Alarm_5 = i.value();
				break;
			case POWERWARE_REG_02_Building_Alarm_4:
				m_powerwareState.State.RegState.Bits.Building_Alarm_4 = i.value();
				break;
			case POWERWARE_REG_02_Building_Alarm_3:
				m_powerwareState.State.RegState.Bits.Building_Alarm_3 = i.value();
				break;
			case POWERWARE_REG_02_Building_Alarm_2:
				m_powerwareState.State.RegState.Bits.Building_Alarm_2 = i.value();
				break;
			case POWERWARE_REG_02_Building_Alarm_1:
				m_powerwareState.State.RegState.Bits.Building_Alarm_1 = i.value();
				break;
			case POWERWARE_REG_02_Charger_logic_power_fail:
				m_powerwareState.State.RegState.Bits.Charger_logic_power_fail = i.value();
				break;
			case POWERWARE_REG_02_Charger_over_voltage_or_current:
				m_powerwareState.State.RegState.Bits.Charger_over_voltage_or_current = i.value();
				break;
			case POWERWARE_REG_02_Inverter_over_temperature:
				m_powerwareState.State.RegState.Bits.Inverter_over_temperature = i.value();
				break;
			case POWERWARE_REG_02_Output_overload:
				m_powerwareState.State.RegState.Bits.Output_overload = i.value();
				break;
			case POWERWARE_REG_02_Inverter_output_over_current:
				m_powerwareState.State.RegState.Bits.Inverter_output_over_current = i.value();
				break;
			case POWERWARE_REG_02_DC_link_over_voltage:
				m_powerwareState.State.RegState.Bits.DC_link_over_voltage = i.value();
				break;
			case POWERWARE_REG_02_DC_link_under_voltage:
				m_powerwareState.State.RegState.Bits.DC_link_under_voltage = i.value();
				break;
			case POWERWARE_REG_02_Rectifier_failed:
				m_powerwareState.State.RegState.Bits.Rectifier_failed = i.value();
				break;
			case POWERWARE_REG_02_Inverter_fault:
				m_powerwareState.State.RegState.Bits.Inverter_fault = i.value();
				break;
			case POWERWARE_REG_02_Battery_contactor_fail:
				m_powerwareState.State.RegState.Bits.Battery_contactor_fail = i.value();
				break;
			case POWERWARE_REG_02_Bypass_breaker_fail:
				m_powerwareState.State.RegState.Bits.Bypass_breaker_fail = i.value();
				break;
			case POWERWARE_REG_02_Static_switch_failure:
				m_powerwareState.State.RegState.Bits.Static_switch_failure = i.value();
				break;
			case POWERWARE_REG_02_Battery_current_limit:
				m_powerwareState.State.RegState.Bits.Battery_current_limit = i.value();
				break;
			case POWERWARE_REG_02_Output_current_over_100:
				m_powerwareState.State.RegState.Bits.Output_current_over_100 = i.value();
				break;
			case POWERWARE_REG_02_Shutdown_imminent:
				m_powerwareState.State.RegState.Bits.Shutdown_imminent = i.value();
				break;
			case POWERWARE_REG_02_Battery_low:
				m_powerwareState.State.RegState.Bits.Battery_low = i.value();
				break;
			case POWERWARE_REG_02_Utility_fail:
				m_powerwareState.State.RegState.Bits.Utility_fail = i.value();
				break;
			case POWERWARE_REG_02_Battery_DC_over_voltage:
				m_powerwareState.State.RegState.Bits.Battery_DC_over_voltage = i.value();
				break;
			case POWERWARE_REG_02_Power_supply_failure:
				m_powerwareState.State.RegState.Bits.Power_supply_failure = i.value();
				break;
			case POWERWARE_REG_02_Rectifier_current_over_125:
				m_powerwareState.State.RegState.Bits.Rectifier_current_over_125 = i.value();
				break;
			case POWERWARE_REG_02_Bypass_not_available:
				m_powerwareState.State.RegState.Bits.Bypass_not_available = i.value();
				break;
			case POWERWARE_REG_02_Battery_contactor_open:
				m_powerwareState.State.RegState.Bits.Battery_contactor_open = i.value();
				break;
			case POWERWARE_REG_02_Inverter_contactor_open:
				m_powerwareState.State.RegState.Bits.Inverter_contactor_open = i.value();
				break;
			case POWERWARE_REG_02_Battery_totally_discharged:
				m_powerwareState.State.RegState.Bits.Battery_totally_discharged = i.value();
				break;
			case POWERWARE_REG_02_Loss_of_redundancy:
				m_powerwareState.State.RegState.Bits.Loss_of_redundancy = i.value();
				break;
			case POWERWARE_REG_02_Output_breaker_open:
				m_powerwareState.State.RegState.Bits.Output_breaker_open = i.value();
				break;
			case POWERWARE_REG_02_Check_battery_flag:
				m_powerwareState.State.RegState.Bits.Check_battery_flag = i.value();
				break;
			case POWERWARE_REG_02_Greater_than_106_overload_on_phase_A:
				m_powerwareState.State.RegState.Bits.Greater_than_106_overload_on_phase_A = i.value();
				break;
			case POWERWARE_REG_02_Greater_than_106_overload_on_phase_B:
				m_powerwareState.State.RegState.Bits.Greater_than_106_overload_on_phase_B = i.value();
				break;
			case POWERWARE_REG_02_Greater_than_106_overload_on_phase_C:
				m_powerwareState.State.RegState.Bits.Greater_than_106_overload_on_phase_C = i.value();
				break;
			case POWERWARE_REG_02_Greater_than_125_overload_on_phase_A:
				m_powerwareState.State.RegState.Bits.Greater_than_125_overload_on_phase_A = i.value();
				break;
			case POWERWARE_REG_02_Greater_than_125_overload_on_phase_B:
				m_powerwareState.State.RegState.Bits.Greater_than_125_overload_on_phase_B = i.value();
				break;
			case POWERWARE_REG_02_Greater_than_125_overload_on_phase_C:
				m_powerwareState.State.RegState.Bits.Greater_than_125_overload_on_phase_C = i.value();
				break;
			case POWERWARE_REG_02_Greater_than_150_overload_on_phase_A:
				m_powerwareState.State.RegState.Bits.Greater_than_150_overload_on_phase_A = i.value();
				break;
			case POWERWARE_REG_02_Greater_than_150_overload_on_phase_B:
				m_powerwareState.State.RegState.Bits.Greater_than_150_overload_on_phase_B = i.value();
				break;
			case POWERWARE_REG_02_Greater_than_150_overload_on_phase_C:
				m_powerwareState.State.RegState.Bits.Greater_than_150_overload_on_phase_C = i.value();
				break;
			case POWERWARE_REG_02_UPS_On_Battery:
				m_powerwareState.State.RegState.Bits.UPS_On_Battery = i.value();
				break;
			case POWERWARE_REG_02_UPS_On_Bypass:
				m_powerwareState.State.RegState.Bits.UPS_On_Bypass = i.value();
				break;
			case POWERWARE_REG_02_Load_Dumped_Load_Power_Off:
				m_powerwareState.State.RegState.Bits.Load_Dumped_Load_Power_Off = i.value();
				break;
			case POWERWARE_REG_02_Low_Battery_Shutdown:
				m_powerwareState.State.RegState.Bits.Low_Battery_Shutdown = i.value();
				break;
			case POWERWARE_REG_02_Bypass_Failure:
				m_powerwareState.State.RegState.Bits.Bypass_Failure = i.value();
				break;
			case POWERWARE_REG_02_Battery_Test_failed:
				m_powerwareState.State.RegState.Bits.Battery_Test_failed = i.value();
				break;
			case POWERWARE_REG_02_Fuse_Failure:
				m_powerwareState.State.RegState.Bits.Fuse_Failure = i.value();
				break;
			case POWERWARE_REG_02_Fan_Failure:
				m_powerwareState.State.RegState.Bits.Fan_Failure = i.value();
				break;
			case POWERWARE_REG_02_Site_Wiring_Fault:
				m_powerwareState.State.RegState.Bits.Site_Wiring_Fault = i.value();
				break;
			case POWERWARE_REG_02_Batteries_Disconnected:
				m_powerwareState.State.RegState.Bits.Batteries_Disconnected = i.value();
				break;
			case POWERWARE_REG_02_Input_Breaker_Failed:
				m_powerwareState.State.RegState.Bits.Input_Breaker_Failed = i.value();
				break;
		}
	}

	if(m_status == DEVICE_OK && isInfoCollected())
	{
		m_powerwareState.Updated = QDateTime::currentDateTime();
	}
	else
	{
		m_powerwareState.Updated = QDateTime();
	}
}

//------------------------------------------------------------------------------
void POWERWARE_MODBUS_DEVICE::setRegisters04()
{
	QMutableMapIterator<quint32, ModbusRegister> i(regs04);
	while(i.hasNext())
	{
		i.next();

		switch(i.key())
		{
			case POWERWARE_REG_04_INPUT_CURRENT_PHASE_A:
				m_powerwareState.State.RegInputCurrentPhaseA._Data = i.value();
				break;
			case POWERWARE_REG_04_INPUT_CURRENT_PHASE_B:
				m_powerwareState.State.RegInputCurrentPhaseB._Data = i.value();
				break;
			case POWERWARE_REG_04_INPUT_CURRENT_PHASE_C:
				m_powerwareState.State.RegInputCurrentPhaseC._Data = i.value();
				break;
			case POWERWARE_REG_04_OUTPUT_TRUE_POWER:
				m_powerwareState.State.RegOutputTruePower._Data = i.value();
				break;
			case POWERWARE_REG_04_INPUT_TRUE_POWER:
				m_powerwareState.State.RegInputTruePower._Data = i.value();
				break;
			case POWERWARE_REG_04_OUTPUT_APPARENT_POWER:
//				m_powerwareState.State.Reg._Data = i.value();
				break;
			case POWERWARE_REG_04_INPUT_APPARENT_POWER:
//				m_powerwareState.State.Reg._Data = i.value();
				break;
			case POWERWARE_REG_04_OUTPUT_POWER_FACTOR:
//				m_powerwareState.State.Reg._Data = i.value();
				break;
			case POWERWARE_REG_04_INPUT_POWER_FACTOR:
//				m_powerwareState.State.Reg._Data = i.value();
				break;
			case POWERWARE_REG_04_OUTPUT_FREQUENCY:
				m_powerwareState.State.RegOutputFrequency._Data = i.value();
				break;
			case POWERWARE_REG_04_INPUT_FREQUENCY:
				m_powerwareState.State.RegInputFrequency._Data = i.value();
				break;
			case POWERWARE_REG_04_BYPASS_FREQUENCY:
				m_powerwareState.State.RegBypassFrequency._Data = i.value();
				break;
			case POWERWARE_REG_04_BATTERY_CURRENT:
				m_powerwareState.State.RegBatteryCurrent._Data = i.value();
				break;
			case POWERWARE_REG_04_BATTERY_VOLTAGE:
				m_powerwareState.State.RegBatteryVoltage._Data = i.value();
				break;
			case POWERWARE_REG_04_BATTERY_LEFT:
				m_powerwareState.State.RegBatteryLeft._Data = i.value();
				break;
			case POWERWARE_REG_04_BATTERY_TIME_REMAINING:
				m_powerwareState.State.RegTimeRemaining._Data = i.value();
				break;
			case POWERWARE_REG_04_BYPASS_VOLTS_PHASE_A:
				m_powerwareState.State.RegBypassVoltagePhaseA._Data = i.value();
				break;
			case POWERWARE_REG_04_BYPASS_VOLTS_PHASE_B:
				m_powerwareState.State.RegBypassVoltagePhaseB._Data = i.value();
				break;
			case POWERWARE_REG_04_BYPASS_VOLTS_PHASE_C:
				m_powerwareState.State.RegBypassVoltagePhaseC._Data = i.value();
				break;
			case POWERWARE_REG_04_INPUT_VOLTS_PHASE_A:
				m_powerwareState.State.RegInputVoltagePhaseA._Data = i.value();
				break;
			case POWERWARE_REG_04_INPUT_VOLTS_PHASE_B:
				m_powerwareState.State.RegInputVoltagePhaseB._Data = i.value();
				break;
			case POWERWARE_REG_04_INPUT_VOLTS_PHASE_C:
				m_powerwareState.State.RegInputVoltagePhaseC._Data = i.value();
				break;
			case POWERWARE_REG_04_LOAD_CURRENT_PHASE_A:
				m_powerwareState.State.RegLoadCurrentPhaseA._Data = i.value();
				break;
			case POWERWARE_REG_04_LOAD_CURRENT_PHASE_B:
				m_powerwareState.State.RegLoadCurrentPhaseB._Data = i.value();
				break;
			case POWERWARE_REG_04_LOAD_CURRENT_PHASE_C:
				m_powerwareState.State.RegLoadCurrentPhaseC._Data = i.value();
				break;
			case POWERWARE_REG_04_LOAD_CURRENT_PHASE_A_BAR_CHART:
//				m_powerwareState.State.Reg._Data = i.value();
				break;
			case POWERWARE_REG_04_LOAD_CURRENT_PHASE_B_BAR_CHART:
//				m_powerwareState.State.Reg._Data = i.value();
				break;
			case POWERWARE_REG_04_LOAD_CURRENT_PHASE_C_BAR_CHART:
//				m_powerwareState.State.Reg._Data = i.value();
				break;
			case POWERWARE_REG_04_OUTPUT_VOLTS_A:
				m_powerwareState.State.RegOutputVoltagePhaseA._Data = i.value();
				break;
			case POWERWARE_REG_04_OUTPUT_VOLTS_B:
				m_powerwareState.State.RegOutputVoltagePhaseB._Data = i.value();
				break;
			case POWERWARE_REG_04_OUTPUT_VOLTS_C:
				m_powerwareState.State.RegOutputVoltagePhaseC._Data = i.value();
				break;
		}
	}

	if(m_status == DEVICE_OK && isInfoCollected())
	{
		m_powerwareState.Updated = QDateTime::currentDateTime();
	}
	else
	{
		m_powerwareState.Updated = QDateTime();
	}
}

//------------------------------------------------------------------------------
void POWERWARE_MODBUS_DEVICE::updateRegs02()
{
//	qDebug() << regs02.toString();

	if(!m_connected)
		regs02.reset();

	checkDeviceState();
	setRegisters02();

	m_needRefresh02 = false;

	if(parent)
		parent->onChangedDeviceState();
}

//------------------------------------------------------------------------------
void POWERWARE_MODBUS_DEVICE::updateRegs04()
{
//	qDebug() << regs04.toString();

	if(!m_connected)
		regs04.reset();

	checkDeviceState();
	setRegisters04();

	m_needRefresh04 = false;

	if(parent)
		parent->onChangedDeviceState();
}

//------------------------------------------------------------------------------
bool POWERWARE_MODBUS_DEVICE::isActualState()
{
	qint64 timeUpdated = TimeUndefined;

	if(!m_powerwareState.Updated.isNull())
		timeUpdated = timeDiff(m_powerwareState.Updated);

	return ((timeUpdated <= 10000) && (timeUpdated >= -10000) && (timeUpdated != TimeUndefined));
}

//------------------------------------------------------------------------------
bool POWERWARE_MODBUS_DEVICE::isInfoCollected()
{
	return (
		regs02[POWERWARE_REG_02_System_Normal].isInitialized() &&
		regs04[POWERWARE_REG_04_BATTERY_LEFT].isInitialized()
	);

	return false;
}

//------------------------------------------------------------------------------
