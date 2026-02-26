#include <network/packet/ContainerSetDataPacket.hpp>
#include <network/PacketIds.h>
#include <network/NetEventCallback.hpp>
ContainerSetDataPacket::ContainerSetDataPacket() {
}
ContainerSetDataPacket::ContainerSetDataPacket(int16_t c, int16_t e, uint8_t f10) {
	this->field_C = c;
	this->field_E = e;
	this->field_10 = f10;
}

ContainerSetDataPacket::~ContainerSetDataPacket() {
}
void ContainerSetDataPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_CONTAINER_SET_DATA_PACKET);
	stream->Write<uint8_t>(this->field_10);
	stream->Write<int16_t>(this->field_C);
	stream->Write<int16_t>(this->field_E);
}
void ContainerSetDataPacket::read(RakNet::BitStream* stream) {
	stream->Read<uint8_t>(this->field_10);
	stream->Read<int16_t>(this->field_C);
	stream->Read<int16_t>(this->field_E);

}
void ContainerSetDataPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
