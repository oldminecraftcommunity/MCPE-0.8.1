#pragma once
#include <util/input/BytesDataInput.hpp>
#include <BitStream.h>

struct RakDataInput: BytesDataInput
{
	RakNet::BitStream* stream;

	virtual bool_t readBytes(void*, int32_t);
	virtual int32_t numBytesLeft(void);
};
