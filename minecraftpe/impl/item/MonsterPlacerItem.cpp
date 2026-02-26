#include <item/MonsterPlacerItem.hpp>
#include <level/Level.hpp>
#include <entity/MobFactory.hpp>
#include <entity/Mob.hpp>
#include <level/MobSpawner.hpp>
#include <math/Facing.hpp>
#include <tile/Tile.hpp>
#include <entity/Player.hpp>
#include <I18n.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

MonsterPlacerItem::MonsterPlacerItem(int32_t a2)
	: Item(a2) {
	this->setStackedByData(1);
	TextureAtlasTextureItem* texItem = Item::getTextureItem("spawn_egg");
	this->field_48 = *texItem->getUV(0);
	this->field_60 = *texItem->getUV(1);
	this->field_78 = *texItem->getUV(2);
	this->field_90 = *texItem->getUV(3);
	this->maxItemdamage = 0;

}
Mob* MonsterPlacerItem::spawnMobAt(struct Level* level, int32_t type, float x, float y, float z) {
	Mob* mobb; // r0
	Mob* v12; // r4
	Mob* mob; // r0

	mobb = MobFactory::getStaticTestMob(type, level);
	if(!mobb || mobb->getCreatureBaseType() != 2) {
		return 0;
	}
	mob = MobFactory::CreateMob(type, level);
	v12 = mob;
	if(mob) {
		v12->moveTo(x, y, z, level->random.nextFloat() * 360.0, 0.0);
		MobSpawner::finalizeMobSettings(v12, level, 0.0, 0.0, 0.0);
		v12->playAmbientSound();
		level->addEntity(v12);
	}
	return v12;
}

MonsterPlacerItem::~MonsterPlacerItem() {
}
TextureUVCoordinateSet* MonsterPlacerItem::getIcon(int32_t a2, int32_t, bool_t) {
	switch(a2) {
		case 12:
			return &this->field_78;
		case 13:
			return &this->field_90;
		case 11:
			return &this->field_60;
	}
	return &this->field_48;
}
bool_t MonsterPlacerItem::useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz) {
	int32_t v14; // r0
	int32_t v15; // r10
	int32_t v16; // r9
	int32_t v17; // r8
	float v18; // s17
	int32_t meta; // r0

	if(!level->isClientMaybe) {
		v14 = level->getTile(x, y, z);
		v15 = x + Facing::STEP_X[face];
		v16 = y + Facing::STEP_Y[face];
		v17 = z + Facing::STEP_Z[face];
		if(face == 1 && v14 == Tile::fence->blockID) {
			v18 = 0.5;
		} else {
			v18 = 0.0;
		}
		meta = item->getAuxValue();
		if(MonsterPlacerItem::spawnMobAt(level, meta, (float)v15 + 0.5, (float)v16 + v18, (float)v17 + 0.5)) {
			if(!player->abilities.instabuild) {
				--item->count;
			}
		}
	}
	return 1;
}
std::string MonsterPlacerItem::getName(const ItemInstance* a3) {
	return I18n::get(this->getDescriptionId() + ".name") + " " + I18n::get(MobFactory::GetMobNameID(a3->getAuxValue())+".name"); //TODO check names
}
