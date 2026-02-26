#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct SetSpawnPositionPacket : Packet{
	int32_t field_C; //useless field
	int32_t x, z;
	uint8_t y;
	int8_t field_19, field_1A, field_1B;
	SetSpawnPositionPacket();

	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
