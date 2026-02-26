#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct TakeItemEntityPacket : Packet{
	int32_t target, eid;

	TakeItemEntityPacket(int32_t, int32_t);
	TakeItemEntityPacket();
	virtual ~TakeItemEntityPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
