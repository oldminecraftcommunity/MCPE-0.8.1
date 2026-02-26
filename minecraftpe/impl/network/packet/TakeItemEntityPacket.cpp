#include <_types.h>
#include <network/packet/TakeItemEntityPacket.hpp>
#include <network/NetEventCallback.hpp>
TakeItemEntityPacket::TakeItemEntityPacket(int32_t eid, int32_t targt) {
	this->eid = eid;
	this->target = targt;
}
TakeItemEntityPacket::TakeItemEntityPacket(){

}
TakeItemEntityPacket::~TakeItemEntityPacket() {
}
void TakeItemEntityPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void TakeItemEntityPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->target);
	stream->Read<int32_t>(this->eid);
}

void TakeItemEntityPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_TAKE_ITEM_ENTITY_PACKET);
	stream->Write<int32_t>(this->target);
	stream->Write<int32_t>(this->eid);
}
