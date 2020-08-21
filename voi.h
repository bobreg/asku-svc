#ifndef VOI_H_INCLUDED
#define VOI_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "../common/sectortable.h"
#include "globalvar.h"
#include "voi_thread.h"

class VOI : public VOI_THREAD
{
	Q_OBJECT

public:
	VOI(QObject * parent = 0);
	~VOI();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

protected slots:
	void syncToSlave(QVariantMap config, QVariantMap state);

public slots:
	void onChangedMain(bool on);

	void onConnectedGpr();
	void onDisconnectedGpr();

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idmodule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigStateLocal(AskuBinStateSet state);
	void sigStateOther(AskuBinStateSet state);

	void sigUpdateSkrPilot();
	void sigDisableTotal(bool on);
	void sigDisableDynamic(AskuSektorTable data);

	void sigOnSyncToSlave(QVariantMap config, QVariantMap state);
	void sigNeedSyncToSlave();
};

#endif //VOI_H_INCLUDED
