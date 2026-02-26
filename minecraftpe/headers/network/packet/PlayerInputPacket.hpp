#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct PlayerInputPacket : Packet{
	float moveForward, moveStrafe;
	bool isJumping, isSneaking;
	byte align, align1;
	PlayerInputPacket();
	PlayerInputPacket(float fwd, float stf, bool jmp, bool snk);

	virtual ~PlayerInputPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
