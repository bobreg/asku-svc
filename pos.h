#ifndef POS_H_INCLUDED
#define POS_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "pos_thread.h"
#include "../common/module.h"
#include "../common/stateset.h"

class POS : public POS_THREAD
{
	Q_OBJECT

public:
	POS(QObject * parent = 0);
	~POS();

public slots:
//	void onChangedState();
	void onChangedMain(bool on);

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);

	void sigState(AskuBinStateSet state);
    void sigOsvPerimetrOn();
    void sigOsvPerimetrOff();
    void perim_light_on_off(bool);
    void sigEventToLog(QString, QString, QString);
};

#endif //POS_H_INCLUDED
