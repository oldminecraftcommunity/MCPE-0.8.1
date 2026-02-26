#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct SetHealthPacket : Packet{
	int32_t health;
	SetHealthPacket();
	SetHealthPacket(int32_t h);

	virtual ~SetHealthPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
