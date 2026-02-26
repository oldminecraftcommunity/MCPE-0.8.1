#include <_types.h>
#include <network/packet/PlayerEquipmentPacket.hpp>
#include <network/NetEventCallback.hpp>
PlayerEquipmentPacket::PlayerEquipmentPacket(int32_t eid, uint16_t itemId, uint16_t itemMeta, int8_t slot) {
	this->eid = eid;
	this->itemID = itemId;
	this->itemMeta = itemMeta;
	this->slot = slot;
}
PlayerEquipmentPacket::PlayerEquipmentPacket() {
}
PlayerEquipmentPacket::~PlayerEquipmentPacket() {
}

void PlayerEquipmentPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void PlayerEquipmentPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->eid);
	stream->Read<uint16_t>(this->itemID);
	stream->Read<uint16_t>(this->itemMeta);
	stream->Read<int8_t>(this->slot);
}

void PlayerEquipmentPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_PLAYER_EQUIPMENT_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<uint16_t>(this->itemID);
	stream->Write<uint16_t>(this->itemMeta);
	stream->Write<int8_t>(this->slot);
}
