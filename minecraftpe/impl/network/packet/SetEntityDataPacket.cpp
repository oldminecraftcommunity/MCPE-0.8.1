#include <network/packet/SetEntityDataPacket.hpp>
#include <network/PacketIds.h>
#include <util/output/RakDataOutput.hpp>
#include <util/input/RakDataInput.hpp>
#include <entity/data/SynchedEntityData.hpp>
#include <network/NetEventCallback.hpp>

SetEntityDataPacket::SetEntityDataPacket() {
	this->field_10 = 0;
}
SetEntityDataPacket::SetEntityDataPacket(int32_t entityId, int8_t f10, std::vector<DataItem*> data) {
	this->entityId = entityId;
	this->field_10 = f10;
	this->data = data;
}
SetEntityDataPacket::~SetEntityDataPacket() {
}
void SetEntityDataPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_SET_ENTITY_DATA_PACKET);
	stream->Write<int32_t>(this->entityId);
	RakDataOutput v5;
	v5.bitStream = stream;
	SynchedEntityData::pack(&this->data, &v5);
}
void SetEntityDataPacket::read(RakNet::BitStream* stream) {
	stream->Read<int32_t>(this->entityId);
	RakDataInput v4;
	v4.stream = stream;
	this->data = SynchedEntityData::unpack(&v4);
	this->field_10 = 1;
}
void SetEntityDataPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
