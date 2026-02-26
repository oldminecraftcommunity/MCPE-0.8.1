#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <string>

struct ChatPacket : Packet{
	std::string message;
	bool_t field_10;
	int8_t field_11, field_12, field_13;
	ChatPacket();
	ChatPacket(std::string, bool_t);

	virtual ~ChatPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
