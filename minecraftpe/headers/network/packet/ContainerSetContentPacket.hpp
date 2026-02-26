#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <vector>

struct ItemInstance;
struct ContainerSetContentPacket: Packet
{
	uint8_t field_C, field_D, field_E, field_F;
	std::vector<ItemInstance> field_10;
	std::vector<int32_t> field_1C;
	ContainerSetContentPacket();
	ContainerSetContentPacket(int32_t, const std::vector<ItemInstance>&, int32_t);
	virtual ~ContainerSetContentPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
