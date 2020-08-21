#ifndef _UPS_SNMP_APC_STRUCT_H_
#define _UPS_SNMP_APC_STRUCT_H_

#include <QDateTime>

#define UPS_SNMP_APC_DEFAULT		0
#define UPS_SNMP_APC_MGE_GALAXY_3500	1
#define UPS_SNMP_APC_MGE_GALAXY_5500	2


// UpsApcState structure
typedef struct tagUpsApcState
{
	struct UpsApcState
	{
		union ApcStateReg
		{
			struct _Bits
			{
				unsigned short On_Battery:1;
				unsigned short On_Bypass:1;
				unsigned short System_Normal:1;
				unsigned short Ups_Off:1;
				unsigned short Inverter_AC_over_voltage:1;
				unsigned short Inverter_AC_under_voltage:1;
				unsigned short Inverter_under_or_over_frequency:1;
				unsigned short Bypass_AC_over_voltage:1;
				unsigned short Bypass_AC_under_voltage:1;
				unsigned short Bypass_under_or_over_frequency:1;
				unsigned short Input_AC_over_voltage:1;
				unsigned short Input_AC_under_voltage:1;
				unsigned short Input_under_or_over_frequency:1;
				unsigned short Output_AC_over_voltage:1;
				unsigned short Output_AC_under_voltage:1;
				unsigned short Output_under_or_over_frequency:1;
				unsigned short Remote_emergency_power_off:1;
				unsigned short Building_Alarm_6:1;
				unsigned short Building_Alarm_5:1;
				unsigned short Building_Alarm_4:1;
				unsigned short Building_Alarm_3:1;
				unsigned short Building_Alarm_2:1;
				unsigned short Building_Alarm_1:1;
				unsigned short Charger_logic_power_fail:1;
				unsigned short Charger_over_voltage_or_current:1;
				unsigned short Inverter_over_temperature:1;
				unsigned short Output_overload:1;
				unsigned short Inverter_output_over_current:1;
				unsigned short DC_link_over_voltage:1;
				unsigned short DC_link_under_voltage:1;
				unsigned short Rectifier_failed:1;
				unsigned short Inverter_fault:1;
				unsigned short Battery_contactor_fail:1;
				unsigned short Bypass_breaker_fail:1;
				unsigned short Static_switch_failure:1;
				unsigned short Battery_current_limit:1;
				unsigned short Output_current_over_100:1;
				unsigned short Shutdown_imminent:1;
				unsigned short Battery_low:1;
				unsigned short Utility_fail:1;
				unsigned short Battery_DC_over_voltage:1;
				unsigned short Power_supply_failure:1;
				unsigned short Rectifier_current_over_125:1;
				unsigned short Bypass_not_available:1;
				unsigned short Battery_contactor_open:1;
				unsigned short Inverter_contactor_open:1;
				unsigned short Battery_totally_discharged:1;
				unsigned short Loss_of_redundancy:1;
				unsigned short Output_breaker_open:1;
				unsigned short Check_battery_flag:1;
				unsigned short Greater_than_106_overload_on_phase_A:1;
				unsigned short Greater_than_106_overload_on_phase_B:1;
				unsigned short Greater_than_106_overload_on_phase_C:1;
				unsigned short Greater_than_125_overload_on_phase_A:1;
				unsigned short Greater_than_125_overload_on_phase_B:1;
				unsigned short Greater_than_125_overload_on_phase_C:1;
				unsigned short Greater_than_150_overload_on_phase_A:1;
				unsigned short Greater_than_150_overload_on_phase_B:1;
				unsigned short Greater_than_150_overload_on_phase_C:1;
				unsigned short UPS_On_Battery:1;
				unsigned short UPS_On_Bypass:1;
				unsigned short Load_Dumped_Load_Power_Off:1;
				unsigned short Low_Battery_Shutdown:1;
				unsigned short Bypass_Failure:1;
				unsigned short Battery_Test_failed:1;
				unsigned short Fuse_Failure:1;
				unsigned short Fan_Failure:1;
				unsigned short Site_Wiring_Fault:1;
				unsigned short Batteries_Disconnected:1;
				unsigned short Input_Breaker_Failed:1;
			} Bits;
//			unsigned short	_Data;
		} RegState;

		union ApcBatteryLeft
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegBatteryLeft;

		union ApcTimeRemaining
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegTimeRemaining;

		union ApcInputTruePower
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 2);
			}
		} RegInputTruePower;

		union ApcOutputTruePower
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 2);
			}
		} RegOutputTruePower;

		union ApcInputVoltagePhase
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegInputVoltagePhaseA, RegInputVoltagePhaseB, RegInputVoltagePhaseC;

		union ApcBypassVoltagePhase
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegBypassVoltagePhaseA, RegBypassVoltagePhaseB, RegBypassVoltagePhaseC;

		union ApcOutputVoltagePhase
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegOutputVoltagePhaseA, RegOutputVoltagePhaseB, RegOutputVoltagePhaseC;

		union ApcInputFrequency
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegInputFrequency;

		union ApcBypassFrequency
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegBypassFrequency;

		union ApcOutputFrequency
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegOutputFrequency;

		union ApcBatteryVoltage
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegBatteryVoltage;

		union ApcBatteryCurrent
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegBatteryCurrent;

		union ApcInputCurrentPhase
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegInputCurrentPhaseA, RegInputCurrentPhaseB, RegInputCurrentPhaseC;

		union ApcLoadCurrentPhase
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegLoadCurrentPhaseA, RegLoadCurrentPhaseB, RegLoadCurrentPhaseC;

		QDateTime	Updated;

		UpsApcState() : Updated()
		{
			memset(&RegState, 0, sizeof(RegState));
			RegBatteryLeft._Data = 0;
			RegTimeRemaining._Data = 0;
			RegInputTruePower._Data = 0;
			RegOutputTruePower._Data = 0;
			RegInputVoltagePhaseA._Data = 0;
			RegInputVoltagePhaseB._Data = 0;
			RegInputVoltagePhaseC._Data = 0;
			RegBypassVoltagePhaseA._Data = 0;
			RegBypassVoltagePhaseB._Data = 0;
			RegBypassVoltagePhaseC._Data = 0;
			RegOutputVoltagePhaseA._Data = 0;
			RegOutputVoltagePhaseB._Data = 0;
			RegOutputVoltagePhaseC._Data = 0;
			RegInputFrequency._Data = 0;
			RegBypassFrequency._Data = 0;
			RegOutputFrequency._Data = 0;
			RegBatteryVoltage._Data = 0;
			RegBatteryCurrent._Data = 0;
			RegInputCurrentPhaseA._Data = 0;
			RegInputCurrentPhaseB._Data = 0;
			RegInputCurrentPhaseC._Data = 0;
			RegLoadCurrentPhaseA._Data = 0;
			RegLoadCurrentPhaseB._Data = 0;
			RegLoadCurrentPhaseC._Data = 0;
		}

	} State;

	QDateTime Updated; // Structure updated time, milliseconds left

	tagUpsApcState() : Updated()
	{
	}
} UpsApcState;


#endif // _UPS_SNMP_APC_STRUCT_H_
