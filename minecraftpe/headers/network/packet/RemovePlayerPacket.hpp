#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct RemovePlayerPacket : Packet{
	int32_t eid;
	RakNet::RakNetGUID clientId;
	RemovePlayerPacket(int32_t eid, RakNet::RakNetGUID cid); //inlined
	RemovePlayerPacket();
	virtual ~RemovePlayerPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
