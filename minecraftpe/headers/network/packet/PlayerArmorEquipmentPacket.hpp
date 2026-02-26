#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct PlayerArmorEquipmentPacket : Packet{
	int32_t eid;
	int8_t headId, chestId, legsId, bootsId;

	PlayerArmorEquipmentPacket(struct Player*);
	PlayerArmorEquipmentPacket();
	virtual ~PlayerArmorEquipmentPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
