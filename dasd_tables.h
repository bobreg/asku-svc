#ifndef __DASD_TABLES_H__
#define __DASD_TABLES_H__

//-----------------------------------------------------------------------------
#include <QObject>
#include <QVariantMap>
#include "../common/xmlfile.h"
#include "../common/stateset.h"
#include "../common/sectortable.h"

//-----------------------------------------------------------------------------

//SWITCH TABLE
#define ADRESS_SWITCH_TABLE 0x1000
#define SWITCH_TABLE_SIZE 0x1000

typedef struct _TAG_SWITCH_TABLE_SEGMENT
{
	unsigned int nchm_code:4;
	unsigned int reserved1:12;
	unsigned int mode_code:4;
	unsigned int reserved2:11;
	unsigned int disable:1;
}SWITCH_TABLE_SEGMENT;

#define SWITCH_TABLE_SEGMENT_COUNT 256

typedef struct _TAG_SWITCH_TABLE_SURVEY
{
	SWITCH_TABLE_SEGMENT segment[SWITCH_TABLE_SEGMENT_COUNT];
}SWITCH_TABLE_SURVEY;

#define SWITCH_TABLE_SURVEY_COUNT 4

typedef struct _TAG_SWITCH_TABLE
{
	SWITCH_TABLE_SURVEY survey[SWITCH_TABLE_SURVEY_COUNT];
}SWITCH_TABLE;

//-----------------------------------------------------------------------------
//DISABLE TABLE
typedef struct _TAG_DISABLE_TABLE_SEGMENT
{
	unsigned int disable:1;
}DISABLE_TABLE_SEGMENT;

#define DISABLE_TABLE_SEGMENT_COUNT SWITCH_TABLE_SEGMENT_COUNT

typedef struct _TAG_DISABLE_TABLE
{
	DISABLE_TABLE_SEGMENT segment[SWITCH_TABLE_SEGMENT_COUNT];
}DISABLE_TABLE;

//-----------------------------------------------------------------------------
//MODE TABLE
#define ADRESS_MODE_TABLE 0x4000
#define MODE_TABLE_SIZE 0x4000

typedef struct _TAG_MODE_TABLE_IMPULSE
{
	unsigned short period_code:16;
	unsigned short zi_code:4;
	unsigned short unused1:4;
	unsigned short max_varu:5;
	unsigned short unused2:3;
}MODE_TABLE_IMPULSE;

#define MODE_TABLE_IMPULSE_COUNT 128
typedef struct _TAG_MODE_TABLE_RO
{
	MODE_TABLE_IMPULSE impulse[MODE_TABLE_IMPULSE_COUNT];
}MODE_TABLE_RO;

#define MODE_TABLE_RO_COUNT 32
typedef struct _TAG_MODE_TABLE
{
	MODE_TABLE_RO ro[MODE_TABLE_RO_COUNT];
}MODE_TABLE;

//-----------------------------------------------------------------------------
//RIPCH TABLE
#define ADRESS_RIPCH_TABLE 0x8000
#define RIPCH_TABLE_SIZE 0x8000

typedef struct _TAG_RIPCH_SAMPLE_LENGTH_DELAY
{
	unsigned int length:16;
	unsigned int delay:16;
}RIPCH_SAMPLE_LENGTH_DELAY;

#define RIPCH_TABLE_SAMPLE_CTRLS 8
#define RIPCH_TABLE_SAMPLE_COMMS 4

typedef struct _TAG_RIPCH_IMPULSE_SAMPLE
{
	unsigned int pch_code:16;
	unsigned int length_code:12;
	unsigned int is_sin:1;
	unsigned int is_lchm:1;
	unsigned int incline:1;
	unsigned int is_nchm:1;

	unsigned int lead_pause:16;
	unsigned int step_lfm:16;

	unsigned int start_phase;
	unsigned int varu_delay;

	RIPCH_SAMPLE_LENGTH_DELAY ctrl[RIPCH_TABLE_SAMPLE_CTRLS];
	RIPCH_SAMPLE_LENGTH_DELAY common[RIPCH_TABLE_SAMPLE_COMMS];
}RIPCH_IMPULSE_SAMPLE;

#define RIPCH_TABLE_SAMPLE_COUNT 32
typedef struct _TAG_RIPCH_IMPULSE
{
	RIPCH_IMPULSE_SAMPLE sample[RIPCH_TABLE_SAMPLE_COUNT];
}RIPCH_IMPULSE;

#define RIPCH_TABLE_IMPULSE_COUNT 16
typedef struct _TAG_RIPCH_TABLE
{
	RIPCH_IMPULSE impulse[RIPCH_TABLE_IMPULSE_COUNT];
}RIPCH_TABLE;

//-----------------------------------------------------------------------------
//NCHM TABLE
#define ADRESS_NCHM_TABLE 0x10000
#define NCHM_TABLE_SIZE 0x0C000

typedef struct _TAG_NCHM_TABLE_CODE_ITEM
{
	unsigned int sin:16;
	unsigned int cos:16;
}NCHM_TABLE_CODE_ITEM;

#define NCHM_TABLE_CODE_ITEM_COUNT 1023
typedef struct _TAG_NCHM_TABLE_CODE_RO
{
	unsigned int length;
	NCHM_TABLE_CODE_ITEM ro[NCHM_TABLE_CODE_ITEM_COUNT];
}NCHM_TABLE_CODE_RO;

#define NCHM_TABLE_RO_COUNT 8
typedef struct _TAG_NCHM_TABLE_CODE
{
	NCHM_TABLE_CODE_RO ro[NCHM_TABLE_RO_COUNT];
}NCHM_TABLE_CODE;

#define NCHM_TABLE_AMPLITUDE_ITEM_COUNT 1024
typedef struct _TAG_NCHM_TABLE_AMPLITUDE_RO
{
	unsigned short amplitude[NCHM_TABLE_AMPLITUDE_ITEM_COUNT];
}NCHM_TABLE_AMPLITUDE_RO;

typedef struct _TAG_NCHM_TABLE_AMPLITUDE
{
	NCHM_TABLE_AMPLITUDE_RO ro[NCHM_TABLE_RO_COUNT];
}NCHM_TABLE_AMPLITUDE;

typedef struct _TAG_NCHM_TABLE
{
	NCHM_TABLE_CODE table_code;
	NCHM_TABLE_AMPLITUDE table_amplitude;
}NCHM_TABLE;

typedef struct _TAG_DEVICE_TABLES
{
	RIPCH_TABLE ripch_table;
	SWITCH_TABLE switch_table;
	MODE_TABLE mode_table;
	NCHM_TABLE nchm_table;
}DEVICE_TABLES;

//-----------------------------------------------------------------------------
//Коды ошибок
enum _TAG_TABLE_ERRORS
{
	TABLES_NO_ERROR = 0,
	TABLES_ERROR_READ_FILE = 1,
	TABLES_ERROR_WRITE_FILE = 2,
	TABLES_ERROR_READ_MODULE = 3,
	TABLES_ERROR_WRITE_MODULE = 4,
	TABLES_ERROR_DATA = 5
};

//-----------------------------------------------------------------------------

class AskuTableFile : public XmlFile
{
	virtual bool checkContent();

	QVariantMap makeHeader(QDomElement tag_table);

	QDomDocument makeDomDocument(QString strType);
	QDomElement makeDomTableMode(QDomDocument & doc, QVariantMap data);
	QDomElement makeDomTableSwitch(QDomDocument & doc, QVariantMap data);
	QDomElement makeDomTableRipch(QDomDocument & doc, QVariantMap data);
	QDomElement makeDomTableDisable(QDomDocument & doc, QVariantMap data);
	QDomElement makeDomHeader(QDomDocument & doc, QVariantMap header);

	QDomDocument makeDomModeTable(QVariantMap data);
	QDomDocument makeDomSwitchTable(QVariantMap data);
	QDomDocument makeDomRipchTable(QVariantMap data);
	QDomDocument makeDomDisableTable(QVariantMap data);

public:

	enum TableError
	{
		NoError = 0,
		ErrorOpen = 1,
		ErrorData = 2,
	};

	AskuTableFile(QString filename = QString());
	bool loadFile(QString filename);
	bool saveFile(QString filename);

	QVariantMap makeModeTable();
	QVariantMap makeSwitchTable();
	QVariantMap makeRipchTable();
	QVariantMap makeDisableTable();
	QVariantMap makeDynamicTable(AskuSektorTable data = AskuSektorTable());

	bool saveXmlModeTable(QString filename, QVariantMap table);
	bool saveXmlSwitchTable(QString filename, QVariantMap table);
	bool saveXmlRipchTable(QString filename, QVariantMap table);
	bool saveXmlDisableTable(QString filename, QVariantMap table);
};

//-----------------------------------------------------------------------------

class DASD_TABLES
{
	qreal m_temparature;
	quint32 m_temp_index;
	quint32 m_survey_index;

	bool m_loaded_ripch;
	bool m_loaded_mode;
	bool m_loaded_switch;
	bool m_loaded_nchm;
	bool m_loaded_disable;
	bool m_loaded_dynamic;

	RIPCH_TABLE ripch_table;
	SWITCH_TABLE switch_table;
	MODE_TABLE mode_table;
	NCHM_TABLE nchm_table;
	DISABLE_TABLE disable_table;
	DISABLE_TABLE dynamic_table;

	QVariantMap ripchTableMap;
	QVariantMap switchTableMap;
	QVariantMap modeTableMap;
	QVariantMap disableTableMap;
	QVariantMap dynamicTableMap;

public:
	DASD_TABLES();

	bool isLoaded();
	bool isLoadedRipch();
	bool isLoadedMode();
	bool isLoadedSwitch();
	bool isLoadedNchm();
	bool isLoadedDisable();
	bool isLoadedDynamic();

	bool setTemperature(qreal t);
	bool setSurvey(quint32 n);

	qint32 loadRipch(QString name);
	qint32 loadMode(QString name);
	qint32 loadSwitch(QString name);
	qint32 loadNchm(QString name);
	qint32 loadDisable(QString name);
	qint32 loadDynamic(QString name);

	bool prepareTables();
	bool prepareMode();
	bool prepareRipch();
	bool prepareSwitch();
	bool prepareDisable();
	bool prepareDynamic();
	bool combineDisableSwitchDynamic();

	bool saveRipch(QString name);
	bool saveMode(QString name);
	bool saveSwitch(QString name);
	bool saveNchm(QString name);
	bool saveDisable(QString name);
	bool saveDynamic(QString name);

	void *data_ripch();
	void *data_mode();
	void *data_switch();
	void *data_nchm();

	QVariantMap tableRipch();
	QVariantMap tableMode();
	QVariantMap tableSwitch();
	QVariantMap tableDisable();
	QVariantMap tableDynamic();

	void setRipch(QVariantMap table);
	void setMode(QVariantMap table);
	void setSwitch(QVariantMap table);
	void setDisable(QVariantMap table);
	void setDynamic(QVariantMap table);
	bool setDynamic(AskuSektorTable data);

	bool compareDynamicTable(QVariantMap table);

	static quint32 mapToBool(QString name, QVariantMap & headerMap, QVariant & dataList);
	static quint32 mapToUInt(QString name, QVariantMap & headerMap, QVariant & dataList);
	static qint32 mapToInt(QString name, QVariantMap & headerMap, QVariant & dataList);
	static double mapToDouble(QString name, QVariantMap & headerMap, QVariant & dataList);
};

//-----------------------------------------------------------------------------

#endif // __DASD_TABLES_H__
