#include "../common/logger.h"
#include "globalvar.h"
#include "des.h"
#include "des_struct.h"
#include "des_deif.h"
#include "des_deif_mains.h"
#include "des_service.h"

//------------------------------------------------------------------------------
DEIF_MAINS_DEVICE::DEIF_MAINS_DEVICE(MODBUS_SERVICE * p, quint32 address, qint32 connection) : MODBUS_DEVICE(p, address, connection)
{
	regs02.addRegister(DEFINE_REGISTER(REG_02_DEIF));
	regs02.addRegister(DEFINE_REGISTER(REG_02_MB_position_ON));
	regs02.addRegister(DEFINE_REGISTER(REG_02_Mains_failure));
	regs02.addRegister(DEFINE_REGISTER(REG_02_Block_mode));
	regs02.addRegister(DEFINE_REGISTER(REG_02_Manual_mode));
	regs02.addRegister(DEFINE_REGISTER(REG_02_SemiAuto_mode));
	regs02.addRegister(DEFINE_REGISTER(REG_02_Auto_mode_new));
	regs02.addRegister(DEFINE_REGISTER(REG_02_Test_mode));

	regs04.addRegister(DEFINE_REGISTER(REG_04_Application_version));
	regs04.addRegister(DEFINE_REGISTER(REG_04_HI_EGEN_Total_energy_counter));
	regs04.addRegister(DEFINE_REGISTER(REG_04_LO_EGEN_Total_energy_counter));
	regs04.addRegister(DEFINE_REGISTER(REG_04_UL1_L2_Mains_voltage));
	regs04.addRegister(DEFINE_REGISTER(REG_04_UL2_L3_Mains_voltage));
	regs04.addRegister(DEFINE_REGISTER(REG_04_UL3_L1_Mains_voltage));
	regs04.addRegister(DEFINE_REGISTER(REG_04_UL1_N_Mains_voltage));
	regs04.addRegister(DEFINE_REGISTER(REG_04_UL2_N_Mains_voltage));
	regs04.addRegister(DEFINE_REGISTER(REG_04_UL3_N_Mains_voltage));
	regs04.addRegister(DEFINE_REGISTER(REG_04_fMains_Mains_freq));
	regs04.addRegister(DEFINE_REGISTER(REG_04_Number_of_alarms));
	regs04.addRegister(DEFINE_REGISTER(REG_04_Number_of_unacknowledged_alarms));
	regs04.addRegister(DEFINE_REGISTER(REG_04_Number_of_acknowledged_active_alarms));
	regs04.addRegister(DEFINE_REGISTER(REG_04_MB_operation_Mains_breaker_operation_counter));
	regs04.addRegister(DEFINE_REGISTER(REG_04_USUPPLY_Supply_voltage));

	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_2));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_3));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_5));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_6));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_10));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_13));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_14));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_15));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_18));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_19));
	regs04.addRegister(DEFINE_REGISTER(REG_06_DEIF_STATUS_20));

	regs03.addRegister(DEFINE_REGISTER(REG_03_DEIF));
	regs03.addRegister(DEFINE_REGISTER(REG_03_CONTROL_1));
	regs03.addRegister(DEFINE_REGISTER(REG_03_CONTROL_2));

	regs10.addRegister(DEFINE_REGISTER(REG_03_CONTROL_1));
	regs10.addRegister(DEFINE_REGISTER(REG_03_CONTROL_2));

	LogDesInfo("DEIF_MAINS_DEVICE: register pack 02\n%s", qPrintable(regs02.toString()));
	LogDesInfo("DEIF_MAINS_DEVICE: register pack 03\n%s", qPrintable(regs03.toString()));
	LogDesInfo("DEIF_MAINS_DEVICE: register pack 04\n%s", qPrintable(regs04.toString()));
	LogDesInfo("DEIF_MAINS_DEVICE: register pack 10\n%s", qPrintable(regs10.toString()));
}

//------------------------------------------------------------------------------
DEIF_MAINS_DEVICE::~DEIF_MAINS_DEVICE()
{
	
}

// ------------------------------------------------------------------
void DEIF_MAINS_DEVICE::setControl1(quint16 value)
{
	regs10[REG_03_CONTROL_1] = value;
	regs10[REG_03_CONTROL_1].update();
}

// ------------------------------------------------------------------
void DEIF_MAINS_DEVICE::setControl2(quint16 value)
{
	regs10[REG_03_CONTROL_2] = value;
	regs10[REG_03_CONTROL_2].update();
}

// ------------------------------------------------------------------
void DEIF_MAINS_DEVICE::setTB(bool on)
{
	m_deifMainsState.Control.RegControl1.Bits.Control   = 1;
	m_deifMainsState.Control.RegControl1.Bits.TB_GB_ON  = on ? 1 : 0;
	m_deifMainsState.Control.RegControl1.Bits.TB_GB_OFF = on ? 0 : 1;
	setControl1(m_deifMainsState.Control.RegControl1._Data);
	m_deifMainsState.Control.RegControl1.Bits.Control   = 0;
}

// ------------------------------------------------------------------
void DEIF_MAINS_DEVICE::setMB(bool on)
{
	m_deifMainsState.Control.RegControl2.Bits.Control   = 1;
	m_deifMainsState.Control.RegControl2.Bits.MB_ON  = on ? 1 : 0;
	m_deifMainsState.Control.RegControl2.Bits.MB_OFF = on ? 0 : 1;
	setControl2(m_deifMainsState.Control.RegControl2._Data);
	m_deifMainsState.Control.RegControl2.Bits.Control   = 0;
}

// ------------------------------------------------------------------
void DEIF_MAINS_DEVICE::setMode(quint32 mode)
{
	m_deifMainsState.Control.RegControl2.Bits.Control  = 1;
	m_deifMainsState.Control.RegControl2.Bits.Auto     = (mode == 0) ? 1 : 0;
	m_deifMainsState.Control.RegControl2.Bits.SemiAuto = (mode == 1) ? 1 : 0;
	m_deifMainsState.Control.RegControl2.Bits.Test     = (mode == 2) ? 1 : 0;
	m_deifMainsState.Control.RegControl2.Bits.Manual   = (mode == 3) ? 1 : 0;
	m_deifMainsState.Control.RegControl2.Bits.Block    = (mode == 4) ? 1 : 0;
	setControl2(m_deifMainsState.Control.RegControl2._Data);
	m_deifMainsState.Control.RegControl2.Bits.Control   = 0;
}

// ------------------------------------------------------------------
void DEIF_MAINS_DEVICE::setReset()
{
	m_deifMainsState.Control.RegControl1.Bits.Control   = 1;
	m_deifMainsState.Control.RegControl1.Bits.Alarm_ack  = 1;
	setControl1(m_deifMainsState.Control.RegControl1._Data);
	m_deifMainsState.Control.RegControl1.Bits.Alarm_ack  = 0;
	m_deifMainsState.Control.RegControl1.Bits.Control   = 0;
}

// ------------------------------------------------------------------
void DEIF_MAINS_DEVICE::onConnected()
{
}

// ------------------------------------------------------------------
void DEIF_MAINS_DEVICE::onDisconnected()
{
	updateRegs02();
	updateRegs03();
	updateRegs04();
}

//------------------------------------------------------------------------------
void DEIF_MAINS_DEVICE::processPacket(const ModbusPacket & packet)
{
	ModbusPacket::Type t = (ModbusPacket::Type)packet.type();

	unsigned char d = packet.device();
	unsigned short c = packet.bytes();

	if(d != address())
		return;

	LogDesBinary("DEIF_MAINS_DEVICE[%d]: read: %s", address(), LogArray(packet.toByteArray()));

	switch(t)
	{
		case ModbusPacket::ResponseDiscrete:
			regs02.setPacket(packet, REG_02_DEIF, 39);
			onAnswer02(DEIF_MAINS_DEVICE_MAX_COUNTER_02);
			updateRegs02();
			break;

		case ModbusPacket::ResponseHolding:
			regs03.setPacket(packet, REG_03_DEIF, 14);
			onAnswer03(DEIF_MAINS_DEVICE_MAX_COUNTER_03);
			updateRegs03();
			break;

		case ModbusPacket::ResponseRegisters:
			switch(c / sizeof(quint16))
			{
			case 77:
				regs04.setPacket(packet, REG_04_DEIF, 77);
				break;
			case 21:
				regs04.setPacket(packet, REG_06_DEIF, 21);
				break;
			}
			onAnswer04(DEIF_MAINS_DEVICE_MAX_COUNTER_04);
			updateRegs04();
			break;

		case ModbusPacket::RecieptMultiRegisters:
			LogDesInfo("DEIF_MAINS_DEVICE[%d] command accepted!!", address());
			onAnswer03(DEIF_MAINS_DEVICE_MAX_COUNTER_03);
			updateRegs03();
			break;

		case ModbusPacket::Error:
			LogDesError("DEIF_MAINS_DEVICE[%d] responce ERROR!!", address());
			break;

		default:
			LogDesError("DEIF_MAINS_DEVICE[%d] unrequested packet", address());
			break;
	}
}

//------------------------------------------------------------------------------
bool DEIF_MAINS_DEVICE::processCommands()
{
//	LogDesInfo("DEIF_MAINS_DEVICE[%d] process commands", address());

	bool wasCommand = false;
	QMutableMapIterator<quint32, ModbusRegister> i(regs10);
	while(i.hasNext())
	{
		i.next();
		if(i.value().isChanged())
		{
			wasCommand = true;
			control10(i.key(), i.key(), 1);
			i.value().respond();

			switch(i.key())
			{
				case REG_03_CONTROL_1:
					i.value().setValue(m_deifMainsState.Control.RegControl1._Data, false);
					break;
				case REG_03_CONTROL_2:
					i.value().setValue(m_deifMainsState.Control.RegControl2._Data, false);
					break;
			}

			break;
		}
	}

	return wasCommand;
}

//------------------------------------------------------------------------------
bool DEIF_MAINS_DEVICE::processQuery()
{
	switch(m_queryPacket)
	{
		case 0:
			request03(REG_03_DEIF, 0, 14);//14 (from 0)
			m_queryPacket = 1;
			break;

		case 1:
			request02(REG_02_DEIF, 0, 39);//39 (from 0)
			m_queryPacket = 2;
			break;

		case 2:
			request04(REG_04_DEIF, 0, 77);//77 (from 500)
			m_queryPacket = 3;
			break;

		case 3:
			request04(REG_06_DEIF, 0, 21);//21 (from 1000)
			m_queryPacket = 4;
			break;

		case 4:
			//nop
			m_queryPacket = 0;
			return false;
			break;
	}

	checkResponce();

	if(m_needRefresh02)
		updateRegs02();

	if(m_needRefresh03)
		updateRegs03();

	if(m_needRefresh04)
		updateRegs04();

	return true;
}

//------------------------------------------------------------------------------
void DEIF_MAINS_DEVICE::setRegisters02()
{
	QMutableMapIterator<quint32, ModbusDiscrete> i(regs02);
	while(i.hasNext())
	{
		i.next();

		switch(i.key())
		{
//			case REG_02_GB_position_ON:
//				m_deifMainsState.State.RegState.Bits.GB_position = i.value();
//				break;
			case REG_02_TB_position_ON:
				m_deifMainsState.State.RegState.Bits.TB_position = i.value();
				break;
			case REG_02_MB_position_ON:
				m_deifMainsState.State.RegState.Bits.MB_position = i.value();
				break;
			case REG_02_Running:
				break;
			case REG_02_Generator_voltage_frequency_OK:
				break;
			case REG_02_Mains_failure:
				break;
			case REG_02_Block_mode:
				m_deifMainsState.State.RegState.Bits.Block_mode = i.value();
				break;
			case REG_02_Manual_mode:
				m_deifMainsState.State.RegState.Bits.Manual_mode = i.value();
				break;
			case REG_02_SemiAuto_mode:
				m_deifMainsState.State.RegState.Bits.SemiAuto_mode = i.value();
				break;
			case REG_02_Auto_mode_new:
				m_deifMainsState.State.RegState.Bits.Auto_mode = i.value();
				break;
			case REG_02_Test_mode:
				m_deifMainsState.State.RegState.Bits.Test_mode = i.value();
				break;
			case REG_02_Island:
				m_deifMainsState.State.RegState.Bits.Island = i.value();
				break;
			case REG_02_Automatic_mains_failure_AMF:
				m_deifMainsState.State.RegState.Bits.Automatic_mains_failure_AMF = i.value();
				break;
			case REG_02_ATS_mode:
				m_deifMainsState.State.RegState.Bits.ATS_mode = i.value();
				break;
			case REG_02_Load_take_over_LTO:
				m_deifMainsState.State.RegState.Bits.Load_take_over_LTO = i.value();
				break;
		}
	}

	if(m_status == DEVICE_OK && isInfoCollected())
	{
		m_deifMainsState.Updated = QDateTime::currentDateTime();
	}
	else
	{
		m_deifMainsState.Updated = QDateTime();
	}
}

//------------------------------------------------------------------------------
void DEIF_MAINS_DEVICE::setRegisters03()
{
	QMutableMapIterator<quint32, ModbusHolding> i(regs03);
	while(i.hasNext())
	{
		i.next();

		switch(i.key())
		{

		}
	}

	if(m_status == DEVICE_OK && isInfoCollected())
	{
		m_deifMainsState.Updated = QDateTime::currentDateTime();
	}
	else
	{
		m_deifMainsState.Updated = QDateTime();
	}
}

//------------------------------------------------------------------------------
void DEIF_MAINS_DEVICE::setRegisters04()
{
	QMutableMapIterator<quint32, ModbusRegister> i(regs04);
	while(i.hasNext())
	{
		i.next();

		switch(i.key())
		{
			case REG_04_Application_version:
				break;
			case REG_04_UL1_L2_Generator_voltage:
				break;
			case REG_04_UL2_L3_Generator_voltage:
				break;
			case REG_04_UL3_L1_Generator_voltage:
				break;
			case REG_04_UL1_N_Generator_voltage:
				m_deifMainsState.State.RegVoltageL1._Data = i.value();
				break;
			case REG_04_UL2_N_Generator_voltage:
				m_deifMainsState.State.RegVoltageL2._Data = i.value();
				break;
			case REG_04_UL3_N_Generator_voltage:
				m_deifMainsState.State.RegVoltageL3._Data = i.value();
				break;
			case REG_04_fL1GEN_Generator_freq:
				m_deifMainsState.State.RegFrequencyL1._Data = i.value();
				break;
			case REG_04_fL2GEN_Generator_freq:
				m_deifMainsState.State.RegFrequencyL2._Data = i.value();
				break;
			case REG_04_fL3GEN_Generator_freq:
				m_deifMainsState.State.RegFrequencyL3._Data = i.value();
				break;
			case REG_04_PhiL1L2_Generator_phase:
				m_deifMainsState.State.RegPhaseL1L2._Data = i.value();
				break;
			case REG_04_PhiL2L3_Generator_phase:
				m_deifMainsState.State.RegPhaseL2L3._Data = i.value();
				break;
			case REG_04_PhiL3L1_Generator_phase:
				m_deifMainsState.State.RegPhaseL3L1._Data = i.value();
				break;
			case REG_04_IL1_Generator_current:
				m_deifMainsState.State.RegCurrentL1._Data = i.value();
				break;
			case REG_04_IL2_Generator_current:
				m_deifMainsState.State.RegCurrentL2._Data = i.value();
				break;
			case REG_04_IL3_Generator_current:
				m_deifMainsState.State.RegCurrentL3._Data = i.value();
				break;
			case REG_04_PL1_Generator_active_power:
				break;
			case REG_04_PL2_Generator_active_power:
				break;
			case REG_04_PL3_Generator_active_power:
				break;
			case REG_04_PGEN_Generator_total_active_power:
				m_deifMainsState.State.RegTotalActivePower._Data = i.value();
				break;
			case REG_04_QL1_Generator_reactive_power:
				break;
			case REG_04_QL2_Generator_reactive_power:
				break;
			case REG_04_QL3_Generator_reactive_power:
				break;
			case REG_04_QGEN_Generator_total_reactive_power:
				m_deifMainsState.State.RegTotalReactivePower._Data = i.value();
				break;
			case REG_04_SL1_Generator_apparent_power:
				break;
			case REG_04_SL2_Generator_apparent_power:
				break;
			case REG_04_SL3_Generator_apparent_power:
				break;
			case REG_04_SGEN_Generator_total_apparent_power:
				m_deifMainsState.State.RegTotalApparentPower._Data = i.value();
				break;
			case REG_04_HI_EGEN_Total_energy_counter:
				m_deifMainsState.State.RegTotalEnergyCounter.setHI(i.value());
				break;
			case REG_04_LO_EGEN_Total_energy_counter:
				m_deifMainsState.State.RegTotalEnergyCounter.setLO(i.value());
				break;
			case REG_04_Generator_cos_phi:
				m_deifMainsState.State.RegCosPhi._Data = i.value();
				break;
			case REG_04_UL1_L2_Mains_voltage:
				break;
			case REG_04_UL2_L3_Mains_voltage:
				break;
			case REG_04_UL3_L1_Mains_voltage:
				break;
			case REG_04_UL1_N_Mains_voltage:
				break;
			case REG_04_UL2_N_Mains_voltage:
				break;
			case REG_04_UL3_N_Mains_voltage:
				break;
			case REG_04_fMains_Mains_freq:
				break;
			case REG_04_HI_Running_time_Absolute:
				m_deifMainsState.State.RegRunningTimeAbsolute.setHI(i.value());
				break;
			case REG_04_LO_Running_time_Absolute:
				m_deifMainsState.State.RegRunningTimeAbsolute.setLO(i.value());
				break;
			case REG_04_HI_Running_time_Relative:
				m_deifMainsState.State.RegRunningTimeRelative.setHI(i.value());
				break;
			case REG_04_LO_Running_time_Relative:
				m_deifMainsState.State.RegRunningTimeRelative.setLO(i.value());
				break;
			case REG_04_Number_of_alarms:
				break;
			case REG_04_Number_of_unacknowledged_alarms:
				break;
			case REG_04_Number_of_acknowledged_active_alarms:
				break;
			case REG_04_GB_operation_Generator_circuit_breaker_operations_counter:
				break;
			case REG_04_MB_operation_Mains_breaker_operation_counter:
				break;
			case REG_04_Start_attempts_Number_of_start_attempts:
				break;
			case REG_04_USUPPLY_Supply_voltage:
				m_deifMainsState.State.RegSupplyVoltage._Data = i.value();
				break;
			case REG_04_Service_timer_1_running_hours:
				m_deifMainsState.State.RegServiceTimerHours1._Data = i.value();
				break;
			case REG_04_Service_timer_1_days:
				m_deifMainsState.State.RegServiceTimerDays1._Data = i.value();
				break;
			case REG_04_Service_timer_2_running_hours:
				m_deifMainsState.State.RegServiceTimerHours2._Data = i.value();
				break;
			case REG_04_Service_timer_2_days:
				m_deifMainsState.State.RegServiceTimerDays2._Data = i.value();
				break;
			case REG_04_RPM_Running_feedback_RPM:
				m_deifMainsState.State.RegRunningFeedback._Data = i.value();
				break;
//06
			case REG_06_DEIF_STATUS_2:
				m_deifMainsState.State.RegState2.Bits.Unbalance_current = TB_REG_BIT(i.value(), REG_06_Unbalance_current);
				m_deifMainsState.State.RegState2.Bits.Unbalance_voltage = TB_REG_BIT(i.value(), REG_06_Unbalance_voltage);
				break;
			case REG_06_DEIF_STATUS_3:
//				m_deifMainsState.State.RegState2.Bits.Mains_unbalanced_voltage = TB_REG_BIT(i.value(), REG_06_Mains_unbalanced_voltage);
				break;
			case REG_06_DEIF_STATUS_5:
				m_deifMainsState.State.RegState2.Bits.Phase_seq_error = TB_REG_BIT(i.value(), REG_06_Phase_seq_error);
				m_deifMainsState.State.RegState2.Bits.TB_open_failure = TB_REG_BIT(i.value(), REG_06_TB_open_failure);
				m_deifMainsState.State.RegState2.Bits.TB_close_failure = TB_REG_BIT(i.value(), REG_06_TB_close_failure);
				m_deifMainsState.State.RegState2.Bits.TB_pos_failure = TB_REG_BIT(i.value(), REG_06_TB_pos_failure);
				m_deifMainsState.State.RegState2.Bits.MB_open_failure = TB_REG_BIT(i.value(), REG_06_MB_open_failure);
				m_deifMainsState.State.RegState2.Bits.MB_close_failure = TB_REG_BIT(i.value(), REG_06_MB_close_failure);
				m_deifMainsState.State.RegState2.Bits.MB_pos_failure = TB_REG_BIT(i.value(), REG_06_MB_pos_failure);
//				m_deifMainsState.State.RegState2.Bits.Close_before_excitation_failure = TB_REG_BIT(i.value(), REG_06_Close_before_excitation_failure);
				break;
			case REG_06_DEIF_STATUS_6:
//				m_deifMainsState.State.RegState2.Bits.GOVERNOR_regulation_failed = TB_REG_BIT(i.value(), REG_06_GOVERNOR_regulation_failed);
//				m_deifMainsState.State.RegState2.Bits.Deload_error = TB_REG_BIT(i.value(), REG_06_Deload_error);
//				m_deifMainsState.State.RegState2.Bits.AVR_regulation_failed = TB_REG_BIT(i.value(), REG_06_AVR_regulation_failed);
				break;
			case REG_06_DEIF_STATUS_10:
				m_deifMainsState.State.RegState2.Bits.Emergency_STOP = TB_REG_BIT(i.value(), REG_06_Emergency_STOP);
				break;
			case REG_06_DEIF_STATUS_13:
				m_deifMainsState.State.RegState2.Bits.Overspeed_1 = TB_REG_BIT(i.value(), REG_06_Overspeed_1);
				m_deifMainsState.State.RegState2.Bits.Overspeed_2 = TB_REG_BIT(i.value(), REG_06_Overspeed_2);
				m_deifMainsState.State.RegState2.Bits.Crank_failure = TB_REG_BIT(i.value(), REG_06_Crank_failure);
				m_deifMainsState.State.RegState2.Bits.Running_feedback_failure = TB_REG_BIT(i.value(), REG_06_Running_feedback_failure);
				m_deifMainsState.State.RegState2.Bits.MPU_wire_failure = TB_REG_BIT(i.value(), REG_06_MPU_wire_failure);
				m_deifMainsState.State.RegState2.Bits.Generator_Hz_V_failure = TB_REG_BIT(i.value(), REG_06_Generator_Hz_V_failure);
				m_deifMainsState.State.RegState2.Bits.Start_failure = TB_REG_BIT(i.value(), REG_06_Start_failure);
				break;
			case REG_06_DEIF_STATUS_14:
				m_deifMainsState.State.RegState2.Bits.Stop_failure = TB_REG_BIT(i.value(), REG_06_Stop_failure);
				m_deifMainsState.State.RegState2.Bits.Underspeed_1 = TB_REG_BIT(i.value(), REG_06_Underspeed_1);
				break;
			case REG_06_DEIF_STATUS_15:
				m_deifMainsState.State.RegState2.Bits.Service_timer_1 = TB_REG_BIT(i.value(), REG_06_Service_timer_1);
				m_deifMainsState.State.RegState2.Bits.Service_timer_2 = TB_REG_BIT(i.value(), REG_06_Service_timer_2);
				m_deifMainsState.State.RegState2.Bits.Stop_coil_wire_break = TB_REG_BIT(i.value(), REG_06_Stop_coil_wire_break);
				m_deifMainsState.State.RegState2.Bits.Internal_comm_failure = TB_REG_BIT(i.value(), REG_06_Internal_comm_failure);
				m_deifMainsState.State.RegState2.Bits.Engine_heater_1 = TB_REG_BIT(i.value(), REG_06_Engine_heater_1);
				m_deifMainsState.State.RegState2.Bits.Battery_test = TB_REG_BIT(i.value(), REG_06_Battery_test);
				m_deifMainsState.State.RegState2.Bits.Battery_assymmetry_1 = TB_REG_BIT(i.value(), REG_06_Battery_assymmetry_1);
				m_deifMainsState.State.RegState2.Bits.Battery_assymmetry_2 = TB_REG_BIT(i.value(), REG_06_Battery_assymmetry_2);
				m_deifMainsState.State.RegState2.Bits.Max_ventilation_1 = TB_REG_BIT(i.value(), REG_06_Max_ventilation_1);
				m_deifMainsState.State.RegState2.Bits.Max_ventilation_2 = TB_REG_BIT(i.value(), REG_06_Max_ventilation_2);
//				m_deifMainsState.State.RegState2.Bits.Blk_swbd_error = TB_REG_BIT(i.value(), REG_06_Blk_swbd_error);
//				m_deifMainsState.State.RegState2.Bits.Stp_swbd_error = TB_REG_BIT(i.value(), REG_06_Stp_swbd_error);
//				m_deifMainsState.State.RegState2.Bits.Unit_not_in_auto = TB_REG_BIT(i.value(), REG_06_Unit_not_in_auto);
				m_deifMainsState.State.RegState2.Bits.Fuel_pump_logic = TB_REG_BIT(i.value(), REG_06_Fuel_pump_logic);
				break;
			case REG_06_DEIF_STATUS_18:
				m_deifMainsState.State.RegState2.Bits.Mains_failure = TB_REG_BIT(i.value(), REG_06_Mains_failure);
//				m_deifMainsState.State.RegState2.Bits.MB_pos_ON = TB_REG_BIT(i.value(), REG_06_MB_pos_ON);
//				m_deifMainsState.State.RegState2.Bits.GB_pos_ON = TB_REG_BIT(i.value(), REG_06_GB_pos_ON);
				m_deifMainsState.State.RegState2.Bits.Engine_running = TB_REG_BIT(i.value(), REG_06_Engine_running);
//				m_deifMainsState.State.RegState2.Bits.Running_detection_timer_expired = TB_REG_BIT(i.value(), REG_06_Running_detection_timer_expired);
//				m_deifMainsState.State.RegState2.Bits.DG_Hz_V_OK_timer_expired = TB_REG_BIT(i.value(), REG_06_DG_Hz_V_OK_timer_expired);
				break;
			case REG_06_DEIF_STATUS_19:
//				m_deifMainsState.State.RegState2.Bits.OFF = TB_REG_BIT(i.value(), REG_06_OFF);
//				m_deifMainsState.State.RegState2.Bits.Manual = TB_REG_BIT(i.value(), REG_06_Manual);
//				m_deifMainsState.State.RegState2.Bits.Auto = TB_REG_BIT(i.value(), REG_06_Auto);
//				m_deifMainsState.State.RegState2.Bits.Test = TB_REG_BIT(i.value(), REG_06_Test);
//				m_deifMainsState.State.RegState2.Bits.Island = TB_REG_BIT(i.value(), REG_06_Island);
//				m_deifMainsState.State.RegState2.Bits.AMF = TB_REG_BIT(i.value(), REG_06_AMF);
//				m_deifMainsState.State.RegState2.Bits.Load_take_over = TB_REG_BIT(i.value(), REG_06_Load_take_over);
//				m_deifMainsState.State.RegState2.Bits.AMF_active = TB_REG_BIT(i.value(), REG_06_AMF_active);
				break;
			case REG_06_DEIF_STATUS_20:
				m_deifMainsState.State.RegState2.Bits.EIC_comm_error = TB_REG_BIT(i.value(), REG_06_EIC_comm_error);
				m_deifMainsState.State.RegState2.Bits.EIC_warning = TB_REG_BIT(i.value(), REG_06_EIC_warning);
				m_deifMainsState.State.RegState2.Bits.EIC_shutdown = TB_REG_BIT(i.value(), REG_06_EIC_shutdown);
				m_deifMainsState.State.RegState2.Bits.EIC_overspeed = TB_REG_BIT(i.value(), REG_06_EIC_overspeed);
				m_deifMainsState.State.RegState2.Bits.EIC_coolant_temp_1 = TB_REG_BIT(i.value(), REG_06_EIC_coolant_temp_1);
				m_deifMainsState.State.RegState2.Bits.EIC_coolant_temp_2 = TB_REG_BIT(i.value(), REG_06_EIC_coolant_temp_2);
				m_deifMainsState.State.RegState2.Bits.EIC_oil_pressure_1 = TB_REG_BIT(i.value(), REG_06_EIC_oil_pressure_1);
				m_deifMainsState.State.RegState2.Bits.EIC_oil_pressure_2 = TB_REG_BIT(i.value(), REG_06_EIC_oil_pressure_2);
				m_deifMainsState.State.RegState2.Bits.EIC_oil_temperature_1 = TB_REG_BIT(i.value(), REG_06_EIC_oil_temperature_1);
				m_deifMainsState.State.RegState2.Bits.EIC_oil_temperature_2 = TB_REG_BIT(i.value(), REG_06_EIC_oil_temperature_2);
				break;
		}
	}

	if(m_status == DEVICE_OK && isInfoCollected())
	{
		m_deifMainsState.Updated = QDateTime::currentDateTime();
	}
	else
	{
		m_deifMainsState.Updated = QDateTime();
	}
}

//------------------------------------------------------------------------------
void DEIF_MAINS_DEVICE::updateRegs02()
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
void DEIF_MAINS_DEVICE::updateRegs03()
{
//	qDebug() << regs03.toString();

	if(!m_connected)
		regs03.reset();

	checkDeviceState();
	setRegisters03();

	m_needRefresh03 = false;

	if(parent)
		parent->onChangedDeviceState();
}

//------------------------------------------------------------------------------
void DEIF_MAINS_DEVICE::updateRegs04()
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
bool DEIF_MAINS_DEVICE::isActualState()
{
	qint64 timeUpdated = TimeUndefined;

	if(!m_deifMainsState.Updated.isNull())
		timeUpdated = timeDiff(m_deifMainsState.Updated);

	return ((timeUpdated <= 10000) && (timeUpdated >= -10000) && (timeUpdated != TimeUndefined));
}

//------------------------------------------------------------------------------
bool DEIF_MAINS_DEVICE::isInfoCollected()
{
	return (
		regs02[REG_02_DEIF].isInitialized() &&
		regs02[REG_03_DEIF].isInitialized() &&
		regs04[REG_04_DEIF].isInitialized()
	);

	return false;
}

//------------------------------------------------------------------------------
