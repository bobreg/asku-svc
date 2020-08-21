#include "../common/logger.h"
#include "dasd_device.h"

#ifdef Q_OS_UNIX

#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

//#define DEBUG_DASD

//=============================================================================

// include file from device driver
#include "dasd_interface.h"

//=============================================================================

bool DASD_DEVICE_LINUX::open()
{
#ifndef DEBUG_DASD
	if((v4_fd = ::open(BOARD_DEVICE, O_RDWR)) < 0)
	{
		LogModuleError("cannot open device '%s' error=%d", BOARD_DEVICE, errno);
		if(errno == ENOENT || errno == ENXIO)
			lastError = ErrorNoDeviceDriver;
		else
			lastError = ErrorNoDeviceBoard;
		return false;
	}
#endif
	lastError = NoError;
	return true;
}

//=============================================================================

void DASD_DEVICE_LINUX::close()
{
	lastError = NoError;
#ifndef DEBUG_DASD
	if(v4_fd>0)
	{
		::close(v4_fd);
		v4_fd = -1;
	}
#endif
}

//=============================================================================

qint32 DASD_DEVICE_LINUX::write_mem(quint32 offset, quint32 *buffer, quint32 length)
{
	qint32 bytes = 0;

#ifndef DEBUG_DASD
	if(v4_fd < 0)
	{
		lastError = ErrorNotInitialized;
		return bytes;
	}

	if(buffer == NULL || length == 0)
	{
		lastError = ErrorInvalidParameter;
		return bytes;
	}

	if(length == sizeof(quint32))
	    return write_mem32(offset,buffer[0]);

	IRW_QUERY_BLOCK message;
	message.offset = offset;
	message.byte_count = length;
	message.data = (void*)buffer;
	
	if(::ioctl(v4_fd, IOCTL_WRITE_BLOCK, (void*)&message) != 0)
	{
		lastError = ErrorReadWrite;
		bytes = 0;
	}
	else
	{
		lastError = NoError;
		bytes = length;
	}
#else
	lastError = NoError;
	bytes = length;
#endif

	return bytes;
}

//=============================================================================

qint32 DASD_DEVICE_LINUX::write_mem32(quint32 offset, quint32 value)
{
	qint32 bytes = 0;

#ifndef DEBUG_DASD
	if(v4_fd < 0)
	{
		lastError = ErrorNotInitialized;
		return bytes;
	}

	IRW_QUERY message;
	message.offset = offset;
	message.value = value;

	if(::ioctl(v4_fd, IOCTL_WRITE_REGISTER, (void*)&message) != 0)
	{
		lastError = ErrorReadWrite;
		bytes = 0;
	}
	else
	{
		lastError = NoError;
		bytes = sizeof(quint32);
	}
#else
	lastError = NoError;
	bytes = sizeof(quint32);
#endif

	return bytes;
}

//=============================================================================

qint32 DASD_DEVICE_LINUX::read_mem (quint32 offset, quint32 *buffer, quint32 length)
{
	qint32 bytes = -1;

#ifndef DEBUG_DASD
	if(v4_fd < 0)
	{
		lastError = ErrorNotInitialized;
		return bytes;
	}

	if(buffer == NULL || length == 0)
	{
		lastError = ErrorInvalidParameter;
		return bytes;
	}

	if(length == sizeof(quint32))
	    return read_mem32(offset,buffer);

	IRW_QUERY_BLOCK message;
	message.offset = offset;
	message.byte_count = length;
	message.data = (void*)buffer;

	if(ioctl(v4_fd, IOCTL_READ_BLOCK, (void*)&message) != 0)
	{
		lastError = ErrorReadWrite;
		bytes = -1;
	}
	else
	{
		lastError = NoError;
		bytes = length;
	}
#else
	lastError = NoError;
	bytes = length;
	memset(buffer,0,length);
#endif

	return bytes;
}

//=============================================================================

qint32 DASD_DEVICE_LINUX::read_mem32 (quint32 offset, quint32 *value)
{
	qint32 bytes = -1;

#ifndef DEBUG_DASD
	if(v4_fd < 0)
	{
		lastError = ErrorNotInitialized;
		return bytes;
	}

	if(value == NULL)
	{
		lastError = ErrorInvalidParameter;
		return bytes;
	}

	IRW_QUERY message;
	message.offset = offset;
	message.value = 0;

	if(ioctl(v4_fd, IOCTL_READ_REGISTER, (void*)&message) != 0)
	{
		lastError = ErrorReadWrite;
		bytes = -1;
	}
	else
	{
		lastError = NoError;
		bytes = sizeof(quint32);
		*value = message.value;
	}
#else
	lastError = NoError;
	bytes = sizeof(quint32);
	*value = 0;
#endif

	return bytes;
}

//=============================================================================

qint32 DASD_DEVICE_LINUX::write_port(quint32 offset, quint16 *buffer)
{
	qint32 bytes = 0;

	if(v4_fd < 0)
	{
		lastError = ErrorNotInitialized;
		return bytes;
	}

	if(buffer == NULL)
	{
		lastError = ErrorInvalidParameter;
		return bytes;
	}

	IRW_QUERY_16 message;
	message.offset = offset;
	message.value = buffer[0];
	Q_UNUSED(message);
/*
	if(::ioctl(v4_fd, IOCTL_WRITE3_REGISTER, (void*)&message) != 0)
	{
		lastError = ErrorReadWrite;
		bytes = 0;
	}
	else
	{
		lastError = NoError;
		bytes = 2;
	}
*/
	return bytes;
}

//=============================================================================

qint32 DASD_DEVICE_LINUX::read_port (quint32 offset, quint16 *buffer)
{
	qint32 bytes = 0;

	if(v4_fd < 0)
	{
		lastError = ErrorNotInitialized;
		return bytes;
	}

	if(buffer == NULL)
	{
		lastError = ErrorInvalidParameter;
		return bytes;
	}

	IRW_QUERY_16 message;
	message.offset = offset;
	message.value = 0;
	Q_UNUSED(message);
/*
	if(::ioctl(v4_fd, IOCTL_READ3_REGISTER, (void*)&message) != 0)
	{
		lastError = ErrorReadWrite;
		bytes = -1;
	}
	else
	{
		lastError = NoError;
		bytes = 2;
	}

	buffer[0] = message.value;
*/
	return bytes;
}

//=============================================================================

#else

#define _UNICODE

#include <windows.h>
#include <winioctl.h>
#include <tchar.h>
#include <time.h>

//=============================================================================
#define IOCTL_READ_MEM1  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS) 
#define IOCTL_READ_MEM2  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS) 
#define IOCTL_WRITE_MEM1  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS) 
#define IOCTL_WRITE_MEM2  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x806, METHOD_BUFFERED, FILE_ANY_ACCESS) 
#define IOCTL_READ_PORT1 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x811, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_READ_PORT2 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x812, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_WRITE_PORT1 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x813, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_WRITE_PORT2 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x814, METHOD_BUFFERED, FILE_ANY_ACCESS)
//=============================================================================

// ------------------------------------------------------------------
bool DASD_DEVICE_WIN::open()
{
#define COUNT_SYMBOL_LINK			3
#define COUNT_CHAR_IN_SYMBOL_LINK	1024
	TCHAR array_symbol_link[COUNT_SYMBOL_LINK][COUNT_CHAR_IN_SYMBOL_LINK];
	int number_last_open_device = -1;
	int device_count = 0;
	HKEY hkResult, hkControl;
	const TCHAR strSubkey[] = _T("SYSTEM\\CurrentControlSet\\Control\\DeviceClasses\\{618969c1-5928-4d81-8ea8-a4b866618600}");
	TCHAR strSimbolLink[1024];
	int i = 0;

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,(LPCTSTR)strSubkey,0,KEY_READ,&hkResult) == ERROR_SUCCESS)
	{
		while(RegEnumKey(hkResult,i,(LPTSTR)strSimbolLink,1024) == ERROR_SUCCESS)
		{
			TCHAR strFullPath[1024];
			lstrcpy((LPTSTR)strFullPath, (LPTSTR)strSubkey);
			lstrcat((LPTSTR)strFullPath, (LPTSTR)_T("\\"));
			lstrcat((LPTSTR)strFullPath, (LPTSTR)strSimbolLink);
			lstrcat((LPTSTR)strFullPath, (LPTSTR)_T("\\Control"));

			if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,(LPTSTR)strFullPath,0,KEY_READ,&hkControl) == ERROR_SUCCESS)
			{
				lstrcpy((LPTSTR)array_symbol_link[device_count], (LPTSTR)strSimbolLink);
				array_symbol_link[device_count][0] = _T('\\'); 
				array_symbol_link[device_count][1] = _T('\\');
				array_symbol_link[device_count][3] = _T('\\');

				device_count++;
				RegCloseKey(hkControl);  
			}

			i++;
		}

		RegCloseKey(HKEY_LOCAL_MACHINE);
		RegCloseKey(hkResult); 
	}
	else
	{
		//char mess[] = "мЕ МЮИДЕМ ДПЮИБЕП СЯРПНИЯРБЮ д2ба011 \n";
		lastError = ErrorNoDeviceDriver;
		return false;
	}

	if(device_count == 0)
	{
		//char mess[] = "мЕ МЮИДЕМЮ МХ НДМЮ ПЮАНРЮЧЫЮЪ ЪВ. д2ба011 \n";
		lastError = ErrorNoDeviceBoard;
		return false;
	}

	device = CreateFile(
					  (LPTSTR) array_symbol_link[ number_last_open_device + 1 ],
					  GENERIC_READ | GENERIC_WRITE,
					  FILE_SHARE_READ | FILE_SHARE_WRITE,
					  NULL, OPEN_EXISTING,
					  FILE_FLAG_OVERLAPPED,
				      NULL
				    );

	if(device == INVALID_HANDLE_VALUE)
	{
		//char mess[] = "нРЯСРЯБСЕР ХКХ МЕХЯОПЮБМЮ ЪВ. д2ба011 \n";
		lastError = ErrorInitDevice;
		return false;
	}
	else
	{
		//char mess[] = "ъВЕИЙЮ д2ба011 Й РЕЯРХПНБЮМХЧ ЦНРНБЮ \n";
		number_last_open_device++;
	}

	///////////////////////////////////////////////////////////
	// МЮЯРПЮХБЮЕЛ ПЮАНРС PLX - ДЕКЮРЭ НДХМ ПЮГ Х НАЪГЮРЕКЭМН
	DWORD device_set[2];
	DWORD count_byte;
	
	device_set[0] = 0x68;  // ЯЛЕЫЕМХЕ
	device_set[1] = 0x900; // ХМТ-ЖХЪ
	if(!DeviceIoControl(
                        device,
                        IOCTL_WRITE_MEM1,
                        device_set,
                        8,
                        NULL, NULL,
                        &count_byte,
                        NULL))
	{
    	//char mess[] = "ъВЕИЙЮ д2ба011 Й РЕЯРХПНБЮМХЧ МЕ ЦНРНБЮ \n";
		lastError = ErrorInitDevice;
		return false;
	}

	lastError = NoError;
	return true;
}

// ------------------------------------------------------------------
void DASD_DEVICE_WIN::close()
{
	lastError = NoError;
	if(device!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(device);
		device = INVALID_HANDLE_VALUE;
	}
}

// ------------------------------------------------------------------
qint32 DASD_DEVICE_WIN::write_mem(quint32 offset, quint32 *buffer, quint32 length)
{
	qint32 bytes = 0;
	qint32 count = 0;

	if(device == INVALID_HANDLE_VALUE)
	{
		lastError = ErrorNotInitialized;
		return bytes;
	}

	if(buffer == NULL || length == 0)
	{
		lastError = ErrorInvalidParameter;
		return bytes;
	}

	quint32 header_length = 2;
	quint32 header_length_bytes = header_length*sizeof(quint32);
	quint32 message_length = length+header_length_bytes;

	quint8 *message = new quint8[message_length];

	quint32 *message32 = (quint32*)message;

	for(quint32 k=0;k<length/sizeof(quint32);k++)
		message32[header_length+k]=buffer[k];

	message32[0] = offset;
	message32[1] = length;

	if(!DeviceIoControl(device,IOCTL_WRITE_MEM2,message32,message_length,NULL,NULL,(LPDWORD)&count,NULL))
	{
		lastError = ErrorReadWrite;
		bytes = 0;
	}
	else
	{
		lastError = NoError;
		bytes = length;
	}

	if(message) delete message;

	lastError = NoError;
	return bytes;
}

// ------------------------------------------------------------------
qint32 DASD_DEVICE_WIN::read_mem (quint32 offset, quint32 *buffer, quint32 length)
{
	qint32 bytes = -1;
	qint32 count = 0;

	if(device == INVALID_HANDLE_VALUE)
	{
		lastError = ErrorNotInitialized;
		return bytes;
	}

	if(buffer == NULL || length == 0)
	{
		lastError = ErrorInvalidParameter;
		return bytes;
	}

	quint32 header_length = 2;
	quint32 header_length_bytes = header_length*sizeof(quint32);
	quint32 message_length = length+header_length_bytes;

	quint8 *message = new quint8[message_length];

	quint32 *message32 = (quint32*)message;

	for(quint32 k=0;k<length/sizeof(quint32);k++)
		message32[header_length+k]=buffer[k];

	message32[0] = offset;
	message32[1] = length;

	if(!DeviceIoControl(device,IOCTL_READ_MEM2,message32,header_length_bytes,&message32[header_length],length,(LPDWORD)&count,NULL))
	{
		lastError = ErrorReadWrite;
		bytes = -1;
	}
	else
	{
		lastError = NoError;
		bytes = length;
	}

	for(quint32 d=0;d<length/sizeof(quint32);d++)
		buffer[d] = message32[header_length+d];

	if(message) delete message;

	return bytes;
}

// ------------------------------------------------------------------
qint32 DASD_DEVICE_WIN::write_port(quint32 offset, quint16 *buffer)
{
	qint32 bytes = 0;
	qint32 count = 0;

	if(device == INVALID_HANDLE_VALUE)
	{
		lastError = ErrorNotInitialized;
		return bytes;
	}

	if(buffer == NULL)
	{
		lastError = ErrorInvalidParameter;
		return bytes;
	}

	quint16 message[2];
	message[0] = offset;
	message[1] = buffer[0];

	if(!DeviceIoControl(device,IOCTL_WRITE_PORT2,&message[0],sizeof(message),NULL,NULL,(LPDWORD)&count,NULL))
	{
		lastError = ErrorReadWrite;
		bytes = 0;
	}
	else
	{
		lastError = NoError;
		bytes = 2;
	}

	return bytes;



}

// ------------------------------------------------------------------
qint32 DASD_DEVICE_WIN::read_port (quint32 offset, quint16 *buffer)
{
	qint32 bytes = 0;
	qint32 count = 0;

	if(device == INVALID_HANDLE_VALUE)
	{
		lastError = ErrorNotInitialized;
		return bytes;
	}

	if(buffer == NULL)
	{
		lastError = ErrorInvalidParameter;
		return bytes;
	}

	quint16 message[2];
	message[0] = offset;
	message[1] = 0;

	if(!DeviceIoControl(device,IOCTL_READ_PORT2,&message[0],sizeof(quint16),&message[1],sizeof(quint16),(LPDWORD)&count,NULL))
	{
		lastError = ErrorReadWrite;
		bytes = -1;
	}
	else
	{
		lastError = NoError;
		bytes = 2;
	}

	buffer[0] = message[1];

	return bytes;
}

// ------------------------------------------------------------------
qint32 DASD_DEVICE_WIN::write_mem32(quint32 /*offset*/, quint32 /*value*/)
{
	return -1;
}
// ------------------------------------------------------------------

qint32 DASD_DEVICE_WIN::read_mem32 (quint32 /*offset*/, quint32* /*value*/)
{
	return -1;
}
// ------------------------------------------------------------------

#endif
