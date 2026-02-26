#pragma once
#include <_types.h>
#include <network/packet/MoveEntityPacket.hpp>
#include <entity/Entity.hpp>

struct MoveEntityPacket_PosRot : MoveEntityPacket{
	MoveEntityPacket_PosRot();
	MoveEntityPacket_PosRot(Entity* e); //always inlined?

	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
};
