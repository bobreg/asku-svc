#ifndef _VOI_STRUCT_H_INCLUDED_
#define _VOI_STRUCT_H_INCLUDED_

#define TS_APP_CLOSE    64		// Закрытие приложения
#define TS_INIT_VOI     65		// Продолжить инициализацию приложения
#define TS_MOVE_WND     66		// Установить координаты окна
#define TS_MAIN_DLG     67		// Открыть главный диалог
#define TS_ON_MAIN      68		// Перейти в основной режим работы
#define TS_RLS_STATE    69		// Состояние РЛС
#define TS_HELLO        71		// Готовность к работе
#define TS_OTWET        72		// Ответ на готовность к работе
#define TS_SKR_VOI      73		// СКР
#define TS_RMO          74		// Обмен данных с РМО
#define TS_RMO_DT       75		// Обмен данных с DT
#define TS_NORM         76		// Обмен данных с ВОИ (регулярная кодограмма о состоянии АСКУ)
#define TS_GPS_RECEIVE  77		// Прием данных с Д2ВБ011
#define TS_GPS_SEND     78		// Посылка данных на Д2ВБ011
#define TS_GPS_CHANNEL  79		// Выбор основного канала на Д2ВБ011
#define TS_RLS_STATE_FULL 80	// Состояние РЛС
#define TS_VOI_ERROR_WITH_GPS 84	// Состояние ВОИ
#define TS_P_CODE       85		// Code P
#define TS_DIS_COORD    86		// Disable Table Coordinates
#define TS_DIS_MAP      89		// Disable Map Coordinates
#define MASK_TS       0x00FF	// Маска поля ТС

typedef struct _TC_VOI_64
{
    unsigned char tc;
    unsigned char reserved;
}TC_VOI_64;

typedef struct _TC_VOI_71
{
    unsigned char tc;
    unsigned char reserved;
}TC_VOI_71;

typedef struct _TC_VOI_72
{
    unsigned char tc;
    unsigned char reserved;
}TC_VOI_72;

typedef struct _TC_VOI_76
{
    unsigned char tc;
    unsigned char reserved;
}TC_VOI_76;

typedef struct _TC_VOI_66
{
    unsigned char tc;
    unsigned char reserved;
    unsigned short X;
    unsigned short Y;
    unsigned short W;
    unsigned short H;
}TC_VOI_66;

typedef struct _TC_VOI_68
{
    unsigned char tc;
    unsigned char rez:1;
    unsigned char op:1;
    unsigned char zr:1;
    unsigned char reserved:5;
}TC_VOI_68;

typedef struct _TC_VOI_73
{
    unsigned char tc;
    unsigned char on:1;
    unsigned char reserved:7;
    unsigned short azimuth;
}TC_VOI_73;

typedef struct _TC_VOI_74
{
    unsigned char tc;
    unsigned char reserved;
    unsigned short length;
    unsigned short data[];
}TC_VOI_74_75;

typedef struct _TC_VOI_77
{
    unsigned char tc;
    unsigned char buffer;
    unsigned short length;
    unsigned short data[];
}TC_VOI_77;

typedef struct _TC_VOI_78
{
    unsigned char tc;
    unsigned char buffer:7;
    unsigned char en:1;
    unsigned short length;
    unsigned short data[];
}TC_VOI_78;

typedef struct _TC_VOI_79
{
    unsigned char tc;
    unsigned char nchannel;
}TC_VOI_79;

typedef struct _tag_KIU_BITS
{
    unsigned char unused:1;
    unsigned char upr2:1;
    unsigned char upr1:1;
    unsigned char select:2;
    unsigned char state:2;
    unsigned char reserve:1;
}KIU_BITS;

typedef union _tag_KIU
{
    KIU_BITS bits;
    unsigned char sbyte;
}KIU;

typedef struct _tag_PCS_BITS
{
    unsigned short unused:5;
    unsigned short no_ask:1;
    unsigned short no_gpr2:1;
    unsigned short no_gpr1:1;
    unsigned short unused2:8;
}PCS_BITS;

typedef union _tag_PCS
{
    PCS_BITS bits;
    unsigned short sword;
}PCS;

typedef struct _TC_VOI_80
{
    unsigned char tc;
    KIU gpr;
    KIU poi;
    KIU vrl;
    PCS code;
}TC_VOI_80;

/*typedef struct _TC_VOI_82
{
    unsigned char tc;
    unsigned char length;
    unsigned short p:10;
    unsigned short reserved1:6;
    unsigned short t1:10;
    unsigned short reserved2:6;
    unsigned short t2:10;
    unsigned short reserved3:6;
    unsigned short t3:10;
    unsigned short reserved4:6;
}TC_VOI_82;*/

typedef struct _TC_VOI_83
{
    unsigned char tc;
    unsigned char length;
    unsigned char gpr:1;
    unsigned char poi:1;
    unsigned char vrl:1;
    unsigned char nrz:1;
    unsigned char reserved1:4;
    unsigned char sost_rls;
    unsigned char sost_gpr;
    unsigned char sost_poi;
    unsigned char sost_vrl;
    unsigned char sost_nrz;
}TC_VOI_83;

typedef struct _TC_VOI_84
{
    unsigned char tc;
    unsigned char length;
    unsigned char is_voi:1;
    unsigned char is_019:1;
    unsigned char is_011:1;
    unsigned char is_kpts:1;
    unsigned char is_vip:1;
    unsigned char is_nrz:1;
    unsigned char is_arp:1;
    unsigned char is_azn:1;
    unsigned char osn:1;
    unsigned char is_disable:1;
    unsigned char is_mpsn:1;
    unsigned char reserved2:5;
    union
    {
        unsigned short word;
        struct
        {
            unsigned short azsens_error:1;
            unsigned short no_azn:1;
            unsigned short async_vrl:1;
            unsigned short time_azn_error:1;
            unsigned short no_mai:1;
            unsigned short network_error:1;
            unsigned short no_vrl_reserve:1;
            unsigned short no_nord:1;
            unsigned short no_mpsn:1;
            unsigned short no_prl:1;
            unsigned short no_vrl:1;
            unsigned short no_nrz:1;
            unsigned short com_error:1;
            unsigned short no_kpts:1;
            unsigned short no_vip:1;
            unsigned short not_complete:1;
        }bits;
    }svoi;
    union
    {
        unsigned short word;
        struct
        {
            unsigned short no_driver:1;
            unsigned short device_fault:1;
            unsigned short line_fault_1:1;
            unsigned short line_fault_2:1;
            unsigned short modem_fault_1:1;
            unsigned short modem_fault_2:1;
            unsigned short device_rw_error:1;
            unsigned short reserved1:2;
            unsigned short line_off_1:1;
            unsigned short line_off_2:1;
            unsigned short reserved2:5;
        }bits;
    }s019;
    union
    {
        unsigned short word;
        struct
        {
            unsigned short no_driver:1;
            unsigned short device_fault:1;
            unsigned short channel_number:1;
            unsigned short invalid_time:1;
            unsigned short reserved:12;
        }bits;
    }s011;
    union
    {
        unsigned short word;
        struct
        {
            unsigned short ch1:1;
            unsigned short ch2:1;
            unsigned short ch3:1;
            unsigned short ch4:1;
            unsigned short ch5:1;
            unsigned short ch6:1;
            unsigned short ch7:1;
            unsigned short ch8:1;
            unsigned short ch9:1;
            unsigned short ch10:1;
            unsigned short ch11:1;
            unsigned short ch12:1;
			unsigned short reserved:2;
            unsigned short avar:1;
            unsigned short no_data:1;
        }bits;
    }sarp;
}TC_VOI_84;

typedef struct _TC_VOI_85
{
    unsigned char tc;
    unsigned char length;
    unsigned short pressure:15;
    unsigned short avar:1;
}TC_VOI_85;

typedef struct _TC_VOI_86
{
    unsigned char tc;
    unsigned char count;
	struct
	{
		unsigned short begin;
		unsigned short end;
	}sektor[];
}TC_VOI_86;

typedef struct _TC_VOI_89
{
    unsigned char tc;
    unsigned char count;
	struct
	{
		unsigned short begin;
		unsigned short end;
	}sektor[];
}TC_VOI_89;


typedef struct tagVoiConfig
{
	bool main;

	tagVoiConfig()
	{
		main = false;
	}

	tagVoiConfig(QVariantMap data)
	{
		fromMap(data);
	}

	QVariantMap toMap() {
		QVariantMap map;

		map["main"] = main;

		return map;
	}
	void fromMap(QVariantMap map) {
		main = map["main"].toBool();
	}
}VoiConfig;


#endif //_VOI_STRUCT_H_INCLUDED_
