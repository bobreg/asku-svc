//----------------------------------------------------------------------------------------------------
//Device Driver DASD
//----------------------------------------------------------------------------------------------------
#ifndef DASD_H_INCLUDED
#define DASD_H_INCLUDED
//----------------------------------------------------------------------------------------------------
#define DASD_MODULE_VERSION "1.0"
//----------------------------------------------------------------------------------------------------
#define BOARD_DEVICE		"/dev/DASD"
#define DEVICE_MAJOR		247
#define DEVICE_MINOR		0
//----------------------------------------------------------------------------------------------------
#define DASD_REG_MASK		0x0080
#define DASD_REG_EVENT		0x0084
#define DASD_REG_CONTROL		0x0004
#define DASD_REG_STATUS		0x0008
//----------------------------------------------------------------------------------------------------
#define DASD_REG_AZ_PRL		0x0020
#define DASD_REG_PPS			0x0050
//----------------------------------------------------------------------------------------------------
#define DASD_BANK_PRL_AZ_TIME	0x3000
//----------------------------------------------------------------------------------------------------
#define DASD_INTERRUPT_GLOBAL_CONNECT_MASK	0x80000000
#define DASD_INTERRUPT_CONNECT_MASK		0x00003f00
#define DASD_INTERRUPT_GLOBAL_SYNC_MASK	0x00000080
#define DASD_INTERRUPT_SYNC_MASK		0x0000001f
//----------------------------------------------------------------------------------------------------
#define IOCTL_INITMODULE	_IOR(DEVICE_MAJOR,0,ssize_t*)
#define IOCTL_GET_REGISTERS_IRQ	_IOR(DEVICE_MAJOR,1,ssize_t*)
#define IOCTL_READ_REGISTER	_IOR(DEVICE_MAJOR,6,ssize_t*)
#define IOCTL_WRITE_REGISTER	_IOR(DEVICE_MAJOR,7,ssize_t*)
#define IOCTL_READ_BLOCK	_IOR(DEVICE_MAJOR,10,ssize_t*)
#define IOCTL_WRITE_BLOCK	_IOR(DEVICE_MAJOR,11,ssize_t*)
#define IOCTL_READ_REGISTER_64	_IOR(DEVICE_MAJOR,26,ssize_t*)
#define IOCTL_WRITE_REGISTER_64	_IOR(DEVICE_MAJOR,27,ssize_t*)
//----------------------------------------------------------------------------------------------------
#define IOCTL_IS_INT		 _IOR(DEVICE_MAJOR,12,ssize_t*)
#define IOCTL_READ_BEAM		 _IOR(DEVICE_MAJOR,13,ssize_t*)
#define IOCTL_WRITE2_BYTE_BLOCK	 _IOR(DEVICE_MAJOR,15,ssize_t*)
#define IOCTL_READ2_BYTE_BLOCK	 _IOR(DEVICE_MAJOR,16,ssize_t*)
//----------------------------------------------------------------------------------------------------
#define FL_INT_PPS		0x1
#define FL_INT_BEAM_PRL		0x2
#define FL_INT_NORD_PRL		0x4
//----------------------------------------------------------------------------------------------------
#define SPEC_PPS		0x10
#define SPEC_PRL_BEAM		0x4
#define SPEC_PRL_NORTH		0x1
//----------------------------------------------------------------------------------------------------
typedef struct _IOCTL_IS_INT
{
    unsigned short nByte;
    unsigned char *pbuffer;
}IRW_IS_INT;
//-----------------------------------------------------------------------------------------
typedef struct _IOCTL_BEAM
{
    unsigned int beam;
    unsigned int time;
}IRW_BEAM;
//----------------------------------------------------------------------------------------------------
typedef struct _IOCTL_READ_WRITE_QUERY
{
    unsigned int offset;
    unsigned int value;
}IRW_QUERY;
//----------------------------------------------------------------------------------------------------
typedef struct _IOCTL_READ_WRITE_QUERY_64
{
    unsigned long offset;
    unsigned long value;
}IRW_QUERY_64;
//----------------------------------------------------------------------------------------------------
typedef struct _IOCTL_READ_WRITE_QUERY_16
{
    unsigned short offset;
    unsigned short value;
}IRW_QUERY_16;
//----------------------------------------------------------------------------------------------------
typedef struct _IOCTL_READ_WRITE_BLOCK
{
    unsigned int offset;
    unsigned int byte_count;
    void* data;
}IRW_QUERY_BLOCK;
//----------------------------------------------------------------------------------------------------
typedef struct _IOCTL_BYTE_BLOCK
{
    unsigned int offset;
    unsigned int byte_count;
    unsigned char *pData;
}IRW_BYTE_BLOCK;
//----------------------------------------------------------------------------------------------------
typedef struct _DASD_REGISTERS
{
	unsigned int event;
	unsigned int mask;
	unsigned int control;
	unsigned int status;
	unsigned char ucLastBeamRead;
}DASD_REGISTERS;
//----------------------------------------------------------------------------------------------------

#endif
