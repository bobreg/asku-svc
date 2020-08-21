#ifndef AVT_H_INCLUDED
#define AVT_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "avt_thread.h"
#include "../common/module.h"
#include "../common/stateset.h"

class AVT : public AVT_THREAD
{
	Q_OBJECT

public:
	AVT(QObject * parent = 0);
	~AVT();

public slots:
//	void onChangedState();
	void onChangedMain(bool on);

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigState(AskuBinStateSet state, AskuValueSet value);
};

#endif //POI_H_INCLUDED
