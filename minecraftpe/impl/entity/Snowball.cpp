#include <entity/Snowball.hpp>
#include <math/HitResult.hpp>
#include <level/Level.hpp>
#include <item/Item.hpp>

Snowball::Snowball(Level* level, Mob* thrower)
	: Throwable(level, thrower) {
	this->entityRenderId = THROWNSNOWBALL;
	//TODO probably has more stuff but it was inlined
}
Snowball::Snowball(Level* level)
	: Throwable(level) {
	this->entityRenderId = THROWNSNOWBALL;
}

Snowball::~Snowball() {
}
int32_t Snowball::getEntityTypeId() const {
	return 81;
}

void Snowball::onHit(const HitResult& a2) {
	int32_t v3; // r5

	if(a2.hitType == 1) {
		a2.entity->hurt(this, 0);
	}
	v3 = 6;
	do {
		this->level->addParticle(PT_BREAKING_ITEM_2, this->posX, this->posY, this->posZ, 0.0, 0.0, 0.0, Item::snowBall->itemID);
		--v3;
	} while(v3);
	if(!this->level->isClientMaybe) {
		this->remove();
	}
}
