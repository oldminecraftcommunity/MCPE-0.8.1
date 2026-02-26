#include <_types.h>
#include <network/packet/LevelEventPacket.hpp>
#include <network/NetEventCallback.hpp>
LevelEventPacket::LevelEventPacket(){

}
LevelEventPacket::LevelEventPacket(int16_t evid, int16_t x, int16_t y, int16_t z, int32_t data) {
	this->evid = evid;
	this->x = x;
	this->y = y;
	this->z = z;
	this->data = data;
}
LevelEventPacket::~LevelEventPacket(){

}
void LevelEventPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void LevelEventPacket::read(RakNet::BitStream* stream){
	stream->Read<int16_t>(this->evid);
	stream->Read<int16_t>(this->x);
	stream->Read<int16_t>(this->y);
	stream->Read<int16_t>(this->z);
	stream->Read<int32_t>(this->data);
}

void LevelEventPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_LEVEL_EVENT_PACKET);
	stream->Write<int16_t>(this->evid);
	stream->Write<int16_t>(this->x);
	stream->Write<int16_t>(this->y);
	stream->Write<int16_t>(this->z);
	stream->Write<int32_t>(this->data);
}
