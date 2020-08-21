#ifndef _VRL_STRUCT_H_INCLUDED_
#define _VRL_STRUCT_H_INCLUDED_

#define N_VRLS 2
#define N_VRL_VUM 8

#pragma pack(push, 1)

typedef struct _tag_complect_bits
{
	unsigned char number:2;
	unsigned char disabled:1;
	unsigned char reserved:1;
	unsigned char proto:4;
}COMPLECT_VRL_BITS;

typedef union _tag_complect_union
{
	COMPLECT_VRL_BITS bits;
	unsigned char byte;
}COMPLECT_VRL;

typedef struct _tag_status_bits
{
	unsigned char code:2;
	unsigned char mest1:1;
	unsigned char mest2:1;
	unsigned char state1:2;
	unsigned char state2:2;
}STATUS_VRL_BITS;

typedef union _tag_status_union
{
	STATUS_VRL_BITS bits;
	unsigned char byte;
}STATUS_VRL;

typedef struct _tag_status_ao_bits
{
	unsigned char zao_connected:1;
	unsigned char zao_ikd:1;
	unsigned char zao_ikp:1;
	unsigned char avar_d2en258_1:1;
	unsigned char avar_d2en258_2:1;
	unsigned char avar_d2en279_1:1;
	unsigned char avar_d2en279_2:1;
	unsigned char avar_d2en277m_1:1;

	unsigned char avar_d2en277m_2:1;
	unsigned char avar_vent_1:1;
	unsigned char avar_vent_2:1;
	unsigned char qf_vum1357:1;
	unsigned char qf_27v_1:1;
	unsigned char qf_krt_1:1;
	unsigned char qf_vum2468:1;
	unsigned char qf_27v_2:1;

	unsigned char qf_krt_2:1;
	unsigned char qf_380v_1:1;
	unsigned char qf_380v_2:1;
	unsigned char reserved1:5;

	unsigned short reserved2:8;
}STATUS_AO_BITS;

typedef union _tag_status_ao_union
{
	STATUS_AO_BITS bits;
	unsigned char byte[4];
}STATUS_AO;

typedef struct _tag_status_prm_bits
{
	unsigned short sum_avar_sharu:1;
	unsigned short dif_avar_sharu:1;
	unsigned short sup_avar_sharu:1;
	unsigned short sum_avar_atten:1;
	unsigned short dif_avar_atten:1;
	unsigned short sup_avar_atten:1;
	unsigned short sum_sharu_code:5;
	unsigned short dif_sharu_code:5;
	unsigned short sup_sharu_code:5;
	unsigned short reserved3:3;

	unsigned short reserved_xx:8;

	unsigned short sum_int_noise:16;
	unsigned short dif_int_noise:16;
	unsigned short sup_int_noise:16;

	unsigned short sum_amp_rbs:16;
	unsigned short dif_amp_rbs:16;
	unsigned short sup_amp_rbs:16;

	unsigned short sum_amp_nrz_f2:16;
	unsigned short dif_amp_nrz_f2:16;
	unsigned short sup_amp_nrz_f2:16;

	unsigned short sum_amp_nrz_f3:16;
	unsigned short dif_amp_nrz_f3:16;
	unsigned short sup_amp_nrz_f3:16;
}STATUS_PRM_BITS;

typedef union _tag_status_prm_union
{
	STATUS_PRM_BITS bits;
	unsigned char byte[28];
}STATUS_PRM;

typedef struct _tag_status_azn_bits
{
	unsigned short p1_avar_sharu:1;
	unsigned short p2_avar_sharu:1;
	unsigned short p3_avar_sharu:1;
	unsigned short p4_avar_sharu:1;
	unsigned short p1_avar_atten:1;
	unsigned short p2_avar_atten:1;
	unsigned short p3_avar_atten:1;
	unsigned short p4_avar_atten:1;

	unsigned short avar_prm_link:1;
	unsigned short avar_prm:1;
	unsigned short reserved1:1;
	unsigned short p1_sharu_code:5;

	unsigned short p2_sharu_code:5;
	unsigned short p3_sharu_code:5;
	unsigned short p4_sharu_code:5;
	unsigned short reserved2:1;

	unsigned short p1_int_noise;
	unsigned short p2_int_noise;
	unsigned short p3_int_noise;
	unsigned short p4_int_noise;

	unsigned short p1_amp;
	unsigned short p2_amp;
	unsigned short p3_amp;
	unsigned short p4_amp;
}STATUS_AZN_BITS;

typedef union _tag_status_azn_union
{
	STATUS_AZN_BITS bits;
	unsigned char byte[20];
}STATUS_AZN;

typedef struct _tag_status_umi_1b_bits
{
	unsigned char f_t:1;
	unsigned char f_pout:1;
	unsigned char f_avar:1;
	unsigned char f_pin:1;
	unsigned char f_potr:1;
	unsigned char f_u:1;
	unsigned char rez:2;
}STATUS_UMI_1B_BITS;

typedef union _tag_status_umi_1_union
{
	STATUS_UMI_1B_BITS bits;
	unsigned char byte;
}STATUS_UMI_1B;

typedef struct _tag_status_umi12_struct
{
	STATUS_UMI_1B flags;
	signed char t;
	unsigned char u;
	unsigned char pin;
	unsigned char pout;
	unsigned char potr;
}STATUS_UMI_12;

typedef struct _tag_status_umi_struct
{
	STATUS_UMI_12 umi_o;
	STATUS_UMI_12 umi_p;
}STATUS_UMI;

typedef struct _tag_message_209
{
	unsigned char code;
	unsigned char length;
	COMPLECT_VRL comp;
	STATUS_VRL status;
	STATUS_AO ao;
	STATUS_PRM prm;
	STATUS_AZN azn;
	STATUS_UMI umi[N_VRL_VUM];
}MESSAGE_209;

typedef struct _tag_message_208_bits
{
	unsigned char status:2;
	unsigned char no_reconf:1;
	unsigned char unused:5;
}MESSAGE_208_BITS;

typedef struct _tag_message_208
{
	unsigned char code;
	unsigned char length;
	MESSAGE_208_BITS bits;
}MESSAGE_208;

#pragma pack(pop)

#define VRL_TYPE_MVRL_KN 1

typedef struct tagVrlConfig
{
	unsigned int type;
	bool main;
	bool monitor;
	unsigned int mainVRL;
	bool reconfVRL;
	bool disable;

	tagVrlConfig()
	{
		type = VRL_TYPE_MVRL_KN;
		main = false;
		monitor = false;
		mainVRL = 0;
		reconfVRL = false;
		disable = false;
	}

	tagVrlConfig(const QVariantMap & data)
	{
		fromMap(data);
	}

	QVariantMap toMap() {
		QVariantMap map;
		map["main"] = main;
		map["type"] = type;
		map["monitor"] = monitor;
		map["mainVRL"] = mainVRL;
		map["reconfVRL"] = reconfVRL;
		map["disable"] = disable;
		return map;
	}
	void fromMap(const QVariantMap & map) {
		main = map["main"].toBool();
		type = map["type"].toBool();
		monitor = map["monitor"].toBool();
		mainVRL = map["mainVRL"].toUInt();
		reconfVRL = map["reconfVRL"].toBool();
		disable = map["disable"].toBool();
	}

}VrlConfig;

#endif //_VRL_STRUCT_H_INCLUDED_
