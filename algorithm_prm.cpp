#include "../common/logger.h"
#include "globalvar.h"
#include "algorithm.h"
#include "canalasku_data.h"

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPrmLocal()
{
	if(localDasd["DASD"] == ELEM_NOT || localDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_zu1"] != ELEM_NORMA)
		localPrm["124vp02_1"] = ELEM_NOT;
	else if(localDasd["ZU_S"] == ELEM_AVAR)
		localPrm["124vp02_1"] = ELEM_AVAR;
	else
		localPrm["124vp02_1"] = ELEM_NORMA;
	messages["prm@124vp02_1"] = localPrm["124vp02_1"];

	if(localDasd["DASD"] == ELEM_NOT || localDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_zu2"] != ELEM_NORMA)
		localPrm["124vp02_2"] = ELEM_NOT;
	else if(localDasd["ZU_D"] == ELEM_AVAR)
		localPrm["124vp02_2"] = ELEM_AVAR;
	else
		localPrm["124vp02_2"] = ELEM_NORMA;
	messages["prm@124vp02_2"] = localPrm["124vp02_2"];

	if(localDasd["DASD"] == ELEM_NOT || localDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_zu1"] != ELEM_NORMA)
		localPrm["d2ht502_1"] = ELEM_NOT;
	else if(localDasd["ZU_S_CTRL"] == ELEM_AVAR)
		localPrm["d2ht502_1"] = ELEM_AVAR;
	else
		localPrm["d2ht502_1"] = ELEM_NORMA;
	messages["prm@d2ht502_1"] = localPrm["d2ht502_1"];
	
	if(localDasd["DASD"] == ELEM_NOT || localDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_zu2"] != ELEM_NORMA)
		localPrm["d2ht502_2"] = ELEM_NOT;
	else if(localDasd["ZU_D_CTRL"] == ELEM_AVAR)
		localPrm["d2ht502_2"] = ELEM_AVAR;
	else
		localPrm["d2ht502_2"] = ELEM_NORMA;
	messages["prm@d2ht502_2"] = localPrm["d2ht502_2"];

	if(localDasd["DASD"] == ELEM_NOT || localDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_gsh"] != ELEM_NORMA)
		localPrm["d2en429"] = ELEM_NOT;
	else if(localDasd["GSH"] == ELEM_AVAR)
		localPrm["d2en429"] = ELEM_AVAR;
	else
		localPrm["d2en429"] = ELEM_NORMA;
	messages["prm@d2en429"] = localPrm["d2en429"];

	if(localDasd["DASD"] == ELEM_NOT || localDasd["DASD"] == ELEM_AVAR)
		localPrm["switch_s"] = ELEM_NOT;
	else if(localDasd["SWITCH_S"] == ELEM_AVAR)
		localPrm["switch_s"] = ELEM_AVAR;
	else
		localPrm["switch_s"] = ELEM_NORMA;
	messages["prm@switch_s"] = localPrm["switch_s"];

	if(localDasd["DASD"] == ELEM_NOT || localDasd["DASD"] == ELEM_AVAR)
		localPrm["switch_d"] = ELEM_NOT;
	else if(localDasd["SWITCH_D"] == ELEM_AVAR)
		localPrm["switch_d"] = ELEM_AVAR;
	else
		localPrm["switch_d"] = ELEM_NORMA;
	messages["prm@switch_d"] = localPrm["switch_d"];

	if(ISGPR1() && b124ee02["p27v_prm1"] != ELEM_NORMA)
		localPrm["124pp03"] = ELEM_NOT;
	else if(ISGPR2() && b124ee02["p27v_prm2"] != ELEM_NORMA)
		localPrm["124pp03"] = ELEM_NOT;
	else if(localKoeff["ObSostKoeff"] == ELEM_NOT && localKoeff["ObSostPilot"] == ELEM_NOT)
		localPrm["124pp03"] = ELEM_NOT;
	else if(localKoeff["ObSostKoeff"] == ELEM_AVAR || localKoeff["ObSostPilot"] == ELEM_AVAR)
		localPrm["124pp03"] = ELEM_AVAR;
	else if(localKoeff["ObSostKoeff"] == ELEM_ERROR || localKoeff["ObSostPilot"] == ELEM_ERROR)
		localPrm["124pp03"] = ELEM_ERROR;
	else
		localPrm["124pp03"] = ELEM_NORMA;

	if(localPrm["124vp02_1"] == ELEM_NOT && localPrm["124vp02_2"] == ELEM_NOT &&
		localPrm["d2ht502_1"] == ELEM_NOT && localPrm["d2ht502_2"] == ELEM_NOT &&
		localPrm["switch_s"] == ELEM_NOT && localPrm["switch_d"] == ELEM_NOT)
		localPrm["ObSost"] = ELEM_NOT;
	else if(localPrm["124vp02_1"] == ELEM_AVAR || localPrm["124vp02_2"] == ELEM_AVAR ||
		localPrm["d2ht502_1"] == ELEM_AVAR || localPrm["d2ht502_2"] == ELEM_AVAR ||
		localPrm["124pp03"] == ELEM_AVAR || localPrm["d2en429"] == ELEM_AVAR ||
		localPrm["switch_s"] == ELEM_AVAR || localPrm["switch_d"] == ELEM_AVAR)
		localPrm["ObSost"] = ELEM_AVAR;
	else if(localPrm["124pp03"] == ELEM_ERROR)
		localPrm["ObSost"] = ELEM_ERROR;
	else if(localPrm["124pp03"] == ELEM_NORMA && m_isMain)
		localPrm["ObSost"] = ELEM_NORMA;
	else
		localPrm["ObSost"] = ELEM_NOT;

//	qDebug() << "localPrm:" << localPrm.dump();

	elements["prmsys@124vp02_1"] = localPrm["124vp02_1"].toString();
	elements["prmsys@124vp02_2"] = localPrm["124vp02_2"].toString();

	elements["prmsys@d2ht502_1"] = localPrm["d2ht502_1"].toString();
	elements["prmsys@d2ht502_2"] = localPrm["d2ht502_2"].toString();

	elements["prm@d2en429"] = localPrm["d2en429"].toString();

	elements["prm@switch_s"] = localPrm["switch_s"].toString();
	elements["prm@switch_d"] = localPrm["switch_d"].toString();

	elements["base@svch_prm_sum"] = localPrm["switch_s"].toString();
	elements["base@svch_prm_dif"] = localPrm["switch_d"].toString();

	elements[QString("base@prm%1").arg(IDGPR() + 1)] = localPrm["ObSost"].toString();

	qDebug() << "otherPrm: pp03=" << otherPrm["124pp03"].toString() << "obsost=" << otherPrm["ObSost"].toString();

}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPrmOther()
{
	if(otherDasd["DASD"] == ELEM_NOT || otherDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_zu1"] != ELEM_NORMA)
		otherPrm["124vp02_1"] = ELEM_NOT;
	else if(otherDasd["ZU_S"] == ELEM_AVAR)
		otherPrm["124vp02_1"] = ELEM_AVAR;
	else
		otherPrm["124vp02_1"] = ELEM_NORMA;
//	messages["prm@124vp02_1"] = otherPrm["124vp02_1"];

	if(otherDasd["DASD"] == ELEM_NOT || otherDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_zu2"] != ELEM_NORMA)
		otherPrm["124vp02_2"] = ELEM_NOT;
	else if(otherDasd["ZU_D"] == ELEM_AVAR)
		otherPrm["124vp02_2"] = ELEM_AVAR;
	else
		otherPrm["124vp02_2"] = ELEM_NORMA;
//	messages["prm@124vp02_2"] = otherPrm["124vp02_2"];

	if(otherDasd["DASD"] == ELEM_NOT || otherDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_zu1"] != ELEM_NORMA)
		otherPrm["d2ht502_1"] = ELEM_NOT;
	else if(otherDasd["ZU_S_CTRL"] == ELEM_AVAR)
		otherPrm["d2ht502_1"] = ELEM_AVAR;
	else
		otherPrm["d2ht502_1"] = ELEM_NORMA;
//	messages["prm@d2ht502_1"] = otherPrm["d2ht502_1"];
	
	if(otherDasd["DASD"] == ELEM_NOT || otherDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_zu2"] != ELEM_NORMA)
		otherPrm["d2ht502_2"] = ELEM_NOT;
	else if(otherDasd["ZU_D_CTRL"] == ELEM_AVAR)
		otherPrm["d2ht502_2"] = ELEM_AVAR;
	else
		otherPrm["d2ht502_2"] = ELEM_NORMA;
//	messages["prm@d2ht502_2"] = otherPrm["d2ht502_2"];

	if(otherDasd["DASD"] == ELEM_NOT || otherDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_gsh"] != ELEM_NORMA)
		otherPrm["d2en429"] = ELEM_NOT;
	else if(otherDasd["GSH"] == ELEM_AVAR)
		otherPrm["d2en429"] = ELEM_AVAR;
	else
		otherPrm["d2en429"] = ELEM_NORMA;
//	messages["prm@d2en429"] = otherPrm["d2en429"];


	if(otherDasd["DASD"] == ELEM_NOT || otherDasd["DASD"] == ELEM_AVAR || b124ee02["p27v_gsh"] != ELEM_NORMA)
		otherPrm["d2en429"] = ELEM_NOT;
	else if(otherDasd["GSH"] == ELEM_AVAR)
		otherPrm["d2en429"] = ELEM_AVAR;
	else
		otherPrm["d2en429"] = ELEM_NORMA;
//	messages["prm@d2en429"] = otherPrm["d2en429"];

	if(otherDasd["DASD"] == ELEM_NOT || otherDasd["DASD"] == ELEM_AVAR)
		otherPrm["switch_s"] = ELEM_NOT;
	else if(otherDasd["SWITCH_S"] == ELEM_AVAR)
		otherPrm["switch_s"] = ELEM_AVAR;
	else
		otherPrm["switch_s"] = ELEM_NORMA;
//	messages["prm@switch_s"] = otherPrm["switch_s"];

	if(otherDasd["DASD"] == ELEM_NOT || otherDasd["DASD"] == ELEM_AVAR)
		otherPrm["switch_d"] = ELEM_NOT;
	else if(otherDasd["SWITCH_D"] == ELEM_AVAR)
		otherPrm["switch_d"] = ELEM_AVAR;
	else
		otherPrm["switch_d"] = ELEM_NORMA;
//	messages["prm@switch_d"] = otherPrm["switch_d"];

	if(!m_isWorkGpr || (ISGPR1() && b124ee02["p27v_prm1"] != ELEM_NORMA))
		otherPrm["124pp03"] = ELEM_NOT;
	else if(!m_isWorkGpr || (ISGPR2() && b124ee02["p27v_prm2"] != ELEM_NORMA))
		otherPrm["124pp03"] = ELEM_NOT;
	else if(otherKoeff["ObSostKoeff"] == ELEM_NOT && otherKoeff["ObSostPilot"] == ELEM_NOT)
		otherPrm["124pp03"] = ELEM_NOT;
	else if(otherKoeff["ObSostKoeff"] == ELEM_AVAR || otherKoeff["ObSostPilot"] == ELEM_AVAR)
		otherPrm["124pp03"] = ELEM_AVAR;
	else if(otherKoeff["ObSostKoeff"] == ELEM_ERROR || otherKoeff["ObSostPilot"] == ELEM_ERROR)
		otherPrm["124pp03"] = ELEM_ERROR;
	else
		otherPrm["124pp03"] = ELEM_NORMA;


	if(!m_isWorkGpr || (otherPrm["124vp02_1"] == ELEM_NOT && otherPrm["124vp02_2"] == ELEM_NOT &&
		otherPrm["d2ht502_1"] == ELEM_NOT && otherPrm["d2ht502_2"] == ELEM_NOT &&
		otherPrm["switch_s"] == ELEM_NOT && otherPrm["switch_d"] == ELEM_NOT))
		otherPrm["ObSost"] = ELEM_NOT;
	else if(otherPrm["124vp02_1"] == ELEM_AVAR || otherPrm["124vp02_2"] == ELEM_AVAR ||
		otherPrm["d2ht502_1"] == ELEM_AVAR || otherPrm["d2ht502_2"] == ELEM_AVAR ||
		otherPrm["124pp03"] == ELEM_AVAR || otherPrm["d2en429"] == ELEM_AVAR ||
		otherPrm["switch_s"] == ELEM_AVAR || otherPrm["switch_d"] == ELEM_AVAR)
		otherPrm["ObSost"] = ELEM_AVAR;
	else if(otherPrm["124pp03"] == ELEM_ERROR)
		otherPrm["ObSost"] = ELEM_ERROR;
	else if(otherPrm["124pp03"] == ELEM_NORMA && !m_isMain)
		otherPrm["ObSost"] = ELEM_NORMA;
	else
		otherPrm["ObSost"] = ELEM_NOT;

//	qDebug() << "otherPrm:" << otherPrm.dump();

//	elements["prmsys@124vp02_1"] = otherPrm["124vp02_1"].toString();
//	elements["prmsys@124vp02_2"] = otherPrm["124vp02_2"].toString();
//	elements["prmsys@d2ht502_1"] = otherPrm["d2ht502_1"].toString();
//	elements["prmsys@d2ht502_2"] = otherPrm["d2ht502_2"].toString();

	elements[QString("base@prm%1").arg(OTHER_GPR_ID() + 1)] = otherPrm["ObSost"].toString();

	qDebug() << "otherPrm: pp03=" << otherPrm["124pp03"].toString() << "obsost=" << otherPrm["ObSost"].toString();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::fun124PP04_raf()
{
	if(localPrm["124pp03"] == ELEM_NOT && otherPrm["124pp03"] == ELEM_NOT)
		localPrm["124PP04"] = ELEM_NOT;
	else if(localPrm["d2en429"] == ELEM_AVAR || 
			localPrm["switch_s"] == ELEM_AVAR || localPrm["switch_d"] == ELEM_AVAR ||
			(localPrm["124pp03"] == ELEM_AVAR && otherPrm["124pp03"] == ELEM_AVAR) ||
			(localPrm["124pp03"] == ELEM_NOT  && otherPrm["124pp03"] == ELEM_AVAR) ||
			(localPrm["124pp03"] == ELEM_AVAR && otherPrm["124pp03"] == ELEM_NOT))
		localPrm["124PP04"] = ELEM_AVAR;
	else if(localPrm["124pp03"] == ELEM_ERROR || otherPrm["124pp03"] == ELEM_ERROR)
		localPrm["124PP04"] = ELEM_ERROR;
	else
		localPrm["124PP04"] = ELEM_NORMA;

	if(ISGPR1())
	{
		elements["prm@124pp03_1"] = localPrm["124pp03"].toString();
		messages["prm@124pp03_1"] = localPrm["124pp03"];

		elements["prm@124pp03_2"] = otherPrm["124pp03"].toString();
		messages["prm@124pp03_2"] = otherPrm["124pp03"];
	}
	if(ISGPR2())
	{
		elements["prm@124pp03_2"] = localPrm["124pp03"].toString();
		messages["prm@124pp03_2"] = localPrm["124pp03"];

		elements["prm@124pp03_1"] = otherPrm["124pp03"].toString();
		messages["prm@124pp03_1"] = otherPrm["124pp03"];
	}

	elements["prmsys@124pp04"] = localPrm["124PP04"].toString();
	elements["zal@124pp04"] = localPrm["124PP04"].toString();
}

// ----------------------------------------------------------------------------
