#include <_types.h>
#include <network/packet/SetTimePacket.hpp>
#include <network/NetEventCallback.hpp>
SetTimePacket::SetTimePacket() {
}
SetTimePacket::SetTimePacket(int32_t tv, bool_t stopTime) {
	this->timeValue = tv;
	this->stopTime = stopTime;
}
SetTimePacket::~SetTimePacket() {
}
void SetTimePacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void SetTimePacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->timeValue);
	stream->Read<bool>(this->stopTime);
}

void SetTimePacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_SET_TIME_PACKET);
	stream->Write<int32_t>(this->timeValue);
	stream->Write<bool>(this->stopTime);
}
