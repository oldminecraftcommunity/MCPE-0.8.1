#include <network/packet/ExplodePacket.hpp>
#include <network/PacketIds.h>
#include <network/NetEventCallback.hpp>
#include <util/TilePos.hpp>
ExplodePacket::ExplodePacket() {
}
ExplodePacket::ExplodePacket(float x, float y, float z, float radius) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->radius = radius;
}
ExplodePacket::~ExplodePacket() {
}
void ExplodePacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_EXPLODE_PACKET);
	stream->Write<float>(this->x);
	stream->Write<float>(this->y);
	stream->Write<float>(this->z);
	stream->Write<float>(this->radius);
	int32_t v13 = this->positions.size();
	stream->Write<int32_t>(v13);
	int32_t x = (int32_t)this->x;
	int32_t y = (int32_t)this->y;
	int32_t z = (int32_t)this->z;

	for(int32_t i = 0; i < v13; ++i) {
		TilePos* tp = &this->positions[i];
		stream->Write<int8_t>(tp->x - x);
		stream->Write<int8_t>(tp->y - y);
		stream->Write<int8_t>(tp->z - z);
	}
}
void ExplodePacket::read(RakNet::BitStream* stream) {
	stream->Read<float>(this->x);
	stream->Read<float>(this->y);
	stream->Read<float>(this->z);
	stream->Read<float>(this->radius);
	int32_t count;
	stream->Read<int32_t>(count);
	if(count >= 0) {
		int8_t x, y, z;
		for(int32_t i = 0; i < count && stream->Read<int8_t>(x) && stream->Read<int8_t>(y) && stream->Read<int8_t>(z); ++i) {
			this->positions.emplace_back(TilePos{(int32_t)this->x + x, (int32_t)this->y + y, (int32_t)this->z + z});
		}
	}

}
void ExplodePacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
