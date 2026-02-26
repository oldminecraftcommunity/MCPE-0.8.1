#include <network/packet/EntityDataPacket.hpp>
#include <network/PacketIds.h>
#include <util/output/RakDataOutput.hpp>
#include <util/input/RakDataInput.hpp>
#include <network/NetEventCallback.hpp>
EntityDataPacket::EntityDataPacket(){

}
EntityDataPacket::EntityDataPacket(int32_t x, int32_t y, int32_t z, CompoundTag* d)
	: data(*d) {
	this->x = x;
	this->y = y;
	this->z = z;
}
EntityDataPacket::~EntityDataPacket() {
}
void EntityDataPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_ENTITY_DATA_PACKET);
	stream->Write<int16_t>(this->x);
	stream->Write<uint8_t>(this->y);
	stream->Write<int16_t>(this->z);
	RakDataOutput v7;
	v7.bitStream = stream;
	Tag::writeNamedTag(&this->data, &v7);
}
void EntityDataPacket::read(RakNet::BitStream* stream) {
	int16_t x, z;
	uint8_t y;
	stream->Read<int16_t>(x);
	stream->Read<uint8_t>(y);
	stream->Read<int16_t>(z);
	this->x = x;
	this->z = z;
	this->y = y;
	RakDataInput a1;
	a1.stream = stream;
	Tag* v5 = Tag::readNamedTag(&a1);
	if(!v5 || v5->getId() != 10) {
		v5 = 0;
	}
	//TODO this will crash on fail, check should it actually happen
	this->data = *(CompoundTag*)v5;
	delete v5;

}
void EntityDataPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
