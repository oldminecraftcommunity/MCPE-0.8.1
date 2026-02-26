#include <_types.h>
#include <network/packet/ContainerClosePacket.hpp>
#include <network/NetEventCallback.hpp>
ContainerClosePacket::ContainerClosePacket() {
}
ContainerClosePacket::ContainerClosePacket(uint8_t field_C) {
	this->field_C = field_C;
}
ContainerClosePacket::~ContainerClosePacket() {
}
void ContainerClosePacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void ContainerClosePacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_CONTAINER_CLOSE_PACKET);
	stream->Write<uint8_t>(this->field_C);
}

void ContainerClosePacket::read(RakNet::BitStream* stream){
	stream->Read<uint8_t>(this->field_C);
}
