#include "../common/logger.h"
#include "../common/stateset.h"
#include "globalvar.h"
#include "canalasku.h"
#include "canalasku_phase.h"

// ------------------------------------------------------------------
AskuPhaseCodes::AskuPhaseCodes()
{
	m_loaded = false;

	for(qint32 p = 0; p < CA_N_TRANSMITTERS; p++)
		for(qint32 m = 0; m < CA_N_MODULES_UMI; m++)
		{
			codes[p][m] = 0xff;
		}
}

// ------------------------------------------------------------------
void AskuPhaseCodes::dump()
{
	qDebug("AskuPhaseCodes: loaded = %d", m_loaded);
	for(qint32 p = 0; p < CA_N_TRANSMITTERS; p++)
	{
		QString str = QString("PRD[%1]: ").arg(p + 1);

		for(qint32 m = 0; m < CA_N_MODULES_UMI; m++)
		{
			str += QString("%1").arg((quint32)codes[p][m],2,10,QChar('0')) + QString(" ");
		}
		qDebug("%s", qPrintable(str));
	}
}

// ------------------------------------------------------------------
bool AskuPhaseCodes::save(QString fileName)
{
	QFile phf(fileName);

	if(phf.open(QIODevice::WriteOnly))
	{
		QTextStream phfs(&phf);

		for(qint32 p = 0; p < CA_N_TRANSMITTERS; p++)
		{
			phfs << QString("PRD%1: ").arg(p+1);
	
			for(qint32 m = 0; m < CA_N_MODULES_UMI; m++)
			{
				phfs << QString("%1").arg(codes[p][m],2,10);

				if(m == (CA_N_MODULES_UMI - 1))
					 phfs << endl;
				else
					 phfs << ", ";
			}
		}

		phf.close();
		return true;
	}

	return false;
}

// ------------------------------------------------------------------
bool AskuPhaseCodes::load(QString fileName)
{
	bool success = true;
	QFile phf(fileName);
	if(phf.open(QIODevice::ReadOnly))
	{
		QTextStream phfs(&phf);
		for(qint32 p = 0; p < CA_N_TRANSMITTERS; p++)
		{
			QString str = phfs.readLine();
			if(str.isNull())
			{
				success = false;
				break;
			}

			QStringList list = str.split(":");
			if(list.count() != 2)
			{
				success = false;
				break;
			}

			if(list[0] != QString("PRD%1").arg(p+1))
			{
				success = false;
				break;
			}

			QStringList vlist = list[1].split(",");
			if((int)vlist.count() != CA_N_MODULES_UMI)
			{
				success = false;
				break;
			}

			for(qint32 m = 0; m < CA_N_MODULES_UMI && m < vlist.count(); m++)
			{
				vlist[m] = vlist[m].simplified();
				if(!vlist[m].isEmpty())
				{
					bool ok = false;
					unsigned int value = vlist[m].toUInt(&ok,10);
					if(!ok)
					{
						success = false;
						codes[p][m] = 0xff;
					}
					else
					{
						codes[p][m] = value;
					}
				}
				else
				{
					success = false;
					codes[p][m] = 0xff;
				}
			}
		}
	}

	m_loaded = success;

	return success;
}

// ------------------------------------------------------------------
void CanalAsku::loadPhaseFile()
{
	QString fileName = QDir::toNativeSeparators(m_setup.path.phase + "/" + m_setup.phase.fileCurrent);
	if(!phaseCodes.load(fileName))
	{
		LogError("CanalAsku: error load current phase file (%s)", qPrintable(fileName));

		QString fileNameEtalon = QDir::toNativeSeparators(m_setup.path.phase + "/" + m_setup.phase.fileEtalon);
		if(!phaseCodes.load(fileNameEtalon))
		{
			LogError("CanalAsku: error load etalon phase file (%s)", qPrintable(fileNameEtalon));
			return;
		}
	}

	phaseCodes.dump();
}

// ------------------------------------------------------------------
void CanalAsku::savePhaseFile()
{
	QString fileName = QDir::toNativeSeparators(m_setup.path.phase + "/" + m_setup.phase.fileCurrent);
	if(!phaseCodes.save(fileName))
	{
		LogError("CanalAsku: error save phase file (%s)", qPrintable(fileName));
	}
}

// ------------------------------------------------------------------
void CanalAsku::setPhaseMap(QVariantMap map)
{
	PRD_COMMAND xmtCmd = prdCmd;
	QVariantList prd;
	qint32 n_module;
	bool wasSet1 = false, wasSet2 = false;

	prd = map["prd1"].toList();
	n_module = 0;

	foreach(QVariant val, prd)
	{
		if(n_module < CA_N_MODULES_UMI && !val.isNull())
		{
			bool ok = false;
			quint32 value = val.toUInt(&ok);
			if(ok)
			{
				xmtCmd.prd[0].b3.module[n_module].BitsN.writePhase = 1;
				xmtCmd.prd[0].b4.module[n_module].BitsN.module = n_module+1;
				xmtCmd.prd[0].b5.module[n_module].BitsN.phase = (unsigned char)value;
				phaseCodes.setValue(0, n_module, value);
				wasSet1 = true;
			}
		}
		n_module++;
	}

	prd = map["prd2"].toList();
	n_module = 0;

	foreach(QVariant val, prd)
	{
		if(n_module <= CA_N_MODULES_UMI && !val.isNull())
		{
			bool ok = false;
			quint32 value = val.toUInt(&ok);
			if(ok)
			{
				xmtCmd.prd[1].b3.module[n_module].BitsN.writePhase = 1;
				xmtCmd.prd[1].b4.module[n_module].BitsN.module = n_module+1;
				xmtCmd.prd[1].b5.module[n_module].BitsN.phase = (unsigned char)value;
				phaseCodes.setValue(1, n_module, value);
				wasSet2 = true;
			}
		}
		n_module++;
	}

	if(wasSet1 || wasSet2)
	{
		setCommandPrd(xmtCmd);
		if(wasSet1)
			setCheckModules(0, 30000);
		if(wasSet2)
			setCheckModules(1, 30000);
		syncToSlave();
		savePhaseFile();
	}
}

// ------------------------------------------------------------------
void CanalAsku::slotStartPhasing(int n_prd, int n_module, bool avto)
{
	LogInfo("CanalAsku: startPhasing n_prd=%d n_module=%d avto=%d", n_prd, n_module, avto);
}

// ------------------------------------------------------------------
void CanalAsku::slotStopPhasing()
{
	LogInfo("CanalAsku: stopPhasing");
}

// ------------------------------------------------------------------






//----------------------------------------------------------------------------------------------------------------
ModulePhasing::ModulePhasing(QObject * parent) : QObject(parent)
{
	waitCounter = 0;
	progressNow = 0;
	progressAll = 0;
	avtoOsc = true;

	qPhasingState = -1;
	phase_errorCode = 0;
	phase_queryPrd = 0;
	phase_queryMod = 0;

	values.clear();
	current = -1;
	connect(&timer,SIGNAL(timeout()),this,SLOT(timeout()));
}

//----------------------------------------------------------------------------------------------------------------
ModulePhasing::~ModulePhasing()
{
}

//----------------------------------------------------------------------------------------------------------------
void ModulePhasing::start(int n_prd, int n_module, bool avto)
{
	qDebug("ModulePhasing: start (%d,%d)", n_prd, n_module);

	values.clear();
	avtoOsc = avto;

	for(int p = 1; p <= CA_N_TRANSMITTERS; p++)
	{
		if(CanalAsku::isAllPrds(n_prd) || CanalAsku::isExactPrd(n_prd,p))
		{
			for(int m = 1; m <= CA_N_MODULES_UMI; m++)
			{
//				qDebug("%d %d %d",isAllModules(n_module), isExactModule(n_module,m), isHalfModule(n_module,m) );
				if(CanalAsku::isAllModules(n_module) || CanalAsku::isExactModule(n_module,m-1) || CanalAsku::isHalfModule(n_module,m-1))
				{
					values.append(ModulePhaseValue(p, m, -1, 0.0));
				}
			}
		}
	}

	if(values.count() > 0)
	{
		current = 0;

		waitCounter = 0;
		progressNow = 0;
		progressAll = values.count();

		emit sigProgress(0);
		emit sigPhaseUpdate();
		emit sigStatus(0, "Начало фазировки.");
		emit sigShowDlg(avtoOsc);

		qPhasingState = 0;
		emit phasingState(qPhasingState);

//		if(avtoOsc)
//			cw->osc->init(m_setup.phase.ip, m_setup.phase.port);
	}
	else
	{
		current = -1;
		progressNow = 0;
		progressAll = 0;

//		if(avtoOsc)
//			cw->osc->close();
	}
}

//----------------------------------------------------------------------------------------------------------------
void ModulePhasing::stop()
{
	qDebug("ModulePhasing: stop");
	current = -1;
	qPhasingState = -1;
	emit phasingState(qPhasingState);

//	if(avtoOsc)
//		cw->osc->close();
}

//----------------------------------------------------------------------------------------------------------------
void ModulePhasing::next(double value)
{
	Q_UNUSED(value);
	qDebug("ModulePhasing: next");

	if((current < 0) || (current >= values.count()))
	{
		qDebug("ModulePhasing: invalid current state");
		return;
	}
}

//----------------------------------------------------------------------------------------------------------------
bool ModulePhasing::isAvto()
{
	return avtoOsc;
}

//----------------------------------------------------------------------------------------------------------------
void ModulePhasing::status(int status, bool reset)
{
	bool ok = false;
//	qDebug("ModulePhasing: status (%d)", status);

	if(reset)
		waitCounter = 0;
	else
		waitCounter++;

	switch(status)
	{
		case 0:
		case 1:
			emit sigStatus(0, QString("Начало измерения фазы. Опрос состояния передатчика. (%1)").arg(waitCounter));
			break;

		case 2:
		case 3:
			emit sigStatus(0, QString("Начало измерения фазы. Опрос состояния модулей. (%1)").arg(waitCounter));
			break;

		case 4:
			if(!avtoOsc)
			{
				qPhasingState++;
				emit phasingState(qPhasingState);
			}
			else
			{
				emit sigStatus(0, QString("Начало измерения фазы. Проверка соединения с ПО Осциллограф."));
				if(/*cw->osc->ready()*/0)
				{
					qPhasingState++;
					emit phasingState(qPhasingState);
				}
				else
				{
					qPhasingState = 202;
					phase_errorCode = 202;
					emit phasingState(qPhasingState, phase_errorCode);
				}
			}
			break;

		case 6:
		case 7:
			emit sigStatus(0, QString("Начало измерения фазы. Установка начального состояния передатчика. (%1)").arg(waitCounter));
			break;

		case 8:
		case 9:
			emit sigStatus(0, QString("Начало измерения фазы. Опрос состояния передатчика. (%1)").arg(waitCounter));
			break;

		case 10:
			emit sigStatus(0, QString("Готов к измерению фазы."));
			emit sigProgress(100 * current / values.count());

			phase_queryPrd = values[current].n_prd;
			phase_queryMod = values[current].n_module;
			qPhasingState++;
			emit phasingState(qPhasingState);

			break;

		case 11:
		case 12:
			emit sigStatus(0, QString("Включение модуля ПРД-%1 УМИ-%2. (%3)").arg(phase_queryPrd).arg(phase_queryMod).arg(waitCounter));
			break;

		case 13:
			emit sigStatus(3, QString("Модуль включен ПРД-%1 УМИ-%2. Введите измеренное значение фазы").arg(phase_queryPrd).arg(phase_queryMod));
			emit sigPhaseUpdate(phase_queryPrd, phase_queryMod, avtoOsc);
			break;

		case 23:
			emit sigStatus(6, QString("Модуль включен ПРД-%1 УМИ-%2. Измерение фазы").arg(phase_queryPrd).arg(phase_queryMod));
			emit sigPhaseUpdate(phase_queryPrd, phase_queryMod, avtoOsc);
			if(0/*cw->osc->start(100,100,5000)*/)
			{
				qPhasingState = 100;//end
				phase_errorCode = 202;
				emit phasingState(qPhasingState, phase_errorCode);
			}
			break;

		case 24:
			emit sigStatus(6, QString("Модуль включен ПРД-%1 УМИ-%2. Измерение фазы. (%3)").arg(phase_queryPrd).arg(phase_queryMod).arg(waitCounter));
			if(1/*!cw->osc->ready()*/)
				emit sigOscPhase(0/*cw->osc->rawValue(&ok)*/, ok);
			else
			{
				if(/*cw->osc->success()*/0)
				{
					if(1/*cw->osc->valid()*/)
					{
						double val = 0/*cw->osc->value()*/;
						emit sigOscPhase(val, true);
						emit sigPhaseValue(phase_queryPrd-1, phase_queryMod-1, val);
						qPhasingState = 14;
						emit phasingState(qPhasingState);
					}
					else
					{
						qPhasingState = 100;//end
						phase_errorCode = 203;
						emit phasingState(qPhasingState, phase_errorCode);
					}
				}
				else
				{
					qPhasingState = 100;//end
					phase_errorCode = 202;
					emit phasingState(qPhasingState, phase_errorCode);
				}
			}
			break;

		case 14:
		case 15:
			emit sigStatus(0, QString("Отключение модуля ПРД-%1 УМИ-%2. (%3)").arg(phase_queryPrd).arg(phase_queryMod).arg(waitCounter));
			break;

		case 16:
			emit sigStatus(0, QString("Готов к измерению фазы."));
			emit sigProgress(100 * current / values.count());

			current++;
			if(current >= values.count())
			{
				qPhasingState = 100;
				emit phasingState(qPhasingState);
			}
			else
			{
				qPhasingState++;
				emit phasingState(qPhasingState);
			}

			break;

		case 18:
			emit sigStatus(5, QString("Модуль не включился ПРД-%1 УМИ-%2. Нажмите \"Далее\"").arg(phase_queryPrd).arg(phase_queryMod));
			emit sigPhaseUpdate();
			break;

		case 20:
			emit sigStatus(5, QString("Модуль не отключился ПРД-%1 УМИ-%2. Нажмите \"Далее\"").arg(phase_queryPrd).arg(phase_queryMod));
			emit sigPhaseUpdate();
			break;

		case 100:
		case 101:
//			if(avtoOsc)
//				cw->osc->stop();
			emit sigStatus(0, QString("Завершение измерения фазы. Отключение передатчика. (%1)").arg(waitCounter));
			emit sigPhaseUpdate();
			break;

		case 102:
			emit sigStatus(2, QString("Завершено. Нажмите кнопку \"Закрыть\""));
			emit sigProgress(100);
			break;

		case 201:
			emit sigStatus(2, QString("Завершено с ошибкой (нет ответа по каналу RS). Нажмите кнопку \"Закрыть\""));
			emit sigProgress(100);
			break;

		case 202:
			emit sigStatus(2, QString("Завершено с ошибкой (нет ответа от ПО Осциллограф). Нажмите кнопку \"Закрыть\""));
			emit sigProgress(100);
			break;

		case 203:
			emit sigStatus(2, QString("Завершено с ошибкой (Нестабильное значение фазы). Нажмите кнопку \"Закрыть\""));
			emit sigProgress(100);
			break;
	}
}

//----------------------------------------------------------------------------------------------------------------
void ModulePhasing::timeout()
{
}

//----------------------------------------------------------------------------------------------------------------
void ModulePhasing::slotNext(int n_prd, int n_module, double value)
{
	qDebug("n_prd=%d n_mod=%d phase=%f", n_prd, n_module, value);
	if(n_prd && n_module)
		emit sigPhaseValue(n_prd-1, n_module-1, value);
	qPhasingState++;
	emit phasingState(qPhasingState);
}

//----------------------------------------------------------------------------------------------------------------
void ModulePhasing::slotCancel()
{
	if(qPhasingState == -1)
	{
		emit sigHideDlg();
	}
	else
	{
		if(qPhasingState < 6)
			qPhasingState = 102;
		else if(qPhasingState < 100)
			qPhasingState = 100;

		emit phasingState(qPhasingState);
	}
}

//----------------------------------------------------------------------------------------------------------------
void ModulePhasing::slotStart(int n_prd, int n_module, bool avto)
{
	start(n_prd, n_module, avto);
}

//----------------------------------------------------------------------------------------------------------------
void ModulePhasing::slotStop()
{
	stop();
}

//----------------------------------------------------------------------------------------------------------------
