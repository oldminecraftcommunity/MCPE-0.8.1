#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct PlayerEquipmentPacket : Packet{
	int32_t eid;
	uint16_t itemID, itemMeta;
	int8_t slot;
	byte align, align2, align3;
	PlayerEquipmentPacket(int32_t eid, uint16_t itemId, uint16_t itemMeta, int8_t slot);
	PlayerEquipmentPacket();
	virtual ~PlayerEquipmentPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
