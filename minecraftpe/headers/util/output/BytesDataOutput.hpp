#pragma once
#include <util/output/IDataOutput.hpp>

struct BytesDataOutput: IDataOutput
{
	virtual ~BytesDataOutput();
	virtual void writeString(const std::string&);
	virtual void writeFloat(float);
	virtual void writeDouble(double);
	virtual void writeByte(int8_t);
	virtual void writeShort(int16_t);
	virtual void writeInt(int32_t);
	virtual void writeLongLong(int64_t);
	virtual void writeBytes(const void*, int32_t) = 0;
};
