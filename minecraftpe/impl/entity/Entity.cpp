#include <entity/Entity.hpp>
#include <tile/Tile.hpp>
#include <math/Mth.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <tile/material/Material.hpp>
#include <math/Vec3.hpp>
#include <utils.h>
#include <nbt/CompoundTag.hpp>
#include <entity/ItemEntity.hpp>
#include <GL/gl.h>
#include <string.h>
#include <util/EntityPos.hpp>
#include <nbt/ListTagFloatAdder.hpp>
#include <nbt/ListTag.hpp>
#include <nbt/FloatTag.hpp>

std::string Entity::RIDING_TAG = "Riding";
Random Entity::sharedRandom(getEpochTimeS());
int32_t Entity::entityCounter = 0;

Entity::Entity(Level* a2) : field_84(0, 0, 0, 0), boundingBox{0, 0, 0, 0, 0, 0}{
	this->somethingRelatedToRenderer = 1.0;
	this->field_2C = 0;
	this->field_30 = 0;
	this->field_34 = 0;
	this->posX = 0.0;
	this->posY = 0.0;
	this->posZ = 0.0;
	this->level = a2;
	this->prevX = 0.0;
	this->prevY = 0.0;
	this->prevZ = 0.0;
	this->motionX = 0.0;
	this->motionY = 0.0;
	this->motionZ = 0.0;
	this->yaw = 0.0;
	this->pitch = 0.0;
	this->prevYaw = 0.0;
	this->prevPitch = 0.0;
	this->field_6C = 0.0;
	this->field_70 = 0.0;
	this->field_74 = 0.0;
	this->field_78 = 0.0;
	this->field_7C = 0.0;
	this->field_80 = 0.0;
	this->entityWidth = 0.6;
	this->field_D8 = 0;
	this->field_DC = 0;
	this->air = 300;
	this->fire = 0;
	this->entityRenderId = ER_NONE;
	this->rider = 0;
	this->ridingAt = 0;
	this->field_FC = 0;
	this->field_FD = 0;
	this->onGround = 0;
	this->isCollidedHorizontally = 0;
	this->field_100 = 0;
	this->field_101 = 0;
	this->wasHurt = 0;
	this->isDead = 0;
	this->noclip = 0;
	this->field_107 = 0;
	this->field_108 = 0;
	this->entityHeight = 1.8;
	this->ridingHeight = 0.0;
	this->field_E8 = 1;
	this->field_103 = 1;
	this->field_106 = 1;
	this->field_B8 = 0.0;
	this->field_BC = 0.0;
	this->prevPosX = 0.0;
	this->prevPosY = 0.0;
	this->prevPosZ = 0.0;
	this->ySize = 0.0;
	this->stepHeight = 0.0;
	this->field_D4 = 0.0;
	this->fallDistance = 0.0;
	this->field_10C = 300;
	this->field_110 = 1;
	this->field_111 = 0;
	this->field_112 = 0;
	this->field_113 = 1;
	this->field_114 = 1;
	this->maybeIsInWeb = 0;
	this->_init();
	this->entityId = ++Entity::entityCounter;
	this->setPos(0.0, 0.0, 0.0);
}
void Entity::_init() {
	float posX; // r3
	float posY; // r3
	float posZ; // r3

	posX = this->posX;
	this->prevPosX = posX;
	this->prevX = posX;
	posY = this->posY;
	this->prevPosY = posY;
	this->prevY = posY;
	posZ = this->posZ;
	this->prevPosZ = posZ;
	this->prevZ = posZ;
	this->prevPitch = this->pitch;
	this->prevYaw = this->yaw;
	this->fire = 0;
	this->isDead = 0;
	this->fallDistance = 0.0;
}
void Entity::checkTileCollisions() {
	int32_t minX; // r6
	int32_t minY; // r9
	int32_t minZ; // r10
	int32_t maxZ; // r11
	int32_t v6; // r0
	int32_t j; // r7
	int32_t i; // r5
	int32_t v9; // r5
	int32_t v10; // r3
	int32_t v11; // r6
	Level* level; // r6
	float Float; // s16
	float v14; // s15
	int32_t maxX; // [sp+18h] [bp-48h]
	int32_t maxY; // [sp+1Ch] [bp-44h]

	minX = Mth::floor(this->boundingBox.minX);
	minY = Mth::floor(this->boundingBox.minY);
	minZ = Mth::floor(this->boundingBox.minZ);
	maxX = Mth::floor(this->boundingBox.maxX);
	maxY = Mth::floor(this->boundingBox.maxY);
	maxZ = Mth::floor(this->boundingBox.maxZ);
	if(this->level->hasChunksAt(minX, minY, minZ, maxX, maxY, maxZ)) {
		while(minX <= maxX) {
			for(i = minY; i <= maxY; ++i) {
				for(j = minZ; j <= maxZ; ++j) {
					v6 = this->level->getTile(minX, i, j);
					if(v6 > 0) {
						Tile::tiles[v6]->entityInside(this->level, minX, i, j, this);
					}
				}
			}
			++minX;
		}
	}
	if(!this->field_112) {
		v9 = this->isInWater();
		if(this->level->containsFireTile(this->boundingBox)) {
			this->burn(1);
			if(v9) {
LABEL_16:
				if(this->isOnFire()) {
					level = this->level;
					v11 = 50;
					level->playSound(this, "random.fizz", 0.7, (float)((float)(Entity::sharedRandom.nextFloat() - Entity::sharedRandom.nextFloat()) * 0.4) + 1.6);
					this->fire = -this->field_E8;
					do {
						Vec3 a3 = this->getRandomPointInAABB(Entity::sharedRandom);
						this->level->addParticle(PT_EXPLODE, a3.x, a3.y, a3.z, 0.0, 0.0, 0.0, 0);
						--v11;
					} while(v11);
				}
				return;
			}
			v10 = this->fire + 1;
			this->fire = v10;
			if(!v10) {
				this->fire = 300;
			}
		} else {
			if(this->fire <= 0) {
				this->fire = -this->field_E8;
			}
			if(v9) {
				goto LABEL_16;
			}
		}
	}
}
float Entity::distanceTo(Entity* a2) {
	float xd; // s13
	float yd; // s15
	float zd; // s14

	xd = this->posX - a2->posX;
	yd = this->posY - a2->posY;
	zd = this->posZ - a2->posZ;
	return sqrt((float)((float)((float)(yd * yd) + (float)(xd * xd)) + (float)(zd * zd)));
}
float Entity::distanceTo(float x, float y, float z) {
	return sqrt((float)((float)((float)((float)(this->posY - y) * (float)(this->posY - y)) + (float)((float)(this->posX - x) * (float)(this->posX - x))) + (float)((float)(this->posZ - z) * (float)(this->posZ - z))));
}
float Entity::distanceToSqr(Entity* e) {
	float xd; // s13
	float yd; // s15
	float zd; // s14

	xd = this->posX - e->posX;
	yd = this->posY - e->posY;
	zd = this->posZ - e->posZ;
	return (float)((float)(yd * yd) + (float)(xd * xd)) + (float)(zd * zd);
}
float Entity::distanceToSqr(float x, float y, float z) {
	return (float)((float)((float)(this->posY - y) * (float)(this->posY - y)) + (float)((float)(this->posX - x) * (float)(this->posX - x))) + (float)((float)(this->posZ - z) * (float)(this->posZ - z));
}
Vec3 Entity::getRandomPointInAABB(Random& a3){
	float f;  // r8
	float v7; // r7
	float v8; // r0

	f = a3.nextFloat();
	v7 = a3.nextFloat();
	v8 = a3.nextFloat();
	Vec3 v9(f, v7, v8);
	Vec3 v10(this->boundingBox.minX, this->boundingBox.minY, this->boundingBox.minZ);
	Vec3 v11(this->boundingBox.maxX, this->boundingBox.maxY, this->boundingBox.maxZ);
	return Vec3(v10.x + (float)((float)(v11.x - v10.x) * v9.x), v10.y + (float)((float)(v11.y - v10.y) * v9.y), v10.z + (float)((float)(v11.z - v10.z) * v9.z));
}
int32_t Entity::hashCode() {
	return this->entityId;
}
bool_t Entity::isRiding() {
	return this->ridingAt != 0;
}
bool_t Entity::operator==(Entity& a2) {
	return this->entityId == a2.entityId;
}
bool_t Entity::saveAsMount(CompoundTag* a2) {
	if(this->isDead) return 0;
	a2->putInt("id", this->getEntityTypeId());
	this->saveWithoutId(a2);
	return 1;
}
void Entity::setOnFire(int32_t seconds) {
	int32_t fire; // r3
	int32_t newOnFire; // r1

	fire = this->fire;
	newOnFire = 20 * seconds;
	if(newOnFire < fire) {
		this->fire = fire;
	} else {
		this->fire = newOnFire;
	}
}
float Entity::setupLighting(bool_t a2, float a3) {
	float v6; // r0
	float v7; // s16
	int32_t v8; // r8
	float x; // s20
	float y; // s19
	float z; // s18
	float field_78; // s14
	float g; // r1
	float b; // r2
	float v16; // s13
	float v17; // s14
	float v18; // s15
	float v19; // s14
	float v20; // s13
	float v21; // s21
	float v22; // s15
	float v23; // r0
	float v24; // r1
	float v25; // r2
	float r; // r0
	float v27; // r1
	float v28; // r2
	float a;

	v6 = this->getBrightness(a3);
	v7 = v6;
	if(v6 > 1.0) {
		v7 = 1.0;
	} else if(v6 <= 0.35) {
		v7 = 0.35;
	}
	if(a2) {
		v8 = this->isSkyLit();

		Vec3 result = v8 ? this->level->getSunlightDirection(a3) : Vec3(0.5, 1.0, 0.5).normalized(); // [sp+14h] [bp-9Ch] BYREF
		x = result.x;
		y = result.y;
		z = result.z;
		if(this->isOnFire()) {
			v7 = 1.0;
			x = Vec3::NEG_UNIT_Y.x;
			y = Vec3::NEG_UNIT_Y.y;
			z = Vec3::NEG_UNIT_Y.z;
		} else if(!v8) {
			v7 = v7 * 1.3;
		}
		field_78 = this->field_78;
		Vec3 ret = (field_78 == 0.0 && this->field_7C == 0.0 && this->field_80 == 0.0) ? Vec3(x, y, z) : Vec3(field_78 + (float)((float)(x - field_78) * 0.1), this->field_7C + (float)((float)(y - this->field_7C) * 0.1), this->field_80 + (float)((float)(z - this->field_80) * 0.1)); // [sp+70h] [bp-40h] BYREF
		Vec3 v30 = ret.normalized();

		this->field_78 = v30.x;
		this->field_7C = v30.y;
		this->field_80 = v30.z;
		float params[4]; // [sp+20h] [bp-90h] BYREF
		memset(params, 0, sizeof(params));
		params[0] = this->field_78;
		params[1] = this->field_7C;
		params[2] = this->field_80;
		glLightfv(0x4000u, 0x1203u, params);

		Color4 col2(v7, v7, v7, 1.0); // [sp+30h] [bp-80h] BYREF
		Color4 v34(0, 0, 0, 0); //memset(&v34, 0, sizeof(v34));

		if(v8) {
			Color4 _ret = this->level->getSkyColor(this, a3);
			Color4 col = Color4::lerp(_ret, col2, 0.5);
			Color4 v36 = this->level->getSunriseColor(a3);
			_ret = Color4::lerp(col, v36, v36.a);
			v34.a = 1.0;
			v34.g = v7 * _ret.g;
			v34.b = v7 * _ret.b;
			v34.r = _ret.r * v7;
		}
		v34.r = v34.r + col2.r;
		v34.g = v34.g + col2.g;
		v34.b = v34.b + col2.b;
		v34.a = v34.a + col2.a;
		if(this->field_84.r == 0.0 && this->field_84.g == 0.0 && this->field_84.b == 0.0 && this->field_84.a == 0.0) {
			r = v34.r;
			v27 = v34.g;
			v28 = v34.b;
			a = v34.a;
		} else {
			Color4 v30 = Color4::lerp(this->field_84, v34, 0.1);
			r = v30.r;
			v27 = v30.g;
			v28 = v30.b;
			a = v30.a;
		}
		this->field_84.r = r;
		this->field_84.g = v27;
		this->field_84.b = v28;
		this->field_84.a = a;
		v16 = (float)(v7 * this->field_84.r) + (float)(v7 * this->field_84.r);
		v17 = (float)(v7 * this->field_84.g) + (float)(v7 * this->field_84.g);
		v18 = (float)(v7 * this->field_84.b) + (float)(v7 * this->field_84.b);
		if(v16 > 1.0) {
			v16 = 1.0;
		} else if(v16 <= 0.0) {
			v16 = 0.0;
		}
		float _ret[4];
		_ret[0] = v16;
		if ( v17 > 1.0 )
		{
			v17 = 1.0;
		}
		else if ( v17 <= 0.0 )
		{
			v17 = 0.0;
		}
		_ret[1] = v17;
		if ( v18 > 1.0 )
		{
			v18 = 1.0;
		}
		else if ( v18 <= 0.0 )
		{
			v18 = 0.0;
		}
		_ret[2] = v18;
		_ret[3] = 1.0;
		glLightfv(0x4000u, 0x1201u, _ret);
		v19 = this->field_84.g;
		v20 = this->field_84.r;
		_ret[3] = 1.0;
		v21 = (float)(v7 + v7) + 0.5;
		v22 = v21 * this->field_84.b;
		_ret[1] = v21 * v19;
		_ret[2] = v22;
		_ret[0] = v20 * v21;
		glLightfv(0x4000u, 0x1200u, _ret);
		v23 = 1.0;
		v24 = 1.0;
		v25 = 1.0;
	}
	else
	{
		v23 = v7;
		v24 = v7;
		v25 = v7;
	}
	glColor4f(v23, v24, v25, 1.0);
	return v7;
}

Entity::~Entity() {
}
void Entity::reset() {
	this->_init();
}
void Entity::setLevel(Level* a2) {
	this->level = a2;
}
void Entity::remove() {
	this->isDead = 1;
}
void Entity::setPos(float x, float y, float z) {
	float entityWidth; // s11
	float radius; // s15
	float minY; // s12
	float entityHeight; // s11

	entityWidth = this->entityWidth;
	this->posX = x;
	this->posY = y;
	this->posZ = z;
	radius = entityWidth * 0.5;
	minY = (float)(y - this->ridingHeight) + this->ySize;
	entityHeight = this->entityHeight;
	this->boundingBox.minY = minY;
	this->boundingBox.minX = x - radius;
	this->boundingBox.maxY = minY + entityHeight;
	this->boundingBox.minZ = z - radius;
	this->boundingBox.maxX = x + radius;
	this->boundingBox.maxZ = z + radius;
}
void Entity::move(float dx, float dy, float dz) {
	float movX;			// s16
	float movY;			// s24
	float movZ;			// s17
	float minY;			// s13
	float v9;			// s14
	float minZ;			// s13
	float posX;			// s26
	float posZ;			// s27
	float maxX;			// s13
	float maxY;			// s14
	float maxZ;			// s15
	float minX;			// s10
	Level* level;		// r0
	float v18;			// s12
	float v20;			// s13
	float v21;			// s14
	float v22;			// s15
	float v23;			// s10
	Level* v24;			// r0
	float v25;			// s12
	float v27;			// s13
	float v28;			// s14
	float v29;			// s15
	float v30;			// s10
	Level* v31;			// r0
	float v32;			// s12
	int32_t v34;		// r9
	Level* v35;			// r6
	float v36;			// s21
	int32_t v37;		// r7
	uint32_t v40;		// r11
	float v41;			// r0
	float v42;			// s18
	float v43;			// s20
	bool_t fallingFlag; // r7
	int32_t v45;		// r10
	uint32_t v47;		// r12
	float v48;			// r0
	int32_t v49;		// r10
	uint32_t v51;		// r12
	float v52;			// r0
	float stepHeight;	// s22
	float v54;			// r0
	float v55;			// r1
	Level* v56;			// r7
	Level* v57;			// r0
	int32_t v58;		// r7
	uint32_t v61;		// r11
	float v62;			// r0
	float v63;			// s19
	float v64;			// s23
	int32_t v65;		// r7
	uint32_t v67;		// r11
	float v68;			// r0
	int32_t v71;		// r6
	uint32_t v72;		// r10
	float v73;			// r0
	float v74;			// s13
	float v75;			// s14
	float v76;			// s13
	bool_t v77;			// r3
	bool v78;			// r2
	bool v79;			// r3
	bool_t field_110;	// r3
	float v82;			// s14
	float v83;			// s15
	double v84;			// d7
	float v85;			// r0
	float v86;			// s13
	int32_t v87;		// r9
	int32_t v88;		// r7
	int32_t v89;		// r10
	int32_t v90;		// r0
	int32_t blockID;	// r5
	float field_BC;		// s15
	uint32_t v93;		// [sp+Ch] [bp-A4h]
	uint32_t v94;		// [sp+Ch] [bp-A4h]

	movX = dx;
	movY = dy;
	movZ = dz;
	if(this->noclip) {
		this->boundingBox.move(dx, dy, dz);
		minY = this->boundingBox.minY;
		this->posX = (float)(this->boundingBox.minX + this->boundingBox.maxX) * 0.5;
		v9 = (float)(minY + this->ridingHeight) - this->ySize;
		minZ = this->boundingBox.minZ;
		this->posY = v9;
		this->posZ = (float)(minZ + this->boundingBox.maxZ) * 0.5;
	} else {
		posX = this->posX;
		posZ = this->posZ;
		if(this->maybeIsInWeb) {
			this->maybeIsInWeb = 0;
			this->motionX = 0.0;
			this->motionY = 0.0;
			this->motionZ = 0.0;
			movX = dx * 0.25;
			movY = dy * 0.05;
			movZ = dz * 0.25;
		}
		AABB boundingBox = this->boundingBox;
		if(this->onGround && this->isSneaking()) {
			while(movX != 0.0) {
				maxX = this->boundingBox.maxX;
				maxY = this->boundingBox.maxY;
				maxZ = this->boundingBox.maxZ;
				minX = this->boundingBox.minX;
				level = this->level;
				v18 = this->boundingBox.minZ + 0.0;
				std::vector<AABB>* cubes = level->getCubes(this, {minX + movX, this->boundingBox.minY - 1.0f, v18, movX + maxX, maxY - 1.0f, maxZ + 0.0f}, 0);
				if(cubes->begin() != cubes->end()) {
					break;
				}
				if(movX < 0.05 && movX >= -0.05) {
					movX = 0.0;
					break;
				}
				if(movX <= 0.0) {
					movX = movX + 0.05;
				} else {
					movX = movX - 0.05;
				}
			}
			while(movZ != 0.0) {
				v20 = this->boundingBox.maxX;
				v21 = this->boundingBox.maxY;
				v22 = this->boundingBox.maxZ;
				v23 = this->boundingBox.minX;
				v24 = this->level;
				v25 = movZ + this->boundingBox.minZ;
				std::vector<AABB>* v26 = v24->getCubes(this, {v23 + 0.0f, this->boundingBox.minY - 1.0f, v25, v20 + 0.0f, v21 - 1.0f, movZ + v22}, 0);
				if(v26->begin() != v26->end()) {
					break;
				}
				if(movZ < 0.05 && movZ >= -0.05) {
					movZ = 0.0;
					break;
				}
				if(movZ <= 0.0) {
					movZ = movZ + 0.05;
				} else {
					movZ = movZ - 0.05;
				}
			}
			while(movX != 0.0) {
				if(movZ == 0.0) {
					break;
				}
				v27 = this->boundingBox.maxX;
				v28 = this->boundingBox.maxY;
				v29 = this->boundingBox.maxZ;
				v30 = this->boundingBox.minX;
				v31 = this->level;
				v32 = movZ + this->boundingBox.minZ;
				std::vector<AABB>* v33 = v31->getCubes(this, {v30 + movX, this->boundingBox.minY - 1.0f, v32, movX + v27, v28 - 1.0f, movZ + v29}, 0);
				if(v33->begin() != v33->end()) {
					break;
				}
				if(movX < 0.05 && movX >= -0.05) {
					movX = 0.0;
				} else if(movX <= 0.0) {
					movX = movX + 0.05;
				} else {
					movX = movX - 0.05;
				}
				if(movZ < 0.05 && movZ >= -0.05) {
					movZ = 0.0;
				} else if(movZ <= 0.0) {
					movZ = movZ + 0.05;
				} else {
					movZ = movZ - 0.05;
				}
			}
			v34 = 1;
		} else {
			v34 = 0;
		}
		v35 = this->level;
		v36 = movY;
		v37 = 0;
		std::vector<AABB>* v38 = v35->getCubes(this, this->boundingBox.expand(movX, movY, movZ), &this->field_74);
		v40 = v38->size();
		while(v37 != v40) {
			v41 = v38->at(v37).clipYCollide(this->boundingBox, v36);
			++v37;
			v36 = v41;
		}
		this->boundingBox.move(0.0, v36, 0.0);
		if(this->field_103 || movY == v36) {
			v42 = movZ;
			v43 = movX;
		} else {
			v36 = 0.0;
			v42 = 0.0;
			v43 = 0.0;
		}
		fallingFlag = this->onGround || movY != v36 && movY < 0.0;
		v45 = 0;
		v47 = v38->size();
		while(v45 != v47) {
			v93 = v47;
			v48 = v38->at(v45).clipXCollide(this->boundingBox, v43);
			v47 = v93;
			++v45;
			v43 = v48;
		}
		this->boundingBox.move(v43, 0.0, 0.0);
		if(!this->field_103 && movX != v43) {
			v42 = 0.0;
			v36 = 0.0;
			v43 = 0.0;
		}
		v49 = 0;
		v51 = v38->size();
		while(v49 != v51) {
			v94 = v51;
			v52 = v38->at(v49).clipZCollide(this->boundingBox, v42);
			v51 = v94;
			++v49;
			v42 = v52;
		}
		this->boundingBox.move(0.0, 0.0, v42);
		if(!this->field_103 && movZ != v42) {
			v42 = 0.0;
			v36 = 0.0;
			v43 = 0.0;
		}
		stepHeight = this->stepHeight;
		if(stepHeight > 0.0 && fallingFlag && this->ySize < 0.05 && (movX != v43 || movZ != v42)) {
			AABB v96{this->boundingBox.minX, this->boundingBox.minY, this->boundingBox.minZ, this->boundingBox.maxX, this->boundingBox.maxY, this->boundingBox.maxZ};
			v55 = this->boundingBox.maxZ;
			this->boundingBox.minX = boundingBox.minX;
			v56 = this->level;
			this->boundingBox.minY = boundingBox.minY;
			this->boundingBox.minZ = boundingBox.minZ;
			this->boundingBox.maxX = boundingBox.maxX;
			this->boundingBox.maxY = boundingBox.maxY;
			this->boundingBox.maxZ = boundingBox.maxZ;
			v57 = v56;
			v58 = 0;
			std::vector<AABB>* v38 = v57->getCubes(this, this->boundingBox.expand(movX, stepHeight, movZ), 0);
			v61 = v38->size();
			while(v58 != v61) {
				v62 = v38->at(v58).clipYCollide(this->boundingBox, stepHeight);
				++v58;
				stepHeight = v62;
			}
			this->boundingBox.move(0.0, stepHeight, 0.0);
			if(this->field_103 || movY == stepHeight) {
				v63 = movZ;
				v64 = movX;
			} else {
				stepHeight = 0.0;
				v63 = 0.0;
				v64 = 0.0;
			}
			v65 = 0;
			v67 = v38->size();
			while(v65 != v67) {
				v68 = v38->at(v65).clipXCollide(this->boundingBox, v64);
				++v65;
				v64 = v68;
			}
			this->boundingBox.move(v64, 0.0, 0.0);
			if(!this->field_103 && movX != v64) {
				v63 = 0.0;
				stepHeight = 0.0;
				v64 = 0.0;
			}
			v71 = 0;
			v72 = v38->size();
			while(v71 != v72) {
				v73 = v38->at(v71).clipZCollide(this->boundingBox, v63);
				++v71;
				v63 = v73;
			}
			this->boundingBox.move(0.0, 0.0, v63);
			if(!this->field_103 && movZ != v63) {
				v63 = 0.0;
				stepHeight = 0.0;
				v64 = 0.0;
			}
			if((float)((float)(v42 * v42) + (float)(v43 * v43)) < (float)((float)(v63 * v63) + (float)(v64 * v64))) {
				v42 = v63;
				this->ySize = this->ySize + 0.5;
				v36 = stepHeight;
				v43 = v64;
			} else {
				this->boundingBox = v96;
			}
		}
		v74 = this->boundingBox.minY;
		this->posX = (float)(this->boundingBox.minX + this->boundingBox.maxX) * 0.5;
		v75 = (float)(v74 + this->ridingHeight) - this->ySize;
		v76 = this->boundingBox.minZ;
		this->posY = v75;
		this->posZ = (float)(v76 + this->boundingBox.maxZ) * 0.5;
		v77 = movX != v43 || movZ != v42;
		this->isCollidedHorizontally = v77;
		this->field_100 = movY != v36;
		v78 = movY != v36 && movY < 0.0;
		v79 = v77 || movY != v36;
		this->field_101 = v79;
		this->onGround = v78;
		this->checkFallDamage(v36, v78);
		if(movX != v43) {
			this->motionX = 0.0;
		}
		if(movY != v36) {
			this->motionY = 0.0;
		}
		field_110 = this->field_110;
		v82 = this->posX;
		v83 = this->posZ;
		if(movZ != v42) {
			this->motionZ = 0.0;
		}
		if(field_110 && !v34) {
			v84 = sqrt((float)((float)((float)(v83 - posZ) * (float)(v83 - posZ)) + (float)((float)(v82 - posX) * (float)(v82 - posX))));
			v85 = this->posX;
			v86 = v84;
			this->field_BC = this->field_BC + (float)(v86 * 0.6);
			v87 = Mth::floor(v85);
			v88 = Mth::floor((float)(this->posY - 0.2) - this->ridingHeight);
			v89 = Mth::floor(this->posZ);
			v90 = this->level->getTile(v87, v88, v89);
			if(!v90) {
				v90 = this->level->getTile(v87, v88 - 1, v89);
				blockID = Tile::fence->blockID;
				if(blockID == v90 || (blockID = Tile::fenceGate->blockID, blockID == v90)) {
					v90 = blockID;
				} else if(Tile::cobbleWall->blockID != v90) {
					v90 = 0;
				}
			}
			field_BC = this->field_BC;
			if(field_BC > (float)this->field_114 && v90 > 0) {
				this->field_114 = (int32_t)field_BC + 1;
				this->playStepSound(v87, v88, v89, v90);
			}
		}
		this->ySize = this->ySize * 0.4;
		this->checkTileCollisions();
	}
}
void Entity::moveTo(float x, float y, float z, float yaw, float pitch) {
	float y2; // s15

	this->posX = x;
	this->prevX = x;
	this->prevPosX = x;
	y2 = y + this->ridingHeight;
	this->posY = y2;
	this->prevY = y2;
	this->prevPosY = y2;
	this->posZ = z;
	this->prevZ = z;
	this->prevPosZ = z;
	this->prevYaw = yaw;
	this->yaw = yaw;
	this->prevPitch = pitch;
	this->pitch = pitch;
	this->setPos(x, y2, z);
}
void Entity::moveRelative(float fw, float sf, float speed) {
	float v8; // s15
	float v9; // s15
	float v10; // s20
	float v11; // s18
	double v12; // d8
	float v13; // s19
	float v14; // s15

	v8 = sqrt((float)((float)(sf * sf) + (float)(fw * fw)));
	if(v8 >= 0.01) {
		if(v8 < 1.0) {
			v8 = 1.0;
		}
		v9 = speed / v8;
		v10 = fw * v9;
		v11 = sf * v9;
		v12 = (float)((float)(this->yaw * 3.1416) / 180.0);
		v13 = sin(v12);
		v14 = cos(v12);
		this->motionX = this->motionX + (float)((float)(v10 * v14) - (float)(v11 * v13));
		this->motionZ = this->motionZ + (float)((float)(v10 * v13) + (float)(v11 * v14));
	}
}
void Entity::lerpTo(float x, float y, float z, float yaw, float pitch, int32_t a7) {
	this->setPos(x, y, z);
	this->setRot(yaw, pitch);
}
void Entity::lerpMotion(float a2, float a3, float a4) {
	this->motionX = a2;
	this->motionY = a3;
	this->motionZ = a4;
}
void Entity::turn(float a2, float a3) {
	float yaw; // s15
	float pitch; // s13
	float v5; // s14
	float v6; // s11
	float v7; // s15
	float v8; // s13

	yaw = this->yaw;
	pitch = this->pitch;
	v5 = yaw + (float)(a2 * 0.15);
	this->yaw = v5;
	v6 = -90.0;
	if((float)(pitch - (float)(a3 * 0.15)) >= -90.0) {
		v6 = pitch - (float)(a3 * 0.15);
	}
	this->pitch = v6;
	v7 = v5 - yaw;
	if(v6 > 90.0) {
		this->pitch = 90.0;
	}
	v8 = this->prevPitch + (float)(this->pitch - pitch);
	this->prevYaw = this->prevYaw + v7;
	this->prevPitch = v8;
}
void Entity::interpolateTurn(float a2, float a3) {
	float pitch; // s15

	this->yaw = this->yaw + (float)(a2 * 0.15);
	pitch = this->pitch - (float)(a3 * 0.15);
	if(pitch < -90.0) {
		pitch = -90.0;
	}
	this->pitch = pitch;
	if(pitch > 90.0) {
		this->pitch = 90.0;
	}
}
void Entity::tick() {
	this->baseTick();
}
void Entity::baseTick() {
	int32_t field_113; // r5
	double v3;		   // r0
	Level* level;	   // r7
	float v5;		   // s17
	Level* v8;		   // r0
	int32_t a9;		   // r7
	float v10;		   // s20
	float v11;		   // r0
	float v12;		   // s22
	float v13;		   // r0
	Level* v14;		   // r8
	float a6;		   // r9
	float motionY;	   // s23
	float v17;		   // s22
	float v18;		   // s18
	float v19;		   // r0
	int32_t v20;	   // r3
	int32_t fire;	   // r0
	int32_t v22;	   // r0

	++this->field_D8;
	this->field_B8 = this->field_BC;
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;
	this->prevPitch = this->pitch;
	this->prevYaw = this->yaw;
	if(this->isInWater()) {
		if(!this->field_111) {
			field_113 = this->field_113;
			if(!this->field_113) {
				v3 = sqrt((float)((float)((float)(this->motionY * this->motionY) + (float)((float)(this->motionX * this->motionX) * 0.2)) + (float)((float)(this->motionZ * this->motionZ) * 0.2)));
				level = this->level;
				v5 = v3 * 0.200000003;
				if(v5 > 1.0) {
					v5 = 1.0;
				}

				v8 = level;
				a9 = field_113;
				v8->playSound(this, "random.splash", v5, (float)((float)(Entity::sharedRandom.nextFloat() - Entity::sharedRandom.nextFloat()) * 0.4) + 1.0);

				v10 = floorf(this->boundingBox.minY);
				while((float)field_113 < (float)((float)(this->entityWidth * 20.0) + 1.0)) {
					++field_113;
					v11 = Entity::sharedRandom.nextFloat();
					v12 = (float)((float)(v11 + v11) - 1.0) * this->entityWidth;
					v13 = Entity::sharedRandom.nextFloat();
					v14 = this->level;
					a6 = this->motionX;
					motionY = this->motionY;
					v17 = v12 + this->posX;
					v18 = this->posZ + (float)((float)((float)(v13 + v13) - 1.0) * this->entityWidth);
					v19 = Entity::sharedRandom.nextFloat();
					v14->addParticle(PT_BUBBLE, v17, v10 + 1.0, v18, a6, motionY - (float)(v19 * 0.2), this->motionZ, a9);
				}
			}
		}
		this->fallDistance = 0.0;
		this->field_111 = 1;
		this->fire = 0;
	} else {
		this->field_111 = 0;
	}
	if(this->level->isClientMaybe) {
		v20 = 0;
LABEL_22:
		this->fire = v20;
		goto LABEL_23;
	}
	fire = this->fire;
	if(fire <= 0) {
		goto LABEL_23;
	}
	if(!this->field_112) {
		if(!(fire % 20)) {
			this->hurt(0, 1);
		}
		v20 = this->fire - 1;
		goto LABEL_22;
	}
	v22 = fire - 4;
	if(v22 < 0) {
		v22 = 0;
	}
	this->fire = v22;
LABEL_23:
	if(this->isInLava()) {
		this->lavaHurt();
	}
	if(this->posY < 0.0) {
		this->outOfWorld();
	}
	this->field_113 = 0;
}
void Entity::rideTick(){
	Entity *ridingAt; // r3
	bool_t isDead; // r5
	Entity *v4; // r0
	Entity *v5; // r3
	float field_70; // s15
	float v7; // s12
	float field_6C; // s15
	float v9; // s13
	float v10; // s14
	float v11; // s15

	ridingAt = this->ridingAt;
	isDead = ridingAt->isDead;
	if ( ridingAt->isDead )
	{
		ridingAt->positionRider(0);
		this->ridingAt = 0;
	}
	else
	{
		this->motionX = 0.0;
		this->motionY = 0.0;
		this->motionZ = 0.0;
		this->tick();
		v4 = this->ridingAt;
		if ( v4 )
		{
			v4->positionRider(isDead);
			v5 = this->ridingAt;
			this->field_70 = this->field_70 + (float)(v5->yaw - v5->prevYaw);
			this->field_6C = this->field_6C + (float)(v5->pitch - v5->prevPitch);
			while ( 1 )
			{
				field_70 = this->field_70;
				if ( field_70 < 180.0 )
				{
					break;
				}
				this->field_70 = field_70 - 360.0;
			}
			while ( 1 )
			{
				v7 = this->field_70;
				if ( v7 >= -180.0 )
				{
					break;
				}
				this->field_70 = v7 + 360.0;
			}
			while ( 1 )
			{
				field_6C = this->field_6C;
				if ( field_6C < 180.0 )
				{
					break;
				}
				this->field_6C = field_6C - 360.0;
			}
			while ( 1 )
			{
				v9 = this->field_6C;
				if ( v9 >= -180.0 )
				{
					break;
				}
				this->field_6C = v9 + 360.0;
			}
			v10 = v7 * 0.5;
			v11 = v9 * 0.5;
			if ( (float)(v7 * 0.5) > 10.0 )
			{
				v10 = 10.0;
			}
			else if ( v10 < -10.0 )
			{
				v10 = -10.0;
			}
			if ( v11 > 10.0 )
			{
				v11 = 10.0;
			}
			else if ( v11 < -10.0 )
			{
				v11 = -10.0;
			}
			this->field_70 = v7 - v10;
			this->field_6C = v9 - v11;
		}
	}
}
void Entity::positionRider(bool_t a2) {
	float v3; // s16
	float v4; // r0

	if(this->rider) {
		if(this->isDead || a2) {
			v3 = 0.01;
		} else {
			v3 = this->getRideHeight();
		}
		v4 = this->rider->getRidingHeight();
		this->rider->setPos(this->posX, (float)(v3 + v4) + this->posY, this->posZ);
	}
}
float Entity::getRidingHeight() {
	return this->ridingHeight;
}
float Entity::getRideHeight() {
	return this->entityHeight * 0.75;
}
void Entity::ride(Entity* a2) {
	Entity* ridingAt; // r3

	this->field_6C = 0;
	this->field_70 = 0;
	ridingAt = this->ridingAt;
	if(a2) {
		if(ridingAt) {
			ridingAt->rider = 0;
		}
		this->ridingAt = a2;
		a2->rider = this;
	} else {
		if(ridingAt) {
			this->moveTo(ridingAt->posX, ridingAt->boundingBox.minY + ridingAt->entityHeight, ridingAt->posZ, this->yaw, this->pitch);
			this->ridingAt->rider = 0;
		}
		this->ridingAt = 0;
	}
}
bool_t Entity::intersects(float a2, float a3, float a4, float a5, float a6, float a7) {
	return a5 > this->boundingBox.minX && a2 < this->boundingBox.maxX && a6 > this->boundingBox.minY && a3 < this->boundingBox.maxY && a7 > this->boundingBox.minZ && a4 < this->boundingBox.maxZ;
}
bool_t Entity::isFree(float x, float y, float z, float a5){
	float maxX; // s11
	float v9; // s10
	float v10; // s12
	float maxZ; // s8
	float v12; // s13
	float minX; // s8
	Level *level; // r0
	std::vector<AABB> *cubes; // r0
	AABB v17; // [sp+0h] [bp-20h] BYREF

	maxX = this->boundingBox.maxX;
	v9 = this->boundingBox.minZ - a5;
	v10 = (float)(a5 + this->boundingBox.maxY) + y;
	maxZ = this->boundingBox.maxZ;
	v17.minY = (float)(this->boundingBox.minY - a5) + y;
	v17.maxY = v10;
	v17.minZ = v9 + z;
	v12 = (float)(a5 + maxZ) + z;
	minX = this->boundingBox.minX;
	level = this->level;
	v17.maxZ = v12;
	v17.maxX = (float)(a5 + maxX) + x;
	v17.minX = (float)(minX - a5) + x;
	cubes = level->getCubes(this, v17, 0);
	return cubes->size() == 0 && !this->level->containsAnyLiquid(v17);
}
bool_t Entity::isFree(float x, float y, float z) {
	float maxY;	  // s9
	float maxX;	  // s12
	float v9;	  // s11
	float v10;	  // s13
	float maxZ;	  // s9
	float v12;	  // s14
	float minX;	  // s9
	Level* level; // r0
	std::vector<AABB>* cubes;
	AABB v17; // [sp+0h] [bp-20h] BYREF

	maxY = this->boundingBox.maxY;
	maxX = this->boundingBox.maxX;
	v9 = z + this->boundingBox.minZ;
	v17.minY = y + this->boundingBox.minY;
	v17.minZ = v9;
	v10 = y + maxY;
	maxZ = this->boundingBox.maxZ;
	v17.maxX = x + maxX;
	v12 = z + maxZ;
	minX = this->boundingBox.minX;
	level = this->level;
	v17.maxY = v10;
	v17.maxZ = v12;
	v17.minX = minX + x;
	cubes = level->getCubes(this, v17, 0);
	return cubes->size() == 0 && !this->level->containsAnyLiquid(v17);
}
bool_t Entity::isInWall() {
	int32_t x; // r0
	float _y; // s16
	int32_t _x; // r7
	float hh; // r0
	int32_t y; // r6
	int32_t z; // r0

	x = Mth::floor(this->posX);
	_y = this->posY;
	_x = x;
	hh = this->getHeadHeight();
	y = Mth::floor(_y + hh);
	z = Mth::floor(this->posZ);
	return this->level->isSolidBlockingTile(_x, y, z);
}
bool_t Entity::isInWater(){
	float maxY; // s11
	float maxX; // s13
	float minY; // s12
	float minX; // r4
	float maxY_; // s14
	float maxZ; // s11
	AABB v10; // [sp+0h] [bp-20h] BYREF

	maxY = this->boundingBox.maxY;
	maxX = this->boundingBox.maxX;
	minY = this->boundingBox.minY + 0.4;
	minX = this->boundingBox.minX;
	v10.minZ = this->boundingBox.minZ;
	v10.minX = minX;
	v10.minY = minY;
	maxY_ = maxY - 0.4;
	maxZ = this->boundingBox.maxZ;
	v10.maxX = maxX + 0.0;
	v10.maxY = maxY_;
	v10.maxZ = maxZ + 0.0;
	return this->level->checkAndHandleWater(v10, Material::water, this);
}
bool_t Entity::isInLava() {
	float maxY; // s13
	float minX; // s9
	float minZ; // s11
	float minY; // s10
	float maxX; // s12
	float v8;	// s14
	float maxZ; // s13
	AABB v11;	// [sp+0h] [bp-20h] BYREF

	maxY = this->boundingBox.maxY;
	minX = this->boundingBox.minX;
	minZ = this->boundingBox.minZ;
	minY = this->boundingBox.minY + 0.4;
	maxX = this->boundingBox.maxX;
	v11.minY = minY;
	v11.minZ = minZ + 0.1;
	v8 = maxY - 0.4;
	maxZ = this->boundingBox.maxZ;
	v11.maxX = maxX - 0.1;
	v11.maxY = v8;
	v11.maxZ = maxZ - 0.1;
	v11.minX = minX + 0.1;
	return this->level->containsMaterial(v11, Material::lava);
}
bool_t Entity::isUnderLiquid(const Material* a2) {
	float posY;		// s16
	float v5;		// s16
	int32_t x;		// r6
	int32_t y;		// r0
	int32_t yy;		// r5
	int32_t z;		// r7
	int32_t result; // r0
	int32_t v11;	// r2
	int32_t v12;	// r5
	int32_t v13;	// r0

	posY = this->posY;
	v5 = posY + this->getHeadHeight();
	x = Mth::floor(this->posX);
	y = Mth::floor(v5);
	yy = Mth::floor((float)y);
	z = Mth::floor(this->posZ);
	result = this->level->getTile(x, yy, z);
	if(result) {
		if(Tile::tiles[result]->material == a2) {
			v11 = yy;
			v12 = yy + 1;
			v13 = this->level->getData(x, v11, z);
			if(v13 > 7) {
				v13 = 0;
			}
			return v5 < (float)((float)v12 - (float)((float)((float)(v13 + 1) / 9.0) - 0.11111));
		} else {
			return 0;
		}
	}
	return 0;
}
float Entity::getShadowRadius() {
	return this->entityWidth;
}
void Entity::makeStuckInWeb() {
	this->maybeIsInWeb = 1;
	this->fallDistance = 0;
}
float Entity::getHeadHeight() {
	return 0;
}
float Entity::getShadowHeightOffs() {
	return this->entityHeight * 0.5;
}
bool_t Entity::isSkyLit() {
	int32_t x; // r6
	int32_t y; // r5
	int32_t z; // r7

	x = Mth::floor(this->posX);
	y = Mth::floor((float)(this->posY - this->ridingHeight) + (float)((float)(this->boundingBox.maxY - this->boundingBox.minY) * 0.66));
	z = Mth::floor(this->posZ);
	if(this->level->hasChunkAt(x, y, z)) {
		return this->level->isSkyLit(x, y, z);
	} else {
		return 1;
	}
}
float Entity::getBrightness(float a2) {
	int32_t x; // r6
	int32_t y; // r5
	int32_t z; // r7

	x = Mth::floor(this->posX);
	y = Mth::floor((float)(this->posY - this->ridingHeight) + (float)((float)(this->boundingBox.maxY - this->boundingBox.minY) * 0.66));
	z = Mth::floor(this->posZ);
	if(this->level->hasChunkAt(x, y, z)) {
		return this->level->getBrightness(x, y, z);
	} else {
		return 255.0;
	}
}
bool_t Entity::interactPreventDefault() {
	return 0;
}
bool_t Entity::interactWithPlayer(Player*) {
	return 0;
}
void Entity::playerTouch(Player*) {
}
void Entity::push(Entity* a2) {
	float v4;	// s17
	float posZ; // s15
	float v6;	// s16
	float v7;	// s14
	float v8;	// s15
	float v11;	// s15
	float v12;	// s16
	float v13;	// s17
	float v14;	// s15
	float v15;	// s14
	float v16;	// s16
	float v17;	// s17

	if(a2->rider != this && a2->ridingAt != this) {
		v4 = a2->posX - this->posX;
		posZ = this->posZ;
		v6 = a2->posZ - posZ;
		if(v4 >= 0.0) {
			v7 = a2->posX - this->posX;
		} else {
			v7 = -v4;
		}
		if(v6 >= 0.0) {
			v8 = a2->posZ - posZ;
		} else {
			v8 = -v6;
		}
		if(v7 > v8) {
			v8 = v7;
		}
		if(v8 >= 0.01) {
			v11 = sqrt(v8);
			v12 = v6 / v11;
			v13 = v4 / v11;
			v14 = 1.0 / v11;
			if(v14 > 1.0) {
				v14 = 1.0;
			}
			v15 = 1.0 - this->field_D4;
			v16 = (float)((float)(v12 * v14) * 0.05) * v15;
			v17 = (float)((float)(v13 * v14) * 0.05) * v15;
			this->push(-v17, 0.0, -v16);
			a2->push(v17, 0.0, v16);
		}
	}
}
void Entity::push(float a2, float a3, float a4) {
	this->motionX = this->motionX + a2;
	this->motionY = this->motionY + a3;
	this->motionZ = this->motionZ + a4;
}
bool_t Entity::isPickable() {
	return 0;
}
bool_t Entity::isPushable() {
	return 0;
}
bool_t Entity::isShootable() {
	return 0;
}
bool_t Entity::isSneaking() {
	return 0;
}
bool_t Entity::isAlive() {
	return !this->isDead;
}
bool_t Entity::isOnFire() {
	return this->fire > 0;
}
bool_t Entity::isPlayer() {
	return 0;
}
bool_t Entity::isCreativeModeAllowed() {
	return 0;
}
bool_t Entity::shouldRender(Vec3& a2) {
	float v2; // s15
	float v3; // s14

	if(this->field_107) {
		return 0;
	}
	v2 = this->posY - a2.y;
	v3 = this->posZ - a2.z;
	return this->shouldRenderAtSqrDistance((float)((float)(v2 * v2) + (float)((float)(this->posX - a2.x) * (float)(this->posX - a2.x))) + (float)(v3 * v3));
}
bool_t Entity::shouldRenderAtSqrDistance(float a2) {
	float v2; // s15

	v2 = (float)((float)((float)((float)(this->boundingBox.maxX - this->boundingBox.minX) + (float)(this->boundingBox.maxY - this->boundingBox.minY)) + (float)(this->boundingBox.maxZ - this->boundingBox.minZ)) / 3.0) * (float)(this->somethingRelatedToRenderer * 64.0);
	return a2 < (float)(v2 * v2);
}
bool_t Entity::hurt(Entity* a2, int32_t a3) {
	this->markHurt();
	return 0;
}
void Entity::animateHurt() {
}
void Entity::handleEntityEvent(int8_t) {
}
float Entity::getPickRadius() {
	return 0.1;
}
Entity* Entity::spawnAtLocation(int32_t a2, int32_t a3) {
	return this->spawnAtLocation(a2, a3, 0.0);
}
Entity* Entity::spawnAtLocation(int32_t a2, int32_t a3, float a4) {
	return this->spawnAtLocation(ItemInstance(a2, a3, 0), a4);
}
Entity* Entity::spawnAtLocation(const ItemInstance& a2, float a3) {
	ItemEntity* ie = new ItemEntity(this->level, this->posX, a3 + this->posY, this->posZ, a2);
	ie->delayBeforePickup = 10;
	this->level->addEntity(ie);
	return ie;
}
void Entity::awardKillScore(Entity*, int32_t) {
}
void Entity::setEquippedSlot(int32_t, int32_t, int32_t) {
}
bool_t Entity::save(CompoundTag* a2) {
	int32_t id = this->getEntityTypeId();
	if(this->isDead) return 0;
	if(id == 0) return 0;
	if(!this->rider) {
		a2->putInt("id", id);
		this->saveWithoutId(a2);
		return 1;
	}
	return 0;
}
void Entity::saveWithoutId(CompoundTag* tag) {
	tag->put("Pos", ListTagFloatAdder()(this->posX)(this->posY)(this->posZ).tag); //what the cliff is this </3
	tag->put("Motion", ListTagFloatAdder()(this->motionX)(this->motionY)(this->motionZ).tag);
	tag->put("Rotation", ListTagFloatAdder()(this->yaw)(this->pitch).tag);
	tag->putFloat("FallDistance", this->fallDistance);
	tag->putShort("Fire", this->fire);
	tag->putShort("Air", this->air);
	tag->putBoolean("OnGround", this->onGround);
	if(this->ridingAt) {
		CompoundTag* v15 = new CompoundTag(Entity::RIDING_TAG);
		if(this->ridingAt->saveAsMount(v15)) {
			tag->put(Entity::RIDING_TAG, v15);
		}
	}
	this->addAdditonalSaveData(tag);
}
bool_t Entity::load(CompoundTag* a2) {
	ListTag* pos;		// r7
	ListTag* motion;	// r8
	ListTag* rotation;	// r9
	float motionZ;		// r0
	float v8;			// s13
	bool_t v9;			// fzf
	bool_t v10;			// fnf
	float v11;			// s13
	float x;			// s16
	float y;			// r6
	float z;			// r0
	float v15;			// s14
	float v16;			// s15
	float yaw;			// r0
	float v18;			// s15
	float pitch;		// r0
	float v20;			// s15
	int32_t vtable_low; // r0

	pos = a2->getList("Pos");
	motion = a2->getList("Motion");
	rotation = a2->getList("Rotation");
	this->setPos(0.0, 0.0, 0.0);
	this->motionX = motion->getFloat(0);
	this->motionY = motion->getFloat(1);
	motionZ = motion->getFloat(2);
	v8 = fabsf(this->motionX);
	v9 = v8 == 10.0;
	v10 = v8 < 10.0;
	v11 = fabsf(this->motionY);
	if(!v10 && !v9) {
		this->motionX = 0.0;
	}
	if(v11 > 10.0) {
		this->motionY = 0.0;
	}
	this->motionZ = motionZ;
	if(fabsf(motionZ) > 10.0) {
		this->motionZ = 0.0;
	}
	x = pos->getFloat(0);
	y = pos->getFloat(1);
	z = pos->getFloat(2);
	v15 = (float)(this->entityWidth * 0.5) + 0.001;
	v16 = z;
	if(x > (float)(256.0 - v15)) {
		x = 256.0 - v15;
	} else if(x <= v15) {
		x = (float)(this->entityWidth * 0.5) + 0.001;
	}
	if(z > (float)(256.0 - v15)) {
		v16 = 256.0 - v15;
	} else if(z <= v15) {
		v16 = (float)(this->entityWidth * 0.5) + 0.001;
	}
	this->posZ = v16;
	this->prevPosZ = v16;
	this->prevZ = v16;
	this->posX = x;
	this->prevPosX = x;
	this->prevX = x;
	this->posY = y;
	this->prevPosY = y;
	this->prevY = y;
	yaw = rotation->getFloat(0);
	v18 = fmod(yaw, 360.0);
	this->yaw = v18;
	this->prevYaw = v18;
	pitch = rotation->getFloat(1);
	v20 = fmod(pitch, 360.0);
	this->pitch = v20;
	this->prevPitch = v20;
	this->fallDistance = a2->getFloat("FallDistance");
	this->fire = a2->getShort("Fire");
	this->air = a2->getShort("Air");
	this->onGround = a2->getByte("OnGround") != 0;

	this->setPos(this->posX, this->posY, this->posZ);
	this->readAdditionalSaveData(a2);
	return a2->field_0 == 0;
}
SynchedEntityData* Entity::getEntityData() const {
	return 0;
}
//TODO there are 2 getEntityData: _ZNK6 and _ZN6

int32_t Entity::getCreatureBaseType() {
	return 0;
}
EntityRendererId Entity::queryEntityRenderer() {
	return ER_NONE;
}
bool_t Entity::isMob() {
	return 0;
}
bool_t Entity::isItemEntity() {
	return 0;
}
bool_t Entity::isHangingEntity() {
	return 0;
}
int32_t Entity::getAuxData() {
	return 0;
}
void Entity::setRot(float y, float p) {
	this->prevYaw = this->yaw = y;
	this->prevPitch = this->pitch = p;
}
void Entity::setSize(float w, float h) {
	this->entityWidth = w;
	this->entityHeight = h;
}
void Entity::setPos(EntityPos* pos) {
	float x;	 // r1
	float y;	 // r2
	float z;	 // r3
	float yaw;	 // r1
	float pitch; // r2

	if(pos->hasXYZ) {
		x = pos->x;
		y = pos->y;
		z = pos->z;
	} else {
		x = this->posX;
		y = this->posY;
		z = this->posZ;
	}
	this->setPos(x, y, z);
	if(pos->hasRot) {
		yaw = pos->yaw;
		pitch = pos->pitch;
	} else {
		yaw = this->yaw;
		pitch = this->pitch;
	}
	this->setRot(yaw, pitch);
}
void Entity::resetPos(bool_t a2) {
	if(this->level) {
		while(this->posY > 0.0) {
			this->setPos(this->posX, this->posY, this->posZ);
			if(this->level->getCubes(this, this->boundingBox, 0)->size() == 0) break;
			this->posY = this->posY + 1.0;
		}
		this->motionZ = 0.0;
		this->motionY = 0.0;
		this->motionX = 0.0;
		this->pitch = 0.0;
	}
}
void Entity::outOfWorld() {
	this->remove();
}
void Entity::checkFallDamage(float fdChange, bool_t a3) {
	int32_t x;		// r6
	int32_t y;		// r7
	int32_t z;		// r5
	int32_t tileID; // r0

	if(a3) {
		if(this->fallDistance <= 0.0) {
			return;
		}
		if(!this->isMob()) {
			goto NOT_MOB_FORCE_JUMP;
		}
		x = Mth::floor(this->posX);
		y = Mth::floor((float)(this->posY - 0.2) - this->ridingHeight);
		z = Mth::floor(this->posZ);
		tileID = this->level->getTile(x, y, z);
		if(!tileID) {
			if(this->level->getTile(x, y - 1, z) != Tile::fence->blockID) {
NOT_MOB_FORCE_JUMP:
				this->causeFallDamage(this->fallDistance);
				this->fallDistance = 0.0;
				return;
			}
			tileID = this->level->getTile(x, y - 1, z);
		}
		if(tileID > 0) {
			Tile::tiles[tileID]->fallOn(this->level, x, y, z, this, this->fallDistance);
		}
		goto NOT_MOB_FORCE_JUMP;
	}
	if(fdChange < 0.0) {
		this->fallDistance = this->fallDistance - fdChange;
	}
}
void Entity::causeFallDamage(float a2) {
	if(this->rider) rider->causeFallDamage(a2);
}
void Entity::markHurt() {
	this->wasHurt = 1;
}
void Entity::burn(int32_t a2) {
	if(!this->field_112) {
		this->hurt(0, a2);
	}
}
void Entity::lavaHurt() {
	if(!this->field_112) {
		this->hurt(0, 4);
		this->setOnFire(30);
	}
}
void Entity::playStepSound(int32_t x, int32_t y, int32_t z, int32_t id) {
	const Tile::SoundType* soundType; // r5

	soundType = Tile::tiles[id]->soundType;
	if(this->level->getTile(x, y + 1, z) == Tile::topSnow->blockID) {
		soundType = Tile::topSnow->soundType;
	} else {
		if(Tile::tiles[id]->material->isLiquid()) {
			return;
		}
	}
	this->level->playSound(this, soundType->field_C, soundType->field_0 * 0.25, soundType->field_4);
}
void Entity::checkInsideTiles() {
	int32_t minX; // r6
	int32_t minY; // r9
	int32_t minZ; // r8
	int32_t maxZ; // r11
	int32_t id;	  // r0
	int32_t z;	  // r7
	int32_t y;	  // r5
	int32_t maxX; // [sp+10h] [bp-38h]
	int32_t maxY; // [sp+14h] [bp-34h]

	minX = Mth::floor(this->boundingBox.minX + 0.001);
	minY = Mth::floor(this->boundingBox.minY + 0.001);
	minZ = Mth::floor(this->boundingBox.minZ + 0.001);
	maxX = Mth::floor(this->boundingBox.maxX - 0.001);
	maxY = Mth::floor(this->boundingBox.maxY - 0.001);
	maxZ = Mth::floor(this->boundingBox.maxZ - 0.001);
	if(this->level->hasChunksAt(minX, minY, minZ, maxX, maxY, maxZ)) {
		while(minX <= maxX) {
			for(y = minY; y <= maxY; ++y) {
				for(z = minZ; z <= maxZ; ++z) {
					id = this->level->getTile(minX, y, z);
					if(id > 0) {
						Tile::tiles[id]->entityInside(this->level, minX, y, z, this);
					}
				}
			}
			++minX;
		}
	}
}
