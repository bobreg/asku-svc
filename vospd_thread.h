#ifndef VOSPD_THREAD_H_INCLUDED
#define VOSPD_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>
#include "vospd_struct.h"

class VOSPD_SERVICE;

class VOSPD_THREAD : public QThread
{
	Q_OBJECT

	VOSPD_SERVICE *service;

public:
	VOSPD_THREAD(QObject * parent = 0);
	~VOSPD_THREAD();

	void start();
	void run();
	void quit();
	void csleep(unsigned long msec);

	quint8 state();

signals:
//signals to service
	void sigSetMain(bool on);
	void sigChangedAzimuthSource(quint32 channel);
};

#endif //VOSPD_THREAD_H_INCLUDED
