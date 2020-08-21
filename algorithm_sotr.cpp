#include "../common/logger.h"
#include "../common/module.h"
#include "globalvar.h"
#include "algorithm.h"
#include "canalasku_data.h"

// ----------------------------------------------------------------------------
void AskuAlgorithm::funCondition()
{
//КОНД 1 ОК
	if(b125yy03["isOkPwr"] == ELEM_NORMA && b124ee02["qf_cond1"] == ELEM_NORMA)
		bCOND["isCond1Ok"] = ELEM_NORMA;
	else
		bCOND["isCond1Ok"] = ELEM_NOT;

//КОНД 2 ОК
	if(b125yy03["isOkPwr"] == ELEM_NORMA && b124ee02["qf_cond2"] == ELEM_NORMA)
		bCOND["isCond2Ok"] = ELEM_NORMA;
	else
		bCOND["isCond2Ok"] = ELEM_NOT;

//КОНТР КОНД 1
	if(bCOND["isCond1Ok"] == ELEM_NORMA && sigmap["elk_cond1_link"])
		bCOND["cond1_controller"] = ELEM_AVAR;
	else if(bCOND["isCond1Ok"] == ELEM_NORMA && !sigmap["elk_cond1_link"])
		bCOND["cond1_controller"] = ELEM_NORMA;
	else
		bCOND["cond1_controller"] = ELEM_NOT;
	messages["sotr@cond1_controller"] = bCOND["cond1_controller"];

//КОНДИЦИОНЕР 1
	if(bCOND["isCond1Ok"] == ELEM_NORMA && bCOND["cond1_controller"] == ELEM_NORMA && (sigmap["elk_cond1_avar"] || sigmap["elk_avar_cond_1"]))
		bCOND["cond1_obSost"] = ELEM_AVAR;
	else if(bCOND["isCond1Ok"] == ELEM_NORMA && bCOND["cond1_controller"] == ELEM_NORMA && !sigmap["elk_cond1_avar"] && !sigmap["elk_avar_cond_1"] && sigmap["elk_cond1_ventile"])
		bCOND["cond1_obSost"] = ELEM_NORMA;
	else
		bCOND["cond1_obSost"] = ELEM_NOT;

//КОНДИЦИОНЕР 1 ДАТЧИК 1
	if(bCOND["isCond1Ok"] == ELEM_NORMA && (sigmap["elk_cond1_kz_dt_vh_1"] || sigmap["elk_cond1_hh_dt_vh_1"]))
		bCOND["cond1_sensor1"] = ELEM_AVAR;
	else if(bCOND["isCond1Ok"] == ELEM_NORMA && !sigmap["elk_cond1_kz_dt_vh_1"] && !sigmap["elk_cond1_hh_dt_vh_1"])
		bCOND["cond1_sensor1"] = ELEM_NORMA;
	else
		bCOND["cond1_sensor1"] = ELEM_NOT;
	messages["sotr@cond1_sensor1"] = bCOND["cond1_sensor1"];

//КОНДИЦИОНЕР 1 ДАТЧИК 2
	if(bCOND["isCond1Ok"] == ELEM_NORMA && (sigmap["elk_cond1_kz_dt_vh_2"] || sigmap["elk_cond1_hh_dt_vh_2"]))
		bCOND["cond1_sensor2"] = ELEM_AVAR;
	else if(bCOND["isCond1Ok"] == ELEM_NORMA && !sigmap["elk_cond1_kz_dt_vh_2"] && !sigmap["elk_cond1_hh_dt_vh_2"])
		bCOND["cond1_sensor2"] = ELEM_NORMA;
	else
		bCOND["cond1_sensor2"] = ELEM_NOT;
	messages["sotr@cond1_sensor2"] = bCOND["cond1_sensor2"];

//КОНДИЦИОНЕР 1 ВЕНТИЛЬ СВМ
	if(bCOND["isCond1Ok"] == ELEM_NORMA && sigmap["elk_cond1_ventile"])
		bCOND["cond1_ventile"] = ELEM_NORMA;
	else
		bCOND["cond1_ventile"] = ELEM_NOT;

//КОНДИЦИОНЕР 1 КОМПРЕССОР
	if(bCOND["isCond1Ok"] == ELEM_NORMA && sigmap["elk_cond1_avar_dvig_compr"])
		bCOND["cond1_compressor"] = ELEM_AVAR;
	else if(bCOND["isCond1Ok"] == ELEM_NORMA && !sigmap["elk_cond1_avar_dvig_compr"] && sigmap["elk_cond1_ventile"])
		bCOND["cond1_compressor"] = ELEM_NORMA;
	else
		bCOND["cond1_compressor"] = ELEM_NOT;
	messages["sotr@cond1_compressor"] = bCOND["cond1_compressor"];

//КОНДИЦИОНЕР 1 ВЕНТИЛЯТОР РЕЦИРКУЛЯЦИИ
	if(bCOND["isCond1Ok"] == ELEM_NORMA && sigmap["elk_cond1_avar_vent_recirc"])
		bCOND["cond1_vent_recycle"] = ELEM_AVAR;
	else if(bCOND["isCond1Ok"] == ELEM_NORMA && !sigmap["elk_cond1_avar_vent_recirc"] && sigmap["elk_cond1_vent_recirc"])
		bCOND["cond1_vent_recycle"] = ELEM_NORMA;
	else
		bCOND["cond1_vent_recycle"] = ELEM_NOT;
	messages["sotr@cond1_vent_recycle"] = bCOND["cond1_vent_recycle"];

//КОНДИЦИОНЕР 1 ВЕНТИЛЯТОР КОНДЕНСОРА
	if(bCOND["isCond1Ok"] == ELEM_NORMA && sigmap["elk_cond1_avar_vent_kondens"])
		bCOND["cond1_vent_condensor"] = ELEM_AVAR;
	else if(bCOND["isCond1Ok"] == ELEM_NORMA && !sigmap["elk_cond1_avar_vent_kondens"] && sigmap["elk_cond1_vent_kondens"])
		bCOND["cond1_vent_condensor"] = ELEM_NORMA;
	else
		bCOND["cond1_vent_condensor"] = ELEM_NOT;
	messages["sotr@cond1_vent_condensor"] = bCOND["cond1_vent_condensor"];

//КОНДИЦИОНЕР 1 ВЫСОКОЕ ДАВЛЕНИЕ
	if(bCOND["isCond1Ok"] == ELEM_NORMA && sigmap["elk_cond1_avar_max_davl_nagn"])
		bCOND["cond1_pressure_high"] = ELEM_AVAR;
	else if(bCOND["isCond1Ok"] == ELEM_NORMA && !sigmap["elk_cond1_avar_max_davl_nagn"])
		bCOND["cond1_pressure_high"] = ELEM_NORMA;
	else
		bCOND["cond1_pressure_high"] = ELEM_NOT;
	messages["sotr@cond1_pressure_high"] = bCOND["cond1_pressure_high"];

//КОНДИЦИОНЕР 1 НИЗКОЕ ДАВЛЕНИЕ
	if(bCOND["isCond1Ok"] == ELEM_NORMA && sigmap["cond1_avar_min_davl_vsas"])
		bCOND["cond1_pressure_low"] = ELEM_AVAR;
	else if(bCOND["isCond1Ok"] == ELEM_NORMA && !sigmap["cond1_avar_min_davl_vsas"])
		bCOND["cond1_pressure_low"] = ELEM_NORMA;
	else
		bCOND["cond1_pressure_low"] = ELEM_NOT;
	messages["sotr@cond1_pressure_low"] = bCOND["cond1_pressure_low"];

//КОНТР КОНД 2
	if(bCOND["isCond2Ok"] == ELEM_NORMA && sigmap["elk_cond2_link"])
		bCOND["cond2_controller"] = ELEM_AVAR;
	else if(bCOND["isCond2Ok"] == ELEM_NORMA && !sigmap["elk_cond2_link"])
		bCOND["cond2_controller"] = ELEM_NORMA;
	else
		bCOND["cond2_controller"] = ELEM_NOT;
	messages["sotr@cond2_controller"] = bCOND["cond2_controller"];

//КОНДИЦИОНЕР 2
	if(bCOND["isCond2Ok"] == ELEM_NORMA && bCOND["cond2_controller"] == ELEM_NORMA && (sigmap["elk_cond2_avar"] || sigmap["elk_avar_cond_2"]))
		bCOND["cond2_obSost"] = ELEM_AVAR;
	else if(bCOND["isCond2Ok"] == ELEM_NORMA && bCOND["cond2_controller"] == ELEM_NORMA && !sigmap["elk_cond2_avar"] && !sigmap["elk_avar_cond_2"] && sigmap["elk_cond2_ventile"])
		bCOND["cond2_obSost"] = ELEM_NORMA;
	else
		bCOND["cond2_obSost"] = ELEM_NOT;

//КОНДИЦИОНЕР 2 ДАТЧИК 1
	if(bCOND["isCond2Ok"] == ELEM_NORMA && (sigmap["elk_cond2_kz_dt_vh_1"] || sigmap["elk_cond2_hh_dt_vh_1"]))
		bCOND["cond2_sensor1"] = ELEM_AVAR;
	else if(bCOND["isCond2Ok"] == ELEM_NORMA && !sigmap["elk_cond2_kz_dt_vh_1"] && !sigmap["elk_cond2_hh_dt_vh_1"])
		bCOND["cond2_sensor1"] = ELEM_NORMA;
	else
		bCOND["cond2_sensor1"] = ELEM_NOT;
	messages["sotr@cond2_sensor1"] = bCOND["cond2_sensor1"];

//КОНДИЦИОНЕР 2 ДАТЧИК 2
	if(bCOND["isCond2Ok"] == ELEM_NORMA && (sigmap["elk_cond2_kz_dt_vh_2"] || sigmap["elk_cond2_hh_dt_vh_2"]))
		bCOND["cond2_sensor2"] = ELEM_AVAR;
	else if(bCOND["isCond2Ok"] == ELEM_NORMA && !sigmap["elk_cond2_kz_dt_vh_2"] && !sigmap["elk_cond2_hh_dt_vh_2"])
		bCOND["cond2_sensor2"] = ELEM_NORMA;
	else
		bCOND["cond2_sensor2"] = ELEM_NOT;
	messages["sotr@cond2_sensor2"] = bCOND["cond2_sensor2"];

//КОНДИЦИОНЕР 2 ВЕНТИЛЬ СВМ
	if(bCOND["isCond2Ok"] == ELEM_NORMA && sigmap["elk_cond2_ventile"])
		bCOND["cond2_ventile"] = ELEM_NORMA;
	else
		bCOND["cond2_ventile"] = ELEM_NOT;

//КОНДИЦИОНЕР 2 КОМПРЕССОР
	if(bCOND["isCond2Ok"] == ELEM_NORMA && sigmap["elk_cond2_avar_dvig_compr"])
		bCOND["cond2_compressor"] = ELEM_AVAR;
	else if(bCOND["isCond2Ok"] == ELEM_NORMA && !sigmap["elk_cond2_avar_dvig_compr"] && sigmap["elk_cond2_ventile"])
		bCOND["cond2_compressor"] = ELEM_NORMA;
	else
		bCOND["cond2_compressor"] = ELEM_NOT;
	messages["sotr@cond2_compressor"] = bCOND["cond2_compressor"];

//КОНДИЦИОНЕР 2 ВЕНТИЛЯТОР РЕЦИРКУЛЯЦИИ
	if(bCOND["isCond2Ok"] == ELEM_NORMA && sigmap["elk_cond2_avar_vent_recirc"])
		bCOND["cond2_vent_recycle"] = ELEM_AVAR;
	else if(bCOND["isCond2Ok"] == ELEM_NORMA && !sigmap["elk_cond2_avar_vent_recirc"] && sigmap["elk_cond2_vent_recirc"])
		bCOND["cond2_vent_recycle"] = ELEM_NORMA;
	else
		bCOND["cond2_vent_recycle"] = ELEM_NOT;
	messages["sotr@cond2_vent_recycle"] = bCOND["cond2_vent_recycle"];

//КОНДИЦИОНЕР 2 ВЕНТИЛЯТОР КОНДЕНСОРА
	if(bCOND["isCond2Ok"] == ELEM_NORMA && sigmap["elk_cond2_avar_vent_kondens"])
		bCOND["cond2_vent_condensor"] = ELEM_AVAR;
	else if(bCOND["isCond2Ok"] == ELEM_NORMA && !sigmap["elk_cond2_avar_vent_kondens"] && sigmap["elk_cond2_vent_kondens"])
		bCOND["cond2_vent_condensor"] = ELEM_NORMA;
	else
		bCOND["cond2_vent_condensor"] = ELEM_NOT;
	messages["sotr@cond2_vent_condensor"] = bCOND["cond2_vent_condensor"];

//КОНДИЦИОНЕР 2 ВЫСОКОЕ ДАВЛЕНИЕ
	if(bCOND["isCond2Ok"] == ELEM_NORMA && sigmap["elk_cond2_avar_max_davl_nagn"])
		bCOND["cond2_pressure_high"] = ELEM_AVAR;
	else if(bCOND["isCond2Ok"] == ELEM_NORMA && !sigmap["elk_cond2_avar_max_davl_nagn"])
		bCOND["cond2_pressure_high"] = ELEM_NORMA;
	else
		bCOND["cond2_pressure_high"] = ELEM_NOT;
	messages["sotr@cond2_pressure_high"] = bCOND["cond2_pressure_high"];

//КОНДИЦИОНЕР 2 НИЗКОЕ ДАВЛЕНИЕ
	if(bCOND["isCond2Ok"] == ELEM_NORMA && sigmap["cond2_avar_min_davl_vsas"])
		bCOND["cond2_pressure_low"] = ELEM_AVAR;
	else if(bCOND["isCond2Ok"] == ELEM_NORMA && !sigmap["cond2_avar_min_davl_vsas"])
		bCOND["cond2_pressure_low"] = ELEM_NORMA;
	else
		bCOND["cond2_pressure_low"] = ELEM_NOT;
	messages["sotr@cond2_pressure_low"] = bCOND["cond2_pressure_low"];

//КОНДИЦИОНЕР (ОБЩЕЕ СОСТОЯНИЕ)
	if(bCOND["cond1_obSost"] == ELEM_AVAR && bCOND["cond2_obSost"] == ELEM_AVAR)
		bCOND["obSost"] = ELEM_AVAR;
	else if(bCOND["cond1_obSost"] == ELEM_AVAR || bCOND["cond2_obSost"] == ELEM_AVAR)
		bCOND["obSost"] = ELEM_ERROR;
	else if(bCOND["cond1_obSost"] == ELEM_NORMA || bCOND["cond2_obSost"] == ELEM_NORMA)
		bCOND["obSost"] = ELEM_NORMA;
	else
		bCOND["obSost"] = ELEM_NOT;

	elements["sotr_cond1@sensor1"] = bCOND["cond1_sensor1"].toString();
	elements["sotr_cond1@sensor2"] = bCOND["cond1_sensor2"].toString();
	elements["sotr_cond1@ventile"] = bCOND["cond1_ventile"].toString();
	elements["sotr_cond1@compressor"] = bCOND["cond1_compressor"].toString();
	elements["sotr_cond1@vent_recycle"] = bCOND["cond1_vent_recycle"].toString();
	elements["sotr_cond1@vent_condensor"] = bCOND["cond1_vent_condensor"].toString();
	elements["sotr_cond1@pressure_high"] = bCOND["cond1_pressure_high"].toString();
	elements["sotr_cond1@pressure_low"] = bCOND["cond1_pressure_low"].toString();

	elements["sotr_cond2@sensor1"] = bCOND["cond2_sensor1"].toString();
	elements["sotr_cond2@sensor2"] = bCOND["cond2_sensor2"].toString();
	elements["sotr_cond2@ventile"] = bCOND["cond2_ventile"].toString();
	elements["sotr_cond2@compressor"] = bCOND["cond2_compressor"].toString();
	elements["sotr_cond2@vent_recycle"] = bCOND["cond2_vent_recycle"].toString();
	elements["sotr_cond2@vent_condensor"] = bCOND["cond2_vent_condensor"].toString();
	elements["sotr_cond2@pressure_high"] = bCOND["cond2_pressure_high"].toString();
	elements["sotr_cond2@pressure_low"] = bCOND["cond2_pressure_low"].toString();

	elements["zal@cond"] = bCOND["obSost"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@cond1"] = bCOND["cond1_obSost"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@cond2"] = bCOND["cond2_obSost"].toString() + b124yy08["mest"].toStringMest();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funCanalSOTR()
{
//EL5
	if(b124yy08["d2vv056"] == ELEM_NORMA && (bCOND["cond1_controller"] == ELEM_NORMA || bCOND["cond2_controller"] == ELEM_NORMA))
		canalSOTR["EL5"] = ELEM_NORMA;
	else if(b124yy08["d2vv056"] == ELEM_NORMA && (bCOND["cond1_controller"] == ELEM_AVAR || bCOND["cond2_controller"] == ELEM_AVAR))
		canalSOTR["EL5"] = ELEM_AVAR;
	else
		canalSOTR["EL5"] = ELEM_NOT;

//EL4
	if(b124yy08["d2vv056"] == ELEM_NORMA && (canalSOTR["EL5"] == ELEM_NORMA || bSOTR["123ya03_4_obmen"] == ELEM_NORMA))
		canalSOTR["EL4"] = ELEM_NORMA;
	else if(b124yy08["d2vv056"] == ELEM_NORMA && bSOTR["123ya03_4_obmen"] == ELEM_AVAR)
		canalSOTR["EL4"] = ELEM_AVAR;
	else
		canalSOTR["EL4"] = ELEM_NOT;

//EL3
	if(b124yy08["d2vv056"] == ELEM_NORMA && (canalSOTR["EL4"] == ELEM_NORMA || bSOTR["123ya03_3_obmen"] == ELEM_NORMA))
		canalSOTR["EL3"] = ELEM_NORMA;
	else if(b124yy08["d2vv056"] == ELEM_NORMA && bSOTR["123ya03_3_obmen"] == ELEM_AVAR)
		canalSOTR["EL3"] = ELEM_AVAR;
	else
		canalSOTR["EL3"] = ELEM_NOT;

//EL2
	if(b124yy08["d2vv056"] == ELEM_NORMA && (canalSOTR["EL3"] == ELEM_NORMA || bSOTR["123ya03_2_obmen"] == ELEM_NORMA))
		canalSOTR["EL2"] = ELEM_NORMA;
	else if(b124yy08["d2vv056"] == ELEM_NORMA && bSOTR["123ya03_2_obmen"] == ELEM_AVAR)
		canalSOTR["EL2"] = ELEM_AVAR;
	else
		canalSOTR["EL2"] = ELEM_NOT;

//EL1
	if(b124yy08["d2vv056"] == ELEM_NORMA && (canalSOTR["EL3"] == ELEM_NORMA || bSOTR["123ya03_1_obmen"] == ELEM_NORMA))
		canalSOTR["EL1"] = ELEM_NORMA;
	else if(b124yy08["d2vv056"] == ELEM_NORMA && bSOTR["123ya03_1_obmen"] == ELEM_AVAR)
		canalSOTR["EL1"] = ELEM_AVAR;
	else
		canalSOTR["EL1"] = ELEM_NOT;

//Общее Состояние
	if(b124yy08["d2vv056"] == ELEM_AVAR || 
		canalSOTR["EL1"] == ELEM_AVAR || canalSOTR["EL2"] == ELEM_AVAR || canalSOTR["EL3"] == ELEM_AVAR || canalSOTR["EL4"] == ELEM_AVAR || canalSOTR["EL5"] == ELEM_AVAR ||
		(bSOTR["123ya03_1_obmen"] == ELEM_AVAR && bSOTR["123ya03_2_obmen"] == ELEM_AVAR) || (bSOTR["123ya03_3_obmen"] == ELEM_AVAR && bSOTR["123ya03_4_obmen"] == ELEM_AVAR) ||
		(bCOND["cond1_controller"] == ELEM_AVAR && bCOND["cond2_controller"] == ELEM_AVAR))
		canalSOTR["obSost"] = ELEM_AVAR;
	else if(b124yy08["d2vv056"] == ELEM_AVAR || 
		canalSOTR["EL1"] == ELEM_AVAR || canalSOTR["EL2"] == ELEM_AVAR || canalSOTR["EL3"] == ELEM_AVAR || canalSOTR["EL4"] == ELEM_AVAR || canalSOTR["EL5"] == ELEM_AVAR ||
		bSOTR["123ya03_1_obmen"] == ELEM_AVAR || bSOTR["123ya03_2_obmen"] == ELEM_AVAR || bSOTR["123ya03_3_obmen"] == ELEM_AVAR || bSOTR["123ya03_4_obmen"] == ELEM_AVAR ||
		bCOND["cond1_controller"] == ELEM_AVAR || bCOND["cond2_controller"] == ELEM_AVAR)
		canalSOTR["obSost"] = ELEM_ERROR;
	else if(b124yy08["d2vv056"] == ELEM_NORMA &&
			(bSOTR["123ya03_1_obmen"] == ELEM_NORMA || bSOTR["123ya03_2_obmen"] == ELEM_NORMA || bSOTR["123ya03_3_obmen"] == ELEM_NORMA || bSOTR["123ya03_4_obmen"] == ELEM_NORMA ||
			bCOND["cond1_controller"] == ELEM_NORMA || bCOND["cond2_controller"] == ELEM_NORMA))
		canalSOTR["obSost"] = ELEM_NORMA;
	else
		canalSOTR["obSost"] = ELEM_NOT;

	elements["rs485_sotr@d2vv056"] = b124yy08["d2vv056"].toString();
	elements["rs485_sotr@line1"] = canalSOTR["EL1"].toString();
	elements["rs485_sotr@line2"] = canalSOTR["EL2"].toString();
	elements["rs485_sotr@line3"] = canalSOTR["EL3"].toString();
	elements["rs485_sotr@line4"] = canalSOTR["EL4"].toString();
	elements["rs485_sotr@line5"] = canalSOTR["EL5"].toString();
	elements["rs485_sotr@oy1"] = bSOTR["123ya03_1_obmen"].toString();
	elements["rs485_sotr@oy2"] = bSOTR["123ya03_2_obmen"].toString();
	elements["rs485_sotr@oy3"] = bSOTR["123ya03_3_obmen"].toString();
	elements["rs485_sotr@oy4"] = bSOTR["123ya03_4_obmen"].toString();
	elements["rs485_sotr@oy5"] = bCOND["cond1_controller"].toString();
	elements["rs485_sotr@oy6"] = bCOND["cond2_controller"].toString();
	elements["base@rs485_sotr"] = canalSOTR["obSost"].toString();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funSOTR_raf()
{
	int nAvar = 0, nError = 0;

//СОТР ОК
	if(b125yy03["isOkPwr"] == ELEM_NORMA && b124ee02["qf_sotr"] == ELEM_NORMA)
		bSOTR["isSotrOk"] = ELEM_NORMA;
	else
		bSOTR["isSotrOk"] = ELEM_NOT;

//124УА03 1 ОБМЕН
	if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_obmen_sotr_1"])
		bSOTR["123ya03_1_obmen"] = ELEM_AVAR;
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_1"])
		bSOTR["123ya03_1_obmen"] = ELEM_NORMA;
	else
		bSOTR["123ya03_1_obmen"] = ELEM_NOT;

//124УА03 1
	if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_obmen_sotr_1"])
	{
		bSOTR["123ya03_1"] = ELEM_AVAR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_error_sotr_1"])
	{
		bSOTR["123ya03_1"] = ELEM_ERROR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_1"] && !sigmap["elk_error_sotr_1"])
		bSOTR["123ya03_1"] = ELEM_NORMA;
	else
		bSOTR["123ya03_1"] = ELEM_NOT;
	messages["sotr@123ya03_1"] = bSOTR["123ya03_1"];

//124УА03 2 ОБМЕН
	if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_obmen_sotr_2"])
		bSOTR["123ya03_2_obmen"] = ELEM_AVAR;
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_2"])
		bSOTR["123ya03_2_obmen"] = ELEM_NORMA;
	else
		bSOTR["123ya03_2_obmen"] = ELEM_NOT;

//124УА03 2
	if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_obmen_sotr_2"])
	{
		bSOTR["123ya03_2"] = ELEM_AVAR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_error_sotr_2"])
	{
		bSOTR["123ya03_2"] = ELEM_ERROR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_2"] && !sigmap["elk_error_sotr_2"])
		bSOTR["123ya03_2"] = ELEM_NORMA;
	else
		bSOTR["123ya03_2"] = ELEM_NOT;
	messages["sotr@123ya03_2"] = bSOTR["123ya03_2"];

//124УА03 3 ОБМЕН
	if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_obmen_sotr_3"])
		bSOTR["123ya03_3_obmen"] = ELEM_AVAR;
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_3"])
		bSOTR["123ya03_3_obmen"] = ELEM_NORMA;
	else
		bSOTR["123ya03_3_obmen"] = ELEM_NOT;

//124УА03 3
	if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_obmen_sotr_3"])
	{
		bSOTR["123ya03_3"] = ELEM_AVAR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_error_sotr_3"])
	{
		bSOTR["123ya03_3"] = ELEM_ERROR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_3"] && !sigmap["elk_error_sotr_3"])
		bSOTR["123ya03_3"] = ELEM_NORMA;
	else
		bSOTR["123ya03_3"] = ELEM_NOT;
	messages["sotr@123ya03_3"] = bSOTR["123ya03_3"];

//124УА03 4 ОБМЕН
	if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_obmen_sotr_4"])
		bSOTR["123ya03_4_obmen"] = ELEM_AVAR;
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_4"])
		bSOTR["123ya03_4_obmen"] = ELEM_NORMA;
	else
		bSOTR["123ya03_4_obmen"] = ELEM_NOT;

//124УА03 4
	if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_obmen_sotr_4"])
	{
		bSOTR["123ya03_4"] = ELEM_AVAR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && sigmap["elk_error_sotr_4"])
	{
		bSOTR["123ya03_4"] = ELEM_ERROR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_4"] && !sigmap["elk_error_sotr_4"])
		bSOTR["123ya03_4"] = ELEM_NORMA;
	else
		bSOTR["123ya03_4"] = ELEM_NOT;
	messages["sotr@123ya03_4"] = bSOTR["123ya03_4"];

//ЗАСЛОНКА 1
	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_2"] && (sigmap["elk_avar_zasl_1"] || sigmap["elk_avar_pit_zasl_1"]))
	{
		bSOTR["zasl1"] = ELEM_AVAR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_2"] && !sigmap["elk_avar_zasl_1"])
		bSOTR["zasl1"] = ELEM_NORMA;
	else
		bSOTR["zasl1"] = ELEM_NOT;
	messages["sotr@zasl1"] = bSOTR["zasl1"];

//ЗАСЛОНКА 1 ОТКРЫТА/ЗАКРЫТА
	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_2"] && sigmap["elk_zasl_1_opened"])
		bSOTR["zasl1_opened"] = ELEM_NORMA;
	else
		bSOTR["zasl1_opened"] = ELEM_NOT;
	messages["sotr@zasl1_opened"] = bSOTR["zasl1_opened"];

	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_2"] && sigmap["elk_zasl_1_closed"])
		bSOTR["zasl1_closed"] = ELEM_NORMA;
	else
		bSOTR["zasl1_closed"] = ELEM_NOT;
	messages["sotr@zasl1_closed"] = bSOTR["zasl1_closed"];

	QString zasl1_user = QString("");
	if(bSOTR["zasl1_opened"] == ELEM_NORMA)
		zasl1_user = QString("opened");
	else if(bSOTR["zasl1_closed"] == ELEM_NORMA)
		zasl1_user = QString("closed");

//ВЕНТИЛЯТОР 1
	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_2"] && sigmap["elk_avar_vent_sotr_1"])
	{
		bSOTR["vent1"] = ELEM_AVAR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_2"] && !sigmap["elk_avar_vent_sotr_1"] && sigmap["elk_vkl_vent_sotr_1"])
		bSOTR["vent1"] = ELEM_NORMA;
	else
		bSOTR["vent1"] = ELEM_NOT;
	messages["sotr@vent1"] = bSOTR["vent1"];

//ЗАСЛОНКА 2
	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_4"] && (sigmap["elk_avar_zasl_2"] || sigmap["elk_avar_pit_zasl_2"]))
	{
		bSOTR["zasl2"] = ELEM_AVAR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_4"] && !sigmap["elk_avar_zasl_2"])
		bSOTR["zasl2"] = ELEM_NORMA;
	else
		bSOTR["zasl2"] = ELEM_NOT;
	messages["sotr@zasl2"] = bSOTR["zasl2"];

//ЗАСЛОНКА 2 ОТКРЫТА/ЗАКРЫТА
	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_4"] && sigmap["elk_zasl_2_opened"])
		bSOTR["zasl2_opened"] = ELEM_NORMA;
	else
		bSOTR["zasl2_opened"] = ELEM_NOT;
	messages["sotr@zasl2_opened"] = bSOTR["zasl2_opened"];

	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_4"] && sigmap["elk_zasl_2_closed"])
		bSOTR["zasl2_closed"] = ELEM_NORMA;
	else
		bSOTR["zasl2_closed"] = ELEM_NOT;
	messages["sotr@zasl2_closed"] = bSOTR["zasl2_closed"];

	QString zasl2_user = QString("");
	if(bSOTR["zasl2_opened"] == ELEM_NORMA)
		zasl2_user = QString("opened");
	else if(bSOTR["zasl2_closed"] == ELEM_NORMA)
		zasl2_user = QString("closed");

//ВЕНТИЛЯТОР 2
	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_4"] && sigmap["elk_avar_vent_sotr_2"])
	{
		bSOTR["vent2"] = ELEM_AVAR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_4"] && !sigmap["elk_avar_vent_sotr_2"] && sigmap["elk_vkl_vent_sotr_2"])
		bSOTR["vent2"] = ELEM_NORMA;
	else
		bSOTR["vent2"] = ELEM_NOT;
	messages["sotr@vent2"] = bSOTR["vent2"];

//ЗАСЛОНКА 3
	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_1"] && (sigmap["elk_avar_zasl_3"] || sigmap["elk_avar_pit_zasl_3"]))
	{
		bSOTR["zasl3"] = ELEM_AVAR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_1"] && !sigmap["elk_avar_zasl_3"])
		bSOTR["zasl3"] = ELEM_NORMA;
	else
		bSOTR["zasl3"] = ELEM_NOT;
	messages["sotr@zasl3"] = bSOTR["zasl3"];

//ЗАСЛОНКА 3 ОТКРЫТА/ЗАКРЫТА
	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_1"] && sigmap["elk_zasl_3_opened"])
		bSOTR["zasl3_opened"] = ELEM_NORMA;
	else
		bSOTR["zasl3_opened"] = ELEM_NOT;
	messages["sotr@zasl3_opened"] = bSOTR["zasl3_opened"];

	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_1"] && sigmap["elk_zasl_3_closed"])
		bSOTR["zasl3_closed"] = ELEM_NORMA;
	else
		bSOTR["zasl3_closed"] = ELEM_NOT;
	messages["sotr@zasl3_closed"] = bSOTR["zasl3_closed"];

	QString zasl3_user = QString("");
	if(bSOTR["zasl3_opened"] == ELEM_NORMA)
		zasl3_user = QString("opened");
	else if(bSOTR["zasl3_closed"] == ELEM_NORMA)
		zasl3_user = QString("closed");

//ЗАСЛОНКА 4
	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_3"] && (sigmap["elk_avar_zasl_4"] || sigmap["elk_avar_pit_zasl_4"]))
	{
		bSOTR["zasl4"] = ELEM_AVAR;
		nError++;
	}
	else if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_3"] && !sigmap["elk_avar_zasl_4"])
		bSOTR["zasl4"] = ELEM_NORMA;
	else
		bSOTR["zasl4"] = ELEM_NOT;
	messages["sotr@zasl4"] = bSOTR["zasl4"];

//ЗАСЛОНКА 4 ОТКРЫТА/ЗАКРЫТА
	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_3"] && sigmap["elk_zasl_4_opened"])
		bSOTR["zasl4_opened"] = ELEM_NORMA;
	else
		bSOTR["zasl4_opened"] = ELEM_NOT;
	messages["sotr@zasl4_opened"] = bSOTR["zasl4_opened"];

	if(bSOTR["isSotrOk"] == ELEM_NORMA && !sigmap["elk_obmen_sotr_3"] && sigmap["elk_zasl_4_closed"])
		bSOTR["zasl4_closed"] = ELEM_NORMA;
	else
		bSOTR["zasl4_closed"] = ELEM_NOT;
	messages["sotr@zasl4_closed"] = bSOTR["zasl4_closed"];

	QString zasl4_user = QString("");
	if(bSOTR["zasl4_opened"] == ELEM_NORMA)
		zasl4_user = QString("opened");
	else if(bSOTR["zasl4_closed"] == ELEM_NORMA)
		zasl4_user = QString("closed");

//ОТКЛ ТЕПЛОВЕНТ
	bSOTR["teplovent"] = b124ee02["qf_teplovent"];

//КОНДИЦИОНЕР 1
	bSOTR["cond1"] = bCOND["cond1_obSost"];

//КОНДИЦИОНЕР 2
	bSOTR["cond2"] = bCOND["cond2_obSost"];

//Неисправность
	if(bSensors["t_internal"] == ELEM_ERROR || bSensors["t_external"] == ELEM_ERROR)
		nError++;

//Аварии
	if(bSensors["t_internal"] == ELEM_AVAR || bSensors["t_external"] == ELEM_AVAR)
		nAvar++;
	if(bSOTR["123ya03_1"] == ELEM_AVAR && bSOTR["123ya03_3"] == ELEM_AVAR)
		nAvar++;
	if(bSOTR["123ya03_2"] == ELEM_AVAR && bSOTR["123ya03_4"] == ELEM_AVAR)
		nAvar++;
	if(bSOTR["zasl1"] == ELEM_AVAR && bSOTR["zasl2"] == ELEM_AVAR)
		nAvar++;
	if(bSOTR["zasl3"] == ELEM_AVAR && bSOTR["zasl4"] == ELEM_AVAR)
		nAvar++;
	if(bSOTR["cond1"] == ELEM_AVAR && bSOTR["cond2"] == ELEM_AVAR)
		nAvar++;

//НОРМА СОТР
	if(b125yy03["isOkPwr"] == ELEM_NORMA && 
		(bSOTR["cond1"] == ELEM_NORMA || bSOTR["cond2"] == ELEM_NORMA || 
		bSOTR["vent1"] == ELEM_NORMA || bSOTR["vent2"] == ELEM_NORMA) &&
		bSOTR["zasl1"] == ELEM_NORMA && bSOTR["zasl2"] == ELEM_NORMA &&
		bSOTR["zasl3"] == ELEM_NORMA && bSOTR["zasl4"] == ELEM_NORMA)
		bSOTR["sotrNorma"] = ELEM_NORMA;
	else
		bSOTR["sotrNorma"] = ELEM_NOT;

//Общее состояние
	if(b125yy03["isOkPwr"] == ELEM_NORMA && ((nAvar != 0) || (bSOTR["sotrAvar"] == ELEM_AVAR)))
		bSOTR["obSost"] = ELEM_AVAR;
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && (nError != 0))
		bSOTR["obSost"] = ELEM_ERROR;
	else if(b125yy03["isOkPwr"] == ELEM_NORMA && bSOTR["sotrNorma"] == ELEM_NORMA)
		bSOTR["obSost"] = ELEM_NORMA;
	else
		bSOTR["obSost"] = ELEM_NOT;


	elements["sotr@cond1"] = bSOTR["cond1"].toString() + b124yy08["mest"].toStringMest();
	elements["sotr@cond2"] = bSOTR["cond2"].toString() + b124yy08["mest"].toStringMest();

	elements["sotr@vent1"] = bSOTR["vent1"].toString() + b124yy08["mest"].toStringMest();
	elements["sotr@vent2"] = bSOTR["vent2"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@vent1"] = bSOTR["vent1"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@vent2"] = bSOTR["vent2"].toString() + b124yy08["mest"].toStringMest();

	elements["sotr@teplovent"] = bSOTR["teplovent"].toString();

	elements["sotr@zasl1"] = bSOTR["zasl1"].toString() + b124yy08["mest"].toStringMest();
	elements["sotr@zasl1"].setUser(zasl1_user);
	elements["sotr@zasl2"] = bSOTR["zasl2"].toString() + b124yy08["mest"].toStringMest();
	elements["sotr@zasl2"].setUser(zasl2_user);
	elements["sotr@zasl3"] = bSOTR["zasl3"].toString() + b124yy08["mest"].toStringMest();
	elements["sotr@zasl3"].setUser(zasl3_user);
	elements["sotr@zasl4"] = bSOTR["zasl4"].toString() + b124yy08["mest"].toStringMest();
	elements["sotr@zasl4"].setUser(zasl4_user);
	elements["zal@zasl1"] = bSOTR["zasl1"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@zasl2"] = bSOTR["zasl2"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@zasl3"] = bSOTR["zasl3"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@zasl4"] = bSOTR["zasl4"].toString() + b124yy08["mest"].toStringMest();

	elements["sotr@123ya03_1"] = bSOTR["123ya03_1"].toString() + b124yy08["mest"].toStringMest();
	elements["sotr@123ya03_2"] = bSOTR["123ya03_2"].toString() + b124yy08["mest"].toStringMest();
	elements["sotr@123ya03_3"] = bSOTR["123ya03_3"].toString() + b124yy08["mest"].toStringMest();
	elements["sotr@123ya03_4"] = bSOTR["123ya03_4"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@123ya03_1"] = bSOTR["123ya03_1"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@123ya03_2"] = bSOTR["123ya03_2"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@123ya03_3"] = bSOTR["123ya03_3"].toString() + b124yy08["mest"].toStringMest();
	elements["zal@123ya03_4"] = bSOTR["123ya03_4"].toString() + b124yy08["mest"].toStringMest();

	elements["base@sotr"] = bSOTR["obSost"].toString() + b124yy08["mest"].toStringMest();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funSensorsPT()
{
	QString str_t_internal, str_t_external, str_p_external;
//P
	if(b125yy03["sensor_p"] == ELEM_NORMA)
	{
		double value = valmap["value_pressure"].toDouble();
		str_p_external = QString("%1").arg(value, 0, 'f', 0);
		bSensors["p_external"] = ELEM_NORMA;
	}
	else
	{
		str_p_external = QString(" ");
		bSensors["p_external"] = ELEM_NOT;
	}

//Т ВНЕШН
	if(b125yy03["sensor_t1"] == ELEM_NORMA && b125yy03["sensor_t2"] == ELEM_NORMA)
	{
		double value1 = valmap["value_temperature_external1"].toDouble();
		double value2 = valmap["value_temperature_external2"].toDouble();
		double value = /*round*/((value1 + value2) / 2.0);
		emit setExtTemperature(value);
		str_t_external = QString("%1").arg(value, 0, 'f', 1);
		bSensors["t_external"] = ELEM_NORMA;
	}
	else if(b125yy03["sensor_t1"] == ELEM_NORMA)
	{
		double value1 = valmap["value_temperature_external1"].toDouble();
		emit setExtTemperature(value1);
		str_t_external = QString("%1").arg(value1, 0, 'f', 1);
		bSensors["t_external"] = ELEM_NORMA;
	}
	else if(b125yy03["sensor_t2"] == ELEM_NORMA)
	{
		double value2 = valmap["value_temperature_external2"].toDouble();
		emit setExtTemperature(value2);
		str_t_external = QString("%1").arg(value2, 0, 'f', 1);
		bSensors["t_external"] = ELEM_NORMA;
	}
	else
	{
		str_t_external = QString(" ");
		bSensors["t_external"] = ELEM_NOT;
	}

//Т ВНУТР
	if(b125yy03["sensor_t3"] == ELEM_NORMA)
	{
		double value = valmap["value_temperature_internal"].toDouble();
		str_t_internal = QString("%1").arg(value, 0, 'f', 1);

		if(value < 4.5)
		{
			bSensors["t_internal"] = ELEM_AVAR;
		}
		else if(value >= 4.5 && value < 5.5)
		{
			if(bSensors["t_internal"] == ELEM_AVAR)
				bSensors["t_internal"] = ELEM_AVAR;
			else
				bSensors["t_internal"] = ELEM_ERROR;
 		}
		else if(value >= 5.5 && value < 6.5)
		{
			bSensors["t_internal"] = ELEM_ERROR;
		}
		else if(value >= 6.5 && value < 7.5)
		{
			if(bSensors["t_internal"] == ELEM_ERROR)
				bSensors["t_internal"] = ELEM_ERROR;
			else
				bSensors["t_internal"] = ELEM_NORMA;
		}
		else if(value >= 7.5 && value < 29.5)
		{
			bSensors["t_internal"] = ELEM_NORMA;
		}
		else if(value >= 29.5 && value < 30.5)
		{
			if(bSensors["t_internal"] == ELEM_NORMA)
				bSensors["t_internal"] = ELEM_NORMA;
			else
				bSensors["t_internal"] = ELEM_ERROR;
		}
		else if(value >= 30.5 && value < 34.5)
		{
			bSensors["t_internal"] = ELEM_ERROR;
		}
		else if(value >= 34.5 && value < 35.5)
		{
			if(bSensors["t_internal"] == ELEM_AVAR)
				bSensors["t_internal"] = ELEM_AVAR;
			else
				bSensors["t_internal"] = ELEM_ERROR;
		}
		else if(value >= 35.5)
		{
			bSensors["t_internal"] = ELEM_AVAR;
		}
	}
	else
	{
		str_t_internal = QString(" ");
		bSensors["t_internal"] = ELEM_NOT;
	}
	messages["sotr@t_internal"] = bSensors["t_internal"];

	elements["sotr@t_external"] = bSensors["t_external"].toString();
	elements["sotr@t_external"].setText(str_t_external);
	elements["sotr@t_internal"] = bSensors["t_internal"].toString();
	elements["sotr@t_internal"].setText(str_t_internal);
	elements["sotr@p_external"] = bSensors["p_external"].toString();
	elements["sotr@p_external"].setText(str_p_external);

	elements["base@t_external"] = bSensors["t_external"].toString();
	elements["base@t_external"].setText(str_t_external);
	elements["base@t_internal"] = bSensors["t_internal"].toString();
	elements["base@t_internal"].setText(str_t_internal);
}

// ----------------------------------------------------------------------------
