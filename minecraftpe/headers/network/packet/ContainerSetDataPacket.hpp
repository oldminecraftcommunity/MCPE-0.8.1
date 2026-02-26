#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct ContainerSetDataPacket : Packet{
	int16_t field_C, field_E;
	uint8_t field_10, field_11, field_12, field_13;
	ContainerSetDataPacket();
	ContainerSetDataPacket(int16_t c, int16_t e, uint8_t f10);
	virtual ~ContainerSetDataPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
