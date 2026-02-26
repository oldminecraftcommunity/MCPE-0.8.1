#include <entity/Chicken.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <entity/ai/goals/FloatGoal.hpp>
#include <entity/ai/goals/PanicGoal.hpp>
#include <entity/ai/goals/BreedGoal.hpp>
#include <entity/ai/goals/TemptGoal.hpp>
#include <entity/ai/goals/FollowParentGoal.hpp>
#include <entity/ai/goals/RandomStrollGoal.hpp>
#include <entity/ai/goals/LookAtPlayerGoal.hpp>
#include <entity/ai/goals/RandomLookAroundGoal.hpp>


Chicken::Chicken(Level* a2)
	: Animal(a2) {
	this->field_C88 = 0;
	this->field_C8C = 0.0;
	this->field_C90 = 0.0;
	this->field_C94 = 0.0;
	this->field_C98 = 0.0;
	this->field_C9C = 1.0;
	this->nextEggCounter = 0;
	this->entityRenderId = CHICKEN;
	this->skin = "mob/chicken.png";
	this->nextEggCounter = this->random.genrand_int32() % 6000 + 6000;
	this->setSize(0.3, 0.7);
	this->goalSelector.addGoal(0, new FloatGoal(this), 1);
	this->goalSelector.addGoal(1, new PanicGoal(this, 1.5), 1);
	this->goalSelector.addGoal(2, new BreedGoal(this, 1.0), 1);
	this->goalSelector.addGoal(3, new TemptGoal(this, 1.0, {Item::seeds_wheat->itemID}, 0), 1);
	this->goalSelector.addGoal(4, new FollowParentGoal(this, 1.1), 1);
	this->goalSelector.addGoal(5, new RandomStrollGoal(this, 1.0), 1);
	this->goalSelector.addGoal(6, new LookAtPlayerGoal(this, 6.0), 1);
	this->goalSelector.addGoal(7, new RandomLookAroundGoal(this), 1);
}

Chicken::~Chicken() {
}
int32_t Chicken::getEntityTypeId() const {
	return 10;
}
void Chicken::causeFallDamage(float) {
}
void Chicken::readAdditionalSaveData(CompoundTag* a2) {
	Animal::readAdditionalSaveData(a2);
}
void Chicken::addAdditonalSaveData(CompoundTag* a2) {
	Animal::addAdditonalSaveData(a2);
}
float Chicken::getBaseSpeed() {
	return 0.25;
}
int32_t Chicken::getMaxHealth() {
	return 4;
}
void Chicken::aiStep() {
	float v2;		 // s14
	float* v3;		 // r3
	float v4;		 // s13
	bool_t onGround; // r2
	float v6;		 // s15
	float v7;		 // s15
	float v9;		 // s15
	float motionY;	 // s13
	Level* level;	 // r7
	int32_t v12;	 // r3

	Animal::aiStep();
	v2 = this->field_C8C;
	this->field_C98 = v2;
	v3 = &this->field_C90;
	v4 = this->field_C90;
	this->field_C94 = v4;
	onGround = this->onGround;
	v6 = -0.3;
	if(!this->onGround) {
		v6 = 1.2;
	}
	v7 = v4 + v6;
	if(v7 < 0.0) {
		v7 = 0.0;
	}
	*v3 = v7;
	if(v7 > 1.0) {
		*v3 = 1.0;
	}
	if(!onGround && this->field_C9C < 1.0) {
		this->field_C9C = 1.0;
	}
	v9 = this->field_C9C * 0.9;
	this->field_C9C = v9;
	if(!onGround) {
		motionY = this->motionY;
		if(motionY < 0.0) {
			this->motionY = motionY * 0.6;
		}
	}
	this->field_C8C = v2 + (float)(v9 + v9);
	if(!this->isBaby()) {
		level = this->level;
		if(!level->isClientMaybe) {
			v12 = this->nextEggCounter - 1;
			this->nextEggCounter = v12;
			if(v12 <= 0) {
				level->playSound(this, "mob.chickenplop", 1.0, (float)((float)(this->random.nextFloat() - this->random.nextFloat()) * 0.2) + 1.0);

				this->spawnAtLocation(Item::egg->itemID, 1);
				this->nextEggCounter = this->random.genrand_int32() % 0x1770 + 6000;
			}
		}
	}
}
void Chicken::dropDeathLoot() {
	int32_t v2; // r6
	int32_t v3; // r7

	v2 = 0;
	v3 = this->random.genrand_int32() % 3;
	while(1) {
		if(v2 >= v3) {
			break;
		}
		++v2;
		this->spawnAtLocation(Item::feather->itemID, 1);
	}
	if(this->isOnFire()) {
		this->spawnAtLocation(Item::chicken_cooked->itemID, 1);
	} else {
		this->spawnAtLocation(Item::chicken_raw->itemID, 1);
	}
}
const char_t* Chicken::getAmbientSound() {
	return "mob.chicken";
}
std::string Chicken::getHurtSound() {
	return "mob.chickenhurt";
}
std::string Chicken::getDeathSound() {
	return "mob.chickenhurt";
}
bool_t Chicken::useNewAi() {
	return 1;
}
bool_t Chicken::isFood(const ItemInstance* a2) {
	if(a2->itemClass) {
		return a2->itemClass->isSeed();
	}
	return 0;
}
Mob* Chicken::getBreedOffspring(Animal*) {
	return new Chicken(this->level);
}
