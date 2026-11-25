#pragma once
#include <network/Packet.hpp>
#include <item/ItemInstance.hpp>
#include <util/PacketUtil.hpp>
#include <network/NetEventCallback.hpp>

struct DropItemPacket : Packet{
	int32_t eid;
	uint8_t motionType;
	ItemInstance itemInstance;
	DropItemPacket() {
	}
	DropItemPacket(int32_t eid, uint8_t mt, const ItemInstance& a2) :
			eid(eid), motionType(mt), itemInstance(a2) {
	}

	virtual ~DropItemPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_DROP_ITEM_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<uint8_t>(this->motionType);
		PacketUtil::writeItemInstance(this->itemInstance, stream);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->eid);
		stream->Read<uint8_t>(this->motionType);
		this->itemInstance = PacketUtil::readItemInstance(stream); //makes a copy
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
