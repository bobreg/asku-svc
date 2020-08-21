#ifndef _DATAFILE_H_INCLUDED_
#define _DATAFILE_H_INCLUDED_


#include <QTextStream>
#include <QMutex>
#include <QTimer>
#include <QDate>
#include <QTime>
#include <QFile>
#include <QThread>
#include <QEvent>
#include "../common/global.h"
#include "globalvar.h"

//-------------------------------------------------------------------------------
enum ErrorCodes {
	FileOk 			= 0,
	NotExists		= -1,
	BadFileName 	= -2,
	OpenFail 		= -3,
	ReadFail 		= -4,
	WriteFail 		= -5,
	UnkwnownError	= -6
};

//-------------------------------------------------------------------------------

class DATE_FILE_THREAD : public QThread 
{
	Q_OBJECT

public:
	DATE_FILE_THREAD(QString fileName);

	virtual void write(QVariant data);
	virtual QVariant read();
	virtual void onOpenCreate();

	bool exists();

	QVariant content();

protected:
	QString m_fileName;
	QString m_newFileName;
	ErrorCodes m_lastError;

	QFile *m_file;
	QTextStream *m_stream;

	QVariantList m_content;
	QVariantList m_writeList;

	QMutex m_writeMutex;
	QMutex m_readMutex;
	QMutex m_stopMutex;

	bool m_exitThread;
	bool m_needWrite;
	bool m_needRead;
	bool m_wasRead;

	virtual void run();

public slots:
	void writeToFile(QVariant data = QVariant());
	void readFromFile(bool readonly);

	void changeFile(QString filename);

	bool open(bool write);
	void close();
	void quit();

signals:
	void loadComplete(ErrorCodes error = FileOk);
	void writeComplete(ErrorCodes error = FileOk);
	void changedFile();
};

//-------------------------------------------------------------------------------

class LOG_FILE_THREAD : public DATE_FILE_THREAD
{
	Q_OBJECT

public:
	LOG_FILE_THREAD(QString fileName);

	virtual void write(QVariant data);
	virtual QVariant read();
	virtual void onOpenCreate();
};

//-------------------------------------------------------------------------------

class DATE_FILE : public QObject
{
	Q_OBJECT

protected:
	DATE_FILE_THREAD *m_thread;

	bool m_loaded;
	bool m_readonly;

	QString m_path;
	QString m_extention;

	QDate m_date;
	QString m_file;

	void setPath(const QString & path);
	void setExtention(const QString & ext);

	virtual void initThread();
	virtual void closeThread();

public:
	DATE_FILE(const QString & path, const QString & ext, const QDate & date = QDate::currentDate(), bool readonly = false);
	DATE_FILE(const QString & filename, const QString & path, const QString & ext, bool readonly = true);
	virtual ~DATE_FILE();

	void loadFile();
	void unloadFile();

	bool isLoaded() {
		return m_loaded;
	}

	QDate getCurrentDate() {
		return m_date;
	};

	QString fileName() {
		return m_file;
	}

	QString path() {
		return m_path;
	}

	static QString errorString(ErrorCodes codes) {
		if(codes == FileOk)
			return QString("");
		else if(codes == NotExists)
			return QString("Файл не найден");
		else if(codes == BadFileName)
			return QString("Неверное имя файла");
		else if(codes == OpenFail)
			return QString("Ошибка открытия файла");
		else if(codes == ReadFail)
			return QString("Ошибка чтения файла");
		else if(codes == WriteFail)
			return QString("Ошибка записи файла");
		else
			return QString("Другая ошибка");
	}

	qint32 deleteOlderFiles(qint32 iDays = m_setup.viewer.days);

	QString currentDateFile();
	QString fileNameFromDate(const QDate & date);
	QDate dateFromFileName(const QString & fileName);

	static QString nameFromDate(const QDate & date);
	static QDate dateFromName(const QString & name);

public slots:
	void onChangedDate();

protected slots:
	void onLoadComplete(ErrorCodes code);

signals:
	void changedFile();
	void loadComplete(ErrorCodes error = FileOk);
};

//-------------------------------------------------------------------------------

class LOG_FILE : public DATE_FILE
{
	Q_OBJECT

protected:
	virtual void initThread();
	virtual void closeThread();

public:
	LOG_FILE(const QDate & date = QDate::currentDate());
	LOG_FILE(const QString & filename);
	virtual ~LOG_FILE();

	void appendToFile(QStringList data);
	QVariant getContext();
};

//-------------------------------------------------------------------------------

#endif //_DATAFILE_H_INCLUDED_
