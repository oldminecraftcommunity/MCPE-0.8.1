#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <string>

struct MessagePacket : Packet{
	RakNet::RakString source;
	RakNet::RakString message;
	MessagePacket();
	MessagePacket(std::string message, std::string source);
	virtual ~MessagePacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
