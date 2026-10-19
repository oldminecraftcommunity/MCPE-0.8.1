#include <entity/Skeleton.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <entity/Arrow.hpp>
#include <entity/ai/goals/FloatGoal.hpp>
#include <entity/ai/goals/RestrictSunGoal.hpp>
#include <entity/ai/goals/FleeSunGoal.hpp>
#include <entity/ai/goals/ArrowAttackGoal.hpp>
#include <entity/ai/goals/RandomStrollGoal.hpp>
#include <entity/ai/goals/LookAtPlayerGoal.hpp>
#include <entity/ai/goals/RandomLookAroundGoal.hpp>
#include <entity/ai/goals/HurtByTargetGoal.hpp>
#include <entity/ai/goals/NearestAttackableTargetGoal.hpp>
#include <math/Mth.hpp>

Skeleton::Skeleton(Level* a2)
	: Monster(a2)
	, heldItem(Item::bow, 1) {
	this->entityRenderId = SKELETON;
	this->skyCheckCounter = 0;
	this->skin = "mob/skeleton.png";
	this->goalSelector.addGoal(1, new FloatGoal(this), 1);
	this->goalSelector.addGoal(2, new RestrictSunGoal(this), 1);
	this->goalSelector.addGoal(3, new FleeSunGoal(this, 1.0), 1);
	this->goalSelector.addGoal(4, new ArrowAttackGoal(this, 1.0, 1, 60), 1);
	this->goalSelector.addGoal(5, new RandomStrollGoal(this, 1.0), 1);
	this->goalSelector.addGoal(6, new LookAtPlayerGoal(this, 8.0), 1);
	this->goalSelector.addGoal(6, new RandomLookAroundGoal(this), 1);
	this->goalSelector.addGoal(1, new HurtByTargetGoal(this, 16), 1);
	this->goalSelector.addGoal(2, new NearestAttackableTargetGoal(this, 16), 1);
}

int32_t Skeleton::getEntityTypeId() const {
	return 34;
}

int32_t Skeleton::getMaxHealth() {
	return 10;
}
void Skeleton::aiStep() {
	this->skyCheckCounter += 1;
	if((this->skyCheckCounter & 1) != 0 && this->level->isDay() && !this->level->isClient && this->getBrightness(1.0) > 0.5f && !this->isOnFire()) {
		if(this->level->canSeeSky(Mth::floor(this->posX), Mth::floor(this->posY), Mth::floor(this->posZ))) {
			this->setOnFire(8);
		}
	}
	Monster::aiStep();
}
ItemInstance* Skeleton::getCarriedItem() {
	return &this->heldItem;
}
int32_t Skeleton::getDeathLoot() {
	return Item::arrow->itemID;
}
void Skeleton::dropDeathLoot() {
	Random* p_random; // r7
	int32_t v3;		  // r6
	int32_t v4;		  // r8
	int32_t v5;		  // r6
	int32_t v6;		  // r7

	v3 = 0;
	v4 = this->random.genrand_int32() % 3;
	while(v3 < v4) {
		++v3;
		this->spawnAtLocation(Item::arrow->itemID, 1);
	}
	v5 = 0;
	v6 = this->random.genrand_int32() % 3;
	while(v5 < v6) {
		++v5;
		this->spawnAtLocation(Item::bone->itemID, 1);
	}
}
const char_t* Skeleton::getAmbientSound() {
	return "mob.skeleton";
}
std::string Skeleton::getHurtSound() {
	return "mob.skeletonhurt";
}
std::string Skeleton::getDeathSound() {
	return "mob.skeletonhurt";
}
bool_t Skeleton::useNewAi(){
return 0;
}
void Skeleton::checkHurtTarget(Entity* a2, float a3) {
	float v5;	  // s18
	float v6;	  // s19
	Arrow* v7;	  // r61
	float v9;	  // s21
	float v10;	  // r0
	Level* level; // r5
	float v12;	  // d8

	if(a3 < 10.0f) {
		v5 = a2->posX - this->posX;
		v6 = a2->posZ - this->posZ;
		if(!this->attackTime) {
			v7 = new Arrow(this->level, (Mob*)this, 1.0f);
			v9 = (float)((float)(a2->posY + a2->getHeadHeight()) - 0.7f) - v7->posY;
			v10 = sqrt((float)((float)(v6 * v6) + (float)(v5 * v5)));
			level = this->level;
			level->playSound(this, "random.bow", 1.0f, 1.0f / (float)((float)(this->random.nextFloat() * 0.4f) + 0.8f));

			this->level->addEntity(v7);
			v7->shoot(v5, v9 + (float)(v10 * 0.2), v6, 1.6f, 32.0f);
			this->attackTime = 60;
		}
		this->_shouldHoldGround = 1;
		this->yaw = Mth::rad2deg(atan2f(v6, v5)) - 90.0f;
	}
}
int32_t Skeleton::getUseDuration() {
	return this->attackTime;
}
