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
	this->field_C8C = 0.0f;
	this->field_C90 = 0.0f;
	this->field_C94 = 0.0f;
	this->field_C98 = 0.0f;
	this->field_C9C = 1.0f;
	this->nextEggCounter = 0;
	this->entityRenderId = CHICKEN;
	this->skin = "mob/chicken.png";
	this->nextEggCounter = this->random.genrand_int32() % 6000 + 6000;
	this->setSize(0.3f, 0.7f);
	this->goalSelector.addGoal(0, new FloatGoal(this), 1);
	this->goalSelector.addGoal(1, new PanicGoal(this, 1.5f), 1);
	this->goalSelector.addGoal(2, new BreedGoal(this, 1.0f), 1);
	this->goalSelector.addGoal(3, new TemptGoal(this, 1.0f, {Item::seeds_wheat->itemID}, 0), 1);
	this->goalSelector.addGoal(4, new FollowParentGoal(this, 1.1f), 1);
	this->goalSelector.addGoal(5, new RandomStrollGoal(this, 1.0f), 1);
	this->goalSelector.addGoal(6, new LookAtPlayerGoal(this, 6.0f), 1);
	this->goalSelector.addGoal(7, new RandomLookAroundGoal(this), 1);
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
int32_t Chicken::getMaxHealth() {
	return 4;
}
void Chicken::aiStep() {
	Animal::aiStep();
	float v2 = this->field_C8C;
	this->field_C98 = v2;
	float v4 = this->field_C90;
	this->field_C94 = v4;
	bool onGround = this->onGround;
	float v6 = -0.3f;
	if(!this->onGround) {
		v6 = 1.2f;
	}
	float v7 = v4 + v6;
	if(v7 < 0.0f) {
		v7 = 0.0f;
	}
	this->field_C90 = v7;
	if(v7 > 1.0f) {
		this->field_C90 = 1.0f;
	}
	if(!onGround && this->field_C9C < 1.0f) {
		this->field_C9C = 1.0f;
	}
	float v9 = this->field_C9C * 0.9f;
	this->field_C9C = v9;
	if(!onGround) {
		if(this->motionY < 0.0f) {
			this->motionY = this->motionY * 0.6f;
		}
	}
	this->field_C8C = v2 + (float)(v9 + v9);

	if(!this->isBaby()) {
		if(!this->level->isClient) {
			this->nextEggCounter -= 1;
			if(this->nextEggCounter <= 0) {
				this->level->playSound(this, "mob.chickenplop", 1.0f, (this->random.nextFloat() - this->random.nextFloat()) * 0.2f + 1.0f);

				this->spawnAtLocation(Item::egg->itemID, 1);
				this->nextEggCounter = this->random.genrand_int32() % 6000 + 6000; //TODO maybe this is inlined Random::nextInt?
			}
		}
	}
}
void Chicken::dropDeathLoot() {
	for(int v2 = 0; v2 < this->random.genrand_int32() % 3; ++v2){
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
bool_t Chicken::isFood(const ItemInstance* a2) const{
	if(a2->itemClass) {
		return a2->itemClass->isSeed();
	}
	return 0;
}
Mob* Chicken::getBreedOffspring(Animal*) {
	return new Chicken(this->level);
}
