#include <_types.h>
#include <network/packet/SetHealthPacket.hpp>
#include <network/NetEventCallback.hpp>
SetHealthPacket::SetHealthPacket() {
}
SetHealthPacket::SetHealthPacket(int32_t h) {
	this->health = h;
}

SetHealthPacket::~SetHealthPacket() {
}
void SetHealthPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void SetHealthPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_SET_HEALTH_PACKET);
	int8_t a = (int8_t) (this->health);
	stream->Write<int8_t>(a);
}

void SetHealthPacket::read(RakNet::BitStream* stream){
	int8_t a;
	stream->Read<int8_t>(a);
	this->health = a;
}
