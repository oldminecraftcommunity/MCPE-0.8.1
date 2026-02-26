#include <item/ShearsItem.hpp>
#include <tile/Tile.hpp>

ShearsItem::ShearsItem(int32_t id)
	: Item(id) {
	this->setMaxStackSize(1);
	this->setMaxDamage(238);
}
ShearsItem::~ShearsItem() {
}
float ShearsItem::getDestroySpeed(ItemInstance* a2, Tile* a3){
	int32_t blockID; // r4

	blockID = a3->blockID;
	if ( blockID == Tile::web->blockID || blockID == Tile::leaves->blockID )
	{
		return 15.0;
	}
	if ( blockID == Tile::cloth->blockID )
	{
		return 5.0;
	}
	return Item::getDestroySpeed(a2, a3);
}
bool_t ShearsItem::canDestroySpecial(const Tile* a2) {
	return a2->blockID == Tile::web->blockID;
}
bool_t ShearsItem::mineBlock(ItemInstance* a2, int32_t id, int32_t a4, int32_t a5, int32_t a6, Mob* a7) {
	if(id != Tile::leaves->blockID && id != Tile::web->blockID) {
		return Item::mineBlock(a2, id, a4, a5, a6, a7);
	}
	a2->hurtAndBreak(1, a7);
	return 1;
}
