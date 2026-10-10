#include <entity/Animal.hpp>
#include <entity/Player.hpp>
#include <entity/player/Abilities.hpp>
#include <inventory/Inventory.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <nbt/CompoundTag.hpp>
#include <tile/Tile.hpp>
#include <math/Mth.hpp>

Animal::Animal(Level* a2)
	: AgableMob(a2) {
	this->inLove = 0;
}
bool_t Animal::canMate(const Animal* a2) const{
	int32_t v4; // r6

	if(a2 != this && (v4 = a2->getEntityTypeId(), v4 == this->getEntityTypeId()) && this->isInLove()) {
		return a2->isInLove();
	} else {
		return 0;
	}
}
bool_t Animal::isInLove() const {
	return this->inLove > 0;
}
void Animal::resetLove() {
	this->inLove = 0;
}

bool_t Animal::interactWithPlayer(Player* a2) {

	ItemInstance* sel = a2->inventory->getSelected();
	if(!sel || !this->isFood(sel)) return Entity::interactWithPlayer(a2);
	if(this->isBaby() || this->getAge() != 0) return Entity::interactWithPlayer(a2);

	if(!a2->abilities.instabuild) {
		--sel->count;
	}
	int v5 = 7;
	this->inLove = 600;
	this->attackTarget = 0;
	do {
		float g = this->random.nextGaussian();
		float g2 = this->random.nextGaussian();
		float g3 = this->random.nextGaussian();
		this->level->addParticle(PT_HEART,
			this->posX + (this->random.nextFloat() * this->entityWidth)*2 - this->entityWidth,
			(this->posY + 0.5f) + (this->random.nextFloat() * this->entityHeight),
			this->posZ + (this->random.nextFloat() * this->entityWidth)*2 - this->entityWidth,
			g * 0.02f, g2 * 0.02f, g3 * 0.02f, 0);
		--v5;
	} while(v5);
	return 1;
}

bool_t Animal::hurt(Entity* a2, int32_t a3) {
	this->inPanicTicksMaybe = 60;
	this->attackTarget = 0;
	this->inLove = 0;
	return Mob::hurt(a2, a3);
}
int32_t Animal::getCreatureBaseType() const{
	return 2;
}
void Animal::readAdditionalSaveData(CompoundTag* a2) {
	AgableMob::readAdditionalSaveData(a2);
	this->inLove = a2->getInt("InLove");
}
void Animal::addAdditonalSaveData(CompoundTag* a2) {
	AgableMob::addAdditonalSaveData(a2);
	a2->putInt("InLove", this->inLove);
}
int32_t Animal::getAmbientSoundInterval() {
	return 240;
}
void Animal::aiStep() {
	AgableMob::aiStep();
	if(this->getAge() != 0) {
		this->inLove = 0;
	}

	if(this->inLove > 0) {
		this->inLove -= 1;
		if((this->inLove & 0xF) == 0) {
			float g = this->random.nextGaussian();
			float g1 = this->random.nextGaussian();
			float g2 = this->random.nextGaussian();

			this->level->addParticle(PT_HEART,
				(this->posX + (this->random.nextFloat() * this->entityWidth)*2) - this->entityWidth,
				(this->posY + 0.5f) + (float)(this->random.nextFloat() * this->entityHeight),
				this->posZ + (this->random.nextFloat() * this->entityWidth)*2 - this->entityWidth,
				g * 0.02f, g1 * 0.02f, g2 * 0.02f, 0
			);
		}
	}
}
bool_t Animal::canSpawn() {
	int x = Mth::floor(this->posX); //all 3 should be inlined
	int y = Mth::floor(this->posY);
	int z = Mth::floor(this->posZ);

	return level->getTile(x, y - 1, z) == Tile::grass->blockID && this->level->getRawBrightness(x, y, z) > 8 && PathfinderMob::canSpawn();
}
bool_t Animal::removeWhenFarAway() {
	return 0;
}
float Animal::getWalkTargetValue(int32_t x, int32_t y, int32_t z) {
	if(this->level->getTile(x, y - 1, z) == Tile::grass->blockID) {
		return 10.0;
	} else {
		return this->level->getBrightness(x, y, z) - 0.5;
	}
}
Entity* Animal::findAttackTarget() {
	return 0;
}
bool_t Animal::isFood(const ItemInstance* a2) const{
	return a2->getId() == Item::wheat->itemID;
}
