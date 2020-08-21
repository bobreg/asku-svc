#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "voi_service.h"
#include "voi_thread.h"

// ------------------------------------------------------------------
VOI_SERVICE::VOI_SERVICE(VOI_THREAD *p)
{
	parent = p;
	network = NULL;
	timer = NULL;

	m_isInitialized = false;
	m_isConnected = false;
	m_voiConfig.main = false;
	m_status = -1;

	m_startedTimeout = STARTED_MAX_TIMEOUT;
	m_controlTimeout = 0;
	m_restartTimeout = 0;
	m_changedTimeout = 0;
	m_helloCounter = 0;

	m_avarPRL = 0;
	m_avarVRL = 0;
	m_avarNRZ = 0;
	m_avarAZN = 0;
	m_avarMPS = 0;

	m_rlkStateCounter = -1;

	m_haVoi = m_setup.voi.ip;//127.0.0.1
	m_portVoi = m_setup.voi.port_out;//0x4000
	m_portAsku = m_setup.voi.port_in;//0x4001
}

// ------------------------------------------------------------------
bool VOI_SERVICE::init()
{
	network = new UdpNetwork(this, QString("VOI_UDP"));
	if(network)
	{
		connect(network, SIGNAL(dataArrived(QByteArray,QHostAddress,quint16)), this, SLOT(onDataArrived(QByteArray,QHostAddress,quint16)));

		LogVoiInfo("VoiService started");
		m_isInitialized = network->init(m_portAsku);
	}

	sendHello();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
	timer->start(300);

	return false;
}

// ------------------------------------------------------------------
VOI_SERVICE::~VOI_SERVICE()
{
	if(timer)
	{
		timer->stop();
		delete timer;
		timer = NULL;
	}
	if(network)
	{
		network->close();
		delete network;
		network = NULL;
	}
}

// ------------------------------------------------------------------
bool VOI_SERVICE::isInitialized()
{
	return m_isInitialized;
}

// ------------------------------------------------------------------
void VOI_SERVICE::setMain(bool main)
{
	if(main != m_voiConfig.main)
	{
		m_voiConfig.main = main;
		cmdChangeReg(m_voiConfig.main, false);
	}
}

// ------------------------------------------------------------------
void VOI_SERVICE::setConnectedGpr()
{
}

// ------------------------------------------------------------------
void VOI_SERVICE::setDisconnectedGpr()
{
	clearOtherState();
}

// ------------------------------------------------------------------
void VOI_SERVICE::setRlsState(QVariantMap rlkState)
{
	m_rlkState = rlkState;

	if((m_rlkStateCounter < 0) || (m_rlkState != rlkState))
		m_rlkStateCounter = 0;
}

// ------------------------------------------------------------------
void VOI_SERVICE::setDisableSektors(QVariantMap disTable)
{
	if(m_disTable != disTable)
	{
		m_disTable = disTable;
		sendDisableSektors();
	}
}

// ------------------------------------------------------------------
void VOI_SERVICE::setControlSektor()
{
	sendSkr();
}

// ------------------------------------------------------------------
void VOI_SERVICE::cmdChangeReg(bool main, bool oper)
{
	if(m_isConnected)
	{
//		if(main)
//			mainWgt->pViewerASKU->AddSwitchMes("АСКУ","Команда в ВОИ - Режим Основной");
//		else
//			mainWgt->pViewerASKU->AddSwitchMes("АСКУ","Команда в ВОИ - Режим Резервный");

		if(main)
		{
			LogVoiInfo("VOI: command set main");
		}
		else
		{
			LogVoiInfo("VOI: command set reserve");
		}

		m_changedTimeout = CHANGED_MAX_TIMEOUT;
		sendCmdReg(main, oper);
	}
}

// ------------------------------------------------------------------
void VOI_SERVICE::timeout()
{
	checkTimeouts();

	if((!m_controlTimeout && m_isConnected) || (m_startedTimeout == 0))
	{
		disconnectVOI();
		m_helloCounter = 0;
		m_startedTimeout = -1;
		return;
	}
	if(m_isConnected)
	{
		sendLive();
	}
	else
	{
		if(!m_helloCounter)
			sendHello();
		else
			m_helloCounter--;
	}
}

// ------------------------------------------------------------------
void VOI_SERVICE::checkStatus()
{
	if(m_isConnected)
	{
		if(m_status == 0 && m_voiConfig.main == false) //main voi on slave asku
		{
			cmdChangeReg(m_voiConfig.main, false);
		}
		if(m_status == 1 && m_voiConfig.main == true) //slave voi on main asku
		{
			cmdChangeReg(m_voiConfig.main, false);
		}
	}
}

// ------------------------------------------------------------------
void VOI_SERVICE::connectVOI()
{
	if(!m_isConnected)
	{
		m_isConnected = true;
		m_startedTimeout = -1;
		bVoiLocalState["connected"] = ELEM_NORMA;
//		mainWgt->pViewerASKU->AddNormaMes("АСКУ","Установлена связь с ПО ВОИ");
		LogVoiInfo("VOI: connected");
	}
	else	//restart
	{
		m_restartTimeout = RESTART_MAX_TIMEOUT;
		bVoiLocalState["connected"] = ELEM_NORMA;
//		mainWgt->pViewerASKU->AddNormaMes("АСКУ","Выявлен перезапуск ВОИ");
//		mainWgt->uprComp->setReserveFlags(RESERVE_VOI_RST,TRUE);
		LogVoiInfo("VOI: connected on restart");
	}

	m_status = -1;
//	emit changedReg(m_status);
	sendSkr();
	sendDisableSektors();
}

// ------------------------------------------------------------------
void VOI_SERVICE::disconnectVOI()
{
	if(m_isConnected)
	{
		m_isConnected = false;
		clearLocalState();
		m_status = -1;
//		emit changedReg(m_status);
//		mainWgt->pViewerASKU->AddAvarMes("АСКУ","Нет связи с ПО ВОИ");
		LogVoiInfo("VOI: disconnected on timeout");
	}
}

// ------------------------------------------------------------------
void VOI_SERVICE::checkTimeouts()
{
	if(m_restartTimeout)
	{
		m_restartTimeout--;
//		if(m_restartTimeout==0)
//			mainWgt->uprComp->setReserveFlags(RESERVE_VOI_RST,FALSE);
	}
	
	if(m_startedTimeout > 0) m_startedTimeout--;
	if(m_controlTimeout) m_controlTimeout++;
	if(m_changedTimeout) m_changedTimeout--;
}

// ------------------------------------------------------------------
void VOI_SERVICE::sendToVOI(quint16 *buffer, quint16 num_words)
{
	if(network)
	{
		quint32 length = num_words*2;
		network->sendReply(QByteArray((const char*)buffer, length), m_haVoi, m_portVoi);
		LogVoiBinary("VOI: Send tc=%d Length=%d: %s",(*buffer)&0x00ff, length, LogArray(QByteArray((char*)buffer, length)));
	}
}

// ------------------------------------------------------------------
void VOI_SERVICE::onDataArrived(QByteArray array, QHostAddress haFrom, quint16 portFrom)
{
	Q_UNUSED(haFrom);
	Q_UNUSED(portFrom);

	quint16 *data = (quint16*)(char*)array.data();
	quint16 num_words = array.size() / 2;

	processData(data, num_words);
}

// ------------------------------------------------------------------
void VOI_SERVICE::processData(quint16 *data, quint16 num_words)
{
	static quint8 oldmes = 0;
	quint32 length = num_words * 2;
	quint32 tslength = 0;

	while(1)
	{
		LogVoiBinary("VOI: Recv tc=%d length=%d: %s", (*data)&0x00ff, length, LogArray(QByteArray((char*)data, length)));
		switch((*data)&0x00ff)
		{
			case TS_APP_CLOSE://64
				recvCloseApp((TC_VOI_64*)data);
				tslength = sizeof(TC_VOI_64);
				break;

			case TS_MOVE_WND://66
				recvMoveWindow((TC_VOI_66*)data);
				tslength = sizeof(TC_VOI_66);
				break;

			case TS_ON_MAIN://68
				recvChangedReg((TC_VOI_68*)data);
				tslength = sizeof(TC_VOI_68);
				break;

			case TS_HELLO://71
				recvHello((TC_VOI_71*)data);
				tslength = sizeof(TC_VOI_71);
				break;

			case TS_OTWET://72
				recvAnswer((TC_VOI_72*)data);
				tslength = sizeof(TC_VOI_72);
				break;

			case TS_RMO://74
			case TS_RMO_DT://75
				tslength = 2 * (*(data+1));
				break;

			case TS_NORM://76
				recvLive((TC_VOI_76*)data);
				tslength = sizeof(TC_VOI_76);
				break;

			case TS_GPS_RECEIVE://77
//				recvGpsData((TC_VOI_77*)data);
				tslength = 2 * (*(data+1));
				break;

			case TS_VOI_ERROR_WITH_GPS://84
				recvState((TC_VOI_84*)data);
				tslength = (((*data)&0xff00) >> 7);
				break;

			case TS_DIS_MAP://89
				recvDisable((TC_VOI_89*)data);
				tslength = 2 + (((*data)&0xff00) >> 8) * 4;
				break;

			default:
			{
				LogVoiError("VOI: Invalid message: TC=%d Length=%d NW=%d PrevTC=%d", (*data) & 0x00ff, length, num_words, oldmes);
				return;
			}
		}

		oldmes = (*data) & 0x00ff;

		length -= tslength;
		if(length > 0)
		{
			data += (tslength / 2);
			continue;
		}

		break;
	}
}

// ------------------------------------------------------------------
void VOI_SERVICE::sendHello()
{
	unsigned short wBuf = TS_HELLO;
	sendToVOI(&wBuf, 1);
	m_helloCounter = 3;
}

// ------------------------------------------------------------------
void VOI_SERVICE::sendAnswer()
{
	TC_VOI_72 tc;
	memset(&tc,0,sizeof(tc));
	tc.tc = TS_OTWET;
	sendToVOI((unsigned short*)&tc,sizeof(tc)/2);
}

// ------------------------------------------------------------------
void VOI_SERVICE::sendLive()
{
	TC_VOI_76 tc;
	memset(&tc,0,sizeof(tc));
	tc.tc = TS_NORM;
	sendToVOI((unsigned short*)&tc,sizeof(tc)/2);
}

// ------------------------------------------------------------------
void VOI_SERVICE::sendSkr()
{
	TC_VOI_73 tc;
	memset(&tc,0,sizeof(tc));
	tc.tc = TS_SKR_VOI;

	if(m_setup.skrps.period)
		tc.on = 1;
	else
		tc.on = 0;

	double unAz = 5.625 * m_setup.skrps.skr_azimuth;
	
	if(m_setup.skrps.offset)
	{
		unAz += 180;
		if(unAz >= 360)
			unAz -= 360;
	}

	unsigned short wAzSKRvoi = (unsigned short)(unAz * 0x8000 / 180);

	tc.azimuth = wAzSKRvoi;

	sendToVOI((unsigned short*)&tc,sizeof(tc)/2);
}

// ------------------------------------------------------------------
void VOI_SERVICE::sendHidePanel()
{
	TC_VOI_66 tc;
	memset(&tc,0,sizeof(tc));
	tc.tc = TS_MOVE_WND;
	sendToVOI((unsigned short*)&tc,sizeof(tc)/2);
}

// ------------------------------------------------------------------
void VOI_SERVICE::sendPressure(unsigned short pressure, bool avar)
{
	if(!avar)
	{
		TC_VOI_85 tc;
		memset(&tc,0,sizeof(tc));
		tc.tc  = TS_P_CODE;
		tc.length = 2;
		tc.pressure = pressure;
		tc.avar = avar;
		sendToVOI((unsigned short*)&tc,sizeof(tc)/2);
	}
}

// ------------------------------------------------------------------
void VOI_SERVICE::sendCmdReg(bool main, bool oper)
{
	TC_VOI_68 tc;
	memset(&tc,0,sizeof(tc));
	tc.tc = TS_ON_MAIN;
	tc.rez = main ? 0 : 1;
	tc.op = oper;
	sendToVOI((unsigned short*)&tc,sizeof(tc)/2);
}

// ------------------------------------------------------------------
void VOI_SERVICE::sendDisableSektors()
{
/*
  	unsigned char buffer[128];
	TC_VOI_86 *tc = (TC_VOI_86*)buffer;
	memset(buffer,0,sizeof(buffer));

	DT_TC_VOI_86 *mes = (DT_TC_VOI_86*)buffer_dt;
    memset(buffer_dt,0,sizeof(buffer_dt));

	mes->id = m_setup.nNumGpr;
	mes->ncomp = 0;
	mes->nparam = 1;
	mes->dt = 1;

	int count = table->count();
	if(count > 15) count = 15;
	int length = 4 * count + 2;

	tc->tc = 86;
    mes->ts.tc=tc->tc;

	tc->count = count;
	mes->ts.count = tc->count;

	for(int k = 0; k < count; k++)
	{
		unsigned short azBegin, azEnd;

		azBegin = (unsigned short)(((*table)[k].AzimuthBegin));
		
		if(m_setup.fSekZaprOffset)
		{
			azBegin+=180;
			if(azBegin>=360)
				azBegin-=360;
		}
		
		tc->sektor[k].begin = (azBegin*0x8000)/180;

        mes->ts.sektor[k].begin=tc->sektor[k].begin;
        
		azEnd = (unsigned short)(((*table)[k].AzimuthEnd));
		
		if(m_setup.fSekZaprOffset)
		{
			azEnd+=180;
			if(azEnd>=360)
				azEnd-=360;
		}
		
		tc->sektor[k].end = (azEnd*0x8000)/180;
		mes->ts.sektor[k].end = tc->sektor[k].end;

	}

  
/  *
QString str,str1;
unsigned short *buf = (unsigned short*)(buffer);
str.sprintf("VOI_86: %04X",buf[0]);
for(int q = 0; q < count*2; q++)
{
	str1.sprintf(" %04X",buf[q+1]);
	str += str1;
}
qDebug("%s",str.ascii());
*  /
 SendToVOI((unsigned short*)tc,length/2);
*/



//	TC_VOI_86 *tc = (TC_VOI_86*)bufferTS86onDT;
//	int length = 4 * tc->count + 2;
//	sendToVOI((unsigned short*)tc,length/2);
}

// ------------------------------------------------------------------
void VOI_SERVICE::sendRlsState()
{
//	TC_VOI_80 tc;
//	make_tc_80(tc);
//	sendToVOI((unsigned short*)&tc,sizeof(tc)/2);
}

// ------------------------------------------------------------------
void VOI_SERVICE::recvCloseApp(TC_VOI_64* tc)
{
	Q_UNUSED(tc);
	disconnectVOI();
}

// ------------------------------------------------------------------
void VOI_SERVICE::recvMoveWindow(TC_VOI_66* tc)
{
	Q_UNUSED(tc);
//	swX = tc->X; swY = tc->Y; swW = tc->W; swH = tc->H;
//	emit changeGeometry(swX,swY,swW,swH);
}

// ------------------------------------------------------------------
void VOI_SERVICE::recvChangedReg(TC_VOI_68* tc)
{
	if(tc->zr)
	{
//		printf("voi zr=1\n");
	}
	else if((int)tc->rez != m_status)
	{
//		if(tc->rez)
//			mainWgt->pViewerASKU->AddSwitchMes("ВОИ","Квитанция - Режим Резервный");
//		else
//			mainWgt->pViewerASKU->AddSwitchMes("ВОИ","Квитанция - Режим Основной");
		m_status = (int)tc->rez;
//		emit changedReg(m_status);
	}
}

// ------------------------------------------------------------------
void VOI_SERVICE::recvHello(TC_VOI_71* tc)
{
	Q_UNUSED(tc);

	m_controlTimeout = CONTROL_MAX_TIMEOUT;
	connectVOI();
	sendAnswer();
}

// ------------------------------------------------------------------
void VOI_SERVICE::recvAnswer(TC_VOI_72* tc)
{
	Q_UNUSED(tc);

	m_controlTimeout = CONTROL_MAX_TIMEOUT;
	connectVOI();
}

// ------------------------------------------------------------------
void VOI_SERVICE::recvLive(TC_VOI_76* tc)
{
	Q_UNUSED(tc);

	m_controlTimeout = CONTROL_MAX_TIMEOUT;
}

// ------------------------------------------------------------------
void VOI_SERVICE::recvGpsData(TC_VOI_77* tc)
{
	Q_UNUSED(tc);
}

// ------------------------------------------------------------------
void VOI_SERVICE::recvState(TC_VOI_84* tc)
{
	Q_UNUSED(tc);

	if(!m_isConnected) return;

	int rez = !tc->osn;
	if(rez != m_status)
	{
//		if(tc->osn)
//			mainWgt->pViewerASKU->AddSwitchMes(nameVOI,"Режим Основной");
//		else
//			mainWgt->pViewerASKU->AddSwitchMes(nameVOI,"Режим резервный");
		m_status = rez;
		//emit changedReg(m_status);
	}

	if(tc->osn)
		bVoiLocalState["VoiStatus"] = ELEM_NORMA;
	else
		bVoiLocalState["VoiStatus"] = ELEM_NOT;

	quint32 nAvar = 0, nError = 0;

	if(!tc->is_voi)
		bVoiLocalState["VoiNotCompleted"] = ELEM_NOT;
	else if(tc->svoi.bits.not_complete)
	{
		nAvar++;
		bVoiLocalState["VoiNotCompleted"] = ELEM_AVAR;
	}
	else
		bVoiLocalState["VoiNotCompleted"] = ELEM_NORMA;

	if(!tc->is_voi || !tc->is_azn)
		bVoiLocalState["VoiTimeAznError"] = ELEM_NOT;
	else if(tc->svoi.bits.time_azn_error)
	{
		nAvar++;
		bVoiLocalState["VoiTimeAznError"] = ELEM_AVAR;
	}
	else
		bVoiLocalState["VoiTimeAznError"] = ELEM_NORMA;

	if(!tc->is_voi)
		bVoiLocalState["VoiNetworkError"] = ELEM_NOT;
	else if(tc->svoi.bits.network_error)
	{
		nAvar++;
		bVoiLocalState["VoiNetworkError"] = ELEM_AVAR;
	}
	else
		bVoiLocalState["VoiNetworkError"] = ELEM_NORMA;

	if(!tc->is_voi || !tc->is_011 || tc->s011.bits.no_driver || tc->s011.bits.device_fault)
		bVoiLocalState["VoiUstError"] = ELEM_NOT;
	else if(tc->svoi.bits.azsens_error)
	{
		nAvar++;
		bVoiLocalState["VoiUstError"] = ELEM_AVAR;
	}
	else
		bVoiLocalState["VoiUstError"] = ELEM_NORMA;

	if(!tc->is_voi || !tc->is_011 || tc->s011.bits.no_driver || tc->s011.bits.device_fault)
		bVoiLocalState["VoiNoNord"] = ELEM_NOT;
	else if(tc->svoi.bits.no_nord)
	{
		nAvar++;
		bVoiLocalState["VoiNoNord"] = ELEM_AVAR;
	}
	else
		bVoiLocalState["VoiNoNord"] = ELEM_NORMA;

	if(!tc->is_voi || !tc->is_011 || tc->s011.bits.no_driver || tc->s011.bits.device_fault)
		bVoiLocalState["VoiNoMai"] = ELEM_NOT;
	else if(tc->svoi.bits.no_mai)
	{
		nAvar++;
		bVoiLocalState["VoiNoMai"] = ELEM_AVAR;
	}
	else
		bVoiLocalState["VoiNoMai"] = ELEM_NORMA;

	if(!tc->is_voi)
		bVoiLocalState["VoiComPortError"] = ELEM_NOT;
	else if(tc->svoi.bits.com_error)
	{
		nError++;
		bVoiLocalState["VoiComPortError"] = ELEM_AVAR;
	}
	else
		bVoiLocalState["VoiComPortError"] = ELEM_NORMA;

	if(!tc->is_voi)
	{
		m_avarPRL = 0;
		bVoiLocalState["VoiDataPrl"] = ELEM_NOT;
	}
	else if(tc->svoi.bits.no_prl)
	{
		if(m_avarPRL > AVAR_PRL_TIMEOUT && m_changedTimeout == 0)
		{
			nError++;
			bVoiLocalState["VoiDataPrl"] = ELEM_AVAR;
		}
		else
		{
			m_avarPRL++;
		}
	}
	else
	{
		m_avarPRL = 0;
		bVoiLocalState["VoiDataPrl"] = ELEM_NORMA;
	}

	if(!tc->is_voi)
	{
		m_avarVRL = 0;
		bVoiLocalState["VoiDataVrl"] = ELEM_NOT;
	}
	else if(tc->svoi.bits.no_vrl)
	{
		if(m_avarVRL > AVAR_VRL_TIMEOUT)
		{
			nError++;
			bVoiLocalState["VoiDataVrl"] = ELEM_AVAR;
		}
		else
		{
			m_avarVRL++;
		}
	}
	else
	{
		m_avarVRL = 0;
		bVoiLocalState["VoiDataVrl"] = ELEM_NORMA;
	}

	if(!tc->is_voi || !tc->is_nrz)
	{
		m_avarNRZ = 0;
		bVoiLocalState["VoiDataNrz"] = ELEM_NOT;
	}
	else if(tc->svoi.bits.no_nrz)
	{
		if(m_avarNRZ > AVAR_NRZ_TIMEOUT)
		{
			nError++;
			bVoiLocalState["VoiDataNrz"] = ELEM_AVAR;
		}
		else
		{
			m_avarNRZ++;
		}
	}
	else
	{
		m_avarNRZ = 0;
		bVoiLocalState["VoiDataNrz"] = ELEM_NORMA;
	}

	if(!tc->is_voi || !tc->is_azn)
	{
		m_avarAZN = 0;
		bVoiLocalState["VoiDataAzn"] = ELEM_NOT;
	}
	else if(tc->svoi.bits.no_azn)
	{
		if(m_avarAZN > AVAR_AZN_TIMEOUT)
		{
			nError++;
			bVoiLocalState["VoiDataAzn"] = ELEM_AVAR;
		}
		else
		{
			m_avarAZN++;
		}
	}
	else
	{
		m_avarAZN = 0;
		bVoiLocalState["VoiDataAzn"] = ELEM_NORMA;
	}

	if(!tc->is_voi || !tc->is_mpsn)
	{
		m_avarMPS = 0;
		bVoiLocalState["VoiDataMpsn"] = ELEM_NOT;
	}
	else if(tc->svoi.bits.no_mpsn)
	{
		if(m_avarMPS > AVAR_MPS_TIMEOUT)
		{
			nError++;
			bVoiLocalState["VoiDataMpsn"] = ELEM_AVAR;
		}
		else
		{
			m_avarMPS++;
		}
	}
	else
	{
		m_avarMPS = 0;
		bVoiLocalState["VoiDataMpsn"] = ELEM_NORMA;
	}

	if(bVoiLocalState["VoiDataPrl"]==ELEM_AVAR && bVoiLocalState["VoiDataNrz"]==ELEM_AVAR)
		nAvar++;

//SyncModule
	if(!tc->is_011)
		bVoiLocalState["ModuleDriver"] = ELEM_NOT;
	else if(tc->s011.bits.no_driver)
	{
		nAvar++;
		bVoiLocalState["ModuleDriver"] = ELEM_AVAR;
	}
	else
		bVoiLocalState["ModuleDriver"] = ELEM_NORMA;

	if(!tc->is_011 || tc->s011.bits.no_driver)
		bVoiLocalState["ModuleFailure"] = ELEM_NOT;
	else if(tc->s011.bits.device_fault)
	{
		nAvar++;
		bVoiLocalState["ModuleFailure"] = ELEM_AVAR;
	}
	else
		bVoiLocalState["ModuleFailure"] = ELEM_NORMA;

	if(!tc->is_011 || tc->s011.bits.no_driver || tc->s011.bits.device_fault)
		bVoiLocalState["ModuleTimeInvalid"] = ELEM_NOT;
	else if(tc->s011.bits.invalid_time)
	{
		nError++;
		bVoiLocalState["ModuleTimeInvalid"] = ELEM_AVAR;
	}
	else
		bVoiLocalState["ModuleTimeInvalid"] = ELEM_NORMA;

//ObSost
	if(nAvar)
		bVoiLocalState["ObSost"] = ELEM_AVAR;
	else if(nError)
		bVoiLocalState["ObSost"] = ELEM_ERROR;
	else
		bVoiLocalState["ObSost"] = ELEM_NORMA;

//Disable Command
	if(tc->is_disable)
		bVoiLocalState["DisableSVCH"] = ELEM_AVAR;
	else
		bVoiLocalState["DisableSVCH"] = ELEM_NORMA;

	emit sigStateLocal(bVoiLocalState);
	emit sigDisableTotal(tc->is_disable);

	checkStatus();
	syncToSlave();
}

// ------------------------------------------------------------------
void VOI_SERVICE::recvDisable(TC_VOI_89* tc)
{
	AskuSektorTable data;
	LogVoiInfo("set disable sektors [%d]:", tc->count);
	for(quint32 n = 0; n < tc->count; n++)
	{
		double sektor_begin = (double)(tc->sektor[n].begin) * 360.0 / 65536.0;
		double sektor_end   = (double)(tc->sektor[n].end  ) * 360.0 / 65536.0;

		LogVoiInfo("  begin: %7.3f end: %7.3f", sektor_begin, sektor_end);

		sektor_begin += 180.0;
		if(sektor_begin >= 360.0)
			sektor_begin -= 360.0;

		sektor_end   += 180.0;
		if(sektor_end >= 360.0)
			sektor_end -= 360.0;

		QVariantMap sektor;
		sektor["begin"] = sektor_begin;
		sektor["end"]   = sektor_end;

		data << sektor;
	}
	
	emit sigDisableDynamic(data);
	syncToSlave();
}

// ------------------------------------------------------------------
void VOI_SERVICE::clearLocalState()
{
	bVoiLocalState.clear(ELEM_NOT);
	bVoiLocalState["connected"] = ELEM_AVAR;
	emit sigStateLocal(bVoiLocalState);
	syncToSlave();
}

// ------------------------------------------------------------------
void VOI_SERVICE::clearOtherState()
{
	bVoiOtherState.clear(ELEM_NOT);
	emit sigStateOther(bVoiOtherState);
}

// ------------------------------------------------------------------
void VOI_SERVICE::syncToSlave()
{
	emit sigSyncToSlave(m_voiConfig.toMap(), bVoiLocalState.toMap());
}

// ------------------------------------------------------------------
void VOI_SERVICE::onSyncToSlave(QVariantMap config, QVariantMap state)
{
	if(!m_voiConfig.main)
	{
		VoiConfig m_masterConfig(config);
		if(m_masterConfig.main)
		{
			LogVoiInfo("VOI_SERVICE::onSyncToSlave processed");
//			qDebug() << "voiMasterConfig accepted";
		}
	}

//	qDebug() << "onSyncToSlave";
//	qDebug() << bVoiOtherState.toMap();
//	qDebug() << "-------------";

	if(bVoiOtherState.fromMap(state))
		emit sigStateOther(bVoiOtherState);
}

// ------------------------------------------------------------------
