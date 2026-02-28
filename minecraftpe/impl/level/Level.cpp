#include <level/Level.hpp>
#include <algorithm>
#include <entity/EntityFactory.hpp>
#include <entity/Player.hpp>
#include <entity/Zombie.hpp>
#include <entity/path/PathFinder.hpp>
#include <level/BiomeSource.hpp>
#include <level/ChunkCache.hpp>
#include <level/Explosion.hpp>
#include <level/LevelListener.hpp>
#include <level/LightLayer.hpp>
#include <level/MobSpawner.hpp>
#include <level/PRInfo.hpp>
#include <level/Region.hpp>
#include <level/TickNextTickData.hpp>
#include <level/chunk/EmptyLevelChunk.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <level/dimension/Dimension.hpp>
#include <level/dimension/DimensionFactory.hpp>
#include <level/storage/LevelStorage.hpp>
#include <math/HitResult.hpp>
#include <math/Mth.hpp>
#include <nbt/CompoundTag.hpp>
#include <network/RakNetInstance.hpp>
#include <network/packet/EntityEventPacket.hpp>
#include <network/packet/ExplodePacket.hpp>
#include <network/packet/SetEntityDataPacket.hpp>
#include <network/packet/SetTimePacket.hpp>
#include <perf/Stopwatch.hpp>
#include <tile/SlabTile.hpp>
#include <tile/Tile.hpp>
#include <tile/entity/TileEntity.hpp>
#include <tile/material/Material.hpp>
#include <util/DistanceEntitySorter.hpp>
#include <util/_TickPtr.hpp>
#include <utils.h>

Level::Level(struct LevelStorage* a2, const std::string& a3, const struct LevelSettings& a4, bool_t a5, int32_t a6, struct Dimension* a7) : random(1){
	this->isClientMaybe = a5;
	this->instantTick = 0;
	this->field_5C = 0;
	this->skyDarken = 0;
	this->rakNetInstance = 0;
	this->field_A48 = 0;
	this->chunkSource = 0;
	this->levelStoragePtr = a2;
	this->field_AF0 = 0;
	this->spawnAnimalsMaybe = 1;
	this->prevRandomNumber = 0x283AE83;
	this->spawnMonstersMaybe = 1;
	this->constRandom = 0x3C6EF35F;
	this->_updateLights = 1;
	this->lightUpdatesCnt = 0;
	this->field_B64 = 0;
	this->nightMode = 0;
	this->field_B64_ = 0.0;
	this->prevTimeSent = 0;
	this->_init(a3, a4, a6, a7);
}
void Level::_init(const std::string& levelName, const struct LevelSettings& a3, int32_t a4, struct Dimension* a5) {
	LevelData* v9;	  // r1
	ChunkSource* v10; // r0
	//LevelData v11; // [sp+0h] [bp-B0h] BYREF

	this->field_12 = 0;
	v9 = this->levelStoragePtr->prepareLevel(this);
	this->field_B64 = v9 == 0;
	if(v9) {
		this->levelData = *v9;
		this->levelData.setLevelName(levelName);
	} else {
		this->levelData = LevelData(a3, levelName, a4);
	}
	if(a5) {
		this->dimensionPtr = a5;
	} else {
		this->dimensionPtr = DimensionFactory::createDefaultDimension(&this->levelData);
	}
	this->dimensionPtr->init(this);
	v10 = this->createChunkSource();
	this->nightMode = 0;
	this->chunkSource = v10;
	this->updateSkyBrightness();
}
void Level::_syncTime(int32_t a2) { //long
	if(!this->isClientMaybe) {
		SetTimePacket pk(a2, (uint32_t)this->levelData.stopTime >> 31);
		this->rakNetInstance->send(pk);
	}
}

bool_t Level::addEntity(struct Entity* e) {
	Entity* ent;	   // r1
	int32_t v4;		   // r8
	int32_t v5;		   // r7
	LevelChunk* chunk; // r0
	Entity* v12;	   // r1
	Entity* a2;		   // [sp+4h] [bp-34h] BYREF

	a2 = e;
	ent = this->getEntity(e->entityId);
	if(ent) {
		this->removeEntity(ent);
	}
	v4 = Mth::floor(a2->posX * 0.0625);
	v5 = Mth::floor(a2->posZ * 0.0625);
	if(a2->isPlayer()) {
		auto&& player = std::find(this->playersMaybe.begin(), this->playersMaybe.end(), a2);
		if(player == this->playersMaybe.end()) {
			this->playersMaybe.emplace_back(a2);
		}
	}
	chunk = this->getChunk(v4, v5);
	chunk->addEntity(a2);
	this->entities.push_back(a2);
	this->eid2entity.insert({a2->entityId, a2});
	v12 = a2;
	this->entityAdded(v12);
	return 1;
}
void Level::addListener(struct LevelListener* ll) {
	this->levelListeners.emplace_back(ll);
}
Particle* Level::addParticle(ParticleType pt, float a3, float a4, float a5, float a6, float a7, float a8, int32_t a9) {
	for(auto&& ll: this->levelListeners) {
		Particle* p = ll->addParticle(pt, a3, a4, a5, a6, a7, a8, a9);
		if(p) return p;
	}
	return 0;
}
void Level::animateTick(int32_t x, int32_t y, int32_t z) {
	int32_t v6;		// r6
	uint32_t v7;	// r9
	int32_t v8;		// r9
	uint32_t v9;	// r8
	int32_t v10;	// r8
	uint32_t v11;	// r10
	int32_t v12;	// r10
	int32_t result; // r0
	Random v16;
	v6 = 100;
	do {
		v7 = x + (this->random.genrand_int32() & 0xF);
		v8 = v7 - (this->random.genrand_int32() & 0xF);
		v9 = y + (this->random.genrand_int32() & 0xF);
		v10 = v9 - (this->random.genrand_int32() & 0xF);
		v11 = z + (this->random.genrand_int32() & 0xF);
		v12 = v11 - (this->random.genrand_int32() & 0xF);
		result = this->getTile(v8, v10, v12);
		if(result > 0) {
			Tile::tiles[result]->animateTick(this, v8, v10, v12, &v16);
		}
		--v6;
	} while(v6);
}
void Level::broadcastEntityEvent(struct Entity* a2, char_t a3) {
	int32_t entityId;				// r6
	RakNetInstance* rakNetInstance; // r0

	if(!this->isClientMaybe) {
		entityId = a2->entityId;
		EntityEventPacket v7(entityId, a3);

		this->rakNetInstance->send(v7);
	}
}
bool_t Level::canSeeSky(int32_t x, int32_t y, int32_t z) {
	int8_t cx = x;
	int8_t cz = z;
	LevelChunk* chunk = this->getChunk(x >> 4, z >> 4);
	return chunk->isSkyLit(cx & 0xf, y, cz & 0xf);
}
bool_t Level::checkAndHandleWater(const struct AABB& a2, const struct Material* a3, struct Entity* a4) {
	int32_t v7;		   // r7
	int32_t v8;		   // r11
	int32_t v9;		   // r10
	Tile* v10;		   // r9
	int32_t v11;	   // r0
	int32_t j;		   // r8
	int32_t i;		   // r5
	float v14;		   // s15
	float v15;		   // s14
	float yCoord;	   // s13
	float v17;		   // s15
	float zCoord;	   // s13
	int32_t v20;	   // [sp+10h] [bp-60h]
	int32_t v21;	   // [sp+14h] [bp-5Ch]
	int32_t v22;	   // [sp+18h] [bp-58h]
	int32_t v23;	   // [sp+1Ch] [bp-54h]
	Vec3 v25{0, 0, 0}; // [sp+2Ch] [bp-44h] BYREF

	v7 = Mth::floor(a2.minX);
	v21 = Mth::floor(a2.maxX + 1.0);
	v8 = Mth::floor(a2.minY);
	v20 = Mth::floor(a2.maxY + 1.0);
	v22 = Mth::floor(a2.minZ);
	v23 = Mth::floor(a2.maxZ + 1.0);
	if(!this->hasChunksAt(v7, v8, v22, v21, v20, v23)) {
		return 0;
	}
	v9 = 0;
	//memset(&v25, 0, sizeof(v25));
	while(v7 < v21) {
		for(i = v8; i < v20; ++i) {
			for(j = v22; j < v23; ++j) {
				v10 = Tile::tiles[this->getTile(v7, i, j)];
				if(v10) {
					if(v10->material == a3) {
						v11 = this->getData(v7, i, j);
						if(v11 > 7) {
							v11 = 0;
						}
						if((float)v20 >= (float)((float)(i + 1) - (float)((float)(v11 + 1) / 9.0))) {
							v10->handleEntityInside(this, v7, i, j, a4, v25);
							v9 = 1;
						}
					}
				}
			}
		}
		++v7;
	}
	v14 = sqrt((float)((float)((float)(v25.y * v25.y) + (float)(v25.x * v25.x)) + (float)(v25.z * v25.z)));
	if(v14 > 0.0) {
		v15 = 0.004 / v14;
		yCoord = v25.y;
		a4->motionX = a4->motionX + (float)((float)(0.004 / v14) * v25.x);
		v17 = a4->motionY + (float)((float)(0.004 / v14) * yCoord);
		zCoord = v25.z;
		a4->motionY = v17;
		a4->motionZ = a4->motionZ + (float)(v15 * zCoord);
	}
	return v9;
}
HitResult Level::clip(const Vec3& start, const Vec3& end, bool_t a5, bool_t a6) {
	//TODO check
	union _float_int32 {
		int32_t i;
		float f;
	};
	_float_int32 v6;	 // s9
	_float_int32 v7;	 // s10
	int32_t v8;			 // s11
	float x;			 // s15
	float y;			 // s15
	float z;			 // s15
	float ex;			 // s15
	float ey;			 // s17
	float ez;			 // s16
	float sy;			 // r1
	_float_int32 sz;	 // r2
	_float_int32 startX; // r4
	_float_int32 startY; // r6
	_float_int32 v23;	 // r5
	float v24;			 // s15
	float v25;			 // s5
	float v26;			 // s7
	float v27;			 // s8
	float v28;			 // s6
	float v29;			 // s4
	float v30;			 // s9
	int v31;			 // r8
	float v32;			 // s12
	float v33;			 // s15
	float v34;			 // s15
	int v35;			 // r0
	float v37;			 // s15
	Tile* v38;			 // r8
	_float_int32 endX;	 // [sp+18h] [bp-98h]
	_float_int32 endY;	 // [sp+1Ch] [bp-94h]
	_float_int32 endZ;	 // [sp+20h] [bp-90h]
	int iterations;		 // [sp+24h] [bp-8Ch]
	int v43;			 // [sp+28h] [bp-88h]
	int v44;			 // [sp+2Ch] [bp-84h]
	Vec3 sx;			 // [sp+38h] [bp-78h] BYREF
	HitResult v49;		 // [sp+50h] [bp-60h] BYREF

	static Stopwatch swclip;
	swclip.start();
	x = start.x;
	y = start.y;
	z = start.z;
	ex = end.x;
	ey = end.y;
	ez = end.z;
	sy = start.y;
	sz.f = start.z;
	sx.x = start.x;
	sx.y = sy;
	sx.z = sz.f;
	endX.i = Mth::floor(ex);
	endY.i = Mth::floor(ey);
	endZ.i = Mth::floor(ez);
	startX.i = Mth::floor(sx.x);
	startY.i = Mth::floor(sx.y);
	iterations = 202;
	v23.i = Mth::floor(sx.z);
	while(1) {
		if(!--iterations) {
LABEL_6:
			swclip.stop();
			return HitResult();
		}
		if(startX.i != endX.i) {
			if(endX.i <= startX.i) {
				if(endX.i >= startX.i) {
LABEL_15:
					v24 = 999.0;
				} else {
					v7.i = startX.i;
					v24 = (float)startX.i + 0.0;
				}
			} else {
				v6.i = startX.i;
				v24 = (float)startX.i + 1.0;
			}
			if(endY.i <= startY.i) {
				if(endY.i >= startY.i) {
					v8 = 999.0;
				} else {
					v7.i = startY.i;
				}
				if(endY.i < startY.i) {
					v8 = (float)v7.i + 0.0;
				}
			} else {
				v6.i = startY.i;
				v8 = (float)startY.i + 1.0;
			}
			goto LABEL_23;
		}
		if(startY.i != endY.i) {
			goto LABEL_15;
		}
		if(v23.i == endZ.i) {
			goto LABEL_6;
		}
		v24 = 999.0;
		v8 = 999.0;
LABEL_23:
		if(endZ.i <= v23.i) {
			if(endZ.i >= v23.i) {
				v7.f = 999.0;
			} else {
				v6.i = v23.i;
			}
			if(endZ.i < v23.i) {
				v7.f = (float)v6.i + 0.0;
			}
		} else {
			v7.f = (float)v23.i + 1.0;
		}
		v25 = end.x - sx.x;
		if(v24 == 999.0) {
			v26 = 999.0;
		} else {
			v26 = v24 - sx.x;
		}
		if(v24 != 999.0) {
			v26 = v26 / v25;
		}
		if(v8 == 999.0) {
			v27 = 999.0;
		} else {
			v27 = v8 - sx.y;
		}
		v28 = end.y - sx.y;
		if(v8 != 999.0) {
			v27 = v27 / v28;
		}
		v29 = end.z - sx.z;
		if(v7.f == 999.0) {
			v30 = 999.0;
		} else {
			v30 = v7.f - sx.z;
		}
		if(v7.f != 999.0) {
			v30 = v30 / v29;
		}
		if(v26 < v27 && v26 < v30) {
			sx.x = v24;
			if(endX.i > startX.i) {
				v31 = 4;
			} else {
				v31 = 5;
			}
			sx.y = sx.y + (float)(v28 * v26);
			v32 = sx.z + (float)(v29 * v26);
			goto LABEL_53;
		}
		if(v27 < v30) {
			sx.y = v8;
			v31 = endY.i <= startY.i;
			v32 = sx.z + (float)(v29 * v27);
			sx.x = sx.x + (float)(v25 * v27);
LABEL_53:
			sx.z = v32;
			goto LABEL_58;
		}
		sx.z = v7.f;
		if(endZ.i > v23.i) {
			v31 = 2;
		} else {
			v31 = 3;
		}
		sx.x = sx.x + (float)(v25 * v30);
		sx.y = sx.y + (float)(v28 * v30);
LABEL_58:
		Vec3 v48(sx.x, sx.y, sx.z);
		v33 = (float)Mth::floor(sx.x);
		startX.i = (int)v33;
		if(v31 == 5) {
			v33 = v33 + 1.0;
		}
		v48.x = v33;
		if(v31 == 5) {
			--startX.i;
		}
		v8 = Mth::floor(sx.y);
		v34 = (float)v8;
		startY.i = (int)(float)v8;
		if(v31 == 1) {
			v34 = v34 + 1.0;
		}
		v48.y = v34;
		if(v31 == 1) {
			--startY.i;
		}
		v35 = Mth::floor(sx.z);
		v6.i = v35;
		v37 = (float)v35;
		v7.i = (int)(float)v35;
		v23.i = v7.i;
		if(v31 == 3) {
			v37 = v37 + 1.0;
		}
		v48.z = v37;
		if(v31 == 3) {
			v23.i = v7.i - 1;
		}
		v43 = this->getTile(startX.i, startY.i, v23.i);
		v44 = this->getData(startX.i, startY.i, v23.i);
		v38 = Tile::tiles[v43];
		if((!a6 || !v38 || v38->getAABB(this, startX.i, startY.i, v23.i)) && v43 > 0) {
			if(v38->mayPick(v44, a5)) {
				if(startX.i >= 0 && v23.i >= 0 && startX.i <= 255 && v23.i <= 255) {
					HitResult v49 = v38->clip(this, startX.i, startY.i, v23.i, sx, end);
					if(v49.hitType != 2) {
						swclip.stop();
						return HitResult(v49);
					}
				}
			}
		}
	}
}
bool_t Level::containsAnyLiquid(const struct AABB& aabb) {
	float minX;	 // s19
	int32_t v5;	 // r5
	int32_t v6;	 // r0
	float minY;	 // s18
	int32_t v8;	 // r7
	int32_t v9;	 // r0
	float minZ;	 // s17
	int32_t v11; // r8
	int32_t v12; // r0
	int32_t v13; // r11
	Tile* v14;	 // r3
	int32_t v15; // r6
	int32_t i;	 // r4
	int32_t v18; // [sp+0h] [bp-40h]
	int32_t v19; // [sp+4h] [bp-3Ch]

	minX = aabb.minX;
	v5 = Mth::floor(aabb.minX);
	v6 = Mth::floor(aabb.maxX + 1.0);
	minY = aabb.minY;
	v18 = v6;
	v8 = Mth::floor(minY);
	v9 = Mth::floor(aabb.maxY + 1.0);
	minZ = aabb.minZ;
	v19 = v9;
	v11 = Mth::floor(minZ);
	v12 = Mth::floor(aabb.maxZ + 1.0);
	if(minX < 0.0) {
		--v5;
	}
	if(minY < 0.0) {
		--v8;
	}
	v13 = v12;
	if(minZ < 0.0) {
		--v11;
	}
	while(1) {
		if(v5 >= v18) {
			return 0;
		}
		v15 = v8;
LABEL_12:
		if(v15 < v19) {
			break;
		}
		++v5;
	}
	for(i = v11;; ++i) {
		if(i >= v13) {
			++v15;
			goto LABEL_12;
		}
		v14 = Tile::tiles[this->getTile(v5, v15, i)];
		if(v14) {
			if(v14->material->isLiquid()) {
				break;
			}
		}
	}
	return 1;
}
bool_t Level::containsFireTile(const struct AABB& aabb) {
	int32_t v4;	 // r5
	int32_t v5;	 // r9
	int32_t v6;	 // r10
	int32_t v7;	 // r11
	int32_t v9;	 // r0
	int32_t i;	 // r7
	int32_t v11; // r4
	int32_t v12; // [sp+10h] [bp-38h]
	int32_t v13; // [sp+14h] [bp-34h]

	v4 = Mth::floor(aabb.minX);
	v12 = Mth::floor(aabb.maxX + 1.0);
	v5 = Mth::floor(aabb.minY);
	v13 = Mth::floor(aabb.maxY + 1.0);
	v6 = Mth::floor(aabb.minZ);
	v7 = Mth::floor(aabb.maxZ + 1.0);
	if(this->hasChunksAt(v4, v5, v6, v12, v13, v7)) {
		while(v4 < v12) {
			v11 = v5;
LABEL_9:
			if(v11 < v13) {
				for(i = v6;; ++i) {
					if(i >= v7) {
						++v11;
						goto LABEL_9;
					}
					v9 = this->getTile(v4, v11, i);
					if(v9 == Tile::fire->blockID || v9 == Tile::lava->blockID || v9 == Tile::calmLava->blockID) {
						break;
					}
				}
				return 1;
			}
			++v4;
		}
	}
	return 0;
}
bool_t Level::containsLiquid(const struct AABB& aabb, const struct Material* mat) {
	int32_t v6;	 // r6
	int32_t v7;	 // r10
	Tile* v8;	 // r3
	int32_t j;	 // r7
	int32_t v10; // r0
	float v11;	 // s15
	int32_t i;	 // r5
	int32_t v14; // [sp+0h] [bp-48h]
	int32_t v15; // [sp+4h] [bp-44h]
	int32_t v16; // [sp+8h] [bp-40h]
	int32_t v17; // [sp+Ch] [bp-3Ch]

	v6 = Mth::floor(aabb.minX);
	v14 = Mth::floor(aabb.maxX + 1.0);
	v15 = Mth::floor(aabb.minY);
	v16 = Mth::floor(aabb.maxY + 1.0);
	v17 = Mth::floor(aabb.minZ);
	v7 = Mth::floor(aabb.maxZ + 1.0);
	while(v6 < v14) {
		for(i = v15; i < v16; ++i) {
			for(j = v17; j < v7; ++j) {
				v8 = Tile::tiles[this->getTile(v6, i, j)];
				if(v8) {
					if(v8->material == mat) {
						v10 = this->getData(v6, i, j);
						v11 = v10 <= 7 ? (float)((float)i + 1.0) - (float)((float)v10 * 0.125) : (float)(i + 1);
						if(v11 >= aabb.minY) {
							return 1;
						}
					}
				}
			}
		}
		++v6;
	}
	return 0;
}
bool_t Level::containsMaterial(const struct AABB& aabb, const struct Material* mat) {
	int32_t v6;	 // r5
	int32_t v7;	 // r9
	int32_t v8;	 // r11
	Tile* v9;	 // r3
	int32_t i;	 // r6
	int32_t v11; // r4
	int32_t v13; // [sp+4h] [bp-3Ch]
	int32_t v14; // [sp+8h] [bp-38h]
	int32_t v15; // [sp+Ch] [bp-34h]

	v6 = Mth::floor(aabb.minX);
	v13 = Mth::floor(aabb.maxX + 1.0);
	v14 = Mth::floor(aabb.minY);
	v15 = Mth::floor(aabb.maxY + 1.0);
	v7 = Mth::floor(aabb.minZ);
	v8 = Mth::floor(aabb.maxZ + 1.0);
	while(1) {
		if(v6 >= v13) {
			return 0;
		}
		v11 = v14;
LABEL_7:
		if(v11 < v15) {
			break;
		}
		++v6;
	}
	for(i = v7;; ++i) {
		if(i >= v8) {
			++v11;
			goto LABEL_7;
		}
		v9 = Tile::tiles[this->getTile(v6, v11, i)];
		if(v9) {
			if(v9->material == mat) {
				break;
			}
		}
	}
	return 1;
}
int32_t Level::countInstanceOfBaseType(int32_t a2) {
	if((uint32_t)(a2 - 1) > 2) return -1;

	int32_t v5 = 0;
	for(int32_t i = 0; i < this->entities.size(); ++i) {
		if(this->entities[i]->getCreatureBaseType() == a2) ++v5;
	}
	return v5;
}
int32_t Level::countInstanceOfType(int32_t a2) {
	int32_t v5 = 0;
	for(int32_t i = 0; i < this->entities.size(); ++i) {
		if(this->entities[i]->getEntityTypeId() == a2) ++v5;
	}
	return v5;
}
void Level::dispatchEntityData(struct Entity* a2) {
	if(!this->isClientMaybe) {
		this->eid2entity2.insert({a2->entityId, a2});
	}
}
void Level::entityAdded(struct Entity* a2) {
	for(auto&& l: this->levelListeners) {
		l->entityAdded(a2);
	}
}
void Level::entityRemoved(struct Entity* a2) {
	if(a2->rider) {
		a2->rider->ride(0);
	}
	if(a2->ridingAt) {
		a2->ride(0);
	}
	for(auto&& l: this->levelListeners) {
		l->entityRemoved(a2);
	}
}
void Level::explode(struct Entity* a2, float a3, float a4, float a5, float a6) {
	this->explode(a2, a3, a4, a5, a6, 0);
}
void Level::explode(struct Entity* a2, float a3, float a4, float a5, float a6, bool_t a7) {
	if(!this->isClientMaybe) {
		Explosion v15(this, a2, a3, a4, a5, a6);
		v15.field_30 = a7;
		v15.explode();
		v15.finalizeExplosion();
		ExplodePacket v14(a3, a4, a5, a6);								//inlined
		v14.positions.assign(v15.field_10.begin(), v15.field_10.end()); //TODO check
		this->rakNetInstance->send(v14);
	}
}
void Level::extinguishFire(int32_t x, int32_t y, int32_t z, int32_t side) {
	int32_t v5; // r4
	int32_t v6; // r6
	int32_t v7; // r5
	float f;	// s16
	float f1;	// r0

	v5 = z;
	v6 = x;
	v7 = y;
	switch(side) {
		case 0:
			v7 = y - 1;
			break;
		case 1:
			v7 = y + 1;
			break;
		case 2:
			v5 = z - 1;
			break;
		case 3:
			v5 = z + 1;
			break;
		case 4:
			v6 = x - 1;
			break;
		case 5:
			v6 = x + 1;
			break;
		default:
			break;
	}
	if(this->getTile(v6, v7, v5) == Tile::fire->blockID) {
		this->playSound((float)v6 + 0.5, (float)v7 + 0.5, (float)v5 + 0.5, "random.fizz", 0.5, (float)((float)(this->random.nextFloat() - this->random.nextFloat()) * 0.8) + 2.6);
		this->removeTile(v6, v7, v5);
	}
}
Path* Level::findPath(Entity* e, Entity* to, float radius, bool_t a5, bool_t a6, bool_t a7, bool_t a8) {
	int32_t v12; // r6
	int32_t v13; // r5
	int32_t v14; // r0

	v12 = Mth::floor(e->posX);
	v13 = Mth::floor(e->posY + 1.0);
	v14 = Mth::floor(e->posZ);
	Region v17(this, v12 - (int32_t)(float)(radius + 16.0), v13 - (int32_t)(float)(radius + 16.0), v14 - (int32_t)(float)(radius + 16.0), v12 + (int32_t)(float)(radius + 16.0), v13 + (int32_t)(float)(radius + 16.0), v14 + (int32_t)(float)(radius + 16.0));
	PathFinder v18(&v17, a5, a6, a7, a8);
	return v18.findPath(e, to, radius);
	//PathFinder::~PathFinder(&v18);
	//Region::~Region(&v17);
}
Path* Level::findPath(Entity* e, int32_t x, int32_t y, int32_t z, float rad, bool_t a7, bool_t a8, bool_t a9, bool_t a10) {
	int32_t v14; // r7
	int32_t v15; // r6
	int32_t v16; // r0

	v14 = Mth::floor(e->posX);
	v15 = Mth::floor(e->posY);
	v16 = Mth::floor(e->posZ);
	Region v19(this, v14 - (int32_t)(float)(rad + 8.0), v15 - (int32_t)(float)(rad + 8.0), v16 - (int32_t)(float)(rad + 8.0), v14 + (int32_t)(float)(rad + 8.0), v15 + (int32_t)(float)(rad + 8.0), v16 + (int32_t)(float)(rad + 8.0));
	PathFinder v20(&v19, a7, a8, a9, a10);
	return v20.findPath(e, x, y, z, rad);
	//PathFinder::~PathFinder(&v20);
	//Region::~Region(&v19);
}

std::vector<struct Entity*>* Level::getAllEntities() {
	return &this->entities;
}
struct BiomeSource* Level::getBiomeSource() {
	return this->dimensionPtr->biomeSourcePtr;
}

int32_t Level::getBrightness(const struct LightLayer& ll, int32_t x, int32_t y, int32_t z) {
	int8_t v7;		   // r5
	int32_t result;	   // r0
	int32_t v10;	   // r9
	LevelChunk* chunk; // r0

	v7 = x;
	if((uint32_t)y > 0x7F) {
		return ll.baseLight;
	}
	v10 = x >> 4;
	result = this->hasChunk(x >> 4, z >> 4);
	if(result) {
		chunk = this->getChunk(v10, z >> 4);
		return chunk->getBrightness(ll, v7 & 0xF, y, z & 0xF);
	}
	return result;
}
struct LevelChunk* Level::getChunk(int32_t x, int32_t z) {
	return this->chunkSource->getChunk(x, z);
}

struct LevelChunk* Level::getChunkAt(int32_t x, int32_t z) {
	return this->getChunk(x >> 4, z >> 4);
}

struct ChunkSource* Level::getChunkSource() {
	return this->chunkSource;
}

Color4 Level::getCloudColor(float f) {
	float timeOfDay; // r0
	float v5;		 // r0
	float v6;		 // s15
	float v7;		 // s14

	timeOfDay = this->getTimeOfDay(f);
	v5 = Mth::cos((float)(timeOfDay * 3.1416) + (float)(timeOfDay * 3.1416));
	v6 = (float)(v5 + v5) + 0.5;
	if(v6 < 0.0) {
		v6 = 0.0;
	} else if(v6 > 1.0) {
		v6 = 1.0;
	}
	v7 = (float)(v6 * 0.9) + 0.1;
	return Color4(v7, v7, (float)(v6 * 0.85) + 0.15, 0);
}
std::vector<AABB>* Level::getCubes(const struct Entity* a2, const AABB& a3, float* a4) {
	int32_t xx;	  // r8
	int32_t k;	  // r6
	int32_t m;	  // r7
	Tile* v10;	  // r0
	int32_t j;	  // r6
	int32_t v13;  // r0
	Tile* v14;	  // r9
	float v15;	  // r0
	int32_t i;	  // r7
	int32_t v17;  // [sp+14h] [bp-4Ch]
	int32_t maxX; // [sp+18h] [bp-48h]
	int32_t minY; // [sp+1Ch] [bp-44h]
	int32_t maxY; // [sp+20h] [bp-40h]
	int32_t minZ; // [sp+24h] [bp-3Ch]
	int32_t maxZ; // [sp+28h] [bp-38h]

	this->aabbVec.clear();
	xx = Mth::floor(a3.minX);
	maxX = Mth::floor(a3.maxX + 1.0);
	minY = Mth::floor(a3.minY);
	maxY = Mth::floor(a3.maxY + 1.0);
	minZ = Mth::floor(a3.minZ);
	maxZ = Mth::floor(a3.maxZ + 1.0);
	if(a4) {
		*a4 = 0.0;
		v17 = 0x7FFFFFFF;
		while(xx < maxX) {
			for(i = minZ; i < maxZ; ++i) {
				if(this->hasChunkAt(xx, 64, i)) {
					for(j = minY - 1; j < maxY; ++j) {
						v13 = this->getTile(xx, j, i);
						v14 = Tile::tiles[v13];
						if(v14) {
							v14->addAABBs(this, xx, j, i, &a3, this->aabbVec);
							v15 = v14->getThickness();
							if(v15 != 0.0 && j < v17) {
								*a4 = v15;
								v17 = j;
							}
						}
					}
				}
			}
			++xx;
		}
	} else {
		while(xx < maxX) {
			for(k = minZ; k < maxZ; ++k) {
				if(this->hasChunkAt(xx, 64, k)) {
					for(m = minY - 1; m < maxY; ++m) {
						v10 = Tile::tiles[this->getTile(xx, m, k)];
						if(v10) {
							v10->addAABBs(this, xx, m, k, &a3, this->aabbVec);
						}
					}
				}
			}
			++xx;
		}
	}
	return &this->aabbVec;
}
int32_t Level::getDirectSignal(int32_t x, int32_t y, int32_t z, int32_t a5) {
	int32_t id = this->getTile(x, y, z);
	if(id) {
		return Tile::tiles[id]->getDirectSignal(this, x, y, z, a5);
	}
	return 0;
}
std::vector<struct Entity*>* Level::getEntities(struct Entity* a2, const AABB& a3) {
	int32_t v6;		   // r7
	int32_t v7;		   // r9
	int32_t v8;		   // r8
	int32_t v9;		   // r10
	LevelChunk* chunk; // r0
	int32_t i;		   // r6
	this->entVec.clear();
	v6 = Mth::floor((float)(a3.minX - 2.0) * 0.0625);
	v7 = Mth::floor((float)(a3.maxX + 2.0) * 0.0625);
	v8 = Mth::floor((float)(a3.minZ - 2.0) * 0.0625);
	v9 = Mth::floor((float)(a3.maxZ + 2.0) * 0.0625);
	while(v6 <= v7) {
		for(i = v8; i <= v9; ++i) {
			if(this->hasChunk(v6, i)) {
				chunk = this->getChunk(v6, i);
				chunk->getEntities(a2, a3, this->entVec);
			}
		}
		++v6;
	}
	return &this->entVec;
}
int32_t Level::getEntitiesOfClass(int32_t a2, const AABB& a3, std::vector<struct Entity*>& a4) {
	int32_t minX;	   // r7
	int32_t maxX;	   // r9
	int32_t maxZ;	   // r0
	int32_t v11;	   // r10
	LevelChunk* chunk; // r0
	int32_t i;		   // r6
	int32_t minZ;	   // [sp+0h] [bp-38h]
	int32_t v16;	   // [sp+4h] [bp-34h]

	minX = Mth::floor((float)(a3.minX - 2.0) * 0.0625);
	maxX = Mth::floor((float)(a3.maxX + 2.0) * 0.0625);
	minZ = Mth::floor((float)(a3.minZ - 2.0) * 0.0625);
	maxZ = Mth::floor((float)(a3.maxZ + 2.0) * 0.0625);
	v16 = -a4.size();
	v11 = maxZ;
	while(minX <= maxX) {
		for(i = minZ; i <= v11; ++i) {
			if(this->hasChunk(minX, i)) {
				chunk = this->getChunk(minX, i);
				chunk->getEntitiesOfClass(a2, a3, a4);
			}
		}
		++minX;
	}
	return a4.size() - v16;
}
int32_t Level::getEntitiesOfType(int32_t a2, const AABB& a3, std::vector<struct Entity*>& a4) {
	int32_t minX;	   // r7
	int32_t maxX;	   // r9
	int32_t maxZ;	   // r0
	int32_t v11;	   // r10
	LevelChunk* chunk; // r0
	int32_t z;		   // r6
	int32_t minZ;	   // [sp+0h] [bp-38h]
	int32_t v16;	   // [sp+4h] [bp-34h]

	minX = Mth::floor((float)(a3.minX - 2.0) * 0.0625);
	maxX = Mth::floor((float)(a3.maxX + 2.0) * 0.0625);
	minZ = Mth::floor((float)(a3.minZ - 2.0) * 0.0625);
	maxZ = Mth::floor((float)(a3.maxZ + 2.0) * 0.0625);
	v16 = -a4.size();
	v11 = maxZ;
	while(minX <= maxX) {
		for(z = minZ; z <= v11; ++z) {
			if(this->hasChunk(minX, z)) {
				chunk = this->getChunk(minX, z);
				chunk->getEntitiesOfType(a2, a3, a4);
			}
		}
		++minX;
	}
	return a4.size() - v16;
}
struct Entity* Level::getEntity(int32_t a2) {
	if(this->eid2entity.count(a2) == 0) return 0;
	return this->eid2entity.at(a2);
}

Color4 Level::getFogColor(float a3) {
	return this->dimensionPtr->getFogColor(this->getTimeOfDay(a3), a3);
}
int32_t Level::getHeightmap(int32_t x, int32_t z) {
	int32_t v3 = x >> 4;
	int32_t v4 = z >> 4;
	int8_t v5 = x;
	int8_t v6 = z;
	if(this->hasChunk(v3, v4)) {
		return this->getChunk(v3, v4)->getHeightmap(v5 & 0xf, v6 & 0xf);
	}
	return 0;
}
struct LevelData* Level::getLevelData() {
	return &this->levelData;
}

struct LevelStorage* Level::getLevelStorage() {
	return this->levelStoragePtr;
}

int32_t Level::getLightDepth(int32_t x, int32_t z) {
	int8_t v3 = x;
	int8_t v4 = z;
	return this->getChunkAt(x, z)->getHeightmap(v3 & 0xf, v4 & 0xf);
}
int32_t Level::getLightsToUpdate() {
	return this->lightsToUpdate.size();
}
struct Mob* Level::getMob(int32_t a2) {
	Entity* e = this->getEntity(a2);
	if(!e || !e->isMob()) return 0;
	return (Mob*)e;
}

int32_t Level::getMoonPhase() {
	return this->dimensionPtr->getMoonPhase(this->getTime());
}
struct Player* Level::getNearestPlayer(struct Entity* a2, float a3) {
	return this->getNearestPlayer(a2->posX, a2->posY, a2->posZ, a3);
}

struct Player* Level::getNearestPlayer(float x, float y, float z, float a5) {
	float v5 = -1;
	Player* v11 = 0;
	for(int v6 = 0; v6 < this->playersMaybe.size(); ++v6) {
		Player* v12 = this->playersMaybe[v6];
		if(!v12->isDead) {
			float v13 = v12->distanceToSqr(x, y, z);
			if((a5 < 0.0 || v13 < (float)(a5 * a5)) && (v5 == -1.0 || v13 < v5)) {
				v5 = v13;
				v11 = v12;
			}
		}
	}
	return v11;
}

struct Player* Level::getPlayer(const std::string& a2) {
	for(auto&& p: this->playersMaybe) {
		if(p->username == a2) return p;
	}
	return 0;
}
/*returns <player_count>:PlayerName,PlayerName2, ...
	segfaults(at least in x86 build) after it was called 9 times, 8th time will have corrupted string
	code used for testing:

	void* level_getPlayerNames = internal_dlsym(handle, "_ZN5Level14getPlayerNamesEv");
	int player = *(int*)(((int)ninecraft_app) + 3168);
	if(player){
		int level = *(int*)(player+64);
		if(level){
			std_string str;
			(((void (*)(std_string*, int)) level_getPlayerNames))(&str, level);
			printf("%s\n", std_string_cstr(&str));
		}
	}
	According to 0.7.2 it uses std::basic_stringstream and std::ostream
	According to 0.8.1 x86 it uses std::ios std::stringbuf std::streambuf and stuff like this
	Doesnt seem to be used by anything in 0.8
	*/
std::string Level::getPlayerNames() {
	printf("Level::getPlayerNames - not implemented\n");
	//TODO getPlayerNames
	return "";
}

Biome::MobSpawnerData Level::getRandomMobSpawnAt(const MobCategory& a3, int32_t a4, int32_t a5, int32_t a6) {
	std::vector<Biome::MobSpawnerData> v18 = this->chunkSource->getMobsAt(a3, a4, a5, a6);
	if(!v18.empty()) {
		int v10 = 0;
		for(auto&& v: v18) {
			v10 += v.rarity;
		}

		int v12 = this->random.genrand_int32() % v10;
		for(auto&& v: v18) {
			v12 -= v.rarity;
			if(v12 < 0) {
				return Biome::MobSpawnerData(v);
			}
		}
	}
	return Biome::MobSpawnerData(-128, 0, 0, 0); //TODO actually sets only ->rarity to -128
}
int32_t Level::getRawBrightness(int32_t x, int32_t y, int32_t z) {
	return this->getRawBrightness(x, y, z, 1);
}
int32_t Level::getRawBrightness(int32_t x, int32_t y, int32_t z, bool_t recursive) {
	int32_t v9;			   // r0
	int32_t RawBrightness; // r11
	int32_t v11;		   // r10
	int32_t v12;		   // r9
	int32_t result;		   // r0
	LevelChunk* chunk;	   // r0
	int32_t v15;		   // [sp+Ch] [bp-2Ch]

	if(recursive && ((v9 = this->getTile(x, y, z), v9 == Tile::stoneSlabHalf->blockID) || v9 == Tile::farmland->blockID || v9 == Tile::woodSlabHalf->blockID)) {
		RawBrightness = this->getRawBrightness(x, y + 1, z, 0);
		v15 = this->getRawBrightness(x + 1, y, z, 0);
		v11 = this->getRawBrightness(x - 1, y, z, 0);
		v12 = this->getRawBrightness(x, y, z + 1, 0);
		result = this->getRawBrightness(x, y, z - 1, 0);
		if(v15 >= RawBrightness) {
			RawBrightness = v15;
		}
		if(RawBrightness >= v11) {
			v11 = RawBrightness;
		}
		if(v11 >= v12) {
			v12 = v11;
		}
		if(v12 >= result) {
			return v12;
		}
	} else if(y < 0) {
		return 0;
	} else if(y <= 127) {
		chunk = this->getChunk(x >> 4, z >> 4);
		return chunk->getRawBrightness(x & 0xF, y, z & 0xF, this->skyDarken);
	} else {
		return (15 - this->skyDarken) & ~((15 - this->skyDarken) >> 31);
	}
	return result;
}
int32_t Level::getSeaLevel() {
	return 63;
}
int32_t Level::getSeed() {
	return this->levelData.getSeed();
}
float Level::getSeenPercent(const Vec3& a2, const AABB& a3) {
	int32_t v3; // r5
	float v7;	// s17
	int32_t v8; // r6
	float v9;	// s14
	float v10;	// s21
	float v11;	// s14
	float v12;	// s20
	float v13;	// s21
	float v14;	// s18
	float v15;	// s16

	v3 = 0;
	v7 = 0.0;
	v8 = 0;
	v9 = a3.maxY - a3.minY;
	v10 = (float)(v9 + v9) + 1.0;
	v11 = (float)(a3.maxZ - a3.minZ) + (float)(a3.maxZ - a3.minZ);
	v12 = 1.0 / (float)((float)((float)(a3.maxX - a3.minX) + (float)(a3.maxX - a3.minX)) + 1.0);
	v13 = 1.0 / v10;
	do {
		v15 = 0.0;
		do {
			v14 = 0.0;
			do {
				++v3;
				Vec3 start(a3.minX + (float)((float)(a3.maxX - a3.minX) * v7), a3.minY + (float)((float)(a3.maxY - a3.minY) * v15), a3.minZ + (float)((float)(a3.maxZ - a3.minZ) * v14));
				HitResult a1 = this->clip(start, a2, 0, 0);
				v14 = v14 + (float)(1.0 / (float)(v11 + 1.0));
				if(a1.hitType == 2) {
					++v8;
				}
			} while(v14 <= 1.0);
			v15 = v15 + v13;
		} while(v15 <= 1.0);
		v7 = v7 + v12;
	} while(v7 <= 1.0);
	return (float)v8 / (float)v3;
}
TilePos Level::getSharedSpawnPos() {
	return {this->levelData.getXSpawn(), this->levelData.getYSpawn(), this->levelData.getZSpawn()};
}
int32_t Level::getSignal(int32_t x, int32_t y, int32_t z, int32_t side) {
	int32_t result; // r0

	if(this->isSolidBlockingTile(x, y, z)) {
		return this->hasDirectSignal(x, y, z);
	}
	result = this->getTile(x, y, z);
	if(result) {
		return Tile::tiles[result]->getSignal(this, x, y, z, side);
	}
	return result;
}
Color4 Level::getSkyColor(struct Entity* a3, float a4) {
	return this->getSkyColor(Mth::floor(a3->posX), Mth::floor(a3->posZ), a4);
}
Color4 Level::getSkyColor(int32_t a3, int32_t a4, float a5) {
	float timeOfDay; // r0
	float v10;		 // r0
	float v11;		 // s16
	Biome* v12;		 // r5
	float v14;		 // r0
	float b;		 // s15
	float v16;		 // s14
	float r;		 // s13

	timeOfDay = this->getTimeOfDay(a5);
	v10 = Mth::cos((float)(timeOfDay * 3.1416) + (float)(timeOfDay * 3.1416));
	v11 = (float)(v10 + v10) + 0.5;
	if(v11 > 1.0) {
		v11 = 1.0;
	} else if(v11 <= 0.0) {
		v11 = 0.0;
	}
	v12 = this->getBiome(a3, a4);
	v14 = v12->getTemperature();
	Color4 v18 = v12->getSkyColor(v14);
	b = v18.b;
	v16 = v11 * v18.g;
	r = v18.r;
	return Color4(r * v11, v16, v11 * b, 1);
}
int32_t Level::getSkyDarken(float a2) {
	float timeOfDay; // r0
	float v3;		 // r0
	float v4;		 // s15

	timeOfDay = this->getTimeOfDay(a2);
	v3 = Mth::cos((float)(timeOfDay * 3.1416) + (float)(timeOfDay * 3.1416));
	v4 = 1.0 - (float)((float)(v3 + v3) + 0.5);
	if(v4 < 0.0) {
		v4 = 0.0;
	} else if(v4 > 0.8) {
		v4 = 0.8;
	}
	return (int32_t)(float)(v4 * 11.0);
}
float Level::getStarBrightness(float a2) {
	float timeOfDay; // r0
	float v3;		 // r0
	float v4;		 // s15

	timeOfDay = this->getTimeOfDay(a2);
	v3 = Mth::cos((float)(timeOfDay * 3.1416) + (float)(timeOfDay * 3.1416));
	v4 = 1.0 - (float)((float)(v3 + v3) + 0.75);
	if(v4 < 0.0) {
		v4 = 0.0;
	} else if(v4 > 1.0) {
		v4 = 1.0;
	}
	return (float)(v4 * v4) * 0.5;
}
float Level::getSunAngle(float a2) {
	float timeOfDay; // r0

	timeOfDay = this->getTimeOfDay(a2);
	return (float)(timeOfDay * 3.1416) + (float)(timeOfDay * 3.1416);
}
float Level::getSunIntensity(float a2, struct Mob* a3, float a4) {
	float v7; // s15
	Vec3 v9 = a3->getLookAngle();
	Vec3 result = this->getSunlightDirection(a2); // [sp+Ch] [bp-24h] BYREF

	v7 = (float)((float)((float)((float)(v9.y * result.y) + (float)(v9.x * result.x)) + (float)(v9.z * result.z)) + 1.0) * 0.5;
	if(v7 > 1.0) {
		v7 = 1.0;
	} else if(v7 <= a4) {
		v7 = a4;
	}
	return (float)(v7 - a4) / (float)(1.0 - a4);
}
Vec3 Level::getSunlightDirection(float a3) {
	float sunAngle = this->getSunAngle(a3);
	return Vec3(0.25, cosf(sunAngle), sinf(sunAngle));
}
Color4 Level::getSunriseColor(float a3) {
	return this->dimensionPtr->getSunriseColor(this->getTimeOfDay(a3), a3);
}
std::vector<AABB> Level::getTileCubes(const AABB& a3) {
	int32_t v6;	 // r8
	int32_t v7;	 // r11
	int32_t i;	 // r7
	int32_t j;	 // r9
	Tile* v10;	 // r0
	int32_t v11; // r7
	int32_t v25; // [sp+14h] [bp-44h]
	int32_t v26; // [sp+18h] [bp-40h]
	int32_t v27; // [sp+1Ch] [bp-3Ch]
	int32_t v28; // [sp+20h] [bp-38h]

	v6 = Mth::floor(a3.minX);
	v25 = Mth::floor(a3.maxX + 1.0);
	v26 = Mth::floor(a3.minY);
	v27 = Mth::floor(a3.maxY + 1.0);
	v28 = Mth::floor(a3.minZ);
	v7 = Mth::floor(a3.maxZ + 1.0);
	while(v6 < v25) {
		for(i = v28; i < v7; ++i) {
			if(this->hasChunkAt(v6, 64, i)) {
				for(j = v26 - 1; j < v27; ++j) {
					v10 = Tile::tiles[this->getTile(v6, j, i)];
					if(v10) {
						v10->addAABBs(this, v6, j, i, &a3, this->aabbVec);
					}
				}
			}
		}
		++v6;
	}
	v11 = 0;
	std::vector<AABB> a1(this->aabbVec.size());
	for(auto&& bb: this->aabbVec) {
		//if(&a1[v11]){
		a1[v11] = bb;
		//}
		++v11;
	}

	return a1;
}
int32_t Level::getTileCubesCount(const AABB& aabb) {
	int32_t v4;	  // r8
	int32_t minX; // r5
	int32_t minY; // r9
	int32_t maxY; // r10
	int32_t maxZ; // r11
	int32_t j;	  // r6
	int32_t i;	  // r4
	int32_t maxX; // [sp+0h] [bp-38h]
	int32_t minZ; // [sp+4h] [bp-34h]

	v4 = 0;
	minX = Mth::floor(aabb.minX);
	maxX = Mth::floor(aabb.maxX + 1.0);
	minY = Mth::floor(aabb.minY);
	maxY = Mth::floor(aabb.maxY + 1.0);
	minZ = Mth::floor(aabb.minZ);
	maxZ = Mth::floor(aabb.maxZ + 1.0);
	while(minX < maxX) {
		for(i = minZ; i < maxZ; ++i) {
			if(this->hasChunkAt(minX, 64, i)) {
				for(j = minY - 1; j < maxY; ++j) {
					if(this->getTile(minX, j, i)) {
						++v4;
					}
				}
			}
		}
		++minX;
	}
	return v4;
}
TileEntity* Level::getTileEntity(int32_t x, int32_t y, int32_t z) {
	LevelChunk* chunk;		  // r0
	TileEntity* res;		  // r0
	uint32_t i;				  // r5
	TileEntity* te;			  // r4
	TileEntity** vecStartPtr; // r3

	chunk = this->getChunk(x >> 4, z >> 4);
	if(!chunk) {
		return 0;
	}
	res = chunk->getTileEntity(x & 0xF, y, z & 0xF);
	if(!res) {
		for(auto te: this->field_50) {
			if(!te->isRemoved() && te->posX == x && te->posY == y && te->posZ == z) {
				return te;
			}
		}
		return 0;
	}
	return res;
}

bool_t Level::getTileObstructsChests(int32_t x, int32_t y, int32_t z) {
	Tile* tile;	   // r4
	bool_t result; // r0

	tile = Tile::tiles[this->getTile(x, y, z)];
	result = tile->isCubeShaped();
	if(result) {
		return 1;
	}
	if(tile == Tile::stoneSlabHalf || tile == Tile::woodSlabHalf) {
		return ((SlabTile*)tile)->isBottomSlab(this, x, y, z);
	}
	return result;
}
int32_t Level::getTime() {
	return this->levelData.getTime();
}
float Level::getTimeOfDay(float a2) {
	int32_t stopTime; // r1

	stopTime = this->levelData.stopTime;
	if(stopTime < 0) {
		stopTime = this->getTime();
	}
	return this->dimensionPtr->getTimeOfDay(stopTime, a2);
}
int32_t Level::getTopSolidBlock(int32_t x, int32_t z) {
	int32_t v6;			 // r4
	LevelChunk* chunk;	 // r7
	Material* v8;		 // r0
	int32_t v9;			 // r8
	int32_t v10;		 // r9
	int32_t v11;		 // r0
	int32_t v12;		 // r6
	const Material* mat; // r0

	v6 = 127;
	chunk = this->getChunkAt(x, z);
	while(1) {
		v8 = this->getMaterial(x, v6, z);
		if(!v8->blocksMotion() || !v6) {
			break;
		}
		--v6;
	}
	v9 = x & 0xF;
	v10 = z & 0xF;
	while(v6) {
		v11 = chunk->getTile(v9, v6, v10);
		v12 = v11;
		if(v11) {
			mat = Tile::tiles[v11]->material;
			if(mat->blocksMotion()) {
				if(Tile::tiles[v12]->material != Material::leaves) {
					return v6 + 1;
				}
			}
		}
		--v6;
	}
	return -1;
}
int32_t Level::getTopTile(int32_t x, int32_t z) {
	int32_t y; // r5

	for(y = 63; !this->isEmptyTile(x, y + 1, z); ++y) {
		;
	}
	return this->getTile(x, y, z);
}
int32_t Level::getTopTileY(int32_t x, int32_t z) {
	int32_t y; // r4

	for(y = 63; !this->isEmptyTile(x, y + 1, z); ++y) {
		;
	}
	return y;
}
bool_t Level::hasChunk(int32_t x, int32_t z) {
	return this->chunkSource->hasChunk(x, z);
}
bool_t Level::hasChunkAt(int32_t x, int32_t y, int32_t z) {
	return (uint32_t)y <= 127 && this->hasChunk(x >> 4, z >> 4);
}
bool_t Level::hasChunksAt(int32_t x, int32_t y, int32_t z, int32_t radius) {
	return this->hasChunksAt(x - radius, y - radius, z - radius, x + radius, y + radius, z + radius);
}
bool_t Level::hasChunksAt(int32_t minX, int32_t minY, int32_t minZ, int32_t maxX, int32_t maxY, int32_t maxZ) {
	int32_t xx;	   // r5
	int32_t minZc; // r7
	bool_t result; // r0
	int32_t zz;	   // r4

	if(maxY < 0 || minY > 127) {
		return 0;
	}
	xx = minX >> 4;
	minZc = minZ >> 4;
	while(xx <= maxX >> 4) {
		for(zz = minZc; zz <= maxZ >> 4; ++zz) {
			result = this->hasChunk(xx, zz);
			if(!result) {
				return result;
			}
		}
		++xx;
	}
	return 1;
}
bool_t Level::hasDirectSignal(int32_t x, int32_t y, int32_t z) {
	if(this->getDirectSignal(x, y - 1, z, 0) || this->getDirectSignal(x, y + 1, z, 1) || this->getDirectSignal(x, y, z - 1, 2) || this->getDirectSignal(x, y, z + 1, 3) || this->getDirectSignal(x - 1, y, z, 4)) {
		return 1;
	} else {
		return this->getDirectSignal(x + 1, y, z, 5);
	}
}
bool_t Level::hasNeighborSignal(int32_t x, int32_t y, int32_t z) {
	if(this->getSignal(x, y - 1, z, 0) || this->getSignal(x, y + 1, z, 1) || this->getSignal(x, y, z - 1, 2) || this->getSignal(x, y, z + 1, 3) || this->getSignal(x - 1, y, z, 4)) {
		return 1;
	} else {
		return this->getSignal(x + 1, y, z, 5);
	}
}
bool_t Level::inRange(int32_t x, int32_t y, int32_t z) {
	return (uint32_t)x <= 0xff && y <= 127 && z >= 0 && z <= 255;
}
bool_t Level::isDay() {
	return this->skyDarken <= 3;
}
bool_t Level::isNightMode() {
	return this->nightMode;
}
bool_t Level::isSkyLit(int32_t x, int32_t y, int32_t z) {
	int8_t xx = x;
	int8_t zz = z;
	if(y < 0) return 0;
	if(y > 127) return 1;
	int32_t v9 = x >> 4;
	int32_t v10 = z >> 4;
	if(!this->hasChunk(x >> 4, z >> 4)) return 0;
	return this->getChunk(v9, v10)->isSkyLit(xx & 0xf, y, zz & 0xf);
}
bool_t Level::isTopSolidBlocking(struct Tile* a2, int32_t a3) {
	if(!a2) {
		return 0;
	}

	if(a2->material->isSolidBlocking() && a2->isCubeShaped()) {
		return 1;
	}
	if(a2->getTileType() == 1) {
		return ((uint32_t)a3 >> 2) & 1;
	}
	if(a2->getTileType() == 2) {
		return ((uint32_t)a3 >> 3) & 1;
	}
	if(a2->getTileType() == 3) {
		return 1;
	}
	if(a2->getTileType() != 4) {
		return 0;
	}
	return (a3 & 7) == 7;
}
bool_t Level::isTopSolidBlocking(int32_t x, int32_t y, int32_t z) {
	Tile* v8 = Tile::tiles[this->getTile(x, y, z)];
	int32_t v9 = this->getData(x, y, z);
	return this->isTopSolidBlocking(v8, v9);
}
bool_t Level::isUnobstructed(const AABB& aabb) {
	for(auto&& e: *this->getEntities(0, aabb)) {
		if(!e->isDead && e->field_FC) {
			return 0; //result = (unsigned __int8)v6->isDead;
		}
	}
	return 1;
}
void Level::levelEvent(struct Player* player, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7) {
	for(auto&& l: this->levelListeners) {
		l->levelEvent(player, a3, a4, a5, a6, a7);
	}
}
void Level::levelEvent(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6) {
	this->levelEvent(0, a2, a3, a4, a5, a6);
}
void Level::lightColumnChanged(int32_t a2, int32_t a3, int32_t a4, int32_t a5) {
	int32_t v6; // r4
	int32_t v7; // r2

	v6 = a5;
	if(a4 > a5) {
		v7 = a4;
		a4 = a5;
		v6 = v7;
	}
	this->setTilesDirty(a2, a4, a3, a2, v6, a3);
}
void Level::loadEntities() {
	if(this->levelStoragePtr) this->levelStoragePtr->loadEntities(this, 0);
}
void Level::loadPlayer(struct Player* player, bool_t a3) {
	CompoundTag* tag; // r0
	CompoundTag* v8;  // r5
	Entity* entity;	  // r0
	Entity* v11;	  // r5
	CompoundTag* v12; // r5

	if(player) {
		tag = this->levelData.getLoadedPlayerTag();
		v8 = tag;
		if(tag) {
			player->load(tag);
			if(v8->contains(Entity::RIDING_TAG)) {
				if(tag->get(Entity::RIDING_TAG)->getId() == 10) {
					v12 = (CompoundTag*)v8->get(Entity::RIDING_TAG);
				} else {
					v12 = new CompoundTag(Entity::RIDING_TAG);
				}
				entity = EntityFactory::loadEntity(v12, this);
				v11 = entity;
				if(entity) {
					this->addEntity(entity);
					player->ride(v11);
				}
			}
			this->levelData.setLoadedPlayerTag(0);
		} else {
			this->levelData.setLoadedPlayerTo(player);
		}
		if(a3) {
			this->addEntity(player);
		}
	}
}
bool_t Level::mayInteract(struct Player*, int32_t, int32_t, int32_t) {
	return 1;
}
bool_t Level::mayPlace(int32_t blockID, int32_t x, int32_t y, int32_t z, bool_t a6, uint8_t side) { //uchar
	int32_t idAtXYZ;																				// r0
	Tile* v12;																						// r5
	Tile* v13;																						// r10
	const AABB* v14;																				// r0

	idAtXYZ = this->getTile(x, y, z);
	v12 = Tile::tiles[blockID];
	v13 = Tile::tiles[idAtXYZ];
	v14 = v12->getAABB(this, x, y, z);
	if((a6 || !v14 || this->isUnobstructed(*v14)) && (!v13 || v13->replaceable) && blockID > 0) {
		return v12->mayPlace(this, x, y, z, side);
	} else {
		return 0;
	}
}
void Level::neighborChanged(int32_t x, int32_t y, int32_t z, int32_t a5, int32_t a6, int32_t a7, int32_t a8) {
	Tile* v12; // r0

	if(!this->isClientMaybe) {
		v12 = Tile::tiles[this->getTile(x, y, z)];
		if(v12) {
			v12->neighborChanged(this, x, y, z, a5, a6, a7, a8);
		}
	}
}
void Level::playSound(struct Entity* e, const std::string& s, float a4, float a5) {
	for(int32_t i = 0; i < this->levelListeners.size(); ++i) {
		this->levelListeners[i]->playSound(s, e->posX, e->posY - e->ridingHeight, e->posZ, a4, a5);
	}
}
void Level::playSound(float x, float y, float z, const std::string& s, float a6, float a7) {
	for(int32_t i = 0; i < this->levelListeners.size(); ++i) {
		this->levelListeners[i]->playSound(s, x, y, z, a6, a7);
	}
}
void Level::prepare() {
	while(this->chunkSource->tick());
}
void Level::registerTemporaryPointer(struct _TickPtr* a2) {
	this->tickPtrSetImpl.insert(a2);
}
void Level::removeEntity(struct Entity* a2) {
	if(a2->rider) a2->rider->ride(0);
	if(a2->ridingAt) a2->ride(0);
	a2->remove();
	if(a2->isPlayer()) {
		if(a2->field_108) {
			auto&& p = std::find(this->playersMaybe.begin(), this->playersMaybe.end(), a2);
			if(p != this->playersMaybe.end()) {
				this->playersMaybe.erase(p);
			}
		}
	}
}
void Level::removeListener(struct LevelListener* a2) {
	this->levelListeners.erase(std::find(this->levelListeners.begin(), this->levelListeners.end(), a2));
}
void Level::removePlayer(struct Player* a2) {
	for(int32_t i = 0; i < this->playersMaybe.size(); ++i) {
		if(this->playersMaybe[i] == a2) {
			this->playersMaybe.erase(this->playersMaybe.begin() + i); //TODO bight be broken?
		}
	}
}
void Level::removeTile(int32_t x, int32_t y, int32_t z) {
	this->setTileAndData(x, y, z, 0, 0, 3);
}
void Level::removeTileEntity(int32_t x, int32_t y, int32_t z) {
	TileEntity* te; // r0

	te = this->getTileEntity(x, y, z);
	if(te) {
		te->setRemoved();
		auto&& a6 = std::find(this->field_50.begin(), this->field_50.end(), te);
		if(a6 != this->field_50.end()) {
			this->field_50.erase(a6);
		}
	}
}
void Level::saveGame() {
	if(this->levelStoragePtr) {
		this->levelStoragePtr->saveGame(this);
		this->saveLevelData();
	}
}
void Level::saveLevelData() {
	this->levelStoragePtr->saveLevelData(this->levelData, &this->playersMaybe);
}
void Level::savePlayers() {
	if(!this->isClientMaybe) {
		if(this->levelStoragePtr) {
			for(int32_t i = 0; i < this->playersMaybe.size(); ++i) {
				Player* p = this->playersMaybe[i];
				if(!p->isLocalPlayer()) {
					this->levelStoragePtr->save(p);
				}
			}
		}
	}
}
void Level::sendTileUpdated(int32_t x, int32_t y, int32_t z) {
	for(auto&& ll: this->levelListeners) {
		ll->tileChanged(x, y, z);
	}
}
void Level::setBrightness(const struct LightLayer& ll, int32_t x, int32_t y, int32_t z, int32_t b) {
	int32_t v10;	   // r9
	LevelChunk* chunk; // r0

	if(y >= 0 && y <= 127) {
		v10 = x >> 4;
		if(this->hasChunk(x >> 4, z >> 4)) {
			chunk = this->getChunk(v10, z >> 4);
			chunk->setBrightness(ll, x & 0xF, y, z & 0xF, b);
			for(auto&& ll: this->levelListeners) {
				ll->tileBrightnessChanged(x, y, z);
			}
		}
	}
}
bool_t Level::setData(int32_t x, int32_t y, int32_t z, int32_t data, int32_t flags) {
	LevelChunk* chunk; // r9
	int v11;		   // r5
	int v12;		   // r9

	if(y < 0 || y > 127) {
		return 0;
	}
	chunk = this->getChunk(x >> 4, z >> 4);
	v11 = chunk->setData(x & 0xF, y, z & 0xF, data);
	if(v11) {
		v12 = chunk->getTile(x & 0xF, y, z & 0xF);
		if((flags & 2) != 0 && (!this->isClientMaybe || (flags & 4) == 0)) {
			this->sendTileUpdated(x, y, z);
		}
		if(!this->isClientMaybe && (flags & 1) != 0) {
			this->tileUpdated(x, y, z, v12);
		}
	}
	return v11;
}
bool_t Level::setDataAndUpdate(int32_t x, int32_t y, int32_t z, int32_t d) {
	return this->setData(x, y, z, d, 3);
}
bool_t Level::setDataNoUpdate(int32_t x, int32_t y, int32_t z, int32_t d) {
	return this->setData(x, y, z, d, 4);
}
void Level::setDayCycleActive(bool_t a2) {
	int32_t v4;	  // r6
	int32_t time; // r1

	if(a2 != (uint32_t)this->levelData.stopTime >> 31) {
		if(a2) {
			this->setTime(this->levelData.stopTime);
			this->levelData.setStopTime(-1);
			time = this->getTime();
			this->_syncTime(time);
		} else {
			v4 = this->getTime();
			this->levelData.setStopTime(v4);
			this->_syncTime(v4);
		}
	}
}
void Level::setInitialSpawn(void) {
	int32_t spawnZ;	  // r4
	int32_t spawnX;	  // r5
	Random* p_random; // r7
	int8_t v5;		  // r8
	int8_t v6;		  // r8

	spawnZ = 128;
	this->field_A48 = 1;
	spawnX = 128;

	while(!this->dimensionPtr->isValidSpawn(spawnX, spawnZ)) {
		v5 = this->random.genrand_int32();
		spawnX += (v5 & 0x1F) - (this->random.genrand_int32() & 0x1F);
		v6 = this->random.genrand_int32();
		spawnZ += (v6 & 0x1F) - (this->random.genrand_int32() & 0x1F);
		if(spawnX > 3) {
			if(spawnX > 251) {
				spawnX -= 32;
			}
		} else {
			spawnX += 32;
		}
		if(spawnZ > 3) {
			if(spawnZ > 251) {
				spawnZ -= 32;
			}
		} else {
			spawnZ += 32;
		}
	}
	this->levelData.setSpawn(spawnX, 64, spawnZ);
	this->field_A48 = 0;
}
void Level::setNightMode(bool_t a2) {
	this->nightMode = a2;
}
void Level::setSpawnPos(Pos a2) {
	this->levelData.setSpawn(a2.x, a2.y, a2.z);
}
void Level::setSpawnSettings(bool_t, bool_t) {
}
bool_t Level::setTile(int32_t x, int32_t y, int32_t z, int32_t id, int32_t flags) {
	return this->setTileAndData(x, y, z, id, 0, flags);
}
bool_t Level::setTileAndData(int32_t x, int32_t y, int32_t z, int32_t id, int32_t meta, int32_t flags) {
	LevelChunk* chunk;	// r0
	LevelChunk* chunk_; // r9
	int32_t curid;		// r11
	bool_t res;			// r9

	if(y < 0 || y > 127) {
		return 0;
	}
	chunk = this->getChunk(x >> 4, z >> 4);
	chunk_ = chunk;
	if((flags & 1) != 0) {
		curid = chunk->getTile(x & 0xF, y, z & 0xF);
	} else {
		curid = 0;
	}
	res = chunk_->setTileAndData(x & 0xF, y, z & 0xF, id, meta);
	if(res) {
		if(!this->isClientMaybe && (flags & 1) != 0) {
			this->tileUpdated(x, y, z, curid);
		}
		if((flags & 2) != 0 && (!this->isClientMaybe || (flags & 4) == 0)) {
			this->sendTileUpdated(x, y, z);
		}
	}
	return res;
}
bool_t Level::setTileAndDataNoUpdate(int32_t x, int32_t y, int32_t z, int32_t id, int32_t meta) {
	return this->setTileAndData(x, y, z, id, meta, 4);
}
void Level::setTileDirty(int32_t x, int32_t y, int32_t z) {
	for(auto&& ll: this->levelListeners) {
		ll->setTilesDirty(x, y, z, x, y, z);
	}
}
void Level::setTileEntity(int32_t x, int32_t y, int32_t z, struct TileEntity* te) {
	TileEntity* v9;	   // r3
	LevelChunk* chunk; // r0

	if(te) {
		if(!te->isRemoved()) {
			if(this->field_5C) {
				v9 = te;
				te->posX = x;
				v9->posY = y;
				v9->posZ = z;
				this->field_50.push_back(te);
			} else {
				this->tileEntities.push_back(te);
				chunk = this->getChunk(x >> 4, z >> 4);
				if(chunk) {
					chunk->setTileEntity(x & 0xF, y, z & 0xF, te);
				}
			}
		}
	}
}
bool_t Level::setTileNoUpdate(int32_t x, int32_t y, int32_t z, int32_t id) {
	return this->setTileAndData(x, y, z, id, 0, 4);
}
void Level::setTilesDirty(int32_t x1, int32_t y1, int32_t z1, int32_t x2, int32_t y2, int32_t z2) {
	for(auto&& ll: this->levelListeners) {
		ll->setTilesDirty(x1, y1, z1, x2, y2, z2);
	}
}
int32_t Level::setTime(int32_t newTime) { //long
	int32_t v3;							  // r4
	int32_t prevTimeSent;				  // r0

	v3 = newTime % 153600;
	this->levelData.setTime(newTime % 153600);
	prevTimeSent = this->prevTimeSent;
	if(prevTimeSent <= v3) {
		return v3 - prevTimeSent;
	} else {
		return 153600 - prevTimeSent + v3;
	}
}
void Level::setUpdateLights(bool_t a2) {
	this->_updateLights = a2;
}
void Level::setZombieAi(std::vector<struct Zombie*>& a2) {
	if(a2.size()) {
		for(int32_t i = 0; i < this->playersMaybe.size(); ++i) {
			Vec3 v9(this->playersMaybe[i]->posX, this->playersMaybe[i]->posY, this->playersMaybe[i]->posZ);
			std::nth_element(a2.begin(), a2.begin(), a2.end(), DistanceEntitySorter{v9.x, v9.y, v9.z});
		}
	}
}
void Level::swap(int32_t x, int32_t y, int32_t z, int32_t x2, int32_t y2, int32_t z2) {
	int32_t id2;   // r7
	int32_t meta2; // r0
	int32_t id1;   // [sp+8h] [bp-30h]
	int32_t meta1; // [sp+Ch] [bp-2Ch]

	id1 = this->getTile(x, y, z);
	meta1 = this->getData(x, y, z);
	id2 = this->getTile(x2, y2, z2);
	meta2 = this->getData(x2, y2, z2);
	this->setTileAndDataNoUpdate(x, y, z, id2, meta2);
	this->setTileAndDataNoUpdate(x2, y2, z2, id1, meta1);
	this->updateNeighborsAt(x, y, z, id2);
	this->updateNeighborsAt(x2, y2, z2, id1);
}
void Level::takePicture(struct TripodCamera* a2, struct Entity* a3) {
	for(auto&& ll: this->levelListeners) {
		ll->takePicture(a2, a3);
	}
}
void Level::tick(struct Entity* e) {
	this->tick(e, 1);
}
void Level::tick(struct Entity* ent, bool_t a3) {
	int32_t v6;		   // r6
	int32_t v7;		   // r0
	float posX;		   // t1
	float posY;		   // s15
	float posZ;		   // s15
	float pitch;	   // s15
	float yaw;		   // s15
	int32_t v14;	   // r6
	int32_t v15;	   // r9
	int32_t v16;	   // r0
	int32_t v17;	   // r7
	int32_t field_2C;  // r1
	LevelChunk* v19;   // r0
	Entity* rider;	   // r1
	double TimeS;	   // d8
	LevelChunk* chunk; // r0

	v6 = Mth::floor(ent->posX);
	v7 = Mth::floor(ent->posZ);
	if(!a3 || this->hasChunksAt(v6 - 32, 0, v7 - 32, v6 + 32, 128, v7 + 32)) {
		ent->prevPosX = ent->posX;
		ent->prevPosY = ent->posY;
		ent->prevPosZ = ent->posZ;
		ent->prevYaw = ent->yaw;
		ent->prevPitch = ent->pitch;
		if(a3) {
			if(ent->field_FD) {
				if(ent->ridingAt) {
					ent->rideTick();
				} else {
					ent->tick();
				}
			}
		}
		posX = ent->posX;
		posY = ent->posY;
		posZ = ent->posZ;
		pitch = ent->pitch;
		yaw = ent->yaw;
		v14 = Mth::floor(posX * 0.0625);
		v15 = Mth::floor(ent->posY * 0.0625);
		v16 = Mth::floor(ent->posZ * 0.0625);
		v17 = v16;
		if(ent->field_FD) {
			field_2C = ent->field_2C;
			if(field_2C == v14 && ent->field_30 == v15 && ent->field_34 == v16) {
				goto LABEL_17;
			}
			if(this->hasChunk(field_2C, ent->field_34)) {
				chunk = this->getChunk(ent->field_2C, ent->field_34);
				chunk->removeEntity(ent, ent->field_30);
			}
		}
		if(this->hasChunk(v14, v17)) {
			ent->field_FD = 1;
			v19 = this->getChunk(v14, v17);
			v19->addEntity(ent);
		} else {
			ent->field_FD = 0;
		}
LABEL_17:
		if(a3) {
			if(ent->field_FD) {
				rider = ent->rider;
				if(rider) {
					if(!rider->isDead && rider->ridingAt == ent) {
						this->tick(rider);
					} else {
						rider->ridingAt = 0;
						ent->rider = 0;
					}
				}
			}
		}
		TimeS = getTimeS();
		if(TimeS - this->field_B64_ >= 30.0) {
			this->saveLevelData();
			this->field_B64_ = TimeS;
		}
	}
}
void Level::tickEntities() {
	this->tickTemporaryPointers();
	for(int i = 0; i < this->field_B94.size(); ++i) {
		Entity* e = this->field_B94[i];
		if(e->isPlayer()) {
			this->field_B6C.emplace_back(PRInfo{e, 16});
		} else {
			delete e;
		}
	}
	this->field_B94.clear();

	for(int j = 0; j < this->entities.size(); ++j) {
		Entity* v9 = this->entities[j];
		if(v9->ridingAt) {
			if(!v9->ridingAt->isDead && v9->ridingAt->rider == v9) {
				continue;
			}
			v9->ridingAt->positionRider(0);
			v9->ridingAt->rider = 0;
			v9->ridingAt = 0;
		}

		if(!v9->isDead) {
			this->tick(v9);
		}
		if(v9->isDead && (!v9->isPlayer() || v9->field_108)) {
			if(v9->field_FD) {
				if(this->hasChunk(v9->field_2C, v9->field_34)) {
					LevelChunk* chunk = this->getChunk(v9->field_2C, v9->field_34);
					chunk->removeEntity(v9);
				}
			}
			this->eid2entity.erase(this->eid2entity.find(v9->entityId));
			this->entities.erase(this->entities.begin() + j);
			--j;
			this->entityRemoved(v9);
			this->field_B94.push_back(v9);
		}
	}
	int32_t v26 = this->field_B6C.size() - 1;
	while(v26 >= 0) {
		PRInfo* info = &this->field_B6C[v26];
		info->i -= 1;
		if(info->i <= 0) {
			if(info->entity) {
				delete info->entity;
			}
			this->field_B6C.erase(this->field_B6C.begin() + v26);
		}
		--v26;
	}

	this->field_5C = 1;
	for(int32_t v36 = 0; v36 < this->tileEntities.size(); ++v36) {
		TileEntity* v37 = this->tileEntities[v36];
		if(!v37->isRemoved()) {
			if(v37->level) {
				if(this->hasChunkAt(v37->posX, v37->posY, v37->posZ)) {
					v37->tick();
				}
			}
		}

		if(v37->isRemoved()) {
			this->tileEntities.erase(this->tileEntities.begin() + v36);
			--v36;
			if(this->hasChunk(v37->posX >> 4, v37->posZ >> 4)) {
				LevelChunk* v39 = this->getChunk(v37->posX >> 4, v37->posZ >> 4);
				if(v39) {
					v39->removeTileEntity(v37->posX & 0xf, v37->posY, v37->posZ & 0xf);
				}
			}
			delete v37;
		}
	}
	this->field_5C = 0;

	if(!this->field_50.empty()) {
		for(int32_t v42 = 0; v42 < this->field_50.size(); ++v42) {
			TileEntity* v9 = this->field_50[v42];
			if(!v9->isRemoved()) {
				bool v46 = 0;
				for(int32_t i = 0; i < this->tileEntities.size(); ++i) {
					if(this->tileEntities[i] == v9) {
						v46 = 1;
						break;
					}
				}

				int v47 = v9->posX;
				int v48 = v9->posZ;
				int v49 = v9->posY;
				LevelChunk* v50 = this->getChunk(v47 >> 4, v48 >> 4);
				if(v50 && v50->hasTileEntityAt(v9)) {
					if(!v46) {
						if(v9) {
							delete v9;
						}
						v9 = 0;
					}
				} else if(!v46) {
					this->tileEntities.push_back(v9);
				}

				if(v9) {
					if(v50) {
						v50->setTileEntity(v47 & 0xF, v49, v48 & 0xF, v9);
					}
				}
				this->sendTileUpdated(v47, v49, v48);
			}
		}
		this->field_50.clear();
	}
}
void Level::tickTemporaryPointers() {
	for(auto&& p: this->tickPtrSetImpl) { //TODO check
		p->invalidate();
	}
}
void Level::tileEntityChanged(int32_t x, int32_t y, int32_t z, struct TileEntity* te) {
	if(this->hasChunkAt(x, y, z)) {
		this->getChunkAt(x, z)->markUnsaved();
	}

	for(auto&& ll: this->levelListeners) {
		ll->tileEntityChanged(x, y, z, te);
	}
}
void Level::tileEvent(int32_t x, int32_t y, int32_t z, int32_t a5, int32_t a6) {
	int32_t id;

	if(this->chunkSource) {
		if(this->hasChunkAt(x, y, z)) {
			id = this->getTile(x, y, z);
			if(id > 0) {
				Tile::tiles[id]->triggerEvent(this, x, y, z, a5, a6);
			}

			for(auto&& ll: this->levelListeners) {
				ll->tileEvent(x, y, z, a5, a6);
			}
		}
	}
}
void Level::tileUpdated(int32_t x, int32_t y, int32_t z, int32_t oldid) {
	this->updateNeighborsAt(x, y, z, oldid);
}
void Level::unregisterTemporaryPointer(struct _TickPtr* a2) {
	this->tickPtrSetImpl.erase(a2);
}
void Level::updateLight(const struct LightLayer& a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8) {
	this->updateLight(a2, a3, a4, a5, a6, a7, a8, 1);
}

static int _D6E4DF94 = 0;
void Level::updateLight(const struct LightLayer& a2, int32_t a3, int32_t a4, int32_t minZ, int32_t maxX, int32_t maxY, int32_t maxZ, bool_t a9) {
	if((!this->dimensionPtr->hasNoSkyMaybe || &a2 != &LightLayer::Sky) && this->_updateLights) {
		int v13 = _D6E4DF94++;
		if(_D6E4DF94 == 50) {
LABEL_8:
			_D6E4DF94 = v13;
			return;
		}

		int v14 = (maxX - a3) / 2;
		LevelChunk* chunk;
		if(!this->hasChunkAt(v14, 64, (maxZ + minZ) / 2) || (chunk = this->getChunkAt(v14, (maxZ + minZ) / 2), chunk->isEmpty())) {
			v13 = _D6E4DF94 - 1;
			goto LABEL_8;
		}

		if(a9) {
			int v17 = 0;
			int v18 = this->lightsToUpdate.size();
			if(v18 >= 5) v18 = 5;

			while(v17 < v18) {
				LightUpdate* v19 = &this->lightsToUpdate[v17]; //TODO check
				if(v19->layer == &a2 && v19->expandToContain(a3, a4, minZ, maxX, maxY, maxZ)) {
					--_D6E4DF94;
					return;
				}
				++v17;
			}
		}
		LightUpdate v21(a2, a3, a4, minZ, maxX, maxY, maxZ);
		this->lightsToUpdate.emplace_back(v21);
		if(this->lightsToUpdate.size() > 28000027) { //TODO check size(in b1.7 it is 1000000)
			this->lightsToUpdate.clear();
		}
		--_D6E4DF94;
	}
}
void Level::updateLightIfOtherThan(const LightLayer& a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6) {
	int v10; // r9
	int v11; // r0

	v10 = a6;
	if(!this->dimensionPtr->hasNoSkyMaybe || &a2 != &LightLayer::Sky) {
		if(this->hasChunkAt(a3, a4, a5)) {
			if(&a2 == &LightLayer::Sky) {
				if(this->isSkyLit(a3, a4, a5)) {
					v10 = 15;
				}
			} else if(&a2 == &LightLayer::Block) {
				v11 = this->getTile(a3, a4, a5);
				if(a6 < Tile::lightEmission[v11]) {
					v10 = Tile::lightEmission[v11];
				}
			}
			if(this->getBrightness(a2, a3, a4, a5) != v10) {
				this->updateLight(a2, a3, a4, a5, a3, a4, a5);
			}
		}
	}
}
bool_t Level::updateLights() {
	int32_t lightUpdatesCnt; // r3
	int32_t v3;				 // r5

	lightUpdatesCnt = this->lightUpdatesCnt;
	if(lightUpdatesCnt <= 49) {
		v3 = 500;
		this->lightUpdatesCnt = lightUpdatesCnt + 1;
		while(1) {
			if(this->lightsToUpdate.size() <= 0) break;
			if(!--v3) {
				--this->lightUpdatesCnt;
				return 1;
			}
			LightUpdate lu = this->lightsToUpdate.back(); //creates a copy
			this->lightsToUpdate.pop_back();
			lu.update(this);
		}
		--this->lightUpdatesCnt;
	}
	return 0;
}
void Level::updateNeighborsAt(int32_t x, int32_t y, int32_t z, int32_t oldid) {
	this->neighborChanged(x - 1, y, z, x, y, z, oldid);
	this->neighborChanged(x + 1, y, z, x, y, z, oldid);
	this->neighborChanged(x, y - 1, z, x, y, z, oldid);
	this->neighborChanged(x, y + 1, z, x, y, z, oldid);
	this->neighborChanged(x, y, z - 1, x, y, z, oldid);
	this->neighborChanged(x, y, z + 1, x, y, z, oldid);
}
bool_t Level::updateSkyBrightness() {
	int32_t sd = this->getSkyDarken(1.0);
	if(sd == this->skyDarken) return 0;
	this->skyDarken = sd;
	return 1;
}
void Level::updateSkyDarken() {
	if(this->updateSkyBrightness()) {
		for(auto&& ll: this->levelListeners) {
			ll->skyColorChanged();
		}
	}
}
void Level::validateSpawn() {
	int32_t xSpawn; // r5
	int32_t zSpawn; // r4
	int8_t xx;		// r10
	int8_t zz;		// r10
	if(this->levelData.getYSpawn() <= 0) {
		this->levelData.setYSpawn(64);
	}
	xSpawn = this->levelData.getXSpawn();
	zSpawn = this->levelData.getZSpawn();
	while(!this->getTopTile(xSpawn, zSpawn) || this->getTopTile(xSpawn, zSpawn) == Tile::invisible_bedrock->blockID) {
		xx = this->random.genrand_int32();
		xSpawn += (xx & 7) - (this->random.genrand_int32() & 7);
		zz = this->random.genrand_int32();
		zSpawn += (zz & 7) - (this->random.genrand_int32() & 7);
		if(xSpawn <= 3) {
			xSpawn += 8;
		} else if(xSpawn > 251) {
			xSpawn -= 8;
		}
		if(zSpawn > 3) {
			if(zSpawn > 251) {
				zSpawn -= 8;
			}
		} else {
			zSpawn += 8;
		}
	}
	this->levelData.setXSpawn(xSpawn);
	this->levelData.setZSpawn(zSpawn);
}

//woah vt is so smol ty mojang <3
Level::~Level() {
	if(this->chunkSource) delete this->chunkSource;
	this->chunkSource = 0;
	if(this->dimensionPtr) delete this->dimensionPtr;
	this->dimensionPtr = 0;
	std::set<Entity*> v27;
	for(auto&& e: this->entities) {
		v27.insert(e);
	}
	for(auto&& p: this->playersMaybe) {
		v27.insert(p);
	}
	for(auto&& p: this->field_B6C) {
		v27.insert(p.entity);
	}
	for(auto&& e: v27) {
		if(e) {
			delete e;
		}
	}
	std::set<TileEntity*> v29;
	for(auto&& te: this->tileEntities) {
		v29.insert(te);
	}
	for(auto&& te: this->field_50) {
		v29.insert(te);
	}
	for(auto&& te: v29) {
		if(te) {
			delete te;
		}
	}
}
int32_t Level::getTile(int32_t x, int32_t y, int32_t z) {
	int8_t v5 = x;
	int8_t v6 = z;
	if(y < 0 || y > 127) return 0;
	LevelChunk* chunk = this->getChunk(x >> 4, z >> 4);
	return chunk->getTile(v5 & 0xf, y, v6 & 0xf);
}
bool_t Level::isEmptyTile(int32_t x, int32_t y, int32_t z) {
	return this->getTile(x, y, z) == 0;
}
float Level::getBrightness(int32_t x, int32_t y, int32_t z) {
	return this->dimensionPtr->lightRamp[this->getRawBrightness(x, y, z)];
}
int32_t Level::getData(int32_t x, int32_t y, int32_t z) {
	int8_t xx;		   // r4
	int8_t zz;		   // r5
	LevelChunk* chunk; // r0

	xx = x;
	zz = z;
	if(y < 0 || y > 127) {
		return 0;
	}
	chunk = this->getChunk(x >> 4, z >> 4);
	return chunk->getData(xx & 0xF, y, zz & 0xF);
}
struct Material* Level::getMaterial(int32_t x, int32_t y, int32_t z) {
	int32_t id = this->getTile(x, y, z);
	if(id) return (Material*)Tile::tiles[id]->material;
	return Material::air;
}

bool_t Level::isSolidRenderTile(int32_t x, int32_t y, int32_t z) {
	Tile* result; // r0

	result = Tile::tiles[this->getTile(x, y, z)];
	if(result) {
		return result->isSolidRender();
	}
	return 0;
}
bool_t Level::isSolidBlockingTile(int32_t x, int32_t y, int32_t z) {
	Tile* v4; // r4

	v4 = Tile::tiles[this->getTile(x, y, z)];
	if(v4 && v4->material->isSolidBlocking()) {
		return v4->isCubeShaped();
	} else {
		return 0;
	}
}
struct Biome* Level::getBiome(int32_t x, int32_t z) {
	return this->dimensionPtr->biomeSourcePtr->getBiome(x, z);
}
static int32_t _D6E4DF90 = 0;
void Level::tick() {
	if(!this->isClientMaybe) {
		if(this->levelData.getSpawnMobs()) {
			if(_D6E4DF90 + 1 > 1) {
				_D6E4DF90 = 0;
				bool spawnMonsters = this->spawnMonstersMaybe;
				if(spawnMonsters) spawnMonsters = this->difficulty > 0;
				bool spawnAnimals = this->spawnAnimalsMaybe;
				if(spawnAnimals) spawnAnimals = (this->getTime() % 400) <= 1;
				MobSpawner::tick(this, spawnMonsters, spawnAnimals);
			} else {
				++_D6E4DF90;
			}
		}
	}
	this->chunkSource->tick();
	this->updateSkyDarken();
	if(this->nightMode) {
		int32_t v6 = 12000;
		int32_t time = this->levelData.getTime();
		if(time % 19200 != 19200) {
			if(time % 19200 <= 11999 && (time + 20) % 19200 > 12000 || (v6 = time + 20, !((time + 20) % 20))) {
				this->_syncTime(v6);
			}
			this->setTime(v6);
		}
	} else {
		int32_t newTime = this->getTime() + 1;
		if(this->setTime(newTime) > 255) {
			this->_syncTime(newTime);
			this->prevTimeSent = this->getTime();
		}
	}
	this->tickPendingTicks(0);
	this->tickTiles();
	for(int32_t v9 = 0; v9 < this->entities.size(); ++v9) {
		Entity* e = this->entities[v9];
		SynchedEntityData* v11 = e->getEntityData();
		if(v11) {
			if(v11->isDirty) {
				SetEntityDataPacket pk(e->entityId, 0, v11->packDirty());
				this->rakNetInstance->send(pk);
			}
		}
	}
}
bool_t Level::tickPendingTicks(bool_t a2) {
	int32_t v4;	 // r6
	int32_t v5;	 // r8
	int32_t v10; // r0

	v4 = 0;
	if(this->tickDataTreeImpl.size() >= 100) {
		v5 = 100;
	} else {
		v5 = this->tickDataTreeImpl.size();
	}

	while(v4 < v5) {
		auto&& v8 = this->tickDataTreeImpl.begin();
		if(!a2) {
			if(v8->delay > this->levelData.getTime()) {
				break;
			}
		}
		if(this->hasChunksAt(v8->x - 8, v8->y - 8, v8->z - 8, v8->x + 8, v8->y + 8, v8->z + 8)) {
			v10 = this->getTile(v8->x, v8->y, v8->z);
			if(v10 == v8->field_10 && v10 > 0) {
				Tile::tiles[v10]->tick(this, v8->x, v8->y, v8->z, &this->random);
			}
		}
		this->tickDataTreeImpl.erase(v8);
		++v4;
	}

	return this->tickDataTreeImpl.size() != 0;
}
void Level::addToTickNextTick(int32_t x, int32_t y, int32_t z, int32_t id, int32_t delay) {
	int32_t v10;  // r0
	int32_t Time; // r0
	TickNextTickData v17(x, y, z, id);

	if(this->instantTick) {
		if(this->hasChunksAt(v17.x - 8, v17.y - 8, v17.z - 8, v17.x + 8, v17.y + 8, v17.z + 8)) {
			v10 = this->getTile(v17.x, v17.y, v17.z);
			if(v10 == v17.field_10 && v10 > 0) {
				Tile::tiles[v10]->tick(this, v17.x, v17.y, v17.z, &this->random);
			}
		}
	} else if(this->hasChunksAt(x - 8, y - 8, z - 8, x + 8, y + 8, z + 8)) {
		if(id > 0) {
			Time = this->levelData.getTime();
			v17.setDelay(delay + Time);
		}

		this->tickDataTreeImpl.insert(v17);
	}
}
void Level::updateSleepingPlayerList() {
}
struct ChunkSource* Level::createChunkSource() {
	LevelStorage* levelStoragePtr; // r0
	ChunkCache* v3;				   // r4
	ChunkStorage* v4;			   // r7
	ChunkSource* v5;			   // r9
	ChunkCache* v6;				   // r0
	LevelChunk* v7;				   // r7

	levelStoragePtr = this->levelStoragePtr;
	if(levelStoragePtr) {
		v4 = levelStoragePtr->createChunkStorage(this->dimensionPtr);
		v5 = this->dimensionPtr->createRandomLevelSource();
		v6 = new ChunkCache();
		v3 = v6;
		v6->generatorSource = v5;
		v6->chunkStorage = v4;
		v6->lastChunkX = -999999999;
		v6->lastChunkZ = -999999999;
		v6->level = this;
		v6->lastChunk = 0;
		v6->field_4 = 1;
		v7 = (LevelChunk*)operator new(0x2DCu);
		v3->emptyChunk = new EmptyLevelChunk(this);
		memset(v3->chunks, 0, sizeof(v3->chunks));
	} else {
		puts("no level data, calling dimension->createRandomLevelSource");
		return (ChunkSource*)this->dimensionPtr->createRandomLevelSource();
	}
	return (ChunkSource*)v3;
}

//no idea why are they stored in data
static ChunkPos _offsets[] = {{-1, -4}, {0, -4}, {1, -4}, {-2, -3}, {-1, -3}, {0, -3}, {1, -3}, {2, -3}, {-3, -2}, {-2, -2}, {-1, -2}, {0, -2}, {1, -2}, {2, -2}, {3, -2}, {-4, -1}, {-3, -1}, {-2, -1}, {-1, -1}, {0, -1}, {1, -1}, {2, -1}, {3, -1}, {4, -1}, {-4, 0}, {-3, 0}, {-2, 0}, {-1, 0}, {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {-4, 1}, {-3, 1}, {-2, 1}, {-1, 1}, {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {-3, 2}, {-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2}, {3, 2}, {-2, 3}, {-1, 3}, {0, 3}, {1, 3}, {2, 3}, {-1, 4}, {0, 4}, {1, 4}};

void Level::tickTiles() {
	this->somethingRelatedToChunkPos.clear();
	for(auto& p: this->playersMaybe) {
		int32_t posX = Mth::floor(p->posX * 0.0625);
		int32_t posZ = Mth::floor(p->posZ * 0.0625);

		for(int32_t i = 0; i < 57; ++i) {
			ChunkPos* off = &_offsets[i];
			int xx = (off->x + posX);
			if((uint32_t)xx <= 0xf) {
				int32_t zz = off->z + posZ;
				if(zz >= 0 && zz <= 15) {
					this->somethingRelatedToChunkPos.insert({xx, zz});
				}
			}
		}
	}

	for(auto& cp: this->somethingRelatedToChunkPos) {
		int32_t wx = 16 * cp.x;
		int32_t wz = 16 * cp.z;
		LevelChunk* chunk = this->getChunk(cp.x, cp.z);
		for(int32_t i = 0; i < 20; ++i) {
			uint32_t randXYZ = this->constRandom + 3 * this->prevRandomNumber;
			int32_t x = (randXYZ >> 2) & 0xF;
			int32_t z = (randXYZ >> 10) & 0xF;
			int32_t y = (randXYZ >> 18) & 0x7F;
			this->prevRandomNumber = randXYZ;
			int32_t v21 = chunk->getTile(x, y, z);
			if(Tile::shouldTick[v21]) {
				Tile::tiles[v21]->tick(this, x + wx, y, z + wz, &this->random);
			}
		}
	}
}
