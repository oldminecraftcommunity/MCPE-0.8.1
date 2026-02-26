#include <entity/Zombie.hpp>
#include <entity/ai/goals/BreakDoorGoal.hpp>
#include <entity/ai/goals/FloatGoal.hpp>
#include <entity/ai/goals/HurtByTargetGoal.hpp>
#include <entity/ai/goals/LookAtPlayerGoal.hpp>
#include <entity/ai/goals/MeleeAttackGoal.hpp>
#include <entity/ai/goals/NearestAttackableTargetGoal.hpp>
#include <entity/ai/goals/RandomLookAroundGoal.hpp>
#include <entity/ai/goals/RandomStrollGoal.hpp>
#include <entity/path/PathNavigation.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>

Zombie::Zombie(Level* a2)
	: Monster(a2) {
	this->field_C84 = 0;
	this->usingNewAI = 0;
	this->entityRenderId = ZOMBIE;
	this->skin = "mob/zombie.png";
	this->attackDamage = 4;
	this->getNavigation()->setCanOpenDoors(1);
	this->goalSelector.addGoal(0, new FloatGoal(this), 1);
	this->goalSelector.addGoal(1, new BreakDoorGoal(this), 1);
	this->goalSelector.addGoal(2, new MeleeAttackGoal(this, 1.0, 0), 1);
	this->goalSelector.addGoal(6, new RandomStrollGoal(this, 1.0), 1);
	this->goalSelector.addGoal(7, new LookAtPlayerGoal(this, 8.0), 1);
	this->goalSelector.addGoal(7, new RandomLookAroundGoal(this), 1);
	this->goalSelector2.addGoal(1, new HurtByTargetGoal(this, 16), 1);
	this->goalSelector2.addGoal(2, new NearestAttackableTargetGoal(this, 16), 1);
}
void Zombie::setUseNewAi(bool_t a2) {
	this->usingNewAI = a2;
}

Zombie::~Zombie() {
}
int32_t Zombie::getEntityTypeId() const {
	return 32;
}
void Zombie::die(Entity* a2) {
	Mob::die(a2);
	if(!this->level->isClientMaybe) {
		if(!(this->random.genrand_int32() << 30)) {
			this->spawnAtLocation(Item::feather->itemID, 1);
		}
		if(!(this->random.genrand_int32() % 0x28)) {
			this->spawnAtLocation(Item::carrot->itemID, 1);
		}
		if(!(this->random.genrand_int32() % 0x28)) {
			this->spawnAtLocation(Item::potato->itemID, 1);
		}
	}
}
float Zombie::getBaseSpeed() {
	return 0.23;
}
int32_t Zombie::getMaxHealth() {
	return 12;
}
int32_t Zombie::getArmorValue() {
	int32_t v; // r0

	v = Mob::getArmorValue() + 2;
	if(v >= 20) {
		return 20;
	}
	return v;
}
void Zombie::aiStep() {
	int32_t v2;	 // r3
	float posX;	 // s15
	int32_t v4;	 // r1
	bool_t v5;	 // fnf
	float posY;	 // s15
	int32_t v7;	 // r2
	bool_t v8;	 // fnf
	float posZ;	 // s15
	int32_t v10; // r3

	v2 = this->field_C84 + 1;
	this->field_C84 = v2;
	if((v2 & 1) != 0 && this->level->isDay() && !this->level->isClientMaybe && !this->isBaby() && this->getBrightness(1.0) > 0.5 && !this->isOnFire()) {
		posX = this->posX;
		v4 = (int32_t)posX;
		v5 = posX < (float)(int32_t)posX;
		posY = this->posY;
		v7 = (int32_t)posY;
		if(v5) {
			--v4;
		}
		v8 = posY < (float)(int32_t)posY;
		posZ = this->posZ;
		v10 = (int32_t)posZ;
		if(v8) {
			--v7;
		}
		if(posZ < (float)(int32_t)posZ) {
			--v10;
		}
		if(this->level->canSeeSky(v4, v7, v10)) {
			this->setOnFire(8);
		}
	}
	Monster::aiStep();
}
int32_t Zombie::getDeathLoot() {
	return 0;
}
const char_t* Zombie::getAmbientSound() {
	return "mob.zombie";
}
std::string Zombie::getHurtSound() {
	return "mob.zombiehurt";
}
std::string Zombie::getDeathSound() {
	return "mob.zombiedeath";
}
bool_t Zombie::useNewAi() {
	return this->usingNewAI;
}
int32_t Zombie::getAttackDamage(Entity* a2) {
	ItemInstance* v3;	  // r0
	int32_t attackDamage; // r4

	v3 = this->getCarriedItem();
	attackDamage = this->attackDamage;
	if(v3) {
		attackDamage += v3->getAttackDamage(this);
	}
	return attackDamage;
}
