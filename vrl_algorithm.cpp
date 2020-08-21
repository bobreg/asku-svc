#include "../common/logger.h"
#include "globalvar.h"
#include "viewer.h"
#include "vrl_service.h"

// ------------------------------------------------------------------
void VRL_SERVICE::verifyObSostVRL()
{
	if(bVrlState["vrl1@mest"]==ELEM_MEST || bVrlState["vrl2@mest"]==ELEM_MEST)
		bVrlState["mest"] = ELEM_MEST;
	else
		bVrlState["mest"] = ELEM_NOT;

	if(bVrlState["vrl1@ObSost"]==ELEM_AVAR && bVrlState["vrl2@ObSost"]==ELEM_AVAR)
		bVrlState["ObSost"] = ELEM_AVAR;
	else if(bVrlState["vrl1@ObSost"]==ELEM_AVAR && bVrlState["vrl2@ObSost"]==ELEM_NOT)
		bVrlState["ObSost"] = ELEM_AVAR;
	else if(bVrlState["vrl1@ObSost"]==ELEM_NOT && bVrlState["vrl2@ObSost"]==ELEM_AVAR)
		bVrlState["ObSost"] = ELEM_AVAR;
	else if(bVrlState["vrl1@ObSost"]==ELEM_NORMA && bVrlState["vrl2@ObSost"]==ELEM_NORMA && (bVrlState["vrl1@main"] == ELEM_NORMA || bVrlState["vrl2@main"] == ELEM_NORMA))
		bVrlState["ObSost"] = ELEM_NORMA;
	else if(bVrlState["vrl1@ObSost"]==ELEM_NORMA && bVrlState["vrl2@ObSost"]==ELEM_NORMA && bVrlState["vrl1@main"] == ELEM_NOT && bVrlState["vrl2@main"] == ELEM_NOT)
		bVrlState["ObSost"] = ELEM_NOT;
	else if(bVrlState["vrl1@ObSost"]==ELEM_NOT && bVrlState["vrl2@ObSost"]==ELEM_NOT)
		bVrlState["ObSost"] = ELEM_NOT;
	else
		bVrlState["ObSost"] = ELEM_ERROR;

	emit sigState(bVrlState);
}

// ------------------------------------------------------------------
void VRL_SERVICE::clearVrl(quint32 n_vrl)
{
	QString vrlName = QString("vrl%1@").arg(n_vrl+1);
	QMutableMapIterator<QString, AskuBinState> i(bVrlState);
	while(i.hasNext())
	{
		i.next();
		QString key = i.key();
		if(key.startsWith(vrlName))
			i.value().setText("") = ELEM_NOT;
		
	}
}

// ------------------------------------------------------------------
void VRL_SERVICE::process_panel(MESSAGE_209 * mes)
{
#ifdef FAKE_VRL
	mes->ao.bits.qf_vum1357 = 0;
	mes->ao.bits.qf_27v_1 = 0;
	mes->ao.bits.qf_krt_1 = 0;
	mes->ao.bits.qf_vum2468 = 0;
	mes->ao.bits.qf_27v_2 = 0;
	mes->ao.bits.qf_krt_2 = 0;
	mes->ao.bits.qf_380v_1 = 0;
	mes->ao.bits.qf_380v_2 = 0;
#endif

	quint32 num = mes->comp.bits.number - 1;
	QString N = QString("vrl%1@").arg(num + 1);
	bool work = bVrlState[N + "connect"] == ELEM_NORMA;

	if(!work)
		bVrlState[N + "qf_380v_1"] = ELEM_NOT;
	else if(mes->ao.bits.qf_380v_1)
		bVrlState[N + "qf_380v_1"] = ELEM_AVAR;
	else
		bVrlState[N + "qf_380v_1"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "qf_380v_2"] = ELEM_NOT;
	else if(mes->ao.bits.qf_380v_2)
		bVrlState[N + "qf_380v_2"] = ELEM_AVAR;
	else
		bVrlState[N + "qf_380v_2"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "qf_vum_1"] = ELEM_NOT;
	else if(mes->ao.bits.qf_vum1357)
		bVrlState[N + "qf_vum_1"] = ELEM_AVAR;
	else
		bVrlState[N + "qf_vum_1"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "qf_vum_2"] = ELEM_NOT;
	else if(mes->ao.bits.qf_vum2468)
		bVrlState[N + "qf_vum_2"] = ELEM_AVAR;
	else
		bVrlState[N + "qf_vum_2"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "qf_27v_1"] = ELEM_NOT;
	else if(mes->ao.bits.qf_27v_1)
		bVrlState[N + "qf_27v_1"] = ELEM_AVAR;
	else
		bVrlState[N + "qf_27v_1"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "qf_27v_2"] = ELEM_NOT;
	else if(mes->ao.bits.qf_27v_2)
		bVrlState[N + "qf_27v_2"] = ELEM_AVAR;
	else
		bVrlState[N + "qf_27v_2"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "qf_krt_1"] = ELEM_NOT;
	else if(mes->ao.bits.qf_krt_1)
		bVrlState[N + "qf_krt_1"] = ELEM_AVAR;
	else
		bVrlState[N + "qf_krt_1"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "qf_krt_2"] = ELEM_NOT;
	else if(mes->ao.bits.qf_krt_2)
		bVrlState[N + "qf_krt_2"] = ELEM_AVAR;
	else
		bVrlState[N + "qf_krt_2"] = ELEM_NORMA;

	panelCommonState();
}

// ------------------------------------------------------------------
void VRL_SERVICE::panelCommonState()
{
	if((bVrlState["vrl1@qf_380v_1"] == ELEM_AVAR && bVrlState["vrl2@qf_380v_1"] != ELEM_NORMA) ||
		(bVrlState["vrl1@qf_380v_1"] != ELEM_NORMA && bVrlState["vrl2@qf_380v_1"] == ELEM_AVAR))
		bVrlState["qf_380v_1"] = ELEM_AVAR;
	else if((bVrlState["vrl1@qf_380v_1"] == ELEM_NORMA && bVrlState["vrl2@qf_380v_1"] != ELEM_AVAR) ||
		(bVrlState["vrl1@qf_380v_1"] != ELEM_AVAR && bVrlState["vrl2@qf_380v_1"] == ELEM_NORMA))
		bVrlState["qf_380v_1"] = ELEM_NORMA;
	else
		bVrlState["qf_380v_1"] = ELEM_NOT;

	if((bVrlState["vrl1@qf_380v_2"] == ELEM_AVAR && bVrlState["vrl2@qf_380v_2"] != ELEM_NORMA) ||
		(bVrlState["vrl1@qf_380v_2"] != ELEM_NORMA && bVrlState["vrl2@qf_380v_2"] == ELEM_AVAR))
		bVrlState["qf_380v_2"] = ELEM_AVAR;
	else if((bVrlState["vrl1@qf_380v_2"] == ELEM_NORMA && bVrlState["vrl2@qf_380v_2"] != ELEM_AVAR) ||
		(bVrlState["vrl1@qf_380v_2"] != ELEM_AVAR && bVrlState["vrl2@qf_380v_2"] == ELEM_NORMA))
		bVrlState["qf_380v_2"] = ELEM_NORMA;
	else
		bVrlState["qf_380v_2"] = ELEM_NOT;

	if((bVrlState["vrl1@qf_vum_1"] == ELEM_AVAR && bVrlState["vrl2@qf_vum_1"] != ELEM_NORMA) ||
		(bVrlState["vrl1@qf_vum_1"] != ELEM_NORMA && bVrlState["vrl2@qf_vum_1"] == ELEM_AVAR))
		bVrlState["qf_vum_1"] = ELEM_AVAR;
	else if((bVrlState["vrl1@qf_vum_1"] == ELEM_NORMA && bVrlState["vrl2@qf_vum_1"] != ELEM_AVAR) ||
		(bVrlState["vrl1@qf_vum_1"] != ELEM_AVAR && bVrlState["vrl2@qf_vum_1"] == ELEM_NORMA))
		bVrlState["qf_vum_1"] = ELEM_NORMA;
	else
		bVrlState["qf_vum_1"] = ELEM_NOT;

	if((bVrlState["vrl1@qf_vum_2"] == ELEM_AVAR && bVrlState["vrl2@qf_vum_2"] != ELEM_NORMA) ||
		(bVrlState["vrl1@qf_vum_2"] != ELEM_NORMA && bVrlState["vrl2@qf_vum_2"] == ELEM_AVAR))
		bVrlState["qf_vum_2"] = ELEM_AVAR;
	else if((bVrlState["vrl1@qf_vum_2"] == ELEM_NORMA && bVrlState["vrl2@qf_vum_2"] != ELEM_AVAR) ||
		(bVrlState["vrl1@qf_vum_2"] != ELEM_AVAR && bVrlState["vrl2@qf_vum_2"] == ELEM_NORMA))
		bVrlState["qf_vum_2"] = ELEM_NORMA;
	else
		bVrlState["qf_vum_2"] = ELEM_NOT;

	if((bVrlState["vrl1@qf_27v_1"] == ELEM_AVAR && bVrlState["vrl2@qf_27v_1"] != ELEM_NORMA) ||
		(bVrlState["vrl1@qf_27v_1"] != ELEM_NORMA && bVrlState["vrl2@qf_27v_1"] == ELEM_AVAR))
		bVrlState["qf_27v_1"] = ELEM_AVAR;
	else if((bVrlState["vrl1@qf_27v_1"] == ELEM_NORMA && bVrlState["vrl2@qf_27v_1"] != ELEM_AVAR) ||
		(bVrlState["vrl1@qf_27v_1"] != ELEM_AVAR && bVrlState["vrl2@qf_27v_1"] == ELEM_NORMA))
		bVrlState["qf_27v_1"] = ELEM_NORMA;
	else
		bVrlState["qf_27v_1"] = ELEM_NOT;

	if((bVrlState["vrl1@qf_27v_2"] == ELEM_AVAR && bVrlState["vrl2@qf_27v_2"] != ELEM_NORMA) ||
		(bVrlState["vrl1@qf_27v_2"] != ELEM_NORMA && bVrlState["vrl2@qf_27v_2"] == ELEM_AVAR))
		bVrlState["qf_27v_2"] = ELEM_AVAR;
	else if((bVrlState["vrl1@qf_27v_2"] == ELEM_NORMA && bVrlState["vrl2@qf_27v_2"] != ELEM_AVAR) ||
		(bVrlState["vrl1@qf_27v_2"] != ELEM_AVAR && bVrlState["vrl2@qf_27v_2"] == ELEM_NORMA))
		bVrlState["qf_27v_2"] = ELEM_NORMA;
	else
		bVrlState["qf_27v_2"] = ELEM_NOT;

	if((bVrlState["vrl1@qf_krt_1"] == ELEM_AVAR && bVrlState["vrl2@qf_krt_1"] != ELEM_NORMA) ||
		(bVrlState["vrl1@qf_krt_1"] != ELEM_NORMA && bVrlState["vrl2@qf_krt_1"] == ELEM_AVAR))
		bVrlState["qf_krt_1"] = ELEM_AVAR;
	else if((bVrlState["vrl1@qf_krt_1"] == ELEM_NORMA && bVrlState["vrl2@qf_krt_1"] != ELEM_AVAR) ||
		(bVrlState["vrl1@qf_krt_1"] != ELEM_AVAR && bVrlState["vrl2@qf_krt_1"] == ELEM_NORMA))
		bVrlState["qf_krt_1"] = ELEM_NORMA;
	else
		bVrlState["qf_krt_1"] = ELEM_NOT;

	if((bVrlState["vrl1@qf_krt_2"] == ELEM_AVAR && bVrlState["vrl2@qf_krt_2"] != ELEM_NORMA) ||
		(bVrlState["vrl1@qf_krt_2"] != ELEM_NORMA && bVrlState["vrl2@qf_krt_2"] == ELEM_AVAR))
		bVrlState["qf_krt_2"] = ELEM_AVAR;
	else if((bVrlState["vrl1@qf_krt_2"] == ELEM_NORMA && bVrlState["vrl2@qf_krt_2"] != ELEM_AVAR) ||
		(bVrlState["vrl1@qf_krt_2"] != ELEM_AVAR && bVrlState["vrl2@qf_krt_2"] == ELEM_NORMA))
		bVrlState["qf_krt_2"] = ELEM_NORMA;
	else
		bVrlState["qf_krt_2"] = ELEM_NOT;

	if((bVrlState["qf_380v_1"] == ELEM_AVAR && bVrlState["qf_380v_2"] == ELEM_AVAR) ||
		(bVrlState["qf_vum_1"] == ELEM_AVAR && bVrlState["qf_vum_2"] == ELEM_AVAR) ||
		(bVrlState["qf_27v_1"] == ELEM_AVAR && bVrlState["qf_27v_2"] == ELEM_AVAR) ||
		(bVrlState["qf_krt_1"] == ELEM_AVAR && bVrlState["qf_krt_2"] == ELEM_AVAR) )
		bVrlState["panel"] = ELEM_AVAR;
	else if(bVrlState["qf_380v_1"] == ELEM_AVAR || bVrlState["qf_380v_2"] == ELEM_AVAR ||
		bVrlState["qf_vum_1"] == ELEM_AVAR || bVrlState["qf_vum_2"] == ELEM_AVAR ||
		bVrlState["qf_27v_1"] == ELEM_AVAR || bVrlState["qf_27v_2"] == ELEM_AVAR ||
		bVrlState["qf_krt_1"] == ELEM_AVAR || bVrlState["qf_krt_2"] == ELEM_AVAR )
		bVrlState["panel"] = ELEM_ERROR;
	else if(bVrlState["qf_380v_1"] == ELEM_NOT && bVrlState["qf_380v_2"] == ELEM_NOT &&
		bVrlState["qf_vum_1"] == ELEM_NOT && bVrlState["qf_vum_2"] == ELEM_NOT &&
		bVrlState["qf_27v_1"] == ELEM_NOT && bVrlState["qf_27v_2"] == ELEM_NOT &&
		bVrlState["qf_krt_1"] == ELEM_NOT && bVrlState["qf_krt_2"] == ELEM_NOT )
		bVrlState["panel"] = ELEM_NOT;
	else
		bVrlState["panel"] = ELEM_NORMA;
}

// ------------------------------------------------------------------
void VRL_SERVICE::process_subblocks(MESSAGE_209 * mes)
{
#ifdef FAKE_VRL
	mes->ao.bits.avar_d2en258_1 = 0;
	mes->ao.bits.avar_d2en258_2 = 0;
	mes->ao.bits.avar_d2en279_1 = 0;
	mes->ao.bits.avar_d2en279_2 = 0;
	mes->ao.bits.avar_d2en277m_1 = 0;
	mes->ao.bits.avar_d2en277m_2 = 0;
	mes->ao.bits.avar_vent_1 = 0;
	mes->ao.bits.avar_vent_2 = 0;
#endif

	quint32 num = mes->comp.bits.number - 1;
	QString N = QString("vrl%1@").arg(num + 1);
	bool work = bVrlState[N + "connect"] == ELEM_NORMA;

	if(!work)
		bVrlState[N + "d2en258_1"] = ELEM_NOT;
	else if(mes->ao.bits.avar_d2en258_1)
		bVrlState[N + "d2en258_1"] = ELEM_AVAR;
	else
		bVrlState[N + "d2en258_1"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "d2en258_2"] = ELEM_NOT;
	else if(mes->ao.bits.avar_d2en258_2)
		bVrlState[N + "d2en258_2"] = ELEM_AVAR;
	else
		bVrlState[N + "d2en258_2"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "d2en279_1"] = ELEM_NOT;
	else if(mes->ao.bits.avar_d2en279_1)
		bVrlState[N + "d2en279_1"] = ELEM_AVAR;
	else
		bVrlState[N + "d2en279_1"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "d2en279_2"] = ELEM_NOT;
	else if(mes->ao.bits.avar_d2en279_2)
		bVrlState[N + "d2en279_2"] = ELEM_AVAR;
	else
		bVrlState[N + "d2en279_2"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "d2en277m_1"] = ELEM_NOT;
	else if(mes->ao.bits.avar_d2en277m_1)
		bVrlState[N + "d2en277m_1"] = ELEM_AVAR;
	else
		bVrlState[N + "d2en277m_1"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "d2en277m_2"] = ELEM_NOT;
	else if(mes->ao.bits.avar_d2en277m_2)
		bVrlState[N + "d2en277m_2"] = ELEM_AVAR;
	else
		bVrlState[N + "d2en277m_2"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "vent_1"] = ELEM_NOT;
	else if(mes->ao.bits.avar_vent_1)
		bVrlState[N + "vent_1"] = ELEM_AVAR;
	else
		bVrlState[N + "vent_1"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "vent_2"] = ELEM_NOT;
	else if(mes->ao.bits.avar_vent_2)
		bVrlState[N + "vent_2"] = ELEM_AVAR;
	else
		bVrlState[N + "vent_2"] = ELEM_NORMA;

#ifdef FAKE_VRL
	if(!work)
		bVrlState[N + "vent_3"] = ELEM_NOT;
	else if(mes->ao.bits.avar_vent_1)
		bVrlState[N + "vent_3"] = ELEM_AVAR;
	else
		bVrlState[N + "vent_3"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "vent_4"] = ELEM_NOT;
	else if(mes->ao.bits.avar_vent_2)
		bVrlState[N + "vent_4"] = ELEM_AVAR;
	else
		bVrlState[N + "vent_4"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "623gv01_ok"] = ELEM_NOT;
	else
		bVrlState[N + "623gv01_ok"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "623gv01_kp"] = ELEM_NOT;
	else
		bVrlState[N + "623gv01_kp"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "623gf01"] = ELEM_NOT;
	else
		bVrlState[N + "623gf01"] = ELEM_NORMA;

	if(!work)
		bVrlState[N + "svch_comm"] = ELEM_NOT;
	else
		bVrlState[N + "svch_comm"] = ELEM_NORMA;

#endif

	bVrlState[N + "623gv01_ok"] = ELEM_DISABLE;
	bVrlState[N + "623gv01_kp"] = ELEM_DISABLE;
	bVrlState[N + "623gf01"] = ELEM_DISABLE;

	subblocksCommonState();
}

// ------------------------------------------------------------------
void VRL_SERVICE::subblocksCommonState()
{
	if((bVrlState["vrl1@d2en258_1"] == ELEM_AVAR && bVrlState["vrl2@d2en258_1"] != ELEM_NORMA) ||
		(bVrlState["vrl1@d2en258_1"] != ELEM_NORMA && bVrlState["vrl2@d2en258_1"] == ELEM_AVAR))
		bVrlState["d2en258_1"] = ELEM_AVAR;
	else if((bVrlState["vrl1@d2en258_1"] == ELEM_NORMA && bVrlState["vrl2@d2en258_1"] != ELEM_AVAR) ||
		(bVrlState["vrl1@d2en258_1"] != ELEM_AVAR && bVrlState["vrl2@d2en258_1"] == ELEM_NORMA))
		bVrlState["d2en258_1"] = ELEM_NORMA;
	else
		bVrlState["d2en258_1"] = ELEM_NOT;

	if((bVrlState["vrl1@d2en258_2"] == ELEM_AVAR && bVrlState["vrl2@d2en258_2"] != ELEM_NORMA) ||
		(bVrlState["vrl1@d2en258_2"] != ELEM_NORMA && bVrlState["vrl2@d2en258_2"] == ELEM_AVAR))
		bVrlState["d2en258_2"] = ELEM_AVAR;
	else if((bVrlState["vrl1@d2en258_2"] == ELEM_NORMA && bVrlState["vrl2@d2en258_2"] != ELEM_AVAR) ||
		(bVrlState["vrl1@d2en258_2"] != ELEM_AVAR && bVrlState["vrl2@d2en258_2"] == ELEM_NORMA))
		bVrlState["d2en258_2"] = ELEM_NORMA;
	else
		bVrlState["d2en258_2"] = ELEM_NOT;

	if((bVrlState["vrl1@d2en279_1"] == ELEM_AVAR && bVrlState["vrl2@d2en279_1"] != ELEM_NORMA) ||
		(bVrlState["vrl1@d2en279_1"] != ELEM_NORMA && bVrlState["vrl2@d2en279_1"] == ELEM_AVAR))
		bVrlState["d2en279_1"] = ELEM_AVAR;
	else if((bVrlState["vrl1@d2en279_1"] == ELEM_NORMA && bVrlState["vrl2@d2en279_1"] != ELEM_AVAR) ||
		(bVrlState["vrl1@d2en279_1"] != ELEM_AVAR && bVrlState["vrl2@d2en279_1"] == ELEM_NORMA))
		bVrlState["d2en279_1"] = ELEM_NORMA;
	else
		bVrlState["d2en279_1"] = ELEM_NOT;

	if((bVrlState["vrl1@d2en279_2"] == ELEM_AVAR && bVrlState["vrl2@d2en279_2"] != ELEM_NORMA) ||
		(bVrlState["vrl1@d2en279_2"] != ELEM_NORMA && bVrlState["vrl2@d2en279_2"] == ELEM_AVAR))
		bVrlState["d2en279_2"] = ELEM_AVAR;
	else if((bVrlState["vrl1@d2en279_2"] == ELEM_NORMA && bVrlState["vrl2@d2en279_2"] != ELEM_AVAR) ||
		(bVrlState["vrl1@d2en279_2"] != ELEM_AVAR && bVrlState["vrl2@d2en279_2"] == ELEM_NORMA))
		bVrlState["d2en279_2"] = ELEM_NORMA;
	else
		bVrlState["d2en279_2"] = ELEM_NOT;

	if((bVrlState["vrl1@d2en277m_1"] == ELEM_AVAR && bVrlState["vrl2@d2en277m_1"] != ELEM_NORMA) ||
		(bVrlState["vrl1@d2en277m_1"] != ELEM_NORMA && bVrlState["vrl2@d2en277m_1"] == ELEM_AVAR))
		bVrlState["d2en277m_1"] = ELEM_AVAR;
	else if((bVrlState["vrl1@d2en277m_1"] == ELEM_NORMA && bVrlState["vrl2@d2en277m_1"] != ELEM_AVAR) ||
		(bVrlState["vrl1@d2en277m_1"] != ELEM_AVAR && bVrlState["vrl2@d2en277m_1"] == ELEM_NORMA))
		bVrlState["d2en277m_1"] = ELEM_NORMA;
	else
		bVrlState["d2en277m_1"] = ELEM_NOT;

	if((bVrlState["vrl1@d2en277m_2"] == ELEM_AVAR && bVrlState["vrl2@d2en277m_2"] != ELEM_NORMA) ||
		(bVrlState["vrl1@d2en277m_2"] != ELEM_NORMA && bVrlState["vrl2@d2en277m_2"] == ELEM_AVAR))
		bVrlState["d2en277m_2"] = ELEM_AVAR;
	else if((bVrlState["vrl1@d2en277m_2"] == ELEM_NORMA && bVrlState["vrl2@d2en277m_2"] != ELEM_AVAR) ||
		(bVrlState["vrl1@d2en277m_2"] != ELEM_AVAR && bVrlState["vrl2@d2en277m_2"] == ELEM_NORMA))
		bVrlState["d2en277m_2"] = ELEM_NORMA;
	else
		bVrlState["d2en277m_2"] = ELEM_NOT;

	if((bVrlState["vrl1@vent_1"] == ELEM_AVAR && bVrlState["vrl2@vent_1"] != ELEM_NORMA) ||
		(bVrlState["vrl1@vent_1"] != ELEM_NORMA && bVrlState["vrl2@vent_1"] == ELEM_AVAR))
		bVrlState["vent_1"] = ELEM_AVAR;
	else if((bVrlState["vrl1@vent_1"] == ELEM_NORMA && bVrlState["vrl2@vent_1"] != ELEM_AVAR) ||
		(bVrlState["vrl1@vent_1"] != ELEM_AVAR && bVrlState["vrl2@vent_1"] == ELEM_NORMA))
		bVrlState["vent_1"] = ELEM_NORMA;
	else
		bVrlState["vent_1"] = ELEM_NOT;

	if((bVrlState["vrl1@vent_2"] == ELEM_AVAR && bVrlState["vrl2@vent_2"] != ELEM_NORMA) ||
		(bVrlState["vrl1@vent_2"] != ELEM_NORMA && bVrlState["vrl2@vent_2"] == ELEM_AVAR))
		bVrlState["vent_2"] = ELEM_AVAR;
	else if((bVrlState["vrl1@vent_2"] == ELEM_NORMA && bVrlState["vrl2@vent_2"] != ELEM_AVAR) ||
		(bVrlState["vrl1@vent_2"] != ELEM_AVAR && bVrlState["vrl2@vent_2"] == ELEM_NORMA))
		bVrlState["vent_2"] = ELEM_NORMA;
	else
		bVrlState["vent_2"] = ELEM_NOT;

	if((bVrlState["vrl1@vent_3"] == ELEM_AVAR && bVrlState["vrl2@vent_3"] != ELEM_NORMA) ||
		(bVrlState["vrl1@vent_3"] != ELEM_NORMA && bVrlState["vrl2@vent_3"] == ELEM_AVAR))
		bVrlState["vent_3"] = ELEM_AVAR;
	else if((bVrlState["vrl1@vent_3"] == ELEM_NORMA && bVrlState["vrl2@vent_3"] != ELEM_AVAR) ||
		(bVrlState["vrl1@vent_3"] != ELEM_AVAR && bVrlState["vrl2@vent_3"] == ELEM_NORMA))
		bVrlState["vent_3"] = ELEM_NORMA;
	else
		bVrlState["vent_3"] = ELEM_NOT;

	if((bVrlState["vrl1@vent_4"] == ELEM_AVAR && bVrlState["vrl2@vent_4"] != ELEM_NORMA) ||
		(bVrlState["vrl1@vent_4"] != ELEM_NORMA && bVrlState["vrl2@vent_4"] == ELEM_AVAR))
		bVrlState["vent_4"] = ELEM_AVAR;
	else if((bVrlState["vrl1@vent_4"] == ELEM_NORMA && bVrlState["vrl2@vent_4"] != ELEM_AVAR) ||
		(bVrlState["vrl1@vent_4"] != ELEM_AVAR && bVrlState["vrl2@vent_4"] == ELEM_NORMA))
		bVrlState["vent_4"] = ELEM_NORMA;
	else
		bVrlState["vent_4"] = ELEM_NOT;

	if((bVrlState["vrl1@svch_comm"] == ELEM_AVAR && bVrlState["vrl2@svch_comm"] != ELEM_NORMA) ||
		(bVrlState["vrl1@svch_comm"] != ELEM_NORMA && bVrlState["vrl2@svch_comm"] == ELEM_AVAR))
		bVrlState["svch_comm"] = ELEM_AVAR;
	else if((bVrlState["vrl1@svch_comm"] == ELEM_NORMA && bVrlState["vrl2@svch_comm"] != ELEM_AVAR) ||
		(bVrlState["vrl1@svch_comm"] != ELEM_AVAR && bVrlState["vrl2@svch_comm"] == ELEM_NORMA))
		bVrlState["svch_comm"] = ELEM_NORMA;
	else
		bVrlState["svch_comm"] = ELEM_NOT;



//#ifndef FAKE_VRL
	bVrlState["vent_3"] = ELEM_DISABLE;
	bVrlState["vent_4"] = ELEM_DISABLE;
	bVrlState["svch_comm"] = ELEM_DISABLE;
//#endif


}

// ------------------------------------------------------------------
void VRL_SERVICE::process_vum(MESSAGE_209 * mes)
{
//	if(mes->comp.bits.number != mes->status.bits.code && mes->status.bits.code != 0)
//		return;

//	quint32 num = mes->comp.bits.number - 1;
//	QString N = QString("vrl%1@").arg(num + 1);
	bool work = (mes->status.bits.code != 0);
	quint32 cntNot = 0, cntAvar = 0;

	for(quint32 nv = 0; nv < N_VRL_VUM; nv++)
	{
		QString NV = QString("vum%1@").arg(nv + 1);
		bool otklVum = false;

		switch(nv)
		{
			case 0:
			case 2:
			case 4:
			case 6:
				otklVum = (bVrlState["qf_vum_1"] == ELEM_AVAR) || (bVrlState["qf_380v_1"] == ELEM_AVAR) || (bVrlState["qf_27v_1"] == ELEM_AVAR);
				break;
			case 1:
			case 3:
			case 5:
			case 7:
				otklVum = (bVrlState["qf_vum_2"] == ELEM_AVAR) || (bVrlState["qf_380v_2"] == ELEM_AVAR) || (bVrlState["qf_27v_2"] == ELEM_AVAR);
				break;
		}

		if(!work || otklVum)
		{
			bVrlState[NV + "ObSost"] = ELEM_NOT;
			cntNot++;
		}
		else if(mes->umi[nv].umi_o.flags.bits.f_avar || mes->umi[nv].umi_p.flags.bits.f_avar)
		{
			bVrlState[NV + "ObSost"] = ELEM_AVAR;
			cntAvar++;
		}
		else
			bVrlState[NV + "ObSost"] = ELEM_NORMA;

		if(!work || otklVum)
			bVrlState[NV + "sumPout"].setText("не измерено") = ELEM_NOT;
		else if(mes->umi[nv].umi_o.flags.bits.f_pout)
			bVrlState[NV + "sumPout"].setText(QString("%1").arg(mes->umi[nv].umi_o.pout)) = ELEM_AVAR;
		else
			bVrlState[NV + "sumPout"].setText(QString("%1").arg(mes->umi[nv].umi_o.pout)) = ELEM_NORMA;

		if(!work || otklVum)
			bVrlState[NV + "supPout"].setText("не измерено") = ELEM_NOT;
		else if(mes->umi[nv].umi_p.flags.bits.f_pout)
			bVrlState[NV + "supPout"].setText(QString("%1").arg(mes->umi[nv].umi_p.pout)) = ELEM_AVAR;
		else
			bVrlState[NV + "supPout"].setText(QString("%1").arg(mes->umi[nv].umi_p.pout)) = ELEM_NORMA;

		if(!work || otklVum)
			bVrlState[NV + "sumPin"].setText("не измерено") = ELEM_NOT;
		else if(mes->umi[nv].umi_o.flags.bits.f_pin)
			bVrlState[NV + "sumPin"].setText(QString("%1").arg(mes->umi[nv].umi_o.pin)) = ELEM_AVAR;
		else
			bVrlState[NV + "sumPin"].setText(QString("%1").arg(mes->umi[nv].umi_o.pin)) = ELEM_NORMA;

		if(!work || otklVum)
			bVrlState[NV + "supPin"].setText("не измерено") = ELEM_NOT;
		else if(mes->umi[nv].umi_p.flags.bits.f_pin)
			bVrlState[NV + "supPin"].setText(QString("%1").arg(mes->umi[nv].umi_p.pin)) = ELEM_AVAR;
		else
			bVrlState[NV + "supPin"].setText(QString("%1").arg(mes->umi[nv].umi_p.pin)) = ELEM_NORMA;

		if(!work || otklVum)
			bVrlState[NV + "sumPotr"].setText("не измерено") = ELEM_NOT;
		else if(mes->umi[nv].umi_o.flags.bits.f_potr)
			bVrlState[NV + "sumPotr"].setText(QString("%1").arg(mes->umi[nv].umi_o.potr)) = ELEM_AVAR;
		else
			bVrlState[NV + "sumPotr"].setText(QString("%1").arg(mes->umi[nv].umi_o.potr)) = ELEM_NORMA;

		if(!work || otklVum)
			bVrlState[NV + "supPotr"].setText("не измерено") = ELEM_NOT;
		else if(mes->umi[nv].umi_p.flags.bits.f_potr)
			bVrlState[NV + "supPotr"].setText(QString("%1").arg(mes->umi[nv].umi_p.potr)) = ELEM_AVAR;
		else
			bVrlState[NV + "supPotr"].setText(QString("%1").arg(mes->umi[nv].umi_p.potr)) = ELEM_NORMA;

		if(!work || otklVum)
			bVrlState[NV + "sumUpit"].setText("не измерено") = ELEM_NOT;
		else if(mes->umi[nv].umi_o.flags.bits.f_u)
			bVrlState[NV + "sumUpit"].setText(QString("%1").arg(mes->umi[nv].umi_o.u)) = ELEM_AVAR;
		else
			bVrlState[NV + "sumUpit"].setText(QString("%1").arg(mes->umi[nv].umi_o.u)) = ELEM_NORMA;

		if(!work || otklVum)
			bVrlState[NV + "supUpit"].setText("не измерено") = ELEM_NOT;
		else if(mes->umi[nv].umi_p.flags.bits.f_u)
			bVrlState[NV + "supUpit"].setText(QString("%1").arg(mes->umi[nv].umi_p.u)) = ELEM_AVAR;
		else
			bVrlState[NV + "supUpit"].setText(QString("%1").arg(mes->umi[nv].umi_p.u)) = ELEM_NORMA;

		if(!work || otklVum)
			bVrlState[NV + "sumT"].setText("не измерено") = ELEM_NOT;
		else if(mes->umi[nv].umi_o.flags.bits.f_t)
			bVrlState[NV + "sumT"].setText(QString("%1").arg(mes->umi[nv].umi_o.t)) = ELEM_AVAR;
		else
			bVrlState[NV + "sumT"].setText(QString("%1").arg(mes->umi[nv].umi_o.t)) = ELEM_NORMA;

		if(!work || otklVum)
			bVrlState[NV + "supT"].setText("не измерено") = ELEM_NOT;
		else if(mes->umi[nv].umi_p.flags.bits.f_t)
			bVrlState[NV + "supT"].setText(QString("%1").arg(mes->umi[nv].umi_p.t)) = ELEM_AVAR;
		else
			bVrlState[NV + "supT"].setText(QString("%1").arg(mes->umi[nv].umi_p.t)) = ELEM_NORMA;
	}

	if(cntNot == N_VRL_VUM)
		bVrlState["prd"] = ELEM_NOT;
	else if(cntAvar > (N_VRL_VUM / 2))
		bVrlState["prd"] = ELEM_AVAR;
	else if(cntAvar > 0)
		bVrlState["prd"] = ELEM_ERROR;
	else
		bVrlState["prd"] = ELEM_NORMA;
}

// ------------------------------------------------------------------
void VRL_SERVICE::process_prm(MESSAGE_209 * mes)
{
//#ifdef FAKE_VRL
	mes->prm.bits.sum_avar_atten = 0;
	mes->prm.bits.dif_avar_atten = 0;
	mes->prm.bits.sup_avar_atten = 0;
//#endif

	quint32 num = mes->comp.bits.number - 1;
	QString PRM = QString("prm%1@").arg(num + 1);
	bool work = true;//(mes->status.bits.code != 0);
	quint32 cntAvar = 0, cntError = 0;

	bool otklPrm = false;//true;
//	if(mes->comp.bits.number == 1)
//		otklPrm = mes->ao.bits.qf_27v_1;
//	if(mes->comp.bits.number == 2)
//		otklPrm = mes->ao.bits.qf_27v_2;

	if(!work || otklPrm)
		bVrlState[PRM + "sum_sharu"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.sum_avar_sharu)
		bVrlState[PRM + "sum_sharu"].setText(QString("%1").arg(mes->prm.bits.sum_sharu_code)) = ELEM_AVAR;
	else
		bVrlState[PRM + "sum_sharu"].setText(QString("%1").arg(mes->prm.bits.sum_sharu_code)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "dif_sharu"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.dif_avar_sharu)
		bVrlState[PRM + "dif_sharu"].setText(QString("%1").arg(mes->prm.bits.dif_sharu_code)) = ELEM_AVAR;
	else
		bVrlState[PRM + "dif_sharu"].setText(QString("%1").arg(mes->prm.bits.dif_sharu_code)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sup_sharu"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.sup_avar_sharu)
		bVrlState[PRM + "sup_sharu"].setText(QString("%1").arg(mes->prm.bits.sup_sharu_code)) = ELEM_AVAR;
	else
		bVrlState[PRM + "sup_sharu"].setText(QString("%1").arg(mes->prm.bits.sup_sharu_code)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sum_sh"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.sum_int_noise >= PrmShMaxValue)
		bVrlState[PRM + "sum_sh"].setText(QString("%1").arg(mes->prm.bits.sum_int_noise)) = ELEM_AVAR;
	else
		bVrlState[PRM + "sum_sh"].setText(QString("%1").arg(mes->prm.bits.sum_int_noise)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "dif_sh"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.dif_int_noise >= PrmShMaxValue)
		bVrlState[PRM + "dif_sh"].setText(QString("%1").arg(mes->prm.bits.dif_int_noise)) = ELEM_AVAR;
	else
		bVrlState[PRM + "dif_sh"].setText(QString("%1").arg(mes->prm.bits.dif_int_noise)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sup_sh"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.sup_int_noise >= PrmShMaxValue)
		bVrlState[PRM + "sup_sh"].setText(QString("%1").arg(mes->prm.bits.sup_int_noise)) = ELEM_AVAR;
	else
		bVrlState[PRM + "sup_sh"].setText(QString("%1").arg(mes->prm.bits.sup_int_noise)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sum_amp_rbs"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.sum_amp_rbs <= PrmAmpRbsMinValue)
		bVrlState[PRM + "sum_amp_rbs"].setText(QString("%1").arg(mes->prm.bits.sum_amp_rbs)) = ELEM_AVAR;
	else
		bVrlState[PRM + "sum_amp_rbs"].setText(QString("%1").arg(mes->prm.bits.sum_amp_rbs)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "dif_amp_rbs"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.dif_amp_rbs <= PrmAmpRbsMinValue)
		bVrlState[PRM + "dif_amp_rbs"].setText(QString("%1").arg(mes->prm.bits.dif_amp_rbs)) = ELEM_AVAR;
	else
		bVrlState[PRM + "dif_amp_rbs"].setText(QString("%1").arg(mes->prm.bits.dif_amp_rbs)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sup_amp_rbs"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.sup_amp_rbs <= PrmAmpRbsMinValue)
		bVrlState[PRM + "sup_amp_rbs"].setText(QString("%1").arg(mes->prm.bits.sup_amp_rbs)) = ELEM_AVAR;
	else
		bVrlState[PRM + "sup_amp_rbs"].setText(QString("%1").arg(mes->prm.bits.sup_amp_rbs)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sum_amp_nrz_f2"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.sum_amp_nrz_f2 <= PrmAmpNrzF2MinValue)
		bVrlState[PRM + "sum_amp_nrz_f2"].setText(QString("%1").arg(mes->prm.bits.sum_amp_nrz_f2)) = ELEM_AVAR;
	else
		bVrlState[PRM + "sum_amp_nrz_f2"].setText(QString("%1").arg(mes->prm.bits.sum_amp_nrz_f2)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "dif_amp_nrz_f2"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.dif_amp_nrz_f2 <= PrmAmpNrzF2MinValue)
		bVrlState[PRM + "dif_amp_nrz_f2"].setText(QString("%1").arg(mes->prm.bits.dif_amp_nrz_f2)) = ELEM_AVAR;
	else
		bVrlState[PRM + "dif_amp_nrz_f2"].setText(QString("%1").arg(mes->prm.bits.dif_amp_nrz_f2)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sup_amp_nrz_f2"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.sup_amp_nrz_f2 <= PrmAmpNrzF2MinValue)
		bVrlState[PRM + "sup_amp_nrz_f2"].setText(QString("%1").arg(mes->prm.bits.sup_amp_nrz_f2)) = ELEM_AVAR;
	else
		bVrlState[PRM + "sup_amp_nrz_f2"].setText(QString("%1").arg(mes->prm.bits.sup_amp_nrz_f2)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sum_amp_nrz_f3"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.sum_amp_nrz_f3 <= PrmAmpNrzF3MinValue)
		bVrlState[PRM + "sum_amp_nrz_f3"].setText(QString("%1").arg(mes->prm.bits.sum_amp_nrz_f3)) = ELEM_AVAR;
	else
		bVrlState[PRM + "sum_amp_nrz_f3"].setText(QString("%1").arg(mes->prm.bits.sum_amp_nrz_f3)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "dif_amp_nrz_f3"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.dif_amp_nrz_f3 <= PrmAmpNrzF3MinValue)
		bVrlState[PRM + "dif_amp_nrz_f3"].setText(QString("%1").arg(mes->prm.bits.dif_amp_nrz_f3)) = ELEM_AVAR;
	else
		bVrlState[PRM + "dif_amp_nrz_f3"].setText(QString("%1").arg(mes->prm.bits.dif_amp_nrz_f3)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sup_amp_nrz_f3"].setText("не измерено") = ELEM_NOT;
	else if(mes->prm.bits.sup_amp_nrz_f3 <= PrmAmpNrzF3MinValue)
		bVrlState[PRM + "sup_amp_nrz_f3"].setText(QString("%1").arg(mes->prm.bits.sup_amp_nrz_f3)) = ELEM_AVAR;
	else
		bVrlState[PRM + "sup_amp_nrz_f3"].setText(QString("%1").arg(mes->prm.bits.sup_amp_nrz_f3)) = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sum_att"] = ELEM_NOT;
	else if(mes->prm.bits.sum_avar_atten)
		bVrlState[PRM + "sum_att"] = ELEM_AVAR;
	else
		bVrlState[PRM + "sum_att"] = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "dif_att"] = ELEM_NOT;
	else if(mes->prm.bits.dif_avar_atten)
		bVrlState[PRM + "dif_att"] = ELEM_AVAR;
	else
		bVrlState[PRM + "dif_att"] = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "sup_att"] = ELEM_NOT;
	else if(mes->prm.bits.sup_avar_atten)
		bVrlState[PRM + "sup_att"] = ELEM_AVAR;
	else
		bVrlState[PRM + "sup_att"] = ELEM_NORMA;

	if(!work || otklPrm)
		bVrlState[PRM + "obSost"] = ELEM_NOT;
	else if(cntAvar > 0)
		bVrlState[PRM + "obSost"] = ELEM_AVAR;
	else if(cntError > 0)
		bVrlState[PRM + "obSost"] = ELEM_ERROR;
	else
		bVrlState[PRM + "obSost"] = ELEM_NORMA;
}

// ------------------------------------------------------------------
void VRL_SERVICE::process_azn(MESSAGE_209 * mes)
{
//#ifdef FAKE_VRL
	mes->azn.bits.avar_prm = 0;
	mes->azn.bits.p1_avar_atten = 0;
	mes->azn.bits.p2_avar_atten = 0;
	mes->azn.bits.p3_avar_atten = 0;
	mes->azn.bits.p4_avar_atten = 0;
//#endif
//	quint32 num = mes->comp.bits.number - 1;
	QString AZ = QString("azn@");
	bool work = true;//(mes->status.bits.code != 0);
	quint32 cntAvar = 0, cntError = 0;

	bool otklAzn = false;//mes->azn.bits.avar_prm_link;

	if(!work || otklAzn)
		bVrlState[AZ + "sharu1"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p1_avar_sharu)
		bVrlState[AZ + "sharu1"].setText(QString("%1").arg(mes->azn.bits.p1_sharu_code)) = ELEM_AVAR;
	else
		bVrlState[AZ + "sharu1"].setText(QString("%1").arg(mes->azn.bits.p1_sharu_code)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "sharu2"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p2_avar_sharu)
		bVrlState[AZ + "sharu2"].setText(QString("%1").arg(mes->azn.bits.p2_sharu_code)) = ELEM_AVAR;
	else
		bVrlState[AZ + "sharu2"].setText(QString("%1").arg(mes->azn.bits.p2_sharu_code)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "sharu3"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p3_avar_sharu)
		bVrlState[AZ + "sharu3"].setText(QString("%1").arg(mes->azn.bits.p3_sharu_code)) = ELEM_AVAR;
	else
		bVrlState[AZ + "sharu3"].setText(QString("%1").arg(mes->azn.bits.p3_sharu_code)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "sharu4"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p4_avar_sharu)
		bVrlState[AZ + "sharu4"].setText(QString("%1").arg(mes->azn.bits.p4_sharu_code)) = ELEM_AVAR;
	else
		bVrlState[AZ + "sharu4"].setText(QString("%1").arg(mes->azn.bits.p4_sharu_code)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "sh1"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p1_int_noise >= AznShMaxValue)
		bVrlState[AZ + "sh1"].setText(QString("%1").arg(mes->azn.bits.p1_int_noise)) = ELEM_AVAR;
	else
		bVrlState[AZ + "sh1"].setText(QString("%1").arg(mes->azn.bits.p1_int_noise)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "sh2"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p2_int_noise >= AznShMaxValue)
		bVrlState[AZ + "sh2"].setText(QString("%1").arg(mes->azn.bits.p2_int_noise)) = ELEM_AVAR;
	else
		bVrlState[AZ + "sh2"].setText(QString("%1").arg(mes->azn.bits.p2_int_noise)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "sh3"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p3_int_noise >= AznShMaxValue)
		bVrlState[AZ + "sh3"].setText(QString("%1").arg(mes->azn.bits.p3_int_noise)) = ELEM_AVAR;
	else
		bVrlState[AZ + "sh3"].setText(QString("%1").arg(mes->azn.bits.p3_int_noise)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "sh4"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p4_int_noise >= AznShMaxValue)
		bVrlState[AZ + "sh4"].setText(QString("%1").arg(mes->azn.bits.p4_int_noise)) = ELEM_AVAR;
	else
		bVrlState[AZ + "sh4"].setText(QString("%1").arg(mes->azn.bits.p4_int_noise)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "amp1"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p1_amp <= AznAmpMinValue)
		bVrlState[AZ + "amp1"].setText(QString("%1").arg(mes->azn.bits.p1_amp)) = ELEM_AVAR;
	else
		bVrlState[AZ + "amp1"].setText(QString("%1").arg(mes->azn.bits.p1_amp)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "amp2"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p2_amp <= AznAmpMinValue)
		bVrlState[AZ + "amp2"].setText(QString("%1").arg(mes->azn.bits.p2_amp)) = ELEM_AVAR;
	else
		bVrlState[AZ + "amp2"].setText(QString("%1").arg(mes->azn.bits.p2_amp)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "amp3"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p3_amp <= AznAmpMinValue)
		bVrlState[AZ + "amp3"].setText(QString("%1").arg(mes->azn.bits.p3_amp)) = ELEM_AVAR;
	else
		bVrlState[AZ + "amp3"].setText(QString("%1").arg(mes->azn.bits.p3_amp)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "amp4"].setText("не измерено") = ELEM_NOT;
	else if(mes->azn.bits.p4_amp <= AznAmpMinValue)
		bVrlState[AZ + "amp4"].setText(QString("%1").arg(mes->azn.bits.p4_amp)) = ELEM_AVAR;
	else
		bVrlState[AZ + "amp4"].setText(QString("%1").arg(mes->azn.bits.p4_amp)) = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "att1"] = ELEM_NOT;
	else if(mes->azn.bits.p1_avar_atten)
		bVrlState[AZ + "att1"] = ELEM_AVAR;
	else
		bVrlState[AZ + "att1"] = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "att2"] = ELEM_NOT;
	else if(mes->azn.bits.p2_avar_atten)
		bVrlState[AZ + "att2"] = ELEM_AVAR;
	else
		bVrlState[AZ + "att2"] = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "att3"] = ELEM_NOT;
	else if(mes->azn.bits.p3_avar_atten)
		bVrlState[AZ + "att3"] = ELEM_AVAR;
	else
		bVrlState[AZ + "att3"] = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "att4"] = ELEM_NOT;
	else if(mes->azn.bits.p4_avar_atten)
		bVrlState[AZ + "att4"] = ELEM_AVAR;
	else
		bVrlState[AZ + "att4"] = ELEM_NORMA;

	if(!work || otklAzn)
		bVrlState[AZ + "obSost"] = ELEM_NOT;
	else if(mes->azn.bits.avar_prm || cntAvar > 0)
		bVrlState[AZ + "obSost"] = ELEM_AVAR;
	else if(cntError > 0)
		bVrlState[AZ + "obSost"] = ELEM_ERROR;
	else
		bVrlState[AZ + "obSost"] = ELEM_NORMA;
}

// ------------------------------------------------------------------
void VRL_SERVICE::process_obr(MESSAGE_209 * mes)
{
	quint32 num = mes->comp.bits.number - 1;
	QString N = QString("obr%1@").arg(num + 1);
	bVrlState[N + "obSost"] = ELEM_NORMA;
}

// ------------------------------------------------------------------
void VRL_SERVICE::process_zao(MESSAGE_209 * mes)
{
#ifdef FAKE_VRL
	mes->ao.bits.zao_connected = 0;
#endif
//	quint32 num = mes->comp.bits.number - 1;
	QString Z = QString("zao@");
	bool work = true;
	bool otklZao = !mes->ao.bits.zao_connected;

	if(!work || otklZao)
		bVrlState[Z + "connect"] = ELEM_NOT;
	else
		bVrlState[Z + "connect"] = ELEM_NORMA;

//	bVrlState[Z + "good"] = ELEM_NOT;
//	bVrlState[Z + "fail"] = ELEM_NOT;

	if(!work || otklZao)
		bVrlState[Z + "obSost"] = ELEM_NOT;
	else if(mes->ao.bits.zao_ikd || mes->ao.bits.zao_ikp)
		bVrlState[Z + "obSost"] = ELEM_NORMA;
	else
		bVrlState[Z + "obSost"] = ELEM_ERROR;
}

// ------------------------------------------------------------------
