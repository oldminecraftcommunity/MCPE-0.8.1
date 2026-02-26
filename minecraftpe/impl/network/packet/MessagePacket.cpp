#include <network/packet/MessagePacket.hpp>
#include <_types.h>
#include <network/NetEventCallback.hpp>
MessagePacket::MessagePacket(){

}
MessagePacket::MessagePacket(std::string message, std::string source) {
	this->message = RakNet::RakString(message.c_str());
	this->source = RakNet::RakString(source.c_str());
}
MessagePacket::~MessagePacket() {
}
void MessagePacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}

void MessagePacket::read(RakNet::BitStream* stream) {
	this->source.Deserialize(stream);
	this->message.Deserialize(stream);
}

void MessagePacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_MESSAGE_PACKET);
	this->source.Serialize(stream);
	this->message.Serialize(stream);
}
