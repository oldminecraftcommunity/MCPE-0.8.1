#pragma once
#include <_types.h>
#include <string>

struct IDataOutput{
	virtual ~IDataOutput();
	virtual void writeString(const std::string&) = 0;
	virtual void writeFloat(float) = 0;
	virtual void writeDouble(double) = 0;
	virtual void writeByte(int8_t) = 0;
	virtual void writeShort(int16_t) = 0;
	virtual void writeInt(int32_t) = 0;
	virtual void writeLongLong(int64_t) = 0;
	virtual void writeBytes(const void*, int32_t) = 0;
};
