#ifndef CORETEMP_H_INCLUDED
#define CORETEMP_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "coretemp_thread.h"

class CORETEMP : public CORETEMP_THREAD
{
	Q_OBJECT

public:
	CORETEMP(QObject * parent = 0);
	~CORETEMP();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

public slots:
	void onChangedMain(bool on);

	void onConnectedGpr();
	void onDisconnectedGpr();

	void refreshState(QVariantMap info);

private slots:
	void syncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigStateLocal(AskuBinStateSet state, AskuValueSet values);
	void sigStateOther(AskuBinStateSet state, AskuValueSet values);

	void sigOnSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure);
	void sigNeedSyncToSlave();
};

#endif //CORETEMP_H_INCLUDED
