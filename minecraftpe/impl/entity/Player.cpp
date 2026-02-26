#include <entity/Player.hpp>
#include <entity/ItemEntity.hpp>
#include <inventory/BaseContainerMenu.hpp>
#include <inventory/Inventory.hpp>
#include <item/ArmorItem.hpp>
#include <level/Level.hpp>
#include <level/dimension/Dimension.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <tile/BedTile.hpp>
#include <nbt/CompoundTag.hpp>
#include <nbt/ListTag.hpp>

Player::Player(Level* a2, bool_t a3)
	: Mob(a2) {
	this->field_C6C = 0;
	this->abilities.invulnerable = 0;
	this->abilities.flying = 0;
	this->abilities.mayfly = 0;
	this->abilities.instabuild = 0;
	this->currentContainer = 0;
	this->field_CA8 = 0;
	this->field_CAC = -9999;
	this->field_CB4 = 0;
	this->bedPosition.x = 0;
	this->bedPosition.y = 0;
	this->bedPosition.z = 0;
	this->field_CC4 = 0.0;
	this->field_CC8 = 0;
	this->field_CCC = 0.0;
	this->field_CD0 = 0;
	this->useItemDuration = 0;
	this->sleepingCounter = 0;
	this->spawn.y = -1;
	this->spawn.x = 0;
	this->spawn.z = 0;
	this->hasRespawnPos = 0;
	this->sleeping = 0;
	this->field_D4E = 0;
	this->isDestroying = 0;
	this->field_106 = 0;
	this->_init();
	this->entityRenderId = PLAYER;
	this->field_BEE = 0;
	this->inventory = new Inventory(this, a3);
	this->ridingHeight = 1.62;
	TilePos res = level->getSharedSpawnPos();
	this->moveTo((float)res.x + 0.5, (float)(res.y + 1), (float)res.z + 0.5, 0.0, 0.0);
	this->health = 20;
	this->field_B84 = "humanoid";
	this->field_B9C = 180.0;
	this->field_E8 = 20;
	this->skin = "mob/char.png";
	this->synchedEntityData.define<int8_t>(16, 0);
	this->synchedEntityData.define<Pos>(17, {0, 0, 0});
}
void Player::_init() {
	this->field_C78 = 0;
	this->field_C74 = 0;
	this->field_B68 = 0;
	this->field_B6C = 0;
	this->score = 0;
}
void Player::animateRespawn(Player*, Level*) {
}
Player* Player::asPlayer(Entity* a2) {
	if(Player::isPlayer(a2)) {
		return (Player*)a2;
	}
	return 0;
}
void Player::attack(Entity* a2) {
	int32_t dmg;	   // r2
	ItemInstance* sel; // r6

	dmg = this->inventory->getAttackDamage(a2);
	if(dmg > 0) {
		a2->hurt(this, dmg);
		sel = this->inventory->getSelected();
		if(sel) {
			if(a2->isMob() && !this->abilities.instabuild) {
				sel->hurtEnemy((Mob*)a2, this);
				if(sel->count <= 0) {
					this->inventory->clearSlot(this->inventory->selectedSlot);
				}
			}
		}
	}
}
bool_t Player::canDestroy(Tile* a2) {
	return this->inventory->canDestroy(a2);
}
bool_t Player::canUseCarriedItemWhileMoving() {
	ItemInstance* res = this->getCarriedItem();
	if(res) {
		if(Item::bow == res->itemClass && Item::bow) {
			return 1;
		}
		return res->itemClass->isFood();
	}
	return 0;
}
bool_t Player::checkBed() {
	return this->level->getTile(this->bedPosition.x, this->bedPosition.y, this->bedPosition.z) == Tile::bed->blockID;
}
void Player::findStandUpPosition(Entity* a2) {
	int32_t v4;	  // r6
	float v5;	  // s17
	float v6;	  // s15
	float maxY;	  // s14
	float maxX;	  // s13
	float minX;	  // s10
	Level* level; // r1
	float posX;	  // s22
	float posZ;	  // s21
	float v13;	  // s12
	float v14;	  // s15
	float maxZ;	  // s14
	int32_t v18;  // s22
	int32_t v19;  // s21
	float posY;	  // s15
	int32_t v22;  // r5
	float v23;	  // s16

	AABB v25{0, 0, 0, 1, 1, 1};
	v4 = 3;
	v5 = -1.5;
	do {
		v22 = 3;
		v23 = -1.5;
		do {
			if(v5 != 0.0 || v23 != 0.0) {
				v6 = this->ridingHeight + 1.0;
				maxY = this->boundingBox.maxY;
				maxX = this->boundingBox.maxX;
				minX = this->boundingBox.minX;
				level = this->level;
				posX = this->posX;
				posZ = this->posZ;
				v13 = v23 + this->boundingBox.minZ;
				v14 = v6 + maxY;
				maxZ = this->boundingBox.maxZ;
				std::vector<AABB> v24 = level->getTileCubes({minX + v5, v6 + this->boundingBox.minY, v13, v5 + maxX, v14, v23 + maxZ});
				if(v24.begin() == v24.end()) {
					v18 = (int32_t)(float)(posX + v5);
					v19 = (int32_t)(float)(posZ + v23);
					posY = this->posY;
					if(this->level->isTopSolidBlocking(v18, (int32_t)this->posY, v19)) {
						this->teleportTo(v5 + this->posX, posY + 1.0, v23 + this->posZ);
						return;
					}
					if(!this->level->isTopSolidBlocking(v18, (int32_t)posY - 1, v19)) {
						this->level->getMaterial(v18, (int32_t)this->posY - 1, v19);
					}
				}
			}
			--v22;
			v23 = v23 + 1.5;
		} while(v22);
		--v4;
		v5 = v5 + 1.5;
	} while(v4);
	a2->positionRider(1);
}
ItemInstance* Player::getArmor(int32_t a2) {
	ItemInstance* v2; // r4

	if((uint32_t)a2 > 3) {
		return 0;
	}
	v2 = &this->armorSlots[a2];
	if(v2->isNull()) {
		return 0;
	}
	return v2;
}
int32_t Player::getArmorTypeHash() {
	int32_t id; // r5
	int32_t v3; // r5
	int32_t v4; // r5

	id = this->armorSlots[0].getId();
	v3 = id + (this->armorSlots[1].getId() << 8);
	v4 = v3 + (this->armorSlots[2].getId() << 16);
	return v4 + (this->armorSlots[3].getId() << 24);
}
float Player::getDestroySpeed(Tile* a2) {
	return this->inventory->getDestroySpeed(a2);
}
TilePos Player::getRespawnPosition() {
	return {this->spawn.x, this->spawn.y, this->spawn.z};
}
int32_t Player::getScore() {
	return this->score;
}
ItemInstance* Player::getSelectedItem() {
	return this->inventory->getSelected();
}
float Player::getSleepRotation() {
	int32_t v2; // r0

	if(!this->isSleeping()) {
		return 0.0;
	}
	v2 = this->level->getData(this->bedPosition.x, this->bedPosition.y, this->bedPosition.z) & 3;
	switch(v2) {
		case 2:
			return 270.0;
		case 3:
			return 180.0;
		case 1:
			return 0.0;
	}
	return 90.0;
}
int32_t Player::getTicksUsingItem() {
	if(this->isUsingItem()) {
		return this->item.getMaxUseDuration() - this->useItemDuration;
	}
	return 0;
}
ItemInstance* Player::getUseItem() {
	return &this->item;
}
bool_t Player::hasRespawnPosition() {
	return this->hasRespawnPos;
}
void Player::interact(Entity* a2) {
	ItemInstance* sel; // r6

	if(!a2->interactWithPlayer(this)) {
		sel = this->inventory->getSelected();
		if(sel) {
			if(a2->isMob()) {
				sel->interactEnemy((Mob*)a2, this);
				if(sel->count <= 0) {
					this->inventory->clearSlot(this->inventory->selectedSlot);
				}
			}
		}
	}
}
bool_t Player::isHurt() {
	return this->health > 0 && this->health < this->getMaxHealth();
}
bool_t Player::isPlayer(Entity* e) {
	if(e) return e->isPlayer();
	return 0;
}
bool_t Player::isSleepingLongEnough() {
	if(this->isSleeping()) {
		return this->sleepingCounter > 99;
	}
	return 0;
}
bool_t Player::isUsingItem() {
	return !this->item.isNull();
}
void Player::reallyDrop(struct ItemEntity* a2) {
	this->level->addEntity(a2);
}
void Player::releaseUsingItem() {
	if(!this->item.isNull()) {
		this->item.releaseUsing(this->level, this, this->useItemDuration);
	}
	this->stopUsingItem();
}
void Player::respawn() {
}
void Player::setAllPlayersSleeping() {
	this->sleepingCounter = 0;
	this->field_D4E = 1;
}
void Player::setArmor(int32_t a2, const ItemInstance* a3) {
	if((uint32_t)a2 <= 3) {
		if(a3) {
			this->armorSlots[a2] = *a3;
		} else {
			this->armorSlots[a2].setNull();
		}
	}
}
void Player::setBedOffset(int32_t a2) {
	float v4; // r3
	float v5; // r2

	this->field_CC4 = 0.0;
	this->field_CCC = 0.0;
	switch(a2) {
		case 0:
			v4 = -1.8;
			goto LABEL_4;
		case 1:
			v5 = 1.8;
			goto LABEL_7;
		case 2:
			v4 = 1.8;
LABEL_4:
			this->field_CCC = v4;
			return;
		case 3:
			v5 = -1.8;
LABEL_7:
			this->field_CC4 = v5;
			break;
		default:
			return;
	}
}
void Player::setDefaultHeadHeight() {
	this->ridingHeight = 1.62;
}
void Player::setRespawnPosition(const struct Pos& a2) {
	this->hasRespawnPos = a2.y >= 0;
	this->spawn = a2;
}
void Player::spawnEatParticles(const ItemInstance* a2, int32_t a3) {
	Level* level; // r5
	float v8;	  // s22
	float v9;	  // s23
	float v10;	  // s17
	float v11;	  // r0
	float v12;	  // s22
	float v13;	  // s15
	float v14;	  // s17
	float v15;	  // s14
	float v16;	  // r0
	float v17;	  // s17
	float v18;	  // s15
	float posX;	  // s22
	float posY;	  // s17
	float v22;	  // s14
	float v23;	  // s13
	Level* v24;	  // r0
	float v25;	  // s15
	float v26;	  // s13
	int32_t v27;  // r6
	Level* v28;	  // r6

	if(a2->getUseAnimation() == 2) {
		this->level->playSound(this, "random.drink", 0.5, (float)(level->random.nextFloat() * 0.1) + 0.9);
	} else {
		if(a2->getUseAnimation() != 1) {
			return;
		}
		v27 = 0;
		while(v27 < a3) {
			++v27;
			v8 = -(float)(this->yaw * 3.1416);
			v9 = (float) - (float)(this->pitch * 3.1416) / 180.0;
			v10 = this->random.nextFloat() - 0.5;
			v11 = Mth::random();
			v12 = v8 / 180.0;
			v13 = (float)(v11 * 0.1) + 0.1;
			v14 = v10 * 0.1;
			if(v14 == 0.0) {
				v14 = 0.0;
			}
			if(v13 == 0.0) {
				v13 = 0.0;
			}

			Vec3 a6{v14, v13, 0.0f};
			a6.xRot(v9);
			a6.yRot(v12);
			v15 = this->random.nextFloat();
			v16 = this->random.nextFloat();
			v17 = (float)(v15 - 0.5) * 0.3;
			if(v17 == 0.0) {
				v17 = 0.0;
			}
			v18 = (float) - (float)(v16 * 0.6) - 0.3;
			if(v18 == 0.0) {
				v18 = 0.0;
			}
			Vec3 vec{v17, v18, 0.6};
			vec.xRot(v9);
			vec.yRot(v12);
			posX = this->posX;
			posY = this->posY;
			v22 = posX + vec.x;
			if((float)(posX + vec.x) == 0.0) {
				v22 = 0.0;
			}
			vec.x = v22;
			v23 = this->getHeadHeight();
			v24 = this->level;
			v25 = (float)(posY + v23) + vec.y;
			v26 = vec.z + this->posZ;
			if(v25 == 0.0) {
				v25 = 0.0;
			}
			vec.y = v25;
			if(v26 == 0.0) {
				v26 = 0.0;
			}
			vec.z = v26;
			v24->addParticle(PT_BREAKING_ITEM_1, v22, v25, v26, a6.x, a6.y + 0.05, a6.z, a2->itemClass->itemID);
		}
		v28 = this->level;
		v28->playSound((Entity*)this, "random.eat", (float)((float)(this->random.genrand_int32() & 1) * 0.5) + 0.5, (float)((float)(this->random.nextFloat() - this->random.nextFloat()) * 0.2) + 1.0);
	}
}
void Player::startUsingItem(ItemInstance a2, int32_t a3) {
	if(!(a2 == this->item)) {
		this->item = a2;
		this->useItemDuration = a3;
		if(!this->level->isClientMaybe) {
			this->setSharedFlag(4, 1);
		}
	}
}
void Player::stopUsingItem() {
	if(this->getCarriedItem()) {
		ItemInstance* v3 = this->getCarriedItem();
		if(v3) {
			if(this->item.itemClass == v3->itemClass) {
				if(this->item.itemClass) {
					this->getCarriedItem()->setAuxValue(this->item.getAuxValue());
				}
			}
		}
	}
	this->item.setNull();
	this->useItemDuration = 0;
	if(!this->level->isClientMaybe) {
		this->setSharedFlag(4, this->level->isClientMaybe);
	}
}
void Player::tileEntityDestroyed(int32_t a2) {
	if(this->currentContainer) {
		if(this->currentContainer->tileEntityDestroyedIsInvalid(a2)) {
			this->closeContainer();
		}
	}
}
void Player::touch(Entity* a2) {
	a2->playerTouch(this);
}

Player::~Player() {
	if(this->inventory) delete this->inventory;
}
void Player::reset() {
	Mob::reset();
	this->_init();
}
void Player::remove() {
	this->field_107 = 1;
	Entity::remove();
}
void Player::tick() {
	int32_t v3;				 // r5
	int32_t y;				 // r1
	int32_t z;				 // r2
	int16_t sleepingCounter; // r3
	int16_t v8;				 // r3
	Level* level;			 // r3
	int16_t v11;			 // r3
	int32_t v13;			 // [sp+0h] [bp-20h] BYREF

	v13 = 16;
	v3 = (this->synchedEntityData.getByte(16) >> 1) & 1; //TODO check

	if(v3 != this->isSleeping()) {
		if(this->isSleeping()) {
			this->stopSleepInBed(1, 1, 1);
		} else {
			Pos v14 = this->synchedEntityData.getPos(17);
			y = v14.y;
			z = v14.z;
			this->bedPosition.x = v14.x;
			this->bedPosition.y = y;
			this->bedPosition.z = z;
			this->startSleepInBed(this->bedPosition.x, this->bedPosition.y, this->bedPosition.z);
		}
	}
	sleepingCounter = this->sleepingCounter;
	if(this->isSleeping()) {
		v8 = sleepingCounter + 1;
		if(v8 > 100) {
			v8 = 100;
		}
		this->sleepingCounter = v8;
		level = this->level;
		if(!level->isClientMaybe) {
			if(this->checkBed()) {
				if(this->level->isDay()) {
					this->stopSleepInBed(0, 1, 1);
				}
			} else {
				this->stopSleepInBed(1, 1, 0);
			}
		}
	} else if(sleepingCounter <= 0) {
		if(this->isDestroying) {
			this->swing();
		}
	} else {
		v11 = sleepingCounter + 1;
		this->sleepingCounter = v11;
		if(v11 > 109) {
			this->sleepingCounter = 0;
		}
	}
	Mob::tick();
	if(!this->level->isClientMaybe) {
		this->foodData.tick(this);
		if(this->isOnFire()) {
			if(this->level->getLevelData()->getGameType() == 1) {
				this->fire = 1;
			}
		}
	}
}
void Player::rideTick() {
	Level* level;	  // r3
	float yaw;		  // r5
	float pitch;	  // r6
	Entity* ridingAt; // r0

	level = this->level;
	if(!level->isClientMaybe && this->isSneaking()) {
		this->ride(0);
		this->setSneaking(0);
	} else {
		yaw = this->yaw;
		pitch = this->pitch;
		Mob::rideTick();
		this->field_C74 = this->field_C78;
		this->field_C78 = 0.0;
		ridingAt = this->ridingAt;
		if(ridingAt) {
			if(ridingAt->getEntityTypeId() == 12) //Pig
			{
				this->pitch = pitch;
				this->yaw = yaw;
				this->field_124 = ((Mob*)this->ridingAt)->field_124;
			}
		}
	}
}
float Player::getRidingHeight() {
	return this->ridingHeight - 0.5;
}
void Player::ride(Entity* a2) {
	Entity* ridingAt; // r1
	Entity* v5;		  // r3

	ridingAt = this->ridingAt;
	if(!ridingAt || a2) {
		Entity::ride(a2);
	} else {
		this->findStandUpPosition(ridingAt);
		v5 = this->ridingAt;
		if(v5) {
			v5->rider = 0;
		}
		this->ridingAt = 0;
	}
}
bool_t Player::isInWall() {
	return Entity::isInWall();
}
float Player::getHeadHeight() {
	return 0.12;
}
bool_t Player::isShootable() {
	return 1;
}
bool_t Player::isPlayer() {
	return 1;
}
bool_t Player::isCreativeModeAllowed() {
	return 1;
}
bool_t Player::hurt(Entity* a2, int32_t a3) {
	int32_t difficulty; // r3

	if(this->abilities.invulnerable) {
		return 0;
	}
	this->noActionTime = 0;
	if(this->health <= 0) {
		return 0;
	}
	if(this->isSleeping() && !this->level->isClientMaybe) {
		this->stopSleepInBed(1, 1, 0);
	}
	if(a2 && (a2->getCreatureBaseType() == 1 || a2->getEntityTypeId() == 80)) {
		if(a2->isMob() && this->level->adventureSettings.field_3) {
			return 0;
		}
		difficulty = this->level->difficulty;
		switch(difficulty) {
			case 0:
				return 0;
			case 1:
				a3 = a3 / 3 + 1;
				break;
			case 3:
				a3 = 3 * a3 / 2;
				break;
		}
	}
	if(a3) {
		return Mob::hurt(a2, a3);
	}
	return 0;
}
void Player::handleEntityEvent(int8_t evid) {
	if(evid == 9) this->completeUsingItem();
	else Mob::handleEntityEvent(evid);
}
void Player::awardKillScore(Entity*, int32_t a3) {
	this->score += a3;
}
int32_t Player::getEntityTypeId() const {
	return 0;
}
void Player::resetPos(bool_t a2) {
	int32_t v4; // r0

	if(!this->isSleeping()) {
		this->ridingHeight = 1.62;
		this->setSize(0.6, 1.8);
		Entity::resetPos(a2);
	}
	this->field_107 = 0;
	if(a2) {
		v4 = this->getMaxHealth();
		this->deathTime = 0;
		this->sleeping = 0;
		this->health = v4;
	}
}
void Player::readAdditionalSaveData(CompoundTag* a2) {
	Mob::readAdditionalSaveData(a2);
	if(a2->contains("Inventory", 9)) {
		this->inventory->load(a2->getList("Inventory"));
	}

	if(a2->contains("Armor", 9)) {
		//Armor string
		ListTag* v10 = a2->getList("Armor");
		if(v10) {
			int32_t v12 = 0;
			int32_t v13 = v10->value.size();
			if(v13 >= 4) v13 = 4;
			while(v12 < v13) {
				CompoundTag* v15;
				if(v12 >= v10->value.size()) {
					v15 = 0;
					v10->field_0 |= 1;
				} else {
					v15 = (CompoundTag*)v10->value[v12];
				}
				if(v15->getId() == 10) {
					this->armorSlots[v12].load(v15);
				}
				++v12;
			}
		}
		//TODO armor string is removed only here, was inlined?
	}

	this->dimension = a2->getInt("Dimension");
	bool_t v17;
	if(a2->contains("Sleeping")) {
		if(a2->contains("SleepTimer")) {
			if(a2->contains("BedPositionX")) {
				if(a2->contains("BedPositionY")) {
					v17 = a2->contains("BedPositionZ");
				} else {
					v17 = 0;
				}
			} else {
				v17 = 0;
			}
			goto LABEL_25;
		}
	}
	v17 = 0;
LABEL_25:
	if(v17) {
		this->sleeping = a2->getByte("Sleeping") != 0;
		this->sleepingCounter = a2->getShort("SleepTimer");
		this->bedPosition = {a2->getInt("BedPositionX"), a2->getInt("BedPositionY"), a2->getInt("BedPositionZ")};
	} else {
		this->sleeping = 0;
		this->bedPosition = {0, 0, 0};
	}

	if(this->sleeping) {
		this->sleeping = 0;
		this->startSleepInBed(this->bedPosition.x, this->bedPosition.y, this->bedPosition.z);
		this->synchedEntityData.setFlag<char>(16, 1);
	} else {
		this->stopSleepInBed(1, 1, 0);
		this->synchedEntityData.setFlag<char>(16, 1);
	}
	this->synchedEntityData.set<Pos>(17, this->bedPosition);
	bool_t v25 = 0;
	if(a2->contains("SpawnX")) {
		if(a2->contains("SpawnY")) {
			v25 = a2->contains("SpawnZ");
		} else {
			v25 = 0;
		}
	} else {
		v25 = 0;
	}

	if(v25) {
		this->spawn = {a2->getInt("SpawnX"), a2->getInt("SpawnY"), a2->getInt("SpawnZ")};
	}
	this->hasRespawnPos = this->spawn.y >= 0;
	this->abilities.loadSaveData(a2);
}
void Player::addAdditonalSaveData(CompoundTag* a2) {
	Mob::addAdditonalSaveData(a2);
	a2->put("Inventory", this->inventory->save(new ListTag()));
	ListTag* v10 = new ListTag();
	for(int32_t i = 0; i != 4; ++i) {
		CompoundTag* v11 = new CompoundTag();
		this->armorSlots[i].save(v11);
		v10->add(v11);
	}
	a2->put("Armor", v10);
	a2->putInt("Dimension", this->dimension);
	a2->putBoolean("Sleeping", this->isSleeping());
	a2->putShort("SleepTimer", this->sleepingCounter);
	a2->putInt("BedPositionX", this->bedPosition.x);
	a2->putInt("BedPositionY", this->bedPosition.y);
	a2->putInt("BedPositionZ", this->bedPosition.z);
	a2->putInt("SpawnX", this->spawn.x);
	a2->putInt("SpawnY", this->spawn.y);
	a2->putInt("SpawnZ", this->spawn.z);
	this->abilities.addSaveData(a2);
}
void Player::die(Entity* a2) {
	Level* level;	  // r3
	int32_t v5;		  // r5
	ItemInstance* v6; // r0
	float v7;		  // s17

	Mob::die(a2);
	this->setSize(0.2, 0.2);
	this->setPos(this->posX, this->posY, this->posZ);
	level = this->level;
	this->motionY = 0.1;
	v5 = 0;
	this->inventory->dropAll(level->isClientMaybe);
	do {
		if(!this->level->isClientMaybe && ItemInstance::isArmorItem(&this->armorSlots[v5])) {
			this->drop(&this->armorSlots[v5], 1);
		}
		v6 = &this->armorSlots[v5++];
		v6->setNull();
	} while(v5 != 4);
	if(a2) {
		v7 = (float)((float)(this->field_14C + this->yaw) * 3.1416) / 180.0;
		this->motionX = -(float)(Mth::cos(v7) * 0.1);
		this->motionZ = -(float)(Mth::sin(v7) * 0.1);
	} else {
		this->motionZ = 0.0;
		this->motionX = 0.0;
	}
	this->ridingHeight = 0.1;
}
bool_t Player::isSleeping() {
	return this->sleeping;
}
float Player::getBaseSpeed() {
	return 0.1;
}
int32_t Player::getMaxHealth() {
	return 20;
}
int32_t Player::getArmorValue() {
	int32_t value = 0;
	for(int32_t i = 0; i != 4; ++i) {
		if(ItemInstance::isArmorItem(&this->armorSlots[i])) {
			value += ((ArmorItem*)this->armorSlots[i].itemClass)->defenseForSlot;
		}
	}
	return value;
}
void Player::travel(float a2, float a3) {
	if(this->abilities.flying) {
		float motionY = this->motionY;
		float jumpMovementFactor = this->jumpMovementFactor;
		this->jumpMovementFactor = 0.05;
		Mob::travel(a2, a3);
		this->motionY = motionY * 0.6;
		this->jumpMovementFactor = jumpMovementFactor;
	} else {
		Mob::travel(a2, a3);
	}
}
void Player::aiStep() {
	float v2;		// s16
	double v3;		// r0
	int32_t health; // r3
	float v6;		// s14
	int32_t v7;		// r3
	float maxY;		// s14
	float minZ;		// s11
	float maxX;		// s12
	float minX;		// s10
	Level* level;	// r0
	int32_t v13;	// r5
	float v14;		// s13
	float maxZ;		// s14
	Entity* v17;	// r1
	float v18;		// s14

	if(!this->level->difficulty && this->health <= 19 && !(this->field_D8 % 240)) {
		this->heal(1);
	}
	this->field_C74 = this->field_C78;
	v2 = sqrt((float)((float)(this->motionZ * this->motionZ) + (float)(this->motionX * this->motionX)));
	v3 = atan((float) - (float)(this->motionY * 0.2));
	onGround = this->onGround;
	health = this->health;
	if(v2 > 0.1) {
		v2 = 0.1;
	}
	this->onGround;
	if(this->onGround) {
		if(health <= 0) {
			v2 = 0.0;
		}
		goto LABEL_12;
	}
	if(health <= 0) {
		v2 = 0.0;
LABEL_12:
		v6 = 0.0;
		goto LABEL_13;
	}
	v18 = v3;
	v2 = 0.0;
	v6 = v18 * 15.0;
LABEL_13:
	this->field_C78 = this->field_C78 + (float)((float)(v2 - this->field_C78) * 0.4);
	v7 = this->health;
	this->field_15C = this->field_15C + (float)((float)(v6 - this->field_15C) * 0.8);
	if(v7 > 0) {
		maxY = this->boundingBox.maxY;
		minZ = this->boundingBox.minZ;
		maxX = this->boundingBox.maxX;
		minX = this->boundingBox.minX;
		level = this->level;
		v13 = 0;
		maxZ = this->boundingBox.maxZ;
		AABB v19{.minX = minX - 1.0f, .minY = this->boundingBox.minY, .minZ = minZ - 1.0f, .maxX = maxX + 1.0f, .maxY = maxY + 0.0f, .maxZ = maxZ + 1.0f}; // [sp+0h] [bp-30h] BYREF

		std::vector<struct Entity*>* ents = level->getEntities(this, v19);
		while(v13 < ents->size()) {
			v17 = ents->at(v13);
			if(!v17->isDead) {
				this->touch(v17);
			}
			++v13;
		}
	}
}
ItemInstance* Player::getCarriedItem() {
	return this->inventory->getSelected();
}
int32_t Player::getUseItemDuration() {
	return this->useItemDuration;
}
bool_t Player::isImmobile() {
	return this->health <= 0 || this->isSleeping();
}
void Player::updateAi() {
	this->updateAttackAnim();
}
float Player::getWalkingSpeedModifier() {
	return 1.0;
}
void Player::hurtArmor(int32_t a2) {
	int32_t v2; // r1
	int32_t v3; // r8
	int32_t i;	// r4

	v2 = a2 / 4;
	if(v2 < 1) {
		v3 = 1;
	} else {
		v3 = v2;
	}
	for(i = 0; i != 4; ++i) {
		if(ItemInstance::isArmorItem(&this->armorSlots[i])) {
			this->armorSlots[i].hurtAndBreak(v3, this);
			if(!this->armorSlots[i].count) {
				this->armorSlots[i].setNull();
			}
		}
	}
}
bool_t Player::hasResource(int32_t a2) {
	return this->inventory->hasResource(a2);
}
void Player::completeUsingItem() {
	ItemInstance* p_item;	// r5
	ItemInstance* selected; // r6
	bool_t v4;				// r7
	ItemInstance* v6;		// r3

	p_item = &this->item;
	if(!this->item.isNull()) {
		this->spawnEatParticles(p_item, 10);
		selected = this->inventory->getSelected();
		if(selected) {
			v4 = ItemInstance::matches(p_item, selected);
		} else {
			v4 = 0;
		}
		ItemInstance v8 = p_item->useTimeDepleted(this->level, this);
		if(v4) {
			v6 = selected;
			*v6 = *p_item;
			if(!selected->count) {
				this->inventory->clearSlot(this->inventory->selectedSlot);
			}
		}
		this->stopUsingItem();
	}
}
void Player::take(Entity*, int32_t) {
}
void Player::drop(const ItemInstance* a2) {
	this->drop(a2, 0);
}
void Player::drop(const ItemInstance* a2, bool_t a3) {
	float v6;		 // s16
	float f;		 // r0
	float v8;		 // s17
	float v9;		 // r0
	float v10;		 // s19
	float v11;		 // s19
	float v12;		 // s16
	float v13;		 // s16
	float v14;		 // s17
	float v15;		 // s18
	float v16;		 // s16
	float v17;		 // s16
	ItemEntity* v18; // r4

	if(a2) {
		if(!a2->isNull()) {
			v16 = this->posY - 0.3;
			v17 = v16 + this->getHeadHeight();
			v18 = new ItemEntity(this->level, this->posX, v17, this->posZ, *a2);
			v18->delayBeforePickup = 40;
			if(a3) {
				v6 = this->random.nextFloat() * 0.5;
				f = this->random.nextFloat();
				v8 = (float)(f * 3.1416) + (float)(f * 3.1416);
				v18->motionX = -(float)(Mth::sin(v8) * v6);
				v9 = Mth::cos(v8);
				v18->motionY = 0.2;
				v18->motionZ = v9 * v6;
			} else {
				v10 = Mth::sin((float)(this->yaw / 180.0) * 3.1416);
				v18->motionX = (float) - (float)(v10 * Mth::cos((float)(this->pitch / 180.0) * 3.1416)) * 0.3;
				v11 = Mth::cos((float)(this->yaw / 180.0) * 3.1416);
				v18->motionZ = (float)(v11 * Mth::cos((float)(this->pitch / 180.0) * 3.1416)) * 0.3;
				v18->motionY = 0.1 - (float)(Mth::sin((float)(this->pitch / 180.0) * 3.1416) * 0.3);
				v12 = this->random.nextFloat() * 3.1416;
				v13 = v12 + v12;
				v14 = this->random.nextFloat() * 0.02;
				v18->motionX = v18->motionX + (float)(Mth::cos(v13) * v14);
				v15 = this->random.nextFloat();
				v18->motionY = v18->motionY + (float)((float)(v15 - this->random.nextFloat()) * 0.1);
				v18->motionZ = v18->motionZ + (float)(Mth::sin(v13) * v14);
			}
			this->reallyDrop(v18);
		}
	}
}
void Player::startCrafting(int32_t, int32_t, int32_t, int32_t) {
}
void Player::startStonecutting(int32_t, int32_t, int32_t) {
}
void Player::startDestroying() {
	this->isDestroying = 1;
}
void Player::stopDestroying() {
	this->isDestroying = 0;
}
void Player::openContainer(ChestTileEntity*) {
}
void Player::openFurnace(FurnaceTileEntity*) {
}
void Player::displayClientMessage(const std::string&) {
}
void Player::animateRespawn() {
}

static float _BED_OFFS_X[] = {0.5f, 0.1f, 0.5f, 0.9f};
static float _BED_OFFS_Z[] = {0.9f, 0.5f, 0.1f, 0.5f};

int32_t Player::startSleepInBed(int32_t x, int32_t y, int32_t z) {
	float v8;	  // s17
	float v9;	  // s18
	Level* level; // r0
	int8_t v12;	  // r0
	float v14;	  // s17
	float v15;	  // s16
	Level* v17;	  // r0
	float v19;	  // s16

	if(!this->level->isClientMaybe) {
		if(this->isSleeping() || !this->isAlive()) {
			return 4;
		}
		v19 = (float)x;
		if(fabsf(this->posX - (float)x) > 3.0) {
			return 3;
		}
		v8 = (float)y;
		if(fabsf(this->posY - (float)y) > 4.0) {
			return 3;
		}
		v9 = (float)z;
		if(fabsf(this->posZ - (float)z) > 3.0) {
			return 3;
		}
		if(this->level->dimensionPtr->isNaturalDimension()) {
			return 1;
		}
		if(this->level->isDay()) {
			return 2;
		}

		std::vector<struct Entity*> v20;																							  // [sp+4h] [bp-4Ch] BYREF
		AABB v21{.minX = v19 - 8.0f, .minY = v8 - 5.0f, .minZ = v9 - 8.0f, .maxX = v19 + 8.0f, .maxY = v8 + 5.0f, .maxZ = v9 + 8.0f}; // [sp+10h] [bp-40h] BYREF
		level = this->level;
		level->getEntitiesOfClass(1, v21, v20);
		if(!v20.empty()) return 5;
	}
	this->setSize(0.2, 0.2);
	this->ridingHeight = 0.2;
	if(this->level->hasChunkAt(x, y, z)) {
		v12 = this->level->getData(x, y, z);
		v14 = _BED_OFFS_X[v12 & 3];
		v15 = _BED_OFFS_Z[v12 & 3];
		this->setBedOffset(v12 & 3);
		this->setPos((float)x + v14, (float)y + 0.9375, (float)z + v15);
	} else {
		this->setPos((float)x + 0.5, (float)y + 0.0625, (float)z + 0.5);
	}
	this->sleeping = 1;
	this->sleepingCounter = 0;
	this->bedPosition = {x, y, z};
	v17 = this->level;
	this->motionY = 0.0;
	this->motionZ = 0.0;
	this->motionX = 0.0;
	if(!v17->isClientMaybe) {
		v17->updateSleepingPlayerList();
	}
	this->synchedEntityData.set<Pos>(17, this->bedPosition);
	this->synchedEntityData.setFlag<char>(16, 1);
	return 0;
}
void Player::stopSleepInBed(bool_t a2, bool_t a3, bool_t a4) {
	int32_t bedPositionX; // r1
	int32_t bedPositionY; // r2
	Level* level;		  // r0
	Level* v12;			  // r0
	int32_t v13;		  // r2
	int32_t v14;		  // r3
	int32_t v15;		  // r1
	Level* v16;			  // r0

	if(this->isSleeping()) {
		this->setSize(0.6, 1.8);
		this->setDefaultHeadHeight();
		level = this->level;
		Pos v17 = this->bedPosition;
		if(level->getTile(bedPositionX, bedPositionY, v17.z) == Tile::bed->blockID) {
			BedTile::setOccupied(this->level, this->bedPosition.x, this->bedPosition.y, this->bedPosition.z, 0);
			if(!BedTile::findStandUpPosition(this->level, this->bedPosition.x, this->bedPosition.y, this->bedPosition.z, 0, v17)) {
				v17 = this->bedPosition;
			}
			this->setPos((float)v17.x + 0.5, (float)((float)v17.y + this->ridingHeight) + 0.1, (float)v17.z + 0.5);
		}
		v12 = this->level;
		this->sleeping = 0;
		if(!v12->isClientMaybe) {
			if(a3) {
				v12->updateSleepingPlayerList();
			}
		}
		if(a2) {
			this->sleepingCounter = 0;
		} else {
			this->sleepingCounter = 100;
		}
		v13 = this->bedPosition.y;
		v14 = this->bedPosition.z;
		v15 = this->bedPosition.x;
		v16 = this->level;
		Pos v18{0, 0, 0};
		BedTile::findStandUpPosition(v16, v15, v13, v14, 0, v18);
		this->setRespawnPosition(v18);
		this->synchedEntityData.clearFlag<int8_t>(16, 1); //char
		this->field_D4E = 0;
	}
}
int32_t Player::getSleepTimer() {
	if(this->field_D4E) return this->sleepingCounter;
	return 0;
}
void Player::openTextEdit(struct TileEntity*) {
}
bool_t Player::isLocalPlayer() {
	return 0;
}
void Player::closeContainer() {
	this->currentContainer = 0;
}
