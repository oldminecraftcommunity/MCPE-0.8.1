#pragma once
#include <_types.h>

struct Packet;
struct MinecraftPackets
{
	static Packet* createPacket(int32_t pid);
};
