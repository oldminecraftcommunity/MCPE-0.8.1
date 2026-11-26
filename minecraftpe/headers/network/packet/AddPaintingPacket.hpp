#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>
#include <string>
#include <entity/Painting.hpp>
#include <Motive.hpp>

struct Painting;
struct AddPaintingPacket : Packet{
	int32_t eid;
	int32_t x, y, z;
	int32_t direction;
	std::string title;
	AddPaintingPacket() {
		this->eid = 0;
		this->x = this->y = this->z = 0;
		this->direction = -1;
	}
		AddPaintingPacket(Painting* e) {
		this->eid = e->entityId;
		this->x = e->tileX;
		this->y = e->tileY;
		this->z = e->tileZ;
		this->direction = e->direction;
		this->title = e->motive->name;
	}
	virtual ~AddPaintingPacket() {
	}

	virtual void write(RakNet::BitStream* stream){
		stream->Write<uint8_t>(PID_ADD_PAINTING_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<int32_t>(this->x);
		stream->Write<int32_t>(this->y);
		stream->Write<int32_t>(this->z);
		stream->Write<int32_t>(this->direction);
		RakNet::RakString v7 = RakNet::RakString::NonVariadic(this->title.c_str());
		stream->Write<RakNet::RakString>(v7);
	}
	virtual void read(RakNet::BitStream* stream){
		stream->Read<int32_t>(this->eid);
		stream->Read<int32_t>(this->x);
		stream->Read<int32_t>(this->y);
		stream->Read<int32_t>(this->z);
		stream->Read<int32_t>(this->direction);
		RakNet::RakString v4;
		stream->Read<RakNet::RakString>(v4);
		this->title = std::string(v4.C_String());
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
		a3->handle(a2, this);
	}
};
