#include <entity/PigZombie.hpp>
#include <entity/Arrow.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <nbt/CompoundTag.hpp>

PigZombie::PigZombie(Level* a2)
	: Zombie(a2)
	, itemInHand(Item::sword_gold) {
	this->anger = 0;
	this->angrySoundCounter = 0;
	this->noAttackTime = 60;
	this->skin = "mob/pigzombie.png";
	this->field_112 = 1;
	this->attackDamage = 5;
}
void PigZombie::alert(Entity* a2) {
	this->attackTarget = a2->entityId;
	this->anger = 400 * (this->random.nextInt(400));
	this->angrySoundCounter = this->random.nextInt(40);
}

void PigZombie::tick() {
	if(this->noAttackTime > 0) {
		this->noAttackTime -= 1;
	}
	if(this->angrySoundCounter > 0) {
		this->angrySoundCounter -= 1;
		if(this->angrySoundCounter == 0) {
			this->level->playSound(
				this->posX, this->posY, this->posZ,
				"mob.zombiepig.zpigangry", this->getSoundVolume() * 2,
				(((this->random.nextFloat() - this->random.nextFloat()) * 0.2f) + 1.0f) * 1.8f
			);
		}
	}
	Monster::tick();
}
bool_t PigZombie::interactWithPlayer(Player*) {
	return 0;
}
bool_t PigZombie::hurt(Entity* a2, int32_t a3) {
	int32_t shooterEID; // r1
	Entity* ent;

	if(a2) {
		if(a2->isPlayer() || a2->getEntityTypeId() == 80 /*arrow*/
				  && (shooterEID = ((Arrow*)a2)->shooterEID) != 0 && (ent = this->level->getEntity(shooterEID), ent->isPlayer())) {
			//TODO it makes a copy for some reason?

			std::vector<struct Entity*>* ents = this->level->getEntities(this, this->boundingBox.grow(12.0f, 12.0f, 12.0f));
			for(auto& p: *ents) {
				if(p->getEntityTypeId() == 36) {
					((PigZombie*)p)->alert(a2);
				}
			}
		}
	}
	return Monster::hurt(a2, a3);
}
int32_t PigZombie::getEntityTypeId() const {
	return 36;
}
void PigZombie::readAdditionalSaveData(CompoundTag* a2) {
	Mob::readAdditionalSaveData(a2);
	this->anger = a2->getShort("Anger");
}
void PigZombie::addAdditonalSaveData(CompoundTag* a2) {
	Mob::addAdditonalSaveData(a2);
	a2->putShort("Anger", this->anger);
}

std::string* PigZombie::getTexture() {
	static std::string _tex = "mob/pigzombie.png";
	return &_tex;
}
bool_t PigZombie::canSpawn() {
	if(this->level->difficulty <= 0) return 0;
	if(!this->level->isUnobstructed(this->boundingBox)) return 0;

	std::vector<AABB>* cubes = this->level->getCubes(this, this->boundingBox, 0);
	return cubes->empty();
}
ItemInstance* PigZombie::getCarriedItem() {
	return &this->itemInHand;
}
int32_t PigZombie::getDeathLoot() {
	return 0;
}
void PigZombie::dropDeathLoot() {
	int8_t v2;	// r0
	int32_t v3; // r3
	int32_t v4; // r6

	v2 = this->random.genrand_int32();
	v3 = 0;
	v4 = v2 & 1;
	while(v3 < v4) {
		this->spawnAtLocation(Item::goldIngot->itemID, 1);
		v3 = 1;
	}
}
const char_t* PigZombie::getAmbientSound() {
	return "mob.zombiepig.zpig";
}
std::string PigZombie::getHurtSound() {
	return "mob.zombiepig.zpighurt";
}
std::string PigZombie::getDeathSound() {
	return "mob.zombiepig.zpigdeath";
}
bool_t PigZombie::useNewAi() {
	return 0;
}
Entity* PigZombie::findAttackTarget() {
	Entity* atk; // r0
	Entity* v3;	 // r5

	if(this->noAttackTime != 0) {
		return 0;
	}
	if(this->anger) {
		return Monster::findAttackTarget();
	}
	atk = Monster::findAttackTarget();
	v3 = atk;
	if(!atk || atk->distanceTo(this->posX, this->posY, this->posZ) >= 5.0f) {
		return 0;
	}
	return v3;
}
int32_t PigZombie::getAttackTime() {
	return 40;
}
