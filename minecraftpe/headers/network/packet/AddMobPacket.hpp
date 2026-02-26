#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <vector>
struct Mob;
struct DataItem;
struct SynchedEntityData;
struct AddMobPacket : Packet{
	int32_t eid;
	int32_t type;
	float x, y, z;
	float yaw, pitch;
	std::vector<DataItem*> readData;
	SynchedEntityData* synchedData;
	AddMobPacket();
	AddMobPacket(Mob*);

	virtual ~AddMobPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
