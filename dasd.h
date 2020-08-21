#ifndef DASD_H_INCLUDED
#define DASD_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "../common/sectortable.h"
#include "dasd_thread.h"

class DASD : public DASD_THREAD
{
	Q_OBJECT

protected:
	QString stringBits(quint32 data, quint32 bits);
	QString stringNum10(quint32 data);
	QString stringNum4_10(quint32 data);
	QString stringNum4(quint32 data);
	QString stringNum3(quint32 data);
	QString stringNum2(quint32 data);
	QString stringNum(quint32 data);
	QString stringNum64(quint32 data_low, quint32 data_high);
	QString stringFloat(quint8 data, double koeff);
	QString stringFloat1(quint32 data, double koeff);
	QString stringFloat1s(quint32 data, double koeff);
	QString stringFloat2(double data);
	QString stringVersion(quint32 data);

public:
	DASD(QObject * parent = 0);
	~DASD();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

protected slots:
	void syncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

public slots:
	void onChangedMain(bool on);

	void onConnectedGpr();
	void onDisconnectedGpr();

	void onSetReset();

	void dumpRegisters(DEVICE_REGISTERS devRegs);
	void refreshRegisters(DEVICE_REGISTERS devRegs);
	void commandList(QStringList list);
	void statusMessage(QString message);

	void refreshSkrPilot();
	void setSkrPilot(quint32 azSKR, quint32 azPS, quint32 period);

	void setFreqDeviation(quint32 value);

	void refreshSetPrmInfo(QVariantMap setPrmInfo);

	void tableRipch(QVariantMap table, qint32 maxRow);
	void tableMode(QVariantMap table, qint32 maxRow);
	void tableSwitch(QVariantMap table, qint32 maxRow);
	void tableDisable(QVariantMap table, qint32 maxRow);
	void tablesResults(QString message);

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigStateLocal(AskuBinStateSet state, AskuValueSet values);
	void sigStateOther(AskuBinStateSet state, AskuValueSet values);

	void sigOnSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);
	void sigNeedSyncToSlave();

	void sigFlushSettings();
	void sigChangedAzimuthSource(quint32 source);
};

#endif
