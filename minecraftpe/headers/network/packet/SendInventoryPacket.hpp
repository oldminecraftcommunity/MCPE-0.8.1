#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <vector>
struct ItemInstance;
struct SendInventoryPacket : Packet{
	int32_t field_C;
	std::vector<ItemInstance> items;
	int16_t field_1C;
	uint8_t field_1E;
	int8_t field_1F;
	SendInventoryPacket();
	virtual ~SendInventoryPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
