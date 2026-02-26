#include <_types.h>
#include <util/PacketUtil.hpp>
#include <item/ItemInstance.hpp>
#include <entity/Entity.hpp>

ItemInstance PacketUtil::readItemInstance(RakNet::BitStream* stream){
	int8_t v5;
	int16_t v6, v7;

	stream->Read<int16_t>(v6);
	stream->Read<int8_t>(v5);
	stream->Read<int16_t>(v7);
	ItemInstance v8(v6, v5, v7);
	if(v8.isValid) return ItemInstance(v8);
	return ItemInstance((bool_t)0);
}

void PacketUtil::writeItemInstance(const ItemInstance& item, RakNet::BitStream* stream){
	int16_t id = item.getId();
	int8_t count = item.count;
	int16_t aux = item.getAuxValue();
	stream->Write<int16_t>(id);
	stream->Write<uint8_t>(count);
	stream->Write<int16_t>(aux);
}

int8_t PacketUtil::Rot_degreesToChar(float deg){
	return (int8_t) ((deg/360) * 256);
}
float PacketUtil::Rot_charToDegrees(int8_t chr){
	return ((float)chr/256.0f)*360.0f; //uses vcvts_n_f32_s32
}
void PacketUtil::Rot_entityToChar(const Entity* a1, int8_t& a2, int8_t& a3) {
	a3 = PacketUtil::Rot_degreesToChar(a1->pitch);
	a2 = PacketUtil::Rot_degreesToChar(a1->yaw);
}
void PacketUtil::Rot_charToEntity(Entity* a1, int8_t a2, int8_t a3) {
	a1->prevPitch = a1->pitch = PacketUtil::Rot_charToDegrees(a3);
	a1->prevYaw = a1->yaw = PacketUtil::Rot_charToDegrees(a2);

}
