#pragma once
#include <util/input/IDataInput.hpp>

struct BytesDataInput : IDataInput{
	virtual ~BytesDataInput();
	virtual std::string readString(void);
	virtual float readFloat(void) ;
	virtual double readDouble(void);
	virtual int8_t readByte(void);
	virtual int16_t readShort(void);
	virtual int32_t readInt(void);
	virtual int64_t readLongLong(void);
	virtual bool_t readBytes(void*, int32_t) = 0;
	virtual int32_t numBytesLeft(void) = 0;
};
