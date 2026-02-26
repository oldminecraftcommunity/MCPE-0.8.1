#include <network/packet/ContainerSetSlotPacket.hpp>
#include <network/PacketIds.h>
#include <util/PacketUtil.hpp>
#include <network/NetEventCallback.hpp>

ContainerSetSlotPacket::ContainerSetSlotPacket(){

}

ContainerSetSlotPacket::ContainerSetSlotPacket(int8_t c, int8_t d, int16_t e, const ItemInstance& f10) : field_10(f10){
	this->field_C = c;
	this->field_D = d;
	this->field_E = e;
}
ContainerSetSlotPacket::~ContainerSetSlotPacket() {
}
void ContainerSetSlotPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_CONTAINER_SET_SLOT_PACKET);
	stream->Write<int8_t>(this->field_D);
	stream->Write<int16_t>(this->field_E);
	PacketUtil::writeItemInstance(this->field_10, stream);
}
void ContainerSetSlotPacket::read(RakNet::BitStream* stream) {
	stream->Read<int8_t>(this->field_D);
	stream->Read<int16_t>(this->field_E);
	this->field_10 = PacketUtil::readItemInstance(stream);
}
void ContainerSetSlotPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
