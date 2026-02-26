#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <nbt/CompoundTag.hpp>

struct EntityDataPacket : Packet{
	int32_t x, y, z;
	CompoundTag data;
	EntityDataPacket();
	EntityDataPacket(int32_t x, int32_t y, int32_t z, CompoundTag* data);

	virtual ~EntityDataPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
