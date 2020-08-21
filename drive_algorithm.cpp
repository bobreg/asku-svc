#include "../common/logger.h"
#include "globalvar.h"
#include "drive_service.h"
#include "drive_vector.h"

// ------------------------------------------------------------------
void DRIVE_SERVICE::updateState()
{
	if(m_driveConfig.main)
	{
		verifyFirstCommands();

		if(m_driveConfig.first)
		{
			updatePortState();
			updateVectorState(0);
			updateVectorState(1);
			updateCommonState();

			emit sigState(bDriveState);
			syncToSlave();
		}
	}
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::updatePortState()
{
	if((!m_driveConfig.main) || (m_driveConfig.main && !m_driveConfig.first))
		return;

	if(!m_portState[MODBUS_MAIN_PORT].State.Bits.Opened)
		bDriveState["port1"] = ELEM_NOT;
	else if(m_portState[MODBUS_MAIN_PORT].State.Bits.NoData)
		bDriveState["port1"] = ELEM_AVAR;
	else if(m_portState[MODBUS_MAIN_PORT].State.Bits.BadData)
		bDriveState["port1"] = ELEM_ERROR;
	else
		bDriveState["port1"] = ELEM_NORMA;
		
	if(!m_portState[MODBUS_RESERVE_PORT].State.Bits.Opened)
		bDriveState["port2"] = ELEM_NOT;
	else if(m_portState[MODBUS_RESERVE_PORT].State.Bits.NoData)
		bDriveState["port2"] = ELEM_AVAR;
	else if(m_portState[MODBUS_RESERVE_PORT].State.Bits.BadData)
		bDriveState["port2"] = ELEM_ERROR;
	else
		bDriveState["port2"] = ELEM_NORMA;

	if(bDriveState["port1"] == ELEM_NOT)
		bDriveState["comm1"] = ELEM_AVAR;
	else
		bDriveState["comm1"] = ELEM_NORMA;

	if(bDriveState["port2"] == ELEM_NOT)
		bDriveState["comm2"] = ELEM_AVAR;
	else
		bDriveState["comm2"] = ELEM_NORMA;

	if((bDriveState["port1"] == ELEM_NOT || bDriveState["port1"] == ELEM_AVAR ) && (bDriveState["port2"] == ELEM_NOT || bDriveState["port2"] == ELEM_AVAR))
		bDriveState["portsFail"] = ELEM_AVAR;
	else if(bDriveState["port1"] == ELEM_NORMA && bDriveState["port2"] == ELEM_NORMA)
		bDriveState["portsFail"] = ELEM_NORMA;
	else
		bDriveState["portsFail"] = ELEM_ERROR;

	bool work1 = vector[0]->isActualState();
	bool work2 = vector[1]->isActualState();

	if(bDriveState["portsFail"] == ELEM_AVAR)
		bDriveState["device1"] = ELEM_NOT;
	else if(!work1 || (bDriveState["port1"] == ELEM_AVAR && bDriveState["port2"] == ELEM_AVAR))
		bDriveState["device1"] = ELEM_AVAR;
	else
		bDriveState["device1"] = ELEM_NORMA;

	if(bDriveState["portsFail"] == ELEM_AVAR)
		bDriveState["device2"] = ELEM_NOT;
	else if(!work2 || (bDriveState["port1"] == ELEM_AVAR && bDriveState["port2"] == ELEM_AVAR))
		bDriveState["device2"] = ELEM_AVAR;
	else
		bDriveState["device2"] = ELEM_NORMA;

	bDriveState["line1"] = bDriveState["line2"] = bDriveState["port1"];
	bDriveState["line3"] = bDriveState["line4"] = bDriveState["port2"];

//obSost Channel
	if(((bDriveState["port1"] == ELEM_NOT || bDriveState["port1"] == ELEM_AVAR ) && (bDriveState["port2"] == ELEM_NOT || bDriveState["port2"] == ELEM_AVAR)) ||
		(bDriveState["device1"] == ELEM_AVAR && bDriveState["device2"] == ELEM_AVAR))
		bDriveState["channel"] = ELEM_AVAR;
	else if(bDriveState["port1"] == ELEM_NORMA && bDriveState["port2"] == ELEM_NORMA &&
		bDriveState["device1"] == ELEM_NORMA && bDriveState["device2"] == ELEM_NORMA)
		bDriveState["channel"] = ELEM_NORMA;
	else
		bDriveState["channel"] = ELEM_ERROR;
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::updateCommonState()
{
	if((!m_driveConfig.main) || (m_driveConfig.main && !m_driveConfig.first))
		return;

	VectorState & state1 = vector[0]->state();
	VectorState & state2 = vector[1]->state();

	bool work1 = vector[0]->isActualState();
	bool work2 = vector[1]->isActualState();

//BanOfWork
	if(work1 && work2)
	{
		if(state1.State.RegProtect.Bits.ExternalBanOfWork || state2.State.RegProtect.Bits.ExternalBanOfWork ||
			state1.State.RegWarning.Bits.ExternalBanOfWork || state2.State.RegWarning.Bits.ExternalBanOfWork)
			bDriveState["ExternalBanOfWork"] = ELEM_AVAR;
		else
			bDriveState["ExternalBanOfWork"] = ELEM_NORMA;
	}
	else if(work1)
	{
		if(state1.State.RegProtect.Bits.ExternalBanOfWork || state1.State.RegWarning.Bits.ExternalBanOfWork)
			bDriveState["ExternalBanOfWork"] = ELEM_AVAR;
		else
			bDriveState["ExternalBanOfWork"] = ELEM_NORMA;
	}
	else if(work2)
	{
		if(state2.State.RegProtect.Bits.ExternalBanOfWork || state2.State.RegWarning.Bits.ExternalBanOfWork)
			bDriveState["ExternalBanOfWork"] = ELEM_AVAR;
		else
			bDriveState["ExternalBanOfWork"] = ELEM_NORMA;
	}
	else
	{
		bDriveState["ExternalBanOfWork"] = ELEM_NOT;
	}

//servo
	if(work1 && !state1.State.RegState.Bits.Fail &&
				state1.State.RegState.Bits.WorkingAlg &&
				state1.State.RegState.Bits.InvertorOn &&
				state1.State.RegState.Bits.ModeVectorCt &&	//!!
				state1.State.RegState.Bits.PowerReady)
		bDriveState["servo1"] = ELEM_NORMA;
	else
		bDriveState["servo1"] = ELEM_NOT;

	if(work2 && !state2.State.RegState.Bits.Fail &&
				state2.State.RegState.Bits.WorkingAlg &&
				state2.State.RegState.Bits.InvertorOn &&
				state2.State.RegState.Bits.ModeVectorCt &&	//!!
				state2.State.RegState.Bits.PowerReady)
		bDriveState["servo2"] = ELEM_NORMA;
	else
		bDriveState["servo2"] = ELEM_NOT;

	if(bDriveState["servo1"] == ELEM_NORMA || bDriveState["servo2"] == ELEM_NORMA)
			bDriveState["servo"] = ELEM_NORMA;
		else
			bDriveState["servo"] = ELEM_NOT;

//cmdOn
	bDriveState["cmdServoOn"] = m_driveConfig.start ? ELEM_NORMA : ELEM_NOT;

//124sg01
	if(work1 && 
		(state1.State.RegOverheat.Bits.Sensor1 || state1.State.RegOverheat.Bits.Sensor2 ||
		state1.State.RegOverheat.Bits.Sensor3 || state1.State.RegOverheat.Bits.Sensor4))
		bDriveState["124sg01_1"] = ELEM_AVAR;
	else if(work1 && 
		!state1.State.RegOverheat.Bits.Sensor1 && !state1.State.RegOverheat.Bits.Sensor2 &&
		!state1.State.RegOverheat.Bits.Sensor3 && !state1.State.RegOverheat.Bits.Sensor4 &&
		state1.State.RegState.Bits.InvertorOn)
		bDriveState["124sg01_1"] = ELEM_NORMA;
	else
		bDriveState["124sg01_1"] = ELEM_NOT;

	if(work2 && 
		(state2.State.RegOverheat.Bits.Sensor1 || state2.State.RegOverheat.Bits.Sensor2 ||
		state2.State.RegOverheat.Bits.Sensor3 || state2.State.RegOverheat.Bits.Sensor4))
		bDriveState["124sg01_2"] = ELEM_AVAR;
	else if(work2 && 
		!state2.State.RegOverheat.Bits.Sensor1 && !state2.State.RegOverheat.Bits.Sensor2 &&
		!state2.State.RegOverheat.Bits.Sensor3 && !state2.State.RegOverheat.Bits.Sensor4 &&
		state2.State.RegState.Bits.InvertorOn)
		bDriveState["124sg01_2"] = ELEM_NORMA;
	else
		bDriveState["124sg01_2"] = ELEM_NOT;

	if(bDriveState["124sg01_1"] == ELEM_AVAR && bDriveState["124sg01_2"] == ELEM_AVAR)
		bDriveState["125sg02"] = ELEM_AVAR;
	else if(bDriveState["124sg01_1"] == ELEM_AVAR || bDriveState["124sg01_2"] == ELEM_AVAR)
		bDriveState["125sg02"] = ELEM_ERROR;
	else if(bDriveState["124sg01_1"] == ELEM_NORMA || bDriveState["124sg01_2"] == ELEM_NORMA)
		bDriveState["125sg02"] = ELEM_NORMA;
	else
		bDriveState["125sg02"] = ELEM_NOT;

//mest
	if((work1 && !state1.State.RegState.Bits.NoLocal) || (work2 && !state2.State.RegState.Bits.NoLocal))
		bDriveState["mest"] = ELEM_MEST;
	else
		bDriveState["mest"] = ELEM_NOT;

	if(work1 && !state1.State.RegState.Bits.NoLocal)
		bDriveState["mest1"] = ELEM_MEST;
	else
		bDriveState["mest1"] = ELEM_NOT;

	if(work2 && !state2.State.RegState.Bits.NoLocal)
		bDriveState["mest2"] = ELEM_MEST;
	else
		bDriveState["mest2"] = ELEM_NOT;

//124yy03
	bool complex_norma_1 =	 state1.State.RegState.Bits.Ready &&
							!state1.State.RegState.Bits.Fail &&
							!state1.State.RegState.Bits.Warning &&
							!state1.State.RegOverheat.Bits.Invertor &&
							 state1.State.RegState.Bits.PowerReady &&
							!state1.State.RegHardware.Bits.SensorAbsBreak &&
							!state1.State.RegHardware.Bits.ErrorAbsLabel;

	bool complex_norma_2 =	 state2.State.RegState.Bits.Ready &&
							!state2.State.RegState.Bits.Fail &&
							!state2.State.RegState.Bits.Warning &&
							!state2.State.RegOverheat.Bits.Invertor &&
							 state2.State.RegState.Bits.PowerReady &&
							!state2.State.RegHardware.Bits.SensorAbsBreak &&
							!state2.State.RegHardware.Bits.ErrorAbsLabel;

	bool complex_error_1 =	 state1.State.RegState.Bits.Warning;
	bool complex_error_2 =	 state2.State.RegState.Bits.Warning;

	if(bDriveState["port1"] != ELEM_NORMA && bDriveState["port2"] != ELEM_NORMA)
		bDriveState["124yy03_1"] = ELEM_NOT;
	else if(work1 && complex_norma_1)
		bDriveState["124yy03_1"] = ELEM_NORMA;
	else if(work1 && complex_error_1)
		bDriveState["124yy03_1"] = ELEM_ERROR;
	else
		bDriveState["124yy03_1"] = ELEM_AVAR;

	if(bDriveState["port1"] != ELEM_NORMA && bDriveState["port2"] != ELEM_NORMA)
		bDriveState["124yy03_2"] = ELEM_NOT;
	else if(work2 && complex_norma_2)
		bDriveState["124yy03_2"] = ELEM_NORMA;
	else if(work2 && complex_error_2)
		bDriveState["124yy03_2"] = ELEM_ERROR;
	else
		bDriveState["124yy03_2"] = ELEM_AVAR;

	if(bDriveState["124yy03_1"] == ELEM_NOT && bDriveState["124yy03_2"] == ELEM_NOT)
		bDriveState["124yy03"] = ELEM_NOT;
	else if(bDriveState["124yy03_1"] == ELEM_AVAR && bDriveState["124yy03_2"] == ELEM_AVAR)
		bDriveState["124yy03"] = ELEM_AVAR;
	else if(bDriveState["124yy03_1"] == ELEM_AVAR || bDriveState["124yy03_2"] == ELEM_AVAR ||
			bDriveState["124yy03_1"] == ELEM_ERROR || bDriveState["124yy03_2"] == ELEM_ERROR)
		bDriveState["124yy03"] = ELEM_ERROR;
	else if(bDriveState["124yy03_1"] == ELEM_NORMA || bDriveState["124yy03_2"] == ELEM_NORMA)
		bDriveState["124yy03"] = ELEM_NORMA;
	else
		bDriveState["124yy03"] = ELEM_NOT;

//obSost
	if(bDriveState["124yy03"] == ELEM_AVAR)
		bDriveState["obSost"] = ELEM_AVAR;
	else if(bDriveState["servo"] == ELEM_NORMA && bDriveState["124yy03"] == ELEM_NORMA)
		bDriveState["obSost"] = ELEM_NORMA;
	else if(bDriveState["124yy03"] == ELEM_NOT)
		bDriveState["obSost"] = ELEM_NOT;
	else
		bDriveState["obSost"] = ELEM_ERROR;
}

// ------------------------------------------------------------------
void DRIVE_SERVICE::updateVectorState(quint32 n_vector)
{
	if((!m_driveConfig.main) || (m_driveConfig.main && !m_driveConfig.first))
		return;

	VectorState & state = vector[n_vector]->state();
	bool work = vector[n_vector]->isActualState();

	QString N = QString("drive%1@").arg(n_vector + 1);

	if(work && !state.State.RegState.Bits.NoLocal)
		bDriveState[N + "mest"] = ELEM_MEST;
	else
		bDriveState[N + "mest"] = ELEM_NOT;

	if(!work)
		bDriveState[N + "Ready"] = ELEM_NOT;
	else if(state.State.RegState.Bits.Ready)
		bDriveState[N + "Ready"] = ELEM_NORMA;
	else
		bDriveState[N + "Ready"] = ELEM_AVAR;

	if(!work)
		bDriveState[N + "Fail"] = ELEM_NOT;
	else if(state.State.RegState.Bits.Fail)
		bDriveState[N + "Fail"] = ELEM_AVAR;
	else
		bDriveState[N + "Fail"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "Main"] = ELEM_NOT;
	else if(state.State.RegState.Bits.Main)
		bDriveState[N + "Main"] = ELEM_NORMA;
	else
		bDriveState[N + "Main"] = ELEM_NOT;

	if(!work)
		bDriveState[N + "Warning"] = ELEM_NOT;
	else if(state.State.RegState.Bits.Warning)
		bDriveState[N + "Warning"] = ELEM_AVAR;
	else
		bDriveState[N + "Warning"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "WorkingAlg"] = ELEM_NOT;
	else if(state.State.RegState.Bits.WorkingAlg)
		bDriveState[N + "WorkingAlg"] = ELEM_NORMA;
	else
		bDriveState[N + "WorkingAlg"] = ELEM_NOT;

	if(!work)
		bDriveState[N + "OVERHEAT"] = ELEM_NOT;
	else if(state.State.RegOverheat.Bits.Sensor1 || 
			state.State.RegOverheat.Bits.Sensor2 ||
			state.State.RegOverheat.Bits.Sensor3 ||
			state.State.RegOverheat.Bits.Sensor4)
		bDriveState[N + "OVERHEAT"] = ELEM_AVAR;
	else
		bDriveState[N + "OVERHEAT"] = ELEM_NORMA;


	if(!work)
		bDriveState[N + "INVERTOR"] = ELEM_NOT;
	else if(state.State.RegOverheat.Bits.Invertor)
		bDriveState[N + "INVERTOR"] = ELEM_AVAR;
	else if(state.State.RegState.Bits.InvertorOn)
		bDriveState[N + "INVERTOR"] = ELEM_NORMA;
	else
		bDriveState[N + "INVERTOR"] = ELEM_NOT;

	if(!work)
		bDriveState[N + "PowerReady"] = ELEM_NOT;
	else if(state.State.RegState.Bits.PowerReady)
		bDriveState[N + "PowerReady"] = ELEM_NORMA;
	else
		bDriveState[N + "PowerReady"] = ELEM_AVAR;

	if(!work)
		bDriveState[N + "ModeVectorCt"] = ELEM_NOT;
	else if(state.State.RegState.Bits.ModeVectorCt)
		bDriveState[N + "ModeVectorCt"] = ELEM_NORMA;
	else
		bDriveState[N + "ModeVectorCt"] = ELEM_NOT;

	if(!work)
		bDriveState[N + "ModeTestUF"] = ELEM_NOT;
	else if(state.State.RegState.Bits.ModeTestUF)
		bDriveState[N + "ModeTestUF"] = ELEM_NORMA;
	else
		bDriveState[N + "ModeTestUF"] = ELEM_NOT;

	if(!work)
		bDriveState[N + "ModeTestCur"] = ELEM_NOT;
	else if(state.State.RegState.Bits.ModeTestCur)
		bDriveState[N + "ModeTestCur"] = ELEM_NORMA;
	else
		bDriveState[N + "ModeTestCur"] = ELEM_NOT;

	if(!work)
		bDriveState[N + "ModeTestSet"] = ELEM_NOT;
	else if(state.State.RegState.Bits.ModeTestSet)
		bDriveState[N + "ModeTestSet"] = ELEM_NORMA;
	else
		bDriveState[N + "ModeTestSet"] = ELEM_NOT;

	if(!work)
		bDriveState[N + "ModePosition"] = ELEM_NOT;
	else if(state.State.RegState.Bits.ModePosition)
		bDriveState[N + "ModePosition"] = ELEM_NORMA;
	else
		bDriveState[N + "ModePosition"] = ELEM_NOT;

	if(!work)
		bDriveState[N + "SensorAbs"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.SensorAbsBreak || state.State.RegHardware.Bits.ErrorAbsLabel)
		bDriveState[N + "SensorAbs"] = ELEM_AVAR;
	else
		bDriveState[N + "SensorAbs"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "SensorInc"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.SensorIncBreak || state.State.RegHardware.Bits.ErrorIndexLabel)
		bDriveState[N + "SensorInc"] = ELEM_AVAR;
	else
		bDriveState[N + "SensorInc"] = ELEM_NORMA;

//REG_PROTECT
	if(!work)
		bDriveState[N + "InvCurrentLimit"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.InvCurrentLimit)
		bDriveState[N + "InvCurrentLimit"] = ELEM_AVAR;
	else
		bDriveState[N + "InvCurrentLimit"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "UdBelowMinimal"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.UdBelowMinimal)
		bDriveState[N + "UdBelowMinimal"] = ELEM_AVAR;
	else
		bDriveState[N + "UdBelowMinimal"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "UdAboveMaximum"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.UdAboveMaximum)
		bDriveState[N + "UdAboveMaximum"] = ELEM_AVAR;
	else
		bDriveState[N + "UdAboveMaximum"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "UdAboveLimit"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.UdAboveLimit)
		bDriveState[N + "UdAboveLimit"] = ELEM_AVAR;
	else
		bDriveState[N + "UdAboveLimit"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "CurrentBelowMinimal"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.CurrentBelowMinimal)
		bDriveState[N + "CurrentBelowMinimal"] = ELEM_AVAR;
	else
		bDriveState[N + "CurrentBelowMinimal"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "CurrentAboveMaximum"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.CurrentAboveMaximum)
		bDriveState[N + "CurrentAboveMaximum"] = ELEM_AVAR;
	else
		bDriveState[N + "CurrentAboveMaximum"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "CurrentAboveLimit"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.CurrentAboveLimit)
		bDriveState[N + "CurrentAboveLimit"] = ELEM_AVAR;
	else
		bDriveState[N + "CurrentAboveLimit"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "CurrentDissymetric"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.CurrentDissymetric)
		bDriveState[N + "CurrentDissymetric"] = ELEM_AVAR;
	else
		bDriveState[N + "CurrentDissymetric"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "UdChargeFail"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.UdChargeFail)
		bDriveState[N + "UdChargeFail"] = ELEM_AVAR;
	else
		bDriveState[N + "UdChargeFail"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "MainCircuitOnFail"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.MainCircuitOnFail)
		bDriveState[N + "MainCircuitOnFail"] = ELEM_AVAR;
	else
		bDriveState[N + "MainCircuitOnFail"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "LostLinkOfControl"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.LostLinkOfControl)
		bDriveState[N + "LostLinkOfControl"] = ELEM_AVAR;
	else
		bDriveState[N + "LostLinkOfControl"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "EmergencyStop"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.EmergencyStop)
		bDriveState[N + "EmergencyStop"] = ELEM_AVAR;
	else
		bDriveState[N + "EmergencyStop"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "ExternalBanOfWork"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.ExternalBanOfWork)
		bDriveState[N + "ExternalBanOfWork"] = ELEM_AVAR;
	else
		bDriveState[N + "ExternalBanOfWork"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "DeviationOfRotorSpeed"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.DeviationOfRotorSpeed)
		bDriveState[N + "DeviationOfRotorSpeed"] = ELEM_AVAR;
	else
		bDriveState[N + "DeviationOfRotorSpeed"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "DeviationOfRotorPosition"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.DeviationOfRotorPosition)
		bDriveState[N + "DeviationOfRotorPosition"] = ELEM_AVAR;
	else
		bDriveState[N + "DeviationOfRotorPosition"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "TrailerSensorSet"] = ELEM_NOT;
	else if(state.State.RegProtect.Bits.TrailerSensorSet)
		bDriveState[N + "TrailerSensorSet"] = ELEM_AVAR;
	else
		bDriveState[N + "TrailerSensorSet"] = ELEM_NORMA;

//REG_PROTECT_ADD
	if(!work)
		bDriveState[N + "SpeedDecrease"] = ELEM_NOT;
	else if(state.State.RegProtectAdd.Bits.SpeedDecrease)
		bDriveState[N + "SpeedDecrease"] = ELEM_AVAR;
	else
		bDriveState[N + "SpeedDecrease"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "SpeedDecreaseUd"] = ELEM_NOT;
	else if(state.State.RegProtectAdd.Bits.SpeedDecreaseUd)
		bDriveState[N + "SpeedDecreaseUd"] = ELEM_AVAR;
	else
		bDriveState[N + "SpeedDecreaseUd"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "CurrentLeekage"] = ELEM_NOT;
	else if(state.State.RegProtectAdd.Bits.CurrentLeekage)
		bDriveState[N + "CurrentLeekage"] = ELEM_AVAR;
	else
		bDriveState[N + "CurrentLeekage"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "SelfExcitation"] = ELEM_NOT;
	else if(state.State.RegProtectAdd.Bits.SelfExcitation)
		bDriveState[N + "SelfExcitation"] = ELEM_AVAR;
	else
		bDriveState[N + "SelfExcitation"] = ELEM_NORMA;

//REG_OVERHEAT
	if(!work)
		bDriveState[N + "Sensor1"] = ELEM_NOT;
	else if(state.State.RegOverheat.Bits.Sensor1)
		bDriveState[N + "Sensor1"] = ELEM_AVAR;
	else
		bDriveState[N + "Sensor1"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "Sensor2"] = ELEM_NOT;
	else if(state.State.RegOverheat.Bits.Sensor2)
		bDriveState[N + "Sensor2"] = ELEM_AVAR;
	else
		bDriveState[N + "Sensor2"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "Sensor3"] = ELEM_NOT;
	else if(state.State.RegOverheat.Bits.Sensor3)
		bDriveState[N + "Sensor3"] = ELEM_AVAR;
	else
		bDriveState[N + "Sensor3"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "Sensor4"] = ELEM_NOT;
	else if(state.State.RegOverheat.Bits.Sensor4)
		bDriveState[N + "Sensor4"] = ELEM_AVAR;
	else
		bDriveState[N + "Sensor4"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "OverheatInvertor"] = ELEM_NOT;
	else if(state.State.RegOverheat.Bits.Invertor)
		bDriveState[N + "OverheatInvertor"] = ELEM_AVAR;
	else
		bDriveState[N + "OverheatInvertor"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "TimeCurrent"] = ELEM_NOT;
	else if(state.State.RegOverheat.Bits.TimeCurrent)
		bDriveState[N + "TimeCurrent"] = ELEM_AVAR;
	else
		bDriveState[N + "TimeCurrent"] = ELEM_NORMA;

//REG_HARDWARE
	if(!work)
		bDriveState[N + "FlashMemory"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.FlashMemory)
		bDriveState[N + "FlashMemory"] = ELEM_AVAR;
	else
		bDriveState[N + "FlashMemory"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "PowerOfCtrlModule"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.PowerOfCtrlModule)
		bDriveState[N + "PowerOfCtrlModule"] = ELEM_AVAR;
	else
		bDriveState[N + "PowerOfCtrlModule"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "LinkXilinxToCpu"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.LinkXilinxToCpu)
		bDriveState[N + "LinkXilinxToCpu"] = ELEM_AVAR;
	else
		bDriveState[N + "LinkXilinxToCpu"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "LinkCpuToXilinx"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.LinkCpuToXilinx)
		bDriveState[N + "LinkCpuToXilinx"] = ELEM_AVAR;
	else
		bDriveState[N + "LinkCpuToXilinx"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "Adp"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.ADP)
		bDriveState[N + "Adp"] = ELEM_AVAR;
	else
		bDriveState[N + "Adp"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "Can"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.CAN)
		bDriveState[N + "Can"] = ELEM_AVAR;
	else
		bDriveState[N + "Can"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "InvertorPower"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.InvertorPower)
		bDriveState[N + "InvertorPower"] = ELEM_AVAR;
	else
		bDriveState[N + "InvertorPower"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "SensorIncBreak"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.SensorIncBreak)
		bDriveState[N + "SensorIncBreak"] = ELEM_AVAR;
	else
		bDriveState[N + "SensorIncBreak"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "ErrorIncLabel"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.ErrorIndexLabel)
		bDriveState[N + "ErrorIncLabel"] = ELEM_AVAR;
	else
		bDriveState[N + "ErrorIncLabel"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "SensorAbsBreak"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.SensorAbsBreak)
		bDriveState[N + "SensorAbsBreak"] = ELEM_AVAR;
	else
		bDriveState[N + "SensorAbsBreak"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "ErrorAbsLabel"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.ErrorAbsLabel)
		bDriveState[N + "ErrorAbsLabel"] = ELEM_AVAR;
	else
		bDriveState[N + "ErrorAbsLabel"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "RestartSoftware"] = ELEM_NOT;
	else if(state.State.RegHardware.Bits.RestartSoftware)
		bDriveState[N + "RestartSoftware"] = ELEM_AVAR;
	else
		bDriveState[N + "RestartSoftware"] = ELEM_NORMA;

//REG_SOFTWARE
	if(!work)
		bDriveState[N + "ErrorInfoStruct"] = ELEM_NOT;
	else if(state.State.RegSoftware.Bits.ErrorInfoStruct)
		bDriveState[N + "ErrorInfoStruct"] = ELEM_AVAR;
	else
		bDriveState[N + "ErrorInfoStruct"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "ErrorCRC1"] = ELEM_NOT;
	else if(state.State.RegSoftware.Bits.ErrorCRC1)
		bDriveState[N + "ErrorCRC1"] = ELEM_AVAR;
	else
		bDriveState[N + "ErrorCRC1"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "ErrorCRC2"] = ELEM_NOT;
	else if(state.State.RegSoftware.Bits.ErrorCRC2)
		bDriveState[N + "ErrorCRC2"] = ELEM_AVAR;
	else
		bDriveState[N + "ErrorCRC2"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "ErrorCRC3"] = ELEM_NOT;
	else if(state.State.RegSoftware.Bits.ErrorCRC3)
		bDriveState[N + "ErrorCRC3"] = ELEM_AVAR;
	else
		bDriveState[N + "ErrorCRC3"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "ParameterConflict"] = ELEM_NOT;
	else if(state.State.RegSoftware.Bits.ParameterConflict)
		bDriveState[N + "ParameterConflict"] = ELEM_AVAR;
	else
		bDriveState[N + "ParameterConflict"] = ELEM_NORMA;

//REG_WARNING
	if(!work)
		bDriveState[N + "VoltageLow"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.VoltageLow)
		bDriveState[N + "VoltageLow"] = ELEM_AVAR;
	else
		bDriveState[N + "VoltageLow"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "VoltageBelowMinimal"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.VoltageBelowMinimal)
		bDriveState[N + "VoltageBelowMinimal"] = ELEM_AVAR;
	else
		bDriveState[N + "VoltageBelowMinimal"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "VoltageAboveMaximal"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.VoltageAboveMaximal)
		bDriveState[N + "VoltageAboveMaximal"] = ELEM_AVAR;
	else
		bDriveState[N + "VoltageAboveMaximal"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "CurrentAboveMaximum_"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.CurrentAboveMaximum)
		bDriveState[N + "CurrentAboveMaximum_"] = ELEM_AVAR;
	else
		bDriveState[N + "CurrentAboveMaximum_"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "CurrentBelowMinimal_"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.CurrentBelowMinimal)
		bDriveState[N + "CurrentBelowMinimal_"] = ELEM_AVAR;
	else
		bDriveState[N + "CurrentBelowMinimal_"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "CurrentDissymetric_"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.CurrentDissymetric)
		bDriveState[N + "CurrentDissymetric_"] = ELEM_AVAR;
	else
		bDriveState[N + "CurrentDissymetric_"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "PowerContactorOpen"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.PowerContactorOpen)
		bDriveState[N + "PowerContactorOpen"] = ELEM_AVAR;
	else
		bDriveState[N + "PowerContactorOpen"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "ReserveFail"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.ReserveFail)
		bDriveState[N + "ReserveFail"] = ELEM_AVAR;
	else
		bDriveState[N + "ReserveFail"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "ErrorIndexLabel_"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.ErrorIndexLabel)
		bDriveState[N + "ErrorIndexLabel_"] = ELEM_AVAR;
	else
		bDriveState[N + "ErrorIndexLabel_"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "DebugMode"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.DebugMode)
		bDriveState[N + "DebugMode"] = ELEM_AVAR;
	else
		bDriveState[N + "DebugMode"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "ExternalBanOfWork_"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.ExternalBanOfWork)
		bDriveState[N + "ExternalBanOfWork_"] = ELEM_AVAR;
	else
		bDriveState[N + "ExternalBanOfWork_"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "SpeedDecrease_"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.SpeedDecrease)
		bDriveState[N + "SpeedDecrease_"] = ELEM_AVAR;
	else
		bDriveState[N + "SpeedDecrease_"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "SpeedDecreaseUd_"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.SpeedDecreaseUd)
		bDriveState[N + "SpeedDecreaseUd_"] = ELEM_AVAR;
	else
		bDriveState[N + "SpeedDecreaseUd_"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "MomentAboveSet"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.MomentAboveSet)
		bDriveState[N + "MomentAboveSet"] = ELEM_AVAR;
	else
		bDriveState[N + "MomentAboveSet"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "LeftTrailerSensorSet"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.LeftTrailerSensorSet)
		bDriveState[N + "LeftTrailerSensorSet"] = ELEM_AVAR;
	else
		bDriveState[N + "LeftTrailerSensorSet"] = ELEM_NORMA;

	if(!work)
		bDriveState[N + "RightTrailerSensorSet"] = ELEM_NOT;
	else if(state.State.RegWarning.Bits.RightTrailerSensorSet)
		bDriveState[N + "RightTrailerSensorSet"] = ELEM_AVAR;
	else
		bDriveState[N + "RightTrailerSensorSet"] = ELEM_NORMA;
}

//-----------------------------------------------------------------------------
