#ifndef AVT_THREAD_H_INCLUDED
#define AVT_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>
#include "avt_struct.h"

class AVT_SERVICE;

class AVT_THREAD : public QThread
{
	Q_OBJECT

	AVT_SERVICE *service;

public:
	AVT_THREAD(QObject * parent = 0);
	~AVT_THREAD();

	void start();
	void run();
	void quit();
	void csleep(unsigned long msec);

	quint8 state();

signals:
//signals to service
	void sigSetMain(bool on);
	void sigSetErase();
};

#endif //AVT_THREAD_H_INCLUDED
