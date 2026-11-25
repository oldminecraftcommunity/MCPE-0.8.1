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
	std::vector<Entity*> v15;
	this->level->getEntitiesOfType(this->animal->getEntityTypeId(), this->animal->boundingBox.grow(8.0f, 8.0f, 8.0f), v15);
	for(auto v13: v15) {
		if(this->animal->canMate((Animal*)v13)) {
			return (Animal*)v13;
		}
	}
	return 0;
}

bool_t BreedGoal::canUse() {
	if(this->animal->isInLove()) {
		Entity* partner = this->getFreePartner();
		if(partner != this->target.entity) {
			if(partner) {
				this->target.entityId = partner->entityId;
				this->target.level = partner->level;
				partner->level->registerTemporaryPointer(&this->target);
				this->target.locked = 0;
			} else {
				this->target.unset();
			}
		}
		return this->target.lock() != 0;
	}
	return 0;
}
bool_t BreedGoal::canContinueToUse() {
	if(this->target.lock()) {
		return this->target.lock()->isAlive() && this->target.lock()->isInLove() && this->inUseTicks <= 59;
	}

	return 0;
}
void BreedGoal::stop() {
	if(this->target.entity) {
		this->target.unset();
	}
	this->inUseTicks = 0;
}
void BreedGoal::tick() {
	this->animal->getLookControl()->setLookAt(this->target.lock(), 10.0, this->animal->getMaxHeadXRot());
	this->animal->getNavigation()->moveTo(this->target.lock(), this->speedMultiplier);
	this->inUseTicks += 1;
	if(this->inUseTicks == 60) {
		this->breed();
	}
}
