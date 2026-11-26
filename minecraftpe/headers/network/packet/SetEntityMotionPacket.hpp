#pragma once
#include <network/Packet.hpp>
#include <entity/Entity.hpp>
#include <network/NetEventCallback.hpp>

struct Entity;
struct SetEntityMotionPacket : Packet{
	int32_t eid;
	float speedX, speedY, speedZ;
	SetEntityMotionPacket(Entity* e) {
		this->speedX = e->motionX;
		this->speedY = e->motionY;
		this->speedZ = e->motionZ;
		this->eid = e->entityId;
	}
	SetEntityMotionPacket() {
	}

	virtual void write(RakNet::BitStream* stream) {
		float motX = this->speedX;
		if (motX > 3.9f) motX = 3.9f;
		else if (motX <= -3.9f) motX = -3.9f;
		short mX = (short) (motX * 8000);

		float motY = this->speedY;
		if (motY > 3.9f) motY = 3.9f;
		else if (motY <= -3.9f) motY = -3.9f;
		short mY = (short) (motY * 8000);

		float motZ = this->speedZ;
		if (motZ > 3.9f) motZ = 3.9f;
		else if (motZ <= -3.9f) motZ = -3.9f;
		short mZ = (short) (motZ * 8000);

		stream->Write<uint8_t>(PID_SET_ENTITY_MOTION_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<short>(mX);
		stream->Write<short>(mY);
		stream->Write<short>(mZ);
	}
	virtual void read(RakNet::BitStream* stream) {
		int16_t speedX, speedY, speedZ;
		stream->Read<int32_t>(this->eid);
		stream->Read<int16_t>(speedX);
		stream->Read<int16_t>(speedY);
		stream->Read<int16_t>(speedZ);
		this->speedX = (float) (speedX) / 8000.0f;
		this->speedY = (float) (speedY) / 8000.0f;
		this->speedZ = (float) (speedZ) / 8000.0f;
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
