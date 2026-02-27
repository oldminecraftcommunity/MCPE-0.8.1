#pragma once
#include <_types.h>
#include <item/ItemInstance.hpp>
#include <network/Packet.hpp>

struct UseItemPacket : Packet{
	int32_t x, y, z;
	int32_t face;
	float faceX, faceY, faceZ;
	float posX, posY, posZ;
	int32_t entityID;
	uint16_t itemId;
	uint8_t blockMeta;
	char align;
	ItemInstance item;
	UseItemPacket();
	UseItemPacket(int32_t eid, int32_t x, int32_t y, int32_t z, int32_t face, int32_t id, int32_t meta);
	UseItemPacket(Entity* e, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz, ItemInstance* it);

	virtual ~UseItemPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
