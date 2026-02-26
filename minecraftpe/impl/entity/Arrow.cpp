#include <entity/Arrow.hpp>
#include <entity/Player.hpp>
#include <inventory/Inventory.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/HitResult.hpp>
#include <math/Mth.hpp>
#include <nbt/CompoundTag.hpp>
#include <tile/Tile.hpp>

Arrow::Arrow(Level* a2)
	: Entity(a2) {
	this->isInReverse = 0;
	this->shooterEID = 0;
	this->_init();
}
Arrow::Arrow(Level* a2, Mob* a3, Mob* a4, float a5, float a6)
	: Entity(a2) {
	float posY; // s16
	float v10;	// s21
	float v11;	// s20
	float v12;	// r0
	float v13;	// s16
	float v14;	// s18
	float v15;	// s17
	float v16;	// s19
	float v17;	// s21
	float v18;	// s16
	float v19;	// s10
	this->isInReverse = a3->isPlayer();
	this->shooterEID = a3->entityId;
	posY = a3->posY;
	this->posY = (float)(posY + a3->getHeadHeight()) - 0.1;
	v10 = a4->posY;
	v11 = a4->posX - a3->posX;
	v12 = a4->getHeadHeight();
	v13 = this->posY;
	v14 = a4->posZ - a3->posZ;
	v15 = v12;
	v16 = Mth::sqrt((float)(v14 * v14) + (float)(v11 * v11));
	if(v16 >= 0.0000001) {
		v17 = (float)((float)(v10 + v15) - 0.7) - v13;
		v18 = atan2(v14, v11);
		v19 = atan2(v17, v16);
		this->moveTo((float)(v11 / v16) + a3->posX, this->posY, (float)(v14 / v16) + a3->posZ, (float)((float)(v18 * 180.0) / 3.1416) - 90.0, -(float)((float)(v19 * 180.0) / 3.1416));
		this->ridingHeight = 0.0;
		this->shoot(v11, v17 + (float)(v16 * 0.2), v14, a5, a6);
	}
}
Arrow::Arrow(Level* a2, Mob* a3, float a4)
	: Entity(a2) {
	float posX; // r7
	float posY; // s16
	float v9;	// r0
	float v10;	// s15
	float v11;	// s16
	float v12;	// s13
	float posZ; // s15
	float v15;	// s17
	float v16;	// r1
	float v17;	// s15
	float v18;	// s15
	float v19;	// s19
	float v20;	// s15
	float v21;	// s17
	float v22;	// s16
	float v23;	// s15

	this->isInReverse = a3->isPlayer();
	this->shooterEID = a3->entityId;
	this->_init();
	posX = a3->posX;
	posY = a3->posY;
	v9 = a3->getHeadHeight();
	this->moveTo(posX, posY + v9, a3->posZ, a3->yaw, a3->pitch);
	v10 = (float)(this->yaw * 0.017453);
	v11 = Mth::cos(v10);
	v12 = this->posY - 0.1;
	posZ = this->posZ;
	v15 = Mth::sin(v10);
	v16 = this->posX - (float)(v11 * 0.16);
	this->posX = v16;
	v17 = posZ - (float)(v15 * 0.16);
	this->posY = v12;
	this->posZ = v17;
	this->setPos(v16, v12, v17);
	v18 = this->pitch / 180.0;
	this->ridingHeight = 0.0;
	v19 = (float)(v18 * 3.1416);
	v20 = Mth::cos(v19);
	v21 = -(float)(v15 * v20);
	v22 = v11 * v20;
	this->motionX = v21;
	this->motionZ = v22;
	v23 = -Mth::sin(v19);
	this->motionY = v23;
	this->shoot(v21, v23, v22, a4 * 1.5, 1.0);
}
Arrow::Arrow(Level* a2, float x, float y, float z)
	: Arrow(a2) {
	this->setPos(x, y, z);
	this->ridingHeight = 0;
}
void Arrow::_init() {
	this->entityRenderId = ARROW;
	this->setSize(0.5, 0.5);
	this->shake = 0;
	this->critical = 0;
	this->xTile = -1;
	this->yTile = -1;
	this->zTile = -1;
	this->inTile = 0;
	this->inData = 0;
	this->inGround = 0;
	this->ticksInGround = 0;
	this->ticksInAir = 0;
}
void Arrow::shoot(float x, float y, float z, float a5, float a6) {
	float v10; // r0
	float v11; // s19
	float v12; // s16
	float v13; // s17
	float v14; // s19
	float v16; // s17
	float v17; // s19
	float v18; // s16
	float v19; // r5
	float v20; // r0
	float v21; // r0

	v10 = Mth::sqrt((float)((float)(y * y) + (float)(x * x)) + (float)(z * z));
	v11 = y / v10;
	v12 = z / v10;
	v13 = (float)(x / v10) + (float)(Entity::sharedRandom.nextGaussian() * (float)(a6 * 0.0075));
	v14 = v11 + (float)(Entity::sharedRandom.nextGaussian() * (float)(a6 * 0.0075));
	v16 = v13 * a5;
	v17 = v14 * a5;
	this->motionX = v16;
	this->motionY = v17;
	v18 = (float)(v12 + (float)(Entity::sharedRandom.nextGaussian() * (float)(a6 * 0.0075))) * a5;
	this->motionZ = v18;
	v19 = Mth::sqrt((float)(v18 * v18) + (float)(v16 * v16));
	v20 = atan2f(v16, v18);
	this->yaw = v20 * 57.296;
	this->prevYaw = v20 * 57.296;
	v21 = atan2f(v17, v19);
	this->ticksInGround = 0;
	this->pitch = v21 * 57.296;
	this->prevPitch = v21 * 57.296;
}

Arrow::~Arrow() {
}
void Arrow::lerpMotion(float x, float y, float z) {
	float v8;	// r7
	float v9;	// r0
	float v10;	// r0
	float posX; // r1
	float posY; // r2
	float yaw;	// [sp+0h] [bp-28h]

	this->motionX = x;
	this->motionY = y;
	this->motionZ = z;
	if(this->prevPitch == 0.0 && this->prevYaw == 0.0) {
		v8 = Mth::sqrt((float)(z * z) + (float)(x * x));
		v9 = atan2f(x, z);
		this->yaw = v9 * 57.296;
		this->prevYaw = v9 * 57.296;
		v10 = atan2f(y, v8);
		posX = this->posX;
		yaw = this->yaw;
		posY = this->posY;
		this->pitch = v10 * 57.296;
		this->prevPitch = v10 * 57.296;
		this->moveTo(posX, posY, this->posZ, yaw, v10 * 57.296);
		this->ticksInGround = 0;
	}
}
void Arrow::tick() {
	float v2;					  // r6
	float v3;					  // s12
	float motionY;				  // r0
	float v5;					  // s16
	int32_t shake;				  // r3
	Level* level;				  // r0
	int32_t tileID;				  // r5
	int32_t tileData;			  // r0
	float motionZ;				  // s15
	int32_t ticksInGroundCounter; // r3
	Level* v13;					  // r0
	int32_t v14;				  // r0
	int32_t v15;				  // r6
	AABB* v16;					  // r0
	float posX;					  // s13
	float posY;					  // s14
	float posZ;					  // s15
	float v20;					  // s12
	float v21;					  // s13
	float v22;					  // s14
	Level* v23;					  // r1
	float v24;					  // s9
	float v25;					  // s10
	float v26;					  // s11
	float v27;					  // s12
	float v28;					  // s13
	float v29;					  // s14
	float v30;					  // s11
	float v31;					  // s15
	float motionX;				  // s12
	float v33;					  // s13
	float v34;					  // s14
	Level* v35;					  // r0
	float minX;					  // s6
	float minY;					  // s7
	float minZ;					  // s8
	float maxX;					  // s9
	float maxY;					  // s10
	float maxZ;					  // s11
	float v43;					  // s17
	Entity* v44;				  // r8
	Entity* v46;				  // r5
	float v48;					  // s15
	float v49;					  // r0
	int32_t damage;				  // r5
	Level* v51;					  // r5
	float v53;					  // s14
	float yaw;					  // s14
	int32_t v55;				  // r2
	int32_t v56;				  // r3
	int32_t v58;				  // r0
	float v59;					  // s13
	float z;					  // s12
	float v61;					  // s15
	float v62;					  // s14
	float v63;					  // s14
	float v64;					  // r0
	Level* v65;					  // r5
	float v66;					  // s12
	float v67;					  // r0
	float v68;					  // s15
	float v69;					  // s13
	float v70;					  // s14
	float v71;					  // s13
	float v72;					  // s14
	float v73;					  // r5
	float v74;					  // s14
	float v75;					  // r0
	float v76;					  // r0
	float v78;					  // s14
	float v79;					  // s15
	int32_t i;					  // r5
	float v81;					  // s15
	int32_t v82;				  // r5
	float v83;					  // s13
	float v85;					  // r1
	float v86;					  // r2

	Entity::tick();
	if(this->prevPitch == 0.0 && this->prevYaw == 0.0) {
		v2 = Mth::sqrt((float)(this->motionZ * this->motionZ) + (float)(this->motionX * this->motionX));
		v3 = atan2f(this->motionX, this->motionZ);
		motionY = this->motionY;
		this->yaw = v3 * 57.296;
		this->prevYaw = v3 * 57.296;
		v5 = atan2f(motionY, v2) * 57.296;
		this->pitch = v5;
		this->prevPitch = v5;
	}
	shake = this->shake;
	if(shake > 0) {
		this->shake = shake - 1;
	}
	if(this->inGround) {
		level = this->level;
		this->motionZ = 0.0;
		this->motionY = 0.0;
		this->motionX = 0.0;
		tileID = level->getTile(this->xTile, this->yTile, this->zTile);
		tileData = this->level->getData(this->xTile, this->yTile, this->zTile);
		if(tileID == this->inTile && tileData == this->inData) {
			ticksInGroundCounter = this->ticksInGround + 1;
			this->ticksInGround = ticksInGroundCounter;
			if(ticksInGroundCounter == 1200) {
				this->remove();
			}
		} else {
			this->inGround = 0;
			this->motionX = this->motionX * (float)(Entity::sharedRandom.nextFloat() * 0.2);
			this->motionY = this->motionY * (float)(Entity::sharedRandom.nextFloat() * 0.2);
			motionZ = this->motionZ;
			this->ticksInGround = 0;
			this->ticksInAir = 0;
			this->motionZ = motionZ * (float)(Entity::sharedRandom.nextFloat() * 0.2);
		}
	} else {
		v13 = this->level;
		++this->ticksInAir;
		v14 = v13->getTile(this->xTile, this->yTile, this->zTile);
		v15 = v14;
		if(v14 > 0) {
			Tile::tiles[v14]->updateShape(this->level, this->xTile, this->yTile, this->zTile);
			v16 = Tile::tiles[v15]->getAABB(this->level, this->xTile, this->yTile, this->zTile);
			if(v16) {
				posX = this->posX;
				posY = this->posY;
				posZ = this->posZ;
				if(posX == 0.0) {
					posX = 0.0;
				}
				if(posY == 0.0) {
					posY = 0.0;
				}
				if(posZ == 0.0) {
					posZ = 0.0;
				}
				if(posX > v16->minX && posX < v16->maxX && posY > v16->minY && posY < v16->maxY && posZ > v16->minZ && posZ < v16->maxZ) {
					this->inGround = 1;
				}
			}
		}
		v20 = this->posX;
		v21 = this->posY;
		v22 = this->posZ;
		v23 = this->level;
		if(v20 == 0.0) {
			v24 = 0.0;
		} else {
			v24 = this->posX;
		}
		if(v21 == 0.0) {
			v25 = 0.0;
		} else {
			v25 = v21;
		}
		if(v22 == 0.0) {
			v26 = 0.0;
		} else {
			v26 = v22;
		}
		Vec3 start(v24, v25, v26);

		v27 = v20 + this->motionX;
		v28 = v21 + this->motionY;
		v29 = v22 + this->motionZ;
		if(v27 == 0.0) {
			v27 = 0.0;
		}
		if(v28 == 0.0) {
			v28 = 0.0;
		}
		if(v29 == 0.0) {
			v29 = 0.0;
		}
		Vec3 endVec(v27, v28, v29);

		HitResult a1 = v23->clip(start, endVec, 0, 1);
		v30 = this->posY;
		v31 = this->posZ;
		start.x = this->posX;
		start.y = v30;
		start.z = v31;
		motionX = this->motionX;
		v33 = this->motionY;
		v34 = this->motionZ;
		endVec.x = start.x + motionX;
		endVec.y = v30 + v33;
		endVec.z = v31 + v34;
		if(a1.hitType != 2) {
			endVec = a1.hitVec;
		}
		v35 = this->level;
		minX = this->boundingBox.minX;
		minY = this->boundingBox.minY;
		minZ = this->boundingBox.minZ;
		maxX = this->boundingBox.maxX;
		maxY = this->boundingBox.maxY;
		maxZ = this->boundingBox.maxZ;
		if(motionX >= 0.0) {
			if(motionX > 0.0) {
				maxX = maxX + motionX;
			}
		} else {
			minX = minX + motionX;
		}
		if(v33 >= 0.0) {
			if(v33 > 0.0) {
				maxY = maxY + v33;
			}
		} else {
			minY = minY + v33;
		}
		if(v34 >= 0.0) {
			if(v34 > 0.0) {
				maxZ = maxZ + v34;
			}
		} else {
			minZ = minZ + v34;
		}

		v43 = 0.0;
		v44 = 0;
		std::vector<Entity*>* ents = v35->getEntities(this, {minX - 1.0f, minY - 1.0f, minZ - 1.0f, maxX + 1.0f, maxY + 1.0f, maxZ + 1.0f});
		for(int32_t v42 = 0; v42 < (uint32_t)ents->size(); ++v42) {
			v46 = ents->at(v42);
			if(v46->isPickable()) {
				if(v46->entityId != this->shooterEID || this->ticksInAir > 4) {
					AABB v94{v46->boundingBox.minX - 0.3f, v46->boundingBox.minY - 0.3f, v46->boundingBox.minZ - 0.3f, v46->boundingBox.maxX + 0.3f, v46->boundingBox.maxY + 0.3f, v46->boundingBox.maxZ + 0.3f}; // [sp+30h] [bp-90h] BYREF
					HitResult a3 = v94.clip(start, endVec);
					if(a3.hitType != 2) {
						double v47 = sqrt((float)((float)((float)((float)(a3.hitVec.y - start.y) * (float)(a3.hitVec.y - start.y)) + (float)((float)(a3.hitVec.x - start.x) * (float)(a3.hitVec.x - start.x))) + (float)((float)(a3.hitVec.z - start.z) * (float)(a3.hitVec.z - start.z))));
						v48 = v47;
						if(v48 < v43 || v43 == 0.0) {
							v43 = v47;
							v44 = v46;
						}
					}
				}
			}
		}
		if(v44) {
			a1 = HitResult(v44);
		}
		if(a1.hitType != 2) {
			if(a1.hitType == 1) {
				v49 = Mth::sqrt((float)((float)(this->motionY * this->motionY) + (float)(this->motionX * this->motionX)) + (float)(this->motionZ * this->motionZ));
				damage = (int32_t)ceilf(v49 + v49);
				if(this->critical) {
					damage += Entity::sharedRandom.genrand_int32() % (damage / 2 + 2);
				}
				if(a1.entity->hurt(this, damage)) {
					if(a1.entity->isMob()) {
						++((Mob*)a1.entity)->field_180;
					}
					v51 = this->level;
					v51->playSound(this, "random.bowhit", 1.0, 1.2 / (float)((float)(Entity::sharedRandom.nextFloat() * 0.2) + 0.9));
					this->remove();
				} else {
					v53 = this->motionX * -0.1;
					this->ticksInAir = 0;
					this->motionX = v53;
					this->motionY = this->motionY * -0.1;
					yaw = this->yaw;
					this->motionZ = this->motionZ * -0.1;
					this->yaw = yaw + 180.0;
					this->prevYaw = this->prevYaw + 180.0;
				}
			} else {
				v55 = a1.field_8;
				v56 = a1.field_C;
				this->xTile = a1.field_4;
				this->yTile = v55;
				this->zTile = v56;
				this->inTile = this->level->getTile(this->xTile, this->yTile, this->zTile);
				v58 = this->level->getData(this->xTile, this->yTile, this->zTile);
				v59 = a1.hitVec.x - this->posX;
				z = a1.hitVec.z;
				v61 = a1.hitVec.y - this->posY;
				v62 = this->posZ;
				this->motionX = v59;
				this->motionY = v61;
				this->inData = v58;
				v63 = z - v62;
				this->motionZ = v63;
				v64 = Mth::sqrt((float)((float)(v61 * v61) + (float)(v59 * v59)) + (float)(v63 * v63));
				v65 = this->level;
				v66 = this->motionY / v64;
				this->posX = this->posX - (float)((float)(this->motionX / v64) * 0.05);
				this->posY = this->posY - (float)(v66 * 0.05);
				this->posZ = this->posZ - (float)((float)(this->motionZ / v64) * 0.05);
				v65->playSound(this, "random.bowhit", 1.0, 1.2 / (float)((float)(Entity::sharedRandom.nextFloat() * 0.2) + 0.9));
				this->inGround = 1;
				this->shake = 7;
				this->critical = 0;
			}
		}
		if(this->critical) {
			for(i = 0; i != 4; ++i) {
				v81 = (float)i;
				this->level->addParticle(PT_CRIT, this->posX + (float)((float)(this->motionX * v81) * 0.25), this->posY + (float)((float)(this->motionY * v81) * 0.25), this->posZ + (float)((float)(this->motionZ * v81) * 0.25), -this->motionX, 0.2 - this->motionY, -this->motionZ, 0);
			}
		}
		v68 = this->motionX;
		v69 = this->posY;
		this->posX = this->posX + v68;
		v70 = v69 + this->motionY;
		v71 = this->posZ;
		this->posY = v70;
		v72 = this->motionZ;
		this->posZ = v71 + v72;
		v73 = Mth::sqrt((float)(v72 * v72) + (float)(v68 * v68));
		v74 = atan2f(this->motionX, this->motionZ);
		v75 = this->motionY;
		this->yaw = v74 * 57.296;
		v76 = atan2f(v75, v73);
		v78 = this->yaw;
		this->pitch = this->prevPitch + (float)((float)((float)(v76 * 57.296) - this->prevPitch) * 0.2);
		this->yaw = this->prevYaw + (float)((float)(v78 - this->prevYaw) * 0.2);
		if(this->isInWater()) {
			v82 = 4;
			do {
				this->level->addParticle(PT_BUBBLE, this->posX - (float)(this->motionX * 0.25), this->posY - (float)(this->motionY * 0.25), this->posZ - (float)(this->motionZ * 0.25), this->motionX, this->motionY, this->motionZ, 0);
				--v82;
			} while(v82);
			v79 = 0.8;
		} else {
			v79 = 0.99;
		}
		v83 = this->motionY;
		v85 = this->posX;
		v86 = this->posY;
		this->motionX = this->motionX * v79;
		this->motionZ = this->motionZ * v79;
		this->motionY = (float)(v79 * v83) - 0.05;
		this->setPos(v85, v86, this->posZ);
	}
}
float Arrow::getShadowRadius() {
	if(this->inGround) return 0;
	else return 0.1;
}
float Arrow::getShadowHeightOffs() {
	return 0;
}
void Arrow::playerTouch(Player* a2) {
	Level* level; // r7

	if(!this->level->isClientMaybe && this->inGround && this->isInReverse && this->shake <= 0) {
		ItemInstance v8(Item::arrow, 1);
		if(a2->inventory->add(&v8)) {
			level = this->level;
			level->playSound(this, "random.pop", 0.2,
							 (float)((float)((float)(Entity::sharedRandom.nextFloat() - Entity::sharedRandom.nextFloat()) * 0.7) + 1.0) * 2); //mcpe optimizes *2 to x+x
			a2->take(this, 1);
			this->remove();
		}
	}
}
int32_t Arrow::getEntityTypeId() const {
	return 80;
}
int32_t Arrow::getAuxData() {
	return this->shooterEID;
}
void Arrow::readAdditionalSaveData(CompoundTag* a2) {
	this->xTile = a2->getShort("xTile");
	this->yTile = a2->getShort("yTile");
	this->zTile = a2->getShort("zTile");
	this->inTile = a2->getByte("inTile");
	this->inData = a2->getByte("inData");
	this->shake = a2->getByte("shake");
	this->inGround = a2->getByte("inGround") == 1;
	this->isInReverse = a2->getByte("player") != 0;
}
void Arrow::addAdditonalSaveData(CompoundTag* a2) {
	a2->putShort("xTile", this->xTile);
	a2->putShort("yTile", this->yTile);
	a2->putShort("zTile", this->zTile);
	a2->putByte("inTile", this->inTile);
	a2->putByte("inData", this->inData);
	a2->putByte("shake", this->shake);
	a2->putByte("inGround", this->inGround);
	a2->putByte("player", this->isInReverse);
}
