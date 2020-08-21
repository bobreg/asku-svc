#ifndef _COOLERS_STRUCT_H_
#define _COOLERS_STRUCT_H_

#include <QDateTime>

#define N_COOLERS 4

#define VESPER_TYPE_DEFAULT 0
#define VESPER_TYPE_E3_8100 1
#define VESPER_TYPE_E3_8300 2

// Vesper state structure
typedef	struct tagVesperState
{
	unsigned int Type;

	struct _Bits
	{
		unsigned char	Active	:1;				// Vesper is active (working)
		unsigned char	Fail	:1;				// Vesper fail
		unsigned char	Local	:1;				// Local control
	} Bits;

	int	LastResult;								// Result of last operation

	struct VesperState_E3_8100
	{
		union VesperStateReg
		{
			struct _Bits
			{
				unsigned short rotation	:1;
				unsigned short reverse	:1;
				unsigned short ready	:1;
				unsigned short fail		:1;
				unsigned short inputErr	:1;
				unsigned short mfo		:1;
				unsigned short unused	:10;
			} Bits;
			unsigned short	_Data;
		} RegState;

		union VesperFailureReg
		{
			struct _Bits
			{
				unsigned short overCurrent		:1;
				unsigned short overVoltage		:1;
				unsigned short overConverter1	:1;
				unsigned short overHeat			:1;
				unsigned short unused			:3;
				unsigned short emergencyStop	:1;
				unsigned short processorFail	:1;
				unsigned short overDrive		:1;
				unsigned short overConverter2	:1;
				unsigned short overMoment		:1;
				unsigned short lowVoltage		:1;
				unsigned short lowDCVoltage		:1;
				unsigned short errModbus		:1;
				unsigned short errControl		:1;
			} Bits;
			unsigned short	_Data;
		} RegFailure;

		union VesperSoftwareReg
		{
			struct _Bits
			{
				unsigned short writingData		:1;
				unsigned short unused1			:2;
				unsigned short valueOverLimits	:1;
				unsigned short valueInvalid		:1;
				unsigned short unused2			:11;
			} Bits;
			unsigned short	_Data;
		} RegSoftware;

		union VesperWarningReg
		{
			struct _Bits
			{
				unsigned short rotation			:1;
				unsigned short zeroSpeed		:1;
				unsigned short achievedFreq		:1;
				unsigned short error			:1;
				unsigned short lowFreqLimit		:1;
				unsigned short highFreqLimit	:1;
				unsigned short ready			:1;
				unsigned short lowVoltage		:1;
				unsigned short blocked			:1;
				unsigned short sourceFreq		:1;
				unsigned short sourceStart		:1;
				unsigned short overMoment		:1;
				unsigned short lowMoment		:1;
				unsigned short manyErrors		:1;
				unsigned short fail				:1;
				unsigned short failPLC			:1;
			} Bits;
			unsigned short	_Data;
		} RegWarning;

		union VesperMFInputReg
		{
			struct _Bits
			{
				unsigned short s1		:1;
				unsigned short s2		:1;
				unsigned short s3		:1;
				unsigned short s4		:1;
				unsigned short s5		:1;
				unsigned short unused	:11;
			} Bits;
			unsigned short	_Data;
		} RegMFInput;

		union VesperMFOutputReg
		{
			struct _Bits
			{
				unsigned short relay	:1;
				unsigned short optron	:1;
				unsigned short unused	:14;
			} Bits;
			unsigned short	_Data;
		} RegMFOutput;

		union VesperConnectionReg
		{
			struct _Bits
			{
				unsigned short errCrc		:1;
				unsigned short errLength	:1;
				unsigned short errParity	:1;
				unsigned short errValue		:1;
				unsigned short errFormat	:1;
				unsigned short errTimeout	:1;
				unsigned short unused		:10;
			} Bits;
			unsigned short	_Data;
		} RegConnection;

		union VesperFrequencyReg
		{
			unsigned short _Data;
			double freq()
			{
				return ((double)_Data / 10.0);
			}
			void setFreq(double value)
			{
				value *= 10.0;
				if ((value - (double)(unsigned short)value) < 0.5)
					_Data = (unsigned short)value;
				else
					_Data = (unsigned short)value + 1;
			}
		} RegFrequency;

		union VesperOutFrequencyReg
		{
			unsigned short _Data;
			double freq()
			{
				return ((double)_Data / 10.0);
			}
		} RegOutFrequency;

		union VesperOutCurrentReg
		{
			unsigned short _Data;
			double current()
			{
				return ((double)_Data / 10.0);
			}
		} RegOutCurrent;

		union VesperOutVoltageReg
		{
			unsigned short _Data;
			double voltage()
			{
				return ((double)_Data);
			}
		} RegOutVoltage;

		union VesperDCVoltageReg
		{
			unsigned short _Data;
			double voltage()
			{
				return ((double)_Data);
			}
		} RegDCVoltage;

		union VesperOutMomentReg
		{
			unsigned short _Data;
			double moment()
			{
				return ((double)_Data);
			}
		} RegOutMoment;

		union VesperOutPowerReg
		{
			unsigned short _Data;
			double power()
			{
				return ((double)_Data);
			}
		} RegOutPower;

		union VesperTimeworkReg
		{
			unsigned short _Data;
			double hours()
			{
				return ((double)_Data);
			}
		} RegTimework;

		QDateTime	Updated;

		VesperState_E3_8100() : Updated()
		{
			RegState._Data = 0;
			RegFailure._Data = 0;
			RegSoftware._Data = 0;
			RegWarning._Data = 0;
			RegMFInput._Data = 0;
			RegMFOutput._Data = 0;
			RegConnection._Data = 0;
			RegFrequency._Data = 0;
			RegOutFrequency._Data = 0;
			RegOutCurrent._Data = 0;
			RegOutVoltage._Data = 0;
			RegDCVoltage._Data = 0;
			RegOutMoment._Data = 0;
			RegOutPower._Data = 0;
			RegTimework._Data = 0;
		}

	} State_8100;


	struct VesperState_E3_8300
	{
		union VesperStateReg
		{
			struct _Bits
			{
				unsigned short Rotation	:1;
				unsigned short Reverse	:1;
				unsigned short Ready	:1;
				unsigned short Fail		:1;
				unsigned short InputErr	:1;
				unsigned short Unused	:11;
			} Bits;
			unsigned short	_Data;
		} RegState;

		union VesperErrorCodeReg
		{
			unsigned short	_Data;
			unsigned short errorCode()
			{
				return _Data;
			}
		} RegErrorCode;

		union VesperMFInOutReg
		{
			struct _Bits
			{
				unsigned short In_s1			:1;
				unsigned short In_s2			:1;
				unsigned short In_s3			:1;
				unsigned short In_s4			:1;
				unsigned short in_s5			:1;
				unsigned short In_s6			:1;
				unsigned short In_ain			:1;
				unsigned short Unused1			:3;
				unsigned short Out_r1a_r1c		:1;
				unsigned short Out_r2a_r2c		:1;
				unsigned short Unused2			:4;
			} Bits;
			unsigned short	_Data;
		} RegMFInOut;

		union VesperFrequencyReg
		{
			unsigned short _Data;
			double freq()
			{
				return ((double)_Data / 100.0);
			}
			void setFreq(double value)
			{
				value *= 100.0;
				if ((value - (double)(unsigned short)value) < 0.5)
					_Data = (unsigned short)value;
				else
					_Data = (unsigned short)value + 1;
			}
		} RegFrequency;

		union VesperOutFrequencyReg
		{
			unsigned short _Data;
			double freq()
			{
				return ((double)_Data / 100.0);
			}
		} RegOutFrequency;

		union VesperOutVoltageReg
		{
			unsigned short _Data;
			double voltage()
			{
				return ((double)_Data);
			}
		} RegOutVoltage;

		union VesperDCVoltageReg
		{
			unsigned short _Data;
			double voltage()
			{
				return ((double)_Data);
			}
		} RegDCVoltage;

		union VesperOutCurrentReg
		{
			unsigned short _Data;
			double current()
			{
				return ((double)_Data / 10.0);
			}
		} RegOutCurrent;

		union VesperOutMomentReg
		{
			unsigned short _Data;
			double moment()
			{
				return ((double)_Data);
			}
		} RegOutMoment;

		QDateTime	Updated;

		VesperState_E3_8300() : Updated()
		{
			RegState._Data = 0;
			RegErrorCode._Data = 0;
			RegMFInOut._Data = 0;
			RegFrequency._Data = 0;
			RegOutFrequency._Data = 0;
			RegOutVoltage._Data = 0;
			RegDCVoltage._Data = 0;
			RegOutCurrent._Data = 0;
			RegOutMoment._Data = 0;
		}

	} State_8300;


	struct VesperControl_E3_8100
	{
		union VesperControlReg
		{
			struct _Bits
			{
				unsigned short start	:1;
				unsigned short reverse	:1;
				unsigned short extFail	:1;
				unsigned short resetErr	:1;
				unsigned short freq1	:1;
				unsigned short freq2	:1;
				unsigned short freq3	:1;
				unsigned short freq4	:1;
				unsigned short freq5	:1;
				unsigned short freq6	:1;
				unsigned short freq7	:1;
				unsigned short unused	:5;
			} Bits;
			unsigned short	_Data;
		} RegControl;

		union VesperFrequencyReg
		{
			unsigned short _Data;
			double freq()
			{
				return ((double)_Data / 10.0);
			}
			void setFreq(double value)
			{
				value *= 10.0;
				if ((value - (double)(unsigned short)value) < 0.5)
					_Data = (unsigned short)value;
				else
					_Data = (unsigned short)value + 1;
			}
		} RegFrequency;

		QDateTime	Updated;

		VesperControl_E3_8100() : Updated()
		{
			RegControl._Data = 0;
			RegFrequency._Data = 0;
		}

	} Control_8100;

	struct VesperControl_E3_8300
	{
		union VesperControlReg
		{
			struct _Bits
			{
				unsigned short start	:1;
				unsigned short reverse	:1;
				unsigned short extFail	:1;
				unsigned short resetErr	:1;
				unsigned short reserved	:1;
				unsigned short mf_s1	:1;
				unsigned short mf_s2	:1;
				unsigned short mf_s3	:1;
				unsigned short mf_s4	:1;
				unsigned short mf_s5	:1;
				unsigned short mf_s6	:1;
				unsigned short mf_ain	:1;
				unsigned short mf_r1a	:1;
				unsigned short mf_r2a	:1;
				unsigned short unused	:2;
			} Bits;
			unsigned short	_Data;
		} RegControl;

		union VesperFrequencyReg
		{
			unsigned short _Data;
			double freq()
			{
				return ((double)_Data / 100.0);
			}
			void setFreq(double value)
			{
				value *= 100.0;
				if ((value - (double)(unsigned short)value) < 0.5)
					_Data = (unsigned short)value;
				else
					_Data = (unsigned short)value + 1;
			}
		} RegFrequency;

		QDateTime	Updated;

		VesperControl_E3_8300() : Updated()
		{
			RegControl._Data = 0;
			RegFrequency._Data = 0;
		}

	} Control_8300;

	QDateTime	Updated;					// Structure updated time, milliseconds left

	tagVesperState() : Updated()
	{
		Bits.Active = 0;
		Bits.Fail = 0;
		Bits.Local = 0;

		LastResult = 0;
		Type = VESPER_TYPE_DEFAULT;
	}
} VesperState;


typedef struct tagCoolersState
{
	VesperState Vesper[N_COOLERS];

	QDateTime Updated;

	tagCoolersState() : Updated()
	{
	}
}CoolersState;


typedef struct tagCoolersConfig
{
	unsigned int type;

	bool main;
	bool reset;
	bool manual;
	bool monitor;
	double exttemp;

	struct VesperConfig
	{
		qint32 status;
		bool first;
		bool start;
		bool prdon;
		double temp;
		double freq;
		QDateTime freqUpdated;

		VesperConfig() : freqUpdated()
		{
			status = -1;
			first = false;
			start = false;
			prdon = false;
			temp = -255.0;
			freq = 0.0;
		}

	}Vesper[N_COOLERS];

	tagCoolersConfig()
	{
		type = VESPER_TYPE_DEFAULT;
		main = false;
		reset = false;
		manual = false;
		monitor = false;
		exttemp = -255.0;
	}

	tagCoolersConfig(QVariantMap data)
	{
		fromMap(data);
	}

	QVariantMap toMap() {
		QVariantMap map;

		map["main"] = main;
		map["type"] = type;
		map["reset"] = reset;
		map["manual"] = manual;
		map["monitor"] = monitor;
		map["exttemp"] = exttemp;

		QVariantList list;
		for(quint32 i = 0; i < N_COOLERS; i++)
		{
			QVariantMap vesp;
			vesp["first"] = Vesper[i].first;
			vesp["start"] = Vesper[i].start;
			vesp["prdon"] = Vesper[i].prdon;
			vesp["temp"] = Vesper[i].temp;
			vesp["freq"] = Vesper[i].freq;
			list << vesp;
		}
		map["vespers"] = list;
		
		return map;
	}
	void fromMap(QVariantMap map) {
		main = map["main"].toBool();
		type = map["type"].toBool();
		reset = map["reset"].toBool();
		manual = map["manual"].toBool();
		monitor = map["monitor"].toBool();
		exttemp = map["exttemp"].toDouble();

		QVariantList list = map["vespers"].toList();
		for(qint32 i = 0; i < N_COOLERS && i < list.count(); i++)
		{
			QVariantMap vesp = list[i].toMap();
			Vesper[i].first = vesp["first"].toBool();
			Vesper[i].start = vesp["start"].toBool();
			Vesper[i].prdon = vesp["prdon"].toBool();
			Vesper[i].temp = vesp["temp"].toDouble();
			Vesper[i].freq = vesp["freq"].toDouble();
		}
	}

}CoolersConfig;

#endif // _COOLERS_STRUCT_H_
