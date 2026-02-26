#include <network/packet/PlayerInputPacket.hpp>
#include <_types.h>
#include <network/NetEventCallback.hpp>
PlayerInputPacket::PlayerInputPacket(){}
PlayerInputPacket::PlayerInputPacket(float fwd, float stf, bool jmp, bool snk) {
	this->moveForward = fwd;
	this->moveStrafe = stf;
	this->isJumping = jmp;
	this->isSneaking = snk;
}

PlayerInputPacket::~PlayerInputPacket() {
}

void PlayerInputPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}

void PlayerInputPacket::read(RakNet::BitStream* stream) {
	stream->Read<float>(this->moveForward);
	stream->Read<float>(this->moveStrafe);
	stream->Read<bool>(this->isJumping);
	stream->Read<bool>(this->isSneaking);
}

void PlayerInputPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_PLAYER_INPUT_PACKET);
	stream->Write<float>(this->moveForward);
	stream->Write<float>(this->moveStrafe);
	stream->Write<bool>(this->isJumping);
	stream->Write<bool>(this->isSneaking);
}
