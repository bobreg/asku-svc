#ifndef _CANALASKU_CODEC_H_
#define _CANALASKU_CODEC_H_

//-------------------------------------------------------------------

#include <QList>
#include "canalasku_defines.h"

//-------------------------------------------------------------------

class CanalAskuCodec
{
	QList<quint8> cmdCodes;
	QList<quint8> addrCodes;

	QVector<unsigned char> askuData;

	QByteArray convertToAscii(const unsigned char *source, unsigned int length);
	QByteArray convertFromAscii(const unsigned char *source, unsigned int length);

	static unsigned char calcCRC(const unsigned char *buffer, unsigned int length, unsigned int offset = 0);

	QByteArray checkMessage(QVector<unsigned char> *vector);
	int decodeMessage(const unsigned char *buffer, unsigned int length);

public:
	CanalAskuCodec();
	~CanalAskuCodec();

	QByteArray codeCommand(unsigned char c_address, unsigned char c_command, unsigned char c_num_bytes, unsigned char *c_command_data);
	void dataReceived(unsigned char * buffer, int length);
	int processData();

	void clear();
	quint8* packet();
	quint8 packetSize();
	quint8 packetAddress();
	quint8 packetCommand();
	quint8 packetModule();

	CA_COMMAND_HEADER header;
	CA_RECEIVE_DATA receive_data;
};

//-------------------------------------------------------------------

#endif //_CANALASKU_CODEC_H_
