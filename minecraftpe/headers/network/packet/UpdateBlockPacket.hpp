#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct UpdateBlockPacket : Packet{
	int32_t x, z;
	uint8_t y;
	uint8_t id, meta;
	UpdateBlockPacket();
	UpdateBlockPacket(int32_t x, int32_t y, int32_t z, int32_t id, int32_t meta);

	virtual ~UpdateBlockPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
