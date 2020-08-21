#ifndef DES_THREAD_H_INCLUDED
#define DES_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>

class DES_SERVICE;

class DES_THREAD : public QThread
{
	Q_OBJECT

	DES_SERVICE *service;

public:
	DES_THREAD(QObject * parent = 0);
	~DES_THREAD();

	void start();
	void run();
	void quit();
	void csleep(unsigned long msec);

	quint8 state();

signals:
//signals to service
	void sigSetMain(bool on);
	void sigRefreshState();
	void sigStartMonitor();
	void sigStopMonitor();
	void sigSetEngine(quint32 n_mns, bool on);
	void sigSetPosGB(quint32 n_dgs, bool on);
	void sigSetPosMB(quint32 n_mns, bool on);
	void sigSetPosTB(quint32 n_mns, bool on);
	void sigSetMainsReset(quint32 n_mns);
	void sigSetDgReset(quint32 n_dgs);
	void sigSetMainsMode(quint32 n_mns, quint32 mode);
	void sigSetDgMode(quint32 n_dgs, quint32 mode);
};

#endif //DES_THREAD_H_INCLUDED
