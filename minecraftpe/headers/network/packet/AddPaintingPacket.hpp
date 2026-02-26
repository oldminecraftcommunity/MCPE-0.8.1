#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <string>

struct Painting;
struct AddPaintingPacket : Packet{
	int32_t eid;
	int32_t x, y, z;
	int32_t direction;
	std::string title;
	AddPaintingPacket();
	AddPaintingPacket(Painting* e);
	virtual ~AddPaintingPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
