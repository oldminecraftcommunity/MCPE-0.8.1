#include <_types.h>
#include <network/packet/MoveEntityPacket.hpp>
#include <network/NetEventCallback.hpp>
MoveEntityPacket::MoveEntityPacket() {
}
MoveEntityPacket::MoveEntityPacket(bool hasrot) {
	this->hasrot = hasrot;
}
void MoveEntityPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void MoveEntityPacket::read(RakNet::BitStream* stream){

}

void MoveEntityPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_MOVE_ENTITY_PACKET);
}
