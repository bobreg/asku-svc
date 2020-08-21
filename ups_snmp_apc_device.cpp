#include "../common/logger.h"
#include "globalvar.h"
#include "ups.h"
#include "ups_struct.h"
#include "ups_snmp_service.h"
#include "ups_snmp_apc_device.h"

//------------------------------------------------------------------------------
APC_SNMP_DEVICE::APC_SNMP_DEVICE(UPS_SNMP_SERVICE * p, const QHostAddress & address, const QString & community, quint32 version) : SNMP_DEVICE(p, address, community, version)
{
	m_parent = p;

	setTimeout(10);

// --- OIDs ---
	SnmpOidList parameterList;

/* CONTROL
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.7.2.2.0, upsAdvTestDiagnostics, INTEGER, /1, 1");	(1 - noTestDiagnostics, 2 - testDiagnostics)
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.7.2.5.0, upsAdvTestRuntimeCalibration, INTEGER, /1, 1");	(1 - noPerformCalibration, 2 - performCalibration, 3 - cancelCurrentCalibration)
*/

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.1.1.1.0, upsBasicIdentModel, STRING, MGE Galaxy 3500 15 kVA");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.1.2.1.0, upsAdvIdentFirmwareRevision, STRING, 953.0718.I");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.1.2.2.0, upsAdvIdentDateOfManufacture, STRING, 06/20/15");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.1.2.3.0, upsAdvIdentSerialNumber, STRING, PS1526330002");

//	QMap<int, QString> upsBasicBatteryStatusValues;
	upsBasicBatteryStatusValues[1] = "unknown";
	upsBasicBatteryStatusValues[2] = "batteryNormal";
	upsBasicBatteryStatusValues[3] = "batteryLow";
	upsBasicBatteryStatusValues[4] = "batteryInFaultCondition";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.1.1.0, upsBasicBatteryStatus, INTEGER, /1, 2");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.1.2.0, upsBasicBatteryTimeOnBattery, Timeticks, (0) 0:00:00.00");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.1.3.0, upsBasicBatteryLastReplaceDate, STRING, 04/01/01");

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.2.1.0, upsAdvBatteryCapacity, Gauge32, /1, 100");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.2.2.0, upsAdvBatteryTemperature, Gauge32, /1. 22");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.2.3.0, upsAdvBatteryRunTimeRemaining, Timeticks, (372000) 1:02:00.00");

//	QMap<int, QString> upsAdvBatteryReplaceIndicatorValues;
	upsAdvBatteryReplaceIndicatorValues[1] = "noBatteryNeedsReplacing";
	upsAdvBatteryReplaceIndicatorValues[2] = "batteryNeedsReplacing";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.2.4.0, upsAdvBatteryReplaceIndicator, INTEGER, /1, 1");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.2.5.0, upsAdvBatteryNumOfBattPacks, INTEGER, /1, 8");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.2.6.0, upsAdvBatteryNumOfBadBattPacks, INTEGER, /1, 0");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.2.7.0, upsAdvBatteryNominalVoltage, INTEGER, /1, 192");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.2.8.0, upsAdvBatteryActualVoltage, INTEGER, /1, 218");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.2.9.0, upsAdvBatteryCurrent, INTEGER, /10, 0");

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.3.1.0, upsHighPrecBatteryCapacity, Gauge32, /10, 1000");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.3.2.0, upsHighPrecBatteryTemperature, Gauge32, /10, 226");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.3.3.0, upsHighPrecBatteryNominalVoltage, INTEGER, 10, 1920");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.2.3.4.0, upsHighPrecBatteryActualVoltage, INTEGER, /10, 2187");

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.3.1.1.0, upsBasicInputPhase, INTEGER, /1, 3");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.3.2.1.0, upsAdvInputLineVoltage, Gauge32, /1, 222");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.3.2.2.0, upsAdvInputMaxLineVoltage, Gauge32, /1, 230");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.3.2.3.0, upsAdvInputMinLineVoltage, Gauge32, /1, 216");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.3.2.4.0, upsAdvInputFrequency, Gauge32, /1, 49");

//	QMap<int, QString> upsAdvInputLineFailCauseValues;
	upsAdvInputLineFailCauseValues[ 1] = "noTransfer";
	upsAdvInputLineFailCauseValues[ 2] = "highLineVoltage";
	upsAdvInputLineFailCauseValues[ 3] = "brownout";
	upsAdvInputLineFailCauseValues[ 4] = "blackout";
	upsAdvInputLineFailCauseValues[ 5] = "smallMomentarySag";
	upsAdvInputLineFailCauseValues[ 6] = "deepMomentarySag";
	upsAdvInputLineFailCauseValues[ 7] = "smallMomentarySpike";
	upsAdvInputLineFailCauseValues[ 8] = "largeMomentarySpike";
	upsAdvInputLineFailCauseValues[ 9] = "selfTest";
	upsAdvInputLineFailCauseValues[10] = "rateOfVoltageChange";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.3.2.5.0, upsAdvInputLineFailCause, INTEGER, /1, 10");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.3.3.1.0, upsHighPrecInputLineVoltage, Gauge32, /10, 2221");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.3.3.2.0, upsHighPrecInputMaxLineVoltage, Gauge32, /10, 2308");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.3.3.3.0, upsHighPrecInputMinLineVoltate, Gauge32, /10, 2168");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.3.3.4.0, upsHighPrecInputFrequency, Gauge32, /10, 499");

//	QMap<int, QString> upsBasicOutputStatusValues;
	upsBasicOutputStatusValues[ 1] = "unknown";
	upsBasicOutputStatusValues[ 2] = "onLine";
	upsBasicOutputStatusValues[ 3] = "onBattery";
	upsBasicOutputStatusValues[ 4] = "onSmartBoost";
	upsBasicOutputStatusValues[ 5] = "timedSleeping";
	upsBasicOutputStatusValues[ 6] = "softwareBypass";
	upsBasicOutputStatusValues[ 7] = "off";
	upsBasicOutputStatusValues[ 8] = "rebooting";
	upsBasicOutputStatusValues[ 9] = "switchedBypass";
	upsBasicOutputStatusValues[10] = "hardwareFailureBypass";
	upsBasicOutputStatusValues[11] = "sleepingUntilPowerReturn";
	upsBasicOutputStatusValues[12] = "onSmartTrim";
	upsBasicOutputStatusValues[13] = "ecoMode";
	upsBasicOutputStatusValues[14] = "hotStandby";
	upsBasicOutputStatusValues[15] = "onBatteryTest";
	upsBasicOutputStatusValues[16] = "emergencyStaticBypass";
	upsBasicOutputStatusValues[17] = "staticBypassStandby";
	upsBasicOutputStatusValues[18] = "powerSavingMode";
	upsBasicOutputStatusValues[19] = "spotMode";
	upsBasicOutputStatusValues[20] = "eConversion";
	upsBasicOutputStatusValues[21] = "chargerSpotmode";
	upsBasicOutputStatusValues[22] = "inverterSpotmode";
	upsBasicOutputStatusValues[23] = "activeLoad";
	upsBasicOutputStatusValues[24] = "batteryDischargeSpotmode";
	upsBasicOutputStatusValues[25] = "inverterStandby";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.1.1.0, upsBasicOutputStatus, INTEGER, /1, 2");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.1.2.0, upsBasicOutputPhase, INTEGER, /1, 3");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.2.1.0, upsAdvOutputVoltage, Gauge32, /1, 219");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.2.2.0, upsAdvOutputFrequency, Gauge32, /1, 49");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.2.3.0, upsAdvOutputLoad, Gauge32, /1, 27");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.2.6.0, upsAdvOutputKVACapacity, INTEGER, /1, 0");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.2.8.0, upsAdvOutputActivePower, INTEGER, /1, 0");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.2.9.0, upsAdvOutputApparentPower, INTEGER, /1, 0");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.3.1.0, upsHighPrecOutputVoltage, Gauge32, /10, 2193");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.3.2.0, upsHighPrecOutputFrequency, Gauge32, /10, 499");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.4.3.3.0, upsHighPrecOutputLoad, Gauge32, /10, 279");


//	QMap<int, QString> upsAdvTestDiagnosticSheduleValues;
	upsAdvTestDiagnosticSheduleValues[ 1] = "unknown";
	upsAdvTestDiagnosticSheduleValues[ 2] = "biweekly";
	upsAdvTestDiagnosticSheduleValues[ 3] = "weekly";
	upsAdvTestDiagnosticSheduleValues[ 4] = "atTurnOn";
	upsAdvTestDiagnosticSheduleValues[ 5] = "never";
	upsAdvTestDiagnosticSheduleValues[ 6] = "fourWeeks";
	upsAdvTestDiagnosticSheduleValues[ 7] = "twelveWeeks";
	upsAdvTestDiagnosticSheduleValues[ 8] = "biweeklySinceLastTest";
	upsAdvTestDiagnosticSheduleValues[ 9] = "weeklySinceLastTest";
	upsAdvTestDiagnosticSheduleValues[10] = "eightWeeks";
	upsAdvTestDiagnosticSheduleValues[11] = "twentyWeeks";
	upsAdvTestDiagnosticSheduleValues[12] = "fiftyWeeks";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.7.2.1.0, upsAdvTestDiagnosticShedule, INTEGER, /1, 5");

//	QMap<int, QString> upsAdvTestDiagnosticsResultsValues;
	upsAdvTestDiagnosticsResultsValues[1] = "ok";
	upsAdvTestDiagnosticsResultsValues[2] = "failed";
	upsAdvTestDiagnosticsResultsValues[3] = "invalidTest";
	upsAdvTestDiagnosticsResultsValues[4] = "testInProgress";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.7.2.3.0, upsAdvTestDiagnosticsResults, INTEGER, /1, 3");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.7.2.4.0, upsAdvTestDiagnosticsDate, STRING, Unknown");

//	QMap<int, QString> upsAdvTestCalibrationResultsValues;
	upsAdvTestCalibrationResultsValues[1] = "ok";
	upsAdvTestCalibrationResultsValues[2] = "invalidCalibration";
	upsAdvTestCalibrationResultsValues[3] = "calibrationInProgress";
	upsAdvTestCalibrationResultsValues[4] = "refused";
	upsAdvTestCalibrationResultsValues[5] = "aborted";
	upsAdvTestCalibrationResultsValues[6] = "pending";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.7.2.6.0, upsAdvTestCalibrationResults, INTEGER, /1, 2");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.7.2.7.0, upsAdvTestCalibrationDate, STRING, Unknown");

//	QMap<int, QString> upsCommStatusValues;
	upsCommStatusValues[1] = "ok";
	upsCommStatusValues[1] = "noComm";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.8.1.0, upsCommStatus, INTEGER, /1, 1");

//	QMap<int, QString> upsBasicStateOutputStateValues;
	upsBasicStateOutputStateValues[ 1] = "Abnormal Condition Present";
	upsBasicStateOutputStateValues[ 2] = "On Battery";
	upsBasicStateOutputStateValues[ 3] = "Low Battery";
	upsBasicStateOutputStateValues[ 4] = "On Line";
	upsBasicStateOutputStateValues[ 5] = "Replace Battery";
	upsBasicStateOutputStateValues[ 6] = "Serial Communication Established";
	upsBasicStateOutputStateValues[ 7] = "AVR Boost Active";
	upsBasicStateOutputStateValues[ 8] = "AVR Trim Active";
	upsBasicStateOutputStateValues[ 9] = "Overload";
	upsBasicStateOutputStateValues[10] = "Runtime Calibration";
	upsBasicStateOutputStateValues[11] = "Batteries Discharged";
	upsBasicStateOutputStateValues[12] = "Manual Bypass";
	upsBasicStateOutputStateValues[13] = "Software Bypass";
	upsBasicStateOutputStateValues[14] = "In Bypass due to Internal Fault";
	upsBasicStateOutputStateValues[15] = "In Bypass due to Supply Failure";
	upsBasicStateOutputStateValues[16] = "In Bypass due to Fan Failure";
	upsBasicStateOutputStateValues[17] = "Sleeping on a Timer";
	upsBasicStateOutputStateValues[18] = "Sleeping until Utility Power Returns";
	upsBasicStateOutputStateValues[19] = "On";
	upsBasicStateOutputStateValues[20] = "Rebooting";
	upsBasicStateOutputStateValues[21] = "Battery Communication Lost";
	upsBasicStateOutputStateValues[22] = "Graceful Shutdown Initiated";
	upsBasicStateOutputStateValues[23] = "Smart Boost or Smart Trim Fault";
	upsBasicStateOutputStateValues[24] = "Bad Output Voltage";
	upsBasicStateOutputStateValues[25] = "Battery Charger Failure";
	upsBasicStateOutputStateValues[26] = "High Battery Temperature";
	upsBasicStateOutputStateValues[27] = "Warning Battery Temperature";
	upsBasicStateOutputStateValues[28] = "Critical Battery Temperature";
	upsBasicStateOutputStateValues[29] = "Self Test In Progress";
	upsBasicStateOutputStateValues[30] = "Low Battery / On Battery";
	upsBasicStateOutputStateValues[31] = "Graceful Shutdown Issued by Upstream Device";
	upsBasicStateOutputStateValues[32] = "Graceful Shutdown Issued by Downstream Device";
	upsBasicStateOutputStateValues[33] = "No Batteries Attached";
	upsBasicStateOutputStateValues[34] = "Synchronized Command is in Progress";
	upsBasicStateOutputStateValues[35] = "Synchronized Sleeping Command is in Progress";
	upsBasicStateOutputStateValues[36] = "Synchronized Rebooting Command is in Progress";
	upsBasicStateOutputStateValues[37] = "Inverter DC Imbalance";
	upsBasicStateOutputStateValues[38] = "Transfer Relay Failure";
	upsBasicStateOutputStateValues[39] = "Shutdown or Unable to Transfer";
	upsBasicStateOutputStateValues[40] = "Low Battery Shutdown";
	upsBasicStateOutputStateValues[41] = "Electronic Unit Fan Failure";
	upsBasicStateOutputStateValues[42] = "Main Relay Failure";
	upsBasicStateOutputStateValues[43] = "Bypass Relay Failure";
	upsBasicStateOutputStateValues[44] = "Temporary Bypass";
	upsBasicStateOutputStateValues[45] = "High Internal Temperature";
	upsBasicStateOutputStateValues[46] = "Battery Temperature Sensor Fault";
	upsBasicStateOutputStateValues[47] = "Input Out of Range for Bypass";
	upsBasicStateOutputStateValues[48] = "DC Bus Overvoltage";
	upsBasicStateOutputStateValues[49] = "PFC Failure";
	upsBasicStateOutputStateValues[50] = "Critical Hardware Fault";
	upsBasicStateOutputStateValues[51] = "Green Mode/ECO Mode";
	upsBasicStateOutputStateValues[52] = "Hot Standby";
	upsBasicStateOutputStateValues[53] = "Emergency Power Off (EPO) Activated";
	upsBasicStateOutputStateValues[54] = "Load Alarm Violation";
	upsBasicStateOutputStateValues[55] = "Bypass Phase Fault";
	upsBasicStateOutputStateValues[56] = "UPS Internal Communication Failure";
	upsBasicStateOutputStateValues[57] = "Efficiency Booster Mode";
	upsBasicStateOutputStateValues[58] = "Off";
	upsBasicStateOutputStateValues[59] = "Standby";
	upsBasicStateOutputStateValues[60] = "Minor or Environment Alarm";
	upsBasicStateOutputStateValues[61] = "<Not Used>";
	upsBasicStateOutputStateValues[62] = "<Not Used>";
	upsBasicStateOutputStateValues[63] = "<Not Used>";
	upsBasicStateOutputStateValues[64] = "<Not Used>";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.11.1.1.0, upsBasicStateOutputState, STRING, 0001010000000000001000000000000000000000000000000000000000000000");

//	QMap<int, QString> upsAdvStateAbnormalConditionsValues;
	upsAdvStateAbnormalConditionsValues[ 1] = "Power Module Failure";
	upsAdvStateAbnormalConditionsValues[ 2] = "Main Intelligence Module Failure";
	upsAdvStateAbnormalConditionsValues[ 3] = "Redundant Intelligence Module Failure";
	upsAdvStateAbnormalConditionsValues[ 4] = "Battery Failure";
	upsAdvStateAbnormalConditionsValues[ 5] = "Load(kVA) Alarm Threshold Violation";
	upsAdvStateAbnormalConditionsValues[ 6] = "Redundancy Lost";
	upsAdvStateAbnormalConditionsValues[ 7] = "Redundancy Below Alarm Threshold";
	upsAdvStateAbnormalConditionsValues[ 8] = "Bypass not in Range; Either Frequency or Voltage";
	upsAdvStateAbnormalConditionsValues[ 9] = "Bypass Contactor Stuck in Bypass Condition";
	upsAdvStateAbnormalConditionsValues[10] = "Bypass Contactor Stuck in On-Line Condition";
	upsAdvStateAbnormalConditionsValues[11] = "In Bypass due to an Internal Fault";
	upsAdvStateAbnormalConditionsValues[12] = "In Bypass due to an Overload";
	upsAdvStateAbnormalConditionsValues[13] = "In Maintenance Bypass";
	upsAdvStateAbnormalConditionsValues[14] = "Input Circuit Braker Tripped Open";
	upsAdvStateAbnormalConditionsValues[15] = "System Level Fan Failure";
	upsAdvStateAbnormalConditionsValues[16] = "Redundant Intelligent Module in Control";
	upsAdvStateAbnormalConditionsValues[17] = "IIC Inter-Module Communication Failure";
	upsAdvStateAbnormalConditionsValues[18] = "No Working Power Modules";
	upsAdvStateAbnormalConditionsValues[19] = "Load Shutdown From Bypass; Input Frequency";
	upsAdvStateAbnormalConditionsValues[20] = "Runtime Below Alarm Threshold";
	upsAdvStateAbnormalConditionsValues[21] = "Extended Run Frame Fault";
	upsAdvStateAbnormalConditionsValues[22] = "Output Voltage out of Range";
	upsAdvStateAbnormalConditionsValues[23] = "UPS Not Synchronized";
	upsAdvStateAbnormalConditionsValues[24] = "No Batteries Installed";
	upsAdvStateAbnormalConditionsValues[25] = "Battery Voltage High";
	upsAdvStateAbnormalConditionsValues[26] = "UPS Specific Fault Detected";
	upsAdvStateAbnormalConditionsValues[27] = "Site Wiring Fault";
	upsAdvStateAbnormalConditionsValues[28] = "Backfeed Protection Relay Opened";
	upsAdvStateAbnormalConditionsValues[29] = "<Not Used>";
	upsAdvStateAbnormalConditionsValues[30] = "<Not Used>";
	upsAdvStateAbnormalConditionsValues[31] = "<Not Used>";
	upsAdvStateAbnormalConditionsValues[32] = "<Not Used>";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.11.2.1.0, upsAdvStateAbnormalConditions, STRING, 00000000000000000000000000000000");

//	QMap<int, QString> upsAdvStateSmartUPSSpecificFaultsValues;
	upsAdvStateSmartUPSSpecificFaultsValues[ 1] = "EPO Switch Activated";
	upsAdvStateSmartUPSSpecificFaultsValues[ 2] = "Static Bypass Switch Fault";
	upsAdvStateSmartUPSSpecificFaultsValues[ 3] = "System Configuration Fault";
	upsAdvStateSmartUPSSpecificFaultsValues[ 4] = "Power Supply Unit Fault";
	upsAdvStateSmartUPSSpecificFaultsValues[ 5] = "Weak Battery";
	upsAdvStateSmartUPSSpecificFaultsValues[ 6] = "High Battery Temperature";
	upsAdvStateSmartUPSSpecificFaultsValues[ 7] = "Internal Mechanical Bypass";
	upsAdvStateSmartUPSSpecificFaultsValues[ 8] = "Loss Of Parallel Redundancy";
	upsAdvStateSmartUPSSpecificFaultsValues[ 9] = "Parallel Bus Communication Fault on Cable 1";
	upsAdvStateSmartUPSSpecificFaultsValues[10] = "Parallel Bus Communication Fault on Cable 2";
	upsAdvStateSmartUPSSpecificFaultsValues[11] = "Auxiliary Bus Communication Fault";
	upsAdvStateSmartUPSSpecificFaultsValues[12] = "Parallel Bus Termination Fault on Cable 1";
	upsAdvStateSmartUPSSpecificFaultsValues[13] = "Parallel Bus Termination Fault on Cable 2";
	upsAdvStateSmartUPSSpecificFaultsValues[14] = "Auxiliary Bus Termination Fault";
	upsAdvStateSmartUPSSpecificFaultsValues[15] = "No Master Present In The Parallel System";
	upsAdvStateSmartUPSSpecificFaultsValues[16] = "Overload on a Parallel Unit";
	upsAdvStateSmartUPSSpecificFaultsValues[17] = "Parallel Configuration Fault";
	upsAdvStateSmartUPSSpecificFaultsValues[18] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[19] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[20] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[21] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[22] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[23] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[24] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[25] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[26] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[27] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[28] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[29] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[30] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[31] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[32] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[33] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[34] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[35] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[36] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[37] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[38] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[39] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[40] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[41] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[42] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[43] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[44] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[45] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[46] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[47] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[48] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[49] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[50] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[51] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[52] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[53] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[54] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[55] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[56] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[57] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[58] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[59] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[60] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[61] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[62] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[63] = "<Not Used>";
	upsAdvStateSmartUPSSpecificFaultsValues[64] = "<Not Used>";

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.11.2.5.0, upsAdvStateSmartUPSSpecificFaults, STRING, 0000000000000000000000000000000000000000000000000000000000000000");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.11.2.6.0, upsAdvStateSystemMessages, STRING, 000");

	parameterList.append(".1.3.6.1.4.1.318.1.1.1.9.3.2.1.4, upsPhaseOutputFrequency, INTEGER, /10, 499");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.9.2.3.1.3.1.1, upsPhaseInputVoltage1, INTEGER, /1, 218");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.9.2.3.1.3.2.1, upsPhaseInputVoltage2, INTEGER, /1, 218");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.9.2.3.1.6.1.1, upsPhaseInputCurrent1, INTEGER, /10, 44");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.9.2.3.1.6.2.1, upsPhaseInputCurrent2, INTEGER, /10, -1");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.9.3.3.1.3.1.1, upsPhaseOutputVoltage, INTEGER, /1, 219");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.9.3.3.1.4.1.1, upsPhaseOutputCurrent, INTEGER, /10, 50");
	parameterList.append(".1.3.6.1.4.1.318.1.1.1.9.3.3.1.10.1.1, upsPhaseOutputPercentLoad, INTEGER, /1, 25");

// --- OIDs ---

	setOidList(parameterList);
}

//------------------------------------------------------------------------------
APC_SNMP_DEVICE::~APC_SNMP_DEVICE()
{
	
}

// ------------------------------------------------------------------
void APC_SNMP_DEVICE::onConnected()
{
	LogUpsInfo("UpsDevice: connected");
	m_parent->onChangedPortState();
}

// ------------------------------------------------------------------
void APC_SNMP_DEVICE::onDisconnected()
{
	LogUpsInfo("UpsDevice: disconnected");
	m_parent->onChangedPortState();
}

//------------------------------------------------------------------------------
void APC_SNMP_DEVICE::processResults()
{
//	LogUpsInfo(QString("processResults (%1)\n%2").arg(m_results.size()).arg(m_results.dump()));
	LogUpsInfo(QString("processResults (%1)(%2)").arg(m_results.size()).arg(m_results.isChanged()));

//	bool changed = m_results.isChanged();

	if(/*changed &&*/ m_parent)
		m_parent->onProcessSnmpResults(this, m_results.toNamedMap());

	m_results.resetChanged();
}

//------------------------------------------------------------------------------
bool APC_SNMP_DEVICE::isActualState()
{
	return false;
}

//------------------------------------------------------------------------------
bool APC_SNMP_DEVICE::isInfoCollected()
{
	return false;
}

//------------------------------------------------------------------------------
QVariant APC_SNMP_DEVICE::translateValue(const QString & key, const QVariant & value)
{
	if(key == QString("upsBasicBatteryStatus"))
		return upsBasicBatteryStatusValues[value.toInt()];
	else if(key == QString("upsAdvBatteryReplaceIndicator"))
		return upsAdvBatteryReplaceIndicatorValues[value.toInt()];
	else if(key == QString("upsAdvInputLineFailCause"))
		return upsAdvInputLineFailCauseValues[value.toInt()];
	else if(key == QString("upsBasicOutputStatus"))
		return upsBasicOutputStatusValues[value.toInt()];
	else if(key == QString("upsAdvTestDiagnosticShedule"))
		return upsAdvTestDiagnosticSheduleValues[value.toInt()];
	else if(key == QString("upsAdvTestDiagnosticsResults"))
		return upsAdvTestDiagnosticsResultsValues[value.toInt()];
	else if(key == QString("upsAdvTestCalibrationResults"))
		return upsAdvTestCalibrationResultsValues[value.toInt()];
	else if(key == QString("upsCommStatus"))
		return upsCommStatusValues[value.toInt()];

//	else if(key == QString("upsBasicStateOutputState"))
//		return upsBasicStateOutputStateValues[value.toInt()];
//	else if(key == QString("upsAdvStateAbnormalConditions"))
//		return upsAdvStateAbnormalConditionsValues[value.toInt()];
//	else if(key == QString("upsAdvStateSmartUPSSpecificFaults"))
//		return upsAdvStateSmartUPSSpecificFaultsValues[value.toInt()];

	else if(key == QString("upsAdvBatteryCurrent"))
		return QVariant(value.toDouble() / 10.0);
	else if(key.startsWith(QString("upsPhaseInputCurrent")))
		return QVariant(value.toDouble() / 10.0);
	else if(key.startsWith(QString("upsPhaseOutputCurrent")))
		return QVariant(value.toDouble() / 10.0);
	else if(key.startsWith(QString("upsHighPrec")))
		return QVariant(value.toDouble() / 10.0);
	else
		return value;
}

//------------------------------------------------------------------------------
