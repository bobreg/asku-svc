#ifndef _CANALASKU_STRUCT_H_
#define _CANALASKU_STRUCT_H_

#include <QVariantMap>
#include "canalasku_defines.h"

//-------------------------------------------------------------------

typedef struct PRDN_1B_type
{
	unsigned char mest						:1; // ПРД МЕСТ ВКЛ
	unsigned char vkl27v					:1; // 27В ПИТ ПРД ВКЛ
	unsigned char avar27v					:1; // АВАР 27В ПИТ ПРД
	unsigned char norma123bb01_1			:1; // ИСПР 123ББ01(1)
	unsigned char qf123bb01_1				:1; // ОТКЛ QF 123ББ01(1)
	unsigned char norma123bb01_2			:1; // ИСПР 123ББ01(2)
	unsigned char qf123bb01_2				:1; // ОТКЛ QF 123ББ01(2)
	unsigned char normaSVChComm				:1; // НОРМА СВЧ КОММУТ
} tPRDN_1B;

typedef struct PRDN_2B_type
{
	unsigned char vkl123gv02				:1; // ВКЛ 123ГВ02-1(2)
	unsigned char avar123gv02				:1; // АВАР 123ГВ02-1(2)
	unsigned char qf123gv02					:1; // ОТКЛ QF 123ГВ02-1(2)
	unsigned char vkl380					:1; // 380В ПИТ ПРД ВКЛ
	unsigned char normaPrd					:1; // ПРД ИСПРАВЕН
	unsigned char errorPrd					:1; // ПРД НЕИСПРАВЕН
	unsigned char avarPrd					:1; // АВАРИЯ ПРД
	unsigned char qfChp1					:1; // ОТКЛ QF ЧП1
} tPRDN_2B;

typedef struct PRDN_3B_type
{
	unsigned char qfChp2					:1; // ОТКЛ QF ЧП2
	unsigned char umi1Avar					:1; // АВАРИЯ УМИ1
	unsigned char umi1Link					:1; // НЕТ СВЯЗИ УМИ1
	unsigned char umi2Avar					:1; // АВАРИЯ УМИ2
	unsigned char umi2Link					:1; // НЕТ СВЯЗИ УМИ2
	unsigned char umi3Avar					:1; // АВАРИЯ УМИ3
	unsigned char umi3Link					:1; // НЕТ СВЯЗИ УМИ3
	unsigned char umi4Avar					:1; // АВАРИЯ УМИ4
} tPRDN_3B;

typedef struct PRDN_4B_type
{
	unsigned char umi4Link					:1; // НЕТ СВЯЗИ УМИ4
	unsigned char umi5Avar					:1; // АВАРИЯ УМИ5
	unsigned char umi5Link					:1; // НЕТ СВЯЗИ УМИ5
	unsigned char umi6Avar					:1; // АВАРИЯ УМИ6
	unsigned char umi6Link					:1; // НЕТ СВЯЗИ УМИ6
	unsigned char umi7Avar					:1; // АВАРИЯ УМИ7
	unsigned char umi7Link					:1; // НЕТ СВЯЗИ УМИ7
	unsigned char umi8Avar					:1; // АВАРИЯ УМИ8
} tPRDN_4B;

typedef struct PRDN_5B_type
{
	unsigned char umi8Link					:1; // НЕТ СВЯЗИ УМИ8
	unsigned char umi9Avar					:1; // АВАРИЯ УМИ9
	unsigned char umi9Link					:1; // НЕТ СВЯЗИ УМИ9
	unsigned char umi10Avar					:1; // АВАРИЯ УМИ10
	unsigned char umi10Link					:1; // НЕТ СВЯЗИ УМИ10
	unsigned char umi11Avar					:1; // АВАРИЯ УМИ11
	unsigned char umi11Link					:1; // НЕТ СВЯЗИ УМИ11
	unsigned char umi12Avar					:1; // АВАРИЯ УМИ12
} tPRDN_5B;

typedef struct PRDN_6B_type
{
	unsigned char umi12Link					:1; // НЕТ СВЯЗИ УМИ12
	unsigned char umi13Avar					:1; // АВАРИЯ УМИ13
	unsigned char umi13Link					:1; // НЕТ СВЯЗИ УМИ13
	unsigned char umi14Avar					:1; // АВАРИЯ УМИ14
	unsigned char umi14Link					:1; // НЕТ СВЯЗИ УМИ14
	unsigned char umi15Avar					:1; // АВАРИЯ УМИ15
	unsigned char umi15Link					:1; // НЕТ СВЯЗИ УМИ15
	unsigned char umi16Avar					:1; // АВАРИЯ УМИ16
} tPRDN_6B;

typedef struct PRDN_7B_type
{
	unsigned char umi16Link					:1; // НЕТ СВЯЗИ УМИ16
	unsigned char umi17Avar					:1; // АВАРИЯ УМИ17
	unsigned char umi17Link					:1; // НЕТ СВЯЗИ УМИ17
	unsigned char umi18Avar					:1; // АВАРИЯ УМИ18
	unsigned char umi18Link					:1; // НЕТ СВЯЗИ УМИ18
	unsigned char umi19Avar					:1; // АВАРИЯ УМИ19
	unsigned char umi19Link					:1; // НЕТ СВЯЗИ УМИ19
	unsigned char umi20Avar					:1; // АВАРИЯ УМИ20
} tPRDN_7B;

typedef struct PRDN_8B_type
{
	unsigned char umi20Link					:1; // НЕТ СВЯЗИ УМИ20
	unsigned char umi21Avar					:1; // АВАРИЯ УМИ21
	unsigned char umi21Link					:1; // НЕТ СВЯЗИ УМИ21
	unsigned char umi22Avar					:1; // АВАРИЯ УМИ22
	unsigned char umi22Link					:1; // НЕТ СВЯЗИ УМИ22
	unsigned char umi23Avar					:1; // АВАРИЯ УМИ23
	unsigned char umi23Link					:1; // НЕТ СВЯЗИ УМИ23
	unsigned char umi24Avar					:1; // АВАРИЯ УМИ24
} tPRDN_8B;

typedef struct PRDN_9B_type
{
	unsigned char umi24Link					:1; // НЕТ СВЯЗИ УМИ24
	unsigned char umi25Avar					:1; // АВАРИЯ УМИ25
	unsigned char umi25Link					:1; // НЕТ СВЯЗИ УМИ25
	unsigned char umi26Avar					:1; // АВАРИЯ УМИ26
	unsigned char umi26Link					:1; // НЕТ СВЯЗИ УМИ26
	unsigned char umi27Avar					:1; // АВАРИЯ УМИ27
	unsigned char umi27Link					:1; // НЕТ СВЯЗИ УМИ27
	unsigned char umi28Avar					:1; // АВАРИЯ УМИ28
} tPRDN_9B;

typedef struct PRDN_10B_type
{
	unsigned char umi28Link					:1; // НЕТ СВЯЗИ УМИ28
	unsigned char umi29Avar					:1; // АВАРИЯ УМИ29
	unsigned char umi29Link					:1; // НЕТ СВЯЗИ УМИ29
	unsigned char umi30Avar					:1; // АВАРИЯ УМИ30
	unsigned char umi30Link					:1; // НЕТ СВЯЗИ УМИ30
	unsigned char umi31Avar					:1; // АВАРИЯ УМИ31
	unsigned char umi31Link					:1; // НЕТ СВЯЗИ УМИ31
	unsigned char umi32Avar					:1; // АВАРИЯ УМИ32
} tPRDN_10B;

typedef struct PRDN_11B_type
{
	unsigned char umi32Link					:1; // НЕТ СВЯЗИ УМИ32
	unsigned char avarD2vv056				:1; // АВАР Д2ВВ056(2)
	unsigned char avar124yy08				:1; // АВАР 124УУ08
	unsigned char blokirIzluchPrd			:1; // БЛОКИР ИЗЛУЧ ПРД
	unsigned char rez1						:3; // резерв
	unsigned char qfVent					:1; // ОТКЛ QF ВЕНТ ОБЩИЙ
} tPRDN_11B;

typedef struct PRDN_12B_type
{
	unsigned char qf126gg02					:1; // ОТКЛ QF 126ГГ02-1(2)
	unsigned char qf124yy08					:1; // ОТКЛ QF 124УУ08
	unsigned char avarD2hl142				:1; // АВАР Д2ХЛ142 1(2)
	unsigned char commSvchPos				:1; // КОММ СВЧ ПОЛ 1(2)
	unsigned char qfVentOtkl				:1; // ОТКЛ QF ВЕНТ 1(2)
	unsigned char rez1						:3; // резерв
} tPRDN_12B;

//-------------------------------------------------------------------

typedef union tagPRD_1B_union
{
	tPRDN_1B BitsN;
	unsigned char Byte;
}PRD_1B;

typedef union tagPRD_2B_union
{
	tPRDN_2B BitsN;
	unsigned char Byte;
}PRD_2B;

typedef union tagPRD_3B_union
{
	tPRDN_3B BitsN;
	unsigned char Byte;
}PRD_3B;

typedef union tagPRD_4B_union
{
	tPRDN_4B BitsN;
	unsigned char Byte;
}PRD_4B;

typedef union tagPRD_5B_union
{
	tPRDN_5B BitsN;
	unsigned char Byte;
}PRD_5B;

typedef union tagPRD_6B_union
{
	tPRDN_6B BitsN;
	unsigned char Byte;
}PRD_6B;

typedef union tagPRD_7B_union
{
	tPRDN_7B BitsN;
	unsigned char Byte;
}PRD_7B;

typedef union tagPRD_8B_union
{
	tPRDN_8B BitsN;
	unsigned char Byte;
}PRD_8B;

typedef union tagPRD_9B_union
{
	tPRDN_9B BitsN;
	unsigned char Byte;
}PRD_9B;

typedef union tagPRD_10B_union
{
	tPRDN_10B BitsN;
	unsigned char Byte;
}PRD_10B;

typedef union tagPRD_11B_union
{
	tPRDN_11B BitsN;
	unsigned char Byte;
}PRD_11B;

typedef union tagPRD_12B_union
{
	tPRDN_12B BitsN;
	unsigned char Byte;
}PRD_12B;

//-------------------------------------------------------------------

typedef struct EUVN_1B_type
{
	unsigned char qf_123bb01_1				:1; // ОТКЛ 123ББ01-1
	unsigned char qf_123bb01_2				:1; // ОТКЛ 123ББ01-2
	unsigned char qf_123bb01_3				:1; // ОТКЛ 123ББ01-3
	unsigned char qf_123bb01_4				:1; // ОТКЛ 123ББ01-4
	unsigned char qf_27v_buf				:1; // ОТКЛ 27V БУФ
	unsigned char qf_rozet_220v				:1; // ОТКЛ РОЗЕТ 220В
	unsigned char qf_cond1					:1; // ОТКЛ КОНДИЦИОНЕР 1
	unsigned char qf_cond2					:1; // ОТКЛ КОНДИЦИОНЕР 2
}tEUVN_1B;

typedef struct EUVN_2B_type
{
	unsigned char qf_kmvrl1					:1; // ОТКЛ КМВРЛ 1
	unsigned char qf_kmvrl2					:1; // ОТКЛ КМВРЛ 2
	unsigned char qf_teplovent				:1; // ОТКЛ ТЕПЛОВЕНТ
	unsigned char qf_124yg02				:1; // ОТКЛ 124УГ02
	unsigned char qf_avar_osv				:1; // ОТКЛ АВАР ОСВ
	unsigned char qf_380v_rpu				:1; // ОТКЛ 380V РПУ АВТ
	unsigned char qf_380v_set				:1; // ОТКЛ СЕТЬ 380V АВТ
	unsigned char qf_124yy03_1				:1; // ОТКЛ 124УУ03-1
}tEUVN_2B;

typedef struct EUVN_3B_type
{
	unsigned char qf_124yy03_2				:1; // ОТКЛ 124УУ03-2
	unsigned char qf_prm1					:1; // ОТКЛ ПРМ 1
	unsigned char qf_prm2					:1; // ОТКЛ ПРМ 2
	unsigned char qf_prd1					:1; // ОТКЛ ПРД 1
	unsigned char qf_prd2					:1; // ОТКЛ ПРД 2
	unsigned char qf_obr1					:1; // ОТКЛ АППАР ОБРАБ 1
	unsigned char qf_obr2					:1; // ОТКЛ АППАР ОБРАБ 2
	unsigned char qf_ups1					:1; // ОТКЛ ИБП 1
}tEUVN_3B;

typedef struct EUVN_4B_type
{
	unsigned char qf_ups2					:1; // ОТКЛ ИБП 2
	unsigned char otkl_cont_380v			:1; // СЕТЬ 380V КОНТ ОТКЛ
	unsigned char p27v_gsh					:1; // 27V ГШ
	unsigned char ups1_error				:1; // НЕИСПР ИБП 1
	unsigned char ups2_error				:1; // НЕИСПР ИБП 2
	unsigned char p27v_123bb02				:1; // 27V 123ББ02
	unsigned char p27v_pit_avt				:1; // 27V ПИТ АВТ
	unsigned char p27v_howl1				:1; // 27V РЕВУН 1
}tEUVN_4B;

typedef struct EUVN_5B_type
{
	unsigned char p27v_howl2				:1; // 27V РЕВУН 2
	unsigned char p27v_prm1					:1; // 27V ПРМ 1
	unsigned char p27v_prm2					:1; // 27V ПРМ 2
	unsigned char p27v_mspd					:1; // 27V МСПД
	unsigned char p27v_zu1					:1; // 27V ЗУ 1
	unsigned char p27v_zu2					:1; // 27V ЗУ 2
	unsigned char p27v_ps1					:1; // 27V ПС 1
	unsigned char p27v_ps2					:1; // 27V ПС 2
}tEUVN_5B;

typedef struct EUVN_6B_type
{
	unsigned char p27v_123gv02_1			:1; // 27V 123ГВ02-1
	unsigned char p27v_123gv02_2			:1; // 27V 123ГВ02-2
	unsigned char p27v_azs1					:1; // 27V АЗИМ ДАТЧ 1
	unsigned char p27v_azs2					:1; // 27V АЗИМ ДАТЧ 2
	unsigned char accum_24v					:1; // 24V НАПР АККУМ
	unsigned char work_cond_1				:1; // РАБОТА КОНД 1
	unsigned char p27v_opu					:1; // 27V ОПУ
	unsigned char avar124yg02				:1; // АВАР 124УГ02
}tEUVN_6B;

typedef struct EUVN_7B_type
{
	unsigned char norma_123bb01_1			:1; // НОРМА 123ББ01-1
	unsigned char norma_123bb01_2			:1; // НОРМА 123ББ01-2
	unsigned char norma_123bb01_3			:1; // НОРМА 123ББ01-3
	unsigned char norma_123bb01_4			:1; // НОРМА 123ББ01-4
	unsigned char avar_123bb01_1			:1; // АВАРИЯ 123ББ01-1
	unsigned char avar_123bb01_2			:1; // АВАРИЯ 123ББ01-2
	unsigned char avar_123bb01_3			:1; // АВАРИЯ 123ББ01-3
	unsigned char avar_123bb01_4			:1; // АВАРИЯ 123ББ01-4
}tEUVN_7B;

typedef struct EUVN_8B_type
{
	unsigned char aorls						:1; // АОРЛС
	unsigned char opu_open					:1; // ЛЮК ОПУ ОТКР
	unsigned char qf_sotr					:1; // ОТКЛ СОТР
	unsigned char qf_pos					:1; // ОТКЛ ПОС
	unsigned char qf_27v_c					:1; // ОТКЛ 27V-Ц
	unsigned char qf_trm					:1; // ОТКЛ ТРМ
	unsigned char qf_osv_apm				:1; // ОТКЛ ОСВЕЩ АПМ
	unsigned char vkl_cont_osv_perim		:1; // ОСВЕЩ ПЕРИМ КОНТ ВКЛ
}tEUVN_8B;

typedef struct EUVN_9B_type
{
	unsigned char qf_accum					:1; // ОТКЛ АККУМ
	unsigned char avar_sotr					:1; // АВАРИЯ СОТР
	unsigned char qf_osv_perim				:1; // ОТКЛ ОСВЕЩ ПЕРИМ
	unsigned char work_cond_2				:1; // РАБОТА КОНД 2
	unsigned char p27v_pit_signal			:1; // ПИТАН СИГНАЛ
	unsigned char p27v_124yy03_1			:1; // 27V 124УУ03-1
	unsigned char p27v_124yy03_2			:1; // 27V 124УУ03-2
	unsigned char avar_zasl_1				:1; // АВАР ЗАСЛ 1
}tEUVN_9B;

typedef struct EUVN_10B_type
{
	unsigned char avar_zasl_2				:1; // АВАР ЗАСЛ 2
	unsigned char avar_zasl_3				:1; // АВАР ЗАСЛ 3
	unsigned char avar_zasl_4				:1; // АВАР ЗАСЛ 4
	unsigned char vkl_vent_sotr_1			:1; // ВЕНТ 1 СОТР ВКЛ
	unsigned char vkl_vent_sotr_2			:1; // ВЕНТ 2 СОТР ВКЛ
	unsigned char obmen_sotr_1				:1; // НЕИСПР ОБМЕНА 1
	unsigned char obmen_sotr_2				:1; // НЕИСПР ОБМЕНА 2
	unsigned char obmen_sotr_3				:1; // НЕИСПР ОБМЕНА 3
}tEUVN_10B;

typedef struct EUVN_11B_type
{
	unsigned char obmen_sotr_4				:1; // НЕИСПР ОБМЕНА 4
	unsigned char zasl_1_opened				:1; // ЗАСЛ 1 ОТКР
	unsigned char zasl_1_closed				:1; // ЗАСЛ 1 ЗАКР
	unsigned char zasl_2_opened				:1; // ЗАСЛ 2 ОТКР
	unsigned char reserv_1					:1; // РЕЗЕРВ 1
	unsigned char reserv_2					:1; // РЕЗЕРВ 2
	unsigned char reserv_3					:1; // РЕЗЕРВ 3
	unsigned char reserv_4					:1; // РЕЗЕРВ 4
}tEUVN_11B;

typedef struct EUVN_12B_type
{
	unsigned char zasl_2_closed				:1; // ЗАСЛ 2 ЗАКР
	unsigned char zasl_3_opened				:1; // ЗАСЛ 3 ОТКР
	unsigned char zasl_3_closed				:1; // ЗАСЛ 3 ЗАКР
	unsigned char zasl_4_opened				:1; // ЗАСЛ 4 ОТКР
	unsigned char zasl_4_closed				:1; // ЗАСЛ 4 ЗАКР
	unsigned char mest						:1; // МЕСТ
	unsigned char avar_pit_zasl_1			:1; // АВАРИЯ ПИТ ЗАСЛ 1
	unsigned char avar_pit_zasl_2			:1; // АВАРИЯ ПИТ ЗАСЛ 2
}tEUVN_12B;

typedef struct EUVN_13B_type
{
	unsigned char avar_pit_zasl_3			:1; // АВАРИЯ ПИТ ЗАСЛ 3
	unsigned char avar_pit_zasl_4			:1; // АВАРИЯ ПИТ ЗАСЛ 4
	unsigned char avar_vent_sotr_1			:1; // АВАРИЯ ВЕНТ 1 СОТР
	unsigned char avar_vent_sotr_2			:1; // АВАРИЯ ВЕНТ 2 СОТР
	unsigned char avar_cond_1				:1; // АВАРИЯ КОНД 1
	unsigned char avar_cond_2				:1; // АВАРИЯ КОНД 2
	unsigned char block_opu					:1; // БЛОКИР ОПУ НАРУШ
	unsigned char avar_vent_12				:1; // АВАРИЯ ВЕНТ 1,2
}tEUVN_13B;

typedef struct EUVN_14B_type
{
	unsigned char cond1_kz_dt_vh_1			:1; // КЗ ДТ ВХU1/1
	unsigned char cond1_hh_dt_vh_1			:1; // ОБРЫВ ДТ ВХU1/1
	unsigned char cond1_kz_dt_vh_2			:1; // КЗ ДТ ВХU2/1
	unsigned char cond1_hh_dt_vh_2			:1; // ОБРЫВ ДТ ВХU2/1
	unsigned char cond1_avar_dvig_compr		:1; // АВАР ДВИГ КОМПР/1
	unsigned char cond1_avar_davl_rd1		:1; // АВАР ДАВЛ РД-1/1
	unsigned char cond1_avar_davl_rd2		:1; // АВАР ДАВЛ РД-2/1
	unsigned char cond1_avar_min_davl_vsas	:1; // АВАР МИН ДАВЛ ВСАС/1
}tEUVN_14B;

typedef struct EUVN_15B_type
{
	unsigned char cond1_avar_max_davl_nagn	:1; // АВАР МАКС ДАВЛ НАГН/1
	unsigned char cond1_avar_vent_recirc	:1; // АВАР ВЕНТ РЕЦИРК/1
	unsigned char cond1_avar_vent_kondens	:1; // АВАР ВЕНТ КОНДЕНС/1
	unsigned char cond2_kz_dt_vh_1			:1; // КЗ ДТ ВХU1/2
	unsigned char cond2_hh_dt_vh_1			:1; // ОБРЫВ ДТ ВХU1/2
	unsigned char cond2_kz_dt_vh_2			:1; // КЗ ДТ ВХU2/2
	unsigned char cond2_hh_dt_vh_2			:1; // ОБРЫВ ДТ ВХU2/2
	unsigned char cond2_avar_dvig_compr		:1; // АВАР ДВИГ КОМПР/2
}tEUVN_15B;

typedef struct EUVN_16B_type
{
	unsigned char cond2_avar_davl_rd1		:1; // АВАР ДАВЛ РД-1/2
	unsigned char cond2_avar_davl_rd2		:1; // АВАР ДАВЛ РД-2/2
	unsigned char cond2_avar_min_davl_vsas	:1; // АВАР МИН ДАВЛ ВСАС/2
	unsigned char cond2_avar_max_davl_nagn	:1; // АВАР МАКС ДАВЛ НАГН/2
	unsigned char cond2_avar_vent_recirc	:1; // АВАР ВЕНТ РЕЦИРК/2
	unsigned char cond2_avar_vent_kondens	:1; // АВАР ВЕНТ КОНДЕНС/2
	unsigned char p27v_a_15_17				:1; // ВКЛ А 15...А 17
	unsigned char p27v_a_18_20				:1; // ВКЛ А 18...А 20
}tEUVN_16B;

typedef struct EUVN_17B_type
{
	unsigned char cond1_ventile				:1; // ВЕНТИЛЬ СВМ 1
	unsigned char cond1_vent_recirc			:1; // ВЕНТ РЕЦИРКУЛЯЦИИ 1
	unsigned char cond1_vent_kondens		:1; // ВЕНТ КОНДЕНСАТОРА 1
	unsigned char cond1_vkl					:1; // СИГНАЛ ВКЛЮЧЕНИЕ 1
	unsigned char cond1_kontroller			:1; // РАБОТА КОНТРОЛЛЕР 1
	unsigned char cond1_avar_kontroller		:1; // ОБЩ АВАР КОНТРОЛЛЕР 1
	unsigned char put_reset_avar			:1; // НАЖАТЬ СБРОС АВАРИИ
	unsigned char cond1_link				:1; // НЕТ СВЯЗИ 1
}tEUVN_17B;

typedef struct EUVN_18B_type
{
	unsigned char cond2_ventile				:1; // ВЕНТИЛЬ СВМ 2
	unsigned char cond2_vent_recirc			:1; // ВЕНТ РЕЦИРКУЛЯЦИИ 2
	unsigned char cond2_vent_kondens		:1; // ВЕНТ КОНДЕНСАТОРА 2
	unsigned char cond2_vkl					:1; // СИГНАЛ ВКЛЮЧЕНИЕ 2
	unsigned char cond2_kontroller			:1; // РАБОТА КОНТРОЛЛЕР 2
	unsigned char cond2_avar_kontroller		:1; // ОБЩ АВАР КОНТРОЛЛЕР 2
	unsigned char reserved					:1; // РЕЗЕРВ
	unsigned char cond2_link				:1; // НЕТ СВЯЗИ 2
}tEUVN_18B;

typedef struct EUVN_19B_type
{
	unsigned char error_sotr_1				:1; // НЕИСПР СОТР 1
	unsigned char error_sotr_2				:1; // НЕИСПР СОТР 2
	unsigned char error_sotr_3				:1; // НЕИСПР СОТР 3
	unsigned char error_sotr_4				:1; // НЕИСПР СОТР 4
	unsigned char t_below_5					:1; // ВНУТР ТЕМП НИЖЕ 5С
	unsigned char t_over_30					:1; // ВНУТР ТЕМП ВЫШЕ 30С
	unsigned char avar_pvu					:1; // АВАРИЯ ПВУ
	unsigned char p27v_a_31_32				:1; // ВКЛ А 31, А 32
}tEUVN_19B;

typedef struct EUVN_34B_type
{
	unsigned char avar_d1					:1; // АВАРИЯ ДАТЧИКА 1
	unsigned char avar_d2					:1; // АВАРИЯ ДАТЧИКА 2
	unsigned char avar_d3					:1; // АВАРИЯ ДАТЧИКА 3
	unsigned char avar_d4					:1; // АВАРИЯ ДАТЧИКА 4
	unsigned char avar_d5					:1; // АВАРИЯ ДАТЧИКА 5
	unsigned char avar_d6					:1; // АВАРИЯ ДАТЧИКА 6
	unsigned char avar_d7					:1; // АВАРИЯ ДАТЧИКА 7
	unsigned char rez						:1; // РЕЗЕРВ
}tEUVN_34B;

//-------------------------------------------------------------------

typedef union tagEUV_1B_union
{
	tEUVN_1B BitsN;
	unsigned char Byte;
}EUV_1B;

typedef union tagEUV_2B_union
{
	tEUVN_2B BitsN;
	unsigned char Byte;
}EUV_2B;

typedef union tagEUV_3B_union
{
	tEUVN_3B BitsN;
	unsigned char Byte;
}EUV_3B;

typedef union tagEUV_4B_union
{
	tEUVN_4B BitsN;
	unsigned char Byte;
}EUV_4B;

typedef union tagEUV_5B_union
{
	tEUVN_5B BitsN;
	unsigned char Byte;
}EUV_5B;

typedef union tagEUV_6B_union
{
	tEUVN_6B BitsN;
	unsigned char Byte;
}EUV_6B;

typedef union tagEUV_7B_union
{
	tEUVN_7B BitsN;
	unsigned char Byte;
}EUV_7B;

typedef union tagEUV_8B_union
{
	tEUVN_8B BitsN;
	unsigned char Byte;
}EUV_8B;

typedef union tagEUV_9B_union
{
	tEUVN_9B BitsN;
	unsigned char Byte;
}EUV_9B;

typedef union tagEUV_10B_union
{
	tEUVN_10B BitsN;
	unsigned char Byte;
}EUV_10B;

typedef union tagEUV_11B_union
{
	tEUVN_11B BitsN;
	unsigned char Byte;
}EUV_11B;

typedef union tagEUV_12B_union
{
	tEUVN_12B BitsN;
	unsigned char Byte;
}EUV_12B;

typedef union tagEUV_13B_union
{
	tEUVN_13B BitsN;
	unsigned char Byte;
}EUV_13B;

typedef union tagEUV_14B_union
{
	tEUVN_14B BitsN;
	unsigned char Byte;
}EUV_14B;

typedef union tagEUV_15B_union
{
	tEUVN_15B BitsN;
	unsigned char Byte;
}EUV_15B;

typedef union tagEUV_16B_union
{
	tEUVN_16B BitsN;
	unsigned char Byte;
}EUV_16B;

typedef union tagEUV_17B_union
{
	tEUVN_17B BitsN;
	unsigned char Byte;
}EUV_17B;

typedef union tagEUV_18B_union
{
	tEUVN_18B BitsN;
	unsigned char Byte;
}EUV_18B;

typedef union tagEUV_19B_union
{
	tEUVN_19B BitsN;
	unsigned char Byte;
}EUV_19B;

typedef struct tagEUVN_HILO
{
	unsigned char Lo;
	unsigned char Hi;
}tEUVN_HILO;

typedef union tagEUV_ADC_union
{
	tEUVN_HILO Bytes;
	short Value;

	inline double DoubleValue() {
		return (double)Value;
	}

	inline bool isOk_old() {
		return (Value >= -1966 && Value <= 1966);
	}
	inline bool isOk() {
		return (Value >= -100 && Value <= 100);
	}

	inline double Temperature(bool *ok = NULL) {
		if(ok)
			*ok = isOk_old();
		return (0.025437*(double)Value);
	}
	inline double Temperature_new(bool *ok = NULL) {
		if(ok)
			*ok = isOk();
		return ((double)Value);
	}

	inline double Pressure() {
		return (83500.0 + (11.9556*(double)Value));
	}

	inline double Pressure_new() {
		return ((double)Value);
	}
}EUV_ADC, EUV_20B_21B, EUV_22B_23B, EUV_24B_25B, EUV_26B_27B, EUV_28B_29B, EUV_30B_31B, EUV_32B_33B;

typedef union tagEUV_34B_union
{
	tEUVN_34B BitsN;
	unsigned char Byte;
}EUV_34B;

//-------------------------------------------------------------------

typedef struct PRD_BPU_1B_type
{
	unsigned char avarBPU			:1; // АВАР БПУ
	unsigned char rez				:1; // резерв
	unsigned char avarUMI1			:1;
	unsigned char avarUMI2			:1;
	unsigned char avarUMI3			:1;
	unsigned char avarUMI4			:1;
	unsigned char avarUMI5			:1;
	unsigned char avarUMI6			:1;
} tPRD_BPU_1B;

typedef struct PRD_BPU_2B_type
{
	unsigned char avarUMI7			:1;
	unsigned char avarUMI8			:1;
	unsigned char avarUMI9			:1;
	unsigned char avarUMI10			:1;
	unsigned char avarUMI11			:1;
	unsigned char avarUMI12			:1;
	unsigned char avarUMI13			:1;
	unsigned char avarUMI14			:1;
} tPRD_BPU_2B;

typedef struct PRD_BPU_3B_type
{
	unsigned char avarUMI15			:1;
	unsigned char avarUMI16			:1;
	unsigned char rez				:6;
} tPRD_BPU_3B;

typedef struct PRD_BPU_4B_type
{
	unsigned char avarUMI17			:1;
	unsigned char avarUMI18			:1;
	unsigned char avarUMI19			:1;
	unsigned char avarUMI20			:1;
	unsigned char avarUMI21			:1;
	unsigned char avarUMI22			:1;
	unsigned char avarUMI23			:1;
	unsigned char avarUMI24			:1;
} tPRD_BPU_4B;

typedef struct PRD_BPU_5B_type
{
	unsigned char avarUMI25			:1;
	unsigned char avarUMI26			:1;
	unsigned char avarUMI27			:1;
	unsigned char avarUMI28			:1;
	unsigned char avarUMI29			:1;
	unsigned char avarUMI30			:1;
	unsigned char avarUMI31			:1;
	unsigned char avarUMI32			:1;
} tPRD_BPU_5B;

typedef struct PRD_BPU_6B_type
{
	unsigned char rez				:8;
} tPRD_BPU_6B;

typedef union tagPRD_BPU_1B_union
{
	tPRD_BPU_1B Bits;
	unsigned char Byte;
}PRD_BPU_1B;

typedef union tagPRD_BPU_2B_union
{
	tPRD_BPU_2B Bits;
	unsigned char Byte;
}PRD_BPU_2B;

typedef union tagPRD_BPU_3B_union
{
	tPRD_BPU_3B Bits;
	unsigned char Byte;
}PRD_BPU_3B;

typedef union tagPRD_BPU_4B_union
{
	tPRD_BPU_4B Bits;
	unsigned char Byte;
}PRD_BPU_4B;

typedef union tagPRD_BPU_5B_union
{
	tPRD_BPU_5B Bits;
	unsigned char Byte;
}PRD_BPU_5B;

typedef union tagPRD_BPU_6B_union
{
	tPRD_BPU_6B Bits;
	unsigned char Byte;
}PRD_BPU_6B;

//-------------------------------------------------------------------

typedef struct EUV_BPU_type
{
	unsigned char avarBPU			:1; // АВАР БПУ
	unsigned char rez				:7; // РЕЗЕРВ
} tEUV_BPU;

typedef union tagEUV_BPU_union
{
	tEUV_BPU Bits;
	unsigned char Byte;
}EUV_BPU;

//-------------------------------------------------------------------

typedef struct PRD_PARAM_UMI_STATE_V5_type
{
	unsigned char impulse               :1;
	unsigned char no_impulse            :1;
	unsigned char u_power               :1;
	unsigned char sensor                :1;
	unsigned char reserved              :4;
} tPRD_PARAM_UMI_STATE_V5;

typedef struct PRD_PARAM_UMI_STATE2_V5_type
{
	unsigned char power380_on           :1;
	unsigned char power_on              :1;
	unsigned char svch_on               :1;
	unsigned char in_power_low          :1;
	unsigned char in_power_high         :1;
	unsigned char out_power             :1;
	unsigned char ksvn                  :1;
	unsigned char temperature           :1;
} tPRD_PARAM_UMI_STATE2_V5;

typedef struct PRD_PARAM_UMI_V5_type
{
	unsigned char n_module;
	unsigned char in_power;
	unsigned char out_power;
	unsigned char ksvn;
	signed char temperature;
	unsigned char u_power;
	union
	{
		tPRD_PARAM_UMI_STATE_V5 bits;
		unsigned char byte;
	}control1;
	union
	{
		tPRD_PARAM_UMI_STATE2_V5 bits;
		unsigned char byte;
	}control2;
	unsigned char serial_lo;
	unsigned char serial_mi;
	unsigned char serial_hi;
	unsigned char phase_set;
	unsigned char phase_def;
	unsigned char time_minute;
	unsigned char time_hour_lo;
	unsigned char time_hour_hi;
	unsigned char reserved1;
	unsigned char reserved2;
}PRD_PARAM_UMI_V5;

typedef union PRD_PARAM_UMI_type
{
	PRD_PARAM_UMI_V5 v5;
}PRD_PARAM_UMI;

//-------------------------------------------------------------------

typedef struct EUV_1_COMMAND_type
{
	unsigned char vklHowl1                   :1; // ВКЛ 1 СИРЕНА ОПУ
	unsigned char vklHowl2                   :1; // ВКЛ 2 СИРЕНА ОПУ
	unsigned char vklRpuLight                :1; // ВКЛ ОСВЕЩ РПУ
	unsigned char sbrosAvar                  :1; // ВКЛ СБРОС АВАР ОБЩ
	unsigned char vklPerimLight              :1; // ВКЛ ОСВЕЩ ПЕРИМ
	unsigned char vklFire                    :1; // ПОЖАР
	unsigned char vklSafe                    :1; // ОХРАНА
	unsigned char vklBlockCond               :1; // ОТКЛ КОНД

	QVariantMap toMap() {
		QVariantMap data;
		data["vklHowl1"]		= vklHowl1;
		data["vklHowl2"]		= vklHowl2;
		data["vklRpuLight"]		= vklRpuLight;
		data["sbrosAvar"]		= sbrosAvar;
		data["vklPerimLight"]	= vklPerimLight;
		data["vklFire"]			= vklFire;
		data["vklSafe"]			= vklSafe;
		data["vklBlockCond"]	= vklBlockCond;
		return data;
	}

	void fromMap(QVariantMap data) {
		vklHowl1		= data["vklHowl1"].toUInt();
		vklHowl2		= data["vklHowl2"].toUInt();
		vklRpuLight		= data["vklRpuLight"].toUInt();
		sbrosAvar		= 0;//data["sbrosAvar"].toUInt();
		vklPerimLight	= data["vklPerimLight"].toUInt();
		vklFire			= data["vklFire"].toUInt();
		vklSafe			= data["vklSafe"].toUInt();
		vklBlockCond	= data["vklBlockCond"].toUInt();
	}
}tEUV_1_COMMAND;

typedef struct EUV_2_COMMAND_type
{
	unsigned char errorRLK                   :1; // РЕВУН СОСТОЯНИЯ
	unsigned char rez                        :7;

	QVariantMap toMap() {
		QVariantMap data;
		data["errorRLK"] = errorRLK;
		return data;
	}

	void fromMap(QVariantMap data) {
		errorRLK = data["errorRLK"].toUInt();
	}
}tEUV_2_COMMAND;

typedef union tagEUV_1_COMMAND_union
{
	tEUV_1_COMMAND BitsN;
	unsigned char Byte;

	tagEUV_1_COMMAND_union() {
		Byte = 0;
	}
}EUV_1_COMMAND;

typedef union tagEUV_2_COMMAND_union
{
	tEUV_2_COMMAND BitsN;
	unsigned char Byte;

	tagEUV_2_COMMAND_union() {
		Byte = 0;
	}
}EUV_2_COMMAND;

typedef struct tagEUV_COMMAND
{
	EUV_1_COMMAND b1;
	EUV_2_COMMAND b2;

	tagEUV_COMMAND() {
	}

	tagEUV_COMMAND(QVariantMap data) {
		fromMap(data);
	}

	QVariantMap toMap() {
		QVariantMap data;
		data.unite(b1.BitsN.toMap());
		data.unite(b2.BitsN.toMap());
		return data;
	}

	void fromMap(QVariantMap data) {
		b1.BitsN.fromMap(data);
		b2.BitsN.fromMap(data);
	}
}EUV_COMMAND;

//-------------------------------------------------------------------

typedef struct PRD_1_COMMAND_type
{
	unsigned char vkl380                     :1; // Вкл 380В
	unsigned char rez                        :7; // резерв

	QVariantMap toMap() {
		QVariantMap data;
		data["vkl380"] = vkl380;
		return data;
	}

	void fromMap(QVariantMap data) {
		vkl380 = data["vkl380"].toUInt();
	}
}tPRD_1_COMMAND;

typedef struct PRD_2_COMMAND_type
{
	unsigned char vklPumi1                   :1; // Вкл ПУМИ I
	unsigned char vklPumi2                   :1; // Вкл ПУМИ II
	unsigned char vklHotRes                  :1; // ВКЛ ГОР РЕЗ
	unsigned char vklSvch1                   :1; // Вкл ВХ СВЧ I
	unsigned char vklSvch2                   :1; // Вкл ВХ СВЧ II
	unsigned char rez                        :3; // резерв

	QVariantMap toMap() {
		QVariantMap data;
		data["vklPumi1"] = vklPumi1;
		data["vklPumi2"] = vklPumi2;
		data["vklHotRes"] = vklHotRes;
		data["vklSvch1"] = vklPumi1;
		data["vklSvch2"] = vklPumi2;
		return data;
	}

	void fromMap(QVariantMap data) {
		vklPumi1 = data["vklPumi1"].toUInt();
		vklPumi2 = data["vklPumi2"].toUInt();
		vklHotRes = data["vklHotRes"].toUInt();
		vklSvch1 = data["vklSvch1"].toUInt();
		vklSvch2 = data["vklSvch2"].toUInt();
	}
}tPRD_2_COMMAND;

typedef struct PRD_3_COMMAND_type
{
	unsigned char vklUmi                     :1; // Вкл сеть УМИ
	unsigned char vklPower                   :1; // Вкл ИП
	unsigned char vklSVCh                    :1; // Вкл СВЧ
	unsigned char sbrosAvar                  :1; // СБРОС АВАР
	unsigned char readPhase                  :1; // чтение ФВ
	unsigned char writePhase                 :1; // запись ФВ
	unsigned char rez                        :2; // резерв

	QVariantMap toMap() {
		QVariantMap data;
		data["vklUmi"] = vklUmi;
		data["vklPower"] = vklPower;
		data["vklSVCh"] = vklSVCh;
		data["sbrosAvar"] = sbrosAvar;
		data["readPhase"] = readPhase;
		data["writePhase"] = writePhase;
		return data;
	}

	void fromMap(QVariantMap data) {
		vklUmi = data["vklUmi"].toUInt();
		vklPower = data["vklPower"].toUInt();
		vklSVCh = data["vklSVCh"].toUInt();
		sbrosAvar = 0;//data["sbrosAvar"].toUInt();
		readPhase = 0;//data["readPhase"].toUInt();
		writePhase = 0;//data["writePhase"].toUInt();
	}
}tPRD_3_COMMAND;

typedef struct PRD_4_COMMAND_type
{
	unsigned char module                     :8; // Номер модуля

	QVariantMap toMap() {
		QVariantMap data;
		data["module"] = module;
		return data;
	}

	void fromMap(QVariantMap data) {
		module = data["module"].toUInt();
	}
}tPRD_4_COMMAND;

typedef struct PRD_5_COMMAND_type
{
	unsigned char phase                      :6; // Значение фазы
	unsigned char rez                        :2; // резерв

	QVariantMap toMap() {
		QVariantMap data;
		data["phase"] = phase;
		return data;
	}

	void fromMap(QVariantMap data) {
		phase = data["phase"].toUInt();
	}
}tPRD_5_COMMAND;

typedef struct PRD_6_COMMAND_type
{
	unsigned char rez                        :8; // резерв

	QVariantMap toMap() {
		QVariantMap data;
		return data;
	}

	void fromMap(QVariantMap data) {
		Q_UNUSED(data);
	}
}tPRD_6_COMMAND;

typedef union tagPRD_1_COMMAND_union
{
	tPRD_1_COMMAND BitsN;
	unsigned char Byte;

	tagPRD_1_COMMAND_union() {
		Byte = 0;
	}
}PRD_1_COMMAND;

typedef union tagPRD_2_COMMAND_union
{
	tPRD_2_COMMAND BitsN;
	unsigned char Byte;

	tagPRD_2_COMMAND_union() {
		Byte = 0;
	}
}PRD_2_COMMAND;

typedef union tagPRD_3_COMMAND_MODULE
{
	tPRD_3_COMMAND BitsN;
	unsigned char Byte;

	tagPRD_3_COMMAND_MODULE() {
		Byte = 0;
	}
}PRD_3_COMMAND_MODULE;

typedef struct tagPRD_3_COMMAND
{
	PRD_3_COMMAND_MODULE module[CA_MAX_N_MODULES_UMI];

	QVariantList toList() {
		QVariantList list;
		for(qint32 n = 0; n < CA_MAX_N_MODULES_UMI; n++)
			list << module[n].BitsN.toMap();
		return list;
	}

	void fromList(QVariantList list) {
		for(qint32 n = 0; n < CA_MAX_N_MODULES_UMI && n < list.count(); n++)
			module[n].BitsN.fromMap(list[n].toMap());
	}
}PRD_3_COMMAND;

typedef union tagPRD_4_COMMAND_MODULE
{
	tPRD_4_COMMAND BitsN;
	unsigned char Byte;

	tagPRD_4_COMMAND_MODULE() {
		Byte = 0;
	}
}PRD_4_COMMAND_MODULE;

typedef struct tagPRD_4_COMMAND
{
	PRD_4_COMMAND_MODULE module[CA_MAX_N_MODULES_UMI];

	QVariantList toList() {
		QVariantList list;
		for(qint32 n = 0; n < CA_MAX_N_MODULES_UMI; n++)
			list << module[n].BitsN.toMap();
		return list;
	}

	void fromList(QVariantList list) {
		for(qint32 n = 0; n < CA_MAX_N_MODULES_UMI && n < list.count(); n++)
			module[n].BitsN.fromMap(list[n].toMap());
	}
}PRD_4_COMMAND;

typedef union tagPRD_5_COMMAND_MODULE
{
	tPRD_5_COMMAND BitsN;
	unsigned char Byte;

	tagPRD_5_COMMAND_MODULE() {
		Byte = 0;
	}
}PRD_5_COMMAND_MODULE;

typedef struct tagPRD_5_COMMAND
{
	PRD_5_COMMAND_MODULE module[CA_MAX_N_MODULES_UMI];

	QVariantList toList() {
		QVariantList list;
		for(qint32 n = 0; n < CA_MAX_N_MODULES_UMI; n++)
			list << module[n].BitsN.toMap();
		return list;
	}

	void fromList(QVariantList list) {
		for(qint32 n = 0; n < CA_MAX_N_MODULES_UMI && n < list.count(); n++)
			module[n].BitsN.fromMap(list[n].toMap());
	}
}PRD_5_COMMAND;

typedef union tagPRD_6_COMMAND_MODULE
{
	tPRD_6_COMMAND BitsN;
	unsigned char Byte;

	tagPRD_6_COMMAND_MODULE() {
		Byte = 0;
	}
}PRD_6_COMMAND_MODULE;

typedef struct tagPRD_6_COMMAND
{
	PRD_6_COMMAND_MODULE module[CA_MAX_N_MODULES_UMI];

	QVariantList toList() {
		QVariantList list;
		for(qint32 n = 0; n < CA_MAX_N_MODULES_UMI; n++)
			list << module[n].BitsN.toMap();
		return list;
	}

	void fromList(QVariantList list) {
		for(qint32 n = 0; n < CA_MAX_N_MODULES_UMI && n < list.count(); n++)
			module[n].BitsN.fromMap(list[n].toMap());
	}
}PRD_6_COMMAND;

typedef struct tagPRD_SINGLE_COMMAND
{
	PRD_1_COMMAND b1;
	PRD_2_COMMAND b2;
	PRD_3_COMMAND b3;
	PRD_4_COMMAND b4;
	PRD_5_COMMAND b5;
	PRD_6_COMMAND b6;

	tagPRD_SINGLE_COMMAND() {
	}

	tagPRD_SINGLE_COMMAND(QVariantMap data) {
		fromMap(data);
	}

	QVariantMap toMap() {
		QVariantMap data;
		data.unite(b1.BitsN.toMap());
		data.unite(b2.BitsN.toMap());
		data["modules"] = b3.toList();
		data["numbers"] = b4.toList();
		data["phases"] = b5.toList();
//		data["unused"] = b6.toList();
		return data;
	}

	void fromMap(QVariantMap data) {
		b1.BitsN.fromMap(data);
		b2.BitsN.fromMap(data);
		b3.fromList(data["modules"].toList());
		b4.fromList(data["numbers"].toList());
		b5.fromList(data["phases"].toList());
//		b6.fromList(data["unused"].toList());
	}
}PRD_SINGLE_COMMAND;

typedef struct tagPRD_COMMAND
{
	PRD_SINGLE_COMMAND prd[CA_N_TRANSMITTERS];

	tagPRD_COMMAND() {
	}

	tagPRD_COMMAND(QVariantList list) {
		fromList(list);
	}

	QVariantList toList() {
		QVariantList list;
		for(quint32 n = 0; n < CA_N_TRANSMITTERS; n++)
			list << prd[n].toMap();
		return list;
	}

	void fromList(QVariantList list) {
		for(qint32 n = 0; (n < CA_N_TRANSMITTERS) && (n < list.count()); n++)
			prd[n].fromMap(list[n].toMap());
	}
}PRD_COMMAND;

//-----------------------------------------------------------------------------

typedef struct tagCanalAskuConfig
{
	bool main;
	bool monitor;
	bool first;
	bool update;

	tagCanalAskuConfig() {
		main = false;
		monitor = false;
		first = false;
		update = false;
	}

	tagCanalAskuConfig(const QVariantMap & data) {
		fromMap(data);
	}

	QVariantMap toMap() {
		QVariantMap map;
		map["main"] = main;
		map["monitor"] = monitor;
		map["first"] = first;
		map["update"] = update;
		return map;
	}

	void fromMap(const QVariantMap & map) {
		main = map["main"].toBool();
		monitor = map["monitor"].toBool();
		first = map["first"].toBool();
		update = map["update"].toBool();
	}

}CanalAskuConfig;

//-----------------------------------------------------------------------------

#endif //_CANALASKU_STRUCT_H_
