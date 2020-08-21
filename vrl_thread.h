#ifndef VRL_THREAD_H_INCLUDED
#define VRL_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>
#include "vrl_struct.h"

class VRL_SERVICE;

class VRL_THREAD : public QThread
{
	Q_OBJECT

	VRL_SERVICE *service;

public:
	VRL_THREAD(QObject * parent = 0);
	~VRL_THREAD();

	void start();
	void run();
	void quit();
	void csleep(unsigned long msec);

	quint8 state();

signals:
//signals to service
	void sigSetMain(bool on);
	void sigSetDisableTotal(bool on);

	void sigConnectedGpr();
	void sigDisconnectedGpr();

	void sigRefreshState();

	void sigSetMainVRL(quint32 n_vrl);
	void sigSetDisableReconf(bool on);
};

#endif //VRL_THREAD_H_INCLUDED
