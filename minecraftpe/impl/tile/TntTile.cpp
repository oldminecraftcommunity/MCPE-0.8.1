#include <tile/TntTile.hpp>
#include <level/Level.hpp>
#include <entity/PrimedTnt.hpp>
#include <entity/Player.hpp>
#include <item/Item.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>


TntTile::TntTile(int32_t id, const std::string& name)
	: Tile(id, Material::explosive) {
	TextureAtlasTextureItem* texItem = this->getTextureItem("tnt");
	this->field_80 = *texItem->getUV(0);
	this->field_98 = *texItem->getUV(1);
	this->field_B0 = *texItem->getUV(2);
	this->field_5C = 3;
}

TntTile::~TntTile() {
}
TextureUVCoordinateSet* TntTile::getTexture(int32_t a2) {
	if(!a2) {
		return &this->field_B0;
	}
	if(a2 == 1) {
		return &this->field_98;
	}
	return &this->field_80;
}

void TntTile::destroy(Level* level, int32_t x, int32_t y, int32_t z, int32_t meta) {
	PrimedTnt* v7; // r5

	if(!level->isClientMaybe && (meta & 1) != 0) {
		v7 = new PrimedTnt(level, (float)x + 0.5, (float)y + 0.5, (float)z + 0.5);
		level->addEntity(v7);
		level->playSound(v7, "random.fuse", 1.0, 1.0);
	}
}

void TntTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t a9) {
	if(a9 > 0) {
		if(Tile::tiles[a9]->isSignalSource()) {
			if(level->hasNeighborSignal(x, y, z)) {
				this->destroy(level, x, y, z, 1);
				level->setTile(x, y, z, 0, 3);
			}
		}
	}
}
int32_t TntTile::getResourceCount(Random*) {
	return 1;
}
void TntTile::wasExploded(Level* level, int32_t x, int32_t y, int32_t z) {
	PrimedTnt* v7; // r4
	uint32_t v8;   // r6

	v7 = new PrimedTnt(level, (float)x + 0.5, (float)y + 0.5, (float)z + 0.5);
	v8 = v7->ticksUntilExplode / 4;
	v7->ticksUntilExplode = level->random.genrand_int32() % v8 + v7->ticksUntilExplode / 8;
	level->addEntity(v7);
}
bool_t TntTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	ItemInstance* item; // r0

	item = player->getSelectedItem();
	if(!item || Item::flintAndSteel != item->itemClass || !Item::flintAndSteel) {
		return Tile::use(level, x, y, z, player);
	}
	if(!player->abilities.instabuild) {
		item->hurtAndBreak(1, player);
	}
	this->destroy(level, x, y, z, 1);
	level->setTile(x, y, z, 0, 3);
	return 1;
}
