#include "../common/logger.h"
#include "globalvar.h"
#include "algorithm.h"
#include "canalasku_data.h"

// ----------------------------------------------------------------------------
void AskuAlgorithm::onStateVrl(AskuBinStateSet state)
{
	mvrlkn = state;

	funMvrlKn();
	funCommonMvrl();
	updateElements();

	ctrlKvit["vrl1"] = mvrlkn["vrl1@main"];
	ctrlKvit["vrl2"] = mvrlkn["vrl2@main"];

	if(mvrlkn["vrl1@main"] == ELEM_NORMA || mvrlkn["vrl2@main"] == ELEM_NORMA)
		ctrlKvit["vrl"] = ELEM_NORMA;
	else
		ctrlKvit["vrl"] = ELEM_NOT;

	emit controlKvit(ctrlKvit);
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funMvrlKn()
{
	elements["vrl_panel@qf_380v_1"] = mvrlkn["qf_380v_1"].toString();
	elements["vrl_panel@qf_380v_2"] = mvrlkn["qf_380v_2"].toString();
	elements["vrl_panel@qf_vum_1"] = mvrlkn["qf_vum_1"].toString();
	elements["vrl_panel@qf_vum_2"] = mvrlkn["qf_vum_2"].toString();
	elements["vrl_panel@qf_27v_1"] = mvrlkn["qf_27v_1"].toString();
	elements["vrl_panel@qf_27v_2"] = mvrlkn["qf_27v_2"].toString();
	elements["vrl_panel@qf_krt_1"] = mvrlkn["qf_krt_1"].toString();
	elements["vrl_panel@qf_krt_2"] = mvrlkn["qf_krt_2"].toString();
	elements["vrl@panel"] = mvrlkn["panel"].toString();

	elements["vrl@d2en258_1"] = mvrlkn["d2en258_1"].toString();
	elements["vrl@d2en258_2"] = mvrlkn["d2en258_2"].toString();
	elements["vrl@d2en279_1"] = mvrlkn["d2en279_1"].toString();
	elements["vrl@d2en279_2"] = mvrlkn["d2en279_2"].toString();
	elements["vrl@d2en277m_1"] = mvrlkn["d2en277m_1"].toString();
	elements["vrl@d2en277m_2"] = mvrlkn["d2en277m_2"].toString();
	elements["vrl@vent_1"] = mvrlkn["vent_1"].toString();
	elements["vrl@vent_2"] = mvrlkn["vent_2"].toString();
	elements["vrl@vent_3"] = mvrlkn["vent_3"].toString();
	elements["vrl@vent_4"] = mvrlkn["vent_4"].toString();

	elements["vrl@623gv01_1_ok"]   = mvrlkn["vrl1@623gv01_ok"].toString();
	elements["vrl_struct@pum1_ok"] = mvrlkn["vrl1@623gv01_ok"].toString();
	elements["vrl@623gv01_1_kp"]   = mvrlkn["vrl1@623gv01_kp"].toString();
	elements["vrl_struct@pum1_kp"] = mvrlkn["vrl1@623gv01_kp"].toString();
	elements["vrl@623gv01_2_ok"]   = mvrlkn["vrl2@623gv01_ok"].toString();
	elements["vrl_struct@pum2_ok"] = mvrlkn["vrl2@623gv01_ok"].toString();
	elements["vrl@623gv01_2_kp"]   = mvrlkn["vrl2@623gv01_kp"].toString();
	elements["vrl_struct@pum2_kp"] = mvrlkn["vrl2@623gv01_kp"].toString();
	elements["vrl@623gf01_1"]  = mvrlkn["vrl1@623gf01"].toString();
	elements["vrl_struct@zg1"] = mvrlkn["vrl1@623gf01"].toString();
	elements["vrl@623gf01_2"]  = mvrlkn["vrl2@623gf01"].toString();
	elements["vrl_struct@zg2"] = mvrlkn["vrl2@623gf01"].toString();
	elements["vrl@svch_comm"] = mvrlkn["svch_comm"].toString();
	elements["vrl_struct@switch_sum"] = mvrlkn["svch_comm"].toString();
	elements["vrl_struct@switch_dif"] = mvrlkn["svch_comm"].toString();
	elements["vrl_struct@switch_sup"] = mvrlkn["svch_comm"].toString();

//prm1
	elements["vrl_prm1@sum_sharu"] = mvrlkn["prm1@sum_sharu"];
	elements["vrl_prm1@dif_sharu"] = mvrlkn["prm1@dif_sharu"];
	elements["vrl_prm1@sup_sharu"] = mvrlkn["prm1@sup_sharu"];
	elements["vrl_prm1@sum_sh"] = mvrlkn["prm1@sum_sh"];
	elements["vrl_prm1@dif_sh"] = mvrlkn["prm1@dif_sh"];
	elements["vrl_prm1@sup_sh"] = mvrlkn["prm1@sup_sh"];
	elements["vrl_prm1@sum_amp_rbs"] = mvrlkn["prm1@sum_amp_rbs"];
	elements["vrl_prm1@dif_amp_rbs"] = mvrlkn["prm1@dif_amp_rbs"];
	elements["vrl_prm1@sup_amp_rbs"] = mvrlkn["prm1@sup_amp_rbs"];
	elements["vrl_prm1@sum_amp_nrz_f2"] = mvrlkn["prm1@sum_amp_nrz_f2"];
	elements["vrl_prm1@dif_amp_nrz_f2"] = mvrlkn["prm1@dif_amp_nrz_f2"];
	elements["vrl_prm1@sup_amp_nrz_f2"] = mvrlkn["prm1@sup_amp_nrz_f2"];
	elements["vrl_prm1@sum_amp_nrz_f3"] = mvrlkn["prm1@sum_amp_nrz_f3"];
	elements["vrl_prm1@dif_amp_nrz_f3"] = mvrlkn["prm1@dif_amp_nrz_f3"];
	elements["vrl_prm1@sup_amp_nrz_f3"] = mvrlkn["prm1@sup_amp_nrz_f3"];
	elements["vrl_prm1@sum_att"] = mvrlkn["prm1@sum_att"].toString();
	elements["vrl_prm1@dif_att"] = mvrlkn["prm1@dif_att"].toString();
	elements["vrl_prm1@sup_att"] = mvrlkn["prm1@sup_att"].toString();
	elements["vrl@123pp02_1"] = mvrlkn["prm1@obSost"].toString();
	elements["vrl_struct@prm1"] = mvrlkn["prm1@obSost"].toString();
//prm2
	elements["vrl_prm2@sum_sharu"] = mvrlkn["prm2@sum_sharu"];
	elements["vrl_prm2@dif_sharu"] = mvrlkn["prm2@dif_sharu"];
	elements["vrl_prm2@sup_sharu"] = mvrlkn["prm2@sup_sharu"];
	elements["vrl_prm2@sum_sh"] = mvrlkn["prm2@sum_sh"];
	elements["vrl_prm2@dif_sh"] = mvrlkn["prm2@dif_sh"];
	elements["vrl_prm2@sup_sh"] = mvrlkn["prm2@sup_sh"];
	elements["vrl_prm2@sum_amp_rbs"] = mvrlkn["prm2@sum_amp_rbs"];
	elements["vrl_prm2@dif_amp_rbs"] = mvrlkn["prm2@dif_amp_rbs"];
	elements["vrl_prm2@sup_amp_rbs"] = mvrlkn["prm2@sup_amp_rbs"];
	elements["vrl_prm2@sum_amp_nrz_f2"] = mvrlkn["prm2@sum_amp_nrz_f2"];
	elements["vrl_prm2@dif_amp_nrz_f2"] = mvrlkn["prm2@dif_amp_nrz_f2"];
	elements["vrl_prm2@sup_amp_nrz_f2"] = mvrlkn["prm2@sup_amp_nrz_f2"];
	elements["vrl_prm2@sum_amp_nrz_f3"] = mvrlkn["prm2@sum_amp_nrz_f3"];
	elements["vrl_prm2@dif_amp_nrz_f3"] = mvrlkn["prm2@dif_amp_nrz_f3"];
	elements["vrl_prm2@sup_amp_nrz_f3"] = mvrlkn["prm2@sup_amp_nrz_f3"];
	elements["vrl_prm2@sum_att"] = mvrlkn["prm2@sum_att"].toString();
	elements["vrl_prm2@dif_att"] = mvrlkn["prm2@dif_att"].toString();
	elements["vrl_prm2@sup_att"] = mvrlkn["prm2@sup_att"].toString();
	elements["vrl@123pp02_2"] = mvrlkn["prm2@obSost"].toString();
	elements["vrl_struct@prm2"] = mvrlkn["prm2@obSost"].toString();
//azn
	elements["vrl_azn@sharu1"] = mvrlkn["azn@sharu1"];
	elements["vrl_azn@sharu2"] = mvrlkn["azn@sharu2"];
	elements["vrl_azn@sharu3"] = mvrlkn["azn@sharu3"];
	elements["vrl_azn@sharu4"] = mvrlkn["azn@sharu4"];
	elements["vrl_azn@sh1"] = mvrlkn["azn@sh1"];
	elements["vrl_azn@sh2"] = mvrlkn["azn@sh2"];
	elements["vrl_azn@sh3"] = mvrlkn["azn@sh3"];
	elements["vrl_azn@sh4"] = mvrlkn["azn@sh4"];
	elements["vrl_azn@amp1"] = mvrlkn["azn@amp1"];
	elements["vrl_azn@amp2"] = mvrlkn["azn@amp2"];
	elements["vrl_azn@amp3"] = mvrlkn["azn@amp3"];
	elements["vrl_azn@amp4"] = mvrlkn["azn@amp4"];
	elements["vrl_azn@att1"] = mvrlkn["azn@att1"].toString();
	elements["vrl_azn@att2"] = mvrlkn["azn@att2"].toString();
	elements["vrl_azn@att3"] = mvrlkn["azn@att3"].toString();
	elements["vrl_azn@att4"] = mvrlkn["azn@att4"].toString();
	elements["vrl@123pp03"] = mvrlkn["azn@obSost"].toString();
	elements["vrl_struct@prm_azn"] = mvrlkn["azn@obSost"].toString();
	elements["base@azn_mshu1"] = mvrlkn["azn@att1"].toString();
	elements["base@azn_mshu2"] = mvrlkn["azn@att2"].toString();
	elements["base@azn_mshu3"] = mvrlkn["azn@att3"].toString();
	elements["base@azn_mshu4"] = mvrlkn["azn@att4"].toString();
//obr1
	elements["vrl@svkr1"] = mvrlkn["obr1@obSost"].toString() + mvrlkn["vrl1@mest"].toStringMest();
	elements["vrl_struct@obr1"] = mvrlkn["obr1@obSost"].toString() + mvrlkn["vrl1@mest"].toStringMest();
	elements["vrl_svkr1@e_3"] = mvrlkn["obr1@obSost"].toString();
	elements["vrl_svkr1@e_4"] = mvrlkn["obr1@obSost"].toString();
//obr2
	elements["vrl@svkr2"] = mvrlkn["obr2@obSost"].toString() + mvrlkn["vrl2@mest"].toStringMest();
	elements["vrl_struct@obr2"] = mvrlkn["obr2@obSost"].toString() + mvrlkn["vrl2@mest"].toStringMest();
	elements["vrl_svkr2@e_3"] = mvrlkn["obr2@obSost"].toString();
	elements["vrl_svkr2@e_4"] = mvrlkn["obr2@obSost"].toString();
//vum
	elements["vrl@vum1"] = mvrlkn["vum1@ObSost"].toString();
	elements["vrl_vum1@sumPout"] = mvrlkn["vum1@sumPout"];
	elements["vrl_vum1@sumPin"]  = mvrlkn["vum1@sumPin"];
	elements["vrl_vum1@sumPotr"] = mvrlkn["vum1@sumPotr"];
	elements["vrl_vum1@sumUpit"] = mvrlkn["vum1@sumUpit"];
	elements["vrl_vum1@sumT"]    = mvrlkn["vum1@sumT"];
	elements["vrl_vum1@supPout"] = mvrlkn["vum1@supPout"];
	elements["vrl_vum1@supPin"]  = mvrlkn["vum1@supPin"];
	elements["vrl_vum1@supPotr"] = mvrlkn["vum1@supPotr"];
	elements["vrl_vum1@supUpit"] = mvrlkn["vum1@supUpit"];
	elements["vrl_vum1@supT"]    = mvrlkn["vum1@supT"];
	elements["vrl@vum2"] = mvrlkn["vum2@ObSost"].toString();
	elements["vrl_vum2@sumPout"] = mvrlkn["vum2@sumPout"];
	elements["vrl_vum2@sumPin"]  = mvrlkn["vum2@sumPin"];
	elements["vrl_vum2@sumPotr"] = mvrlkn["vum2@sumPotr"];
	elements["vrl_vum2@sumUpit"] = mvrlkn["vum2@sumUpit"];
	elements["vrl_vum2@sumT"]    = mvrlkn["vum2@sumT"];
	elements["vrl_vum2@supPout"] = mvrlkn["vum2@supPout"];
	elements["vrl_vum2@supPin"]  = mvrlkn["vum2@supPin"];
	elements["vrl_vum2@supPotr"] = mvrlkn["vum2@supPotr"];
	elements["vrl_vum2@supUpit"] = mvrlkn["vum2@supUpit"];
	elements["vrl_vum2@supT"]    = mvrlkn["vum2@supT"];
	elements["vrl@vum3"] = mvrlkn["vum3@ObSost"].toString();
	elements["vrl_vum3@sumPout"] = mvrlkn["vum3@sumPout"];
	elements["vrl_vum3@sumPin"]  = mvrlkn["vum3@sumPin"];
	elements["vrl_vum3@sumPotr"] = mvrlkn["vum3@sumPotr"];
	elements["vrl_vum3@sumUpit"] = mvrlkn["vum3@sumUpit"];
	elements["vrl_vum3@sumT"]    = mvrlkn["vum3@sumT"];
	elements["vrl_vum3@supPout"] = mvrlkn["vum3@supPout"];
	elements["vrl_vum3@supPin"]  = mvrlkn["vum3@supPin"];
	elements["vrl_vum3@supPotr"] = mvrlkn["vum3@supPotr"];
	elements["vrl_vum3@supUpit"] = mvrlkn["vum3@supUpit"];
	elements["vrl_vum3@supT"]    = mvrlkn["vum3@supT"];
	elements["vrl@vum4"] = mvrlkn["vum4@ObSost"].toString();
	elements["vrl_vum4@sumPout"] = mvrlkn["vum4@sumPout"];
	elements["vrl_vum4@sumPin"]  = mvrlkn["vum4@sumPin"];
	elements["vrl_vum4@sumPotr"] = mvrlkn["vum4@sumPotr"];
	elements["vrl_vum4@sumUpit"] = mvrlkn["vum4@sumUpit"];
	elements["vrl_vum4@sumT"]    = mvrlkn["vum4@sumT"];
	elements["vrl_vum4@supPout"] = mvrlkn["vum4@supPout"];
	elements["vrl_vum4@supPin"]  = mvrlkn["vum4@supPin"];
	elements["vrl_vum4@supPotr"] = mvrlkn["vum4@supPotr"];
	elements["vrl_vum4@supUpit"] = mvrlkn["vum4@supUpit"];
	elements["vrl_vum4@supT"]    = mvrlkn["vum4@supT"];
	elements["vrl@vum5"] = mvrlkn["vum5@ObSost"].toString();
	elements["vrl_vum5@sumPout"] = mvrlkn["vum5@sumPout"];
	elements["vrl_vum5@sumPin"]  = mvrlkn["vum5@sumPin"];
	elements["vrl_vum5@sumPotr"] = mvrlkn["vum5@sumPotr"];
	elements["vrl_vum5@sumUpit"] = mvrlkn["vum5@sumUpit"];
	elements["vrl_vum5@sumT"]    = mvrlkn["vum5@sumT"];
	elements["vrl_vum5@supPout"] = mvrlkn["vum5@supPout"];
	elements["vrl_vum5@supPin"]  = mvrlkn["vum5@supPin"];
	elements["vrl_vum5@supPotr"] = mvrlkn["vum5@supPotr"];
	elements["vrl_vum5@supUpit"] = mvrlkn["vum5@supUpit"];
	elements["vrl_vum5@supT"]    = mvrlkn["vum5@supT"];
	elements["vrl@vum6"] = mvrlkn["vum6@ObSost"].toString();
	elements["vrl_vum6@sumPout"] = mvrlkn["vum6@sumPout"];
	elements["vrl_vum6@sumPin"]  = mvrlkn["vum6@sumPin"];
	elements["vrl_vum6@sumPotr"] = mvrlkn["vum6@sumPotr"];
	elements["vrl_vum6@sumUpit"] = mvrlkn["vum6@sumUpit"];
	elements["vrl_vum6@sumT"]    = mvrlkn["vum6@sumT"];
	elements["vrl_vum6@supPout"] = mvrlkn["vum6@supPout"];
	elements["vrl_vum6@supPin"]  = mvrlkn["vum6@supPin"];
	elements["vrl_vum6@supPotr"] = mvrlkn["vum6@supPotr"];
	elements["vrl_vum6@supUpit"] = mvrlkn["vum6@supUpit"];
	elements["vrl_vum6@supT"]    = mvrlkn["vum6@supT"];
	elements["vrl@vum7"] = mvrlkn["vum7@ObSost"].toString();
	elements["vrl_vum7@sumPout"] = mvrlkn["vum7@sumPout"];
	elements["vrl_vum7@sumPin"]  = mvrlkn["vum7@sumPin"];
	elements["vrl_vum7@sumPotr"] = mvrlkn["vum7@sumPotr"];
	elements["vrl_vum7@sumUpit"] = mvrlkn["vum7@sumUpit"];
	elements["vrl_vum7@sumT"]    = mvrlkn["vum7@sumT"];
	elements["vrl_vum7@supPout"] = mvrlkn["vum7@supPout"];
	elements["vrl_vum7@supPin"]  = mvrlkn["vum7@supPin"];
	elements["vrl_vum7@supPotr"] = mvrlkn["vum7@supPotr"];
	elements["vrl_vum7@supUpit"] = mvrlkn["vum7@supUpit"];
	elements["vrl_vum7@supT"]    = mvrlkn["vum7@supT"];
	elements["vrl@vum8"] = mvrlkn["vum8@ObSost"].toString();
	elements["vrl_vum8@sumPout"] = mvrlkn["vum8@sumPout"];
	elements["vrl_vum8@sumPin"]  = mvrlkn["vum8@sumPin"];
	elements["vrl_vum8@sumPotr"] = mvrlkn["vum8@sumPotr"];
	elements["vrl_vum8@sumUpit"] = mvrlkn["vum8@sumUpit"];
	elements["vrl_vum8@sumT"]    = mvrlkn["vum8@sumT"];
	elements["vrl_vum8@supPout"] = mvrlkn["vum8@supPout"];
	elements["vrl_vum8@supPin"]  = mvrlkn["vum8@supPin"];
	elements["vrl_vum8@supPotr"] = mvrlkn["vum8@supPotr"];
	elements["vrl_vum8@supUpit"] = mvrlkn["vum8@supUpit"];
	elements["vrl_vum8@supT"]    = mvrlkn["vum8@supT"];
	elements["vrl_struct@prd"] = mvrlkn["prd"].toString();
//zao
//	elements["vrl_zao@loaded"] = mvrlkn["zao@loaded"].toString();
//	elements["vrl_zao@good"] = mvrlkn["zao@good"].toString();
//	elements["vrl_zao@fail"] = mvrlkn["zao@fail"].toString();
	elements["vrl@zao"] = mvrlkn["zao@obSost"].toString();
}

// ----------------------------------------------------------------------------
void AskuAlgorithm::funCommonMvrl()
{
	elements["zal@126gp02"] = mvrlkn["ObSost"].toString() + mvrlkn["mest"].toStringMest();
	elements["base@mvrl_kn"] = mvrlkn["ObSost"].toString() + mvrlkn["mest"].toStringMest();
	elements["status_window@common_mvrl"] = mvrlkn["ObSost"].toString() + mvrlkn["mest"].toStringMest();
	messages["vrl@obSost"] = mvrlkn["ObSost"];

	funCommonUrlk();
}

