#include "../common/logger.h"
#include <QThread>
#include <QDir>
#include "globalvar.h"
#include "modbus_service.h"
#include "modbus_device.h"
#include "modbus_packet.h"

// ------------------------------------------------------------------
MODBUS_SERVICE::MODBUS_SERVICE(QObject *p) : QObject(p)
{
	network = NULL;
	queryTimer = NULL;
	liveTimer = NULL;
	connectTimer = NULL;

	m_cmdMain = false;
	m_addressTest = 0;
	m_separateConnections = false;
	m_singleConnection = false;

	for(quint32 i = 0; i < MODBUS_MAX_PORTS; i++)
	{
		m_isInitialized[i] = false;
		m_isConnected[i] = false;

		m_port[i] = 0;
		m_haConnection[i] = QHostAddress();

		m_idConnection[i] = -1;
		m_dataConnection[i].clear();

		m_portCounter[i] = 0;
	}
}

// ------------------------------------------------------------------
bool MODBUS_SERVICE::init()
{
	m_queryDevice = 0;

	queryTimer = new QTimer(this);
	connect(queryTimer,SIGNAL(timeout()),this,SLOT(slotQueryTimer()));

	liveTimer = new QTimer(this);
	connect(liveTimer,SIGNAL(timeout()),this,SLOT(slotLiveTimer()));

	connectTimer = new QTimer(this);
	connect(connectTimer,SIGNAL(timeout()),this,SLOT(slotConnectTimer()));

	network = new TcpNetwork(this, QString("MODBUS_NET"));
	if(network)
	{
		connect(network, SIGNAL(sigConnected(qint32,QHostAddress,quint16)), this, SLOT(onConnected(qint32)));
		connect(network, SIGNAL(sigDisconnected(qint32)), this, SLOT(onDisconnected(qint32)));
		connect(network, SIGNAL(dataArrived(qint32, QByteArray)), this, SLOT(onDataArrived(qint32, QByteArray)));

		LogModbusInfo("ModbusService started");
		for(quint32 i = 0; i < MODBUS_MAX_PORTS; i++)
			if(m_port[i] && !m_haConnection[i].isNull())
				m_isInitialized[i] = network->init(m_haConnection[i], m_port[i]);
	}

	return false;
}

// ------------------------------------------------------------------
MODBUS_SERVICE::~MODBUS_SERVICE()
{
	if(connectTimer)
	{
		connectTimer->stop();
		delete connectTimer;
		connectTimer = NULL;
	}
	if(liveTimer)
	{
		liveTimer->stop();
		delete liveTimer;
		liveTimer = NULL;
	}
	if(queryTimer)
	{
		queryTimer->stop();
		delete queryTimer;
		queryTimer = NULL;
	}
	if(network)
	{
		network->destroy();
		delete network;
		network = NULL;
	}
}

// ------------------------------------------------------------------
bool MODBUS_SERVICE::isInitialized()
{
	return m_isInitialized;
}

// ------------------------------------------------------------------
ModbusPortState MODBUS_SERVICE::portState(quint32 port)
{
	if(port < MODBUS_MAX_PORTS)
		return m_portState[port];
	else
		return ModbusPortState();
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::setTestAddress(quint32 address)
{
	m_addressTest = address;
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::resetQueryDevice()
{
	m_queryDevice = 0;
}

// ------------------------------------------------------------------
quint32 MODBUS_SERVICE::nextQueryDevice()
{
	quint32 temp = m_queryDevice;

	m_queryDevice++;

	if(m_queryDevice >= (quint32)devices.count())
		m_queryDevice = 0;

	return temp;
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::setMain(bool main)
{
	if(main != m_cmdMain)
	{
		m_cmdMain = main;
	}

	onChangedMain(m_cmdMain);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::setSeparateConnections(bool on)
{
	m_separateConnections = on;
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::setSingleConnection(bool on)
{
	m_singleConnection = on;
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::onChangedMain(bool main)
{
	Q_UNUSED(main);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::addConnection(QHostAddress address, quint16 port)
{
	for(quint32 i = 0; i < MODBUS_MAX_PORTS; i++)
		if(m_port[i] == 0 && m_haConnection[i].isNull())
		{
			LogModbusInfo("MODBUS: add connection to %s:%d", qPrintable(address.toString()), port);
			m_haConnection[i] = address;
			m_port[i] = port;
			break;
		}
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::addDevice(MODBUS_DEVICE * device)
{
	quint32 address = device->address();
	LogModbusInfo("MODBUS: add device %d", device->address());
	if(devices.contains(address) && !device->isConnectionDependent())
		LogModbusError("MODBUS: error add device %d: address already in list", address);
	devices.insert(address, device);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::removeDevice(MODBUS_DEVICE * device)
{
	quint32 address = device->address();
	LogModbusInfo("MODBUS: remove device %d", device->address());
	if(devices.contains(address, device))
		devices.remove(address, device);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::startConnect(int msec)
{
	if(connectTimer)
		connectTimer->start(msec);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::stopConnect()
{
	if(connectTimer)
		connectTimer->stop();
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::startQuery(int msec)
{
	if(connectTimer)
		connectTimer->stop();

	if(queryTimer)
		queryTimer->start(msec);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::stopQuery()
{
	if(queryTimer)
		queryTimer->stop();
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::startLive(int msec)
{
	if(liveTimer)
		liveTimer->start(msec);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::stopLive()
{
	if(liveTimer)
		liveTimer->stop();
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::slotConnectTimer()
{
	LogModbusInfo("MODBUS: connect timeout");
	stopConnect();
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::slotLiveTimer()
{
	if(!m_cmdMain)
		return;

	LogModbusInfo("MODBUS: live timer");
	onLive();
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::slotQueryTimer()
{
	if(!m_cmdMain)
		return;

	LogModbusInfo("MODBUS: query timer");

	if(!onQuery())
	{
		if(!m_separateConnections && !m_singleConnection)
			test_port();

		checkResponcePorts();
	}
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::onConnected(qint32 id)
{
	TcpNetworkConnection *c = network->connectionInfo(id);
	if(c)
	{
		for(quint32 p = 0; p < MODBUS_MAX_PORTS; p++)
			if(c->peerAddress() == m_haConnection[p] && c->peerPort() == m_port[p])
			{
				if(m_idConnection[p] == -1)
				{
					LogModbusInfo("MODBUS: id=%d connection on port%d", id, p+1);

					quint32 count = 0;
					for(quint32 i = 0; i < MODBUS_MAX_PORTS; i++)
						if(m_idConnection[i] == -1)
							count++;

					m_idConnection[p] = id;
					m_isConnected[p] = true;
					m_dataConnection[p].clear();

					if(count == MODBUS_MAX_PORTS)
					{
						LogModbusInfo("MODBUS: connected port%d", p+1);
						stopConnect();
						onConnected();
					}

					m_portState[p].State.Bits.Opened = 1;

					if(m_separateConnections)
					{
						onConnectedPort(p);
						LogModbusInfo("MODBUS: set port%d active", p+1);
						m_portState[p].State.Bits.Active = 1;
					}
					else
					{
						if(p == MODBUS_MAIN_PORT)
						{
							if(m_portState[MODBUS_RESERVE_PORT].State.Bits.Opened == 0)
							{
								LogModbusInfo("MODBUS: set main port active");
								m_portState[p].State.Bits.Active = 1;
							}
						}
						else
						{
							if(m_portState[MODBUS_MAIN_PORT].State.Bits.Opened == 0)
							{
								LogModbusInfo("MODBUS: set reserve port active");
								m_portState[p].State.Bits.Active = 1;
							}
						}
					}

					m_portState[p].Updated = QDateTime::currentDateTime();
					m_portCounter[p] = PORT_COUNTER_NEGATIVE;

					onChangedPortState();
				}
			}
	}
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::onDisconnected(qint32 id)
{
	for(quint32 p = 0; p < MODBUS_MAX_PORTS; p++)
		if(m_idConnection[p] == id)
		{
			LogModbusInfo("MODBUS: id=%d disconnection on port%d", id, p+1);

			m_idConnection[p] = -1;
			m_isConnected[p] = false;
			m_dataConnection[p].clear();

			quint32 count = 0;
			for(quint32 i = 0; i < MODBUS_MAX_PORTS; i++)
				if(m_idConnection[i] == -1)
					count++;

			if(count == MODBUS_MAX_PORTS)
			{
				LogModbusInfo("MODBUS: disconnected port%d", p+1);
				stopQuery();
				stopLive();
				onDisconnected();
			}

			m_portCounter[p] = 0;

			m_portState[p].State.Bits.NoData = 0;
			m_portState[p].State.Bits.Opened = 0;
			m_portState[p].State.Bits.Active = 0;

			if(m_separateConnections)
			{
				onDisconnectedPort(p);
			}
			else
			{
				if(p == MODBUS_MAIN_PORT)
				{
					if(m_portState[MODBUS_RESERVE_PORT].State.Bits.Opened == 1 && m_portState[MODBUS_RESERVE_PORT].State.Bits.Active == 0)
					{
						LogModbusInfo("MODBUS: set reserve port active (disconnect main)");
						m_portState[MODBUS_RESERVE_PORT].State.Bits.Active = 1;
					}
				}
				else
				{
					if(m_portState[MODBUS_MAIN_PORT].State.Bits.Opened == 1 && m_portState[MODBUS_MAIN_PORT].State.Bits.Active == 0)
					{
						LogModbusInfo("MODBUS: set main port active (disconnect reserve)");
						m_portState[MODBUS_MAIN_PORT].State.Bits.Active = 1;
					}
				}
			}

			m_portState[p].Updated = QDateTime::currentDateTime();

			onChangedPortState();
		}
}

// ------------------------------------------------------------------
bool MODBUS_SERVICE::onQuery()
{
	return false;
}

// ------------------------------------------------------------------
bool MODBUS_SERVICE::onLive()
{
	return false;
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::onDataArrived(qint32 id, QByteArray data)
{
	LogModbusBinary("MODBUS: id=%d data=%s", id, qPrintable(LogArray(data)));

	for(quint32 p = 0; p < MODBUS_MAX_PORTS; p++)
		if(m_idConnection[p] == id)
		{
			m_dataConnection[p] += data;
			while(processData(p, &m_dataConnection[p]));
		}
}

// ------------------------------------------------------------------
bool MODBUS_SERVICE::processData(quint32 n_port, QByteArray * buffer)
{
	QList<ModbusPacket> p;
	int bad = ModbusPacket::processBuffer(buffer, &p);

	if(bad)
		m_portState[n_port].State.Bits.BadData = 1;
	else
		m_portState[n_port].State.Bits.BadData = 0;

	if(m_portCounter[n_port] <= 0)
	{
		if(m_portState[n_port].State.Bits.NoData)
			LogModbusInfo(QString("MODBUS: port %1: responce").arg(n_port));

		m_portState[n_port].State.Bits.NoData = 0;
		m_portState[n_port].Updated = QDateTime::currentDateTime();

		onChangedPortState();
	}

	m_portCounter[n_port] = PORT_COUNTER_POSITIVE;

	if(!bad && p.count() > 0)
	{
		for(QList<ModbusPacket>::const_iterator packet = p.constBegin(); packet != p.constEnd(); ++packet)
			foreach(MODBUS_DEVICE * dev, devices)
				if(dev)
				{
					qint32 connection = dev->connection();
					if((connection < 0) || ((connection >= 0) && ((quint32)connection == n_port)))
						dev->processPacket(*packet);
				}
	}

	return false;

}

// ------------------------------------------------------------------
void MODBUS_SERVICE::processPacket(const ModbusPacket & packet)
{
	Q_UNUSED(packet);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::checkResponcePorts()
{
	bool need_check_ports = false;

	for(quint32 nn = 0; nn < MODBUS_MAX_PORTS; nn++)
	if(m_portCounter[nn])
	{
		if(m_portCounter[nn] > 0)
			m_portCounter[nn]--;
		else
			m_portCounter[nn]++;

		if(m_portCounter[nn] == 0)
		{
			if(!m_portState[nn].State.Bits.NoData)
				LogModbusInfo(QString("MODBUS: port %1: timeout responce").arg(nn));
			m_portState[nn].State.Bits.NoData = 1;
			need_check_ports = true;
		}
	}

	if(need_check_ports)
	{
		if(m_portState[MODBUS_MAIN_PORT].State.Bits.Opened && m_portState[MODBUS_MAIN_PORT].State.Bits.Active && m_portState[MODBUS_MAIN_PORT].State.Bits.NoData && 
			m_portState[MODBUS_RESERVE_PORT].State.Bits.Opened)
		{
			if(!m_separateConnections)
			{
				m_portState[MODBUS_MAIN_PORT].State.Bits.Active = 0;
				m_portState[MODBUS_RESERVE_PORT].State.Bits.Active = 1;
				LogModbusInfo("MODBUS: set reserve port active (no data on main)");
			}

			m_portCounter[MODBUS_MAIN_PORT] = PORT_COUNTER_NEGATIVE;
			m_portCounter[MODBUS_RESERVE_PORT] = PORT_COUNTER_NEGATIVE;
		}
		else if(m_portState[MODBUS_RESERVE_PORT].State.Bits.Opened && m_portState[MODBUS_RESERVE_PORT].State.Bits.Active && m_portState[MODBUS_RESERVE_PORT].State.Bits.NoData && 
			m_portState[MODBUS_MAIN_PORT].State.Bits.Opened)
		{
			if(!m_separateConnections)
			{
				m_portState[MODBUS_MAIN_PORT].State.Bits.Active = 1;
				m_portState[MODBUS_RESERVE_PORT].State.Bits.Active = 0;
				LogModbusInfo("MODBUS: set main port active (no data on reserve)");
			}

			m_portCounter[MODBUS_MAIN_PORT] = PORT_COUNTER_NEGATIVE;
			m_portCounter[MODBUS_RESERVE_PORT] = PORT_COUNTER_NEGATIVE;
		}

		m_portState[MODBUS_MAIN_PORT].Updated = QDateTime::currentDateTime();
		m_portState[MODBUS_RESERVE_PORT].Updated = QDateTime::currentDateTime();

		onChangedPortState();
	}
}

//------------------------------------------------------------------------------
void MODBUS_SERVICE::test_port()
{
	ModbusPacket pkt;
	pkt.refRead(ModbusPacket::RequestHolding, m_addressTest, 1, 1);
	LogModbusBinary("MODBUS: test port : %s", LogArray(pkt.toByteArray()));

	if(network && m_portState[MODBUS_MAIN_PORT].State.Bits.Active)
		network->sendReply(m_idConnection[MODBUS_RESERVE_PORT], pkt.toByteArray());

	if(network && m_portState[MODBUS_RESERVE_PORT].State.Bits.Active)
		network->sendReply(m_idConnection[MODBUS_MAIN_PORT], pkt.toByteArray());
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::sendToDevice(QByteArray data, qint32 connection)
{
	if(connection >= 0)
	{
		sendToDevice((quint32)connection, data);
	}
	else
	{
		sendToDevice(MODBUS_MAIN_PORT, data);
		sendToDevice(MODBUS_RESERVE_PORT, data);
	}
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::sendToDevice(quint32 p, QByteArray data)
{
	if(network && m_portState[p].State.Bits.Active)
		network->sendReply(m_idConnection[p], data);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::onConnected()
{
	
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::onDisconnected()
{
	
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::onConnectedPort(qint32 port)
{
	Q_UNUSED(port);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::onDisconnectedPort(qint32 port)
{
	Q_UNUSED(port);
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::onChangedDeviceState()
{
	
}

// ------------------------------------------------------------------
void MODBUS_SERVICE::onChangedPortState()
{
	
}

// ------------------------------------------------------------------
