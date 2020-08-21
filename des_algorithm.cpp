#include "../common/logger.h"
#include "globalvar.h"
#include "des_service.h"
#include "des_deif_mains.h"
#include "des_deif_dg.h"

// ------------------------------------------------------------------
void DES_SERVICE::updateState()
{
	verifyFirstCommands();
	updatePortState();
	updateDesMainsState(0);
	updateDesDgState(0);
	updateDesDgState(1);
	updateCommonState();

	emit sigState(bDesState);
}

// ------------------------------------------------------------------
void DES_SERVICE::updatePortState()
{
	if(!m_portState[MODBUS_PORT_1].State.Bits.Opened)
		bDesState["port"] = ELEM_NOT;
	else if(m_portState[MODBUS_PORT_1].State.Bits.NoData)
		bDesState["port"] = ELEM_AVAR;
	else if(m_portState[MODBUS_PORT_1].State.Bits.BadData)
		bDesState["port"] = ELEM_ERROR;
	else
		bDesState["port"] = ELEM_NORMA;

	if(bDesState["port"] == ELEM_NOT)
		bDesState["comm"] = ELEM_AVAR;
	else
		bDesState["comm"] = ELEM_NORMA;

	bool work1 = deif_mains[0]->isActualState();
	bool work2 = deif_dg[0]->isActualState();
	bool work3 = deif_dg[1]->isActualState();
//	bool info1 = deif_mains[0]->isInfoCollected();
//	bool info2 = deif_dg[1]->isInfoCollected();
//	bool info3 = deif_dg[1]->isInfoCollected();

	if(bDesState["port"] == ELEM_NOT)
		bDesState["device1"] = ELEM_NOT;
	else if(!work1 || bDesState["port"] == ELEM_AVAR)
		bDesState["device1"] = ELEM_AVAR;
	else
		bDesState["device1"] = ELEM_NORMA;

	if(bDesState["port"] == ELEM_NOT)
		bDesState["device2"] = ELEM_NOT;
	else if(!work2 || bDesState["port"] == ELEM_AVAR)
		bDesState["device2"] = ELEM_AVAR;
	else
		bDesState["device2"] = ELEM_NORMA;

	if(bDesState["port"] == ELEM_NOT)
		bDesState["device3"] = ELEM_NOT;
	else if(!work3 || bDesState["port"] == ELEM_AVAR)
		bDesState["device3"] = ELEM_AVAR;
	else
		bDesState["device3"] = ELEM_NORMA;

	if(bDesState["port"] == ELEM_NOT)
		bDesState["line1"] = ELEM_NOT;
	else if((!work1 && !work2 && !work3) || bDesState["port"] == ELEM_AVAR)
		bDesState["line1"] = ELEM_AVAR;
	else
		bDesState["line1"] = ELEM_NORMA;

	if(bDesState["port"] == ELEM_NOT)
		bDesState["line2"] = ELEM_NOT;
	else if((!work2 && !work3) || bDesState["port"] == ELEM_AVAR)
		bDesState["line2"] = ELEM_AVAR;
	else
		bDesState["line2"] = ELEM_NORMA;

	if(bDesState["port"] == ELEM_NOT)
		bDesState["line3"] = ELEM_NOT;
	else if(!work3 || bDesState["port"] == ELEM_AVAR)
		bDesState["line3"] = ELEM_AVAR;
	else
		bDesState["line3"] = ELEM_NORMA;

//obSost Channel
	if((bDesState["port"] == ELEM_AVAR || bDesState["port"] == ELEM_NOT) ||
		(bDesState["device1"] == ELEM_AVAR && bDesState["device2"] == ELEM_AVAR && bDesState["device3"] == ELEM_AVAR))
		bDesState["channel"] = ELEM_AVAR;
	else if(bDesState["port"] == ELEM_NORMA &&
		bDesState["device1"] == ELEM_NORMA && bDesState["device2"] == ELEM_NORMA && bDesState["device3"] == ELEM_NORMA)
		bDesState["channel"] = ELEM_NORMA;
	else
		bDesState["channel"] = ELEM_ERROR;
}

// ------------------------------------------------------------------
void DES_SERVICE::updateCommonState()
{
	if(bDesState["mains1@ObSost"] == ELEM_NOT && bDesState["dg1@ObSost"] == ELEM_NOT && bDesState["dg2@ObSost"] == ELEM_NOT)
		bDesState["des@ObSost"] = ELEM_NOT;
	else if((bDesState["mains1@ObSost"] == ELEM_AVAR || bDesState["mains1@ObSost"] == ELEM_NOT) || 
			((bDesState["dg1@ObSost"] == ELEM_AVAR || bDesState["dg1@ObSost"] == ELEM_NOT) && 
			(bDesState["dg2@ObSost"] == ELEM_AVAR || bDesState["dg2@ObSost"] == ELEM_NOT)))
		bDesState["des@ObSost"] = ELEM_AVAR;
	else if(bDesState["mains1@ObSost"] == ELEM_NORMA && bDesState["dg1@ObSost"] == ELEM_NORMA && bDesState["dg2@ObSost"] == ELEM_NORMA)
		bDesState["des@ObSost"] = ELEM_NORMA;
	else
		bDesState["des@ObSost"] = ELEM_ERROR;
}

// ------------------------------------------------------------------
void DES_SERVICE::updateDesMainsState(quint32 n_mains)
{
	DeifMainsState & state = deif_mains[n_mains]->state();
	bool work = deif_mains[n_mains]->isActualState();

	QString N = QString("mains%1@").arg(n_mains + 1);

	quint32 nError = 0, nAvar = 0;

//02
	if(!work)
		bDesState[N + "TB_position"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.TB_position)
		bDesState[N + "TB_position"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "TB_position"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "MB_position"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.MB_position)
		bDesState[N + "MB_position"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "MB_position"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Block_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Block_mode)
	{
		bDesState[N + "Block_mode"].setText("ВКЛ") = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Block_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Test_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Test_mode)
	{
		bDesState[N + "Test_mode"].setText("ВКЛ") = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Test_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Manual_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Manual_mode)
	{
		bDesState[N + "Manual_mode"].setText("ВКЛ") = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Manual_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "SemiAuto_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.SemiAuto_mode)
	{
		bDesState[N + "SemiAuto_mode"].setText("ВКЛ") = ELEM_ERROR;
		nError++;
	}
	else
		bDesState[N + "SemiAuto_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Auto_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Auto_mode)
		bDesState[N + "Auto_mode"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "Auto_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Island"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Island)
		bDesState[N + "Island"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "Island"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Automatic_mains_failure_AMF"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Automatic_mains_failure_AMF)
		bDesState[N + "Automatic_mains_failure_AMF"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "Automatic_mains_failure_AMF"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "ATS_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.ATS_mode)
		bDesState[N + "ATS_mode"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "ATS_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Load_take_over_LTO"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Load_take_over_LTO)
		bDesState[N + "Load_take_over_LTO"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "Load_take_over_LTO"].setText("ОТКЛ") = ELEM_NORMA;

//04
	if(!work)
		bDesState[N + "UL1_N_Generator_voltage"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "UL1_N_Generator_voltage"].setText(state.State.RegVoltageL1.textValue());
		bDesState[N + "UL1_N_Generator_voltage"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "UL2_N_Generator_voltage"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "UL2_N_Generator_voltage"].setText(state.State.RegVoltageL2.textValue());
		bDesState[N + "UL2_N_Generator_voltage"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "UL3_N_Generator_voltage"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "UL3_N_Generator_voltage"].setText(state.State.RegVoltageL3.textValue());
		bDesState[N + "UL3_N_Generator_voltage"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "fL1GEN_Generator_freq"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "fL1GEN_Generator_freq"].setText(state.State.RegFrequencyL1.textValue());
		bDesState[N + "fL1GEN_Generator_freq"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "fL2GEN_Generator_freq"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "fL2GEN_Generator_freq"].setText(state.State.RegFrequencyL2.textValue());
		bDesState[N + "fL2GEN_Generator_freq"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "fL3GEN_Generator_freq"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "fL3GEN_Generator_freq"].setText(state.State.RegFrequencyL3.textValue());
		bDesState[N + "fL3GEN_Generator_freq"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "PhiL1L2_Generator_phase"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "PhiL1L2_Generator_phase"].setText(state.State.RegPhaseL1L2.textValue());
		bDesState[N + "PhiL1L2_Generator_phase"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "PhiL2L3_Generator_phase"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "PhiL2L3_Generator_phase"].setText(state.State.RegPhaseL2L3.textValue());
		bDesState[N + "PhiL2L3_Generator_phase"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "PhiL3L1_Generator_phase"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "PhiL3L1_Generator_phase"].setText(state.State.RegPhaseL3L1.textValue());
		bDesState[N + "PhiL3L1_Generator_phase"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "IL1_Generator_current"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "IL1_Generator_current"].setText(state.State.RegCurrentL1.textValue());
		bDesState[N + "IL1_Generator_current"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "IL2_Generator_current"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "IL2_Generator_current"].setText(state.State.RegCurrentL2.textValue());
		bDesState[N + "IL2_Generator_current"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "IL3_Generator_current"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "IL3_Generator_current"].setText(state.State.RegCurrentL3.textValue());
		bDesState[N + "IL3_Generator_current"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "PGEN_Generator_total_active_power"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "PGEN_Generator_total_active_power"].setText(state.State.RegTotalActivePower.textValue());
		bDesState[N + "PGEN_Generator_total_active_power"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "QGEN_Generator_total_reactive_power"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "QGEN_Generator_total_reactive_power"].setText(state.State.RegTotalReactivePower.textValue());
		bDesState[N + "QGEN_Generator_total_reactive_power"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "SGEN_Generator_total_apparent_power"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "SGEN_Generator_total_apparent_power"].setText(state.State.RegTotalApparentPower.textValue());
		bDesState[N + "SGEN_Generator_total_apparent_power"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "EGEN_Total_energy_counter"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "EGEN_Total_energy_counter"].setText(state.State.RegTotalEnergyCounter.textValue());
		bDesState[N + "EGEN_Total_energy_counter"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "Generator_cos_phi"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "Generator_cos_phi"].setText(state.State.RegCosPhi.textValue());
		bDesState[N + "Generator_cos_phi"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "USUPPLY_Supply_voltage"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "USUPPLY_Supply_voltage"].setText(state.State.RegSupplyVoltage.textValue());
		bDesState[N + "USUPPLY_Supply_voltage"] = ELEM_NORMA;
	}

//06
	if(!work)
		bDesState[N + "Unbalance_current"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Unbalance_current)
	{
		bDesState[N + "Unbalance_current"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Unbalance_current"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Unbalance_voltage"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Unbalance_voltage)
	{
		bDesState[N + "Unbalance_voltage"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Unbalance_voltage"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Phase_seq_error"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Phase_seq_error)
	{
		bDesState[N + "Phase_seq_error"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Phase_seq_error"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "TB_open_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.TB_open_failure)
	{
		bDesState[N + "TB_open_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "TB_open_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "TB_close_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.TB_close_failure)
	{
		bDesState[N + "TB_close_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "TB_close_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "TB_pos_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.TB_pos_failure)
	{
		bDesState[N + "TB_pos_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "TB_pos_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "MB_open_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.MB_open_failure)
	{
		bDesState[N + "MB_open_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "MB_open_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "MB_close_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.MB_close_failure)
	{
		bDesState[N + "MB_close_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "MB_close_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "MB_pos_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.MB_pos_failure)
	{
		bDesState[N + "MB_pos_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "MB_pos_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Mains_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Mains_failure)
	{
		bDesState[N + "Mains_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Mains_failure"] = ELEM_NORMA;

//Mains
	if(!work)
		bDesState[N + "ObSost"] = ELEM_NOT;
	else if(nAvar > 0)
		bDesState[N + "ObSost"] = ELEM_AVAR;
	else if(nError > 0)
		bDesState[N + "ObSost"] = ELEM_ERROR;
	else
		bDesState[N + "ObSost"] = ELEM_NORMA;
}

//-----------------------------------------------------------------------------
void DES_SERVICE::updateDesDgState(quint32 n_dg)
{
	DeifDgState & state = deif_dg[n_dg]->state();
	bool work = deif_dg[n_dg]->isActualState();

	QString N = QString("dg%1@").arg(n_dg + 1);

	quint32 nError = 0, nAvar = 0;

//02
	if(!work)
		bDesState[N + "GB_position"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.GB_position)
		bDesState[N + "GB_position"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "GB_position"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "MB_position"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.MB_position)
		bDesState[N + "MB_position"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "MB_position"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Block_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Block_mode)
	{
		bDesState[N + "Block_mode"].setText("ВКЛ") = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Block_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Test_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Test_mode)
	{
		bDesState[N + "Test_mode"].setText("ВКЛ") = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Test_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Manual_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Manual_mode)
	{
		bDesState[N + "Manual_mode"].setText("ВКЛ") = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Manual_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "SemiAuto_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.SemiAuto_mode)
	{
		bDesState[N + "SemiAuto_mode"].setText("ВКЛ") = ELEM_ERROR;
		nError++;
	}
	else
		bDesState[N + "SemiAuto_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Auto_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Auto_mode)
		bDesState[N + "Auto_mode"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "Auto_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Island"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Island)
		bDesState[N + "Island"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "Island"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Automatic_mains_failure_AMF"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Automatic_mains_failure_AMF)
		bDesState[N + "Automatic_mains_failure_AMF"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "Automatic_mains_failure_AMF"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "ATS_mode"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.ATS_mode)
		bDesState[N + "ATS_mode"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "ATS_mode"].setText("ОТКЛ") = ELEM_NORMA;

	if(!work)
		bDesState[N + "Load_take_over_LTO"].setText(" ") = ELEM_NOT;
	else if(state.State.RegState.Bits.Load_take_over_LTO)
		bDesState[N + "Load_take_over_LTO"].setText("ВКЛ") = ELEM_NORMA;
	else
		bDesState[N + "Load_take_over_LTO"].setText("ОТКЛ") = ELEM_NORMA;

//04
	if(!work)
		bDesState[N + "UL1_N_Generator_voltage"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "UL1_N_Generator_voltage"].setText(state.State.RegVoltageL1.textValue());
		bDesState[N + "UL1_N_Generator_voltage"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "UL2_N_Generator_voltage"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "UL2_N_Generator_voltage"].setText(state.State.RegVoltageL2.textValue());
		bDesState[N + "UL2_N_Generator_voltage"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "UL3_N_Generator_voltage"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "UL3_N_Generator_voltage"].setText(state.State.RegVoltageL3.textValue());
		bDesState[N + "UL3_N_Generator_voltage"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "fL1GEN_Generator_freq"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "fL1GEN_Generator_freq"].setText(state.State.RegFrequencyL1.textValue());
		bDesState[N + "fL1GEN_Generator_freq"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "fL2GEN_Generator_freq"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "fL2GEN_Generator_freq"].setText(state.State.RegFrequencyL2.textValue());
		bDesState[N + "fL2GEN_Generator_freq"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "fL3GEN_Generator_freq"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "fL3GEN_Generator_freq"].setText(state.State.RegFrequencyL3.textValue());
		bDesState[N + "fL3GEN_Generator_freq"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "PhiL1L2_Generator_phase"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "PhiL1L2_Generator_phase"].setText(state.State.RegPhaseL1L2.textValue());
		bDesState[N + "PhiL1L2_Generator_phase"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "PhiL2L3_Generator_phase"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "PhiL2L3_Generator_phase"].setText(state.State.RegPhaseL2L3.textValue());
		bDesState[N + "PhiL2L3_Generator_phase"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "PhiL3L1_Generator_phase"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "PhiL3L1_Generator_phase"].setText(state.State.RegPhaseL3L1.textValue());
		bDesState[N + "PhiL3L1_Generator_phase"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "IL1_Generator_current"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "IL1_Generator_current"].setText(state.State.RegCurrentL1.textValue());
		bDesState[N + "IL1_Generator_current"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "IL2_Generator_current"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "IL2_Generator_current"].setText(state.State.RegCurrentL2.textValue());
		bDesState[N + "IL2_Generator_current"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "IL3_Generator_current"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "IL3_Generator_current"].setText(state.State.RegCurrentL3.textValue());
		bDesState[N + "IL3_Generator_current"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "PGEN_Generator_total_active_power"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "PGEN_Generator_total_active_power"].setText(state.State.RegTotalActivePower.textValue());
		bDesState[N + "PGEN_Generator_total_active_power"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "QGEN_Generator_total_reactive_power"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "QGEN_Generator_total_reactive_power"].setText(state.State.RegTotalReactivePower.textValue());
		bDesState[N + "QGEN_Generator_total_reactive_power"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "SGEN_Generator_total_apparent_power"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "SGEN_Generator_total_apparent_power"].setText(state.State.RegTotalApparentPower.textValue());
		bDesState[N + "SGEN_Generator_total_apparent_power"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "EGEN_Total_energy_counter"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "EGEN_Total_energy_counter"].setText(state.State.RegTotalEnergyCounter.textValue());
		bDesState[N + "EGEN_Total_energy_counter"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "Generator_cos_phi"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "Generator_cos_phi"].setText(state.State.RegCosPhi.textValue());
		bDesState[N + "Generator_cos_phi"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "Running_time_Relative"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "Running_time_Relative"].setText(state.State.RegRunningTimeRelative.textValue());
		bDesState[N + "Running_time_Relative"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "Running_time_Absolute"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "Running_time_Absolute"].setText(state.State.RegRunningTimeAbsolute.textValue());
		bDesState[N + "Running_time_Absolute"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "USUPPLY_Supply_voltage"].setText(" ") = ELEM_NOT;
	else
	{
		bDesState[N + "USUPPLY_Supply_voltage"].setText(state.State.RegSupplyVoltage.textValue());
		bDesState[N + "USUPPLY_Supply_voltage"] = ELEM_NORMA;
	}

	if(!work)
		bDesState[N + "Service_timer_1_running_hours"].setText(" ") = ELEM_NOT;
	else
	{
		if(state.State.RegState2.Bits.Service_timer_1)
		{
			bDesState[N + "Service_timer_1_running_hours"] = ELEM_AVAR;
			nAvar++;
		}
		else
			bDesState[N + "Service_timer_1_running_hours"] = ELEM_NORMA;

		bDesState[N + "Service_timer_1_running_hours"].setText(state.State.RegServiceTimerHours1.textValue());
	}

	if(!work)
		bDesState[N + "Service_timer_1_running_days"].setText(" ") = ELEM_NOT;
	else
	{
		if(state.State.RegState2.Bits.Service_timer_1)
		{
			bDesState[N + "Service_timer_1_running_days"] = ELEM_AVAR;
			nAvar++;
		}
		else
			bDesState[N + "Service_timer_1_running_days"] = ELEM_NORMA;

		bDesState[N + "Service_timer_1_running_days"].setText(state.State.RegServiceTimerDays1.textValue());
	}

	if(!work)
		bDesState[N + "Service_timer_2_running_hours"].setText(" ") = ELEM_NOT;
	else
	{
		if(state.State.RegState2.Bits.Service_timer_2)
		{
			bDesState[N + "Service_timer_2_running_hours"] = ELEM_AVAR;
			nAvar++;
		}
		else
			bDesState[N + "Service_timer_2_running_hours"] = ELEM_NORMA;

		bDesState[N + "Service_timer_2_running_hours"].setText(state.State.RegServiceTimerHours2.textValue());
	}

	if(!work)
		bDesState[N + "Service_timer_2_running_days"].setText(" ") = ELEM_NOT;
	else
	{
		if(state.State.RegState2.Bits.Service_timer_1)
		{
			bDesState[N + "Service_timer_2_running_days"] = ELEM_AVAR;
			nAvar++;
		}
		else
			bDesState[N + "Service_timer_2_running_days"] = ELEM_NORMA;

		bDesState[N + "Service_timer_2_running_days"].setText(state.State.RegServiceTimerDays2.textValue());
	}

	if(!work)
		bDesState[N + "RPM_Running_feedback"].setText(" ") = ELEM_NOT;
	else
	{
		if(state.State.RegState2.Bits.Running_feedback_failure)
		{
			bDesState[N + "RPM_Running_feedback"] = ELEM_AVAR;
			nError++;
		}
		else
			bDesState[N + "RPM_Running_feedback"] = ELEM_NORMA;

		bDesState[N + "RPM_Running_feedback"].setText(state.State.RegRunningFeedback.textValue());
	}

//06
	if(!work)
		bDesState[N + "EIC_comm_error"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.EIC_comm_error)
	{
		bDesState[N + "EIC_comm_error"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "EIC_comm_error"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "EIC_warning"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.EIC_warning)
	{
		bDesState[N + "EIC_warning"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "EIC_warning"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "EIC_shutdown"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.EIC_shutdown)
	{
		bDesState[N + "EIC_shutdown"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "EIC_shutdown"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "EIC_overspeed"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.EIC_overspeed)
	{
		bDesState[N + "EIC_overspeed"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "EIC_overspeed"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "EIC_coolant_temp_1"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.EIC_coolant_temp_1)
	{
		bDesState[N + "EIC_coolant_temp_1"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "EIC_coolant_temp_1"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "EIC_coolant_temp_2"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.EIC_coolant_temp_2)
	{
		bDesState[N + "EIC_coolant_temp_2"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "EIC_coolant_temp_2"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "EIC_oil_pressure_1"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.EIC_oil_pressure_1)
	{
		bDesState[N + "EIC_oil_pressure_1"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "EIC_oil_pressure_1"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "EIC_oil_pressure_2"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.EIC_oil_pressure_2)
	{
		bDesState[N + "EIC_oil_pressure_2"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "EIC_oil_pressure_2"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "EIC_oil_temperature_1"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.EIC_oil_temperature_1)
	{
		bDesState[N + "EIC_oil_temperature_1"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "EIC_oil_temperature_1"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "EIC_oil_temperature_2"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.EIC_oil_temperature_2)
	{
		bDesState[N + "EIC_oil_temperature_2"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "EIC_oil_temperature_2"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Unbalance_current"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Unbalance_current)
	{
		bDesState[N + "Unbalance_current"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Unbalance_current"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Unbalance_voltage"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Unbalance_voltage)
	{
		bDesState[N + "Unbalance_voltage"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Unbalance_voltage"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Phase_seq_error"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Phase_seq_error)
	{
		bDesState[N + "Phase_seq_error"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Phase_seq_error"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "GB_open_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.GB_open_failure)
	{
		bDesState[N + "GB_open_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "GB_open_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "GB_close_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.GB_close_failure)
	{
		bDesState[N + "GB_close_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "GB_close_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "GB_pos_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.GB_pos_failure)
	{
		bDesState[N + "GB_pos_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "GB_pos_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "MB_open_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.MB_open_failure)
	{
		bDesState[N + "MB_open_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "MB_open_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "MB_close_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.MB_close_failure)
	{
		bDesState[N + "MB_close_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "MB_close_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "MB_pos_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.MB_pos_failure)
	{
		bDesState[N + "MB_pos_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "MB_pos_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Emergency_STOP"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Emergency_STOP)
	{
		bDesState[N + "Emergency_STOP"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Emergency_STOP"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Overspeed_1"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Overspeed_1)
	{
		bDesState[N + "Overspeed_1"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Overspeed_1"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Overspeed_2"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Overspeed_2)
	{
		bDesState[N + "Overspeed_2"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Overspeed_2"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Crank_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Crank_failure)
	{
		bDesState[N + "Crank_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Crank_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Running_feedback_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Running_feedback_failure)
	{
		bDesState[N + "Running_feedback_failure"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Running_feedback_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "MPU_wire_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.MPU_wire_failure)
	{
		bDesState[N + "MPU_wire_failure"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "MPU_wire_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Start_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Start_failure)
	{
		bDesState[N + "Start_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Start_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Stop_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Stop_failure)
	{
		bDesState[N + "Stop_failure"] = ELEM_AVAR;
		nAvar++;
	}
	else
		bDesState[N + "Stop_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Stop_coil_wire_break"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Stop_coil_wire_break)
	{
		bDesState[N + "Stop_coil_wire_break"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Stop_coil_wire_break"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Underspeed"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Underspeed_1)
	{
		bDesState[N + "Underspeed"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Underspeed"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Internal_comm_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Internal_comm_failure)
	{
		bDesState[N + "Internal_comm_failure"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Internal_comm_failure"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Engine_heater"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Engine_heater_1)
		bDesState[N + "Engine_heater"] = ELEM_NORMA;
	else
		bDesState[N + "Engine_heater"] = ELEM_NOT;

	if(!work)
		bDesState[N + "Battery_test"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Battery_test)
		bDesState[N + "Battery_test"] = ELEM_NORMA;
	else
		bDesState[N + "Battery_test"] = ELEM_NOT;

	if(!work)
		bDesState[N + "Battery_assymmetry_1"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Battery_assymmetry_1)
	{
		bDesState[N + "Battery_assymmetry_1"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Battery_assymmetry_1"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Battery_assymmetry_2"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Battery_assymmetry_2)
	{
		bDesState[N + "Battery_assymmetry_2"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Battery_assymmetry_2"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Max_ventilation_1"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Max_ventilation_1)
		bDesState[N + "Max_ventilation_1"] = ELEM_NORMA;
	else
		bDesState[N + "Max_ventilation_1"] = ELEM_NOT;

	if(!work)
		bDesState[N + "Max_ventilation_2"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Max_ventilation_2)
		bDesState[N + "Max_ventilation_2"] = ELEM_NORMA;
	else
		bDesState[N + "Max_ventilation_2"] = ELEM_NOT;

	if(!work)
		bDesState[N + "Fuel_pump_logic"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Fuel_pump_logic)
	{
		bDesState[N + "Fuel_pump_logic"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Fuel_pump_logic"] = ELEM_NORMA;

	if(!work)
		bDesState[N + "Engine_running"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Engine_running)
		bDesState[N + "Engine_running"] = ELEM_NORMA;
	else
		bDesState[N + "Engine_running"] = ELEM_NOT;

	if(!work)
		bDesState[N + "Generator_Hz_V_failure"] = ELEM_NOT;
	else if(state.State.RegState2.Bits.Generator_Hz_V_failure)
	{
		bDesState[N + "Generator_Hz_V_failure"] = ELEM_AVAR;
		nError++;
	}
	else
		bDesState[N + "Generator_Hz_V_failure"] = ELEM_NORMA;

//Dg
	if(!work)
		bDesState[N + "ObSost"] = ELEM_NOT;
	else if(nAvar > 0)
		bDesState[N + "ObSost"] = ELEM_AVAR;
	else if(nError > 0)
		bDesState[N + "ObSost"] = ELEM_ERROR;
	else
		bDesState[N + "ObSost"] = ELEM_NORMA;
}

//-----------------------------------------------------------------------------
