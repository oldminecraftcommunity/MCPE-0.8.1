#include <item/CameraItem.hpp>
#include <level/Level.hpp>
#include <entity/TripodCamera.hpp>
#include <entity/Player.hpp>

CameraItem::CameraItem(int32_t id)
	: Item(id) {
}
CameraItem::~CameraItem() {
}
ItemInstance* CameraItem::use(ItemInstance* a2, Level* a3, Player* a4) {
	a3->addEntity(new TripodCamera(a3, a4, a4->posX, a4->posY, a4->posZ));
	return a2;
}
