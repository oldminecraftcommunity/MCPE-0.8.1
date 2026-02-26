#include <entity/path/PathNavigation.hpp>
#include <entity/Mob.hpp>
#include <entity/ai/MoveControl.hpp>
#include <entity/path/Node.hpp>
#include <entity/path/Path.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

PathNavigation::PathNavigation(Mob* a2, Level* a3, float a4) {
	this->mob = a2;
	this->level = a3;
	this->field_10 = a4;
	this->field_20.x = 0.0;
	this->field_20.y = 0.0;
	this->field_20.z = 0.0;
	this->path = 0;
	this->speedMultiplier = 0.0;
	this->avoidSun = 0;
	this->field_18 = 0;
	this->field_1C = 0;
	this->_canPassDoors = 1;
	this->_canOpenDoors = 0;
	this->avoidWater = 0;
	this->canFloat = 0;
}
bool_t PathNavigation::canMoveDirectly(Vec3 a4, Vec3 a5, int32_t a8, int32_t a9, int32_t a10) {
	float x;		// s19
	float z;		// s18
	float v9;		// s17
	float y;		// s22
	float v11;		// s16
	int32_t v12;	// r5
	int32_t v13;	// r6
	float v14;		// r0
	float v15;		// s16
	float v16;		// s17
	int32_t result; // r0
	float v18;		// s26
	float v19;		// s27
	float v20;		// s20
	float v21;		// s21
	int32_t v22;	// r7
	int32_t v23;	// r8
	float v24;		// s20
	int32_t v25;	// r9
	float v26;		// s21
	int32_t v27;	// r11
	int32_t v28;	// r12
	int32_t v30;	// [sp+24h] [bp-6Ch]
	int32_t v31;	// [sp+28h] [bp-68h]

	x = a4.x;
	z = a4.z;
	v9 = a5.z - a4.z;
	y = a4.y;
	v11 = a5.x - a4.x;
	v12 = Mth::floor(a4.x);
	v13 = Mth::floor(z);
	if((float)((float)(v9 * v9) + (float)(v11 * v11)) < 0.000001) {
		return 0;
	}
	v14 = sqrtf((float)(v9 * v9) + (float)(v11 * v11));
	v15 = v11 * (float)(1.0 / v14);
	v16 = v9 * (float)(1.0 / v14);
	result = this->canWalkOn(v12, (int32_t)y, v13, a8 + 2, a9, a10 + 2, a4, v15, v16);
	if(result) {
		v18 = 1.0 / fabsf(v15);
		v19 = 1.0 / fabsf(v16);
		v20 = (float)v12 - x;
		v21 = (float)v13 - z;
		if(v15 >= 0.0) {
			v20 = v20 + 1.0;
		}
		if(v16 >= 0.0) {
			v21 = v21 + 1.0;
		}
		if(v15 >= 0.0) {
			v22 = 1;
		} else {
			v22 = -1;
		}
		if(v16 >= 0.0) {
			v23 = 1;
		} else {
			v23 = -1;
		}
		v24 = v20 / v15;
		v25 = Mth::floor(a5.x);
		v31 = v25 - v12;
		v26 = v21 / v16;
		v27 = Mth::floor(a5.z);
		v28 = v27 - v13;
		while(v22 * v31 > 0 || v23 * v28 > 0) {
			if(v24 < v26) {
				v12 += v22;
				v24 = v24 + v18;
				v31 = v25 - v12;
			} else {
				v26 = v26 + v19;
				v13 += v23;
				v28 = v27 - v13;
			}
			v30 = v28;
			result = this->canWalkOn(v12, (int32_t)y, v13, a8, a9, a10, {x, y, z}, v15, v16);
			v28 = v30;
			if(!result) {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
bool_t PathNavigation::canOpenDoors() {
	return this->_canOpenDoors;
}
bool_t PathNavigation::canPassDoors() {
	return this->_canPassDoors;
}
bool_t PathNavigation::canUpdatePath() {
	if(this->mob->onGround) return 1;
	if(this->canFloat) return this->isInLiquid();
	return 0;
}
bool_t PathNavigation::canWalkAbove(int32_t x, int32_t y, int32_t z, int32_t xsize, int32_t ysize, int32_t zsize, Vec3 a8, float a11, float a12) {
	int32_t xx;	 // r4
	int32_t zz;	 // r5
	int32_t v16; // r0
	int32_t yy;	 // r6

	for(xx = x; xx < x + xsize; ++xx) {
		for(yy = y; yy < y + ysize; ++yy) {
			for(zz = z; zz < zsize + z; ++zz) {
				if((float)((float)((float)((float)((float)zz + 0.5) - a8.z) * a12) + (float)((float)((float)((float)xx + 0.5) - a8.x) * a11)) >= 0.0) {
					v16 = this->level->getTile(xx, yy, zz);
					if(v16 > 0) {
						if(!Tile::tiles[v16]->isPathfindable(this->level, xx, yy, zz)) {
							return 0;
						}
					}
				}
			}
		}
	}
	return 1;
}
bool_t PathNavigation::canWalkOn(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, Vec3 a8, float a9, float a10) {
	int32_t v12;			  // r8
	int32_t v13;			  // r4
	int32_t v14;			  // r11
	int32_t v16;			  // r0
	const Material* material; // r3
	int32_t v18;			  // r0
	int32_t i;				  // r5
	const Material* v20;	  // [sp+24h] [bp-44h]

	v12 = a4 - a7 / 2;
	v13 = a2 - a5 / 2;
	if(!this->canWalkAbove(v13, a3, v12, a5, a6, a7, a8, a9, a10)) {
		return 0;
	}
	v14 = v13 + a5;
	while(v13 < v14) {
		for(i = v12; i < v12 + a7; ++i) {
			if((float)((float)((float)((float)((float)i + 0.5) - a8.z) * a10) + (float)((float)((float)((float)v13 + 0.5) - a8.x) * a9)) >= 0.0) {
				v16 = this->level->getTile(v13, a3 - 1, i);
				if(v16 <= 0) {
					return 0;
				}
				material = Tile::tiles[v16]->material;
				if(material == Material::water) {
					v20 = Tile::tiles[v16]->material;
					v18 = this->mob->isInWater();
					material = v20;
					if(!v18) {
						return 0;
					}
				}
				if(material == Material::lava) {
					return 0;
				}
			}
		}
		++v13;
	}
	return 1;
}
Path* PathNavigation::createPath(Mob* a2) {
	if(this->canUpdatePath()) {
		return this->level->findPath(this->mob, a2, this->field_10, this->_canPassDoors, this->_canOpenDoors, this->avoidWater, this->canFloat);
	}
	return 0;
}
Path* PathNavigation::createPath(float x, float y, float z) {
	if(this->canUpdatePath()) {
		return this->level->findPath(this->mob, Mth::floor(x), (int32_t)y, Mth::floor(z), this->field_10, this->_canPassDoors, this->_canOpenDoors, this->avoidWater, this->canFloat);
	}
	return 0;
}
bool_t PathNavigation::getAvoidWater() {
	return this->avoidWater;
}
Path* PathNavigation::getPath() {
	return this->path;
}
int32_t PathNavigation::getSurfaceY() {
	int32_t v2;	  // r0
	Mob* mob;	  // r6
	Level* level; // r8
	int32_t minY; // r4
	int32_t v6;	  // r10
	int32_t v7;	  // r9
	int32_t v8;	  // r0
	int32_t v9;	  // r0
	Mob* v10;	  // r8
	Level* v11;	  // r6
	int32_t v12;  // r11
	int32_t v13;  // r0

	v2 = this->mob->isInWater();
	mob = this->mob;
	if(!v2 || !this->canFloat) {
		return (int32_t)(mob->boundingBox.minY + 0.5);
	}
	level = this->level;
	minY = (int32_t)mob->boundingBox.minY;
	v6 = minY + 17;
	v7 = Mth::floor(mob->posX);
	v8 = Mth::floor(mob->posZ);
	v9 = level->getTile(v7, minY, v8);
	while(v9 == Tile::water->blockID || v9 == Tile::calmWater->blockID) {
		v10 = this->mob;
		++minY;
		v11 = this->level;
		v12 = Mth::floor(this->mob->posX);
		v13 = Mth::floor(v10->posZ);
		v9 = v11->getTile(v12, minY, v13);
		if(minY == v6) {
			return (int32_t)this->mob->boundingBox.minY;
		}
	}
	return minY;
}
Vec3 PathNavigation::getTempMobPos() {
	float x;   // s16
	int32_t y; // r0
	float z;   // s14

	x = this->mob->posX;
	y = this->getSurfaceY();
	z = this->mob->posZ;
	return Vec3(x, y, z);
}
bool_t PathNavigation::isDone() {
	return !this->path || this->path->isDone();
}
bool_t PathNavigation::isInLiquid() {
	if(this->mob->isInWater()) return 1;
	return this->mob->isInLava();
}
bool_t PathNavigation::moveTo(Mob* a2, float speedm) {
	Path* p = this->createPath(a2);
	if(p) {
		return this->moveTo(p, speedm);
	}
	return 0;
}
bool_t PathNavigation::moveTo(Path* a2, float speedMultiplier) {
	int32_t v9; // r3

	if(a2) {
		if(a2->sameAs(this->path)) {
			delete a2;
		} else {
			if(this->path) {
				delete this->path;
			}
			this->path = a2;
		}
		if(this->avoidSun) {
			this->trimPathFromSun();
		}
		if(this->path->getSize()) {
			v9 = this->field_18;
			this->speedMultiplier = speedMultiplier;
			this->field_1C = v9;
			this->field_20 = this->getTempMobPos();
			return 1;
		}
		return 0;
	} else {
		if(this->path) {
			delete this->path;
		}
		this->path = 0;
		return 0;
	}
}
bool_t PathNavigation::moveTo(float x, float y, float z, float sm) {
	return this->moveTo(this->createPath(x, y, z), sm);
}
void PathNavigation::setAvoidSun(bool_t a2) {
	this->avoidSun = a2;
}
void PathNavigation::setAvoidWater(bool_t a2) {
	this->avoidWater = a2;
}
void PathNavigation::setCanFloat(bool_t a2) {
	this->canFloat = a2;
}
void PathNavigation::setCanOpenDoors(bool_t a2) {
	this->_canOpenDoors = a2;
}
void PathNavigation::setCanPassDoors(bool_t a2) {
	this->_canPassDoors = a2;
}
void PathNavigation::setLevel(Level* a2) {
	this->level = a2;
}
void PathNavigation::setSpeed(float a2) {
	this->speedMultiplier = a2;
}
void PathNavigation::stop() {
	if(this->path) {
		delete this->path;
	}
	this->path = 0;
}
void PathNavigation::tick() {
	++this->field_18;
	if(!this->isDone()) {
		if(this->canUpdatePath()) {
			this->updatePath();
		}
		if(!this->isDone()) {
			Vec3 a2 = this->path->currentPos(this->mob);
			this->mob->getMoveControl()->setWantedPosition(a2.x, a2.y, a2.z, this->speedMultiplier);
		}
	}
}
void PathNavigation::trimPathFromSun() {
	Mob* mob;	// r5
	int32_t v3; // r6
	int32_t v4; // r0
	Node* v5;	// r0
	int32_t i;	// r5

	mob = this->mob;
	v3 = Mth::floor(this->mob->posX);
	v4 = Mth::floor(mob->posZ);
	if(!this->level->canSeeSky(v3, (int32_t)(mob->boundingBox.minY + 0.5), v4)) {
		for(i = 0; i < this->path->getSize(); ++i) {
			v5 = this->path->get(i);
			if(this->level->canSeeSky(v5->xCoord, v5->yCoord, v5->zCoord)) {
				this->path->setSize(i - 1);
				return;
			}
		}
	}
}
void PathNavigation::updatePath() {
	int32_t sz;			  // r6
	int32_t i;			  // r7
	Path* path;			  // r0
	float v5;			  // s16
	int32_t j;			  // r7
	Mob* mob;			  // r7
	int32_t v8;			  // r6
	int32_t a8;			  // r8
	int32_t entityHeight; // s15
	float x;			  // r0
	float y;			  // r1
	float z;			  // r2
	Vec3* v14;			  // r4
	Node* v15;			  // r0

	Vec3 v16 = this->getTempMobPos();
	sz = this->path->getSize();
	for(i = this->path->getIndex();; ++i) {
		path = this->path;
		if(!path || i >= path->getSize()) {
			break;
		}
		v15 = this->path->get(i);
		if(v15->yCoord != (int32_t)v16.y) {
			sz = i;
			break;
		}
	}
	v5 = this->mob->entityWidth * this->mob->entityWidth;
	for(j = this->path->getIndex(); j < sz; ++j) {
		Vec3 result = this->path->getPos(this->mob, j);
		if((float)((float)((float)((float)(result.y - v16.y) * (float)(result.y - v16.y)) + (float)((float)(result.x - v16.x) * (float)(result.x - v16.x))) + (float)((float)(result.z - v16.z) * (float)(result.z - v16.z))) < v5) {
			this->path->setIndex(j + 1);
		}
	}
	mob = this->mob;
	v8 = sz - 1;
	a8 = (int32_t)ceilf(this->mob->entityWidth);
	entityHeight = (int32_t)mob->entityHeight;
	while(v8 >= this->path->getIndex()) {
		Vec3 result = this->path->getPos(this->mob, v8);
		if(this->canMoveDirectly(v16, result, a8, entityHeight + 1, a8)) {
			this->path->setIndex(v8);
			break;
		}
		--v8;
	}
	if(this->field_18 - this->field_1C > 100) {
		if((float)((float)((float)((float)(this->field_20.y - v16.y) * (float)(this->field_20.y - v16.y)) + (float)((float)(this->field_20.x - v16.x) * (float)(this->field_20.x - v16.x))) + (float)((float)(this->field_20.z - v16.z) * (float)(this->field_20.z - v16.z))) < 2.25) {
			this->stop();
		}
		x = v16.x;
		y = v16.y;
		z = v16.z;
		this->field_1C = this->field_18;
		v14 = &this->field_20;
		v14->x = x;
		v14->y = y;
		v14->z = z;
	}
}
PathNavigation::~PathNavigation() {
	if(this->path) delete this->path;
}
