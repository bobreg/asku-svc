#ifndef UPS_THREAD_H_INCLUDED
#define UPS_THREAD_H_INCLUDED

#include <QThread>
#include <QVariantMap>
#include "ups_struct.h"

class UPS_MODBUS_SERVICE;
class UPS_SNMP_SERVICE;

class UPS_THREAD : public QThread
{
	Q_OBJECT

	UPS_MODBUS_SERVICE *service_jbus;
	UPS_SNMP_SERVICE *service_snmp;

public:
	UPS_THREAD(QObject * parent = 0);
	~UPS_THREAD();

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

#endif //UPS_THREAD_H_INCLUDED
