#include "../common/logger.h"
#include "vospd_parser.h"

//----------------------------------------------------------------------------------------------------------------
AskuVospdParser::AskuVospdParser() : AskuCommonParser<QByteArray>()
{
	
}

//----------------------------------------------------------------------------------------------------------------
AskuVospdParser::~AskuVospdParser()
{
	
}

//----------------------------------------------------------------------------------------------------------------
bool AskuVospdParser::parse()
{
	quint32 step = 0;
	qint32 length = m_bytedata.count();
	qint32 messageLength = 0;
	qint32 pos = 0;
	quint8 cStart1 = 0x55;
	quint8 cStart2 = 0xAA;
	quint8 cLength = 0;
	qint32 parseError = NoError;

	while(pos < length)
	{
		quint8 sym = m_bytedata[pos];

//		qDebug() << QString("%1").arg(sym,0,16,QChar('0')).toLatin1() << "\t" << step << "\t" << length << "\t" <<  cLength;

		switch(step)
		{
			case 0:
				if(sym == cStart1)
				{
					step = 1;
					pos++;
					messageLength++;
				}
				else
				{
					if(sym != 0)
						LogVospdError("VospdParser: unknown start symbol 0x%02X", sym);
					m_bytedata.remove(pos, 1);
					messageLength = 0;
					length--;
					parseError = ErrorNoStart;
				}
				break;
			case 1:
				if(sym == cStart2)
				{
					step = 2;
					pos++;
					messageLength++;
				}
				else
				{
					LogVospdError("VospdParser: unknown start symbol 0x%02X", sym);
					m_bytedata.remove(pos - 1, 2);
					messageLength = 0;
					length -= 2;
					pos--;
					parseError = ErrorNoStart;
					step = 0;
				}
				break;
			case 2:
				if(sym < 6)
				{
					LogVospdError("VospdParser: invalid length 0x%02X", sym);
					m_bytedata.remove(pos - 2, 3);
					messageLength = 0;
					length -= 3;
					pos -= 2;
					parseError = ErrorDataError;
					step = 0;
				}
				else
				{
					cLength = sym - 3;
					step = 3;
					pos++;
					messageLength++;
				}
				break;
			case 3:
				if(cLength > 0)
				{
					pos++;
					messageLength++;
					cLength--;
				}
				if(cLength == 0)
					step = 4;
				break;
			case 4:
				break;
		}

//		qDebug() << "\t\t\t\t" << pos << "\t" << step << "\t" << length << "\t" <<  cLength;


		if(step < 4)
		{
			if(pos >= length)
			{
				LogVospdError("VospdParser: not enough data");
				parseError = ErrorNoStop;
			}
		}
		else
		{
			QByteArray message = m_bytedata.left(messageLength);
			if(message.isEmpty())
			{
				LogVospdError("VospdParser: warning empty data");
				m_parseError = ErrorDataError;
			}
			else
			{
				m_parseError = NoError;
				m_messages.append(message);
			}

			m_bytedata.remove(0, messageLength);

//			qDebug() << m_bytedata.count();

			length -= messageLength;
			step = 0;
			pos = 0;
			messageLength = 0;
		}
	}

	m_parseError = parseError;

	return isPendingMessage();
}

//----------------------------------------------------------------------------------------------------------------
unsigned short AskuVospdParser::crc16_ccitt(const char *msg, int len)
{
//	QString str,str1;
//	str = QString("crc16: ");
//	for(int i = 0; i < len; i++)
//	{
//		str1.sprintf("%02X ", (unsigned char)*(msg + i));
//		str += str1;
//	}

	unsigned short crc = 0xFFFF;

	while(len-- > 0)
	{
		crc ^= (int) *msg++ << 8;

		for(int j = 0; j < 8; j++)
			crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : crc << 1;
	}

//	qDebug() << str << "CRC16=" << crc;

	return crc;
}
//----------------------------------------------------------------------------------------------------------------
