#include <_types.h>
#include <network/packet/ReadyPacket.hpp>
#include <network/NetEventCallback.hpp>
ReadyPacket::ReadyPacket(int8_t s) {
	this->status = s;
}
ReadyPacket::~ReadyPacket() {
}
void ReadyPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void ReadyPacket::read(RakNet::BitStream* stream){
	stream->Read<int8_t>(this->status);
}

void ReadyPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_READY_PACKET);
	stream->Write<int8_t>(this->status);
}
