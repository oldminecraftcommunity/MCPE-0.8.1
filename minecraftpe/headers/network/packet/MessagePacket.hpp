#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <string>
#include <network/NetEventCallback.hpp>

struct MessagePacket : Packet{
	RakNet::RakString source;
	RakNet::RakString message;
	MessagePacket(){}
	MessagePacket(const std::string& message, const std::string& source) {
		this->message = RakNet::RakString::NonVariadic(message.c_str());
		this->source = RakNet::RakString::NonVariadic(source.c_str());
	}
	virtual ~MessagePacket(){}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_MESSAGE_PACKET);
		this->source.Serialize(stream);
		this->message.Serialize(stream);
	}
	virtual void read(RakNet::BitStream* stream) {
		this->source.Deserialize(stream);
		this->message.Deserialize(stream);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
