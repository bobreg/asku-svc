#ifndef __VOI_SERVICE_H__
#define __VOI_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/udpnetwork.h"
#include "../common/stateset.h"
#include "../common/sectortable.h"
#include "voi_struct.h"

//-----------------------------------------------------------------------------

class VOI_THREAD;

//-----------------------------------------------------------------------------

class VOI_SERVICE : public QObject
{
	Q_OBJECT

	VOI_THREAD *parent;

	bool m_isInitialized;
	bool m_isConnected;

	qint32 m_status;	//0 - osn, 1 - rez, -1 - unknown (disconnected)
	qint32 m_startedTimeout;
	quint32 m_controlTimeout;
	quint32 m_restartTimeout;
	quint32 m_changedTimeout;
	qint32 m_rlkStateCounter;
	quint32 m_helloCounter;
	quint32 m_avarPRL, m_avarVRL, m_avarNRZ, m_avarAZN, m_avarMPS;

	UdpNetwork *network;
	QHostAddress m_haVoi;
	quint16 m_portAsku;
	quint16 m_portVoi;

	QVariantMap m_disTable;
	QVariantMap m_rlkState;

	QTimer *timer;

	enum { STARTED_MAX_TIMEOUT = 10 };
	enum { CONTROL_MAX_TIMEOUT = 10 };
	enum { RESTART_MAX_TIMEOUT = 10 };
	enum { CHANGED_MAX_TIMEOUT = 35 };

	enum { AVAR_PRL_TIMEOUT = 1 };
	enum { AVAR_VRL_TIMEOUT = 1 };
	enum { AVAR_NRZ_TIMEOUT = 1  };
	enum { AVAR_AZN_TIMEOUT = 1  };
	enum { AVAR_MPS_TIMEOUT = 1  };

	VoiConfig m_voiConfig;

	AskuBinStateSet bVoiLocalState;
	AskuBinStateSet bVoiOtherState;

protected:
	void sendToVOI(quint16 *buffer, quint16 num_words);
	void sendHello();
	void sendAnswer();
	void sendLive();
	void sendBye();
	void sendSkr();
	void sendHidePanel();
	void sendPressure(unsigned short pressure, bool avar);
	void sendCmdReg(bool main, bool oper);
	void sendDisableSektors();
	void sendRlsState();

	void processData(quint16 *data, quint16 num_words);
	void recvCloseApp(TC_VOI_64* tc);
	void recvMoveWindow(TC_VOI_66* tc);
	void recvChangedReg(TC_VOI_68* tc);
	void recvHello(TC_VOI_71* tc);
	void recvAnswer(TC_VOI_72* tc);
	void recvLive(TC_VOI_76* tc);
	void recvGpsData(TC_VOI_77* tc);
	void recvState(TC_VOI_84* tc);
	void recvDisable(TC_VOI_89* tc);

	void checkStatus();
	void checkTimeouts();
	void connectVOI();
	void disconnectVOI();

	void clearLocalState();
	void clearOtherState();

	void cmdChangeReg(bool main, bool oper);

protected slots:
	void timeout();
	void onDataArrived(QByteArray data, QHostAddress haFrom, quint16 portFrom);

public slots:
//slots from thread
	void setMain(bool on);

	void setConnectedGpr();
	void setDisconnectedGpr();

	void setRlsState(QVariantMap rlkState);
	void setDisableSektors(QVariantMap disableTable);
	void setControlSektor();

	void syncToSlave();
	void onSyncToSlave(QVariantMap config, QVariantMap state);

public:
	VOI_SERVICE(VOI_THREAD * parent);
	~VOI_SERVICE();

	bool init();
	bool isInitialized();

signals:
	void sigStateLocal(AskuBinStateSet state);
	void sigStateOther(AskuBinStateSet state);

	void sigSyncToSlave(QVariantMap config, QVariantMap state);
	void sigChangedState();

	void sigDisableTotal(bool on);
	void sigDisableDynamic(AskuSektorTable data);
};

//-----------------------------------------------------------------------------

#endif // __VOI_SERVICE_H__
