#ifndef __COOLERS_SERVICE_H__
#define __COOLERS_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/tcpnetwork.h"
#include "../common/stateset.h"
#include "modbus_service.h"
#include "coolers_struct.h"

//-----------------------------------------------------------------------------

class COOLERS_THREAD;
class VESPER_DEVICE;

//-----------------------------------------------------------------------------

#define VESPER_N_DEVICES 4

//-----------------------------------------------------------------------------

class COOLERS_SERVICE : public MODBUS_SERVICE
{
	Q_OBJECT

	COOLERS_THREAD *parent;
	VESPER_DEVICE *vesper[VESPER_N_DEVICES];

	CoolersConfig m_coolerConfig;
	CoolersState m_state;

	AskuBinStateSet bCoolerState;

protected:
	bool processData(QByteArray *data);
	void sendToDrive(QByteArray data);

	virtual void updateState();
	void updateVesperState(quint32 n_vesper);
	void updatePortState();
	void updateCommonState();
	void verifyFirstCommands();
	bool calcFreq(quint32 n_vesper, bool on, double temperature);
	double freqFromExternalT();

protected slots:
	virtual void onConnected();
	virtual void onDisconnected();
	virtual bool onQuery();
	virtual bool onLive();
	void setFirstCommands();

public slots:
	void onChangedMain(bool main);
	void setTemperature(quint32 n_cooler, bool on, double temp);
	void setExtTemperature(double temp);
	void setReset();
	void setManual(bool manual);
	void setOn(quint32 n_cooler, bool on);
	void setFreq(quint32 n_cooler, double freq);
	void onRefreshCoolers();
	void startMonitor();
	void stopMonitor();
	void syncToSlave();
	void onSyncToSlave(QVariantMap data);

signals:
	void sigChangedState();
	void sigCoolersState(QVariantMap info);
	void sigSyncToSlave(QVariantMap data);

public:
	COOLERS_SERVICE(COOLERS_THREAD * parent);
	~COOLERS_SERVICE();

	bool init();

	virtual void onChangedDeviceState();
	virtual void onChangedPortState();

signals:
	void sigState(AskuBinStateSet state);
};

//-----------------------------------------------------------------------------

#endif // __COOLERS_SERVICE_H__
