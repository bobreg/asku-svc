#ifndef POI_H_INCLUDED
#define POI_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "poi_thread.h"
#include "../common/module.h"
#include "../common/stateset.h"

class POI : public POI_THREAD
{
	Q_OBJECT

public:
	POI(QObject * parent = 0);
	~POI();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

protected slots:
	void syncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff, QVariantMap pilot);

public slots:
	void onChangedMain(bool on);
	void onResetKoeff();

	void onConnectedGpr();
	void onDisconnectedGpr();

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigStateLocal(AskuBinStateSet state);
	void sigKoeffLocal(AskuValueSet state);
	void sigPilotLocal(AskuValueSet state);
	void sigTransmitterLocal(AskuValueSet state);

	void sigStateOther(AskuBinStateSet state);
	void sigKoeffOther(AskuValueSet state);
	void sigPilotOther(AskuValueSet state);
	void sigTransmitterOther(AskuValueSet state);

	void sigOnSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap koeff, QVariantMap pilot);
	void sigNeedSyncToSlave();
};

#endif //POI_H_INCLUDED
