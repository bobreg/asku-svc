#ifndef __DRIVE_SERVICE_H__
#define __DRIVE_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/tcpnetwork.h"
#include "../common/stateset.h"
#include "modbus_service.h"
#include "drive_struct.h"

//-----------------------------------------------------------------------------

class DRIVE_THREAD;
class VECTOR_DEVICE;

//-----------------------------------------------------------------------------

#define VECTOR_N_DEVICES 2

//-----------------------------------------------------------------------------

class DRIVE_SERVICE : public MODBUS_SERVICE
{
	Q_OBJECT

protected:
	DRIVE_THREAD *parent;
	VECTOR_DEVICE *vector[VECTOR_N_DEVICES];

	DriveConfig m_driveConfig;
	DriveState m_state;

	AskuBinStateSet bDriveState;

	bool processData(QByteArray *data);
	void sendToDrive(QByteArray data);

	virtual void updateState();
	void updateVectorState(quint32 n_vector);
	void updatePortState();
	void updateCommonState();
	void verifyFirstCommands();

public:
	DRIVE_SERVICE(DRIVE_THREAD * parent);
	~DRIVE_SERVICE();

	bool init();

	virtual void onChangedDeviceState();
	virtual void onChangedPortState();

protected slots:
	virtual void onConnected();
	virtual void onDisconnected();
	virtual void onConnectedPort(qint32 port);
	virtual void onDisconnectedPort(qint32 port);
	virtual bool onQuery();
	virtual bool onLive();
	void setFirstCommands();

public slots:
	void onChangedMain(bool main);

	void setManual(bool manual);
	void setServo(quint32 n_drive);
	void setOverride(quint32 n_drive);
	void setSpeed(double speed);
	void setReset();

	void onRefreshDrive();

	void startMonitor();
	void stopMonitor();

	void syncToSlave();
	void onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

signals:
	void sigSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);
	void sigState(AskuBinStateSet state);

	void sigDriveState(QVariantMap info);
	void sigChangedState();

	void sigButtonServo(quint32 ndrv);

	void sigStopped();
	void sigStarted();
};

//-----------------------------------------------------------------------------

#endif // __DRIVE_SERVICE_H__
