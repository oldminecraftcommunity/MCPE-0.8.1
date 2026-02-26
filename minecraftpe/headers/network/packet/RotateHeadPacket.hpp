#pragma once
#include <_types.h>
#include <network/Packet.hpp>
struct Entity;
struct RotateHeadPacket : Packet{
	int32_t eid;
	int8_t headYaw;
	int8_t field_11, field_12, field_13;
	RotateHeadPacket(Entity*, float);
	RotateHeadPacket();

	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
