#ifndef __SVCMODULE_H__
#define __SVCMODULE_H__

#include "../common/module.h"

class AskuSvcApplication;
class CanalAsku;
class DASD;
class VOI;
class POI;
class VRL;
class DRIVE;
class COOLERS;
class UPS;
class DES;
class AskuAlgorithm;
class AskuGprControl;
class AskuViewer;
class PowerMeter;
class Avtomatica;
class POS;
class CORETEMP;
class VOSPD;

//----------------------------------------------------------------------------------------------------------------
class AskuSvcModule : public AskuModule
{
Q_OBJECT
	CanalAsku *canalAsku;
	DASD *mDASD;
	VOI *mVOI;
	POI *mPOI;
	VRL *mVRL;
	DRIVE *mDRIVE;
	COOLERS *mCOOLERS;
	UPS *mUPS;
	DES *mDES;
	POS *mPOS;
	CORETEMP *mCORE;
	VOSPD *mVOSPD;
	AskuAlgorithm *mAlgorithm;
	AskuGprControl *mControl;
	AskuViewer *mViewer;
	PowerMeter *mPWM;
	Avtomatica *mAVT;

public:
	AskuSvcModule(AskuSvcApplication * parent, quint32 idGpr);
	~AskuSvcModule();

	virtual void processMessage(AskuMessage & message, qint32 idModule, qint32 idConnection);
	qint32 processControlCommand(QVariantMap data);

public slots:
	void makeLoggerMessage();
	void prepareToQuit();
    void eventFromPosToLog(QString, QString, QString);
};

//----------------------------------------------------------------------------------------------------------------

#endif // __SVCMODULE_H__
