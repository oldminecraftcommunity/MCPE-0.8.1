#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct LevelChunk;
struct ChunkDataPacket : Packet{
	int32_t xPos, zPos;
	RakNet::BitStream stream;
	LevelChunk* chunk;
	ChunkDataPacket();
	ChunkDataPacket(int32_t x, int32_t z, LevelChunk* chunk);

	virtual ~ChunkDataPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
