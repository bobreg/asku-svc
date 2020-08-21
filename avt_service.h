#ifndef __AVT_SERVICE_H__
#define __AVT_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../common/udpnetwork.h"
#include "../common/stateset.h"
#include "avt_struct.h"

//-----------------------------------------------------------------------------

class AVT_THREAD;

#define N_AVT 2

//-----------------------------------------------------------------------------

class AVT_SERVICE : public QObject
{
	Q_OBJECT

	AVT_THREAD *parent;

	AVT_REQUSITES m_requisites[N_AVT];

	bool m_isInitialized;
	bool m_isConnected[N_AVT];
	bool m_isRequisites[N_AVT];
	qint32 m_counterState[N_AVT];
	bool m_cmdMain;

	UdpNetwork *network;

	quint16 m_portOur;
	quint16 m_portAvt[N_AVT];
	QHostAddress m_haAvt[N_AVT];

	QTimer *timer;

	AskuBinStateSet bAvtState;
	AskuValueSet bAvtParam;

protected:
	enum { STATEAVT_MAX_TIMEOUT = 10 };

	bool processMessage(qint32 n, QByteArray data);
	bool processRequisites(qint32 n, QByteArray data);
	bool processState(qint32 n, QByteArray data);
	bool processErase(qint32 n, QByteArray data);
	void clear(qint32 n);

	void sendToAvt(qint32 n, QByteArray data);

	void sendQueryRequisites(qint32 n);
	void sendQueryState(qint32 n);
	void sendErase(qint32 n);

protected slots:
	void timeout();
	void onDataArrived(QByteArray data, QHostAddress haFrom, quint16 portFrom);

public slots:
//slots from thread
	void setMain(bool on);
	void setErase();

signals:
	void sigChangedState();

public:
	AVT_SERVICE(AVT_THREAD * parent);
	~AVT_SERVICE();

	bool init();
	bool isInitialized();

signals:
	void sigState(AskuBinStateSet state, AskuValueSet value);
};

//-----------------------------------------------------------------------------

#endif // __VOI_SERVICE_H__
