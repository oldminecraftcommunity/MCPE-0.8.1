#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct TileEventPacket : Packet{
	int32_t x, y, z;
	int32_t case1, case2;
	TileEventPacket();
	TileEventPacket(int, int, int, int, int);
	virtual ~TileEventPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
