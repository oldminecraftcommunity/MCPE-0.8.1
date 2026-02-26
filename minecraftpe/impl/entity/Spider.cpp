#include <entity/Spider.hpp>
#include <level/Level.hpp>
#include <item/Item.hpp>
#include <entity/Player.hpp>
#include <math.h>

Spider::Spider(Level* a2)
	: Monster(a2) {
	this->field_C88 = 0;
	this->entityRenderId = SPIDER;
	this->setSize(1.4, 0.9);
	this->synchedEntityData.define<int8_t>(16, 0); //signed char
}
float Spider::getModelScale() {
	return 1.0;
}
bool_t Spider::isClimbing() {
	return this->synchedEntityData.getByte(16) & 1;
}
int32_t Spider::makeStepSound() {
	return 0;
}
void Spider::setClimbing(bool_t a2) {
	if(a2) {
		this->synchedEntityData.set<int8_t>(16, this->synchedEntityData.getByte(16) | 1);
	}else{
		this->synchedEntityData.set<int8_t>(16, this->synchedEntityData.getByte(16) & 0xfe);
	}
}

Spider::~Spider() {
}
void Spider::tick() {
	Monster::tick();
	if(!this->level->isClientMaybe) {
		this->setClimbing(this->isCollidedHorizontally);
	}
}
float Spider::getShadowRadius() {
	return this->entityWidth * 0.7;
}
void Spider::makeStuckInWeb() {
}
int32_t Spider::getEntityTypeId() const {
	return 35;
}
bool_t Spider::onLadder() {
	return this->isClimbing();
}
float Spider::getBaseSpeed() {
	return 0.3;
}
int32_t Spider::getMaxHealth() {
	return 8;
}
void Spider::aiStep() {
	Monster::aiStep();
}
int32_t Spider::getDeathLoot() {
	return Item::string->itemID;
}
const char_t* Spider::getAmbientSound() {
	return "mob.spider";
}
std::string Spider::getHurtSound() {
	return "mob.spider";
}
std::string Spider::getDeathSound() {
	return "mob.spiderdeath";
}
Entity* Spider::findAttackTarget() {
	if(this->getBrightness(1.0) >= 0.5) {
		return 0;
	}
	return this->level->getNearestPlayer(this, 16);
}
void Spider::checkHurtTarget(Entity* a2, float a3) {
	float diffX; // s17
	float diffZ; // s16
	float dist2; // s12

	if(this->getBrightness(1.0) <= 0.5 || this->random.genrand_int32() % 0x64) {
		if(a3 <= 2.0 || a3 >= 6.0 || this->random.genrand_int32() % 0xA) {
			Monster::checkHurtTarget(a2, a3);
		} else if(this->onGround) {
			diffX = a2->posX - this->posX;
			diffZ = a2->posZ - this->posZ;
			this->motionY = 0.4;
			dist2 = sqrt((float)((float)(diffZ * diffZ) + (float)(diffX * diffX)));
			this->motionX = (float)(this->motionX * 0.2) + (float)((float)((float)(diffX / dist2) * 0.5) * 0.8);
			this->motionZ = (float)(this->motionZ * 0.2) + (float)((float)((float)(diffZ / dist2) * 0.5) * 0.8);
		}
	} else {
		this->attackTarget = 0;
	}
}
