#ifndef __CONTROL_RAF_H__
#define __CONTROL_RAF_H__

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QVariantMap>
#include <QStringList>
#include "../common/global.h"
#include "../common/module.h"
#include "../common/stateset.h"

// ----------------------------------------------------------------------------

typedef QVariantMap AskuRlkCommandSet;

// ----------------------------------------------------------------------------

typedef struct _AskuRafMessage
{
	QString message;
	QString state;
	QString time;

	_AskuRafMessage(QString mes, QString st, QString t)
	{
		message = mes;
		state = st;
		time = t;
	}
	QStringList toList()
	{
		return QStringList() << message << state << time;
	}
	
}AskuRafMessage;

// ----------------------------------------------------------------------------

class AskuRlkRafMessage : public QList<AskuRafMessage>
{
public:
	AskuRlkRafMessage();
	AskuRlkRafMessage(QVariantList list);
	QVariantList toList();
};

// ----------------------------------------------------------------------------

typedef struct _AskuOnOffCommand
{
	QString device;
	quint32 time;
	QString status;
	QString textCommand;
	QString textKvit;
	QString textError;

	_AskuOnOffCommand(QString d = QString(), quint32 t = 0, QString tc = QString(), QString tk = QString(), QString te = QString())
	{
		device = d;
		time = t;
		status = "off";
		textCommand = tc;
		textKvit = tk;
		textError = te;
	}
}AskuOnOffCommand;

// ----------------------------------------------------------------------------

class AskuCommandList : public QList<AskuOnOffCommand>
{
public:
	AskuCommandList();


	AskuOnOffCommand & operator[](int i);
	const AskuOnOffCommand & operator[](int i) const;

	AskuOnOffCommand operator[](QString device);
	void setStatus(QString st);
};

// ----------------------------------------------------------------------------

class AskuOnOffRaf
{
public:
	QTimer *m_onOffTimer;

	AskuCommandList m_timeOn;
	AskuCommandList m_timeOff;

	quint32 m_OnOffRafMultiplier;
	quint32 m_OnOffRafInterval;
	quint32 m_OnOffRafCounter;
	quint32 m_OnOffRafCounterFinish;
	qint32 m_OnOffRafStatus;

	AskuOnOffRaf();
};

// ----------------------------------------------------------------------------

#endif //__CONTROL_RAF_H__