#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct RequestChunkPacket : Packet{
	int32_t x, z;
	RequestChunkPacket();
	RequestChunkPacket(int32_t x, int32_t z);

	virtual ~RequestChunkPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
