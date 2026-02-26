#include <_types.h>
#include <network/packet/ChatPacket.hpp>
#include <network/NetEventCallback.hpp>
ChatPacket::ChatPacket(){

}
ChatPacket::ChatPacket(std::string a2, bool_t a3) {
	if(a2.size() > 116) {
		a2 = a2.substr(0, 116);
	}
	this->message = a2;
	this->field_10 = a3;
}

ChatPacket::~ChatPacket() {
}
void ChatPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void ChatPacket::read(RakNet::BitStream* stream){
	RakNet::RakString v5;
	v5.Deserialize(stream);
	this->message = v5.C_String();
}

void ChatPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_CHAT_PACKET);
	RakNet::RakString::Serialize(this->message.c_str(), stream);
}

//TODO remove this->message?
