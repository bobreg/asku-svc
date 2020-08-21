#ifndef COOLERS_THREAD_H_INCLUDED
#define COOLERS_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>

class COOLERS_SERVICE;

class COOLERS_THREAD : public QThread
{
	Q_OBJECT

	COOLERS_SERVICE *service;

public:
	COOLERS_THREAD(QObject * parent = 0);
	~COOLERS_THREAD();

	void start();
	void run();
	void quit();
	void csleep(unsigned long msec);

	quint8 state();

signals:
//signals to service
	void sigSetMain(bool on);
	void sigSetTemperature(quint32 n_cooler, bool on, double temperature);
	void sigSetExtTemperature(double temperature);
	void sigSetReset();
	void sigSetManual(bool manual);
	void sigSetOn(quint32 n_cooler, bool on);
	void sigSetFreq(quint32 n_cooler, double freq);
	void sigRefreshState();
	void sigStartMonitor();
	void sigStopMonitor();
};

#endif //COOLERS_THREAD_H_INCLUDED
