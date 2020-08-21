#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__

#include <QHostAddress>
#include <QString>
#include "../common/global.h"

//----------------------------------------------------------------------------------------------------------------

#ifndef ELEM_STATE_DEFINED
#define ELEM_STATE_DEFINED

const int ELEM_NORMA = 0; 
const int ELEM_ERROR = 1;
const int ELEM_AVAR = 2;
const int ELEM_NOT = 3;
const int ELEM_DISABLE = 4;
const int ELEM_BACKGROUND = 5;
const int ELEM_MEST = 6; 
const int ELEM_ISPR = 7;

const int ELEM_SOST_MEST=10;
const int ELEM_NORMA_MEST=10;
const int ELEM_ERROR_MEST=11;
const int ELEM_AVAR_MEST=12;
const int ELEM_NOT_MEST=13;
const int ELEM_NOT_WORK=14;
const int ELEM_ISPR_MEST=17;

#endif

// ------------------------------------------------------------------

#ifndef MAKEWORD
	#define MAKEWORD(low, high) \
	((unsigned short)((((unsigned short)(high)) << 8) | ((unsigned char)(low))))
#endif

//----------------------------------------------------------------------------------------------------------------

typedef struct tagMAIN
{
	quint32 id;
	quint32 litera;
	bool mobile;
	bool main;
}SetupMAIN;

typedef struct tagPATH
{
	QString tables;
	QString log;
	QString phase;
}SetupPATH;

typedef struct tagGPR
{
	QHostAddress ip;
	quint16 port;
}SetupGPR;

typedef struct tagPOI
{
	QHostAddress ip;
	quint16 port;
}SetupPOI;

typedef struct tagKOEFF_POI
{
	double kshAvar;
	double kshError;
	double kshNorma;
	double psNorma;
	double kpNorma;
}SetupKOEFF_POI;

typedef struct tagCOMM
{
	QHostAddress ip;
}SetupCOMM;

typedef struct tagVOI
{
	QHostAddress ip;
	quint16 port_in;
	quint16 port_out;
}SetupVOI;

typedef struct tagASKU
{
	quint16 port1;
	quint16 port2;
	quint32 log;
}SetupASKU;

typedef struct tagN106
{
	QHostAddress ip;
	quint16 port_in;
	quint16 port_out;
}SetupN106;

typedef struct tagSKRPS
{
	quint32 skr_azimuth;
	quint32 ps_azimuth;
	quint32 skr_strobe;
	quint32 ps_strobe;
	quint32 period;
	quint32 offset;
}SetupSKRPS;

typedef struct tagModule
{
	QString fileRipch;
	QString fileMode;
	QString fileSwitch;
	QString fileNchm;
	QString fileDisable;
	quint16 lir1_offset;
	quint16 lir2_offset;
	quint32 freq_deviation;
	quint32 lastMode;
}SetupModule;

typedef struct tagDRIVE
{
	quint16 port1;
	quint16 port2;
	quint32 address1;
	quint32 address2;
	double speed1;
	double speed2;
}SetupDRIVE;

typedef struct tagCOOLERS
{
	quint16 port1;
	quint16 port2;
	quint32 address1;
	quint32 address2;
	quint32 address3;
	quint32 address4;
	double frequency;
}SetupCOOLERS;

typedef struct tagUPS
{
	quint16 port1;
	quint16 port2;
	quint32 address1;
	quint32 address2;

	quint32 type;
	QHostAddress ip1;
	QHostAddress ip2;
	quint16 port;
	quint32 address;
	QString snmp_community;
	quint32 snmp_version;
	quint32 snmp_timeout;
}SetupUPS;

typedef struct tagDES
{
	QHostAddress ip;
	quint16 port;
	quint32 mains_address1;
	quint32 mains_address2;
	quint32 dg_address1;
	quint32 dg_address2;
	quint32 dg_address3;
	quint32 dg_address4;
}SetupDES;

typedef struct tagVRL
{
	QHostAddress ip;
	quint16 port;
	quint16 port_listen;
}SetupVRL;

typedef struct tagPHASE
{
	QHostAddress ip;
	quint16 port;
	QString fileEtalon;
	QString fileCurrent;
}SetupPHASE;

typedef struct tagViewer
{
	quint32 days;
}SetupViewer;

typedef struct tagPWM
{
	quint32 pwrFail;
	quint32 pwrLow;
	quint32 pwrGate;
}SetupPWM;

typedef struct tagPOS
{
	QHostAddress ip;
	quint16 port;
}SetupPOS;

typedef struct tagVOSPD
{
	quint32 type;
	QHostAddress ip1;
	QHostAddress ip2;
	quint16 port;
}SetupVOSPD;

typedef struct tagSetupData
{
	SetupMAIN main;
	SetupPATH path;
	SetupGPR  gpr1;
	SetupGPR  gpr2;
	SetupPOI  poi;
	SetupKOEFF_POI koeffPoi;
	SetupCOMM com1;
	SetupCOMM com2;
	SetupVOI  voi;
	SetupASKU asku;
	SetupSKRPS skrps;
	SetupModule module;
	SetupDRIVE drive;
	SetupCOOLERS coolers;
	SetupUPS ups;
	SetupDES des;
	SetupVRL vrl1;
	SetupVRL vrl2;
	SetupPWM pwm;
	SetupPOS pos;
	SetupVOSPD vospd;
	SetupN106 n106;
	SetupPHASE phase;
	SetupViewer viewer;
}SetupData;

//----------------------------------------------------------------------------------------------------------------

#define LITERA_A 1
#define LITERA_B 2

#define IDGPR1 0
#define IDGPR2 1
#define IDPPV 2
#define IDRMO 3
#define IDSOI 4

#define IDGPR() (m_setup.main.id)
#define OTHER_GPR_ID() (m_setup.main.id == IDGPR1 ? IDGPR2 : IDGPR1)
#define ISGPR() (m_setup.main.id < IDPPV)
#define ISGPR1() (m_setup.main.id == IDGPR1)
#define ISGPR2() (m_setup.main.id == IDGPR2)
#define ISPPV() (m_setup.main.id == IDPPV)
#define ISRMO() (m_setup.main.id >= IDRMO)

#define NUM_GPR() (m_setup.main.id + 1)
#define NUM_OTHER_GPR() ((m_setup.main.id == IDGPR1 ? IDGPR2 : IDGPR1) + 1)

#define FROM_GPR(id) (id < IDPPV)
#define FROM_LOCAL_GPR(id) (FROM_GPR(id) && IDGPR() == id)
#define FROM_OTHER_GPR(id) (FROM_GPR(id) && IDGPR() != id)
#define FROM_PPV(id) (id == IDPPV)
#define FROM_RMO(id) (id == IDRMO)
//#define FROM_RMO(id) (id == IDRMO /*&& id > IDSOI*/)
#define FROM_SOI(id) (id == IDSOI)

#define IS_MAIN_GPR() (m_setup.main.main)

#define GPR1_IP() (m_setup.gpr1.ip)
#define GPR2_IP() (m_setup.gpr2.ip)
#define GPR1_PORT() (m_setup.gpr1.port)
#define GPR2_PORT() (m_setup.gpr2.port)
#define MY_GPR_IP() ( ISGPR() ? (ISGPR1() ? GPR1_IP() : GPR2_IP()) : QHostAddress())
#define OTHER_GPR_IP() ( ISGPR() ? (ISGPR1() ? GPR2_IP() : GPR1_IP()) : QHostAddress())
#define MY_GPR_PORT() ( ISGPR() ? (ISGPR1() ? GPR1_PORT() : GPR2_PORT()) : 0)
#define OTHER_GPR_PORT() ( ISGPR() ? (ISGPR1() ? GPR2_PORT() : GPR1_PORT()) : 0)

extern SetupData m_setup;

//----------------------------------------------------------------------------------------------------------------

void NormalToGeo(double dNormal, int *pnGr, int *pnMin, float *pfSec);

//----------------------------------------------------------------------------------------------------------------

#endif // __GLOBALVAR_H__
