#include "../common/logger.h"
#include "../common/xmlfile.h"
#include "../common/jsonfile.h"
#include "globalvar.h"
#include "dasd_tables.h"

//-----------------------------------------------------------------------------
DASD_TABLES::DASD_TABLES()
{
	m_temp_index = 7;
	m_temparature = 20.0;
	m_survey_index = 0;
	m_loaded_ripch = m_loaded_mode = m_loaded_switch = m_loaded_nchm = m_loaded_disable = m_loaded_dynamic = false;

	memset(&ripch_table, 0 , sizeof(ripch_table));
	memset(&mode_table, 0 , sizeof(mode_table));
	memset(&switch_table, 0 , sizeof(switch_table));
	memset(&nchm_table, 0 , sizeof(nchm_table));
	memset(&disable_table, 0 , sizeof(disable_table));
	memset(&dynamic_table, 0 , sizeof(disable_table));
}

//-----------------------------------------------------------------------------
void* DASD_TABLES::data_ripch()
{
	if(m_loaded_ripch)
		return (void*)&ripch_table;
	else
		return NULL;
}

//-----------------------------------------------------------------------------
void* DASD_TABLES::data_mode()
{
	if(m_loaded_mode)
		return (void*)&mode_table;
	else
		return NULL;
}

//-----------------------------------------------------------------------------
void* DASD_TABLES::data_switch()
{
	if(m_loaded_switch)
		return (void*)&switch_table;
	else
		return NULL;
}

//-----------------------------------------------------------------------------
void* DASD_TABLES::data_nchm()
{
	if(m_loaded_nchm)
		return (void*)&nchm_table;
	else
		return NULL;
}

//-----------------------------------------------------------------------------
QVariantMap DASD_TABLES::tableRipch()
{
	return ripchTableMap;
}

//-----------------------------------------------------------------------------
QVariantMap DASD_TABLES::tableMode()
{
	return modeTableMap;
}

//-----------------------------------------------------------------------------
QVariantMap DASD_TABLES::tableSwitch()
{
	return switchTableMap;
}

//-----------------------------------------------------------------------------
QVariantMap DASD_TABLES::tableDisable()
{
	return disableTableMap;
}

//-----------------------------------------------------------------------------
QVariantMap DASD_TABLES::tableDynamic()
{
	return dynamicTableMap;
}

//-----------------------------------------------------------------------------
void DASD_TABLES::setRipch(QVariantMap table)
{
	ripchTableMap = table;
}

//-----------------------------------------------------------------------------
void DASD_TABLES::setMode(QVariantMap table)
{
	modeTableMap = table;
}

//-----------------------------------------------------------------------------
void DASD_TABLES::setSwitch(QVariantMap table)
{
	switchTableMap = table;
}

//-----------------------------------------------------------------------------
void DASD_TABLES::setDisable(QVariantMap table)
{
	disableTableMap = table;
}

//-----------------------------------------------------------------------------
void DASD_TABLES::setDynamic(QVariantMap table)
{
	dynamicTableMap = table;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::setDynamic(AskuSektorTable data)
{
	QVariantMap table = AskuTableFile().makeDynamicTable(data);
	if(compareDynamicTable(table))
	{
		m_loaded_dynamic = true;
		dynamicTableMap = table;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::compareDynamicTable(QVariantMap table)
{
	QVariantList t1 = dynamicTableMap["segments"].toList();
	QVariantList t2 = table["segments"].toList();

	if(t1.count() != t2.count())
		return true;

	for(qint32 i = 0; i < t1.count(); i++)
	{
		QVariantMap line1 = t1[i].toMap();
		QVariantMap line2 = t2[i].toMap();

		if((line1["begin"].toUInt() != line2["begin"].toUInt()) || (line1["end"].toUInt() != line2["end"].toUInt()))
			return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::setTemperature(qreal t)
{
	if(m_temparature != t)
	{
		LogModuleInfo("DASD_TABLES::setTemperature: %3.1f", t);

		bool need_change = false;

		if(m_temparature == -100.0)
			need_change = true;
		else if(t <= -41.5 && m_temparature > -41.5)
			need_change = true;
		else if(t > -38.5 && m_temparature <= -38.5)
			need_change = true;
		else if(t <= -31.5 && m_temparature > -31.5)
			need_change = true;
		else if(t > -28.5 && m_temparature <= -28.5)
			need_change = true;
		else if(t <= -21.5 && m_temparature > -21.5)
			need_change = true;
		else if(t > -18.5 && m_temparature <= -18.5)
			need_change = true;
		else if(t <= -11.5 && m_temparature > -11.5)
			need_change = true;
		else if(t > -8.5 && m_temparature <= -8.5)
			need_change = true;
		else if(t <= -1.5 && m_temparature > -1.5)
			need_change = true;
		else if(t > 1.5 && m_temparature <= 1.5)
			need_change = true;
		else if(t <= 8.5 && m_temparature > 8.5)
			need_change = true;
		else if(t > 11.5 && m_temparature <= 11.5)
			need_change = true;
		else if(t <= 18.5 && m_temparature > 18.5)
			need_change = true;
		else if(t > 21.5 && m_temparature <= 21.5)
			need_change = true;
		else if(t <= 28.5 && m_temparature > 28.5)
			need_change = true;
		else if(t > 31.5 && m_temparature <= 31.5)
			need_change = true;
		else if(t <= 38.5 && m_temparature > 38.5)
			need_change = true;
		else if(t > 41.5 && m_temparature <= 41.5)
			need_change = true;

		m_temparature = t;

		if(need_change)
		{
			quint32 i;

			if(t <= -40.0)
				i = 0;
			else if(t <= -30.0)
				i = 1;
			else if(t <= -20.0)
				i = 2;
			else if(t <= -10.0)
				i = 3;
			else if(t <= 0.0)
				i = 4;
			else if(t <= 10.0)
				i = 5;
			else if(t <= 20.0)
				i = 6;
			else if(t <= 30.0)
				i = 7;
			else if(t <= 40.0)
				i = 8;
			else
				i = 9;

			m_temp_index = i;
		
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::setSurvey(quint32 n)
{
	LogModuleInfo("DASD_TABLES: setSurvey %d", n);

	if(n < SWITCH_TABLE_SURVEY_COUNT)
	{
		if(m_survey_index != n)
		{
			m_survey_index = n;
			return true;
		}
	}
	else
	{
		LogModuleError("DASD_TABLES: setSurvey invalid survey number (%d)", n);
	}
	return false;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::isLoaded()
{
	return m_loaded_ripch && m_loaded_mode && m_loaded_switch && m_loaded_nchm && m_loaded_disable && m_loaded_dynamic;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::isLoadedRipch()
{
	return m_loaded_ripch;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::isLoadedMode()
{
	return m_loaded_mode;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::isLoadedSwitch()
{
	return m_loaded_switch;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::isLoadedNchm()
{
	return m_loaded_nchm;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::isLoadedDisable()
{
	return m_loaded_disable;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::isLoadedDynamic()
{
	return m_loaded_dynamic;
}

//-----------------------------------------------------------------------------
qint32 DASD_TABLES::loadRipch(QString name)
{
	LogModuleInfo("loadRipch: %s", qPrintable(name));

	AskuTableFile ripchFile(name);
	if(ripchFile.wasError())
		return AskuTableFile::ErrorOpen;

	ripchTableMap = ripchFile.makeRipchTable();
	m_loaded_ripch = true;

	return AskuTableFile::NoError;
}

//-----------------------------------------------------------------------------
qint32 DASD_TABLES::loadMode(QString name)
{
	LogModuleInfo("loadMode: %s", qPrintable(name));

	AskuTableFile modeFile(name);
	if(modeFile.wasError())
		return AskuTableFile::ErrorOpen;

	modeTableMap = modeFile.makeModeTable();
	m_loaded_mode = true;

	return AskuTableFile::NoError;
}

//-----------------------------------------------------------------------------
qint32 DASD_TABLES::loadSwitch(QString name)
{
	LogModuleInfo("loadSwitch: %s", qPrintable(name));

	AskuTableFile switchFile(name);
	if(switchFile.wasError())
		return AskuTableFile::ErrorOpen;

	switchTableMap = switchFile.makeSwitchTable();
	m_loaded_switch = true;

	return AskuTableFile::NoError;
}

//-----------------------------------------------------------------------------
qint32 DASD_TABLES::loadNchm(QString name)
{
	LogModuleInfo("loadNchm: %s", qPrintable(name));

	QFile readfile(name);

	if(!readfile.exists())
		return AskuTableFile::ErrorOpen;

	if(readfile.open(QIODevice::ReadOnly))
	{
		qint64 result;
		bool goodfile = false;

		result = readfile.read((char*)&nchm_table,sizeof(NCHM_TABLE));

		if(result == sizeof(NCHM_TABLE))
			goodfile = true;

		readfile.close();

		if(!goodfile)
		{
			m_loaded_nchm = false;
			memset(&nchm_table, 0, sizeof(NCHM_TABLE));
			return AskuTableFile::ErrorData;
		}

		m_loaded_nchm = true;
		return AskuTableFile::NoError;
	}

	return AskuTableFile::ErrorOpen;
}

//-----------------------------------------------------------------------------
qint32 DASD_TABLES::loadDisable(QString name)
{
	LogModuleInfo("loadDisable: %s", qPrintable(name));

	AskuTableFile disableFile(name);
//	disableFile.loadFile(name);
	if(disableFile.wasError())
		return AskuTableFile::ErrorOpen;

	disableTableMap = disableFile.makeDisableTable();
	m_loaded_disable = true;

	return AskuTableFile::NoError;
}

//-----------------------------------------------------------------------------
qint32 DASD_TABLES::loadDynamic(QString name)
{
	LogModuleInfo("loadDynamic: %s", qPrintable(name));

	AskuTableFile dynamicFile;

	dynamicTableMap = dynamicFile.makeDynamicTable();
	m_loaded_dynamic = true;

	return AskuTableFile::NoError;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::prepareTables()
{
	return prepareRipch() && prepareMode() && prepareSwitch() && prepareDisable() && prepareDynamic() && combineDisableSwitchDynamic();
}

//-----------------------------------------------------------------------------
quint32 DASD_TABLES::mapToUInt(QString name, QVariantMap & headerMap, QVariant & dataList)
{
	QVariantMap map = headerMap[name].toMap();
//	qDebug() << map;

	quint32 index = map["index"].toUInt();
	quint32 min = map["min"].toUInt();
	quint32 max = map["max"].toUInt();
	quint32 mul = map["mul"].toUInt();
	quint32 off = map["off"].toUInt();
	quint32 value  = dataList.toStringList().at(index).toUInt();
//	qDebug("mapToUInt: val=%u min=%u max=%u mul=%u off=%u",value,min,max,mul,off);

	if(min != 0 || max != 0)
	{
		if(value < min)
		{
			qDebug("mapToUInt: \"%s\" value is lower minimum boundary", qPrintable(name));
			value = min;
		}
		if(value > max)
		{
			qDebug("mapToUInt: \"%s\" value is greater maximum boundary", qPrintable(name));
			value = max;
		}
	}

	if(off != 0)
		value += off;

	if(mul != 0)
		value *= mul;

	return value;
}

//-----------------------------------------------------------------------------
qint32 DASD_TABLES::mapToInt(QString name, QVariantMap & headerMap, QVariant & dataList)
{
	QVariantMap map = headerMap[name].toMap();
//	qDebug() << map;

	quint32 index = map["index"].toUInt();
	qint32 min = map["min"].toInt();
	qint32 max = map["max"].toInt();
	qint32 mul = map["mul"].toInt();
	qint32 off = map["off"].toInt();
	qint32 value  = dataList.toStringList().at(index).toInt();
//	qDebug("mapToInt: val=%d min=%d max=%d mul=%d off=%d",value,min,max,mul,off);

	if(min != 0 || max != 0)
	{
		if(value < min)
		{
			qDebug("mapToInt: \"%s\" value is lower minimum boundary", qPrintable(name));
			value = min;
		}
		if(value > max)
		{
			qDebug("mapToInt: \"%s\" value is greater maximum boundary", qPrintable(name));
			value = max;
		}
	}

	if(off != 0)
		value += off;

	if(mul != 0)
		value *= mul;

	return value;
}

//-----------------------------------------------------------------------------
quint32 DASD_TABLES::mapToBool(QString name, QVariantMap & headerMap, QVariant & dataList)
{
	QVariantMap map = headerMap[name].toMap();
//	qDebug() << map;

	quint32 index = map["index"].toUInt();
	qint32 value  = dataList.toStringList().at(index).toUInt();
//	qDebug("mapToBool: val=%d",value);

	if(value != 0 && value != 1)
	{
		qDebug("mapToBool: \"%s\" value is out of boundary", qPrintable(name));
		value = 1;
	}

	return value ? 1 : 0;
}

//-----------------------------------------------------------------------------
double DASD_TABLES::mapToDouble(QString name, QVariantMap & headerMap, QVariant & dataList)
{
	QVariantMap map = headerMap[name].toMap();
//	qDebug() << map;

	quint32 index = map["index"].toUInt();
	double min = map["min"].toDouble();
	double max = map["max"].toDouble();
	double mul = map["mul"].toDouble();
	double off = map["off"].toDouble();
	double value = dataList.toStringList().at(index).toDouble();
//	qDebug("mapToDouble: val=%f min=%f max=%f mul=%f off=%f",value,min,max,mul,off);

	if(min != 0 || max != 0)
	{
		if(value < min)
		{
			qDebug("mapToDouble: \"%s\" value is lower minimum boundary", qPrintable(name));
			value = min;
		}
		if(value > max)
		{
			qDebug("mapToDouble: \"%s\" value is greater maximum boundary", qPrintable(name));
			value = max;
		}
	}

	if(off != 0)
		value += off;

	if(mul != 0)
		value *= mul;

	return value;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::prepareRipch()
{
	if(!m_loaded_ripch)
		return false;

//	qDebug() << ripchTableMap;
	
	QVariantMap headerMap = ripchTableMap["header"].toMap();
	if(headerMap.isEmpty())
		return false;

//	qDebug() << headerMap;

	QStringList colNames;
	colNames << "freq_t0" << "freq_t1" << "freq_t2" << "freq_t3" << "freq_t4" << 
				"freq_t5" << "freq_t6" << "freq_t7" << "freq_t8" << "freq_t9" << 
				"length" << "sin" << "lchm" << "slope" << "nchm" << "delay" << "phase" << 
				"c_len1" << "c_del1" << "c_len2" << "c_del2" << "c_len3" << "c_del3" << "c_len4" << "c_del4" << 
				"c_len5" << "c_del5" << "c_len6" << "c_del6" << "c_len7" << "c_del7" << "c_len8" << "c_del8" << 
				"e_len1" << "e_del1" << "e_len2" << "e_del2" << "e_len3" << "e_del3" << "e_len4" << "e_del4";

	foreach(QString name, colNames)
		if(!headerMap.contains(name))
			return false;

	for(int i = 0; i < RIPCH_TABLE_IMPULSE_COUNT; i++)
	{
		QVariantList dataList = ripchTableMap["impulse_" + QString::number(i)].toList();
//		qDebug() << dataList;

		for(int j = 0; j < RIPCH_TABLE_SAMPLE_COUNT; j++)
		{
			RIPCH_IMPULSE_SAMPLE *sample = &(ripch_table.impulse[i].sample[j]);
			if(dataList.isEmpty() || j >= dataList.count())
			{
				sample->pch_code = 0;
				sample->length_code = 0;
				sample->is_sin = 0;
				sample->is_lchm = 0;
				sample->incline = 0;
				sample->is_nchm = 0;
				sample->lead_pause = 0;
				sample->step_lfm = 0;
				sample->start_phase = 0;
				sample->varu_delay = 0;

				for(int k = 0; k < RIPCH_TABLE_SAMPLE_CTRLS; k++)
				{
					sample->ctrl[k].length = 0;
					sample->ctrl[k].delay = 0;
				}
				for(int m = 0; m < RIPCH_TABLE_SAMPLE_COMMS; m++)
				{
					sample->common[m].length = 0;
					sample->common[m].delay = 0;
				}
			}
			else
			{
				sample->pch_code    = (unsigned int)mapToDouble("freq_t" + QString::number(m_temp_index), headerMap, dataList[j]);
				sample->length_code = (unsigned int)mapToDouble("length", headerMap, dataList[j]);
				sample->is_sin      = (unsigned int)mapToBool("sin", headerMap, dataList[j]);
				sample->is_lchm     = (unsigned int)mapToBool("lchm", headerMap, dataList[j]);
				sample->incline     = (unsigned int)mapToBool("slope", headerMap, dataList[j]);
				sample->is_nchm     = (unsigned int)mapToBool("nchm", headerMap, dataList[j]);
				sample->lead_pause  = (unsigned int)mapToDouble("delay", headerMap, dataList[j]);
				sample->step_lfm    = (unsigned int)mapToDouble("step_lfm", headerMap, dataList[j]);
				sample->start_phase = (unsigned int)mapToUInt("phase", headerMap, dataList[j]);
				sample->varu_delay      = (unsigned int)mapToDouble("varu_delay", headerMap, dataList[j]);

				for(int k = 0; k < RIPCH_TABLE_SAMPLE_CTRLS; k++)
				{
					sample->ctrl[k].length = (unsigned int)mapToDouble("c_len" + QString::number(k+1), headerMap, dataList[j]);
					sample->ctrl[k].delay  = (unsigned int)mapToDouble("c_del" + QString::number(k+1), headerMap, dataList[j]);
				}
				for(int m = 0; m < RIPCH_TABLE_SAMPLE_COMMS; m++)
				{
					sample->common[m].length = (unsigned int)mapToDouble("e_len" + QString::number(m+1), headerMap, dataList[j]);
					sample->common[m].delay  = (unsigned int)mapToDouble("e_del" + QString::number(m+1), headerMap, dataList[j]);
				}

//				qDebug("impulse=%d sample=%d %d %d", i, j, sample->pch_code, sample->length_code);
			}
//			qDebug("impulse=%d sample=%d %d %d", i, j, sample->pch_code, sample->length_code);
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::prepareMode()
{
	if(!m_loaded_mode)
		return false;

//	qDebug() << modeTableMap;
	
	QVariantMap headerMap = modeTableMap["header"].toMap();
	if(headerMap.isEmpty())
		return false;

//	qDebug() << headerMap;

	QStringList colNames;
	colNames << "i_code" << "period" << "max_varu";

	foreach(QString name, colNames)
		if(!headerMap.contains(name))
			return false;

	for(int i = 0; i < MODE_TABLE_RO_COUNT; i++)
	{
		QVariantList dataList = modeTableMap["mode_" + QString::number(i)].toList();
//		qDebug() << dataList;

		for(int j = 0; j < MODE_TABLE_IMPULSE_COUNT; j++)
		{
			MODE_TABLE_IMPULSE *imp = &(mode_table.ro[i].impulse[j]);
			if(dataList.isEmpty() || j >= dataList.count())
			{
				imp->period_code = 0;
				imp->zi_code = 0;
				imp->unused1 = 0;
				imp->max_varu = 0;
				imp->unused2 = 0;
			}
			else
			{
				imp->zi_code = mapToUInt("i_code", headerMap, dataList[j]);
				imp->period_code = mapToDouble("period", headerMap, dataList[j]);
				imp->unused1 = mapToUInt("unused1", headerMap, dataList[j]);
				imp->max_varu = mapToUInt("max_varu", headerMap, dataList[j]);
				imp->unused2 = mapToUInt("unused2", headerMap, dataList[j]);
//				qDebug("mode=%d impulse=%d %d %d", i, j, imp->zi_code, imp->period_code);
			}
//			qDebug("mode=%d impulse=%d %d %d", i, j, imp->zi_code, imp->period_code);
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::prepareSwitch()
{
	if(!m_loaded_switch)
		return false;

//	qDebug() << switchTableMap;
	
	QVariantMap headerMap = switchTableMap["header"].toMap();
	if(headerMap.isEmpty())
	{
		LogModuleError("DASD_TABLES: prepareSwitch empty header");
		return false;
	}

//	qDebug() << headerMap;

	QStringList colNames;
	colNames << "begin" << "end" << "mode" << "nchm";

	foreach(QString name, colNames)
		if(!headerMap.contains(name))
		{
			LogModuleError("DASD_TABLES: prepareSwitch invalid header");
			return false;
		}

	quint32 survey_index = m_survey_index;

	for(int i = 0; i < SWITCH_TABLE_SURVEY_COUNT; i++)
	{
//		qDebug("DASD_TABLES: survey index = %d", survey_index);

		if(survey_index >= SWITCH_TABLE_SURVEY_COUNT)
			survey_index = 0;

		QVariantList dataList = switchTableMap["survey_" + QString::number(/*i*/survey_index)].toList();
//		qDebug() << dataList;

		survey_index++;

		for(int j = 0; j < SWITCH_TABLE_SEGMENT_COUNT; j++)
		{
			SWITCH_TABLE_SEGMENT *seg = &(switch_table.survey[i].segment[j]);
			seg->mode_code = 0;
			seg->reserved1 = 0;
			seg->nchm_code = 0;
			seg->reserved2 = 0;
		}

		bool overlap = false;
		QByteArray c_array(SWITCH_TABLE_SEGMENT_COUNT,0);

		foreach(QVariant data, dataList)
		{
			quint32 s_begin = mapToUInt("begin", headerMap, data);
			quint32 s_end   = mapToUInt("end",   headerMap, data);
			quint32 mode_code = mapToUInt("mode", headerMap, data);
			quint32 nchm_code = mapToUInt("nchm", headerMap, data);

			if(s_begin >= SWITCH_TABLE_SEGMENT_COUNT)
				s_begin = SWITCH_TABLE_SEGMENT_COUNT - 1;

			if(s_end >= SWITCH_TABLE_SEGMENT_COUNT)
				s_end = SWITCH_TABLE_SEGMENT_COUNT - 1;

			if(s_begin <= s_end)
			{
				for(unsigned int j = s_begin; j <= s_end; j++)
				{
					if(c_array[j])
						overlap = 1;

					c_array[j] = c_array[j] + 1;

					SWITCH_TABLE_SEGMENT *seg = &(switch_table.survey[i].segment[j]);
					seg->mode_code = mode_code;
					seg->nchm_code = nchm_code;
				}
			}
			else
			{
				for(unsigned int j = s_begin; j <= (SWITCH_TABLE_SEGMENT_COUNT-1); j++)
				{
					if(c_array[j])
						overlap = 1;

					c_array[j] = c_array[j] + 1;

					SWITCH_TABLE_SEGMENT *seg = &(switch_table.survey[i].segment[j]);
					seg->mode_code = mode_code;
					seg->nchm_code = nchm_code;
				}
				for(unsigned int j = 0; j <= s_end; j++)
				{
					if(c_array[j])
						overlap = 1;

					c_array[j] = c_array[j] + 1;

					SWITCH_TABLE_SEGMENT *seg = &(switch_table.survey[i].segment[j]);
					seg->mode_code = mode_code;
					seg->nchm_code = nchm_code;
				}
			}
		}
/*
		QString deb = QString("Survey %1 Sektors:\n").arg(i);
		for(quint32 x = 0; x < SWITCH_TABLE_SEGMENT_COUNT; x++)
			deb += QString::number(c_array[x]);
		qDebug("%s",qPrintable(deb));
*/
		if(overlap)
			LogModuleInfo("Warning: switch table has overlapped sektors");
	}

	return true;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::combineDisableSwitchDynamic()
{
	if(!m_loaded_switch && !m_loaded_disable && !m_loaded_dynamic)
		return false;

	for(int i = 0; i < SWITCH_TABLE_SURVEY_COUNT; i++)
	{
		for(int j = 0; j < SWITCH_TABLE_SEGMENT_COUNT; j++)
		{
			SWITCH_TABLE_SEGMENT *seg_sw = &(switch_table.survey[i].segment[j]);
			DISABLE_TABLE_SEGMENT *seg_ds = &(disable_table.segment[j]);
			DISABLE_TABLE_SEGMENT *seg_dy = &(dynamic_table.segment[j]);
			seg_sw->disable = seg_ds->disable || seg_dy->disable;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::prepareDisable()
{
	if(!m_loaded_disable)
		return false;

//	qDebug() << disableTableMap;
	
	QVariantMap headerMap = disableTableMap["header"].toMap();
	if(headerMap.isEmpty())
		return false;

//	qDebug() << headerMap;

	QStringList colNames;
	colNames << "begin" << "end";

	foreach(QString name, colNames)
		if(!headerMap.contains(name))
			return false;

	QVariantList dataList = disableTableMap["segments"].toList();
//	qDebug() << dataList;

	for(int j = 0; j < DISABLE_TABLE_SEGMENT_COUNT; j++)
	{
		DISABLE_TABLE_SEGMENT *seg = &(disable_table.segment[j]);
		seg->disable = 0;
	}

	bool overlap = false;
	QByteArray c_array(DISABLE_TABLE_SEGMENT_COUNT,0);

	foreach(QVariant data, dataList)
	{
//		qDebug() << data;

		quint32 s_begin   = mapToUInt("begin", headerMap, data);
		quint32 s_end     = mapToUInt("end",   headerMap, data);

		if(s_begin >= DISABLE_TABLE_SEGMENT_COUNT)
			s_begin = DISABLE_TABLE_SEGMENT_COUNT - 1;

		if(s_end >= DISABLE_TABLE_SEGMENT_COUNT)
			s_end = DISABLE_TABLE_SEGMENT_COUNT - 1;

		if(s_begin <= s_end)
		{
			for(unsigned int j = s_begin; j <= s_end; j++)
			{
				if(c_array[j])
					overlap = 1;

				c_array[j] = c_array[j] + 1;

				DISABLE_TABLE_SEGMENT *seg = &(disable_table.segment[j]);
				seg->disable = 1;
			}
		}
		else
		{
			for(unsigned int j = s_begin; j <= (DISABLE_TABLE_SEGMENT_COUNT-1); j++)
			{
				if(c_array[j])
					overlap = 1;

				c_array[j] = c_array[j] + 1;

				DISABLE_TABLE_SEGMENT *seg = &(disable_table.segment[j]);
				seg->disable = 1;
			}
			for(unsigned int j = 0; j <= s_end; j++)
			{
				if(c_array[j])
					overlap = 1;

				c_array[j] = c_array[j] + 1;

				DISABLE_TABLE_SEGMENT *seg = &(disable_table.segment[j]);
				seg->disable = 1;
			}
		}
	}

	QString deb = QString("Disabled Sektors:\n");
	for(quint32 x = 0; x < DISABLE_TABLE_SEGMENT_COUNT; x++)
		deb += QString::number(c_array[x]);
	LogModuleBinary("DASD_TABLES: %s", qPrintable(deb));

	if(overlap)
		LogModuleInfo("Warning: disable table has overlapped sektors");

	return true;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::prepareDynamic()
{
	if(!m_loaded_dynamic)
		return false;

//	qDebug() << dynamicTableMap;
	
	QVariantMap headerMap = dynamicTableMap["header"].toMap();
	if(headerMap.isEmpty())
		return false;

//	qDebug() << headerMap;

	QStringList colNames;
	colNames << "begin" << "end";

	foreach(QString name, colNames)
		if(!headerMap.contains(name))
			return false;

	QVariantList dataList = dynamicTableMap["segments"].toList();
//	qDebug() << dataList;

	for(int j = 0; j < DISABLE_TABLE_SEGMENT_COUNT; j++)
	{
		DISABLE_TABLE_SEGMENT *seg = &(dynamic_table.segment[j]);
		seg->disable = 0;
	}

	bool overlap = false;
	QByteArray c_array(DISABLE_TABLE_SEGMENT_COUNT,0);

	foreach(QVariant data, dataList)
	{
//		qDebug() << data;

		quint32 s_begin   = mapToUInt("begin", headerMap, data);
		quint32 s_end     = mapToUInt("end",   headerMap, data);

//		qDebug() << s_begin << s_end;

		if(s_begin >= DISABLE_TABLE_SEGMENT_COUNT)
			s_begin = DISABLE_TABLE_SEGMENT_COUNT - 1;

		if(s_end >= DISABLE_TABLE_SEGMENT_COUNT)
			s_end = DISABLE_TABLE_SEGMENT_COUNT - 1;

		if(s_begin <= s_end)
		{
			for(unsigned int j = s_begin; j <= s_end; j++)
			{
				if(c_array[j])
					overlap = 1;

				c_array[j] = c_array[j] + 1;

				DISABLE_TABLE_SEGMENT *seg = &(dynamic_table.segment[j]);
				seg->disable = 1;
			}
		}
		else
		{
			for(unsigned int j = s_begin; j <= (DISABLE_TABLE_SEGMENT_COUNT-1); j++)
			{
				if(c_array[j])
					overlap = 1;

				c_array[j] = c_array[j] + 1;

				DISABLE_TABLE_SEGMENT *seg = &(dynamic_table.segment[j]);
				seg->disable = 1;
			}
			for(unsigned int j = 0; j <= s_end; j++)
			{
				if(c_array[j])
					overlap = 1;

				c_array[j] = c_array[j] + 1;

				DISABLE_TABLE_SEGMENT *seg = &(dynamic_table.segment[j]);
				seg->disable = 1;
			}
		}
	}

	QString deb = QString("Dynamic Disable Sektors:\n");
	for(quint32 x = 0; x < DISABLE_TABLE_SEGMENT_COUNT; x++)
		deb += QString::number(c_array[x]);
	LogModuleBinary("DASD_TABLES: %s", qPrintable(deb));

	if(overlap)
		LogModuleInfo("DASD_TABLES: dynamic table has overlapped sektors");

	return true;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::saveRipch(QString name)
{
//	JsonFile file(ripchTableMap, name+".json");
//	return file.save();
	AskuTableFile ripchFile;
	return ripchFile.saveXmlRipchTable(name, ripchTableMap);
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::saveMode(QString name)
{
//	JsonFile file(modeTableMap, name+".json");
//	return file.save();
	AskuTableFile modeFile;
	return modeFile.saveXmlModeTable(name, modeTableMap);
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::saveSwitch(QString name)
{
//	JsonFile file(switchTableMap, name+".json");
//	return file.save();
	AskuTableFile switchFile;
	return switchFile.saveXmlSwitchTable(name, switchTableMap);
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::saveNchm(QString name)
{
	Q_UNUSED(name);
	return false;
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::saveDisable(QString name)
{
//	JsonFile file(disableTableMap, name+".json");
//	return file.save();
	AskuTableFile disableFile;
	return disableFile.saveXmlDisableTable(name, disableTableMap);
}

//-----------------------------------------------------------------------------
bool DASD_TABLES::saveDynamic(QString name)
{
	Q_UNUSED(name);
	return false;
}

//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
AskuTableFile::AskuTableFile(QString filename) : XmlFile()
{
	if(!filename.isEmpty())
		loadFile(filename);
}

//----------------------------------------------------------------------------------------------------------------
bool AskuTableFile::loadFile(QString filename)
{
	LogModuleInfo("Loading file: %s", qPrintable(filename));

	bool result = load(filename);
	if(wasError())
		LogModuleError("Error loading file: %s", qPrintable(lastErrorMessage()));

	return result;
}

//----------------------------------------------------------------------------------------------------------------
bool AskuTableFile::saveFile(QString filename)
{
//	filename += ".test";

	LogModuleInfo("Saving file: %s", qPrintable(filename));

	bool result = save(filename);
	if(wasError())
		LogModuleError("Error saving file: %s", qPrintable(lastErrorMessage()));

	return result;
}

//----------------------------------------------------------------------------------------------------------------
bool AskuTableFile::checkContent()
{
	if((doctype().name().left(5) != "DASD_" && doctype().name().left(8) != "D2VK028_") || doctype().name().right(6) != "_table")
	{
		LogModuleError("AskuTableFile: not a DASD_*_table");
		return false;
	}

	if(documentElement().tagName() != "table")
	{
		LogModuleError("AskuTableFile: no table tag");
		return false;
	}

	return true;
}

//----------------------------------------------------------------------------------------------------------------
bool AskuTableFile::saveXmlSwitchTable(QString name, QVariantMap table)
{
	clear();
	setContent(makeDomSwitchTable(table).toString());
	return saveFile(name);
}

//----------------------------------------------------------------------------------------------------------------
bool AskuTableFile::saveXmlRipchTable(QString name, QVariantMap table)
{
	clear();
	setContent(makeDomRipchTable(table).toString());
	return saveFile(name);
}

//----------------------------------------------------------------------------------------------------------------
bool AskuTableFile::saveXmlDisableTable(QString name, QVariantMap table)
{
	clear();
	setContent(makeDomDisableTable(table).toString());
	return saveFile(name);
}

//----------------------------------------------------------------------------------------------------------------
bool AskuTableFile::saveXmlModeTable(QString name, QVariantMap table)
{
	clear();
	setContent(makeDomModeTable(table).toString());
	return saveFile(name);
}

//----------------------------------------------------------------------------------------------------------------
QDomDocument AskuTableFile::makeDomSwitchTable(QVariantMap data)
{
	QDomDocument doc = makeDomDocument("DASD_switch_table");
	QDomElement tableElement = makeDomTableSwitch(doc, data);
	doc.appendChild(tableElement);
	return doc; 
}

//----------------------------------------------------------------------------------------------------------------
QDomDocument AskuTableFile::makeDomRipchTable(QVariantMap data)
{
	QDomDocument doc = makeDomDocument("DASD_ripch_table");
	QDomElement tableElement = makeDomTableRipch(doc, data);
	doc.appendChild(tableElement);
	return doc; 
}

//----------------------------------------------------------------------------------------------------------------
QDomDocument AskuTableFile::makeDomDisableTable(QVariantMap data)
{
	QDomDocument doc = makeDomDocument("DASD_disable_table");
	QDomElement tableElement = makeDomTableDisable(doc, data);
	doc.appendChild(tableElement);
	return doc; 
}

//----------------------------------------------------------------------------------------------------------------
QDomDocument AskuTableFile::makeDomModeTable(QVariantMap data)
{
	QDomDocument doc = makeDomDocument("DASD_mode_table");
	QDomElement tableElement = makeDomTableMode(doc, data);
	doc.appendChild(tableElement);
	return doc; 
}

//----------------------------------------------------------------------------------------------------------------
QDomElement AskuTableFile::makeDomTableMode(QDomDocument & doc, QVariantMap data)
{
	QDomElement tableElement = doc.createElement("table");
	tableElement.setAttribute("name","mode_table");

	QDomElement headerElement = makeDomHeader(doc, data["header"].toMap());
	tableElement.appendChild(headerElement);

	for(qint32 i = 0; i < data.count(); i++)
	{
		QString mode = QString("mode_%1").arg(i);
		if(data.contains(mode))
		{
			QVariantList list = data[mode].toList();

			if(!list.isEmpty())
			{
				QDomElement modeElement = doc.createElement("mode");
				modeElement.setAttribute("code", QString::number(i));

				foreach(QVariant itemlist, list)
				{
					QDomElement impulseElement = doc.createElement("impulse");
					QString modeString = itemlist.toStringList().join("\t");
					QDomText textNode = doc.createTextNode(modeString);
					impulseElement.appendChild(textNode);
					modeElement.appendChild(impulseElement);
				}

				tableElement.appendChild(modeElement);
			}
		}
	}

	return tableElement;
}

//----------------------------------------------------------------------------------------------------------------
QDomElement AskuTableFile::makeDomTableSwitch(QDomDocument & doc, QVariantMap data)
{
	QDomElement tableElement = doc.createElement("table");
	tableElement.setAttribute("name","switch_table");

	QDomElement headerElement = makeDomHeader(doc, data["header"].toMap());
	tableElement.appendChild(headerElement);

	for(qint32 i = 0; i < data.count(); i++)
	{
		QString mode = QString("survey_%1").arg(i);
		if(data.contains(mode))
		{
			QVariantList list = data[mode].toList();

			if(!list.isEmpty())
			{
				QDomElement modeElement = doc.createElement("survey");
				modeElement.setAttribute("code", QString::number(i));

				foreach(QVariant itemlist, list)
				{
					QDomElement impulseElement = doc.createElement("segment");
					QString modeString = itemlist.toStringList().join("\t");
					QDomText textNode = doc.createTextNode(modeString);
					impulseElement.appendChild(textNode);
					modeElement.appendChild(impulseElement);
				}

				tableElement.appendChild(modeElement);
			}
		}
	}

	return tableElement;
}

//----------------------------------------------------------------------------------------------------------------
QDomElement AskuTableFile::makeDomTableRipch(QDomDocument & doc, QVariantMap data)
{
	QDomElement tableElement = doc.createElement("table");
	tableElement.setAttribute("name","ripch_table");

	QDomElement headerElement = makeDomHeader(doc, data["header"].toMap());
	tableElement.appendChild(headerElement);

	for(qint32 i = 0; i < data.count(); i++)
	{
		QString mode = QString("impulse_%1").arg(i);
		if(data.contains(mode))
		{
			QVariantList list = data[mode].toList();

			if(!list.isEmpty())
			{
				QDomElement modeElement = doc.createElement("impulse");
				modeElement.setAttribute("code", QString::number(i));

				foreach(QVariant itemlist, list)
				{
					QDomElement impulseElement = doc.createElement("sample");
					QString modeString = itemlist.toStringList().join("\t");
					QDomText textNode = doc.createTextNode(modeString);
					impulseElement.appendChild(textNode);
					modeElement.appendChild(impulseElement);
				}

				tableElement.appendChild(modeElement);
			}
		}
	}

	return tableElement;
}

//----------------------------------------------------------------------------------------------------------------
QDomElement AskuTableFile::makeDomTableDisable(QDomDocument & doc, QVariantMap data)
{
	QDomElement tableElement = doc.createElement("table");
	tableElement.setAttribute("name","disable_table");

	QDomElement headerElement = makeDomHeader(doc, data["header"].toMap());
	tableElement.appendChild(headerElement);

	QVariantList segments = data["segments"].toList();

	foreach(QVariant segment, segments)
	{
//		QVariantList list = segment.toList();
		QDomElement impulseElement = doc.createElement("segment");
		QString modeString = segment.toStringList().join("\t");
		QDomText textNode = doc.createTextNode(modeString);
		impulseElement.appendChild(textNode);

		tableElement.appendChild(impulseElement);
	}

	return tableElement;
}

//----------------------------------------------------------------------------------------------------------------
QDomDocument AskuTableFile::makeDomDocument(QString strType)
{
	QDomDocumentType docType = implementation().createDocumentType(strType, QString(), QString());
	QDomDocument doc = implementation().createDocument(QString(), strType, docType);
	doc.removeChild(doc.firstChild());

	QDomProcessingInstruction process = createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
	doc.appendChild(process);

	return doc;
}

//----------------------------------------------------------------------------------------------------------------
QDomElement AskuTableFile::makeDomHeader(QDomDocument & doc, QVariantMap header)
{
	QDomElement headerElement = doc.createElement("header");

	for(qint32 i = 0; i < header.count(); i++)
	{
		QVariantMap headerItem;

		foreach(QString hkey, header.keys())
		{
			headerItem = header[hkey].toMap();
			if(headerItem["index"].toInt() == i)
				break;
		}

		QDomElement columnElement = doc.createElement("column");

		foreach(QString attrkey, headerItem.keys())
		{
			QString value = headerItem[attrkey].toString();
			if(!value.isEmpty())
				columnElement.setAttribute(attrkey, value);
		}

		headerElement.appendChild(columnElement);
	}

	return headerElement;
}

//----------------------------------------------------------------------------------------------------------------
QVariantMap AskuTableFile::makeModeTable()
{
	QVariantMap result;

	if(wasError())
		return QVariantMap();

	QDomElement tag_table = documentElement();
	if(!tag_table.isNull() && tag_table.nodeName() == "table")
	{
		result["header"] = makeHeader(tag_table);

		for(QDomElement tag_mode = tag_table.firstChildElement("mode"); !tag_mode.isNull(); tag_mode = tag_mode.nextSiblingElement("mode"))
		{
			QVariantList dataList;

			QString a_code = tag_mode.attribute("code", "");

			for(QDomElement tag_impulse = tag_mode.firstChildElement("impulse"); !tag_impulse.isNull(); tag_impulse = tag_impulse.nextSiblingElement("impulse"))
			{
				QString a_impulse = textFromElement(tag_impulse," ");
				QStringList a_list = a_impulse.split("\t", QString::SkipEmptyParts);
				dataList << a_list;
			}

			result["mode_" + a_code] = dataList;
		}
	}

	return result;
}

//----------------------------------------------------------------------------------------------------------------
QVariantMap AskuTableFile::makeSwitchTable()
{
	QVariantMap result;

	if(wasError())
		return QVariantMap();

	QDomElement tag_table = documentElement();
	if(!tag_table.isNull() && tag_table.nodeName() == "table")
	{
		result["header"] = makeHeader(tag_table);

		for(QDomElement tag_survey = tag_table.firstChildElement("survey"); !tag_survey.isNull(); tag_survey = tag_survey.nextSiblingElement("survey"))
		{
			QVariantList dataList;

			QString a_code = tag_survey.attribute("code", "");

			for(QDomElement tag_segment = tag_survey.firstChildElement("segment"); !tag_segment.isNull(); tag_segment = tag_segment.nextSiblingElement("segment"))
			{
				QString a_impulse = textFromElement(tag_segment," ");
				QStringList a_list = a_impulse.split("\t", QString::SkipEmptyParts);
				dataList << a_list;
			}

			result["survey_" + a_code] = dataList;
		}
	}

	return result;
}

//----------------------------------------------------------------------------------------------------------------
QVariantMap AskuTableFile::makeRipchTable()
{
	QVariantMap result;

	if(wasError())
		return QVariantMap();

	QDomElement tag_table = documentElement();
	if(!tag_table.isNull() && tag_table.nodeName() == "table")
	{
		result["header"] = makeHeader(tag_table);

		for(QDomElement tag_impulse = tag_table.firstChildElement("impulse"); !tag_impulse.isNull(); tag_impulse = tag_impulse.nextSiblingElement("impulse"))
		{
			QVariantList dataList;

			QString a_code = tag_impulse.attribute("code", "");

			for(QDomElement tag_sample = tag_impulse.firstChildElement("sample"); !tag_sample.isNull(); tag_sample = tag_sample.nextSiblingElement("sample"))
			{
				QString a_impulse = textFromElement(tag_sample," ");
				QStringList a_list = a_impulse.split("\t", QString::SkipEmptyParts);
				dataList << a_list;
			}

			result["impulse_" + a_code] = dataList;
		}
	}

	return result;
}

//----------------------------------------------------------------------------------------------------------------
QVariantMap AskuTableFile::makeDisableTable()
{
	QVariantMap result;

	if(wasError())
		return QVariantMap();

	QDomElement tag_table = documentElement();
	if(!tag_table.isNull() && tag_table.nodeName() == "table")
	{
		result["header"] = makeHeader(tag_table);

		QVariantList dataList;
		for(QDomElement tag_segment = tag_table.firstChildElement("segment"); !tag_segment.isNull(); tag_segment = tag_segment.nextSiblingElement("segment"))
		{
			QString a_segment = textFromElement(tag_segment," ");
			QStringList a_list = a_segment.split("\t", QString::SkipEmptyParts);
			dataList << a_list;
		}

		result["segments"] = dataList;
	}

	return result;
}

//----------------------------------------------------------------------------------------------------------------
QVariantMap AskuTableFile::makeDynamicTable(AskuSektorTable data)
{
	QVariantMap result;
	QVariantMap header;

	QVariantMap column;
	column["index"] = 0;
	column["name"] = "begin";
	column["title"] = "Сектор начала";
	column["min"] = "0";
	column["max"] = "255";
	column["units"] = "№";
	column["mul"] = "";
	column["off"] = "";
	header["begin"] = column;

	column["index"] = 1;
	column["name"] = "end";
	column["title"] = "Сектор конца";
	header["end"] = column;

	result["header"] = header;

	QVariantList dataList;

	if(!data.isEmpty())
	{
		for(qint32 i = 0; i < data.count(); i++)
		{
			QVariantMap line = data[i].toMap();
			double begin = line["begin"].toDouble();
			double end   = line["end"].toDouble();
			double c = 360.0 / (double)(DISABLE_TABLE_SEGMENT_COUNT);
			quint32 out_begin = 0;
			quint32 out_end = 0;
//			double c_begin;
//			double c_end;

			if(begin < 0.0) begin = 0.0;
			if(begin > 360.0) begin = 360.0;
			if(end < 0.0) end = 0.0;
			if(end > 360.0) end = 360.0;

			if(begin == end)
			{
//			qDebug() << "begin == end";
				out_begin = 0;
				out_end   = DISABLE_TABLE_SEGMENT_COUNT - 1;

				dataList << (QStringList() << QString("%1").arg(out_begin) << QString("%1").arg(out_end));

//				c_begin = 360.0 * (double)lineout["begin"].toUInt() / (double)DISABLE_TABLE_SEGMENT_COUNT;
//				c_end   = 360.0 * (double)(lineout["end"].toUInt()+1) / (double)DISABLE_TABLE_SEGMENT_COUNT;
//				qDebug() << QString("  %1(%2-%3) - %4(%5-%6)").arg(lineout["begin"].toUInt(), 3).arg(begin, 7, 'f', 3).arg(c_begin, 7, 'f', 3).arg(lineout["end"].toUInt(), 3).arg(end, 7, 'f', 3).arg(c_end, 7, 'f', 3);
			}
			else if(begin > end)
			{
//			qDebug() << "begin > end (1)";
				for(quint32 s = 0; s < DISABLE_TABLE_SEGMENT_COUNT; s++)
				{
					double b = c * (s+0);
					double e = c * (s+1);
//			bool aa = false, bb = false;

					if(b <= begin && e >= begin)	// begin at this sektor
					{
						out_begin = s;
						out_end   = DISABLE_TABLE_SEGMENT_COUNT - 1;
//						aa = bb = true;
					}
//			qDebug() << QString("%1").arg(s,3) << QString("%1").arg(begin,7,'f',3) << QString("%1").arg(end,7,'f',3) << QString("%1").arg(b,7,'f',3) << QString("%1").arg(e,7,'f',3) << aa << bb;
				}

				dataList << (QStringList() << QString("%1").arg(out_begin) << QString("%1").arg(out_end));

//				c_begin = 360.0 * (double)lineout["begin"].toUInt() / (double)DISABLE_TABLE_SEGMENT_COUNT;
//				c_end   = 360.0 * (double)(lineout["end"].toUInt()+1) / (double)DISABLE_TABLE_SEGMENT_COUNT;
//				qDebug() << QString("  %1(%2-%3) - %4(%5-%6)").arg(lineout["begin"].toUInt(), 3).arg(begin, 7, 'f', 3).arg(c_begin, 7, 'f', 3).arg(lineout["end"].toUInt(), 3).arg(end, 7, 'f', 3).arg(c_end, 7, 'f', 3);

				if(end > 0.0)
				{
//			qDebug() << "begin > end (2)";
					for(quint32 s = 0; s < DISABLE_TABLE_SEGMENT_COUNT; s++)
					{
						double b = c * (s+0);
						double e = c * (s+1);
//			bool aa = false, bb = false;

						if(b <= end && e >= end)		//end at this sektor
						{
							out_begin = 0;
							out_end   = s;
//							aa = bb = true;
							break;
						}
//			qDebug() << QString("%1").arg(s,3) << QString("%1").arg(begin,7,'f',3) << QString("%1").arg(end,7,'f',3) << QString("%1").arg(b,7,'f',3) << QString("%1").arg(e,7,'f',3) << aa << bb;
					}

					dataList << (QStringList() << QString("%1").arg(out_begin) << QString("%1").arg(out_end));

//					c_begin = 360.0 * (double)lineout["begin"].toUInt() / (double)DISABLE_TABLE_SEGMENT_COUNT;
//					c_end   = 360.0 * (double)(lineout["end"].toUInt()+1) / (double)DISABLE_TABLE_SEGMENT_COUNT;
//					qDebug() << QString("  %1(%2-%3) - %4(%5-%6)").arg(lineout["begin"].toUInt(), 3).arg(begin, 7, 'f', 3).arg(c_begin, 7, 'f', 3).arg(lineout["end"].toUInt(), 3).arg(end, 7, 'f', 3).arg(c_end, 7, 'f', 3);
				}
			}
			else
			{
//			qDebug() << "begin < end";
				for(quint32 s = 0; s < DISABLE_TABLE_SEGMENT_COUNT; s++)
				{
					double b = c * (s+0);
					double e = c * (s+1);
//			bool aa = false, bb = false;
					if(b <= begin && e >= begin)	// begin at this sektor
					{
						out_begin = s;
//						aa = true;
					}

					if(b <= end && e >= end)		//end at this sektor
					{
						out_end = s;
//						bb = true;
						break;
					}
//			qDebug() << QString("%1").arg(s,3) << QString("%1").arg(begin,7,'f',3) << QString("%1").arg(end,7,'f',3) << QString("%1").arg(b,7,'f',3) << QString("%1").arg(e,7,'f',3) << aa << bb;
				}

				dataList << (QStringList() << QString("%1").arg(out_begin) << QString("%1").arg(out_end));

//				c_begin = 360.0 * (double)lineout["begin"].toUInt() / (double)DISABLE_TABLE_SEGMENT_COUNT;
//				c_end   = 360.0 * (double)(lineout["end"].toUInt()+1) / (double)DISABLE_TABLE_SEGMENT_COUNT;
//				qDebug() << QString("  %1(%2-%3) - %4(%5-%6)").arg(lineout["begin"].toUInt(), 3).arg(begin, 7, 'f', 3).arg(c_begin, 7, 'f', 3).arg(lineout["end"].toUInt(), 3).arg(end, 7, 'f', 3).arg(c_end, 7, 'f', 3);
			}
		}
	}

	result["segments"] = dataList;
//	qDebug() << dataList;

	return result;
}

//----------------------------------------------------------------------------------------------------------------
QVariantMap AskuTableFile::makeHeader(QDomElement tag_table)
{
	QVariantMap columnMap;
	QDomElement tag_header = tag_table.firstChildElement("header");

	if(!tag_header.isNull())
	{
		quint32 index = 0;

		for(QDomElement tag_column = tag_header.firstChildElement("column"); !tag_column.isNull(); tag_column = tag_column.nextSiblingElement("column"))
		{
			QString a_name = tag_column.attribute("name", "");
			QString a_title = tag_column.attribute("title", "");
			QString a_min = tag_column.attribute("min", "");
			QString a_max = tag_column.attribute("max", "");
			QString a_units = tag_column.attribute("units", "");
			QString a_mul = tag_column.attribute("mul", "");
			QString a_off = tag_column.attribute("off", "");

			QVariantMap column;
			column["index"] = index++;
			column["name"] = a_name;
			column["title"] = a_title;
			column["min"] = a_min;
			column["max"] = a_max;
			column["units"] = a_units;
			column["mul"] = a_mul;
			column["off"] = a_off;

			columnMap[a_name] = column;
		}
	}

	return columnMap;
}

//----------------------------------------------------------------------------------------------------------------
