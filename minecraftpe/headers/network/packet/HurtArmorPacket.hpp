#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct HurtArmorPacket : Packet{
	int8_t health;
	byte align1, align2, align3;

	HurtArmorPacket(int8_t);
	HurtArmorPacket();
	virtual ~HurtArmorPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
