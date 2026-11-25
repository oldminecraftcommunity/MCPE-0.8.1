#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <item/ItemInstance.hpp>
#include <util/PacketUtil.hpp>
#include <network/NetEventCallback.hpp>

struct ContainerSetSlotPacket : Packet{
	int8_t field_C, field_D;
	int16_t slot;
	ItemInstance field_10;

	ContainerSetSlotPacket() {
	}
	ContainerSetSlotPacket(int8_t c, int8_t d, int16_t slot, const ItemInstance& f10) :
			field_C(c), field_D(d), slot(slot), field_10(f10) {
	}
	virtual ~ContainerSetSlotPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_CONTAINER_SET_SLOT_PACKET);
		stream->Write<int8_t>(this->field_D);
		stream->Write<int16_t>(this->slot);
		PacketUtil::writeItemInstance(this->field_10, stream);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int8_t>(this->field_D);
		stream->Read<int16_t>(this->slot);
		this->field_10 = PacketUtil::readItemInstance(stream);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
