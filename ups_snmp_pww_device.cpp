#include "../common/logger.h"
#include "globalvar.h"
#include "ups.h"
#include "ups_struct.h"
#include "ups_snmp_service.h"
#include "ups_snmp_pww_device.h"

//------------------------------------------------------------------------------
// PWW Oids list

const char* PW_SNMP_xupsOutputSource		= ".1.3.6.1.4.1.534.1.4.5.0";
const char* PW_SNMP_xupsBatTimeRemaining	= ".1.3.6.1.4.1.534.1.2.1.0";
const char* PW_SNMP_xupsBatVoltage		= ".1.3.6.1.4.1.534.1.2.2.0";
const char* PW_SNMP_xupsBatCurrent		= ".1.3.6.1.4.1.534.1.2.3.0";
const char* PW_SNMP_xupsBatCapacity		= ".1.3.6.1.4.1.534.1.2.4.0";
const char* PW_SNMP_xupsOutputLoad		= ".1.3.6.1.4.1.534.1.4.1.0";
const char* PW_SNMP_xupsOutputFrequency		= ".1.3.6.1.4.1.534.1.4.2.0";
const char* PW_SNMP_xupsOutputVoltage1		= ".1.3.6.1.4.1.534.1.4.4.1.2.1";
const char* PW_SNMP_xupsOutputVoltage2		= ".1.3.6.1.4.1.534.1.4.4.1.2.2";
const char* PW_SNMP_xupsOutputVoltage3		= ".1.3.6.1.4.1.534.1.4.4.1.2.3";
const char* PW_SNMP_xupsOutputCurrent1		= ".1.3.6.1.4.1.534.1.4.4.1.3.1";
const char* PW_SNMP_xupsOutputCurrent2		= ".1.3.6.1.4.1.534.1.4.4.1.3.2";
const char* PW_SNMP_xupsOutputCurrent3		= ".1.3.6.1.4.1.534.1.4.4.1.3.3";
const char* PW_SNMP_xupsInputVoltage1		= ".1.3.6.1.4.1.534.1.3.4.1.2.1";
const char* PW_SNMP_xupsInputVoltage2		= ".1.3.6.1.4.1.534.1.3.4.1.2.2";
const char* PW_SNMP_xupsInputVoltage3		= ".1.3.6.1.4.1.534.1.3.4.1.2.3";
const char* PW_SNMP_xupsInputCurrent1		= ".1.3.6.1.4.1.534.1.3.4.1.3.1";
const char* PW_SNMP_xupsInputCurrent2		= ".1.3.6.1.4.1.534.1.3.4.1.3.2";
const char* PW_SNMP_xupsInputCurrent3		= ".1.3.6.1.4.1.534.1.3.4.1.3.3";

const char* PW_SNMP_xupsIdentManufacturer	= ".1.3.6.1.4.1.534.1.1.1.0";
const char* PW_SNMP_xupsIdentModel		= ".1.3.6.1.4.1.534.1.1.2.0";
const char* PW_SNMP_xupsIdentSoftwareVersion	= ".1.3.6.1.4.1.534.1.1.3.0";

const char* PW_SNMP_xupsInputFrequency		= ".1.3.6.1.4.1.534.1.3.1.0";
const char* PW_SNMP_xupsInputWatts1		= ".1.3.6.1.4.1.534.1.3.4.1.4.1";
const char* PW_SNMP_xupsInputWatts2		= ".1.3.6.1.4.1.534.1.3.4.1.4.2";
const char* PW_SNMP_xupsInputWatts3		= ".1.3.6.1.4.1.534.1.3.4.1.4.3";
const char* PW_SNMP_xupsOutputWatts1		= ".1.3.6.1.4.1.534.1.4.4.1.4.1";
const char* PW_SNMP_xupsOutputWatts2		= ".1.3.6.1.4.1.534.1.4.4.1.4.2";
const char* PW_SNMP_xupsOutputWatts3		= ".1.3.6.1.4.1.534.1.4.4.1.4.3";
const char* PW_SNMP_xupsBypassVoltage1		= ".1.3.6.1.4.1.534.1.5.3.1.2.1";
const char* PW_SNMP_xupsBypassVoltage2		= ".1.3.6.1.4.1.534.1.5.3.1.2.2";
const char* PW_SNMP_xupsBypassVoltage3		= ".1.3.6.1.4.1.534.1.5.3.1.2.3";
const char* PW_SNMP_xupsEnvAmbientTemp		= ".1.3.6.1.4.1.534.1.6.1.0";
const char* PW_SNMP_xupsTestBatteryStatus	= ".1.3.6.1.4.1.534.1.8.2.0";
const char* PW_SNMP_xupsAlarms			= ".1.3.6.1.4.1.534.1.7.1.0";
const char* PW_SNMP_xupsInputSource		= ".1.3.6.1.4.1.534.1.4.5.0";
const char* PW_SNMP_xupsBypassFrequency		= ".1.3.6.1.4.1.534.1.5.1.0";
const char* PW_SNMP_xupsAlarmTable		= ".1.3.6.1.4.1.534.1.7.2.1";
const char* PW_SNMP_xupsAlarmDescr		= ".1.3.6.1.4.1.534.1.7.2.1.2";

const char* PW_SNMP_xupsLowBattery 		= ".1.3.6.1.4.1.534.1.7.4";
const char* PW_SNMP_xupsInternalFailure 	= ".1.3.6.1.4.1.534.1.7.8";
const char* PW_SNMP_xupsUtilityPowerRestored	= ".1.3.6.1.4.1.534.1.7.5";
const char* PW_SNMP_xupsReturnFromLowBattery	= ".1.3.6.1.4.1.534.1.7.6";
const char* PW_SNMP_xupsOutputOverload		= ".1.3.6.1.4.1.534.1.7.7";
const char* PW_SNMP_xupsBatteryDischarged	= ".1.3.6.1.4.1.534.1.7.9";
const char* PW_SNMP_xupsOnBattery		= ".1.3.6.1.4.1.534.1.7.3";
const char* PW_SNMP_xupsInverterFailure		= ".1.3.6.1.4.1.534.1.7.10";
const char* PW_SNMP_xupsOnBypass		= ".1.3.6.1.4.1.534.1.7.11";
const char* PW_SNMP_xupsBypassNotAvailable	= ".1.3.6.1.4.1.534.1.7.12";
const char* PW_SNMP_xupsOutputOff		= ".1.3.6.1.4.1.534.1.7.13";
const char* PW_SNMP_xupsInputFailure		= ".1.3.6.1.4.1.534.1.7.14";
const char* PW_SNMP_xupsBuildingAlarm		= ".1.3.6.1.4.1.534.1.7.15";
const char* PW_SNMP_xupsShutdownImminent	= ".1.3.6.1.4.1.534.1.7.16";
const char* PW_SNMP_xupsOnInverter		= ".1.3.6.1.4.1.534.1.7.17";

const char* PW_SNMP_xupsBreakerOpen		= ".1.3.6.1.4.1.534.1.7.20";
const char* PW_SNMP_xupsAlarmEntryAdded		= ".1.3.6.1.4.1.534.1.7.21"; // 1+
const char* PW_SNMP_xupsAlarmEntryRemoved	= ".1.3.6.1.4.1.534.1.7.22"; // 1-
const char* PW_SNMP_xupsAlarmBatteryBad		= ".1.3.6.1.4.1.534.1.7.23";
const char* PW_SNMP_xupsOutputOffAsRequested	= ".1.3.6.1.4.1.534.1.7.24";
const char* PW_SNMP_xupsDiagnosticTestFailed	= ".1.3.6.1.4.1.534.1.7.25";
const char* PW_SNMP_xupsCommunicationsLost	= ".1.3.6.1.4.1.534.1.7.26";
const char* PW_SNMP_xupsUpsShutdownPending	= ".1.3.6.1.4.1.534.1.7.27";
const char* PW_SNMP_xupsAlarmTestInProgress	= ".1.3.6.1.4.1.534.1.7.28";
const char* PW_SNMP_xupsAmbientTempBad		= ".1.3.6.1.4.1.534.1.7.29";

const char* PW_SNMP_xupsContactActiveNotice	= ".1.3.6.1.4.1.534.1.7.30"; // 2+
const char* PW_SNMP_xupsContactInactiveNotice	= ".1.3.6.1.4.1.534.1.7.31"; // 2-
const char* PW_SNMP_xupsLossOfRedundancy	= ".1.3.6.1.4.1.534.1.7.32";
const char* PW_SNMP_xupsAlarmTempBad		= ".1.3.6.1.4.1.534.1.7.33";
const char* PW_SNMP_xupsAlarmChargerFailed	= ".1.3.6.1.4.1.534.1.7.34";
const char* PW_SNMP_xupsAlarmFanFailure		= ".1.3.6.1.4.1.534.1.7.35";
const char* PW_SNMP_xupsAlarmFuseFailure	= ".1.3.6.1.4.1.534.1.7.36";
const char* PW_SNMP_xupsPowerSwitchBad		= ".1.3.6.1.4.1.534.1.7.37";
const char* PW_SNMP_xupsModuleFailure		= ".1.3.6.1.4.1.534.1.7.38";
//const char* PW_SNMP_xupsInputSource		= ".1.3.6.1.4.1.534.1.7.39";

const char* PW_SNMP_xupsAltPowerNotAvailable	= ".1.3.6.1.4.1.534.1.7.40";
const char* PW_SNMP_xupsNoticeCondition		= ".1.3.6.1.4.1.534.1.7.41";
const char* PW_SNMP_xupsRemoteTempBad		= ".1.3.6.1.4.1.534.1.7.42";
const char* PW_SNMP_xupsRemoteHumidityBad	= ".1.3.6.1.4.1.534.1.7.43";
const char* PW_SNMP_xupsHeartbeat		= ".1.3.6.1.4.1.534.1.7.44";
const char* PW_SNMP_xupsDiagnosticTestPassed	= ".1.3.6.1.4.1.534.1.7.45";
const char* PW_SNMP_xupsOutputBad		= ".1.3.6.1.4.1.534.1.7.46";
const char* PW_SNMP_xupsAwaitingPower		= ".1.3.6.1.4.1.534.1.7.47";
const char* PW_SNMP_xupsOnMaintenanceBypass	= ".1.3.6.1.4.1.534.1.7.78";
const char* PW_SNMP_xupsCommEstablished		= ".1.3.6.1.4.1.534.1.7.79";

const char* PW_SNMP_xupsAgentDown		= ".1.3.6.1.4.1.534.1.7.50";

//------------------------------------------------------------------------------
PWW_SNMP_DEVICE::PWW_SNMP_DEVICE(UPS_SNMP_SERVICE * p, const QHostAddress & address, const QString & community, quint32 version) : SNMP_DEVICE(p, address, community, version)
{
/*
	parameterList.append(".1.3.6.1.4.1.534.1.1.1.0, xupsIdentManufacturer, STRING, EATON");//
	parameterList.append(".1.3.6.1.4.1.534.1.1.2.0, xupsIdentModel, STRING, 93E HV 40000");//
	parameterList.append(".1.3.6.1.4.1.534.1.1.3.0, xupsIdentSoftwareVersion, STRING, INV: 2.08.0011");//
	parameterList.append(".1.3.6.1.4.1.534.1.1.4.0, xupsIdentOemCode, INTEGER, -, /1, 0");
	appendToOidList(oidsIdentityList, parameterList);
	appendToResults(parameterList);
	parameterList.clear();

	parameterList.append(".1.3.6.1.4.1.534.1.2.6.0, xupsBatteryLastReplacedDate, STRING, ");
	parameterList.append(".1.3.6.1.4.1.534.1.3.3.0, xupsInputNumPhases, INTEGER, , /1, 3");
	parameterList.append(".1.3.6.1.4.1.534.1.4.3.0, xupsOutputNumPhases, INTEGER, , /1, 3");
	parameterList.append(".1.3.6.1.4.1.534.1.5.2.0, xupsBypassNumPhases, INTEGER, , /1, 3");
	parameterList.append(".1.3.6.1.4.1.534.1.6.2.0, xupsEnvAmbientLowerLimit, INTEGER, Degrees Centigrade, /1, 0");
	parameterList.append(".1.3.6.1.4.1.534.1.6.3.0, xupsEnvAmbientUpperLimit, INTEGER, Degrees Centigrade, /1, 40");
	parameterList.append(".1.3.6.1.4.1.534.1.10.1.0, xupsConfigOutputVoltage, INTEGER, RMS Volts, /1, 220");
	parameterList.append(".1.3.6.1.4.1.534.1.10.2.0, xupsConfigInputVoltage, INTEGER, RMS Volts, /1, 220");
	parameterList.append(".1.3.6.1.4.1.534.1.10.3.0, xupsConfigOutputWatts, INTEGER, Watts, /1, 36000");
	parameterList.append(".1.3.6.1.4.1.534.1.10.4.0, xupsConfigOutputFreq, INTEGER, Hertz, /10, 500");
	parameterList.append(".1.3.6.1.4.1.534.1.10.6.0, xupsConfigLowOutputVoltageLimit, INTEGER, RMS Volts, /1, 0");
	parameterList.append(".1.3.6.1.4.1.534.1.10.7.0, xupsConfigHighOutputVoltageLimit, INTEGER, RMS Volts, /1, 0");
	parameterList.append(".1.3.6.1.4.1.534.1.10.8.0, xupsConfigInstallDate, STRING, ");
	appendToOidList(oidsConfigList, parameterList);
	appendToResults(parameterList);
	parameterList.clear();

	parameterList.append(".1.3.6.1.4.1.534.1.2.1.0, xupsBatTimeRemaining, INTEGER, seconds, /1, 23978");//
	parameterList.append(".1.3.6.1.4.1.534.1.2.2.0, xupsBatVoltage, INTEGER, Volts DC, /1, 441");//
	parameterList.append(".1.3.6.1.4.1.534.1.2.3.0, xupsBatCurrent, INTEGER, Amp DC, /1, 3");//
	parameterList.append(".1.3.6.1.4.1.534.1.2.4.0, xupsBatCapacity, INTEGER, percent, /1, 90");//
	parameterList.append(".1.3.6.1.4.1.534.1.2.5.0, xupsBatteryAbmStatus, INTEGER, Status, /1, 0");
	parameterList.append(".1.3.6.1.4.1.534.1.3.1.0, xupsInputFrequency, INTEGER, Hertz, /10, 500");//
	parameterList.append(".1.3.6.1.4.1.534.1.3.2.0, xupsInputLineBads, INTEGER, counter, /1, 0");
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1, xupsInputTable, SEQUENCE");
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.1.1, xupsInputPhase, INTEGER, , /1, 1");
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.2.1, xupsInputVoltage, INTEGER, RMS Volts, /1, 221");//
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.3.1, xupsInputCurrent, INTEGER, RMS Amp, /1, 4");//
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.4.1, xupsInputWatts, INTEGER, Watts, /1, 0");//
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.1.2, xupsInputPhase, INTEGER, , /1, 2");
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.2.2, xupsInputVoltage, INTEGER, RMS Volts, /1, 226");//
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.3.2, xupsInputCurrent, INTEGER, RMS Amp, /1, 4");//
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.4.2, xupsInputWatts, INTEGER, Watts, /1, 0");//
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.1.3, xupsInputPhase, INTEGER, , /1, 3");
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.2.3, xupsInputVoltage, INTEGER, RMS Volts, /1, 227");//
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.3.3, xupsInputCurrent, INTEGER, RMS Amp, /1, 4");//
	parameterList.append(".1.3.6.1.4.1.534.1.3.4.1.4.3, xupsInputWatts, INTEGER, Watts, /1, 0");//
	parameterList.append(".1.3.6.1.4.1.534.1.3.5.0, xupsInputSource, INTEGER, Status, /1, 3");//       		//!!!! switch
	parameterList.append(".1.3.6.1.4.1.534.1.4.1.0, xupsOutputLoad, INTEGER, percent, /1, 5");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.2.0, xupsOutputFrequency, INTEGER, Hertz, /10, 500");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1, xupsOutputTable, SEQUENCE");
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.1.1, xupsOutputPhase, INTEGER, , /1, 1");
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.2.1, xupsOutputVoltage, INTEGER, RMS Volts, /1, 220");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.3.1, xupsOutputCurrent, INTEGER, RMS Amp, /1, 2");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.4.1, xupsOutputWatts, INTEGER, Watts, /1, 600");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.1.2, xupsOutputPhase, INTEGER, , /1, 2");
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.2.2, xupsOutputVoltage, INTEGER, RMS Volts, /1, 220");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.3.2, xupsOutputCurrent, INTEGER, RMS Amp, /1, 0");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.4.2, xupsOutputWatts, INTEGER, Watts, /1, 0");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.1.3, xupsOutputPhase, INTEGER, , /1, 3");
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.2.3, xupsOutputVoltage, INTEGER, RMS Volts, /1, 220");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.3.3, xupsOutputCurrent, INTEGER, RMS Amp, /1, 2");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.4.1.4.3, xupsOutputWatts, INTEGER, Watts, /1, 400");//
	parameterList.append(".1.3.6.1.4.1.534.1.4.5.0, xupsOutputSource, INTEGER, Status, /1, 3"); //      //SWITCH!
	parameterList.append(".1.3.6.1.4.1.534.1.5.1.0, xupsBypassFrequency, INTEGER, Hertz, /10, 0");//
	parameterList.append(".1.3.6.1.4.1.534.1.5.3.1, xupsBypassTable, SEQUENCE");
	parameterList.append(".1.3.6.1.4.1.534.1.5.3.1.1.1, xupsBypassPhase, INTEGER, , /1, 1");
	parameterList.append(".1.3.6.1.4.1.534.1.5.3.1.2.1, xupsBypassVoltage, INTEGER, RMS Volts, /1, 0");//
	parameterList.append(".1.3.6.1.4.1.534.1.5.3.1.1.2, xupsBypassPhase, INTEGER, , /1, 2");
	parameterList.append(".1.3.6.1.4.1.534.1.5.3.1.2.2, xupsBypassVoltage, INTEGER, RMS Volts, /1, 0");//
	parameterList.append(".1.3.6.1.4.1.534.1.5.3.1.1.3, xupsBypassPhase, INTEGER, , /1, 3");
	parameterList.append(".1.3.6.1.4.1.534.1.5.3.1.2.3, xupsBypassVoltage, INTEGER, RMS Volts, /1, 0");//
	parameterList.append(".1.3.6.1.4.1.534.1.6.1.0, xupsEnvAmbientTemp, INTEGER, Degrees Centigrade, /1, 25");//
	parameterList.append(".1.3.6.1.4.1.534.1.8.2.0, xupsTestBatteryStatus, INTEGER, , /1, 1");//
	parameterList.append(".1.3.6.1.4.1.534.1.7.1.0, xupsAlarms, INTEGER, counter, /1, 1");//  //not show
	parameterList.append(".1.3.6.1.4.1.534.1.7.2.1, xupsAlarmTable, SEQUENCE");
	//parameterList.append(".1.3.6.1.4.1.534.1.10.5.0, xupsConfigDateAndTime, STRING, 10/18/2018 15:34:33");
	appendToOidList(oidsWatchList, parameterList);
	appendToResults(parameterList);
	parameterList.clear();
*/
}

//------------------------------------------------------------------------------
PWW_SNMP_DEVICE::~PWW_SNMP_DEVICE()
{
	
}

//------------------------------------------------------------------------------
void PWW_SNMP_DEVICE::onConnected()
{
}

//------------------------------------------------------------------------------
void PWW_SNMP_DEVICE::onDisconnected()
{
}

//------------------------------------------------------------------------------
void PWW_SNMP_DEVICE::processResults()
{
}

//------------------------------------------------------------------------------
bool PWW_SNMP_DEVICE::isActualState()
{
	return false;
}

//------------------------------------------------------------------------------
bool PWW_SNMP_DEVICE::isInfoCollected()
{
	return false;
}

//------------------------------------------------------------------------------
QVariant PWW_SNMP_DEVICE::translateValue(const QString & key, const QVariant & value)
{
	Q_UNUSED(key);
	return value;
}

//------------------------------------------------------------------------------
