#include "../common/logger.h"
#include "globalvar.h"
#include "algorithm.h"
#include "canalasku_data.h"

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPoiKoeffLocal()
{
	quint32 nAvarKsh = 0, nErrorKsh = 0, nNormaKsh = 0;
	quint32 nAvarSharu = 0;

	QString KOEFF = QString("koeff%1@").arg(IDGPR() + 1);

	bool work = (localPoi["dsp"] != ELEM_NOT);

	for(int n = 1; n <= 2; n++)
	{
		QString N = QString::number(n);
		QString nKsh  = "ksh"  + N;
		QString nSsh  = "ssh"  + N;
		QString nSshr = "sshr" + N;
		QString nGsh  = "gsh"  + N;
		QString nSht  = "sht"  + N;
		QString nSharu  = "sharu" + N;
		QString nSharuO = "sharu_overflow"  + N;
		QString nSharuU = "sharu_underflow" + N;
		QString str_value;
		double value;
		bool ok;
		bool valid = (bool)valLocalPoiKoeff["sharu_time"].toUInt();

//Ksh
		value = valLocalPoiKoeff[nKsh].toDouble(&ok);
//		LogInfo("%3.1f %3.1f %3.1f %3.1f", value, m_setup.koeffPoi.kshNorma, m_setup.koeffPoi.kshError, m_setup.koeffPoi.kshAvar);
		if(work && ok && valid)
		{
			if(value >= m_setup.koeffPoi.kshNorma && value <= m_setup.koeffPoi.kshError)
			{
				localKoeff[nKsh] = ELEM_NORMA;
				nNormaKsh++;
			}
			else if(value > m_setup.koeffPoi.kshError && value <= m_setup.koeffPoi.kshAvar)
			{
				localKoeff[nKsh] = ELEM_ERROR;
				nErrorKsh++;
			}
			else if(value > m_setup.koeffPoi.kshAvar)
			{
				localKoeff[nKsh] = ELEM_AVAR;
				nAvarKsh++;
			}
			else
				localKoeff[nKsh] = ELEM_NOT;

			str_value = QString("%1").arg(value, 0, 'f', 1);
		}
		else
		{
			localKoeff[nKsh] = ELEM_NOT;
			str_value = " ";
		}

		elements[KOEFF + nKsh] = localKoeff[nKsh].toString();
		elements[KOEFF + nKsh].setText(str_value);

//Ssh
		value = valLocalPoiKoeff[nSsh].toDouble(&ok);
		if(work && ok)
		{
			str_value = QString("%1").arg(value, 0, 'f', 1);
			localKoeff[nSsh] = ELEM_NORMA;
		}
		else
		{
			str_value = " ";
			localKoeff[nSsh] = ELEM_NOT;
		}

		elements[KOEFF + nSsh] = localKoeff[nSsh].toString();
		elements[KOEFF + nSsh].setText(str_value);

//Sshr
		value = valLocalPoiKoeff[nSshr].toDouble(&ok);
		if(work && ok && valid)
		{
			str_value = QString("%1").arg(value, 0, 'f', 1);
			localKoeff[nSshr] = ELEM_NORMA;
		}
		else
		{
			str_value = " ";
			localKoeff[nSshr] = ELEM_NOT;
		}

		elements[KOEFF + nSshr] = localKoeff[nSshr].toString();
		elements[KOEFF + nSshr].setText(str_value);

//Gsh
		value = valLocalPoiKoeff[nGsh].toDouble(&ok);
		if(work && ok && valid)
		{
			str_value = QString("%1").arg(value, 0, 'f', 1);
			localKoeff[nGsh] = ELEM_NORMA;
		}
		else
		{
			str_value = " ";
			localKoeff[nGsh] = ELEM_NOT;
		}

		elements[KOEFF + nGsh] = localKoeff[nGsh].toString();
		elements[KOEFF + nGsh].setText(str_value);

//Sht
		value = valLocalPoiKoeff[nSht].toDouble(&ok);
		if(work && ok)
		{
			str_value = QString("%1").arg(value, 0, 'f', 1);
			localKoeff[nSht] = ELEM_NORMA;
		}
		else
		{
			str_value = " ";
			localKoeff[nSht] = ELEM_NOT;
		}

		elements[KOEFF + nSht] = localKoeff[nSht].toString();
		elements[KOEFF + nSht].setText(str_value);

//Sharu
		QString str_sharu;
		if(work && localPoi[nSharuO] == ELEM_AVAR)
		{
			str_sharu = "overflow";
			localPoi[nSharu] = ELEM_AVAR;
			nAvarSharu++;
		}
		else if(work && localPoi[nSharuU] == ELEM_AVAR)
		{
			str_sharu = "underflow";
			localPoi[nSharu] = ELEM_AVAR;
			nAvarSharu++;
		}
		else if(work && (localPoi[nSharuO] == ELEM_NORMA || localPoi[nSharuU] == ELEM_NORMA))
		{
			str_sharu = "normal";
			localPoi[nSharu] = ELEM_NORMA;
		}
		else
		{
			str_sharu = " ";
			localPoi[nSharu] = ELEM_NOT;
		}

		elements[KOEFF + nSharu] = localPoi[nSharu].toString();
		elements[KOEFF + nSharu].setUser(str_sharu);
	}

	if(nAvarKsh > 0 || nAvarSharu > 0)
		localKoeff["ObSostKoeff"] = ELEM_AVAR;
	else if(nErrorKsh > 0)
		localKoeff["ObSostKoeff"] = ELEM_ERROR;
	else if(nNormaKsh > 0)
		localKoeff["ObSostKoeff"] = ELEM_NORMA;
	else
		localKoeff["ObSostKoeff"] = ELEM_NOT;
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPoiKoeffOther()
{
	quint32 nAvarKsh = 0, nErrorKsh = 0, nNormaKsh = 0;
	quint32 nAvarSharu = 0;

	QString KOEFF = QString("koeff%1@").arg(OTHER_GPR_ID() + 1);

	bool work = (otherPoi["dsp"] != ELEM_NOT);

	for(int n = 1; n <= 2; n++)
	{
		QString N = QString::number(n);
		QString nKsh  = "ksh"  + N;
		QString nSsh  = "ssh"  + N;
		QString nSshr = "sshr" + N;
		QString nGsh  = "gsh"  + N;
		QString nSht  = "sht"  + N;
		QString nSharu  = "sharu" + N;
		QString nSharuO = "sharu_overflow"  + N;
		QString nSharuU = "sharu_underflow" + N;
		QString str_value;
		double value;
		bool ok;
		bool valid = (bool)valOtherPoiKoeff["sharu_time"].toUInt();

//Ksh
		value = valOtherPoiKoeff[nKsh].toDouble(&ok);
//		LogInfo("%3.1f %3.1f %3.1f %3.1f", value, m_setup.koeffPoi.kshNorma, m_setup.koeffPoi.kshError, m_setup.koeffPoi.kshAvar);
		if(work && ok && valid)
		{
			if(value >= m_setup.koeffPoi.kshNorma && value <= m_setup.koeffPoi.kshError)
			{
				otherKoeff[nKsh] = ELEM_NORMA;
				nNormaKsh++;
			}
			else if(value > m_setup.koeffPoi.kshError && value <= m_setup.koeffPoi.kshAvar)
			{
				otherKoeff[nKsh] = ELEM_ERROR;
				nErrorKsh++;
			}
			else if(value > m_setup.koeffPoi.kshAvar)
			{
				otherKoeff[nKsh] = ELEM_AVAR;
				nAvarKsh++;
			}
			else
				otherKoeff[nKsh] = ELEM_NOT;

			str_value = QString("%1").arg(value, 0, 'f', 1);
		}
		else
		{
			otherKoeff[nKsh] = ELEM_NOT;
			str_value = " ";
		}

		elements[KOEFF + nKsh] = otherKoeff[nKsh].toString();
		elements[KOEFF + nKsh].setText(str_value);

//Ssh
		value = valOtherPoiKoeff[nSsh].toDouble(&ok);
		if(work && ok)
		{
			str_value = QString("%1").arg(value, 0, 'f', 1);
			otherKoeff[nSsh] = ELEM_NORMA;
		}
		else
		{
			str_value = " ";
			otherKoeff[nSsh] = ELEM_NOT;
		}

		elements[KOEFF + nSsh] = otherKoeff[nSsh].toString();
		elements[KOEFF + nSsh].setText(str_value);

//Sshr
		value = valOtherPoiKoeff[nSshr].toDouble(&ok);
		if(work && ok && valid)
		{
			str_value = QString("%1").arg(value, 0, 'f', 1);
			otherKoeff[nSshr] = ELEM_NORMA;
		}
		else
		{
			str_value = " ";
			otherKoeff[nSshr] = ELEM_NOT;
		}

		elements[KOEFF + nSshr] = otherKoeff[nSshr].toString();
		elements[KOEFF + nSshr].setText(str_value);

//Gsh
		value = valOtherPoiKoeff[nGsh].toDouble(&ok);
		if(work && ok && valid)
		{
			str_value = QString("%1").arg(value, 0, 'f', 1);
			otherKoeff[nGsh] = ELEM_NORMA;
		}
		else
		{
			str_value = " ";
			otherKoeff[nGsh] = ELEM_NOT;
		}

		elements[KOEFF + nGsh] = otherKoeff[nGsh].toString();
		elements[KOEFF + nGsh].setText(str_value);

//Sht
		value = valOtherPoiKoeff[nSht].toDouble(&ok);
		if(work && ok)
		{
			str_value = QString("%1").arg(value, 0, 'f', 1);
			otherKoeff[nSht] = ELEM_NORMA;
		}
		else
		{
			str_value = " ";
			otherKoeff[nSht] = ELEM_NOT;
		}

		elements[KOEFF + nSht] = otherKoeff[nSht].toString();
		elements[KOEFF + nSht].setText(str_value);

//Sharu
		QString str_sharu;
		if(work && otherPoi[nSharuO] == ELEM_AVAR)
		{
			str_sharu = "overflow";
			otherPoi[nSharu] = ELEM_AVAR;
			nAvarSharu++;
		}
		else if(work && otherPoi[nSharuU] == ELEM_AVAR)
		{
			str_sharu = "underflow";
			otherPoi[nSharu] = ELEM_AVAR;
			nAvarSharu++;
		}
		else if(work && (otherPoi[nSharuO] == ELEM_NORMA || otherPoi[nSharuU] == ELEM_NORMA))
		{
			str_sharu = "normal";
			otherPoi[nSharu] = ELEM_NORMA;
		}
		else
		{
			str_sharu = " ";
			otherPoi[nSharu] = ELEM_NOT;
		}

		elements[KOEFF + nSharu] = otherPoi[nSharu].toString();
		elements[KOEFF + nSharu].setUser(str_sharu);
	}

	if(nAvarKsh > 0 || nAvarSharu > 0)
		otherKoeff["ObSostKoeff"] = ELEM_AVAR;
	else if(nErrorKsh > 0)
		otherKoeff["ObSostKoeff"] = ELEM_ERROR;
	else if(nNormaKsh > 0)
		otherKoeff["ObSostKoeff"] = ELEM_NORMA;
	else
		otherKoeff["ObSostKoeff"] = ELEM_NOT;
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPoiPilotLocal()
{
	quint32 nAvarPs = 0, nNormaPs = 0;
	QString KOEFF = QString("koeff%1@").arg(IDGPR() + 1);
	bool work = (localPoi["dsp"] != ELEM_NOT);

	for(int n = 1; n <= 24; n++)
	{
		QString N = QString::number(n);
		QString nMag  = "mag" + N;
		QString nSup  = "sup" + N;
		QString nPs = "ps" + N;
		QString nKp = "kp" + N;
		QString str_value;
		double value;
		bool ok;

//Ps
		value = valLocalPoiPilot[nMag].toDouble(&ok);
		if(work && ok)
		{
			if(value > m_setup.koeffPoi.psNorma)
			{
				localKoeff[nPs] = ELEM_NORMA;
				nNormaPs++;
			}
			else
			{
				localKoeff[nPs] = ELEM_AVAR;
				nAvarPs++;
			}

			str_value = QString("%1").arg(value, 0, 'f', 0);
		}
		else
		{
			localKoeff[nPs] = ELEM_NOT;
			str_value = " ";
		}

		elements[KOEFF + nPs] = localKoeff[nPs].toString();
		elements[KOEFF + nPs].setText(str_value);

//Kp
		value = valLocalPoiPilot[nSup].toDouble(&ok);
		if(work && ok)
		{
			if(value > m_setup.koeffPoi.kpNorma)
			{
				localKoeff[nKp] = ELEM_NORMA;
				nNormaPs++;
			}
			else
			{
				localKoeff[nKp] = ELEM_AVAR;
				nAvarPs++;
			}

			str_value = QString("%1").arg(value, 0, 'f', 0);
		}
		else
		{
			localKoeff[nKp] = ELEM_NOT;
			str_value = " ";
		}

		elements[KOEFF + nKp] = localKoeff[nKp].toString();
		elements[KOEFF + nKp].setText(str_value);
	}

	if(nAvarPs > 12)
		localKoeff["ObSostPilot"] = ELEM_AVAR;
	else if(nAvarPs > 0)
		localKoeff["ObSostPilot"] = ELEM_ERROR;
	else if(nNormaPs > 0)
		localKoeff["ObSostPilot"] = ELEM_NORMA;
	else
		localKoeff["ObSostPilot"] = ELEM_NOT;
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPoiPilotOther()
{
	quint32 nAvarPs = 0, nNormaPs = 0;
	QString KOEFF = QString("koeff%1@").arg(OTHER_GPR_ID() + 1);
	bool work = (otherPoi["dsp"] != ELEM_NOT);

	for(int n = 1; n <= 24; n++)
	{
		QString N = QString::number(n);
		QString nMag  = "mag" + N;
		QString nSup  = "sup" + N;
		QString nPs = "ps" + N;
		QString nKp = "kp" + N;
		QString str_value;
		double value;
		bool ok;

//Ps
		value = valOtherPoiPilot[nMag].toDouble(&ok);
		if(work && ok)
		{
			if(value > m_setup.koeffPoi.psNorma)
			{
				otherKoeff[nPs] = ELEM_NORMA;
				nNormaPs++;
			}
			else
			{
				otherKoeff[nPs] = ELEM_AVAR;
				nAvarPs++;
			}

			str_value = QString("%1").arg(value, 0, 'f', 0);
		}
		else
		{
			otherKoeff[nPs] = ELEM_NOT;
			str_value = " ";
		}

		elements[KOEFF + nPs] = otherKoeff[nPs].toString();
		elements[KOEFF + nPs].setText(str_value);

//Kp
		value = valOtherPoiPilot[nSup].toDouble(&ok);
		if(work && ok)
		{
			if(value > m_setup.koeffPoi.kpNorma)
			{
				otherKoeff[nKp] = ELEM_NORMA;
				nNormaPs++;
			}
			else
			{
				otherKoeff[nKp] = ELEM_AVAR;
				nAvarPs++;
			}

			str_value = QString("%1").arg(value, 0, 'f', 0);
		}
		else
		{
			otherKoeff[nKp] = ELEM_NOT;
			str_value = " ";
		}

		elements[KOEFF + nKp] = otherKoeff[nKp].toString();
		elements[KOEFF + nKp].setText(str_value);
	}

	if(nAvarPs > 12)
		otherKoeff["ObSostPilot"] = ELEM_AVAR;
	else if(nAvarPs > 0)
		otherKoeff["ObSostPilot"] = ELEM_ERROR;
	else if(nNormaPs > 0)
		otherKoeff["ObSostPilot"] = ELEM_NORMA;
	else
		otherKoeff["ObSostPilot"] = ELEM_NOT;
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPoiCommon()
{
	if(localKoeff["ObSostKoeff"] == ELEM_AVAR || localKoeff["ObSostPilot"] == ELEM_AVAR)
		localKoeff["ObSost"] = ELEM_AVAR;
	else if(localKoeff["ObSostKoeff"] == ELEM_ERROR || localKoeff["ObSostPilot"] == ELEM_ERROR)
		localKoeff["ObSost"] = ELEM_ERROR;
	else if(localKoeff["ObSostKoeff"] == ELEM_NORMA || localKoeff["ObSostPilot"] == ELEM_NORMA)
		localKoeff["ObSost"] = ELEM_NORMA;
	else
		localKoeff["ObSost"] = ELEM_NOT;

	if(ISGPR1())
	{
		b124pp04["dsp_1"] = localPoi["dsp"];
		b124pp04["dsp_2"] = otherPoi["dsp"];
		b124pp04["koeff_pilot_1"] = localKoeff["ObSost"];
		b124pp04["koeff_pilot_2"] = otherKoeff["ObSost"];
	}

	if(ISGPR2())
	{
		b124pp04["dsp_2"] = localPoi["dsp"];
		b124pp04["dsp_1"] = otherPoi["dsp"];
		b124pp04["koeff_pilot_2"] = localKoeff["ObSost"];
		b124pp04["koeff_pilot_1"] = otherKoeff["ObSost"];
	}
}

// ----------------------------------------------------------------------------
