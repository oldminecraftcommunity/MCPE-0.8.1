#include <_types.h>
#include <network/packet/ContainerAckPacket.hpp>
#include <network/NetEventCallback.hpp>
ContainerAckPacket::ContainerAckPacket() {
}
void ContainerAckPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void ContainerAckPacket::read(RakNet::BitStream* stream){
	stream->Read<uint8_t>(this->field_E);
	stream->Read<int16_t>(this->field_C);
	stream->Read<bool>(this->field_F);
}

void ContainerAckPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_CONTAINER_ACK_PACKET);
	stream->Write<uint8_t>(this->field_E);
	stream->Write<int16_t>(this->field_C);
	stream->Write<bool>(this->field_F);
}
