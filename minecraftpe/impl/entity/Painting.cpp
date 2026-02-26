#include <entity/Painting.hpp>
#include <Motive.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <nbt/CompoundTag.hpp>

Painting::Painting(Level* a2)
	: HangingEntity(a2) {
	this->entityRenderId = PAINTING;
}
Painting::Painting(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6)
	: HangingEntity(a2, a3, a4, a5, a6) {
	this->setRandomMotive(a6);
	this->entityRenderId = PAINTING;
}
Painting::Painting(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, const std::string& a7)
	: HangingEntity(a2, a3, a4, a5, a6) {
	this->motive = Motive::getMotiveByName(a7);
	this->setDir(a6);
	this->entityRenderId = PAINTING;
}
void Painting::setRandomMotive(int32_t direction) {
	std::vector<const Motive*> v12 = Motive::getAllMotivesAsList();
	std::vector<const Motive*> possible;
	for(auto&& m: v12) {
		if(m->isUsed) {
			this->motive = m;
			this->setDir(direction);
			if(this->survives()) {
				possible.emplace_back(m);
			}
		}
	}
	if(possible.empty()) {
		this->motive = Motive::DefaultImage;
	} else {
		this->motive = possible[Entity::sharedRandom.genrand_int32() % possible.size()];
	}
	this->setDir(direction);
}

Painting::~Painting() {
}
float Painting::getShadowRadius() {
	return 0;
}
bool_t Painting::isPickable() {
	return 1;
}
int32_t Painting::getEntityTypeId() const {
	return 83;
}
void Painting::readAdditionalSaveData(CompoundTag* a2) {
	this->motive = Motive::getMotiveByName(a2->getString("Motive"));
	HangingEntity::readAdditionalSaveData(a2);
}
void Painting::addAdditonalSaveData(CompoundTag* a2) {
	if(this->motive) {
		a2->putString("Motive", this->motive->name);
	}
	HangingEntity::addAdditonalSaveData(a2);
}
int32_t Painting::getWidth() {
	return this->motive->w;
}
int32_t Painting::getHeight() {
	return this->motive->h;
}
void Painting::dropItem() {
	if(this->level->getLevelData()->getGameType() != 1) {
		this->spawnAtLocation(Item::painting->itemID, 1);
	}
}
