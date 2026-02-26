#include <_types.h>
#include <network/packet/AddEntityPacket.hpp>
#include <entity/Entity.hpp>
#include <network/NetEventCallback.hpp>
AddEntityPacket::AddEntityPacket() {
}
AddEntityPacket::AddEntityPacket(Entity* a2, int did) {
	this->eid = a2->entityId;
	this->x = a2->posX;
	this->y = a2->posY;
	this->z = a2->posZ;
	this->did = did;
	this->type = a2->getEntityTypeId();
	if(did > 0) {
		this->motionX = a2->motionX;
		this->motionY = a2->motionY;
		this->motionZ = a2->motionZ;
	}
}

AddEntityPacket::~AddEntityPacket() {
}
void AddEntityPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_ADD_ENTITY_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<uint8_t>(this->type);
	stream->Write<float>(this->x);
	stream->Write<float>(this->y);
	stream->Write<float>(this->z);
	stream->Write<int32_t>(this->did);
	if(this->did > 0){
		float motX = this->motionX;
		float motY = this->motionY;
		float motZ = this->motionZ;
		if(motX > 3.9f) motX = 3.9f;
		else if(motX <= -3.9f) motX = -3.9f;
		int16_t mX = (int16_t)(motX*8000);

		if(motY > 3.9f) motY = 3.9f;
		else if(motY <= -3.9) motY = -3.9f;
		int16_t mY = (int16_t)(motY*8000);

		if(motZ > 3.9) motZ = 3.9;
		else if(motZ <= -3.9) motZ = -3.9;
		int16_t mZ = (int16_t)(motZ*8000);

		stream->Write<int16_t>(mX);
		stream->Write<int16_t>(mY);
		stream->Write<int16_t>(mZ);
	}
}

void AddEntityPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->eid);
	uint8_t tt = (uint8_t) this->type;
	stream->Read<uint8_t>(tt);
	stream->Read<float>(this->x);
	stream->Read<float>(this->y);
	stream->Read<float>(this->z);
	stream->Read<int32_t>(this->did);
	if(this->did > 0){
		int16_t mx, my, mz;
		stream->Read<int16_t>(mx);
		stream->Read<int16_t>(my);
		stream->Read<int16_t>(mz);

		this->motionX = (float)mx / 8000.0f;
		this->motionY = (float)my / 8000.0f;
		this->motionZ = (float)mz / 8000.0f;
	}
}

void AddEntityPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}
