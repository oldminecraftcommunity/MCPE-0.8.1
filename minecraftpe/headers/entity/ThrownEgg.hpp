#pragma once
#include <entity/Throwable.hpp>
#include <entity/Chicken.hpp>
#include <level/Level.hpp>
#include <math/HitResult.hpp>
#include <item/Item.hpp>


struct ThrownEgg: Throwable
{
	ThrownEgg(Level* level, Mob* thrower) :
			Throwable(level, thrower) {
		this->entityRenderId = THROWNEGG;
	}
	ThrownEgg(Level* level) :
			Throwable(level) {
		this->entityRenderId = THROWNEGG;
	}

	virtual ~ThrownEgg(){}
	virtual int32_t getEntityTypeId() const {
		return 82;
	}
	virtual void onHit(const HitResult& a2) {
		if (a2.hitType == 1) {
			a2.entity->hurt(this, 0);
		}

		if (this->level->isClient && Entity::sharedRandom.nextInt(8) == 0) {
			int toSpawn = Entity::sharedRandom.nextInt(32) != 0 ? 1 : 4;

			for(int v3 = 0; v3 < toSpawn; ++v3){
				Chicken* v5 = new Chicken(this->level);
				v5->setAge(-24000);
				v5->moveTo(this->posX, this->posY, this->posZ, this->yaw, 0);
				this->level->addEntity(v5);
			}
		}
		for(int v4 = 6; v4 > 0; --v4){
			this->level->addParticle(PT_BREAKING_ITEM_2, this->posX, this->posY, this->posZ, 0, 0, 0, Item::egg->itemID);
		}

		if (!this->level->isClient) {
			this->remove();
		}
	}
};
