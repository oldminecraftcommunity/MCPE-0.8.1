#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct AnimatePacket : Packet{
	int32_t eid;
	int8_t action;
	char align1, align2, align3;

	AnimatePacket();
	AnimatePacket(int32_t eid, int32_t action);
	virtual ~AnimatePacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
