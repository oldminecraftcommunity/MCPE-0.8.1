#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <vector>

struct TilePos;
struct ExplodePacket : Packet{
	float x, y, z, radius;
	std::vector<TilePos> positions;
	ExplodePacket(float x, float y, float z, float radius);
	ExplodePacket();
	virtual ~ExplodePacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
