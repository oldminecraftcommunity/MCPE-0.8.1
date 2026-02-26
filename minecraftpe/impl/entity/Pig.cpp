#include <entity/Pig.hpp>
#include <entity/Player.hpp>
#include <entity/ai/goals/BreedGoal.hpp>
#include <entity/ai/goals/FloatGoal.hpp>
#include <entity/ai/goals/FollowParentGoal.hpp>
#include <entity/ai/goals/LookAtPlayerGoal.hpp>
#include <entity/ai/goals/PanicGoal.hpp>
#include <entity/ai/goals/RandomLookAroundGoal.hpp>
#include <entity/ai/goals/RandomStrollGoal.hpp>
#include <entity/ai/goals/TemptGoal.hpp>
#include <entity/path/PathNavigation.hpp>
#include <item/Item.hpp>

Pig::Pig(Level* a2)
	: Animal(a2) {
	this->entityRenderId = PIG;
	this->skin = "mob/pig.png";
	this->setSize(0.9, 0.9);
	this->synchedEntityData.define<int8_t>(16, 0); //signed char
	this->getNavigation()->setAvoidWater(1);
	this->goalSelector.addGoal(0, new FloatGoal(this), 1);
	this->goalSelector.addGoal(1, new PanicGoal(this, 1.5), 1);
	this->goalSelector.addGoal(2, new BreedGoal(this, 1.0), 1);
	this->goalSelector.addGoal(3, new TemptGoal(this, 1.0, {Item::potato->itemID, Item::carrot->itemID, Item::beetroot->itemID}, 0), 1);
	this->goalSelector.addGoal(4, new FollowParentGoal(this, 1.1), 1);
	this->goalSelector.addGoal(5, new RandomStrollGoal(this, 1.0), 1);
	this->goalSelector.addGoal(6, new LookAtPlayerGoal(this, 6.0), 1);
	this->goalSelector.addGoal(7, new RandomLookAroundGoal(this), 1);
}
bool_t Pig::hasSaddle() {
	return this->synchedEntityData.getByte(16) & 1;
}
void Pig::setSaddle(bool_t a2) {
	this->synchedEntityData.set<int8_t>(16, a2);
}

Pig::~Pig() {
}
bool_t Pig::interactWithPlayer(Player* a2) {
	return Animal::interactWithPlayer(a2);
}
int32_t Pig::getEntityTypeId() const {
	return 12;
}
float Pig::getBaseSpeed() {
	return 0.25;
}
int32_t Pig::getMaxHealth() {
	return 10;
}
bool_t Pig::canBeControlledByRider() {
	return this->rider && this->rider->isPlayer() && ((Player*)this->rider)->getCarriedItem();
}
int32_t Pig::getDeathLoot() {
	if(this->isOnFire()) {
		return Item::porkChop_cooked->itemID;
	}
	return Item::porkChop_raw->itemID;
}
const char_t* Pig::getAmbientSound() {
	return "mob.pig";
}
std::string Pig::getHurtSound() {
	return "mob.pig";
}
std::string Pig::getDeathSound() {
	return "mob.pigdeath";
}
bool_t Pig::useNewAi() {
	return 1;
}
bool_t Pig::isFood(const ItemInstance* a2) {
	int id; // r0

	id = a2->getId();
	return id == Item::potato->itemID || id == Item::carrot->itemID || id == Item::beetroot->itemID;
}
Mob* Pig::getBreedOffspring(Animal* a2) {
	return new Pig(this->level);
}
