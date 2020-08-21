#ifndef VRL_H_INCLUDED
#define VRL_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "../common/sectortable.h"
#include "vrl_thread.h"

class VRL : public VRL_THREAD
{
	Q_OBJECT

public:
	VRL(QObject * parent = 0);
	~VRL();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

protected slots:
	void syncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff);

public slots:
	void onChangedMain(bool on);

	void onConnectedGpr();
	void onDisconnectedGpr();

	void cmdSetMainVRL(quint32 n_vrl);
	void cmdSetDisableReconfVRL(bool on);
	void cmdDisableTotal(bool on);
	void cmdDisableDynamic(AskuSektorTable data);
	void refreshState(QVariantMap info);

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigState(AskuBinStateSet state);
	void sigKoeff(AskuValueSet state);

	void sigOnSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff);
	void sigNeedSyncToSlave();
};

#endif //VRL_H_INCLUDED
