#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct AnimatePacket : Packet{
	int32_t eid;
	int8_t action;

	AnimatePacket() {
	}

	AnimatePacket(int32_t eid, int32_t action) {
		this->eid = eid;
		this->action = action;
	}
	virtual ~AnimatePacket() {
	}

	virtual void write(RakNet::BitStream* stream){
		stream->Write<uint8_t>(PID_ANIMATE_PACKET);
		stream->Write<int8_t>(this->action);
		stream->Write<int32_t>(this->eid);
	}
	virtual void read(RakNet::BitStream* stream){
		stream->Read<int8_t>(this->action);
		stream->Read<int32_t>(this->eid);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
