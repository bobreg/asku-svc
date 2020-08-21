#ifndef _VOSPD_STRUCT_H_INCLUDED_
#define _VOSPD_STRUCT_H_INCLUDED_

#include "vospd_parser.h"
#include <QDebug>
#include <QHostAddress>

//-----------------------------------------------------------------------------
enum VospdMessages
{
	RequestVersion		= 0x01,
	RequestState		= 0x02,
	SetConfig		= 0x03,
	RequestAngles		= 0x04,
	SetResetFailure		= 0x05,
	RequestConfig		= 0x06,
	SetFrameFormat		= 0x07,
	SetActiveSensor		= 0x08,
	RequestError		= 0x09,
	SetAzCorrection		= 0x0A,
	SetAzImitator		= 0x0B,
	TestCoreManch		= 0x0C,
	SetIpAddress		= 0x0D,
	RequestActSensor	= 0x0E
};

//-----------------------------------------------------------------------------

class VospdMessage : public QByteArray
{
public:
	VospdMessage(unsigned char cmd, const QByteArray & data = QByteArray())
	{
		resize(0);

		append(0x55);
		append(0xAA);
		append(6 + data.count());
		append(cmd);
		append(data);

		unsigned short crc = AskuVospdParser::crc16_ccitt((const char*)constData(), count());
		unsigned char c1 = (unsigned char)((crc & 0xFF00) >> 8);
		unsigned char c2 = (unsigned char)((crc & 0x00FF));

		append(c2);
		append(c1);
	}
};

//-----------------------------------------------------------------------------

class VospdRequestVersion : public VospdMessage
{
public:
	VospdRequestVersion() : VospdMessage(RequestVersion)
	{
	}
};

//-----------------------------------------------------------------------------

class VospdRequestState : public VospdMessage
{
public:
	VospdRequestState() : VospdMessage(RequestState)
	{
	}
};

//-----------------------------------------------------------------------------

class VospdSetConfig : public VospdMessage
{
public:
	QByteArray makeData(quint8 config1, quint8 config2, quint8 led_test)
	{
		QByteArray data;
		data.append(config1);
		data.append(config2);
		data.append(led_test);
		return data;
	}

	VospdSetConfig(quint8 config1, quint8 config2, quint8 led_test) : VospdMessage(SetConfig, makeData(config1, config2, led_test))
	{
	}
};

//-----------------------------------------------------------------------------

class VospdRequestAngles : public VospdMessage
{
public:
	VospdRequestAngles() : VospdMessage(RequestAngles)
	{
	}
};

//-----------------------------------------------------------------------------

class VospdSetResetFailure : public VospdMessage
{
public:
	VospdSetResetFailure() : VospdMessage(SetResetFailure)
	{
	}
};

//-----------------------------------------------------------------------------

class VospdRequestConfig : public VospdMessage
{
public:
	VospdRequestConfig() : VospdMessage(RequestConfig)
	{
	}
};

//-----------------------------------------------------------------------------

class VospdSetFrameFormat : public VospdMessage
{
public:
	QByteArray makeData(quint8 format)
	{
		QByteArray data;
		data.append(format);
		return data;
	}

	VospdSetFrameFormat(quint8 format) : VospdMessage(SetFrameFormat, makeData(format))
	{
	}
};

//-----------------------------------------------------------------------------

class VospdSetActiveSensor : public VospdMessage
{
public:
	QByteArray makeData(quint8 sensor)
	{
		QByteArray data;
		data.append(sensor);
		return data;
	}

	VospdSetActiveSensor(quint8 sensor) : VospdMessage(SetActiveSensor, makeData(sensor))
	{
	}
};

//-----------------------------------------------------------------------------

class VospdSetAzimuthCorrection : public VospdMessage
{
public:
	QByteArray makeData(unsigned short az1, unsigned short az2, bool set1, bool set2)
	{
		QByteArray data;

		az1 &= 0x3FFF;
		az2 &= 0x3FFF;

		az1 |= set1 ? 0x8000 : 0;
		az2 |= set2 ? 0x8000 : 0;

		data.append(az1 & 0x00FF);
		data.append((az1 & 0xFF00) >> 8);
		data.append(az2 & 0x00FF);
		data.append((az2 & 0xFF00) >> 8);

		return data;
	}

	VospdSetAzimuthCorrection(unsigned short az1, unsigned short az2, bool set1 = true, bool set2 = true) : VospdMessage(SetAzCorrection, makeData(az1, az2, set1, set2))
	{
	}
};

//-----------------------------------------------------------------------------

class VospdSetImitator : public VospdMessage
{
public:
	QByteArray makeData(bool on)
	{
		QByteArray data;
		data.append(on ? 0x80 : 0x00);
		return data;
	}

	VospdSetImitator(bool on) : VospdMessage(SetAzImitator, makeData(on))
	{
	}
};

//-----------------------------------------------------------------------------

class VospdSetIpAddress : public VospdMessage
{
public:
	QByteArray makeData(QHostAddress ip, QHostAddress mask, QHostAddress gate)
	{
		QByteArray data;

		quint32 i_ip   = ip.toIPv4Address();
		data.append((i_ip & 0xFF000000) >> 24);
		data.append((i_ip & 0x00FF0000) >> 16);
		data.append((i_ip & 0x0000FF00) >> 8);
		data.append(i_ip & 0x000000FF);

		quint32 i_mask = mask.toIPv4Address();
		data.append((i_mask & 0xFF000000) >> 24);
		data.append((i_mask & 0x00FF0000) >> 16);
		data.append((i_mask & 0x0000FF00) >> 8);
		data.append(i_mask & 0x000000FF);

		quint32 i_gate = gate.toIPv4Address();
		data.append((i_gate & 0xFF000000) >> 24);
		data.append((i_gate & 0x00FF0000) >> 16);
		data.append((i_gate & 0x0000FF00) >> 8);
		data.append(i_gate & 0x000000FF);

		return data;
	}

	VospdSetIpAddress(QHostAddress ip, QHostAddress mask, QHostAddress gate = QHostAddress()) : VospdMessage(SetIpAddress, makeData(ip, mask, gate))
	{
		
	}
};

//-----------------------------------------------------------------------------

class VospdRequestActiveSensor : public VospdMessage
{
public:
	VospdRequestActiveSensor() : VospdMessage(RequestActSensor)
	{
	}
};

#pragma pack(push, 1)

//-----------------------------------------------------------------------------

typedef struct _AnswerHeader
{
	unsigned short preambula;
	unsigned char length;
	unsigned char cmd;
}CMD_HEADER;

//-----------------------------------------------------------------------------

const unsigned int AnswerVersionLength = 12;

typedef struct _VospdAnswerVersion
{
	CMD_HEADER header;
	unsigned char Major_Bot;
	unsigned char Minor_Bot;
	unsigned char Patch_Bot;
	unsigned char Major_Top;
	unsigned char Minor_Top;
	unsigned char Patch_Top;
	unsigned short crc;

	_VospdAnswerVersion(const QByteArray & data) {
		*this = *((const _VospdAnswerVersion*)(const char*)data.constData());
	}
}VospdAnswerVersion;

//-----------------------------------------------------------------------------
typedef struct _VospdStatus
{
	unsigned char bot_Main:1;
	unsigned char opt_Main:1;
	unsigned char top_Main:1;
	unsigned char az_status1:1;
	unsigned char az_status2:1;
	unsigned char dg_link:1;
	unsigned char horizont_status:1;
	unsigned char cmd_status:1;
}VospdStatus;

//-----------------------------------------------------------------------------

const unsigned int AnswerStatusLength = 7;

typedef struct _VospdAnswerStatus
{
	CMD_HEADER header;
	VospdStatus status;
	unsigned short crc;

	_VospdAnswerStatus(const QByteArray & data) {
		*this = *((const _VospdAnswerStatus*)(const char*)data.constData());
	}
}VospdAnswerStatus;

//-----------------------------------------------------------------------------

const unsigned int AnswerActSensorLength = 7;

typedef struct _VospdAnswerActSensor
{
	CMD_HEADER header;
	unsigned char act_sensor;
	unsigned short crc;

	_VospdAnswerActSensor(const QByteArray & data) {
		*this = *((const _VospdAnswerActSensor*)(const char*)data.constData());
	}
}VospdAnswerActSensor;

//-----------------------------------------------------------------------------

typedef struct _VospdAzimuthCorrection
{
	unsigned short correction:14;
	unsigned short reserve:1;
	unsigned short apply:1;
}VospdAzimuthCorrection;

//-----------------------------------------------------------------------------

typedef struct _VospdIndicators
{
	unsigned short left_up:2;
	unsigned short left_dn:2;
	unsigned short right_up:2;
	unsigned short right_dn:2;
	unsigned short front_up:2;
	unsigned short front_dn:2;
	unsigned short rear_up:2;
	unsigned short rear_dn:2;
}VospdIndicators;

//-----------------------------------------------------------------------------

typedef struct _VospdAngles
{
	float cross;
	float axis;
}VospdAngles;

//-----------------------------------------------------------------------------

const unsigned int AnswerAnglesLength = 17;

typedef struct _VospdAnswerAngles
{
	CMD_HEADER header;
	VospdStatus status;
	VospdAngles angles;
	VospdIndicators indicators;
	unsigned short crc;

	_VospdAnswerAngles(const QByteArray & data) {
		*this = *((const _VospdAnswerAngles*)(const char*)data.constData());
	}
}VospdAnswerAngles;

//-----------------------------------------------------------------------------

typedef struct _VospdConfig
{
	unsigned char forc_Az:1;
	unsigned char used_Az:1;
	unsigned char virt_Az:1;
	unsigned char virt_En:1;
	unsigned char imit_En:1;
	unsigned char kod_format:1;
	unsigned char reserve:2;
}VospdConfig;

//-----------------------------------------------------------------------------
const unsigned int AnswerConfigLength = 12;

typedef struct _VospdAnswerConfig
{
	CMD_HEADER header;
	VospdStatus status;
	VospdConfig config;
	VospdAzimuthCorrection az1_cfg;
	VospdAzimuthCorrection az2_cfg;
	unsigned short crc;

	_VospdAnswerConfig(const QByteArray & data) {
		*this = *((const _VospdAnswerConfig*)(const char*)data.constData());
	}
}VospdAnswerConfig;

//-----------------------------------------------------------------------------

class VspdStatus
{
public:
	QString versionTop;
	QString versionBot;
	quint8 azSensorStatus;
	quint8 azSensorActive;
	quint16 correction1;
	quint16 correction2;
	quint8 test_manch;
	bool imitator;

	VspdStatus() {
		versionTop = QString();
		versionBot = QString();
		azSensorStatus = 0;
		azSensorActive = 0;
		correction1 = 0;
		correction2 = 0;
		test_manch = 0;
		imitator = false;
	}
};

#pragma pack(pop)

//-----------------------------------------------------------------------------

#endif //_VOSPD_STRUCT_H_INCLUDED_
