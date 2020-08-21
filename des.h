#ifndef DES_H_INCLUDED
#define DES_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "des_thread.h"

class DES : public DES_THREAD
{
	Q_OBJECT

public:
	DES(QObject * parent = 0);
	~DES();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

public slots:
	void onChangedMain(bool on);
	void refreshState(QVariantMap info);

private slots:
	void syncToSlave(QVariantMap data);

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigState(AskuBinStateSet state);
	void sigOnSyncToSlave(QVariantMap data);
	void sigNeedSyncToSlave();
};

#endif //DES_H_INCLUDED
