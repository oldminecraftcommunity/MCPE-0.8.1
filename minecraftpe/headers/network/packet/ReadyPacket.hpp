#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct ReadyPacket : Packet{
	int8_t status;
	int8_t align1, align2, align3;

	ReadyPacket(int8_t status);

	virtual ~ReadyPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
