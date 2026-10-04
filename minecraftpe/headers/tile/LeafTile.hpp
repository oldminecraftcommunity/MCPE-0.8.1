#pragma once
#include <tile/TransparentTile.hpp>
#include <tile/material/Material.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <entity/Player.hpp>
#include <inventory/Inventory.hpp>

struct LeafTile : TransparentTile{
	int32_t* treeBlocksNearby;
	bool_t field_88;
	int8_t field_89, field_8A, field_8B;
	TextureUVCoordinateSet field_8C[4];
	TextureUVCoordinateSet field_EC[4];
	TextureUVCoordinateSet field_14C[4];
	int32_t field_1AC, field_1B0, field_1B4, field_1B8, field_1BC, field_1C0;

	LeafTile(int32_t id, const std::string& name) :
			TransparentTile(id, name, Material::leaves) {
		this->treeBlocksNearby = 0;
		TextureAtlasTextureItem* texIt = this->getTextureItem("leaves_opaque");
		TextureAtlasTextureItem* texIt2 = this->getTextureItem("leaves");
		for (int32_t i = 0; i < 4; ++i) {
			this->field_8C[i] = *texIt->getUV(i);
			this->field_14C[i] = *texIt2->getUV(i);
			this->field_EC[i] = *texIt2->getUV(i + 4);
		}
		this->field_5C = 3;
	}

	virtual ~LeafTile() {
		if (this->treeBlocksNearby) delete[] this->treeBlocksNearby;
	}
	virtual TextureUVCoordinateSet* getTexture(int32_t a2, int32_t meta) {
		if (this->field_88) return &this->field_14C[meta & 3];

		return &this->field_8C[meta & 3];
	}
	virtual TextureUVCoordinateSet* getCarriedTexture(int32_t a2, int32_t a3) {
		return &this->field_EC[a3 & 3];
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual void tick(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
		//TODO fix this
		int32_t* treeBlocksNearby; // r10
		int32_t* v15; // r11
		int32_t* v16; // r11
		int32_t* v17; // r11
		int32_t* v18; // r11
		int32_t* v19; // r11
		int32_t v20; // r12
		int32_t v21; // r6
		int32_t v22; // r3
		int32_t v23; // r2
		int32_t j; // r1
		int32_t i; // r0
		int32_t v27; // r0
		int32_t yy; // [sp+14h] [bp-44h]
		int32_t v29; // [sp+18h] [bp-40h]
		int32_t v30; // [sp+1Ch] [bp-3Ch]
		int32_t data; // [sp+24h] [bp-34h]
		if (!level->isClient) {
			int data = level->getData(x, y, z);
			if ((data & 0xC) == 4) {
				//taken from b1.2_02-20110517
				const int yzo = 32 * 32;
				const int co = 32 / 2;
				if (!this->treeBlocksNearby) {
					this->treeBlocksNearby = new int[32 * 32 * 32];
					//mojang forgot to fill this array with zeros?
					//for(int i = 0; i < 32 * 32 * 32; ++i) this->treeBlocksNearby[i] = 0;
				}
				if (level->hasChunksAt(x - 5, y - 5, z - 5, x + 5, y + 5, z + 5)) {
					for (int xx = -4; xx <= 4; ++xx) {
						for (int yy = -4; yy <= 4; ++yy) {
							for (int zz = -4; zz <= 4; ++zz) {
								int tile = level->getTile(x + xx, y + yy, z + zz);
								if (tile == Tile::treeTrunk->blockID) this->treeBlocksNearby[((xx + co) * yzo) + ((yy + co) * 32) + zz + co] = 0;
								else if (tile == Tile::leaves->blockID) this->treeBlocksNearby[((xx + co) * yzo) + ((yy + co) * 32) + zz + co] = -2;
								else this->treeBlocksNearby[((xx + co) * yzo) + ((yy + co) * 32) + zz + co] = -1;
							}
						}
					}
					for (int type = 1; type <= 4; ++type) {
						for (int xx = -4; xx <= 4; ++xx) {
							for (int yy = -4; yy <= 4; ++yy) {
								for (int zz = -4; zz <= 4; ++zz) {
									if (this->treeBlocksNearby[((xx + co) * yzo) + ((yy + co) * 32) + zz + co] == type - 1) {
										if (this->treeBlocksNearby[(((xx + co) - 1) * yzo) + ((yy + co) * 32) + zz + co] == -2) {
											this->treeBlocksNearby[(((xx + co) - 1) * yzo) + ((yy + co) * 32) + zz + co] = type;
										}
										if (this->treeBlocksNearby[(((xx + co) + 1) * yzo) + ((yy + co) * 32) + zz + co] == -2) {
											this->treeBlocksNearby[(((xx + co) + 1) * yzo) + ((yy + co) * 32) + zz + co] = type;
										}
										if (this->treeBlocksNearby[((xx + co) * yzo) + (((yy + co) - 1) * 32) + zz + co] == -2) {
											this->treeBlocksNearby[((xx + co) * yzo) + (((yy + co) - 1) * 32) + zz + co] = type;
										}
										if (this->treeBlocksNearby[((xx + co) * yzo) + (((yy + co) + 1) * 32) + zz + co] == -2) {
											this->treeBlocksNearby[((xx + co) * yzo) + (((yy + co) + 1) * 32) + zz + co] = type;
										}
										if (this->treeBlocksNearby[((xx + co) * yzo) + ((yy + co) * 32) + ((zz + co) - 1)] == -2) {
											this->treeBlocksNearby[((xx + co) * yzo) + ((yy + co) * 32) + ((zz + co) - 1)] = type;
										}
										if (this->treeBlocksNearby[((xx + co) * yzo) + ((yy + co) * 32) + ((zz + co) + 1)] == -2) {
											this->treeBlocksNearby[((xx + co) * yzo) + ((yy + co) * 32) + ((zz + co) + 1)] = type;
										}
									}
								}
							}
						}
					}
				}
				if (this->treeBlocksNearby[(co * yzo) + (co * 32) + co] < 0) {
					//call this->die ?
					v27 = level->getData(x, y, z);
					this->spawnResources(level, x, y, z, v27 & 3, 0.0);
					level->setTile(x, y, z, 0, 3);
				} else {
					level->setDataNoUpdate(x, y, z, data & 0xFFFFFFFB);
				}
			}
		}
	}
	virtual void onRemove(Level* level, int32_t x, int32_t y, int32_t z) {
		int32_t v8; // r11
		int32_t meta; // r0
		int32_t zz; // r7
		int32_t yy; // r6
		int32_t xx; // r5
		int32_t v13; // [sp+10h] [bp-30h]
		if (!level->isClient && level->hasChunksAt(x - 2, y - 2, z - 2, x + 2, y + 2, z + 2)) {
			for (xx = -1; xx != 2; ++xx) {
				yy = -1;
				v13 = xx + x;
				do {
					for (zz = -1; zz != 2; ++zz) {
						v8 = zz + z;
						if (level->getTile(v13, yy + y, zz + z) == Tile::leaves->blockID) {
							meta = level->getData(v13, yy + y, v8);
							level->setDataNoUpdate(v13, yy + y, v8, meta | 4);
						}
					}
					++yy;
				} while (yy != 2);
			}
		}
	}
	virtual void onGraphicsModeChanged(bool_t a2) {
		this->field_7C = a2;
		this->field_88 = a2;
		this->goodGraphics = a2;
	}
	virtual int32_t getResource(int32_t, Random*) {
		return Tile::sapling->blockID;
	}
	virtual int32_t getResourceCount(Random* a2) {
		return a2->genrand_int32() % 20 == 0;
	}
	virtual void spawnResources(Level* level, int32_t x, int32_t y, int32_t z, int32_t meta, float a7) {
		Random* p_random; // r7
		int32_t v12; // r0
		int32_t v13; // [sp+Ch] [bp-44h]
		ItemInstance v14; // [sp+14h] [bp-3Ch] BYREF
		if (!level->isClient) {
			p_random = &level->random;
			if (!(level->random.genrand_int32() % 0x14)) {
				v13 = this->getResource(meta, p_random);
				v12 = this->getSpawnResourcesAuxValue(meta);
				this->popResource(level, x, y, z, ItemInstance(v13, 1, v12));
			}
			if (!(meta << 30) && (p_random->genrand_int32() % 0xC8) == 0) {
				this->popResource(level, x, y, z, ItemInstance(Item::apple, 1, 0));
			}
		}
	}
	virtual int32_t getRenderLayer() {
		return 3;
	}
	virtual int32_t getColor(LevelSource* level, int32_t x, int32_t y, int32_t z) {
		int32_t v5; // r3
		int32_t result; // r0
		v5 = level->getData(x, y, z) & 3;
		if (v5 == 1) {
			return 0x619961;
		}
		result = 0x48B518;
		if (v5 == 2) {
			return 0x80A755;
		}
		return result;
	}
	virtual void playerDestroy(Level* level, Player* player, int32_t x, int32_t y, int32_t z, int32_t a7) {
		ItemInstance* sel; // r0
		if (!level->isClient && (sel = player->inventory->getSelected()) != 0 && Item::shears == sel->itemClass && Item::shears) {
			this->popResource(level, x, y, z, ItemInstance(Tile::leaves->blockID, 1, a7 & 3));
		} else {
			Tile::playerDestroy(level, player, x, y, z, a7);
		}
	}
	virtual int32_t getSpawnResourcesAuxValue(int32_t a2) {
		return a2 & 3;
	}
};
