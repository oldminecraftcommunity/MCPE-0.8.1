#pragma once
#include <network/Packet.hpp>
#include <vector>
#include <util/output/RakDataOutput.hpp>
#include <util/input/RakDataInput.hpp>
#include <entity/data/SynchedEntityData.hpp>
#include <network/NetEventCallback.hpp>

struct DataItem;
struct SetEntityDataPacket : Packet{
	int32_t entityId;
	bool needsMemoryFreeing;
	std::vector<DataItem*> data;

	SetEntityDataPacket() {
		this->needsMemoryFreeing = 0;
	}
	SetEntityDataPacket(int32_t entityId, bool f10, std::vector<DataItem*> data) :
		entityId(entityId), needsMemoryFreeing(f10), data(data){
	}
	virtual ~SetEntityDataPacket() {
		if (this->needsMemoryFreeing) {
			for (int i = 0; i < this->data.size(); ++i) {
				if (this->data[i]) {
					delete this->data[i];
				}
			}
		}
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_SET_ENTITY_DATA_PACKET);
		stream->Write<int32_t>(this->entityId);
		RakDataOutput v5(stream);
		SynchedEntityData::pack(&this->data, &v5);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->entityId);
		RakDataInput v4;
		v4.stream = stream;
		this->data = SynchedEntityData::unpack(&v4);
		this->needsMemoryFreeing = 1;
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
