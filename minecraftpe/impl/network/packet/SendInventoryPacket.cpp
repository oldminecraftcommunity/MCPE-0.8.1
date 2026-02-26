#include <network/packet/SendInventoryPacket.hpp>
#include <network/PacketIds.h>
#include <util/PacketUtil.hpp>
#include <network/NetEventCallback.hpp>
SendInventoryPacket::SendInventoryPacket() {
}
SendInventoryPacket::~SendInventoryPacket() {
}
void SendInventoryPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_SEND_INVENTORY_PACKET);
	stream->Write<int32_t>(this->field_C);
	stream->Write<uint8_t>(this->field_1E);
	stream->Write<int16_t>(this->field_1C);
	int32_t v5 = 0;
	while(v5 < this->field_1C) {
		PacketUtil::writeItemInstance(this->items[v5], stream);
		++v5;
	}
	for(int32_t i = 0; i != 4; ++i) {
		PacketUtil::writeItemInstance(this->items[i + this->field_1C], stream);
	}
}
void SendInventoryPacket::read(RakNet::BitStream* stream) {
	stream->Read<int32_t>(this->field_C);
	stream->Read<uint8_t>(this->field_1E);
	stream->Read<int16_t>(this->field_1C);
	int32_t v5 = 0;
	while(this->field_1C + 3 >= v5) {
		this->items.emplace_back(PacketUtil::readItemInstance(stream));
		++v5;
	}
}
void SendInventoryPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
