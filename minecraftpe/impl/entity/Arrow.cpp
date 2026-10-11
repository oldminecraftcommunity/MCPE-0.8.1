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

const float Arrow::ARROW_BASE_DAMAGE = 2.0f;
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
	float d = Mth::sqrt((x * x) + (y * y) + (z * z));
	float nx = x / d;
	float ny = y / d;
	float nz = z / d;
	float mx = (nx + Entity::sharedRandom.nextGaussian() * (a6 * 0.0075f)) * a5;
	float my = (ny + Entity::sharedRandom.nextGaussian() * (a6 * 0.0075f)) * a5;
	float mz = (nz + Entity::sharedRandom.nextGaussian() * (a6 * 0.0075f)) * a5;

	this->motionX = mx;
	this->motionY = my;
	this->motionZ = mz;

	float v19 = Mth::sqrt(mx*mx + mz*mz);
	this->prevYaw = this->yaw = Mth::rad2deg(atan2f(mx, mz)) ;
	this->prevPitch = this->pitch = Mth::rad2deg(atan2f(my, v19));
	this->ticksInGround = 0;
}
void Arrow::lerpMotion(float x, float y, float z) {
	this->motionX = x;
	this->motionY = y;
	this->motionZ = z;
	if(this->prevPitch == 0.0 && this->prevYaw == 0.0) {
		float v8 = Mth::sqrt((x * x) + (z * z));
		this->prevYaw = this->yaw = Mth::rad2deg(atan2f(x, z));
		this->prevPitch = this->pitch = Mth::rad2deg(atan2f(y, v8));
		this->moveTo(this->posX, this->posY, this->posZ, this->yaw, this->pitch);
		this->ticksInGround = 0;
	}
}
void Arrow::tick() {

	Entity::tick();
	if(this->prevPitch == 0.0 && this->prevYaw == 0.0) {
		float v2 = Mth::sqrt((this->motionX * this->motionX) + (this->motionZ * this->motionZ));
		this->prevYaw = this->yaw = Mth::rad2deg(atan2f(this->motionX, this->motionZ));
		this->prevPitch = this->pitch = Mth::rad2deg(atan2f(this->motionY, v2));
	}
	if(this->shake > 0) this->shake -= 1;

	if(this->inGround) {
		this->motionZ = 0.0;
		this->motionY = 0.0;
		this->motionX = 0.0;
		int tileID = this->level->getTile(this->xTile, this->yTile, this->zTile);
		int tileData = this->level->getData(this->xTile, this->yTile, this->zTile);
		if(tileID == this->inTile && tileData == this->inData) {
			this->ticksInGround += 1;
			if(this->ticksInGround == 1200) {
				this->remove();
			}
		} else {
			this->inGround = 0;
			this->motionX *= Entity::sharedRandom.nextFloat() * 0.2f;
			this->motionY *= Entity::sharedRandom.nextFloat() * 0.2f;
			this->motionZ *= Entity::sharedRandom.nextFloat() * 0.2f;
			this->ticksInGround = 0;
			this->ticksInAir = 0;
		}
	} else {
		++this->ticksInAir;
		int tileID = this->level->getTile(this->xTile, this->yTile, this->zTile);
		if(tileID > 0) {
			Tile::tiles[tileID]->updateShape(this->level, this->xTile, this->yTile, this->zTile);
			AABB* v16 = Tile::tiles[tileID]->getAABB(this->level, this->xTile, this->yTile, this->zTile);
			if(v16) {
				;
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
				if(v16->contains(Vec3(this->posX, this->posY, this->posZ))){
					this->inGround = 1;
				}
			}
		}

		Vec3 start(this->posX, this->posY, this->posZ);
		Vec3 endVec(this->posX + this->motionX, this->posY + this->motionY, this->posZ + this->motionZ);
		HitResult a1 = this->level->clip(start, endVec, 0, 1);

		start.x = this->posX;
		start.y = this->posY;
		start.z = this->posZ;
		endVec.x = start.x + this->motionX;
		endVec.y = start.y + this->motionY;
		endVec.z = start.z + this->motionZ;

		if(a1.hitType != 2) {
			endVec = a1.hitVec;
		}

		float bestDist = 0.0;
		Entity* bestEnt = 0;
		std::vector<Entity*>* ents = this->level->getEntities(this, this->boundingBox.expand(this->motionX, this->motionY, this->motionZ).grow(1, 1, 1));
		for(int32_t v42 = 0; v42 < (uint32_t)ents->size(); ++v42) {
			Entity* v46 = ents->at(v42);
			if(v46->isPickable()) {
				if(v46->entityId != this->shooterEID || this->ticksInAir > 4) {
					HitResult a3 = v46->boundingBox.grow(0.3f, 0.3f, 0.3f).clip(start, endVec);
					if(a3.hitType != 2) {
						float v48 = sqrt(((a3.hitVec.x - start.x) * (a3.hitVec.x - start.x)) + ((a3.hitVec.y - start.y) * (a3.hitVec.y - start.y)) + ((a3.hitVec.z - start.z) * (a3.hitVec.z - start.z)));
						if(v48 < bestDist || bestDist == 0.0) {
							bestDist = v48;
							bestEnt = v46;
						}
					}
				}
			}
		}
		if(bestEnt) {
			a1 = HitResult(bestEnt);
		}
		if(a1.hitType != 2) {
			if(a1.hitType == 1) {
				float v49 = Mth::sqrt((this->motionX * this->motionX) + (this->motionY * this->motionY) + (this->motionZ * this->motionZ));
				int damage = (int32_t)ceilf(v49 + v49);
				if(this->critical) {
					damage += Entity::sharedRandom.genrand_int32() % (damage / 2 + 2);
				}
				if(a1.entity->hurt(this, damage)) {
					if(a1.entity->isMob()) {
						++((Mob*)a1.entity)->field_180;
					}
					this->level->playSound(this, "random.bowhit", 1.0, 1.2 / (float)((float)(Entity::sharedRandom.nextFloat() * 0.2f) + 0.9f));
					this->remove();
				} else {
					this->ticksInAir = 0;
					this->motionX *= -0.1f;
					this->motionY *= -0.1f;
					this->motionZ *= -0.1f;
					this->yaw += 180.0f;
					this->prevYaw += 180.0f;
				}
			} else {
				this->xTile = a1.x;
				this->yTile = a1.y;
				this->zTile = a1.z;
				this->inTile = this->level->getTile(this->xTile, this->yTile, this->zTile);
				this->inData = this->level->getData(this->xTile, this->yTile, this->zTile);
				this->motionX = a1.hitVec.x - this->posX;
				this->motionY = a1.hitVec.y - this->posY;
				this->motionZ = a1.hitVec.z - this->posZ;
				float v64 = Mth::sqrt(this->motionX*this->motionX + this->motionY*this->motionY + this->motionZ*this->motionZ);
				//v65 = this->level
				this->posX -= (this->motionX / v64) * 0.05f;
				this->posY -= (this->motionY / v64) * 0.05f;
				this->posZ -= (this->motionZ / v64) * 0.05f;
				this->level->playSound(this, "random.bowhit", 1.0, 1.2 / (float)((float)(Entity::sharedRandom.nextFloat() * 0.2) + 0.9));
				this->inGround = 1;
				this->shake = 7;
				this->critical = 0;
			}
		}
		if(this->critical) {
			for(int i = 0; i != 4; ++i) {
				this->level->addParticle(PT_CRIT, this->posX + (this->motionX * i) * 0.25f, this->posY + (this->motionY * i) * 0.25f, this->posZ + (this->motionZ * i) * 0.25f, -this->motionX, 0.2f - this->motionY, -this->motionZ, 0);
			}
		}
		this->posX += this->motionX;
		this->posY += this->motionY;
		this->posZ += this->motionZ;
		float v73 = Mth::sqrt(this->motionX*this->motionX + this->motionZ*this->motionZ);
		this->yaw = Mth::rad2deg(atan2f(this->motionX, this->motionZ));
		this->pitch = Mth::rad2deg(atan2f(this->motionY, v73));
		this->pitch = this->prevPitch + (pitch - this->prevPitch) * 0.2f;
		this->yaw = this->prevYaw + (float)((float)(this->yaw - this->prevYaw) * 0.2f);
		float mul;
		if(this->isInWater()) {
			int cnt = 4;
			do {
				this->level->addParticle(PT_BUBBLE, this->posX - (this->motionX * 0.25f), this->posY - (this->motionY * 0.25f), this->posZ - (this->motionZ * 0.25f), this->motionX, this->motionY, this->motionZ, 0);
			} while(--cnt);
			mul = 0.8f;
		} else {
			mul = 0.99f;
		}

		this->motionX *= mul;
		this->motionZ *= mul;
		this->motionY *= mul;

		this->motionY -= 0.05;
		this->setPos(this->posX, this->posY, this->posZ);
	}
}
float Arrow::getShadowHeightOffs() {
	return 0;
}
void Arrow::playerTouch(Player* a2) {
	if(!this->level->isClient && this->inGround && this->isInReverse && this->shake <= 0) {
		ItemInstance v8(Item::arrow, 1);
		if(a2->inventory->add(&v8)) {
			this->level->playSound(this, "random.pop", 0.2f, (((Entity::sharedRandom.nextFloat() - Entity::sharedRandom.nextFloat()) * 0.7f) + 1.0f) * 2);
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
