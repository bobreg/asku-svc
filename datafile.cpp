#include "../common/logger.h"
#include <sys/types.h>
#include "datafile.h"

// ------------------------------------------------------------------
DATE_FILE::DATE_FILE(const QString & filename, const QString & path, const QString & ext, bool readonly)
{
	m_thread = NULL;
	m_loaded = false;
	m_readonly = readonly;

	LogInfo("DATE_FILE::DATE_FILE by name (%s)", qPrintable(filename));

	if(!filename.isNull())
	{
//		QFileInfo info(filename);

//		if(!path.isNull())
			setPath(path);
//		else
//			setPath(info.absolutePath());

//		if(!path.isNull())
			setExtention(ext);
//		else
//			setExtention(info.suffix());

//		if(path.isNull() && ext.isNull())
//			m_file = info.absoluteFilePath();
//		else
//			m_file = info.baseName();

	m_file = filename;

	m_date = dateFromFileName(m_file);

	if(!m_path.isNull() && !filename.startsWith(m_path))
		m_file = m_path + m_file;
		
	if(!m_extention.isNull() && !filename.endsWith(m_extention))
		m_file = m_file + m_extention;

	if(m_date.isNull() || !m_date.isValid())
		LogError("DATE_FILE::Error in date (%s)", qPrintable(m_file));
	}
}

// ------------------------------------------------------------------
DATE_FILE::DATE_FILE(const QString & path,const QString & ext,const QDate & date, bool readonly)
{
	m_thread = NULL;
	m_loaded = false;
	m_readonly = readonly;

	setPath(path);
	setExtention(ext);

	m_date = date;
	m_file = fileNameFromDate(date);

	LogInfo("DATE_FILE::DATE_FILE by date (%s)", qPrintable(m_file));
}

// ------------------------------------------------------------------
DATE_FILE::~DATE_FILE()
{
	LogInfo("DATE_FILE::~DATE_FILE (%s)", qPrintable(m_file));
	closeThread();
}

// ------------------------------------------------------------------
void DATE_FILE::setPath(const QString & path)
{
	QString qslash1("/");
	QString qslash2("\\");

	if(path.right(1) != qslash1 && path.right(1) != qslash2)
		m_path = path + qslash1;
	else
		m_path = path;

	m_path = QDir::toNativeSeparators(m_path);
}

//------------------------------------------------------------------
void DATE_FILE::setExtention(const QString & ext)
{
	QString qdot(".");
	if(ext.left(1) != qdot)
		m_extention = qdot + ext;
	else
		m_extention = ext;
}

// ------------------------------------------------------------------
QString DATE_FILE::nameFromDate(const QDate & date)
{
	if(!date.isValid())
		return QString::null;
	else
		return date.toString("yy_MM_dd");
}

// ------------------------------------------------------------------
QDate DATE_FILE::dateFromName(const QString & name)
{
	if(name.isNull() || name.isEmpty())
		return QDate();
	else
		return QDate::fromString(QFileInfo(name).baseName(), "yy_MM_dd").addYears(100);
}

// ------------------------------------------------------------------
QString DATE_FILE::fileNameFromDate(const QDate & date)
{
	if(m_path.isNull() || m_extention.isNull() || !date.isValid())
		return QString::null;
	else
		return m_path + nameFromDate(date) + m_extention;
}

// ------------------------------------------------------------------
QDate DATE_FILE::dateFromFileName(const QString & fileName)
{
	return dateFromName(QFileInfo(fileName).baseName());
}

// ------------------------------------------------------------------
qint32 DATE_FILE::deleteOlderFiles(qint32 iDays)
{
	QDate fileDate;
	int count = 0;

	QDir dir(m_setup.path.log, QString("*") + m_extention, QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::NoSymLinks | QDir::TypeMask);
	for(qint32 i = 0; i < (qint32)dir.count(); i++)
	{
		fileDate = dateFromFileName(dir[i]);
		if(fileDate.isNull())
		{
			LogError("DATE_FILE::deleteOlderFiles ERROR (%s)", qPrintable(dir[i]));
		}
		else
		{
			if(m_date.addDays(-iDays) > fileDate)
			{
				if(dir.remove(dir[i]))
				{
//					LogInfo("DATE_FILE::deleteOlderFiles removed (%s)", qPrintable(dir[i]));
					count++;
				}
				else
				{
					LogError("DATE_FILE::deleteOlderFiles failed remove (%s)", qPrintable(dir[i]));
				}
			}
		}
	}

	return count;
}

// ------------------------------------------------------------------
QString DATE_FILE::currentDateFile()
{
	return fileNameFromDate(m_date);
}

// ------------------------------------------------------------------
void DATE_FILE::onChangedDate()
{
	m_loaded = false;

//	closeThread();

	m_date = QDate::currentDate();
	m_file = fileNameFromDate(m_date);
	LogInfo("DATE_FILE: changed file by date (%s)", qPrintable(m_file));

	if(m_thread)
		m_thread->changeFile(m_file);

//	startThread();
//	initThread();

	emit changedFile();
	deleteOlderFiles();
}

// ------------------------------------------------------------------
void DATE_FILE::loadFile()
{
//qDebug() << "-----------------------------------------";
//	qDebug() << "loadFile: " << m_file;
//qDebug() << "-----------------------------------------";

	if(m_file.isEmpty())
	{
		LogError("LOG_FILE: loadFile is empty");
		return;
	}

//	restartThread();
//	closeThread();
	initThread();
}

// ------------------------------------------------------------------
void DATE_FILE::unloadFile()
{
	closeThread();
}

// ------------------------------------------------------------------
void DATE_FILE::initThread()
{
	
}

// ------------------------------------------------------------------
void DATE_FILE::closeThread()
{
	
}

// ------------------------------------------------------------------
LOG_FILE::LOG_FILE(const QDate & date) : DATE_FILE(m_setup.path.log, "lf", date, false)
{
}

// ------------------------------------------------------------------
LOG_FILE::LOG_FILE(const QString & filename) : DATE_FILE(filename, m_setup.path.log, "lf", true)
{
}

// ------------------------------------------------------------------
LOG_FILE::~LOG_FILE()
{
}

// ------------------------------------------------------------------
void LOG_FILE::initThread()
{
	if(!m_thread)
	{
		m_thread = new LOG_FILE_THREAD(m_file);
		if(m_thread)
		{
			connect(m_thread, SIGNAL(loadComplete(ErrorCodes)), this, SLOT(onLoadComplete(ErrorCodes)));
			connect(m_thread, SIGNAL(changedFile()), this, SIGNAL(changedFile()));
//			qDebug() << "init thread";
			m_thread->readFromFile(m_readonly);
		}
	}
}

// ------------------------------------------------------------------
void LOG_FILE::closeThread()
{
	if(m_thread)
	{
//		qDebug() << "close thread";
		m_thread->quit();
		m_thread->wait();
		delete m_thread;
		m_thread = NULL;
	}
}

// ------------------------------------------------------------------
void DATE_FILE::onLoadComplete(ErrorCodes code)
{
	m_loaded = true;//(code == FileOk);
	emit loadComplete(code);
}

// ------------------------------------------------------------------
void LOG_FILE::appendToFile(QStringList data)
{
	if(m_thread)
		m_thread->writeToFile(QVariant(data));
}

// ------------------------------------------------------------------
QVariant LOG_FILE::getContext()
{
	if(m_thread && m_loaded)
		return m_thread->content();
	else
		return QVariant();
}

// ------------------------------------------------------------------
DATE_FILE_THREAD::DATE_FILE_THREAD(QString fileName): QThread()
{
	m_fileName = fileName;
	m_newFileName = QString();
	m_lastError = FileOk;

	m_file = NULL;
	m_stream = NULL;

	m_exitThread = false;
	m_needWrite = false;
	m_needRead = false;
	m_wasRead = false;
}

// ------------------------------------------------------------------
void DATE_FILE_THREAD::run()
{
//	qDebug() << "DATE_FILE_THREAD RUN!!";
while(1)
{
	if(m_needRead)
	{
//		qDebug() << "DATE_FILE_THREAD::run  READ!!";

		m_readMutex.lock();

		if(!exists())
		{
			m_lastError = NotExists;
		}
		else if(open(false))
		{
			m_content.clear();

			while(!m_exitThread && m_needRead)
			{
				QVariant data = read();

				if(!data.isNull())
					m_content.append(data);
				else
					break;
			}

			m_lastError = FileOk;
		}
		else
		{
			m_lastError = OpenFail;
		}

		close();
		m_readMutex.unlock();
		m_needRead = false;
		m_wasRead = true;
		if(!m_exitThread)
			emit loadComplete(m_lastError);
//		qDebug() << "load complete lines:" << m_content.count();
	}

	if(m_exitThread)
		break;

	if(m_needWrite)
	{
//		qDebug() << "DATE_FILE_THREAD::run  WRITE!!";
		bool file_exists = exists();

		while(1)
		{
//		qDebug() << "DATE_FILE_THREAD::run  WRITE lock!!";
			m_writeMutex.lock();

			if(m_writeList.count() > 0 || !file_exists)
			{
				if(open(true))
				{
					if(!file_exists)
					{
						onOpenCreate();
						file_exists = true;
					}
					while(m_writeList.count() > 0)
					{
						QVariant data = m_writeList.takeFirst();
						write(data);

						m_readMutex.lock();
						m_content.append(data);
						m_readMutex.unlock();
					}

					m_lastError = FileOk;
				}
				else
				{
					m_lastError = OpenFail;
				}

				close();
				emit writeComplete(m_lastError);
//				qDebug() << "write complete";
			}

			m_writeMutex.unlock();
//		qDebug() << "DATE_FILE_THREAD::run  WRITE unlock!!";

			if(!m_newFileName.isEmpty())
			{
				m_fileName = m_newFileName;
				m_newFileName = QString();
				m_needRead = true;
				emit changedFile();
//				qDebug() << "BREAK BY CHANGE FILE";
				break;
			}

			if(m_exitThread || !m_needWrite)
			{
//				qDebug() << "BREAK FROM WRITE";
				break;
			}

			msleep(10);
		}

		if(m_exitThread)
			break;

//		qDebug() << "THREAD WAITING";
		msleep(10);
	}
}
//	qDebug() << "DATE_FILE_THREAD RUN END!!!!!!!!!";
}

// ------------------------------------------------------------------
void DATE_FILE_THREAD::writeToFile(QVariant data)
{
	if(!data.isNull())
	{
		m_writeMutex.lock();
		m_writeList.append(data);
		m_writeMutex.unlock();
	}

	m_needWrite = true;
	if(!isRunning())
		start();
}

// ------------------------------------------------------------------
void DATE_FILE_THREAD::readFromFile(bool readonly)
{
//	qDebug() << "DATE_FILE_THREAD::readFromFile";

	m_needRead = true;

	if(!readonly)
		m_needWrite = true;

	if(!isRunning())
		start();
}

// ------------------------------------------------------------------
void DATE_FILE_THREAD::write(QVariant data)
{
	Q_UNUSED(data);
}

// ------------------------------------------------------------------
QVariant DATE_FILE_THREAD::read()
{
	return QVariant();
}

// ------------------------------------------------------------------
bool DATE_FILE_THREAD::exists()
{
	return QFile::exists(m_fileName);
}

// ------------------------------------------------------------------
void DATE_FILE_THREAD::onOpenCreate()
{
	
}

// ------------------------------------------------------------------
bool DATE_FILE_THREAD::open(bool write)
{
	m_file = new QFile(m_fileName);

	QIODevice::OpenMode mode;

	if(write)
		mode = QIODevice::WriteOnly | QIODevice::Append;
	else
		mode = QIODevice::ReadOnly;

	if(m_file && m_file->open(mode))
	{
		m_stream = new QTextStream(m_file);
		if(m_stream)
		{
			m_stream->setCodec(QTextCodec::codecForName(APP_CODEC_STRING));
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------
void DATE_FILE_THREAD::close()
{
	if(m_file)
	{
		m_file->flush();
		m_file->close();
		delete m_file;
		m_file = NULL;
	}
}

// ------------------------------------------------------------------
void DATE_FILE_THREAD::changeFile(QString filename)
{
	m_newFileName = filename;
}

// ------------------------------------------------------------------
QVariant DATE_FILE_THREAD::content()
{
	QVariant c;
	m_readMutex.lock();
	c = m_content;
	m_readMutex.unlock();
	return c;
}

// ------------------------------------------------------------------
void DATE_FILE_THREAD::quit()
{
	m_exitThread = true;
	QThread::quit();
}

// ------------------------------------------------------------------
LOG_FILE_THREAD::LOG_FILE_THREAD(QString fileName) : DATE_FILE_THREAD(fileName)
{
}

// ------------------------------------------------------------------
void LOG_FILE_THREAD::write(QVariant data)
{
	if(m_stream)
	{
		QStringList list = data.toStringList();
		if(!list.isEmpty())
		{
			QString str = list.join("\t");
			if(!str.isEmpty())
			{
				*m_stream << str << endl;
			}
		}
	}
}

// ------------------------------------------------------------------
QVariant LOG_FILE_THREAD::read()
{
	if(m_stream->atEnd()) 
		return QVariant();

	QString line = m_stream->readLine();

	QStringList list;

	if(line.isEmpty())
		return QVariant(list);

	list = line.split("\t");

	return QVariant(list);
}

// ------------------------------------------------------------------
void LOG_FILE_THREAD::onOpenCreate()
{
	QVariant data = QStringList() << QTime::currentTime().toString("hh:mm:ss") << "#000000" << "" << QString("--------- открыт новый файл %1 ---------").arg(QFileInfo(m_fileName).fileName());
	m_writeList.prepend(data);
}

// ------------------------------------------------------------------
