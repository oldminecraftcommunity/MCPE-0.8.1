#include <_types.h>
#include <network/packet/RotateHeadPacket.hpp>
#include <entity/Entity.hpp>
#include <network/NetEventCallback.hpp>
RotateHeadPacket::RotateHeadPacket(Entity* e, float yaw) {
	this->eid = e->entityId;
	this->headYaw = yaw;
}

RotateHeadPacket::RotateHeadPacket(){

}

void RotateHeadPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void RotateHeadPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->eid);
	stream->Read<int8_t>(this->headYaw);
}

void RotateHeadPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_ROTATE_HEAD_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<int8_t>(this->headYaw);
}
