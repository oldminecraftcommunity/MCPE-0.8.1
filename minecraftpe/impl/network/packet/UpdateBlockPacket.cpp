#include <_types.h>
#include <network/packet/UpdateBlockPacket.hpp>
#include <network/NetEventCallback.hpp>
UpdateBlockPacket::UpdateBlockPacket(){

}
UpdateBlockPacket::UpdateBlockPacket(int32_t x, int32_t y, int32_t z, int32_t id, int32_t meta) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->id = id;
	this->meta = meta;
}
UpdateBlockPacket::~UpdateBlockPacket() {
}
void UpdateBlockPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void UpdateBlockPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_UPDATE_BLOCK_PACKET);
	stream->Write<int32_t>(this->x);
	stream->Write<int32_t>(this->z);
	stream->Write<uint8_t>(this->y);
	stream->Write<uint8_t>(this->id);
	stream->Write<uint8_t>(this->meta);
}

void UpdateBlockPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->x);
	stream->Read<int32_t>(this->z);
	stream->Read<uint8_t>(this->y);
	stream->Read<uint8_t>(this->id);
	stream->Read<uint8_t>(this->meta);
}

