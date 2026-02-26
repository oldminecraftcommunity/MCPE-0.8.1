#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct ContainerOpenPacket : Packet{
	uint8_t field_C;
	uint8_t containerId;
	uint8_t field_E, field_F;
	int32_t x, y, z;
	ContainerOpenPacket();
	ContainerOpenPacket(uint8_t c, uint8_t cid, uint8_t e, int32_t x, int32_t y, int32_t z);

	virtual ~ContainerOpenPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
