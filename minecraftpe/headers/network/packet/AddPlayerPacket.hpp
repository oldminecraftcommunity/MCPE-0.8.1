#pragma once
#include <network/Packet.hpp>
#include <vector>
#include <entity/Player.hpp>
#include <inventory/Inventory.hpp>
#include <entity/data/DataItem.hpp>
#include <util/PacketUtil.hpp>
#include <util/output/RakDataOutput.hpp>
#include <util/input/RakDataInput.hpp>
#include <network/NetEventCallback.hpp>

struct DataItem;
struct AddPlayerPacket : Packet{
	int32_t field_C;
	RakNet::RakNetGUID clientId;
	RakNet::RakString username;
	int32_t eid;
	float x, y, z, pitch, yaw;
	int16_t itemId, itemAuxValue;
	std::vector<DataItem*> entityData;
	const struct SynchedEntityData* dataToSend;

	AddPlayerPacket() {
		this->dataToSend = 0;
	}
	AddPlayerPacket(const Player* a2) : clientId(a2->rakNetGUID) {
		this->eid = a2->entityId;
		this->x = a2->posX;
		this->y = a2->posY - a2->ridingHeight;
		this->z = a2->posZ;
		this->pitch = a2->pitch;
		this->yaw = a2->yaw;
		this->itemId = 0;
		this->itemAuxValue = 0;
		this->dataToSend = a2->getEntityData();
		this->username = RakNet::RakString::NonVariadic(a2->username.data());
		ItemInstance* sel = a2->inventory->getSelected();
		if(sel) {
			this->itemId = sel->getId();
			this->itemAuxValue = sel->getAuxValue();
		}
	}

	virtual ~AddPlayerPacket() {
		for(int32_t i = 0; i < this->entityData.size(); ++i) {
			if(this->entityData[i]) {
				delete this->entityData[i];
			}
		}
	}

	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_ADD_PLAYER_PACKET);
		stream->Write<RakNet::RakNetGUID>(this->clientId); //TODO check
		this->username.Serialize(stream);
		stream->Write<int32_t>(this->eid);
		stream->Write<float>(this->x);
		stream->Write<float>(this->y);
		stream->Write<float>(this->z);
		stream->Write<int8_t>(PacketUtil::Rot_degreesToChar(this->yaw));
		stream->Write<int8_t>(PacketUtil::Rot_degreesToChar(this->pitch));
		stream->Write<int16_t>(this->itemId);
		stream->Write<int16_t>(this->itemAuxValue);
		RakDataOutput v7(stream);
		this->dataToSend->packAll(&v7);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<RakNet::RakNetGUID>(this->clientId); //TODO check
		stream->Read<RakNet::RakString>(this->username);
		stream->Read<int32_t>(this->eid);
		stream->Read<float>(this->x);
		stream->Read<float>(this->y);
		stream->Read<float>(this->z);
		char yaw, pitch;
		stream->Read<char>(yaw);
		stream->Read<char>(pitch);
		stream->Read<int16_t>(this->itemId);
		stream->Read<int16_t>(this->itemAuxValue);
		RakDataInput v7;
		v7.stream = stream;
		this->entityData = SynchedEntityData::unpack(&v7);
		this->yaw = PacketUtil::Rot_degreesToChar(yaw); //XXX possible mcpe bug here
		this->pitch = PacketUtil::Rot_charToDegrees(pitch);

	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
