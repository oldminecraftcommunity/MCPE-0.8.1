#include <entity/HangingEntity.hpp>
#include <entity/Player.hpp>
#include <inventory/Inventory.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <math/Direction.hpp>
#include <math/Mth.hpp>
#include <nbt/CompoundTag.hpp>
#include <tile/material/Material.hpp>

HangingEntity::HangingEntity(Level* a2)
	: Entity(a2) {
	this->init();
}
HangingEntity::HangingEntity(Level* a2, int32_t x, int32_t y, int32_t z, int32_t)
	: Entity(a2) {
	this->tileX = x;
	this->tileY = y;
	this->tileZ = z;
	this->init();
}
void HangingEntity::init() {
	this->ridingHeight = 0;
	this->setSize(0.5, 0.5);
	this->direction = 0;
	this->surviveTicker = 0;
}
float HangingEntity::offs(int32_t a2) {
	if(a2 == 32 || a2 == 64) return 0.5;
	return 0;
}
void HangingEntity::setDir(int32_t direction) {
	float v5;		 // s15
	int32_t width;	 // s22
	float height;	 // s21
	int32_t width2;	 // r0
	float v9;		 // s22
	float v10;		 // s20
	float v11;		 // s15
	float v12;		 // s22
	float v13;		 // s21
	float v14;		 // s20
	float v15;		 // s17
	float v16;		 // s19
	float v17;		 // s16
	int32_t v18;	 // r0
	int32_t v19;	 // r0
	int32_t v20;	 // r0
	int32_t v21;	 // r0
	int32_t height2; // r0
	float v23;		 // s19

	this->direction = direction;
	v5 = (float)(90 * direction);
	this->yaw = v5;
	this->prevYaw = v5;
	width = this->getWidth();
	height = (float)this->getHeight();
	width2 = this->getWidth();
	if(direction == 2 || !direction) {
		v10 = 2.0;
		v9 = (float)width;
		v11 = (float)(90 * Direction::DIRECTION_OPPOSITE[direction]);
		this->prevYaw = v11;
		this->yaw = v11;
	} else {
		v9 = 2.0;
		v10 = (float)width2;
	}
	v12 = v9 * 0.03125;
	v13 = height * 0.03125;
	v14 = v10 * 0.03125;
	v15 = (float)this->tileX + 0.5;
	v16 = (float)this->tileY + 0.5;
	v17 = (float)this->tileZ + 0.5;
	if(direction == 2) {
		v17 = v17 - 0.5625;
		v18 = this->getWidth();
		v15 = v15 - this->offs(v18);
	} else if(direction == 1) {
		v15 = v15 - 0.5625;
		v19 = this->getWidth();
		v17 = v17 + this->offs(v19);
	} else if(direction) {
		if(direction == 3) {
			v15 = v15 + 0.5625;
			v21 = this->getWidth();
			v17 = v17 - this->offs(v21);
		}
	} else {
		v17 = v17 + 0.5625;
		v20 = this->getWidth();
		v15 = v15 + this->offs(v20);
	}
	height2 = this->getHeight();
	v23 = v16 + this->offs(height2);
	this->setPos(v15, v23, v17);
	this->boundingBox.minX = (float)(v15 - v12) + 0.03125;
	this->boundingBox.minY = (float)(v23 - v13) + 0.03125;
	this->boundingBox.minZ = (float)(v17 - v14) + 0.03125;
	this->boundingBox.maxX = (float)(v15 + v12) - 0.03125;
	this->boundingBox.maxY = (float)(v23 + v13) - 0.03125;
	this->boundingBox.maxZ = (float)(v17 + v14) - 0.03125;
}
void HangingEntity::setPosition(int32_t x, int32_t y, int32_t z) {
	this->tileX = x;
	this->tileY = y;
	this->tileZ = z;
}

HangingEntity::~HangingEntity() {
}
void HangingEntity::move(float a2, float a3, float a4) {
	if(!this->level->isClientMaybe && !this->isDead && (float)((float)((float)(a3 * a3) + (float)(a2 * a2)) + (float)(a4 * a4)) > 0.0) {
		this->dropItem();
		this->remove();
	}
}
void HangingEntity::tick() {
	int32_t surviveTicker; // r3

	surviveTicker = this->surviveTicker;
	this->surviveTicker = surviveTicker + 1;
	if(surviveTicker == 100 && !this->level->isClientMaybe) {
		this->surviveTicker = this->level->isClientMaybe;
		if(!this->isDead && !this->survives()) {
			this->remove();
			this->dropItem();
		}
	}
}
float HangingEntity::getBrightness(float a2) {
	int32_t x; // r6
	int32_t z; // r5
	int32_t y; // r0

	x = Mth::floor(this->posX);
	z = Mth::floor(this->posZ);
	if(!this->level->hasChunkAt(x, 0, z)) {
		return 0.0;
	}
	y = Mth::floor(this->posY);
	return this->level->getBrightness(x, y, z);
}
bool_t HangingEntity::interactWithPlayer(Player* a2) {
	Level* level;		  // r3
	Inventory* inventory; // r0

	if(this->isDead) {
		return 0;
	}
	level = this->level;
	if(level->isClientMaybe) {
		return 0;
	}
	if(a2) {
		inventory = a2->inventory;
		if(inventory) {
			if(inventory->getSelected() && Item::bow == a2->inventory->getSelected()->itemClass && Item::bow) {
				return 0;
			}
		}
	}
	this->remove();
	this->markHurt();
	if(a2) {
		if(!a2->abilities.instabuild) {
			this->dropItem();
		}
	}
	return 1;
}
void HangingEntity::push(float x, float y, float z) {
	if(!this->level->isClientMaybe && !this->isDead && (float)((float)((float)(y * y) + (float)(x * x)) + (float)(z * z)) > 0.0) {
		this->dropItem();
		this->remove();
	}
}
bool_t HangingEntity::isPickable() {
	return 1;
}
bool_t HangingEntity::hurt(Entity* a2, int32_t a3) {
	Player* v5; // r0

	if(!this->isDead && !this->level->isClientMaybe) {
		this->remove();
		this->markHurt();
		v5 = Player::asPlayer(a2);
		if(!v5 || !v5->abilities.instabuild) {
			this->dropItem();
		}
	}
	return 1;
}
bool_t HangingEntity::isHangingEntity() {
	return 1;
}
void HangingEntity::readAdditionalSaveData(CompoundTag* a2) {
	if(!a2->contains("Direction")) {
		int32_t b = a2->getByte("Dir");
		switch(b) {
			case 0:
				this->direction = 2;
				break;
			case 1:
				this->direction = 1;
				break;
			case 2:
				this->direction = 0;
				break;
			case 3:
				this->direction = 3;
				break;
		}
	} else {
		this->direction = a2->getByte("Direction");
	}
	this->tileX = a2->getInt("TileX");
	this->tileY = a2->getInt("TileY");
	this->tileZ = a2->getInt("TileZ");
	this->setDir(this->direction);
}
void HangingEntity::addAdditonalSaveData(CompoundTag* a2) {
	a2->putByte("Direction", this->direction);
	a2->putInt("TileX", this->tileX);
	a2->putInt("TileY", this->tileY);
	a2->putInt("TileZ", this->tileZ);
	switch(this->direction) {
		case 0:
			a2->putByte("Dir", 2);
			break;
		case 1:
			a2->putByte("Dir", 1);
			break;
		case 2:
			a2->putByte("Dir", 0);
			break;
		case 3:
			a2->putByte("Dir", 3);
			break;
	}
}
bool_t HangingEntity::survives() {
	std::vector<AABB>* cubes = this->level->getCubes(this, this->boundingBox, 0);
	if(cubes->empty()) {
		int32_t widthBlocks = this->getWidth() / 16;
		if(widthBlocks < 1) {
			widthBlocks = 1;
		}
		int32_t widthBlocks2 = widthBlocks;
		int32_t v5 = this->getHeight();
		int32_t tileX = this->tileX;
		int32_t tileZ = this->tileZ;
		int32_t heightBlocks = v5 / 16;
		if(heightBlocks < 1) {
			heightBlocks = 1;
		}
		int32_t heightBlocks2 = heightBlocks;
		if(this->direction == 2) {
			float posX = this->posX;
			int32_t v10 = this->getWidth();
			tileX = Mth::floor(posX - (float)((float)v10 * 0.03125));
		}
		if(this->direction == 1) {
			float posZ = this->posZ;
			int32_t v12 = this->getWidth();
			tileZ = Mth::floor(posZ - (float)((float)v12 * 0.03125));
		}
		if(this->direction == 0) {
			float posX_2 = this->posX;
			int32_t v14 = this->getWidth();
			tileX = Mth::floor(posX_2 - (float)((float)v14 * 0.03125));
		}
		if(this->direction == 3) {
			float v15 = this->posZ;
			int32_t v16 = this->getWidth();
			tileZ = Mth::floor(v15 - (float)((float)v16 * 0.03125));
		}
		float posY = this->posY;
		int32_t off = 0;
		int32_t v19 = this->getHeight();
		int32_t minY = Mth::floor(posY - (float)((float)v19 * 0.03125));
		int32_t y = minY;
		while(1) {
			int32_t direction = this->direction;
			Level* level = this->level;
			Material* v23;
			if(direction != 2 && direction) {
				v23 = level->getMaterial(this->tileX, y, off + tileZ);
			} else {
				v23 = level->getMaterial(off + tileX, y, this->tileZ);
			}
			if(!v23->isSolid()) {
				break;
			}
			if(++y - minY >= heightBlocks2) {
				for(auto&& e: std::vector<Entity*>(*this->level->getEntities(this, this->boundingBox))) {
					if(e->isHangingEntity()) {
						return 0;
					}
				}

				if(++off >= widthBlocks2) return 1;

				y = minY; //goto LABEL_32
				continue;
			}
		}
	}
	return 0;
}
