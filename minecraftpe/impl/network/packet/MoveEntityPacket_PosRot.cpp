#include <_types.h>
#include <network/packet/MoveEntityPacket_PosRot.hpp>
#include <entity/Entity.hpp>
MoveEntityPacket_PosRot::MoveEntityPacket_PosRot() : MoveEntityPacket(1){

}
MoveEntityPacket_PosRot::MoveEntityPacket_PosRot(Entity* e) {
	this->pitch = e->pitch;
	this->eid = e->entityId;
	this->yaw = e->yaw;
	this->posY = e->posY - e->ridingHeight;
	this->posX = e->posX;
	this->posZ = e->posZ;
}
void MoveEntityPacket_PosRot::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->eid);
	stream->Read<float>(this->posX);
	stream->Read<float>(this->posY);
	stream->Read<float>(this->posZ);
	stream->Read<float>(this->yaw);
	stream->Read<float>(this->pitch);
}

void MoveEntityPacket_PosRot::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_MOVE_ENTITY_POSROT_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<float>(this->posX);
	stream->Write<float>(this->posY);
	stream->Write<float>(this->posZ);
	stream->Write<float>(this->yaw);
	stream->Write<float>(this->pitch);
}
