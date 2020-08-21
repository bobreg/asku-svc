#ifndef __DASD_SERVICE_H__
#define __DASD_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/logger.h"
#include "../common/stateset.h"
#include "dasd_device.h"
#include "dasd_registers.h"
#include "dasd_tables.h"

//-----------------------------------------------------------------------------

class DASD_THREAD;

//-----------------------------------------------------------------------------

class DASD_SERVICE : public QObject
{
	Q_OBJECT

public:
	enum CommandType {
		CommandOff = 0,
		CommandOn = 1,
		CommandToggle = 2
	};

protected:
	DASD_THREAD *parent;
	DASD_DEVICE *device;

	QTimer *timer;

	bool initialized;
	bool fixedError;
	bool isAvarFref;
	bool isAvarFrefFixed;
	void checkFref();

	QString errorString();

	bool allowPchVoi;
	bool allowPchCtrl;
	bool allowPchMain;

	QDateTime m_timeChangedMain;

//Состояние ячейки
	AskuBinStateSet bDasdLocalState;
	AskuValueSet bDasdLocalMeasure;
	AskuBinStateSet bDasdOtherState;
	AskuValueSet bDasdOtherMeasure;

	void clearLocalState();
	void clearOtherState();

//Режим настройки приёмника
	bool isPrmActive;
	bool isPrmSkr;
	bool isPrmPilot;
	bool isPrmGsh;
	bool isPrmZu;
	quint32 codePrmSharu1;
	quint32 codePrmSharu2;

//Выбранный азимутальный датчик
	quint32 activeSensor;

//Сброс аварии ЗУ по старту
	bool checkedErrorZu;
	void checkErrorZu();

//Установка параметров по старту
	bool startupParameters;
	void checkStartupParameters();

//Команды
	quint32 cmdSetMain;
	quint32 cmdSetRipch;
	quint32 cmdSetStartSkr;
	quint32 cmdSetImitator;
	quint32 cmdSetActiveSensor;

//Обработка команд
	void processCommands();

//Доступ к регистрам
	DEVICE_REGISTERS devRegs;
	REG_AZIMUTH regAzimuthPRL;
	REG_AZIMUTH_CONTROL regAzimuthCtrl;
	void readRegisters();

//Установка отдельных регистров
	void setRegMain(CommandType cmd);
	void setRegRipch(CommandType cmd);
	void setRegSkrAllOn(CommandType cmd);
	void setRegSkrOn(CommandType cmd);
	void setRegSkrAlwaysOn(CommandType cmd);
	void setRegPilotOn(CommandType cmd);
	void setRegPilotAlwaysOn(CommandType cmd);
	void setRegGshOn(CommandType cmd);
	void setRegGshAlwaysOn(CommandType cmd);
	void setRegZuOn(CommandType cmd);
	void setRegZuAlwaysOn(CommandType cmd);

//Таблицы
	bool loadTablesComplete;
	DEVICE_TABLES tables;
	DASD_TABLES devTables;

	QString tableModeName;
	QString tableRipchName;
	QString tableSwitchName;
	QString tableDisableName;
	QString tableNchmName;

//Доступ к таблицам
	bool loadTables();

	bool writeTables();
	bool writeRipchTable();
	bool writeModeTable();
	bool writeSwitchTable();
	bool writeNchmTable();

//Доступ к девайсу
	bool read_device_mem(quint32 adress, void* buffer, quint32 length);
	bool write_device_mem(quint32 adress, void* buffer, quint32 length);
	bool read_device_port(quint32 adress, quint16* value);
	bool write_device_port(quint32 adress, quint16* value);
	bool checkError();

//Доступ к навигатору
	qint32 time1Counter;
	qint32 time2Counter;
	QVector<quint8> tx0buffer;
	QVector<quint8> rx0buffer;
	QVector<quint8> rx1buffer;

	void checkSyncronize();
	void onChangedState();

//Температура платы
	quint32 waitTemperature;
	void checkTemperature();

	void paintDlg();

//СКР и ПС
	quint32 azSKR;
	quint32 strobeSKR;
	quint32 azPS;
	quint32 strobePS;
	quint32 periodSKRPS;
	quint32 countSKRPS;
	bool needNowSKRPS;
	bool wasSetSKR;
	bool wasSetPS;
	bool preLock;
	bool setChangeSKR;
	bool setChangePS;

	void processSkrPs();
	void registerSetSKR(bool on);
	void registerSetPS(bool on);

//Поправки азимута и угла места
	quint16 offsetLir1;
	quint16 offsetLir2;
	void checkOffsets();

//Азимутальные датчики
	void checkSensors();

//Выполнить при выходе
	void setShutdown();

//Вывод на диалог
	bool isMonitoring;
	quint32 monitoringRate;
	quint32 monitoringCounter;

	void monitoring();

	void verifyRipch();

protected slots:
	void timeout();

public slots:
//slots from thread
	void setConnectedGpr();
	void setDisconnectedGpr();

	void syncToSlave();
	void onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

	void setCmdMain(bool on);
	void setCmdRipch(bool on);
	void setCmdImitator(bool on);
	void setCmdActiveSensor(quint32 sensor);
	void setCmdOverview(quint32 number);

	void resetTables();
	void setMain(bool on);
	void toggleMain();
	void setRipch(bool on);
	void toggleRipch();
	void toggleImitatorPeriod();
	void toggleAzimuthSource();
	void toggleAzimuthMode();
	void toggleAzimuthPeriod();
	void toggleAzimuthLir1Load();
	void toggleAzimuthLir2Load();
	void toggleAzimuthSerialLoad();

	void toggleBlockZu();
	void toggleBlockSwitch();
	void toggleBlockYY();
	void toggleVaruBan();
	void toggleTestSin();
	void toggleStrobeEnable();
	void toggleBlockAvto();
	void toggleImpulsePrd();
	void toggleTimerSource();
	void toggleSharuSource();
	void toggleErrorZu1();
	void toggleErrorZu2();
	void toggleTimerLoad();

	void toggleSkrOn();
	void toggleSkrAlwaysOn();
	void togglePilotOn();
	void togglePilotAlwaysOn();
	void toggleGshOn();
	void toggleGshAlwaysOn();
	void toggleZuOn();
	void toggleZuAlwaysOn();

	void setLir1Offset(quint32 offset);
	void setLir2Offset(quint32 offset);
	void setLirOffsets(quint32 offset1, quint32 offset2);
	void setSharu1Code(quint32 code);
	void setSharu2Code(quint32 code);
	void setSharuCodes(quint32 code1, quint32 code2);
	void setSharuSource(quint32 source);
	void setAmpDelayPilotParam(quint32 parameter, quint32 value);
	void setStepDopler(quint32 value);
	void setFreqDeviation(quint32 value);
	void setSyncrOutput(quint32 value);
	void setImpulsePrd(quint32 value);

	void setDump(quint32 info);
	void startMonitor();
	void stopMonitor();
	void setMonitorRate(quint32 rate);

	void setDisableTotal(bool on);
	void setDisableDynamic(AskuSektorTable data);

	void setTemperature(double value);

	void refreshTables(quint32 what, bool files);
	void saveTableRipch(QVariantMap mapdata, bool save);
	void saveTableMode(QVariantMap mapdata, bool save);
	void saveTableSwitch(QVariantMap mapdata, bool save);
	void saveTableDisable(QVariantMap mapdata, bool save);

	void updateSkrPilot();
	void refreshSetPrm();

	void setPrmSharu1Code(quint32 code);
	void setPrmSharu2Code(quint32 code);
	void setPrmGSH(bool on);
	void setPrmZU(bool on);
	void setPrmPILOT(bool on);
	void setPrmSKR(bool on);
	void setPrmOn(bool on);

signals:
	void sigStateLocal(AskuBinStateSet state, AskuValueSet values);
	void sigStateOther(AskuBinStateSet state, AskuValueSet values);

	void sigSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

	void sigChangedAzimuthSource(quint32 source);
	void sigChangedOffsets(quint32 offset1, quint32 offset2, quint32 reason = 0);

	void sigDumpRegisters(DEVICE_REGISTERS device);
	void sigRefreshRegisters(DEVICE_REGISTERS device);
	void sigStatusMessage(QString status);

	void sigTableRipch(QVariantMap data, qint32 maxRow);
	void sigTableMode(QVariantMap data, qint32 maxRow);
	void sigTableSwitch(QVariantMap data, qint32 maxRow);
	void sigTableDisable(QVariantMap data, qint32 maxRow);
	void sigTablesResults(QString message);

	bool tablesRefresh(DEVICE_TABLES*);
	void tablesResult(qint32 result);

	void errorTables(int code, QString * filename = NULL);

	void checkState(DEVICE_REGISTERS *device);

	void sigLoadTablesMessage(quint32 code);
	void sigLoadTablesComplete();

	void sigV4Version(quint32);
	void sigTemperature(qreal temp);

	void sigRefreshSetPrmInfo(QVariantMap setPrmInfo);

public:
	DASD_SERVICE(DASD_THREAD * parent);
	~DASD_SERVICE();

	bool init();

	bool isInitialized();
	bool isErrorDevice();
	bool isLoadedTables();
	bool isLoadedEPROM();
	bool isNeedReboot();
	bool isCmdMain();

	bool isDeviceOk();
	bool isFrefOk();
	bool isModeMaster();
	bool isAntennaGpsOk();
	bool isAz1SensorOk();
	bool isAz2SensorOk();
	bool isSerialSensorOk();
	bool is123GF01Ok();
	bool isSvchSwitchSOk();
	bool isSvchSwitchDOk();
	bool isZuSOk();
	bool isZuDOk();
	bool isZuSCtrlOk();
	bool isZuDCtrlOk();

	bool periodOk();
	double periodValue();
};

//-----------------------------------------------------------------------------

#endif // __DASD_SERVICE_H__
