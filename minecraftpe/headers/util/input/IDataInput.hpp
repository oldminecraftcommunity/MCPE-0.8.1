#pragma once
#include <_types.h>
#include <string>
struct IDataInput{
	bool_t hasBytesLeft(int32_t a2);

	virtual ~IDataInput();
	virtual std::string readString(void) = 0;
	virtual float readFloat(void) = 0;
	virtual double readDouble(void) = 0;
	virtual int8_t readByte(void) = 0;
	virtual int16_t readShort(void) = 0;
	virtual int32_t readInt(void) = 0;
	virtual int64_t readLongLong(void) = 0;
	virtual bool_t readBytes(void*, int32_t) = 0;
	virtual int32_t numBytesLeft(void) = 0;
};
