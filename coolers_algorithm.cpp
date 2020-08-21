#include "../common/logger.h"
#include "globalvar.h"
#include "coolers_service.h"
#include "coolers_vesper.h"

// ------------------------------------------------------------------
void COOLERS_SERVICE::updateState()
{
	verifyFirstCommands();
	updatePortState();
	updateVesperState(0);
	updateVesperState(1);
	updateVesperState(2);
	updateVesperState(3);
	updateCommonState();

	emit sigState(bCoolerState);
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::updatePortState()
{
	if(!m_portState[MODBUS_MAIN_PORT].State.Bits.Opened)
		bCoolerState["port1"] = ELEM_NOT;
	else if(m_portState[MODBUS_MAIN_PORT].State.Bits.NoData)
		bCoolerState["port1"] = ELEM_AVAR;
	else if(m_portState[MODBUS_MAIN_PORT].State.Bits.BadData)
		bCoolerState["port1"] = ELEM_ERROR;
	else
		bCoolerState["port1"] = ELEM_NORMA;

	if(!m_portState[MODBUS_RESERVE_PORT].State.Bits.Opened)
		bCoolerState["port2"] = ELEM_NOT;
	else if(m_portState[MODBUS_RESERVE_PORT].State.Bits.NoData)
		bCoolerState["port2"] = ELEM_AVAR;
	else if(m_portState[MODBUS_RESERVE_PORT].State.Bits.BadData)
		bCoolerState["port2"] = ELEM_ERROR;
	else
		bCoolerState["port2"] = ELEM_NORMA;

	if(bCoolerState["port1"] == ELEM_NOT)
		bCoolerState["comm1"] = ELEM_AVAR;
	else
		bCoolerState["comm1"] = ELEM_NORMA;

	if(bCoolerState["port2"] == ELEM_NOT)
		bCoolerState["comm2"] = ELEM_AVAR;
	else
		bCoolerState["comm2"] = ELEM_NORMA;

	if((bCoolerState["port1"] == ELEM_NOT || bCoolerState["port1"] == ELEM_AVAR ) && (bCoolerState["port2"] == ELEM_NOT || bCoolerState["port2"] == ELEM_AVAR))
		bCoolerState["portsFail"] = ELEM_AVAR;
	else if(bCoolerState["port1"] == ELEM_NORMA && bCoolerState["port2"] == ELEM_NORMA)
		bCoolerState["portsFail"] = ELEM_NORMA;
	else
		bCoolerState["portsFail"] = ELEM_ERROR;

	bool work1 = vesper[0]->isActualState();
	bool work2 = vesper[1]->isActualState();
	bool work3 = vesper[2]->isActualState();
	bool work4 = vesper[3]->isActualState();

	if(bCoolerState["portsFail"] == ELEM_AVAR)
		bCoolerState["device1"] = ELEM_NOT;
	else if(!work1 || (bCoolerState["port1"] == ELEM_AVAR && bCoolerState["port2"] == ELEM_AVAR))
		bCoolerState["device1"] = ELEM_AVAR;
	else
		bCoolerState["device1"] = ELEM_NORMA;

	if(bCoolerState["portsFail"] == ELEM_AVAR)
		bCoolerState["device2"] = ELEM_NOT;
	else if(!work2 || (bCoolerState["port1"] == ELEM_AVAR && bCoolerState["port2"] == ELEM_AVAR))
		bCoolerState["device2"] = ELEM_AVAR;
	else
		bCoolerState["device2"] = ELEM_NORMA;

	if(bCoolerState["portsFail"] == ELEM_AVAR)
		bCoolerState["device3"] = ELEM_NOT;
	else if(!work3 || (bCoolerState["port1"] == ELEM_AVAR && bCoolerState["port2"] == ELEM_AVAR))
		bCoolerState["device3"] = ELEM_AVAR;
	else
		bCoolerState["device3"] = ELEM_NORMA;

	if(bCoolerState["portsFail"] == ELEM_AVAR)
		bCoolerState["device4"] = ELEM_NOT;
	else if(!work4 || (bCoolerState["port1"] == ELEM_AVAR && bCoolerState["port2"] == ELEM_AVAR))
		bCoolerState["device4"] = ELEM_AVAR;
	else
		bCoolerState["device4"] = ELEM_NORMA;

	bCoolerState["line1"] = bCoolerState["line2"] = bCoolerState["port1"];
	bCoolerState["line3"] = bCoolerState["line4"] = bCoolerState["port2"];

//obSost Channel
	if(bCoolerState["portsFail"] == ELEM_AVAR ||
		((bCoolerState["device1"] == ELEM_AVAR && bCoolerState["device2"] == ELEM_AVAR) || (bCoolerState["device3"] == ELEM_AVAR && bCoolerState["device4"] == ELEM_AVAR)))
		bCoolerState["channel"] = ELEM_AVAR;
	else if(bCoolerState["port1"] == ELEM_NORMA && bCoolerState["port2"] == ELEM_NORMA &&
		bCoolerState["device1"] == ELEM_NORMA && bCoolerState["device2"] == ELEM_NORMA && bCoolerState["device3"] == ELEM_NORMA && bCoolerState["device4"] == ELEM_NORMA)
		bCoolerState["channel"] = ELEM_NORMA;
	else
		bCoolerState["channel"] = ELEM_ERROR;
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::updateCommonState()
{
//obSostSVO1
	if(bCoolerState["vesper1@ObSost"] == ELEM_NOT && bCoolerState["vesper2@ObSost"] == ELEM_NOT)
		bCoolerState["SVO1"] = ELEM_NOT;
	else if(bCoolerState["vesper1@ObSost"] == ELEM_AVAR && bCoolerState["vesper2@ObSost"] == ELEM_AVAR)
		bCoolerState["SVO1"] = ELEM_AVAR;
	else if(bCoolerState["vesper1@ObSost"] == ELEM_NORMA && bCoolerState["vesper2@ObSost"] == ELEM_NORMA &&
			(bCoolerState["vesper1@Venilator"] == ELEM_NORMA || bCoolerState["vesper2@Ventilator"] == ELEM_NORMA))
		bCoolerState["SVO1"] = ELEM_NORMA;
	else if(bCoolerState["vesper1@ObSost"] == ELEM_NORMA && bCoolerState["vesper2@ObSost"] == ELEM_NORMA)
		bCoolerState["SVO1"] = ELEM_NOT;
	else
		bCoolerState["SVO1"] = ELEM_ERROR;

//obSostSVO2
	if(bCoolerState["vesper3@ObSost"] == ELEM_NOT && bCoolerState["vesper4@ObSost"] == ELEM_NOT)
		bCoolerState["SVO2"] = ELEM_NOT;
	else if(bCoolerState["vesper3@ObSost"] == ELEM_AVAR && bCoolerState["vesper4@ObSost"] == ELEM_AVAR)
		bCoolerState["SVO2"] = ELEM_AVAR;
	else if(bCoolerState["vesper3@ObSost"] == ELEM_NORMA && bCoolerState["vesper4@ObSost"] == ELEM_NORMA &&
			(bCoolerState["vesper3@Ventilator"] == ELEM_NORMA || bCoolerState["vesper4@Ventilator"] == ELEM_NORMA))
		bCoolerState["SVO2"] = ELEM_NORMA;
	else if(bCoolerState["vesper3@ObSost"] == ELEM_NORMA && bCoolerState["vesper4@ObSost"] == ELEM_NORMA)
		bCoolerState["SVO2"] = ELEM_NOT;
	else
		bCoolerState["SVO2"] = ELEM_ERROR;

//obSost
	if(bCoolerState["SVO1"] == ELEM_NOT && bCoolerState["SVO2"] == ELEM_NOT)
		bCoolerState["obSost"] = ELEM_NOT;
	else if(bCoolerState["SVO1"] == ELEM_AVAR || bCoolerState["SVO2"] == ELEM_AVAR)
		bCoolerState["obSost"] = ELEM_AVAR;
	else if(bCoolerState["SVO1"] == ELEM_NORMA && bCoolerState["SVO2"] == ELEM_NORMA)
		bCoolerState["obSost"] = ELEM_NORMA;
	else
		bCoolerState["obSost"] = ELEM_ERROR;
}

// ------------------------------------------------------------------
void COOLERS_SERVICE::updateVesperState(quint32 n_vesper)
{
	VesperState & state = vesper[n_vesper]->state();
	bool work = vesper[n_vesper]->isActualState();

	QString N = QString("vesper%1@").arg(n_vesper + 1);

	if(!work)
		bCoolerState[N + "Ready"] = ELEM_NOT;
	else if(state.State_8300.RegState.Bits.Ready)
		bCoolerState[N + "Ready"] = ELEM_NORMA;
	else
		bCoolerState[N + "Ready"] = ELEM_AVAR;

	if(!work)
		bCoolerState[N + "Fail"] = ELEM_NOT;
	else if(state.State_8300.RegState.Bits.Fail)
		bCoolerState[N + "Fail"] = ELEM_AVAR;
	else
		bCoolerState[N + "Fail"] = ELEM_NORMA;

	if(!work)
		bCoolerState[N + "Rotation"] = ELEM_NOT;
	else if(state.State_8300.RegState.Bits.Rotation)
		bCoolerState[N + "Rotation"] = ELEM_NORMA;
	else
		bCoolerState[N + "Rotation"] = ELEM_AVAR;

	if(!work)
		bCoolerState[N + "Reverse"] = ELEM_NOT;
	else if(state.State_8300.RegState.Bits.Reverse)
		bCoolerState[N + "Reverse"] = ELEM_AVAR;
	else
		bCoolerState[N + "Reverse"] = ELEM_NORMA;

	if(!work)
		bCoolerState[N + "InputErr"] = ELEM_NOT;
	else if(state.State_8300.RegState.Bits.InputErr)
		bCoolerState[N + "InputErr"] = ELEM_AVAR;
	else
		bCoolerState[N + "InputErr"] = ELEM_NORMA;

	if(!work)
		bCoolerState[N + "ErrorCode"] = ELEM_NOT;
	else if(state.State_8300.RegErrorCode.errorCode() == 0)
		bCoolerState[N + "ErrorCode"] = ELEM_NORMA;
	else
		bCoolerState[N + "ErrorCode"] = ELEM_AVAR;

	if(!work)
		bCoolerState[N + "ErrorCodeValue"] = 0;
	else
		bCoolerState[N + "ErrorCodeValue"] = state.State_8300.RegErrorCode.errorCode();

//Vesper
	if(bCoolerState["portsFail"] == ELEM_AVAR)
		bCoolerState[N + "ObSost"] = ELEM_NOT;
	else if(!work || bCoolerState[N + "Fail"] == ELEM_AVAR)
		bCoolerState[N + "ObSost"] = ELEM_AVAR;
	else if(bCoolerState[N + "Ready"] != ELEM_NORMA)
		bCoolerState[N + "ObSost"] = ELEM_AVAR;
	else if(bCoolerState[N + "InputErr"] == ELEM_AVAR || bCoolerState[N + "ErrorCode"] == ELEM_AVAR)
		bCoolerState[N + "ObSost"] = ELEM_ERROR;
	else
		bCoolerState[N + "ObSost"] = ELEM_NORMA;

//Ventilator
	if(bCoolerState[N + "ObSost"] == ELEM_NORMA && bCoolerState[N + "Rotation"] == ELEM_NORMA)
		bCoolerState[N + "Ventilator"] = ELEM_NORMA;
	else
		bCoolerState[N + "Ventilator"] = ELEM_NOT;
}

//-----------------------------------------------------------------------------
