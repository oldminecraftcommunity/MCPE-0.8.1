#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>
#include <entity/Entity.hpp>

struct SetEntityLinkPacket : Packet{
	int32_t typeMaybe, rider, riding;

	SetEntityLinkPacket(int32_t type, Entity* rider, Entity* riding) {
		this->typeMaybe = type;
		this->rider = rider ? rider->entityId : 0;
		this->riding = riding ? riding->entityId : 0;
	}
	SetEntityLinkPacket() {
	}

	virtual ~SetEntityLinkPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_SET_ENTITY_LINK_PACKET);
		stream->Write<int32_t>(this->rider);
		stream->Write<int32_t>(this->riding);
		stream->Write<int32_t>(this->typeMaybe);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->rider);
		stream->Read<int32_t>(this->riding);
		stream->Read<int32_t>(this->typeMaybe);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
