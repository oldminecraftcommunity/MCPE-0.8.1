#include <network/packet/PlayerArmorEquipmentPacket.hpp>
#include <network/PacketIds.h>
#include <entity/Player.hpp>
#include <network/NetEventCallback.hpp>
static void _D6602FA2_armorId(int8_t* res, ItemInstance* it) {
	if(it) {
		*res = it->getId();
	} else {
		*res = -1;
	}
}
PlayerArmorEquipmentPacket::PlayerArmorEquipmentPacket() {
}
PlayerArmorEquipmentPacket::PlayerArmorEquipmentPacket(struct Player* a2) {
	this->eid = a2->entityId;
	_D6602FA2_armorId(&this->headId, a2->getArmor(0));
	_D6602FA2_armorId(&this->chestId, a2->getArmor(1));
	_D6602FA2_armorId(&this->legsId, a2->getArmor(2));
	_D6602FA2_armorId(&this->bootsId, a2->getArmor(3));
}

PlayerArmorEquipmentPacket::~PlayerArmorEquipmentPacket() {
}
void PlayerArmorEquipmentPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_PLAYER_ARMOR_EQUIPMENT_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<int8_t>(this->headId);
	stream->Write<int8_t>(this->chestId);
	stream->Write<int8_t>(this->legsId);
	stream->Write<int8_t>(this->bootsId);
}
void PlayerArmorEquipmentPacket::read(RakNet::BitStream* stream) {
	stream->Read<int32_t>(this->eid);
	stream->Read<int8_t>(this->headId);
	stream->Read<int8_t>(this->chestId);
	stream->Read<int8_t>(this->legsId);
	stream->Read<int8_t>(this->bootsId);
}
void PlayerArmorEquipmentPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
