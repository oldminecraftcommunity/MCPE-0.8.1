#include <_types.h>
#include <network/packet/RequestChunkPacket.hpp>
#include <network/NetEventCallback.hpp>
RequestChunkPacket::RequestChunkPacket() {
}
RequestChunkPacket::RequestChunkPacket(int32_t x, int32_t z) {
	this->x = x;
	this->z = z;
}

RequestChunkPacket::~RequestChunkPacket() {
}
void RequestChunkPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void RequestChunkPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_REQUEST_CHUNK_PACKET);
	stream->Write<int32_t>(this->x);
	stream->Write<int32_t>(this->z);
}

void RequestChunkPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->x);
	stream->Read<int32_t>(this->z);
}
