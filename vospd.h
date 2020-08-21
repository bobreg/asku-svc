#ifndef VOSPD_H_INCLUDED
#define VOSPD_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "vospd_thread.h"
#include "../common/module.h"
#include "../common/stateset.h"

class VOSPD : public VOSPD_THREAD
{
	Q_OBJECT

public:
	VOSPD(QObject * parent = 0);
	~VOSPD();

public slots:
//	void onChangedState();
	void onChangedMain(bool on);
	void onChangedAzimuthSource(quint32 channel);

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigState(AskuBinStateSet state, AskuValueSet values);
};

#endif //VOSPD_H_INCLUDED
