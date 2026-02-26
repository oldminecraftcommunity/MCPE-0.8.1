#include <entity/Sheep.hpp>
#include <tile/Tile.hpp>
#include <entity/ai/goals/EatTileGoal.hpp>
#include <level/Level.hpp>
#include <math/Mth.hpp>
#include <entity/path/PathNavigation.hpp>
#include <entity/ai/goals/FloatGoal.hpp>
#include <entity/ai/goals/PanicGoal.hpp>
#include <entity/ai/goals/BreedGoal.hpp>
#include <entity/ai/goals/TemptGoal.hpp>
#include <item/Item.hpp>
#include <entity/ai/goals/FollowParentGoal.hpp>
#include <entity/ai/goals/RandomStrollGoal.hpp>
#include <entity/ai/goals/LookAtPlayerGoal.hpp>
#include <entity/ai/goals/RandomLookAroundGoal.hpp>
#include <nbt/CompoundTag.hpp>
#include <entity/Player.hpp>
#include <entity/ItemEntity.hpp>
#include <inventory/Inventory.hpp>

Sheep::Sheep(Level* a2)
	: Animal(a2) {
	this->field_C88 = 0;
	this->entityRenderId = SHEEP;
	this->skin = "mob/sheep.png";
	this->setSize(0.9, 1.3);
	this->synchedEntityData.define<int8_t>(16, 0); //signed char
	this->eatTileGoal = new EatTileGoal(this);
	this->getNavigation()->setAvoidWater(1);
	this->goalSelector.addGoal(0, new FloatGoal(this), 1);
	this->goalSelector.addGoal(1, new PanicGoal(this, 1.5), 1);
	this->goalSelector.addGoal(2, new BreedGoal(this, 1.0), 1);
	this->goalSelector.addGoal(3, new TemptGoal(this, 1.0, {Item::wheat->itemID}, 0), 1);
	this->goalSelector.addGoal(4, new FollowParentGoal(this, 1.0), 1);
	this->goalSelector.addGoal(5, this->eatTileGoal, 0);
	this->goalSelector.addGoal(6, new RandomStrollGoal(this, 1.0), 1);
	this->goalSelector.addGoal(7, new LookAtPlayerGoal(this, 6.0), 1);
	this->goalSelector.addGoal(8, new RandomLookAroundGoal(this), 1);
}
int32_t Sheep::getColor() {
	return this->synchedEntityData.getByte(16) & 0xf;
}
float Sheep::getHeadEatAngleScale(float a2) {
	int v3; // r1

	v3 = this->field_C88;
	if((uint32_t)(v3 - 5) <= 0x1F) {
		return (float)((float)(3.1416 * 0.07) * Mth::sin((float)((float)((float)(v3 - 4) - a2) * 0.03125) * 28.7)) + (float)(3.1416 * 0.2);
	}
	if(v3 <= 0) {
		return this->pitch / (float)(180.0 / 3.1416);
	}
	return 3.1416 * 0.2;
}
float Sheep::getHeadEatPositionScale(float a2) {
	int32_t v2; // r3
	int32_t v3; // s12

	v2 = this->field_C88;
	if(v2 <= 0) {
		return 0.0;
	}
	if((uint32_t)(v2 - 4) <= 0x20) {
		return 1.0;
	}
	if(v2 > 3) {
		return -(float)((float)((float)(v2 - 40) - a2) * 0.25);
	}
	v3 = this->field_C88;
	return (float)((float)v2 - a2) * 0.25;
}
int32_t Sheep::getSheepColor(Random* a1) {
	int32_t v2; // r1

	v2 = a1->genrand_int32() % 100;
	if(v2 <= 4) {
		return 15;
	}
	if(v2 <= 9) {
		return 7;
	}
	if(v2 <= 14) {
		return 8;
	}
	if(v2 <= 17) {
		return 12;
	}
	if(a1->genrand_int32() % 500) {
		return 0;
	}
	return 6;
}
bool_t Sheep::isSheared() {
	return ((uint32_t)this->synchedEntityData.getByte(16) >> 4) & 1;
}
void Sheep::setColor(int32_t a2) {
	int32_t v4 = a2 & 0xF | this->synchedEntityData.getByte(16) & 0xF0;
	this->synchedEntityData.set<int8_t>(16, v4); //signed char
}
void Sheep::setSheared(bool_t a2) {
	int8_t b = this->synchedEntityData.getByte(16);
	if(a2) b |= 0x10;
	else b &= 0xEF;
	this->synchedEntityData.set<int8_t>(16, b); //signed char
}

Sheep::~Sheep() {
}
bool_t Sheep::interactWithPlayer(Player* a2) {
	ItemInstance* sel; // r0
	ItemInstance* v5;  // r8
	int32_t v6;		   // r11
	int32_t i;		   // r10
	Level* level;	   // r3

	sel = a2->inventory->getSelected();
	v5 = sel;
	if(sel) {
		if(Item::shears == sel->itemClass) {
			if(Item::shears) {
				if(!this->isSheared() && !this->isBaby()) {
					level = this->level;
					if(!level->isClientMaybe) {
						i = 0;
						this->setSheared(1);
						v6 = this->random.genrand_int32() % 3;
						do {
							++i;
							Entity* v10 = this->spawnAtLocation(ItemInstance(Tile::cloth->blockID, 1, this->getColor()), 1.0);
							v10->motionY = v10->motionY + (float)(this->random.nextFloat() * 0.05);
							v10->motionX = v10->motionX + (float)((float)(this->random.nextFloat() - this->random.nextFloat()) * 0.1);
							v10->motionZ = v10->motionZ + (float)((float)(this->random.nextFloat() - this->random.nextFloat()) * 0.1);
						} while(v6 >= i);
					}
					if(!a2->abilities.instabuild) {
						v5->hurtAndBreak(1, a2);
					}
				}
			}
		}
	}
	return Animal::interactWithPlayer(a2);
}
void Sheep::handleEntityEvent(int8_t event) {
	if(event == 10) {
		this->field_C88 = 40;
	} else {
		Mob::handleEntityEvent(event);
	}
}
int32_t Sheep::getEntityTypeId() const {
	return 13;
}
void Sheep::readAdditionalSaveData(CompoundTag* a2) {
	Animal::readAdditionalSaveData(a2);
	this->setSheared(a2->getByte("Sheared") != 0);
	this->setColor(a2->getByte("Color"));
}
void Sheep::addAdditonalSaveData(CompoundTag* a2) {
	Animal::addAdditonalSaveData(a2);
	a2->putByte("Sheared", this->isSheared());
	a2->putByte("Color", this->getColor());
}

static std::string _textures[] = {"mob/sheep_0.png", "mob/sheep_1.png", "mob/sheep_2.png", "mob/sheep_3.png", "mob/sheep_4.png", "mob/sheep_5.png", "mob/sheep_6.png", "mob/sheep_7.png", "mob/sheep_8.png", "mob/sheep_9.png", "mob/sheep_10.png", "mob/sheep_11.png", "mob/sheep_12.png", "mob/sheep_13.png", "mob/sheep_14.png", "mob/sheep_15.png"};
std::string* Sheep::getTexture() {
	return &_textures[this->getColor()];
}
float Sheep::getBaseSpeed() {
	return 0.25;
}
int32_t Sheep::getMaxHealth() {
	return 8;
}
void Sheep::aiStep() {
	if(this->level->isClientMaybe) {
		if(this->field_C88 > 0) {
			this->field_C88 = this->field_C88 - 1;
		}
	}
	Animal::aiStep();
}
void Sheep::finalizeMobSpawn() {
	this->setColor(Sheep::getSheepColor(&this->random));
	if(this->isBaby()) {
		int32_t v4 = this->getAge() + 1200;
		this->setAge(v4 & (v4 >> 31));
	}
}
void Sheep::ate() {
	this->setSheared(0);
}
int32_t Sheep::getDeathLoot() {
	return Tile::cloth->blockID;
}
void Sheep::dropDeathLoot() {
	if(!this->isSheared()) {
		this->spawnAtLocation(ItemInstance(Tile::cloth->blockID, 1, this->getColor()), 0.0);
	}
}
void Sheep::jumpFromGround() {
	if(this->field_C88 <= 0) {
		Mob::jumpFromGround();
	}
}
void Sheep::newServerAiStep() {
	this->field_C88 = this->eatTileGoal->getEatAnimationTick();
	Mob::newServerAiStep();
}
const char_t* Sheep::getAmbientSound() {
	return "mob.sheep";
}
std::string Sheep::getHurtSound() {
	return "mob.sheep";
}
std::string Sheep::getDeathSound() {
	return "mob.sheep";
}
bool_t Sheep::useNewAi() {
	return 1;
}
bool_t Sheep::shouldHoldGround() {
	return this->field_C88 > 0;
}
Mob* Sheep::getBreedOffspring(Animal* a2) {
	Sheep* s = new Sheep(this->level);
	if((this->level->random.genrand_int32() & 0x8000000) != 0) {
		s->setColor(this->getColor());
	} else {
		s->setColor(((Sheep*)a2)->getColor());
	}
	return s;
}
