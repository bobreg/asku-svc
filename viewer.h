#ifndef _VIEWER_H_INCLUDED_
#define _VIEWER_H_INCLUDED_

#include <QObject>
#include <QList>
#include "../common/global.h"
#include "../common/module.h"
#include "datafile.h"

//-----------------------------------------------------------------------------

class AskuViewer : public QObject
{
	Q_OBJECT

protected:

	LOG_FILE* m_logFile;
	QList<LOG_FILE*> m_logSelect;

	QTimer *m_timer;

	QTime m_currentTime;
	QDate m_currentDate;

	bool m_currentRequested;
	bool m_changedDate;

public:
	enum MessageType
	{
		M_SIMPLE,
		M_AVAR,
		M_ERROR,
		M_SWITCH
	};

	AskuViewer(QObject *parent = 0);
	~AskuViewer();

	void quit();

	qint32 processControlCommand(QVariantMap data);

	void AddWinMes(MessageType type, QString source, QString message);

	QStringList fileList();
	QStringList fileArchiveList();

	QString logFileName(LOG_FILE * log = NULL);
	QVariantList logFileContent(LOG_FILE * log = NULL);
	bool logFileCurrent(LOG_FILE * log = NULL);

	void makeViewerMessage(QStringList & data);
	void makeFileListMessage();
	void makeFileContentMessage(LOG_FILE * log = NULL);
	void makeFileErrorMessage(ErrorCodes code, LOG_FILE *log = NULL);
	void makeChangedDateMessage();

protected slots:
	void OnTimer();
	void onLoadComplete(ErrorCodes code);

public slots:
	void makefileList();
	void makeFileContent(QString fileName = QString());

signals:
	void fileChanged();
	void changedDate();
	void changedHour();

	void sendControlAnswer(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
	void sendInfoMessage(QVariantMap data, qint32 idModule = idAskuModuleAll, qint32 idConnection = idConnectionAll);
};

//-----------------------------------------------------------------------------

extern AskuViewer *askuViewer;

#define AddStartStopMes(source, message) { if(askuViewer) askuViewer->AddWinMes(AskuViewer::M_SIMPLE, QString(source), QString(message)); else {} }
#define AddSimpleMes(source, message) { if(askuViewer) askuViewer->AddWinMes(AskuViewer::M_SIMPLE, QString(source), QString(message)); else {} }
#define AddAvarMes(source, message) { if(askuViewer) askuViewer->AddWinMes(AskuViewer::M_AVAR, QString(source), QString(message)); else {} }
#define AddErrorMes(source, message) { if(askuViewer) askuViewer->AddWinMes(AskuViewer::M_ERROR, QString(source), QString(message)); else {} }
#define AddSwitchMes(source, message) { if(askuViewer) askuViewer->AddWinMes(AskuViewer::M_SWITCH, QString(source), QString(message)); else {} }
#define AddNormaMes(source, message) { if(askuViewer) askuViewer->AddWinMes(AskuViewer::M_SIMPLE, QString(source), QString(message)); else {} }

//-----------------------------------------------------------------------------

#endif //_VIEWER_H_INCLUDED_
