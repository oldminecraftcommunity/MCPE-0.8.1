#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <string>

struct LoginPacket : Packet{
	RakNet::RakString username;
	int32_t protocol1, protocol2;
	int32_t clientId;
	RakNet::RakString data;
	LoginPacket();
	LoginPacket(std::string name, int32_t clientId, std::string payload);

	virtual ~LoginPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
