#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <string>
#include <network/NetEventCallback.hpp>


struct ChatPacket : Packet{
	std::string message;
	bool_t field_10;
	ChatPacket() {
	}
	ChatPacket(std::string a2, bool_t a3) {
		if (a2.size() > 116) {
			a2 = a2.substr(0, 116);
		}
		this->message = a2;
		this->field_10 = a3;
	}

	virtual ~ChatPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_CHAT_PACKET);
		RakNet::RakString::Serialize(this->message.c_str(), stream);
	}
	virtual void read(RakNet::BitStream* stream) {
		RakNet::RakString v5;
		v5.Deserialize(stream);
		this->message = v5.C_String();
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
