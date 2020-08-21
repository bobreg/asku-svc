#ifndef DRIVE_H_INCLUDED
#define DRIVE_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "drive_thread.h"
#include "drive_struct.h"

class DRIVE : public DRIVE_THREAD
{
	Q_OBJECT

public:
	DRIVE(QObject * parent = 0);
	~DRIVE();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

public slots:
	void onChangedMain(bool on);

	void onConnectedGpr();
	void onDisconnectedGpr();

	void refreshState(QVariantMap info);

	void onSetSpeed(double speed);
	void onSetServo(quint32 n_drive);
	void onSetOverride(quint32 n_drive);
	void onSetReset();

	void onSetServoOn();
	void onSetServo1On();
	void onSetServo2On();
	void onSetServoOff();

	void onSetOverview(quint32 number);

protected slots:
	void syncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigState(AskuBinStateSet state);

	void sigOnSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);
	void sigNeedSyncToSlave();

	void sigButtonServo(quint32 ndrv);
};

#endif //DRIVE_H_INCLUDED
