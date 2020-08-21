#ifndef DASD_THREAD_H_INCLUDED
#define DASD_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>
#include "../common/stateset.h"
#include "../common/sectortable.h"
#include "dasd_registers.h"

class DASD_SERVICE;

class DASD_THREAD : public QThread
{
	Q_OBJECT

protected:
	DASD_SERVICE *service;

public:
	DASD_THREAD(QObject * parent = 0);
	~DASD_THREAD();

	void start();
	void run();
	void quit();
	void csleep(unsigned long msec);

	quint8 state();
	quint8 stateAzSensor1();
	quint8 stateAzSensor2();
	quint8 stateSensorSerial();

signals:
//signals to service
	void sigConnectedGpr();
	void sigDisconnectedGpr();

	void sigStartMonitor();
	void sigStopMonitor();

	void sigResetTables();

	void sigSetMain(bool on);
	void sigSetRipch(bool on);
	void sigSetAzimuthSource(quint32 source);
	void sigSetOverview(quint32 number);

	void sigToggleMain();
	void sigToggleRipch();
	void sigToggleImitator();
	void sigToggleImitatorPeriod();
	void sigToggleAzimuthSource();
	void sigToggleAzimuthMode();
	void sigToggleAzimuthPeriod();
	void sigToggleAzimuthLir1Load();
	void sigToggleAzimuthLir2Load();
	void sigToggleAzimuthSerialLoad();
	void sigToggleBlockZu();
	void sigToggleBlockSwitch();
	void sigToggleBlockYY();
	void sigToggleVaruBan();
	void sigToggleTestSin();
	void sigToggleStrobeEnable();
	void sigToggleBlockAvto();
	void sigToggleImpulsePrd();
	void sigToggleTimerSource();
	void sigToggleSharuSource();
	void sigToggleErrorZu1();
	void sigToggleErrorZu2();
	void sigToggleSkrOn();
	void sigToggleSkrAlwaysOn();
	void sigTogglePilotOn();
	void sigTogglePilotAlwaysOn();
	void sigToggleGshOn();
	void sigToggleGshAlwaysOn();
	void sigToggleZuOn();
	void sigToggleZuAlwaysOn();
	void sigToggleTimerLoad();

	void sigSetLir1Offset(quint32 offset);
	void sigSetLir2Offset(quint32 offset);
	void sigSetLirOffsets(quint32 offset1, quint32 offset2);
	void sigSetSharu1Code(quint32 code);
	void sigSetSharu2Code(quint32 code);
	void sigSetSharuCodes(quint32 code1, quint32 code2);
	void sigSetSyncrOutput(quint32 offset);
	void sigSetImpulsePrd(quint32 offset);
	void sigSetAmpDelayPilotParam(quint32 parameter, quint32 value);
	void sigSetStepDopler(quint32 value);
	void sigSetFreqDeviation(quint32 value);
	void sigSetDump(quint32 info);

	void sigSetMonitorRate(quint32 rate);
	void sigSetDisableTotal(bool on);
	void sigSetDisableDynamic(AskuSektorTable data);
	void sigSetTemperature(double value);

	void sigRefreshTables(quint32 what, bool files);
	void sigSaveTableRipch(QVariantMap mapdata, bool save);
	void sigSaveTableMode(QVariantMap mapdata, bool save);
	void sigSaveTableSwitch(QVariantMap mapdata, bool save);
	void sigSaveTableDisable(QVariantMap mapdata, bool save);

	void sigUpdateSkrPilot();
	void sigUpdateOffsets();

	void sigRefreshSetPrm();
	void sigSetPrmOn(bool on);
	void sigSetPrmGsh(bool on);
	void sigSetPrmZu(bool on);
	void sigSetPrmPilot(bool on);
	void sigSetPrmSkr(bool on);
	void sigSetPrmSharu1Code(quint32 code);
	void sigSetPrmSharu2Code(quint32 code);
};

#endif //DASD_THREAD_H_INCLUDED
