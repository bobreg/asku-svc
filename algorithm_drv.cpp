#include "../common/logger.h"
#include "globalvar.h"
#include "algorithm.h"
#include "canalasku_data.h"

// ----------------------------------------------------------------------------
void AskuAlgorithm::funVospd()
{
	elements["base@az_sensor1"] = vospd["vospd@az_sensor1"];
	elements["base@az_sensor2"] = vospd["vospd@az_sensor2"];
	elements["base@hr_sensor"] = vospd["vospd@hr_sensor"];

	elements["ant@az_sensor1"] = vospd["vospd@az_sensor1"];
	elements["ant@az_sensor2"] = vospd["vospd@az_sensor2"];
	elements["ant@hr_sensor"] = vospd["vospd@hr_sensor"];

	elements["vospd@az_sensor1"] = vospd["vospd@az_sensor1"];
	elements["vospd@az_sensor2"] = vospd["vospd@az_sensor2"];
	elements["vospd@hr_sensor"] = vospd["vospd@hr_sensor"];

	elements["vospd@123hp01_1"] = vospd["vospd1@top_main"];
	elements["vospd@123hp01_2"] = vospd["vospd2@top_main"];
	elements["vospd@123hp02_1"] = vospd["vospd1@bot_main"];
	elements["vospd@123hp02_2"] = vospd["vospd2@bot_main"];

	elements["vospd@line1"] = vospd["vospd1@opt_main"];
	elements["vospd@line2"] = vospd["vospd2@opt_main"];

	elements["vospd@ethernet"] = vospd["vospd@ethernet"];
	elements["vospd@comm1"] = vospd["vospd@comm1"];
	elements["vospd@comm2"] = vospd["vospd@comm2"];
	elements["vospd@svkr1"] = ELEM_DISABLE;
	elements["vospd@svkr2"] = ELEM_DISABLE;

	elements["ant@123hp01"] = vospd["vospd@123hp01"];
	elements["obr_base@123hp02"] = vospd["vospd@123hp02"];

	elements["base@need_horizont"] = vospd["vospd@need_horizont"];
//	elements["ant@need_horizont"] = vospd["vospd@need_horizont"];

	elements["base@vospd"] = vospd["vospd@ObSost"];
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funAntenna()
{
	if(localDasd["AzSensor1"] == ELEM_AVAR && drives["servo"] == ELEM_NORMA)
		bAntenna["az_sensor1"] = ELEM_AVAR;
	else if(localDasd["AzSensor1"] == ELEM_NORMA && drives["servo"] == ELEM_NORMA)
		bAntenna["az_sensor1"] = ELEM_NORMA;
	else
		bAntenna["az_sensor1"] = ELEM_NOT;

	if(localDasd["AzSensor2"] == ELEM_AVAR && drives["servo"] == ELEM_NORMA)
		bAntenna["az_sensor2"] = ELEM_AVAR;
	else if(localDasd["AzSensor2"] == ELEM_NORMA && drives["servo"] == ELEM_NORMA)
		bAntenna["az_sensor2"] = ELEM_NORMA;
	else
		bAntenna["az_sensor2"] = ELEM_NOT;

	if(m_isMain)
	{
//		elements["base@az_sensor1"] = bAntenna["az_sensor1"].toString();
//		elements["base@az_sensor2"] = bAntenna["az_sensor2"].toString();
//		elements["ant@az_sensor1"] = bAntenna["az_sensor1"].toString();
//		elements["ant@az_sensor2"] = bAntenna["az_sensor2"].toString();

		elements["ant@124sg01_1"] = drives["124sg01_1"].toString() + drives["drive1@mest"].toStringMest();
		elements["ant@124sg01_2"] = drives["124sg01_2"].toString() + drives["drive2@mest"].toStringMest();

		elements["base@antenna"] = drives["125sg02"].toString() + drives["mest"].toStringMest();

//		messages["AzSensor1"] = bAntenna["az_sensor1"];
//		messages["AzSensor2"] = bAntenna["az_sensor2"];
	}

	double p = 0;
	if(m_setup.module.lastMode == 1)
		p = m_setup.drive.speed2;
	else
		p = m_setup.drive.speed1;

	if(p != 0) 
		p = 360.0 / p;

	if(drives["servo"] == ELEM_NORMA && /*localDasd["periodValid"] == ELEM_NORMA &&*/
		((localDasd["AzSensor1"] == ELEM_NORMA && localDasd["AzSensorMain"] == 1) ||
		(localDasd["AzSensor2"] == ELEM_NORMA && localDasd["AzSensorMain"] == 2)))
	{
		double value = valLocalPeriod["period"].toDouble();
		if(value < (p - 0.2) || value > (p + 0.2))
			bAntenna["period"] = ELEM_AVAR;
		else if(value < (p - 0.1) || value > (p + 0.1))
			bAntenna["period"] = ELEM_ERROR;
		else
			bAntenna["period"] = ELEM_NORMA;
	}
	else
		bAntenna["period"] = ELEM_NOT;

//period
	if(m_isMain)
	{
		bAntenna["setperiod"] = ELEM_DISABLE;
		elements["base@setperiod"] = bAntenna["setperiod"].toString();

		if(p != 0)
			elements["base@setperiod"].setText(QString("%1±0.1").arg(p, 0, 'f', 1));
		else
			elements["base@setperiod"].setText("---");

		elements["base@period"] = bAntenna["period"].toString();
		if(bAntenna["period"] == ELEM_NOT)
		{
			elements["base@period"].setText("...");
		}
		else
		{
			double value = valLocalPeriod["period"].toDouble();
			elements["base@period"].setText(QString::number(value,'f',1));
		}
		messages["base@period"] = bAntenna["period"];
	}
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::fun124YY03_raf()
{
	b124yy03["mest"] = drives["mest"];

	if(b124ee02["qf_124yy03_1"] == ELEM_AVAR)
		b124yy03["124yy03_1"] = ELEM_NOT;
	else
		b124yy03["124yy03_1"] = drives["124yy03_1"];

	if(b124ee02["qf_124yy03_1"] == ELEM_AVAR)
		b124yy03["124yy03_2"] = ELEM_NOT;
	else
		b124yy03["124yy03_2"] = drives["124yy03_2"];

	if(b124yy03["124yy03_1"] == ELEM_NOT && b124yy03["124yy03_2"] == ELEM_NOT)
		b124yy03["ObSost"] = ELEM_NOT;
	else if(b124yy03["124yy03_1"] == ELEM_AVAR && b124yy03["124yy03_2"] == ELEM_AVAR)
		b124yy03["ObSost"] = ELEM_AVAR;
	else if(b124yy03["124yy03_1"] == ELEM_AVAR || b124yy03["124yy03_2"] == ELEM_AVAR ||
			b124yy03["124yy03_1"] == ELEM_ERROR || b124yy03["124yy03_2"] == ELEM_ERROR)
		b124yy03["ObSost"] = ELEM_ERROR;
	else if(b124yy03["124yy03_1"] == ELEM_NORMA || b124yy03["124yy03_2"] == ELEM_NORMA)
		b124yy03["ObSost"] = ELEM_NORMA;
	else
		b124yy03["ObSost"] = ELEM_NOT;

	elements["elk@124yy03"] = b124yy03["ObSost"].toString() + b124yy03["mest"].toStringMest();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::fun124YY08_raf()
{
//МЕСТ
/*	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && sigmap["elk_mest"])
		b124yy08["mest"] = ELEM_MEST;
	else
		b124yy08["mest"] = ELEM_NOT;*/
	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && sigmap["elk_mest"])
		b124yy08["mest"] = ELEM_MEST;
	else if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && !sigmap["elk_mest"])
		b124yy08["mest"] = ELEM_NORMA;
	else
		b124yy08["mest"] = ELEM_NOT;
	messages["124yy08@mest"] = b124yy08["mest"];

//МЕСТ РГДВ
	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && sigmap["elk_mest"])
	{
		elementsRgdv["124yy08_mest"] = ELEM_MEST;
		elementsRgdv["124yy08_mest"] = "МЕСТ";
	}
	else if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && !sigmap["elk_mest"])
	{
		elementsRgdv["124yy08_mest"] = ELEM_NORMA;
		elementsRgdv["124yy08_mest"] = "ОТКЛ";
	}
	else
	{
		elementsRgdv["124yy08_mest"] = ELEM_DISABLE;
		elementsRgdv["124yy08_mest"] = "НЕ КОНТР";
	}

//Д2ВВ056
	if(canalAsku["OY1"] == ELEM_AVAR)
	{
		b124yy08["d2vv056"] = ELEM_AVAR;

		elementsRgdv["124yy08_ou"] = b124yy08["d2vv056"];
		elementsRgdv["124yy08_ou"] = "АВАРИЯ";
	}
	else if(canalAsku["OY1"] == ELEM_NORMA)
	{
		b124yy08["d2vv056"] = ELEM_NORMA;

		elementsRgdv["124yy08_ou"] = b124yy08["d2vv056"];
		elementsRgdv["124yy08_ou"] = "НОРМА";
	}
	else
	{
		b124yy08["d2vv056"] = ELEM_NOT;

		elementsRgdv["124yy08_ou"] = b124yy08["d2vv056"];
		elementsRgdv["124yy08_ou"] = "ОТКЛ";
	}
	messages["124yy08@d2vv056"] = b124yy08["d2vv056"];

//123УУ01
	if(canalAsku["OY1_OS_TEST2"] == ELEM_NORMA && sigmap["elk_avarBPU"])
		b124yy08["123yy01"] = ELEM_AVAR;
	else if(canalAsku["OY1_OS_TEST2"] == ELEM_NORMA && !sigmap["elk_avarBPU"])
		b124yy08["123yy01"] = ELEM_NORMA;
	else
		b124yy08["123yy01"] = ELEM_NOT;
	messages["124yy08@123yy01"] = b124yy08["123yy01"];

//Общее состояние
	if(b124yy08["d2vv056"] == ELEM_AVAR)
		b124yy08["obSost"] = ELEM_AVAR;
	else if(b124yy08["123yy01"] == ELEM_AVAR)
		b124yy08["obSost"] = ELEM_ERROR;
	else if(b124yy08["d2vv056"] == ELEM_NORMA)
		b124yy08["obSost"] = ELEM_NORMA;
	else
		b124yy08["obSost"] = ELEM_NOT;

	elements["elk_block@d2vv056"] = b124yy08["d2vv056"].toString() + b124yy08["mest"].toStringMest();
	elements["elk_block@123yy01"] = b124yy08["123yy01"].toString() + b124yy08["mest"].toStringMest();

	elements["elk@124yy08"] = b124yy08["obSost"].toString() + b124yy08["mest"].toStringMest();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::checkReserveBep()
{
//	LogInfo("ASKU::checkReserveBep");
/*
	if(m_isMain && drives["mest"] != ELEM_NORMA && drives["cmdServoOn"] == ELEM_NORMA &&
		b124yy03["drive_overheat"] != ELEM_AVAR && b124yy03["block_opu"] != ELEM_AVAR)
	{
//		LogInfo("ASKU::checkReserveBep 1");

		if(b124yy03["drive_2_on"] == ELEM_ISPR)
		{
//			LogInfo("ASKU::checkReserveBep 2");

			if(drives["cmdServoOn"] == ELEM_NORMA && 
				((drives["drive1@Fail"] == ELEM_AVAR || drives["drive1@Ready"] == ELEM_ERROR || drives["drive1@Ready"] == ELEM_AVAR) || b124yy03["124yy03_1"] == ELEM_AVAR) &&
				drives["drive2@Fail"] == ELEM_NORMA && drives["drive2@Ready"] == ELEM_NORMA && b124yy03["124yy03_2"] == ELEM_NORMA)	// drive 1 fail & 2 ok
			{
//				LogInfo("ASKU::checkReserveBep 3");
				emit cmdSetBep2On(false, true);
				m_timerBep->stop();
				m_timerBep->start(20000);
				return;
			}
		}
		else if(b124yy03["drive_2_on"] == ELEM_NORMA)
		{
//			LogInfo("ASKU::checkReserveBep 5");

			if(drives["cmdServoOn"] == ELEM_NORMA && 
				((drives["drive2@Fail"] == ELEM_AVAR || drives["drive2@Ready"] == ELEM_ERROR || drives["drive2@Ready"] == ELEM_AVAR) || b124yy03["124yy03_2"] == ELEM_AVAR) &&
				drives["drive1@Fail"] == ELEM_NORMA && drives["drive1@Ready"] == ELEM_NORMA && b124yy03["124yy03_1"] == ELEM_NORMA)	// drive 2 fail & 1 ok
			{
				LogInfo("ASKU::checkReserveBep 6");
				emit cmdSetBep1On(false, true);
				m_timerBep->stop();
				m_timerBep->start(20000);
				return;
			}
		}
	}
	if(m_isMain && drives["mest"] != ELEM_NORMA && 
		(drives["drive1@Fail"] == ELEM_AVAR || drives["drive1@Ready"] == ELEM_ERROR || drives["drive1@Ready"] == ELEM_AVAR || b124yy03["124yy03_1"] == ELEM_AVAR ||
		drives["drive2@Fail"] == ELEM_AVAR || drives["drive2@Ready"] == ELEM_ERROR || drives["drive2@Ready"] == ELEM_AVAR || b124yy03["124yy03_2"] == ELEM_AVAR))
	{
		if(resetAvarCounter < 3)
		{
//			LogInfo("ASKU::checkReserveBep 9");

			emit cmdSetResetAvarBep();
			m_timerBep->stop();
			m_timerBep->start(10000);
			resetAvarCounter++;
			return;
		}
	}

	if(m_timerBep->interval() != 1000)
	{
//		LogInfo("ASKU::checkReserveBep 8");
		m_timerBep->stop();
		m_timerBep->start(1000);
//		resetAvarCounter = 0;
	}
*/
}

// ----------------------------------------------------------------------------
