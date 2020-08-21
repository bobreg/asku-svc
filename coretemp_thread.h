#ifndef CORETEMP_THREAD_H_INCLUDED
#define CORETEMP_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>
#include "../common/stateset.h"

class CORETEMP_SERVICE;

class CORETEMP_THREAD : public QThread
{
	Q_OBJECT

	CORETEMP_SERVICE *service;

public:
	CORETEMP_THREAD(QObject * parent = 0);
	~CORETEMP_THREAD();

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
};

#endif //CORETEMP_THREAD_H_INCLUDED
