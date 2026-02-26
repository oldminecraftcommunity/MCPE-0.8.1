#include <entity/PigZombie.hpp>
#include <entity/Arrow.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <nbt/CompoundTag.hpp>

PigZombie::PigZombie(Level* a2)
	: Zombie(a2)
	, itemInHand(Item::sword_gold) {
	this->field_C90 = 0;
	this->field_C94 = 0;
	this->field_C98 = 60;
	this->skin = "mob/pigzombie.png";
	this->field_112 = 1;
	this->attackDamage = 5;
}
int32_t PigZombie::alert(Entity* a2) {
	Random* p_random; // r5
	int32_t v4;		  // r0
	int32_t r;		  // r0
	int32_t v6;		  // r1

	p_random = &this->random;
	this->attackTarget = a2->entityId;
	this->field_C90 = 400 * (this->random.genrand_int32() % 0x190);
	v4 = p_random->genrand_int32();
	v6 = v4 % 0x28u;
	r = v4 / 0x28u;
	this->field_C94 = v6;
	return r;
}

PigZombie::~PigZombie() {
}
void PigZombie::tick() {
	int32_t v2;	  // r3
	int32_t v3;	  // r3
	int32_t v4;	  // r3
	Level* level; // r7
	float posX;	  // r10
	float posY;	  // r9
	float posZ;	  // r8
	float v9;	  // s16
	float v10;	  // s11
	float v11;	  // s14

	v2 = this->field_C98;
	if(v2 > 0) {
		this->field_C98 = v2 - 1;
	}
	v3 = this->field_C94;
	if(v3 > 0) {
		v4 = v3 - 1;
		this->field_C94 = v4;
		if(!v4) {
			level = this->level;
			posX = this->posX;
			posY = this->posY;
			posZ = this->posZ;
			v9 = this->getSoundVolume();
			level->playSound(posX, posY, posZ, "mob.zombiepig.zpigangry", v9 + v9, (float)((float)((float)(this->random.nextFloat() - this->random.nextFloat()) * 0.2) + 1.0) * 1.8);
		}
	}
	Monster::tick();
}
bool_t PigZombie::interactWithPlayer(Player*) {
	return 0;
}
bool_t PigZombie::hurt(Entity* a2, int32_t a3) {
	int32_t shooterEID; // r1
	Level* level;		// r0
	Entity* ent;

	if(a2) {
		if(a2->isPlayer()
		   || a2->getEntityTypeId() == 80 /*arrow*/
				  && (shooterEID = ((Arrow*)a2)->shooterEID) != 0 && (ent = this->level->getEntity(shooterEID), ent->isPlayer())) {
			level = this->level;
			//TODO it makes a copy for some reason?
			std::vector<struct Entity*>* ents = level->getEntities(this, {this->boundingBox.minX - 12.0f, this->boundingBox.minY - 12.0f, this->boundingBox.minZ - 12.0f, this->boundingBox.maxX + 12.0f, this->boundingBox.maxY + 12.0f, this->boundingBox.maxZ + 12.0f});
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
	this->field_C90 = a2->getShort("Anger");
}
void PigZombie::addAdditonalSaveData(CompoundTag* a2) {
	Mob::addAdditonalSaveData(a2);
	a2->putShort("Anger", this->field_C90);
}

//TODO probably not actually static
static std::string _tex = "mob/pigzombie.png";
std::string* PigZombie::getTexture() {
	return &_tex;
}
float PigZombie::getBaseSpeed() {
	return 0.25;
}
bool_t PigZombie::canSpawn() {
	Level* level; // r0

	level = this->level;
	if(level->difficulty <= 0 || !level->isUnobstructed(this->boundingBox)) {
		return 0;
	}
	std::vector<AABB>* cubes = this->level->getCubes(this, this->boundingBox, 0);
	return cubes->begin() - cubes->end() + (cubes->begin() == cubes->end()) + cubes->begin() - cubes->end();
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

	if(this->field_C98) {
		return 0;
	}
	if(this->field_C90) {
		return Monster::findAttackTarget();
	}
	atk = Monster::findAttackTarget();
	v3 = atk;
	if(!atk || atk->distanceTo(this->posX, this->posY, this->posZ) >= 5.0) {
		return 0;
	}
	return v3;
}
int32_t PigZombie::getAttackTime() {
	return 40;
}
