#include "../common/logger.h"
#include "globalvar.h"
#include "ups_modbus_service.h"
#include "ups_modbus_pww_device.h"

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::updateState()
{
	updatePortState();
	updateUpsState(0);
	updateUpsState(1);
	updateCommonState();

	emit sigState(bUpsState);
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::updatePortState()
{
	if(!m_portState[MODBUS_PORT_1].State.Bits.Opened)
		bUpsState["port1"] = ELEM_NOT;
	else if(m_portState[MODBUS_PORT_1].State.Bits.NoData)
		bUpsState["port1"] = ELEM_AVAR;
	else if(m_portState[MODBUS_PORT_1].State.Bits.BadData)
		bUpsState["port1"] = ELEM_ERROR;
	else
		bUpsState["port1"] = ELEM_NORMA;

	if(!m_portState[MODBUS_PORT_2].State.Bits.Opened)
		bUpsState["port2"] = ELEM_NOT;
	else if(m_portState[MODBUS_PORT_2].State.Bits.NoData)
		bUpsState["port2"] = ELEM_AVAR;
	else if(m_portState[MODBUS_PORT_2].State.Bits.BadData)
		bUpsState["port2"] = ELEM_ERROR;
	else
		bUpsState["port2"] = ELEM_NORMA;

	if(bUpsState["port1"] == ELEM_NOT)
		bUpsState["comm1"] = ELEM_AVAR;
	else
		bUpsState["comm1"] = ELEM_NORMA;

	if(bUpsState["port2"] == ELEM_NOT)
		bUpsState["comm2"] = ELEM_AVAR;
	else
		bUpsState["comm2"] = ELEM_NORMA;

	bool work1 = powerware[0]->isActualState();
	bool work2 = powerware[1]->isActualState();
//	bool info1 = powerware[0]->isInfoCollected();
//	bool info2 = powerware[1]->isInfoCollected();

	if(bUpsState["port1"] == ELEM_NOT)
		bUpsState["device1"] = ELEM_NOT;
	else if(!work1 || bUpsState["port1"] == ELEM_AVAR)
		bUpsState["device1"] = ELEM_AVAR;
	else
		bUpsState["device1"] = ELEM_NORMA;

	if(bUpsState["port2"] == ELEM_NOT)
		bUpsState["device2"] = ELEM_NOT;
	else if(!work2 || bUpsState["port2"] == ELEM_AVAR)
		bUpsState["device2"] = ELEM_AVAR;
	else
		bUpsState["device2"] = ELEM_NORMA;

	bUpsState["line1"] = bUpsState["line2"] = bUpsState["port1"];
	bUpsState["line3"] = bUpsState["line4"] = bUpsState["port2"];

//obSost Channel
	if(((bUpsState["port1"] == ELEM_AVAR || bUpsState["port1"] == ELEM_NOT) && (bUpsState["port2"] == ELEM_AVAR || bUpsState["port2"] == ELEM_NOT)) ||
		(bUpsState["device1"] == ELEM_AVAR && bUpsState["device2"] == ELEM_AVAR))
		bUpsState["channel"] = ELEM_AVAR;
	else if(bUpsState["port1"] == ELEM_NORMA && bUpsState["port2"] == ELEM_NORMA &&
		bUpsState["device1"] == ELEM_NORMA && bUpsState["device2"] == ELEM_NORMA)
		bUpsState["channel"] = ELEM_NORMA;
	else
		bUpsState["channel"] = ELEM_ERROR;
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::updateCommonState()
{
}

// ------------------------------------------------------------------
void UPS_MODBUS_SERVICE::updateUpsState(quint32 n_ups)
{
	Q_UNUSED(n_ups);
/*
	PowerwareState & state = powerware[n_ups]->state();
	bool work = powerware[n_ups]->isActualState();

	QString N = QString("ups%1@").arg(n_ups + 1);

//02
	if(work && state.State.RegState.Bits.On_Battery)
		bUpsState[N + "ON_BATTERY"] = ELEM_AVAR;
	else
		bUpsState[N + "ON_BATTERY"] = ELEM_NOT;

	if(work && state.State.RegState.Bits.Ups_Off)
		bUpsState[N + "STATUS_UPS_OFF"] = ELEM_AVAR;
	else
		bUpsState[N + "STATUS_UPS_OFF"] = ELEM_NOT;

	if(work && state.State.RegState.Bits.On_Bypass)
		bUpsState[N + "STATUS_BYPASS"] = ELEM_AVAR;
	else
		bUpsState[N + "STATUS_BYPASS"] = ELEM_NOT;

	if(work && state.State.RegState.Bits.On_Battery)
		bUpsState[N + "STATUS_ON_BATTERY"] = ELEM_AVAR;
	else
		bUpsState[N + "STATUS_ON_BATTERY"] = ELEM_NOT;

	if(work && state.State.RegState.Bits.System_Normal)
		bUpsState[N + "STATUS_NORMAL"] = ELEM_AVAR;
	else
		bUpsState[N + "STATUS_NORMAL"] = ELEM_NOT;

	if(!work)
		bUpsState[N + "STATUS"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Ups_Off)
		bUpsState[N + "STATUS"].setText("ОТКЛЮЧЕН") = ELEM_NORMA;
	else if(state.State.RegState.Bits.On_Bypass)
		bUpsState[N + "STATUS"].setText("БАЙПАС") = ELEM_NORMA;
	else if(state.State.RegState.Bits.On_Battery)
		bUpsState[N + "STATUS"].setText("НА БАТАРЕЯХ") = ELEM_NORMA;
	else if(state.State.RegState.Bits.System_Normal)
		bUpsState[N + "STATUS"].setText("НОРМА") = ELEM_NORMA;
	else
		bUpsState[N + "STATUS"].setText("---") = ELEM_ERROR;

	if(!work)
		bUpsState[N + "Input_AC_voltage"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Input_AC_over_voltage)
		bUpsState[N + "Input_AC_voltage"].setText("ВЫШЕ НОРМЫ") = ELEM_AVAR;
	else if(state.State.RegState.Bits.Input_AC_under_voltage)
		bUpsState[N + "Input_AC_voltage"].setText("НИЖЕ НОРМЫ") = ELEM_AVAR;
	else
		bUpsState[N + "Input_AC_voltage"].setText("НОРМА") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Input_frequency"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Input_under_or_over_frequency)
		bUpsState[N + "Input_frequency"].setText("НЕ НОРМА") = ELEM_AVAR;
	else
		bUpsState[N + "Input_frequency"].setText("НОРМА") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Inverter_AC_voltage"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Inverter_AC_over_voltage)
		bUpsState[N + "Inverter_AC_voltage"].setText("ВЫШЕ НОРМЫ") = ELEM_AVAR;
	else if(state.State.RegState.Bits.Inverter_AC_under_voltage)
		bUpsState[N + "Inverter_AC_voltage"].setText("НИЖЕ НОРМЫ") = ELEM_AVAR;
	else
		bUpsState[N + "Inverter_AC_voltage"].setText("НОРМА") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Inverter_frequency"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Inverter_under_or_over_frequency)
		bUpsState[N + "Inverter_frequency"].setText("НЕ НОРМА") = ELEM_AVAR;
	else
		bUpsState[N + "Inverter_frequency"].setText("НОРМА") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Bypass_AC_voltage"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Bypass_AC_over_voltage)
		bUpsState[N + "Bypass_AC_voltage"].setText("ВЫШЕ НОРМЫ") = ELEM_AVAR;
	else if(state.State.RegState.Bits.Bypass_AC_under_voltage)
		bUpsState[N + "Bypass_AC_voltage"].setText("НИЖЕ НОРМЫ") = ELEM_AVAR;
	else
		bUpsState[N + "Bypass_AC_voltage"].setText("НОРМА") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Bypass_frequency"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Bypass_under_or_over_frequency)
		bUpsState[N + "Bypass_frequency"].setText("НЕ НОРМА") = ELEM_AVAR;
	else
		bUpsState[N + "Bypass_frequency"].setText("НОРМА") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Output_AC_voltage"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Output_AC_over_voltage)
		bUpsState[N + "Output_AC_voltage"].setText("ВЫШЕ НОРМЫ") = ELEM_AVAR;
	else if(state.State.RegState.Bits.Output_AC_under_voltage)
		bUpsState[N + "Output_AC_voltage"].setText("НИЖЕ НОРМЫ") = ELEM_AVAR;
	else
		bUpsState[N + "Output_AC_voltage"].setText("НОРМА") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Output_frequency"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Output_under_or_over_frequency)
		bUpsState[N + "Output_frequency"].setText("НЕ НОРМА") = ELEM_AVAR;
	else
		bUpsState[N + "Output_frequency"].setText("НОРМА") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "DC_link_voltage"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.DC_link_over_voltage)
		bUpsState[N + "DC_link_voltage"].setText("ВЫШЕ НОРМЫ") = ELEM_AVAR;
	else if(state.State.RegState.Bits.DC_link_under_voltage)
		bUpsState[N + "DC_link_voltage"].setText("НИЖЕ НОРМЫ") = ELEM_AVAR;
	else
		bUpsState[N + "DC_link_voltage"].setText("НОРМА") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Output_overload"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Output_overload)
		bUpsState[N + "Output_overload"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Output_overload"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Output_current_over_100"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Output_current_over_100)
		bUpsState[N + "Output_current_over_100"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Output_current_over_100"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Battery_low"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Battery_low)
		bUpsState[N + "Battery_low"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Battery_low"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Power_supply_failure"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Power_supply_failure)
		bUpsState[N + "Power_supply_failure"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Power_supply_failure"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Rectifier_failed"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Rectifier_failed)
		bUpsState[N + "Rectifier_failed"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Rectifier_failed"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Rectifier_current_over_125"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Rectifier_current_over_125)
		bUpsState[N + "Rectifier_current_over_125"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Rectifier_current_over_125"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Inverter_fault"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Inverter_fault)
		bUpsState[N + "Inverter_fault"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Inverter_fault"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Inverter_over_temperature"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Inverter_over_temperature)
		bUpsState[N + "Inverter_over_temperature"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Inverter_over_temperature"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Inverter_output_over_current"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Inverter_output_over_current)
		bUpsState[N + "Inverter_output_over_current"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Inverter_output_over_current"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Charger_logic_power_fail"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Charger_logic_power_fail)
		bUpsState[N + "Charger_logic_power_fail"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Charger_logic_power_fail"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Charger_over_voltage_or_current"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Charger_over_voltage_or_current)
		bUpsState[N + "Charger_over_voltage_or_current"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Charger_over_voltage_or_current"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Battery_contactor_fail"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Battery_contactor_fail)
		bUpsState[N + "Battery_contactor_fail"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Battery_contactor_fail"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Bypass_breaker_fail"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Bypass_breaker_fail)
		bUpsState[N + "Bypass_breaker_fail"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Bypass_breaker_fail"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Battery_current_limit"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Battery_current_limit)
		bUpsState[N + "Battery_current_limit"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Battery_current_limit"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Battery_DC_voltage"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Battery_DC_over_voltage)
		bUpsState[N + "Battery_DC_voltage"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Battery_DC_voltage"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Utility_fail"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Utility_fail)
		bUpsState[N + "Utility_fail"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Utility_fail"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Shutdown_imminent"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Shutdown_imminent)
		bUpsState[N + "Shutdown_imminent"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Shutdown_imminent"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Battery_totally_discharged"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Battery_totally_discharged)
		bUpsState[N + "Battery_totally_discharged"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Battery_totally_discharged"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Check_battery_flag"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Check_battery_flag)
		bUpsState[N + "Check_battery_flag"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Check_battery_flag"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Battery_Test_failed"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Battery_Test_failed)
		bUpsState[N + "Battery_Test_failed"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Battery_Test_failed"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Fuse_Failure"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Fuse_Failure)
		bUpsState[N + "Fuse_Failure"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Fuse_Failure"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Fan_Failure"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Fan_Failure)
		bUpsState[N + "Fan_Failure"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Fan_Failure"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Input_Breaker_Failed"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Input_Breaker_Failed)
		bUpsState[N + "Input_Breaker_Failed"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Input_Breaker_Failed"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Batteries_Disconnected"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Batteries_Disconnected)
		bUpsState[N + "Batteries_Disconnected"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Batteries_Disconnected"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Low_Battery_Shutdown"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Low_Battery_Shutdown)
		bUpsState[N + "Low_Battery_Shutdown"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Low_Battery_Shutdown"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Bypass_Failure"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Bypass_Failure)
		bUpsState[N + "Bypass_Failure"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Bypass_Failure"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Bypass_not_available"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Bypass_not_available)
		bUpsState[N + "Bypass_not_available"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Bypass_not_available"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Remote_emergency_power_off"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Remote_emergency_power_off)
		bUpsState[N + "Remote_emergency_power_off"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Remote_emergency_power_off"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Site_Wiring_Fault"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Site_Wiring_Fault)
		bUpsState[N + "Site_Wiring_Fault"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Site_Wiring_Fault"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Static_switch_failure"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Static_switch_failure)
		bUpsState[N + "Static_switch_failure"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Static_switch_failure"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "Load_Dumped_Load_Power_Off"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Load_Dumped_Load_Power_Off)
		bUpsState[N + "Load_Dumped_Load_Power_Off"].setText("ДА") = ELEM_AVAR;
	else
		bUpsState[N + "Load_Dumped_Load_Power_Off"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "overload_on_phase_A"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Greater_than_150_overload_on_phase_A)
		bUpsState[N + "overload_on_phase_A"].setText(">150%") = ELEM_AVAR;
	else if(state.State.RegState.Bits.Greater_than_125_overload_on_phase_A)
		bUpsState[N + "overload_on_phase_A"].setText(">125%") = ELEM_ERROR;
	else if(state.State.RegState.Bits.Greater_than_106_overload_on_phase_A)
		bUpsState[N + "overload_on_phase_A"].setText(">106%") = ELEM_ERROR;
	else
		bUpsState[N + "overload_on_phase_A"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "overload_on_phase_B"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Greater_than_150_overload_on_phase_B)
		bUpsState[N + "overload_on_phase_B"].setText(">150%") = ELEM_AVAR;
	else if(state.State.RegState.Bits.Greater_than_125_overload_on_phase_B)
		bUpsState[N + "overload_on_phase_B"].setText(">125%") = ELEM_ERROR;
	else if(state.State.RegState.Bits.Greater_than_106_overload_on_phase_B)
		bUpsState[N + "overload_on_phase_B"].setText(">106%") = ELEM_ERROR;
	else
		bUpsState[N + "overload_on_phase_B"].setText("НЕТ") = ELEM_NORMA;

	if(!work)
		bUpsState[N + "overload_on_phase_C"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Greater_than_150_overload_on_phase_C)
		bUpsState[N + "overload_on_phase_C"].setText(">150%") = ELEM_AVAR;
	else if(state.State.RegState.Bits.Greater_than_125_overload_on_phase_C)
		bUpsState[N + "overload_on_phase_C"].setText(">125%") = ELEM_ERROR;
	else if(state.State.RegState.Bits.Greater_than_106_overload_on_phase_C)
		bUpsState[N + "overload_on_phase_C"].setText(">106%") = ELEM_ERROR;
	else
		bUpsState[N + "overload_on_phase_C"].setText("НЕТ") = ELEM_NORMA;

//04
	if(!work)
		bUpsState[N + "BATTERY_LEFT"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "BATTERY_LEFT"].setText(state.State.RegBatteryLeft.textValue());

		if(state.State.RegState.Bits.Batteries_Disconnected || state.State.RegState.Bits.Battery_totally_discharged)
			bUpsState[N + "BATTERY_LEFT"] = ELEM_AVAR;
		else if(state.State.RegState.Bits.Battery_low)
			bUpsState[N + "BATTERY_LEFT"] = ELEM_ERROR;
		else
			bUpsState[N + "BATTERY_LEFT"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "BATTERY_TIME_REMAINING"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "BATTERY_TIME_REMAINING"].setText(state.State.RegTimeRemaining.textValue());

		if(state.State.RegState.Bits.Batteries_Disconnected || state.State.RegState.Bits.Battery_totally_discharged)
			bUpsState[N + "BATTERY_TIME_REMAINING"] = ELEM_AVAR;
		else if(state.State.RegState.Bits.Battery_low)
			bUpsState[N + "BATTERY_TIME_REMAINING"] = ELEM_ERROR;
		else
			bUpsState[N + "BATTERY_TIME_REMAINING"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "INPUT_TRUE_POWER"].setText(" ") = ELEM_NOT;
	else
		bUpsState[N + "INPUT_TRUE_POWER"].setText(state.State.RegInputTruePower.textValue()) = ELEM_NORMA;

	if(!work)
		bUpsState[N + "OUTPUT_TRUE_POWER"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "OUTPUT_TRUE_POWER"].setText(state.State.RegOutputTruePower.textValue());

		if(state.State.RegState.Bits.Output_overload)
			bUpsState[N + "OUTPUT_TRUE_POWER"] = ELEM_AVAR;
		else
			bUpsState[N + "OUTPUT_TRUE_POWER"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "INPUT_VOLTS_PHASE_A"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "INPUT_VOLTS_PHASE_A"].setText(state.State.RegInputVoltagePhaseA.textValue());

		if(state.State.RegState.Bits.Input_AC_over_voltage || state.State.RegState.Bits.Input_AC_under_voltage)
			bUpsState[N + "INPUT_VOLTS_PHASE_A"] = ELEM_AVAR;
		else
			bUpsState[N + "INPUT_VOLTS_PHASE_A"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "INPUT_VOLTS_PHASE_B"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "INPUT_VOLTS_PHASE_B"].setText(state.State.RegInputVoltagePhaseB.textValue());

		if(state.State.RegState.Bits.Input_AC_over_voltage || state.State.RegState.Bits.Input_AC_under_voltage)
			bUpsState[N + "INPUT_VOLTS_PHASE_B"] = ELEM_AVAR;
		else
			bUpsState[N + "INPUT_VOLTS_PHASE_B"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "INPUT_VOLTS_PHASE_C"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "INPUT_VOLTS_PHASE_C"].setText(state.State.RegInputVoltagePhaseC.textValue());

		if(state.State.RegState.Bits.Input_AC_over_voltage || state.State.RegState.Bits.Input_AC_under_voltage)
			bUpsState[N + "INPUT_VOLTS_PHASE_C"] = ELEM_AVAR;
		else
			bUpsState[N + "INPUT_VOLTS_PHASE_C"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "BYPASS_VOLTS_PHASE_A"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "BYPASS_VOLTS_PHASE_A"].setText(state.State.RegBypassVoltagePhaseA.textValue());

		if(state.State.RegState.Bits.Bypass_AC_over_voltage || state.State.RegState.Bits.Bypass_AC_under_voltage)
			bUpsState[N + "BYPASS_VOLTS_PHASE_A"] = ELEM_AVAR;
		else
			bUpsState[N + "BYPASS_VOLTS_PHASE_A"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "BYPASS_VOLTS_PHASE_B"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "BYPASS_VOLTS_PHASE_B"].setText(state.State.RegBypassVoltagePhaseB.textValue());

		if(state.State.RegState.Bits.Bypass_AC_over_voltage || state.State.RegState.Bits.Bypass_AC_under_voltage)
			bUpsState[N + "BYPASS_VOLTS_PHASE_B"] = ELEM_AVAR;
		else
			bUpsState[N + "BYPASS_VOLTS_PHASE_B"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "BYPASS_VOLTS_PHASE_C"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "BYPASS_VOLTS_PHASE_C"].setText(state.State.RegBypassVoltagePhaseC.textValue());

		if(state.State.RegState.Bits.Bypass_AC_over_voltage || state.State.RegState.Bits.Bypass_AC_under_voltage)
			bUpsState[N + "BYPASS_VOLTS_PHASE_C"] = ELEM_AVAR;
		else
			bUpsState[N + "BYPASS_VOLTS_PHASE_C"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "OUTPUT_VOLTS_PHASE_A"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "OUTPUT_VOLTS_PHASE_A"].setText(state.State.RegOutputVoltagePhaseA.textValue());

		if(state.State.RegState.Bits.Output_AC_over_voltage || state.State.RegState.Bits.Output_AC_under_voltage)
			bUpsState[N + "OUTPUT_VOLTS_PHASE_A"] = ELEM_AVAR;
		else
			bUpsState[N + "OUTPUT_VOLTS_PHASE_A"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "OUTPUT_VOLTS_PHASE_B"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "OUTPUT_VOLTS_PHASE_B"].setText(state.State.RegOutputVoltagePhaseB.textValue());

		if(state.State.RegState.Bits.Output_AC_over_voltage || state.State.RegState.Bits.Output_AC_under_voltage)
			bUpsState[N + "OUTPUT_VOLTS_PHASE_B"] = ELEM_AVAR;
		else
			bUpsState[N + "OUTPUT_VOLTS_PHASE_B"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "OUTPUT_VOLTS_PHASE_C"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "OUTPUT_VOLTS_PHASE_C"].setText(state.State.RegOutputVoltagePhaseC.textValue());

		if(state.State.RegState.Bits.Output_AC_over_voltage || state.State.RegState.Bits.Output_AC_under_voltage)
			bUpsState[N + "OUTPUT_VOLTS_PHASE_C"] = ELEM_AVAR;
		else
			bUpsState[N + "OUTPUT_VOLTS_PHASE_C"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "INPUT_FREQUENCY"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "INPUT_FREQUENCY"].setText(state.State.RegInputFrequency.textValue());

		if(state.State.RegState.Bits.Input_under_or_over_frequency)
			bUpsState[N + "INPUT_FREQUENCY"] = ELEM_AVAR;
		else
			bUpsState[N + "INPUT_FREQUENCY"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "BYPASS_FREQUENCY"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "BYPASS_FREQUENCY"].setText(state.State.RegBypassFrequency.textValue());

		if(state.State.RegState.Bits.Bypass_under_or_over_frequency)
			bUpsState[N + "BYPASS_FREQUENCY"] = ELEM_AVAR;
		else
			bUpsState[N + "BYPASS_FREQUENCY"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "OUTPUT_FREQUENCY"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "OUTPUT_FREQUENCY"].setText(state.State.RegOutputFrequency.textValue());

		if(state.State.RegState.Bits.Output_under_or_over_frequency)
			bUpsState[N + "OUTPUT_FREQUENCY"] = ELEM_AVAR;
		else
			bUpsState[N + "OUTPUT_FREQUENCY"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "BATTERY_VOLTAGE"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "BATTERY_VOLTAGE"].setText(state.State.RegBatteryVoltage.textValue());

		if(state.State.RegState.Bits.Battery_DC_over_voltage)
			bUpsState[N + "BATTERY_VOLTAGE"] = ELEM_AVAR;
		else
			bUpsState[N + "BATTERY_VOLTAGE"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "BATTERY_CURRENT"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "BATTERY_CURRENT"].setText(state.State.RegBatteryCurrent.textValue());

		if(state.State.RegState.Bits.Battery_current_limit)
			bUpsState[N + "BATTERY_CURRENT"] = ELEM_AVAR;
		else
			bUpsState[N + "BATTERY_CURRENT"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "INPUT_CURRENT_PHASE_A"].setText(" ") = ELEM_NOT;
	else
		bUpsState[N + "INPUT_CURRENT_PHASE_A"].setText(state.State.RegInputCurrentPhaseA.textValue()) = ELEM_NORMA;

	if(!work)
		bUpsState[N + "INPUT_CURRENT_PHASE_B"].setText(" ") = ELEM_NOT;
	else
		bUpsState[N + "INPUT_CURRENT_PHASE_B"].setText(state.State.RegInputCurrentPhaseB.textValue()) = ELEM_NORMA;

	if(!work)
		bUpsState[N + "INPUT_CURRENT_PHASE_C"].setText(" ") = ELEM_NOT;
	else
		bUpsState[N + "INPUT_CURRENT_PHASE_C"].setText(state.State.RegInputCurrentPhaseC.textValue()) = ELEM_NORMA;

	if(!work)
		bUpsState[N + "LOAD_CURRENT_PHASE_A"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "LOAD_CURRENT_PHASE_A"].setText(state.State.RegLoadCurrentPhaseA.textValue());

		if(state.State.RegState.Bits.Greater_than_150_overload_on_phase_A)
			bUpsState[N + "LOAD_CURRENT_PHASE_A"] = ELEM_AVAR;
		else if(state.State.RegState.Bits.Greater_than_125_overload_on_phase_A || state.State.RegState.Bits.Greater_than_106_overload_on_phase_A)
			bUpsState[N + "LOAD_CURRENT_PHASE_A"] = ELEM_ERROR;
		else
			bUpsState[N + "LOAD_CURRENT_PHASE_A"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "LOAD_CURRENT_PHASE_B"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "LOAD_CURRENT_PHASE_B"].setText(state.State.RegLoadCurrentPhaseB.textValue());

		if(state.State.RegState.Bits.Greater_than_150_overload_on_phase_B)
			bUpsState[N + "LOAD_CURRENT_PHASE_B"] = ELEM_AVAR;
		else if(state.State.RegState.Bits.Greater_than_125_overload_on_phase_B || state.State.RegState.Bits.Greater_than_106_overload_on_phase_B)
			bUpsState[N + "LOAD_CURRENT_PHASE_B"] = ELEM_ERROR;
		else
			bUpsState[N + "LOAD_CURRENT_PHASE_B"] = ELEM_NORMA;
	}

	if(!work)
		bUpsState[N + "LOAD_CURRENT_PHASE_C"].setText(" ") = ELEM_NOT;
	else
	{
		bUpsState[N + "LOAD_CURRENT_PHASE_C"].setText(state.State.RegLoadCurrentPhaseC.textValue());

		if(state.State.RegState.Bits.Greater_than_150_overload_on_phase_C)
			bUpsState[N + "LOAD_CURRENT_PHASE_C"] = ELEM_AVAR;
		else if(state.State.RegState.Bits.Greater_than_125_overload_on_phase_C || state.State.RegState.Bits.Greater_than_106_overload_on_phase_C)
			bUpsState[N + "LOAD_CURRENT_PHASE_C"] = ELEM_ERROR;
		else
			bUpsState[N + "LOAD_CURRENT_PHASE_C"] = ELEM_NORMA;
	}

//Ups
	if(!work)
		bUpsState[N + "ObSost"] = ELEM_NOT;
	else if(
		state.State.RegState.Bits.Fuse_Failure ||
		state.State.RegState.Bits.Input_Breaker_Failed ||
		state.State.RegState.Bits.Remote_emergency_power_off ||
		state.State.RegState.Bits.Shutdown_imminent ||
		state.State.RegState.Bits.Load_Dumped_Load_Power_Off )
		bUpsState[N + "ObSost"] = ELEM_AVAR;
	else if(
		state.State.RegState.Bits.Power_supply_failure ||
		state.State.RegState.Bits.Rectifier_failed ||
		state.State.RegState.Bits.Inverter_fault ||
		state.State.RegState.Bits.Battery_contactor_fail ||
		state.State.RegState.Bits.Bypass_breaker_fail ||
		state.State.RegState.Bits.Fan_Failure ||
		state.State.RegState.Bits.Inverter_over_temperature ||
		state.State.RegState.Bits.Charger_logic_power_fail ||
		state.State.RegState.Bits.Charger_over_voltage_or_current ||
		state.State.RegState.Bits.Site_Wiring_Fault ||
		state.State.RegState.Bits.Static_switch_failure ||
		state.State.RegState.Bits.Inverter_output_over_current ||
		state.State.RegState.Bits.Rectifier_current_over_125 ||
		state.State.RegState.Bits.DC_link_over_voltage ||
		state.State.RegState.Bits.DC_link_under_voltage )
	{
		if(state.State.RegState.Bits.Bypass_Failure)
			bUpsState[N + "ObSost"] = ELEM_AVAR;
		else
			bUpsState[N + "ObSost"] = ELEM_ERROR;
	}
	else if(state.State.RegState.Bits.Battery_totally_discharged ||
			state.State.RegState.Bits.Battery_current_limit ||
			state.State.RegState.Bits.Check_battery_flag ||
			state.State.RegState.Bits.Battery_Test_failed ||
			state.State.RegState.Bits.Batteries_Disconnected ||
			state.State.RegState.Bits.Low_Battery_Shutdown ||
			state.State.RegState.Bits.Battery_DC_over_voltage )
	{
		if(state.State.RegState.Bits.Bypass_not_available)
			bUpsState[N + "ObSost"] = ELEM_AVAR;
		else
			bUpsState[N + "ObSost"] = ELEM_ERROR;
	}
	else if(state.State.RegState.Bits.Utility_fail ||
			state.State.RegState.Bits.Bypass_Failure ||
			state.State.RegState.Bits.Battery_low ||
			state.State.RegState.Bits.Bypass_not_available ||

			state.State.RegState.Bits.Output_overload ||
			state.State.RegState.Bits.Output_current_over_100 ||

			state.State.RegState.Bits.Greater_than_106_overload_on_phase_A ||
			state.State.RegState.Bits.Greater_than_106_overload_on_phase_B ||
			state.State.RegState.Bits.Greater_than_106_overload_on_phase_C ||
			state.State.RegState.Bits.Greater_than_125_overload_on_phase_A ||
			state.State.RegState.Bits.Greater_than_125_overload_on_phase_B ||
			state.State.RegState.Bits.Greater_than_125_overload_on_phase_C ||
			state.State.RegState.Bits.Greater_than_150_overload_on_phase_A ||
			state.State.RegState.Bits.Greater_than_150_overload_on_phase_B ||
			state.State.RegState.Bits.Greater_than_150_overload_on_phase_C )
	{
		bUpsState[N + "ObSost"] = ELEM_ERROR;
	}
	else
	{
		bUpsState[N + "ObSost"] = ELEM_NORMA;
	}
*/
}

//-----------------------------------------------------------------------------
