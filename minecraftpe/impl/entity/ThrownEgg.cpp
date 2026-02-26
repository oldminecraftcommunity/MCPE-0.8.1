#include <entity/ThrownEgg.hpp>
#include <entity/Chicken.hpp>
#include <level/Level.hpp>
#include <math/HitResult.hpp>
#include <item/Item.hpp>

ThrownEgg::ThrownEgg(Level* level, Mob* thrower)
	: Throwable(level, thrower) {
	this->entityRenderId = THROWNEGG;
}
ThrownEgg::ThrownEgg(Level* level)
	: Throwable(level) {
	this->entityRenderId = THROWNEGG;
}

ThrownEgg::~ThrownEgg() {
}
int32_t ThrownEgg::getEntityTypeId() const {
	return 82;
}
void ThrownEgg::onHit(const HitResult& a2) {
	int32_t v3;	 // r8
	int32_t v4;	 // r5
	Chicken* v5; // r5
	int32_t v6;	 // r9

	if(a2.hitType == 1) {
		a2.entity->hurt(this, 0);
	}
	if(!this->level->isClientMaybe) {
		v3 = Entity::sharedRandom.genrand_int32() & 7;
		if(!v3) {
			if((Entity::sharedRandom.genrand_int32() & 31) != 0) {
				v6 = 1;
			} else {
				v6 = 4;
			}
			do {
				++v3;
				v5 = new Chicken(this->level);
				v5->setAge(-24000);
				v5->moveTo(this->posX, this->posY, this->posZ, this->yaw, 0.0);
				this->level->addEntity(v5);
			} while(v3 < v6);
		}
	}
	v4 = 6;
	do {
		this->level->addParticle(PT_BREAKING_ITEM_2, this->posX, this->posY, this->posZ, 0.0, 0.0, 0.0, Item::egg->itemID);
		--v4;
	} while(v4);
	if(!this->level->isClientMaybe) {
		this->remove();
	}
}
