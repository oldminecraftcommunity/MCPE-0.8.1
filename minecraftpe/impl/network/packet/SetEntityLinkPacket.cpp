#include <_types.h>
#include <network/packet/SetEntityLinkPacket.hpp>
#include <network/NetEventCallback.hpp>
SetEntityLinkPacket::SetEntityLinkPacket(int32_t type, int32_t rider, int32_t riding) {
	this->typeMaybe = type;
	this->rider = rider;
	this->riding = riding;
}
SetEntityLinkPacket::SetEntityLinkPacket(){

}

SetEntityLinkPacket::~SetEntityLinkPacket() {
}
void SetEntityLinkPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void SetEntityLinkPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->rider);
	stream->Read<int32_t>(this->riding);
	stream->Read<int32_t>(this->typeMaybe);
}

void SetEntityLinkPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_SET_ENTITY_LINK_PACKET);
	stream->Write<int32_t>(this->rider);
	stream->Write<int32_t>(this->riding);
	stream->Write<int32_t>(this->typeMaybe);
}
