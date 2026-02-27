#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct SetTimePacket : Packet{
	int32_t timeValue;
	bool stopTime;
	char align, align1, align2;
	SetTimePacket();
	SetTimePacket(int32_t tv, bool_t stopTime);

	virtual ~SetTimePacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
