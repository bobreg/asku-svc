#ifndef __VOSPD_SERVICE_H__
#define __VOSPD_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/tcpnetwork.h"
#include "../common/udpnetwork.h"
#include "../common/stateset.h"
#include "vospd_struct.h"
#include "vospd_parser.h"

//-----------------------------------------------------------------------------

class VOSPD_THREAD;

// ----------------------------------------------------------------------------

class VOSPD_SERVICE : public QObject
{
	Q_OBJECT

	VOSPD_THREAD *parent;

	bool m_isInitialized[2];
	bool m_isConnected[2];
	qint32 m_counterState[2];
	bool m_cmdMain;
	quint32 m_azimuthSource;
	qint32 m_queryState;

	TcpNetwork *network_tcp[2];
	UdpNetwork *network_udp;

	quint16 m_portOur;
	QHostAddress m_haVospd[2];
	qint32 m_idVospd[2];
	AskuVospdParser m_dataVospd[2];

	QTimer *stateTimer;
	QTimer *queryTimer;

	AskuBinStateSet m_VospdState;
	AskuValueSet m_VospdValues;

protected:
	enum { STATEVOSPD_MAX_TIMEOUT = 10 };

	bool parseData(qint32 id, QByteArray & data);
	bool processMessage(quint32 n_vospd, const QByteArray & message);
	bool processVersion(quint32 n_vospd, const QByteArray & message);
	bool processState(quint32 n_vospd, const QByteArray & message);
	bool processAngles(quint32 n_vospd, const QByteArray & message);
	bool processFrameFormat(quint32 n_vospd, const QByteArray & message);
	bool processActiveSensor(quint32 n_vospd, const QByteArray & message);
	bool processConfig(quint32 n_vospd, const QByteArray & message);
	bool processSetActiveSensor(quint32, const QByteArray & message);

	void sendToVospd(QByteArray data, qint32 n_vospd);
	void sendRequestState(qint32 n_vospd);
	void sendRequestVersion(qint32 n_vospd);
	void sendRequestAngles(qint32 n_vospd);
	void sendIpAddress(qint32 n_vospd);
	void sendImitator(qint32 n_vospd, bool on);
	void sendFrameFormat(qint32 n_vospd, quint8 format);
	void sendRequestActSensor(qint32 n_vospd);
	void sendRequestConfig(qint32 n_vospd);
	void sendActiveSensor(qint32 n_vospd, quint8 n_active);

	void updateStatus(quint32 n_vospd, const VospdStatus & status);
	void updateAngles(quint32 n_vospd, const VospdAnswerAngles & angles);
	void updateActSensor(quint32 n_vospd, quint8 act_sensor);
	void updateConfig(quint32 n_vospd, const VospdConfig & config);
	void updateCorrections(quint32 n_vospd, const VospdAzimuthCorrection & az1_cor, const VospdAzimuthCorrection & az2_cor);
	void updateCommonState();
	void clearVospd(quint32 n_vospd);

protected slots:
	void timeout();
	void queryTimeout();

	void onDataArrived(QByteArray data, QHostAddress address, quint16 port);	//udp

	void onDataArrived(qint32 id, QByteArray data);					//tcp
	void onConnected(qint32 id, QHostAddress address, quint16 port);
	void onDisconnected(qint32 id);

public slots:
//slots from thread
	void setMain(bool on);
	void onChangedAzimuthSource(quint32 channel);

signals:
	void sigChangedState();

public:
	VOSPD_SERVICE(VOSPD_THREAD * parent);
	~VOSPD_SERVICE();

	bool init();
	bool isInitialized();

signals:
	void sigState(AskuBinStateSet state, AskuValueSet values);
};

//-----------------------------------------------------------------------------

#endif // __VOSPD_SERVICE_H__
