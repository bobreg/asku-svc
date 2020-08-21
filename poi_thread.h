#ifndef POI_THREAD_H_INCLUDED
#define POI_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>
#include "poi_struct.h"

class POI_SERVICE;

class POI_THREAD : public QThread
{
	Q_OBJECT

	POI_SERVICE *service;

public:
	POI_THREAD(QObject * parent = 0);
	~POI_THREAD();

	void start();
	void run();
	void quit();
	void csleep(unsigned long msec);

	quint8 state();

signals:
//signals to service
	void sigSetMain(bool on);
	void sigResetKoeff();

	void sigConnectedGpr();
	void sigDisconnectedGpr();

	void sigRefreshState();

	void sigSetTemperature(double temp);
};

#endif //POI_THREAD_H_INCLUDED
