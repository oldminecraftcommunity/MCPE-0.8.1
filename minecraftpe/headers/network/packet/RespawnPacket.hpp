#pragma once
#include <_types.h>
#include <network/Packet.hpp>
struct Player;
struct RespawnPacket : Packet{
	float x, y, z;
	int32_t eid;
	RespawnPacket();
	RespawnPacket(Player* p);

	virtual ~RespawnPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
