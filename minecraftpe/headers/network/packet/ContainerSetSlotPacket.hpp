#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <item/ItemInstance.hpp>

struct ContainerSetSlotPacket : Packet{
	int8_t field_C, field_D;
	int16_t field_E;
	ItemInstance field_10;

	ContainerSetSlotPacket();
	ContainerSetSlotPacket(int8_t c, int8_t d, int16_t e, const ItemInstance& f10);
	virtual ~ContainerSetSlotPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
