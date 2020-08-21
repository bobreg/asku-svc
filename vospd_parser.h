#ifndef __VOSPD_PARSER_H__
#define __VOSPD_PARSER_H__

#include "../common/parser.h"

//----------------------------------------------------------------------------------------------------------------

class AskuVospdParser : public AskuCommonParser<QByteArray>
{
public:
	AskuVospdParser();
	virtual ~AskuVospdParser();
	virtual bool parse();

	static unsigned short crc16_ccitt(const char *msg, int len);
};

//----------------------------------------------------------------------------------------------------------------

#endif // __VOSPD_PARSER_H__