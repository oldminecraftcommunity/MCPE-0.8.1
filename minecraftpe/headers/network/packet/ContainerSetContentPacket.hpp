#pragma once
#include <network/Packet.hpp>
#include <vector>
#include <util/PacketUtil.hpp>
#include <network/NetEventCallback.hpp>

struct ItemInstance;
struct ContainerSetContentPacket: Packet
{
	uint8_t field_C, field_D, field_E, field_F;
	std::vector<ItemInstance> field_10;
	std::vector<int32_t> field_1C;
	ContainerSetContentPacket() {
	}
	ContainerSetContentPacket(int32_t a2, const std::vector<ItemInstance>& a3, int32_t a4) {
		this->field_C = a2;
		this->field_10 = a3;
	}
	virtual ~ContainerSetContentPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_CONTAINER_SET_CONTENT_PACKET);
		stream->Write<uint8_t>(this->field_C);
		int16_t v10 = this->field_10.size();
		stream->Write<int16_t>(v10);
		for (int32_t i = 0; i < this->field_10.size(); ++i) {
			PacketUtil::writeItemInstance(this->field_10[i], stream);
		}
		v10 = this->field_1C.size();
		stream->Write<int16_t>(v10);
		for (int& i : this->field_1C) {
			stream->Write<int32_t>(i);
		}
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<uint8_t>(this->field_C);
		int16_t v7;
		stream->Read<int16_t>(v7);
		for (int32_t i = 0; i < v7; ++i) {
			this->field_10.push_back(PacketUtil::readItemInstance(stream));
		}
		int16_t v8;
		stream->Read<int16_t>(v8);
		for (int32_t i = 0; i < v8; ++i) {
			int32_t v9;
			stream->Read<int32_t>(v9);
			this->field_1C.push_back(v9);
		}
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
