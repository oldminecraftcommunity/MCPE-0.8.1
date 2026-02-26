#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct StartGamePacket : Packet{
	int32_t seed, genver, gamemode, eid;
	float x, y, z;
	StartGamePacket();
	StartGamePacket(int seed, int genver, int gm, int eid, float x, float y, float z);
	virtual ~StartGamePacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
