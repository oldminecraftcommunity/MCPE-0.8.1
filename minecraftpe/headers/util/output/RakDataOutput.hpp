#pragma once
#include <util/output/BytesDataOutput.hpp>
#include <BitStream.h>

struct RakDataOutput: BytesDataOutput
{
	RakNet::BitStream* bitStream;

	virtual ~RakDataOutput();
	virtual void writeBytes(const void*, int32_t);
};
