#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct LevelEventPacket : Packet{
	int16_t evid;
	int16_t x, y, z;
	int32_t data;
	LevelEventPacket();
	LevelEventPacket(int16_t evid, int16_t x, int16_t y, int16_t z, int32_t data);
	virtual ~LevelEventPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
