#include <QByteArray>
#include "modbus_packet.h"

// Таблицы значений для вычисления CRC-16
static unsigned char CRC16H[256] = {
					0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
					0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
					0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
					0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
					0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
					0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
					0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
					0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
					0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
					0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
					0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
					0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
					0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
					0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
					0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
					0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
					0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
					0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
					0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
					0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
					0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
					0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
					0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
					0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
					0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
					0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

static unsigned char CRC16L[256] = {
					0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 
					0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 
					0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 
					0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 
					0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 
					0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 
					0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 
					0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 
					0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 
					0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 
					0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 
					0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 
					0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 
					0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 
					0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 
					0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 
					0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 
					0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 
					0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 
					0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 
					0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 
					0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 
					0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 
					0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 
					0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 
					0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};


// Класс универсального пакета ВЕСПЕРа
// ***********************************

ModbusPacket::ModbusPacket()
{
	for (unsigned char i = 0; i < MB_MAX_LEN; i++)
		f_data[i] = 0;
	f_len = MB_MAX_LEN;
}

ModbusPacket::ModbusPacket(const ModbusPacket &other)
{
	copy(other);
}

ModbusPacket::ModbusPacket(Type type, unsigned char device)
{
	reform(type, device);
}

ModbusPacket::ModbusPacket(const unsigned char* data, unsigned char length)
{
	copy(data, length);
}

ModbusPacket::ModbusPacket(QByteArray & data)
{
	copy((unsigned char*)data.data(), data.length());
}


unsigned char ModbusPacket::type() const
{
	return type((const unsigned char*)&f_data, f_len);
}

unsigned char ModbusPacket::isInvalid() const
{
	return isInvalid((const unsigned char*)&f_data, f_len);
}


unsigned char ModbusPacket::length() const
{
	return f_len;
}

unsigned char& ModbusPacket::operator[](unsigned char i)
{
	if (i > f_len - 1)
		i = f_len - 1;
	return f_data[i];
}

unsigned char& ModbusPacket::at(unsigned char i)
{
	if (i > f_len - 1)
		i = f_len - 1;
	return f_data[i];
}


unsigned char ModbusPacket::device() const
{
	return f_data[0];
}

unsigned char ModbusPacket::code() const
{
	return f_data[1];
}

unsigned char ModbusPacket::error() const
{
	unsigned char result = 0xFF;
	if (type() == Error)
		result = f_data[2];
	return result;
}

unsigned short ModbusPacket::address() const
{
	unsigned short result = 0xFFFF;
	unsigned char t = type();
	if ((t >= RequestCoil) && (t <= RecieptMultiRegisters))
		result = word(f_data[3], f_data[2]);
	return result;
}

unsigned short ModbusPacket::count() const
{
	unsigned short result = 0xFFFF;
	unsigned char t = type();
	if ((t >= RequestCoil) && (t <= RecieptMultiRegisters))
		result = word(f_data[5], f_data[4]);
	return result;
}

unsigned short ModbusPacket::bytes() const
{
	unsigned short result = 0xFFFF;
	unsigned char t = type();
	if(t == ResponseHolding || t == ResponseRegisters)
		result = word(f_data[2], 0);
	return result;
}

unsigned short ModbusPacket::cs() const
{
	return word(f_data[f_len - 1], f_data[f_len - 2]);
}

unsigned short ModbusPacket::value(unsigned char i) const
{
	unsigned short result = 0xFFFF;
	unsigned char t = type();
	if (t >= ResponseCoil && t <= ResponseRegisters)
	{
		result = word(f_data[4 + 2 * i], f_data[3 + 2 * i]);
	}
	else if (t >= CommandSingleCoil && t <= CommandMultiRegisters)
	{
		result = word(f_data[8 + 2 * i], f_data[7 + 2 * i]);
	}
	return result;
}

unsigned char ModbusPacket::valueLength() const
{
	unsigned char result = 0;
	unsigned char t = type();
	if (t >= ResponseCoil && t <= ResponseRegisters)
	{
		result = (unsigned char)((f_len - 5) / 2);
	}
	else if (t >= CommandSingleCoil && t <= CommandMultiRegisters)
	{
		result = (unsigned char)((f_len - 9) / 2);
	}
	return result;
}


void ModbusPacket::setDevice(unsigned char device)
{
	f_data[0] = device;
	calcCS();
}

void ModbusPacket::setCode(unsigned char code)
{
	if ((type() == Error) && (code & MB_CODE_ERROR_MASK))
	{
		f_data[1] = code;
		calcCS();
	}
}

void ModbusPacket::setError(unsigned char error)
{
	if (type() == Error)
	{
		f_data[2] = error;
		calcCS();
	}
}

void ModbusPacket::setAddress(unsigned short address)
{
	unsigned char t = type();
	if ((t >= RequestCoil && t <= RequestRegisters) || (t >= CommandSingleCoil && t <= RecieptMultiRegisters))
	{
		f_data[2] = hi(address);
		f_data[3] = lo(address);
		calcCS();
	}
}

void ModbusPacket::setCount(unsigned short count)
{
	unsigned char t = type();
	if ((t >= RequestCoil && t <= RequestRegisters) || (t >= CommandSingleCoil && t <= RecieptMultiRegisters))
	{
		f_data[4] = hi(count);
		f_data[5] = lo(count);
		if (t >= CommandSingleCoil && t <= CommandMultiRegisters)
		{
			f_len = 9 + 2 * count;
			f_data[6] = 2 * count;
		}
		calcCS();
	}
	else if (t >= ResponseCoil && t <= ResponseRegisters)
	{
		f_len = 5 + 2 * count;
		f_data[2] = 2 * count;
		calcCS();
	}
}

void ModbusPacket::setValue(unsigned char i, unsigned short value)
{
	unsigned char t = type();
	if ((t >= ResponseCoil && t <= ResponseRegisters) && (i < (unsigned char)((f_len - 5) / 2)))
	{
		f_data[3 + 2 * i] = hi(value);
		f_data[4 + 2 * i] = lo(value);
		calcCS();
	}
	else if ((t >= CommandSingleCoil && t <= CommandMultiRegisters) && (i < (unsigned char)((f_len - 9) / 2)))
	{
		f_data[7 + 2 * i] = hi(value);
		f_data[8 + 2 * i] = lo(value);
		calcCS();
	}
}

void ModbusPacket::setValueBit(unsigned char i, unsigned char bit, bool value)
{
	unsigned char t = type();
	if ((t >= ResponseCoil && t <= ResponseRegisters) && (i < (unsigned char)((f_len - 5) / 2)) && (bit < 16))
	{
		if (bit < 8)
		{
			if (value)
			{
				f_data[4 + 2 * i] |=  (0x01 << bit);
			}
			else
			{
				f_data[4 + 2 * i] &= ~(0x01 << bit);
			}
		}
		else
		{
			if (value)
			{
				f_data[3 + 2 * i] |=  (0x01 << (bit - 8));
			}
			else
			{
				f_data[3 + 2 * i] &= ~(0x01 << (bit - 8));
			}
		}
		calcCS();
	}
	else if ((t >= CommandSingleCoil && t <= CommandMultiRegisters) && (i < (unsigned char)((f_len - 9) / 2)) && (bit < 16))
	{
		if (bit < 8)
		{
			if (value)
			{
				f_data[8 + 2 * i] |=  (0x01 << bit);
			}
			else
			{
				f_data[8 + 2 * i] &= ~(0x01 << bit);
			}
		}
		else
		{
			if (value)
			{
				f_data[7 + 2 * i] |=  (0x01 << (bit - 8));
			}
			else
			{
				f_data[7 + 2 * i] &= ~(0x01 << (bit - 8));
			}
		}
		calcCS();
	}
}

void ModbusPacket::calcCS()
{
	if (f_len > 1)
	{
		unsigned short cksum = checkSum((const unsigned char*)&f_data, f_len - 2);
		f_data[f_len - 2] = hi(cksum);
		f_data[f_len - 1] = lo(cksum);
	}
}


void ModbusPacket::reform(Type type, unsigned char device)
{
	for (unsigned char i = 0; i < MB_MAX_LEN; i++)
		f_data[i] = 0;

	f_data[0] = device;
	switch (type)
	{
		case RequestCoil:
			f_len = 8;
			f_data[1] = MB_CODE_READ_COIL_STATUS;
			f_data[5] = 0x01;
			break;
		case RequestDiscrete:
			f_len = 8;
			f_data[1] = MB_CODE_READ_DISCRETE_INPUTS;
			f_data[5] = 0x01;
			break;
		case RequestHolding:
			f_len = 8;
			f_data[1] = MB_CODE_READ_HOLDING_REGISTERS;
			f_data[5] = 0x01;
			break;
		case RequestRegisters:
			f_len = 8;
			f_data[1] = MB_CODE_READ_INPUT_REGISTERS;
			f_data[5] = 0x01;
			break;
		case ResponseCoil:
			f_len = 7;
			f_data[1] = MB_CODE_READ_COIL_STATUS;
			f_data[2] = 0x02;
			break;
		case ResponseDiscrete:
			f_len = 7;
			f_data[1] = MB_CODE_READ_DISCRETE_INPUTS;
			f_data[2] = 0x02;
			break;
		case ResponseHolding:
			f_len = 7;
			f_data[1] = MB_CODE_READ_HOLDING_REGISTERS;
			f_data[2] = 0x02;
			break;
		case ResponseRegisters:
			f_len = 7;
			f_data[1] = MB_CODE_READ_INPUT_REGISTERS;
			f_data[2] = 0x02;
			break;
		case CommandSingleCoil:
			f_len = 11;
			f_data[1] = MB_CODE_FORCE_SINGLE_COIL;
			f_data[5] = 0x01;
			f_data[6] = 0x02;
			break;
		case CommandSingleRegister:
			f_len = 11;
			f_data[1] = MB_CODE_PRESET_SINGLE_REGISTER;
			f_data[5] = 0x01;
			f_data[6] = 0x02;
			break;
		case CommandMultiCoils:
			f_len = 11;
			f_data[1] = MB_CODE_FORCE_MULTIPLE_COILS;
			f_data[5] = 0x01;
			f_data[6] = 0x02;
			break;
		case CommandMultiRegisters:
			f_len = 11;
			f_data[1] = MB_CODE_PRESET_MULTIPLE_REGISTERS;
			f_data[5] = 0x01;
			f_data[6] = 0x02;
			break;
		case RecieptSingleCoil:
			f_len = 8;
			f_data[1] = MB_CODE_FORCE_SINGLE_COIL;
			f_data[5] = 0x01;
			break;
		case RecieptSingleRegister:
			f_len = 8;
			f_data[1] = MB_CODE_PRESET_SINGLE_REGISTER;
			f_data[5] = 0x01;
			break;
		case RecieptMultiCoils:
			f_len = 8;
			f_data[1] = MB_CODE_FORCE_MULTIPLE_COILS;
			f_data[5] = 0x01;
			break;
		case RecieptMultiRegisters:
			f_len = 8;
			f_data[1] = MB_CODE_PRESET_MULTIPLE_REGISTERS;
			f_data[5] = 0x01;
			break;
		case Error:
			f_len = 5;
			f_data[1] = MB_CODE_ERROR_MASK;
			f_data[2] = MB_ERR_OPERATION;
	}
	calcCS();
}

void ModbusPacket::refError (Type type, unsigned char device, unsigned char error)
{
	reform(Error, device);
	switch(type)
	{
		case RequestCoil:
			f_data[1] = MB_CODE_READ_COIL_STATUS;
			break;
		case RequestDiscrete:
			f_data[1] = MB_CODE_READ_DISCRETE_INPUTS;
			break;
		case RequestHolding:
			f_data[1] = MB_CODE_READ_HOLDING_REGISTERS;
			break;
		case RequestRegisters:
			f_data[1] = MB_CODE_READ_INPUT_REGISTERS;
			break;
		case CommandSingleCoil:
			f_data[1] = MB_CODE_FORCE_SINGLE_COIL;
			break;
		case CommandSingleRegister:
			f_data[1] = MB_CODE_PRESET_SINGLE_REGISTER;
			break;
		case CommandMultiCoils:
			f_data[1] = MB_CODE_FORCE_MULTIPLE_COILS;
			break;
		case CommandMultiRegisters:
			f_data[1] = MB_CODE_PRESET_MULTIPLE_REGISTERS;
			break;
		default:
			f_data[1] = 0;
	}
	f_data[1] |= MB_CODE_ERROR_MASK;
	f_data[2] = error;
	calcCS();
}

void ModbusPacket::refRead (Type type, unsigned char device, unsigned short address, unsigned short count)
{
	if(type >= RequestCoil && type <= RequestRegisters)
	{
		reform(type, device);
		f_data[2] = hi(address);
		f_data[3] = lo(address);
		f_data[4] = hi(count);
		f_data[5] = lo(count);
		calcCS();
	}
}

void ModbusPacket::refWrite(Type type, unsigned char device, unsigned short address, unsigned short value)
{
	if(type >= CommandSingleCoil && type <= CommandSingleRegister)
	{
		reform(type, device);
		f_data[2] = hi(address);
		f_data[3] = lo(address);
		f_data[4] = 0x00;
		f_data[5] = 0x01;
		f_data[6] = 0x02;
		f_data[7] = hi(value);
		f_data[8] = lo(value);
		calcCS();
	}
}

void ModbusPacket::refWrite(Type type, unsigned char device, unsigned short address, unsigned short* values, unsigned char count)
{
	if (values && count && type >= CommandMultiCoils && type <= CommandMultiRegisters)
	{
		reform(type, device);
		f_len = 9 + 2 * count;
		f_data[2] = hi(address);
		f_data[3] = lo(address);
		f_data[4] = 0x00;
		f_data[5] = count;
		f_data[6] = 2 * count;
		for (unsigned char i = 0; i < count; i++)
		{
			f_data[7 + 2 * i] = hi(values[i]);
			f_data[8 + 2 * i] = lo(values[i]);
		}
		calcCS();
	}
}

void ModbusPacket::refResponce (Type type, unsigned char device, unsigned short /*address*/, unsigned short *values, unsigned short count)
{
	if(values && (type == ResponseHolding || type == ResponseRegisters) && ((2 * count + 5) <= MB_MAX_LEN))
	{
		reform(type, device);
		f_len = 5 + 2 * count;
		f_data[2] = (unsigned char)(2 * count);
		for (unsigned char i = 0; i < count; i++)
		{
			f_data[3 + 2 * i] = hi(values[i]);
			f_data[4 + 2 * i] = lo(values[i]);
		}
		calcCS();
	}
}

void ModbusPacket::refResponce (Type type, unsigned char device, unsigned short /*address*/, bool *values, unsigned short count)
{
	if(values && (type == ResponseCoil || type == ResponseDiscrete))
	{
		unsigned short bytes = 0;
		unsigned short bits = 0;

		reform(type, device);

		while(1)
		{
			for(unsigned char bit = 0; bit < 8; bit++)
			{
				if(bits < count)
				{
					if (values[bits])
					{
						f_data[3 + bytes] |=  (0x01 << bit);
					}
					else
					{
						f_data[3 + bytes] &= ~(0x01 << bit);
					}
				}
				else
				{
					f_data[3 + bytes] &= ~(0x01 << bit);
				}
				bits++;
			}
			bytes++;
			if((bytes >= (MB_MAX_LEN - 5)) || (bits >= count))
				break;
		}
		f_data[2] = (unsigned char)(bytes);
		f_len = 5 + bytes;
		calcCS();
	}
}

void ModbusPacket::refResponce (Type type, unsigned char device, unsigned short address, unsigned short count)
{
	if(type == RecieptMultiRegisters || type == RecieptMultiCoils)
	{
		reform(type, device);
		f_len = 8;
		f_data[2] = hi(address);
		f_data[3] = lo(address);
		f_data[4] = 0x00;
		f_data[5] = count;
		calcCS();
	}
}

void ModbusPacket::getResponce (Type type, bool *values, unsigned short count)  const
{
	if(values && (type == ResponseCoil || type == ResponseDiscrete))
	{
		unsigned short bytes = 0;
		unsigned short bits = 0;

		while(1)
		{
			for(unsigned char bit = 0; bit < 8; bit++)
			{
				if(bits < count)
				{
					if(f_data[3 + bytes] & (0x01 << bit))
						values[bits] = true;
					else
						values[bits] = false;
				}
				bits++;
			}
			bytes++;
			if(bytes >= f_data[2] || bits >= count)
				break;
		}
	}
}

void ModbusPacket::getResponce (Type type, unsigned short *values, unsigned short count)  const
{
	if(values && (type == ResponseHolding || type == ResponseRegisters))
	{
		for(unsigned char i = 0; i < count; i++)
		{
			if(2*i < f_data[2])
				values[i] = word(f_data[4 + 2 * i],f_data[3 + 2 * i]);
		}
	}
}

void ModbusPacket::copy(const ModbusPacket &other)
{
	*this = other;
}

void ModbusPacket::copy(const unsigned char* data, unsigned char length)
{
	if (data && length/* && (length <= MB_MAX_LEN)*/)
	{
		for (unsigned char i = 0; i < length; i++)
			f_data[i] = data[i];
		f_len = length;
	}
}

void ModbusPacket::copy(QVector<unsigned char> *data, unsigned char length)
{
	if (data && data->count() >= length && length/* && (length <= MB_MAX_LEN)*/)
	{
		QVector<unsigned char>::iterator it;
		it = data->begin();
		for (unsigned char i = 0; i < length; i++)
			f_data[i] = *it++;
		f_len = length;
	}
}

unsigned short ModbusPacket::checkSum(const unsigned char* data, unsigned char length)
{
	unsigned short cksum = 0xFFFF;
	if (data && length)
	{
		unsigned char i;
		while (length--)
		{
			i = hi(cksum) ^ *data++;
			cksum = word(CRC16L[i], (lo(cksum) ^ CRC16H[i]));
		}
	}
	return cksum;
}

unsigned char ModbusPacket::type(const unsigned char* data, unsigned char length)
{
	unsigned char result = 0;

	if ((length == 5) && (data[1] & MB_CODE_ERROR_MASK))
	{
		result = Error;
	}
	else if (length == 8 /*&& ((length - 5) != data[2])*/)
	{
		switch(data[1])
		{
			case MB_CODE_READ_COIL_STATUS:			result = RequestCoil;		break;
			case MB_CODE_READ_DISCRETE_INPUTS:		result = RequestDiscrete;	break;
			case MB_CODE_READ_HOLDING_REGISTERS:	result = RequestHolding;	break;
			case MB_CODE_READ_INPUT_REGISTERS:		result = RequestRegisters;	break;

			case MB_CODE_FORCE_SINGLE_COIL:			result = RecieptSingleCoil;		break;
			case MB_CODE_PRESET_SINGLE_REGISTER:	result = RecieptSingleRegister;	break;
			case MB_CODE_FORCE_MULTIPLE_COILS:		result = RecieptMultiCoils;		break;
			case MB_CODE_PRESET_MULTIPLE_REGISTERS:	result = RecieptMultiRegisters;	break;
		}
	}
	else if ((length >= 6) && (length <= (MB_MAX_LEN-5)) && ((length - 5) == data[2]))
	{
		switch(data[1])
		{
			case MB_CODE_READ_COIL_STATUS:			result = ResponseCoil;		break;
			case MB_CODE_READ_DISCRETE_INPUTS:		result = ResponseDiscrete;	break;
			case MB_CODE_READ_HOLDING_REGISTERS:	result = ResponseHolding;	break;
			case MB_CODE_READ_INPUT_REGISTERS:		result = ResponseRegisters;	break;
		}
	}
	else if ((length >= 7) && (length <= MB_MAX_LEN-5) && ((length - 5) % 2 == 0))
	{
		switch(data[1])
		{
			case MB_CODE_FORCE_SINGLE_COIL:			result = CommandSingleCoil;		break;
			case MB_CODE_PRESET_SINGLE_REGISTER:	result = CommandSingleRegister;	break;
			case MB_CODE_FORCE_MULTIPLE_COILS:		result = CommandMultiCoils;		break;
			case MB_CODE_PRESET_MULTIPLE_REGISTERS:	result = CommandMultiRegisters;	break;
		}
	}
	return result;
}

unsigned char ModbusPacket::isInvalid(const unsigned char* data, unsigned char length)
{
	unsigned char result = 0;
	if (data[0] > 31)
	{
		result |= BadDevice;
	}
	if ((length < MB_MIN_LEN)/* || (length > MB_MAX_LEN)*/)
	{
		result |= BadLength;
	}
	else if (checkSum(data, length - 2) != word(data[length - 1], data[length - 2]))
	{
		result |= BadCS;
	}
	else switch (data[1])
	{
		case MB_CODE_READ_COIL_STATUS:
		case MB_CODE_READ_DISCRETE_INPUTS:
			if (length != 8)
			{
				if ((length < 6) || (length > (MB_MAX_LEN - 4)) || (length != data[2] + 5))
				{
					result |= BadLength;
				}
			}
			break;
		case MB_CODE_READ_HOLDING_REGISTERS:
		case MB_CODE_READ_INPUT_REGISTERS:
			if (length != 8)
			{
				if ((length < 7) || (length > (MB_MAX_LEN - 4)) || ((length - 5) % 2) || (length != data[2] + 5))
				{
					result |= BadLength;
				}
			}
			break;
		case MB_CODE_FORCE_SINGLE_COIL:
		case MB_CODE_PRESET_SINGLE_REGISTER:
		case MB_CODE_FORCE_MULTIPLE_COILS:
		case MB_CODE_PRESET_MULTIPLE_REGISTERS:
			if (length != 8)
			{
				if ((length < 11) || ((length - 9) % 2) || (length != data[6] + 9))
				{
					result |= BadLength;
				}
			}
			break;
		case MB_CODE_ERROR_READ_COIL_STATUS:
		case MB_CODE_ERRORREAD_DISCRETE_INPUTS:
		case MB_CODE_ERRORREAD_HOLDING_REGISTERS:
		case MB_CODE_ERRORREAD_INPUT_REGISTERS:
		case MB_CODE_ERRORFORCE_SINGLE_COIL:
		case MB_CODE_ERRORPRESET_SINGLE_REGISTER:
		case MB_CODE_ERRORFORCE_MULTIPLE_COILS:
		case MB_CODE_ERRORPRESET_MULTIPLE_REGISTERS:
			if (length != 5)
			{
				result |= BadLength;
			}
			break;
		default:
			result |= BadCode;
	}
	return result;
}


unsigned char ModbusPacket::lo(unsigned short word)
{
	return (unsigned char)word;
}

unsigned char ModbusPacket::hi(unsigned short word)
{
	return (unsigned char)(word >> 8);
}

unsigned short ModbusPacket::word(unsigned char lo, unsigned char hi)
{
	return (((unsigned short)hi << 8) | ((unsigned short)lo));
}

unsigned short ModbusPacket::swap(unsigned short word)
{
	unsigned char hi = (unsigned char)word;
	return (((unsigned short)hi << 8) | (word >> 8));
}

QByteArray ModbusPacket::toByteArray() const
{
	return QByteArray((const char*)f_data, f_len);
}


// Функция разбора буфера
// Описание: функция производит поиск пакетов в буфере и копирует найденные пакеты в массив (если его
//           длина задана и не превышена, или не задана). Неразобранная часть буфера (если таковая
//           имеется), помещается в начало буфера. Функция возвращает количество некорректных байт,
//           найденных в буфере.
// Входные параметры:  buffer - указатель на буфер (массив байт), который необходимо разобрать,
//                     length - длина буфера в байтах,
//                     p      - указатель на массив пакетов, куда следует помещать найденые пакеты,
//                     count  - максимальное кол-во пакетов в массиве (если = 0 - не ограничено)
// Выходные параметры: buffer - указатель на буфер после разбора,
//                     length - длина буфера после разбора (= 0, если весь буфер разобран),
//                     p      - указатель на массив найденных пакетов,
//                     count  - кол-во найденных в буфере пакетов
// Результат: кол-во некорректных байт (т.е. не являющихся частью пакета), найденных в буфере
int ModbusPacket::processBuffer(unsigned char* buffer, unsigned int &length, ModbusPacket* p, unsigned int &count)
{
	unsigned int max = count;             // Максимальная длина массива пакетов
	count = 0;
	if (!buffer || !p)
		return -1;
	if (length < MB_MIN_LEN)
		return  0;

	int bad =  0;                         // Кол-во некорректных байт (результат)
	int pos = -1;                         // Начало некорректных данных
	unsigned int start = 0;               // Начало пакета
	unsigned int end   = MB_MIN_LEN - 1; // Конец  пакета
	unsigned int i;

	bool exec = true;
	while (exec)
	{
		// Пока конец пакета в границах буфера, и длина пакета не превышает максимальную,
		// и пакет некорректен - сдвигать конец пакета на одну позицию к концу буфера
		while ((end < length - 1) && ((end - start) < MB_MAX_LEN - 1) && (ModbusPacket::isInvalid(buffer + start, end - start + 1)))
		{
			end++;
		}
		// Если пакет корректный
		if (!ModbusPacket::isInvalid(buffer + start, end - start + 1))
		{
			// Если до пакета был мусор
			if (pos >= 0)
			{
				bad += start - pos;
				pos = -1;
			}
			// Если не превышена длина массива пакетов
			if (!max || ((max > 0) && (count < max)))
			{
				p[count].copy(buffer + start, end - start + 1);
				count++;
				start = end + 1;
				end = start + MB_MIN_LEN - 1;
				if(end >= length)
					pos  = start;
			}
			// Иначе выйти из цикла
			else
			{
				pos  = start;
				exec = false;
			}
		}
		else // т.е. if ( ((end - start) == MB_MAX_LEN - 1) || (end == length - 1) )
		{
			// Если достигнута максимальная длина пакета или конец буфера -
			// продолжить поиск со следующего байта
			if (pos < 0)
				pos = (int)start;
			start++;
			end = start + MB_MIN_LEN - 1;
		}
		// Если в неразобранной части буфера не умещается пакет минимальной длины - выйти
		if (exec)
			exec = (start + MB_MIN_LEN - 1 < length);
	} // while (exec)

	// Если остались неразобранные данные - переместить в начало буфера
	if (pos >= 0)
	{
		if (length - pos >= MB_MAX_LEN)
		{
			bad += length - pos - MB_MAX_LEN + 1;
			pos = length - MB_MAX_LEN + 1;
		}
		for (i = 0; i < (length - pos); i++)
			buffer[i] = buffer[pos + i];
		length -= pos;
	}
	else
	{
		length = 0;
	}
	return bad;
}


int ModbusPacket::processBuffer(QByteArray *buffer, QList<ModbusPacket>* p)
{
	if (!buffer || !p)
		return -1;

	if (buffer->size() < MB_MIN_LEN)
		return  0;

	unsigned char *data = (unsigned char*)buffer->data();
	unsigned int length = buffer->length();

	int bad =  0;                         // Кол-во некорректных байт (результат)
	int pos = -1;                         // Начало некорректных данных
	unsigned int start = 0;               // Начало пакета
	unsigned int end   = MB_MIN_LEN - 1;  // Конец  пакета
//	unsigned int i;

	bool exec = true;
	while (exec)
	{
		// Пока конец пакета в границах буфера, и длина пакета не превышает максимальную,
		// и пакет некорректен - сдвигать конец пакета на одну позицию к концу буфера
		while ((end < length - 1) && ((end - start) < MB_MAX_LEN - 1) && (ModbusPacket::isInvalid(data + start, end - start + 1)))
		{
			end++;
		}
		// Если пакет корректный
		if (!ModbusPacket::isInvalid(data + start, end - start + 1))
		{
			// Если до пакета был мусор
			if (pos >= 0)
			{
				bad += start - pos;
				pos = -1;
			}

			p->append(ModbusPacket(data + start, end - start + 1));
//			p[count].copy(data + start, end - start + 1);
//			count++;
			start = end + 1;
			end = start + MB_MIN_LEN - 1;

			if(end >= length)
				pos  = start;
		}
		else // т.е. if ( ((end - start) == MB_MAX_LEN - 1) || (end == length - 1) )
		{
			// Если достигнута максимальная длина пакета или конец буфера -
			// продолжить поиск со следующего байта
			if (pos < 0)
				pos = (int)start;
			start++;
			end = start + MB_MIN_LEN - 1;
		}
		// Если в неразобранной части буфера не умещается пакет минимальной длины - выйти
		if (exec)
			exec = (start + MB_MIN_LEN - 1 < length);
	} // while (exec)

	// Если остались неразобранные данные - переместить в начало буфера
	if (pos >= 0)
	{
		if (length - pos >= MB_MAX_LEN)
		{
			bad += length - pos - MB_MAX_LEN + 1;
			pos = length - MB_MAX_LEN + 1;
		}
//		for (i = 0; i < (length - pos); i++)
//			buffer[i] = buffer[pos + i];
		buffer->remove(0, pos);
		length -= pos;
	}
	else
	{
		length = 0;
	}
	return bad;
}
