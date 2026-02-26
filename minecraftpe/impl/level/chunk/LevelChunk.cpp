#include <level/chunk/LevelChunk.hpp>
#include <string.h>
#include <entity/Entity.hpp>
#include <level/Level.hpp>
#include <tile/entity/TileEntity.hpp>
#include <tile/Tile.hpp>
#include <tile/EntityTile.hpp>
#include <level/LightLayer.hpp>
#include <math/Mth.hpp>
#include <level/dimension/Dimension.hpp>
#include <algorithm>

bool_t LevelChunk::touchedSky = 0;

LevelChunk::LevelChunk(struct Level* a2, int32_t a3, int32_t a4)
	: tileMeta(32768)
	, skyLight(32768)
	, blockLight(32768) {
	this->level = a2;
	this->field_4 = 32768;
	this->field_258 = 1;
	this->chunkX = a3;
	this->chunkZ = a4;
	this->chunkXworld = a3 * 16;
	this->chunkZworld = a4 * 16;
	this->tiles = new uint8_t[0x8000];
	memset(this->tiles, 0, 0x8000);
	this->init();
}
LevelChunk::LevelChunk(struct Level* a2, uint8_t* a3, int32_t x, int32_t z)
	: tileMeta(32768)
	, skyLight(32768)
	, blockLight(32768) {
	this->level = a2;
	this->chunkX = x;
	this->chunkZ = z;
	this->chunkXworld = 16 * x;
	this->chunkZworld = 16 * z;
	this->tiles = a3;
	this->field_258 = 0;
	this->init();
}
void LevelChunk::addTileEntity(struct TileEntity* a2) {
	int32_t posX = a2->posX;
	int32_t posZ = a2->posZ;
	int32_t czw = this->chunkZworld;
	this->setTileEntity(posX - this->chunkXworld, a2->posY, posZ - czw, a2);
	if(this->loaded) {
		this->level->tileEntities.emplace_back(a2);
	}
}
void LevelChunk::clearUpdateMap() {
	memset(this->updateMap, 0, sizeof(this->updateMap));
	this->unsaved = 0;
}
void LevelChunk::deleteBlockData() {
	if(this->tiles) delete[] this->tiles;
}
struct TileEntity* LevelChunk::getTileEntity(int32_t x, int32_t y, int32_t z) {
	TilePos xyz{x, y, z};
	auto te = this->tileEntities.find(xyz);
	TileEntity* tent;
	if(te != this->tileEntities.end()) {
		tent = te->second;
	} else {
		int32_t tile = this->getTile(x, y, z);
		if(tile <= 0 || !Tile::isEntityTile[tile]) return 0;
		tent = ((EntityTile*)Tile::tiles[tile])->newTileEntity();
		this->level->setTileEntity(this->chunkXworld + x, y, z + this->chunkZworld, tent);
	}
	if(tent && tent->isRemoved()) return 0;
	return tent;
}

std::unordered_map<TilePos, struct TileEntity*>* LevelChunk::getTileEntityMap() {
	return &this->tileEntities;
}
bool_t LevelChunk::hasTileEntityAt(struct TileEntity* ent) {
	TilePos xyz{ent->posX & 0xf, ent->posY, ent->posZ & 0xf};
	return this->tileEntities.find(xyz) != this->tileEntities.end();
}

bool_t LevelChunk::hasTileEntityAt(int32_t x, int32_t y, int32_t z) {
	TilePos xyz{x, y, z};
	return this->tileEntities.find(xyz) != this->tileEntities.end();
}
void LevelChunk::init() {
	this->decorated = 0;
	this->field_24A = 0;
	this->unsaved = 0;
	this->field_24C = 0;
	this->field_24B = 0;
	this->field_250 = 0;
	memset(this->heightMap, 0, sizeof(this->heightMap));
	memset(this->updateMap, 0, sizeof(this->updateMap));
}
void LevelChunk::lightGap(int32_t x, int32_t z, int32_t a4) {
	int32_t hm = this->level->getHeightmap(x, z);
	if(hm <= a4) {
		if(hm < a4) this->level->updateLight(LightLayer::Sky, x, hm, z, x, a4, z);
	} else {
		this->level->updateLight(LightLayer::Sky, x, a4, z, x, hm, z);
	}
}
void LevelChunk::lightGaps(int32_t x, int32_t z) {
	int32_t v6 = this->getHeightmap(x, z);
	int32_t v7 = x + this->chunkXworld;
	int32_t v8 = z + this->chunkZworld;
	this->lightGap(v7 - 1, v8, v6);
	this->lightGap(v7 + 1, v8, v6);
	this->lightGap(v7, v8 - 1, v6);
	this->lightGap(v7, v8 + 1, v6);
}
void LevelChunk::recalcHeight(int32_t x, int32_t y, int32_t z) {
	int32_t xzIndex;		   // r11
	int32_t hm;				   // r8
	int32_t v8;				   // r1
	int32_t v9;				   // r4
	int32_t v11;			   // r10
	int32_t v12;			   // r0
	int32_t i;				   // r3
	int32_t v14;			   // r0
	int32_t v15;			   // r1
	int32_t v16;			   // r2
	int32_t v17;			   // r11
	DataLayer* p_skyLight; // r12
	int32_t v19;			   // r8
	int32_t v20;			   // r3
	DataLayer* v21;		   // [sp+14h] [bp-34h]
	int32_t a5;				   // [sp+18h] [bp-30h]
	int32_t v23;			   // [sp+1Ch] [bp-2Ch]

	xzIndex = x | (16 * z);
	hm = this->heightMap[xzIndex];
	v8 = (x << 11) | (z << 7);
	if(hm < y) {
		v9 = y;
	} else {
		v9 = this->heightMap[xzIndex];
	}
	while(v9 > 0 && !Tile::lightBlock[this->tiles[v9 - 1 + v8]]) {
		--v9;
	}
	v23 = v9;
	if(v9 != hm) {
		v11 = x + this->chunkXworld;
		a5 = z + this->chunkZworld;
		this->level->lightColumnChanged(v11, a5, v9, hm);
		this->heightMap[xzIndex] = v9;
		if(v9 >= this->topBlockY) {
			v16 = 0;
			v15 = 127;
			do {
				for(i = 0; i != 16; ++i) {
					v12 = v16 | (16 * i);
					v14 = this->heightMap[v12];
					if(v15 >= v14) {
						v15 = v14;
					}
				}
				++v16;
			} while(v16 != 16);
			this->topBlockY = v15;
		} else {
			this->topBlockY = v9;
		}
		if(v9 >= hm) {
			this->level->updateLight(LightLayer::Sky, v11, hm, a5, v11, v9, a5);
			while(hm < v9) {
				this->skyLight.set(x, hm++, z, 0);
			}
		} else {
			v17 = v9;
			p_skyLight = &this->skyLight;
			while(v17 < hm) {
				v21 = p_skyLight;
				p_skyLight->set(x, v17, z, 15);
				p_skyLight = v21;
				++v17;
			}
		}
		v19 = 15;
		while(v9 > 0) {
			if(!v19) {
				while(v9 > 0 && !Tile::lightBlock[this->getTile(x, v9 - 1, z)]) {
					--v9;
				}
				break;
			}
			v20 = Tile::lightBlock[this->getTile(x, --v9, z)];
			if(!v20) {
				v20 = 1;
			}
			v19 = (v19 - v20) & ~((v19 - v20) >> 31);
			this->skyLight.set(x, v9, z, v19);
		}
		if(v9 != v23) {
			this->level->updateLight(LightLayer::Sky, v11 - 1, v9, a5 - 1, v11 + 1, v23, a5 + 1);
		}
	}
}
void LevelChunk::removeTileEntity(int32_t x, int32_t y, int32_t z) {
	if(this->loaded) {
		TilePos v7{x, y, z};
		auto v5 = this->tileEntities.find(v7);
		if(v5 != this->tileEntities.end()) {
			v5->second->setRemoved();
			this->tileEntities.erase(v5);
		}
	}
}
void LevelChunk::setTileEntity(int32_t x, int32_t y, int32_t z, struct TileEntity* tile) {
	tile->setLevelAndPos(this->level, x + this->chunkXworld, y, z + this->chunkZworld);
	int32_t t = this->getTile(x, y, z);
	if(t) {
		if(Tile::isEntityTile[t]) {
			tile->clearRemoved();
			TilePos v16{x, y, z};
			this->tileEntities[v16] = tile; //TODO check
		}
	}
}
void LevelChunk::setTileRaw(int32_t x, int32_t y, int32_t z, int32_t id) {
	int32_t in = y | (x << 11) | (z << 7);
	this->tiles[in] = id;
}


LevelChunk::~LevelChunk() {
	if(this->field_258) delete this->tiles;
}
bool_t LevelChunk::isAt(int32_t x, int32_t z) {
	return x == this->chunkX && z == this->chunkZ;
}
int32_t LevelChunk::getHeightmap(int32_t x, int32_t z) {
	return this->heightMap[x | (16 * z)];
}
void LevelChunk::recalcHeightmap() {
	int32_t v2 = 0;
	int32_t v3 = 127;
	do {
		for(int32_t i = 0; i != 16; ++i) {
			int32_t v4 = 127;
			int32_t v5 = (v2 << 11) | (i << 7);
			do {
				if(Tile::lightBlock[this->tiles[v5 - 1 + v4]]) break;
				--v4;
			} while(v4);
			this->heightMap[v2 | (16 * i)] = v4;
			if(!this->level->dimensionPtr->hasNoSkyMaybe) {
				int32_t v8 = 127;
				int32_t v6 = 15;
				do {
					v6 -= Tile::lightBlock[this->tiles[v8 + v5]];
					if(v6 > 0) {
						this->skyLight.set(v2, v8, i, v6);
					}
					--v8;
				} while(v8 && v6 > 0);
			}
			if(v3 >= v4) v3 = v4;
		}
		++v2;
	} while(v2 != 16);
	this->topBlockY = v3;
	for(int32_t j = 0; j != 16; ++j) {
		for(int32_t k = 0; k != 16; ++k) {
			this->lightGaps(j, k);
		}
	}
}
void LevelChunk::recalcHeightmapOnly() {
	int32_t v1 = 0;
	int32_t v2 = 127;
	do {
		for(int32_t i = 0; i != 16; ++i) {
			int32_t v4 = 127;
			do {
				if(Tile::lightBlock[this->tiles[((v1 << 11) | (i << 7)) - 1 + v4]]) --v4;
			} while(v4);
			int32_t v6 = v1 | (16 * i);
			if(v2 >= v4) v2 = v4;
			this->heightMap[v6] = v4;
		}
		++v1;
	} while(v1 != 16);
	this->topBlockY = v2;
}
int32_t LevelChunk::getBrightness(const LightLayer& a2, int32_t x, int32_t y, int32_t z) {
	if(&a2 == &LightLayer::Sky) {
		return this->skyLight.get(x, y, z);
	}
	if(&a2 == &LightLayer::Block) {
		return this->blockLight.get(x, y, z);
	}
	return 0;
}
void LevelChunk::setBrightness(const struct LightLayer& a2, int32_t x, int32_t y, int32_t z, int32_t ll) {
	if(&a2 == &LightLayer::Sky) {
		this->skyLight.set(x, y, z, ll);
	}
	if(&a2 == &LightLayer::Block) {
		this->blockLight.set(x, y, z, ll);
	}
}
int32_t LevelChunk::getRawBrightness(int32_t x, int32_t y, int32_t z, int32_t a5) {
	int32_t v9 = this->skyLight.get(x, y, z);
	if(v9 > 0) LevelChunk::touchedSky = 1;
	int32_t v10 = v9 - a5;
	int32_t res = this->blockLight.get(x, y, z);
	if(res < v10) return v10;
	return res;
}
void LevelChunk::addEntity(struct Entity* a2) {
	this->field_24C = 1;
	float v2 = a2->posY * 0.0625;
	int32_t v5 = Mth::floor(v2);
	if(v5 < 0) v5 = 0;
	else if(v5 >= 7) v5 = 7;
	a2->field_FD = 1;
	a2->field_30 = v5;
	a2->field_2C = this->chunkX;
	a2->field_34 = this->chunkZ;
	this->miniChunkEntities[v5].push_back(a2);
}
void LevelChunk::removeEntity(struct Entity* a2) {
	this->removeEntity(a2, a2->field_30);
}
void LevelChunk::removeEntity(struct Entity* a2, int32_t a3) {
	if(a3 < 0) a3 = 0;
	if(a3 >= 7) a3 = 7;

	auto e = std::find(this->miniChunkEntities[a3].begin(), this->miniChunkEntities[a3].end(), a2);
	if(e != this->miniChunkEntities[a3].end()) {
		this->miniChunkEntities[a3].erase(e);
	}
}
void LevelChunk::getEntitiesOfClass(int32_t a2, const struct AABB& a3, std::vector<struct Entity*>& a4) {
	int32_t minChunkY = Mth::floor((a3.minY - 2) * 0.0625);
	int32_t maxChunkY = Mth::floor((a3.maxY + 2) * 0.0625);
	if(minChunkY > 0b111) minChunkY = 0b111; //usat(3, v);
	else if(minChunkY < 0) minChunkY = 0;
	if(maxChunkY > 0b111) maxChunkY = 0b111; //usat(3, v);
	else if(minChunkY < 0) minChunkY = 0;

	while(minChunkY <= maxChunkY) {
		for(auto e: this->miniChunkEntities[minChunkY]) {
			if(e->getCreatureBaseType() == a2) {
				a4.push_back(e);
			}
		}
		++minChunkY;
	}
}
void LevelChunk::getEntitiesOfType(int32_t a2, const struct AABB& a3, std::vector<struct Entity*>& a4) {
	int32_t minChunkY = Mth::floor((a3.minY - 2) * 0.0625);
	int32_t maxChunkY = Mth::floor((a3.maxY + 2) * 0.0625);
	if(minChunkY > 0b111) minChunkY = 0b111; //usat(3, v);
	else if(minChunkY < 0) minChunkY = 0;
	if(maxChunkY > 0b111) maxChunkY = 0b111; //usat(3, v);
	else if(minChunkY < 0) minChunkY = 0;

	while(minChunkY <= maxChunkY) {
		for(auto e: this->miniChunkEntities[minChunkY]) {
			if(e->getEntityTypeId() == a2) {
				a4.push_back(e);
			}
		}
		++minChunkY;
	}
}

bool_t LevelChunk::isSkyLit(int32_t a2, int32_t a3, int32_t a4) {
	return a3 >= this->heightMap[a2 | 16 * a4];
}
void LevelChunk::lightLava() {
}
void LevelChunk::recalcBlockLights() {
}
void LevelChunk::skyBrightnessChanged() {
}
void LevelChunk::load() {
	this->loaded = 1;
}
void LevelChunk::unload() {
	this->loaded = 0;
}
bool_t LevelChunk::shouldSave(bool_t a2) {
	return !this->field_24A && this->unsaved;
}
void LevelChunk::markUnsaved() {
	this->unsaved = 1;
}
int32_t LevelChunk::countEntities() {
	int32_t v1 = 0;
	int32_t entCnt = 0;
	do {
		entCnt += this->miniChunkEntities[v1].size();
		++v1;
	} while(v1 != 8);
	return entCnt;
}
void LevelChunk::getEntities(struct Entity* a2, const struct AABB& bb, std::vector<struct Entity*>& a4) {
	int32_t minChunkY = Mth::floor((bb.minY - 2) * 0.0625);
	int32_t maxChunkY = Mth::floor((bb.maxY + 2) * 0.0625);
	minChunkY = minChunkY & ~(minChunkY >> 31);
	if(maxChunkY >= 7) maxChunkY = 7;

	while(minChunkY <= maxChunkY) {
		for(auto e: this->miniChunkEntities[minChunkY]) {
			if(e != a2 && bb.maxX > e->boundingBox.minX && bb.minX < e->boundingBox.maxX && bb.maxY > e->boundingBox.minY && bb.minY < e->boundingBox.maxY && bb.maxZ > e->boundingBox.minZ && bb.minZ < e->boundingBox.maxZ) {
				a4.push_back(e);
			}
		}

		++minChunkY;
	}
}
int32_t LevelChunk::getTile(int32_t x, int32_t y, int32_t z) {
	return this->tiles[y | (x << 11) | (z << 7)];
}
bool_t LevelChunk::setTile(int32_t x, int32_t y, int32_t z, int32_t id) {
	int32_t v21 = x | (16 * z);
	int32_t v10 = y | (x << 11) | (z << 7);
	int32_t v22 = this->heightMap[v21];
	int32_t oldID = this->tiles[v10];
	if(oldID == id) return 0;
	int32_t worldX = x + this->chunkXworld;
	int32_t worldZ = z + this->chunkZworld;
	this->tiles[v10] = id;
	if(oldID) Tile::tiles[oldID]->onRemove(this->level, worldX, y, worldZ);
	this->tileMeta.set(x, y, z, 0);
	if(Tile::lightBlock[id]) {
		if(y >= v22) {
			this->recalcHeight(x, y + 1, z);
		}
	} else if(y == v22 - 1) {
		this->recalcHeight(x, y, z);
	}
	this->level->updateLight(LightLayer::Sky, worldX, y, worldZ, worldX, y, worldZ);
	this->level->updateLight(LightLayer::Block, worldX, y, worldZ, worldX, y, worldZ);
	if(id) {
		if(!this->level->isClientMaybe) Tile::tiles[id]->onPlace(this->level, worldX, y, worldZ);
	}
	this->unsaved = 1;
	this->updateMap[v21] |= 1 << (y >> 4);
	return 1;
}
bool_t LevelChunk::setTileAndData(int32_t x, int32_t y, int32_t z, int32_t id, int32_t meta) {
	int32_t v22 = x | (16 * z);
	int32_t v23 = this->heightMap[v22];
	int32_t v9 = y | (x << 11) | (z << 7);
	int32_t oldid = this->tiles[v9];
	if(oldid == id) {
		int32_t m = this->tileMeta.get(x, y, z);
		if(m == meta) return 0;
	}
	int32_t v18 = this->chunkXworld + x;
	int32_t v19 = this->chunkZworld + z;
	this->tiles[v9] = id;
	if(oldid) {
		Tile::tiles[oldid]->onRemove(this->level, v18, y, v19);
		if(this->level->isClientMaybe && oldid != id && Tile::isEntityTile[oldid]) {
			this->level->removeTileEntity(v18, y, v19);
		}
	}
	this->tileMeta.set(x, y, z, meta);
	if(!this->level->dimensionPtr->hasNoSkyMaybe) {
		if(Tile::lightBlock[id]) {
			if(y >= v23) {
				this->recalcHeight(x, y + 1, z);
			}
		} else {
			this->recalcHeight(x, y, z);
		}
		this->level->updateLight(LightLayer::Sky, v18, y, v19, v18, y, v19);
	}
	this->level->updateLight(LightLayer::Block, v18, y, v19, v18, y, v19);
	this->lightGaps(x, z);
	if(id) {
		if(!this->level->isClientMaybe) {
			Tile::tiles[id]->onPlace(this->level, v18, y, v19);
		}
	}
	this->unsaved = 1;
	this->updateMap[v22] |= 1 << (y >> 4);
	return 1;
}

int32_t LevelChunk::getData(int32_t x, int32_t y, int32_t z) {
	return this->tileMeta.get(x, y, z);
}
bool_t LevelChunk::setData(int32_t x, int32_t y, int32_t z, int32_t d) {
	this->unsaved = 1;
	if(this->tileMeta.get(x, y, z) == d) return 0;
	this->tileMeta.set(x, y, z, d);
	return 1;
}
void LevelChunk::setBlocks(uint8_t* data, int32_t y) {
	for(int32_t i = 0; i != 8192; ++i) {
		this->tiles[8192 * y + i] = data[i];
	}
	int32_t v5 = 4 * y;
	int32_t v6 = 4 * y;
	int32_t v7 = 4 * (y + 1);
	while(v6 < v7) {
		for(int32_t j = 0; j != 16; ++j) {
			this->recalcHeight(v6, 0, j);
		}
		++v6;
	}
	this->level->updateLight(LightLayer::Sky, v5 + this->chunkXworld, 0, this->chunkZworld, v5 + this->chunkXworld + 4, 128, this->chunkZworld + 16);
	this->level->updateLight(LightLayer::Block, v5 + this->chunkXworld, 0, this->chunkZworld, v5 + this->chunkXworld + 4, 128, this->chunkZworld + 16);
	this->level->setTilesDirty(v5 + this->chunkXworld, 0, this->chunkZworld, v5 + this->chunkXworld + 4, 128, this->chunkZworld);
}
int32_t LevelChunk::getBlocksAndData(uint8_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	int32_t v9; // r7
	int32_t v12; // r10
	int32_t v13; // r5
	int32_t v15; // r11
	int32_t v16; // r1
	int32_t v17; // r9
	int32_t v18; // r12
	int32_t v19; // r3
	int32_t v20; // r10
	int32_t v21; // r5
	int32_t i; // r11
	int32_t v23; // r1
	int32_t v24; // r9
	int32_t v25; // r12
	int32_t v26; // r3
	int32_t j; // r10
	int32_t v28; // r1
	int32_t v29; // r9
	int32_t v30; // r12
	int32_t v31; // r3
	int32_t v32; // r1
	int32_t v33; // r9
	int32_t v34; // r3
	int32_t v35; // r10
	int32_t v37; // [sp+0h] [bp-38h]
	int32_t v38; // [sp+0h] [bp-38h]
	int32_t v39; // [sp+0h] [bp-38h]
	int32_t v40; // [sp+0h] [bp-38h]
	int32_t v41; // [sp+4h] [bp-34h]
	int32_t v42; // [sp+4h] [bp-34h]
	int32_t v43; // [sp+4h] [bp-34h]

	v9 = a3;
	v12 = a3;
	v13 = a7 - a4;
	if(a8 < a5) {
		v15 = 0;
	} else {
		v15 = a8 - a5;
	}
	while(1) {
		v19 = a9;
		if(v12 >= a6) {
			break;
		}
		v18 = a4 | (v12 << 11);
		v17 = a5;
		while(v17 < a8) {
			v16 = v18 | (v17++ << 7);
			v37 = v19;
			v41 = v18;
			memcpy(&a2[v19], &this->tiles[v16], v13);
			v18 = v41;
			v19 = v37 + v13;
		}
		++v12;
		a9 += v15 * v13;
	}
	v20 = v9;
	v21 = v13 / 2;
	for(i = v15 * v21;; a9 += i) {
		v26 = a9;
		if(v20 >= a6) {
			break;
		}
		v25 = a4 | (v20 << 11);
		v24 = a5;
		while(v24 < a8) {
			v23 = v25 | (v24++ << 7);
			v38 = v26;
			v42 = v25;
			memcpy(&a2[v26], &this->tileMeta.data[v23 >> 1], v21);
			v25 = v42;
			v26 = v38 + v21;
		}
		++v20;
	}
	for(j = v9;; ++j) {
		v31 = a9;
		if(j >= a6) {
			break;
		}
		v30 = a4 | (j << 11);
		v29 = a5;
		while(v29 < a8) {
			v28 = v30 | (v29++ << 7);
			v39 = v31;
			v43 = v30;
			memcpy(&a2[v31], &this->blockLight.data[v28 >> 1], v21);
			v30 = v43;
			v31 = v39 + v21;
		}
		a9 += i;
	}
	while(1) {
		v35 = a9;
		if(v9 >= a6) {
			break;
		}
		v34 = a4 | (v9 << 11);
		v33 = a5;
		while(v33 < a8) {
			v32 = v34 | (v33++ << 7);
			v40 = v34;
			memcpy(&a2[v35], &this->skyLight.data[v32 >> 1], v21);
			v34 = v40;
			v35 += v21;
		}
		++v9;
		a9 += i;
	}
	return a9;
}

int32_t LevelChunk::setBlocksAndData(uint8_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	int32_t v9; // r10
	int32_t v12; // r6
	int32_t v14; // r9
	int32_t i; // r12
	int32_t v16; // r0
	int32_t v17; // r8
	int32_t v18; // r3
	int32_t v19; // r11
	int32_t v20; // r6
	int32_t v21; // r10
	int32_t j; // r9
	int32_t v23; // r0
	int32_t v24; // r8
	int32_t v25; // r3
	int32_t v26; // r11
	int32_t k; // r9
	int32_t v28; // r0
	int32_t v29; // r8
	int32_t v30; // r3
	int32_t v31; // r11
	int32_t m; // r9
	int32_t v33; // r0
	int32_t v34; // r8
	int32_t v35; // r3
	int32_t v36; // r11
	int32_t v37; // [sp+0h] [bp-38h]
	int32_t v38; // [sp+0h] [bp-38h]
	int32_t v39; // [sp+0h] [bp-38h]
	int32_t v40; // [sp+0h] [bp-38h]
	int32_t v41; // [sp+4h] [bp-34h]

	v12 = a7 - a4;
	if(a8 >= a5) {
		v9 = a8 - a5;
	}
	v14 = a3;
	if(a8 < a5) {
		v9 = 0;
	}
	for(i = v9 * v12;; a9 += i) {
		v19 = a9;
		if(v14 >= a6) {
			break;
		}
		v18 = a4 | (v14 << 11);
		v17 = a5;
		while(v17 < a8) {
			v16 = v18 | (v17 << 7);
			v37 = v18;
			v41 = i;
			++v17;
			memcpy(&this->tiles[v16], &a2[v19], v12);
			v18 = v37;
			i = v41;
			v19 += v12;
		}
		++v14;
	}
	v20 = v12 / 2;
	this->recalcHeightmapOnly();
	v21 = v9 * v20;
	for(j = a3;; ++j) {
		v26 = a9;
		if(j >= a6) {
			break;
		}
		v25 = a4 | (j << 11);
		v24 = a5;
		while(v24 < a8) {
			v23 = v25 | (v24 << 7);
			v38 = v25;
			++v24;
			memcpy(&this->tileMeta.data[v23 >> 1], &a2[v26], v20);
			v25 = v38;
			v26 += v20;
		}
		a9 += v21;
	}
	for(k = a3;; ++k) {
		v31 = a9;
		if(k >= a6) {
			break;
		}
		v30 = a4 | (k << 11);
		v29 = a5;
		while(v29 < a8) {
			v28 = v30 | (v29 << 7);
			v39 = v30;
			++v29;
			memcpy(&this->blockLight.data[v28 >> 1], &a2[v31], v20);
			v30 = v39;
			v31 += v20;
		}
		a9 += v21;
	}
	for(m = a3;; ++m) {
		v36 = a9;
		if(m >= a6) {
			break;
		}
		v35 = a4 | (m << 11);
		v34 = a5;
		while(v34 < a8) {
			v33 = v35 | (v34 << 7);
			v40 = v35;
			++v34;
			memcpy(&this->skyLight.data[v33 >> 1], &a2[v36], v20);
			v35 = v40;
			v36 += v20;
		}
		a9 += v21;
	}

	return a9;
}
Random LevelChunk::getRandom(int32_t x) {
	int32_t v5 = this->level->getSeed() + 4987142 * this->chunkX * this->chunkX + 5947611 * this->chunkX + 4392871 * this->chunkZ * this->chunkZ + 389711 * this->chunkZ;
	return Random(v5 ^ x);
}

bool_t LevelChunk::isEmpty() {
	return 0;
}
