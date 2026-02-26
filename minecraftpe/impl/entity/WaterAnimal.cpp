#include <entity/WaterAnimal.hpp>
#include <level/Level.hpp>

WaterAnimal::WaterAnimal(Level* level)
	: PathfinderMob(level) {
}
int32_t WaterAnimal::getExperienceReward(Player*) {
	return this->random.genrand_int32() % 3 + 1;
}
WaterAnimal::~WaterAnimal() {
}
int32_t WaterAnimal::getCreatureBaseType() {
	return 3;
}
void WaterAnimal::readAdditionalSaveData(CompoundTag* t) {
	PathfinderMob::readAdditionalSaveData(t);
}
void WaterAnimal::addAdditonalSaveData(CompoundTag* t) {
	PathfinderMob::addAdditonalSaveData(t);
}
bool_t WaterAnimal::isWaterMob() {
	return 1;
}
int32_t WaterAnimal::getAmbientSoundInterval() {
	return 120;
}
float WaterAnimal::getBaseSpeed() {
	return 0.2;
}
bool_t WaterAnimal::canSpawn() {
	return this->level->isUnobstructed(this->boundingBox);
}
bool_t WaterAnimal::removeWhenFarAway() {
	return 1;
}
