#include "globalvar.h"
#include "canalasku_codec.h"

//--------------------------------------------------------------
CanalAskuCodec::CanalAskuCodec()
{
	addrCodes.append(addr124YY08);
	addrCodes.append(addr124YG02G1);
	addrCodes.append(addr124YG02G2);

	cmdCodes.append(commTest1);
	cmdCodes.append(commTest2);
	cmdCodes.append(commUpr2);
	cmdCodes.append(commSost2);
	cmdCodes.append(commParamUMIv4);

	clear();
}

//--------------------------------------------------------------
CanalAskuCodec::~CanalAskuCodec()
{
}

//--------------------------------------------------------------
void CanalAskuCodec::clear()
{
	memset((void*)&header, 0, sizeof(CA_COMMAND_HEADER));
	memset((void*)&receive_data, 0, sizeof(CA_RECEIVE_DATA));
}

//--------------------------------------------------------------
QByteArray CanalAskuCodec::codeCommand(unsigned char c_address, unsigned char c_command,unsigned char c_num_bytes, unsigned char *c_command_data)
{
	QByteArray buffer;

	if(c_num_bytes > CA_HEADER_MAX_N_BYTES)
	{
		qDebug("CanalAskuCodec::codeCommand : Too much data = %d bytes", c_num_bytes);
		return buffer;
	}

	buffer.append((unsigned char)CA_HEADER_PREAMBULA);
	buffer.append((unsigned char)CA_HEADER_START_BYTE);
	buffer.append((unsigned char)c_address);
	buffer.append((unsigned char)c_command);
	buffer.append((unsigned char)c_num_bytes);

	QByteArray bufferAscii = convertToAscii(c_command_data, c_num_bytes);
	buffer.append(bufferAscii);

	unsigned char cCRC = calcCRC((const unsigned char*)buffer.data(), buffer.size() - 2, 2);
	QByteArray bufferCrc = convertToAscii(&cCRC, 1);
	buffer.append(bufferCrc);

	buffer.append((unsigned char)CA_HEADER_STOP_BYTE);

	return buffer;	//	total size = 8 + c_num_bytes * 2;
}

//-------------------------------------------------------------------------
void CanalAskuCodec::dataReceived(unsigned char* buf, int len)
{
	for(int k = 0; k < len; k++)
		askuData.append(buf[k]);
}

//-------------------------------------------------------------------------
int CanalAskuCodec::processData()
{
	int nResult = CA_ERROR_NO_DATA;

	QByteArray buffer = checkMessage(&askuData);
	if(!buffer.isEmpty())
	{
		nResult = decodeMessage((const unsigned char*)buffer.data(), buffer.size());
	}

	return nResult;
}

//-------------------------------------------------------------------------
QByteArray CanalAskuCodec::convertToAscii(const unsigned char *source, unsigned int length)
{
	QByteArray destination;
	unsigned char K = 0, Kh = 0, Kl = 0;
	unsigned char Cl = 0, Ch = 0;

	for(unsigned int i = 0; i < length; i++)
	{
		K = *(source + i);
		Kh = K & 0xf0;
		Kh = Kh >> 4;
		Kl = K & 0x0f;

		if(Kl < 10)
			Cl = Kl + 0x30;
		else
			Cl = Kl + 0x37;

		if(Kh < 10)
			Ch = Kh + 0x30;
		else
			Ch = Kh + 0x37;

		destination.append(Cl);
		destination.append(Ch);
	}

	return destination;
}

// ------------------------------------------------------------------
QByteArray CanalAskuCodec::convertFromAscii(const unsigned char *source, unsigned int length)
{
	QByteArray destination;
	int k = 0;
	unsigned char Cl = 0, Ch = 0;
	unsigned char C = 0;

	for(unsigned int i = 0; i < length; i++)
	{
		Cl = *(source + k);
		k++;
		Ch = *(source + k);
		k++;

		if(Cl >= 0x41)
			Cl = Cl - 0x37;
		else
			Cl = Cl - 0x30;

		if(Ch >= 0x41)
			Ch = Ch - 0x37;
		else
			Ch = Ch - 0x30;

		C = Ch;
		C = C << 4;
		C = C | Cl;

		destination.append(C);
	}

	return destination;
}

//-----------------------------------------------------------------------
unsigned char CanalAskuCodec::calcCRC(const unsigned char* buffer, unsigned int length, unsigned int offset)
{
	unsigned char cCRC = 0;

	if(length > 0)
	{
		for(unsigned int i = 0; i < length; i++)
		{
			cCRC = cCRC + *(buffer + i + offset);
		}
	}

	cCRC = ~cCRC;
	cCRC = cCRC + 1;

	return cCRC;
}

//---------------------------------------------------------------------
QByteArray CanalAskuCodec::checkMessage(QVector<unsigned char> *vector)
{
	QByteArray buffer;

	if(vector->isEmpty())
		return buffer;

	unsigned int count = vector->count();
	int NN = 0, NL = 0;

	int state = 0;
	QVector<unsigned char>::iterator it;
	unsigned int bytes = 0;

	it = vector->begin();
	while(1)
	{
		switch(state)
		{
			case 0:
			{
				if(*it == 0xff)
				{
					state = 1;	//found preambula
					it++;
					bytes++;
				}
				else	//found strange
				{
					it = vector->erase(it);	//delete it
					bytes = 0;
					state = 0;
				}
				break;
			}

			case 1:
			{
				if(*it == 0x10)
				{
					state = 2;	//found start
					it++;
					bytes++;
				}
				else	//found strange
				{
					it = vector->erase(it);
					it = vector->erase(vector->begin(), it);
					bytes = 0;
					state = 0;
				}
				break;
			}

			case 2:
			{
				state = 3;	//addr
				it++;
				bytes++;
				break;
			}

			case 3:
			{
				state = 4;	//comm
				it++;
				bytes++;
				break;
			}

			case 4:
			{
				NN = *it;
				NL = (NN + 1) * 2;
				it++;
				bytes++;
				state = 5;	//len
				break;
			}
			case 5:
			{
				if(NL)	//data
				{
					it++;
					bytes++;
					NL--;
				}
				else
				{
					if(*it == 0x11)	//stop
					{
						it++;
						bytes++;

						QVector<unsigned char>::iterator it_buf;
						it_buf = vector->begin();

						for(unsigned int k = 0; k < bytes; k++)
						{
							buffer.append((unsigned char)(*it_buf));
							vector->erase(it_buf);
						}

						return buffer;	//MESSAGE!!
					}
					else	//no stop byte - > junk
					{
						it = vector->erase(it);
						it = vector->erase(vector->begin(), it);
						bytes = 0;
						state = 0;
					}
				}
				break;
			}
		}

		count = vector->count();
		if(bytes >= count)
			break;
	}

	return buffer;
}

//---------------------------------------------------------------------------------
int CanalAskuCodec::decodeMessage(const unsigned char *buffer_to_decode, unsigned int n_length)
{
	if(n_length < CA_MIN_MESSAGE_LENGTH)
		return CA_ERROR_SMALLDATA;

	if(n_length > CA_MAX_MESSAGE_LENGTH)
		return CA_ERROR_LARGEDATA;

	memcpy((void*)&receive_data.header, (void*)buffer_to_decode, sizeof(CA_COMMAND_HEADER));

	if(receive_data.header.preambula != CA_HEADER_PREAMBULA)
		return CA_ERROR_PREAMBULA;

	if(receive_data.header.start_byte != CA_HEADER_START_BYTE)
		return CA_ERROR_START_BYTE;

	if(addrCodes.indexOf(receive_data.header.address) < 0)
		return CA_ERROR_ADRRESS;

	if(cmdCodes.indexOf(receive_data.header.command) < 0)
		return CA_ERROR_COMMAND;

	if(receive_data.header.n_bytes > CA_HEADER_MAX_N_BYTES)
		return CA_ERROR_N_BYTES;

	if(*(buffer_to_decode + n_length - 1) != CA_HEADER_STOP_BYTE)
		return CA_ERROR_STOP_BYTE;

	receive_data.stop_byte = *(buffer_to_decode + n_length - 1);

	unsigned char cCRC = calcCRC(buffer_to_decode, 3 + (receive_data.header.n_bytes * 2), 2);

	QByteArray data = convertFromAscii((const unsigned char*)(buffer_to_decode + sizeof(CA_COMMAND_HEADER)), receive_data.header.n_bytes + 1);

	for(int i = 0; i < data.size(); i++)
	{
		unsigned char C = data.at(i);

		if(i == receive_data.header.n_bytes)
			receive_data.crc = C;
		else
		{
			 if(i < CA_HEADER_STATE_N_BYTES)
				receive_data.data[i] = C;
		}
	}

	if(cCRC != receive_data.crc)
		return CA_ERROR_CRC;

	return CA_NO_ERROR;
}

//---------------------------------------------------------------------------------
quint8* CanalAskuCodec::packet()
{
	return receive_data.data;
}

//---------------------------------------------------------------------------------
quint8 CanalAskuCodec::packetSize()
{
	return receive_data.header.n_bytes;
}

//---------------------------------------------------------------------------------
quint8 CanalAskuCodec::packetAddress()
{
	return receive_data.header.address;
}

//---------------------------------------------------------------------------------
quint8 CanalAskuCodec::packetCommand()
{
	return receive_data.header.command;
}

//---------------------------------------------------------------------------------
quint8 CanalAskuCodec::packetModule()
{
	return receive_data.data[0];
}

//---------------------------------------------------------------------------------
