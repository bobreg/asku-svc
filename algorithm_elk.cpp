#include "../common/logger.h"
#include "globalvar.h"
#include "algorithm.h"
#include "canalasku_data.h"

// ----------------------------------------------------------------------------
void AskuAlgorithm::fun124EE02_raf()
{
	int nAvar = 0, nError = 0;

//ОК
	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && b124yy08["d2vv056"] == ELEM_NORMA)
		b124ee02["isOk"] = ELEM_NORMA;
	else
		b124ee02["isOk"] = ELEM_NOT;

//АО РЛС
	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && sigmap["elk_aorls"])
		b124ee02["aorls"] = ELEM_AVAR;
	else
		b124ee02["aorls"] = ELEM_NOT;
	messages["aorls"] = b124ee02["aorls"];

//АО РЛС (РГДВ)
	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && sigmap["elk_aorls"])
	{
		elementsRgdv["124yy08_aorls"] = ELEM_AVAR;
		elementsRgdv["124yy08_aorls"] = "АО РЛС";
	}
	else if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && !sigmap["elk_aorls"])
	{
		elementsRgdv["124yy08_aorls"] = ELEM_NORMA;
		elementsRgdv["124yy08_aorls"] = "ОТКЛ";
	}
	else
	{
		elementsRgdv["124yy08_aorls"] = ELEM_DISABLE;
		elementsRgdv["124yy08_aorls"] = "НЕ КОНТР";
	}

//ОТКЛ 380В КОНТ
	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && sigmap["elk_otkl_cont_380v"])
		b124ee02["otkl_cont_380v"] = ELEM_AVAR;
	else if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && !sigmap["elk_otkl_cont_380v"])
		b124ee02["otkl_cont_380v"] = ELEM_NORMA;
	else
		b124ee02["otkl_cont_380v"] = ELEM_NOT;
	messages["124ee02@otkl_cont_380v"] = b124ee02["otkl_cont_380v"];

//ПРЕДОХРАНИТЕЛИ
//27V ПИТАН СИГН
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_pit_signal"])
	{
		b124ee02["p27v_pit_signal"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_pit_signal"])
		b124ee02["p27v_pit_signal"] = ELEM_NORMA;
	else
		b124ee02["p27v_pit_signal"] = ELEM_NOT;
	messages["124ee02@p27v_pit_signal"] = b124ee02["p27v_pit_signal"];

//27V 124УУ03 1
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_124yy03_1"])
	{
		b124ee02["p27v_124yy03_1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_124yy03_1"])
		b124ee02["p27v_124yy03_1"] = ELEM_NORMA;
	else
		b124ee02["p27v_124yy03_1"] = ELEM_NOT;
	messages["124ee02@p27v_124yy03_1"] = b124ee02["p27v_124yy03_1"];

//27V 124УУ03 1 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_124yy03_1"])
	{
		elementsRgdv["124yy08_p27v_124yy03_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_124yy03_1"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_124yy03_1"])
	{
		elementsRgdv["124yy08_p27v_124yy03_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_124yy03_1"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_124yy03_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_124yy03_1"] = "НЕ КОНТР";
	}

//27V 124УУ03 2
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_124yy03_2"])
	{
		b124ee02["p27v_124yy03_2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_124yy03_2"])
		b124ee02["p27v_124yy03_2"] = ELEM_NORMA;
	else
		b124ee02["p27v_124yy03_2"] = ELEM_NOT;
	messages["124ee02@p27v_124yy03_2"] = b124ee02["p27v_124yy03_2"];

//27V 124УУ03 2 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_124yy03_2"])
	{
		elementsRgdv["124yy08_p27v_124yy03_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_124yy03_2"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_124yy03_2"])
	{
		elementsRgdv["124yy08_p27v_124yy03_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_124yy03_2"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_124yy03_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_124yy03_2"] = "НЕ КОНТР";
	}

//27V 123ББ02
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_123bb02"])
	{
		b124ee02["p27v_123bb02"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_123bb02"])
		b124ee02["p27v_123bb02"] = ELEM_NORMA;
	else
		b124ee02["p27v_123bb02"] = ELEM_NOT;
	messages["124ee02@p27v_123bb02"] = b124ee02["p27v_123bb02"];

//27V 123ББ02 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_123bb02"])
	{
		elementsRgdv["124yy08_p27v_123bb02"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_123bb02"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_123bb02"])
	{
		elementsRgdv["124yy08_p27v_123bb02"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_123bb02"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_123bb02"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_123bb02"] = "НЕ КОНТР";
	}

//27V ПИТ АВТ
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_pit_avt"])
	{
		b124ee02["p27v_pit_avt"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_pit_avt"])
		b124ee02["p27v_pit_avt"] = ELEM_NORMA;
	else
		b124ee02["p27v_pit_avt"] = ELEM_NOT;
	messages["124ee02@p27v_pit_avt"] = b124ee02["p27v_pit_avt"];

//27V ПИТ АВТ (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_pit_avt"])
	{
		elementsRgdv["124yy08_p27v_pit_avt"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_pit_avt"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_pit_avt"])
	{
		elementsRgdv["124yy08_p27v_pit_avt"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_pit_avt"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_pit_avt"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_pit_avt"] = "НЕ КОНТР";
	}

//АВТ ВКЛ
	b124ee02["isAvtOk"] = (b124ee02["p27v_pit_avt"] == ELEM_NORMA) ? ELEM_NORMA : ELEM_NOT;

//27V РЕВУН 1
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_howl1"])
	{
		b124ee02["p27v_howl1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_howl1"])
		b124ee02["p27v_howl1"] = ELEM_NORMA;
	else
		b124ee02["p27v_howl1"] = ELEM_NOT;
	messages["124ee02@p27v_howl1"] = b124ee02["p27v_howl1"];

//27V РЕВУН 1 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_howl1"])
	{
		elementsRgdv["124yy08_p27v_howl_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_howl_1"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_howl1"])
	{
		elementsRgdv["124yy08_p27v_howl_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_howl_1"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_howl_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_howl_1"] = "НЕ КОНТР";
	}

//27V РЕВУН 2
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_howl2"])
	{
		b124ee02["p27v_howl2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_howl2"])
		b124ee02["p27v_howl2"] = ELEM_NORMA;
	else
		b124ee02["p27v_howl2"] = ELEM_NOT;
	messages["124ee02@p27v_howl2"] = b124ee02["p27v_howl2"];

//27V РЕВУН 2 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_howl2"])
	{
		elementsRgdv["124yy08_p27v_howl_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_howl_2"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_howl2"])
	{
		elementsRgdv["124yy08_p27v_howl_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_howl_2"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_howl_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_howl_2"] = "НЕ КОНТР";
	}

//27V ПРМ 1
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_prm1"])
	{
		b124ee02["p27v_prm1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_prm1"])
		b124ee02["p27v_prm1"] = ELEM_NORMA;
	else
		b124ee02["p27v_prm1"] = ELEM_NOT;
	messages["124ee02@p27v_prm1"] = b124ee02["p27v_prm1"];

//27V ПРМ 1 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_prm1"])
	{
		elementsRgdv["124yy08_p27v_prm_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_prm_1"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_prm1"])
	{
		elementsRgdv["124yy08_p27v_prm_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_prm_1"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_prm_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_prm_1"] = "НЕ КОНТР";
	}

//27V ПРМ 2
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_prm2"])
	{
		b124ee02["p27v_prm2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_prm2"])
		b124ee02["p27v_prm2"] = ELEM_NORMA;
	else
		b124ee02["p27v_prm2"] = ELEM_NOT;
	messages["124ee02@p27v_prm2"] = b124ee02["p27v_prm2"];

//27V ПРМ 2 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_prm2"])
	{
		elementsRgdv["124yy08_p27v_prm_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_prm_2"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_prm2"])
	{
		elementsRgdv["124yy08_p27v_prm_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_prm_2"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_prm_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_prm_2"] = "НЕ КОНТР";
	}

//27V МСПД
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_mspd"])
	{
		b124ee02["p27v_mspd"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_mspd"])
		b124ee02["p27v_mspd"] = ELEM_NORMA;
	else
		b124ee02["p27v_mspd"] = ELEM_NOT;
	messages["124ee02@p27v_mspd"] = b124ee02["p27v_mspd"];

//27V МСПД (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_mspd"])
	{
		elementsRgdv["124yy08_p27v_mspd"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_mspd"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_mspd"])
	{
		elementsRgdv["124yy08_p27v_mspd"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_mspd"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_mspd"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_mspd"] = "НЕ КОНТР";
	}

//27V А 15
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_a_15_17"])
	{
		b124ee02["p27v_a15"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_a_15_17"])
		b124ee02["p27v_a15"] = ELEM_NORMA;
	else
		b124ee02["p27v_a15"] = ELEM_NOT;
	messages["124ee02@p27v_a15"] = b124ee02["p27v_a15"];

//27V А 16
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_a_15_17"])
	{
		b124ee02["p27v_a16"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_a_15_17"])
		b124ee02["p27v_a16"] = ELEM_NORMA;
	else
		b124ee02["p27v_a16"] = ELEM_NOT;
	messages["124ee02@p27v_a16"] = b124ee02["p27v_a16"];

//27V А 17
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_a_15_17"])
	{
		b124ee02["p27v_a17"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_a_15_17"])
		b124ee02["p27v_a17"] = ELEM_NORMA;
	else
		b124ee02["p27v_a17"] = ELEM_NOT;
	messages["124ee02@p27v_a17"] = b124ee02["p27v_a17"];

//27V А 18
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_a_18_20"])
	{
		b124ee02["p27v_a18"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_a_18_20"])
		b124ee02["p27v_a18"] = ELEM_NORMA;
	else
		b124ee02["p27v_a18"] = ELEM_NOT;
	messages["124ee02@p27v_a18"] = b124ee02["p27v_a18"];

//27V А 19
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_a_18_20"])
	{
		b124ee02["p27v_a19"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_a_18_20"])
		b124ee02["p27v_a19"] = ELEM_NORMA;
	else
		b124ee02["p27v_a19"] = ELEM_NOT;
	messages["124ee02@p27v_a19"] = b124ee02["p27v_a19"];

//27V А 20
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_a_18_20"])
	{
		b124ee02["p27v_a20"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_a_18_20"])
		b124ee02["p27v_a20"] = ELEM_NORMA;
	else
		b124ee02["p27v_a20"] = ELEM_NOT;
	messages["124ee02@p27v_a20"] = b124ee02["p27v_a20"];

//27V ЗУ 1
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_zu1"])
	{
		b124ee02["p27v_zu1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_zu1"])
		b124ee02["p27v_zu1"] = ELEM_NORMA;
	else
		b124ee02["p27v_zu1"] = ELEM_NOT;
	messages["124ee02@p27v_zu1"] = b124ee02["p27v_zu1"];

//27V ЗУ 1 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_zu1"])
	{
		elementsRgdv["124yy08_p27v_zu_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_zu_1"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_zu1"])
	{
		elementsRgdv["124yy08_p27v_zu_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_zu_1"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_zu_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_zu_1"] = "НЕ КОНТР";
	}

//27V ЗУ 2
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_zu2"])
	{
		b124ee02["p27v_zu2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_zu2"])
		b124ee02["p27v_zu2"] = ELEM_NORMA;
	else
		b124ee02["p27v_zu2"] = ELEM_NOT;
	messages["124ee02@p27v_zu2"] = b124ee02["p27v_zu2"];

//27V ЗУ 2 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_zu2"])
	{
		elementsRgdv["124yy08_p27v_zu_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_zu_2"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_zu2"])
	{
		elementsRgdv["124yy08_p27v_zu_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_zu_2"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_zu_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_zu_2"] = "НЕ КОНТР";
	}

//27V ПС 1
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_ps1"])
	{
		b124ee02["p27v_ps1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_ps1"])
		b124ee02["p27v_ps1"] = ELEM_NORMA;
	else
		b124ee02["p27v_ps1"] = ELEM_NOT;
	messages["124ee02@p27v_ps1"] = b124ee02["p27v_ps1"];

//27V ПС 1 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_ps1"])
	{
		elementsRgdv["124yy08_p27v_ps_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_ps_1"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_ps1"])
	{
		elementsRgdv["124yy08_p27v_ps_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_ps_1"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_ps_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_ps_1"] = "НЕ КОНТР";
	}

//27V ПС 2
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_ps2"])
	{
		b124ee02["p27v_ps2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_ps2"])
		b124ee02["p27v_ps2"] = ELEM_NORMA;
	else
		b124ee02["p27v_ps2"] = ELEM_NOT;
	messages["124ee02@p27v_ps2"] = b124ee02["p27v_ps2"];

//27V ПС 2 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_ps2"])
	{
		elementsRgdv["124yy08_p27v_ps_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_ps_2"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_ps2"])
	{
		elementsRgdv["124yy08_p27v_ps_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_ps_2"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_ps_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_ps_2"] = "НЕ КОНТР";
	}

//27V 123ГВ02 1
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_123gv02_1"])
	{
		b124ee02["p27v_123gv02_1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_123gv02_1"])
		b124ee02["p27v_123gv02_1"] = ELEM_NORMA;
	else
		b124ee02["p27v_123gv02_1"] = ELEM_NOT;
	messages["124ee02@p27v_123gv02_1"] = b124ee02["p27v_123gv02_1"];

//27V 123ГВ02 1 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_123gv02_1"])
	{
		elementsRgdv["124yy08_p27v_123gv02_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_123gv02_1"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_123gv02_1"])
	{
		elementsRgdv["124yy08_p27v_123gv02_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_123gv02_1"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_123gv02_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_123gv02_1"] = "НЕ КОНТР";
	}

//27V 123ГВ02 2
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_123gv02_2"])
	{
		b124ee02["p27v_123gv02_2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_123gv02_2"])
		b124ee02["p27v_123gv02_2"] = ELEM_NORMA;
	else
		b124ee02["p27v_123gv02_2"] = ELEM_NOT;
	messages["124ee02@p27v_123gv02_2"] = b124ee02["p27v_123gv02_2"];

//27V 123ГВ02 2 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_123gv02_2"])
	{
		elementsRgdv["124yy08_p27v_123gv02_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_123gv02_2"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_123gv02_2"])
	{
		elementsRgdv["124yy08_p27v_123gv02_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_123gv02_2"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_123gv02_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_123gv02_2"] = "НЕ КОНТР";
	}

//27V АЗИМ ДАТЧ 1
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_azs1"])
	{
		b124ee02["p27v_azs1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_azs1"])
		b124ee02["p27v_azs1"] = ELEM_NORMA;
	else
		b124ee02["p27v_azs1"] = ELEM_NOT;
	messages["124ee02@p27v_azs1"] = b124ee02["p27v_azs1"];

//27V АЗИМ ДАТЧ 1 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_azs1"])
	{
		elementsRgdv["124yy08_p27v_azsens_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_azsens_1"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_azs1"])
	{
		elementsRgdv["124yy08_p27v_azsens_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_azsens_1"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_azsens_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_azsens_1"] = "НЕ КОНТР";
	}

//27V АЗИМ ДАТЧ 2
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_azs2"])
	{
		b124ee02["p27v_azs2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_azs2"])
		b124ee02["p27v_azs2"] = ELEM_NORMA;
	else
		b124ee02["p27v_azs2"] = ELEM_NOT;
	messages["124ee02@p27v_azs2"] = b124ee02["p27v_azs2"];

//27V АЗИМ ДАТЧ 2 (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_azs2"])
	{
		elementsRgdv["124yy08_p27v_azsens_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_azsens_2"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_azs2"])
	{
		elementsRgdv["124yy08_p27v_azsens_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_azsens_2"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_azsens_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_azsens_2"] = "НЕ КОНТР";
	}

//27V ГШ
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_gsh"])
	{
		b124ee02["p27v_gsh"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_gsh"])
		b124ee02["p27v_gsh"] = ELEM_NORMA;
	else
		b124ee02["p27v_gsh"] = ELEM_NOT;
	messages["124ee02@p27v_gsh"] = b124ee02["p27v_gsh"];

//27V ГШ (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_gsh"])
	{
		elementsRgdv["124yy08_p27v_gsh"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_gsh"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_gsh"])
	{
		elementsRgdv["124yy08_p27v_gsh"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_gsh"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_gsh"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_gsh"] = "НЕ КОНТР";
	}

//27V ОПУ
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_opu"])
	{
		b124ee02["p27v_opu"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_opu"])
		b124ee02["p27v_opu"] = ELEM_NORMA;
	else
		b124ee02["p27v_opu"] = ELEM_NOT;
	messages["124ee02@p27v_opu"] = b124ee02["p27v_opu"];

//27V ОПУ (РГДВ)
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_opu"])
	{
		elementsRgdv["124yy08_p27v_opu"] = ELEM_AVAR;
		elementsRgdv["124yy08_p27v_opu"] = "НЕ ИСПРАВЕН";
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_opu"])
	{
		elementsRgdv["124yy08_p27v_opu"] = ELEM_NORMA;
		elementsRgdv["124yy08_p27v_opu"] = "ИСПРАВЕН";
	}
	else
	{
		elementsRgdv["124yy08_p27v_opu"] = ELEM_DISABLE;
		elementsRgdv["124yy08_p27v_opu"] = "НЕ КОНТР";
	}

//27V А 31
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_a_31_32"])
	{
		b124ee02["p27v_a31"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_a_31_32"])
		b124ee02["p27v_a31"] = ELEM_NORMA;
	else
		b124ee02["p27v_a31"] = ELEM_NOT;
	messages["124ee02@p27v_a31"] = b124ee02["p27v_a31"];

//27V А 32
	if(b124ee02["isOk"] == ELEM_NORMA && sigmap["elk_p27v_a_31_32"])
	{
		b124ee02["p27v_a32"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && !sigmap["elk_p27v_a_31_32"])
		b124ee02["p27v_a32"] = ELEM_NORMA;
	else
		b124ee02["p27v_a32"] = ELEM_NOT;
	messages["124ee02@p27v_a32"] = b124ee02["p27v_a32"];

//АВТОМАТЫ
//QF АККУМ
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_accum"])
	{
		b124ee02["qf_accum"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_accum"])
		b124ee02["qf_accum"] = ELEM_NORMA;
	else
		b124ee02["qf_accum"] = ELEM_NOT;
	messages["124ee02@qf_accum"] = b124ee02["qf_accum"];

//QF АККУМ (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_accum"])
	{
		elementsRgdv["124yy08_qf_accum"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_accum"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_accum"])
	{
		elementsRgdv["124yy08_qf_accum"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_accum"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_accum"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_accum"] = "НЕ КОНТР";
	}

//QF 124УУ08
//	b124ee02["qf_124yy08"] = ELEM_DISABLE;
/*
	if(b124ee02["isAvtOk"] == ELEM_NORMA)
		b124ee02["qf_124yy08"] = ELEM_NORMA;
	else
		b124ee02["qf_124yy08"] = ELEM_NOT;
*/
	if(b124ee02["isAvtOk"] == ELEM_NORMA && (sigmap["prd1_qf124yy08"] || sigmap["prd2_qf124yy08"]))
	{
		b124ee02["qf_124yy08"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["prd1_qf124yy08"] && !sigmap["prd2_qf124yy08"])
		b124ee02["qf_124yy08"] = ELEM_NORMA;
	else
		b124ee02["qf_124yy08"] = ELEM_NOT;
	messages["124ee02@qf_124yy08"] = b124ee02["qf_124yy08"];

//QF 124УГ02
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_124yg02"])
	{
		b124ee02["qf_124yg02"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_124yg02"])
		b124ee02["qf_124yg02"] = ELEM_NORMA;
	else
		b124ee02["qf_124yg02"] = ELEM_NOT;
	messages["124ee02@qf_124yg02"] = b124ee02["qf_124yg02"];

//QF 124УГ02 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_124yg02"])
	{
		elementsRgdv["124yy08_qf_124yg02"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_124yg02"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_124yg02"])
	{
		elementsRgdv["124yy08_qf_124yg02"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_124yg02"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_124yg02"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_124yg02"] = "НЕ КОНТР";
	}

//QF 27V БУФ
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_27v_buf"])
	{
		b124ee02["qf_27v_buf"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_27v_buf"])
		b124ee02["qf_27v_buf"] = ELEM_NORMA;
	else
		b124ee02["qf_27v_buf"] = ELEM_NOT;
	messages["124ee02@qf_27v_buf"] = b124ee02["qf_27v_buf"];

//QF 27V БУФ (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_27v_buf"])
	{
		elementsRgdv["124yy08_qf_27v_buf"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_27v_buf"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_27v_buf"])
	{
		elementsRgdv["124yy08_qf_27v_buf"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_27v_buf"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_27v_buf"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_27v_buf"] = "НЕ КОНТР";
	}

//QF ПОС
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_pos"])
	{
		b124ee02["qf_pos"] = ELEM_AVAR;
//		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_pos"])
		b124ee02["qf_pos"] = ELEM_NORMA;
	else
		b124ee02["qf_pos"] = ELEM_NOT;
	messages["124ee02@qf_pos"] = b124ee02["qf_pos"];

//QF ПРМ1
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_prm1"])
	{
		b124ee02["qf_prm1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_prm1"])
		b124ee02["qf_prm1"] = ELEM_NORMA;
	else
		b124ee02["qf_prm1"] = ELEM_NOT;
	messages["124ee02@qf_prm1"] = b124ee02["qf_prm1"];

//QF ПРМ1 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_prm1"])
	{
		elementsRgdv["124yy08_qf_prm_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_prm_1"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_prm1"])
	{
		elementsRgdv["124yy08_qf_prm_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_prm_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_prm_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_prm_1"] = "НЕ КОНТР";
	}

//QF ПРМ2
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_prm2"])
	{
		b124ee02["qf_prm2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_prm2"])
		b124ee02["qf_prm2"] = ELEM_NORMA;
	else
		b124ee02["qf_prm2"] = ELEM_NOT;
	messages["124ee02@qf_prm2"] = b124ee02["qf_prm2"];

//QF ПРМ2 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_prm2"])
	{
		elementsRgdv["124yy08_qf_prm_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_prm_2"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_prm2"])
	{
		elementsRgdv["124yy08_qf_prm_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_prm_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_prm_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_prm_2"] = "НЕ КОНТР";
	}

//QF ТРМ
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_trm"])
	{
		b124ee02["qf_trm"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_trm"])
		b124ee02["qf_trm"] = ELEM_NORMA;
	else
		b124ee02["qf_trm"] = ELEM_NOT;
	messages["124ee02@qf_trm"] = b124ee02["qf_trm"];

//QF 27V Ц
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_27v_c"])
	{
		b124ee02["qf_27v_c"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_27v_c"])
		b124ee02["qf_27v_c"] = ELEM_NORMA;
	else
		b124ee02["qf_27v_c"] = ELEM_NOT;
	messages["124ee02@qf_27v_c"] = b124ee02["qf_27v_c"];

//QF 27V Ц (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_27v_c"])
	{
		elementsRgdv["124yy08_qf_27v_c"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_27v_c"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_27v_c"])
	{
		elementsRgdv["124yy08_qf_27v_c"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_27v_c"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_27v_c"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_27v_c"] = "НЕ КОНТР";
	}

//QF АВАР ОСВ
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_avar_osv"])
	{
		b124ee02["qf_avar_osv"] = ELEM_AVAR;
//		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_avar_osv"])
		b124ee02["qf_avar_osv"] = ELEM_NORMA;
	else
		b124ee02["qf_avar_osv"] = ELEM_NOT;
	messages["124ee02@qf_avar_osv"] = b124ee02["qf_avar_osv"];

//QF СЕТЬ 380V 50HZ
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_380v_set"])
	{
		b124ee02["qf_380v_set"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_380v_set"])
		b124ee02["qf_380v_set"] = ELEM_NORMA;
	else
		b124ee02["qf_380v_set"] = ELEM_NOT;
	messages["124ee02@qf_380v_set"] = b124ee02["qf_380v_set"];

//QF СЕТЬ 380V 50HZ (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_380v_set"])
	{
		elementsRgdv["124yy08_qf_set_380v"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_set_380v"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_380v_set"])
	{
		elementsRgdv["124yy08_qf_set_380v"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_set_380v"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_set_380v"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_set_380v"] = "НЕ КОНТР";
	}

//QF ОСВ АПМ
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_osv_apm"])
	{
		b124ee02["qf_osv_apm"] = ELEM_AVAR;
//		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_osv_apm"])
		b124ee02["qf_osv_apm"] = ELEM_NORMA;
	else
		b124ee02["qf_osv_apm"] = ELEM_NOT;
	messages["124ee02@qf_osv_apm"] = b124ee02["qf_osv_apm"];

//QF ОСВ ПЕРИМ
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_osv_perim"])
	{
		b124ee02["qf_osv_perim"] = ELEM_AVAR;
//		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_osv_perim"])
		b124ee02["qf_osv_perim"] = ELEM_NORMA;
	else
		b124ee02["qf_osv_perim"] = ELEM_NOT;
	messages["124ee02@qf_osv_perim"] = b124ee02["qf_osv_perim"];

//QF 380V 50HZ РПУ
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_380v_rpu"])
	{
		b124ee02["qf_380v_rpu"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_380v_rpu"])
		b124ee02["qf_380v_rpu"] = ELEM_NORMA;
	else
		b124ee02["qf_380v_rpu"] = ELEM_NOT;
	messages["124ee02@qf_380v_rpu"] = b124ee02["qf_380v_rpu"];

//QF 380V 50HZ РПУ (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_380v_rpu"])
	{
		elementsRgdv["124yy08_qf_380v_rpu"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_380v_rpu"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_380v_rpu"])
	{
		elementsRgdv["124yy08_qf_380v_rpu"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_380v_rpu"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_380v_rpu"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_380v_rpu"] = "НЕ КОНТР";
	}

//QF ТЕПЛОВЕНТ
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_teplovent"])
	{
		b124ee02["qf_teplovent"] = ELEM_AVAR;
//		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_teplovent"])
		b124ee02["qf_teplovent"] = ELEM_NORMA;
	else
		b124ee02["qf_teplovent"] = ELEM_NOT;
	messages["124ee02@qf_teplovent"] = b124ee02["qf_teplovent"];

//QF СОТР
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_sotr"])
	{
		b124ee02["qf_sotr"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_sotr"])
		b124ee02["qf_sotr"] = ELEM_NORMA;
	else
		b124ee02["qf_sotr"] = ELEM_NOT;
	messages["124ee02@qf_sotr"] = b124ee02["qf_sotr"];

//QF РОЗЕТ 220В (был QF ЗОЛ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_rozet_220v"])
	{
		b124ee02["qf_rozet_220v"] = ELEM_AVAR;
//		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_rozet_220v"])
		b124ee02["qf_rozet_220v"] = ELEM_NORMA;
	else
		b124ee02["qf_rozet_220v"] = ELEM_NOT;
	messages["124ee02@qf_rozet_220v"] = b124ee02["qf_rozet_220v"];

//QF ИБП 1
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_ups1"])
	{
		b124ee02["qf_ups1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_ups1"])
		b124ee02["qf_ups1"] = ELEM_NORMA;
	else
		b124ee02["qf_ups1"] = ELEM_NOT;
	messages["124ee02@qf_ups1"] = b124ee02["qf_ups1"];

//QF ИБП 1 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_ups1"])
	{
		elementsRgdv["124yy08_qf_ups_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_ups_1"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_ups1"])
	{
		elementsRgdv["124yy08_qf_ups_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_ups_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_ups_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_ups_1"] = "НЕ КОНТР";
	}

//QF ПРД 1
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_prd1"])
	{
		b124ee02["qf_prd1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_prd1"])
		b124ee02["qf_prd1"] = ELEM_NORMA;
	else
		b124ee02["qf_prd1"] = ELEM_NOT;
	messages["124ee02@qf_prd1"] = b124ee02["qf_prd1"];

//QF ПРД 1 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_prd1"])
	{
		elementsRgdv["124yy08_qf_prd_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_prd_1"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_prd1"])
	{
		elementsRgdv["124yy08_qf_prd_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_prd_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_prd_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_prd_1"] = "НЕ КОНТР";
	}

//QF 124УУ03 1
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_124yy03_1"])
	{
		b124ee02["qf_124yy03_1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_124yy03_1"])
		b124ee02["qf_124yy03_1"] = ELEM_NORMA;
	else
		b124ee02["qf_124yy03_1"] = ELEM_NOT;
	messages["124ee02@qf_124yy03_1"] = b124ee02["qf_124yy03_1"];

//QF 124УУ03 1 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_124yy03_1"])
	{
		elementsRgdv["124yy08_qf_124yy03_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_124yy03_1"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_124yy03_1"])
	{
		elementsRgdv["124yy08_qf_124yy03_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_124yy03_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_124yy03_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_124yy03_1"] = "НЕ КОНТР";
	}

//QF КМВРЛ 1
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_kmvrl1"])
	{
		b124ee02["qf_kmvrl1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_kmvrl1"])
		b124ee02["qf_kmvrl1"] = ELEM_NORMA;
	else
		b124ee02["qf_kmvrl1"] = ELEM_NOT;
	messages["124ee02@qf_kmvrl1"] = b124ee02["qf_kmvrl1"];

//QF КМВРЛ 1 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_kmvrl1"])
	{
		elementsRgdv["124yy08_qf_kmvrl_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_kmvrl_1"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_kmvrl1"])
	{
		elementsRgdv["124yy08_qf_kmvrl_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_kmvrl_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_kmvrl_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_kmvrl_1"] = "НЕ КОНТР";
	}

//QF АПП ОБР 1
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_obr1"])
	{
		b124ee02["qf_obr1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_obr1"])
		b124ee02["qf_obr1"] = ELEM_NORMA;
	else
		b124ee02["qf_obr1"] = ELEM_NOT;
	messages["124ee02@qf_obr1"] = b124ee02["qf_obr1"];

//QF АПП ОБР 1 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_obr1"])
	{
		elementsRgdv["124yy08_qf_obr_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_obr_1"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_obr1"])
	{
		elementsRgdv["124yy08_qf_obr_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_obr_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_obr_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_obr_1"] = "НЕ КОНТР";
	}

//QF КОНДИЦИОНЕР 1
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_cond1"])
	{
		b124ee02["qf_cond1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_cond1"])
		b124ee02["qf_cond1"] = ELEM_NORMA;
	else
		b124ee02["qf_cond1"] = ELEM_NOT;
	messages["124ee02@qf_cond1"] = b124ee02["qf_cond1"];

//QF КОНДИЦИОНЕР 1 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_cond1"])
	{
		elementsRgdv["124yy08_qf_cond_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_cond_1"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_cond1"])
	{
		elementsRgdv["124yy08_qf_cond_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_cond_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_cond_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_cond_1"] = "НЕ КОНТР";
	}

//QF 123ББ01-1
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_123bb01_1"])
	{
		b124ee02["qf_123bb01_1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_123bb01_1"])
		b124ee02["qf_123bb01_1"] = ELEM_NORMA;
	else
		b124ee02["qf_123bb01_1"] = ELEM_NOT;
	messages["124ee02@qf_123bb01_1"] = b124ee02["qf_123bb01_1"];

//QF 123ББ01-1 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_123bb01_1"])
	{
		elementsRgdv["124yy08_qf_123bb01_1"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_123bb01_1"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_123bb01_1"])
	{
		elementsRgdv["124yy08_qf_123bb01_1"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_123bb01_1"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_123bb01_1"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_123bb01_1"] = "НЕ КОНТР";
	}

//QF 123ББ01-2
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_123bb01_2"])
	{
		b124ee02["qf_123bb01_2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_123bb01_2"])
		b124ee02["qf_123bb01_2"] = ELEM_NORMA;
	else
		b124ee02["qf_123bb01_2"] = ELEM_NOT;
	messages["124ee02@qf_123bb01_2"] = b124ee02["qf_123bb01_2"];

//QF 123ББ01-2 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_123bb01_2"])
	{
		elementsRgdv["124yy08_qf_123bb01_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_123bb01_2"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_123bb01_2"])
	{
		elementsRgdv["124yy08_qf_123bb01_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_123bb01_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_123bb01_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_123bb01_2"] = "НЕ КОНТР";
	}

//QF ИБП 2
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_ups2"])
	{
		b124ee02["qf_ups2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_ups2"])
		b124ee02["qf_ups2"] = ELEM_NORMA;
	else
		b124ee02["qf_ups2"] = ELEM_NOT;
	messages["124ee02@qf_ups2"] = b124ee02["qf_ups2"];

//QF ИБП 2 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_ups2"])
	{
		elementsRgdv["124yy08_qf_ups_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_ups_2"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_ups2"])
	{
		elementsRgdv["124yy08_qf_ups_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_ups_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_ups_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_ups_2"] = "НЕ КОНТР";
	}

//QF ПРД 2
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_prd2"])
	{
		b124ee02["qf_prd2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_prd2"])
		b124ee02["qf_prd2"] = ELEM_NORMA;
	else
		b124ee02["qf_prd2"] = ELEM_NOT;
	messages["124ee02@qf_prd2"] = b124ee02["qf_prd2"];

//QF ПРД 2 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_prd2"])
	{
		elementsRgdv["124yy08_qf_prd_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_prd_2"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_prd2"])
	{
		elementsRgdv["124yy08_qf_prd_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_prd_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_prd_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_prd_2"] = "НЕ КОНТР";
	}

//QF 124УУ03 2
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_124yy03_2"])
	{
		b124ee02["qf_124yy03_2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_124yy03_2"])
		b124ee02["qf_124yy03_2"] = ELEM_NORMA;
	else
		b124ee02["qf_124yy03_2"] = ELEM_NOT;
	messages["124ee02@qf_124yy03_2"] = b124ee02["qf_124yy03_2"];

//QF 124УУ03 2 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_124yy03_2"])
	{
		elementsRgdv["124yy08_qf_124yy03_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_124yy03_2"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_124yy03_2"])
	{
		elementsRgdv["124yy08_qf_124yy03_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_124yy03_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_124yy03_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_124yy03_2"] = "НЕ КОНТР";
	}

//QF КМВРЛ 2
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_kmvrl2"])
	{
		b124ee02["qf_kmvrl2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_kmvrl2"])
		b124ee02["qf_kmvrl2"] = ELEM_NORMA;
	else
		b124ee02["qf_kmvrl2"] = ELEM_NOT;
	messages["124ee02@qf_kmvrl2"] = b124ee02["qf_kmvrl2"];

//QF КМВРЛ 2 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_kmvrl2"])
	{
		elementsRgdv["124yy08_qf_kmvrl_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_kmvrl_2"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_kmvrl2"])
	{
		elementsRgdv["124yy08_qf_kmvrl_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_kmvrl_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_kmvrl_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_kmvrl_2"] = "НЕ КОНТР";
	}

//QF АПП ОБР 2
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_obr2"])
	{
		b124ee02["qf_obr2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_obr2"])
		b124ee02["qf_obr2"] = ELEM_NORMA;
	else
		b124ee02["qf_obr2"] = ELEM_NOT;
	messages["124ee02@qf_obr2"] = b124ee02["qf_obr2"];

//QF АПП ОБР 2 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_obr2"])
	{
		elementsRgdv["124yy08_qf_obr_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_obr_2"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_obr2"])
	{
		elementsRgdv["124yy08_qf_obr_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_obr_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_obr_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_obr_2"] = "НЕ КОНТР";
	}

//QF КОНДИЦИОНЕР 2
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_cond2"])
	{
		b124ee02["qf_cond2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_cond2"])
		b124ee02["qf_cond2"] = ELEM_NORMA;
	else
		b124ee02["qf_cond2"] = ELEM_NOT;
	messages["124ee02@qf_cond2"] = b124ee02["qf_cond2"];

//QF КОНДИЦИОНЕР 2 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_cond2"])
	{
		elementsRgdv["124yy08_qf_cond_2"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_cond_2"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_cond2"])
	{
		elementsRgdv["124yy08_qf_cond_2"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_cond_2"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_cond_2"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_cond_2"] = "НЕ КОНТР";
	}

//QF 123ББ01-3
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_123bb01_3"])
	{
		b124ee02["qf_123bb01_3"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_123bb01_3"])
		b124ee02["qf_123bb01_3"] = ELEM_NORMA;
	else
		b124ee02["qf_123bb01_3"] = ELEM_NOT;
	messages["124ee02@qf_123bb01_3"] = b124ee02["qf_123bb01_3"];

//QF 123ББ01-3 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_123bb01_3"])
	{
		elementsRgdv["124yy08_qf_123bb01_3"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_123bb01_3"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_123bb01_3"])
	{
		elementsRgdv["124yy08_qf_123bb01_3"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_123bb01_3"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_123bb01_3"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_123bb01_3"] = "НЕ КОНТР";
	}

//QF 123ББ01-4
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_123bb01_4"])
	{
		b124ee02["qf_123bb01_4"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_123bb01_4"])
		b124ee02["qf_123bb01_4"] = ELEM_NORMA;
	else
		b124ee02["qf_123bb01_4"] = ELEM_NOT;
	messages["124ee02@qf_123bb01_4"] = b124ee02["qf_123bb01_4"];

//QF 123ББ01-4 (РГДВ)
	if(b124ee02["isAvtOk"] == ELEM_NORMA && sigmap["elk_qf_123bb01_4"])
	{
		elementsRgdv["124yy08_qf_123bb01_4"] = ELEM_AVAR;
		elementsRgdv["124yy08_qf_123bb01_4"] = "ОТКЛ";
	}
	else if(b124ee02["isAvtOk"] == ELEM_NORMA && !sigmap["elk_qf_123bb01_4"])
	{
		elementsRgdv["124yy08_qf_123bb01_4"] = ELEM_NORMA;
		elementsRgdv["124yy08_qf_123bb01_4"] = "ВКЛ";
	}
	else
	{
		elementsRgdv["124yy08_qf_123bb01_4"] = ELEM_DISABLE;
		elementsRgdv["124yy08_qf_123bb01_4"] = "НЕ КОНТР";
	}

//123ББ01-1
	if(b124ee02["isOk"] == ELEM_NORMA && b124ee02["qf_123bb01_1"] == ELEM_NORMA && sigmap["elk_avar_123bb01_1"])
	{
		b124ee02["123bb01_1"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && b124ee02["qf_123bb01_1"] == ELEM_NORMA && sigmap["elk_norma_123bb01_1"])
		b124ee02["123bb01_1"] = ELEM_NORMA;
	else
		b124ee02["123bb01_1"] = ELEM_NOT;
	messages["124ee02@123bb01_1"] = b124ee02["123bb01_1"];

//123ББ01-2
	if(b124ee02["isOk"] == ELEM_NORMA && b124ee02["qf_123bb01_2"] == ELEM_NORMA && sigmap["elk_avar_123bb01_2"])
	{
		b124ee02["123bb01_2"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && b124ee02["qf_123bb01_2"] == ELEM_NORMA && sigmap["elk_norma_123bb01_2"])
		b124ee02["123bb01_2"] = ELEM_NORMA;
	else
		b124ee02["123bb01_2"] = ELEM_NOT;
	messages["124ee02@123bb01_2"] = b124ee02["123bb01_2"];

//123ББ01-3
	if(b124ee02["isOk"] == ELEM_NORMA && b124ee02["qf_123bb01_3"] == ELEM_NORMA && sigmap["elk_avar_123bb01_3"])
	{
		b124ee02["123bb01_3"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && b124ee02["qf_123bb01_3"] == ELEM_NORMA && sigmap["elk_norma_123bb01_3"])
		b124ee02["123bb01_3"] = ELEM_NORMA;
	else
		b124ee02["123bb01_3"] = ELEM_NOT;
	messages["124ee02@123bb01_3"] = b124ee02["123bb01_3"];

//123ББ01-4
	if(b124ee02["isOk"] == ELEM_NORMA && b124ee02["qf_123bb01_4"] == ELEM_NORMA && sigmap["elk_avar_123bb01_4"])
	{
		b124ee02["123bb01_4"] = ELEM_AVAR;
		nError++;
	}
	else if(b124ee02["isOk"] == ELEM_NORMA && b124ee02["qf_123bb01_4"] == ELEM_NORMA && sigmap["elk_norma_123bb01_4"])
		b124ee02["123bb01_4"] = ELEM_NORMA;
	else
		b124ee02["123bb01_4"] = ELEM_NOT;
	messages["124ee02@123bb01_4"] = b124ee02["123bb01_4"];

//Общее состояние
	if(b124ee02["p27v_pit_avt"] == ELEM_AVAR)
		nAvar++;
	if(b124ee02["p27v_gsh"] == ELEM_AVAR)
		nAvar++;
	if(b124ee02["p27v_opu"] == ELEM_AVAR)
		nAvar++;
	if(b124ee02["p27v_zu1"] == ELEM_AVAR && b124ee02["p27v_zu2"] == ELEM_AVAR)
		nAvar++;
	if(b124ee02["p27v_ps1"] == ELEM_AVAR && b124ee02["p27v_ps2"] == ELEM_AVAR)
		nAvar++;
	if(b124ee02["p27v_123gv02_1"] == ELEM_AVAR && b124ee02["p27v_123gv02_2"] == ELEM_AVAR)
		nAvar++;
	if(b124ee02["p27v_azs1"] == ELEM_AVAR && b124ee02["p27v_azs2"] == ELEM_AVAR)
		nAvar++;
	if(b124ee02["123bb01_1"] == ELEM_AVAR && b124ee02["123bb01_2"] == ELEM_AVAR && b124ee02["123bb01_3"] == ELEM_AVAR && b124ee02["123bb01_4"] == ELEM_AVAR)
		nAvar++;
	if(b124ee02["qf_123bb01_1"] == ELEM_AVAR && b124ee02["qf_123bb01_2"] == ELEM_AVAR && b124ee02["qf_123bb01_3"] == ELEM_AVAR && b124ee02["qf_123bb01_4"] == ELEM_AVAR)
		nAvar++;
	if((b124ee02["qf_124yy03_1"] == ELEM_AVAR || b124ee02["p27v_124yy03_1"] == ELEM_AVAR) && (b124ee02["qf_124yy03_2"] == ELEM_AVAR || b124ee02["p27v_124yy03_2"] == ELEM_AVAR))
		nAvar++;
	if(b124ee02["qf_kmvrl1"] == ELEM_AVAR && b124ee02["qf_kmvrl2"] == ELEM_AVAR)
		nAvar++;
	if((b124ee02["qf_prm1"] == ELEM_AVAR || b124ee02["p27v_prm1"] == ELEM_AVAR) && (b124ee02["qf_prm2"] == ELEM_AVAR || b124ee02["p27v_prm2"] == ELEM_AVAR))
		nAvar++;
	if(b124ee02["qf_prd1"] == ELEM_AVAR && b124ee02["qf_prd2"] == ELEM_AVAR)
		nAvar++;
	if(b124ee02["qf_obr1"] == ELEM_AVAR && b124ee02["qf_obr2"] == ELEM_AVAR)
		nAvar++;

	if(b124ee02["isOk"] == ELEM_NORMA && (nAvar != 0))
		b124ee02["obSost"] = ELEM_AVAR;
	else if(b124ee02["isOk"] == ELEM_NORMA && (nError!=0))
		b124ee02["obSost"] = ELEM_ERROR;
	else if(b124ee02["isOk"] == ELEM_NORMA && b124ee02["aorls"] != ELEM_AVAR && b124ee02["otkl_cont_380v"] != ELEM_AVAR)
		b124ee02["obSost"] = ELEM_NORMA;
	else
		b124ee02["obSost"] = ELEM_NOT;

	elements["elk_panel@p27v_pit_signal"] = b124ee02["p27v_pit_signal"].toString();
	elements["elk_panel@p27v_124yy03_1"] = b124ee02["p27v_124yy03_1"].toString();
	elements["elk_panel@p27v_124yy03_2"] = b124ee02["p27v_124yy03_2"].toString();
	elements["elk_panel@p27v_123bb02"] = b124ee02["p27v_123bb02"].toString();
	elements["elk_panel@p27v_pit_avt"] = b124ee02["p27v_pit_avt"].toString();
	elements["elk_panel@p27v_howl1"] = b124ee02["p27v_howl1"].toString();
	elements["elk_panel@p27v_howl2"] = b124ee02["p27v_howl2"].toString();
	elements["elk_panel@p27v_prm1"] = b124ee02["p27v_prm1"].toString();
	elements["elk_panel@p27v_prm2"] = b124ee02["p27v_prm2"].toString();
	elements["elk_panel@p27v_mspd"] = b124ee02["p27v_mspd"].toString();
	elements["elk_panel@p27v_a15"] = b124ee02["p27v_a15"].toString();
	elements["elk_panel@p27v_a16"] = b124ee02["p27v_a16"].toString();
	elements["elk_panel@p27v_a17"] = b124ee02["p27v_a17"].toString();
	elements["elk_panel@p27v_a18"] = b124ee02["p27v_a18"].toString();
	elements["elk_panel@p27v_a19"] = b124ee02["p27v_a19"].toString();
	elements["elk_panel@p27v_a20"] = b124ee02["p27v_a20"].toString();
	elements["elk_panel@p27v_zu1"] = b124ee02["p27v_zu1"].toString();
	elements["elk_panel@p27v_zu2"] = b124ee02["p27v_zu2"].toString();
	elements["elk_panel@p27v_ps1"] = b124ee02["p27v_ps1"].toString();
	elements["elk_panel@p27v_ps2"] = b124ee02["p27v_ps2"].toString();
	elements["elk_panel@p27v_123gv02_1"] = b124ee02["p27v_123gv02_1"].toString();
	elements["elk_panel@p27v_123gv02_2"] = b124ee02["p27v_123gv02_2"].toString();
	elements["elk_panel@p27v_azs1"] = b124ee02["p27v_azs1"].toString();
	elements["elk_panel@p27v_azs2"] = b124ee02["p27v_azs2"].toString();
	elements["elk_panel@p27v_gsh"] = b124ee02["p27v_gsh"].toString();
	elements["elk_panel@p27v_opu"] = b124ee02["p27v_opu"].toString();
	elements["elk_panel@p27v_a31"] = b124ee02["p27v_a31"].toString();
	elements["elk_panel@p27v_a32"] = b124ee02["p27v_a32"].toString();

	elements["elk_panel@qf_accum"] = b124ee02["qf_accum"].toString();
	elements["elk_panel@qf_124yy08"] = b124ee02["qf_124yy08"].toString();
	elements["elk_panel@qf_124yg02"] = b124ee02["qf_124yg02"].toString();
	elements["elk_panel@qf_27v_buf"] = b124ee02["qf_27v_buf"].toString();
	elements["elk_panel@qf_pos"] = b124ee02["qf_pos"].toString();
	elements["elk_panel@qf_prm1"] = b124ee02["qf_prm1"].toString();
	elements["elk_panel@qf_prm2"] = b124ee02["qf_prm2"].toString();
	elements["elk_panel@qf_trm"] = b124ee02["qf_trm"].toString();
	elements["elk_panel@qf_27v_c"] = b124ee02["qf_27v_c"].toString();
	elements["elk_panel@qf_avar_osv"] = b124ee02["qf_avar_osv"].toString();
	elements["elk_panel@qf_380v_set"] = b124ee02["qf_380v_set"].toString();
	elements["elk_panel@qf_osv_apm"] = b124ee02["qf_osv_apm"].toString();
	elements["elk_panel@qf_osv_perim"] = b124ee02["qf_osv_perim"].toString();
	elements["elk_panel@qf_380v_rpu"] = b124ee02["qf_380v_rpu"].toString();
	elements["elk_panel@qf_teplovent"] = b124ee02["qf_teplovent"].toString();
	elements["elk_panel@qf_sotr"] = b124ee02["qf_sotr"].toString();
	elements["elk_panel@qf_rozet_220v"] = b124ee02["qf_rozet_220v"].toString();

	elements["elk_panel@qf_ups1"] = b124ee02["qf_ups1"].toString();
	elements["elk_panel@qf_prd1"] = b124ee02["qf_prd1"].toString();
	elements["elk_panel@qf_124yy03_1"] = b124ee02["qf_124yy03_1"].toString();
	elements["elk_panel@qf_kmvrl1"] = b124ee02["qf_kmvrl1"].toString();
	elements["elk_panel@qf_obr1"] = b124ee02["qf_obr1"].toString();
	elements["elk_panel@qf_cond1"] = b124ee02["qf_cond1"].toString();
	elements["elk_panel@qf_123bb01_1"] = b124ee02["qf_123bb01_1"].toString();
	elements["elk_panel@qf_123bb01_2"] = b124ee02["qf_123bb01_2"].toString();

	elements["elk_panel@qf_ups2"] = b124ee02["qf_ups2"].toString();
	elements["elk_panel@qf_prd2"] = b124ee02["qf_prd2"].toString();
	elements["elk_panel@qf_124yy03_2"] = b124ee02["qf_124yy03_2"].toString();
	elements["elk_panel@qf_kmvrl2"] = b124ee02["qf_kmvrl2"].toString();
	elements["elk_panel@qf_obr2"] = b124ee02["qf_obr2"].toString();
	elements["elk_panel@qf_cond2"] = b124ee02["qf_cond2"].toString();
	elements["elk_panel@qf_123bb01_3"] = b124ee02["qf_123bb01_3"].toString();
	elements["elk_panel@qf_123bb01_4"] = b124ee02["qf_123bb01_4"].toString();

	elements["elk_panel@123bb01_1"] = b124ee02["123bb01_1"].toString();
	elements["elk_panel@123bb01_2"] = b124ee02["123bb01_2"].toString();
	elements["elk_panel@123bb01_3"] = b124ee02["123bb01_3"].toString();
	elements["elk_panel@123bb01_4"] = b124ee02["123bb01_4"].toString();

	elements["elk@124ee02"] = b124ee02["obSost"].toString();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::fun125YY03_raf()
{
	int nAvar = 0, nError = 0;

//ОК
	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && b124yy08["d2vv056"] == ELEM_NORMA)
		b125yy03["isOk"] = ELEM_NORMA;
	else
		b125yy03["isOk"] = ELEM_NOT;

//АО РЛС
	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && sigmap["elk_aorls"])
		b125yy03["aorls"] = ELEM_AVAR;
	else
		b125yy03["aorls"] = ELEM_NOT;

//НАЖАТЬ СБРОС АВАРИИ
	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && sigmap["elk_put_reset_avar"])
	{
		nAvar++;
		b125yy03["put_reset_avar"] = ELEM_AVAR;
	}
	else
		b125yy03["put_reset_avar"] = ELEM_NOT;
	messages["125yy03@put_reset_avar"] = b125yy03["put_reset_avar"];

//ОТКЛ 380В КОНТ
	if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && sigmap["elk_otkl_cont_380v"])
		b125yy03["otkl_cont_380v"] = ELEM_AVAR;
	else if(canalAsku["OY1_OS_STATE"] == ELEM_NORMA && !sigmap["elk_otkl_cont_380v"])
		b125yy03["otkl_cont_380v"] = ELEM_NORMA;
	else
		b125yy03["otkl_cont_380v"] = ELEM_NOT;

//ОК_POWER
	if(b125yy03["isOk"] == ELEM_NORMA && b125yy03["otkl_cont_380v"] != ELEM_AVAR && b125yy03["aorls"] != ELEM_AVAR)
		b125yy03["isOkPwr"] = ELEM_NORMA;
	else
		b125yy03["isOkPwr"] = ELEM_NOT;

//ОСВЕЩ ПЕРИМ КОНТ ВКЛ
    if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_vkl_cont_osv_perim"]){
		b125yy03["vkl_cont_osv_perim"] = ELEM_NORMA;
        emit perim_light_on_off(true);
    }else{
		b125yy03["vkl_cont_osv_perim"] = ELEM_NOT;
        emit perim_light_on_off(false);
    }
    //если что-то не так, то удалить ниже сигнал perim_light_on_off
    if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_vkl_cont_osv_perim"]){
		b125yy03["vkl_cont_osv_perim_s"] = ELEM_NORMA;       
        emit perim_light_on_off(true);
    }
    else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_vkl_cont_osv_perim"]){
		b125yy03["vkl_cont_osv_perim_s"] = ELEM_AVAR;       
        emit perim_light_on_off(false);
    }
    else{
		b125yy03["vkl_cont_osv_perim_s"] = ELEM_NOT;
        emit perim_light_on_off(false);
    }
    messages["125yy03@vkl_cont_osv_perim"] = b125yy03["vkl_cont_osv_perim_s"];

//ОСВЕЩ РПУ КОНТ ВКЛ
/*	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_vkl_cont_osv_rpu"])
		b125yy03["vkl_cont_osv_rpu"] = ELEM_NORMA;
	else
		b125yy03["vkl_cont_osv_rpu"] = ELEM_NOT;
	messages["125yy03@vkl_cont_osv_rpu"] = b125yy03["vkl_cont_osv_rpu"];
*/
//ВЕНТИЛЯТОР 1
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_avar_vent_12"])
	{
		b125yy03["vent1"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_avar_vent_12"])
		b125yy03["vent1"] = ELEM_NORMA;
	else
		b125yy03["vent1"] = ELEM_NOT;
	messages["125yy03@vent1"] = b125yy03["vent1"];

//ВЕНТИЛЯТОР 2
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_avar_vent_12"])
	{
		b125yy03["vent2"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_avar_vent_12"])
		b125yy03["vent2"] = ELEM_NORMA;
	else
		b125yy03["vent2"] = ELEM_NOT;
	messages["125yy03@vent2"] = b125yy03["vent2"];

//123ББ02
	if(b125yy03["isOkPwr"] == ELEM_NORMA && b124ee02["p27v_123bb02"] == ELEM_NORMA && sigmap["elk_avar_d1"] && sigmap["elk_avar_d2"] && sigmap["elk_avar_d3"] && sigmap["elk_avar_d4"])
	{
		b125yy03["123bb02"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && b124ee02["p27v_123bb02"] == ELEM_NORMA && (!sigmap["elk_avar_d1"] || !sigmap["elk_avar_d2"] || !sigmap["elk_avar_d3"] || !sigmap["elk_avar_d4"]))
		b125yy03["123bb02"] = ELEM_NORMA;
	else
		b125yy03["123bb02"] = ELEM_NOT;
	messages["125yy03@123bb02"] = b125yy03["123bb02"];

//ДАТЧИК ДАВЛЕНИЯ
	if(b125yy03["isOkPwr"] == ELEM_NORMA && b125yy03["123bb02"] == ELEM_NORMA && sigmap["elk_avar_d1"])
	{
		b125yy03["sensor_p"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && b125yy03["123bb02"] == ELEM_NORMA && !sigmap["elk_avar_d1"])
		b125yy03["sensor_p"] = ELEM_NORMA;
	else
		b125yy03["sensor_p"] = ELEM_NOT;
	messages["125yy03@sensor_p"] = b125yy03["sensor_p"];

//ДАТЧИК ТЕМПЕРАТУРЫ 1 (НПН 1)
	if(b125yy03["isOkPwr"] == ELEM_NORMA && b125yy03["123bb02"] == ELEM_NORMA && sigmap["elk_avar_d2"])
	{
		b125yy03["sensor_t1"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && b125yy03["123bb02"] == ELEM_NORMA && !sigmap["elk_avar_d2"])
		b125yy03["sensor_t1"] = ELEM_NORMA;
	else
		b125yy03["sensor_t1"] = ELEM_NOT;
	messages["125yy03@sensor_t1"] = b125yy03["sensor_t1"];

//ДАТЧИК ТЕМПЕРАТУРЫ 2 (НПН 2)
	if(b125yy03["isOkPwr"] == ELEM_NORMA && b125yy03["123bb02"] == ELEM_NORMA && sigmap["elk_avar_d3"])
	{
		b125yy03["sensor_t2"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && b125yy03["123bb02"] == ELEM_NORMA && !sigmap["elk_avar_d3"])
		b125yy03["sensor_t2"] = ELEM_NORMA;
	else
		b125yy03["sensor_t2"] = ELEM_NOT;
	messages["125yy03@sensor_t2"] = b125yy03["sensor_t2"];

//ДАТЧИК ТЕМПЕРАТУРЫ 3 (НПН 3)
	if(b125yy03["isOkPwr"] == ELEM_NORMA && b125yy03["123bb02"] == ELEM_NORMA && sigmap["elk_avar_d4"])
	{
		b125yy03["sensor_t3"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && b125yy03["123bb02"] == ELEM_NORMA && !sigmap["elk_avar_d4"])
		b125yy03["sensor_t3"] = ELEM_NORMA;
	else
		b125yy03["sensor_t3"] = ELEM_NOT;
	messages["125yy03@sensor_t3"] = b125yy03["sensor_t3"];

//24V НАПР АККУМ
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_accum_24v"] && b124ee02["qf_accum"] == ELEM_NORMA)
		b125yy03["accum_24v"] = ELEM_AVAR;
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_accum_24v"] && b124ee02["qf_accum"] == ELEM_NORMA)
		b125yy03["accum_24v"] = ELEM_NORMA;
	else
		b125yy03["accum_24v"] = ELEM_NOT;
	messages["125yy03@accum_24v"] = b125yy03["accum_24v"];

//24V НАПР АККУМ (РГДВ)
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_accum_24v"])
	{
		elementsRgdv["124yy08_24v_accum"] = ELEM_AVAR;
		elementsRgdv["124yy08_24v_accum"] = "АВАРИЯ";
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_accum_24v"])
	{
		elementsRgdv["124yy08_24v_accum"] = ELEM_NORMA;
		elementsRgdv["124yy08_24v_accum"] = "НОРМА";
	}
	else
	{
		elementsRgdv["124yy08_24v_accum"] = ELEM_DISABLE;
		elementsRgdv["124yy08_24v_accum"] = "НЕ КОНТР";
	}

//НЕИСПР ИБП 1
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_ups1_error"])
	{
		b125yy03["ups1_error"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_ups1_error"])
		b125yy03["ups1_error"] = ELEM_NORMA;
	else
		b125yy03["ups1_error"] = ELEM_NOT;
	messages["125yy03@ups1_error"] = b125yy03["ups1_error"];

//НЕИСПР ИБП 2
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_ups2_error"])
	{
		b125yy03["ups2_error"] = ELEM_AVAR;
		nError++;
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_ups2_error"])
		b125yy03["ups2_error"] = ELEM_NORMA;
	else
		b125yy03["ups2_error"] = ELEM_NOT;
	messages["125yy03@ups2_error"] = b125yy03["ups2_error"];

// --- ПЕРЕНЕСТИ!

//БЛОКИР ОПУ НАРУШ
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_block_opu"])
		b125yy03["block_opu"] = ELEM_AVAR;
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_block_opu"])
		b125yy03["block_opu"] = ELEM_NORMA;
	else
		b125yy03["block_opu"] = ELEM_NOT;
	messages["125yy03@block_opu"] = b125yy03["block_opu"];

//БЛОКИР ОПУ НАРУШ (РГДВ)
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_block_opu"])
	{
		elementsRgdv["124yy08_block_opu"] = ELEM_AVAR;
		elementsRgdv["124yy08_block_opu"] = "НАРУШЕНА";
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_block_opu"])
	{
		elementsRgdv["124yy08_block_opu"] = ELEM_NORMA;
		elementsRgdv["124yy08_block_opu"] = "НЕ НАРУШЕНА";
	}
	else
	{
		elementsRgdv["124yy08_block_opu"] = ELEM_DISABLE;
		elementsRgdv["124yy08_block_opu"] = "НЕ КОНТР";
	}

//ЛЮК ОПУ ОТКР
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_opu_open"])
		b125yy03["opu_open"] = ELEM_AVAR;
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_opu_open"])
		b125yy03["opu_open"] = ELEM_NORMA;
	else
		b125yy03["opu_open"] = ELEM_NOT;
	messages["125yy03@opu_open"] = b125yy03["opu_open"];

//ЛЮК ОПУ ОТКР (РГДВ)
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_opu_open"])
	{
		elementsRgdv["124yy08_opu_open"] = ELEM_AVAR;
		elementsRgdv["124yy08_opu_open"] = "ОТКРЫТ";
	}
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_opu_open"])
	{
		elementsRgdv["124yy08_opu_open"] = ELEM_NORMA;
		elementsRgdv["124yy08_opu_open"] = "ЗАКРЫТ";
	}
	else
	{
		elementsRgdv["124yy08_opu_open"] = ELEM_DISABLE;
		elementsRgdv["124yy08_opu_open"] = "НЕ КОНТР";
	}

//РАБОТА КОНД 1
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_work_cond_1"])
		b125yy03["work_cond_1"] = ELEM_NORMA;
	else
		b125yy03["work_cond_1"] = ELEM_NOT;

	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_work_cond_1"])
		b125yy03["work_cond_1_s"] = ELEM_NORMA;
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_work_cond_1"])
		b125yy03["work_cond_1_s"] = ELEM_AVAR;
	else
		b125yy03["work_cond_1_s"] = ELEM_NOT;
	messages["125yy03@work_cond_1"] = b125yy03["work_cond_1_s"];

//РАБОТА КОНД 2
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_work_cond_2"])
		b125yy03["work_cond_2"] = ELEM_NORMA;
	else
		b125yy03["work_cond_2"] = ELEM_NOT;

	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_work_cond_2"])
		b125yy03["work_cond_2_s"] = ELEM_NORMA;
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_work_cond_2"])
		b125yy03["work_cond_2_s"] = ELEM_AVAR;
	else
		b125yy03["work_cond_2_s"] = ELEM_NOT;
	messages["125yy03@work_cond_2"] = b125yy03["work_cond_2_s"];

//АВАР 124УГ02
	if(b125yy03["isOkPwr"] == ELEM_NORMA && sigmap["elk_avar124yg02"])
		b125yy03["avar124yg02"] = ELEM_AVAR;
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && !sigmap["elk_avar124yg02"])
		b125yy03["avar124yg02"] = ELEM_NORMA;
	else
		b125yy03["avar124yg02"] = ELEM_NOT;
	messages["125yy03@avar124yg02"] = b125yy03["avar124yg02"];

// ПЕРЕНЕСТИ! ---

//АВАРИИ
	if(b125yy03["124yy03_1"] == ELEM_AVAR && b125yy03["124yy03_2"] == ELEM_AVAR)
		nAvar++;
	if(b125yy03["ups1_error"] == ELEM_AVAR && b125yy03["ups2_error"] == ELEM_AVAR)
		nAvar++;

//МЕСТ
	if(b124yy08["mest"] == ELEM_MEST || b124yy03["mest"] == ELEM_MEST)
		b125yy03["mest"] = ELEM_MEST;
	else
		b125yy03["mest"] = ELEM_NOT;

//ОБЩЕЕ СОСТОЯНИЕ
	if(b124yy08["obSost"] == ELEM_AVAR || b124ee02["obSost"] == ELEM_AVAR || b124yy03["ObSost"] == ELEM_AVAR || (nAvar != 0))
		b125yy03["obSost"] = ELEM_AVAR;
	else if(b124yy08["obSost"] == ELEM_ERROR || b124ee02["obSost"] == ELEM_ERROR || b124yy03["ObSost"] == ELEM_AVAR || (nError != 0))
		b125yy03["obSost"] = ELEM_ERROR;
	else if(b125yy03["isOk"] == ELEM_NORMA && b125yy03["aorls"] != ELEM_AVAR && b125yy03["otkl_cont_380v"] != ELEM_AVAR)
		b125yy03["obSost"] = ELEM_NORMA;
	else
		b125yy03["obSost"] = ELEM_NOT;

	elements["elk@vent1"] = b125yy03["vent1"].toString();
	elements["elk@vent2"] = b125yy03["vent2"].toString();
	elements["elk@123bb02"] = b125yy03["123bb02"].toString();
	elements["elk@sensor_p"] = b125yy03["sensor_p"].toString();
	elements["elk@sensor_t1"] = b125yy03["sensor_t1"].toString();
	elements["elk@sensor_t2"] = b125yy03["sensor_t2"].toString();
	elements["elk@sensor_t3"] = b125yy03["sensor_t3"].toString();

	elements["elk@cont_380v"] = b125yy03["otkl_cont_380v"].toString();
	elements["elk@cont_osv_perim"] = b125yy03["vkl_cont_osv_perim"].toString() + b124yy08["mest"].toStringMest();
//	elements["elk@cont_osv_rpu"] = b125yy03["vkl_cont_osv_rpu"].toString() + b124yy08["mest"].toStringMest();
	elements["elk@accum_24v"] = b125yy03["accum_24v"].toString();
	elements["elk@ups1_error"] = b125yy03["ups1_error"].toString();
	elements["elk@ups2_error"] = b125yy03["ups2_error"].toString();
	elements["elk@aorls"] = b125yy03["aorls"].toString();
	elements["base@aorls"] = b125yy03["aorls"].toString();
	elements["base@put_reset_avar"] = b125yy03["put_reset_avar"].toString();
	elements["elk@put_reset_avar"] = b125yy03["put_reset_avar"].toString();

//ПЕРЕНЕСТИ
	elements["elk@block_opu"] = b125yy03["block_opu"].toString();
	elements["base@block_opu"] = b125yy03["block_opu"].toString();
	elements["elk@opu_open"] = b125yy03["opu_open"].toString();
	elements["ant@opu_open"] = b125yy03["opu_open"].toString();
	elements["elk@work_cond_1"] = b125yy03["work_cond_1"].toString();
	elements["elk@work_cond_2"] = b125yy03["work_cond_2"].toString();
	elements["elk@avar124yg02"] = b125yy03["avar124yg02"].toString();
//ПЕРЕНЕСТИ

	elements["base@elk"] = b125yy03["obSost"].toString() + b125yy03["mest"].toStringMest();
	elements["zal@125yy03"] = b125yy03["obSost"].toString() + b125yy03["mest"].toStringMest();
}

// ----------------------------------------------------------------------------
