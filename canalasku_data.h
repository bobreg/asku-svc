#ifndef _CANALASKU_DATA_H_
#define _CANALASKU_DATA_H_

//-------------------------------------------------------------------

#include <QList>
#include <QVariantMap>
#include <QMutex>
#include <QDateTime>
#include "canalasku_defines.h"

//-------------------------------------------------------------------

class CanalAskuData
{
	quint32 ulCount;

	quint32 portActive;
	quint8 portStatus1;
	quint8 portStatus2;

	quint8 bUpdatedUmi[CA_N_DEVICES][CA_N_MODULES_UMI];

	quint8 bTest1[CA_N_DEVICES][CA_HEADER_TEST1_N_BYTES];
	quint8 bTest1Error[CA_N_DEVICES];

	quint8 bTest2[CA_N_DEVICES][CA_HEADER_TEST2_N_BYTES];
	quint8 bTest2Error[CA_N_DEVICES];

	quint8 bCommand[CA_N_DEVICES][CA_HEADER_COMMAND_N_BYTES];
	quint8 bCommandError[CA_N_DEVICES];

	quint8 bCommandUmi[CA_N_DEVICES][CA_N_MODULES_UMI][CA_HEADER_COMMAND_MODULES_N_BYTES];
	quint8 bCommandUmiError[CA_N_DEVICES][CA_N_MODULES_UMI];

	quint8 bState[CA_N_DEVICES][CA_HEADER_STATE_N_BYTES];
	quint8 bStateError[CA_N_DEVICES];

	quint8 bParamUmi[CA_N_DEVICES][CA_N_MODULES_UMI][CA_HEADER_DC_MAX_N_BYTES];
	quint8 bParamUmiError[CA_N_DEVICES][CA_N_MODULES_UMI];

public:
	CanalAskuData();
	CanalAskuData(const QVariantMap & data);

	~CanalAskuData();

	void clear();

	bool fromMap(const QVariantMap & data);
	QVariantMap toMap() const;

	quint32 checkCompare(quint8 device, CanalAskuData *data) const;
	quint32 checkCompareUMI(CanalAskuData *data) const;

	void clearTest1Error(quint8 device);
	void setTest1Error(quint8 device, quint8 value);
	quint8 getTest1Error(quint8 device) const;
	void clearTest1(quint8 device);
	void setTest1(quint8 device, quint8 offset, quint8 value);
	void setTest1(quint8 device, quint8 *data, quint8 size);
	quint8 getTest1(quint8 device, quint8 offset) const;

	void clearTest2Error(quint8 device);
	void setTest2Error(quint8 device, quint8 value);
	quint8 getTest2Error(quint8 device) const;
	void clearTest2(quint8 device);
	void setTest2(quint8 device, quint8 *data, quint8 size);
	quint8 getTest2(quint8 device, quint8 offset) const;

	void clearCommandError(quint8 device);
	void setCommandError(quint8 device, quint8 value);
	quint8 getCommandError(quint8 device) const;
	void clearCommand(quint8 device);
	void setCommand(quint8 device, quint8 offset, quint8 value);
	void setCommand(quint8 device, quint8 *data, quint8 size);
	quint8 getCommand(quint8 device, quint8 offset) const;

	void clearStateError(quint8 device);
	void setStateError(quint8 device, quint8 value);
	quint8 getStateError(quint8 device) const;
	void clearState(quint8 device);
	void setState(quint8 device, quint8 *data, quint8 size);
	quint8 getState(quint8 device, quint8 offset, quint8 *data, quint8 size) const;
	quint8 getState(quint8 device, quint8 offset) const;

	void clearParamUmiError(quint8 device, quint8 umi);
	void setParamUmiError(quint8 device, quint8 umi, quint8 value);
	quint8 getParamUmiError(quint8 device, quint8 umi) const;
	void clearParamUmi(quint8 device, quint8 umi);
	void setParamUmi(quint8 device, quint8 umi, quint8 *data, quint8 size);
	quint8 getParamUmi(quint8 device, quint8 umi, quint8 *data, quint8 size) const;
	quint8 getParamUmi(quint8 device, quint8 umi, quint8 offset) const;

	void clearCommandUmi(quint8 device, quint8 module);
	void setCommandUmi(quint8 device, qint8 module, quint8 *data, quint8 size);
	quint8 getCommandUmi(quint8 device, quint8 module, quint8 offset) const;
	void clearCommandUmiError(quint8 device, quint8 module);
	void setCommandUmiError(quint8 device, quint8 module, quint8 value);
	quint8 getCommandUmiError(quint8 device, quint8 module) const;

	void incCount();
	quint32 getCount() const;

	void setPortActive(quint32 active);
	quint32 getPortActive() const;

	quint8 getPort1Status() const;
	quint8 getPort2Status() const;
	void setPortStatus(quint8 status1, quint8 status2);

	void setUpdatedUmi(quint8 device, quint8 umi);
	quint8 getUpdatedUmi(quint8 device, quint8 umi) const;
	void resetUpdatedUmi();
};

//-------------------------------------------------------------------

class CanalAskuCommand
{
	QList<CA_TYPE_COMMAND> commandQueue[CA_N_DEVICES];
	QDateTime m_timeLastCommand[CA_N_DEVICES];
	QMutex m_mutex;

public:
	CanalAskuCommand();
	~CanalAskuCommand();

	void append(quint8 device, CA_TYPE_COMMAND value);
	bool extract(quint8 device, CA_TYPE_COMMAND* value);
	bool extractByTime(quint8 device, CA_TYPE_COMMAND* value);
	void append(CanalAskuCommand *newCommand);
	void flush();

	QString dump() const;
};

//-------------------------------------------------------------------

#endif //_CANALASKU_DATA_H_
