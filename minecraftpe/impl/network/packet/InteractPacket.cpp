#include <_types.h>
#include <network/packet/InteractPacket.hpp>
#include <network/NetEventCallback.hpp>
InteractPacket::InteractPacket(int32_t eid, int32_t type, uint8_t action) {
	this->eid = eid;
	this->type = type;
	this->action = action;
}
InteractPacket::InteractPacket() {
}
InteractPacket::~InteractPacket(){

}
void InteractPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void InteractPacket::read(RakNet::BitStream* stream){
	stream->Read<uint8_t>(this->action);
	stream->Read<int32_t>(this->eid);
	stream->Read<int32_t>(this->type);
}

void InteractPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_INTERACT_PACKET);
	stream->Write<uint8_t>(this->action);
	stream->Write<int32_t>(this->eid);
	stream->Write<int32_t>(this->type);
}
