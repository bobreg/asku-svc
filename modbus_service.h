#ifndef __MODBUS_SERVICE_H__
#define __MODBUS_SERVICE_H__

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include "../common/tcpnetwork.h"
#include "modbus_device.h"
#include "modbus_packet.h"

//-----------------------------------------------------------------------------

#define MODBUS_MAX_PORTS 2
#define MODBUS_MAX_DEVICES 8

#define MODBUS_MAIN_PORT 0
#define MODBUS_RESERVE_PORT 1

#define MODBUS_PORT_1 0
#define MODBUS_PORT_2 1

enum PORT_COUNTER
{
	PORT_COUNTER_POSITIVE = 8,
	PORT_COUNTER_NEGATIVE = -6
};

//-----------------------------------------------------------------------------

typedef struct tagModbusPortState
{
	union PortsState
	{
		struct _Bits
		{
			unsigned short	Opened		:1;	// Port - Opened
			unsigned short	Active		:1;	// Port - Active
			unsigned short	Fail		:1;	// Port - Fail
			unsigned short	NoData		:1;	// Port - No data  (listening)
			unsigned short	BadData		:1;	// Port - Bad data (listening)
		} Bits;
		unsigned char _Data;
	} State;

	QDateTime	Updated;					// Updated time, milliseconds left

	tagModbusPortState()
	{
		State._Data = 0;
		Updated = QDateTime();
	}
} ModbusPortState;

//-----------------------------------------------------------------------------

class MODBUS_SERVICE : public QObject
{
	Q_OBJECT

	TcpNetwork *network;

protected:
	bool m_cmdMain;
	bool m_singleConnection;
	bool m_separateConnections;

	ModbusPortState m_portState[MODBUS_MAX_PORTS];

	bool m_isInitialized[MODBUS_MAX_PORTS];
	bool m_isConnected[MODBUS_MAX_PORTS];

private:
	qint32 m_portCounter[MODBUS_MAX_PORTS];

	quint16 m_port[MODBUS_MAX_PORTS];
	QHostAddress m_haConnection[MODBUS_MAX_PORTS];

	qint32 m_idConnection[MODBUS_MAX_PORTS];
	QByteArray m_dataConnection[MODBUS_MAX_PORTS];

	QTimer *queryTimer;
	QTimer *liveTimer;
	QTimer *connectTimer;

	quint32 m_queryDevice;
	QMultiMap<quint32, MODBUS_DEVICE*> devices;
	quint32 m_addressTest;

protected:
	bool processData(quint32 id, QByteArray * data);
	void processPacket(const ModbusPacket & packet);
	void checkResponcePorts();
	void test_port();

protected slots:
	void slotConnectTimer();
	void slotQueryTimer();
	void slotLiveTimer();

	void onDataArrived(qint32 id, QByteArray data);
	void onConnected(qint32 id);
	void onDisconnected(qint32 id);

	virtual void onConnected();
	virtual void onDisconnected();
	virtual void onConnectedPort(qint32 port);
	virtual void onDisconnectedPort(qint32 port);
	virtual void onChangedMain(bool main);

	virtual bool onQuery();
	virtual bool onLive();

public slots:
//slots from thread
	void setMain(bool on);
	void setSeparateConnections(bool on);
	void setSingleConnection(bool on);

public:
	MODBUS_SERVICE(QObject * parent);
	~MODBUS_SERVICE();

	bool init();
	bool isInitialized();

	ModbusPortState portState(quint32 port);

	void setTestAddress(quint32 address);

//	virtual void updateState();
	virtual void onChangedDeviceState();
	virtual void onChangedPortState();

	void resetQueryDevice();
	quint32 nextQueryDevice();

	void addConnection(QHostAddress address, quint16 port);

	void addDevice(MODBUS_DEVICE * device);
	void removeDevice(MODBUS_DEVICE * device);

	void sendToDevice(QByteArray data, qint32 connection = -1);
	void sendToDevice(quint32 p, QByteArray data);

	void startConnect(int msec);
	void stopConnect();
	void startQuery(int msec);
	void stopQuery();
	void startLive(int msec);
	void stopLive();
};

//-----------------------------------------------------------------------------

#endif // __MODBUS_SERVICE_H__
