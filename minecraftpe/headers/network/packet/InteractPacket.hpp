#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct InteractPacket : Packet{
	uint8_t action;
	int32_t eid, type;
	InteractPacket(int32_t eid, int32_t type, uint8_t action) {
		this->eid = eid;
		this->type = type;
		this->action = action;
	}
	InteractPacket() {
	}
	virtual ~InteractPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_INTERACT_PACKET);
		stream->Write<uint8_t>(this->action);
		stream->Write<int32_t>(this->eid);
		stream->Write<int32_t>(this->type);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<uint8_t>(this->action);
		stream->Read<int32_t>(this->eid);
		stream->Read<int32_t>(this->type);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
