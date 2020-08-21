#ifndef _DES_STRUCT_H_
#define _DES_STRUCT_H_

#include <QDateTime>

#define N_DES_MNS 2
#define N_DES_DGS 4

#define DES_TYPE_DEFAULT 0
#define DES_TYPE_1_MAINS_2_DGS 1
#define DES_TYPE_2_MAINS_4_DGS 2


// Powerware state structure
typedef	struct tagDeifState
{
	struct DeifState
	{
		union DeifStateReg
		{
			struct _Bits
			{
				unsigned short TB_position:1;
				unsigned short GB_position:1;
				unsigned short MB_position:1;
				unsigned short Block_mode:1;
				unsigned short Test_mode:1;
				unsigned short Manual_mode:1;
				unsigned short SemiAuto_mode:1;
				unsigned short Auto_mode:1;
				unsigned short Island:1;
				unsigned short Automatic_mains_failure_AMF:1;
				unsigned short ATS_mode:1;
				unsigned short Load_take_over_LTO:1;
			} Bits;
//			unsigned short	_Data;
		} RegState;

		union DeifState2Reg
		{
			struct _Bits
			{
				unsigned short Unbalance_current:1;
				unsigned short Unbalance_voltage:1;
				unsigned short Phase_seq_error:1;
				unsigned short TB_open_failure:1;
				unsigned short TB_close_failure:1;
				unsigned short TB_pos_failure:1;
				unsigned short MB_open_failure:1;
				unsigned short MB_close_failure:1;
				unsigned short MB_pos_failure:1;
				unsigned short GB_open_failure:1;
				unsigned short GB_close_failure:1;
				unsigned short GB_pos_failure:1;
				unsigned short Emergency_STOP:1;
				unsigned short Mains_failure:1;
				unsigned short Service_timer_1:1;
				unsigned short Service_timer_2:1;
				unsigned short EIC_comm_error:1;
				unsigned short EIC_warning:1;
				unsigned short EIC_shutdown:1;
				unsigned short EIC_overspeed:1;
				unsigned short EIC_coolant_temp_1:1;
				unsigned short EIC_coolant_temp_2:1;
				unsigned short EIC_oil_pressure_1:1;
				unsigned short EIC_oil_pressure_2:1;
				unsigned short EIC_oil_temperature_1:1;
				unsigned short EIC_oil_temperature_2:1;
				unsigned short Overspeed_1:1;
				unsigned short Overspeed_2:1;
				unsigned short Crank_failure:1;
				unsigned short Running_feedback_failure:1;
				unsigned short MPU_wire_failure:1;
				unsigned short Start_failure:1;
				unsigned short Stop_failure:1;
				unsigned short Stop_coil_wire_break:1;
				unsigned short Underspeed_1:1;
				unsigned short Internal_comm_failure:1;
				unsigned short Engine_heater_1:1;
				unsigned short Battery_test:1;
				unsigned short Battery_assymmetry_1:1;
				unsigned short Battery_assymmetry_2:1;
				unsigned short Max_ventilation_1:1;
				unsigned short Max_ventilation_2:1;
				unsigned short Fuel_pump_logic:1;
				unsigned short Engine_running:1;
				unsigned short Generator_Hz_V_failure:1;
			} Bits;
//			unsigned short	_Data;
		} RegState2;

		union DeifGeneratorVoltage
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 0);
			}
		} RegVoltageL1, RegVoltageL2, RegVoltageL3;

		union DeifGeneratorFrequency
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 100.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 2);
			}
		} RegFrequencyL1, RegFrequencyL2, RegFrequencyL3;

		union DeifGeneratorPhase
		{
			short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegPhaseL1L2, RegPhaseL2L3, RegPhaseL3L1;

		union DeifGeneratorCurrent
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 0);
			}
		} RegCurrentL1, RegCurrentL2, RegCurrentL3;

		union DeifGeneratorTotalPower
		{
			short _Data;
			double realValue() {
				return ((double)_Data);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 0);
			}
		} RegTotalActivePower, RegTotalReactivePower, RegTotalApparentPower;

		union DeifGeneratorTotalEnergyCounter
		{
			unsigned int _Data;
			double realValue() {
				return ((double)_Data);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 0);
			}
			void setHI(unsigned short value) {
				_Data &= 0x0000FFFF;
				_Data |= (((unsigned int)value) << 16) & 0xFFFF0000;
			}
			void setLO(unsigned short value) {
				_Data &= 0xFFFF0000;
				_Data |= ((unsigned int)value) & 0x0000FFFF;
			}
		} RegTotalEnergyCounter;

		union DeifRunningTime
		{
			unsigned int _Data;
			double realValue() {
				return ((double)_Data);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 0);
			}
			void setHI(unsigned short value) {
				_Data &= 0x0000FFFF;
				_Data |= (((unsigned int)value) << 16) & 0xFFFF0000;
			}
			void setLO(unsigned short value) {
				_Data &= 0xFFFF0000;
				_Data |= ((unsigned int)value) & 0x0000FFFF;
			}
		} RegRunningTimeRelative, RegRunningTimeAbsolute;

		union DeifGeneratorCosPhi
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 100.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 2);
			}
		} RegCosPhi;

		union DeifSupplyVoltage
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data / 10.0);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 1);
			}
		} RegSupplyVoltage;

		union DeifRunningFeedback
		{
			unsigned short _Data;
			double realValue() {
				return ((double)_Data);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 0);
			}
		} RegRunningFeedback;

		union DeifServiceTimerHours
		{
			short _Data;
			double realValue() {
				return ((double)_Data);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 0);
			}
		} RegServiceTimerHours1, RegServiceTimerHours2;

		union DeifServiceTimerDays
		{
			short _Data;
			double realValue() {
				return ((double)_Data);
			}
			QString textValue() {
				return QString::number(realValue(), 'f', 0);
			}
		} RegServiceTimerDays1, RegServiceTimerDays2;

		QDateTime	Updated;

		DeifState() : Updated()
		{
//			RegState._Data = 0;
			memset(&RegState, 0, sizeof(RegState));
			memset(&RegState2, 0, sizeof(RegState2));
			RegVoltageL1._Data = 0;
			RegVoltageL2._Data = 0;
			RegVoltageL3._Data = 0;
			RegFrequencyL1._Data = 0;
			RegFrequencyL2._Data = 0;
			RegFrequencyL3._Data = 0;
			RegPhaseL1L2._Data = 0;
			RegPhaseL2L3._Data = 0;
			RegPhaseL3L1._Data = 0;
			RegCurrentL1._Data = 0;
			RegCurrentL2._Data = 0;
			RegCurrentL3._Data = 0;
			RegTotalActivePower._Data = 0;
			RegTotalReactivePower._Data = 0;
			RegTotalApparentPower._Data = 0;
			RegTotalEnergyCounter._Data = 0;
			RegCosPhi._Data = 0;
			RegRunningTimeRelative._Data = 0;
			RegRunningTimeAbsolute._Data = 0;
			RegSupplyVoltage._Data = 0;
			RegServiceTimerHours1._Data = 0;
			RegServiceTimerDays1._Data = 0;
			RegServiceTimerHours2._Data = 0;
			RegServiceTimerDays2._Data = 0;
			RegRunningFeedback._Data = 0;
		}

	} State;

	struct DeifControl
	{
		union DeifControlReg1
		{
			struct _Bits
			{
				unsigned short Control		:1;
				unsigned short Start		:1;
				unsigned short TB_GB_ON		:1;
				unsigned short TB_GB_OFF	:1;
				unsigned short Stop			:1;
				unsigned short Alarm_ack	:1;
				unsigned short Unused1		:5;
				unsigned short Nominal_1	:1;
				unsigned short Nominal_2	:1;
				unsigned short Nominal_3	:1;
				unsigned short Nominal_4	:1;
				unsigned short Unused2		:1;
			} Bits;
			unsigned short	_Data;
		} RegControl1;

		union DeifControlReg2
		{
			struct _Bits
			{
				unsigned short Control		:1;
				unsigned short Island		:1;
				unsigned short AMF			:1;
				unsigned short Peak_Shaving	:1;
				unsigned short Fixed_Power	:1;
				unsigned short MPE			:1;
				unsigned short LTO			:1;
				unsigned short Unused		:2;
				unsigned short MB_ON		:1;
				unsigned short MB_OFF		:1;
				unsigned short Block		:1;
				unsigned short Manual		:1;
				unsigned short Auto			:1;
				unsigned short SemiAuto		:1;
				unsigned short Test			:1;
			} Bits;
			unsigned short	_Data;
		} RegControl2;

		QDateTime	Updated;

		DeifControl() : Updated()
		{
			RegControl1._Data = 0;
			RegControl2._Data = 0;
		}

	} Control;

	QDateTime	Updated;					// Structure updated time, milliseconds left

	tagDeifState() : Updated()
	{
	}
} DeifDgState, DeifMainsState;


typedef struct tagDesConfig
{
	unsigned int type;
	bool main;
	bool monitor;

	struct DeifMainsConfig
	{
		bool first;
		bool regAuto;
		bool regSemiAuto;
		bool regTest;
		bool regManual;
		bool regBlock;

		bool posTB;
		bool posMB;

		DeifMainsConfig()
		{
			first = false;
			regAuto = false;
			regSemiAuto = false;
			regTest = false;
			regManual = false;
			regBlock = false;

			posTB = false;
			posMB = false;
		}

	}Mns[N_DES_MNS];

	struct DeifDgConfig
	{
		bool first;
		bool regAuto;
		bool regSemiAuto;
		bool regTest;
		bool regManual;
		bool regBlock;

		bool posGB;
		bool runDG;

		DeifDgConfig()
		{
			first = false;

			regAuto = false;
			regSemiAuto = false;
			regTest = false;
			regManual = false;
			regBlock = false;

			posGB = false;
			runDG = false;
		}

	}Dgs[N_DES_DGS];

	tagDesConfig()
	{
		type = DES_TYPE_DEFAULT;
		main = false;
		monitor = false;
	}

	tagDesConfig(QVariantMap data)
	{
		fromMap(data);
	}

	QVariantMap toMap() {
		QVariantMap map;
		map["main"] = main;
		map["type"] = type;
		map["monitor"] = monitor;

		QVariantList listm;
		for(quint32 i = 0; i < N_DES_MNS; i++)
		{
			QVariantMap mns;
			mns["first"]       = Mns[i].first;
			mns["regAuto"]     = Mns[i].regAuto;
			mns["regSemiAuto"] = Mns[i].regSemiAuto;
			mns["regTest"]     = Mns[i].regTest;
			mns["regManual"]   = Mns[i].regManual;
			mns["regBlock"]    = Mns[i].regBlock;
			mns["posTB"] = Mns[i].posTB;
			mns["posMB"] = Mns[i].posMB;
			listm << mns;
		}
		map["mns"] = listm;

		QVariantList listg;
		for(quint32 i = 0; i < N_DES_DGS; i++)
		{
			QVariantMap dgs;
			dgs["first"]       = Dgs[i].first;
			dgs["regAuto"]     = Dgs[i].regAuto;
			dgs["regSemiAuto"] = Dgs[i].regSemiAuto;
			dgs["regTest"]     = Dgs[i].regTest;
			dgs["regManual"]   = Dgs[i].regManual;
			dgs["regBlock"]    = Dgs[i].regBlock;
			dgs["posGB"] = Dgs[i].posGB;
			dgs["runDG"] = Dgs[i].runDG;
			listg << dgs;
		}
		map["dgs"] = listg;

		return map;
	}
	void fromMap(QVariantMap map) {
		main = map["main"].toBool();
		type = map["type"].toBool();
		monitor = map["monitor"].toBool();

		QVariantList listm = map["mns"].toList();
		for(qint32 i = 0; i < N_DES_MNS && i < listm.count(); i++)
		{
			QVariantMap mns = listm[i].toMap();
			Mns[i].first       = mns["first"].toBool();
			Mns[i].regAuto     = mns["regAuto"].toBool();
			Mns[i].regSemiAuto = mns["regSemiAuto"].toBool();
			Mns[i].regTest     = mns["regTest"].toBool();
			Mns[i].regManual   = mns["regManual"].toBool();
			Mns[i].regBlock    = mns["regBlock"].toBool();
			Mns[i].posTB = mns["posTB"].toBool();
			Mns[i].posMB = mns["posMB"].toBool();
		}

		QVariantList listg = map["dgs"].toList();
		for(qint32 i = 0; i < N_DES_DGS && i < listg.count(); i++)
		{
			QVariantMap dgs = listg[i].toMap();
			Dgs[i].first       = dgs["first"].toBool();
			Dgs[i].regAuto     = dgs["regAuto"].toBool();
			Dgs[i].regSemiAuto = dgs["regSemiAuto"].toBool();
			Dgs[i].regTest     = dgs["regTest"].toBool();
			Dgs[i].regManual   = dgs["regManual"].toBool();
			Dgs[i].regBlock    = dgs["regBlock"].toBool();
			Dgs[i].posGB = dgs["posGB"].toBool();
			Dgs[i].runDG = dgs["runDG"].toBool();
		}

	}

}DesConfig;


#endif // _DES_STRUCT_H_
