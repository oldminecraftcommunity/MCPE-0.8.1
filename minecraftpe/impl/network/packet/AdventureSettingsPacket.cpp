#include <network/packet/AdventureSettingsPacket.hpp>
#include <network/PacketIds.h>
#include <network/NetEventCallback.hpp>
AdventureSettingsPacket::AdventureSettingsPacket(){

}
void AdventureSettingsPacket::set(AdventureSettingsPacket::Flags a2, bool_t a3) {
	int32_t flags; // r3
	int32_t v4; // r3

	flags = this->flags;
	if(a3) {
		v4 = flags | a2;
	} else {
		v4 = flags & ~a2;
	}
	this->flags = v4;
}

AdventureSettingsPacket::~AdventureSettingsPacket() {
}
void AdventureSettingsPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_ADVENTURE_SETTINGS_PACKET);
	stream->Write<int32_t>(this->flags);

}
void AdventureSettingsPacket::read(RakNet::BitStream* stream) {
	stream->Read<int32_t>(this->flags);
}
void AdventureSettingsPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
