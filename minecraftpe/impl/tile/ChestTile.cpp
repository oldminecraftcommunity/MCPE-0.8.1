#include <tile/ChestTile.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>
#include <tile/entity/ChestTileEntity.hpp>
#include <entity/ItemEntity.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>
#include <math/Mth.hpp>

ChestTile::ChestTile(int32_t id)
	: EntityTile(id, Material::wood) {
	this->setShape(0.025, 0.0, 0.025, 0.975, 0.95, 0.975);
	TextureAtlasTextureItem* texItem = this->getTextureItem("chest_inventory");
	this->field_A50 = *texItem->getUV(0);
	this->field_A68 = *texItem->getUV(1);
	this->field_A80 = *texItem->getUV(2);
}

bool_t ChestTile::isCubeShaped() {
	return 0;
}
int32_t ChestTile::getRenderShape() {
	return 22;
}
TextureUVCoordinateSet* ChestTile::getTexture(int32_t a2) {
	if((uint32_t)a2 <= 1) return &this->field_A50;
	if(a2 == 3) return &this->field_A80;
	return &this->field_A68;
}
TextureUVCoordinateSet* ChestTile::getTexture(LevelSource* ls, int32_t x, int32_t y, int32_t z, int32_t a6) {
	if((uint32_t)a6 <= 1) return &this->field_A50;
	if(a6 == ls->getData(x, y, z)) return &this->field_A80;
	return &this->field_A68;
}
bool_t ChestTile::isSolidRender() {
	return 0;
}
void ChestTile::onRemove(Level* level, int32_t x, int32_t y, int32_t z) {
	TileEntity* te = (ChestTileEntity*)level->getTileEntity(x, y, z);
	if(te && te->type == 2) {
		ChestTileEntity* chest = (ChestTileEntity*)te;
		chest->unpair();
		if(!level->isClient) {
			for(int n = 0; n < chest->getContainerSize(); ++n) {
				ItemInstance* it = chest->getItem(n);
				if(it) {
					float xo = this->random.nextFloat() * 0.8f + 0.1f;
					float yo = this->random.nextFloat() * 0.8f + 0.1f;
					float zo = this->random.nextFloat() * 0.8f + 0.1f;
					while(it->count > 0) {
						int v16 = this->random.nextInt(21) + 10;
						int count = v16 < it->count ? v16 : it->count;
						it->count -= count;

						ItemEntity* e = new ItemEntity(level,
							x + xo,
							y + yo,
							z + zo,
							ItemInstance(it->itemClass, count, it->getAuxValue())
						);
						e->motionX = this->random.nextGaussian() * 0.05f;
						e->motionY = this->random.nextGaussian() * 0.05f + 0.2f;
						e->motionZ = this->random.nextGaussian() * 0.05f;
						level->addEntity(e);
					}
				}
			}
		}
	}
	EntityTile::onRemove(level, x, y, z);
}
bool_t ChestTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	TileEntity* te = level->getTileEntity(x, y, z);
	if(te->isType(2)) {
		if(!level->isClient) {
			if(((ChestTileEntity*)te)->canOpen()) {
				((ChestTileEntity*)te)->openBy(player);
			}
		}
	}
	return 1;
}
int32_t ChestTile::getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, struct Mob* a10, int32_t a11) {
	float dir = ((a10->yaw * 4) / 360.0f) + 0.5f;
	int32_t v12 = Mth::floor(dir) & 3;
	if(v12 == 0) return a11 | 2;
	if(v12 == 1) return a11 | 5;
	if(v12 == 2) return a11 | 3;
	return a11 | 4;
}
