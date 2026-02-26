#include <entity/Throwable.hpp>
#include <nbt/CompoundTag.hpp>
#include <math/Vec3.hpp>
#include <math/Mth.hpp>
#include <entity/Mob.hpp>
#include <level/Level.hpp>
#include <math/HitResult.hpp>
#include <math.h>

Throwable::Throwable(Level* a2)
	: Entity(a2) {
	this->_init();
	this->setSize(0.25, 0.25);
}
Throwable::Throwable(Level* a2, Mob* a3)
	: Throwable(a2) {
	float posY; // s16
	float posX; // r7
	float v7; // r0
	float v8; // s15
	float v9; // s20
	float v10; // s13
	float posZ; // s15
	float v13; // s21
	float v14; // r1
	float v15; // r3
	float pitch; // s19
	float v18; // s15
	float v19; // s16

	this->auxData = a3->entityId;
	posY = a3->posY;
	posX = a3->posX;
	v7 = a3->getHeadHeight();
	this->moveTo(posX, posY + v7, a3->posZ, a3->yaw, a3->pitch);
	v8 = (float)((float)(this->yaw / 180.0) * 3.1416);
	v9 = Mth::cos(v8);
	v10 = this->posY - 0.1;
	posZ = this->posZ;
	v13 = Mth::sin(v8);
	v14 = this->posX - (float)(v9 * 0.16);
	this->posX = v14;
	this->posY = v10;
	v15 = posZ - (float)(v13 * 0.16);
	this->posZ = v15;
	this->setPos(v14, v10, v15);
	this->ridingHeight = 0.0;
	if(a3->isPlayer()) {
		this->shoot(a3->field_174, this->getThrowPower(), 1.0);
	} else {
		pitch = this->pitch;
		v18 = Mth::sin(((float)((float)(pitch / 180.0) * 3.1416) * 10430.0));
		v19 = Mth::sin(((float)((float)(pitch + this->getThrowUpAngleOffset()) / 180.0) * 3.1416));
		this->shoot(-(float)(v13 * v18), -v19, v9 * v18, this->getThrowPower(), 1.0);
	}
}
Throwable::Throwable(Level* a2, float x, float y, float z)
	: Throwable(a2) {
	this->setPos(x, y, z);
	this->ridingHeight = 0;
}

void Throwable::_init() {
	this->auxData = 0;
	this->shake = 0;
	this->inGround = 0;
	this->ticksInGround = 0;
	this->ticksInAir = 0;
	this->xTile = -1;
	this->yTile = -1;
	this->zTile = -1;
	this->inTile = 0;
}
void Throwable::shoot(const Vec3& a2, float a3, float a4) {
	this->shoot(a2.x, a2.y, a2.z, a3, a4);
}
void Throwable::shoot(float x, float y, float z, float a5, float a6) {
	float v10; // r0
	float v11; // s17
	float v12; // s21
	float v13; // s16
	float v14; // s17
	float v15; // s21
	float g; // r0
	float v17; // s17
	float v18; // s16
	float v19; // r5
	float v20; // s15
	float v21; // r0
	float v22; // s16

	v10 = Mth::sqrt((float)((float)(y * y) + (float)(x * x)) + (float)(z * z));
	if(v10 < 0.001) {
		v13 = 0.0;
		v12 = 0.0;
		v11 = 0.0;
	} else {
		v11 = x / v10;
		v12 = y / v10;
		v13 = z / v10;
	}
	v14 = v11 + (float)((float)(Entity::sharedRandom.nextGaussian() * 0.0075) * a6);
	v15 = v12 + (float)((float)(Entity::sharedRandom.nextGaussian() * 0.0075) * a6);
	g = Entity::sharedRandom.nextGaussian();
	v17 = v14 * a5;
	this->motionX = v17;
	v18 = (float)(v13 + (float)((float)(g * 0.0075) * a6)) * a5;
	this->motionZ = v18;
	this->motionY = v15 * a5;
	v19 = Mth::sqrt((float)(v18 * v18) + (float)(v17 * v17));
	v20 = (float)(Mth::atan2(v17, v18) * 180.0) / 3.1416;
	this->yaw = v20;
	this->prevYaw = v20;
	v21 = Mth::atan2(v15 * a5, v19);
	this->ticksInGround = 0;
	v22 = (float)(v21 * 180.0) / 3.1416;
	this->pitch = v22;
	this->prevPitch = v22;
}

Throwable::~Throwable() {
}
void Throwable::lerpMotion(float x, float y, float z) {
	float v8; // r7
	float v9; // s15
	float v10; // s16

	this->motionX = x;
	this->motionY = y;
	this->motionZ = z;
	if(this->prevPitch == 0.0 && this->prevYaw == 0.0) {
		v8 = Mth::sqrt((float)(z * z) + (float)(x * x));
		v9 = (float)(Mth::atan2(x, z) * 180.0) / 3.1416;
		this->yaw = v9;
		this->prevYaw = v9;
		v10 = (float)(Mth::atan2(y, v8) * 180.0) / 3.1416;
		this->pitch = v10;
		this->prevPitch = v10;
	}
}
void Throwable::tick() {
	int shake; // r3
	int v7; // r3
	float posX; // s12
	float posY; // s13
	float posZ; // s14
	Level* level; // r1
	float v12; // s9
	float v13; // s10
	float v14; // s11
	float v15; // s12
	float v16; // s13
	float v17; // s14
	float v18; // s11
	float v19; // s15
	float motionX; // s12
	float motionY; // s13
	float motionZ; // s14
	Level* v23; // r0
	float minX; // s6
	float minY; // s7
	float minZ; // s8
	float maxX; // s9
	float maxY; // s10
	float maxZ; // s11
	float v31; // s17
	Entity* v32; // r7
	Entity* v36; // r5
	float v38; // s15
	float v39; // s15
	float v40; // s13
	float v41; // s14
	float v42; // s13
	float v43; // s14
	float v44; // r5
	float v45; // s13
	float v46; // r0
	float v47; // s15
	float prevPitch; // s14
	float v49; // s14
	float v50; // s11
	float yaw; // s13
	float prevYaw; // s15
	float v53; // s15
	float v55; // s17
	int32_t v56; // r5
	float v57; // s15
	float v58; // s13
	float v60; // r1
	float v61; // r2

	this->prevPosX = this->posX;
	this->prevPosY = this->posY;
	this->prevPosZ = this->posZ;
	Entity::tick();
	shake = this->shake;
	if(shake > 0) {
		this->shake = shake - 1;
	}
	if(!this->inGround) {
		++this->ticksInAir;
		goto LABEL_9;
	}
	if(this->level->getTile(this->xTile, this->yTile, this->zTile) != this->inTile) {
		this->inGround = 0;
		this->motionX = this->motionX * (float)(Entity::sharedRandom.nextFloat() * 0.2);
		this->motionY = this->motionY * (float)(Entity::sharedRandom.nextFloat() * 0.2);
		this->ticksInGround = 0;
		this->ticksInAir = 0;
		this->motionZ = this->motionZ * (float)(Entity::sharedRandom.nextFloat() * 0.2);
LABEL_9:
		posX = this->posX;
		posY = this->posY;
		posZ = this->posZ;
		level = this->level;
		if(posX == 0.0) {
			v12 = 0.0;
		} else {
			v12 = this->posX;
		}
		if(posY == 0.0) {
			v13 = 0.0;
		} else {
			v13 = posY;
		}
		if(posZ == 0.0) {
			v14 = 0.0;
		} else {
			v14 = posZ;
		}
		Vec3 start(v12, v13, v14); // [sp+18h] [bp-B0h] BYREF

		v15 = posX + this->motionX;
		v16 = posY + this->motionY;
		v17 = posZ + this->motionZ;
		if(v15 == 0.0) {
			v15 = 0.0;
		}
		if(v16 == 0.0) {
			v16 = 0.0;
		}
		if(v17 == 0.0) {
			v17 = 0.0;
		}
		Vec3 end(v15, v16, v17); // [sp+24h] [bp-A4h] BYREF

		HitResult a1 = level->clip(start, end, 0, 0);
		v18 = this->posY;
		v19 = this->posZ;
		start.x = this->posX;
		start.y = v18;
		start.z = v19;
		motionX = this->motionX;
		motionY = this->motionY;
		motionZ = this->motionZ;
		end.x = start.x + motionX;
		end.y = v18 + motionY;
		end.z = v19 + motionZ;
		if(a1.hitType != 2) {
			end = a1.hitVec;
		}
		v23 = this->level;
		if(!v23->isClientMaybe) {
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
			if(motionY >= 0.0) {
				if(motionY > 0.0) {
					maxY = maxY + motionY;
				}
			} else {
				minY = minY + motionY;
			}
			if(motionZ >= 0.0) {
				if(motionZ > 0.0) {
					maxZ = maxZ + motionZ;
				}
			} else {
				minZ = minZ + motionZ;
			}
			v31 = 0.0;
			v32 = 0;

			std::vector<Entity*>* entities = v23->getEntities(this, {minX - 1.0f, minY - 1.0f, minZ - 1.0f, maxX + 1.0f, maxY + 1.0f, maxZ + 1.0f});
			for(int32_t v30 = 0; v30 < entities->size(); ++v30) {
				v36 = entities->at(v30);
				if(v36->isPickable()) {
					if(v36->entityId != this->auxData || this->ticksInAir > 4) {
						AABB v69{v36->boundingBox.minX - 0.3f, v36->boundingBox.minY - 0.3f, v36->boundingBox.minZ - 0.3f, v36->boundingBox.maxX + 0.3f, v36->boundingBox.maxY + 0.3f, v36->boundingBox.maxZ + 0.3f};

						HitResult v71 = v69.clip(start, end);
						if(v71.hitType != 2) {
							double v37 = sqrt((float)((float)((float)((float)(v71.hitVec.y - start.y) * (float)(v71.hitVec.y - start.y)) + (float)((float)(v71.hitVec.x - start.x) * (float)(v71.hitVec.x - start.x))) + (float)((float)(v71.hitVec.z - start.z) * (float)(v71.hitVec.z - start.z))));
							v38 = v37;
							if(v38 < v31 || v31 == 0.0) {
								v31 = v37;
								v32 = v36;
							}
						}
					}
				}
			}

			if(v32) {
				a1 = HitResult(v32);
			}
		}
		if(a1.hitType != 2) {
			this->onHit(a1);
		}
		v39 = this->motionX;
		v40 = this->posY;
		this->posX = this->posX + v39;
		v41 = v40 + this->motionY;
		v42 = this->posZ;
		this->posY = v41;
		v43 = this->motionZ;
		this->posZ = v42 + v43;
		v44 = Mth::sqrt((float)(v43 * v43) + (float)(v39 * v39));
		v45 = Mth::atan2(this->motionX, this->motionZ);
		v46 = this->motionY;
		this->yaw = (float)(v45 * 180.0) / 3.1416;
		v47 = (float)(Mth::atan2(v46, v44) * 180.0) / 3.1416;
		this->pitch = v47;
		while(1) {
			prevPitch = this->prevPitch;
			if((float)(v47 - prevPitch) >= -180.0) {
				break;
			}
			this->prevPitch = prevPitch - 360.0;
		}
		while(1) {
			v49 = this->prevPitch;
			v50 = v47 - v49;
			if((float)(v47 - v49) < 180.0) {
				break;
			}
			this->prevPitch = v49 + 360.0;
		}
		yaw = this->yaw;
		while(1) {
			prevYaw = this->prevYaw;
			if((float)(yaw - prevYaw) >= -180.0) {
				break;
			}
			this->prevYaw = prevYaw - 360.0;
		}
		while(1) {
			v53 = this->prevYaw;
			if((float)(yaw - v53) < 180.0) {
				break;
			}
			this->prevYaw = v53 + 360.0;
		}
		this->pitch = v49 + (float)(v50 * 0.2);
		this->yaw = v53 + (float)((float)(yaw - v53) * 0.2);
		v55 = this->getGravity();
		if ( this->isInWater())
		{
			v56 = 4;
			do
			{
				this->level->addParticle(
					PT_BUBBLE,
					this->posX - (float)(this->motionX * 0.25),
					this->posY - (float)(this->motionY * 0.25),
					this->posZ - (float)(this->motionZ * 0.25),
					this->motionX,
					this->motionY,
					this->motionZ,
					0);
				--v56;
			}
			while ( v56 );
			v57 = 0.8;
		}
		else
		{
			v57 = 0.99;
		}
		this->motionX = this->motionX * v57;
		this->motionY = (float)(v57 * this->motionY) - v55;
		this->motionZ = this->motionZ * v57;
		this->setPos(this->posX, this->posY, this->posZ);
		return;
	}
	v7 = this->ticksInGround + 1;
	this->ticksInGround = v7;
	if ( v7 == 1200 )
	{
		this->remove();
	}
}
float Throwable::getShadowHeightOffs() {
	return 0;
}
bool_t Throwable::shouldRenderAtSqrDistance(float a2){
	float v2; // s15

	v2 = ((this->boundingBox.maxX - this->boundingBox.minX) + (this->boundingBox.maxY - this->boundingBox.minY) + (this->boundingBox.maxZ - this->boundingBox.minZ)) / 3.0 * 4.0 * 64.0;
	return a2 < (float)(v2 * v2);
}
int32_t Throwable::getAuxData() {
	return this->auxData;
}
void Throwable::readAdditionalSaveData(CompoundTag* a2) {
	this->xTile = a2->getShort("xTile");
	this->yTile = a2->getShort("yTile");
	this->zTile = a2->getShort("zTile");
	this->inTile = a2->getByte("inTile");
	this->shake = a2->getByte("shake");
	this->inGround = a2->getByte("inGround") == 1;
}
void Throwable::addAdditonalSaveData(CompoundTag* a2) {
	a2->putShort("xTile", this->xTile);
	a2->putShort("yTile", this->yTile);
	a2->putShort("zTile", this->zTile);
	a2->putByte("inTile", this->inTile);
	a2->putByte("shake", this->shake);
	a2->putByte("inGround", this->inGround);

}
float Throwable::getThrowPower() {
	return 1.5;
}
float Throwable::getThrowUpAngleOffset() {
	return 0;
}
float Throwable::getGravity() {
	return 0.03;
}
