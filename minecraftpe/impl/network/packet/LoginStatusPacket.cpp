#include <_types.h>
#include <network/packet/LoginStatusPacket.hpp>
#include <network/NetEventCallback.hpp>
LoginStatusPacket::LoginStatusPacket(){

}
LoginStatusPacket::LoginStatusPacket(int32_t status) {
	this->status = status;
}

LoginStatusPacket::~LoginStatusPacket() {
}
void LoginStatusPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void LoginStatusPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->status);
}

void LoginStatusPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_LOGIN_STATUS_PACKET);
	stream->Write<int32_t>(this->status);
}
