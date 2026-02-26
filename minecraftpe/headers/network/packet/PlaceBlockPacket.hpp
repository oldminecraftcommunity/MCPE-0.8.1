#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct PlaceBlockPacket : Packet{
	int32_t field_C;
	int32_t field_10;
	int32_t field_14;
	uint8_t field_18;
	uint8_t field_19;
	uint8_t field_1A;
	uint8_t field_1B;

	PlaceBlockPacket();

	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
