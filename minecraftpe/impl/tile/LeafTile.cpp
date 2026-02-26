#include <tile/LeafTile.hpp>
#include <util/Random.hpp>
#include <level/Level.hpp>
#include <entity/Player.hpp>
#include <inventory/Inventory.hpp>
#include <item/Item.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

LeafTile::LeafTile(int32_t id, const std::string& name)
	: TransparentTile(id, name, Material::leaves) {
	this->treeBlocksNearby = 0;
	TextureAtlasTextureItem* texIt = this->getTextureItem("leaves_opaque");
	TextureAtlasTextureItem* texIt2 = this->getTextureItem("leaves");
	for(int32_t i = 0; i < 4; ++i) {
		this->field_8C[i] = *texIt->getUV(i);
		this->field_14C[i] = *texIt2->getUV(i);
		this->field_EC[i] = *texIt2->getUV(i + 4);
	}

	this->field_5C = 3;
}
LeafTile::~LeafTile() {
	if(this->treeBlocksNearby) delete[] this->treeBlocksNearby;
}
TextureUVCoordinateSet* LeafTile::getTexture(int32_t a2, int32_t meta) {
	if(this->field_88) return &this->field_14C[meta & 3];
	return &this->field_8C[meta & 3];
}
TextureUVCoordinateSet* LeafTile::getCarriedTexture(int32_t a2, int32_t a3) {
	return &this->field_EC[a3 & 3];
}
bool_t LeafTile::isSolidRender() {
	return 0;
}
void LeafTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
	//TODO fix this
	int32_t v10;			   // r10
	int32_t v11;			   // r0
	int32_t v12;			   // r3
	int32_t zz;				   // r12
	int32_t* treeBlocksNearby; // r10
	int32_t* v15;			   // r11
	int32_t* v16;			   // r11
	int32_t* v17;			   // r11
	int32_t* v18;			   // r11
	int32_t* v19;			   // r11
	int32_t v20;			   // r12
	int32_t v21;			   // r6
	int32_t v22;			   // r3
	int32_t v23;			   // r2
	int32_t j;				   // r1
	int32_t i;				   // r0
	int32_t v27;			   // r0
	int32_t yy;				   // [sp+14h] [bp-44h]
	int32_t v29;			   // [sp+18h] [bp-40h]
	int32_t v30;			   // [sp+1Ch] [bp-3Ch]
	int32_t xx;				   // [sp+20h] [bp-38h]
	int32_t v32;			   // [sp+24h] [bp-34h]

	if(!level->isClientMaybe) {
		v32 = level->getData(x, y, z);
		if((v32 & 0xC) == 4) {
			if(!this->treeBlocksNearby) {
				this->treeBlocksNearby = new int[0x8000];
			}
			if(level->hasChunksAt(x - 5, y - 5, z - 5, x + 5, y + 5, z + 5)) {
				v10 = 384;
				xx = x - 4;
				do {
					for(yy = -4; yy != 5; ++yy) {
						zz = -4;
						v30 = ((yy + v10) << 7) + 2096;
						do {
							v29 = zz;
							v11 = level->getTile(xx, yy + y, zz + z);
							if(v11 == Tile::treeTrunk->blockID) {
								this->treeBlocksNearby[v30 / 4] = 0;
								// *(int*)((char*)this->treeBlocksNearby + v30) = 0;
							} else {
								if(v11 == Tile::leaves->blockID) {
									v12 = -2;
								} else {
									v12 = -1;
								}
								this->treeBlocksNearby[v30 / 4] = v12;
								// *(int*)((char*)this->treeBlocksNearby + v30) = v12;
							}
							zz = v29 + 1;
							v30 += 4;
						} while(v29 != 4);
					}
					v10 += 32;
					++xx;
				} while(v10 != 672);

				for(i = 1; i != 5; ++i) {
					for(j = 384; j != 672; j += 32) {
						v22 = 0;
						v23 = (j << 7) + 1584;
						do {
							v20 = -4;
							v21 = v23 + v22;
							do {
								treeBlocksNearby = this->treeBlocksNearby;
								if(treeBlocksNearby[v21 / 4] == i - 1) {
									if(treeBlocksNearby[(v21 - 4096) / 4] == -2) {
										treeBlocksNearby[(v21 - 4096) / 4] = i;
									}
									v15 = this->treeBlocksNearby;
									if(v15[(v21 + 4096) / 4] == -2) {
										v15[(v21 + 4096) / 4] = i;
									}
									v16 = this->treeBlocksNearby;
									if(v16[(v21 - 128) / 4] == -2) {
										v16[(v21 - 128) / 4] = i;
									}
									v17 = this->treeBlocksNearby;
									if(v17[(v21 + 128) / 4] == -2) {
										v17[(v21 + 128) / 4] = i;
									}
									v18 = this->treeBlocksNearby;
									if(v18[(v21 - 4) / 4] == -2) {
										v18[(v21 - 4) / 4] = i;
									}
									v19 = this->treeBlocksNearby;
									if(v19[(v21 + 4) / 4] == -2) {
										v19[(v21 + 4) / 4] = i;
									}
								}
								++v20;
								v21 += 4;
							} while(v20 != 5);
							v22 += 128;
						} while(v22 != 1152);
					}
				}
			}
			if(this->treeBlocksNearby[16912] < 0) {
				v27 = level->getData(x, y, z);
				this->spawnResources(level, x, y, z, v27 & 3, 0.0);
				level->setTile(x, y, z, 0, 3);
			} else {
				level->setDataNoUpdate(x, y, z, v32 & 0xFFFFFFFB);
			}
		}
	}
}
void LeafTile::onRemove(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v8;	  // r11
	int32_t meta; // r0
	int32_t zz;	  // r7
	int32_t yy;	  // r6
	int32_t xx;	  // r5
	int32_t v13;  // [sp+10h] [bp-30h]

	if(!level->isClientMaybe && level->hasChunksAt(x - 2, y - 2, z - 2, x + 2, y + 2, z + 2)) {
		for(xx = -1; xx != 2; ++xx) {
			yy = -1;
			v13 = xx + x;
			do {
				for(zz = -1; zz != 2; ++zz) {
					v8 = zz + z;
					if(level->getTile(v13, yy + y, zz + z) == Tile::leaves->blockID) {
						meta = level->getData(v13, yy + y, v8);
						level->setDataNoUpdate(v13, yy + y, v8, meta | 4);
					}
				}
				++yy;
			} while(yy != 2);
		}
	}
}
void LeafTile::onGraphicsModeChanged(bool_t a2) {
	this->field_7C = a2;
	this->field_88 = a2;
	this->goodGraphics = a2;
}
int32_t LeafTile::getResource(int32_t, Random*) {
	return Tile::sapling->blockID;
}
int32_t LeafTile::getResourceCount(Random* a2) {
	return a2->genrand_int32() % 20 == 0;
}
void LeafTile::spawnResources(Level* level, int32_t x, int32_t y, int32_t z, int32_t meta, float a7) {
	Random* p_random; // r7
	int32_t v12;	  // r0
	int32_t v13;	  // [sp+Ch] [bp-44h]
	ItemInstance v14; // [sp+14h] [bp-3Ch] BYREF

	if(!level->isClientMaybe) {
		p_random = &level->random;
		if(!(level->random.genrand_int32() % 0x14)) {
			v13 = this->getResource(meta, p_random);
			v12 = this->getSpawnResourcesAuxValue(meta);
			this->popResource(level, x, y, z, ItemInstance(v13, 1, v12));
		}
		if(!(meta << 30) && !(p_random->genrand_int32() % 0xC8)) {
			this->popResource(level, x, y, z, ItemInstance(Item::apple, 1, 0));
		}
	}
}
int32_t LeafTile::getRenderLayer() {
	return 3;
}
int32_t LeafTile::getColor(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	int32_t v5;		// r3
	int32_t result; // r0

	v5 = level->getData(x, y, z) & 3;
	if(v5 == 1) {
		return 0x619961;
	}
	result = 0x48B518;
	if(v5 == 2) {
		return 0x80A755;
	}
	return result;
}
void LeafTile::playerDestroy(Level* level, Player* player, int32_t x, int32_t y, int32_t z, int32_t a7) {
	ItemInstance* sel; // r0

	if(!level->isClientMaybe && (sel = player->inventory->getSelected()) != 0 && Item::shears == sel->itemClass && Item::shears) {
		this->popResource(level, x, y, z, ItemInstance(Tile::leaves->blockID, 1, a7 & 3));
	} else {
		Tile::playerDestroy(level, player, x, y, z, a7);
	}
}
int32_t LeafTile::getSpawnResourcesAuxValue(int32_t a2) {
	return a2 & 3;
}
