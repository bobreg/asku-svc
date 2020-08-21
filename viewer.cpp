#include "../common/module.h"
#include "../common/logger.h"
#include "globalvar.h"
#include "viewer.h"

//----------------------------------------------------------------------------------------------------------------

AskuViewer *askuViewer = NULL;

//-------------------------------------------------------------------------------
AskuViewer::AskuViewer(QObject *parent) : QObject(parent)
{
	qRegisterMetaType<ErrorCodes>("ErrorCodes");

	m_logSelect.clear();

	m_logFile = new LOG_FILE;
	if(m_logFile)
	{
		connect(this, SIGNAL(changedDate()), m_logFile, SLOT(onChangedDate()));
		connect(m_logFile, SIGNAL(loadComplete(ErrorCodes)), this, SLOT(onLoadComplete(ErrorCodes)));
	}

	m_currentRequested = false;
	m_changedDate = false;

	askuViewer = this;

	m_currentDate = QDate::currentDate();
	m_currentTime = QTime::currentTime();

	m_logFile->loadFile();

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
	m_timer->start(500);
}

//-------------------------------------------------------------------------------
AskuViewer::~AskuViewer()
{
	askuViewer = NULL;
	quit();
}

// ------------------------------------------------------------------
void AskuViewer::quit()
{
	if(m_timer)
	{
		m_timer->stop();
		delete m_timer;
		m_timer = NULL;
	}
	foreach(LOG_FILE *f, m_logSelect)
	{
		if(f)
		{
			m_logSelect.removeOne(f);
			delete f;
		}
	}
	if(m_logFile)
	{
		delete m_logFile;
		m_logFile = NULL;
	}
}

// ------------------------------------------------------------------
void AskuViewer::OnTimer()
{
	QDate dt = QDate::currentDate();

	if(dt != m_currentDate)
	{
		m_currentDate = dt;
		m_changedDate = true;
		emit changedDate();
	}

	QTime tm = QTime::currentTime();
	if(tm.hour() != m_currentTime.hour())
	{
		m_currentTime = tm;
		emit changedHour();
	}

/*
	static int a = 0;
	static int x = 0;
	x++;
	if(x > 5)
	{
		x = 0;
		AddNormaMes("АСКУ", QString("test %1").arg(a++));
	}
*/
}

// ----------------------------------------------------------------------------
qint32 AskuViewer::processControlCommand(QVariantMap data)
{
	qint32 result = AskuModule::CommandNotFound;

	if(data.isEmpty())
	{
		LogError("AskuViewer: empty command data!");
		return result;
	}

	QString command = data["Command"].toString();
	QStringList parameters = data["Parameters"].toStringList();

	if(command.isEmpty())
	{
		LogError("AskuViewer: empty command");
		return result;
	}

	bool ok = false;
	quint32 numGpr = data["ToGprId"].toUInt(&ok);
	if(ok && numGpr != IDGPR())
	{
		LogError("AskuViewer: success but not mine");
		result = AskuModule::CommandSuccess;
		return result;
	}

	LogInfo("Command: %s", qPrintable(command));

	if(command == "getCurrent")
	{
		QTimer::singleShot(0, this, SLOT(makeFileContent()));
		result = AskuModule::CommandSuccess;
	}
	if(command == "getList")
	{
		QTimer::singleShot(0, this, SLOT(makefileList()));
		result = AskuModule::CommandSuccess;
	}
	if(command == "getFile")
	{
		if(parameters.count() < 1)
		{
			result = AskuModule::CommandNotEnoughParameters;
		}
		else
		{
			QString fileName = parameters[0];

			if(fileName.isEmpty())
			{
				result = AskuModule::CommandInvalidParameter;
			}
			else
			{
				makeFileContent(fileName);
				result = AskuModule::CommandSuccess;
			}
		}
	}
	if(command == "saveFile")
	{
//		QTimer::singleShot(0, this, SLOT(refreshListRgdv()));
		result = AskuModule::CommandSuccess;
	}
	if(command == "unsaveFile")
	{
//		QTimer::singleShot(0, this, SLOT(refreshListRgdv()));
		result = AskuModule::CommandSuccess;
	}

	QVariantMap answer;

	switch(result)
	{
		case AskuModule::CommandNotFound:
			answer["Result"] = QString("NotFound");
			break;
		case AskuModule::CommandSuccess:
			answer["Result"] = QString("Success");
			break;
		case AskuModule::CommandInvalid:
			answer["Result"] = QString("Invalid");
			break;
		case AskuModule::CommandNotEnoughParameters:
			answer["Result"] = QString("NotEnoughParameters");
			break;
		case AskuModule::CommandInvalidParameter:
			answer["Result"] = QString("InvalidParameter");
			break;
	}

	answer["ModuleTo"] = data["ModuleFrom"];
	answer["ModuleFrom"] = data["ModuleTo"];
	answer["WasCommand"] = data["Command"];

	emit sendControlAnswer(answer, idAskuModuleGui);

	return result;
}

//-------------------------------------------------------------------------------
void AskuViewer::AddWinMes(MessageType type, QString source, QString message)
{
	QString timeStamp = (QTime::currentTime()).toString("hh:mm:ss");
	QString strType;// = QString("%1").arg(type);
	switch(type)
	{
		case M_AVAR:
			strType = "#FF0000";
			break;
		case M_ERROR:
			strType = "#FF0040";
			break;
		case M_SWITCH:
			strType = "#004000";
			break;
		case M_SIMPLE:
			strType = "#000000";
			break;
		default:
			strType = "#000000";
	}

	LogInfo("AskuViewer: %s %s %s %s", qPrintable(timeStamp), qPrintable(strType), qPrintable(source), qPrintable(message));

	QStringList data = QStringList() << timeStamp << strType << source << message;

	if(m_logFile)
		m_logFile->appendToFile(data);

	makeViewerMessage(data);
}

//-------------------------------------------------------------------------------
QStringList AskuViewer::fileList()
{
	QStringList data;

	QDir dir(m_setup.path.log, QString("*.lf"), QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::NoSymLinks | QDir::TypeMask);
	for(qint32 i = 0; i < (qint32)dir.count(); i++)
	{
		QString name = dir[i];
		if(!DATE_FILE::dateFromName(name).isNull())
			data << name;
	}

	return data;
}

//-------------------------------------------------------------------------------
QStringList AskuViewer::fileArchiveList()
{
	QStringList data;

	QDir dir(m_setup.path.log, QString("*.lfa"), QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::NoSymLinks | QDir::TypeMask);
	for(qint32 i = 0; i < (qint32)dir.count(); i++)
	{
		QString name = dir[i];
		if(!DATE_FILE::dateFromName(name).isNull())
			data << name;
	}

	return data;
}

//-------------------------------------------------------------------------------
QString AskuViewer::logFileName(LOG_FILE * log)
{
	if(log == NULL)
		log = m_logFile;	//current

	if(log && log->isLoaded())
		return QFileInfo(log->fileName()).fileName();
	else
		return QString();
}

//-------------------------------------------------------------------------------
QVariantList AskuViewer::logFileContent(LOG_FILE * log)
{
	if(log == NULL)
		log = m_logFile;	//current

	QVariant data;

	if(log && log->isLoaded())
		data = log->getContext();

	return data.toList();
}

//-------------------------------------------------------------------------------
bool AskuViewer::logFileCurrent(LOG_FILE * log)
{
	return ((log == NULL) || (log == m_logFile));
}

//-------------------------------------------------------------------------------
void AskuViewer::makeViewerMessage(QStringList & message)
{
	QVariantMap data;

	data["InfoType"] = "VIEWER_MESSAGE";
	data["ModuleTo"] = "dialog_viewer";
	data["ModuleFrom"] = "viewer";
	data["GprId"] = IDGPR();

	QVariantMap info;
	info["Message"] = message;

	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

//-------------------------------------------------------------------------------
void AskuViewer::makeFileListMessage()
{
	QVariantMap data;

	data["InfoType"] = "VIEWER_FILE_LIST";
	data["ModuleTo"] = "dialog_viewer";
	data["ModuleFrom"] = "viewer";
	data["GprId"] = IDGPR();

	QVariantMap info;
	info["List"] = fileList();

	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

//-------------------------------------------------------------------------------
void AskuViewer::makeFileContentMessage(LOG_FILE * log)
{
	QVariantMap data;

	data["InfoType"] = "VIEWER_FILE_CONTENT";
	data["ModuleTo"] = "dialog_viewer";
	data["ModuleFrom"] = "viewer";
	data["GprId"] = IDGPR();

	QVariantMap info;
	info["IsCurrent"] = logFileCurrent(log);
	info["FileName"] = logFileName(log);
	info["Content"] = logFileContent(log);

	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

//-------------------------------------------------------------------------------
void AskuViewer::makeFileErrorMessage(ErrorCodes code, LOG_FILE *log)
{
	QVariantMap data;

	data["InfoType"] = "VIEWER_FILE_CONTENT";
	data["ModuleTo"] = "dialog_viewer";
	data["ModuleFrom"] = "viewer";
	data["GprId"] = IDGPR();

	QVariantMap info;
	info["IsCurrent"] = logFileCurrent(log);
	info["FileName"] = logFileName(log);
	info["ErrorCode"] = (int)code;
	info["ErrorString"] = DATE_FILE::errorString(code);

	data["Info"] = info;

	emit sendInfoMessage(data, idAskuModuleGui);
}

//-------------------------------------------------------------------------------
void AskuViewer::makeChangedDateMessage()
{
	QVariantMap data;

	data["InfoType"] = "VIEWER_CHANGED_DATE";
	data["ModuleTo"] = "dialog_viewer";
	data["ModuleFrom"] = "viewer";
	data["GprId"] = IDGPR();

	emit sendInfoMessage(data, idAskuModuleGui);
}

//-------------------------------------------------------------------------------
void AskuViewer::makefileList()
{
	makeFileListMessage();
}

//-------------------------------------------------------------------------------
void AskuViewer::makeFileContent(QString fileName)
{
	if(fileName.isEmpty() || fileName == QFileInfo(m_logFile->fileName()).fileName())
	{
		if(m_logFile->isLoaded())
			makeFileContentMessage();
		else
			m_currentRequested = true;
		return;
	}

	LOG_FILE *log = new LOG_FILE(fileName);

	connect(log, SIGNAL(loadComplete(ErrorCodes)), this, SLOT(onLoadComplete(ErrorCodes)));

	m_logSelect.append(log);
	log->loadFile();
}

//-------------------------------------------------------------------------------
void AskuViewer::onLoadComplete(ErrorCodes code)
{
	if(sender() == m_logFile)
	{
		if(code != FileOk)
		{
			if(!m_changedDate)
			{
				LogError("AskuViewer: load file error (%d)", (int)code);
				makeFileErrorMessage(code);
			}
			else
			{
				makeChangedDateMessage();
				m_changedDate = false;
			}
		}
		else if(m_changedDate)
		{
			makeChangedDateMessage();
			m_changedDate = false;
		}
		else if(m_currentRequested)
		{
			makeFileContentMessage();
			m_currentRequested = false;
		}
	}
	else
	{
		LOG_FILE *l = NULL;
		foreach(LOG_FILE* log, m_logSelect)
		{
			if(log == sender())
			{
				if(code != FileOk)
				{
					LogError("AskuViewer: load file error (%d)", (int)code);
					makeFileErrorMessage(code, log);
				}
				else
				{
					makeFileContentMessage(log);
				}
				l = log;
			}
		}

		if(l)
		{
			m_logSelect.removeOne(l);
			l->deleteLater();
		}
	}
}

//-------------------------------------------------------------------------------
