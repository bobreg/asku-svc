#ifndef __VRL_SERVICE_H__
#define __VRL_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/udpnetwork.h"
#include "../common/stateset.h"
#include "vrl_struct.h"

//#define FAKE_VRL

//-----------------------------------------------------------------------------

class VRL_THREAD;

//-----------------------------------------------------------------------------
const unsigned short PrmShMaxValue = 65535;
const unsigned short PrmAmpRbsMinValue = 0;
const unsigned short PrmAmpNrzF2MinValue = 0;
const unsigned short PrmAmpNrzF3MinValue = 0;
const unsigned short AznShMaxValue = 65535;
const unsigned short AznAmpMinValue = 0;
//-----------------------------------------------------------------------------

class VRL_SERVICE : public QObject
{
	Q_OBJECT

	VRL_THREAD *parent;
	UdpNetwork *network;

	VrlConfig m_vrlConfig;

	bool m_isInitialized;
	bool m_cmdMain;

	bool m_allowReserve;
	qint32 m_nOsnVRL;
	qint32 m_nOsnVRLState[N_VRLS];
	quint32 m_avarStatusCounter;
	quint32 m_timeoutCounter[N_VRLS];
	quint32 m_workVrl[N_VRLS];
	qint32 m_mest[N_VRLS];
	qint32 m_state[N_VRLS];

	bool m_isConnected[N_VRLS];
	QHostAddress m_haVrl[N_VRLS];
	quint16 m_portOur;
	quint16 m_portVrl;

	QTimer *m_timer;

#ifdef FAKE_VRL
	QTimer *m_fakeTimer;
#endif

	AskuBinStateSet bVrlState;

	enum { CONNECT_MAX_TIMEOUT = 35 };

protected:
	void sendToVRL(quint32 n_vrl, QByteArray data);
	void processData(quint32 n_vrl, QByteArray data);

	void process_209(MESSAGE_209 * mes);
	void clearVrl(quint32 n_vrl);

	void commandVRL(bool priority = false);
	void checkReserve(quint32 status);

	void verifyObSostVRL();
	void panelCommonState();
	void subblocksCommonState();
	void process_panel(MESSAGE_209 * mes);
	void process_subblocks(MESSAGE_209 * mes);
	void process_vum(MESSAGE_209 * mes);
	void process_prm(MESSAGE_209 * mes);
	void process_azn(MESSAGE_209 * mes);
	void process_obr(MESSAGE_209 * mes);
	void process_zao(MESSAGE_209 * mes);

protected slots:
	void timeout();
	void onDataArrived(QByteArray data, QHostAddress haFrom, quint16 portFrom);

#ifdef FAKE_VRL
	void fakeCommands();
#endif

public slots:
//slots from thread
	void setMain(bool on);

	void setMainVRL(quint32 n_vrl);
	void setDisableTotal(bool on);
	void setDisableReconf(bool on);
	void setAutoMainVRL();

	void onRefreshVrl();

	void setConnectedGpr();
	void setDisconnectedGpr();

	void startMonitor();
	void stopMonitor();

	void syncToSlave();
	void onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff);

public:
	VRL_SERVICE(VRL_THREAD * parent);
	~VRL_SERVICE();

	bool init();
	bool isInitialized();

signals:
	void sigState(AskuBinStateSet state);
	void sigKoeff(AskuValueSet state);

	void sigChangedState();

	void sigVrlState(QVariantMap info);
	void sigSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff);
};

//-----------------------------------------------------------------------------

#endif // __VRL_SERVICE_H__
