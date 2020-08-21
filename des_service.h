#ifndef __DES_SERVICE_H__
#define __DES_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/tcpnetwork.h"
#include "../common/stateset.h"
#include "modbus_service.h"
#include "des_struct.h"

//-----------------------------------------------------------------------------

class DES_THREAD;
class DEIF_MAINS_DEVICE;
class DEIF_DG_DEVICE;

//-----------------------------------------------------------------------------

#define DES_N_MAINS_DEVICES 2
#define DES_N_DGS_DEVICES 4

//-----------------------------------------------------------------------------

class DES_SERVICE : public MODBUS_SERVICE
{
	Q_OBJECT

	DES_THREAD *parent;

	DesConfig m_desConfig;

	DEIF_MAINS_DEVICE *deif_mains[DES_N_MAINS_DEVICES];
	DEIF_DG_DEVICE *deif_dg[DES_N_DGS_DEVICES];

	AskuBinStateSet bDesState;

	bool isMonitoring;

protected:
	bool processData(QByteArray *data);
	void sendToDes(QByteArray data);

	virtual void updateState();
	void updateDesMainsState(quint32 n_mains);
	void updateDesDgState(quint32 n_dg);
	void updatePortState();
	void updateCommonState();
	void verifyFirstCommands();

protected slots:
	virtual void onConnected();
	virtual void onDisconnected();
	virtual bool onQuery();
	virtual bool onLive();
	void setFirstCommands();

public slots:
	void onChangedMain(bool main);

	void setEngine(quint32 n_dgs, bool on);
	void setPosGB(quint32 n_dgs, bool on);
	void setPosMB(quint32 n_mns, bool on);
	void setPosTB(quint32 n_mns, bool on);
	void setMainsReset(quint32 n_mns);
	void setDgReset(quint32 n_dgs);
	void setMainsMode(quint32 n_mns, quint32 mode);
	void setDgMode(quint32 n_dgs, quint32 mode);

	void onRefreshDes();
	void startMonitor();
	void stopMonitor();
	void syncToSlave();
	void onSyncToSlave(QVariantMap data);

signals:
	void sigChangedState();
	void sigDesState(QVariantMap info);
	void sigSyncToSlave(QVariantMap data);

public:
	DES_SERVICE(DES_THREAD * parent);
	~DES_SERVICE();

	bool init();

	virtual void onChangedDeviceState();
	virtual void onChangedPortState();

signals:
	void sigState(AskuBinStateSet state);
};

//-----------------------------------------------------------------------------

#endif // __DES_SERVICE_H__
