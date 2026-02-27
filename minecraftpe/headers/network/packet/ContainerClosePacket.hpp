#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct ContainerClosePacket : Packet{
UNK	uint8_t field_C;
	char align1, align2, align3;
	ContainerClosePacket();
	ContainerClosePacket(uint8_t field_C);
	virtual ~ContainerClosePacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
