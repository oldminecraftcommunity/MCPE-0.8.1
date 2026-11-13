#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct RemovePlayerPacket : Packet{
	int32_t eid;
	RakNet::RakNetGUID clientId;
	RemovePlayerPacket(int32_t eid, const RakNet::RakNetGUID& cid) :
		eid(eid), clientId(cid) {
	}
	RemovePlayerPacket() {
	}
	virtual ~RemovePlayerPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_REMOVE_PLAYER_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<RakNet::RakNetGUID>(this->clientId);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->eid);
		stream->Read<RakNet::RakNetGUID>(this->clientId);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
