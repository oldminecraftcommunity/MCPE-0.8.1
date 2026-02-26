#include <_types.h>
#include <network/packet/ContainerOpenPacket.hpp>
#include <network/NetEventCallback.hpp>
ContainerOpenPacket::ContainerOpenPacket() {
}
ContainerOpenPacket::ContainerOpenPacket(uint8_t c, uint8_t cid, uint8_t e, int32_t x, int32_t y, int32_t z) {
	this->field_C = c;
	this->containerId = cid;
	this->field_E = e;
	this->x = x;
	this->y = y;
	this->z = z;
}

ContainerOpenPacket::~ContainerOpenPacket() {
}
void ContainerOpenPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void ContainerOpenPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_CONTAINER_OPEN_PACKET);
	stream->Write<uint8_t>(this->field_C);
	stream->Write<uint8_t>(this->containerId);
	stream->Write<uint8_t>(this->field_E);
	stream->Write<int32_t>(this->x);
	stream->Write<int32_t>(this->y);
	stream->Write<int32_t>(this->z);
}

void ContainerOpenPacket::read(RakNet::BitStream* stream){
	stream->Read<uint8_t>(this->field_C);
	stream->Read<uint8_t>(this->containerId);
	stream->Read<uint8_t>(this->field_E);
	stream->Read<int32_t>(this->x);
	stream->Read<int32_t>(this->y);
	stream->Read<int32_t>(this->z);
}
