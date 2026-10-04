#include <item/DyePowderItem.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>
#include <entity/Sheep.hpp>
#include <I18n.hpp>
const int DyePowderItem::COLOR_RGB[] = {
	0x1E1B1B, 0xB3312C, 0x3B511A, 0x51301A, 0x253192, 0x7B2FBE, 0x287697, 0x287697,
	0x434343, 0xD88198, 0x41CD34, 0xDECF2A, 0x6689D3, 0xC354CD, 0xEB8844, 0xF0F0F0
};
std::string DyePowderItem::COLOR_DESCS[] = {"black", "red", "green", "brown", "blue", "purple", "cyan", "silver", "gray", "pink", "lime", "yellow", "lightBlue", "magenta", "orange", "white"};

DyePowderItem::DyePowderItem(int32_t a2)
	: Item(a2)
	, field_48() {
	this->setStackedByData(1);
	this->setMaxDamage(0);
	this->field_48 = *this->getTextureItem("dye_powder");
}

const TextureUVCoordinateSet* DyePowderItem::getIcon(int32_t a2, int32_t, bool_t) const{
	if(a2 > 0b1111) a2 = 0b1111; //usat(4, v);
	return this->field_48.getUV(a2);
}
bool_t DyePowderItem::useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz) {
	Tile* result; // r0

	if(item->getAuxValue() != 15 || level->isClient) {
		return 0;
	}
	if(!player->abilities.instabuild) {
		--item->count;
	}
	result = Tile::tiles[level->getTile(x, y, z)];
	if(result) {
		return result->onFertilized(level, x, y, z);
	}
	return 0;
}
void DyePowderItem::interactEnemy(ItemInstance* a2, Mob* a3, Player* a4) {
	int8_t meta; // r7
	int32_t v9; // r7

	if(a3->getEntityTypeId() == 13) {
		meta = a2->getAuxValue();
		if(!((Sheep*)a3)->isSheared()) {
			v9 = ~meta & 0xF;
			if(((Sheep*)a3)->getColor() != v9) {
				((Sheep*)a3)->setColor(v9);
				if(a4) {
					if(!a4->abilities.instabuild) {
						--a2->count;
					}
				}
			}
		}
	}
}
std::string DyePowderItem::getName(const ItemInstance* a2) const{
	int32_t meta = a2->getAuxValue();
	int32_t v6 = meta & ~(meta >> 31);
	int32_t v7;
	if(v6 >= 15) {
		v7 = 15;
	} else {
		v7 = v6;
	}
	return I18n::get(Item::getDescriptionId() + "." + DyePowderItem::COLOR_DESCS[v7] + ".name");
}
std::string DyePowderItem::getDescriptionId(const ItemInstance* a2) const{
	int32_t meta = a2->getAuxValue();
	int32_t v6 = meta & ~(meta >> 31);
	int32_t v7;
	if(v6 >= 15) {
		v7 = 15;
	} else {
		v7 = v6;
	}
	return Item::getDescriptionId() + "." + DyePowderItem::COLOR_DESCS[v7];
}
