#ifndef __DASD_REGISTERS_H__
#define __DASD_REGISTERS_H__

//-----------------------------------------------------------------------------
#include <QObject>

//-----------------------------------------------------------------------------
#define ADRESS_BASE 0x0000

#define ADRESS_VERSION 0x0000
typedef struct _TAG_REG_VERSION
{
	union
	{
		struct
		{
			unsigned int version:8;
			unsigned int day:8;
			unsigned int month:8;
			unsigned int year:8;
		}bits;
		unsigned int dword;
	};
}REG_VERSION;

#define ADRESS_CONTROL 0x0004
typedef struct _TAG_REG_CONTROL
{
	union
	{
		struct
		{
			unsigned int main:1;
			unsigned int block_avto:1;
			unsigned int regime:2;
			unsigned int is_observer:1;
			unsigned int reserved2:27;
		}bits;
		unsigned int dword;
	};
	QString main();
	QString value();
}REG_CONTROL;

#define ADRESS_STATE 0x0008
typedef struct _TAG_REG_STATE
{
	union
	{
		struct
		{
			unsigned int main:1;
			unsigned int pch_on:1;
			unsigned int azim_source:2;
			unsigned int avar_switch_s:1;
			unsigned int avar_switch_d:1;
			unsigned int ind_switch_s:1;
			unsigned int ind_switch_d:1;
			unsigned int n_observe:2;
			unsigned int reserved1:6;
			unsigned int avar_sync:1;
			unsigned int reserved2:15;
		}bits;
		unsigned int dword;
	};
}REG_STATE;

#define ADRESS_SYNCR 0x000C
typedef struct _TAG_REG_SYNCR
{
	union
	{
		struct
		{
			unsigned int output:8;
			unsigned int reserved:24;
		}bits;
		unsigned int dword;
	};
}REG_SYNCR;

#define ADRESS_AZIMUTH_CONTROL 0x0010
typedef struct _TAG_REG_AZIMUTH_CONTROL
{
	union
	{
		struct
		{
			unsigned int source:2;
			unsigned int reserved1:2;
			unsigned int im_period:3;
			unsigned int reserved2:1;
			unsigned int load_lir_1:1;
			unsigned int load_lir_2:1;
			unsigned int load_serial:1;
			unsigned int reserved3:21;
		}bits;
		unsigned int dword;
	};
}REG_AZIMUTH_CONTROL;

#define ADRESS_LIR1_SENSOR 0x0014
#define ADRESS_LIR2_SENSOR 0x0018
typedef struct _TAG_REG_LIR_SENSOR
{
	union
	{
		struct
		{
			unsigned int azimuth:14;
			unsigned int unused1:2;
			unsigned int imitator:1;
			unsigned int active_comp:1;
			unsigned int active_sensor:1;
			unsigned int unused2:11;
			unsigned int parity_error:1;
			unsigned int line_detect_error:1;
		}bits;
		unsigned int dword;
	};
}REG_LIR_SENSOR;

#define ADRESS_SERIAL_SENSOR 0x001C
typedef struct _TAG_REG_SERIAL_SENSOR
{
	union
	{
		struct
		{
			unsigned int azimuth:14;
			unsigned int unused1:2;
			unsigned int imitator:1;
			unsigned int active_comp:1;
			unsigned int active_sensor:1;
			unsigned int unused2:11;
			unsigned int parity_error:1;
			unsigned int line_detect_error:1;
		}bits;
		unsigned int dword;
	};
}REG_SERIAL_SENSOR;

#define ADRESS_AZIMUTH 0x0020
typedef struct _TAG_REG_AZIMUTH
{
	union
	{
		struct
		{
			unsigned int azimuth:14;
			unsigned int unused1:2;
			unsigned int sektor:8;
			unsigned int unused2:8;
		}bits;
		unsigned int dword;
	};
}REG_AZIMUTH;

#define ADRESS_OFFSET 0x0024
typedef struct _TAG_REG_OFFSET
{
	union
	{
		struct
		{
			unsigned int azimuth1:14;
			unsigned int reserved1:2;
			unsigned int azimuth2:14;
			unsigned int reserved2:1;
			unsigned int ready:1;
		}bits;
		unsigned int dword;
	};
}REG_OFFSET;

#define ADRESS_MAI_PER 0x0028
typedef struct _TAG_REG_MAI_PER
{
	union
	{
		struct
		{
			unsigned int time_mai:16;
			unsigned int time_nord:16;
		}bits;
		unsigned int dword;
	};
}REG_MAI_PER;

#define ADRESS_SENSOR_OFFSET 0x002C
typedef struct _TAG_REG_SENSOR_OFFSET
{
	union
	{
		struct
		{
			unsigned int azimuth1:14;
			unsigned int reserved1:2;
			unsigned int azimuth2:14;
			unsigned int reserved2:2;
		}bits;
		unsigned int dword;
	};
}REG_SENSOR_OFFSET;

#define ADRESS_SKR 0x0030
typedef struct _TAG_REG_SKR
{
	union
	{
		struct
		{
			unsigned int azimuth_on:14;
			unsigned int reserved1:2;
			unsigned int azimuth_off:14;
			unsigned int always_on:1;
			unsigned int set_on:1;
		}bits;
		unsigned int dword;
	};
}REG_SKR;

#define ADRESS_GSH 0x0034
typedef struct _TAG_REG_GSH
{
	union
	{
		struct
		{
			unsigned int azimuth_on:14;
			unsigned int reserved1:2;
			unsigned int azimuth_off:14;
			unsigned int always_on:1;
			unsigned int set_on:1;
		}bits;
		unsigned int dword;
	};
}REG_GSH;

#define ADRESS_PILOT 0x0038
typedef struct _TAG_REG_PILOT
{
	union
	{
		struct
		{
			unsigned int azimuth_on:14;
			unsigned int reserved1:2;
			unsigned int azimuth_off:14;
			unsigned int always_on:1;
			unsigned int set_on:1;
		}bits;
		unsigned int dword;
	};
}REG_PILOT;

#define ADRESS_ZU 0x003C
typedef struct _TAG_REG_ZU
{
	union
	{
		struct
		{
			unsigned int azimuth_on:14;
			unsigned int reserved1:2;
			unsigned int azimuth_off:14;
			unsigned int always_on:1;
			unsigned int set_on:1;
		}bits;
		unsigned int dword;
	};
}REG_ZU;

#define ADRESS_TIMER_CONTROL 0x0040
typedef struct _TAG_REG_TIMER_CONTROL
{
	union
	{
		struct
		{
			unsigned int source:2;
			unsigned int reserved1:6;
			unsigned int speed_int:4;
			unsigned int reserved2:4;
			unsigned int speed_a:4;
			unsigned int reserved3:4;
			unsigned int speed_b:4;
			unsigned int reserved4:4;
		}bits;
		unsigned int dword;
	};
}REG_TIMER_CONTROL;

#define ADRESS_TIME 0x0044
typedef struct _TAG_REG_TIME
{
	union
	{
		struct
		{
			unsigned int second:8;
			unsigned int minute:8;
			unsigned int hour:8;
			unsigned int sure_msv_int:1;
			unsigned int sure_msv_a:1;
			unsigned int sure_msv_b:1;
			unsigned int sure_kd_int:1;
			unsigned int sure_kd_a:1;
			unsigned int sure_kd_b:1;
			unsigned int sure_kd_main:1;
			unsigned int sure_main:1;
		}bits;
		unsigned int dword;
	};
}REG_TIME;

#define ADRESS_SUBSECOND  0x0048
typedef struct _TAG_REG_SUBSECOND
{
	unsigned int value;
}REG_SUBSECOND;

#define ADRESS_DATE  0x004C
typedef struct _TAG_REG_DATE
{
	union
	{
		struct
		{
			unsigned int day:8;
			unsigned int month:8;
			unsigned int year:8;//2000+n
			unsigned int reserved:8;
		}bits;
		unsigned int dword;
	};
}REG_DATE;

#define ADRESS_TIMER  0x0050
typedef struct _TAG_REG_TIMER
{
	union
	{
		struct
		{
			unsigned int subsecond:30;
			unsigned int reserved:1;
			unsigned int no_pps:1;
		}bits;
		unsigned int dword;
	};
}REG_TIMER;

#define ADRESS_TIMER_STATE 0x0054
typedef struct _TAG_REG_TIMER_STATE
{
	union
	{
		struct
		{
			unsigned int antenna_ok:1;
			unsigned int load_on:1;
			unsigned int reserved:30;
		}bits;
		unsigned int dword;
	};
}REG_TIMER_STATE;

#define ADRESS_RX0_STATE 0x0060
#define ADRESS_RX1_STATE 0x0064
typedef struct _TAG_REG_RX_STATE
{
	union
	{
		struct
		{
			unsigned int r_adress:10;
			unsigned int l_adress:10;
			unsigned int count:10;
			unsigned int empty:1;
			unsigned int overflow:1;
		}bits;
		struct
		{
			unsigned int reset:1;
			unsigned int reserved:31;
		}bits_w;
		unsigned int dword;
	};
}REG_RX_STATE;

#define ADRESS_TX0_CONTROL 0x0068
typedef struct _TAG_REG_TX_CONTROL
{
	union
	{
		struct
		{
			unsigned int adress:10;
			unsigned int reserved1:6;
			unsigned int count:10;
			unsigned int reserved2:4;
			unsigned int en:1;
			unsigned int start:1;
		}bits;
		unsigned int dword;
	};
}REG_TX_CONTROL;

#define ADRESS_COMMON_RF_FORMER 0x0070
typedef struct _TAG_REG_COMMON_RF_FORMER
{
	union
	{
		struct
		{
			unsigned int allow_pch:1;
			unsigned int block_zu:1;
			unsigned int block_switch:1;
			unsigned int block_yy11:1;
			unsigned int no_write_varu:1;
			unsigned int test_sin:1;
			unsigned int reserved1:1;
			unsigned int strobe_enable:1;
			unsigned int error_crc:1;	//dsp
			unsigned int error_parity:1;	//dsp
			unsigned int error_stop:1;	//dsp
			unsigned int error_compare:1;	//dsp
			unsigned int avar_block_gf:1;
			unsigned int is_ref_freq:1;
			unsigned int allow_yy:1;
			unsigned int error_timeout:1;	//dsp
			unsigned int impulse:8;
			unsigned int main_yy_1:1;
			unsigned int main_yy_2:1;
			unsigned int reserved2:2;
			unsigned int err_ctrl_zu_s:1;	//err_ctrl_prd_1:1;
			unsigned int err_ctrl_zu_d:1;	//err_ctrl_prd_2:1;
			unsigned int ant_key_rf_enable:1;	//ant switch common state
			unsigned int rf_enable_indicator:1;	//global rf enable
		}bits;
		unsigned int dword;
	};
}REG_COMMON_RF_FORMER;

#define ADRESS_ERR_ZU 0x0074
typedef struct _TAG_REG_ERR_ZU
{
	union
	{
		struct
		{
			unsigned int reset_s:1;
			unsigned int reserved1:15;
			unsigned int reset_d:1;
			unsigned int reserved2:15;
		}bits_w;
		struct
		{
			unsigned int avar_s:8;
			unsigned int reserved1:7;
			unsigned int link_s:1;
			unsigned int avar_d:8;
			unsigned int reserved2:7;
			unsigned int link_d:1;
		}bits;
		struct
		{
			unsigned int avar_s_kz1:1;
			unsigned int avar_s_kz2:1;
			unsigned int avar_s_hh1:1;
			unsigned int avar_s_hh2:1;
			unsigned int avar_s_a80v:1;
			unsigned int avar_s_a5v:1;
			unsigned int avar_s6:1;
			unsigned int avar_s7:1;
			unsigned int reserved1:7;
			unsigned int link_s:1;
			unsigned int avar_d_kz1:1;
			unsigned int avar_d_kz2:1;
			unsigned int avar_d_hh1:1;
			unsigned int avar_d_hh2:1;
			unsigned int avar_d_a80v:1;
			unsigned int avar_d_a5v:1;
			unsigned int avar_d6:1;
			unsigned int avar_d7:1;
			unsigned int reserved2:7;
			unsigned int link_d:1;
		}bits1;
		unsigned int dword;
	};
}REG_ERR_ZU;

#define ADRESS_SHARU_CONTROL 0x0078
typedef struct _TAG_REG_SHARU_CONTROL
{
	union
	{
		struct
		{
			unsigned int code_s:5;
			unsigned int reserved1:3;
			unsigned int code_d:5;
			unsigned int reserved2:3;
			unsigned int source:2;
			unsigned int reserved3:14;
		}bits;
		unsigned int dword;
	};
}REG_SHARU_CONTROL;

#define ADRESS_EVENT_MASK  0x0080
typedef struct _TAG_REG_EVENT_MASK
{
	union
	{
		struct
		{
			unsigned int pps:1;
			unsigned int mai256:1;
			unsigned int nord:1;
			unsigned int reserved1:4;
			unsigned int common_mai_time:1;
			unsigned int reserved2:23;
			unsigned int enable_interrupt:1;
		}bits;
		unsigned int dword;
	};
}REG_EVENT_MASK;

#define ADRESS_EVENT_FLAG  0x0084
typedef struct _TAG_REG_EVENT_FLAG
{
	union
	{
		struct
		{
			unsigned int pps:1;
			unsigned int mai256:1;
			unsigned int nord:1;
			unsigned int reserved1:5;
			unsigned int reserved2:24;
		}bits;
		unsigned int dword;
	};
}REG_EVENT_FLAG;

#define ADRESS_STEP_DOPLER 0x0090
typedef struct _TAG_REG_STEP_DOPLER
{
	union
	{
		struct
		{
			unsigned int step:32;
		}bits;
		unsigned int dword;
	};
}REG_STEP_DOPLER;

#define ADRESS_AMP_DELAY_PILOT 0x0094
typedef struct _TAG_REG_AMP_DELAY_PILOT
{
	union
	{
		struct
		{
			unsigned int delay:16;
			unsigned int amplitude:16;
		}bits;
		unsigned int dword;
	};
}REG_AMP_DELAY_PILOT;

#define ADRESS_DAC_CONTROL 0x0100
typedef struct _TAG_REG_DAC_CONTROL
{
	union
	{
		struct
		{
			unsigned int reserved:31;
			unsigned int write:1;
		}bits;
		unsigned int dword;
	};
}REG_DAC_CONTROL;

#define ADRESS_RFS_CONTROL 0x0104
typedef struct _TAG_REG_RFS_CONTROL
{
	union
	{
		struct
		{
			unsigned int fref_fout:1;
			unsigned int fref_fin:1;
			unsigned int fref_80:1;
			unsigned int reserved1:1;
			unsigned int pch_60_frf1:1;
			unsigned int pch_300_frf2:1;
			unsigned int reserved2:2;
			unsigned int div_400_SO:1;
			unsigned int div_400_N0:1;
			unsigned int div_400_N1:1;
			unsigned int div_400_N2:1;
			unsigned int div_400_DIV1:1;
			unsigned int div_400_BYP:1;
			unsigned int reserved3:2;
			unsigned int div_80_SO:1;
			unsigned int div_80_N0:1;
			unsigned int div_80_N1:1;
			unsigned int div_80_N2:1;
			unsigned int div_80_DIV1:1;
			unsigned int div_80_BYP:1;
			unsigned int reserved4:2;
			unsigned int reserved5:8;
		}bits;
		unsigned int dword;
	};
}REG_RFS_CONTROL;

#define ADRESS_FREQ_DEVIATION 0x0114
typedef struct _TAG_REG_FREQ_DEVIATION
{
	unsigned int dword;
}REG_FREQ_DEVIATION;

#define ADRESS_LATITUDE_LOW   0x0120
#define ADRESS_LATITUDE_HIGH  0x0124
#define ADRESS_LONGITUDE_LOW  0x0128
#define ADRESS_LONGITUDE_HIGH 0x012C
#define ADRESS_ALTITUDE_LOW   0x0130
#define ADRESS_ALTITUDE_HIGH  0x0134
typedef struct _TAG_REG_COORD
{
	double value;
}REG_COORD;

#define ADRESS_SERIAL_CONTROL 0x0204
typedef struct _TAG_REG_SERIAL_CONTROL
{
	union
	{
		struct
		{
			unsigned int mai:16;
			unsigned int reserved:15;
			unsigned int alarm:1;
		}bits;
		unsigned int dword;
	};
}REG_SERIAL_CONTROL;

#define ADRESS_GNSS_CONTROL 0x0220
typedef struct _TAG_REG_GNSS_CONTROL
{
	union
	{
		struct
		{
			unsigned int reserved1:24;
			unsigned int sleep:1;
			unsigned int reserved2:7;
		}bits;
		struct
		{
			unsigned int reserved1:25;
			unsigned int reset:1;
			unsigned int reserved2:6;
		}bits_w;
		unsigned int dword;
	};
}REG_GNSS_CONTROL;

#define ADRESS_TXEN_DELAY 0x0230
typedef struct _TAG_REG_TXEN_DELAY
{
	union
	{
		struct
		{
			unsigned int leading_edge:16;
			unsigned int trailing_edge:16;
		}bits;
		unsigned int dword;
	};
}REG_TXEN_DELAY;

typedef struct _TAG_REG_UNUSED
{
	unsigned int unused;
}REG_UNUSED;

//-----------------------------------------------------------------------------

#define ADRESS_TX0_DATA 0x0400
#define ADRESS_RX0_DATA 0x0800
#define ADRESS_RX1_DATA 0x0C00

#define TX_DATA_SIZE_BYTE 1024
#define RX_DATA_SIZE_BYTE 1024

#define DASD_TIME_MAX_VALUE 50

//-----------------------------------------------------------------------------

//*** DEVICE REGS ***/
typedef struct _TAG_DEVICE_REGS_PACK_1
{
	REG_VERSION version;				//0x0000
	REG_CONTROL control;				//0x0004
	REG_STATE state;					//0x0008
	REG_SYNCR syncr;					//0x000C
	REG_AZIMUTH_CONTROL az_control;		//0x0010
	REG_LIR_SENSOR lir1_sensor;			//0x0014
	REG_LIR_SENSOR lir2_sensor;			//0x0018
	REG_SERIAL_SENSOR serial_sensor;	//0x001C
	REG_AZIMUTH azimuth;				//0x0020
	REG_OFFSET offset;					//0x0024
	REG_MAI_PER mai_period;				//0x0028
	REG_SENSOR_OFFSET sensor_offset;	//0x002C
	REG_SKR skr;						//0x0030
	REG_GSH gsh;						//0x0034
	REG_PILOT pilot;					//0x0038
	REG_ZU zu;							//0x003C
	REG_TIMER_CONTROL timer_control;	//0x0040
	REG_TIME time;						//0x0044
	REG_SUBSECOND  subsecond;			//0x0048
	REG_DATE date;						//0x004C
	REG_TIMER timer;					//0x0050
	REG_TIMER_STATE	timer_state;		//0x0054
	REG_UNUSED unused58;				//
	REG_UNUSED unused5C;				//
	REG_RX_STATE rx0_state;				//0x0060
	REG_RX_STATE rx1_state;				//0x0064
	REG_TX_CONTROL tx0_control;			//0x0068
	REG_UNUSED unused6C;				//
	REG_COMMON_RF_FORMER rf_former;		//0x0070
	REG_ERR_ZU err_zu;					//0x0074
	REG_SHARU_CONTROL sharu_control;	//0x0078
	REG_UNUSED unused7C;				//
	REG_EVENT_MASK event_mask;			//0x0080
	REG_EVENT_FLAG event_flag;			//0x0084
	REG_UNUSED unused88;				//
	REG_UNUSED unused8C;				//
	REG_STEP_DOPLER step_dopler;		//0x0090
	REG_AMP_DELAY_PILOT amp_delay;		//0x0094
	REG_UNUSED unused98;				//
	REG_UNUSED unused9C;				//
}DEVICE_REGS_PACK_1;

typedef struct _TAG_DEVICE_REGS_PACK_2
{
	REG_DAC_CONTROL dac_control;		//0x0100
	REG_RFS_CONTROL rfs_control;		//0x0104
	REG_UNUSED unused108;				//
	REG_UNUSED unused10C;				//
	REG_UNUSED unused110;			//0x0110
	REG_FREQ_DEVIATION freq_deviation;	//0x0114
	REG_UNUSED unused118;
	REG_UNUSED unused11C;
	REG_COORD latitude;					//0x0120,0x0124
	REG_COORD longitude;				//0x0128,0x012C
	REG_COORD altitude;					//0x0130,0x0134
}DEVICE_REGS_PACK_2;

typedef struct _TAG_DEVICE_REGS_PACK_3
{
	REG_UNUSED unused200;				//
	REG_SERIAL_CONTROL serial_control;	//0x0204
	REG_UNUSED unused208;				//
	REG_UNUSED unused20C;				//
	REG_UNUSED unused210;				//
	REG_UNUSED unused214;				//
	REG_UNUSED unused218;				//
	REG_UNUSED unused21C;				//
	REG_GNSS_CONTROL gnss_control;		//0x0220
	REG_UNUSED unused224;				//
	REG_UNUSED unused228;				//
	REG_UNUSED unused22C;				//
	REG_TXEN_DELAY txen_delay;			//0x0230
	REG_UNUSED unused234;				//
	REG_UNUSED unused238;				//
	REG_UNUSED unused23C;				//
	REG_UNUSED unused240;				//0x0240
	REG_UNUSED unused244;				//
	REG_UNUSED unused248;				//
	REG_UNUSED unused24C;				//
	REG_UNUSED unused250;				//0x0250
	REG_UNUSED unused254;				//
	REG_UNUSED unused258;				//
	REG_UNUSED unused25C;				//
}DEVICE_REGS_PACK_3;

#define ADRESS_PACK_1 0x0000
#define ADRESS_PACK_2 0x0100
#define ADRESS_PACK_3 0x0200

typedef struct _TAG_DEVICE_REGISTERS
{
	DEVICE_REGS_PACK_1 pack1;
	DEVICE_REGS_PACK_2 pack2;
	DEVICE_REGS_PACK_3 pack3;
}DEVICE_REGISTERS;

//-----------------------------------------------------------------------------

#endif // __DASD_REGISTERS_H__
