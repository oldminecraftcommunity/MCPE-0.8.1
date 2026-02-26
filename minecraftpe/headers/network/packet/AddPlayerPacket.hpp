#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <vector>
struct Player;
struct DataItem;
struct AddPlayerPacket : Packet{
	int32_t field_C;
	RakNet::RakNetGUID clientId;
	int32_t field_1C;
	RakNet::RakString username;
	int32_t eid;
	float x, y, z, pitch, yaw;
	int16_t itemId, itemAuxValue;
	std::vector<DataItem*> field_40;
	const struct SynchedEntityData* data;
	AddPlayerPacket();
	AddPlayerPacket(const Player*);

	virtual ~AddPlayerPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
