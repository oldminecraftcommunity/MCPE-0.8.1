#pragma once
#include <_types.h>
#include <item/ItemInstance.hpp>
#include <network/Packet.hpp>

struct DropItemPacket : Packet{
	int32_t eid;
	uint8_t motionType;
	byte align, align1, align2;
	ItemInstance itemInstance;
	DropItemPacket();
	DropItemPacket(int32_t eid, uint8_t, const ItemInstance& a2);

	virtual ~DropItemPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
