#include <entity/Creeper.hpp>
#include <entity/Player.hpp>
#include <inventory/Inventory.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <entity/ai/goals/FloatGoal.hpp>
#include <entity/ai/goals/SwellGoal.hpp>
#include <entity/ai/goals/MeleeAttackGoal.hpp>
#include <entity/ai/goals/RandomStrollGoal.hpp>
#include <entity/ai/goals/RandomLookAroundGoal.hpp>
#include <entity/ai/goals/LookAtPlayerGoal.hpp>
#include <entity/ai/goals/NearestAttackableTargetGoal.hpp>
#include <entity/ai/goals/HurtByTargetGoal.hpp>


Creeper::Creeper(Level* a2)
	: Monster(a2) {
	this->swellTime = 0;
	this->prevSwellTime = 0;
	this->field_C8C = -1;
	this->entityRenderId = CREEPER;
	this->skin = "mob/creeper.png";
	this->synchedEntityData.define<int8_t>(16, -1);
	this->goalSelector.addGoal(1, new FloatGoal(this), 1);
	this->goalSelector.addGoal(2, new SwellGoal(this), 1);
	this->goalSelector.addGoal(4, new MeleeAttackGoal(this, 1.25, 0), 1);
	this->goalSelector.addGoal(5, new RandomStrollGoal(this, 1.0), 1);
	this->goalSelector.addGoal(6, new LookAtPlayerGoal(this, 8.0), 1);
	this->goalSelector.addGoal(6, new RandomLookAroundGoal(this), 1);
	this->goalSelector2.addGoal(2, new NearestAttackableTargetGoal(this, 16), 1);
	this->goalSelector2.addGoal(2, new HurtByTargetGoal(this, 16), 1);
}
int32_t Creeper::getSwellDir() {
	return this->synchedEntityData.getByte(16);
}
float Creeper::getSwelling(float a2) {
	return (float)((float)this->prevSwellTime + (float)((float)(this->swellTime - this->prevSwellTime) * a2)) / 28.0;
}
void Creeper::setSwellDir(int32_t a2) {
	this->synchedEntityData.set(16, a2);
}

Creeper::~Creeper() {
}
void Creeper::tick() {
	int32_t v3; // r3

	this->prevSwellTime = this->swellTime;
	if(this->level->isClientMaybe && this->getSwellDir() > 0) {
		if(!this->swellTime) {
			this->level->playSound(this, "random.fuse", 1.0, 0.5);
		}
		v3 = this->swellTime + 1;
		if(v3 < 0) {
			v3 = 0;
		}
		this->swellTime = v3;
		if(this->swellTime > 29) {
			this->swellTime = 30;
		}
	}
	Monster::tick();
	if(!this->level->isClientMaybe && !this->attackTarget) {
		this->checkCantSeeTarget(0, 0.0);
	}
}
bool_t Creeper::interactWithPlayer(Player* a2) {
	ItemInstance* sel; // r0
	ItemInstance* v5;  // r7
	float v7;		   // s18
	float v8;		   // s17
	float v9;		   // s16
	Level* level;	   // r8

	sel = a2->inventory->getSelected();
	v5 = sel;
	if(!sel || Item::flintAndSteel != sel->itemClass || !Item::flintAndSteel) {
		return this->interactWithPlayer(a2);
	}
	if(!this->level->isClientMaybe && this->getSwellDir() != 2) {
		v7 = a2->posX + 0.5;
		v8 = a2->posY + 0.5;
		v9 = a2->posZ + 0.5;
		level = this->level;
		level->playSound(v7, v8, v9, "fire.ignite", 1.0, (float)(level->random.nextFloat() * 0.4) + 0.8);
		;
		this->setSwellDir(2);
	}
	v5->hurtAndBreak(1, a2);
	return 1;
}
int32_t Creeper::getEntityTypeId() const {
	return 33;
}
float Creeper::getBaseSpeed() {
	return 0.25;
}
int32_t Creeper::getMaxHealth() {
	return 16;
}
int32_t Creeper::getDeathLoot() {
	return Item::sulphur->itemID;
}
std::string Creeper::getHurtSound() {
	return "mob.creeper";
}
std::string Creeper::getDeathSound() {
	return "mob.creeperdeath";
}
bool_t Creeper::useNewAi() {
	return 0;
}
void Creeper::checkHurtTarget(Entity* a2, float radius) {
	int32_t v6;		  // r0
	int32_t v7;		  // r5
	int32_t swellDIr; // r5
	int32_t v10;	  // r3

	if(!this->level->isClientMaybe) {
		v6 = this->getSwellDir();
		v7 = v6;
		if(v6 > 0) {
			if(radius >= 7.0) {
				if(v6 != 2) {
LABEL_11:
					swellDIr = -1;
					goto LABEL_13;
				}
LABEL_9:
				swellDIr = 2;
				goto LABEL_13;
			}
		} else if(radius >= 3.0) {
			goto LABEL_11;
		}
		if(!this->swellTime) {
			this->level->playSound(this, "random.fuse", 1.0, 0.5);
		}
		if(v7 != 2) {
			swellDIr = 1;
LABEL_13:
			this->setSwellDir(swellDIr);
			if(swellDIr <= 0) {
				this->checkCantSeeTarget(a2, radius);
			} else {
				v10 = this->swellTime + 1;
				this->swellTime = v10;
				if(v10 > 29) {
					this->level->explode(this, this->posX, this->posY, this->posZ, 2.4);
					this->remove();
				}
				this->_shouldHoldGround = 1;
			}
			return;
		}
		goto LABEL_9;
	}
}
void Creeper::checkCantSeeTarget(Entity* a2, float a3) {
	int32_t v4; // r3

	if(!this->level->isClientMaybe && this->swellTime > 0 && this->getSwellDir() != 2) {
		this->setSwellDir(-1);
		v4 = this->swellTime - 1;
		if(v4 < 0) {
			v4 = 0;
		}
		this->swellTime = v4;
	}
}
