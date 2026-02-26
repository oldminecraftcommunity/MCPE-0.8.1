#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct RemoveBlockPacket : Packet{
	int32_t eid;
	int32_t x, z;
	uint8_t y;
	int8_t field_19, field_1A, field_1B;
	RemoveBlockPacket();
	RemoveBlockPacket(int32_t eid, int32_t x, int32_t y, int32_t z);
	virtual ~RemoveBlockPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
