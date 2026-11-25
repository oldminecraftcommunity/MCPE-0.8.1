#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct ContainerClosePacket : Packet{
	uint8_t containerId;

	ContainerClosePacket() {
	}
	ContainerClosePacket(int id) : containerId(id) {
	}
	virtual ~ContainerClosePacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_CONTAINER_CLOSE_PACKET);
		stream->Write<uint8_t>(this->containerId);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<uint8_t>(this->containerId);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
