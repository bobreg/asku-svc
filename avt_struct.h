#ifndef _AVT_STRUCT_H_INCLUDED_
#define _AVT_STRUCT_H_INCLUDED_

#pragma pack(push, 1)

const unsigned char AVT_N106A_CODE = 0x1B;
const unsigned char AVT_N106B_CODE = 0x06;

typedef struct tag_avt_requisites
{
	unsigned char n106_code;
	unsigned short serial;
}AVT_REQUSITES;

const unsigned char AVT_ASKU_CODE  = 0x1C;

typedef struct tag_avt_header
{
	unsigned char asku_code;
	AVT_REQUSITES requsites;
}AVT_HEADER;

const unsigned char AVT_COMMAND_QUERY_REQUISITES = 0x00;
const unsigned char AVT_COMMAND_QUERY_STATE = 0x01;
const unsigned char AVT_COMMAND_ERASE = 0x08;

typedef struct tag_avt_command_bits
{
	AVT_HEADER header;
	unsigned char unused:4;
	unsigned char command:4;
}AVT_COMMAND;

const unsigned char AVT_ANSWER_NO_ERROR = 0x00;
const unsigned char AVT_ANSWER_ERROR_REQUISITES = 0x01;
const unsigned char AVT_ANSWER_CANNOT_EXECUTE = 0x02;
const unsigned char AVT_ANSWER_RESERVED = 0xFF;

typedef struct tag_avt_answer_bits
{
	unsigned char error:4;
	unsigned char command:4;
}AVT_ANSWER;

typedef struct tag_avt_answer_requisites
{
	AVT_ANSWER answer;
	AVT_REQUSITES requisites;
}AVT_ANSWER_REQUISITES, AVT_ANSWER_ERASE;

typedef struct tag_avt_state_b1
{
	unsigned char pult:1;
	unsigned char b2:1;
	unsigned char unused:5;
	unsigned char fail:1;
}AVT_STATE_B1;

typedef struct tag_avt_state_b2
{
	unsigned char uvk:1;
	unsigned char b3:1;
	unsigned char unused:5;
	unsigned char fail:1;
}AVT_STATE_B2;

typedef struct tag_avt_state_b3_a
{
	unsigned char shdu:1;
	unsigned char gsch:1;
	unsigned char shdu_noconnect:1;
	unsigned char shdu_fail:1;
	unsigned char shdu_notloaded:1;
	unsigned char unused:2;
	unsigned char fail:1;
}AVT_STATE_B3_A;

typedef struct tag_avt_state_b3_b
{
	unsigned char inter:1;
	unsigned char gsch:1;
	unsigned char unused:5;
	unsigned char fail:1;
}AVT_STATE_B3_B;

typedef union tag_avt_state_b3
{
	AVT_STATE_B3_A a;
	AVT_STATE_B3_B b;
}AVT_STATE_B3;

typedef struct tag_avt_state
{
	AVT_STATE_B1 b1;
	AVT_STATE_B2 b2;
	AVT_STATE_B3 b3;
	unsigned char key_actual;
	unsigned char key_next;
	unsigned short cat_unexpended;
	unsigned int cat_expended;
	unsigned int crc;
}AVT_STATE;

typedef struct tag_avt_answer_state
{
	AVT_ANSWER answer;
	AVT_STATE state;
}AVT_ANSWER_STATE;

#pragma pack(pop)
/*
unsigned char S[255] = { // Таблица S, степеней
};

unsigned char L[255] = { // Таблица L, логарифмов
}; 

unsigned long CalcKsum (int len, unsigned char *data)
{
union {
unsigned long D; unsigned char B[4];
} KS;
int i;
unsigned char b;

SK.D = 0;
for (i=0; i<len; i++) {
if ((b = data[i]) != 0) { KS.B[0] ^= b;
KS.B[1] ^= S[(L[b]+i+1) % 255];
KS.B[2] ^= S[(L[b]+((i+1) % len)+1) % 255];
KS.B[3] ^= S[(L[b]+len-i) % 255];
}
}
return KS.D;
}
 */

#endif //_AVT_STRUCT_H_INCLUDED_
