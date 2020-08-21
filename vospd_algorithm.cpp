#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "vospd_service.h"
#include "vospd_thread.h"

// ------------------------------------------------------------------
void VOSPD_SERVICE::updateStatus(quint32 n_vospd, const VospdStatus & status)
{
	QString N_VOSPD = QString("vospd%1").arg(n_vospd + 1);

	if(status.bot_Main == 1)
		m_VospdState[N_VOSPD + "@bot_main"] = ELEM_AVAR;
	else
		m_VospdState[N_VOSPD + "@bot_main"] = ELEM_NORMA;

	if(status.bot_Main == 1)
		m_VospdState[N_VOSPD + "@opt_main"] = ELEM_NOT;
	else if(status.opt_Main == 1)
		m_VospdState[N_VOSPD + "@opt_main"] = ELEM_AVAR;
	else
		m_VospdState[N_VOSPD + "@opt_main"] = ELEM_NORMA;

	if(status.bot_Main == 1 || status.opt_Main == 1)
		m_VospdState[N_VOSPD + "@top_main"] = ELEM_NOT;
	else if(status.top_Main == 1)
		m_VospdState[N_VOSPD + "@top_main"] = ELEM_AVAR;
	else
		m_VospdState[N_VOSPD + "@top_main"] = ELEM_NORMA;

	if(status.bot_Main == 1 || status.opt_Main == 1 || status.top_Main == 1)
		m_VospdState[N_VOSPD + "@az_sensor1"] = ELEM_NOT;
	else if(status.az_status1 == 1)
		m_VospdState[N_VOSPD + "@az_sensor1"] = ELEM_AVAR;
	else
		m_VospdState[N_VOSPD + "@az_sensor1"] = ELEM_NORMA;

	if(status.bot_Main == 1 || status.opt_Main == 1 || status.top_Main == 1)
		m_VospdState[N_VOSPD + "@az_sensor2"] = ELEM_NOT;
	else if(status.az_status2 == 1)
		m_VospdState[N_VOSPD + "@az_sensor2"] = ELEM_AVAR;
	else
		m_VospdState[N_VOSPD + "@az_sensor2"] = ELEM_NORMA;

	if(status.bot_Main == 1 || status.opt_Main == 1 || status.top_Main == 1)
		m_VospdState[N_VOSPD + "@hr_sensor"] = ELEM_NOT;
	else if(status.dg_link == 1)
		m_VospdState[N_VOSPD + "@hr_sensor"] = ELEM_AVAR;
	else
		m_VospdState[N_VOSPD + "@hr_sensor"] = ELEM_NORMA;

	if(status.bot_Main == 1 || status.opt_Main == 1 || status.top_Main == 1)
		m_VospdState[N_VOSPD + "@need_horizont"] = ELEM_NOT;
	else if(status.horizont_status == 1)
		m_VospdState[N_VOSPD + "@need_horizont"] = ELEM_AVAR;
	else
		m_VospdState[N_VOSPD + "@need_horizont"] = ELEM_NORMA;
}

// ------------------------------------------------------------------

void VOSPD_SERVICE::updateAngles(quint32 n_vospd, const VospdAnswerAngles & answer)
{
	QString N_VOSPD = QString("vospd%1").arg(n_vospd + 1);

//qDebug() << "axis" << answer.angles.axis;
//qDebug() << "cross" << answer.angles.cross;

	if(answer.status.top_Main || answer.status.dg_link)
	{
		m_VospdState[N_VOSPD + "@axis_value"] = ELEM_NOT;
		m_VospdValues[N_VOSPD + "@axis_value"] = QString("%1").arg(answer.angles.axis);
	}
	else if(answer.status.horizont_status)
	{
		m_VospdState[N_VOSPD + "@axis_value"] = ELEM_AVAR;
		m_VospdValues[N_VOSPD + "@axis_value"] = QString("%1").arg(answer.angles.axis);
	}
	else
	{
		m_VospdState[N_VOSPD + "@axis_value"] = ELEM_NORMA;
		m_VospdValues[N_VOSPD + "@axis_value"] = QString("%1").arg(answer.angles.axis);
	}

	if(answer.status.top_Main || answer.status.dg_link)
	{
		m_VospdState[N_VOSPD + "@cross_value"] = ELEM_NOT;
		m_VospdValues[N_VOSPD + "@cross_value"] = QString("%1").arg(answer.angles.cross);
	}
	else if(answer.status.horizont_status)
	{
		m_VospdState[N_VOSPD + "@cross_value"] = ELEM_AVAR;
		m_VospdValues[N_VOSPD + "@cross_value"] = QString("%1").arg(answer.angles.cross);
	}
	else
	{
		m_VospdState[N_VOSPD + "@cross_value"] = ELEM_NORMA;
		m_VospdValues[N_VOSPD + "@cross_value"] = QString("%1").arg(answer.angles.cross);
	}
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::updateActSensor(quint32 n_vospd, quint8 act_sensor)
{
	QString N_VOSPD = QString("vospd%1").arg(n_vospd + 1);

	if(act_sensor == 1)
		m_VospdState[N_VOSPD + "@act_sensor1"] = ELEM_NORMA;
	else
		m_VospdState[N_VOSPD + "@act_sensor1"] = ELEM_NOT;

	if(act_sensor == 2)
		m_VospdState[N_VOSPD + "@act_sensor2"] = ELEM_NORMA;
	else
		m_VospdState[N_VOSPD + "@act_sensor2"] = ELEM_NOT;
}

// ------------------------------------------------------------------
void VOSPD_SERVICE::updateConfig(quint32 n_vospd, const VospdConfig & config)
{

}

// ------------------------------------------------------------------
void VOSPD_SERVICE::updateCorrections(quint32 n_vospd, const VospdAzimuthCorrection & az1_cor, const VospdAzimuthCorrection & az2_cor)
{

}

// ------------------------------------------------------------------
void VOSPD_SERVICE::updateCommonState()
{
//123HP02
	if(m_VospdState["vospd1@bot_main"] == ELEM_NOT && m_VospdState["vospd2@bot_main"] == ELEM_NOT)
		m_VospdState["vospd@123hp02"] = ELEM_NOT;
	else if((m_VospdState["vospd1@bot_main"] == ELEM_AVAR && m_VospdState["vospd2@bot_main"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@bot_main"] == ELEM_AVAR && m_VospdState["vospd2@bot_main"] == ELEM_NOT) ||
		(m_VospdState["vospd1@bot_main"] == ELEM_NOT && m_VospdState["vospd2@bot_main"] == ELEM_AVAR))
		m_VospdState["vospd@123hp02"] = ELEM_AVAR;
	else if((m_VospdState["vospd1@bot_main"] == ELEM_AVAR || m_VospdState["vospd2@bot_main"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@bot_main"] == ELEM_AVAR || m_VospdState["vospd2@bot_main"] == ELEM_NOT) ||
		(m_VospdState["vospd1@bot_main"] == ELEM_NOT || m_VospdState["vospd2@bot_main"] == ELEM_AVAR))
		m_VospdState["vospd@123hp02"] = ELEM_ERROR;
	else if(m_VospdState["vospd1@bot_main"] == ELEM_NORMA && m_VospdState["vospd2@bot_main"] == ELEM_NORMA)
		m_VospdState["vospd@123hp02"] = ELEM_NORMA;
	else
		m_VospdState["vospd@123hp02"] = ELEM_ERROR;

//123HP01
	if(m_VospdState["vospd1@top_main"] == ELEM_NOT && m_VospdState["vospd2@top_main"] == ELEM_NOT)
		m_VospdState["vospd@123hp01"] = ELEM_NOT;
	else if((m_VospdState["vospd1@top_main"] == ELEM_AVAR && m_VospdState["vospd2@top_main"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@top_main"] == ELEM_AVAR && m_VospdState["vospd2@top_main"] == ELEM_NOT) ||
		(m_VospdState["vospd1@top_main"] == ELEM_NOT && m_VospdState["vospd2@top_main"] == ELEM_AVAR))
		m_VospdState["vospd@123hp01"] = ELEM_AVAR;
	else if((m_VospdState["vospd1@top_main"] == ELEM_AVAR || m_VospdState["vospd2@top_main"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@top_main"] == ELEM_AVAR || m_VospdState["vospd2@top_main"] == ELEM_NOT) ||
		(m_VospdState["vospd1@top_main"] == ELEM_NOT || m_VospdState["vospd2@top_main"] == ELEM_AVAR))
		m_VospdState["vospd@123hp01"] = ELEM_ERROR;
	else if(m_VospdState["vospd1@top_main"] == ELEM_NORMA && m_VospdState["vospd2@top_main"] == ELEM_NORMA)
		m_VospdState["vospd@123hp01"] = ELEM_NORMA;
	else
		m_VospdState["vospd@123hp01"] = ELEM_ERROR;

//AZ1_SENSOR
	if((m_VospdState["vospd1@az_sensor1"] == ELEM_AVAR && m_VospdState["vospd2@az_sensor1"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@az_sensor1"] == ELEM_AVAR && m_VospdState["vospd2@az_sensor1"] == ELEM_NOT) ||
		(m_VospdState["vospd1@az_sensor1"] == ELEM_NOT && m_VospdState["vospd2@az_sensor1"] == ELEM_AVAR))
		m_VospdState["vospd@az_sensor1"] = ELEM_AVAR;
	else if((m_VospdState["vospd1@az_sensor1"] == ELEM_NORMA && m_VospdState["vospd2@az_sensor1"] == ELEM_NORMA) ||
		(m_VospdState["vospd1@az_sensor1"] == ELEM_NORMA && m_VospdState["vospd2@az_sensor1"] == ELEM_NOT) ||
		(m_VospdState["vospd1@az_sensor1"] == ELEM_NOT && m_VospdState["vospd2@az_sensor1"] == ELEM_NORMA))
		m_VospdState["vospd@az_sensor1"] = ELEM_NORMA;
	else if(m_VospdState["vospd1@az_sensor1"] == ELEM_NOT && m_VospdState["vospd2@az_sensor1"] == ELEM_NOT)
		m_VospdState["vospd@az_sensor1"] = ELEM_NOT;
	else
		m_VospdState["vospd@az_sensor1"] = ELEM_ERROR;

//AZ2_SENSOR
	if((m_VospdState["vospd1@az_sensor2"] == ELEM_AVAR && m_VospdState["vospd2@az_sensor2"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@az_sensor2"] == ELEM_AVAR && m_VospdState["vospd2@az_sensor2"] == ELEM_NOT) ||
		(m_VospdState["vospd1@az_sensor2"] == ELEM_NOT && m_VospdState["vospd2@az_sensor2"] == ELEM_AVAR))
		m_VospdState["vospd@az_sensor2"] = ELEM_AVAR;
	else if((m_VospdState["vospd1@az_sensor2"] == ELEM_NORMA && m_VospdState["vospd2@az_sensor2"] == ELEM_NORMA) ||
		(m_VospdState["vospd1@az_sensor2"] == ELEM_NORMA && m_VospdState["vospd2@az_sensor2"] == ELEM_NOT) ||
		(m_VospdState["vospd1@az_sensor2"] == ELEM_NOT && m_VospdState["vospd2@az_sensor2"] == ELEM_NORMA))
		m_VospdState["vospd@az_sensor2"] = ELEM_NORMA;
	else if(m_VospdState["vospd1@az_sensor2"] == ELEM_NOT && m_VospdState["vospd2@az_sensor2"] == ELEM_NOT)
		m_VospdState["vospd@az_sensor2"] = ELEM_NOT;
	else
		m_VospdState["vospd@az_sensor2"] = ELEM_ERROR;
/*
//HR_SENSOR
	if((m_VospdState["vospd1@hr_sensor"] == ELEM_AVAR && m_VospdState["vospd2@hr_sensor"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@hr_sensor"] == ELEM_AVAR && m_VospdState["vospd2@hr_sensor"] == ELEM_NOT) ||
		(m_VospdState["vospd1@hr_sensor"] == ELEM_NOT && m_VospdState["vospd2@hr_sensor"] == ELEM_AVAR))
		m_VospdState["vospd@hr_sensor"] = ELEM_AVAR;
	else if((m_VospdState["vospd1@hr_sensor"] == ELEM_NORMA && m_VospdState["vospd2@hr_sensor"] == ELEM_NORMA) ||
		(m_VospdState["vospd1@hr_sensor"] == ELEM_NORMA && m_VospdState["vospd2@hr_sensor"] == ELEM_NOT) ||
		(m_VospdState["vospd1@hr_sensor"] == ELEM_NOT && m_VospdState["vospd2@hr_sensor"] == ELEM_NORMA))
		m_VospdState["vospd@hr_sensor"] = ELEM_NORMA;
	else if(m_VospdState["vospd1@hr_sensor"] == ELEM_NOT && m_VospdState["vospd2@hr_sensor"] == ELEM_NOT)
		m_VospdState["vospd@hr_sensor"] = ELEM_NOT;
	else
		m_VospdState["vospd@hr_sensor"] = ELEM_ERROR;

//NEED_HORIZONT
	if((m_VospdState["vospd1@top_main"] == ELEM_NORMA && m_VospdState["vospd1@need_horizont"] == ELEM_AVAR) ||
		(m_VospdState["vospd2@top_main"] == ELEM_NORMA && m_VospdState["vospd2@need_horizont"] == ELEM_AVAR))
		m_VospdState["vospd@need_horizont"] = ELEM_AVAR;
	else
		m_VospdState["vospd@need_horizont"] = ELEM_NORMA;
*/
//HR_SENSOR
	m_VospdState["vospd@hr_sensor"] = m_VospdState["vospd1@hr_sensor"];

//NEED_HORIZONT
	m_VospdState["vospd@need_horizont"] = m_VospdState["vospd1@top_main"];

//ETHERNET
	if(m_VospdState["vospd1@connected"] == ELEM_NORMA || m_VospdState["vospd2@connected"] == ELEM_NORMA)
		m_VospdState["vospd@ethernet"] = ELEM_NORMA;
	else
		m_VospdState["vospd@ethernet"] = ELEM_NOT;

//COMM1
	if(m_VospdState["vospd1@connected"] == ELEM_NORMA)
		m_VospdState["vospd@comm1"] = ELEM_NORMA;
	else
		m_VospdState["vospd@comm1"] = ELEM_NOT;

//COMM2
	if(m_VospdState["vospd2@connected"] == ELEM_NORMA)
		m_VospdState["vospd@comm2"] = ELEM_NORMA;
	else
		m_VospdState["vospd@comm2"] = ELEM_NOT;

//ObSost
	if((m_VospdState["vospd1@top_main"] == ELEM_AVAR && m_VospdState["vospd2@top_main"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@bot_main"] == ELEM_AVAR && m_VospdState["vospd2@bot_main"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@opt_main"] == ELEM_AVAR && m_VospdState["vospd2@opt_main"] == ELEM_AVAR))
		m_VospdState["vospd@ObSost"] = ELEM_AVAR;
	else if((m_VospdState["vospd1@top_main"] == ELEM_AVAR || m_VospdState["vospd2@top_main"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@bot_main"] == ELEM_AVAR || m_VospdState["vospd2@bot_main"] == ELEM_AVAR) ||
		(m_VospdState["vospd1@opt_main"] == ELEM_AVAR || m_VospdState["vospd2@opt_main"] == ELEM_AVAR))
		m_VospdState["vospd@ObSost"] = ELEM_ERROR;
	else if((m_VospdState["vospd1@top_main"] == ELEM_NORMA && m_VospdState["vospd2@top_main"] == ELEM_NORMA) &&
		(m_VospdState["vospd1@bot_main"] == ELEM_NORMA && m_VospdState["vospd2@bot_main"] == ELEM_NORMA) &&
		(m_VospdState["vospd1@opt_main"] == ELEM_NORMA && m_VospdState["vospd2@opt_main"] == ELEM_NORMA))
		m_VospdState["vospd@ObSost"] = ELEM_NORMA;
	else if((m_VospdState["vospd1@top_main"] == ELEM_NOT && m_VospdState["vospd2@top_main"] == ELEM_NOT) &&
		(m_VospdState["vospd1@bot_main"] == ELEM_NOT && m_VospdState["vospd2@bot_main"] == ELEM_NOT) &&
		(m_VospdState["vospd1@opt_main"] == ELEM_NOT && m_VospdState["vospd2@opt_main"] == ELEM_NOT))
		m_VospdState["vospd@ObSost"] = ELEM_NOT;
	else
		m_VospdState["vospd@ObSost"] = ELEM_ERROR;

	emit sigState(m_VospdState, m_VospdValues);
}

// ------------------------------------------------------------------
