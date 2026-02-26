#include <_types.h>
#include <network/packet/AnimatePacket.hpp>
#include <network/NetEventCallback.hpp>

AnimatePacket::AnimatePacket() {
}
AnimatePacket::AnimatePacket(int32_t eid, int32_t action) {
	this->eid = eid;
	this->action = action;
}
AnimatePacket::~AnimatePacket() {
}
void AnimatePacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void AnimatePacket::read(RakNet::BitStream* stream){
	stream->Read<int8_t>(this->action);
	stream->Read<int32_t>(this->eid);
}

void AnimatePacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_ANIMATE_PACKET);
	stream->Write<int8_t>(this->action);
	stream->Write<int32_t>(this->eid);
}
