#include <_types.h>
#include <network/packet/LoginPacket.hpp>
#include <network/NetEventCallback.hpp>

LoginPacket::LoginPacket() {
	this->clientId = 0;
	this->protocol1 = this->protocol2 = -1;
}

LoginPacket::LoginPacket(std::string name, int32_t clientId, std::string payload) {
	this->clientId = clientId;
	this->protocol1 = this->protocol2 = 14;
	this->username = RakNet::RakString::NonVariadic(name.c_str());
	this->data = RakNet::RakString::NonVariadic(payload.c_str());
}

LoginPacket::~LoginPacket() {
}
void LoginPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void LoginPacket::read(RakNet::BitStream* stream){
	stream->Read<RakNet::RakString>(this->username);

	//TODO if(stream->sizeInBits != steam->field_8)
	{
		stream->Read<int32_t>(this->protocol1);
		stream->Read<int32_t>(this->protocol1);
	}

	//TODO if(stream->sizeInBits != steam->field_8)
	{
		stream->Read<int32_t>(this->clientId);
		stream->Read<RakNet::RakString>(this->data);
	}
}

void LoginPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_LOGIN_PACKET);
	stream->Write<RakNet::RakString>(this->username);
	stream->Write<int32_t>(this->protocol1);
	stream->Write<int32_t>(this->protocol2);
	stream->Write<int32_t>(this->clientId);
	stream->Write<RakNet::RakString>(this->data);
}
