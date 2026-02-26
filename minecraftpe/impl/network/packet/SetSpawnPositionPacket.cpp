#include <_types.h>
#include <network/packet/SetSpawnPositionPacket.hpp>
#include <network/NetEventCallback.hpp>
SetSpawnPositionPacket::SetSpawnPositionPacket() {
}
void SetSpawnPositionPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void SetSpawnPositionPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->x);
	stream->Read<int32_t>(this->z);
	stream->Read<uint8_t>(this->y);
}

void SetSpawnPositionPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_SET_SPAWN_POSITION_PACKET);
	stream->Write<int32_t>(this->x);
	stream->Write<int32_t>(this->z);
	stream->Write<uint8_t>(this->y);
}
