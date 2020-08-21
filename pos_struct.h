#ifndef _POS_STRUCT_H_INCLUDED_
#define _POS_STRUCT_H_INCLUDED_

//-----------------------------------------------------------------------------
#include <QDateTime>
//-----------------------------------------------------------------------------

struct PosAlarm
{
	quint32 zoneId;
	quint32 sensorId;
	qint32 timeout;
	QDateTime lastSeen;
	QString name;
};


struct PosEventToLog
{
    QString name;
    bool state;
    bool lastState;
    QString type;
    QString event;
    QString Operator;
    QString zone;

};

//-----------------------------------------------------------------------------

#endif //_POS_STRUCT_H_INCLUDED_
