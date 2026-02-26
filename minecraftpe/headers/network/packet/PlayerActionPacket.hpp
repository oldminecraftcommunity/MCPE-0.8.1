#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct PlayerActionPacket : Packet{
	int32_t x, y, z;
	int32_t face, action, eid;
	PlayerActionPacket();
	PlayerActionPacket(int32_t eid, int32_t x, int32_t y, int32_t z, int32_t face, int32_t action);

	virtual ~PlayerActionPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
