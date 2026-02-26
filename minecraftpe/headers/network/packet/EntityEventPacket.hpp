#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct EntityEventPacket : Packet{
	int32_t eid;
	uint8_t event;
	byte align1, align2, align3;
	EntityEventPacket();
	EntityEventPacket(int32_t eid, uint8_t event);

	virtual ~EntityEventPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
