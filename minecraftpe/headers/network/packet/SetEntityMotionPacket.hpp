#pragma once
#include <_types.h>
#include <network/Packet.hpp>
struct Entity;
struct SetEntityMotionPacket : Packet{
	int32_t eid;
	float speedX, speedY, speedZ;
	SetEntityMotionPacket(Entity*); //always inlined
	SetEntityMotionPacket();

	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
