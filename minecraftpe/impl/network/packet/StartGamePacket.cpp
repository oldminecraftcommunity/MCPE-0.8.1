#include <_types.h>
#include <network/packet/StartGamePacket.hpp>
#include <network/NetEventCallback.hpp>
StartGamePacket::StartGamePacket() {
}
StartGamePacket::StartGamePacket(int seed, int genver, int gm, int eid, float x, float y, float z) {
	this->seed = seed;
	this->genver = genver;
	this->gamemode = gm;
	this->eid = eid;
	this->x = x;
	this->y = y;
	this->z = z;
}
StartGamePacket::~StartGamePacket() {
}
void StartGamePacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void StartGamePacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->seed);
	stream->Read<int32_t>(this->genver);
	stream->Read<int32_t>(this->gamemode);
	stream->Read<int32_t>(this->eid);
	stream->Read<float>(this->x);
	stream->Read<float>(this->y);
	stream->Read<float>(this->z);
}

void StartGamePacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_START_GAME_PACKET);
	stream->Write<int32_t>(this->seed);
	stream->Write<int32_t>(this->genver);
	stream->Write<int32_t>(this->gamemode);
	stream->Write<int32_t>(this->eid);
	stream->Write<float>(this->x);
	stream->Write<float>(this->y);
	stream->Write<float>(this->z);
}
