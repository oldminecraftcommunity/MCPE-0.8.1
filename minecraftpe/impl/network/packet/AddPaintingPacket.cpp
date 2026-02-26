#include <_types.h>
#include <network/packet/AddPaintingPacket.hpp>
#include <entity/Painting.hpp>
#include <Motive.hpp>
#include <network/NetEventCallback.hpp>
AddPaintingPacket::AddPaintingPacket() {
	this->eid = 0;
	this->x = this->y = this->z = 0;
	this->direction = -1;
}
AddPaintingPacket::AddPaintingPacket(Painting* e) {
	this->eid = e->entityId;
	this->x = e->tileX;
	this->y = e->tileY;
	this->z = e->tileZ;
	this->direction = e->direction;
	this->title = e->motive->name;
}
AddPaintingPacket::~AddPaintingPacket() {
}
void AddPaintingPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->eid);
	stream->Read<int32_t>(this->x);
	stream->Read<int32_t>(this->y);
	stream->Read<int32_t>(this->z);
	stream->Read<int32_t>(this->direction);
	RakNet::RakString v4;
	stream->Read<RakNet::RakString>(v4);
	this->title = v4.C_String();
}

void AddPaintingPacket::write(RakNet::BitStream* stream){
	stream->Write<int32_t>(this->eid);
	stream->Write<int32_t>(this->x);
	stream->Write<int32_t>(this->y);
	stream->Write<int32_t>(this->z);
	stream->Write<int32_t>(this->direction);
	RakNet::RakString v7 = RakNet::RakString::NonVariadic(this->title.c_str());
	v7.Serialize(stream);
}

void AddPaintingPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

//TODO need to free this->title?
