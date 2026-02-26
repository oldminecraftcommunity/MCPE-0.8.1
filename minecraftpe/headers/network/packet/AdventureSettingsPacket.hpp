#pragma once
#include <_types.h>
#include <network/Packet.hpp>

struct AdventureSettingsPacket: Packet
{
	enum Flags {
		AS_ALLOW_INTERACT = 0x1,
		AS_ENABLE_PVP = 0x2,
		AS_ENABLE_PVE = 0x4,
		AS_FIELD_3 = 0x8,
		AS_NO_DAYLIGHT_CYCLE = 0x10,
		AS_FIELD_5 = 0x20
	};

	int32_t flags;

	//TODO constructor
	AdventureSettingsPacket();
	void set(AdventureSettingsPacket::Flags, bool_t);

	virtual ~AdventureSettingsPacket();
	virtual void write(RakNet::BitStream*);
	virtual void read(RakNet::BitStream*);
	virtual void handle(const RakNet::RakNetGUID&, NetEventCallback*);
};
