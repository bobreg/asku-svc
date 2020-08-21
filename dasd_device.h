#ifndef __DASD_DEVICE_H__
#define __DASD_DEVICE_H__

#include <QObject>

class DASD_DEVICE
{
public:

	enum ErrorCode
	{
		NoError=0,
		ErrorNoDeviceDriver=1,
		ErrorNoDeviceBoard=2,
		ErrorInitDevice=3,
		ErrorReadWrite=4,
		ErrorNotInitialized=5,
		ErrorInvalidParameter=6
	};

	DASD_DEVICE() { lastError = ErrorNotInitialized; };
	virtual ~DASD_DEVICE() { };

	virtual bool open() { return false; };
	virtual void close() { };

	virtual qint32 write_mem(quint32, quint32*, quint32) { return 0;};
	virtual qint32 read_mem (quint32, quint32*, quint32) { return 0;};

	virtual qint32 write_mem32(quint32, quint32) { return 0;};
	virtual qint32 read_mem32 (quint32, quint32*) { return 0;};

	virtual qint32 write_port(quint32, quint16*) { return 0;};
	virtual qint32 read_port (quint32, quint16*) { return 0;};

	ErrorCode error() { return lastError; };

protected:
	ErrorCode lastError;
};

#ifdef Q_OS_WIN32

#include <windows.h>

class DASD_DEVICE_WIN : public DASD_DEVICE
{
	HANDLE device;	//WIN

public:
	DASD_DEVICE_WIN() { device=INVALID_HANDLE_VALUE;};
	virtual ~DASD_DEVICE_WIN() { };
	
	virtual bool open();
	virtual void close();

	virtual qint32 write_mem(quint32 offset, quint32 *buffer, quint32 length);
	virtual qint32 read_mem (quint32 offset, quint32 *buffer, quint32 length);

	virtual qint32 write_mem32(quint32, quint32);
	virtual qint32 read_mem32 (quint32, quint32*);

	virtual qint32 write_port(quint32 offset, quint16 *buffer);
	virtual qint32 read_port (quint32 offset, quint16 *buffer);
};

#else

class DASD_DEVICE_LINUX : public DASD_DEVICE
{
	int v4_fd;	//LIN

public:
	DASD_DEVICE_LINUX() { };
	virtual ~DASD_DEVICE_LINUX() { };
	
	virtual bool open();
	virtual void close();

	virtual qint32 write_mem(quint32 offset, quint32 *buffer, quint32 length);
	virtual qint32 read_mem (quint32 offset, quint32 *buffer, quint32 length);

	virtual qint32 write_mem32(quint32, quint32);
	virtual qint32 read_mem32 (quint32, quint32*);

	virtual qint32 write_port(quint32 offset, quint16 *buffer);
	virtual qint32 read_port (quint32 offset, quint16 *buffer);
};

#endif

#endif // __DASD_DEVICE_H__
