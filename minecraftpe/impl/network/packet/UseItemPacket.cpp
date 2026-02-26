#include <network/packet/UseItemPacket.hpp>
#include <entity/Entity.hpp>
#include <network/NetEventCallback.hpp>
UseItemPacket::UseItemPacket() {
}
UseItemPacket::UseItemPacket(int32_t eid, int32_t x, int32_t y, int32_t z, int32_t face, int32_t id, int32_t meta) {
	this->entityID = eid;
	this->face = face;
	this->x = x;
	this->y = y;
	this->z = z;
	this->itemId = id;
	this->blockMeta = meta;
}

UseItemPacket::UseItemPacket(Entity* e, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz, ItemInstance* it) {
	this->faceX = fx;
	this->x = x;
	this->faceY = fy;
	this->faceZ = fz;
	this->y = y;
	this->z = z;
	this->face = face;
	this->itemId = it ? it->getId() : 0;
	this->blockMeta = it ? it->getAuxValue() : 0;
	this->entityID = e->entityId;
	this->posX = e->posY;
	this->posY = e->posY;
	this->posZ = e->posZ;
}


UseItemPacket::~UseItemPacket() {
}
void UseItemPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_USE_ITEM_PACKET);
	stream->Write<int32_t>(this->x);
	stream->Write<int32_t>(this->y);
	stream->Write<int32_t>(this->z);
	stream->Write<int32_t>(this->face);
	stream->Write<uint16_t>(this->itemId);
	stream->Write<uint8_t>(this->blockMeta);
	stream->Write<int32_t>(this->entityID);
	stream->Write<float>(this->faceX);
	stream->Write<float>(this->faceY);
	stream->Write<float>(this->faceZ);
	stream->Write<float>(this->posX);
	stream->Write<float>(this->posY);
	stream->Write<float>(this->posZ);
}
void UseItemPacket::read(RakNet::BitStream* stream) {
	stream->Read<int32_t>(this->x);
	stream->Read<int32_t>(this->y);
	stream->Read<int32_t>(this->z);
	stream->Read<int32_t>(this->face);
	stream->Read<uint16_t>(this->itemId);
	stream->Read<uint8_t>(this->blockMeta);
	stream->Read<int32_t>(this->entityID);
	stream->Read<float>(this->faceX);
	stream->Read<float>(this->faceY);
	stream->Read<float>(this->faceZ);
	stream->Read<float>(this->posX);
	stream->Read<float>(this->posY);
	stream->Read<float>(this->posZ);
	this->item = ItemInstance(this->itemId, this->blockMeta, this->itemId != 0 && this->blockMeta != 0); //actually checks (((int*)this->itemID) & 0xffffff) != 0
}
void UseItemPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
