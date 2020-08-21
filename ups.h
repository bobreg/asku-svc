#ifndef UPS_H_INCLUDED
#define UPS_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "ups_thread.h"

class UPS : public UPS_THREAD
{
	Q_OBJECT

public:
	UPS(QObject * parent = 0);
	~UPS();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

private slots:
	void syncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

public slots:
	void onChangedMain(bool on);

	void onConnectedGpr();
	void onDisconnectedGpr();

	void refreshState(QVariantMap info);

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigState(AskuBinStateSet state, AskuValueSet measure);
	void sigOnSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);
	void sigNeedSyncToSlave();
};

#endif //UPS_H_INCLUDED
