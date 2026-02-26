#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct MovePlayerPacket : Packet{
	int32_t eid;
	float x, y, z;
	float pitch, yaw, bodyYaw;
	MovePlayerPacket();
	MovePlayerPacket(int32_t eid, float x, float y, float z, float p, float yaw, float byaw);

	virtual ~MovePlayerPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
