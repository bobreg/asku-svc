#ifndef __SVCAPPLICATION_H__
#define __SVCAPPLICATION_H__

#include "../common/application.h"
#include "svcmodule.h"

//----------------------------------------------------------------------------------------------------------------
class AskuSvcApplication : public AskuApplication
{
Q_OBJECT

	AskuSvcModule *svcModule;
	qint32 m_gprOverride;

private:
	virtual bool writeSettings(QSettings &m_settings);
	virtual bool readSettings (QSettings &m_settings);
//---------Чел!------------
//----------запуск скрипта проверки работы программы------
    QProcess control_run;
//---------Чел!------------

public:
	AskuSvcApplication(int & argc, char** argv);
	virtual ~AskuSvcApplication();
};

//----------------------------------------------------------------------------------------------------------------

#endif // __SVCAPPLICATION_H__
