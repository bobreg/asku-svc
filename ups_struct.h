#ifndef _UPS_STRUCT_H_
#define _UPS_STRUCT_H_

#include <QDateTime>
#include <QVariantMap>


#define UPS_MAX_N_DEVICES			2

#define UPS_TYPE_NONE				0
#define UPS_TYPE_MODBUS_POWERWARE	1
#define UPS_TYPE_MODBUS_APC			2
#define UPS_TYPE_SNMP_POWERWARE		3
#define UPS_TYPE_SNMP_APC			4


typedef struct tagUpsConfig
{
	unsigned int type;
	unsigned int count;

	bool main;
	bool monitor;

	tagUpsConfig()
	{
		type = UPS_TYPE_NONE;
		count = 0;
		main = false;
		monitor = false;
	}

	tagUpsConfig(const QVariantMap & data)
	{
		fromMap(data);
	}

	QVariantMap toMap() {
		QVariantMap map;
		map["main"]		= main;
		map["type"]		= type;
		map["count"]	= count;
		map["monitor"]	= monitor;
		return map;
	}

	void fromMap(const QVariantMap & map) {
		main	= map["main"].toBool();
		type	= map["type"].toBool();
		count	= map["count"].toBool();
		monitor	= map["monitor"].toBool();
	}

}UpsConfig;


#endif // _UPS_STRUCT_H_
