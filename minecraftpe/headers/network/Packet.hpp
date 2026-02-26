#pragma once
#include <_types.h>
#include <BitStream.h>
#include <network/PacketIds.h>
#include <PacketPriority.h>
struct NetEventCallback;

struct Packet{
	PacketPriority packetPriorityMaybe;
	PacketReliability packetReliabilityMaybe;

	Packet();

	virtual ~Packet();
	virtual void read(RakNet::BitStream*) = 0;
	virtual void write(RakNet::BitStream*) = 0;
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*) = 0;
};
