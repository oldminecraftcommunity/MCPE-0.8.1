#pragma once
#include <_types.h>
#include <BitStream.h>
#include <item/ItemInstance.hpp>

struct PacketUtil{
	static int8_t Rot_degreesToChar(float deg);
	static float Rot_charToDegrees(int8_t chr);
	static void Rot_entityToChar(const Entity*, int8_t&, int8_t&);
	static void Rot_charToEntity(Entity*, int8_t, int8_t);
	static void writeItemInstance(const ItemInstance& item, RakNet::BitStream* stream);
	static ItemInstance readItemInstance(RakNet::BitStream* stream);
};
