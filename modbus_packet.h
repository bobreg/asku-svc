#ifndef MODBUS_PACKET_H
#define MODBUS_PACKET_H

#include <QVector>

// Коды операций и ошибок
// **********************

// Коды операций
#define	MB_CODE_READ_COIL_STATUS          0x01 // Чтение регистров флагов
#define	MB_CODE_READ_DISCRETE_INPUTS      0x02 // Чтение дискретных входов
#define	MB_CODE_READ_HOLDING_REGISTERS    0x03 // Чтение регистров хранения
#define	MB_CODE_READ_INPUT_REGISTERS      0x04 // Чтение регистров ввода

#define	MB_CODE_FORCE_SINGLE_COIL         0x05 // Запись значения одного флага
#define	MB_CODE_PRESET_SINGLE_REGISTER    0x06 // Запись значения в регистр хранения

#define	MB_CODE_FORCE_MULTIPLE_COILS      0x0F // Запись значений нескольких флагов
#define	MB_CODE_PRESET_MULTIPLE_REGISTERS 0x10 // Запись значений в несколько регистров хранения


#define	MB_CODE_ERROR_MASK                0x80 // Ответ при наличии ошибки

#define	MB_CODE_ERROR_READ_COIL_STATUS         (MB_CODE_ERROR_MASK | MB_CODE_READ_COIL_STATUS)
#define	MB_CODE_ERRORREAD_DISCRETE_INPUTS      (MB_CODE_ERROR_MASK | MB_CODE_READ_DISCRETE_INPUTS)
#define	MB_CODE_ERRORREAD_HOLDING_REGISTERS    (MB_CODE_ERROR_MASK | MB_CODE_READ_HOLDING_REGISTERS)
#define	MB_CODE_ERRORREAD_INPUT_REGISTERS      (MB_CODE_ERROR_MASK | MB_CODE_READ_INPUT_REGISTERS)
#define	MB_CODE_ERRORFORCE_SINGLE_COIL         (MB_CODE_ERROR_MASK | MB_CODE_FORCE_SINGLE_COIL)
#define	MB_CODE_ERRORPRESET_SINGLE_REGISTER    (MB_CODE_ERROR_MASK | MB_CODE_PRESET_SINGLE_REGISTER)
#define	MB_CODE_ERRORFORCE_MULTIPLE_COILS      (MB_CODE_ERROR_MASK | MB_CODE_FORCE_MULTIPLE_COILS)
#define	MB_CODE_ERRORPRESET_MULTIPLE_REGISTERS (MB_CODE_ERROR_MASK | MB_CODE_PRESET_MULTIPLE_REGISTERS)


// Коды ошибок
#define	MB_ERR_OPERATION    0x01 // Ошибка кода операции
#define	MB_ERR_REGISTER     0x02 // Ошибка номера регистра
#define	MB_ERR_DATAARRANGE  0x03 // Ошибка размещения данных


// Класс универсального пакета ВЕСПЕРа
// ***********************************

#define MB_MIN_LEN    5
#define MB_MAX_LEN    255

class ModbusPacket
{
	unsigned char f_data[MB_MAX_LEN];
	unsigned char f_len;

public:
	enum Type { RequestCoil = 1, RequestDiscrete = 2, RequestHolding = 3, RequestRegisters = 4, 
				ResponseCoil = 5, ResponseDiscrete = 6, ResponseHolding = 7, ResponseRegisters = 8, 
				CommandSingleCoil = 9, CommandSingleRegister = 10, CommandMultiCoils = 11, CommandMultiRegisters = 12, 
				RecieptSingleCoil = 13, RecieptSingleRegister = 14, RecieptMultiCoils = 15, RecieptMultiRegisters = 16, 
				Error = 17 };
	enum PError { BadLength = 1, BadCS = 2, BadCode = 4, BadData = 8, BadDevice = 16 };

	ModbusPacket();
	ModbusPacket(const ModbusPacket &other);
	ModbusPacket(Type type, unsigned char device);
	ModbusPacket(const unsigned char* data, unsigned char length);
	ModbusPacket(QByteArray & data);

	// Тип пакета и его целостность
	unsigned char type()      const;
	unsigned char isInvalid() const;

	// Доступ к данным
	unsigned char length() const;
	unsigned char& operator[](unsigned char i);
	unsigned char& at        (unsigned char i);
	QByteArray toByteArray() const;

	unsigned char  device  () const;
	unsigned char  code    () const;
	unsigned char  error   () const;
	unsigned short address () const;
	unsigned short count   () const;
	unsigned short bytes   () const;
	unsigned short cs      () const;
	unsigned short value(unsigned char i = 0) const;
	unsigned char  valueLength() const;

	// Операции с пакетом(-ами)
	void setDevice   (unsigned char device  );
	void setCode     (unsigned char code    );
	void setError    (unsigned char error   );
	void setAddress  (unsigned short address);
	void setCount    (unsigned short count  );
	void setValue    (unsigned char i, unsigned short value);
	void setValueBit (unsigned char i, unsigned char bit, bool value);
	void calcCS();

	// Формирование пакетов
	void reform      (Type type, unsigned char device);
	void refRead     (Type type, unsigned char device, unsigned short address, unsigned short count);
	void refWrite    (Type type, unsigned char device, unsigned short address, unsigned short value);
	void refWrite    (Type type, unsigned char device, unsigned short address, unsigned short* values, unsigned char count);
	void refError    (Type type, unsigned char device, unsigned char error);
	void refResponce (Type type, unsigned char device, unsigned short address, unsigned short *values, unsigned short count);
	void refResponce (Type type, unsigned char device, unsigned short address, bool *values, unsigned short count);
	void refResponce (Type type, unsigned char device, unsigned short address, unsigned short count);

	void getResponce (Type type, bool *values, unsigned short count) const;
	void getResponce (Type type, unsigned short *values, unsigned short count) const;

	void copy(const ModbusPacket &other);
	void copy(const unsigned char* data, unsigned char length);
	void copy(QVector<unsigned char>* data, unsigned char length);

	static unsigned short checkSum (const unsigned char* data, unsigned char length);
	static unsigned char  type     (const unsigned char* data, unsigned char length);
	static unsigned char  isInvalid(const unsigned char* data, unsigned char length);

	static unsigned char lo(unsigned short word);
	static unsigned char hi(unsigned short word);
	static unsigned short word(unsigned char lo, unsigned char hi);
	static unsigned short swap(unsigned short word);

	static int processBuffer(unsigned char* buffer, unsigned int &length, ModbusPacket* p, unsigned int &count);
	static int processBuffer(QByteArray *buffer, QList<ModbusPacket>* p);
};


#endif // MODBUS_PACKET_H
