#include <_types.h>
#include <network/packet/PlaceBlockPacket.hpp>
#include <network/NetEventCallback.hpp>
PlaceBlockPacket::PlaceBlockPacket(){}
void PlaceBlockPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void PlaceBlockPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->field_C);
	stream->Read<int32_t>(this->field_10);
	stream->Read<int32_t>(this->field_14);
	stream->Read<uint8_t>(this->field_18);
	stream->Read<uint8_t>(this->field_19);
	stream->Read<uint8_t>(this->field_1A);
	stream->Read<uint8_t>(this->field_1B);
}

void PlaceBlockPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_PLACE_BLOCK_PACKET);
	stream->Write<int32_t>(this->field_C);
	stream->Write<int32_t>(this->field_10);
	stream->Write<int32_t>(this->field_14);
	stream->Write<uint8_t>(this->field_18);
	stream->Write<uint8_t>(this->field_19);
	stream->Write<uint8_t>(this->field_1A);
	stream->Write<uint8_t>(this->field_1B);
}
