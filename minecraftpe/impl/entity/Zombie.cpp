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
#include <math/Mth.hpp>

Zombie::Zombie(Level* a2)
	: Monster(a2) {
	this->skyCheckCounter = 0;
	this->usingNewAI = 0;
	this->entityRenderId = ZOMBIE;
	this->skin = "mob/zombie.png";
	this->attackDamage = 4;
	this->getNavigation()->setCanOpenDoors(1);
	this->goalSelector.addGoal(0, new FloatGoal(this), 1);
	this->goalSelector.addGoal(1, new BreakDoorGoal(this), 1);
	this->goalSelector.addGoal(2, new MeleeAttackGoal(this, 1.0f, 0), 1);
	this->goalSelector.addGoal(6, new RandomStrollGoal(this, 1.0f), 1);
	this->goalSelector.addGoal(7, new LookAtPlayerGoal(this, 8.0f), 1);
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
	if(!this->level->isClient) {
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

int32_t Zombie::getMaxHealth() {
	return 12;
}
int32_t Zombie::getArmorValue() {
	int v = Mob::getArmorValue() + 2;
	if(v >= 20) {
		return 20;
	}
	return v;
}
void Zombie::aiStep() {
	this->skyCheckCounter += 1;
	if((this->skyCheckCounter & 1) != 0 && this->level->isDay() && !this->level->isClient && !this->isBaby()) {
		if(this->getBrightness(1.0f) > 0.5f) {
			if(!this->isOnFire()) {
				int x = Mth::floor(this->posX);
				int y = Mth::floor(this->posY);
				int z = Mth::floor(this->posZ);
				if(this->level->canSeeSky(x, y, z)) { //TODO make this compile into cbnz and not cbz </3
					this->setOnFire(8);
				}
			}
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
	ItemInstance* v3 = this->getCarriedItem();
	int attackDamage = this->attackDamage;
	if(v3) {
		attackDamage += v3->getAttackDamage(this);
	}
	return attackDamage;
}
