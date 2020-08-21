#ifndef _CANALASKU_PHASE_H_
#define _CANALASKU_PHASE_H_

#include <QObject>
#include <QList>
#include <QTimer>
#include "canalasku_defines.h"

//-------------------------------------------------------

typedef quint8 ModulePhaseCode;

//-------------------------------------------------------

class AskuPhaseCodes
{
	bool m_loaded;
	ModulePhaseCode codes[CA_N_TRANSMITTERS][CA_N_MODULES_UMI];

public:
	AskuPhaseCodes();

	bool isLoaded() {
		return m_loaded;
	}

	bool save(QString name);
	bool load(QString name);
	void dump();

	ModulePhaseCode value(quint32 p, quint32 m) {
		if(p < CA_N_TRANSMITTERS && m < CA_N_MODULES_UMI)
			return codes[p][m];
		else
			return 0xff;
	}
	void setValue(quint32 p, quint32 m, ModulePhaseCode value) {
		if(p < CA_N_TRANSMITTERS && m < CA_N_MODULES_UMI)
			codes[p][m] = value & 0x3f;
	}
};

//-------------------------------------------------------

class Oscilloscope;

//-------------------------------------------------------

typedef struct _tag_ModulePhaseValue
{
	int n_prd;
	int n_module;
	double phase;
	int code;

	_tag_ModulePhaseValue() {
		n_prd = 0;
		n_module = 0;
		phase = 0.0;
		code = 0;
	}
	_tag_ModulePhaseValue(int p, int m, double ph, int c) {
		n_prd = p;
		n_module = m;
		phase = ph;
		code = c;
	}
}ModulePhaseValue;

//-------------------------------------------------------

class ModulePhasing : public QObject
{
Q_OBJECT

	QList<ModulePhaseValue> values;
	int current;
	QTimer timer;
	int waitCounter;
	int progressNow;
	int progressAll;
	bool avtoOsc;

	Oscilloscope *osc;

	qint32 qPhasingState;
	qint32 phase_errorCode;
	qint32 phase_queryPrd;
	qint32 phase_queryMod;

public:
	ModulePhasing(QObject * parent = 0);
	~ModulePhasing();

	void status(int status, bool reset = false);
	bool isAvto();

protected:
	void start(int n_prd, int n_module, bool avto);
	void stop();
	void next(double value);

protected slots:
	void timeout();

public slots:
	void slotNext(int n_prd, int n_module, double value);
	void slotCancel();
	void slotStart(int n_prd, int n_module, bool avto);
	void slotStop();

signals:
	void sigStatus(int state, QString status);
	void sigProgress(int value);
	void sigPhaseUpdate(int n_prd = 0, int n_module = 0, bool avto = false);
	void sigOscPhase(double value, bool valid);
	void sigShowDlg(bool avtoOsc);
	void sigHideDlg();
	void sigPhaseValue(int n_prd, int n_module, double value);

//to canalasku
	void phasingState(qint32 state, qint32 error = 0);
};

#endif //_CANALASKU_PHASE_H_
