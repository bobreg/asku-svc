#include "../common/logger.h"
#include "globalvar.h"
#include "algorithm.h"
#include "canalasku_data.h"

// ----------------------------------------------------------------------------
void AskuAlgorithm::funSvkrCoreLocal()
{
//	qDebug() << "A: " << localCoreTemp.dump();
//	qDebug() << "B: " << valLocalCoreTemp.dump();

// Local
	QString NGPR = QString("cpu%1@").arg(IDGPR() + 1);

	localSvkr["cpu"] = localCoreTemp["cpu_temp"] = localCoreTemp["Physical id 0"];

	double cpu_temp = valLocalCoreTemp["Physical id 0"].toDouble();
	double loadavg_1 = valLocalCoreTemp["LoadAvg_1"].toDouble();
	double loadavg_5 = valLocalCoreTemp["LoadAvg_5"].toDouble();
	double loadavg_15 = valLocalCoreTemp["LoadAvg_15"].toDouble();
	quint32 mem_total = valLocalCoreTemp["MemTotal"].toUInt();
	quint32 mem_avail = valLocalCoreTemp["MemAvailable"].toUInt();
	double mem_used = valLocalCoreTemp["MemUsedPercent"].toDouble();
	quint32 swap_total = valLocalCoreTemp["SwapTotal"].toUInt();
	quint32 swap_free = valLocalCoreTemp["SwapFree"].toUInt();
	double swap_used = valLocalCoreTemp["SwapFreePercent"].toDouble();
	quint32 hdd_total = valLocalCoreTemp["HddTotal"].toUInt();
	quint32 hdd_avail = valLocalCoreTemp["HddAvailable"].toUInt();
	double hdd_used = valLocalCoreTemp["HddUsedPercent"].toDouble();

	elements[NGPR + "os_name"] = localCoreTemp["version"].toString();
	elements[NGPR + "os_name"].setText(valLocalCoreTemp["version"].toString());

	elements[NGPR + "os_kernel"] = localCoreTemp["kernel"].toString();
	elements[NGPR + "os_kernel"].setText(valLocalCoreTemp["kernel"].toString());

	elements[NGPR + "os_load"] = localCoreTemp["LoadAvg_1"].toString();
	elements[NGPR + "os_load"].setText(localCoreTemp["LoadAvg_1"] != ELEM_NOT ? QString("%1 %2 %3").arg(loadavg_1, 0, 'f', 3).arg(loadavg_5, 0, 'f', 3).arg(loadavg_15, 0, 'f', 3) : QString(""));

	elements[NGPR + "cpu_name"] = localCoreTemp["cpu_name"].toString();
	elements[NGPR + "cpu_name"].setText(valLocalCoreTemp["cpu_name"].toString());

	elements[NGPR + "cpu_temp"] = localCoreTemp["cpu_temp"].toString();
	elements[NGPR + "cpu_temp"].setText(localCoreTemp["cpu_temp"] != ELEM_NOT ? QString("%1").arg(cpu_temp, 0, 'f', 0) : QString(""));

	elements[NGPR + "mem_total"] = localCoreTemp["MemTotal"].toString();
	elements[NGPR + "mem_total"].setText(localCoreTemp["MemTotal"] != ELEM_NOT ? QString("%1").arg(mem_total) : QString(""));

	elements[NGPR + "mem_avail"] = localCoreTemp["MemUsedPercent"].toString();
	elements[NGPR + "mem_avail"].setText(localCoreTemp["MemUsedPercent"] != ELEM_NOT ? QString("%1 (%2%)").arg(mem_avail).arg(mem_used, 0, 'f', 1) : QString(""));

	elements[NGPR + "swap_total"] = localCoreTemp["SwapTotal"].toString();
	elements[NGPR + "swap_total"].setText(localCoreTemp["SwapTotal"] != ELEM_NOT ? QString("%1").arg(swap_total) : QString(""));

	elements[NGPR + "swap_avail"] = localCoreTemp["SwapFreePercent"].toString();
	elements[NGPR + "swap_avail"].setText(localCoreTemp["SwapFreePercent"] != ELEM_NOT ? QString("%1 (%2%)").arg(swap_free).arg(swap_used, 0, 'f', 1) : QString(""));

	elements[NGPR + "hdd_total"] = localCoreTemp["HddTotal"].toString();
	elements[NGPR + "hdd_total"].setText(localCoreTemp["HddTotal"] != ELEM_NOT ? QString("%1").arg(hdd_total) : QString(""));

	elements[NGPR + "hdd_avail"] = localCoreTemp["HddUsedPercent"].toString();
	elements[NGPR + "hdd_avail"].setText(localCoreTemp["HddUsedPercent"] != ELEM_NOT ? QString("%1 (%2%)").arg(hdd_avail).arg(hdd_used, 0, 'f', 1) : QString(""));
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funSvkrCoreOther()
{
//	qDebug() << "A: " << otherCoreTemp.dump();
//	qDebug() << "B: " << valOtherCoreTemp.dump();

// Other
	QString NGPR = QString("cpu%1@").arg(OTHER_GPR_ID() + 1);

	otherSvkr["cpu"] = otherCoreTemp["cpu_temp"] = otherCoreTemp["Physical id 0"];

	double cpu_temp = valOtherCoreTemp["Physical id 0"].toDouble();
	double loadavg_1 = valOtherCoreTemp["LoadAvg_1"].toDouble();
	double loadavg_5 = valOtherCoreTemp["LoadAvg_5"].toDouble();
	double loadavg_15 = valOtherCoreTemp["LoadAvg_15"].toDouble();
	quint32 mem_total = valOtherCoreTemp["MemTotal"].toUInt();
	quint32 mem_avail = valOtherCoreTemp["MemAvailable"].toUInt();
	double mem_used = valOtherCoreTemp["MemUsedPercent"].toDouble();
	quint32 swap_total = valOtherCoreTemp["SwapTotal"].toUInt();
	quint32 swap_free = valOtherCoreTemp["SwapFree"].toUInt();
	double swap_used = valOtherCoreTemp["SwapFreePercent"].toDouble();
	quint32 hdd_total = valOtherCoreTemp["HddTotal"].toUInt();
	quint32 hdd_avail = valOtherCoreTemp["HddAvailable"].toUInt();
	double hdd_used = valOtherCoreTemp["HddUsedPercent"].toDouble();

	elements[NGPR + "os_name"] = otherCoreTemp["version"].toString();
	elements[NGPR + "os_name"].setText(valOtherCoreTemp["version"].toString());

	elements[NGPR + "os_kernel"] = otherCoreTemp["kernel"].toString();
	elements[NGPR + "os_kernel"].setText(valOtherCoreTemp["kernel"].toString());

	elements[NGPR + "os_load"] = otherCoreTemp["LoadAvg_1"].toString();
	elements[NGPR + "os_load"].setText(otherCoreTemp["LoadAvg_1"] != ELEM_NOT ? QString("%1 %2 %3").arg(loadavg_1, 0, 'f', 3).arg(loadavg_5, 0, 'f', 3).arg(loadavg_15, 0, 'f', 3) : QString(""));

	elements[NGPR + "cpu_name"] = otherCoreTemp["cpu_name"].toString();
	elements[NGPR + "cpu_name"].setText(valOtherCoreTemp["cpu_name"].toString());

	elements[NGPR + "cpu_temp"] = otherCoreTemp["cpu_temp"].toString();
	elements[NGPR + "cpu_temp"].setText(otherCoreTemp["cpu_temp"] != ELEM_NOT ? QString("%1").arg(cpu_temp, 0, 'f', 0) : QString(""));

	elements[NGPR + "mem_total"] = otherCoreTemp["MemTotal"].toString();
	elements[NGPR + "mem_total"].setText(otherCoreTemp["MemTotal"] != ELEM_NOT ? QString("%1").arg(mem_total) : QString(""));

	elements[NGPR + "mem_avail"] = otherCoreTemp["MemUsedPercent"].toString();
	elements[NGPR + "mem_avail"].setText(otherCoreTemp["MemUsedPercent"] != ELEM_NOT ? QString("%1 (%2%)").arg(mem_avail).arg(mem_used, 0, 'f', 1) : QString(""));

	elements[NGPR + "swap_total"] = otherCoreTemp["SwapTotal"].toString();
	elements[NGPR + "swap_total"].setText(otherCoreTemp["SwapTotal"] != ELEM_NOT ? QString("%1").arg(swap_total) : QString(""));

	elements[NGPR + "swap_avail"] = otherCoreTemp["SwapFreePercent"].toString();
	elements[NGPR + "swap_avail"].setText(otherCoreTemp["SwapFreePercent"] != ELEM_NOT ? QString("%1 (%2%)").arg(swap_free).arg(swap_used, 0, 'f', 1) : QString(""));

	elements[NGPR + "hdd_total"] = otherCoreTemp["HddTotal"].toString();
	elements[NGPR + "hdd_total"].setText(otherCoreTemp["HddTotal"] != ELEM_NOT ? QString("%1").arg(hdd_total) : QString(""));

	elements[NGPR + "hdd_avail"] = otherCoreTemp["HddUsedPercent"].toString();
	elements[NGPR + "hdd_avail"].setText(otherCoreTemp["HddUsedPercent"] != ELEM_NOT ? QString("%1 (%2%)").arg(hdd_avail).arg(hdd_used, 0, 'f', 1) : QString(""));
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funSvkrLocal()
{
//PROCESSOR BOARD
	if(valLocalCoreTemp.contains("Physical id 0"))
		funSvkrCoreLocal();
	else
	{
		if(localPoi["dsp"] != ELEM_NOT)
			localSvkr["cpu"] = ELEM_NORMA;
		else
			localSvkr["cpu"] = ELEM_NOT;
	}

//WORKING
	if(localPoi["dsp"] == ELEM_AVAR || localSvkr["cpu"] == ELEM_AVAR || localVoi["ObSost"] == ELEM_AVAR || localDasd["DASD"] == ELEM_AVAR || localDasd["123GF01"] == ELEM_AVAR)
		localSvkr["ObSost"] = ELEM_AVAR;
	else if(localSvkr["cpu"] == ELEM_ERROR || localVoi["ObSost"] == ELEM_ERROR)
		localSvkr["ObSost"] = ELEM_ERROR;
	else if(localPoi["dsp"] == ELEM_NORMA && localSvkr["cpu"] == ELEM_NORMA && localVoi["ObSost"] == ELEM_NORMA && localDasd["DASD"] == ELEM_NORMA && localDasd["123GF01"] == ELEM_NORMA)
		localSvkr["ObSost"] = ELEM_NORMA;
	else if(localPoi["dsp"] == ELEM_NOT && localSvkr["cpu"] == ELEM_NOT && localVoi["ObSost"] == ELEM_NOT && localDasd["DASD"] == ELEM_NOT && localDasd["123GF01"] == ELEM_NOT)
		localSvkr["ObSost"] = ELEM_NOT;
	else
		localSvkr["ObSost"] = ELEM_ERROR;

	QString NGPR = QString("obr_svkr%1@").arg(IDGPR() + 1);

	elements[NGPR + "dsp"] = localPoi["dsp"].toString();
	elements[NGPR + "cpu"] = localSvkr["cpu"].toString();

	elements[NGPR + "d2vk028"] = localDasd["DASD"].toString();
	elements[NGPR + "d2vk028"].setUser(localDasd["DASD"] != ELEM_NOT ? (localDasd["dasd_master"] == ELEM_NORMA ? "master" : "slave") : "");

	elements[NGPR + "123gf01"] = localDasd["123GF01"].toString();

	messages[NGPR + "123gf01"] = localDasd["123GF01"];
	messages[NGPR + "d2vk028"] = localDasd["DASD"];

	QString NVMPK = QString("obr_base@svkr%1").arg(IDGPR() + 1);
	elements[NVMPK] = localSvkr["ObSost"].toString();

	QString NOBR = QString("base@obr%1").arg(IDGPR() + 1);
	elements[NOBR] = localSvkr["ObSost"].toString();
	elements[NOBR].setUser(m_isMain ? "master" : "slave");

	QString NZG = QString("base@zg%1").arg(IDGPR() + 1);
	elements[NZG] = localDasd["ZG"].toString();//123GF01
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funSvkrOther()
{
//PROCESSOR BOARD
	if(valOtherCoreTemp.contains("Physical id 0"))
		funSvkrCoreOther();
	else
	{
		if(otherPoi["dsp"] != ELEM_NOT)
			otherSvkr["cpu"] = ELEM_NORMA;
		else
			otherSvkr["cpu"] = ELEM_NOT;
	}

//WORKING
	if(otherPoi["dsp"] == ELEM_AVAR || otherSvkr["cpu"] == ELEM_AVAR || otherVoi["ObSost"] == ELEM_AVAR || otherDasd["DASD"] == ELEM_AVAR || otherDasd["123GF01"] == ELEM_AVAR)
		otherSvkr["ObSost"] = ELEM_AVAR;
	else if(otherSvkr["cpu"] == ELEM_ERROR || otherVoi["ObSost"] == ELEM_ERROR)
		otherSvkr["ObSost"] = ELEM_ERROR;
	else if(otherPoi["dsp"] == ELEM_NORMA && otherSvkr["cpu"] == ELEM_NORMA && otherVoi["ObSost"] == ELEM_NORMA && otherDasd["DASD"] == ELEM_NORMA && otherDasd["123GF01"] == ELEM_NORMA)
		otherSvkr["ObSost"] = ELEM_NORMA;
	else if(otherPoi["dsp"] == ELEM_NOT && otherSvkr["cpu"] == ELEM_NOT && otherVoi["ObSost"] == ELEM_NOT && otherDasd["DASD"] == ELEM_NOT && otherDasd["123GF01"] == ELEM_NOT)
		otherSvkr["ObSost"] = ELEM_NOT;
	else
		otherSvkr["ObSost"] = ELEM_ERROR;

	QString NGPR = QString("obr_svkr%1@").arg(OTHER_GPR_ID() + 1);

	elements[NGPR + "dsp"] = otherPoi["dsp"].toString();
	elements[NGPR + "cpu"] = otherSvkr["cpu"].toString();

	elements[NGPR + "d2vk028"] = otherDasd["DASD"].toString();
	elements[NGPR + "d2vk028"].setUser(otherDasd["DASD"] != ELEM_NOT ? (otherDasd["dasd_master"] == ELEM_NORMA ? "master" : "slave") : "");

	elements[NGPR + "123gf01"] = otherDasd["123GF01"].toString();

	messages[NGPR + "123gf01"] = otherDasd["123GF01"];
	messages[NGPR + "d2vk028"] = otherDasd["DASD"];

	QString NVMPK = QString("obr_base@svkr%1").arg(OTHER_GPR_ID() + 1);
	elements[NVMPK] = otherSvkr["ObSost"].toString();

	QString NOBR = QString("base@obr%1").arg(OTHER_GPR_ID() + 1);
	elements[NOBR] = otherSvkr["ObSost"].toString();
	elements[NOBR].setUser(m_isWorkGpr ? (!m_isMain ? "master" : "slave") : "");

	QString NZG = QString("base@zg%1").arg(OTHER_GPR_ID() + 1);
	elements[NZG] = otherDasd["123GF01"].toString();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::checkReserveProc()
{
//	LogInfo("prm1 = %s, prm2 = %s", qPrintable(b126gg03["fsv1"].toString()), qPrintable(b126gg03["fsv2"].toString()));

//qDebug() << sigmap.dump();

	bool avarPrm1 = b124pp04["koeff_pilot_1"] == ELEM_AVAR || b124pp04["dsp_1"] == ELEM_AVAR;
	bool avarPrm2 = b124pp04["koeff_pilot_2"] == ELEM_AVAR || b124pp04["dsp_2"] == ELEM_AVAR;
	bool offPrm = !m_isWorkGpr;

//	LogInfo("CONTROL::checkReserveProc prm1 = %d, prm2 = %d  off = %d", avarPrm1, avarPrm2, offPrm);

	if(m_isMain)
	{
		if(ISGPR1() && avarPrm1 && !avarPrm2 && !offPrm)
		{
			LogInfo("CONTROL: cmdChangeKits 2");
			emit cmdChangeKits();
		}

		if(ISGPR2() && avarPrm2 && !avarPrm1 && !offPrm)
		{
			LogInfo("CONTROL: cmdChangeKits 1");
			emit cmdChangeKits();
		}
	}
}

// ----------------------------------------------------------------------------
