#ifndef __DES_DEIF_H__
#define __DES_DEIF_H__

#include "modbus_packet.h"
#include "modbus_device.h"
#include "modbus_service.h"
#include "des_struct.h"
#include "des_service.h"

//-----------------------------------------------------------------------------

#define REG_02_DEIF								0
#define REG_02_GB_position_ON					0
#define REG_02_TB_position_ON					0
#define REG_02_MB_position_ON					1
#define REG_02_Running							3
#define REG_02_Generator_voltage_frequency_OK	4
#define REG_02_Mains_failure					5
#define REG_02_OFF_mode							6
#define REG_02_Block_mode						6
#define REG_02_Manual_mode						7
#define REG_02_Auto_mode_old					8
#define REG_02_SemiAuto_mode					8
#define REG_02_Auto_mode_new					9
#define REG_02_Test_mode						10
#define REG_02_Island							13
#define REG_02_Automatic_mains_failure_AMF		14
#define REG_02_ATS_mode							15
#define REG_02_Load_take_over_LTO				18

//-----------------------------------------------------------------------------

#define REG_04_DEIF									500
#define REG_04_Application_version					500
#define REG_04_UL1_L2_Generator_voltage				501
#define REG_04_UL2_L3_Generator_voltage				502
#define REG_04_UL3_L1_Generator_voltage				503
#define REG_04_UL1_N_Generator_voltage				504
#define REG_04_UL2_N_Generator_voltage				505
#define REG_04_UL3_N_Generator_voltage				506
#define REG_04_fGEN_Generator_freq					507
#define REG_04_fL1GEN_Generator_freq				507
#define REG_04_fL2GEN_Generator_freq				508
#define REG_04_fL3GEN_Generator_freq				509
#define REG_04_PhiL1L2_Generator_phase				510
#define REG_04_PhiL2L3_Generator_phase				511
#define REG_04_PhiL3L1_Generator_phase				512
#define REG_04_IL1_Generator_current				513
#define REG_04_IL2_Generator_current				514
#define REG_04_IL3_Generator_current				515
#define REG_04_PL1_Generator_active_power			516
#define REG_04_PL2_Generator_active_power			517
#define REG_04_PL3_Generator_active_power			518
#define REG_04_PGEN_Generator_total_active_power	519
#define REG_04_QL1_Generator_reactive_power			520
#define REG_04_QL2_Generator_reactive_power			521
#define REG_04_QL3_Generator_reactive_power			522
#define REG_04_QGEN_Generator_total_reactive_power	523
#define REG_04_SL1_Generator_apparent_power			524
#define REG_04_SL2_Generator_apparent_power			525
#define REG_04_SL3_Generator_apparent_power			526
#define REG_04_SGEN_Generator_total_apparent_power	527
#define REG_04_HI_EGEN_Total_energy_counter			536
#define REG_04_LO_EGEN_Total_energy_counter			537
#define REG_04_Generator_cos_phi					538
#define REG_04_UL1_L2_Mains_voltage					539
#define REG_04_UL2_L3_Mains_voltage					540
#define REG_04_UL3_L1_Mains_voltage					541
#define REG_04_UL1_N_Mains_voltage					542
#define REG_04_UL2_N_Mains_voltage					543
#define REG_04_UL3_N_Mains_voltage					544
#define REG_04_fMains_Mains_freq					545
#define REG_04_HI_Running_time_Absolute				554
#define REG_04_LO_Running_time_Absolute				555
#define REG_04_HI_Running_time_Relative				556
#define REG_04_LO_Running_time_Relative				557
#define REG_04_Number_of_alarms						558
#define REG_04_Number_of_unacknowledged_alarms		559
#define REG_04_Number_of_acknowledged_active_alarms	560
#define REG_04_GB_operation_Generator_circuit_breaker_operations_counter	563
#define REG_04_MB_operation_Mains_breaker_operation_counter	564
#define REG_04_Start_attempts_Number_of_start_attempts		566
#define REG_04_USUPPLY_Supply_voltage				567
#define REG_04_Service_timer_1_running_hours		569
#define REG_04_Service_timer_1_days					570
#define REG_04_Service_timer_2_running_hours		571
#define REG_04_Service_timer_2_days					572
#define REG_04_RPM_Running_feedback_RPM				576

//-----------------------------------------------------------------------------

#define TB_VALUE(off,bit) ((off << 16) | bit)
#define TB_OFF(x) ((x >> 16) & 0x0000ffff)
#define TB_BIT(x) (x & 0x0000ffff)
#define TB_LW(x) (TB_OFF(x)*100 + TB_BIT(x))
#define TB_REG(x,y) (x[TB_OFF(y)] & (1 << TB_BIT(y)))
#define TB_REG_BIT(x,y) ((x >> TB_BIT(y)) & 1)
#define TB_REG_SET(x,y) (x[TB_OFF(y)] |= (1 << TB_BIT(y)))
#define TB_REG_BIT_SET(x,y) (x |= (1 << TB_BIT(y)))
#define TB_REG_CLR(x,y) (x[TB_OFF(y)] &= ~(1 << TB_BIT(y)))
#define TB_REG_BIT_CLR(x,y) (x &= ~(1 << TB_BIT(y)))
#define TB_ALARM(x) (TB_OFF(x) * 16 + TB_BIT(x))

#define REG_06_DEIF							1000
#define REG_06_DEIF_STATUS_2				1002
#define REG_06_DEIF_STATUS_3				1003
#define REG_06_DEIF_STATUS_5				1005
#define REG_06_DEIF_STATUS_6				1006
#define REG_06_DEIF_STATUS_10				1010
#define REG_06_DEIF_STATUS_13				1013
#define REG_06_DEIF_STATUS_14				1014
#define REG_06_DEIF_STATUS_15				1015
#define REG_06_DEIF_STATUS_18				1018
#define REG_06_DEIF_STATUS_19				1019
#define REG_06_DEIF_STATUS_20				1020

#define REG_06_Unbalance_current			TB_VALUE(1002,12)
#define REG_06_Unbalance_voltage			TB_VALUE(1002,13)
#define REG_06_Mains_unbalanced_voltage		TB_VALUE(1003,7)
#define REG_06_Phase_seq_error				TB_VALUE(1005,3)
#define REG_06_TB_open_failure				TB_VALUE(1005,4)
#define REG_06_TB_close_failure				TB_VALUE(1005,5)
#define REG_06_TB_pos_failure				TB_VALUE(1005,6)
#define REG_06_GB_open_failure				TB_VALUE(1005,4)
#define REG_06_GB_close_failure				TB_VALUE(1005,5)
#define REG_06_GB_pos_failure				TB_VALUE(1005,6)
#define REG_06_MB_open_failure				TB_VALUE(1005,7)
#define REG_06_MB_close_failure				TB_VALUE(1005,8)
#define REG_06_MB_pos_failure				TB_VALUE(1005,9)
#define REG_06_Close_before_excitation_failure TB_VALUE(1005,10)
#define REG_06_GOVERNOR_regulation_failed	TB_VALUE(1006,0)
#define REG_06_Deload_error					TB_VALUE(1006,1)
#define REG_06_AVR_regulation_failed		TB_VALUE(1006,2)
#define REG_06_Emergency_STOP				TB_VALUE(1010,12)
#define REG_06_Overspeed_1					TB_VALUE(1013,9)
#define REG_06_Overspeed_2					TB_VALUE(1013,10)

#define REG_06_VDO_fuel_level				TB_VALUE(1013,11)
#define REG_06_Crank_failure				TB_VALUE(1013,11)

#define REG_06_Charger_gen					TB_VALUE(1013,12)
#define REG_06_Running_feedback_failure		TB_VALUE(1013,12)

#define REG_06_V_Belt						TB_VALUE(1013,13)
#define REG_06_MPU_wire_failure				TB_VALUE(1013,13)

#define REG_06_Generator_Hz_V_failure		TB_VALUE(1013,14)
#define REG_06_Start_failure				TB_VALUE(1013,15)
#define REG_06_Stop_failure					TB_VALUE(1014,0)
#define REG_06_Underspeed_1					TB_VALUE(1014,5)
#define REG_06_Service_timer_1				TB_VALUE(1015,0)
#define REG_06_Service_timer_2				TB_VALUE(1015,1)
#define REG_06_Stop_coil_wire_break			TB_VALUE(1015,2)
#define REG_06_Internal_comm_failure		TB_VALUE(1015,3)
#define REG_06_Engine_heater_1				TB_VALUE(1015,4)
#define REG_06_Battery_test					TB_VALUE(1015,5)
#define REG_06_Battery_assymmetry_1			TB_VALUE(1015,6)
#define REG_06_Battery_assymmetry_2			TB_VALUE(1015,7)
#define REG_06_Max_ventilation_1			TB_VALUE(1015,8)
#define REG_06_Max_ventilation_2			TB_VALUE(1015,9)
#define REG_06_Blk_swbd_error				TB_VALUE(1015,10)
#define REG_06_Stp_swbd_error				TB_VALUE(1015,11)
#define REG_06_Unit_not_in_auto				TB_VALUE(1015,12)
#define REG_06_Fuel_fill_check				TB_VALUE(1015,13)
#define REG_06_Fuel_pump_logic				TB_VALUE(1015,13)

#define REG_06_Mains_failure				TB_VALUE(1018,0)
#define REG_06_MB_pos_ON					TB_VALUE(1018,1)
#define REG_06_GB_pos_ON					TB_VALUE(1018,4)
#define REG_06_Engine_running				TB_VALUE(1018,6)
#define REG_06_Running_detection_timer_expired	TB_VALUE(1018,7)
#define REG_06_DG_Hz_V_OK_timer_expired		TB_VALUE(1018,8)
#define REG_06_OFF							TB_VALUE(1019,0)
#define REG_06_Manual						TB_VALUE(1019,1)
#define REG_06_Auto							TB_VALUE(1019,3)
#define REG_06_Test							TB_VALUE(1019,4)
#define	REG_06_Island						TB_VALUE(1019,5)
#define REG_06_AMF							TB_VALUE(1019,6)
#define REG_06_Load_take_over				TB_VALUE(1019,10)
#define REG_06_AMF_active					TB_VALUE(1019,15)
#define REG_06_EIC_comm_error				TB_VALUE(1020,0)
#define REG_06_EIC_warning					TB_VALUE(1020,1)
#define REG_06_EIC_shutdown					TB_VALUE(1020,2)
#define REG_06_EIC_overspeed				TB_VALUE(1020,3)
#define REG_06_EIC_coolant_temp_1			TB_VALUE(1020,4)
#define REG_06_EIC_coolant_temp_2			TB_VALUE(1020,5)
#define REG_06_EIC_oil_pressure_1			TB_VALUE(1020,6)
#define REG_06_EIC_oil_pressure_2			TB_VALUE(1020,7)
#define REG_06_EIC_oil_temperature_1		TB_VALUE(1020,8)
#define REG_06_EIC_oil_temperature_2		TB_VALUE(1020,9)

//-----------------------------------------------------------------------------

#define REG_03_DEIF							0
#define REG_03_CONTROL_1					5
#define REG_03_CONTROL_2					6

#define REG_03_Control_1					TB_VALUE(5,0)
#define REG_03_Start						TB_VALUE(5,1)
#define REG_03_GB_ON						TB_VALUE(5,2)
#define REG_03_GB_OFF						TB_VALUE(5,3)
#define REG_03_TB_ON						TB_VALUE(5,2)
#define REG_03_TB_OFF						TB_VALUE(5,3)
#define REG_03_Stop							TB_VALUE(5,4)
#define REG_03_Alarm_ack					TB_VALUE(5,10)
#define REG_03_Nominal_1					TB_VALUE(5,11)
#define REG_03_Nominal_2					TB_VALUE(5,12)
#define REG_03_Nominal_3					TB_VALUE(5,13)
#define REG_03_Nominal_4					TB_VALUE(5,14)

#define REG_03_Control_2					TB_VALUE(6,0)
#define REG_03_Island						TB_VALUE(6,1)
#define REG_03_AMF							TB_VALUE(6,2)
#define REG_03_Peak_Shaving					TB_VALUE(6,3)
#define REG_03_Fixed_Power					TB_VALUE(6,4)
#define REG_03_MPE							TB_VALUE(6,5)
#define REG_03_LTO							TB_VALUE(6,6)
#define REG_03_MB_ON						TB_VALUE(6,9)
#define REG_03_MB_OFF						TB_VALUE(6,10)
#define REG_03_OFF							TB_VALUE(6,11)
#define REG_03_Block						TB_VALUE(6,11)
#define REG_03_Manual						TB_VALUE(6,12)
#define REG_03_Auto							TB_VALUE(6,13)
#define REG_03_SemiAuto						TB_VALUE(6,14)
#define REG_03_Test							TB_VALUE(6,15)

//-----------------------------------------------------------------------------

#endif // __DES_DEIF_H__
