#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct MoveEntityPacket : Packet{
	int32_t eid;
	float posX, posY, posZ;
	float pitch, yaw;
	bool_t hasrot;
	MoveEntityPacket();
	MoveEntityPacket(bool hasrot);
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
