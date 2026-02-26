#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct RemoveEntityPacket : Packet{
	int32_t eid;
	RemoveEntityPacket(int32_t eid);
	RemoveEntityPacket();
	virtual ~RemoveEntityPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
