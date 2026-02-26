#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct ContainerAckPacket : Packet{
	int16_t field_C;
	uint8_t field_E;
	bool field_F;
	ContainerAckPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
