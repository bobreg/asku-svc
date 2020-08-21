#include "../common/logger.h"
#include "../common/stateset.h"
#include "globalvar.h"
#include "canalasku.h"

//---------------------------------------------------------------------------------
void CanalAsku::onReadyData(CanalAskuData* data)
{
//	LogInfo("CanalAsku: ready data %d", data->getCount());
	algChannelAsku(data);
	makeDataMaps(data);
	makeMonitorPhase(data);
	checkFirstCommands(data);
//	checkCommandKits();
	checkCommandModules();
	syncToSlave();
	dataReady();
}

//---------------------------------------------------------------------------------
void CanalAsku::algChannelAsku(CanalAskuData * data)
{
	qint32 n_device;
	bool a[CA_N_DEVICES],b[CA_N_DEVICES];
	bool elements[CA_N_DEVICES+1];
 
	for(n_device = 0; n_device < CA_N_DEVICES; n_device++)
		a[n_device] = b[n_device] = false;

	for(n_device = 0; n_device < CA_N_DEVICES + 1; n_device++)
		elements[n_device] = false;

	qint32 dev_count = CA_N_DEVICES;

	quint32 addr[CA_N_DEVICES] = { CA_ELECTRO, CA_TRANSMITTER1, CA_TRANSMITTER2 };

	for(n_device = 0; n_device < dev_count; n_device++)
	{
		if(data->getPortActive() == 0)
		{
			bool state1 = (data->getTest1Error(addr[n_device]) == CA_NO_ERROR);
			bool state2 = (data->getTest2Error(addr[n_device]) == CA_NO_ERROR);
			a[n_device] = state2;
			b[n_device] = state1;
		}
		else
		{
			bool state1 = (data->getTest1Error(addr[n_device]) == CA_NO_ERROR);
			bool state2 = (data->getTest2Error(addr[n_device]) == CA_NO_ERROR);
			a[n_device] = state1;
			b[n_device] = state2;
		}
	}

	qint32 cnt_a = -1;
	for(n_device = 0; n_device < dev_count; n_device++)
	{
		if(a[n_device])
			cnt_a = n_device;
	}
/*
#ifndef NO_DEBUG
	QString strA = "a=";
	QString strAA;
	for(n_device = 0; n_device < dev_count; n_device++)
	{
		strAA.sprintf("%d ", a[n_device]);
		strA += strAA; 
	}
	strAA.sprintf("cnt_a=%d", cnt_a);
	strA += strAA;
	qDebug("%s", qPrintable(strA));
#endif
*/
	if(cnt_a != -1)
	{
		for(n_device = 0; n_device < cnt_a; n_device++)
			elements[n_device] = true;
	}

	qint32 cnt_b = -1;
	for(n_device = dev_count; n_device > 0; n_device--)
	{
		if(b[n_device - 1])
			cnt_b = n_device - 1;
	}
/*
#ifndef NO_DEBUG
	QString strB = "b=";
	QString strBB;
	for(n_device = 0; n_device < dev_count; n_device++)
	{
		strBB.sprintf("%d ", b[n_device]);
		strB += strBB; 
	}
	strBB.sprintf("cnt_b=%d", cnt_b);
	strB += strBB;
	qDebug("%s", qPrintable(strB));
#endif
*/
	if(cnt_b != -1)
	{
		for(n_device = dev_count; n_device >= cnt_b; n_device--)
			elements[n_device] = true;
	}
/*
#ifndef NO_DEBUG
	QString strE = "elements=";
	QString strEE;
	for(n_device = 0; n_device < dev_count + 1; n_device++)
	{
		strEE.sprintf("%d ",elements[n_device]);
		strE+=strEE; 
	}
	qDebug("%s", qPrintable(strE));
#endif
*/

//Port 1
	if(data->getPort1Status())
		cnl["Port1"] = ELEM_NORMA;
	else
		cnl["Port1"] = ELEM_NOT;

//Port 2
	if(data->getPort2Status())
		cnl["Port2"] = ELEM_NORMA;
	else
		cnl["Port2"] = ELEM_NOT;

	bool portFail = (cnl["Port1"] == ELEM_NOT) && (cnl["Port2"] == ELEM_NOT);

//	qDebug("ports: %d %d %d (%d %d)", quint8(cnl["Port1"]), quint8(cnl["Port2"]), portFail, cnl["Port1"] == ELEM_NOT, cnl["Port2"] == ELEM_NOT);

//OY1
	bool test1 = (data->getTest1Error(CA_ELECTRO) == CA_NO_ERROR);
	bool test2 = (data->getTest2Error(CA_ELECTRO) == CA_NO_ERROR);
	bool state = (data->getStateError(CA_ELECTRO) == CA_NO_ERROR);

//	qDebug("-------OY1 test1 = %d, test2 = %d, state = %d ------------", test1, test2, state);

	cnl["OY1_OS_TEST1"] = portFail ? ELEM_NOT : (test1 ? ELEM_NORMA : ELEM_AVAR);
	cnl["OY1_OS_TEST2"] = portFail ? ELEM_NOT : (test2 ? ELEM_NORMA : ELEM_AVAR);
	cnl["OY1_OS_STATE"] = portFail ? ELEM_NOT : (state ? ELEM_NORMA : ELEM_AVAR);

	if(portFail)
		cnl["OY1"] = ELEM_NOT;
	else if(test1 || test2 || state)
		cnl["OY1"] = ELEM_NORMA;
	else
		cnl["OY1"] = ELEM_AVAR;

//OY2
	test1 = (data->getTest1Error(CA_TRANSMITTER1) == CA_NO_ERROR);
	test2 = (data->getTest2Error(CA_TRANSMITTER1) == CA_NO_ERROR);
	state = (data->getStateError(CA_TRANSMITTER1) == CA_NO_ERROR);

//	qDebug("-------OY2 test1 = %d, test2 = %d, state = %d ------------", test1, test2, state);

	cnl["OY2_OS_TEST1"] = portFail ? ELEM_NOT : (test1 ? ELEM_NORMA : ELEM_AVAR);
	cnl["OY2_OS_TEST2"] = portFail ? ELEM_NOT : (test2 ? ELEM_NORMA : ELEM_AVAR);
	cnl["OY2_OS_STATE"] = portFail ? ELEM_NOT : (state ? ELEM_NORMA : ELEM_AVAR);

	for(quint32 n_module_umi = 0; n_module_umi < CA_N_MODULES_UMI; n_module_umi++)
	{
		bool param_umi = (data->getParamUmiError(CA_TRANSMITTER1, n_module_umi) == CA_NO_ERROR);
		cnl[QString("OY2_OS_UMI_%1").arg(n_module_umi + 1)] = portFail ? ELEM_NOT : (param_umi ? ELEM_NORMA : ELEM_AVAR);
	}

	if(portFail)
		cnl["OY2"] = ELEM_NOT;
	else if(test1 || test2 || state)
		cnl["OY2"] = ELEM_NORMA;
	else
		cnl["OY2"] = ELEM_AVAR;

//OY3
	test1 = (data->getTest1Error(CA_TRANSMITTER2) == CA_NO_ERROR);
	test2 = (data->getTest2Error(CA_TRANSMITTER2) == CA_NO_ERROR);
	state = (data->getStateError(CA_TRANSMITTER2) == CA_NO_ERROR);
	
//	qDebug("-------OY3 test1 = %d, test2 = %d, state = %d ------------", test1, test2, state);

	for(quint32 module = 0; module < CA_N_MODULES_UMI; module++)
	{
		bool param_umi = (data->getParamUmiError(CA_TRANSMITTER2, module) == CA_NO_ERROR);
		cnl[QString("OY3_OS_UMI_%1").arg(module + 1)] = param_umi ? ELEM_NORMA : ELEM_AVAR;
	}

	cnl["OY3_OS_TEST1"] = portFail ? ELEM_NOT : (test1 ? ELEM_NORMA : ELEM_AVAR);
	cnl["OY3_OS_TEST2"] = portFail ? ELEM_NOT : (test2 ? ELEM_NORMA : ELEM_AVAR);
	cnl["OY3_OS_STATE"] = portFail ? ELEM_NOT : (state ? ELEM_NORMA : ELEM_AVAR);

	if(portFail)
		cnl["OY3"] = ELEM_NOT;
	else if(test1 || test2 || state)
		cnl["OY3"] = ELEM_NORMA;
	else
		cnl["OY3"] = ELEM_AVAR;

//EL1, EL2
	if((cnl["Port1"] == ELEM_NOT) && (cnl["Port2"] == ELEM_NOT))
		cnl["EL2"] = cnl["EL1"] = ELEM_NOT;
	else if(cnl["Port1"] == ELEM_NOT)
		cnl["EL2"] = cnl["EL1"] = ELEM_NOT;
	else if(elements[0])
		cnl["EL2"] = cnl["EL1"] = ELEM_NORMA;
	else
		cnl["EL2"] = cnl["EL1"] = ELEM_AVAR;

//EL3
	if((cnl["Port1"] == ELEM_NOT) && (cnl["Port2"] == ELEM_NOT))
		cnl["EL3"] = ELEM_NOT;
	else if(elements[1])
		cnl["EL3"] = ELEM_NORMA;
	else
		cnl["EL3"] = ELEM_AVAR;

//EL4, EL5
	if((cnl["Port1"] == ELEM_NOT) && (cnl["Port2"] == ELEM_NOT))
		cnl["EL5"] = cnl["EL4"] = ELEM_NOT;
	else if(cnl["Port2"] == ELEM_NOT)
		cnl["EL5"] = cnl["EL4"] = ELEM_NOT;
	else if(elements[2] || elements[3])
		cnl["EL5"] = cnl["EL4"] = ELEM_NORMA;
	else
		cnl["EL5"] = cnl["EL4"] = ELEM_AVAR;

//Comm1, Comm2
	if(cnl["Port1"] == ELEM_NOT)
		cnl["Comm1"] = ELEM_AVAR;
	else
		cnl["Comm1"] = ELEM_NORMA;

	if(cnl["Port2"] == ELEM_NOT)
		cnl["Comm2"] = ELEM_AVAR;
	else
		cnl["Comm2"] = ELEM_NORMA;

//ObSost
	if((cnl["Port1"] == ELEM_NOT) && (cnl["Port2"] == ELEM_NOT))
		cnl["ObSost"] = ELEM_AVAR;
	else if(((cnl["EL1"] == ELEM_NOT) && (cnl["EL5"] == ELEM_AVAR)) ||
			((cnl["EL1"] == ELEM_AVAR) && (cnl["EL5"] == ELEM_NOT)) ||
			((cnl["EL1"] == ELEM_AVAR) && (cnl["EL5"] == ELEM_AVAR)) ||
			((cnl["OY1"] == ELEM_AVAR) || (cnl["OY2"] == ELEM_AVAR && cnl["OY3"] == ELEM_AVAR)))
		cnl["ObSost"] = ELEM_AVAR;
	else if((cnl["Port1"] == ELEM_AVAR) || (cnl["Port2"] == ELEM_AVAR) || (cnl["Comm1"] == ELEM_AVAR) || (cnl["Comm2"] == ELEM_AVAR) ||
			(cnl["EL1"] == ELEM_AVAR) || (cnl["EL3"] == ELEM_AVAR) || (cnl["EL5"] == ELEM_AVAR) ||
			(cnl["OY2"] == ELEM_AVAR) || (cnl["OY3"] == ELEM_AVAR))
		cnl["ObSost"] = ELEM_ERROR;
	else
		cnl["ObSost"] = ELEM_NORMA;

//	qDebug() << cnl.dump();

	emit sigState(cnl);
}

//--------------------------------------------------------------
QVariantMap CanalAsku::getCanalAskuStateLocal()
{
	return cnl.toMap();
}

//--------------------------------------------------------------
void CanalAsku::setCanalAskuStateOther(const QVariantMap & state)
{
	if(!isMain() && cnl.fromMap(state))
	{
//qDebug() << "CANALASKU_STATE_FROM_OTHER";
		emit sigState(cnl);
	}
}

//---------------------------------------------------------------------------------
#define MAKE_SIGNAL(a, b, c) a["elk_"#c] = b.BitsN.c;
#define MAKE_SIGNAL1(a, b, c) a["elk_"#c] = b.Bits.c;
#define MAKE_VALUE(a, b, c) a["value_"#c] = b;
#define MAKE_SIGNAL2(a, b, c) a["prd1_"#c] = b[0].BitsN.c; a["prd2_"#c] = b[1].BitsN.c;
#define MAKE_SIGNAL3(a, b, c) a["prd1_"#c] = b[0].Bits.c; a["prd2_"#c] = b[1].Bits.c;
#define MAKE_UMI_SIGNAL1(a, b, c, d, e) a[QString("prd%1_umi%2_"#e).arg(b+1).arg(c+1)] = d[b][c].v5.control1.bits.e;
#define MAKE_UMI_SIGNAL2(a, b, c, d, e) a[QString("prd%1_umi%2_"#e).arg(b+1).arg(c+1)] = d[b][c].v5.control2.bits.e;
#define MAKE_UMI_VALUE(a, b, c, d, e) a[QString("value_prd%1_umi%2_"#e).arg(b+1).arg(c+1)] = d[b][c].v5.e;
//---------------------------------------------------------------------------------
void CanalAsku::makeDataMaps(CanalAskuData* data)
{
	AskuSignalSet sigMap;
	AskuValueSet valMap;

	elk1b.Byte = data->getState(CA_ELECTRO,0);
	elk2b.Byte = data->getState(CA_ELECTRO,1);
	elk3b.Byte = data->getState(CA_ELECTRO,2);
	elk4b.Byte = data->getState(CA_ELECTRO,3);
	elk5b.Byte = data->getState(CA_ELECTRO,4);
	elk6b.Byte = data->getState(CA_ELECTRO,5);
	elk7b.Byte = data->getState(CA_ELECTRO,6);
	elk8b.Byte = data->getState(CA_ELECTRO,7);
	elk9b.Byte = data->getState(CA_ELECTRO,8);
	elk10b.Byte = data->getState(CA_ELECTRO,9);
	elk11b.Byte = data->getState(CA_ELECTRO,10);
	elk12b.Byte = data->getState(CA_ELECTRO,11);
	elk13b.Byte = data->getState(CA_ELECTRO,12);
	elk14b.Byte = data->getState(CA_ELECTRO,13);
	elk15b.Byte = data->getState(CA_ELECTRO,14);
	elk16b.Byte = data->getState(CA_ELECTRO,15);
	elk17b.Byte = data->getState(CA_ELECTRO,16);
	elk18b.Byte = data->getState(CA_ELECTRO,17);
	elk19b.Byte = data->getState(CA_ELECTRO,18);
	elk2021b.Bytes.Lo = data->getState(CA_ELECTRO,19);
	elk2021b.Bytes.Hi = data->getState(CA_ELECTRO,20);
	elk2223b.Bytes.Lo = data->getState(CA_ELECTRO,21);
	elk2223b.Bytes.Hi = data->getState(CA_ELECTRO,22);
	elk2425b.Bytes.Lo = data->getState(CA_ELECTRO,23);
	elk2425b.Bytes.Hi = data->getState(CA_ELECTRO,24);
	elk2627b.Bytes.Lo = data->getState(CA_ELECTRO,25);
	elk2627b.Bytes.Hi = data->getState(CA_ELECTRO,26);
	elk2829b.Bytes.Lo = data->getState(CA_ELECTRO,27);
	elk2829b.Bytes.Hi = data->getState(CA_ELECTRO,28);
	elk3031b.Bytes.Lo = data->getState(CA_ELECTRO,29);
	elk3031b.Bytes.Hi = data->getState(CA_ELECTRO,30);
	elk3233b.Bytes.Lo = data->getState(CA_ELECTRO,31);
	elk3233b.Bytes.Hi = data->getState(CA_ELECTRO,32);
	elk34b.Byte = data->getState(CA_ELECTRO,33);
	elkBPU.Byte = data->getTest2(CA_ELECTRO,0);

	prd1b[0].Byte = data->getState(CA_TRANSMITTER1,0);
	prd2b[0].Byte = data->getState(CA_TRANSMITTER1,1);
	prd3b[0].Byte = data->getState(CA_TRANSMITTER1,2);
	prd4b[0].Byte = data->getState(CA_TRANSMITTER1,3);
	prd5b[0].Byte = data->getState(CA_TRANSMITTER1,4);
	prd6b[0].Byte = data->getState(CA_TRANSMITTER1,5);
	prd7b[0].Byte = data->getState(CA_TRANSMITTER1,6);
	prd8b[0].Byte = data->getState(CA_TRANSMITTER1,7);
	prd9b[0].Byte = data->getState(CA_TRANSMITTER1,8);
	prd10b[0].Byte = data->getState(CA_TRANSMITTER1,9);
	prd11b[0].Byte = data->getState(CA_TRANSMITTER1,10);
	prd12b[0].Byte = data->getState(CA_TRANSMITTER1,11);

	prdBPU1b[0].Byte = data->getTest2(CA_TRANSMITTER1,0);
	prdBPU2b[0].Byte = data->getTest2(CA_TRANSMITTER1,1);
	prdBPU3b[0].Byte = data->getTest2(CA_TRANSMITTER1,2);
	prdBPU4b[0].Byte = data->getTest2(CA_TRANSMITTER1,3);
	prdBPU5b[0].Byte = data->getTest2(CA_TRANSMITTER1,4);
	prdBPU6b[0].Byte = data->getTest2(CA_TRANSMITTER1,5);

	prd1b[1].Byte = data->getState(CA_TRANSMITTER2,0);
	prd2b[1].Byte = data->getState(CA_TRANSMITTER2,1);
	prd3b[1].Byte = data->getState(CA_TRANSMITTER2,2);
	prd4b[1].Byte = data->getState(CA_TRANSMITTER2,3);
	prd5b[1].Byte = data->getState(CA_TRANSMITTER2,4);
	prd6b[1].Byte = data->getState(CA_TRANSMITTER2,5);
	prd7b[1].Byte = data->getState(CA_TRANSMITTER2,6);
	prd8b[1].Byte = data->getState(CA_TRANSMITTER2,7);
	prd9b[1].Byte = data->getState(CA_TRANSMITTER2,8);
	prd10b[1].Byte = data->getState(CA_TRANSMITTER2,9);
	prd11b[1].Byte = data->getState(CA_TRANSMITTER2,10);
	prd12b[1].Byte = data->getState(CA_TRANSMITTER2,11);

	prdBPU1b[1].Byte = data->getTest2(CA_TRANSMITTER2,0);
	prdBPU2b[1].Byte = data->getTest2(CA_TRANSMITTER2,1);
	prdBPU3b[1].Byte = data->getTest2(CA_TRANSMITTER2,2);
	prdBPU4b[1].Byte = data->getTest2(CA_TRANSMITTER2,3);
	prdBPU5b[1].Byte = data->getTest2(CA_TRANSMITTER2,4);
	prdBPU6b[1].Byte = data->getTest2(CA_TRANSMITTER2,5);

	for(quint32 n_module = 0; n_module < CA_N_MODULES_UMI; n_module++)
	{
		data->getParamUmi(CA_TRANSMITTER1, n_module, (quint8*)(&paramUMI[0][n_module]), sizeof(PRD_PARAM_UMI));
		data->getParamUmi(CA_TRANSMITTER2, n_module, (quint8*)(&paramUMI[1][n_module]), sizeof(PRD_PARAM_UMI));
	}

//ELK
	MAKE_SIGNAL(sigMap, elk1b, qf_123bb01_1);
	MAKE_SIGNAL(sigMap, elk1b, qf_123bb01_2);
	MAKE_SIGNAL(sigMap, elk1b, qf_123bb01_3);
	MAKE_SIGNAL(sigMap, elk1b, qf_123bb01_4);
	MAKE_SIGNAL(sigMap, elk1b, qf_27v_buf);
	MAKE_SIGNAL(sigMap, elk1b, qf_rozet_220v);
	MAKE_SIGNAL(sigMap, elk1b, qf_cond1);
	MAKE_SIGNAL(sigMap, elk1b, qf_cond2);

	MAKE_SIGNAL(sigMap, elk2b, qf_kmvrl1);
	MAKE_SIGNAL(sigMap, elk2b, qf_kmvrl2);
	MAKE_SIGNAL(sigMap, elk2b, qf_teplovent);
	MAKE_SIGNAL(sigMap, elk2b, qf_124yg02);
	MAKE_SIGNAL(sigMap, elk2b, qf_avar_osv);
	MAKE_SIGNAL(sigMap, elk2b, qf_380v_rpu);
	MAKE_SIGNAL(sigMap, elk2b, qf_380v_set);
	MAKE_SIGNAL(sigMap, elk2b, qf_124yy03_1);

	MAKE_SIGNAL(sigMap, elk3b, qf_124yy03_2);
	MAKE_SIGNAL(sigMap, elk3b, qf_prm1);
	MAKE_SIGNAL(sigMap, elk3b, qf_prm2);
	MAKE_SIGNAL(sigMap, elk3b, qf_prd1);
	MAKE_SIGNAL(sigMap, elk3b, qf_prd2);
	MAKE_SIGNAL(sigMap, elk3b, qf_obr1);
	MAKE_SIGNAL(sigMap, elk3b, qf_obr2);
	MAKE_SIGNAL(sigMap, elk3b, qf_ups1);

	MAKE_SIGNAL(sigMap, elk4b, qf_ups2);
	MAKE_SIGNAL(sigMap, elk4b, otkl_cont_380v);
	MAKE_SIGNAL(sigMap, elk4b, p27v_gsh);
	MAKE_SIGNAL(sigMap, elk4b, ups1_error);
	MAKE_SIGNAL(sigMap, elk4b, ups2_error);
	MAKE_SIGNAL(sigMap, elk4b, p27v_123bb02);
	MAKE_SIGNAL(sigMap, elk4b, p27v_pit_avt);
	MAKE_SIGNAL(sigMap, elk4b, p27v_howl1);

	MAKE_SIGNAL(sigMap, elk5b, p27v_howl2);
	MAKE_SIGNAL(sigMap, elk5b, p27v_prm1);
	MAKE_SIGNAL(sigMap, elk5b, p27v_prm2);
	MAKE_SIGNAL(sigMap, elk5b, p27v_mspd);
	MAKE_SIGNAL(sigMap, elk5b, p27v_zu1);
	MAKE_SIGNAL(sigMap, elk5b, p27v_zu2);
	MAKE_SIGNAL(sigMap, elk5b, p27v_ps1);
	MAKE_SIGNAL(sigMap, elk5b, p27v_ps2);

	MAKE_SIGNAL(sigMap, elk6b, p27v_123gv02_1);
	MAKE_SIGNAL(sigMap, elk6b, p27v_123gv02_2);
	MAKE_SIGNAL(sigMap, elk6b, p27v_azs1);
	MAKE_SIGNAL(sigMap, elk6b, p27v_azs2);
	MAKE_SIGNAL(sigMap, elk6b, accum_24v);
	MAKE_SIGNAL(sigMap, elk6b, work_cond_1);
	MAKE_SIGNAL(sigMap, elk6b, p27v_opu);
	MAKE_SIGNAL(sigMap, elk6b, avar124yg02);

	MAKE_SIGNAL(sigMap, elk7b, norma_123bb01_1);
	MAKE_SIGNAL(sigMap, elk7b, norma_123bb01_2);
	MAKE_SIGNAL(sigMap, elk7b, norma_123bb01_3);
	MAKE_SIGNAL(sigMap, elk7b, norma_123bb01_4);
	MAKE_SIGNAL(sigMap, elk7b, avar_123bb01_1);
	MAKE_SIGNAL(sigMap, elk7b, avar_123bb01_2);
	MAKE_SIGNAL(sigMap, elk7b, avar_123bb01_3);
	MAKE_SIGNAL(sigMap, elk7b, avar_123bb01_4);

	MAKE_SIGNAL(sigMap, elk8b, aorls);
	MAKE_SIGNAL(sigMap, elk8b, opu_open);
	MAKE_SIGNAL(sigMap, elk8b, qf_sotr);
	MAKE_SIGNAL(sigMap, elk8b, qf_pos);
	MAKE_SIGNAL(sigMap, elk8b, qf_27v_c);
	MAKE_SIGNAL(sigMap, elk8b, qf_trm);
	MAKE_SIGNAL(sigMap, elk8b, qf_osv_apm);
	MAKE_SIGNAL(sigMap, elk8b, vkl_cont_osv_perim);

	MAKE_SIGNAL(sigMap, elk9b, qf_accum);
	MAKE_SIGNAL(sigMap, elk9b, avar_sotr);
	MAKE_SIGNAL(sigMap, elk9b, qf_osv_perim);
	MAKE_SIGNAL(sigMap, elk9b, work_cond_2);
	MAKE_SIGNAL(sigMap, elk9b, p27v_pit_signal);
	MAKE_SIGNAL(sigMap, elk9b, p27v_124yy03_1);
	MAKE_SIGNAL(sigMap, elk9b, p27v_124yy03_2);
	MAKE_SIGNAL(sigMap, elk9b, avar_zasl_1);

	MAKE_SIGNAL(sigMap, elk10b, avar_zasl_2);
	MAKE_SIGNAL(sigMap, elk10b, avar_zasl_3);
	MAKE_SIGNAL(sigMap, elk10b, avar_zasl_4);
	MAKE_SIGNAL(sigMap, elk10b, vkl_vent_sotr_1);
	MAKE_SIGNAL(sigMap, elk10b, vkl_vent_sotr_2);
	MAKE_SIGNAL(sigMap, elk10b, obmen_sotr_1);
	MAKE_SIGNAL(sigMap, elk10b, obmen_sotr_2);
	MAKE_SIGNAL(sigMap, elk10b, obmen_sotr_3);

	MAKE_SIGNAL(sigMap, elk11b, obmen_sotr_4);
	MAKE_SIGNAL(sigMap, elk11b, zasl_1_opened);
	MAKE_SIGNAL(sigMap, elk11b, zasl_1_closed);
	MAKE_SIGNAL(sigMap, elk11b, zasl_2_opened);
//	MAKE_SIGNAL(sigMap, elk11b, reserv_1);
//	MAKE_SIGNAL(sigMap, elk11b, reserv_2);
//	MAKE_SIGNAL(sigMap, elk11b, reserv_3);
//	MAKE_SIGNAL(sigMap, elk11b, reserv_4);

	MAKE_SIGNAL(sigMap, elk12b, zasl_2_closed);
	MAKE_SIGNAL(sigMap, elk12b, zasl_3_opened);
	MAKE_SIGNAL(sigMap, elk12b, zasl_3_closed);
	MAKE_SIGNAL(sigMap, elk12b, zasl_4_opened);
	MAKE_SIGNAL(sigMap, elk12b, zasl_4_closed);
	MAKE_SIGNAL(sigMap, elk12b, mest);
	MAKE_SIGNAL(sigMap, elk12b, avar_pit_zasl_1);
	MAKE_SIGNAL(sigMap, elk12b, avar_pit_zasl_2);

	MAKE_SIGNAL(sigMap, elk13b, avar_pit_zasl_3);
	MAKE_SIGNAL(sigMap, elk13b, avar_pit_zasl_4);
	MAKE_SIGNAL(sigMap, elk13b, avar_vent_sotr_1);
	MAKE_SIGNAL(sigMap, elk13b, avar_vent_sotr_2);
	MAKE_SIGNAL(sigMap, elk13b, avar_cond_1);
	MAKE_SIGNAL(sigMap, elk13b, avar_cond_2);
	MAKE_SIGNAL(sigMap, elk13b, block_opu);
	MAKE_SIGNAL(sigMap, elk13b, avar_vent_12);

	MAKE_SIGNAL(sigMap, elk14b, cond1_kz_dt_vh_1);
	MAKE_SIGNAL(sigMap, elk14b, cond1_hh_dt_vh_1);
	MAKE_SIGNAL(sigMap, elk14b, cond1_kz_dt_vh_2);
	MAKE_SIGNAL(sigMap, elk14b, cond1_hh_dt_vh_2);
	MAKE_SIGNAL(sigMap, elk14b, cond1_avar_dvig_compr);
	MAKE_SIGNAL(sigMap, elk14b, cond1_avar_davl_rd1);
	MAKE_SIGNAL(sigMap, elk14b, cond1_avar_davl_rd2);
	MAKE_SIGNAL(sigMap, elk14b, cond1_avar_min_davl_vsas);

	MAKE_SIGNAL(sigMap, elk15b, cond1_avar_max_davl_nagn);
	MAKE_SIGNAL(sigMap, elk15b, cond1_avar_vent_recirc);
	MAKE_SIGNAL(sigMap, elk15b, cond1_avar_vent_kondens);
	MAKE_SIGNAL(sigMap, elk15b, cond2_kz_dt_vh_1);
	MAKE_SIGNAL(sigMap, elk15b, cond2_hh_dt_vh_1);
	MAKE_SIGNAL(sigMap, elk15b, cond2_kz_dt_vh_2);
	MAKE_SIGNAL(sigMap, elk15b, cond2_hh_dt_vh_2);
	MAKE_SIGNAL(sigMap, elk15b, cond2_avar_dvig_compr);

	MAKE_SIGNAL(sigMap, elk16b, cond2_avar_davl_rd1);
	MAKE_SIGNAL(sigMap, elk16b, cond2_avar_davl_rd2);
	MAKE_SIGNAL(sigMap, elk16b, cond2_avar_min_davl_vsas);
	MAKE_SIGNAL(sigMap, elk16b, cond2_avar_max_davl_nagn);
	MAKE_SIGNAL(sigMap, elk16b, cond2_avar_vent_recirc);
	MAKE_SIGNAL(sigMap, elk16b, cond2_avar_vent_kondens);
	MAKE_SIGNAL(sigMap, elk16b, p27v_a_15_17);
	MAKE_SIGNAL(sigMap, elk16b, p27v_a_18_20);

	MAKE_SIGNAL(sigMap, elk17b, cond1_ventile);
	MAKE_SIGNAL(sigMap, elk17b, cond1_vent_recirc);
	MAKE_SIGNAL(sigMap, elk17b, cond1_vent_kondens);
	MAKE_SIGNAL(sigMap, elk17b, cond1_vkl);
	MAKE_SIGNAL(sigMap, elk17b, cond1_kontroller);
	MAKE_SIGNAL(sigMap, elk17b, cond1_avar_kontroller);
	MAKE_SIGNAL(sigMap, elk17b, put_reset_avar);
	MAKE_SIGNAL(sigMap, elk17b, cond1_link);

	MAKE_SIGNAL(sigMap, elk18b, cond2_ventile);
	MAKE_SIGNAL(sigMap, elk18b, cond2_vent_recirc);
	MAKE_SIGNAL(sigMap, elk18b, cond2_vent_kondens);
	MAKE_SIGNAL(sigMap, elk18b, cond2_vkl);
	MAKE_SIGNAL(sigMap, elk18b, cond2_kontroller);
	MAKE_SIGNAL(sigMap, elk18b, cond2_avar_kontroller);
	MAKE_SIGNAL(sigMap, elk18b, reserved);
	MAKE_SIGNAL(sigMap, elk18b, cond2_link);

	MAKE_SIGNAL(sigMap, elk19b, error_sotr_1);
	MAKE_SIGNAL(sigMap, elk19b, error_sotr_2);
	MAKE_SIGNAL(sigMap, elk19b, error_sotr_3);
	MAKE_SIGNAL(sigMap, elk19b, error_sotr_4);
	MAKE_SIGNAL(sigMap, elk19b, t_below_5);
	MAKE_SIGNAL(sigMap, elk19b, t_over_30);
	MAKE_SIGNAL(sigMap, elk19b, avar_pvu);
	MAKE_SIGNAL(sigMap, elk19b, p27v_a_31_32);

	MAKE_SIGNAL(sigMap, elk34b, avar_d1);
	MAKE_SIGNAL(sigMap, elk34b, avar_d2);
	MAKE_SIGNAL(sigMap, elk34b, avar_d3);
	MAKE_SIGNAL(sigMap, elk34b, avar_d4);
	MAKE_SIGNAL(sigMap, elk34b, avar_d5);
	MAKE_SIGNAL(sigMap, elk34b, avar_d6);
	MAKE_SIGNAL(sigMap, elk34b, avar_d7);
//	MAKE_SIGNAL(sigMap, elk34b, rez);

	MAKE_SIGNAL1(sigMap, elkBPU, avarBPU);

//PRD'S
	MAKE_SIGNAL2(sigMap, prd1b, mest);
	MAKE_SIGNAL2(sigMap, prd1b, vkl27v);
	MAKE_SIGNAL2(sigMap, prd1b, avar27v);
	MAKE_SIGNAL2(sigMap, prd1b, norma123bb01_1);
	MAKE_SIGNAL2(sigMap, prd1b, qf123bb01_1);
	MAKE_SIGNAL2(sigMap, prd1b, norma123bb01_2);
	MAKE_SIGNAL2(sigMap, prd1b, qf123bb01_2);
	MAKE_SIGNAL2(sigMap, prd1b, normaSVChComm);

	MAKE_SIGNAL2(sigMap, prd2b, vkl123gv02);
	MAKE_SIGNAL2(sigMap, prd2b, avar123gv02);
	MAKE_SIGNAL2(sigMap, prd2b, qf123gv02);
	MAKE_SIGNAL2(sigMap, prd2b, vkl380);
	MAKE_SIGNAL2(sigMap, prd2b, normaPrd);
	MAKE_SIGNAL2(sigMap, prd2b, errorPrd);
	MAKE_SIGNAL2(sigMap, prd2b, avarPrd);
	MAKE_SIGNAL2(sigMap, prd2b, qfChp1);

	MAKE_SIGNAL2(sigMap, prd3b, qfChp2);
	MAKE_SIGNAL2(sigMap, prd3b, umi1Avar);
	MAKE_SIGNAL2(sigMap, prd3b, umi1Link);
	MAKE_SIGNAL2(sigMap, prd3b, umi2Avar);
	MAKE_SIGNAL2(sigMap, prd3b, umi2Link);
	MAKE_SIGNAL2(sigMap, prd3b, umi3Avar);
	MAKE_SIGNAL2(sigMap, prd3b, umi3Link);
	MAKE_SIGNAL2(sigMap, prd3b, umi4Avar);

	MAKE_SIGNAL2(sigMap, prd4b, umi4Link);
	MAKE_SIGNAL2(sigMap, prd4b, umi5Avar);
	MAKE_SIGNAL2(sigMap, prd4b, umi5Link);
	MAKE_SIGNAL2(sigMap, prd4b, umi6Avar);
	MAKE_SIGNAL2(sigMap, prd4b, umi6Link);
	MAKE_SIGNAL2(sigMap, prd4b, umi7Avar);
	MAKE_SIGNAL2(sigMap, prd4b, umi7Link);
	MAKE_SIGNAL2(sigMap, prd4b, umi8Avar);

	MAKE_SIGNAL2(sigMap, prd5b, umi8Link);
	MAKE_SIGNAL2(sigMap, prd5b, umi9Avar);
	MAKE_SIGNAL2(sigMap, prd5b, umi9Link);
	MAKE_SIGNAL2(sigMap, prd5b, umi10Avar);
	MAKE_SIGNAL2(sigMap, prd5b, umi10Link);
	MAKE_SIGNAL2(sigMap, prd5b, umi11Avar);
	MAKE_SIGNAL2(sigMap, prd5b, umi11Link);
	MAKE_SIGNAL2(sigMap, prd5b, umi12Avar);

	MAKE_SIGNAL2(sigMap, prd6b, umi12Link);
	MAKE_SIGNAL2(sigMap, prd6b, umi13Avar);
	MAKE_SIGNAL2(sigMap, prd6b, umi13Link);
	MAKE_SIGNAL2(sigMap, prd6b, umi14Avar);
	MAKE_SIGNAL2(sigMap, prd6b, umi14Link);
	MAKE_SIGNAL2(sigMap, prd6b, umi15Avar);
	MAKE_SIGNAL2(sigMap, prd6b, umi15Link);
	MAKE_SIGNAL2(sigMap, prd6b, umi16Avar);

	MAKE_SIGNAL2(sigMap, prd7b, umi16Link);
	MAKE_SIGNAL2(sigMap, prd7b, umi17Avar);
	MAKE_SIGNAL2(sigMap, prd7b, umi17Link);
	MAKE_SIGNAL2(sigMap, prd7b, umi18Avar);
	MAKE_SIGNAL2(sigMap, prd7b, umi18Link);
	MAKE_SIGNAL2(sigMap, prd7b, umi19Avar);
	MAKE_SIGNAL2(sigMap, prd7b, umi19Link);
	MAKE_SIGNAL2(sigMap, prd7b, umi20Avar);

	MAKE_SIGNAL2(sigMap, prd8b, umi20Link);
	MAKE_SIGNAL2(sigMap, prd8b, umi21Avar);
	MAKE_SIGNAL2(sigMap, prd8b, umi21Link);
	MAKE_SIGNAL2(sigMap, prd8b, umi22Avar);
	MAKE_SIGNAL2(sigMap, prd8b, umi22Link);
	MAKE_SIGNAL2(sigMap, prd8b, umi23Avar);
	MAKE_SIGNAL2(sigMap, prd8b, umi23Link);
	MAKE_SIGNAL2(sigMap, prd8b, umi24Avar);

	MAKE_SIGNAL2(sigMap, prd9b, umi24Link);
	MAKE_SIGNAL2(sigMap, prd9b, umi25Avar);
	MAKE_SIGNAL2(sigMap, prd9b, umi25Link);
	MAKE_SIGNAL2(sigMap, prd9b, umi26Avar);
	MAKE_SIGNAL2(sigMap, prd9b, umi26Link);
	MAKE_SIGNAL2(sigMap, prd9b, umi27Avar);
	MAKE_SIGNAL2(sigMap, prd9b, umi27Link);
	MAKE_SIGNAL2(sigMap, prd9b, umi28Avar);

	MAKE_SIGNAL2(sigMap, prd10b, umi28Link);
	MAKE_SIGNAL2(sigMap, prd10b, umi29Avar);
	MAKE_SIGNAL2(sigMap, prd10b, umi29Link);
	MAKE_SIGNAL2(sigMap, prd10b, umi30Avar);
	MAKE_SIGNAL2(sigMap, prd10b, umi30Link);
	MAKE_SIGNAL2(sigMap, prd10b, umi31Avar);
	MAKE_SIGNAL2(sigMap, prd10b, umi31Link);
	MAKE_SIGNAL2(sigMap, prd10b, umi32Avar);

	MAKE_SIGNAL2(sigMap, prd11b, umi32Link);
	MAKE_SIGNAL2(sigMap, prd11b, avarD2vv056);
	MAKE_SIGNAL2(sigMap, prd11b, avar124yy08);
	MAKE_SIGNAL2(sigMap, prd11b, blokirIzluchPrd);
//	MAKE_SIGNAL2(sigMap, prd11b, rez1);
	MAKE_SIGNAL2(sigMap, prd11b, qfVent);

	MAKE_SIGNAL2(sigMap, prd12b, qf126gg02);
	MAKE_SIGNAL2(sigMap, prd12b, qf124yy08);
	MAKE_SIGNAL2(sigMap, prd12b, avarD2hl142);
	MAKE_SIGNAL2(sigMap, prd12b, commSvchPos);
	MAKE_SIGNAL2(sigMap, prd12b, qfVentOtkl);
//	MAKE_SIGNAL2(sigMap, prd12b, rez1);

	MAKE_SIGNAL3(sigMap, prdBPU1b, avarBPU);

//UMI
	for(quint32 n_prd = 0; n_prd < CA_N_TRANSMITTERS; n_prd++)
		for(quint32 n_module = 0; n_module < CA_N_MODULES_UMI; n_module++)
		{
			MAKE_UMI_SIGNAL1(sigMap, n_prd, n_module, paramUMI, impulse);
			MAKE_UMI_SIGNAL1(sigMap, n_prd, n_module, paramUMI, no_impulse);
			MAKE_UMI_SIGNAL1(sigMap, n_prd, n_module, paramUMI, u_power);
			MAKE_UMI_SIGNAL1(sigMap, n_prd, n_module, paramUMI, sensor);
			MAKE_UMI_SIGNAL1(sigMap, n_prd, n_module, paramUMI, impulse);

			MAKE_UMI_SIGNAL2(sigMap, n_prd, n_module, paramUMI, power380_on);
			MAKE_UMI_SIGNAL2(sigMap, n_prd, n_module, paramUMI, power_on);
			MAKE_UMI_SIGNAL2(sigMap, n_prd, n_module, paramUMI, svch_on);
			MAKE_UMI_SIGNAL2(sigMap, n_prd, n_module, paramUMI, in_power_low);
			MAKE_UMI_SIGNAL2(sigMap, n_prd, n_module, paramUMI, in_power_high);
			MAKE_UMI_SIGNAL2(sigMap, n_prd, n_module, paramUMI, out_power);
			MAKE_UMI_SIGNAL2(sigMap, n_prd, n_module, paramUMI, ksvn);
			MAKE_UMI_SIGNAL2(sigMap, n_prd, n_module, paramUMI, temperature);
		}

	MAKE_VALUE(valMap, elk2021b.Pressure(), pressure);
	MAKE_VALUE(valMap, elk2223b.Temperature(), temperature_external1);
	MAKE_VALUE(valMap, elk2425b.Temperature(), temperature_external2);
	MAKE_VALUE(valMap, elk2627b.Temperature(), temperature_internal);

//UMI
	for(quint32 n_prd = 0; n_prd < CA_N_TRANSMITTERS; n_prd++)
		for(quint32 n_module = 0; n_module < CA_N_MODULES_UMI; n_module++)
		{
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, in_power);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, out_power);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, ksvn);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, temperature);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, u_power);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, serial_lo);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, serial_mi);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, serial_hi);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, phase_set);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, phase_def);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, time_minute);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, time_hour_lo);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, time_hour_hi);
			MAKE_UMI_VALUE(valMap, n_prd, n_module, paramUMI, phase_def);
		}

//	qDebug() << sigMap.dump();
//	qDebug() << valMap.dump();

	emit sigDataAsku(sigMap, valMap);
}

// ------------------------------------------------------------------
