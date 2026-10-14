#include <entity/ai/goals/BreedGoal.hpp>
#include <entity/Animal.hpp>
#include <entity/ai/LookControl.hpp>
#include <entity/path/PathNavigation.hpp>
#include <level/Level.hpp>

BreedGoal::BreedGoal(Animal* a2, float a3) :
	Goal(), animal(a2), target(), inUseTicks(0), speedMultiplier(a3){
	this->level = a2->level;
	this->setRequiredControlFlags(3);
}
void BreedGoal::breed() {

	AgableMob* baby = (AgableMob*)this->animal->getBreedOffspring(this->target.lock());
	if(baby) {
		this->animal->setAge(6000);
		this->target.lock()->setAge(6000);
		this->animal->resetLove();
		this->target.lock()->resetLove();

		baby->setAge(-24000);
		baby->moveTo(this->animal->posX, this->animal->posY, this->animal->posZ, 0.0, 0.0);
		this->level->addEntity(baby);


		int cnt = 7;
		Random* rng = &this->animal->level->random;
		do {
			float g = rng->nextGaussian();
			float g2 = rng->nextGaussian();
			float g3 = rng->nextGaussian();
			this->level->addParticle(PT_HEART,
				this->animal->posX + (rng->nextFloat() * this->animal->entityWidth) * 2 - this->animal->entityWidth,
				(this->animal->posY + 0.5f) + (rng->nextFloat() * this->animal->entityHeight),
				this->animal->posZ + (rng->nextFloat() * this->animal->entityWidth) * 2 - this->animal->entityWidth,
				g * 0.02f, g2 * 0.02f, g3 * 0.02f, 0
			);
		} while(--cnt);
	} else {
		this->animal->resetLove();
		this->target.lock()->resetLove();
	}
}
Animal* BreedGoal::getFreePartner() {
	Level* level;	// r5
	Animal* animal; // r0
	int32_t v4;		// r0
	Animal* v5;		// r3
	float minZ;		// s11
	float maxX;		// s12
	float maxY;		// s13
	float maxZ;		// s14
	float minX;		// s9
	Animal* v12;	// r5
	Animal* v13;	// t1

	level = this->level;
	animal = this->animal;
	std::vector<Entity*> v15;
	v4 = animal->getEntityTypeId();
	v5 = this->animal;
	minZ = v5->boundingBox.minZ;
	maxX = v5->boundingBox.maxX;
	maxY = v5->boundingBox.maxY;
	maxZ = v5->boundingBox.maxZ;
	minX = v5->boundingBox.minX;
	AABB v16{minX - 8.0f, v5->boundingBox.minY - 8.0f, minZ - 8.0f, maxX + 8.0f, maxY + 8.0f, maxZ + 8.0f};
	level->getEntitiesOfType(v4, v16, v15);
	for(auto& v13: v15) {
		v12 = (Animal*)v13;
		if(this->animal->canMate((const Animal*)v13)) {
			return v12;
		}
	}
	return 0;
}

bool_t BreedGoal::canUse() {
	bool_t result;	   // r0
	Animal* freeCliff; // r0
	Level* level;	   // r0

	result = this->animal->isInLove();
	if(result) {
		freeCliff = this->getFreePartner();
		if(freeCliff != this->target.entity) {
			if(freeCliff) {
				this->target.entityId = freeCliff->entityId;
				level = freeCliff->level;
				this->target.level = level;
				level->registerTemporaryPointer(&this->target);
				this->target.locked = 0;
			} else {
				this->target.unset();
			}
		}
		return this->target.lock() != 0;
	}
	return result;
}
bool_t BreedGoal::canContinueToUse() {
	Mob* v4;	// r0
	Animal* v5; // r0

	if(this->target.lock() && (v4 = this->target.lock(), v4->isAlive()) && (v5 = this->target.lock(), v5->isInLove())) {
		return this->inUseTicks <= 59;
	} else {
		return 0;
	}
}
void BreedGoal::stop() {
	if(this->target.entity) {
		this->target.unset();
	}
	this->inUseTicks = 0;
}
void BreedGoal::tick() {
	LookControl* look;	 // r7
	Entity* v3;			 // r6
	float v4;			 // r0
	PathNavigation* nav; // r6
	Mob* v6;			 // r0
	int32_t v7;			 // r3

	look = this->animal->getLookControl();
	v3 = this->target.lock();
	v4 = this->animal->getMaxHeadXRot();
	look->setLookAt(v3, 10.0, v4);
	nav = this->animal->getNavigation();
	v6 = this->target.lock();
	nav->moveTo(v6, this->speedMultiplier);
	v7 = this->inUseTicks + 1;
	this->inUseTicks = v7;
	if(v7 == 60) {
		this->breed();
	}
}
