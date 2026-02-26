#pragma once
#include <_types.h>
#include <network/Packet.hpp>
struct ItemEntity;
struct AddItemEntityPacket : Packet{
	int32_t eid;
	float x, y, z;
	int16_t itemID;
	int16_t itemMeta;
	int8_t count;
	int8_t motionX, motionY, motionZ;
	AddItemEntityPacket(ItemEntity* e);
	AddItemEntityPacket();
	virtual ~AddItemEntityPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
