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
	return (this->prevSwellTime + ((this->swellTime - this->prevSwellTime) * a2)) / 28.0f;
}
void Creeper::setSwellDir(int32_t a2) {
	this->synchedEntityData.set<int8_t>(16, a2);
}

void Creeper::tick() {
	this->prevSwellTime = this->swellTime;
	if(this->level->isClient && this->getSwellDir() > 0) {
		if(!this->swellTime) {
			this->level->playSound(this, "random.fuse", 1.0, 0.5);
		}
		int v3 = this->swellTime + 1;
		if(v3 < 0) {
			v3 = 0;
		}
		this->swellTime = v3;
		if(this->swellTime > 29) {
			this->swellTime = 30;
		}
	}
	Monster::tick();
	if(!this->level->isClient && !this->attackTarget) {
		this->checkCantSeeTarget(0, 0.0);
	}
}
bool_t Creeper::interactWithPlayer(Player* a2) {
	ItemInstance* sel = a2->inventory->getSelected();
	if(!sel || Item::flintAndSteel != sel->itemClass || !Item::flintAndSteel) {
		return this->interactWithPlayer(a2);
	}
	if(!this->level->isClient && this->getSwellDir() != 2) {
		float x = a2->posX + 0.5f;
		float y = a2->posY + 0.5f;
		float z = a2->posZ + 0.5f;
		this->level->playSound(x, y, z, "fire.ignite", 1.0f, level->random.nextFloat() * 0.4f + 0.8f);
		this->setSwellDir(2);
	}
	sel->hurtAndBreak(1, a2);
	return 1;
}
int32_t Creeper::getEntityTypeId() const {
	return 33;
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
	int32_t swellDir; // r5

	if(!this->level->isClient) {
		int v6 = this->getSwellDir();
		if(v6 > 0) {
			if(radius >= 7.0) {
				if(v6 != 2) {
LABEL_11:
					swellDir = -1;
					goto LABEL_13;
				}
LABEL_9:
				swellDir = 2;
				goto LABEL_13;
			}
		} else if(radius >= 3.0) {
			goto LABEL_11;
		}
		if(this->swellTime == 0) {
			this->level->playSound(this, "random.fuse", 1.0, 0.5);
		}
		if(v6 != 2) {
			swellDir = 1;
LABEL_13:
			this->setSwellDir(swellDir);
			if(swellDir <= 0) {
				this->checkCantSeeTarget(a2, radius);
			} else {
				this->swellTime += 1;
				if(this->swellTime > 29) {
					this->level->explode(this, this->posX, this->posY, this->posZ, 2.4f);
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
	if(!this->level->isClient && this->swellTime > 0 && this->getSwellDir() != 2) {
		this->setSwellDir(-1);
		int v4 = this->swellTime - 1;
		if(v4 < 0) {
			v4 = 0;
		}
		this->swellTime = v4;
	}
}
