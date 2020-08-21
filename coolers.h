#ifndef COOLERS_H_INCLUDED
#define COOLERS_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "modbus_service.h"
#include "coolers_thread.h"
#include "coolers_struct.h"

class COOLERS : public COOLERS_THREAD
{
	Q_OBJECT

public:
	COOLERS(QObject * parent = 0);
	~COOLERS();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

public slots:
	void onChangedMain(bool on);

	void onSetTemperature(quint32 n_cooler, bool on, double temperature);
	void onSetExtTemperature(double temperature);
	void onSetReset();
	void onSetOn(quint32 n_cooler, bool on);

	void cmdSetSvo1On(bool oper = false);
	void cmdSetSvo2On(bool oper = false);
	void cmdSetSvo1Off(bool oper = false);
	void cmdSetSvo2Off(bool oper = false);

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

#endif //COOLERS_H_INCLUDED
