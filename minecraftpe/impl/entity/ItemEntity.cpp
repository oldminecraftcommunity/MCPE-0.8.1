#include <entity/ItemEntity.hpp>
#include <entity/Player.hpp>
#include <inventory/Inventory.hpp>
#include <level/Level.hpp>
#include <math/Mth.hpp>
#include <nbt/CompoundTag.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

ItemEntity::ItemEntity(Level* a2)
	: Entity(a2) {
	this->field_130 = 0;
	this->delayBeforePickup = 0;
	this->age = 0;
	this->health = 5;
	this->lifeTime = 6000;
	this->entityRenderId = ITEM_ENTITY;
	this->hoverStart = (Mth::random() * 3.1416) * 2;
	this->setSize(0.25, 0.25);
	this->ridingHeight = this->entityHeight * 0.5;
}
ItemEntity::ItemEntity(Level* a2, float a3, float a4, float z, const ItemInstance& a6)
	: Entity(a2)
	, itemInstance(a6) {
	this->field_130 = 0;
	this->delayBeforePickup = 0;
	this->age = 0;
	this->health = 5;
	this->lifeTime = 6000;
	this->entityRenderId = ITEM_ENTITY;
	this->hoverStart = (float)(Mth::random() * 3.1416) * 2;
	this->setSize(0.25, 0.25);
	this->ridingHeight = this->entityHeight * 0.5;
	this->setPos(a3, a4, z);
	this->yaw = Mth::random() * 360.0;
	this->motionY = 0.2;
	this->motionX = (float)(Mth::random() * 0.2) - 0.1;
	this->field_110 = 0;
	this->motionZ = (float)(Mth::random() * 0.2) - 0.1;
}
bool_t ItemEntity::checkInTile(float x, float y, float z) {
	int32_t xFloor; // r7
	int32_t yFloor; // r6
	int32_t zFloor; // r5
	float xDiff;	// s16
	bool_t xNeg;	// r10
	bool_t zNeg;	// r11
	int32_t zPos;	// r0
	float v15;		// s15
	int32_t v16;	// r7
	float v17;		// s16
	float yDiff;	// s13
	float v19;		// s13
	float zDiff;	// s14
	float v21;		// s15
	bool_t xPos;	// [sp+4h] [bp-44h]
	bool_t yNeg;	// [sp+8h] [bp-40h]
	bool_t yPos;	// [sp+Ch] [bp-3Ch]

	xFloor = Mth::floor(x);
	yFloor = Mth::floor(y);
	zFloor = Mth::floor(z);
	if(Tile::solid[this->level->getTile(xFloor, yFloor, zFloor)]) {
		xDiff = x - (float)xFloor;
		xNeg = Tile::solid[this->level->getTile(xFloor - 1, yFloor, zFloor)];
		xPos = Tile::solid[this->level->getTile(xFloor + 1, yFloor, zFloor)];
		yNeg = Tile::solid[this->level->getTile(xFloor, yFloor - 1, zFloor)];
		yPos = Tile::solid[this->level->getTile(xFloor, yFloor + 1, zFloor)];
		zNeg = Tile::solid[this->level->getTile(xFloor, yFloor, zFloor - 1)];
		zPos = this->level->getTile(xFloor, yFloor, zFloor + 1);
		if(xNeg || xDiff >= 9999.0) {
			v15 = 9999.0;
			v16 = -1;
		} else {
			v15 = xDiff;
			v16 = 0;
		}
		if(!xPos) {
			v17 = 1.0 - xDiff;
			if(v17 < v15) {
				v15 = v17;
				v16 = 1;
			}
		}
		yDiff = y - (float)yFloor;
		if(!yNeg && yDiff < v15) {
			v15 = y - (float)yFloor;
			v16 = 2;
		}
		if(!yPos) {
			v19 = 1.0 - yDiff;
			if(v19 < v15) {
				v15 = v19;
				v16 = 3;
			}
		}
		zDiff = z - (float)zFloor;
		if(!zNeg && zDiff < v15) {
			v15 = z - (float)zFloor;
			v16 = 4;
		}
		if(!Tile::solid[zPos] && (float)(1.0 - zDiff) < v15) {
			v16 = 5;
		}
		v21 = (float)(Entity::sharedRandom.nextFloat() * 0.2) + 0.1;
		if(!v16) {
			v21 = -v21;
LABEL_24:
			this->motionX = v21;
			return 0;
		}
		if(v16 == 1) {
			goto LABEL_24;
		}
		if(v16 == 2) {
			v21 = -v21;
		} else if(v16 != 3) {
			if(v16 == 4) {
				v21 = -v21;
			} else if(v16 != 5) {
				return 0;
			}
			this->motionZ = v21;
			return 0;
		}
		this->motionY = v21;
	}
	return 0;
}
int32_t ItemEntity::getLifeTime() {
	return this->lifeTime;
}
ItemEntity::~ItemEntity() {
}
void ItemEntity::tick() {
	float motionY;		   // s14
	int delayBeforePickup; // r3
	float posY;			   // r8
	float posZ;			   // r7
	bool v6;			   // cc
	float posX;			   // r0
	Level* level;		   // r5
	int v9;				   // r9
	int v10;			   // r8
	int v11;			   // r0
	int v17;			   // r0
	Level* v18;			   // r5
	int v19;			   // r9
	int v20;			   // r8
	int v21;			   // r0
	int v22;			   // r0
	float v23;			   // s15
	bool_t onGround;	   // r3
	float v25;			   // s16
	float v26;			   // s15
	int lifeTime;		   // r2
	int v28;			   // r3

	Entity::tick();
	motionY = this->motionY;
	delayBeforePickup = this->delayBeforePickup;
	posY = this->posY;
	posZ = this->posZ;
	v6 = delayBeforePickup <= 0;
	posX = this->posX;
	if(delayBeforePickup > 0) {
		--delayBeforePickup;
	}
	this->prevY = posY;
	if(!v6) {
		this->delayBeforePickup = delayBeforePickup;
	}
	this->prevZ = posZ;
	this->prevX = posX;
	level = this->level;
	this->motionY = motionY - 0.04;
	v9 = Mth::floor(posX);
	v10 = Mth::floor(posY);
	v11 = Mth::floor(posZ);
	if(Material::lava == level->getMaterial(v9, v10, v11)) {
		this->motionY = 0.2;
		this->motionX = (float)(Entity::sharedRandom.nextFloat() - Entity::sharedRandom.nextFloat()) * 0.2;
		this->motionZ = (float)(Entity::sharedRandom.nextFloat() - Entity::sharedRandom.nextFloat()) * 0.2;
		this->level->playSound(this, "random.fizz", 0.4, (float)(Entity::sharedRandom.nextFloat() * 0.4) + 2.0);
	}
	this->checkInTile(this->posX, this->posY, this->posZ);
	this->move(this->motionX, this->motionY, this->motionZ);
	if(this->onGround) {
		v17 = Mth::floor(this->posX);
		v18 = this->level;
		v19 = v17;
		v20 = Mth::floor(this->boundingBox.minY);
		v21 = Mth::floor(this->posZ);
		v22 = v18->getTile(v19, v20 - 1, v21);
		if(v22 <= 0) {
			v23 = 0.588;
		} else {
			v23 = Tile::tiles[v22]->slipperiness * 0.98;
		}
	} else {
		v23 = 0.98;
	}
	onGround = this->onGround;
	this->motionX = this->motionX * v23;
	v25 = this->motionY * 0.98;
	v26 = this->motionZ * v23;
	this->motionY = v25;
	this->motionZ = v26;
	if(onGround) {
		this->motionY = v25 * -0.5;
	}
	lifeTime = this->lifeTime;
	++this->age;
	v28 = this->field_130 + 1;
	this->field_130 = v28;
	if(v28 >= lifeTime) {
		this->remove();
	}
}
bool_t ItemEntity::isInWater() {
	return this->level->checkAndHandleWater(this->boundingBox, Material::water, this);
}
void ItemEntity::playerTouch(Player* a2) {
	int32_t count; // r7

	if(!this->level->isClientMaybe) {
		count = this->itemInstance.count;
		if(!this->delayBeforePickup && a2->isAlive()) {
			if(a2->inventory->add(&this->itemInstance)) {
				this->level->playSound(this, "random.pop", 0.3, (float)((float)((float)(Entity::sharedRandom.nextFloat() - Entity::sharedRandom.nextFloat()) * 0.7) + 1.0) * 2);
				a2->take(this, count);
				this->remove();
			}
		}
	}
}
bool_t ItemEntity::hurt(Entity* a2, int32_t a3) {
	int32_t v5; // r2

	this->markHurt();
	v5 = this->health - a3;
	this->health = v5;
	if(v5 <= 0) {
		this->remove();
	}
	return 0;
}
int32_t ItemEntity::getEntityTypeId() const {
	return 64;
}
bool_t ItemEntity::isItemEntity() {
	return 1;
}
void ItemEntity::burn(int32_t a2) {
	this->hurt(0, a2);
}
void ItemEntity::readAdditionalSaveData(CompoundTag* a2) {
	this->health = a2->getShort("Health");
	this->field_130 = a2->getShort("Age");
	CompoundTag* item = a2->getCompound("Item");
	this->itemInstance.load(item);
}
void ItemEntity::addAdditonalSaveData(CompoundTag* a2) {
	a2->putShort("Health", this->health);
	a2->putShort("Age", this->field_130);
	CompoundTag* ct = new CompoundTag();
	this->itemInstance.save(ct);
	a2->put("Item", ct);
}
