#ifndef VOI_THREAD_H_INCLUDED
#define VOI_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>
#include "voi_struct.h"

class VOI_SERVICE;

class VOI_THREAD : public QThread
{
	Q_OBJECT

protected:
	VOI_SERVICE *service;

public:
	VOI_THREAD(QObject * parent = 0);
	~VOI_THREAD();

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
};

#endif //VOI_THREAD_H_INCLUDED
