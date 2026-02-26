#pragma once
#include <_types.h>
#include <network/Packet.hpp>
struct Entity;
struct AddEntityPacket : Packet{
	int32_t eid;
	float x, y, z;
	float motionX, motionY, motionZ;
	int32_t type, did;
	AddEntityPacket();
	AddEntityPacket(Entity*, int did);

	virtual ~AddEntityPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
