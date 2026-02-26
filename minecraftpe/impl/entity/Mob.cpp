#include <entity/Mob.hpp>
#include <nbt/CompoundTag.hpp>
#include <level/Level.hpp>
#include <item/Item.hpp>
#include <utils.h>
#include <math/Mth.hpp>
#include <math.h>
#include <tile/Tile.hpp>
#include <entity/ai/BodyControl.hpp>
#include <entity/ai/JumpControl.hpp>
#include <entity/ai/LookControl.hpp>
#include <entity/ai/MoveControl.hpp>
#include <entity/path/PathNavigation.hpp>
#include <entity/ai/Sensing.hpp>
#include <entity/Player.hpp>
#include <tile/material/Material.hpp>
#include <network/packet/MoveEntityPacket_PosRot.hpp>
#include <network/packet/SetEntityMotionPacket.hpp>
#include <network/packet/RotateHeadPacket.hpp>
#include <network/RakNetInstance.hpp>

Mob::Mob(Level* a2)
	: Entity(a2) {
	this->field_124 = 0.0;
	this->field_128 = 0.0;
	this->field_130 = 0.0;
	this->field_118 = 20;
	this->field_134 = 0.0;
	this->field_138 = 0.0;
	this->field_168 = 0.0;
	this->field_16C = 0.0;
	this->field_170 = 0.0;
	this->field_174.x = 0.0;
	this->field_174.y = 0.0;
	this->field_174.z = 0.0;
	this->field_180 = 0;
	this->field_184 = 0;
	this->hasArmorMaybe = 0;
	this->field_B68 = 0;
	this->field_B6C = 0;
	this->field_B74 = 0.0;
	this->jumpMovementFactor = 0.02;
	this->field_B7C = 1.0;
	this->skin = "mob/char.png";
	this->field_B84 = "";
	this->field_B88 = 0;
	this->field_B8C = 0.0;
	this->field_B90 = 0.0;
	this->field_B94 = 0.0;
	this->field_B98 = 0.0;
	this->field_BA0 = 1.0;
	this->field_BA4 = 0;
	this->field_BA8 = 0;
	this->field_BAC = 0.0;
	this->field_BB0 = 0.0;
	this->field_BB4 = 0.0;
	this->field_BB8 = 0.0;
	this->field_BBC = 0.0;
	this->field_BC0 = 0;
	this->field_BC4 = 0;
	this->field_BC8 = 0.0;
	this->field_BCC = 0.0;
	this->field_BD0 = 0.0;
	this->field_BD4 = 0.0;
	this->field_BD8 = 0.0;
	this->field_BDC = 0.0;
	this->field_BE0 = 0.0;
	this->field_BE4 = 0.0;
	this->field_BE8 = 0;
	this->field_BEC = 1;
	this->isJumping = 0;
	this->field_BEE = 1;
	this->targetEID = 0;
	this->maybeEntityWhichIsBeingLookedByThisEntity = 0;
	this->field_C58 = 0;
	this->field_C5C = 0;
	this->field_C60 = 0;
	this->speed = 0.0;
	this->synchedEntityData.define<int8_t>(0, 0);
	this->synchedEntityData.define<int16_t>(1, 300);
	this->_init();
	this->health = 10;
	this->field_FC = 1;
	this->field_C64 = -(a2->random.genrand_int32() % 0x64);
	float posY = this->posY;
	float posX = this->posX;
	float posZ = this->posZ;
	this->field_120 = (float)(Mth::random() + 1.0) * 0.01;
	this->setPos(posX, posY, posZ);
	this->field_11C = Mth::random() * 12398.0;
	float v11 = Mth::random();
	this->stepHeight = 0.5;
	float v12 = (float)(v11 * 3.1416) + (float)(v11 * 3.1416);
	this->yaw = v12;
	this->headYaw = v12;
	this->lookControl = new LookControl(this);
	this->moveControl = new MoveControl(this);
	this->jumpControl = new JumpControl(this);
	this->bodyControl = new BodyControl(this);
	this->navigation = new PathNavigation(this, a2, 16.0);
	this->sensing = new Sensing(this);
}
void Mob::_init() {
	this->field_124 = 0.0;
	this->field_128 = 0.0;
	this->field_B9C = 0.0;
	this->field_BC0 = 0;
	this->deathTime = 0;
	this->attackTime = 0;
	this->field_148 = 0;
	this->hurtTime = 0;
	this->field_160 = 0;
	this->noActionTime = 0;
	this->field_164 = 0;
	this->field_15C = 0;
	this->field_158 = 0;
	this->field_14C = 0;
	this->moveStrafe = 0.0;
	this->moveForward = 0.0;
	this->field_B64 = 0.0;
	this->field_B7C = 1.0;
	this->health = 10;
	this->prevHealthMaybe = 20;
}
void Mob::checkDespawn(Mob* source) {
	int32_t v4; // r0
	float v5; // s14
	float posZ; // s13
	float v7; // s16
	int32_t v8; // r5
	float v9; // s16

	if(source) {
		v4 = this->removeWhenFarAway();
		v5 = source->posX - this->posX;
		posZ = source->posZ;
		v7 = source->posY - this->posY;
		v8 = v4;
		v9 = (float)((float)(v7 * v7) + (float)(v5 * v5)) + (float)((float)(posZ - this->posZ) * (float)(posZ - this->posZ));
		if(v4) {
			if(v9 > 9216.0) // force despawn 96 blocks away
			{
				this->remove();
			}
		}
		if(this->noActionTime <= 600 || this->random.genrand_int32() % 0x320 || !v8 || v9 <= 1024.0) {
			this->noActionTime = 0;
		} else {
			this->remove();
		}
	}
}
void Mob::checkDespawn() {
	this->checkDespawn((Mob*)this->level->getNearestPlayer(this, -1.0));
}
JumpControl* Mob::getJumpControl() {
	return this->jumpControl;
}
LookControl* Mob::getLookControl() {
	return this->lookControl;
}
MoveControl* Mob::getMoveControl() {
	return this->moveControl;
}
PathNavigation* Mob::getNavigation() {
	return this->navigation;
}
Sensing* Mob::getSensing() {
	return this->sensing;
}
bool_t Mob::getSharedFlag(int32_t a2) {
	return (this->synchedEntityData.getByte(0) >> a2) & 1;
}
float Mob::getSpeed() {
	if(this->useNewAi()) return this->speed;
	return this->getBaseSpeed();
}
float Mob::getYHeadRot() {
	return this->headYaw;
}
bool_t Mob::interpolateOnly() {
	return this->level->isClientMaybe;
}
void Mob::pushEntities() {
	float maxX; // s12
	float v3; // s11
	float maxY; // s13
	float minX; // s10
	Level* level; // r0
	uint32_t v7; // r6
	float maxZ; // s14
	Mob* v10; // r5

	if(!this->isPlayer() || !this->isSleeping()) {
		maxX = this->boundingBox.maxX;
		v3 = this->boundingBox.minZ - 0.2;
		maxY = this->boundingBox.maxY;
		minX = this->boundingBox.minX;
		level = this->level;
		v7 = 0;
		maxZ = this->boundingBox.maxZ;

		std::vector<struct Entity*>* ents = level->getEntities(this, {minX - 0.2f, this->boundingBox.minY, v3, maxX + 0.2f, maxY + 0.0f, maxZ + 0.2f});
		while(v7 < ents->size()) {
			v10 = (Mob*)ents->at(v7);
			if(!v10->isPlayer() || !v10->isSleeping()) {
				if(v10->isPushable()) {
					v10->push(this);
				}
			}
			++v7;
		}
	}
}
void Mob::setJumping(bool_t a2) {
	this->isJumping = a2;
}
void Mob::setSharedFlag(int32_t a2, bool_t a3) {
	if(a3) {
		int32_t oldf = this->synchedEntityData.getByte(0);
		uint8_t newf = (1 << a2) | oldf;
		this->synchedEntityData.setFlag<char>(0, newf);
		if(((newf >> a2) & 1) == ((oldf >> a2) & 1)) return;
	} else {
		int32_t oldf = this->synchedEntityData.getByte(0);
		uint8_t newf = oldf & ~(1 << a2);
		this->synchedEntityData.clearFlag<char>(0, newf);
		if(((newf >> a2) & 1) == ((oldf >> a2) & 1)) return;
	}
	this->synchedEntityData.markDirty(0);
}
void Mob::setSpeed(float a2) {
	this->speed = a2;
	this->moveForward = a2;
}
void Mob::setYHeadRot(float a2) {
	this->headYaw = a2;
}
void Mob::setYya(float a2) {
	this->moveForward = a2;
}
void Mob::updateAttackAnim() {
	int32_t v1; // r3

	v1 = this->field_B68;
	if(this->field_B68 && (v1 = this->field_B6C + 1, v1 > 7)) {
		this->field_B6C = 0;
		this->field_B68 = 0;
	} else {
		this->field_B6C = v1;
	}
	this->field_138 = vcvts_n_f32_s32(this->field_B6C, 3u);
}
Mob* Mob::updateMobId(int32_t* a2) {
	int32_t v3; // r1
	Mob* result; // r0

	v3 = *a2;
	if(v3 <= 0 || (result = this->level->getMob(v3)) == 0) {
		result = 0;
		*a2 = 0;
	}
	return result;
}

Mob::~Mob() {
	if(this->lookControl) delete this->lookControl;
	if(this->moveControl) delete this->moveControl;
	if(this->jumpControl) delete this->jumpControl;
	delete this->bodyControl;
	if(this->navigation) {
		delete this->navigation;
	}
	if(this->sensing) {
		delete this->sensing;
	}
}
void Mob::reset() {
	Entity::reset();
	this->_init();
}
void Mob::lerpTo(float a2, float a3, float a4, float a5, float a6, int32_t a7) {
	this->field_BAC = a2;
	this->field_BB0 = a3 + this->ridingHeight;
	this->field_BB4 = a4;
	this->field_BB8 = a5;
	this->field_BBC = a6;
	this->field_BA8 = a7;
}
void Mob::tick() {
	Level* level; // r3
	int32_t v3; // r3
	int32_t v4; // r2
	int32_t v5; // r3
	float yaw; // s13
	float v7; // s14
	float x; // s10
	float y; // s11
	float z; // s12
	float i; // s15
	float v12; // s13
	float pitch; // s15
	float v14; // s13
	float v16; // s19
	float v17; // s20
	double v18; // r0
	float v19; // s17
	float v20; // s15
	float v21; // s18
	float v22; // s14
	float v23; // s15
	bool_t onGround; // r3
	float v25; // s15
	float j; // s14
	float v27; // s13
	float k; // s15
	bool_t v29; // r3
	float v30; // s14
	float v31; // s13
	float prevYaw; // s15
	float v33; // s14
	float v34; // s13
	float v35; // s14
	float v36; // s14
	float v37; // s13
	float prevPitch; // s14
	float v39; // s14
	float headYaw; // s13
	float v41; // s14
	float v42; // s14

	Entity::tick();
	level = this->level;
	if(!level->isClientMaybe) {
		this->setSharedFlag(0, this->fire > 0);
	}
	v3 = this->field_180;
	if(v3 > 0) {
		if(this->field_184 <= 0) {
			this->field_184 = 60;
		}
		v4 = this->field_184 - 1;
		this->field_184 = v4;
		if(v4 <= 0) {
			this->field_180 = v3 - 1;
		}
	}
	v5 = this->field_BA8;
	if(v5 > 0) {
		yaw = this->yaw;
		v7 = (float)v5;
		x = this->posX + (float)((float)(this->field_BAC - this->posX) / (float)v5);
		y = this->posY + (float)((float)(this->field_BB0 - this->posY) / (float)v5);
		z = this->posZ + (float)((float)(this->field_BB4 - this->posZ) / (float)v5);
		for(i = this->field_BB8 - yaw; i < -180.0; i = i + 360.0) {
			;
		}
		while(i >= 180.0) {
			i = i - 360.0;
		}
		v12 = yaw + (float)(i / v7);
		pitch = this->pitch;
		this->yaw = v12;
		v14 = this->field_BBC - pitch;
		this->field_BA8 = v5 - 1;
		this->pitch = pitch + (float)(v14 / v7);
		this->setPos(x, y, z);
		this->setRot(this->yaw, this->pitch);
	}
	this->aiStep();
	v16 = this->posX - this->prevX;
	v17 = this->posZ - this->prevZ;
	v18 = sqrt((float)((float)(v17 * v17) + (float)(v16 * v16)));
	v19 = this->field_124;
	this->field_B8C = this->field_B90;
	v20 = v18;
	if(v20 <= 0.05) {
		v23 = 0.0;
		v21 = 0.0;
	} else {
		v21 = v20 * 3.0;
		v22 = atan2(v17, v16);
		v19 = (float)(v22 * 57.296) - 90.0;
		v23 = 1.0;
	}
	onGround = this->onGround;
	if(this->field_138 > 0.0) {
		v19 = this->yaw;
	}
	if(!this->onGround) {
		v23 = 0.0;
	}
	this->field_B90 = this->field_B90 + (float)((float)(v23 - this->field_B90) * 0.3);
	if(this->useNewAi()) {
		this->bodyControl->clientTick();
	} else {
		v25 = this->field_124;
		for(j = v19 - v25; j < -180.0; j = j + 360.0) {
			;
		}
		while(j >= 180.0) {
			j = j - 360.0;
		}
		v27 = this->yaw;
		for(k = v27 - (float)(v25 + (float)(j * 0.3)); k < -180.0; k = k + 360.0) {
			;
		}
		while(k >= 180.0) {
			k = k - 360.0;
		}
		v29 = k < -90.0 || k >= 90.0;
		if(k < -75.0) {
			k = -75.0;
		} else if(k >= 75.0) {
			k = 75.0;
		}
		v30 = v27 - k;
		if((float)(k * k) > 2500.0) {
			v30 = v30 + (float)(k * 0.2);
		}
		this->field_124 = v30;
		if(v29) {
			v21 = -v21;
		}
	}
	v31 = this->yaw;
	while(1) {
		prevYaw = this->prevYaw;
		if((float)(v31 - prevYaw) >= -180.0) {
			break;
		}
		this->prevYaw = prevYaw - 360.0;
	}
	while(1) {
		v33 = this->prevYaw;
		if((float)(v31 - v33) < 180.0) {
			break;
		}
		this->prevYaw = v33 + 360.0;
	}
	v34 = this->field_124;
	while(1) {
		v35 = this->field_128;
		if((float)(v34 - v35) >= -180.0) {
			break;
		}
		this->field_128 = v35 - 360.0;
	}
	while(1) {
		v36 = this->field_128;
		if((float)(v34 - v36) < 180.0) {
			break;
		}
		this->field_128 = v36 + 360.0;
	}
	v37 = this->pitch;
	while(1) {
		prevPitch = this->prevPitch;
		if((float)(v37 - prevPitch) >= -180.0) {
			break;
		}
		this->prevPitch = prevPitch - 360.0;
	}
	while(1) {
		v39 = this->prevPitch;
		if((float)(v37 - v39) < 180.0) {
			break;
		}
		this->prevPitch = v39 + 360.0;
	}
	headYaw = this->headYaw;
	while(1) {
		v41 = this->field_130;
		if((float)(headYaw - v41) >= -180.0) {
			break;
		}
		this->field_130 = v41 - 360.0;
	}
	while(1) {
		v42 = this->field_130;
		if((float)(headYaw - v42) < 180.0) {
			break;
		}
		this->field_130 = v42 + 360.0;
	}
	this->updateWalkAnim();
	this->field_B94 = this->field_B94 + v21;
}
void Mob::baseTick() {
	int v2; // r3
	int v3; // r7
	float v5; // s17
	float v7; // s16
	float v8; // s18
	float v9; // r0
	Level* level; // r3
	int attackTime; // r3
	int hurtTime; // r3
	int field_DC; // r3
	int v15; // r3
	float yaw; // s14
	float v17; // r3
	float pitch; // s15
	int v19; // r3
	int v20; // r7
	float v21; // s24
	float v22; // s23
	float v23; // s22
	float v24; // s21
	float v25; // s20
	float v26; // r0
	float posX; // s17
	Level* v28; // r8
	float v29; // s19
	float v30; // r0
	float entityWidth; // s15
	float v32; // s25
	float posY; // s17
	float v34; // r0
	float posZ; // s26
	float v36; // s17
	float v37; // r0
	float* v38; // r8
	float* v39; // r7
	float* v40; // r5
	float motionY; // s13
	float motionX; // s12
	float motionZ; // s14
	float v44; // s15
	int v50; // r0
	int v51; // r3
	int32_t v52; // r5
	//char v65; // [sp+3Ch] [bp-54h]

	this->field_134 = this->field_138;
	Entity::baseTick();
	v2 = this->field_C64;
	this->field_C64 = v2 + 1;
	if(!(v2 << 28) && (int32_t)(this->random.genrand_int32() % 0x7D0) < this->field_C64) {
		this->field_C64 = -this->getAmbientSoundInterval();
		this->playAmbientSound();
	}
	if(this->isAlive()) {
		if(this->isInWall()) {
			this->hurt(0, 1);
		}
	}
	if(this->isAlive() && this->isUnderLiquid(Material::water) && !this->isWaterMob()) {
		if(this->air == -19) {
			v3 = 8;
			this->air = 0;
			do {
				v5 = this->random.nextFloat() - this->random.nextFloat();
				v7 = this->random.nextFloat() - this->random.nextFloat();
				v8 = this->random.nextFloat();
				v9 = this->random.nextFloat();
				this->level->addParticle(PT_BUBBLE, v5 + this->posX, v7 + this->posY, (float)(v8 - v9) + this->posZ, this->motionX, this->motionY, this->motionZ, 0);
				--v3;
			} while(v3);
			this->hurt(0, 2);
		} else {
			--this->air;
		}
		level = this->level;
		if(!level->isClientMaybe && this->isRiding()) {
			if(this->ridingAt->isMob()) {
				this->ride(0);
			}
		}
	} else {
		this->air = this->field_10C;
	}
	this->field_158 = this->field_15C;
	attackTime = this->attackTime;
	if(attackTime > 0) {
		this->attackTime = attackTime - 1;
	}
	hurtTime = this->hurtTime;
	if(hurtTime > 0) {
		this->hurtTime = hurtTime - 1;
	}
	field_DC = this->field_DC;
	if(field_DC > 0) {
		this->field_DC = field_DC - 1;
	}
	if(this->field_C5C > 0) {
		v15 = this->field_C60;
		if(v15 <= 0) {
			this->setLastHurtByMob(0);
		} else {
			this->field_C60 = v15 - 1;
		}
	}
	if(this->health <= 0) {
		v19 = this->deathTime + 1;
		this->deathTime = v19;
		if(v19 > 20) {
			v20 = 20;
			this->beforeRemove();
			this->remove();
			do {
				v21 = this->random.nextFloat();
				v22 = this->random.nextFloat();
				v23 = this->random.nextFloat();
				v24 = this->random.nextFloat();
				v25 = this->random.nextFloat();
				v26 = this->random.nextFloat();
				posX = this->posX;
				v28 = this->level;
				v29 = v26;
				v30 = this->random.nextFloat();
				entityWidth = this->entityWidth;
				v32 = posX + (float)((float)(v30 * entityWidth) + (float)(v30 * entityWidth));
				posY = this->posY;
				v34 = this->random.nextFloat();
				posZ = this->posZ;
				v36 = posY + (float)(v34 * this->entityHeight);
				v37 = this->random.nextFloat();
				v28->addParticle(PT_EXPLODE, v32 - entityWidth, v36, (float)(posZ + (float)((float)(v37 * this->entityWidth) + (float)(v37 * this->entityWidth))) - this->entityWidth, (float)((float)((float)(v21 + v21) - 1.0) * (float)((float)(v22 + v22) - 1.0)) * 0.02, (float)((float)((float)(v23 + v23) - 1.0) * (float)((float)(v24 + v24) - 1.0)) * 0.02, (float)((float)((float)(v25 + v25) - 1.0) * (float)((float)(v29 + v29) - 1.0)) * 0.02, 0);
				--v20;
			} while(v20);
		}
	}
	this->field_B98 = this->field_B94;
	yaw = this->yaw;
	v17 = this->field_124;
	this->prevYaw = yaw;
	pitch = this->pitch;
	this->prevPitch = pitch;
	this->field_128 = v17;
	this->field_130 = this->headYaw;
	if(!this->level->isClientMaybe) {
		if(this->field_BEE) {
			v38 = &this->field_BD0;
			v39 = &this->field_BD4;
			v40 = &this->field_BD8;
			if(fabsf(this->posX - this->field_BC8) > 0.1 || fabsf(this->posY - this->field_BCC) > 0.05 || fabsf(this->posZ - *v38) > 0.1 || fabsf(*v39 - pitch) > 1.0 || fabsf(*v40 - yaw) > 1.0) {
				MoveEntityPacket_PosRot movePacket(this);
				this->level->rakNetInstance->send(movePacket);
				this->field_BC8 = this->posX;
				this->field_BCC = this->posY;
				*v38 = this->posZ;
				*v39 = this->pitch;
				*v40 = this->yaw;
			}
		}
		motionY = this->motionY;
		motionX = this->motionX;
		motionZ = this->motionZ;
		v44 = (float)((float)((float)(motionY - this->field_BE0) * (float)(motionY - this->field_BE0)) + (float)((float)(motionX - this->field_BDC) * (float)(motionX - this->field_BDC))) + (float)((float)(motionZ - this->field_BE4) * (float)(motionZ - this->field_BE4));
		if(v44 > 0.0004 || v44 > 0.0 && motionX == 0.0 && motionY == 0.0 && motionZ == 0.0) {
			this->field_BDC = motionX;
			this->field_BE0 = motionY;
			this->field_BE4 = motionZ;
			SetEntityMotionPacket packet(this);
			this->level->rakNetInstance->send(packet);
		}
		v50 = Mth::floor((float)(this->headYaw * 256.0) / 360.0);
		v51 = v50 - this->field_BE8;
		v52 = v50;
		if(v51 < 0) {
			v51 = this->field_BE8 - v50;
		}
		if(v51 > 3) {
			RotateHeadPacket packet(this, v52);
			this->level->rakNetInstance->send(packet);
			this->field_BE8 = v52;
		}
	}
}
void Mob::rideTick() {
	Entity::rideTick();
	this->field_B8C = this->field_B90;
	this->field_B90 = 0.0;
	this->fallDistance = 0.0;
}
float Mob::getHeadHeight() {
	return this->entityHeight * 0.85;
}
bool_t Mob::isPickable() {
	return !this->isDead;
}
bool_t Mob::isPushable() {
	return !this->isDead;
}
bool_t Mob::isShootable() {
	return 2;
}
bool_t Mob::isSneaking() {
	return this->getSharedFlag(1);
}
bool_t Mob::isAlive() {
	return !this->isDead && this->health > 0;
}
bool_t Mob::isOnFire() {
	if(this->fire > 0) return 1;
	return this->getSharedFlag(0);
}
bool_t Mob::hurt(Entity* a2, int32_t a3) {
	Level* level; // r3
	bool_t isClientMaybe; // r7
	int32_t health; // r3
	int32_t v9; // r2
	int32_t v10; // r1
	float v12; // s18
	float i; // s19
	float v14; // s18
	float v15; // s19
	float v16; // r0
	float v18; // r0

	isClientMaybe = this->level->isClientMaybe;
	if(isClientMaybe) {
		return 0;
	}
	health = this->health;
	this->noActionTime = isClientMaybe;
	if(health <= 0) {
		return 0;
	}
	this->field_16C = 1.5;
	v9 = this->field_118;
	if((float)this->field_DC <= vcvts_n_f32_s32(v9, 1u)) {
		this->prevHealthMaybe = health;
		isClientMaybe = 1;
		this->field_BC0 = a3;
		this->field_DC = v9;
		this->actuallyHurt(a3);
		this->field_148 = 10;
		this->hurtTime = 10;
		goto LABEL_7;
	}
	v10 = this->field_BC0;
	if(a3 <= v10) {
		return 0;
	}
	this->actuallyHurt(a3 - v10);
	this->field_BC0 = a3;
LABEL_7:
	this->field_14C = 0.0;
	if(isClientMaybe) {
		this->level->broadcastEntityEvent(this, 2);
		this->markHurt();
		if(a2) {
			v12 = a2->posX - this->posX;
			for(i = a2->posZ - this->posZ; (float)((float)(i * i) + (float)(v12 * v12)) < 0.0001; i = (float)(v15 - Mth::random()) * 0.01) {
				v14 = Mth::random();
				v12 = (float)(v14 - Mth::random()) * 0.01;
				v15 = Mth::random();
			}
			v16 = atan2f(i, v12);
			this->field_14C = (float)(v16 * 57.296) - this->yaw;
			this->knockback(a2, a3, v12, i);
			if(a2->isMob()) {
				this->setLastHurtByMob((Mob*)a2);
			}
		} else {
			v18 = Mth::random();
			this->field_14C = (float)(int32_t)(float)(v18 + v18) * 180.0;
		}
	}
	if(this->health > 0) {
		if(isClientMaybe) {
			this->level->playSound(this, this->getHurtSound(), this->getSoundVolume(), this->getVoicePitch());
		}
	} else {
		if(isClientMaybe) {
			this->level->playSound(this, this->getDeathSound(), this->getSoundVolume(), this->getVoicePitch());
		}
		this->die(a2);
	}
	return 1;
}
void Mob::animateHurt() {
	this->field_148 = 10;
	this->hurtTime = 10;
	this->field_14C = 0;
}
void Mob::handleEntityEvent(int8_t event) {
	Level* level; // r6
	Level* v6; // r6

	if(event == 2) {
		level = this->level;
		this->field_DC = this->field_118;
		this->field_148 = 10;
		this->hurtTime = 10;
		this->field_14C = 0;
		level->playSound(this, this->getHurtSound(), this->getSoundVolume(), this->getVoicePitch());
		this->hurt(0, 0);
	} else if(event == 3) {
		v6 = this->level;
		v6->playSound(this, this->getDeathSound(), this->getSoundVolume(), this->getVoicePitch());
		this->health = 0;
		this->die(0);
	}
}
SynchedEntityData* Mob::getEntityData() const{
	return &this->synchedEntityData;
}
//there are two getEntityData functions for some reason
bool_t Mob::isMob() {
	return 1;
}

void Mob::setSize(float w, float h) {
	Entity::setSize(w, h);
}
void Mob::outOfWorld() {
	int32_t h = this->health;
	this->hurt(0, 4);
	if(this->health >= h) {
		this->actuallyHurt(4);
	}
}
void Mob::causeFallDamage(float a2) {
	int32_t v3; // r5
	Level* level; // r7
	int32_t v6; // r0
	Level* v7; // r5
	int32_t v8; // r9
	int32_t v9; // r8
	int32_t v10; // r0
	int32_t v11; // r0
	const Tile::SoundType* soundType; // r2

	v3 = (int32_t)ceil((float)(a2 - 3.0));
	if(v3 > 0) {
		level = this->level;
		level->playSound(this, v3 <= 4 ? "damage.fallsmall" : "damage.fallbig", 0.75, 1.0);
		this->hurt(0, v3);
		v6 = Mth::floor(this->posX);
		v7 = this->level;
		v8 = v6;
		v9 = Mth::floor((float)(this->posY - 0.2) - this->ridingHeight);
		v10 = Mth::floor(this->posZ);
		v11 = v7->getTile(v8, v9, v10);
		if(v11 > 0) {
			soundType = Tile::tiles[v11]->soundType;
			this->level->playSound(this, soundType->field_C, soundType->field_0 * 0.5, soundType->field_4 * 0.75);
		}
	}
}
void Mob::readAdditionalSaveData(CompoundTag* a2) {
	this->health = a2->getShort("Health");
	this->hurtTime = a2->getShort("HurtTime");
	this->deathTime = a2->getShort("DeathTime");
	this->attackTime = a2->getShort("AttackTime");
}
void Mob::addAdditonalSaveData(CompoundTag* a2) {
	a2->putShort("Health", this->health);
	a2->putShort("HurtTime", this->hurtTime);
	a2->putShort("DeathTime", this->deathTime);
	a2->putShort("AttackTime", this->attackTime);
}
void Mob::postInit() {
	this->health = this->getMaxHealth();
}
void Mob::knockback(Entity* a2, int32_t a3, float a4, float a5) {
	float motionY; // s9
	float v6; // s13
	float motionZ; // s10
	float v8; // s11

	motionY = this->motionY;
	// This weird thing is sqrt(a4*a4 + a5*a5)/(a4*a4 + a5*a5)
	/*v6 = COERCE_FLOAT(0x5F3759DF - (COERCE_INT((float)(a5 * a5) + (float)(a4 * a4)) >> 1))
		 * (float)(1.5
				   - (float)((float)((float)((float)((float)(a5 * a5) + (float)(a4 * a4)) * 0.5)
									 * COERCE_FLOAT(0x5F3759DF - (COERCE_INT((float)(a5 * a5) + (float)(a4 * a4)) >> 1)))
							 * COERCE_FLOAT(0x5F3759DF - (COERCE_INT((float)(a5 * a5) + (float)(a4 * a4)) >> 1))));*/
	v6 = sqrt(a4 * a4 + a5 * a5) / (a4 * a4 + a5 * a5);
	motionZ = this->motionZ;
	this->motionX = (float)(this->motionX * 0.5) - (float)((float)(a4 * v6) * 0.4);
	v8 = (float)(motionY * 0.5) + 0.4;
	this->motionY = v8;
	this->motionZ = (float)(motionZ * 0.5) - (float)((float)(a5 * v6) * 0.4);
	if(v8 > 0.4) {
		this->motionY = 0.4;
	}
}
void Mob::die(Entity* a2) {
	int32_t v3; // r2

	v3 = this->field_B88;
	if(v3 > 0) {
		if(a2) {
			a2->awardKillScore(this, v3);
		}
	}
	if(!this->level->isClientMaybe) {
		if(!this->isBaby()) {
			this->dropDeathLoot();
		}
		this->level->broadcastEntityEvent(this, 3);
	}
}
bool_t Mob::canSee(Entity* a2) {
	HitResult a1 = this->level->clip(Vec3(this->posX, this->posY + this->getHeadHeight(), this->posZ), Vec3(a2->posX, a2->posY + a2->getHeadHeight(), a2->posZ), 0, 0);
	return a1.hitType == 2;
}
bool_t Mob::onLadder() {
	int32_t v2; // r7
	int32_t v3; // r6
	int32_t v4; // r8

	v2 = Mth::floor(this->posX);
	v3 = Mth::floor(this->boundingBox.minY);
	v4 = Mth::floor(this->posZ);
	return this->level->getTile(v2, v3, v4) == Tile::ladder->blockID || this->level->getTile(v2, v3 + 1, v4) == Tile::ladder->blockID;
}
void Mob::spawnAnim() {
}
std::string* Mob::getTexture() {
	return &this->skin;
}
bool_t Mob::isSleeping() {
	return 0;
}
bool_t Mob::isWaterMob() {
	return 0;
}
void Mob::setSneaking(bool_t a2) {
	this->setSharedFlag(1, a2);
}
float Mob::getVoicePitch() {
	Random* p_random; // r4
	float f; // s17
	float v3; // s17
	float v4; // s15
	float v5; // s17

	p_random = &this->random;
	if(this->isBaby()) {
		f = p_random->nextFloat();
		v3 = f - p_random->nextFloat();
		v4 = 1.5;
	} else {
		v5 = p_random->nextFloat();
		v3 = v5 - p_random->nextFloat();
		v4 = 1.0;
	}
	return v4 + (float)(v3 * 0.2);
}
void Mob::playAmbientSound() {
	const char_t* v2; // r1

	v2 = this->getAmbientSound();
	if(v2) {
		this->level->playSound(this, v2, this->getSoundVolume(), this->getVoicePitch());
	}
}
int32_t Mob::getAmbientSoundInterval() {
	return 160;
}
TextureUVCoordinateSet* Mob::getItemInHandIcon(const ItemInstance* a2, int32_t a3) {
	int32_t v4 = a2->itemClass->getAnimationFrameFor(this);
	return a2->getIcon(v4, 0);
}
void Mob::superTick() {
	Entity::tick();
}
void Mob::heal(int32_t a2) {
	int32_t health; // r3
	int32_t newHealth; // r1

	health = this->health;
	if(health > 0) {
		newHealth = health + a2;
		if(newHealth > 20) {
			this->health = 20;
		} else {
			this->health = newHealth;
		}
		this->field_DC = this->field_118 / 2;
	}
}
int32_t Mob::getMaxHealth() {
	return 10;
}
void Mob::actuallyHurt(int32_t a2) {
	if(!this->hasArmorMaybe) {
		a2 = this->getDamageAfterArmorAbsorb(a2);
	}
	this->health -= a2;
}
int32_t Mob::getArmorValue() {
	return 0;
}
HitResult Mob::pick(float a3, float a4, bool_t a5) {
	Vec3 start = this->getPos(a4);
	Vec3 v11 = this->getViewVector(a4);
	Vec3 v12(a3 * v11.x, a3 * v11.y, a3 * v11.z);
	Vec3 v13(start.x + v12.x, start.y + v12.y, start.z + v12.z);
	return this->level->clip(start, v13, a5, 0);
}
void Mob::travel(float strafe, float forward) {
	bool_t isInWater; // r0
	float posY; // s17
	float motionX; // s13
	float v10; // s15
	float v11; // s16
	float motionZ; // s14
	float v14; // s13
	float v15; // s14
	int32_t v16; // r0
	Level* level; // r8
	int32_t v18; // r10
	int32_t v19; // r9
	int32_t v20; // r0
	int32_t v21; // r0
	float friction; // s16
	float speed; // s17
	float modifier; // r0
	float jumpMovementFactor; // s16
	int32_t v26; // r0
	Level* v27; // r6
	int32_t v28; // r9
	int32_t v29; // r8
	int32_t v30; // r0
	int32_t v31; // r0
	float v32; // s16
	float v34; // s16

	isInWater = this->isInWater();
	if(isInWater) {
		posY = this->posY;
		this->moveRelative(strafe, forward, 0.02);
		this->move(this->motionX, this->motionY, this->motionZ);
		motionX = this->motionX;
		v10 = 0.8;
		goto LABEL_5;
	}
	if(this->isInLava()) {
		posY = this->posY;
		this->moveRelative(strafe, forward, 0.02);
		this->move(this->motionX, this->motionY, this->motionZ);
		v10 = 0.5;
		motionX = this->motionX;
LABEL_5:
		v11 = (float)(this->motionY * v10) - 0.02;
		motionZ = this->motionZ;
		v14 = motionX * v10;
		this->motionY = v11;
		v15 = motionZ * v10;
		this->motionX = v14;
		this->motionZ = v15;
		if(this->isCollidedHorizontally) {
			if(this->isFree(v14, (float)((float)(v11 + 0.6) - this->posY) + posY, v15)) {
				this->motionY = 0.3;
			}
		}
		return;
	}
	if(this->onGround) {
		v16 = Mth::floor(this->posX);
		level = this->level;
		v18 = v16;
		v19 = Mth::floor(this->boundingBox.minY - 0.5);
		v20 = Mth::floor(this->posZ);
		v21 = level->getTile(v18, v19, v20);
		if(v21 <= 0) {
			friction = 0.546;
		} else {
			friction = Tile::tiles[v21]->slipperiness * 0.91;
		}
	} else {
		friction = 0.91;
	}
	speed = this->getSpeed();
	modifier = this->getWalkingSpeedModifier();

	if(this->onGround) {
		jumpMovementFactor = (float)(speed * modifier) * (float)(0.16277 / (float)((float)(friction * friction) * friction));
	} else {
		jumpMovementFactor = this->jumpMovementFactor;
	}
	this->moveRelative(strafe, forward, jumpMovementFactor);
	if(this->onGround) {
		v26 = Mth::floor(this->posX);
		v27 = this->level;
		v28 = v26;
		v29 = Mth::floor(this->boundingBox.minY - 0.5);
		v30 = Mth::floor(this->posZ);
		v31 = v27->getTile(v28, v29, v30);
		if(v31 <= 0) {
			v32 = 0.546;
		} else {
			v32 = Tile::tiles[v31]->slipperiness * 0.91;
		}
	} else {
		v32 = 0.91;
	}
	if(this->onLadder()) {
		this->fallDistance = 0.0;
		if(this->motionY < -0.15) {
			this->motionY = -0.15;
		}
		if(this->isSneaking()) {
			if(this->motionY < 0.0) {
				this->motionY = 0.0;
			}
		}
	}
	this->move(this->motionX, this->motionY, this->motionZ);
	if(this->isCollidedHorizontally && this->onLadder()) {
		this->motionY = 0.2;
	}
	this->motionY = (float)(this->motionY - 0.08) * 0.98;
	v34 = v32 * this->field_B7C;
	this->motionX = this->motionX * v34;
	this->motionZ = this->motionZ * v34;
}
void Mob::updateWalkAnim() {
	float v2; // s16
	float posZ; // s14
	float v4; // s13
	float prevZ; // s15
	float v6; // s19
	float v7; // s18
	float v8; // s14
	float v9; // s15
	float v10; // s15

	if(this->isOnFire()) {
		v2 = 1.5;
	} else {
		v2 = 1.5;
		if(!this->hurtTime) {
			v2 = 1.0;
		}
	}
	if(!this->onGround && this->motionY > 0.0) {
		v2 = v2 * 0.35;
	}
	posZ = this->posZ;
	v4 = this->posX - this->prevX;
	prevZ = this->prevZ;
	v6 = this->field_124;
	v7 = this->field_128;
	this->field_168 = this->field_16C;
	v8 = sqrt((float)((float)((float)(posZ - prevZ) * (float)(posZ - prevZ)) + (float)(v4 * v4)));
	v9 = v8 * 4.0;
	if((float)(v8 * 4.0) == 0.0) {
		v9 = fabsf(v6 - v7) * 0.15;
		if(v9 > 0.5) {
			v9 = 0.5;
		}
	}
	if(v9 > 1.0) {
		v9 = 1.0;
	}
	v10 = this->field_16C + (float)((float)((float)(v9 * v2) - this->field_16C) * 0.4);
	this->field_16C = v10;
	this->field_170 = this->field_170 + v10;
}
void Mob::aiStep() {
	float* p_moveForward; // r5
	float* v3; // r6
	int32_t usenewai; // r0
	int32_t v7; // r7
	int32_t v8; // r0
	float jumpMovementFactor; // r8

	p_moveForward = &this->moveForward;
	v3 = &this->field_B64;
	if(this->isImmobile()) {
		this->isJumping = 0;
		this->moveStrafe = 0.0;
		*p_moveForward = 0.0;
		*v3 = 0.0;
	} else if(!this->interpolateOnly()) {
		usenewai = this->useNewAi();
		if(usenewai) {
			this->newServerAiStep();
		} else {
			if(this->useNewAi()) {
				this->setSpeed(this->getBaseSpeed());
			}
			this->updateAi();
			this->headYaw = this->yaw;
		}
	}
	v7 = this->isInWater();
	v8 = this->isInLava();
	if(this->isJumping) {
		if(v7 || v8) {
			this->motionY = this->motionY + 0.04;
		} else if(this->onGround) {
			this->jumpFromGround();
		}
	}
	this->moveStrafe = this->moveStrafe * 0.98;
	*p_moveForward = *p_moveForward * 0.98;
	*v3 = *v3 * 0.9;
	jumpMovementFactor = this->jumpMovementFactor;
	this->jumpMovementFactor = jumpMovementFactor * this->getWalkingSpeedModifier();
	this->travel(this->moveStrafe, *p_moveForward);
	this->jumpMovementFactor = jumpMovementFactor;
	this->pushEntities();
}
void Mob::lookAt(Entity* a2, float a3, float a4) {
	float v4; // s16
	float posY; // s27
	float v9; // s17
	float v10; // s25
	float v11; // s26
	float v12; // s20
	float v13; // s14
	double v14; // r0
	float pitch; // s20
	float v16; // s16
	float v17; // r0
	float yaw; // s16
	float v19; // s15
	float v20; // s23
	float v21; // s15
	float v22; // s22

	v4 = a2->posX - this->posX;
	posY = this->posY;
	v9 = a2->posZ - this->posZ;
	v10 = (float)(a2->boundingBox.minY + a2->boundingBox.maxY) * 0.5;
	v11 = this->getHeadHeight();
	v12 = sqrt((float)((float)(v9 * v9) + (float)(v4 * v4)));
	v13 = atan2(v9, v4) * 180.0 / 3.1416;
	v14 = atan2((float)(v10 - (float)(posY + v11)), v12);
	pitch = this->pitch;
	v16 = v14 * 180.0 / 3.1416;
	v17 = Mth::wrapDegrees(v16 - pitch);
	yaw = this->yaw;
	v19 = v17;
	if(v17 > a4) {
		v19 = a4;
	}
	v20 = -a4;
	if(v19 >= v20) {
		v20 = v19;
	}
	this->pitch = -(float)(pitch + v20);
	v21 = Mth::wrapDegrees((float)(v13 - 90.0) - yaw);
	if(v21 > a3) {
		v21 = a3;
	}
	v22 = -a3;
	if(v21 >= v22) {
		v22 = v21;
	}
	this->yaw = yaw + v22;
}
bool_t Mob::isLookingAtAnEntity() {
	return this->maybeEntityWhichIsBeingLookedByThisEntity != 0;
}
void Mob::beforeRemove() {
}
bool_t Mob::canSpawn() {
	if(!this->level->isUnobstructed(this->boundingBox)) return 0;
	std::vector<AABB>* cubes = this->level->getCubes(this, this->boundingBox, 0);
	return cubes->size() == 0 && !this->level->containsAnyLiquid(this->boundingBox);
}
void Mob::finalizeMobSpawn() {
}
float Mob::getAttackAnim(float a2) {
	float v2 = this->field_134;
	float v3 = this->field_138 - v2;
	if(v3 < 0) v3 += 1;
	return v2 + (v3 * a2);
}
Vec3 Mob::getPos(float a3) {
	float posY; // r2
	float posX; // r1
	float posZ; // r3
	float prevZ; // s14
	float v8; // s11
	float v9; // s13
	float v10; // s14

	if(a3 == 1.0) {
		posY = this->posY;
		posX = this->posX;
		posZ = this->posZ;
	} else {
		prevZ = this->prevZ;
		v8 = this->posZ - prevZ;
		v9 = this->prevY + (float)((float)(this->posY - this->prevY) * a3);
		posX = this->prevX + (float)((float)(this->posX - this->prevX) * a3);
		v10 = prevZ + (float)(v8 * a3);
		posY = v9;
		posZ = v10;
	}
	return Vec3(posX, posY, posZ);
}
Vec3 Mob::getLookAngle() const {
	return this->getViewVector(1);
}
Vec3 Mob::getViewVector(float a3) const {
	float v5; // s16
	float v6; // s18
	float v7; // r0
	float v8; // s17
	float v9; // s19
	float v10; // s16
	float v11; // r0
	float v12; // s19
	float v13; // s16
	float v14; // r1
	float v15; // s16
	float v16; // s17
	float v17; // s19
	float v18; // s20
	float v19; // s16

	if(a3 == 1.0) {
		v5 = (float) - (float)(this->yaw * 0.017453) - 3.1416;
		v6 = Mth::cos(v5);
		v7 = Mth::sin(v5);
		v8 = -(float)(this->pitch * 0.017453);
		v9 = v7;
		v10 = -Mth::cos(v8);
		v11 = Mth::sin(v8);
		v12 = v9 * v10;
		v13 = v6 * v10;
		v14 = v12;
	} else {
		v15 = (float) - (float)((float)(this->prevYaw + (float)((float)(this->yaw - this->prevYaw) * a3)) * 0.017453) - 3.1416;
		v16 = -(float)((float)(this->prevPitch + (float)((float)(this->pitch - this->prevPitch) * a3)) * 0.017453);
		v17 = Mth::cos(v15);
		v18 = Mth::sin(v15);
		v19 = -Mth::cos(v16);
		v11 = Mth::sin(v16);
		v14 = v18 * v19;
		v13 = v17 * v19;
	}
	return Vec3(v14, v11, v13);
}
int32_t Mob::getMaxSpawnClusterSize() {
	return 4;
}
bool_t Mob::isBaby() {
	return 0;
}
ItemInstance* Mob::getCarriedItem() {
	return 0;
}
int32_t Mob::getUseItemDuration() {
	return 0;
}
void Mob::swing() {
	if(!this->field_B68 || this->field_B6C > 2 || this->field_B6C < 0) {
		this->field_B6C = -1;
		this->field_B68 = 1;
	}
}
void Mob::ate() {
}
float Mob::getMaxHeadXRot() {
	return 40;
}
Mob* Mob::getLastHurtByMob() {
	return this->updateMobId(&this->field_C5C);
}
void Mob::setLastHurtByMob(Mob* a2) {
	if(a2) {
		this->field_C5C = a2->entityId;
		this->field_C60 = 60;
	} else {
		this->field_C5C = 0;
		this->field_C60 = 0;
	}
}
void Mob::getLastHurtMob() {
	this->updateMobId(&this->field_C58);
}
void Mob::setLastHurtMob(Entity* a2) {
	if(a2->isMob()) {
		this->field_C58 = a2->entityId;
	}
}
Entity* Mob::getTarget() {
	if(this->targetEID) {
		return this->level->getMob(this->targetEID);
	}
	return 0;
}
void Mob::setTarget(Mob* a2) {
	if(a2) {
		this->targetEID = a2->entityId;
	} else {
		this->targetEID = 0;
	}
}
bool_t Mob::doHurtTarget(Entity* a2) {
	this->setLastHurtMob(a2);
	return 0;
}
bool_t Mob::canBeControlledByRider() {
	return 0;
}
void Mob::teleportTo(float x, float y, float z) {
	this->moveTo(x, y, z, this->yaw, this->pitch);
}
bool_t Mob::removeWhenFarAway() {
	return 1;
}
int32_t Mob::getDeathLoot() {
	return 0;
}
void Mob::dropDeathLoot() {
	int32_t v2 = this->getDeathLoot();
	if(v2 > 0) {
		int32_t v3 = 0;
		int32_t v4 = this->random.genrand_int32() % 3;
		while(v3 < v4) {
			++v3;
			this->spawnAtLocation(v2, 1);
		}
	}
}
bool_t Mob::isImmobile() {
	return this->health <= 0;
}
void Mob::jumpFromGround() {
	this->motionY = 0.42;
}
void Mob::updateAi() {
	Random* p_random; // r5
	Player* v4; // r0
	int32_t maybeEntityWhichIsBeingLookedByThisEntity; // r1
	Entity* entity; // r0
	Entity* v7; // r6
	int32_t v10; // r3
	int32_t entityId; // r3

	p_random = &this->random;
	++this->noActionTime;
	this->checkDespawn(this->level->getNearestPlayer(this, -1.0));
	this->moveStrafe = 0.0;
	this->moveForward = 0.0;
	if(p_random->nextFloat() < 0.02) {
		v4 = this->level->getNearestPlayer(this, 8.0);
		if(v4) {
			this->maybeEntityWhichIsBeingLookedByThisEntity = v4->entityId;
			this->field_160 = p_random->genrand_int32() % 0x14 + 10;
		} else {
			this->field_B64 = (float)(p_random->nextFloat() - 0.5) * 20.0;
		}
	}
	maybeEntityWhichIsBeingLookedByThisEntity = this->maybeEntityWhichIsBeingLookedByThisEntity;
	if(maybeEntityWhichIsBeingLookedByThisEntity) {
		entity = this->level->getEntity(maybeEntityWhichIsBeingLookedByThisEntity);
		this->maybeEntityWhichIsBeingLookedByThisEntity = 0;
		v7 = entity;
		if(entity) {
			this->lookAt(v7, 10.0, this->getMaxHeadXRot());
			v10 = this->field_160;
			this->field_160 = v10 - 1;
			if(v10 <= 0 || v7->isDead || v7->distanceToSqr(this) > 64.0) {
				entityId = 0;
			} else {
				entityId = v7->entityId;
			}
			this->maybeEntityWhichIsBeingLookedByThisEntity = entityId;
		}
	} else {
		if(p_random->nextFloat() < 0.05) {
			this->field_B64 = (float)(p_random->nextFloat() - 0.5) * 20.0;
		}
		this->yaw = this->yaw + this->field_B64;
		this->pitch = this->field_B74;
	}
	if(this->isInWater() || this->isInLava()) {
		this->isJumping = p_random->nextFloat() < 0.8;
	}
}
void Mob::newServerAiStep() {
	++this->noActionTime;
	Mob::checkDespawn(this);
	this->isJumping = 0;
	this->sensing->_canSee.clear();
	this->sensing->_cannotSee.clear();
	this->goalSelector2.tick();
	this->goalSelector.tick();
	this->navigation->tick();
	this->serverAiMobStep();
	this->moveControl->tick();
	this->lookControl->tick();
	this->jumpControl->tick();
}
void Mob::serverAiMobStep() {
}
float Mob::getSoundVolume() {
	return 1.0;
}
const char_t* Mob::getAmbientSound() {
	return 0;
}
std::string Mob::getHurtSound() {
	return "random.hurt";
}
std::string Mob::getDeathSound() {
	return "random.hurt";
}
float Mob::getWalkingSpeedModifier() {
	return 0.7;
}
int32_t Mob::getDamageAfterArmorAbsorb(int32_t a2) {
	int32_t v4; // r5

	v4 = this->field_BC4 + (25 - this->getArmorValue()) * a2;
	this->hurtArmor(a2);
	this->field_BC4 = v4 % 25;
	return v4 / 25;
}
void Mob::hurtArmor(int32_t) {
}
bool_t Mob::useNewAi() {
	return 0l;
}
