#include <_types.h>
#include <network/packet/SetEntityMotionPacket.hpp>
#include <entity/Entity.hpp>
#include <network/NetEventCallback.hpp>

SetEntityMotionPacket::SetEntityMotionPacket(Entity* e) {
	this->speedX = e->motionX;
	this->speedY = e->motionY;
	this->speedZ = e->motionZ;
	this->eid = e->entityId;
}
SetEntityMotionPacket::SetEntityMotionPacket(){

}
void SetEntityMotionPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void SetEntityMotionPacket::read(RakNet::BitStream* stream){
	int16_t speedX, speedY, speedZ;
	stream->Read<int32_t>(this->eid);
	stream->Read<int16_t>(speedX);
	stream->Read<int16_t>(speedY);
	stream->Read<int16_t>(speedZ);

	this->speedX = (float)speedX/8000.0f;
	this->speedY = (float)speedY/8000.0f;
	this->speedZ = (float)speedZ/8000.0f;
}

void SetEntityMotionPacket::write(RakNet::BitStream* stream){
	float motX = this->speedX;
	float motY = this->speedY;
	float motZ = this->speedZ;
	if(motX > 3.9f) motX = 3.9f;
	else if(motX <= -3.9f) motX = -3.9f;
	int16_t mX = (int16_t)(motX*8000);

	if(motY > 3.9f) motY = 3.9f;
	else if(motY <= -3.9) motY = -3.9f;
	int16_t mY = (int16_t)(motY*8000);

	if(motZ > 3.9) motZ = 3.9;
	else if(motZ <= -3.9) motZ = -3.9;
	int16_t mZ = (int16_t)(motZ*8000);

	stream->Write<uint8_t>(PID_SET_ENTITY_MOTION_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<int16_t>(motX);
	stream->Write<int16_t>(motY);
	stream->Write<int16_t>(motZ);
}
