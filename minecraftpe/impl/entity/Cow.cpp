#include <entity/Cow.hpp>
#include <item/Item.hpp>
#include <inventory/Inventory.hpp>
#include <entity/Player.hpp>
#include <entity/path/PathNavigation.hpp>
#include <entity/ai/goals/FloatGoal.hpp>
#include <entity/ai/goals/PanicGoal.hpp>
#include <entity/ai/goals/BreedGoal.hpp>
#include <entity/ai/goals/TemptGoal.hpp>
#include <entity/ai/goals/FollowParentGoal.hpp>
#include <entity/ai/goals/RandomStrollGoal.hpp>
#include <entity/ai/goals/LookAtPlayerGoal.hpp>
#include <entity/ai/goals/RandomLookAroundGoal.hpp>

Cow::Cow(Level* a2)
	: Animal(a2) {
	this->milkedTicks = 0;
	this->entityRenderId = COW;
	this->skin = "mob/cow.png";
	this->setSize(0.9, 1.3);
	this->getNavigation()->setAvoidWater(1);
	this->goalSelector.addGoal(0, new FloatGoal(this), 1);
	this->goalSelector.addGoal(1, new PanicGoal(this, 1.5), 1);
	this->goalSelector.addGoal(2, new BreedGoal(this, 1.0), 1);
	this->goalSelector.addGoal(3, new TemptGoal(this, 1.0, {Item::wheat->itemID}, 0), 1);
	this->goalSelector.addGoal(4, new FollowParentGoal(this, 1.1), 1);
	this->goalSelector.addGoal(5, new RandomStrollGoal(this, 0.8), 1);
	this->goalSelector.addGoal(6, new LookAtPlayerGoal(this, 6.0), 1);
	this->goalSelector.addGoal(7, new RandomLookAroundGoal(this), 1);
}

Cow::~Cow() {
}
void Cow::tick() {
	++this->milkedTicks;
	Mob::tick();
}
bool_t Cow::interactWithPlayer(Player* a2) {
	ItemInstance* sel; // r0
	ItemInstance* v5;  // r4
	int v11;		   // r3

	sel = a2->inventory->getSelected();
	v5 = sel;
	if(this->milkedTicks <= 20 || !sel || Item::bucket != sel->itemClass || !Item::bucket || sel->getAuxValue() || a2->abilities.instabuild) {
		return Animal::interactWithPlayer(a2);
	}
	this->milkedTicks = a2->abilities.instabuild;
	ItemInstance v12(Item::bucket, 1, 1);
	v11 = v5->count - 1;
	v5->count = v11;
	if(v11) {
		a2->inventory->add(&v12);
	} else {
		*v5 = v12;
	}
	return 1;
}
int32_t Cow::getEntityTypeId() const {
	return 11;
}
void Cow::readAdditionalSaveData(CompoundTag* a2) {
	Animal::readAdditionalSaveData(a2);
}
void Cow::addAdditonalSaveData(CompoundTag* a2) {
	Animal::addAdditonalSaveData(a2);
}
float Cow::getBaseSpeed() {
	return 0.2;
}
int32_t Cow::getMaxHealth() {
	return 10;
}
int32_t Cow::getDeathLoot() {
	return Item::leather->itemID;
}
void Cow::dropDeathLoot() {
	int32_t v3; // r6
	int32_t v4; // r8
	int32_t v5; // r6
	int32_t v6; // r7

	v3 = 0;
	v4 = this->random.genrand_int32() % 3;
	while(v3 < v4) {
		++v3;
		this->spawnAtLocation(Item::leather->itemID, 1);
	}
	v5 = 0;
	v6 = this->random.genrand_int32() % 3;
	do {
		if(this->isOnFire()) {
			this->spawnAtLocation(Item::beef_cooked->itemID, 1);
		} else {
			this->spawnAtLocation(Item::beef_raw->itemID, 1);
		}
		++v5;

	} while(v6 >= v5);
}
float Cow::getSoundVolume() {
	return 0.4;
}
const char_t* Cow::getAmbientSound() {
	return "mob.cow";
}
std::string Cow::getHurtSound() {
	return "mob.cowhurt";
}
std::string Cow::getDeathSound() {
	return "mob.cowhurt";
}
bool_t Cow::useNewAi() {
	return 1;
}
Mob* Cow::getBreedOffspring(Animal*) {
	return new Cow(this->level);
}
