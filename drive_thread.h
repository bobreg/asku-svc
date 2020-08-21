#ifndef DRIVE_THREAD_H_INCLUDED
#define DRIVE_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>

class DRIVE_SERVICE;

class DRIVE_THREAD : public QThread
{
	Q_OBJECT

	DRIVE_SERVICE *service;

public:
	DRIVE_THREAD(QObject * parent = 0);
	~DRIVE_THREAD();

	void start();
	void run();
	void quit();
	void csleep(unsigned long msec);

	quint8 state();

signals:
//signals to service
	void sigSetMain(bool on);

	void sigConnectedGpr();
	void sigDisconnectedGpr();

	void sigRefreshState();

	void sigStartMonitor();
	void sigStopMonitor();

	void sigSetReset();
	void sigSetManual(bool manual);
	void sigSetServo(quint32 n_drive);
	void sigSetOverride(quint32 n_drive);
	void sigSetSpeed(double speed);
};

#endif //DRIVE_THREAD_H_INCLUDED
