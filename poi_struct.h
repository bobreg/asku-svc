#ifndef _POI_STRUCT_H_INCLUDED_
#define _POI_STRUCT_H_INCLUDED_

//-----------------------------------------------------------------------------

#define POI_TYPE_OBSERVER 1

//-----------------------------------------------------------------------------

typedef struct tagPoiConfig
{
	unsigned int type;
	bool main;
	bool monitor;
	double temperature;

	tagPoiConfig() {
		type = POI_TYPE_OBSERVER;
		main = false;
		monitor = false;
		temperature = 25.0;
	}

	tagPoiConfig(const QVariantMap & data) {
		fromMap(data);
	}

	QVariantMap toMap() {
		QVariantMap map;
		map["type"] = type;
		map["main"] = main;
		map["monitor"] = monitor;
		map["temperature"] = temperature;
		return map;
	}

	void fromMap(const QVariantMap & map) {
		type = map["type"].toUInt();
		main = map["main"].toBool();
		monitor = map["monitor"].toBool();
		temperature = map["temperature"].toDouble();
	}

}PoiConfig;

//-----------------------------------------------------------------------------

#endif //_POI_STRUCT_H_INCLUDED_
