#include "../common/logger.h"
#include "globalvar.h"
#include "algorithm.h"
#include "canalasku_data.h"
#include "canalasku.h"
#include "viewer.h"

// ----------------------------------------------------------------------------
void AskuAlgorithm::fun124YG02_raf()
{
//МЕСТ 1
/*	if(canalAsku["OY2_OS_STATE"] == ELEM_NORMA && sigmap["prd1_mest"])
		b124yg02["mest1"] = ELEM_MEST;
	else
		b124yg02["mest1"] = ELEM_NOT;*/
	if(canalAsku["OY2_OS_STATE"] == ELEM_NORMA && sigmap["prd1_mest"])
		b124yg02["mest1"] = ELEM_MEST;
	else if(canalAsku["OY2_OS_STATE"] == ELEM_NORMA && !sigmap["prd1_mest"])
		b124yg02["mest1"] = ELEM_NORMA;
	else
		b124yg02["mest1"] = ELEM_NOT;
	messages["124yg02@mest1"] = b124yg02["mest1"];

//МЕСТ 1 РГДВ
	if(canalAsku["OY2_OS_STATE"] == ELEM_NORMA && sigmap["prd1_mest"])
	{
		elementsRgdv["124yg02_1_mest"] = ELEM_MEST;
		elementsRgdv["124yg02_1_mest"] = "МЕСТ";
	}
	else if(canalAsku["OY2_OS_STATE"] == ELEM_NORMA && !sigmap["prd1_mest"])
	{
		elementsRgdv["124yg02_1_mest"] = ELEM_NORMA;
		elementsRgdv["124yg02_1_mest"] = "ОТКЛ";
	}
	else
	{
		elementsRgdv["124yg02_1_mest"] = ELEM_DISABLE;
		elementsRgdv["124yg02_1_mest"] = "НЕ КОНТР";
	}

//МЕСТ 2
/*	if(canalAsku["OY3_OS_STATE"] == ELEM_NORMA && sigmap["prd2_mest"])
		b124yg02["mest2"] = ELEM_MEST;
	else
		b124yg02["mest2"] = ELEM_NOT;*/
	if(canalAsku["OY3_OS_STATE"] == ELEM_NORMA && sigmap["prd2_mest"])
		b124yg02["mest2"] = ELEM_MEST;
	else if(canalAsku["OY3_OS_STATE"] == ELEM_NORMA && !sigmap["prd2_mest"])
		b124yg02["mest2"] = ELEM_NORMA;
	else
		b124yg02["mest2"] = ELEM_NOT;
	messages["124yg02@mest2"] = b124yg02["mest2"];

//МЕСТ 2 РГДВ
	if(canalAsku["OY3_OS_STATE"] == ELEM_NORMA && sigmap["prd2_mest"])
	{
		elementsRgdv["124yg02_2_mest"] = ELEM_MEST;
		elementsRgdv["124yg02_2_mest"] = "МЕСТ";
	}
	else if(canalAsku["OY3_OS_STATE"] == ELEM_NORMA && !sigmap["prd2_mest"])
	{
		elementsRgdv["124yg02_2_mest"] = ELEM_NORMA;
		elementsRgdv["124yg02_2_mest"] = "ОТКЛ";
	}
	else
	{
		elementsRgdv["124yg02_2_mest"] = ELEM_DISABLE;
		elementsRgdv["124yg02_2_mest"] = "НЕ КОНТР";
	}

//МЕСТ
	if(b124yg02["mest1"] == ELEM_MEST || b124yg02["mest2"] == ELEM_MEST)
		b124yg02["mest"] = ELEM_MEST;
	else
		b124yg02["mest"] = ELEM_NOT;

//Д2ВВ056(1)
	if(canalAsku["OY2"] == ELEM_AVAR)
	{
		b124yg02["d2vv056_1"] = ELEM_AVAR;

		elementsRgdv["124yg02_1_ou"] = b124yg02["d2vv056_1"];
		elementsRgdv["124yg02_1_ou"] = "АВАРИЯ";
	}
	else if(canalAsku["OY2"] == ELEM_NORMA)
	{
		b124yg02["d2vv056_1"] = ELEM_NORMA;

		elementsRgdv["124yg02_1_ou"] = b124yg02["d2vv056_1"];
		elementsRgdv["124yg02_1_ou"] = "НОРМА";
	}
	else
	{
		b124yg02["d2vv056_1"] = ELEM_NOT;

		elementsRgdv["124yg02_1_ou"] = b124yg02["d2vv056_1"];
		elementsRgdv["124yg02_1_ou"] = "ОТКЛ";
	}
	messages["124yg02@d2vv056_1"] = b124yg02["d2vv056_1"];

//Д2ВВ056(2)
	if(canalAsku["OY3"] == ELEM_AVAR)
	{
		b124yg02["d2vv056_2"] = ELEM_AVAR;

		elementsRgdv["124yg02_2_ou"] = b124yg02["d2vv056_1"];
		elementsRgdv["124yg02_2_ou"] = "АВАРИЯ";
	}
	else if(canalAsku["OY3"] == ELEM_NORMA)
	{
		b124yg02["d2vv056_2"] = ELEM_NORMA;

		elementsRgdv["124yg02_2_ou"] = b124yg02["d2vv056_1"];
		elementsRgdv["124yg02_2_ou"] = "НОРМА";
	}
	else
	{
		b124yg02["d2vv056_2"] = ELEM_NOT;

		elementsRgdv["124yg02_2_ou"] = b124yg02["d2vv056_1"];
		elementsRgdv["124yg02_2_ou"] = "ОТКЛ";
	}
	messages["124yg02@d2vv056_2"] = b124yg02["d2vv056_2"];

//123УУ01
	if((canalAsku["OY2_OS_TEST2"] == ELEM_NORMA && sigmap["prd1_avarBPU"]) || (canalAsku["OY3_OS_TEST2"] == ELEM_NORMA && sigmap["prd2_avarBPU"]))
		b124yg02["123yy01"] = ELEM_AVAR;
	else if((canalAsku["OY2_OS_TEST2"] == ELEM_NORMA && !sigmap["prd1_avarBPU"]) || (canalAsku["OY3_OS_TEST2"] == ELEM_NORMA && !sigmap["prd2_avarBPU"]))
		b124yg02["123yy01"] = ELEM_NORMA;
	else
		b124yg02["123yy01"] = ELEM_NOT;
	messages["124yg02@123yy01"] = b124yg02["123yy01"];

//Общее состояние
	if(b124yg02["d2vv056_1"] == ELEM_AVAR && b124yg02["d2vv056_2"] == ELEM_AVAR)
		b124yg02["obSost"] = ELEM_AVAR;
	else if(b124yg02["d2vv056_1"] == ELEM_AVAR || b124yg02["d2vv056_2"] == ELEM_AVAR || b124yg02["123yy01"] == ELEM_AVAR)
		b124yg02["obSost"] = ELEM_ERROR;
	else if(b124yg02["d2vv056_1"] == ELEM_NORMA || b124yg02["d2vv056_2"] == ELEM_NORMA)
		b124yg02["obSost"] = ELEM_NORMA;
	else
		b124yg02["obSost"] = ELEM_NOT;

	elements["prd_control_block@d2vv056_1"] = b124yg02["d2vv056_1"].toString() + b124yg02["mest1"].toStringMest();
	elements["prd_control_block@d2vv056_2"] = b124yg02["d2vv056_2"].toString() + b124yg02["mest2"].toStringMest();
	elements["prd_control_block@123yy01"] = b124yg02["123yy01"].toString() + b124yg02["mest"].toStringMest();
	elements["prd_control@124yg02"] = b124yg02["obSost"].toString() + b124yg02["mest"].toStringMest();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPanelAvt_raf()
{
	int nAvar = 0, nError = 0;

//ОК 1
	if(canalAsku["OY2_OS_STATE"] == ELEM_NORMA && b124yg02["d2vv056_1"] == ELEM_NORMA)
		bPanelAvt["isOk1"] = ELEM_NORMA;
	else
		bPanelAvt["isOk1"] = ELEM_NOT;

//ОК 2
	if(canalAsku["OY3_OS_STATE"] == ELEM_NORMA && b124yg02["d2vv056_2"] == ELEM_NORMA)
		bPanelAvt["isOk2"] = ELEM_NORMA;
	else
		bPanelAvt["isOk2"] = ELEM_NOT;

//OK
	if(bPanelAvt["isOk1"] == ELEM_NORMA || bPanelAvt["isOk2"] == ELEM_NORMA)
		bPanelAvt["isOk"] = ELEM_NORMA;
	else
		bPanelAvt["isOk"] = ELEM_NOT;

//Check off
//		b124ee02["aorls"] = ELEM_AVAR;
//		b124ee02["otkl_cont_380v"] = ELEM_AVAR;

//QF 123ГВ02-1
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qf123gv02"])
	{
		bPanelAvt["qf_123gv02_1"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qf123gv02"])
		bPanelAvt["qf_123gv02_1"] = ELEM_NORMA;
	else
		bPanelAvt["qf_123gv02_1"] = ELEM_NOT;
	messages["prd_control_panel@qf_123gv02_1"] = bPanelAvt["qf_123gv02_1"];

//QF 123ГВ02-1 (РГДВ)
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qf123gv02"])
	{
		elementsRgdv["124yg02_1_qf_123gv02_1"] = ELEM_AVAR;
		elementsRgdv["124yg02_1_qf_123gv02_1"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qf123gv02"])
	{
		elementsRgdv["124yg02_1_qf_123gv02_1"] = ELEM_NORMA;
		elementsRgdv["124yg02_1_qf_123gv02_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_1_qf_123gv02_1"] = ELEM_DISABLE;
		elementsRgdv["124yg02_1_qf_123gv02_1"] = "НЕ КОНТР";
	}

//QF 123ГВ02-2
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qf123gv02"])
	{
		bPanelAvt["qf_123gv02_2"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qf123gv02"])
		bPanelAvt["qf_123gv02_2"] = ELEM_NORMA;
	else
		bPanelAvt["qf_123gv02_2"] = ELEM_NOT;
	messages["prd_control_panel@qf_123gv02_2"] = bPanelAvt["qf_123gv02_2"];

//QF 123ГВ02-2 (РГДВ)
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qf123gv02"])
	{
		elementsRgdv["124yg02_2_qf_123gv02_2"] = ELEM_AVAR;
		elementsRgdv["124yg02_2_qf_123gv02_2"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qf123gv02"])
	{
		elementsRgdv["124yg02_2_qf_123gv02_2"] = ELEM_NORMA;
		elementsRgdv["124yg02_2_qf_123gv02_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_2_qf_123gv02_2"] = ELEM_DISABLE;
		elementsRgdv["124yg02_2_qf_123gv02_2"] = "НЕ КОНТР";
	}

//QF 123ББ01-1
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qf123bb01_1"])
	{
		bPanelAvt["qf_123bb01_1"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qf123bb01_1"])
		bPanelAvt["qf_123bb01_1"] = ELEM_NORMA;
	else
		bPanelAvt["qf_123bb01_1"] = ELEM_NOT;
	messages["prd_control_panel@qf_123bb01_1"] = bPanelAvt["qf_123bb01_1"];

//QF 123ББ01-1 (РГДВ)
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qf123bb01_1"])
	{
		elementsRgdv["124yg02_1_qf_123bb01_1"] = ELEM_AVAR;
		elementsRgdv["124yg02_1_qf_123bb01_1"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qf123bb01_1"])
	{
		elementsRgdv["124yg02_1_qf_123bb01_1"] = ELEM_NORMA;
		elementsRgdv["124yg02_1_qf_123bb01_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_1_qf_123bb01_1"] = ELEM_DISABLE;
		elementsRgdv["124yg02_1_qf_123bb01_1"] = "НЕ КОНТР";
	}

//QF 123ББ01-2
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qf123bb01_2"])
	{
		bPanelAvt["qf_123bb01_2"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qf123bb01_2"])
		bPanelAvt["qf_123bb01_2"] = ELEM_NORMA;
	else
		bPanelAvt["qf_123bb01_2"] = ELEM_NOT;
	messages["prd_control_panel@qf_123bb01_2"] = bPanelAvt["qf_123bb01_2"];

//QF 123ББ01-2 (РГДВ)
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qf123bb01_2"])
	{
		elementsRgdv["124yg02_1_qf_123bb01_2"] = ELEM_AVAR;
		elementsRgdv["124yg02_1_qf_123bb01_2"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qf123bb01_2"])
	{
		elementsRgdv["124yg02_1_qf_123bb01_2"] = ELEM_NORMA;
		elementsRgdv["124yg02_1_qf_123bb01_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_1_qf_123bb01_2"] = ELEM_DISABLE;
		elementsRgdv["124yg02_1_qf_123bb01_2"] = "НЕ КОНТР";
	}

//QF 123ББ01-3
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qf123bb01_1"])
	{
		bPanelAvt["qf_123bb01_3"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qf123bb01_1"])
		bPanelAvt["qf_123bb01_3"] = ELEM_NORMA;
	else
		bPanelAvt["qf_123bb01_3"] = ELEM_NOT;
	messages["prd_control_panel@qf_123bb01_3"] = bPanelAvt["qf_123bb01_3"];

//QF 123ББ01-3 (РГДВ)
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qf123bb01_1"])
	{
		elementsRgdv["124yg02_2_qf_123bb01_3"] = ELEM_AVAR;
		elementsRgdv["124yg02_2_qf_123bb01_3"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qf123bb01_1"])
	{
		elementsRgdv["124yg02_2_qf_123bb01_3"] = ELEM_NORMA;
		elementsRgdv["124yg02_2_qf_123bb01_3"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_2_qf_123bb01_3"] = ELEM_DISABLE;
		elementsRgdv["124yg02_2_qf_123bb01_3"] = "НЕ КОНТР";
	}

//QF 123ББ01-4
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qf123bb01_2"])
	{
		bPanelAvt["qf_123bb01_4"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qf123bb01_2"])
		bPanelAvt["qf_123bb01_4"] = ELEM_NORMA;
	else
		bPanelAvt["qf_123bb01_4"] = ELEM_NOT;
	messages["prd_control_panel@qf_123bb01_4"] = bPanelAvt["qf_123bb01_4"];

//QF 123ББ01-4 (РГДВ)
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qf123bb01_2"])
	{
		elementsRgdv["124yg02_2_qf_123bb01_4"] = ELEM_AVAR;
		elementsRgdv["124yg02_2_qf_123bb01_4"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qf123bb01_2"])
	{
		elementsRgdv["124yg02_2_qf_123bb01_4"] = ELEM_NORMA;
		elementsRgdv["124yg02_2_qf_123bb01_4"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_2_qf_123bb01_4"] = ELEM_DISABLE;
		elementsRgdv["124yg02_2_qf_123bb01_4"] = "НЕ КОНТР";
	}

//QF 126ГГ02-1
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qf126gg02"])
	{
		bPanelAvt["qf_126gg02_1"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qf126gg02"])
		bPanelAvt["qf_126gg02_1"] = ELEM_NORMA;
	else
		bPanelAvt["qf_126gg02_1"] = ELEM_NOT;
	messages["prd_control_panel@qf_126gg02_1"] = bPanelAvt["qf_126gg02_1"];

//QF 126ГГ02-1 (РГДВ)
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qf126gg02"])
	{
		elementsRgdv["124yg02_1_qf_prd1"] = ELEM_AVAR;
		elementsRgdv["124yg02_1_qf_prd1"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qf126gg02"])
	{
		elementsRgdv["124yg02_1_qf_prd1"] = ELEM_NORMA;
		elementsRgdv["124yg02_1_qf_prd1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_1_qf_prd1"] = ELEM_DISABLE;
		elementsRgdv["124yg02_1_qf_prd1"] = "НЕ КОНТР";
	}

//QF 126ГГ02-2
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qf126gg02"])
	{
		bPanelAvt["qf_126gg02_2"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qf126gg02"])
		bPanelAvt["qf_126gg02_2"] = ELEM_NORMA;
	else
		bPanelAvt["qf_126gg02_2"] = ELEM_NOT;
	messages["prd_control_panel@qf_126gg02_2"] = bPanelAvt["qf_126gg02_2"];

//QF 126ГГ02-2 (РГДВ)
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qf126gg02"])
	{
		elementsRgdv["124yg02_2_qf_prd2"] = ELEM_AVAR;
		elementsRgdv["124yg02_2_qf_prd2"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qf126gg02"])
	{
		elementsRgdv["124yg02_2_qf_prd2"] = ELEM_NORMA;
		elementsRgdv["124yg02_2_qf_prd2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_2_qf_prd2"] = ELEM_DISABLE;
		elementsRgdv["124yg02_2_qf_prd2"] = "НЕ КОНТР";
	}

//QF ЧП1
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qfChp1"])
	{
		bPanelAvt["qf_chp_1"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qfChp1"])
		bPanelAvt["qf_chp_1"] = ELEM_NORMA;
	else
		bPanelAvt["qf_chp_1"] = ELEM_NOT;
	messages["prd_control_panel@qf_chp_1"] = bPanelAvt["qf_chp_1"];

//QF ЧП1 (РГДВ)
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qfChp1"])
	{
		elementsRgdv["124yg02_1_qf_chp_1"] = ELEM_AVAR;
		elementsRgdv["124yg02_1_qf_chp_1"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qfChp1"])
	{
		elementsRgdv["124yg02_1_qf_chp_1"] = ELEM_NORMA;
		elementsRgdv["124yg02_1_qf_chp_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_1_qf_chp_1"] = ELEM_DISABLE;
		elementsRgdv["124yg02_1_qf_chp_1"] = "НЕ КОНТР";
	}

//QF ЧП2
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qfChp2"])
	{
		bPanelAvt["qf_chp_2"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qfChp2"])
		bPanelAvt["qf_chp_2"] = ELEM_NORMA;
	else
		bPanelAvt["qf_chp_2"] = ELEM_NOT;
	messages["prd_control_panel@qf_chp_2"] = bPanelAvt["qf_chp_2"];

//QF ЧП2 (РГДВ)
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qfChp2"])
	{
		elementsRgdv["124yg02_1_qf_chp_2"] = ELEM_AVAR;
		elementsRgdv["124yg02_1_qf_chp_2"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qfChp2"])
	{
		elementsRgdv["124yg02_1_qf_chp_2"] = ELEM_NORMA;
		elementsRgdv["124yg02_1_qf_chp_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_1_qf_chp_2"] = ELEM_DISABLE;
		elementsRgdv["124yg02_1_qf_chp_2"] = "НЕ КОНТР";
	}

//QF ЧП3
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qfChp1"])
	{
		bPanelAvt["qf_chp_3"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qfChp1"])
		bPanelAvt["qf_chp_3"] = ELEM_NORMA;
	else
		bPanelAvt["qf_chp_3"] = ELEM_NOT;
	messages["prd_control_panel@qf_chp_3"] = bPanelAvt["qf_chp_3"];

//QF ЧП3 (РГДВ)
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qfChp1"])
	{
		elementsRgdv["124yg02_2_qf_chp_3"] = ELEM_AVAR;
		elementsRgdv["124yg02_2_qf_chp_3"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qfChp1"])
	{
		elementsRgdv["124yg02_2_qf_chp_3"] = ELEM_NORMA;
		elementsRgdv["124yg02_2_qf_chp_3"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_2_qf_chp_3"] = ELEM_DISABLE;
		elementsRgdv["124yg02_2_qf_chp_3"] = "НЕ КОНТР";
	}

//QF ЧП4
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qfChp2"])
	{
		bPanelAvt["qf_chp_4"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qfChp2"])
		bPanelAvt["qf_chp_4"] = ELEM_NORMA;
	else
		bPanelAvt["qf_chp_4"] = ELEM_NOT;
	messages["prd_control_panel@qf_chp_4"] = bPanelAvt["qf_chp_4"];

//QF ЧП4 (РГДВ)
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qfChp2"])
	{
		elementsRgdv["124yg02_2_qf_chp_4"] = ELEM_AVAR;
		elementsRgdv["124yg02_2_qf_chp_4"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qfChp2"])
	{
		elementsRgdv["124yg02_2_qf_chp_4"] = ELEM_NORMA;
		elementsRgdv["124yg02_2_qf_chp_4"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_2_qf_chp_4"] = ELEM_DISABLE;
		elementsRgdv["124yg02_2_qf_chp_4"] = "НЕ КОНТР";
	}

//QF ОБЩ ВЕНТ 1
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qfVentOtkl"])
	{
		bPanelAvt["qf_vent_1"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qfVentOtkl"])
		bPanelAvt["qf_vent_1"] = ELEM_NORMA;
	else
		bPanelAvt["qf_vent_1"] = ELEM_NOT;
	messages["prd_control_panel@qf_vent_1"] = bPanelAvt["qf_vent_1"];

//QF ОБЩ ВЕНТ 1 (РГДВ)
	if(bPanelAvt["isOk1"] == ELEM_NORMA && sigmap["prd1_qfVentOtkl"])
	{
		elementsRgdv["124yg02_1_qf_vent"] = ELEM_AVAR;
		elementsRgdv["124yg02_1_qf_vent"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk1"] == ELEM_NORMA && !sigmap["prd1_qfVentOtkl"])
	{
		elementsRgdv["124yg02_1_qf_vent"] = ELEM_NORMA;
		elementsRgdv["124yg02_1_qf_vent"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_1_qf_vent"] = ELEM_DISABLE;
		elementsRgdv["124yg02_1_qf_vent"] = "НЕ КОНТР";
	}

//QF ОБЩ ВЕНТ 2
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qfVentOtkl"])
	{
		bPanelAvt["qf_vent_2"] = ELEM_AVAR;
		nError++;
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qfVentOtkl"])
		bPanelAvt["qf_vent_2"] = ELEM_NORMA;
	else
		bPanelAvt["qf_vent_2"] = ELEM_NOT;
	messages["prd_control_panel@qf_vent_2"] = bPanelAvt["qf_vent_2"];

//QF ОБЩ ВЕНТ 2 (РГДВ)
	if(bPanelAvt["isOk2"] == ELEM_NORMA && sigmap["prd2_qfVentOtkl"])
	{
		elementsRgdv["124yg02_2_qf_vent"] = ELEM_AVAR;
		elementsRgdv["124yg02_2_qf_vent"] = "ОТКЛ";
	}
	else if(bPanelAvt["isOk2"] == ELEM_NORMA && !sigmap["prd2_qfVentOtkl"])
	{
		elementsRgdv["124yg02_2_qf_vent"] = ELEM_NORMA;
		elementsRgdv["124yg02_2_qf_vent"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_2_qf_vent"] = ELEM_DISABLE;
		elementsRgdv["124yg02_2_qf_vent"] = "НЕ КОНТР";
	}

//Аварии
	if(bPanelAvt["qf_123gv02_1"] == ELEM_AVAR && bPanelAvt["qf_123gv02_2"] == ELEM_AVAR)
		nAvar++;
	if(bPanelAvt["qf_123bb01_1"] == ELEM_AVAR && bPanelAvt["qf_123bb01_2"] == ELEM_AVAR)
		nAvar++;
	if(bPanelAvt["qf_123bb01_3"] == ELEM_AVAR && bPanelAvt["qf_123bb01_4"] == ELEM_AVAR)
		nAvar++;
	if(bPanelAvt["qf_126gg02_1"] == ELEM_AVAR && bPanelAvt["qf_126gg02_2"] == ELEM_AVAR)
		nAvar++;
	if(bPanelAvt["qf_chp_1"] == ELEM_AVAR && bPanelAvt["qf_chp_2"] == ELEM_AVAR)
		nAvar++;
	if(bPanelAvt["qf_chp_3"] == ELEM_AVAR && bPanelAvt["qf_chp_4"] == ELEM_AVAR)
		nAvar++;

//Общее состояние ПАНЕЛЬ АВТОМАТОВ
	if(bPanelAvt["isOk"] == ELEM_NORMA && (nAvar > 0))
		bPanelAvt["obSost"] = ELEM_AVAR;
	else if(bPanelAvt["isOk"] == ELEM_NORMA && (nError > 0))
		bPanelAvt["obSost"] = ELEM_ERROR;
	else if(bPanelAvt["isOk"] == ELEM_NORMA && (nError == 0 && nAvar == 0))
		bPanelAvt["obSost"] = ELEM_NORMA;
	else
		bPanelAvt["obSost"] = ELEM_NOT;

	elements["prd_control_panel@qf_123gv02_1"] = bPanelAvt["qf_123gv02_1"].toString();
	elements["prd_control_panel@qf_123gv02_2"] = bPanelAvt["qf_123gv02_2"].toString();
	elements["prd_control_panel@qf_123bb01_1"] = bPanelAvt["qf_123bb01_1"].toString();
	elements["prd_control_panel@qf_123bb01_2"] = bPanelAvt["qf_123bb01_2"].toString();
	elements["prd_control_panel@qf_123bb01_3"] = bPanelAvt["qf_123bb01_3"].toString();
	elements["prd_control_panel@qf_123bb01_4"] = bPanelAvt["qf_123bb01_4"].toString();
	elements["prd_control_panel@qf_126gg02_1"] = bPanelAvt["qf_126gg02_1"].toString();
	elements["prd_control_panel@qf_126gg02_2"] = bPanelAvt["qf_126gg02_2"].toString();
	elements["prd_control_panel@qf_chp_1"] = bPanelAvt["qf_chp_1"].toString();
	elements["prd_control_panel@qf_chp_2"] = bPanelAvt["qf_chp_2"].toString();
	elements["prd_control_panel@qf_chp_3"] = bPanelAvt["qf_chp_3"].toString();
	elements["prd_control_panel@qf_chp_4"] = bPanelAvt["qf_chp_4"].toString();
	elements["prd_control_panel@qf_vent_1"] = bPanelAvt["qf_vent_1"].toString();
	elements["prd_control_panel@qf_vent_2"] = bPanelAvt["qf_vent_2"].toString();
	elements["prd_control@avt_panel"] = bPanelAvt["obSost"].toString();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::fun125YY04_raf()
{
	int nAvar = 0, nError = 0, nNorma = 0;

//ОК 1
	if(canalAsku["OY2_OS_STATE"] == ELEM_NORMA && b124yg02["d2vv056_1"] == ELEM_NORMA)
		b125yy04["isOkPrd1"] = ELEM_NORMA;
	else
		b125yy04["isOkPrd1"] = ELEM_NOT;

//ОК 2
	if(canalAsku["OY3_OS_STATE"] == ELEM_NORMA && b124yg02["d2vv056_2"] == ELEM_NORMA)
		b125yy04["isOkPrd2"] = ELEM_NORMA;
	else
		b125yy04["isOkPrd2"] = ELEM_NOT;

//OK
	if(b125yy04["isOkPrd1"] == ELEM_NORMA || b125yy04["isOkPrd2"] == ELEM_NORMA)
		b125yy04["isOkPrd"] = ELEM_NORMA;
	else
		b125yy04["isOkPrd"] = ELEM_NOT;

//123ГВ02-1
	if(b125yy04["isOkPrd1"] == ELEM_NORMA && b124ee02["p27v_123gv02_1"] == ELEM_NORMA && bPanelAvt["qf_123gv02_1"] == ELEM_NORMA && sigmap["prd1_avar123gv02"])
	{
		b125yy04["123gv02_1"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy04["isOkPrd1"] == ELEM_NORMA && b124ee02["p27v_123gv02_1"] == ELEM_NORMA && bPanelAvt["qf_123gv02_1"] == ELEM_NORMA && !sigmap["prd1_avar123gv02"] && sigmap["prd1_vkl123gv02"])
	{
		b125yy04["123gv02_1"] = ELEM_NORMA;
		nNorma++;
	}
	else
	{
		b125yy04["123gv02_1"] = ELEM_NOT;
	}
	messages["prd_control@123gv02_1"] = b125yy04["123gv02_1"];

//123ГВ02-2
	if(b125yy04["isOkPrd2"] == ELEM_NORMA && b124ee02["p27v_123gv02_2"] == ELEM_NORMA && bPanelAvt["qf_123gv02_2"] == ELEM_NORMA && sigmap["prd2_avar123gv02"])
	{
		b125yy04["123gv02_2"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy04["isOkPrd2"] == ELEM_NORMA && b124ee02["p27v_123gv02_2"] == ELEM_NORMA && bPanelAvt["qf_123gv02_2"] == ELEM_NORMA && !sigmap["prd2_avar123gv02"] && sigmap["prd2_vkl123gv02"])
	{
		b125yy04["123gv02_2"] = ELEM_NORMA;
		nNorma++;
	}
	else
	{
		b125yy04["123gv02_2"] = ELEM_NOT;
	}
	messages["prd_control@123gv02_2"] = b125yy04["123gv02_2"];

//СВЧ КОММУТАТОР ВХ
	if((b125yy04["isOkPrd1"] == ELEM_NORMA && sigmap["prd1_commSvchPos"]) || (b125yy04["isOkPrd2"] == ELEM_NORMA && sigmap["prd2_commSvchPos"]))
	{
		b125yy04["svch_in"] = ELEM_NORMA;
		nNorma++;
	}
	else
		b125yy04["svch_in"] = ELEM_NOT;

//СВЧ КОММУТАТОР ПУМ
	if((b125yy04["isOkPrd1"] == ELEM_NORMA && sigmap["prd1_normaSVChComm"]) || (b125yy04["isOkPrd2"] == ELEM_NORMA && sigmap["prd2_normaSVChComm"]))
	{
		b125yy04["svch_pum"] = ELEM_NORMA;
		nNorma++;
	}
	else
		b125yy04["svch_pum"] = ELEM_NOT;

//123ББ01-1
	if(b125yy04["isOkPrd1"] == ELEM_NORMA && b124ee02["qf_prd1"] == ELEM_NORMA && bPanelAvt["qf_123bb01_1"] == ELEM_NORMA && !sigmap["prd1_norma123bb01_1"])
	{
		b125yy04["123bb01_1"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy04["isOkPrd1"] == ELEM_NORMA && b124ee02["qf_prd1"] == ELEM_NORMA && bPanelAvt["qf_123bb01_1"] == ELEM_NORMA && sigmap["prd1_norma123bb01_1"])
		b125yy04["123bb01_1"] = ELEM_NORMA;
	else
		b125yy04["123bb01_1"] = ELEM_NOT;
	messages["prd_control@123bb01_1"] = b125yy04["123bb01_1"];

//123ББ01-2
	if(b125yy04["isOkPrd1"] == ELEM_NORMA && b124ee02["qf_prd1"] == ELEM_NORMA && bPanelAvt["qf_123bb01_2"] == ELEM_NORMA && !sigmap["prd1_norma123bb01_2"])
	{
		b125yy04["123bb01_2"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy04["isOkPrd1"] == ELEM_NORMA && b124ee02["qf_prd1"] == ELEM_NORMA && bPanelAvt["qf_123bb01_2"] == ELEM_NORMA && sigmap["prd1_norma123bb01_2"])
		b125yy04["123bb01_2"] = ELEM_NORMA;
	else
		b125yy04["123bb01_2"] = ELEM_NOT;
	messages["prd_control@123bb01_2"] = b125yy04["123bb01_2"];

//123ББ01-3
	if(b125yy04["isOkPrd2"] == ELEM_NORMA && b124ee02["qf_prd2"] == ELEM_NORMA && bPanelAvt["qf_123bb01_3"] == ELEM_NORMA && !sigmap["prd2_norma123bb01_1"])
	{
		b125yy04["123bb01_3"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy04["isOkPrd2"] == ELEM_NORMA && b124ee02["qf_prd2"] == ELEM_NORMA && bPanelAvt["qf_123bb01_3"] == ELEM_NORMA && sigmap["prd2_norma123bb01_1"])
		b125yy04["123bb01_3"] = ELEM_NORMA;
	else
		b125yy04["123bb01_3"] = ELEM_NOT;
	messages["prd_control@123bb01_3"] = b125yy04["123bb01_3"];

//123ББ01-4
	if(b125yy04["isOkPrd2"] == ELEM_NORMA && b124ee02["qf_prd2"] == ELEM_NORMA && bPanelAvt["qf_123bb01_4"] == ELEM_NORMA && !sigmap["prd2_norma123bb01_2"])
	{
		b125yy04["123bb01_4"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy04["isOkPrd2"] == ELEM_NORMA && b124ee02["qf_prd2"] == ELEM_NORMA && bPanelAvt["qf_123bb01_4"] == ELEM_NORMA && sigmap["prd2_norma123bb01_2"])
		b125yy04["123bb01_4"] = ELEM_NORMA;
	else
		b125yy04["123bb01_4"] = ELEM_NOT;
	messages["prd_control@123bb01_4"] = b125yy04["123bb01_4"];
/*
//ЗАЩ ОБЩ ВЕНТ 1
	if(b125yy04["isOkPrd1"] == ELEM_NORMA && sigmap["prd1_qfVent"])
	{
		b125yy04["qf_vent_1"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy04["isOkPrd1"] == ELEM_NORMA && !sigmap["prd1_qfVent"])
		b125yy04["qf_vent_1"] = ELEM_NORMA;
	else
		b125yy04["qf_vent_1"] = ELEM_NOT;
	messages["prd_control@qf_vent_1"] = b125yy04["qf_vent_1"];

//ЗАЩ ОБЩ ВЕНТ 1 (РГДВ)
	if(b125yy04["isOkPrd1"] == ELEM_NORMA && sigmap["prd1_qfVent"])
	{
		elementsRgdv["124yg02_1_qf_vent"] = ELEM_AVAR;
		elementsRgdv["124yg02_1_qf_vent"] = "ОТКЛ";
	}
	else if(b125yy04["isOkPrd1"] == ELEM_NORMA && !sigmap["prd1_qfVent"])
	{
		elementsRgdv["124yg02_1_qf_vent"] = ELEM_NORMA;
		elementsRgdv["124yg02_1_qf_vent"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_1_qf_vent"] = ELEM_DISABLE;
		elementsRgdv["124yg02_1_qf_vent"] = "НЕ КОНТР";
	}

//ЗАЩ ОБЩ ВЕНТ 2
	if(b125yy04["isOkPrd2"] == ELEM_NORMA && sigmap["prd2_qfVent"])
	{
		b125yy04["qf_vent_2"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy04["isOkPrd2"] == ELEM_NORMA && !sigmap["prd2_qfVent"])
		b125yy04["qf_vent_2"] = ELEM_NORMA;
	else
		b125yy04["qf_vent_2"] = ELEM_NOT;
	messages["prd_control@qf_vent_2"] = b125yy04["qf_vent_2"];

//ЗАЩ ОБЩ ВЕНТ 2 (РГДВ)
	if(b125yy04["isOkPrd2"] == ELEM_NORMA && sigmap["prd2_qfVent"])
	{
		elementsRgdv["124yg02_2_qf_vent"] = ELEM_AVAR;
		elementsRgdv["124yg02_2_qf_vent"] = "ОТКЛ";
	}
	else if(b125yy04["isOkPrd2"] == ELEM_NORMA && !sigmap["prd2_qfVent"])
	{
		elementsRgdv["124yg02_2_qf_vent"] = ELEM_NORMA;
		elementsRgdv["124yg02_2_qf_vent"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yg02_2_qf_vent"] = ELEM_DISABLE;
		elementsRgdv["124yg02_2_qf_vent"] = "НЕ КОНТР";
	}
*/
//ЧП1
//	if(bPanelAvt["qf_chp_1"] == ELEM_NORMA || b125yy04["isOkPrd1"] != ELEM_NORMA)
	if((bPanelAvt["qf_chp_1"] == ELEM_NORMA && b124ee02["qf_prd1"] == ELEM_NORMA) || 
		b125yy04["isOkPrd1"] != ELEM_NORMA || b124ee02["isAvtOk"] != ELEM_NORMA)
	{
		b125yy04["chp_1"] = coolers["vesper1@ObSost"];
		if(b125yy04["chp_1"] == ELEM_AVAR || b125yy04["chp_1"] == ELEM_ERROR)
			nError++;
	}
	else
	{
		b125yy04["chp_1"] = ELEM_NOT;
	}
	messages["prd_control@chp_1"] = b125yy04["chp_1"];

//ЧП2
//	if(bPanelAvt["qf_chp_2"] == ELEM_NORMA || b125yy04["isOkPrd1"] != ELEM_NORMA)
	if((bPanelAvt["qf_chp_2"] == ELEM_NORMA && b124ee02["qf_prd1"] == ELEM_NORMA) || 
		b125yy04["isOkPrd1"] != ELEM_NORMA || b124ee02["isAvtOk"] != ELEM_NORMA)
	{
		b125yy04["chp_2"] = coolers["vesper2@ObSost"];
		if(b125yy04["chp_2"] == ELEM_AVAR || b125yy04["chp_2"] == ELEM_ERROR)
			nError++;
	}
	else
		b125yy04["chp_2"] = ELEM_NOT;
	messages["prd_control@chp_2"] = b125yy04["chp_2"];

//ЧП3
//	if(bPanelAvt["qf_chp_3"] == ELEM_NORMA || b125yy04["isOkPrd2"] != ELEM_NORMA)
	if((bPanelAvt["qf_chp_3"] == ELEM_NORMA && b124ee02["qf_prd2"] == ELEM_NORMA) || 
		b125yy04["isOkPrd2"] != ELEM_NORMA || b124ee02["isAvtOk"] != ELEM_NORMA)
	{
		b125yy04["chp_3"] = coolers["vesper3@ObSost"];
		if(b125yy04["chp_3"] == ELEM_AVAR || b125yy04["chp_3"] == ELEM_ERROR)
			nError++;
	}
	else
		b125yy04["chp_3"] = ELEM_NOT;
	messages["prd_control@chp_3"] = b125yy04["chp_3"];

//ЧП4
//	if(bPanelAvt["qf_chp_4"] == ELEM_NORMA || b125yy04["isOkPrd1"] != ELEM_NORMA)
	if((bPanelAvt["qf_chp_4"] == ELEM_NORMA && b124ee02["qf_prd2"] == ELEM_NORMA) || 
		b125yy04["isOkPrd2"] != ELEM_NORMA || b124ee02["isAvtOk"] != ELEM_NORMA)
	{
		b125yy04["chp_4"] = coolers["vesper4@ObSost"];
		if(b125yy04["chp_4"] == ELEM_AVAR || b125yy04["chp_4"] == ELEM_ERROR)
			nError++;
	}
	else
		b125yy04["chp_4"] = ELEM_NOT;
	messages["prd_control@chp_4"] = b125yy04["chp_4"];

//Аварии
	if(b125yy04["123gv02_1"] == ELEM_AVAR && b125yy04["123gv02_2"] == ELEM_AVAR)
		nAvar++;
	if(b125yy04["123bb01_1"] == ELEM_AVAR && b125yy04["123bb01_2"] == ELEM_AVAR && b125yy04["123bb01_3"] == ELEM_AVAR && b125yy04["123bb01_4"] == ELEM_AVAR)
		nAvar++;
//	if(b125yy04["qf_vent_1"] == ELEM_AVAR && b125yy04["qf_vent_2"] == ELEM_AVAR)
//		nAvar++;
	if(b125yy04["chp_1"] == ELEM_AVAR && b125yy04["chp_2"] == ELEM_AVAR)
		nAvar++;
	if(b125yy04["chp_3"] == ELEM_AVAR && b125yy04["chp_4"] == ELEM_AVAR)
		nAvar++;

//Общее состояние 125УУ04
	if(b124yg02["obSost"] == ELEM_AVAR || bPanelAvt["obSost"] == ELEM_AVAR || (nAvar != 0))
		b125yy04["obSost"] = ELEM_AVAR;
	else if(b124yg02["obSost"] == ELEM_ERROR || bPanelAvt["obSost"] == ELEM_ERROR || (nError != 0))
		b125yy04["obSost"] = ELEM_ERROR;
	else if(b125yy04["isOkPrd"] == ELEM_NORMA && b124yg02["obSost"] == ELEM_NORMA && bPanelAvt["obSost"] == ELEM_NORMA && (nError == 0) && (nAvar == 0) /*&& (nNorma > 1)*/)
		b125yy04["obSost"] = ELEM_NORMA;
	else
		b125yy04["obSost"] = ELEM_NOT;

	elements["prd_control@123gv02_1"] = b125yy04["123gv02_1"].toString() + b124yg02["mest1"].toStringMest();
	elements["prd_control@123gv02_2"] = b125yy04["123gv02_2"].toString() + b124yg02["mest2"].toStringMest();
	elements["base@pum1"] = b125yy04["123gv02_1"].toString() + b124yg02["mest1"].toStringMest();
	elements["base@pum2"] = b125yy04["123gv02_2"].toString() + b124yg02["mest2"].toStringMest();

	elements["prd_control@svch_in"]  = b125yy04["svch_in"].toString() + b124yg02["mest"].toStringMest();
	elements["prd_control@svch_pum"] = b125yy04["svch_pum"].toString() + b124yg02["mest"].toStringMest();

	elements["prd_control@123bb01_1"] = b125yy04["123bb01_1"].toString();
	elements["prd_control@123bb01_2"] = b125yy04["123bb01_2"].toString();
	elements["prd_control@123bb01_3"] = b125yy04["123bb01_3"].toString();
	elements["prd_control@123bb01_4"] = b125yy04["123bb01_4"].toString();
//	elements["prd_control@qf_vent_1"] = b125yy04["qf_vent_1"].toString();
//	elements["prd_control@qf_vent_2"] = b125yy04["qf_vent_2"].toString();

	elements["prd_control@chp_1"] = b125yy04["chp_1"].toString();
	elements["prd_control@chp_2"] = b125yy04["chp_2"].toString();
	elements["prd_control@chp_3"] = b125yy04["chp_3"].toString();
	elements["prd_control@chp_4"] = b125yy04["chp_4"].toString();

	elements["prdsys@125yy04"] = b125yy04["obSost"].toString() + b124yg02["mest"].toStringMest();
	elements["zal@125yy04"]    = b125yy04["obSost"].toString() + b124yg02["mest"].toStringMest();

	elements["base@svch_in"]  = b125yy04["svch_in"].toString() + b124yg02["mest"].toStringMest();
	elements["base@svch_pum"] = b125yy04["svch_pum"].toString() + b124yg02["mest"].toStringMest();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::fun126GG02_raf(qint32 n_prd)
{
	quint32 nAvar = 0, nError = 0, nNorma = 0;
	quint32 numModules = 0;
	QString OY_OS_UMI;
	QString N_PRD = QString::number(n_prd + 1);
	QString NAME_PRD = "prd" + N_PRD + "_";

	if(n_prd == 0)
	{
//ОК 1
		if(canalAsku["OY2_OS_STATE"] == ELEM_NORMA && b124yg02["d2vv056_1"] == ELEM_NORMA && bPanelAvt["qf_126gg02_1"] == ELEM_NORMA)
			b126gg02[n_prd]["isOkGG"] = ELEM_NORMA;
		else
			b126gg02[n_prd]["isOkGG"] = ELEM_NOT;

//WORKING 1
		if(b126gg02[n_prd]["isOkGG"] == ELEM_NORMA && sigmap["prd1_vkl380"])
			b126gg02[n_prd]["Working"] = ELEM_NORMA;
		else
			b126gg02[n_prd]["Working"] = ELEM_NOT;

		b126gg02[n_prd]["Mest"] = b124yg02["Mest1"];
		numModules = (quint8)canalAsku["OY2_MODULES_UMI"];
		OY_OS_UMI = "OY2_OS_UMI_";
	}
	if(n_prd == 1)
	{
//ОК 2
		if(canalAsku["OY3_OS_STATE"] == ELEM_NORMA && b124yg02["d2vv056_2"] == ELEM_NORMA && bPanelAvt["qf_126gg02_2"] == ELEM_NORMA)
			b126gg02[n_prd]["isOkGG"] = ELEM_NORMA;
		else
			b126gg02[n_prd]["isOkGG"] = ELEM_NOT;

//WORKING 2
		if(b126gg02[n_prd]["isOkGG"] == ELEM_NORMA && sigmap["prd2_vkl380"])
			b126gg02[n_prd]["Working"] = ELEM_NORMA;
		else
			b126gg02[n_prd]["Working"] = ELEM_NOT;

		b126gg02[n_prd]["mest"] = b124yg02["Mest2"];
		numModules = (quint8)canalAsku["OY3_MODULES_UMI"];
		OY_OS_UMI = "OY3_OS_UMI_";
	}

//D2HL142
	if(b126gg02[n_prd]["Working"] == ELEM_NORMA && sigmap[NAME_PRD + "avarD2hl142"])
		b126gg02[n_prd]["d2hl142"] = ELEM_AVAR;
	else if(b126gg02[n_prd]["Working"] == ELEM_NORMA && !sigmap[NAME_PRD + "avarD2hl142"])
		b126gg02[n_prd]["d2hl142"] = ELEM_NORMA;
	else
		b126gg02[n_prd]["d2hl142"] = ELEM_NOT;

		if(m_isMain)
		{
			messages[NAME_PRD + "base@d2hl142"] = b126gg02[n_prd]["d2hl142"];
			elements[NAME_PRD + "base@d2hl142"] = b126gg02[n_prd]["d2hl142"].toString() + b126gg02[n_prd]["mest"].toStringMest();
		}

	double temperatureCommon = 0;
	quint32 counterCommon = 0;
	double temperatureWorking = 0;
	quint32 counterWorking = 0;

	for(quint32 module = 0; module < numModules; module++)
	{
		QString N_MODULE = QString::number(module + 1);
		QString NAME_MODULE = "umi" + N_MODULE;
		QString NAME_SIGNAL = NAME_PRD + NAME_MODULE + "_";
		QString NAME_VALUE = "value_" + NAME_PRD + NAME_MODULE + "_";

		bool state = canalAsku[OY_OS_UMI + N_MODULE] == ELEM_NORMA;

//		bool avarUmi = sigmap[NAME_PRD + NAME_MODULE + "Avar"];

		bool offUmi = sigmap[NAME_PRD + NAME_MODULE + "Link"];

		bool avarUmi = sigmap[NAME_SIGNAL + "temperature"] || 
						(sigmap[NAME_SIGNAL + "out_power"] && !sigmap[NAME_SIGNAL + "svch_on"]) ||
						sigmap[NAME_SIGNAL + "ksvn"] ||
						sigmap[NAME_SIGNAL + "u_power"] ||
//						sigmap[NAME_SIGNAL + "no_impulse"] ||
						sigmap[NAME_SIGNAL + "impulse"];

		bool errorUmi = sigmap[NAME_SIGNAL + "sensor"] ||
			((sigmap[NAME_SIGNAL + "in_power_low"] || sigmap[NAME_SIGNAL + "in_power_high"]) && !sigmap[NAME_SIGNAL + "out_power"]) ||
			(sigmap[NAME_SIGNAL + "out_power"] && sigmap[NAME_SIGNAL + "svch_on"] && !sigmap[NAME_SIGNAL + "no_impulse"]);

		bool onUmi = sigmap[NAME_SIGNAL + "power380_on"] && 
						sigmap[NAME_SIGNAL + "power_on"] && 
						sigmap[NAME_SIGNAL + "svch_on"] &&
						!sigmap[NAME_SIGNAL + "no_impulse"];

//УМИ
//		if(b126gg02[n_prd]["isOkGG"] == ELEM_NORMA && avarUmi)
		if(b126gg02[n_prd]["isOkGG"] == ELEM_NORMA && state && !offUmi && avarUmi)
		{
			b126gg02[n_prd][NAME_MODULE] = ELEM_AVAR;
			nAvar++;
		}
		else if(b126gg02[n_prd]["isOkGG"] == ELEM_NORMA && state && !offUmi && errorUmi)
		{
			b126gg02[n_prd][NAME_MODULE] = ELEM_ERROR;
			nError++;
		}
		else if(b126gg02[n_prd]["isOkGG"] == ELEM_NORMA && state && !offUmi && onUmi)
		{
			b126gg02[n_prd][NAME_MODULE] = ELEM_NORMA;
			nNorma++;
		}
		else
			b126gg02[n_prd][NAME_MODULE] = ELEM_NOT;

//Температура УМИ
		if(b126gg02[n_prd]["isOkGG"] == ELEM_NORMA && state && 
			!offUmi && !sigmap[NAME_SIGNAL + "sensor"])
		{
			temperatureCommon += valmap[NAME_VALUE + "temperature"].toUInt();
			counterCommon++;

			if(onUmi)
			{
				temperatureWorking += valmap[NAME_VALUE + "temperature"].toUInt();
				counterWorking++;
			}
		}
		
		if(m_isMain)
		{
			messages[NAME_PRD + "base@" + NAME_MODULE] = b126gg02[n_prd][NAME_MODULE];
			elements[NAME_PRD + "base@" + NAME_MODULE] = b126gg02[n_prd][NAME_MODULE].toString() + b126gg02[n_prd]["mest"].toStringMest();
		}

		funDC_UMI(n_prd, module);
	}

//Общая температура шкафа
	quint8 stateCommon = ELEM_NOT;
	QString textCommon = "---";

	if(counterCommon > 0)
	{
		temperatureCommon /= counterCommon;
		textCommon = QString("%1").arg(temperatureCommon, 0, 'f', 1);

		if(temperatureCommon < 5.0 || temperatureCommon > 75.0)
			stateCommon = ELEM_AVAR;
		else if(temperatureCommon < 10.0 || temperatureCommon > 70.0)
			stateCommon = ELEM_ERROR;
		else
			stateCommon = ELEM_NORMA;
	}

	valmap["value_temperature_prd" + N_PRD + "_common"] = temperatureCommon;
	b126gg02[n_prd]["TemperatureCommon"].setText(textCommon) = stateCommon;

//Общая температура работающих модулей шкафа
	quint8 stateWorking = ELEM_NOT;
	QString textWorking = "---";

	if(counterWorking > 0)
	{
		temperatureWorking /= counterWorking;
		textWorking = QString("%1").arg(temperatureWorking, 0, 'f', 1);

		if(temperatureWorking < 5.0 || temperatureWorking > 75.0)
			stateWorking = ELEM_AVAR;
		else if(temperatureWorking < 10.0 || temperatureWorking > 70.0)
			stateWorking = ELEM_ERROR;
		else
			stateWorking = ELEM_NORMA;
	}


	valmap["value_temperature_prd" + N_PRD + "_working"] = temperatureWorking;
	b126gg02[n_prd]["TemperatureWorking"].setText(textWorking) = stateWorking;

	emit setPrdTemperature(n_prd * 2 + 0, b126gg02[n_prd]["Working"] == ELEM_NORMA, temperatureWorking);
	emit setPrdTemperature(n_prd * 2 + 1, b126gg02[n_prd]["Working"] == ELEM_NORMA, temperatureWorking);

	elements["prdsys@temp_text_" + N_PRD] = b126gg02[n_prd]["TemperatureWorking"].toString();
	elements["prdsys@temp_" + N_PRD] = b126gg02[n_prd]["TemperatureWorking"].toString();
	elements["prdsys@temp_" + N_PRD].setText(textWorking);

//Общее состояние 126ГГ02
	if(nAvar > 8)
		b126gg02[n_prd]["obSost"] = ELEM_AVAR;
	else if(nAvar > 0 || nError > 0)
		b126gg02[n_prd]["obSost"] = ELEM_ERROR;
	else if(nNorma > 0)
		b126gg02[n_prd]["obSost"] = ELEM_NORMA;
	else
		b126gg02[n_prd]["obSost"] = ELEM_NOT;

	elements["prdsys@126gg02_" + N_PRD] = b126gg02[n_prd]["obSost"].toString() + b126gg02[n_prd]["mest"].toStringMest();
	elements["zal@126gg02_" + N_PRD] = b126gg02[n_prd]["obSost"].toString() + b126gg02[n_prd]["mest"].toStringMest();

	if(b126gg02[n_prd]["obSost"] == ELEM_AVAR || b124yg02["d2vv056_" + N_PRD] == ELEM_AVAR)
		b126gg02[n_prd]["obSostPrd"] = ELEM_AVAR;
	else if(b126gg02[n_prd]["obSost"] == ELEM_ERROR)
		b126gg02[n_prd]["obSostPrd"] = ELEM_ERROR;
	else if(b126gg02[n_prd]["obSost"] == ELEM_NORMA)
		b126gg02[n_prd]["obSostPrd"] = ELEM_NORMA;
	else
		b126gg02[n_prd]["obSostPrd"] = ELEM_NOT;

	elements["base@prd" + N_PRD] = b126gg02[n_prd]["obSostPrd"].toString() + b126gg02[n_prd]["mest"].toStringMest();

	b126gg02[n_prd]["Modules_ON"] = nNorma;

	if(nNorma > 0)
		ctrlKvit["prd" + N_PRD + "_on"] = ELEM_NORMA;
	else
		ctrlKvit["prd" + N_PRD + "_on"] = ELEM_NOT;
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::showOverheatWarning()
{
	AddErrorMes("АСКУ", "Возможен перегрев нагрузки ПРД при продолжении работы");
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::cmdOverheatWarning()
{
	AddAvarMes("АСКУ", "Во избежании перегрева нагрузки ПРД дальнейшая работа не возможна!");
	emit cmdSetPrdOff();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funPrdSys_raf()
{
	quint8 modules1 = b126gg02[0]["Modules_ON"];
	quint8 modules2 = b126gg02[1]["Modules_ON"];
	quint8 diff = 0;

	if(modules1 > 0 || modules2 > 0)
	{
		if(modules1 >= modules2)
			diff = modules1 - modules2;
		else
			diff = modules2 - modules1;
	}
	if(overheatWarning)
		overheatWarning->setAvar(diff > 10);
	if(overheatCommand)
		overheatCommand->setAvar(diff > 10);

//ВЕНТИЛЯТОРЫ СВО
//ВЕНТ1
	if(b125yy04["isOkPrd1"] == ELEM_NORMA && bPanelAvt["qf_chp_1"] == ELEM_NORMA)
		b125yy04["vent_1"] = coolers["vesper1@Ventilator"];
	else
		b125yy04["vent_1"] = ELEM_NOT;

//ВЕНТ2
	if(b125yy04["isOkPrd1"] == ELEM_NORMA && bPanelAvt["qf_chp_2"] == ELEM_NORMA)
		b125yy04["vent_2"] = coolers["vesper2@Ventilator"];
	else
		b125yy04["vent_2"] = ELEM_NOT;

//ВЕНТ3
	if(b125yy04["isOkPrd1"] == ELEM_NORMA && bPanelAvt["qf_chp_1"] == ELEM_NORMA)
		b125yy04["vent_3"] = coolers["vesper1@Ventilator"];
	else
		b125yy04["vent_3"] = ELEM_NOT;

//ВЕНТ4
	if(b125yy04["isOkPrd1"] == ELEM_NORMA && bPanelAvt["qf_chp_2"] == ELEM_NORMA)
		b125yy04["vent_4"] = coolers["vesper2@Ventilator"];
	else
		b125yy04["vent_4"] = ELEM_NOT;

//ВЕНТ5
	if(b125yy04["isOkPrd2"] == ELEM_NORMA && bPanelAvt["qf_chp_3"] == ELEM_NORMA)
		b125yy04["vent_5"] = coolers["vesper3@Ventilator"];
	else
		b125yy04["vent_5"] = ELEM_NOT;

//ВЕНТ6
	if(b125yy04["isOkPrd2"] == ELEM_NORMA && bPanelAvt["qf_chp_4"] == ELEM_NORMA)
		b125yy04["vent_6"] = coolers["vesper4@Ventilator"];
	else
		b125yy04["vent_6"] = ELEM_NOT;

//ВЕНТ7
	if(b125yy04["isOkPrd2"] == ELEM_NORMA && bPanelAvt["qf_chp_3"] == ELEM_NORMA)
		b125yy04["vent_7"] = coolers["vesper3@Ventilator"];
	else
		b125yy04["vent_7"] = ELEM_NOT;

//ВЕНТ8
	if(b125yy04["isOkPrd2"] == ELEM_NORMA && bPanelAvt["qf_chp_4"] == ELEM_NORMA)
		b125yy04["vent_8"] = coolers["vesper4@Ventilator"];
	else
		b125yy04["vent_8"] = ELEM_NOT;


//obSostSVO1
	if(b125yy04["chp_1"] == ELEM_NOT && b125yy04["chp_2"] == ELEM_NOT)
		b125yy04["SVO1"] = ELEM_NOT;
	else if(b125yy04["chp_1"] == ELEM_AVAR && b125yy04["chp_2"] == ELEM_AVAR)
		b125yy04["SVO1"] = ELEM_AVAR;
	else if(b125yy04["chp_1"] == ELEM_NORMA && b125yy04["chp_2"] == ELEM_NORMA &&
			(b125yy04["vent_1"] == ELEM_NORMA || b125yy04["vent_2"] == ELEM_NORMA))
		b125yy04["SVO1"] = ELEM_NORMA;
	else if(b125yy04["chp_1"] == ELEM_NORMA && b125yy04["chp_2"] == ELEM_NORMA)
		b125yy04["SVO1"] = ELEM_NOT;
	else
		b125yy04["SVO1"] = ELEM_ERROR;

//obSostSVO2
	if(b125yy04["chp_3"] == ELEM_NOT && b125yy04["chp_4"] == ELEM_NOT)
		b125yy04["SVO2"] = ELEM_NOT;
	else if(b125yy04["chp_3"] == ELEM_AVAR && b125yy04["chp_4"] == ELEM_AVAR)
		b125yy04["SVO2"] = ELEM_AVAR;
	else if(b125yy04["chp_3"] == ELEM_NORMA && b125yy04["chp_4"] == ELEM_NORMA &&
			(b125yy04["vent_5"] == ELEM_NORMA || b125yy04["vent_6"] == ELEM_NORMA))
		b125yy04["SVO2"] = ELEM_NORMA;
	else if(b125yy04["chp_3"] == ELEM_NORMA && b125yy04["chp_4"] == ELEM_NORMA)
		b125yy04["SVO2"] = ELEM_NOT;
	else
		b125yy04["SVO2"] = ELEM_ERROR;

//obSostSVO
	if(b125yy04["SVO1"] == ELEM_NOT && b125yy04["SVO2"] == ELEM_NOT)
		b125yy04["SVO"] = ELEM_NOT;
	else if(b125yy04["SVO1"] == ELEM_AVAR || b125yy04["SVO2"] == ELEM_AVAR)
		b125yy04["SVO"] = ELEM_AVAR;
	else if(b125yy04["SVO1"] == ELEM_NORMA && b125yy04["SVO2"] == ELEM_NORMA)
		b125yy04["SVO"] = ELEM_NORMA;
	else
		b125yy04["SVO"] = ELEM_ERROR;

if(m_isMain)
{
	elements["prdsys@vent_1"] = b125yy04["vent_1"].toString();
	elements["prdsys@vent_2"] = b125yy04["vent_2"].toString();
	elements["prdsys@vent_3"] = b125yy04["vent_3"].toString();
	elements["prdsys@vent_4"] = b125yy04["vent_4"].toString();
	elements["prdsys@vent_5"] = b125yy04["vent_5"].toString();
	elements["prdsys@vent_6"] = b125yy04["vent_6"].toString();
	elements["prdsys@vent_7"] = b125yy04["vent_7"].toString();
	elements["prdsys@vent_8"] = b125yy04["vent_8"].toString();

//	elements["base@svo1"] = coolers["SVO1"].toString();
//	elements["base@svo2"] = coolers["SVO2"].toString();
//	elements["zal@svo"] = coolers["obSost"].toString();
	elements["base@svo1"] = b125yy04["SVO1"].toString();
	elements["base@svo2"] = b125yy04["SVO2"].toString();
	elements["zal@svo"] = b125yy04["SVO"].toString();
}
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funDC_UMI(quint32 n_prd, quint32 n_module)
{
//	qDebug() << "prd=" << n_prd << "umi=" << n_module;
	QString OY_OS_UMI;
	QString N_PRD = QString::number(n_prd + 1);
	QString NAME_PRD = "prd" + N_PRD + "_";
	QString N_MODULE = QString::number(n_module + 1);
	QString NAME_MODULE = "umi" + N_MODULE;
	QString NAME_VALUE = "value_" + NAME_PRD + NAME_MODULE + "_";
	QString NAME_SIGNAL = NAME_PRD + NAME_MODULE + "_";

	if(n_prd == 0)
		OY_OS_UMI = "OY2_OS_UMI_";
	if(n_prd == 1)
		OY_OS_UMI = "OY3_OS_UMI_";

	bool state = canalAsku[OY_OS_UMI + N_MODULE] == ELEM_NORMA;
	bool offUmi = sigmap[NAME_PRD + NAME_MODULE + "Link"];

	QString no_info_text = "** нет информации **";
	QString no_module_text = "** нет модуля **";
	QString text_value;
	QString user_value;
	quint8 element;

//TEMPERATURE
	if(!state)
	{
		text_value = no_info_text;
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		text_value = no_module_text;
		element = ELEM_NOT;
	}
	else
	{
		if(sigmap[NAME_SIGNAL + "sensor"])
			text_value = "Датчик неисправен";
		else
			text_value.sprintf("%d", valmap[NAME_VALUE + "temperature"].toUInt());

		if(sigmap[NAME_SIGNAL + "sensor"] || sigmap[NAME_SIGNAL + "temperature"])
			element = ELEM_AVAR;
		else
			element = ELEM_NORMA;
	}
if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@temperature"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@temperature"].setText(text_value);
}

//IN_POWER
	if(!state)
	{
		text_value = no_info_text;
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		text_value = no_module_text;
		element = ELEM_NOT;
	}
	else
	{
		text_value.sprintf("%d", valmap[NAME_VALUE + "in_power"].toUInt());

		if(sigmap[NAME_SIGNAL + "in_power_low"] || sigmap[NAME_SIGNAL + "in_power_high"])
			element = ELEM_AVAR;
		else
			element = ELEM_NORMA;
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@in_power"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@in_power"].setText(text_value);
}

//OUT_POWER
	if(!state)
	{
		text_value = no_info_text;
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		text_value = no_module_text;
		element = ELEM_NOT;
	}
	else
	{
		text_value.sprintf("%d", valmap[NAME_VALUE + "out_power"].toUInt());

		if(sigmap[NAME_SIGNAL + "out_power"])
			element = ELEM_AVAR;
		else
			element = ELEM_NORMA;
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@out_power"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@out_power"].setText(text_value);
}

//KSVN
	if(!state)
	{
		text_value = no_info_text;
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		text_value = no_module_text;
		element = ELEM_NOT;
	}
	else
	{
		text_value.sprintf("%d", valmap[NAME_VALUE + "ksvn"].toUInt());

		if(sigmap[NAME_SIGNAL + "ksvn"])
			element = ELEM_AVAR;
		else
			element = ELEM_NORMA;
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@ksvn"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@ksvn"].setText(text_value);
}

//U_POWER
	if(!state)
	{
		text_value = no_info_text;
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		text_value = no_module_text;
		element = ELEM_NOT;
	}
	else
	{
		text_value.sprintf("%d", valmap[NAME_VALUE + "u_power"].toUInt());

		if(sigmap[NAME_SIGNAL + "u_power"])
			element = ELEM_AVAR;
		else
			element = ELEM_NORMA;
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@u_power"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@u_power"].setText(text_value);
}

//SERIAL
	if(!state)
	{
		text_value = no_info_text;
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		text_value = no_module_text;
		element = ELEM_NOT;
	}
	else
	{
		quint8 serial_hi = valmap[NAME_VALUE + "serial_hi"].toUInt();
		quint8 serial_mi = valmap[NAME_VALUE + "serial_mi"].toUInt();
		quint8 serial_lo = valmap[NAME_VALUE + "serial_lo"].toUInt();
		text_value = CanalAsku::moduleUmiSerial(serial_hi, serial_mi, serial_lo);
		element = ELEM_NORMA;
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@serial"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@serial"].setText(text_value);
}

//TIME
	if(!state)
	{
		text_value = no_info_text;
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		text_value = no_module_text;
		element = ELEM_NOT;
	}
	else
	{
		quint8 time_hour_hi = valmap[NAME_VALUE + "time_hour_hi"].toUInt();
		quint8 time_hour_lo = valmap[NAME_VALUE + "time_hour_lo"].toUInt();
		quint8 time_minute = valmap[NAME_VALUE + "time_minute"].toUInt();
		text_value.sprintf("%d:%02d", MAKEWORD(time_hour_lo, time_hour_hi), time_minute);
		element = ELEM_NORMA;
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@time"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@time"].setText(text_value);
}

//PHASE_DEF
	if(!state)
	{
		text_value = no_info_text;
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		text_value = no_module_text;
		element = ELEM_NOT;
	}
	else
	{
		quint8 phase_def = valmap[NAME_VALUE + "phase_def"].toUInt();
		double phase_def_d = (double)phase_def * 5.625;
		text_value.sprintf("%0d (%5.3f)", phase_def, phase_def_d);
		element = ELEM_NORMA;
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@phase_def"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@phase_def"].setText(text_value);
}

//PHASE_SET
	if(!state)
	{
		text_value = no_info_text;
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		text_value = no_module_text;
		element = ELEM_NOT;
	}
	else
	{
		quint8 phase_set = valmap[NAME_VALUE + "phase_set"].toUInt();
		double phase_set_d = (double)phase_set * 5.625;
		text_value.sprintf("%0d (%5.3f)", phase_set, phase_set_d);
		element = ELEM_NORMA;
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@phase_set"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@phase_set"].setText(text_value);
}

//IMPULSE
	if(!state)
	{
//		text_value = no_info_text;
		user_value = "undef";
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		user_value = "nomod";
		element = ELEM_NOT;
	}
	else
	{
		if(sigmap[NAME_SIGNAL + "power380_on"] && sigmap[NAME_SIGNAL + "power_on"])
		{
			if(sigmap[NAME_SIGNAL + "no_impulse"])
			{
//				text_value = QString("ОТСУТСТВУЮТ");
				user_value = "noimpulse";
				element = ELEM_AVAR;
			}
			else if(sigmap[NAME_SIGNAL + "impulse"])
			{
//				text_value = QString("ПЕРЕГРУЗКА");
				user_value = "overload";
				element = ELEM_AVAR;
			}
			else
			{
//				text_value = QString("НОРМА");
				user_value = "on";
				element = ELEM_NORMA;
			}
		}
		else
		{
			if(sigmap[NAME_SIGNAL + "no_impulse"])
			{
//				text_value = QString("ОТСУТСТВУЮТ");
				user_value = "noimpulse";
				element = ELEM_AVAR;
			}
			else if(sigmap[NAME_SIGNAL + "impulse"])
			{
//				text_value = QString("ПЕРЕГРУЗКА");
				user_value = "overload";
				element = ELEM_AVAR;
			}
			else
			{
//				text_value = QString("ОТКЛ");
				user_value = "off";
				element = ELEM_NOT;
			}
		}
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@impulse"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@impulse"].setUser(user_value);
//	elements[NAME_PRD + NAME_MODULE + "@impulse"].setText(text_value);
}

//UMI_POWER_ON
	if(!state)
	{
//		text_value = no_info_text;
		user_value = "undef";
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		user_value = "nomod";
		element = ELEM_NOT;
	}
	else
	{
		if(sigmap[NAME_SIGNAL + "u_power"])
		{
//			text_value = QString("АВАРИЯ");
			user_value = "fail";
			element = ELEM_AVAR;
		}
		else if(sigmap[NAME_SIGNAL + "power_on"])
		{
//			text_value = QString("ВКЛ");
			user_value = "on";
			element = ELEM_NORMA;
		}
		else
		{
//			text_value = QString("ОТКЛ");
			user_value = "off";
			element = ELEM_NOT;
		}
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@power_on"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@power_on"].setUser(user_value);
//	elements[NAME_PRD + NAME_MODULE + "@power_on"].setText(text_value);
}

//UMI_POWER_380V_ON
	if(!state)
	{
//		text_value = no_info_text;
		user_value = "undef";
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		user_value = "nomod";
		element = ELEM_NOT;
	}
	else
	{
		if(sigmap[NAME_SIGNAL + "power380_on"])
		{
//			text_value = QString("ВКЛ");
			user_value = "on";
			element = ELEM_NORMA;
		}
		else
		{
//			text_value = QString("ОТКЛ");
			user_value = "off";
			element = ELEM_NOT;
		}
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@power380v_on"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@power380v_on"].setUser(user_value);
//	elements[NAME_PRD + NAME_MODULE + "@power380v_on"].setText(text_value);
}

//UMI_SVCH_ON
	if(!state)
	{
//		text_value = no_info_text;
		user_value = "undef";
		element = ELEM_NOT;
	}
	else if(offUmi)
	{
		user_value = "nomod";
		element = ELEM_NOT;
	}
	else
	{
		if(sigmap[NAME_SIGNAL + "svch_on"])
		{
//			text_value = QString("ВКЛ");
			user_value = "on";
			element = ELEM_NORMA;
		}
		else
		{
//			text_value = QString("ОТКЛ");
			user_value = "off";
			element = ELEM_NOT;
		}
	}

if(m_isMain)
{
	elements[NAME_PRD + NAME_MODULE + "@svch_on"] = stateToString(element);
	elements[NAME_PRD + NAME_MODULE + "@svch_on"].setUser(user_value);
//	elements[NAME_PRD + NAME_MODULE + "@svch_on"].setText(text_value);
}
}

// ----------------------------------------------------------------------------
