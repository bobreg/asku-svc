#include "../common/logger.h"
#include "globalvar.h"
#include "canalasku_data.h"

//--------------------------------------------------------------
CanalAskuData::CanalAskuData()
{
	clear();
}

//--------------------------------------------------------------
CanalAskuData::CanalAskuData(const QVariantMap & map)
{
	clear();
	fromMap(map);
}

//--------------------------------------------------------------
CanalAskuData::~CanalAskuData()
{
}

//--------------------------------------------------------------
void CanalAskuData::clear()
{
	ulCount = 0;
	portActive = 0;
	portStatus1 = portStatus2 = ELEM_NOT;
	memset(bCommand,0,sizeof(bCommand));
	memset(bCommandError,CA_ERROR_NO_DATA,sizeof(bCommandError));
	memset(bState,0,sizeof(bState));
	memset(bStateError,CA_ERROR_NO_DATA,sizeof(bStateError));
	memset(bTest1,0,sizeof(bTest1));
	memset(bTest1Error,CA_ERROR_NO_DATA,sizeof(bTest1Error));
	memset(bTest2,0,sizeof(bTest2));
	memset(bTest2Error,CA_ERROR_NO_DATA,sizeof(bTest2Error));
	memset(bParamUmi,0,sizeof(bParamUmi));
	memset(bParamUmiError,CA_ERROR_NO_DATA,sizeof(bParamUmiError));
	memset(bCommandUmi,0,sizeof(bCommandUmi));
	memset(bCommandUmiError,0,sizeof(bCommandUmi));
	memset(bUpdatedUmi,0,sizeof(bUpdatedUmi));
}

//--------------------------------------------------------------
void CanalAskuData::incCount()
{
	resetUpdatedUmi();
	ulCount++;
}

//--------------------------------------------------------------
quint32 CanalAskuData::getCount() const
{
	return ulCount;
}

//--------------------------------------------------------------
void CanalAskuData::setPortActive(quint32 active)
{
	portActive = active;
}

//--------------------------------------------------------------
quint32 CanalAskuData::getPortActive() const
{
	return portActive;
}

//--------------------------------------------------------------
quint8 CanalAskuData::getPort1Status() const
{
	return portStatus1;
}

//--------------------------------------------------------------
quint8 CanalAskuData::getPort2Status() const
{
	return portStatus2;
}

//--------------------------------------------------------------
void CanalAskuData::setPortStatus(quint8 status1, quint8 status2)
{
	portStatus1 = status1;
	portStatus2 = status2;
}

//--------------------------------------------------------------
void CanalAskuData::clearState(quint8 device)
{
	clearStateError(device);
	if(device < CA_N_DEVICES)
		memset(bState[device], 0, CA_HEADER_STATE_N_BYTES);
}

//--------------------------------------------------------------
void CanalAskuData::setState(quint8 device, quint8 *data, quint8 size)
{
	Q_UNUSED(size);
	if(device < CA_N_DEVICES && size <= CA_HEADER_STATE_N_BYTES)
		memcpy(bState[device], data, size);
}

//--------------------------------------------------------------
quint8 CanalAskuData::getState(quint8 device, quint8 offset) const
{
	if(device < CA_N_DEVICES && offset < CA_HEADER_STATE_N_BYTES)
		return bState[device][offset];
	else
		return 0;
}

//--------------------------------------------------------------
quint8 CanalAskuData::getState(quint8 device, quint8 offset, quint8 *data, quint8 size) const
{
	if(device < CA_N_DEVICES && (offset + size) < CA_HEADER_STATE_N_BYTES)
	{
		memcpy(data, &bState[device][offset], size);
		return size;
	}
	return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearStateError(quint8 device)
{
	if(device < CA_N_DEVICES)
		bStateError[device] = CA_ERROR_NO_DATA;
}

//--------------------------------------------------------------
void CanalAskuData::setStateError(quint8 device, quint8 value)
{
	if(device < CA_N_DEVICES)
		bStateError[device] = value;
}

//--------------------------------------------------------------
quint8 CanalAskuData::getStateError(quint8 device) const
{
	if(device < CA_N_DEVICES)
		return bStateError[device];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearParamUmiError(quint8 device, quint8 umi)
{
	if(device < CA_N_DEVICES && umi < CA_N_MODULES_UMI)
		bParamUmiError[device][umi] = CA_ERROR_NO_DATA;
}

//--------------------------------------------------------------
void CanalAskuData::setParamUmiError(quint8 device, quint8 umi, quint8 value)
{
	if(device < CA_N_DEVICES && umi < CA_N_MODULES_UMI)
	{
		bParamUmiError[device][umi] = value;
		setUpdatedUmi(device, umi);
	}
}

//--------------------------------------------------------------
quint8 CanalAskuData::getParamUmiError(quint8 device, quint8 umi) const
{
	if(device < CA_N_DEVICES && umi < CA_N_MODULES_UMI)
		return bParamUmiError[device][umi];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearParamUmi(quint8 device, quint8 umi)
{
	if(device < CA_N_DEVICES && umi < CA_N_MODULES_UMI)
	{
		clearParamUmiError(device, umi);
		memset(bParamUmi[device][umi], 0, CA_HEADER_DC_MAX_N_BYTES);
	}
}

//--------------------------------------------------------------
void CanalAskuData::setParamUmi(quint8 device, quint8 umi, quint8 *data, quint8 size)
{
	if(device < CA_N_DEVICES && umi < CA_N_MODULES_UMI && size <= CA_HEADER_DC_MAX_N_BYTES)
	{
		memcpy(bParamUmi[device][umi],data, size);
		setUpdatedUmi(device, umi);
	}
}

//--------------------------------------------------------------
quint8 CanalAskuData::getParamUmi(quint8 device, quint8 umi, quint8 *data, quint8 size) const
{
	if(device < CA_N_DEVICES && umi < CA_N_MODULES_UMI && size <= CA_HEADER_DC_MAX_N_BYTES)
	{
		memcpy(data, bParamUmi[device][umi], size);
		return size;
	}
	return 0;
}

//--------------------------------------------------------------
quint8 CanalAskuData::getParamUmi(quint8 device, quint8 umi, quint8 offset) const
{
	if(device < CA_N_DEVICES && umi < CA_N_MODULES_UMI && offset < CA_HEADER_DC_MAX_N_BYTES)
		return bParamUmi[device][umi][offset];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearCommand(quint8 device)
{
	clearCommandError(device);
	if(device < CA_N_DEVICES)
		memset(bCommand[device], 0, CA_HEADER_COMMAND_N_BYTES);
}

//--------------------------------------------------------------
void CanalAskuData::setCommand(quint8 device, quint8 offset, quint8 value)
{
	if(device < CA_N_DEVICES && offset < CA_HEADER_COMMAND_N_BYTES)
		bCommand[device][offset] = value;
}

//--------------------------------------------------------------
void CanalAskuData::setCommand(quint8 device, quint8 *data, quint8 size)
{
	if(device < CA_N_DEVICES && size <= CA_HEADER_COMMAND_N_BYTES)
		memcpy(bCommand[device], data, size);
}

//--------------------------------------------------------------
quint8 CanalAskuData::getCommand(quint8 device, quint8 offset) const
{
	if(device < CA_N_DEVICES && offset < CA_HEADER_COMMAND_N_BYTES)
		return bCommand[device][offset];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearCommandError(quint8 device)
{
	if(device < CA_N_DEVICES)
		bCommandError[device] = CA_ERROR_NO_DATA;
}

//--------------------------------------------------------------
void CanalAskuData::setCommandError(quint8 device, quint8 value)
{
	if(device < CA_N_DEVICES)
		bCommandError[device] = value;
}

//--------------------------------------------------------------
quint8 CanalAskuData::getCommandError(quint8 device) const
{
	if(device < CA_N_DEVICES)
		return bCommandError[device];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearCommandUmi(quint8 device, quint8 module)
{
	clearCommandUmiError(device, module);
	if(device < CA_N_DEVICES && module < CA_N_MODULES_UMI)
		memset(bCommandUmi[device][module], 0, CA_HEADER_COMMAND_MODULES_N_BYTES);
}

//--------------------------------------------------------------
void CanalAskuData::setCommandUmi(quint8 device, qint8 module, quint8 *data, quint8 size)
{
	if(device < CA_N_DEVICES && module < CA_N_MODULES_UMI && size <= CA_HEADER_COMMAND_MODULES_N_BYTES)
		memcpy(bCommandUmi[device][module], data, size);
}

//--------------------------------------------------------------
quint8 CanalAskuData::getCommandUmi(quint8 device, quint8 module, quint8 offset) const
{
	if(device < CA_N_DEVICES && module < CA_N_MODULES_UMI && offset < CA_HEADER_COMMAND_MODULES_N_BYTES)
		return bCommandUmi[device][module][offset];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearCommandUmiError(quint8 device, quint8 module)
{
	if(device < CA_N_DEVICES && module < CA_N_MODULES_UMI)
		bCommandUmiError[device][module] = CA_ERROR_NO_DATA;
}

//--------------------------------------------------------------
void CanalAskuData::setCommandUmiError(quint8 device, quint8 module, quint8 value)
{
	if(device < CA_N_DEVICES && module < CA_N_MODULES_UMI)
		bCommandUmiError[device][module] = value;
}

//--------------------------------------------------------------
quint8 CanalAskuData::getCommandUmiError(quint8 device, quint8 module) const
{
	if(device < CA_N_DEVICES && module < CA_N_MODULES_UMI)
		return bCommandUmiError[device][module];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearTest1(quint8 device)
{
	clearTest1Error(device);
	if(device < CA_N_DEVICES)
		memset(bTest1[device], 0, CA_HEADER_TEST1_N_BYTES);
}

//--------------------------------------------------------------
void CanalAskuData::setTest1(quint8 device, quint8 offset, quint8 value)
{
	if(device < CA_N_DEVICES && offset < CA_HEADER_TEST1_N_BYTES)
		bTest1[device][offset] = value;
}

//--------------------------------------------------------------
void CanalAskuData::setTest1(quint8 device, quint8 *data, quint8 size)
{
	if(device < CA_N_DEVICES && size <= CA_HEADER_TEST1_N_BYTES)
		memcpy(bTest1[device], data, size);
}

//--------------------------------------------------------------
quint8 CanalAskuData::getTest1(quint8 device, quint8 offset) const
{
	if(device < CA_N_DEVICES)
		return bTest1[device][offset];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearTest1Error(quint8 device)
{
	if(device < CA_N_DEVICES)
		bTest1Error[device] = CA_ERROR_NO_DATA;
}

//--------------------------------------------------------------
void CanalAskuData::setTest1Error(quint8 device, quint8 value)
{
	if(device < CA_N_DEVICES)
		bTest1Error[device] = value;
}

//--------------------------------------------------------------
quint8 CanalAskuData::getTest1Error(quint8 device) const
{
	if(device < CA_N_DEVICES)
		return bTest1Error[device];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearTest2(quint8 device)
{
	clearTest2Error(device);
	if(device < CA_N_DEVICES)
		memset(bTest2[device], 0, CA_HEADER_TEST2_N_BYTES);
}

//--------------------------------------------------------------
void CanalAskuData::setTest2(quint8 device, quint8 *data, quint8 size)
{
	if(device < CA_N_DEVICES && size <= CA_HEADER_TEST2_N_BYTES)
		memcpy(bTest2[device], data, size);
}

//--------------------------------------------------------------
quint8 CanalAskuData::getTest2(quint8 device, quint8 offset) const
{
	if(device < CA_N_DEVICES && offset < CA_HEADER_TEST2_N_BYTES)
		return bTest2[device][offset];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::clearTest2Error(quint8 device)
{
	if(device < CA_N_DEVICES)
		bTest2Error[device] = CA_ERROR_NO_DATA;
}

//--------------------------------------------------------------
void CanalAskuData::setTest2Error(quint8 device, quint8 value)
{
	if(device < CA_N_DEVICES)
		bTest2Error[device] = value;
}

//--------------------------------------------------------------
quint8 CanalAskuData::getTest2Error(quint8 device) const
{
	if(device < CA_N_DEVICES)
		return bTest2Error[device];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::setUpdatedUmi(quint8 device, quint8 umi)
{
	if(device < CA_N_DEVICES && umi < CA_N_MODULES_UMI)
		bUpdatedUmi[device][umi] = 1;
}

//--------------------------------------------------------------
quint8 CanalAskuData::getUpdatedUmi(quint8 device, quint8 umi) const
{
	if(device < CA_N_DEVICES && umi < CA_N_MODULES_UMI)
		return bUpdatedUmi[device][umi];
	else
		return 0;
}

//--------------------------------------------------------------
void CanalAskuData::resetUpdatedUmi()
{
	memset(bUpdatedUmi,0,sizeof(bUpdatedUmi));
}

//--------------------------------------------------------------
quint32 CanalAskuData::checkCompare(quint8 device, CanalAskuData *data) const
{
	quint32 offset;
	quint32 diff = 0;

	if(device < CA_N_DEVICES)
	{
		for(offset = 0; offset < CA_HEADER_TEST1_N_BYTES; offset++)
			if(bTest1[device][offset] != data->getTest1(device,offset))	diff |= 0x00000001;
		if(bTest1Error[device] != data->getTest1Error(device))		diff |= 0x00000001;

		for(offset = 0; offset < CA_HEADER_TEST2_N_BYTES; offset++)
			if(bTest2[device][offset] != data->getTest2(device,offset))	diff |= 0x00000002;
		if(bTest2Error[device] != data->getTest2Error(device))		diff |= 0x00000002;

		for(offset = 0; offset < CA_HEADER_TEST2_N_BYTES; offset++)
			if(bCommand[device][offset] != data->getCommand(device,offset))	diff |= 0x00000004;
		if(bCommandError[device] != data->getCommandError(device))	diff |= 0x00000004;

		for(offset = 0; offset < CA_HEADER_STATE_N_BYTES; offset++)
			if(bState[device][offset] != data->getState(device,offset))	diff |= 0x00000008;
		if(bStateError[device] != data->getStateError(device)) diff |= 0x00000008;
	}

	return diff;
}

//--------------------------------------------------------------
quint32 CanalAskuData::checkCompareUMI(CanalAskuData *data) const
{
	quint32 device, module, offset;
	quint32 diff = 0;

	for(device = 0; device < CA_N_DEVICES; device++)
	{
		for(module = 0; module < CA_N_MODULES_UMI; module++)
		{
			for(offset = 0; offset < CA_HEADER_DC_MAX_N_BYTES; offset++)
				if(bParamUmi[device][module][offset] != data->getParamUmi(device, module, offset)) diff |= (1 << module);
			if(bParamUmiError[device][module] != data->getParamUmiError(device, module)) diff |= (1 << module);
		}
	}

	return diff;
}

//--------------------------------------------------------------
QVariantMap CanalAskuData::toMap() const
{
	QVariantMap data;
	QVariantList devices;
	qint32 device, module, byte;

	for(device = 0; device < CA_N_DEVICES; device++)
	{
		QVariantList modulesUmi;
		QStringList state, test1, test2;
		QString stateError, test1Error, test2Error;

		for(byte = 0; byte < CA_HEADER_STATE_N_BYTES; byte++)
			state << QString::number(bState[device][byte],16);
		stateError = QString::number(bStateError[device],16);

		for(byte = 0; byte < CA_HEADER_TEST1_N_BYTES; byte++)
			test1 << QString::number(bTest1[device][byte],16);
		test1Error = QString::number(bTest1Error[device],16);

		for(byte = 0; byte < CA_HEADER_TEST2_N_BYTES; byte++)
			test2 << QString::number(bTest2[device][byte],16);
		test2Error = QString::number(bTest2Error[device],16);

		for(module = 0; module < CA_N_MODULES_UMI; module++)
		{
			QStringList umi;
			QString umiError;

			for(byte = 0; byte < CA_HEADER_DC_MAX_N_BYTES; byte++)
				umi << QString::number(bParamUmi[device][module][byte],16);
			umiError = QString::number(bParamUmiError[device][module],16);

			QVariantMap umis;
			umis["Module"] = module;
			umis["Name"] = QString("УМИ-%1").arg(module + 1);
			umis["UmiInfo"] = umi;
			umis["UmiError"] = umiError;

			modulesUmi << umis;
		}

		QVariantMap dev;

		dev["StateInfo"] = state;
		dev["StateError"] = stateError;
		dev["Test1Info"] = test1;
		dev["Test1Error"] = test1Error;
		dev["Test2Info"] = test2;
		dev["Test2Error"] = test2Error;

		dev["Device"] = device;

		switch(device)
		{
			case 0:
				dev["Name"] = "124УУ08";
				dev["Address"] = addr124YY08;
				break;
			case 1:
				dev["Name"] = "124УГ02-1";
				dev["Address"] = addr124YG02G1;
				dev["Modules"] = modulesUmi;
				break;
			case 2:
				dev["Name"] = "124УГ02-2";
				dev["Address"] = addr124YG02G2;
				dev["Modules"] = modulesUmi;
				break;
		}

		devices << dev;
	}

	data["Devices"] = devices;

	return data;
}

//--------------------------------------------------------------
bool CanalAskuData::fromMap(const QVariantMap & data)
{
	bool changed = true;

	qint32 dev_index = 0;
	const QVariantList & devices = data["Devices"].toList();
	for(QVariantList::const_iterator vdev = devices.constBegin(); vdev != devices.constEnd(); ++vdev)
	{
		const QVariantMap & dev = (*vdev).toMap();
		if(dev.contains("Device"))
		{
			bool ok = false;
			qint32 device = dev["Device"].toString().toUInt(&ok);

			if(ok && device >= 0 && device < CA_N_DEVICES)
			{
				QStringList state, test1, test2;
				QString stateError, test1Error, test2Error;
				qint32 offset;
				quint32 value;

				state = dev["StateInfo"].toStringList();
				for(offset = 0; offset < CA_HEADER_STATE_N_BYTES; offset++)
				{
					value = 0;
					if(offset < state.count())
					{
						bool ok = false;
						value = state[offset].toUInt(&ok,16);
						if(!ok) value = 0;
					}
					bState[device][offset] = (quint8)value;
				}

				stateError = dev["StateError"].toString();
				value = 0;
				if(!stateError.isEmpty())
				{
					bool ok = false;
					value = stateError.toUInt(&ok,16);
					if(!ok) value = 0;
				}
				bStateError[device] = (quint8)value;

				test1 = dev["Test1Info"].toStringList();
				for(offset = 0; offset < CA_HEADER_TEST1_N_BYTES; offset++)
				{
					value = 0;
					if(offset < test1.count())
					{
						bool ok = false;
						value = test1[offset].toUInt(&ok,16);
						if(!ok) value = 0;
					}
					bTest1[device][offset] = (quint8)value;
				}

				test1Error = dev["Test1Error"].toString();
				value = 0;
				if(!test1Error.isEmpty())
				{
					bool ok = false;
					value = test1Error.toUInt(&ok,16);
					if(!ok) value = 0;
				}
				bTest1Error[device] = (quint8)value;

				test2 = dev["Test2Info"].toStringList();
				for(offset = 0; offset < CA_HEADER_TEST2_N_BYTES; offset++)
				{
					value = 0;
					if(offset < test2.count())
					{
						bool ok = false;
						value = test2[offset].toUInt(&ok,16);
						if(!ok) value = 0;
					}
					bTest2[device][offset] = (quint8)value;
				}

				test2Error = dev["Test2Error"].toString();
				value = 0;
				if(!test2Error.isEmpty())
				{
					bool ok = false;
					value = test2Error.toUInt(&ok,16);
					if(!ok) value = 0;
				}
				bTest2Error[device] = (quint8)value;

				qint32 umi_index = 0;
				const QVariantList & umis = dev["Modules"].toList();
				if(!umis.isEmpty())
				{
					for(QVariantList::const_iterator mod = umis.constBegin(); mod != umis.constEnd(); ++mod)
					{
						const QVariantMap & module = (*mod).toMap();
						if(!module.isEmpty())
						{
							const QStringList & umiInfo = module["UmiInfo"].toStringList();
							if(!umiInfo.isEmpty())
							{
								for(offset = 0; offset < CA_HEADER_DC_MAX_N_BYTES; offset++)
								{
									value = 0;
									if(offset < umiInfo.count())
									{
										bool ok = false;
										value = umiInfo[offset].toUInt(&ok,16);
										if(!ok) value = 0;
									}
									bParamUmi[device][umi_index][offset] = (quint8)value;
								}
							}

							QString umiError = module["UmiError"].toString();
							value = 0;
							if(!umiError.isEmpty())
							{
								bool ok = false;
								value = umiError.toUInt(&ok,16);
								if(!ok) value = 0;
							}
							bParamUmiError[device][umi_index] = (quint8)value;
						}

						umi_index++;
					}
				}

				dev_index++;
			}
		}
	}

	return changed;
}

//--------------------------------------------------------------
//==============================================================
CanalAskuCommand::CanalAskuCommand()
{
	for(quint32 i = 0; i < CA_N_DEVICES; i++)
		m_timeLastCommand[i] = QDateTime::currentDateTime();
}

//--------------------------------------------------------------
CanalAskuCommand::~CanalAskuCommand()
{
}

//--------------------------------------------------------------
void CanalAskuCommand::flush()
{
	m_mutex.lock();
	for(quint32 device = 0; device < CA_N_DEVICES; device++)
	{
		m_timeLastCommand[device] = QDateTime::currentDateTime();
		commandQueue[device].clear();
	}
	m_mutex.unlock();
}

//--------------------------------------------------------------
void CanalAskuCommand::append(quint8 device, CA_TYPE_COMMAND value)
{
	if(device >= CA_N_DEVICES)
		return;

//	qDebug() << "CanalAskuCommand::append : " << value.dump();

	m_mutex.lock();
	commandQueue[device].push_back(value);
	m_mutex.unlock();
}

//--------------------------------------------------------------
bool CanalAskuCommand::extract(quint8 device, CA_TYPE_COMMAND *value)
{
	if(device >= CA_N_DEVICES)
		return false;

	if(commandQueue[device].isEmpty())
		return false;

	m_mutex.lock();
	*value = commandQueue[device].first();
	commandQueue[device].pop_front();
	m_mutex.unlock();

	return true;
}

//--------------------------------------------------------------
bool CanalAskuCommand::extractByTime(quint8 device, CA_TYPE_COMMAND *value)
{
	if(device >= CA_N_DEVICES)
		return false;

	if(commandQueue[device].isEmpty())
		return false;

	m_mutex.lock();
	*value = commandQueue[device].first();
	QDateTime current = QDateTime::currentDateTime();

	qint64 timeout = m_timeLastCommand[device].msecsTo(current);
	if(timeout < (qint64)(value->timeout))
	{
		m_mutex.unlock();
		return false;
	}

	commandQueue[device].pop_front();
	m_timeLastCommand[device] = current;
	m_mutex.unlock();

	return true;
}
//--------------------------------------------------------------
void CanalAskuCommand::append(CanalAskuCommand *newCommand)
{
	CA_TYPE_COMMAND cmd;
	for(quint32 device = 0; device < CA_N_DEVICES; device++)
		while(newCommand->extract(device, &cmd))
			append(device, cmd);
}

//--------------------------------------------------------------
QString CanalAskuCommand::dump() const
{
	return QString();
}

//--------------------------------------------------------------
