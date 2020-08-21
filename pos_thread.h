#ifndef POS_THREAD_H_INCLUDED
#define POS_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>
#include "pos_struct.h"

class POS_SERVICE;

class POS_THREAD : public QThread
{
	Q_OBJECT

	POS_SERVICE *service;

public:
	POS_THREAD(QObject * parent = 0);
	~POS_THREAD();

	void start();
	void run();
	void quit();
	void csleep(unsigned long msec);

	quint8 state();

signals:
//signals to service
    void sigSetMain(bool on);
};

#endif //POS_THREAD_H_INCLUDED
