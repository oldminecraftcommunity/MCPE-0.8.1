#include <network/packet/DropItemPacket.hpp>
#include <network/PacketIds.h>
#include <util/PacketUtil.hpp>
#include <network/NetEventCallback.hpp>

DropItemPacket::DropItemPacket() {
}

DropItemPacket::DropItemPacket(int32_t eid, uint8_t mt, const ItemInstance& a2)
	: itemInstance(a2) {
	this->eid = eid;
	this->motionType = mt;
}

DropItemPacket::~DropItemPacket() {
}
void DropItemPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_DROP_ITEM_PACKET);
	stream->Write<int32_t>(this->eid);
	stream->Write<uint8_t>(this->motionType);
	PacketUtil::writeItemInstance(this->itemInstance, stream);
}
void DropItemPacket::read(RakNet::BitStream* stream) {
	stream->Read<int32_t>(this->eid);
	stream->Read<uint8_t>(this->motionType);
	this->itemInstance = PacketUtil::readItemInstance(stream); //makes a copy
}
void DropItemPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
