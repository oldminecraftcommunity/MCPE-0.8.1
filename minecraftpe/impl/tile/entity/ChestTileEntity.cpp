#include <tile/entity/ChestTileEntity.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>
#include <nbt/CompoundTag.hpp>
#include <nbt/ListTag.hpp>
#include <network/packet/EntityDataPacket.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

ChestTileEntity::ChestTileEntity()
	: TileEntity(2)
	, FillingContainer(0x1B, 0, 0, 0) {
	this->field_8C = 0;
	this->field_90 = 0;
	this->pair = 0;
	this->field_84 = 0.0;
	this->field_88 = 0.0;
	this->field_A4 = 0;
	this->isUnpaired = 1;
	this->openedBy = 0;
	this->renderId = TER_CHEST;
}
bool_t ChestTileEntity::_canOpenThis() {
	Tile* v2; // r3

	v2 = Tile::tiles[this->level->getTile(this->posX, this->posY + 1, this->posZ)];
	if(v2 && v2->material->isSolidBlocking()) {
		return this->level->getTileObstructsChests(this->posX, this->posY + 1, this->posZ) ^ 1;
	} else {
		return 1;
	}
}
void ChestTileEntity::_getCenter(float& x, float& y, float& z) {
	ChestTileEntity* pair; // r2
	int32_t posX;		   // r4
	float posZ;			   // s15
	int32_t v7;			   // s14

	y = (float)this->posY;
	pair = this->pair;
	posX = this->posX;
	if(pair) {
		x = (float)(posX + pair->posX) * 0.5;
		posZ = (float)(this->posZ + this->pair->posZ) * 0.5;
	} else {
		v7 = this->posX;
		x = (float)posX;
		posZ = (float)this->posZ;
	}
	z = posZ;
}
bool_t ChestTileEntity::_saveClientSideState(CompoundTag* a2) {
	if(TileEntity::save(a2)) {
		if(this->pair) {
			if(this->isUnpaired) {
				a2->putInt("pairx", this->posX);
				a2->putInt("pairz", this->posZ);
			}
		}
		return 1;
	}
	return 0;
}
void ChestTileEntity::_unpair() {
	this->pair = 0;
	this->isUnpaired = 1;
}
bool_t ChestTileEntity::canOpen() {
	if(this->pair) {
		if(!this->_canOpenThis()) return 0;
		return this->pair->_canOpenThis();
	}
	return this->_canOpenThis();
}
bool_t ChestTileEntity::canPairWith(TileEntity* a2) {
	int32_t d;	// r6
	int32_t v5; // r0

	if(!a2) {
		return 0;
	}
	if(!a2->isType(2)) {
		return 0;
	}
	if(a2->posY != this->posY) {
		return 0;
	}
	if(((ChestTileEntity*)a2)->pair) {
		return 0;
	}
	d = this->getData();
	if(d != a2->getData()) {
		return 0;
	}
	if(a2->posX == this->posX) {
		v5 = d - 2;
	} else {
		v5 = d - 4;
	}
	return (uint32_t)v5 > 1;
}
float ChestTileEntity::getModelOffsetX() {
	ChestTileEntity* pair; // r3
	int32_t posZ;		   // r2
	int32_t posX;		   // r3

	if(!this->isUnpaired) {
		return 0.0;
	}
	pair = this->pair;
	if(this->pairSameXPos) {
		posZ = pair->posZ;
		posX = this->posZ;
	} else {
		posZ = pair->posX;
		posX = this->posX;
	}
	if(posZ >= posX) {
		return 0.5;
	} else {
		return -0.5;
	}
}
void ChestTileEntity::openBy(Player* a2) {
	ChestTileEntity* dis = this;
	while(!dis->isUnpaired) {
		dis = this->pair;
	}
	if(!dis->openedBy) {
		this->field_A8 = 6;
		this->openedBy = a2;
		this->startOpen();
	}
}
void ChestTileEntity::pairWith(ChestTileEntity* a2, bool_t a3) {
	this->pair = a2;
	this->isUnpaired = a3;
	this->pairSameXPos = a2->posX == this->posX;
	if(a3) {
		this->aabb = this->aabb.merge(a2->aabb);
	}
}
void ChestTileEntity::unpair() {
	if(this->pair) {
		this->pair->_unpair();
		this->_unpair();
		this->_resetAABB();
	}
}

ChestTileEntity::~ChestTileEntity() {
}
bool_t ChestTileEntity::shouldSave() {
	return 1;
}
void ChestTileEntity::load(CompoundTag* a2) {
	TileEntity::load(a2);
	this->field_A4 = a2->contains("pairx");
	if(this->field_A4) {
		this->field_9C = a2->getInt("pairx");
		this->field_A0 = a2->getInt("pairz");
	}

	if(a2->contains("Items")) {
		ListTag* v7 = a2->getList("Items");
		for(int32_t i = 0; i < v7->value.size(); ++i) {
			Tag* tg = (Tag*)v7->value[i];
			if(tg->getId() == 10) {
				CompoundTag* v9 = (CompoundTag*)tg;
				int32_t v = (uint8_t)v9->getByte("Slot");
				if(v <= 0x1A) {
					if(!this->items[v]) {
						this->items[v] = new ItemInstance();
					}
					this->items[v]->load(v9);
				}
			}
		}
	}
}
bool_t ChestTileEntity::save(CompoundTag* a2) {
	if(this->_saveClientSideState(a2)) {
		ListTag* v7 = new ListTag();
		for(int32_t i = 0; i != 27; ++i) {
			ItemInstance* v8 = this->items[i];
			if(v8) {
				if(!v8->isNull()) {
					CompoundTag* v9 = new CompoundTag();
					v9->putByte("Slot", i);
					v8->save(v9);
					v7->add(v9);
				}
			}
		}
		a2->put("Items", v7);
		return 1;
	}
	return 0;
}
void ChestTileEntity::tick() {
	TileEntity* te; // r5
	int32_t v3;		// r3
	int32_t v4;		// r3
	int32_t v5;		// r3
	float v6;		// s15
	float v7;		// s19
	float v8;		// s18
	float v9;		// s17
	Level* level;	// r6
	int32_t v12;	// r3
	float v13;		// s15
	float v14;		// s14
	float v15;		// s20
	float v16;		// s19
	float v17;		// s18
	Level* v18;		// r6
	float a2;		// [sp+18h] [bp-38h] BYREF
	float a3;		// [sp+1Ch] [bp-34h] BYREF
	float a4;		// [sp+20h] [bp-30h] BYREF

	if(this->field_A4) {
		te = this->level->getTileEntity(this->field_9C, this->posY, this->field_A0);
		if(te) {
			this->pairWith((ChestTileEntity*)te, 1);
			((ChestTileEntity*)te)->pairWith(this, 0);
			this->field_A4 = 0;
		}
	}
	v3 = this->field_90 + 1;
	this->field_90 = v3;
	if(v3 > 79) {
		this->level->tileEvent(this->posX, this->posY, this->posZ, 1, this->field_8C);
		this->field_90 = 0;
	}
	if(this->openedBy) {
		v4 = this->field_A8 - 1;
		this->field_A8 = v4;
		if(!v4) {
			if(this->level->getLevelData()->getGameType() != 1) {
				this->openedBy->openContainer(this);
			}
			this->openedBy = 0;
			--this->field_8C;
		}
	}
	v5 = this->field_8C;
	v6 = this->field_84;
	this->field_88 = v6;
	if(v5 > 0 && v6 == 0.0) {
		this->_getCenter(a2, a3, a4);
		v7 = a2;
		v8 = a3;
		v9 = a4;
		level = this->level;
		level->playSound(v7 + 0.5, v8 + 0.5, v9 + 0.5, "random.chestopen", 0.5, (float)(level->random.nextFloat() * 0.1) + 0.9);
	}

	v12 = this->field_8C;
	if(!v12) {
		if(this->field_84 <= 0.0) {
			return;
		}
		goto LABEL_19;
	}
	if(v12 > 0 && this->field_84 < 1.0) {
LABEL_19:
		v13 = this->field_84;
		if(v12 <= 0) {
			v14 = v13 - 0.1;
		} else {
			v14 = v13 + 0.1;
		}

		this->field_84 = v14;
		if(this->field_84 > 1.0) {
			this->field_84 = 1.0;
		}
		if(this->field_84 < 0.5 && v13 >= 0.5) {
			this->_getCenter(a2, a3, a4);
			v15 = a2;
			v16 = a3;
			v17 = a4;
			v18->playSound(v15 + 0.5, v16 + 0.5, v17 + 0.5, "random.chestclosed", 0.5, (float)(v18->random.nextFloat() * 0.1) + 0.9);
		}
		if(this->field_84 < 0.0) {
			this->field_84 = 0.0;
		}
	}
}
Packet* ChestTileEntity::getUpdatePacket() {
	CompoundTag v3;
	this->_saveClientSideState(&v3);
	return new EntityDataPacket(this->posX, this->posY, this->posZ, &v3);
}
void ChestTileEntity::onUpdatePacket(CompoundTag* a2) {
	this->load(a2);
}
void ChestTileEntity::setRemoved() {
	this->clearCache();
	TileEntity::setRemoved();
}
void ChestTileEntity::triggerEvent(int32_t a2, int32_t a3) {
	if(a2 == 1) this->field_8C = a3;
}
void ChestTileEntity::clearCache() {
	TileEntity::clearCache();
}
void ChestTileEntity::onNeighborChanged(int32_t a2, int32_t a3, int32_t a4) {
	Level* level;	// r0
	TileEntity* te; // r5

	if(!this->pair) {
		level = this->level;
		if(!level->isClientMaybe) {
			te = level->getTileEntity(a2, a3, a4);
			if(this->canPairWith(te)) {
				this->pairWith(((ChestTileEntity*)te), 0);
				((ChestTileEntity*)te)->pairWith(this, 1);
			}
		}
	}
}
int32_t ChestTileEntity::getContainerSize() {
	if(this->pair) return 54;
	return 27;
}
int32_t ChestTileEntity::getMaxStackSize() {
	return 64;
}
std::string ChestTileEntity::getName() {
	return this->pair ? "container.largechest" : "container.chest";
}
ItemInstance* ChestTileEntity::getItem(int32_t a2) {
	ChestTileEntity* pair; // r3
	ChestTileEntity* v3;   // r2
	bool_t v4;			   // cc

	pair = this->pair;
	if(this->isUnpaired) {
		v3 = this->pair;
		pair = this;
	} else {
		v3 = this;
	}
	if(a2 <= 26) {
		return pair->items[a2];
	} else {
		a2 -= 27;
		return v3->items[a2];
	}
}
void ChestTileEntity::setItem(int32_t a2, ItemInstance* a3) {
	int32_t v3;			   // r4
	ChestTileEntity* v6;   // r2
	ItemInstance* v10;	   // r2
	ChestTileEntity* pair; // r3
	ItemInstance v18;	   // [sp+4h] [bp-2Ch] BYREF

	v3 = a2;
	if(a2 >= 0 && a2 < this->getContainerSize()) {
		pair = this->pair;
		if(this->isUnpaired) {
			v6 = this->pair;
			pair = this;
		} else {
			v6 = this;
		}
		ItemInstance* v9;
		if(v3 > 26) {
			v3 -= 27;
			v9 = v6->items[v3];
		} else {
			v9 = pair->items[v3];
		}
		if(v9) {
			*v9 = (a3 ? ItemInstance(*a3) : ItemInstance());
		} else {
			ItemInstance* v15 = (a3 ? new ItemInstance(*a3) : new ItemInstance());
			if(a2 > 26) {
				v6->items[v3] = v15;
			} else {
				pair->items[v3] = v15;
			}
		}
	}
}
bool_t ChestTileEntity::stillValid(Player* a2) {
	ChestTileEntity* te; // r0

	te = (ChestTileEntity*)this->level->getTileEntity(this->posX, this->posY, this->posZ);
	return te == this && a2->distanceToSqr((float)te->posX + 0.5, (float)te->posY + 0.5, (float)te->posZ + 0.5) <= 64.0;
}
void ChestTileEntity::startOpen() {
	bool_t v1;	// r1
	int32_t v2; // r2

	v1 = this->field_34;
	v2 = this->field_8C + 1;
	this->field_8C = v2;
	if(!v1) {
		this->level->tileEvent(this->posX, this->posY, this->posZ, 1, v2);
	}
}
void ChestTileEntity::stopOpen() {
	bool_t v1;	// r1
	int32_t v2; // r2

	if(this->isUnpaired) {
		v1 = this->field_34;
		v2 = this->field_8C - 1;
		this->field_8C = v2;
		if(!v1) {
			this->level->tileEvent(this->posX, this->posY, this->posZ, 1, v2);
		}
	} else {
		this->pair->stopOpen();
	}
}
