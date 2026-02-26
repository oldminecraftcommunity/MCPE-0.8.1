#include <network/packet/AddPlayerPacket.hpp>
#include <network/PacketIds.h>
#include <entity/data/DataItem.hpp>
#include <util/PacketUtil.hpp>
#include <util/output/RakDataOutput.hpp>
#include <util/input/RakDataInput.hpp>
#include <entity/Player.hpp>
#include <inventory/Inventory.hpp>
#include <network/NetEventCallback.hpp>
AddPlayerPacket::AddPlayerPacket() {
	this->data = 0;
}
AddPlayerPacket::AddPlayerPacket(const Player* a2) {
	this->clientId = a2->rakNetGUID;
	this->field_1C = a2->field_CA0;
	this->eid = a2->entityId;
	this->x = a2->posX;
	this->y = a2->posY;
	this->z = a2->posZ;
	this->pitch = a2->pitch;
	this->yaw = a2->yaw;
	this->itemId = 0;
	this->itemAuxValue = 0;
	this->data = a2->getEntityData();
	this->username = RakNet::RakString::NonVariadic(a2->username.data());
	ItemInstance* sel = a2->inventory->getSelected();
	if(sel) {
		this->itemId = sel->getId();
		this->itemAuxValue = sel->getAuxValue();
	}
}

AddPlayerPacket::~AddPlayerPacket() {
	for(int32_t i = 0; i < this->field_40.size(); ++i) {
		if(this->field_40[i]) {
			delete this->field_40[i];
		}
	}
}
void AddPlayerPacket::write(RakNet::BitStream* stream) {
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
	RakDataOutput v7;
	v7.bitStream = stream;
	this->data->packAll(&v7);
}
void AddPlayerPacket::read(RakNet::BitStream* stream) {
	stream->Read<RakNet::RakNetGUID>(this->clientId); //TODO check
	stream->Read<RakNet::RakString>(this->username);
	stream->Read<int32_t>(this->eid);
	stream->Read<float>(this->x);
	stream->Read<float>(this->y);
	stream->Read<float>(this->z);
	int8_t yaw, pitch;
	stream->Read<int8_t>(yaw);
	stream->Read<int8_t>(pitch);
	stream->Read<int16_t>(this->itemId);
	stream->Read<int16_t>(this->itemAuxValue);
	RakDataInput v7;
	v7.stream = stream;
	this->field_40 = SynchedEntityData::unpack(&v7);
	this->yaw = PacketUtil::Rot_degreesToChar(yaw); //XXX possible mcpe bug here
	this->pitch = PacketUtil::Rot_charToDegrees(pitch);

}
void AddPlayerPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
