#include <network/packet/MovePlayerPacket.hpp>
#include <_types.h>
#include <network/NetEventCallback.hpp>

MovePlayerPacket::MovePlayerPacket(){

}
MovePlayerPacket::MovePlayerPacket(int32_t eid, float x, float y, float z, float p, float yaw, float byaw) {
	this->eid = eid;
	this->x = x;
	this->y = y;
	this->z = z;
	this->pitch = p;
	this->yaw = yaw;
	this->bodyYaw = byaw;
}

MovePlayerPacket::~MovePlayerPacket() {
}

void MovePlayerPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}

void MovePlayerPacket::read(RakNet::BitStream* stream) {
	stream->Read<int32_t>(this->eid);
	stream->Read<float>(this->x);
	stream->Read<float>(this->y);
	stream->Read<float>(this->z);
	stream->Read<float>(this->yaw);
	stream->Read<float>(this->pitch);
	stream->Read<float>(this->bodyYaw);
}

void MovePlayerPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_MOVE_PLAYER_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<float>(this->x);
	stream->Write<float>(this->y);
	stream->Write<float>(this->z);
	stream->Write<float>(this->yaw);
	stream->Write<float>(this->pitch);
	stream->Write<float>(this->bodyYaw);
}
