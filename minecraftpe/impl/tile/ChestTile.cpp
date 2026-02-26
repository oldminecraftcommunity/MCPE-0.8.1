#include <tile/ChestTile.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>
#include <tile/entity/ChestTileEntity.hpp>
#include <entity/ItemEntity.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

ChestTile::ChestTile(int32_t id)
	: EntityTile(id, Material::wood) {
	this->setShape(0.025, 0.0, 0.025, 0.975, 0.95, 0.975);
	TextureAtlasTextureItem* texItem = this->getTextureItem("chest_inventory");
	this->field_A50 = *texItem->getUV(0);
	this->field_A68 = *texItem->getUV(1);
	this->field_A80 = *texItem->getUV(2);
}

ChestTile::~ChestTile() {
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
int32_t ChestTile::getTileEntityType() {
	return 2;
}
void ChestTile::onRemove(Level* level, int32_t x, int32_t y, int32_t z) {
	ChestTileEntity* te; // r0
	ChestTileEntity* v8; // r6
	int32_t n;			 // r7
	ItemInstance* v10;	 // r9
	float v11;			 // s14
	float v12;			 // s22
	float v13;			 // s14
	float v14;			 // s23
	float v15;			 // s14
	int32_t v16;		 // r1
	int32_t count;		 // r8
	Item* itemClass;	 // r1
	int32_t auxValue;	 // r0
	ItemEntity* v20;	 // r8
	Item* v21;			 // [sp+Ch] [bp-74h]

	te = (ChestTileEntity*)level->getTileEntity(x, y, z);
	v8 = te;
	if(te) {
		if(te->type == 2) {
			te->unpair();
			n = 0;
			if(!level->isClientMaybe) {
				while(n < v8->getContainerSize()) {
					v10 = (ItemInstance*)v8->getItem(n);
					if(v10) {
						v11 = this->random.nextFloat();
						v12 = (float)(v11 * 0.8) + 0.1;
						v13 = this->random.nextFloat();
						v14 = (float)(v13 * 0.8) + 0.1;
						v15 = this->random.nextFloat();
						while(v10->count > 0) {
							v16 = this->random.genrand_int32() % 0x15 + 10;
							if(v16 >= v10->count) {
								count = v10->count;
							} else {
								count = v16;
							}
							itemClass = v10->itemClass;
							v10->count -= count;
							v21 = itemClass;
							auxValue = v10->getAuxValue();
							v20 = new ItemEntity(level, (float)x + v12, (float)y + v14, (float)z + (float)((float)(v15 * 0.8) + 0.1), ItemInstance(v21, count, auxValue));
							v20->motionX = this->random.nextGaussian() * 0.05;
							v20->motionY = (float)(this->random.nextGaussian() * 0.05) + 0.2;
							v20->motionZ = this->random.nextGaussian() * 0.05;
							level->addEntity(v20);
						}
					}
					++n;
				}
			}
		}
	}
	EntityTile::onRemove(level, x, y, z);
}
bool_t ChestTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	TileEntity* te = level->getTileEntity(x, y, z);
	if(te->isType(2)) {
		if(!level->isClientMaybe) {
			if(((ChestTileEntity*)te)->canOpen()) {
				((ChestTileEntity*)te)->openBy(player);
			}
		}
	}
	return 1;
}
int32_t ChestTile::getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, struct Mob* a10, int32_t a11) {
	float v11 = ((a10->yaw * 4) / 360.0) + 0.5;
	int32_t v12 = (int32_t)v11;
	if(v11 < (float)(int32_t)v11) v12 = v12 - 1;
	switch(v12 & 3) {
		case 0:
			return a11 | 2;
		case 1:
			return a11 | 5;
		case 2:
			return a11 | 3;
	}
	return a11 | 4;
}
