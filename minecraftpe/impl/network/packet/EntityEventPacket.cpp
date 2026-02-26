#include <_types.h>
#include <network/packet/EntityEventPacket.hpp>
#include <network/NetEventCallback.hpp>
EntityEventPacket::EntityEventPacket(){}
EntityEventPacket::EntityEventPacket(int32_t eid, uint8_t event) {
	this->eid = eid;
	this->event = event;
}

EntityEventPacket::~EntityEventPacket() {
}
void EntityEventPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void EntityEventPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->eid);
	stream->Read<uint8_t>(this->event);
}

void EntityEventPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_ENTITY_EVENT_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<uint8_t>(this->event);
}
