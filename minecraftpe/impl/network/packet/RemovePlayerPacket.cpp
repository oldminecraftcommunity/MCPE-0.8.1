#include <_types.h>
#include <network/packet/RemovePlayerPacket.hpp>
#include <network/NetEventCallback.hpp>
RemovePlayerPacket::RemovePlayerPacket(){

}
RemovePlayerPacket::RemovePlayerPacket(int32_t eid, RakNet::RakNetGUID cid) : clientId(cid){
	this->eid = eid;
}
RemovePlayerPacket::~RemovePlayerPacket() {
}
void RemovePlayerPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
	a3->handle(a2, this);
}

void RemovePlayerPacket::read(RakNet::BitStream* stream){
	stream->Read<int32_t>(this->eid);
	stream->Read<RakNet::RakNetGUID>(this->clientId);
}

void RemovePlayerPacket::write(RakNet::BitStream* stream){
	stream->Write<uint8_t>(PID_REMOVE_PLAYER_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<RakNet::RakNetGUID>(this->clientId);
}
