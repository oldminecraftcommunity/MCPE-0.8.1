#include <tile/StairTile.hpp>
#include <level/Level.hpp>
#include <entity/Mob.hpp>
#include <math/HitResult.hpp>

int StairTile::DEAD_SPACES[8][2] = {{2, 6}, {3, 7}, {2, 3}, {6, 7}, {0, 4}, {1, 5}, {0, 1}, {4, 5}};
StairTile::StairTile(int32_t a2, Tile* a3, int32_t a4)
	: Tile(a2, a3->material) {
	this->block = a3;
	this->meta = a4;
	this->field_84 = 0;
	this->field_88 = 0;
	this->setDestroyTime(a3->blockHardness);
	this->setExplodeable(a3->blockResistance / 3.0);
	this->setSoundType(*a3->soundType);
	this->setLightBlock(255);
	this->field_5C = a3->field_5C;
}
bool_t StairTile::isLockAttached(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
	int32_t v9; // r0

	v9 = level->getTile(x, y, z);
	return StairTile::isStairs(v9) && level->getData(x, y, z) == a6;
}
bool_t StairTile::isStairs(int32_t id) {
	return id > 0 && Tile::tiles[id]->getRenderShape() == 10;
}
void StairTile::setBaseShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	int32_t v6; // r0

	v6 = level->getData(x, y, z); //lobyte = ...
	if((v6 & 4) != 0) {
		this->setShape(0.0, 0.5, 0.0, 1.0, 1.0, 1.0);
	} else {
		this->setShape(0.0, 0.0, 0.0, 1.0, 0.5, 1.0);
	}
}
bool_t StairTile::setInnerPieceShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	float v5;			   // s17
	float v10;			   // s16
	int32_t v11;			   // r0
	int32_t v12;			   // r7
	int32_t v13;			   // r3
	int32_t v15;			   // r11
	int32_t v16;			   // r10
	bool_t v17;			   // r0
	float v18;			   // r3
	float v19;			   // r0
	float v20;			   // r4
	float v21;			   // r1
	int32_t v22;			   // r11
	int32_t v23;			   // r10
	bool_t v24;			   // r0
	bool_t v25;			   // r0
	int32_t v26;			   // r11
	int32_t v27;			   // r10
	int32_t v28;			   // r11
	int32_t v29;			   // r10
	bool_t isLockAttached; // r0
	int32_t v31;			   // r10
	int32_t v32;			   // r10

	v5 = 0.0;
	v10 = 1.0;
	v11 = level->getData(x, y, z);
	v12 = v11;
	if((v11 & 4) != 0) {
		v10 = 0.5;
	} else {
		v5 = 0.5;
	}
	v13 = v11 & 3;
	switch(v13) {
		case 0:
			v15 = level->getTile(x - 1, y, z);
			v16 = level->getData(x - 1, y, z);
			if(!StairTile::isStairs(v15) || ((v16 ^ v12) & 4) != 0) {
				return 0;
			}
			v31 = v16 & 3;
			if(v31 != 3) {
				if(v31 != 2) {
					return 0;
				}
				isLockAttached = this->isLockAttached(level, x, y, z + 1, v12);
				goto LABEL_9;
			}
			v17 = this->isLockAttached(level, x, y, z - 1, v12);
			goto LABEL_25;
		case 1:
			v22 = level->getTile(x + 1, y, z);
			v23 = level->getData(x + 1, y, z);
			if(!StairTile::isStairs(v22) || ((v23 ^ v12) & 4) != 0) {
				return 0;
			}
			v32 = v23 & 3;
			if(v32 != 3) {
				if(v32 != 2) {
					return 0;
				}
				v25 = this->isLockAttached(level, x, y, z + 1, v12);
LABEL_18:
				if(v25) {
					return 0;
				}
				v19 = 1.0;
				v18 = 0.5;
LABEL_43:
				v20 = v19;
				v21 = v18;
				goto success_shape_set;
			}
			v24 = this->isLockAttached(level, x, y, z - 1, v12);
			break;
		case 2:
			v26 = level->getTile(x, y, z - 1);
			v27 = level->getData(x, y, z - 1);
			if(!StairTile::isStairs(v26) || ((v27 ^ v12) & 4) != 0) {
				return 0;
			}
			if((v27 & 3) == 1) {
				v17 = this->isLockAttached(level, x - 1, y, z, v12);
LABEL_25:
				if(v17) {
					return 0;
				}
				v19 = 0.5;
				v18 = 0.0;
				goto LABEL_43;
			}
			if((v27 & 3) != 0) {
				return 0;
			}
			v24 = this->isLockAttached(level, x + 1, y, z, v12);
			break;
		default:
			v28 = level->getTile(x, y, z + 1);
			v29 = level->getData(x, y, z + 1);
			if(!StairTile::isStairs(v28) || ((v29 ^ v12) & 4) != 0) {
				return 0;
			}
			if((v29 & 3) == 1) {
				isLockAttached = this->isLockAttached(level, x - 1, y, z, v12);
LABEL_9:
				if(!isLockAttached) {
					v18 = 0.5;
					v19 = 1.0;
					v20 = 0.5;
					v21 = 0.0;
success_shape_set:
					this->setShape(v21, v5, v18, v20, v10, v19);
					return 1;
				}
				return 0;
			}
			if((v29 & 3) != 0) {
				return 0;
			}
			v25 = this->isLockAttached(level, x + 1, y, z, v12);
			goto LABEL_18;
	}
	if(!v24) {
		v19 = 0.5;
		v18 = 0.0;
		v20 = 1.0;
		v21 = 0.5;
		goto success_shape_set;
	}
	return 0;
}
bool_t StairTile::setStepShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	int32_t blockMeta;		 // r0
	int32_t blockMeta2;		 // r7
	float maxY;				 // s19
	float minY;				 // s20
	int32_t metaAnd3;		 // r10
	int32_t v15;			 // r11
	int32_t v16;			 // r10
	bool_t isLockAttached;	 // r0
	float maxZ;				 // s15
	float minZ;				 // r3
	float minX;				 // r1
	float maxX;				 // s14
	int32_t blockMetaNearby; // r11
	int32_t v23;			 // r11
	int32_t v24;			 // r10
	int32_t v25;			 // r11
	int32_t v26;			 // r10
	int32_t v27;			 // r10
	int32_t v28;			 // r11
	int32_t blockIDNearby;	 // [sp+14h] [bp-44h]

	blockMeta = level->getData(x, y, z);
	blockMeta2 = blockMeta;
	if((blockMeta & 4) != 0) {
		maxY = 0.5;
	} else {
		maxY = 1.0;
	}
	if((blockMeta & 4) != 0) {
		minY = 0.0;
	} else {
		minY = 0.5;
	}
	metaAnd3 = blockMeta & 3;
	if(metaAnd3) {
		if(metaAnd3 == 1) {
			blockIDNearby = level->getTile(x - 1, y, z);
			blockMetaNearby = level->getData(x - 1, y, z);
			if(!StairTile::isStairs(blockIDNearby) || ((blockMetaNearby ^ blockMeta2) & 4) != 0) {
				maxZ = 1.0;
				minZ = 0.0;
				maxX = 0.5;
				goto LABEL_46;
			}
			v28 = blockMetaNearby & 3;
			if(v28 != 3) {
				if(v28 == 2 && !this->isLockAttached(level, x, y, z - 1, blockMeta2)) {
					goto LABEL_24;
				}
LABEL_20:
				metaAnd3 = 1;
				maxZ = 1.0;
				minZ = 0.0;
				maxX = 0.5;
LABEL_46:
				minX = minZ;
				goto _setAndReturn;
			}
			if(this->isLockAttached(level, x, y, z + 1, blockMeta2)) {
				goto LABEL_20;
			}
LABEL_21:
			maxZ = 0.5;
			metaAnd3 = 0;
			minZ = 0.0;
			goto LABEL_22;
		}
		if(metaAnd3 == 2) {
			v23 = level->getTile(x, y, z + 1);
			v24 = level->getData(x, y, z + 1);
			if(!StairTile::isStairs(v23) || ((v24 ^ blockMeta2) & 4) != 0) {
				metaAnd3 = 1;
				maxZ = 1.0;
				minZ = 0.5;
				minX = 0.0;
				maxX = 1.0;
				goto _setAndReturn;
			}
			if((v24 & 3) == 1) {
				if(!this->isLockAttached(level, x + 1, y, z, blockMeta2)) {
LABEL_24:
					minZ = 0.5;
					metaAnd3 = 0;
					maxZ = 1.0;
					maxX = 0.5;
LABEL_31:
					minX = 0.0;
					goto _setAndReturn;
				}
			} else if((v24 & 3) == 0 && !this->isLockAttached(level, x - 1, y, z, blockMeta2)) {
				goto LABEL_14;
			}
			maxZ = 1.0;
			metaAnd3 = 1;
			minZ = 0.5;
			maxX = 1.0;
			goto LABEL_31;
		}
		v25 = level->getTile(x, y, z - 1);
		v26 = level->getData(x, y, z - 1);
		if(!StairTile::isStairs(v25) || ((v26 ^ blockMeta2) & 4) != 0) {
			minZ = 0.0;
			metaAnd3 = 1;
			maxZ = 0.5;
			maxX = 1.0;
			goto LABEL_46;
		}
		if((v26 & 3) == 1) {
			if(!this->isLockAttached(level, x + 1, y, z, blockMeta2)) {
				goto LABEL_21;
			}
		} else if((v26 & 3) == 0) {
			isLockAttached = this->isLockAttached(level, x - 1, y, z, blockMeta2);
			if(!isLockAttached) {
				goto LABEL_42;
			}
		}
		metaAnd3 = 1;
		maxZ = 0.5;
		minZ = 0.0;
		maxX = 1.0;
		goto LABEL_46;
	}
	v15 = level->getTile(x + 1, y, z);
	v16 = level->getData(x + 1, y, z);
	if(!StairTile::isStairs(v15) || ((v16 ^ blockMeta2) & 4) != 0) {
		metaAnd3 = 1;
		maxZ = 1.0;
		minZ = 0.0;
		minX = 0.5;
		maxX = 1.0;
		goto _setAndReturn;
	}
	v27 = v16 & 3;
	if(v27 != 3) {
		if(v27 == 2 && !this->isLockAttached(level, x, y, z - 1, blockMeta2)) {
LABEL_14:
			metaAnd3 = 0;
			maxZ = 1.0;
			minZ = 0.5;
LABEL_22:
			maxX = maxZ;
			goto LABEL_46;
		}
		goto LABEL_12;
	}
	isLockAttached = this->isLockAttached(level, x, y, z + 1, blockMeta2);
	if(!isLockAttached) {
LABEL_42:
		metaAnd3 = isLockAttached;
		maxZ = 0.5;
		minZ = 0.0;
		minX = 0.5;
		maxX = 1.0;
		goto _setAndReturn;
	}
LABEL_12:
	maxZ = 1.0;
	metaAnd3 = 1;
	minZ = 0.0;
	minX = 0.5;
	maxX = 1.0;
_setAndReturn:
	this->setShape(minX, minY, minZ, maxX, maxY, maxZ);
	return metaAnd3;
}

StairTile::~StairTile() {
}
int32_t StairTile::getTileType() {
	return 1;
}
bool_t StairTile::isCubeShaped() {
	return 0;
}
int32_t StairTile::getRenderShape() {
	return 10;
}
void StairTile::updateShape(LevelSource*, int32_t, int32_t, int32_t) {
	int v5; // r1

	if(this->field_84) {
		v5 = this->field_88;
		this->setShape((float)(v5 % 2) * 0.5, (float)(v5 / 2 % 2) * 0.5, (float)(v5 / 4 % 2) * 0.5, (float)((float)(v5 % 2) * 0.5) + 0.5, (float)((float)(v5 / 2 % 2) * 0.5) + 0.5, (float)((float)(v5 / 4 % 2) * 0.5) + 0.5);
	} else {
		this->setShape(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
	}
}
void StairTile::addLights(Level* level, int32_t x, int32_t y, int32_t z) {
	this->block->addLights(level, x, y, z);
}
float StairTile::getBrightness(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	return this->block->getBrightness(level, x, y, z);
}
TextureUVCoordinateSet* StairTile::getTexture(int32_t a2) {
	return this->block->getTexture(a2, this->meta);
}
TextureUVCoordinateSet* StairTile::getTexture(int32_t a2, int32_t) {
	return this->block->getTexture(a2, this->meta);
}
TextureUVCoordinateSet* StairTile::getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t a6) {
	return this->block->getTexture(a6, this->meta);
}
void StairTile::addAABBs(Level* level, int32_t x, int32_t y, int32_t z, const AABB* aabb, std::vector<AABB>& vec) {
	bool_t v11; // r11

	this->setBaseShape(level, x, y, z);
	Tile::addAABBs(level, x, y, z, aabb, vec);
	v11 = this->setStepShape(level, x, y, z);
	Tile::addAABBs(level, x, y, z, aabb, vec);
	if(v11) {
		if(this->setInnerPieceShape(level, x, y, z)) {
			Tile::addAABBs(level, x, y, z, aabb, vec);
		}
	}
	this->setShape(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
}
AABB StairTile::getTileAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	return this->getTileAABB(level, x, y, z);
}
bool_t StairTile::isSolidRender() {
	return 0;
}
bool_t StairTile::mayPick() {
	return this->block->mayPick();
}
bool_t StairTile::mayPick(int32_t a2, bool_t a3) {
	return this->block->mayPick(a2, a3);
}
bool_t StairTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z, uint8_t) {
	return this->block->mayPlace(level, x, y, z);
}
int32_t StairTile::getTickDelay() {
	return this->block->getTickDelay();
}
void StairTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
	return this->block->tick(level, x, y, z, rng);
}
void StairTile::animateTick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
	return this->block->animateTick(level, x, y, z, rng);
}
void StairTile::destroy(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
	return this->block->destroy(level, x, y, z, a6);
}
void StairTile::onPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	this->neighborChanged(level, x, y, z, x, y, z, 0);
	return this->block->onPlace(level, x, y, z);
}
void StairTile::onRemove(Level* level, int32_t x, int32_t y, int32_t z) {
	return this->block->onRemove(level, x, y, z);
}
int32_t StairTile::getResourceCount(Random* rng) {
	return this->block->getResourceCount(rng);
}
float StairTile::getExplosionResistance(Entity* e) {
	return this->block->getExplosionResistance(e);
}
HitResult StairTile::clip(Level* level, int32_t x, int32_t y, int32_t z, const Vec3& a7, const Vec3& a8) {
	HitResult a1_40[8];
	int v14 = level->getData(x, y, z);
	int v15 = 0;
	int v17 = v14 & 7;
	this->field_84 = 1;
	do {
		this->field_88 = v15;
		a1_40[v15] = Tile::clip(level, x, y, z, a7, a8); //TODO check
		++v15;

	} while(v15 != 8);
	this->field_84 = 0;
	a1_40[StairTile::DEAD_SPACES[v17][0]] = HitResult();
	a1_40[StairTile::DEAD_SPACES[v17][1]] = HitResult();

	float v33 = 0;
	int v34 = 0;
	HitResult* v35 = 0;
	do {
		HitResult* v36 = &a1_40[v34];
		if(v36->hitType != 2) {
			float v37 = a8.y - v36->hitVec.y;
			float v38 = (float)((float)((float)(v37 * v37) + (float)((float)(a8.x - v36->hitVec.x) * (float)(a8.x - v36->hitVec.x))) + (float)((float)(a8.z - v36->hitVec.z) * (float)(a8.z - v36->hitVec.z)));
			if(v38 > v33) {
				v33 = v38;
				v35 = &a1_40[v34];
			}
		}
		++v34;
	} while(v34 != 8);

	if(v35) {
		return HitResult(*v35);
	}
	return HitResult();

}
void StairTile::wasExploded(Level* level, int32_t x, int32_t y, int32_t z) {
	this->block->wasExploded(level, x, y, z);
}
int32_t StairTile::getRenderLayer() {
	return this->block->getRenderLayer();
}
bool_t StairTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* p) {
	return this->block->use(level, x, y, z, p);
}
void StairTile::stepOn(Level* a2, int32_t x, int32_t y, int32_t z, Entity* e) {
	this->block->stepOn(a2, x, y, z, e);
}
int32_t StairTile::getPlacementDataValue(Level* level, int32_t x, int32_t y, int32_t z, int32_t data, float a7, float a8, float a9, Mob* a10, int32_t a11) {
	int8_t v11; // r0
	int32_t result; // r0
	float v13; // s15
	int32_t v14; // r3
	int32_t v15; // r3

	v11 = a11;
	if(!data || data != 1 && a8 > 0.5) {
		v11 = a11 | 4;
	}
	result = v11 & 4;
	v13 = (float)((float)(a10->yaw * 4.0) / 360.0) + 0.5;
	v14 = (int32_t)v13;
	if(v13 < (float)(int32_t)v13) {
		/*LOBYTE(v14)*/ v14 = v14 - 1;
	}
	v15 = v14 & 3;
	switch(v15) {
		case 0:
			return result | 2;
		case 1:
			return result | 1;
		case 2:
			return result | 3;
	}
	return result;
}
void StairTile::prepareRender(Level* level, int32_t x, int32_t y, int32_t z) {
	this->block->prepareRender(level, x, y, z);
}
void StairTile::attack(Level* level, int32_t x, int32_t y, int32_t z, Player* p) {
	this->block->attack(level, x, y, z, p);
}
void StairTile::handleEntityInside(Level* level, int32_t x, int32_t y, int32_t z, Entity* e, Vec3& v) {
	this->block->handleEntityInside(level, x, y, z, e, v);
}
