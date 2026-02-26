#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct InteractPacket : Packet{
	uint8_t action;
	byte align1, align2, align3;
	int32_t eid, type;
	InteractPacket(int32_t eid, int32_t type, uint8_t action);
	InteractPacket();
	virtual ~InteractPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
