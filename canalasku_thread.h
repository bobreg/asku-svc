#ifndef _CANALASKU_THREAD_H_
#define _CANALASKU_THREAD_H_

//-------------------------------------------------------------------

#include <QThread>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QHostAddress>
#include "canalasku_data.h"
#include "canalasku_codec.h"

//-------------------------------------------------------------------

#define COMM_QCNT 2

//-------------------------------------------------------------------

typedef struct _CA_tag_TYPE_TRANSMITTER_MODULE
{
	quint32 transmitter;
	quint32 module;

	_CA_tag_TYPE_TRANSMITTER_MODULE() {
		transmitter = 0;
		module = 0;
	}
	_CA_tag_TYPE_TRANSMITTER_MODULE(quint32 t, quint32 m) {
		transmitter = t;
		module = m;
	}
	bool operator< ( const _CA_tag_TYPE_TRANSMITTER_MODULE & t ) const {
		return ((transmitter < t.transmitter) || (transmitter < t.transmitter && module < t.module));
	}
	bool operator== ( const _CA_tag_TYPE_TRANSMITTER_MODULE & t ) const {
		return (transmitter == t.transmitter && module == t.module);
	}
}CA_TYPE_TRM;

//-------------------------------------------------------------------

class CanalAskuThread : public QThread, protected CanalAskuCodec
{
	Q_OBJECT

	enum ConnectionState {
		Disconnected = 0,
		Waiting = 1,
		Connected = 2
	};

	enum CommunicatorState {
		Undefined = 0,
		NoAnswer = 1,
		GoodAnswer = 2
	};

	enum CanalAskuMode
	{
		SlaveMode = -1,
		NormalMode = 0,
		LoaderMode = 1,
		PhaseMode = 2
	};

	ConnectionState connected[COMM_QCNT];
	CommunicatorState communicator[COMM_QCNT];

	QTcpSocket *socket[COMM_QCNT];

	CanalAskuData *canalAskuData;
	CanalAskuData *canalAskuDataOther;
	CanalAskuCommand *canalAskuCommand;

	QHostAddress adress[COMM_QCNT];
	quint16 port[COMM_QCNT];

	bool m_isMain;
	quint32 m_mainTimeout;
	bool waiting;
	bool running;
	bool changedActive;
	quint32 n_active;
	quint32 n_passive;
	bool test_active;
	bool test_passive;
	quint32 n_dc_umi;
	QMap<CA_TYPE_TRM, quint32> mon_dc_umi;

	CanalAskuMode m_mode;

	void connectToHost(quint32);
	void disconnectFromHost(quint32);

	bool doExchange(quint8 command, quint32 nc, quint32 ncp, qint32 ndevice = -1, qint32 nmodule = -1);
	bool doListenSlave(quint32 ncp);

	void setAskuState(quint8 command, qint32 numOY, qint8 nMODULE, quint8 state);
	void setAskuData(quint8 command, qint32 numOY, qint8 nMODULE, quint8* packet, quint8 packetSize);

public:

	CanalAskuThread(QObject *parent = 0);
	~CanalAskuThread();

	bool isMain() {
		return m_isMain;
	}

	void setMode(CanalAskuMode mode);

	void cancelMonitored();
	void addMonitoredModule(quint32 transmitter, quint32 module);
	void removeMonitoredModule(quint32 transmitter, quint32 module);

	void run();
	void quit();

// --
	QVariantMap getCanalAskuDataLocal();
	void setCanalAskuDataOther(const QVariantMap & data);
// --

public slots:
	void setMain(bool on);

	void setMonitoredModule(quint32 n_prd, quint32 n_module);
	void dataReady();

	void updateCommands(CanalAskuCommand *command);

signals:
	void readyData(CanalAskuData* data);
};

//-------------------------------------------------------------------

#endif //_CANALASKU_THREAD_H_
