#pragma once
#include <network/Packet.hpp>
#include <util/output/RakDataOutput.hpp>
#include <util/input/RakDataInput.hpp>
#include <entity/data/DataItem.hpp>
#include <entity/data/SynchedEntityData.hpp>
#include <util/PacketUtil.hpp>
#include <entity/Mob.hpp>
#include <network/NetEventCallback.hpp>
#include <vector>
struct Mob;
struct DataItem;
struct SynchedEntityData;
struct AddMobPacket : Packet{
	int32_t eid;
	int32_t type;
	float x, y, z;
	float yaw, pitch;
	std::vector<DataItem*> readData;
	SynchedEntityData* synchedData;
	AddMobPacket() {
		this->synchedData = 0;
	}
	AddMobPacket(Mob* a2) {
		this->eid = a2->entityId;
		this->type = a2->getEntityTypeId();
		this->x = a2->posX;
		this->y = a2->posY;
		this->z = a2->posZ;
		this->yaw = a2->pitch;
		this->pitch = a2->yaw;
		this->synchedData = a2->getEntityData();
	}

	virtual ~AddMobPacket() {
		int32_t v2 = 0;
		while(1) {
			if(v2 >= this->readData.size()) break;
			DataItem* v3 = this->readData[v2];
			if(v3) delete v3;
			++v2;
		}
	}
	virtual void write(RakNet::BitStream* stream) {
		SynchedEntityData* synchedData;
		int8_t p;
		RakDataOutput input;

		stream->Write<uint8_t>(PID_ADD_MOB_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<int32_t>(this->type);
		stream->Write<float>(this->x);
		stream->Write<float>(this->y);
		stream->Write<float>(this->z);
		p = PacketUtil::Rot_degreesToChar(this->pitch);
		stream->Write<int8_t>(p);
		p = PacketUtil::Rot_degreesToChar(this->yaw);
		stream->Write<int8_t>(p);
		synchedData = this->synchedData;
		input.bitStream = stream;
		synchedData->packAll(&input);
	}
	virtual void read(RakNet::BitStream* stream) {
		int32_t v4;
		char v5, v6;
		char rotDegC;
		RakDataInput input;

		stream->Read<int32_t>(this->eid);
		stream->Read<int32_t>(this->type);
		stream->Read<float>(this->x);
		stream->Read<float>(this->y);
		stream->Read<float>(this->z);
		stream->Read<char>(rotDegC);
		stream->Read<char>(v6);
		input.stream = stream;
		this->readData = SynchedEntityData::unpack(&input);
		this->pitch = PacketUtil::Rot_degreesToChar((float)rotDegC);
		v5 = v6;
		this->yaw = PacketUtil::Rot_charToDegrees(v5);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
		a3->handle(a2, this);
	}
};
