#ifndef PWM_H_INCLUDED
#define PWM_H_INCLUDED

#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"

class PowerMeter : public QObject
{
	Q_OBJECT

	bool m_main;
	bool m_connected;
	bool m_ready;
	bool m_opened;
	bool m_applied;
	bool m_fault;
	bool m_processing;
	bool m_measured;
	double m_value;
	double m_koeff;
	qint32 m_status;
	QString m_pwmVersion;
	QString m_pwmName;
	QString m_pwmSerial;

	QTimer *m_processTimer;

	AskuBinStateSet bPwmState;
	AskuValueSet bPwmValue;

protected:
	void algorithmPwm();
	double calc_power(double value, double koeff);

public:
	PowerMeter(QObject * parent = 0);
	~PowerMeter();

	qint32 processControlCommand(QVariantMap data);
	qint32 processInfo(QVariantMap data);

public slots:
	void onChangedMain(bool on);
	void cmdMeasure();
	void cmdReset();
	void refreshState(QVariantMap info);
	void onRefreshPwm();

	void start();
	void stop();

	void processTimeout();

	void onConnected();
	void onDisconnected();

private slots:
	void syncToSlave(QVariantMap data);
	void sendAction(QString command, QStringList parameters = QStringList());
	void sendControlAction(QString command, QStringList parameters = QStringList());

signals:
	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendControlCommand(QVariantMap data, qint32 idModule = idAskuModulePwm, qint32 idConnection = idConnectionAll);

	void sigState(AskuBinStateSet state, AskuValueSet values);
	void sigOnSyncToSlave(QVariantMap data);
};

#endif //PWM_H_INCLUDED
