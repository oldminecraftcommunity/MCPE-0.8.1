#pragma once
#include <util/output/BytesDataOutput.hpp>
#include <BitStream.h>

struct RakDataOutput: BytesDataOutput
{
	RakNet::BitStream* bitStream;
	RakDataOutput(RakNet::BitStream* bitStream)
		: bitStream(bitStream) {
	}
	virtual ~RakDataOutput() {
	}
	virtual void writeBytes(const void* a2, int32_t a3) {
		this->bitStream->WriteBits((const unsigned char*) (a2), a3 * 8, 1);
	}
};
