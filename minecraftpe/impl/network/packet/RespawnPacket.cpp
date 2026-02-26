#include <_types.h>
#include <network/packet/RespawnPacket.hpp>
#include <entity/Player.hpp>
#include <network/NetEventCallback.hpp>
RespawnPacket::RespawnPacket() {
}
RespawnPacket::RespawnPacket(Player* p) {
	this->x = p->posX;
	this->y = p->posY;
	this->z = p->posZ;
	this->eid = p->entityId;
}

RespawnPacket::~RespawnPacket() {
}
void RespawnPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void RespawnPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->eid);
	stream->Read<float>(this->x);
	stream->Read<float>(this->y);
	stream->Read<float>(this->z);
}

void RespawnPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_RESPAWN_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<float>(this->x);
	stream->Write<float>(this->y);
	stream->Write<float>(this->z);
}
