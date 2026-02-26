#include <_types.h>
#include <network/packet/RemoveEntityPacket.hpp>
#include <network/NetEventCallback.hpp>
RemoveEntityPacket::RemoveEntityPacket(){

}
RemoveEntityPacket::RemoveEntityPacket(int32_t eid) {
	this->eid = eid;
}
RemoveEntityPacket::~RemoveEntityPacket() {
}
void RemoveEntityPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void RemoveEntityPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->eid);
}

void RemoveEntityPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_REMOVE_ENTITY_PACKET);
	stream->Write<int32_t>(this->eid);
}
