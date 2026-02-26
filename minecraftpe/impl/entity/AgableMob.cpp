#include <entity/AgableMob.hpp>
#include <nbt/CompoundTag.hpp>
#include <level/Level.hpp>

AgableMob::AgableMob(Level* a2)
	: PathfinderMob(a2) {
	this->age = -1;
	this->synchedEntityData.define<int8_t>(14, 0); //signed char

	this->setAge(0);
}

int32_t AgableMob::getAge() {
	return this->age;
}
void AgableMob::setAge(int32_t age) {
	//TODO check
	bool_t v5 = age >= 0 ? ((uint32_t)this->age >> 31) : 0;
	if(v5) {
		this->synchedEntityData.clearFlag<char>(14, 0);
	} else if(((this->age >= 0) & ((uint32_t)age >> 31)) != 0) {
		this->synchedEntityData.setFlag<char>(14, 0);
	}
	this->age = age;
}

AgableMob::~AgableMob() {
}
float AgableMob::getShadowRadius() {
	float v3 = this->entityWidth * 0.8;
	float v4 = 0.5;
	if(!this->isBaby()) {
		v4 = 1.0;
	}
	return v3 * v4;
}
void AgableMob::readAdditionalSaveData(CompoundTag* a2) {
	Mob::readAdditionalSaveData(a2);
	this->setAge(a2->getInt("Age"));
}
void AgableMob::addAdditonalSaveData(CompoundTag* a2) {
	Mob::addAdditonalSaveData(a2);
	a2->putInt("Age", this->getAge());
}
void AgableMob::aiStep() {
	Mob::aiStep();
	if(this->age >= 0) {
		if(this->age) {
			this->setAge(this->age - 1);
		}
	} else {
		this->setAge(this->age + 1);
	}
}
bool_t AgableMob::isBaby() {
	if(!this->level->isClientMaybe) {
		return (uint32_t)this->age >> 31;
	}
	return this->synchedEntityData.getByte(14) & 1;
}
