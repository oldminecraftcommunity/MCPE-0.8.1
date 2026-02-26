#include <_types.h>
#include <network/packet/TileEventPacket.hpp>
#include <network/NetEventCallback.hpp>
TileEventPacket::TileEventPacket() {
}
TileEventPacket::TileEventPacket(int32_t x, int32_t y, int32_t z, int32_t c1, int32_t c2) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->case1 = c1;
	this->case2 = c2;
}
TileEventPacket::~TileEventPacket(){

}
void TileEventPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void TileEventPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->x);
	stream->Read<int32_t>(this->y);
	stream->Read<int32_t>(this->z);
	stream->Read<int32_t>(this->case1);
	stream->Read<int32_t>(this->case2);
}

void TileEventPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_TILE_EVENT_PACKET);
	stream->Write<int32_t>(this->x);
	stream->Write<int32_t>(this->y);
	stream->Write<int32_t>(this->z);
	stream->Write<int32_t>(this->case1);
	stream->Write<int32_t>(this->case2);
}
