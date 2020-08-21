#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "coretemp_service.h"
#include "coretemp_thread.h"

// ------------------------------------------------------------------
CORETEMP_SERVICE::CORETEMP_SERVICE(CORETEMP_THREAD *p)
{
	parent = p;
	m_timer = NULL;
	m_isInited = false;
	m_isMonitored = false;
}

// ------------------------------------------------------------------
bool CORETEMP_SERVICE::init()
{
	LogCoreInfo("CoreTempService started");

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(onRefreshCoreTemp()));
	m_timer->start(10000);

	if(!sensors_init(NULL))
		m_isInited = true;

	updateInfoOs();
	updateInfoKernel();
	updateInfoCpu();

	onRefreshCoreTemp();

	return !m_isInited;
}

// ------------------------------------------------------------------
CORETEMP_SERVICE::~CORETEMP_SERVICE()
{
	if(m_timer)
	{
		m_timer->stop();
		delete m_timer;
		m_timer = NULL;
	}
	if(m_isInited)
	{
		sensors_cleanup();
		m_isInited = false;
	}
}

// ------------------------------------------------------------------
void CORETEMP_SERVICE::onChangedMain(bool main)
{
	Q_UNUSED(main);
}

// ------------------------------------------------------------------
void CORETEMP_SERVICE::setConnectedGpr()
{
}

// ------------------------------------------------------------------
void CORETEMP_SERVICE::setDisconnectedGpr()
{
	clearOtherState();
}

// ------------------------------------------------------------------
void CORETEMP_SERVICE::startMonitor()
{
	m_isMonitored = true;
	syncToSlave();
}

// ------------------------------------------------------------------
void CORETEMP_SERVICE::stopMonitor()
{
	m_isMonitored = false;
	syncToSlave();
}

// ------------------------------------------------------------------
void CORETEMP_SERVICE::onRefreshCoreTemp()
{
	updateState();
	syncToSlave();
}

// ------------------------------------------------------------------
void CORETEMP_SERVICE::clearOtherState()
{
	bCoreStateOther.clear(ELEM_NOT);
	bCoreValuesOther.clear();
	emit sigStateOther(bCoreStateOther, bCoreValuesOther);
}

// ------------------------------------------------------------------
void CORETEMP_SERVICE::updateState()
{
	updateInfoCpuTemp();
	updateInfoMemory();
	updateInfoHdd();
	updateInfoSysLoad();

	LogCoreInfo("CORETEMP_SERVICE::updateState\n%s\n%s", qPrintable(bCoreValuesLocal.dump()), qPrintable(bCoreStateLocal.dump()));
	emit sigStateLocal(bCoreStateLocal, bCoreValuesLocal);
}

// ------------------------------------------------------------------
// libcoretemp
void CORETEMP_SERVICE::updateInfoCpuTemp()
{
	const sensors_chip_name *cn;
	int c = 0;

	while((cn = sensors_get_detected_chips(NULL, &c)) != NULL)
	{
		const sensors_feature *feat;
		int f = 0;

		while((feat = sensors_get_features(cn, &f)) != NULL)
		{
			QString label_name = QString(sensors_get_label(cn, feat));

			const sensors_subfeature *subf;
			int s = 0;

			while((subf = sensors_get_all_subfeatures(cn, feat, &s)) != NULL)
			{
				int type = int(subf->type);
				qreal val;

				if(subf->flags & SENSORS_MODE_R)
				{
					if(type == SENSORS_SUBFEATURE_TEMP_INPUT)
					{
						int rc = sensors_get_value(cn, subf->number, &val);
						if (rc < 0)
						{
							LogCoreError("CoreTemp: error get value \"%s\"", qPrintable(label_name));
							bCoreValuesLocal[label_name] = QVariant();
							bCoreStateLocal[label_name] = ELEM_NOT;
						}
						else
						{
							LogCoreInfo("CoreTemp: value[\"%s\"] = %6.2f", qPrintable(label_name), val);
							bCoreValuesLocal[label_name] = QVariant(val);
							bCoreStateLocal[label_name] = ELEM_NORMA;
						}
					}
				}
			}
		}
	}
}

// ------------------------------------------------------------------
// /proc/meminfo
void CORETEMP_SERVICE::updateInfoMemory()
{
	bool wasSet = false;

	QStringList meminfo_label_names = QStringList() << "MemTotal" << "MemFree" << "MemAvailable"  << "MemUsedPercent" << "SwapTotal" << "SwapFree" << "SwapFreePercent";
	QFile meminfo("/proc/meminfo");
	if(meminfo.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QString content = meminfo.readAll();
		meminfo.close();

		QStringList meminfoStrings = content.split('\n');
		for(QStringList::const_iterator it = meminfoStrings.constBegin(); it != meminfoStrings.constEnd(); ++it)
		{
			QString one_string = *it;
			QString label_name = one_string.split(':').first();

			if(meminfo_label_names.contains(label_name))
			{
				qulonglong value = 0;
				QRegExp regexp(":\\s+(\\d+)\\s+");

				int pos = regexp.indexIn(one_string);
				if(pos >= -1)
				{
					value = regexp.cap(1).toLongLong() / 1024;
					LogCoreInfo("CoreTemp: value[\"%s\"] = %d", qPrintable(label_name), value);
					bCoreValuesLocal[label_name] = QVariant(value);
					bCoreStateLocal[label_name] = ELEM_NORMA;
					wasSet = true;
				}
			}
		}

		if(wasSet)
		{
			QString label_name = "MemUsedPercent";
			if(bCoreStateLocal["MemTotal"] == ELEM_NORMA && bCoreStateLocal["MemAvailable"] == ELEM_NORMA)
			{
				double total = bCoreValuesLocal["MemTotal"].toDouble();
				if(total == 0)
				{
					LogCoreInfo("CoreTemp: value[\"%s\"] = NAN", qPrintable(label_name));
					bCoreValuesLocal[label_name] = QVariant();
					bCoreStateLocal[label_name] = ELEM_NORMA;
				}
				else
				{
					double value = 100.0 * bCoreValuesLocal["MemAvailable"].toDouble() / total;
					LogCoreInfo("CoreTemp: value[\"%s\"] = %d", qPrintable(label_name), value);
					bCoreValuesLocal[label_name] = QVariant(value);
					bCoreStateLocal[label_name] = ELEM_NORMA;
				}
			}
			else
			{
				bCoreValuesLocal[label_name] = QVariant();
				bCoreStateLocal[label_name] = ELEM_NOT;
			}

			label_name = "SwapFreePercent";
			if(bCoreStateLocal["SwapTotal"] == ELEM_NORMA && bCoreStateLocal["SwapFree"] == ELEM_NORMA)
			{
				double total = bCoreValuesLocal["SwapTotal"].toDouble();
				if(total == 0)
				{
					LogCoreInfo("CoreTemp: value[\"%s\"] = NAN", qPrintable(label_name));
					bCoreValuesLocal[label_name] = QVariant();
					bCoreStateLocal[label_name] = ELEM_NORMA;
				}
				else
				{
					double value =  100.0 * bCoreValuesLocal["SwapFree"].toDouble() / total;
					LogCoreInfo("CoreTemp: value[\"%s\"] = %d", qPrintable(label_name), value);
					bCoreValuesLocal[label_name] = QVariant(value);
					bCoreStateLocal[label_name] = ELEM_NORMA;
				}
			}
			else
			{
				bCoreValuesLocal[label_name] = QVariant();
				bCoreStateLocal[label_name] = ELEM_NOT;
			}
		}
	}

	for(QStringList::const_iterator i = meminfo_label_names.constBegin(); i != meminfo_label_names.constEnd(); ++i)
	{
		if(!wasSet)
		{
			bCoreValuesLocal[*i] = QVariant();
			bCoreStateLocal[*i] = ELEM_NOT;
		}
	}
}

// ------------------------------------------------------------------
// /proc/loadavg
void CORETEMP_SERVICE::updateInfoSysLoad()
{
	bool wasSet = false;
	double value_1 = 0, value_5 = 0, value_15 = 0;
	QString label_name_1 = QString("LoadAvg_1");
	QString label_name_5 = QString("LoadAvg_5");
	QString label_name_15 = QString("LoadAvg_15");

	QFile loadavg("/proc/loadavg");
	if(loadavg.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QString content = loadavg.readAll();
		loadavg.close();

		QRegExp regexp("^(\\d+.\\d*)\\s(\\d+.\\d*)\\s(\\d+.\\d*)\\s");

		int pos = regexp.indexIn(content);

		if(pos > -1)
		{
			value_1 = regexp.cap(1).replace('.',',').toDouble();
			value_5 = regexp.cap(2).replace('.',',').toDouble();
			value_15 = regexp.cap(3).replace('.',',').toDouble();
			wasSet = true;
		}
	}

	if(wasSet)
	{
		LogCoreInfo("CoreTemp: value[\"%s\"] = %7.3f", qPrintable(label_name_1), value_1);
		LogCoreInfo("CoreTemp: value[\"%s\"] = %7.3f", qPrintable(label_name_5), value_5);
		LogCoreInfo("CoreTemp: value[\"%s\"] = %7.3f", qPrintable(label_name_15), value_15);

		bCoreValuesLocal[label_name_1] = QVariant(value_1);
		bCoreValuesLocal[label_name_5] = QVariant(value_5);
		bCoreValuesLocal[label_name_15] = QVariant(value_15);

		bCoreStateLocal[label_name_1] = ELEM_NORMA;
		bCoreStateLocal[label_name_5] = ELEM_NORMA;
		bCoreStateLocal[label_name_15] = ELEM_NORMA;
	}
	else
	{
		bCoreValuesLocal[label_name_1] = QVariant();
		bCoreValuesLocal[label_name_5] = QVariant();
		bCoreValuesLocal[label_name_15] = QVariant();

		bCoreStateLocal[label_name_1] = ELEM_NOT;
		bCoreStateLocal[label_name_5] = ELEM_NOT;
		bCoreStateLocal[label_name_15] = ELEM_NOT;
	}
}

// ------------------------------------------------------------------
// /proc/cpuinfo
void CORETEMP_SERVICE::updateInfoCpu()
{
	bool wasSet = false;
	QString label_name = QString("cpu_name");
	QString cpu_name;

//	QStringList cpuinfo_label_names = QStringList() << QString("model name");
	QFile cpuinfo("/proc/cpuinfo");
	if(cpuinfo.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QString content = cpuinfo.readAll();
		cpuinfo.close();

		QStringList cpuinfoStrings = content.split('\n');
		for(QStringList::const_iterator it = cpuinfoStrings.constBegin(); it != cpuinfoStrings.constEnd(); ++it)
		{
			QStringList one_string_list = (*it).split(':');
			QString tag_name = one_string_list.first();

			if(tag_name.startsWith("model name"))
			{
				cpu_name = one_string_list.last().simplified();
				wasSet = true;
				break;
			}
		}
	}

	if(wasSet)
	{
		LogCoreInfo("CoreTemp: value[\"%s\"] = %s", qPrintable(label_name), qPrintable(cpu_name));
		bCoreValuesLocal[label_name] = QVariant(cpu_name);
		bCoreStateLocal[label_name] = ELEM_NORMA;
	}
	else
	{
		bCoreValuesLocal[label_name] = QVariant();
		bCoreStateLocal[label_name] = ELEM_NOT;
	}
}

// ------------------------------------------------------------------
// /etc/astra_version
void CORETEMP_SERVICE::updateInfoOs()
{
	bool wasSet = false;
	QString os_name;
	QString label_name = "version";

	QFile osinfo("/etc/astra_version");
	if(osinfo.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		os_name = osinfo.readAll().simplified();
		osinfo.close();

		if(!os_name.isEmpty())
			wasSet = true;
	}

	if(wasSet)
	{
		LogCoreInfo("CoreTemp: value[\"%s\"] = %s", qPrintable(label_name), qPrintable(os_name));
		bCoreValuesLocal[label_name] = QVariant(os_name);
		bCoreStateLocal[label_name] = ELEM_NORMA;
	}
	else
	{
		bCoreValuesLocal[label_name] = QVariant();
		bCoreStateLocal[label_name] = ELEM_NOT;
	}
}

// ------------------------------------------------------------------
// /proc/version_signature
void CORETEMP_SERVICE::updateInfoKernel()
{
	bool wasSet = false;
	QString kernel_name;
	QString label_name = "kernel";

	QFile kernelinfo("/proc/version_signature");
	if(kernelinfo.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		kernel_name = kernelinfo.readAll().simplified();
		kernelinfo.close();

		if(!kernel_name.isEmpty())
			wasSet = true;
	}

	if(wasSet)
	{
		LogCoreInfo("CoreTemp: value[\"%s\"] = %s", qPrintable(label_name), qPrintable(kernel_name));
		bCoreValuesLocal[label_name] = QVariant(kernel_name);
		bCoreStateLocal[label_name] = ELEM_NORMA;
	}
}

// ------------------------------------------------------------------
// df
void CORETEMP_SERVICE::updateInfoHdd()
{
	QString label_name = "HddTotal";
	bCoreValuesLocal[label_name] = QVariant();
	bCoreStateLocal[label_name] = ELEM_NOT;

	label_name = "HddAvailable";
	bCoreValuesLocal[label_name] = QVariant();
	bCoreStateLocal[label_name] = ELEM_NOT;

	label_name = "HddUsedPercent";
	bCoreValuesLocal[label_name] = QVariant();
	bCoreStateLocal[label_name] = ELEM_NOT;
}

// ------------------------------------------------------------------
void CORETEMP_SERVICE::syncToSlave()
{
	emit sigSyncToSlave(QVariantMap(), bCoreStateLocal.toMap(), bCoreValuesLocal.toMap());
}

// ------------------------------------------------------------------
void CORETEMP_SERVICE::onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure)
{
	Q_UNUSED(config);

	if(!state.isEmpty() && !measure.isEmpty())
	{
		bCoreStateOther.fromMap(state);
		bCoreValuesOther.fromMap(measure);

//		qDebug() << bCoreStateOther.dump();
//		qDebug() << bCoreValuesOther.dump();

		emit sigStateOther(bCoreStateOther, bCoreValuesOther);
	}
}

// ------------------------------------------------------------------
