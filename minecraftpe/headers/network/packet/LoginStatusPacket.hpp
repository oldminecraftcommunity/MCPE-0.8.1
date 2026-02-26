#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct LoginStatusPacket : Packet{
	int32_t status;
	LoginStatusPacket();
	LoginStatusPacket(int32_t status);

	virtual ~LoginStatusPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
