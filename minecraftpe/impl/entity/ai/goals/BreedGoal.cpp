#include <entity/ai/goals/BreedGoal.hpp>
#include <entity/Animal.hpp>
#include <entity/ai/LookControl.hpp>
#include <entity/path/PathNavigation.hpp>
#include <level/Level.hpp>

BreedGoal::BreedGoal(Animal* a2, float a3)
	: Goal() {
	this->animal = a2;
	this->speedMultiplier = a3;
	this->level = a2->level;
	this->setRequiredControlFlags(3);
}
void BreedGoal::breed() {
	Animal* animal;	   // r5
	Animal* v5;		   // r0
	AgableMob* v6;	   // r5
	Animal* v8;		   // r0
	AgableMob* v9;	   // r0
	Animal* v10;	   // r0
	int32_t v11;	   // r6
	Random* p_random;  // r5
	float g;		   // s23
	float Gaussian;	   // s22
	float v15;		   // r0
	Level* level;	   // r7
	float posX;		   // s18
	float v18;		   // s21
	Animal* v20;	   // r3
	float entityWidth; // s13
	float v22;		   // s14
	float v23;		   // s20
	float posY;		   // s18
	Animal* v26;	   // r3
	float posZ;		   // s25
	float v28;		   // s14
	float v29;		   // s18
	float v30;		   // s14

	animal = this->animal;
	v5 = this->target.lock();
	v6 = (AgableMob*)animal->getBreedOffspring(v5);
	if(v6) {
		this->animal->setAge(6000);
		v9 = this->target.lock();
		v9->setAge(6000);
		this->animal->resetLove();
		v10 = this->target.lock();
		v10->resetLove();
		v6->setAge(-24000);
		v6->moveTo(this->animal->posX, this->animal->posY, this->animal->posZ, 0.0, 0.0);
		v11 = 7;
		this->level->addEntity(v6);
		p_random = &this->animal->level->random;
		do {
			g = p_random->nextGaussian();
			Gaussian = p_random->nextGaussian();
			v15 = p_random->nextGaussian();
			level = this->level;
			posX = this->animal->posX;
			v18 = v15;
			v20 = this->animal;
			entityWidth = v20->entityWidth;
			v22 = p_random->nextFloat();
			v23 = posX + (float)((float)(v22 * entityWidth) + (float)(v22 * entityWidth));
			posY = v20->posY;
			v26 = this->animal;
			posZ = v26->posZ;
			v28 = p_random->nextFloat();
			v29 = (float)(posY + 0.5) + (float)(v28 * v26->entityHeight);
			v30 = p_random->nextFloat();
			level->addParticle(PT_HEART, v23 - entityWidth, v29, (float)(posZ + (float)((float)(v30 * this->animal->entityWidth) + (float)(v30 * this->animal->entityWidth))) - this->animal->entityWidth, g * 0.02, Gaussian * 0.02, v18 * 0.02, 0);
			--v11;
		} while(v11);
	} else {
		this->animal->resetLove();
		v8 = this->target.lock();
		v8->resetLove();
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

BreedGoal::~BreedGoal() {
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
void BreedGoal::setLevel(Level* l) {
	this->level = l;
}
