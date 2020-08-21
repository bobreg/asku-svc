#ifndef __CORETEMP_SERVICE_H__
#define __CORETEMP_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/stateset.h"

#ifdef LM_SENSORS_LIB
	#include "sensors/sensors.h"
#endif

//-----------------------------------------------------------------------------

class CORETEMP_THREAD;

//-----------------------------------------------------------------------------

class CORETEMP_SERVICE : public QObject
{
	Q_OBJECT

protected:
	bool m_isInited;
	bool m_isMonitored;

	CORETEMP_THREAD *parent;

	QTimer *m_timer;

	AskuBinStateSet bCoreStateLocal;
	AskuValueSet bCoreValuesLocal;

	AskuBinStateSet bCoreStateOther;
	AskuValueSet bCoreValuesOther;

	void updateState();

	void updateInfoOs();
	void updateInfoKernel();
	void updateInfoCpu();

	void updateInfoCpuTemp();
	void updateInfoMemory();
	void updateInfoHdd();
	void updateInfoSysLoad();

	void clearOtherState();

protected slots:
	void onRefreshCoreTemp();

	void syncToSlave();
	void onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

public slots:
	void onChangedMain(bool main);

	void setConnectedGpr();
	void setDisconnectedGpr();

	void startMonitor();
	void stopMonitor();

public:
	CORETEMP_SERVICE(CORETEMP_THREAD * parent);
	~CORETEMP_SERVICE();

	bool init();

signals:
	void sigSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

	void sigStateLocal(AskuBinStateSet state, AskuValueSet values);
	void sigStateOther(AskuBinStateSet state, AskuValueSet values);

	void sigChangedState();
};

//-----------------------------------------------------------------------------

#endif // __CORETEMP_SERVICE_H__
