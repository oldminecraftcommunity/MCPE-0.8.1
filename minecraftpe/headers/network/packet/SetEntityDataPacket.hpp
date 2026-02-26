#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <vector>

struct DataItem;
struct SetEntityDataPacket : Packet{
	int32_t entityId;
	int8_t field_10, field_11, field_12, field_13;
	std::vector<DataItem*> data;

	SetEntityDataPacket();
	SetEntityDataPacket(int32_t entityId, int8_t f10, std::vector<DataItem*> data); //inlined
	virtual ~SetEntityDataPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
