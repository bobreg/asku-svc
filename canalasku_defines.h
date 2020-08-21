#ifndef _CANALASKU_DEFINES_H_
#define _CANALASKU_DEFINES_H_

//-------------------------------------------------------------------
#define CA_N_DEVICES			3
#define CA_N_MODULES_UMI		32
#define CA_N_TRANSMITTERS		2
#define CA_MAX_N_MODULES_UMI	(CA_N_MODULES_UMI + 1)
//-------------------------------------------------------------------
//#define CA_N_TRANSMITTER1		1
//#define CA_N_TRANSMITTER2		2

//-------------------------------------------------------------------
#define CA_N_DEVICES_MAX_ADDRESS	0x3F

//-------------------------------------------------------------------
#define addrOffsetObserver		0x00	//---
#define addr124YY08				0x1A	//ELK for Observer
#define addr124YG02G1			0x1B	//PRD1 for Observer
#define addr124YG02G2			0x1C	//PRD2 for Observer

//-------------------------------------------------------------------

#define CA_MIN_MESSAGE_LENGTH	8
#define CA_MAX_MESSAGE_LENGTH	104 //48*2+8

#define CA_HEADER_PREAMBULA		0xFF
#define CA_HEADER_START_BYTE	0x10
#define CA_HEADER_STOP_BYTE		0x11
#define CA_HEADER_MAX_N_BYTES	48

#define CA_ELECTRO		0
#define CA_TRANSMITTER1	1
#define CA_TRANSMITTER2 2

#define CA_HEADER_TEST1_N_BYTES		1
#define CA_HEADER_TEST2_N_BYTES		6
#define CA_HEADER_COMMAND_N_BYTES	6
#define CA_HEADER_DC_MAX_N_BYTES	18
#define CA_HEADER_UMI_N_BYTES		18
#define CA_HEADER_STATE_N_BYTES		48
#define CA_HEADER_COMMAND_MODULES_N_BYTES 6

//-------------------------------------------------------------------
#define commTest1								0x70
#define commTest2								0x71
#define commUpr									0x72
#define commSost								0x73
#define commParamUMIv1							0x74
#define commAnalog								0x78
#define commUpr2								0x82
#define commSost2								0x86
#define commSost3								0x87
#define commParamUMIv2							0x84
#define commParamUMIv3							0x94
#define commParamUMIv4							0x8E
#define commParamUMIv5							0x8D
#define commParamUMIv5Group						0x8A
#define commParamFSV							0x89

//-------------------------------------------------------------------
#define CA_NO_ERROR								0
#define CA_ERROR_SMALLDATA						1
#define CA_ERROR_LARGEDATA						2
#define CA_ERROR_PREAMBULA						3
#define CA_ERROR_START_BYTE						4
#define CA_ERROR_ADRRESS						5
#define CA_ERROR_COMMAND						6
#define CA_ERROR_N_BYTES						7
#define CA_ERROR_CRC							8
#define CA_ERROR_STOP_BYTE						9
#define CA_ERROR_CODES							10
#define CA_ERROR_NO_OS							11
#define CA_ERROR_NO_DATA						12
#define CA_ERROR_NO_NETWORK						13

//-------------------------------------------------------------------
#define CA_COMMAND_NULL							0x00
//-------------------------------------------------------------------
#define CA_COMMAND_PRD_N_380_ON					0x60
#define CA_COMMAND_PRD_N_380_OFF				0x61
#define CA_COMMAND_PRD_N_PUMI1_ON				0x70
#define CA_COMMAND_PRD_N_PUMI_OFF				0x71
#define CA_COMMAND_PRD_N_PUMI2_ON				0x72
#define CA_COMMAND_PRD_N_HOT_RES_ON				0x74
#define CA_COMMAND_PRD_N_HOT_RES_OFF			0x75
#define CA_COMMAND_PRD_N_SVCH1_ON				0x78
#define CA_COMMAND_PRD_N_SVCH_OFF				0x79
#define CA_COMMAND_PRD_N_SVCH2_ON				0x7A
#define CA_COMMAND_PRD_N_UMI_380_ON				0x94
#define CA_COMMAND_PRD_N_UMI_380_OFF			0x95
#define CA_COMMAND_PRD_N_UMI_POWER_ALL_ON		0x80
#define CA_COMMAND_PRD_N_UMI_POWER_ON			0x82
#define CA_COMMAND_PRD_N_UMI_POWER_ALL_OFF		0x81
#define CA_COMMAND_PRD_N_UMI_POWER_OFF			0x83
#define CA_COMMAND_PRD_N_UMI_SVCH_ALL_ON		0x84
#define CA_COMMAND_PRD_N_UMI_SVCH_ON			0x86
#define CA_COMMAND_PRD_N_UMI_SVCH_ALL_OFF		0x85
#define CA_COMMAND_PRD_N_UMI_SVCH_OFF			0x87
#define CA_COMMAND_PRD_N_UMI_RESET_ON			0x90
#define CA_COMMAND_PRD_N_UMI_RESET_OFF			0x91
#define CA_COMMAND_PRD_N_UMI_WRITE_PHASE_ON		0x92
#define CA_COMMAND_PRD_N_UMI_WRITE_PHASE_OFF	0x93
#define CA_COMMAND_PRD_N_UMI_READ_PHASE_ON		0x96
#define CA_COMMAND_PRD_N_UMI_READ_PHASE_OFF		0x97
//-------------------------------------------------------------------
#define CA_COMMAND_ELK_N_HOWL1_ON				0x90
#define CA_COMMAND_ELK_N_HOWL1_OFF				0x91
#define CA_COMMAND_ELK_N_HOWL2_ON				0x92
#define CA_COMMAND_ELK_N_HOWL2_OFF				0x93
#define CA_COMMAND_ELK_N_RPU_LIGHT_ON			0x94
#define CA_COMMAND_ELK_N_RPU_LIGHT_OFF			0x95
#define CA_COMMAND_ELK_N_RESET_ON				0x96
#define CA_COMMAND_ELK_N_RESET_OFF				0x97
#define CA_COMMAND_ELK_N_PERIM_LIGHT_ON			0x98
#define CA_COMMAND_ELK_N_PERIM_LIGHT_OFF		0x99
#define CA_COMMAND_ELK_N_FIRE_ON				0x9A
#define CA_COMMAND_ELK_N_FIRE_OFF				0x9B
#define CA_COMMAND_ELK_N_SAFE_ON				0x9C
#define CA_COMMAND_ELK_N_SAFE_OFF				0x9D
#define CA_COMMAND_ELK_N_BLOCK_COND_ON			0x9E
#define CA_COMMAND_ELK_N_BLOCK_COND_OFF			0x9F
//-------------------------------------------------------------------

typedef struct _CA_tag_COMMAND_HEADER
{
	unsigned char preambula;
	unsigned char start_byte;
	unsigned char address;
	unsigned char command;
	unsigned char n_bytes;
}CA_COMMAND_HEADER;

typedef struct _CA_tag_RECEIVE_DATA
{
	CA_COMMAND_HEADER header;
	unsigned char data[CA_HEADER_STATE_N_BYTES];
	unsigned char crc;
	unsigned char stop_byte;
}CA_RECEIVE_DATA;

typedef struct _CA_tag_TYPE_COMMAND
{
	unsigned char command[CA_HEADER_COMMAND_N_BYTES];
	quint32 timeout;
	_CA_tag_TYPE_COMMAND(quint32 t = 0, unsigned char b1 = 0, unsigned char b2 = 0, unsigned char b3 = 0, unsigned char b4 = 0, unsigned char b5 = 0, unsigned char b6 = 0)
	{
		command[0] = b1;
		command[1] = b2;
		command[2] = b3;
		command[3] = b4;
		command[4] = b5;
		command[5] = b6;
		timeout = t;
	}
	QString dump() {
		return QString("time=%1 command: ").arg(timeout) + 
				QString("%1 %2 %3 %4 %5 %6")
					.arg((int)command[0],2,16,QChar('0'))
					.arg((int)command[1],2,16,QChar('0'))
					.arg((int)command[2],2,16,QChar('0'))
					.arg((int)command[3],2,16,QChar('0'))
					.arg((int)command[4],2,16,QChar('0'))
					.arg((int)command[5],2,16,QChar('0')).toUpper();
	}
}CA_TYPE_COMMAND;

//-------------------------------------------------------------------

#endif //_CANALASKU_DEFINES_H_
