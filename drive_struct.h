#ifndef _DRIVE_STRUCT_H_
#define _DRIVE_STRUCT_H_

#include <QDateTime>

#define N_DRIVE 2

//Drive Commands
#define DRIVE_CMD_OFF	0
#define DRIVE_CMD_ON_1	1
#define DRIVE_CMD_ON_2	2
#define DRIVE_CMD_ON	3

// Vector state structure
typedef	struct tagVectorState
{
	struct _Bits
	{
		unsigned char	Active	:1;				// Vesper is active (working)
		unsigned char	Fail	:1;				// Vesper fail
		unsigned char	Local	:1;				// Local control
	} Bits;

	int	LastResult;								// Result of last operation

	struct VectorState
	{
		union VectorStateReg
		{
			struct _Bits
			{
				unsigned short	Ready			:1;
				unsigned short	Fail			:1;
				unsigned short	Warning			:1;
				unsigned short	WorkingAlg		:1;
				unsigned short	InvertorOn		:1;
				unsigned short	WaitingReady	:1;
				unsigned short	PowerReady		:1;
				unsigned short	Main			:1;
				unsigned short	NoLocal			:1;
				unsigned short	ModeVectorCt	:1;
				unsigned short	ModeTestUF		:1;
				unsigned short	ModeTestCur		:1;
				unsigned short	ModeTestSet		:1;
				unsigned short	ModePosition	:1;
				unsigned short	PositionSet		:1;
			} Bits;
			unsigned short	_Data;
		} RegState;

		union VectorProtectionReg
		{
			struct _Bits
			{
				unsigned short	InvCurrentLimit			:1;
				unsigned short	UdBelowMinimal			:1;
				unsigned short	UdAboveMaximum			:1;
				unsigned short	UdAboveLimit			:1;
				unsigned short	CurrentBelowMinimal		:1;
				unsigned short	CurrentAboveMaximum		:1;
				unsigned short	CurrentAboveLimit		:1;
				unsigned short	CurrentDissymetric		:1;
				unsigned short	UdChargeFail			:1;
				unsigned short	MainCircuitOnFail		:1;
				unsigned short	LostLinkOfControl		:1;
				unsigned short	EmergencyStop			:1;
				unsigned short	ExternalBanOfWork		:1;
				unsigned short	DeviationOfRotorSpeed	:1;
				unsigned short	DeviationOfRotorPosition:1;
				unsigned short	TrailerSensorSet		:1;
			} Bits;
			unsigned short	_Data;
		} RegProtect;

		union VectorProtectionAddReg
		{
			struct _Bits
			{
				unsigned short	SpeedDecrease			:1;
				unsigned short	SpeedDecreaseUd			:1;
				unsigned short	CurrentLeekage			:1;
				unsigned short	Reserved				:4;
				unsigned short	SelfExcitation			:1;
			} Bits;
			unsigned short	_Data;
		} RegProtectAdd;

		union VectorOverheatReg
		{
			struct _Bits
			{
				unsigned short	Sensor1		:1;
				unsigned short	Sensor2		:1;
				unsigned short	Sensor3		:1;
				unsigned short	Sensor4		:1;
				unsigned short	Invertor	:1;
				unsigned short	TimeCurrent	:1;
			} Bits;
			unsigned short	_Data;
		} RegOverheat;

		union VectorHardwareFailReg
		{
			struct _Bits
			{
				unsigned short	FlashMemory			:1;
				unsigned short	PowerOfCtrlModule	:1;
				unsigned short	LinkXilinxToCpu		:1;
				unsigned short	LinkCpuToXilinx		:1;
				unsigned short	ADP					:1;
				unsigned short	CAN					:1;
				unsigned short	InvertorPower		:1;
				unsigned short	SensorIncBreak		:1;
				unsigned short	ErrorIndexLabel		:1;
				unsigned short	SensorAbsBreak		:1;
				unsigned short	ErrorAbsLabel		:1;
				unsigned short	RestartSoftware		:1;
			} Bits;
			unsigned short	_Data;
		} RegHardware;

		union VectorSoftwareFailReg
		{
			struct _Bits
			{
				unsigned short	ErrorInfoStruct		:1;
				unsigned short	ErrorCRC1			:1;
				unsigned short	ErrorCRC2			:1;
				unsigned short	ErrorCRC3			:1;
				unsigned short	ParameterConflict	:1;
			} Bits;
			unsigned short	_Data;
		} RegSoftware;

		union VectorMainReserveLinkReg
		{
			struct _Bits
			{
				unsigned short	NoAnswerOther		:1;
				unsigned short	NoQueryOther		:1;
				unsigned short	ErrorParameterOther	:1;
				unsigned short	ErrorVersionOther	:1;
				unsigned short	MainModeOther		:1;
			} Bits;
			unsigned short	_Data;
		} RegLink;

		union VectorWarningReg
		{
			struct _Bits
			{
				unsigned short	VoltageLow			:1;
				unsigned short	VoltageBelowMinimal	:1;
				unsigned short	VoltageAboveMaximal	:1;
				unsigned short	CurrentAboveMaximum	:1;
				unsigned short	CurrentBelowMinimal	:1;
				unsigned short	CurrentDissymetric	:1;
				unsigned short	PowerContactorOpen	:1;
				unsigned short	ReserveFail			:1;
				unsigned short	ErrorIndexLabel		:1;
				unsigned short	DebugMode			:1;
				unsigned short	ExternalBanOfWork	:1;
				unsigned short	SpeedDecrease		:1;
				unsigned short	SpeedDecreaseUd		:1;
				unsigned short	MomentAboveSet		:1;
				unsigned short	LeftTrailerSensorSet:1;
				unsigned short	RightTrailerSensorSet:1;
			} Bits;
			unsigned short	_Data;
		} RegWarning;

		union VectorSpeedReg
		{
			signed short	_Data;
			double RealValue() {
				return ((double)_Data / 100.0);
			}
		} RegSpeed;

		union VectorPositionReg
		{
			unsigned short	_Data;
			double RealValue() {
				return ((double)_Data / 100.0);
			}
		} RegPosition;

		union VectorRotStatPositionReg
		{
			unsigned short	_Data;
			double RealValue() {
				return ((double)_Data / 100.0);
			}
		} RegRotStatPos;

		union VectorMomentReg
		{
			signed short	_Data;
			double RealValue() {
				return ((double)_Data);
			}
		} RegMoment;

		union VectorCurrentReg
		{
			unsigned short	_Data;
			double RealValue() {
				return ((double)_Data / 10.0);
			}
		} RegCurrent;

		union VectorVoltageReg
		{
			unsigned short	_Data;
			double RealValue() {
				return ((double)_Data);
			}
		} RegVoltage;

		union VectorFirmwareConfigReg
		{
			unsigned short	_Data;
			quint32 Config() {
				return _Data;
			}
		} RegFWConf;

		union VectorVersionReg
		{
			unsigned short	_Data;
		} RegVersion;

		union VectorVersionDateReg
		{
			unsigned short	_Data;
		} RegVersionDate;

		union VectorVersionTimeReg
		{
			unsigned short	_Data;
		} RegVersionTime;

		union VectorSerialReg
		{
			unsigned short	_Data;
			quint32 Serial() {
				return _Data;
			}
		} RegSerial;

		union VectorProductionDateReg
		{
			unsigned short	_Data;
		} RegProductionDate;

		union VectorWorkHoursReg
		{
			unsigned short	_Data;
			quint32 Hours() {
				return (quint32)_Data * 10;
			}
		} RegWorkHours;

		QString strVersion() {
			return QString::number(RegVersion._Data) + QString(" ") + QString::number(RegVersionDate._Data) + QString(" ") + QString::number(RegVersionTime._Data);
		}

		QDateTime	Updated;				// State register updated time, milliseconds left

		VectorState() : Updated()
		{
			RegState._Data = 0;
			RegProtect._Data = 0;
			RegProtectAdd._Data = 0;
			RegOverheat._Data = 0;
			RegHardware._Data = 0;
			RegSoftware._Data = 0;
			RegLink._Data = 0;
			RegWarning._Data = 0;
			RegSpeed._Data = 0;
			RegPosition._Data = 0;
			RegRotStatPos._Data = 0;
			RegMoment._Data = 0;
			RegCurrent._Data = 0;
			RegVoltage._Data = 0;
			RegFWConf._Data = 0;
			RegVersion._Data = 0;
			RegVersionDate._Data = 0;
			RegVersionTime._Data = 0;
			RegSerial._Data = 0;
			RegProductionDate._Data = 0;
			RegWorkHours._Data = 0;
		}

	} State;

	QDateTime	Updated;					// Structure updated time, milliseconds left

	tagVectorState() : Updated()
	{
		Bits.Active = 0;
		Bits.Fail = 0;
		Bits.Local = 0;

		LastResult = 0;
	}
} VectorState;


typedef struct tagDriveState
{
	VectorState  Vector[N_DRIVE];

	QDateTime Updated;

	tagDriveState() : Updated()
	{
	}
}DriveState;


typedef struct tagDriveConfig
{
	bool first;
	bool start;
	bool separate;
	quint32 override;
	double speed;
	bool reset;
	bool main;
	bool manual;
	bool monitor;

	tagDriveConfig()
	{
		first = false;
		main = false;
		start = false;
		separate = false;
		reset = false;
		manual = false;
		monitor = false;
		override = 0;
		speed = 0.0;
	}

	tagDriveConfig(QVariantMap data)
	{
		fromMap(data);
	}

	QVariantMap toMap() {
		QVariantMap map;

		map["first"] = first;
		map["main"] = main;
		map["start"] = start;
		map["separate"] = separate;
		map["reset"] = reset;
		map["manual"] = manual;
		map["monitor"] = monitor;
		map["override"] = override;
		map["speed"] = speed;

		return map;
	}
	void fromMap(QVariantMap map) {
		first = map["first"].toBool();
		main = map["main"].toBool();
		start = map["start"].toBool();
		separate = map["separate"].toBool();
		reset = map["reset"].toBool();
		manual = map["manual"].toBool();
		monitor = map["monitor"].toBool();
		override = map["override"].toUInt();
		speed = map["speed"].toDouble();
	}
}DriveConfig;

#endif // _DRIVE_STRUCT_H_
