#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct SetEntityLinkPacket : Packet{
	int32_t typeMaybe, rider, riding;

	SetEntityLinkPacket(int32_t type, int32_t rider, int32_t riding);
	SetEntityLinkPacket();

	virtual ~SetEntityLinkPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
