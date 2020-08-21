#ifndef AVT_H_INCLUDED
#define AVT_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"

class Avtomatica : public QObject
{
	Q_OBJECT

	bool m_main;
	bool m_connected;
	bool m_ready;
	qint32 m_status;
	QString m_avtVersion;

	QTimer *m_processTimer;

	AskuBinStateSet bAvtState;
	AskuValueSet bAvtValue;

protected:
	void algorithmAvt();

public:
	Avtomatica(QObject * parent = 0);
	~Avtomatica();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

public slots:
	void onChangedMain(bool on);
	void cmdQuery();
	void refreshState(QVariantMap info);
	void onRefreshAvt();

	void start();
	void stop();

	void processTimeout();

	void onConnected();
	void onDisconnected();

private slots:
	void syncToSlave(QVariantMap data);
	void sendAction(QString command, QStringList parameters = QStringList());
	void sendControlAction(QString command, QStringList parameters = QStringList());

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendControlCommand(QVariantMap data, qint32 idModule = idAskuModulePwm, qint32 idConnection = idConnectionAll);

	void sigState(AskuBinStateSet state, AskuValueSet values);
	void sigOnSyncToSlave(QVariantMap data);
	void sigNeedSyncToSlave();
};

#endif //AVT_H_INCLUDED
