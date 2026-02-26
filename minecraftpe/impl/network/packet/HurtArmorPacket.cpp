#include <_types.h>
#include <network/packet/HurtArmorPacket.hpp>
#include <network/NetEventCallback.hpp>

HurtArmorPacket::HurtArmorPacket(int8_t h) {
	this->health = h;
}
HurtArmorPacket::HurtArmorPacket() {
}
HurtArmorPacket::~HurtArmorPacket(){

}

void HurtArmorPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void HurtArmorPacket::read(RakNet::BitStream* stream){
	stream->Read<int8_t>(this->health);
}

void HurtArmorPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_HURT_ARMOR_PACKET);
	stream->Write<int8_t>(this->health);
}
