#include "../common/logger.h"
#include "../common/module.h"
#include "../common/stateset.h"
#include "globalvar.h"
#include "canalasku.h"

//---------------------------------------------------------------------------------
void CanalAsku::checkFirstCommands(CanalAskuData * data)
{
	Q_UNUSED(data);
//	LogInfo("CanalAsku::checkFirstCommands  main=%d first=%d", m_canalAskuConfig.main, m_canalAskuConfig.first);

	if(m_canalAskuConfig.main && !m_canalAskuConfig.first)
	{
		bool onPrd1 = prd2b[0].BitsN.vkl380;
		prdCmd.prd[0].b1.BitsN.vkl380 = onPrd1;

		bool onPrd2 = prd2b[1].BitsN.vkl380;
		prdCmd.prd[1].b1.BitsN.vkl380 = onPrd2;

		bool onPumi1 = prd2b[0].BitsN.vkl123gv02;
		prdCmd.prd[0].b2.BitsN.vklPumi1 = onPumi1;
		prdCmd.prd[1].b2.BitsN.vklPumi1 = onPumi1;

		bool onPumi2 = prd2b[1].BitsN.vkl123gv02;
		prdCmd.prd[0].b2.BitsN.vklPumi2 = onPumi2;
		prdCmd.prd[1].b2.BitsN.vklPumi2 = onPumi2;

		m_canalAskuConfig.first = true;

		syncToSlave();

		LogInfo("CanalAsku::checkFirstCommands  prd1 = %d  prd2 = %d  pumi1 = %d  pumi2 = %d", onPrd1, onPrd2, onPumi1, onPumi2);
		emit sigReadyToCheckMode(onPrd1 || onPrd2);
	}
}

//---------------------------------------------------------------------------------
void CanalAsku::putOnErrorANT()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklHowl1 = 1;
	euvCmd.b1.BitsN.vklHowl2 = 1;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOffErrorANT()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklHowl1 = 0;
	euvCmd.b1.BitsN.vklHowl2 = 0;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOnErrorRLK()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b2.BitsN.errorRLK = 1;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOffErrorRLK()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b2.BitsN.errorRLK = 0;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putResetElk()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.sbrosAvar = 1;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOnRpuLight()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklRpuLight = 1;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOffRpuLight()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklRpuLight = 0;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOnPerimLight()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklPerimLight = 1;
	setCommandElk(euvCmd);
	syncToSlave();
    qDebug() << "вкл. свет (canalasku_commands)";
}

//---------------------------------------------------------------------------------
void CanalAsku::putOffPerimLight()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklPerimLight = 0;
	setCommandElk(euvCmd);
	syncToSlave();
    qDebug() << "откл. свет (canalasku_commands)";
}

//---------------------------------------------------------------------------------
void CanalAsku::putOnFire()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklFire = 1;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOffFire()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklFire = 0;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOnSafe()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklSafe = 1;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOffSafe()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklSafe = 0;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOnNoCond()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklBlockCond = 1;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOffNoCond()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklBlockCond = 0;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOnHowl1()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklHowl1 = 1;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOffHowl1()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklHowl1 = 0;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOnHowl2()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklHowl2 = 1;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
void CanalAsku::putOffHowl2()
{
	EUV_COMMAND euvCmd = elkCmd;
	euvCmd.b1.BitsN.vklHowl2 = 0;
	setCommandElk(euvCmd);
	syncToSlave();
}

//---------------------------------------------------------------------------------
bool CanalAsku::setCommandElk(EUV_COMMAND elkCmdNew)
{
	bool changed = false;
	CanalAskuCommand commands;

	if(elkCmdNew.b1.BitsN.vklFire && !elkCmd.b1.BitsN.vklFire)	//vkl fire
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_FIRE_ON, elkCmdNew.b2.Byte));
		changed = true;
	}
	else if(!elkCmdNew.b1.BitsN.vklFire && elkCmd.b1.BitsN.vklFire)	//otkl fire
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_FIRE_OFF, elkCmdNew.b2.Byte));
		changed = true;
	}

	if(elkCmdNew.b1.BitsN.vklSafe && !elkCmd.b1.BitsN.vklSafe)	//vkl safe
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_SAFE_ON, elkCmdNew.b2.Byte));
		changed = true;
	}
	else if(!elkCmdNew.b1.BitsN.vklSafe && elkCmd.b1.BitsN.vklSafe)	//otkl safe
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_SAFE_OFF, elkCmdNew.b2.Byte));
		changed = true;
	}
	if(elkCmdNew.b1.BitsN.vklBlockCond && !elkCmd.b1.BitsN.vklBlockCond)	//vkl block cond
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_BLOCK_COND_ON, elkCmdNew.b2.Byte));
		changed = true;
	}
	else if(!elkCmdNew.b1.BitsN.vklBlockCond && elkCmd.b1.BitsN.vklBlockCond)	//otkl block cond
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_BLOCK_COND_OFF, elkCmdNew.b2.Byte));
		changed = true;
	}
	if(elkCmdNew.b1.BitsN.vklHowl1 && !elkCmd.b1.BitsN.vklHowl1)	//vkl howl 1
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_HOWL1_ON, elkCmdNew.b2.Byte));
		changed = true;
	}
	else if(!elkCmdNew.b1.BitsN.vklHowl1 && elkCmd.b1.BitsN.vklHowl1)	//otkl howl 1
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_HOWL1_OFF, elkCmdNew.b2.Byte));
		changed = true;
	}
	if(elkCmdNew.b1.BitsN.vklHowl2 && !elkCmd.b1.BitsN.vklHowl2)	//vkl howl 2
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_HOWL2_ON, elkCmdNew.b2.Byte));
		changed = true;
	}
	else if(!elkCmdNew.b1.BitsN.vklHowl2 && elkCmd.b1.BitsN.vklHowl2)	//otkl howl 2
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_HOWL2_OFF, elkCmdNew.b2.Byte));
		changed = true;
	}
	if(elkCmdNew.b1.BitsN.vklRpuLight && !elkCmd.b1.BitsN.vklRpuLight)	//vkl rpu light
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_RPU_LIGHT_ON, elkCmdNew.b2.Byte));
		changed = true;
	}
	else if(!elkCmdNew.b1.BitsN.vklRpuLight && elkCmd.b1.BitsN.vklRpuLight)	//otkl rpu light
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_RPU_LIGHT_OFF, elkCmdNew.b2.Byte));
		changed = true;
	}
	if(elkCmdNew.b1.BitsN.vklPerimLight && !elkCmd.b1.BitsN.vklPerimLight)	//vkl perim light
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_PERIM_LIGHT_ON, elkCmdNew.b2.Byte));
		changed = true;
	}
	else if(!elkCmdNew.b1.BitsN.vklPerimLight && elkCmd.b1.BitsN.vklPerimLight)	//otkl perim light
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_PERIM_LIGHT_OFF, elkCmdNew.b2.Byte));
		changed = true;
	}
	if(elkCmdNew.b1.BitsN.sbrosAvar && !elkCmd.b1.BitsN.sbrosAvar)	//sbros avar common
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(100, CA_COMMAND_ELK_N_RESET_ON, elkCmdNew.b2.Byte));
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_RESET_OFF, elkCmdNew.b2.Byte));
		changed = true;
	}
	else if(!elkCmdNew.b1.BitsN.sbrosAvar && elkCmd.b1.BitsN.sbrosAvar)	//otkl sbros avar common
	{
		commands.append(CA_ELECTRO, CA_TYPE_COMMAND(0, CA_COMMAND_ELK_N_RESET_OFF, elkCmdNew.b2.Byte));
		changed = true;
	}

	if(changed)
	{
		elkCmdNew.b1.BitsN.sbrosAvar = 0;
		elkCmd = elkCmdNew;

		updateCommands(&commands);
	}

	return changed;
}

//---------------------------------------------------------------------------------
bool CanalAsku::setCommandPrd(PRD_COMMAND prdCmdNew)
{
	bool changed = false;
	CanalAskuCommand commands;
	qint32 m = -1, cntVkl380 = 0, cntVklPower = 0, cntVklSVCh = 0, cntOtkl380 = 0, cntOtklPower = 0, cntOtklSVCh = 0, cntResetAvar = 0;
	bool was_write = false;

	for(quint32 p_index = 0; p_index < CA_N_TRANSMITTERS; p_index++)
	{
		quint32 CA_TRANSMITTER = CA_TRANSMITTER1 + p_index;

//---- start on -----
//Byte 1
			if(prdCmdNew.prd[p_index].b1.BitsN.vkl380 && !prdCmd.prd[p_index].b1.BitsN.vkl380)//vkl PRD 380
			{
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(3000, CA_COMMAND_PRD_N_380_ON));
				changed = true;
			}

//Byte 2
			if(prdCmdNew.prd[p_index].b2.BitsN.vklPumi1 && !prdCmd.prd[p_index].b2.BitsN.vklPumi1)//vkl Pumi 1
			{
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, CA_COMMAND_PRD_N_PUMI_OFF));
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0,   0, CA_COMMAND_PRD_N_PUMI1_ON));
				changed = true;
			}
			else if(prdCmdNew.prd[p_index].b2.BitsN.vklPumi2 && !prdCmd.prd[p_index].b2.BitsN.vklPumi2)//vkl Pumi 2
			{
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, CA_COMMAND_PRD_N_PUMI_OFF));
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(  0, 0, CA_COMMAND_PRD_N_PUMI2_ON));
				changed = true;
			}
			if(prdCmdNew.prd[p_index].b2.BitsN.vklSvch1 && !prdCmd.prd[p_index].b2.BitsN.vklSvch1)//vkl Svch 1
			{
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, CA_COMMAND_PRD_N_SVCH_OFF));
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0,   0, CA_COMMAND_PRD_N_SVCH1_ON));
				changed = true;
			}
			else if(prdCmdNew.prd[p_index].b2.BitsN.vklSvch2 && !prdCmd.prd[p_index].b2.BitsN.vklSvch2)//vkl Svch 2
			{
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, CA_COMMAND_PRD_N_SVCH_OFF));
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(  0, 0, CA_COMMAND_PRD_N_SVCH2_ON));
				changed = true;
			}
			if(prdCmdNew.prd[p_index].b2.BitsN.vklHotRes && !prdCmd.prd[p_index].b2.BitsN.vklHotRes)//vkl Hot Reserve
			{
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0, 0, CA_COMMAND_PRD_N_HOT_RES_ON));
				changed = true;
			}

//Byte 3
//Umis
			cntVkl380 = cntVklPower = cntVklSVCh = 0;
			for(m = 0; m < CA_N_MODULES_UMI; m++)
			{
				if(prdCmdNew.prd[p_index].b3.module[m].BitsN.vklUmi && !prdCmd.prd[p_index].b3.module[m].BitsN.vklUmi)//vkl UMI 380
					cntVkl380++;
				if(prdCmdNew.prd[p_index].b3.module[m].BitsN.vklPower && !prdCmd.prd[p_index].b3.module[m].BitsN.vklPower)//vkl UMI Power
					cntVklPower++;
				if(prdCmdNew.prd[p_index].b3.module[m].BitsN.vklSVCh && !prdCmd.prd[p_index].b3.module[m].BitsN.vklSVCh)//vkl UMI SVCh
					cntVklSVCh++;
			}

			if(cntVkl380 == CA_N_MODULES_UMI)
			{
				prdCmdNew.prd[p_index].b3.module[CA_N_MODULES_UMI].BitsN.vklUmi = 1;
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(2000, 0, 0, CA_COMMAND_PRD_N_UMI_380_ON, 0));
				changed = true;
			}
			else
			{
				for(m = 0; m < CA_N_MODULES_UMI; m++)
				{
					if(prdCmdNew.prd[p_index].b3.module[m].BitsN.vklUmi && !prdCmd.prd[p_index].b3.module[m].BitsN.vklUmi)//vkl UMI 380
					{
						commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, 0, CA_COMMAND_PRD_N_UMI_380_ON, m+1));
						changed = true;
					}
				}
			}

			if(cntVklPower == CA_N_MODULES_UMI)
			{
				prdCmdNew.prd[p_index].b3.module[CA_N_MODULES_UMI].BitsN.vklPower = 1;
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(2000, 0, 0, CA_COMMAND_PRD_N_UMI_POWER_ALL_ON, 0));
				changed = true;
			}
			else
			{
				for(m = 0; m < CA_N_MODULES_UMI; m++)
				{
					if(prdCmdNew.prd[p_index].b3.module[m].BitsN.vklPower && !prdCmd.prd[p_index].b3.module[m].BitsN.vklPower)//vkl UMI IP
					{
						commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(200, 0, 0, CA_COMMAND_PRD_N_UMI_POWER_ON, m+1));
						changed = true;
					}
				}
			}

			if(cntVklSVCh == CA_N_MODULES_UMI)
			{
				prdCmdNew.prd[p_index].b3.module[CA_N_MODULES_UMI].BitsN.vklSVCh = 1;
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(3000, 0, 0, CA_COMMAND_PRD_N_UMI_SVCH_ALL_ON, 0));
				changed = true;
			}
			else
			{
				for(m = 0; m < CA_N_MODULES_UMI; m++)
				{
					if(prdCmdNew.prd[p_index].b3.module[m].BitsN.vklSVCh && !prdCmd.prd[p_index].b3.module[m].BitsN.vklSVCh)//vkl UMI SVCH
					{
						commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(200, 0, 0, CA_COMMAND_PRD_N_UMI_SVCH_ON, m+1));
						changed = true;
					}
				}
			}

//---- end on -----

//---- start off -----
//Byte 3
//Umis
			cntOtkl380 = cntOtklPower = cntOtklSVCh = 0;
			for(m = 0; m < CA_N_MODULES_UMI; m++)
			{
				if(!prdCmdNew.prd[p_index].b3.module[m].BitsN.vklUmi && prdCmd.prd[p_index].b3.module[m].BitsN.vklUmi)//otkl UMI 380
					cntOtkl380++;
				if(!prdCmdNew.prd[p_index].b3.module[m].BitsN.vklPower && prdCmd.prd[p_index].b3.module[m].BitsN.vklPower)//otkl UMI Power
					cntOtklPower++;
				if(!prdCmdNew.prd[p_index].b3.module[m].BitsN.vklSVCh && prdCmd.prd[p_index].b3.module[m].BitsN.vklSVCh)//otkl UMI SVCh
					cntOtklSVCh++;
			}

			if(cntOtklSVCh == CA_N_MODULES_UMI)
			{
				prdCmdNew.prd[p_index].b3.module[CA_N_MODULES_UMI].BitsN.vklSVCh = 0;
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(1000, 0, 0, CA_COMMAND_PRD_N_UMI_SVCH_ALL_OFF, 0));
				changed = true;
			}
			else
			{
				for(m = 0; m < CA_N_MODULES_UMI; m++)
				{
					if(!prdCmdNew.prd[p_index].b3.module[m].BitsN.vklSVCh && prdCmd.prd[p_index].b3.module[m].BitsN.vklSVCh)//otkl UMI SVCH
					{
						commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, 0, CA_COMMAND_PRD_N_UMI_SVCH_OFF, m+1));
						changed = true;
					}
				}
			}

			if(cntOtklPower == CA_N_MODULES_UMI)
			{
				prdCmdNew.prd[p_index].b3.module[CA_N_MODULES_UMI].BitsN.vklPower = 0;
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(1000, 0, 0, CA_COMMAND_PRD_N_UMI_POWER_ALL_OFF, 0));
				changed = true;
			}
			else
			{
				for(m = 0; m < CA_N_MODULES_UMI; m++)
				{
					if(!prdCmdNew.prd[p_index].b3.module[m].BitsN.vklPower && prdCmd.prd[p_index].b3.module[m].BitsN.vklPower)//otkl UMI IP
					{
						commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, 0, CA_COMMAND_PRD_N_UMI_POWER_OFF, m+1));
						changed = true;
					}
				}
			}

			if(cntOtkl380 == CA_N_MODULES_UMI)
			{
				prdCmdNew.prd[p_index].b3.module[CA_N_MODULES_UMI].BitsN.vklUmi = 0;
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(1000, 0, 0, CA_COMMAND_PRD_N_UMI_380_OFF, 0));
				changed = true;
			}
			else
			{
				for(m = 0; m < CA_N_MODULES_UMI; m++)
				{
					if(!prdCmdNew.prd[p_index].b3.module[m].BitsN.vklUmi && prdCmd.prd[p_index].b3.module[m].BitsN.vklUmi)//otkl UMI 380
					{
						commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, 0, CA_COMMAND_PRD_N_UMI_380_OFF, m+1));
						changed = true;
					}
				}
			}

//Byte 2
			if(!prdCmdNew.prd[p_index].b2.BitsN.vklHotRes && prdCmd.prd[p_index].b2.BitsN.vklHotRes)//otkl Hot Reserve
			{
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0, 0, CA_COMMAND_PRD_N_HOT_RES_OFF));
				changed = true;
			}

			if(!prdCmdNew.prd[p_index].b2.BitsN.vklPumi1 && !prdCmdNew.prd[p_index].b2.BitsN.vklPumi2 && 
				(prdCmd.prd[p_index].b2.BitsN.vklPumi1 || prdCmd.prd[p_index].b2.BitsN.vklPumi2))//otkl Pumi
			{
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0, 0, CA_COMMAND_PRD_N_PUMI_OFF));
				changed = true;
			}
			if(!prdCmdNew.prd[p_index].b2.BitsN.vklSvch1 && !prdCmdNew.prd[p_index].b2.BitsN.vklSvch2 && 
				(prdCmd.prd[p_index].b2.BitsN.vklSvch1 || prdCmd.prd[p_index].b2.BitsN.vklSvch2))//otkl Svch
			{
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0, 0, CA_COMMAND_PRD_N_SVCH_OFF));
				changed = true;
			}

//Byte 1
			if(!prdCmdNew.prd[p_index].b1.BitsN.vkl380 && prdCmd.prd[p_index].b1.BitsN.vkl380)//otkl PRD 380
			{
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0, CA_COMMAND_PRD_N_380_OFF));
				changed = true;
			}

//---- end off -----

			cntResetAvar = 0;
			for(m = 0; m < CA_N_MODULES_UMI; m++)
			{
				if(prdCmdNew.prd[p_index].b3.module[m].BitsN.sbrosAvar && !prdCmd.prd[p_index].b3.module[m].BitsN.sbrosAvar)//sbros avar UMI
					cntResetAvar++;
			}

			if(cntResetAvar == CA_N_MODULES_UMI)
			{
				prdCmdNew.prd[p_index].b3.module[CA_N_MODULES_UMI].BitsN.sbrosAvar = 1;
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(300, 0, 0, CA_COMMAND_PRD_N_UMI_RESET_ON, 0));
				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0,   0, 0, CA_COMMAND_PRD_N_UMI_RESET_OFF, 0));
				changed = true;
			}
			else
			{
				for(m = 0; m < CA_N_MODULES_UMI; m++)
				{
					if(prdCmdNew.prd[p_index].b3.module[m].BitsN.sbrosAvar && !prdCmd.prd[p_index].b3.module[m].BitsN.sbrosAvar)//sbros avar UMI
					{
						commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, 0, CA_COMMAND_PRD_N_UMI_RESET_ON, m+1));
						commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0,   0, 0, CA_COMMAND_PRD_N_UMI_RESET_OFF, m+1));
						changed = true;
					}
				}
			}

			was_write = false;
			for(m = 0; m < CA_N_MODULES_UMI; m++)
			{
				if(prdCmdNew.prd[p_index].b3.module[m].BitsN.writePhase && !prdCmd.prd[p_index].b3.module[m].BitsN.writePhase)//write phase UMI
				{
					commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, 0, CA_COMMAND_PRD_N_UMI_WRITE_PHASE_ON, m+1, prdCmdNew.prd[p_index].b5.module[m].Byte));
					prdCmdNew.prd[p_index].b3.module[m].BitsN.writePhase = 0;
					changed = true;
					was_write = true;
				}
			}
			if(was_write)
			{
//				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0, 0, 0, CA_COMMAND_PRD_N_UMI_WRITE_PHASE_OFF));
//				changed = true;
			}

			was_write = false;
			for(m = 0; m < CA_N_MODULES_UMI; m++)
			{
				if(prdCmdNew.prd[p_index].b3.module[m].BitsN.readPhase && !prdCmd.prd[p_index].b3.module[m].BitsN.readPhase)//read phase UMI
				{
					commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(100, 0, 0, CA_COMMAND_PRD_N_UMI_READ_PHASE_ON, m+1));
					prdCmdNew.prd[p_index].b3.module[m].BitsN.readPhase = 0;
					changed = true;
					was_write = true;
				}
			}
			if(was_write)
			{
//				commands.append(CA_TRANSMITTER, CA_TYPE_COMMAND(0, 0, 0, CA_COMMAND_PRD_N_UMI_READ_PHASE_OFF));
//				changed = true;
			}
	}

	if(changed)
	{
		for(m = 0; m <= CA_N_MODULES_UMI; m++)
			prdCmdNew.prd[0].b3.module[m].BitsN.sbrosAvar = prdCmdNew.prd[1].b3.module[m].BitsN.sbrosAvar = 0;

		prdCmd = prdCmdNew;

		updateCommands(&commands);
	}
	return changed;
}

// ------------------------------------------------------------------
void CanalAsku::slotHotRes(bool on)
{
	PRD_COMMAND xmtCmd = prdCmd;
	xmtCmd.prd[0].b2.BitsN.vklHotRes = xmtCmd.prd[1].b2.BitsN.vklHotRes = on;
	setCommandPrd(xmtCmd);
	syncToSlave();
	emit sigPrdHotResState(on, true);
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdPumi(bool on1, bool on2)
{
//	qDebug("slotPrdPumi on1=%d on2=%d", on1, on2);
	PRD_COMMAND xmtCmd = prdCmd;

	bool onetwo = false;
	bool active = false;

	if(!on1 && !on2)
	{
		xmtCmd.prd[0].b2.BitsN.vklPumi1 = xmtCmd.prd[1].b2.BitsN.vklPumi1 = 0;
		xmtCmd.prd[0].b2.BitsN.vklPumi2 = xmtCmd.prd[1].b2.BitsN.vklPumi2 = 0;
		active = false;
		onetwo = false;
	}
	else if(on1)
	{
		xmtCmd.prd[0].b2.BitsN.vklPumi1 = xmtCmd.prd[1].b2.BitsN.vklPumi1 = 1;
		xmtCmd.prd[0].b2.BitsN.vklPumi2 = xmtCmd.prd[1].b2.BitsN.vklPumi2 = 0;
		active = true;
		onetwo = false;
	}
	else if(on2)
	{
		xmtCmd.prd[0].b2.BitsN.vklPumi1 = xmtCmd.prd[1].b2.BitsN.vklPumi1 = 0;
		xmtCmd.prd[0].b2.BitsN.vklPumi2 = xmtCmd.prd[1].b2.BitsN.vklPumi2 = 1;
		active = true;
		onetwo = true;
	}

	setCommandPrd(xmtCmd);
	syncToSlave();
	emit sigPrdPumiState(onetwo, active);
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdPower(bool on, int n_prd)
{
//	qDebug("slotPrdPower n_prd=%d on=%d", n_prd, on);
	PRD_COMMAND xmtCmd = prdCmd;

	if(isAllPrds(n_prd) || isExactPrd(n_prd,1))
		xmtCmd.prd[0].b1.BitsN.vkl380 = on;
	if(isAllPrds(n_prd) || isExactPrd(n_prd,2))
		xmtCmd.prd[1].b1.BitsN.vkl380 = on;

//DDD	setCheckModules(n_prd-1, 30000);
	setCommandPrd(xmtCmd);
	syncToSlave();
	emit sigPrdPowerState(on, true);
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdPower380Module(bool on, int n_prd, int n_module)
{
//	qDebug("slotPrdPower380Module n_prd=%d n_mod=%d on=%d", n_prd, n_module, on);
	PRD_COMMAND xmtCmd = prdCmd;

	if(isAllPrds(n_prd) || isExactPrd(n_prd,1))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[0].b3.module[m].BitsN.vklUmi = on;
				xmtCmd.prd[0].b4.module[m].BitsN.module = m+1;
			}

	if(isAllPrds(n_prd) || isExactPrd(n_prd,2))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[1].b3.module[m].BitsN.vklUmi = on;
				xmtCmd.prd[1].b4.module[m].BitsN.module = m+1;
			}

//DDD	setCheckModules(n_prd-1, 30000);
	setCommandPrd(xmtCmd);
	syncToSlave();
	emit sigPrdModule380State(on, true);
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdPowerModule(bool on, int n_prd, int n_module)
{
//	qDebug("slotPrdPowerModule n_prd=%d n_mod=%d on=%d", n_prd, n_module, on);
	PRD_COMMAND xmtCmd = prdCmd;

	if(isAllPrds(n_prd) || isExactPrd(n_prd,1))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[0].b3.module[m].BitsN.vklPower = on;
				xmtCmd.prd[0].b4.module[m].BitsN.module = m+1;
			}

	if(isAllPrds(n_prd) || isExactPrd(n_prd,2))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[1].b3.module[m].BitsN.vklPower = on;
				xmtCmd.prd[1].b4.module[m].BitsN.module = m+1;
			}

	setCommandPrd(xmtCmd);
	syncToSlave();
	emit sigPrdModuleState(on, true);
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdSVChModule(bool on, int n_prd, int n_module)
{
//	qDebug("slotPrdSVChModule n_prd=%d n_mod=%d on=%d", n_prd, n_module, on);
	PRD_COMMAND xmtCmd = prdCmd;

	if(isAllPrds(n_prd) || isExactPrd(n_prd,1))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[0].b3.module[m].BitsN.vklSVCh = on;
				xmtCmd.prd[0].b4.module[m].BitsN.module = m+1;
			}

	if(isAllPrds(n_prd) || isExactPrd(n_prd,2))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[1].b3.module[m].BitsN.vklSVCh = on;
				xmtCmd.prd[1].b4.module[m].BitsN.module = m+1;
			}

//DDD	setCheckModules(n_prd-1, 30000);
	setCommandPrd(xmtCmd);
	syncToSlave();
	emit sigPrdSVChState(on, true);
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdResetModule(int n_prd, int n_module)
{
//	qDebug("slotPrdResetModule n_prd=%d n_mod=%d", n_prd, n_module);
	PRD_COMMAND xmtCmd = prdCmd;

	if(isAllPrds(n_prd) || isExactPrd(n_prd,1))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[0].b3.module[m].BitsN.sbrosAvar = 1;
				xmtCmd.prd[0].b4.module[m].BitsN.module = m+1;
			}
	if(isAllPrds(n_prd) || isExactPrd(n_prd,2))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[1].b3.module[m].BitsN.sbrosAvar = 1;
				xmtCmd.prd[1].b4.module[m].BitsN.module = m+1;
			}

//DDD	setCheckModules(n_prd-1, 30000);
	setCommandPrd(xmtCmd);
	syncToSlave();
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdQueryPhase(int n_prd, int n_module)
{
//	qDebug("slotPrdQueryPhase n_prd=%d n_mod=%d", n_prd, n_module);
	PRD_COMMAND xmtCmd = prdCmd;

	if(isAllPrds(n_prd) || isExactPrd(n_prd,1))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[0].b3.module[m].BitsN.readPhase = 1;
				xmtCmd.prd[0].b4.module[m].BitsN.module = m+1;
			}
	if(isAllPrds(n_prd) || isExactPrd(n_prd,2))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[1].b3.module[m].BitsN.readPhase = 1;
				xmtCmd.prd[1].b4.module[m].BitsN.module = m+1;
			}

	setCommandPrd(xmtCmd);
	syncToSlave();
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdSetPhase(int value, int n_prd, int n_module)
{
//	qDebug("slotPrdSetPhase n_prd=%d n_mod=%d phase=%d", n_prd, n_module, value);
	PRD_COMMAND xmtCmd = prdCmd;

	if(isAllPrds(n_prd) || isExactPrd(n_prd,1))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[0].b3.module[m].BitsN.writePhase = 1;
				xmtCmd.prd[0].b4.module[m].BitsN.module = m+1;
				xmtCmd.prd[0].b5.module[m].BitsN.phase = (unsigned char)value;
			}
	if(isAllPrds(n_prd) || isExactPrd(n_prd,2))
		for(int m = 0; m < CA_N_MODULES_UMI; m++)
			if(isAllModules(n_module) || isExactModule(n_module, m) || isHalfModule(n_module, m))
			{
				xmtCmd.prd[1].b3.module[m].BitsN.writePhase = 1;
				xmtCmd.prd[1].b4.module[m].BitsN.module = m+1;
				xmtCmd.prd[1].b5.module[m].BitsN.phase = (unsigned char)value;
			}

	setCommandPrd(xmtCmd);
	syncToSlave();
}

// ------------------------------------------------------------------
void CanalAsku::putPumi1On()
{
	PRD_COMMAND xmtCmd = prdCmd;
	xmtCmd.prd[0].b2.BitsN.vklPumi1 = xmtCmd.prd[1].b2.BitsN.vklPumi1 = 1;
	xmtCmd.prd[0].b2.BitsN.vklPumi2 = xmtCmd.prd[1].b2.BitsN.vklPumi2 = 0;
	emit sigPrdPumiState(false, true);
	setCommandPrd(xmtCmd);
	syncToSlave();
}

// ------------------------------------------------------------------
void CanalAsku::putPumiOff()
{
	PRD_COMMAND xmtCmd = prdCmd;
	xmtCmd.prd[0].b2.BitsN.vklPumi1 = xmtCmd.prd[1].b2.BitsN.vklPumi1 = 0;
	xmtCmd.prd[0].b2.BitsN.vklPumi2 = xmtCmd.prd[1].b2.BitsN.vklPumi2 = 0;
	emit sigPrdPumiState(false, false);
	setCommandPrd(xmtCmd);
	syncToSlave();
}

// ------------------------------------------------------------------
void CanalAsku::putPumi2On()
{
	PRD_COMMAND xmtCmd = prdCmd;
	xmtCmd.prd[0].b2.BitsN.vklPumi1 = xmtCmd.prd[1].b2.BitsN.vklPumi1 = 0;
	xmtCmd.prd[0].b2.BitsN.vklPumi2 = xmtCmd.prd[1].b2.BitsN.vklPumi2 = 1;
	emit sigPrdPumiState(true, true);
	setCommandPrd(xmtCmd);
	syncToSlave();
}

// ------------------------------------------------------------------
void CanalAsku::putSvch1On()
{
	PRD_COMMAND xmtCmd = prdCmd;
	xmtCmd.prd[0].b2.BitsN.vklSvch1 = xmtCmd.prd[1].b2.BitsN.vklSvch1 = 1;
	xmtCmd.prd[0].b2.BitsN.vklSvch2 = xmtCmd.prd[1].b2.BitsN.vklSvch2 = 0;
	emit sigPrdSvchState(false, true);
	setCommandPrd(xmtCmd);
	syncToSlave();
}

// ------------------------------------------------------------------
void CanalAsku::putSvchOff()
{
	PRD_COMMAND xmtCmd = prdCmd;
	xmtCmd.prd[0].b2.BitsN.vklSvch1 = xmtCmd.prd[1].b2.BitsN.vklSvch1 = 0;
	xmtCmd.prd[0].b2.BitsN.vklSvch2 = xmtCmd.prd[1].b2.BitsN.vklSvch2 = 0;
	emit sigPrdSvchState(false, false);
	setCommandPrd(xmtCmd);
	syncToSlave();
}

// ------------------------------------------------------------------
void CanalAsku::putSvch2On()
{
	PRD_COMMAND xmtCmd = prdCmd;
	xmtCmd.prd[0].b2.BitsN.vklPumi1 = xmtCmd.prd[1].b2.BitsN.vklSvch1 = 0;
	xmtCmd.prd[0].b2.BitsN.vklPumi2 = xmtCmd.prd[1].b2.BitsN.vklSvch2 = 1;
	emit sigPrdSvchState(true, true);
	setCommandPrd(xmtCmd);
	syncToSlave();
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdHrOn()
{
	slotHotRes(true);
}

// ------------------------------------------------------------------
void CanalAsku::slotPrdHrOff()
{
	slotHotRes(false);
}

// ------------------------------------------------------------------
void CanalAsku::putPrdOn1()
{
	slotPrdPower(true,1);
	slotPrdPower380Module(true,1,0);
	slotPrdPowerModule(true,1,0);
	slotPrdSVChModule(true,1,0);
	slotPrdResetModule(1,0);
}

// ------------------------------------------------------------------
void CanalAsku::putPrdOff1()
{
	slotPrdSVChModule(false,1,0);
	slotPrdPowerModule(false,1,0);
	slotPrdPower380Module(false,1,0);
	slotPrdPower(false,1);
	slotPrdResetModule(1,0);
}

// ------------------------------------------------------------------
void CanalAsku::putResetPrd1()
{
	slotPrdResetModule(1,0);
}

// ------------------------------------------------------------------
void CanalAsku::putPrdOn2()
{
	slotPrdPower(true,2);
	slotPrdPower380Module(true,2,0);
	slotPrdPowerModule(true,2,0);
	slotPrdSVChModule(true,2,0);
	slotPrdResetModule(2,0);
}

// ------------------------------------------------------------------
void CanalAsku::putPrdOff2()
{
	slotPrdSVChModule(false,2,0);
	slotPrdPowerModule(false,2,0);
	slotPrdPower380Module(false,2,0);
	slotPrdPower(false,2);
	slotPrdResetModule(2,0);
}

// ------------------------------------------------------------------
void CanalAsku::putResetPrd2()
{
	slotPrdResetModule(2,0);
}

// ------------------------------------------------------------------
void CanalAsku::setCheckModules(quint32 n_prd, qint32 state)
{
	if(n_prd < CA_N_TRANSMITTERS)
	{
		m_checkModulesTime[n_prd] = QDateTime::currentDateTime();
		m_checkModules[n_prd] = state;
	}
}

// ------------------------------------------------------------------
bool CanalAsku::isCheckModulesTime(quint32 n_prd)
{
	if(m_checkModules[n_prd] < 0)
		return false;

	qint64 time = m_checkModulesTime[n_prd].msecsTo(QDateTime::currentDateTime());
	return (m_checkModules[n_prd] < time);
}

// ------------------------------------------------------------------
void CanalAsku::checkCommandModules()
{
	PRD_COMMAND xmtCmd = prdCmd;

	for(qint32 p = 0; p < CA_N_TRANSMITTERS; p++)
	{
		if(!isCheckModulesTime(p))
			continue;

		bool wasCommand = false;
		bool wasCommandPhase = false;

		for(qint32 m = 0; m < CA_N_MODULES_UMI; m++)
		{
			if(paramUMI[p][m].v5.time_minute == 0 && paramUMI[p][m].v5.time_hour_lo == 0 && paramUMI[p][m].v5.time_hour_hi == 0 && paramUMI[p][m].v5.phase_set == 0) //module out
				continue;
//			if(paramUMI[p][m].v5.time_minute != 0 || paramUMI[p][m].v5.time_hour_lo != 0 || paramUMI[p][m].v5.time_hour_hi != 0) //module out
			{
				if(xmtCmd.prd[p].b3.module[m].BitsN.vklUmi && !paramUMI[p][m].v5.control2.bits.power380_on)
				{
					xmtCmd.prd[p].b3.module[m].BitsN.vklUmi = 0;
					xmtCmd.prd[p].b4.module[m].BitsN.module = m+1;
					setCommandPrd(xmtCmd);

					xmtCmd.prd[p].b3.module[m].BitsN.vklUmi = 1;
					xmtCmd.prd[p].b4.module[m].BitsN.module = m+1;
					setCommandPrd(xmtCmd);

					wasCommand = true;
					LogInfo("CanalAsku: prd[%d] module[%02d] vklUmi resend", p, m);
					continue;
				}
				if(xmtCmd.prd[p].b3.module[m].BitsN.vklPower && !paramUMI[p][m].v5.control2.bits.power_on)
				{
					xmtCmd.prd[p].b3.module[m].BitsN.vklPower = 0;
					xmtCmd.prd[p].b4.module[m].BitsN.module = m+1;
					setCommandPrd(xmtCmd);

					xmtCmd.prd[p].b3.module[m].BitsN.sbrosAvar = 1;
					xmtCmd.prd[p].b4.module[m].BitsN.module = m+1;
					setCommandPrd(xmtCmd);
					xmtCmd.prd[p].b3.module[m].BitsN.sbrosAvar = 0;

					xmtCmd.prd[p].b3.module[m].BitsN.vklPower = 1;
					xmtCmd.prd[p].b4.module[m].BitsN.module = m+1;
					setCommandPrd(xmtCmd);

					wasCommand = true;
					LogInfo("CanalAsku: prd[%d] module[%02d] vklPower resend", p, m);
					continue;
				}
				if(xmtCmd.prd[p].b3.module[m].BitsN.vklSVCh && !paramUMI[p][m].v5.control2.bits.svch_on && !paramUMI[p][m].v5.control2.bits.ksvn)
				{
					xmtCmd.prd[p].b3.module[m].BitsN.vklSVCh = 0;
					xmtCmd.prd[p].b4.module[m].BitsN.module = m+1;
					setCommandPrd(xmtCmd);

					xmtCmd.prd[p].b3.module[m].BitsN.vklSVCh = 1;
					xmtCmd.prd[p].b4.module[m].BitsN.module = m+1;
					setCommandPrd(xmtCmd);

					wasCommand = true;
					LogInfo("CanalAsku: prd[%d] module[%02d] vklSVCh resend", p, m);
					continue;
				}
				if(xmtCmd.prd[p].b3.module[m].BitsN.vklSVCh && !paramUMI[p][m].v5.control2.bits.svch_on && paramUMI[p][m].v5.control2.bits.ksvn)
				{
					xmtCmd.prd[p].b3.module[m].BitsN.sbrosAvar = 1;
					xmtCmd.prd[p].b4.module[m].BitsN.module = m+1;
					setCommandPrd(xmtCmd);
					xmtCmd.prd[p].b3.module[m].BitsN.sbrosAvar = 0;

					wasCommand = true;
					LogInfo("CanalAsku: prd[%d] module[%02d] reset on ksvn", p, m);
					continue;
				}
				if(phaseCodes.isLoaded())
				{
					quint32 value = (quint32)phaseCodes.value(p,m);
					qint32 inmod = (qint32)paramUMI[p][m].v5.phase_set - (qint32)paramUMI[p][m].v5.phase_def;
					if(inmod < 0)
						inmod += 64;
					if(value != 0xff && ((quint32)inmod != value) && prd2b[p].BitsN.vkl380)
					{
						xmtCmd.prd[p].b3.module[m].BitsN.writePhase = 1;
						xmtCmd.prd[p].b4.module[m].BitsN.module = m+1;
						xmtCmd.prd[p].b5.module[m].BitsN.phase = (unsigned char)value;
						wasCommandPhase = true;
						LogInfo("CanalAsku: prd[%d] module[%02d] set phase=%d (in module=%d)", p, m, value, paramUMI[p][m].v5.phase_set);
					}
				}
			}
		}
		if(wasCommandPhase)
		{
			setCommandPrd(xmtCmd);
			wasCommand = true;
		}
		if(wasCommand)
		{
//DDD			setCheckModules(p, 30000);
		}
	}
}

// ------------------------------------------------------------------
void CanalAsku::setCheckSvch(qint32 state)
{
	m_checkSvchTime = QDateTime::currentDateTime();
	m_checkSvch = state;
}

// ------------------------------------------------------------------
bool CanalAsku::isCheckSvchTime()
{
	if(m_checkSvch < 0)
		return false;

	qint64 time = m_checkSvchTime.msecsTo(QDateTime::currentDateTime());
	return (m_checkSvch < time);
}

// ------------------------------------------------------------------
void CanalAsku::checkCommandSvch()
{
//	PRD_COMMAND xmtCmd = prdCmd;

	if(!isCheckSvchTime())
		return;

	bool wasCommand = false;
//	bool wasCommandSvch = false;

	if(ISGPR1() && m_canalAskuConfig.main)
	{
		if(prd12b[0].BitsN.commSvchPos == 0)
		{
			wasCommand = true;
			putSvch1On();
		}
	}
	if(ISGPR2() && m_canalAskuConfig.main)
	{
		if(prd12b[1].BitsN.commSvchPos == 0)
		{
			wasCommand = true;
			putSvch2On();
		}
	}

/*	if(wasCommandSvch)
	{
		setCommandPrd(xmtCmd);
		wasCommand = true;
	}*/
	if(wasCommand)
		setCheckSvch(10000);
}

// ------------------------------------------------------------------
void CanalAsku::needSyncToSlave()
{
	syncToSlave();
}

// ------------------------------------------------------------------
void CanalAsku::syncToSlave()
{
	if(isMain())
	{
		QVariantMap config;
		config["main"] = QVariant(isMain());
		config["config"] = m_canalAskuConfig.toMap();
		config["cmdelk"] = elkCmd.toMap();
		config["cmdprd"] = prdCmd.toList();

		QVariantMap state = getCanalAskuStateLocal();
		QVariantMap measure = getCanalAskuDataLocal();

		syncToSlave(config, state, measure);
	}
}

// ------------------------------------------------------------------
void CanalAsku::syncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure)
{
//	LogInfo("CanalAsku::syncToSlave");

	QVariantMap data;
	data["InfoType"] = "RS485_SLAVE_SYNC";
	data["ModuleTo"] = "canalasku";
	data["ModuleFrom"] = "canalasku";
	data["GprId"] = IDGPR();
	if(!config.isEmpty())
		data["Config"] = config;
	if(!state.isEmpty())
		data["State"] = state;
	if(!measure.isEmpty())
		data["Measure"] = measure;

	emit sendInfoMessage(data, idAskuModuleSvc);
}

// ------------------------------------------------------------------
void CanalAsku::onSyncToSlave(QVariantMap config, QVariantMap state, QVariantMap measure)
{
//	if(!isMain())
	{
//		LogInfo("CanalAsku::onSyncToSlave processed");

		if(config.contains("main"))
		{
			if(config["main"].toBool() == true)
			{
				CanalAskuConfig m_masterConfig(config["config"].toMap());

				if(m_masterConfig.first == true)
				{
					QVariantMap cmdElkMap = config["cmdelk"].toMap();
					QVariantList cmdPrdList = config["cmdprd"].toList();

					EUV_COMMAND elkCmdNew(cmdElkMap);
					PRD_COMMAND prdCmdNew(cmdPrdList);

					LogSerialInfo("CanalAsku::commands from master: ELK: %02X PRD %02X", elkCmdNew.b1.Byte, prdCmdNew.prd[0].b1.Byte);

					elkCmd = elkCmdNew;
					prdCmd = prdCmdNew;

					m_canalAskuConfig.first = true;
				}

				if(!state.isEmpty())
					setCanalAskuStateOther(state);

				if(!measure.isEmpty())
					setCanalAskuDataOther(measure);
			}
		}
	}
}

// ------------------------------------------------------------------
