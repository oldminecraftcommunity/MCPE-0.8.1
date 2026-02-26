#include <tile/entity/NetherReactorTileEntity.hpp>
#include <entity/ItemEntity.hpp>
#include <entity/PigZombie.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <level/MobSpawner.hpp>
#include <level/NetherReactorPattern.hpp>
#include <math.h>
#include <nbt/CompoundTag.hpp>
#include <tile/NetherReactor.hpp>

ItemInstance NetherReactorTileEntity::GetLowOddsSpawnItem() {
	//TODO seems to be global~
	Item* lowOddsSpawnItems[] = {Item::arrow, Item::bed, Item::bone, Item::bow, Item::bowl, Item::feather, Item::painting, Item::door_wood};

	return ItemInstance(lowOddsSpawnItems[this->level->random.genrand_int32() % 9]);
}
NetherReactorTileEntity::NetherReactorTileEntity()
	: TileEntity(3) {
	this->isInitialized = 0;
	this->hasFinished = 0;
	this->field_60 = 0;
	this->progress = 0;
}
void NetherReactorTileEntity::buildCrockedRoofVolume(bool_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8) {
	int32_t i;	 // r4
	int32_t v10; // r9
	int32_t v11; // r6
	int32_t v12; // r9
	int32_t j;	 // r5

	for(i = -a6; i <= a6; ++i) {
		for(j = -a6; j <= a6; ++j) {
			if(a2) {
				v10 = -i - j;
			} else {
				v10 = j + i;
			}
			v11 = 0;
			v12 = v10 / 2 + a7 + a6;
			while(v11 < a7 + a6 + a6) {
				if(v12 >= v11 && (this->isEdge(i, a6, j) || v12 == v11)) {
					this->level->setTile(i + a3, v11 + a4, j + a5, a8, 3);
				}
				++v11;
			}
		}
	}
}
void NetherReactorTileEntity::buildDome(int32_t x, int32_t y, int32_t z) {
	this->buildFloorVolume(x, y - 3, z, 8, 2, Tile::netherrack->blockID);
	this->buildHollowedVolume(x, y - 1, z, 8, 4, Tile::netherrack->blockID, 0);
	this->buildFloorVolume(x, y + 3, z, 8, 1, Tile::netherrack->blockID);
	this->buildCrockedRoofVolume(0, x, y + 4, z, 8, 1, Tile::netherrack->blockID);
	this->buildCrockedRoofVolume(1, x, y + 5, z, 5, 8, Tile::netherrack->blockID);
	this->buildCrockedRoofVolume(0, x, y + 11, z, 3, 14, Tile::netherrack->blockID);
}
void NetherReactorTileEntity::buildFloorVolume(int32_t x, int32_t y, int32_t z, int32_t r, int32_t h, int32_t id) {
	int32_t yo;	 // r4
	int32_t xo;	 // r5
	int32_t zz;	 // r3
	int32_t zo;	 // r6
	int32_t xx;	 // r12
	int32_t v16; // [sp+8h] [bp-30h]

	for(yo = 0; yo < h; ++yo) {
		for(xo = -r; xo <= r; ++xo) {
			zo = -r;
			xx = xo + x;
			while(zo <= r) {
				zz = zo + z;
				++zo;
				v16 = xx;
				this->level->setTile(xx, yo + y, zz, id, 3);
				xx = v16;
			}
		}
	}
}
void NetherReactorTileEntity::buildHollowedVolume(int32_t x, int32_t y, int32_t z, int32_t a5, int32_t a6, int32_t a7, int32_t a8) {
	int32_t v10; // r8
	int32_t v11; // r9
	int32_t i;	 // r5
	int32_t v13; // r3
	int32_t j;	 // r4

	v10 = 0;
	v11 = -a5;
LABEL_21:
	if(v10 < a6) {
		for(i = -a5;; ++i) {
			if(i > a5) {
				++v10;
				goto LABEL_21;
			}
			for(j = -a5; j <= a5; ++j) {
				if(i == v11 || i == a5 || j == v11 || j == a5) {
					v13 = a7;
LABEL_14:
					this->level->setTile(i + x, y + v10, j + z, v13, 3);
					continue;
				}
				if(v10 > 2 || i < -1 || i > 1 || j < -1 || j > 1) {
					v13 = a8;
					goto LABEL_14;
				}
			}
		}
	}
}
static int32_t _d6753c7c[] = {0xA, 0xD, 0x14, 0x16, 0x19, 0x1E, 0x22, 0x24, 0x26, 0x28};
bool_t NetherReactorTileEntity::checkLevelChange(int32_t a2) {
	int32_t v2; // r3

	v2 = 0;
	while(_d6753c7c[v2] != a2) {
		if(++v2 == 10) {
			return 0;
		}
	}
	return 1;
}
void NetherReactorTileEntity::clearDomeSpace(int32_t x, int32_t y, int32_t z) {
	int32_t i;	 // r4
	int32_t v9;	 // r12
	int32_t v10; // r5
	int32_t j;	 // r6
	int32_t v12; // [sp+Ch] [bp-2Ch]

	for(i = -12; i != 13; ++i) {
		for(j = -3; j != 40; ++j) {
			v10 = -12;
			v9 = j + y;
			do {
				if(j > 2 || i < -1 || i > 1 || v10 < -1 || v10 > 1) {
					v12 = v9;
					this->level->setTile(i + x, v9, v10 + z, 0, 3);
					v9 = v12;
				}
				++v10;
			} while(v10 != 13);
		}
	}
}
void NetherReactorTileEntity::deterioateCrockedRoofVolume(bool_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8) {
	int32_t i;	 // r4
	int32_t v10; // r9
	int32_t k;	 // r9
	int32_t j;	 // r5
	int32_t v13; // [sp+Ch] [bp-44h]

	for(i = -a6; i <= a6; ++i) {
		for(j = -a6; j <= a6; ++j) {
			if(a2) {
				v10 = -i - j;
			} else {
				v10 = j + i;
			}
			v13 = v10 / 2 + a7 + a6;
			for(k = 0; k < a7 + a6 + a6; ++k) {
				if(v13 >= k && this->isEdge(i, a6, j) && !(this->level->random.genrand_int32() << 30)) {
					this->level->setTile(i + a3, k + a4, j + a5, a8, 3);
				}
			}
		}
	}
}
void NetherReactorTileEntity::deterioateDome(int32_t x, int32_t y, int32_t z) {
	this->deterioateHollowedVolume(x, y - 1, z, 8, 5, 0);
	this->deterioateCrockedRoofVolume(0, x, y + 4, z, 8, 1, 0);
	this->deterioateCrockedRoofVolume(1, x, y + 5, z, 5, 8, 0);
	this->deterioateCrockedRoofVolume(0, x, y + 11, z, 3, 14, 0);
}
void NetherReactorTileEntity::deterioateHollowedVolume(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7) {
	int32_t v9;	 // r8
	int32_t v10; // r9
	int32_t i;	 // r4
	int32_t j;	 // r5

	v9 = 0;
	v10 = -a5;
	while(v9 < a6) {
		for(i = -a5; i <= a5; ++i) {
			for(j = -a5; j <= a5; ++j) {
				if((i == v10 || i == a5 || j == v10 || j == a5) && !(this->level->random.genrand_int32() % 3)) {
					this->level->setTile(i + a2, a3 + v9, j + a4, a7, 3);
				}
			}
		}
		++v9;
	}
}
void NetherReactorTileEntity::finishReactorRun() {
	int32_t i;	  // r5
	int32_t j;	  // r6
	int32_t k;	  // r7
	int32_t posZ; // r3

	NetherReactor::setPhase(this->level, this->posX, this->posY, this->posZ, 2);
	this->level->setNightMode(0);
	this->hasFinished = 1;
	this->deterioateDome(this->posX, this->posY, this->posZ);
	for(i = this->posX - 1; i <= this->posX + 1; ++i) {
		for(j = this->posY - 1; j <= this->posY + 1; ++j) {
			for(k = this->posZ - 1;; ++k) {
				posZ = this->posZ;
				if(k > posZ + 1) {
					break;
				}
				if(i != this->posX || j != this->posY || k != posZ) {
					this->level->setTile(i, j, k, Tile::obsidian->blockID, 3);
				}
			}
		}
	}
}
std::string NetherReactorTileEntity::getName() {
	return "NetherReactor";
}
int32_t NetherReactorTileEntity::getNumEnemiesPerLevel(int32_t a2) {
	Random* p_random; // r0

	if(!a2) {
		return 3;
	}
	if(a2 <= 3) {
		return 2;
	}
	p_random = &this->level->random;
	if(a2 <= 5) {
		return p_random->genrand_int32() & 1;
	}
	p_random->genrand_int32();
	return 0;
}
int32_t NetherReactorTileEntity::getNumItemsPerLevel(int32_t a2) {
	Random* p_random; // r0
	int32_t v3;		  // r1

	if(!a2) {
		return 9;
	}
	if(a2 <= 3) {
		return 15;
	}
	p_random = &this->level->random;
	if(a2 > 7) {
		v3 = p_random->genrand_int32() % 27 - 2;
	} else {
		v3 = p_random->genrand_int32() % 42 - 4;
	}
	return v3 & ~(v3 >> 31);
}
ItemInstance NetherReactorTileEntity::getSpawnItem() {
	switch(this->level->random.genrand_int32() % 9) {
		case 0:
			return ItemInstance(Item::yellowDust, 3);
		case 1:
			return ItemInstance(Item::seeds_melon);
		case 2:
			return ItemInstance(Tile::mushroom1);
		case 3:
			return ItemInstance(Tile::mushroom2);
		case 4:
			return ItemInstance(Item::reeds);
		case 5:
			return ItemInstance(Tile::cactus);
		case 6:
			return ItemInstance(Item::netherQuartz, 4);
		case 7:
			return ItemInstance(Item::seeds_pumpkin);
		default:
			return this->GetLowOddsSpawnItem();
	}
}
Vec3 NetherReactorTileEntity::getSpawnPosition(float x, float y, float z) {
	float v9;  // s14
	double v10; // d8
	float v11; // s18
	double v12; // d9
	float v13; // s21
	float v14; // s20
	float v15; // s14

	v9 = this->level->random.nextFloat();
	v10 = (float)(x + (float)(v9 * y));
	v11 = this->level->random.nextFloat();
	v12 = (float)(v11 * 6.2832);
	v13 = (double)this->posX + sin(v12) * v10;
	v14 = z + (float)this->posY;
	v15 = (double)this->posZ + cos(v12) * v10;
	return Vec3(v13, v14, v15);
}
bool_t NetherReactorTileEntity::isEdge(int32_t x, int32_t y, int32_t z) {
	return x == -y || x == y || z == -y || z == y;
}
void NetherReactorTileEntity::killPigZombies() {
	float posX;	  // s11
	float posY;	  // s12
	int32_t posZ; // s15

	posX = (float)this->posX;
	posY = (float)this->posY;
	posZ = this->posZ;
	std::vector<Entity*>* vents = this->level->getEntities(0, {posX - 40.0f, posY - 40.0f, (float)posZ - 40.0f, (float)(posX + 1.0f) + 40.0f, (float)(posY + 1.0f) + 40.0f, (float)((float)posZ + 1.0f) + 40.0f});

	for(auto&& e: *vents) {
		if(e->getEntityTypeId() == 36) {
			e->remove();
		}
	}
}
void NetherReactorTileEntity::lightItUp(int32_t x, int32_t y, int32_t z) {
	this->field_60 = 0;
	NetherReactor::setPhase(this->level, x, y, z, 1);
	this->isInitialized = 1;
	this->buildDome(x, y, z);
	this->level->setNightMode(1);
}
int32_t NetherReactorTileEntity::numOfFreeEnemySlots() {
	float posX;	  // s11
	int32_t v2;	  // r5
	float posY;	  // s12
	int32_t posZ; // s15
	AABB v11;	  // [sp+10h] [bp-28h] BYREF

	posX = (float)this->posX;
	v2 = 0;
	posY = (float)this->posY;
	posZ = this->posZ;
	std::vector<struct Entity*>* ents = this->level->getEntities(0, {posX - 7.0f, posY - 7.0f, (float)posZ - 7.0f, (float)(posX + 1.0f) + 7.0f, (float)(posY + 1.0f) + 7.0f, (float)((float)posZ + 1.0f) + 7.0f});
	for(auto p: *ents) {
		if(p->getEntityTypeId() == 36) {
			if(p->isAlive()) {
				++v2;
			}
		}
	}
	return 3 - v2;
}
bool_t NetherReactorTileEntity::playersAreCloseBy() {
	float posX; // s12
	int v3;		// r6
	float posY; // s13
	int posZ;	// s15

	posX = (float)this->posX;
	v3 = 0;
	posY = (float)this->posY;
	posZ = this->posZ;
	std::vector<struct Entity*>* ents = this->level->getEntities(0, {posX - 40.0f, posY - 40.0f, (float)posZ - 40.0f, (float)(posX + 1.0) + 40.0f, (float)(posY + 1.0) + 40.0f, (float)((float)posZ + 1.0) + 40.0f});
	for(auto e: *ents) {
		if(e->isPlayer() && e->isAlive() && e->distanceTo(this->posX, this->posY, this->posZ) < 40) {
			++v3;
		}
	}

	if(v3) {
		return 1;
	}
	return 0;
}
void NetherReactorTileEntity::spawnEnemy() {
	float z; // s15
	float x; // s14

	PigZombie* v3 = new PigZombie(this->level);
	if(v3) {
		v3->postInit();
	}
	Vec3 v6 = this->getSpawnPosition(3.0, 4.0, -1.0);
	z = v6.z;
	x = v6.x;
	while(x < 0.0 || z < 0.0 || x >= 256.0 || z >= 256.0) {
		v6 = this->getSpawnPosition(3.0, 4.0, -1.0);
		x = v6.x;
		z = v6.z;
	}
	MobSpawner::addMob(this->level, (Mob*)v3, x, v6.y, z, 0.0, 0.0, 1);
}
void NetherReactorTileEntity::spawnItem() {
	float z;		// s16
	float x;		// s17
	ItemEntity* v4; // r5

	Vec3 v5 = this->getSpawnPosition(3.0, 4.0, -1.0);
	z = v5.z;
	x = v5.x;
	while(x < 0.0 || z < 0.0 || x >= 256.0 || z >= 256.0) {
		v5 = this->getSpawnPosition(3.0, 4.0, -1.0);
		x = v5.x;
		z = v5.z;
	}
	v4 = new ItemEntity(this->level, x, v5.y, z, this->getSpawnItem());
	v4->delayBeforePickup = 10;
	v4->field_130 = v4->getLifeTime() - 600;
	this->level->addEntity(v4);
}
void NetherReactorTileEntity::spawnItems(int32_t cnt) {
	for(int32_t i = 0; i < cnt; ++i) {
		this->spawnItem();
	}
}
void NetherReactorTileEntity::tickGlowingRedstoneTransformation(int32_t a2) {
	switch(a2) {
		case 2:
			this->turnLayerToGlowingObsidian(0, Tile::stoneBrick->blockID);
			break;
		case 3:
			this->turnLayerToGlowingObsidian(1, Tile::stoneBrick->blockID);
			break;
		case 4:
			this->turnLayerToGlowingObsidian(2, Tile::stoneBrick->blockID);
			break;
		case 7:
			this->turnLayerToGlowingObsidian(0, Tile::goldBlock->blockID);
			break;
		case 8:
			this->turnLayerToGlowingObsidian(1, Tile::goldBlock->blockID);
			break;
		case 9:
			this->turnLayerToGlowingObsidian(2, Tile::goldBlock->blockID);
			break;
	}
}
void NetherReactorTileEntity::trySpawnPigZombies(int32_t a2, int32_t a3) {
	int32_t v6; // r0
	int32_t v7; // r7
	int32_t i;	// r4

	if(this->level->difficulty) {
		v6 = 3 - this->numOfFreeEnemySlots();
		if(v6 < a2) {
			v7 = a2 - v6;
			for(i = 0; i < a3 && i != v7; ++i) {
				this->spawnEnemy();
			}
		}
	}
}
void NetherReactorTileEntity::turnGlowingObsidianLayerToObsidian(int32_t a2) {
	int32_t i;				 // r6
	int32_t j;				 // r5
	NetherReactorPattern v6; // [sp+Ch] [bp-8Ch] BYREF
	for(i = -1; i != 2; ++i) {
		for(j = -1; j != 2; ++j) {
			if(this->level->getTile(i + this->posX, this->posY - 1 + a2, j + this->posZ) != Tile::netherReactor->blockID) {
				this->level->setTile(i + this->posX, this->posY - 1 + a2, j + this->posZ, Tile::obsidian->blockID, 3);
			}
		}
	}
}
void NetherReactorTileEntity::turnLayerToGlowingObsidian(int32_t a2, int32_t a3) {
	int32_t i;				 // r4
	int32_t v7;				 // r8
	int32_t v8;				 // r5
	NetherReactorPattern v9; // [sp+Ch] [bp-94h] BYREF
	for(i = -1; i != 2; ++i) {
		v8 = -1;
		do {
			v7 = v8 + 1;
			if(v9.getTileAt(a2, i + 1, v8 + 1) == a3) {
				this->level->setTile(i + this->posX, this->posY - 1 + a2, v8 + this->posZ, Tile::glowingObsidian->blockID, 3);
			}
			++v8;
		} while(v7 != 2);
	}
}

NetherReactorTileEntity::~NetherReactorTileEntity() {
}
bool_t NetherReactorTileEntity::shouldSave() {
	return 1;
}
void NetherReactorTileEntity::load(CompoundTag* a2) {
	TileEntity::load(a2);
	this->isInitialized = a2->getByte("IsInitialized") != 0;
	if(this->isInitialized) {
		this->progress = a2->getShort("Progress");
		this->hasFinished = a2->getByte("HasFinished") != 0;
	}
}
bool_t NetherReactorTileEntity::save(CompoundTag* a2) {
	TileEntity::save(a2);
	a2->putByte("IsInitialized", this->isInitialized);
	a2->putShort("Progress", this->progress);
	a2->putByte("HasFinished", this->hasFinished);
	if(this->isInitialized) {
		if(!this->hasFinished) {
			this->level->setNightMode(1);
		}
	}
	return 1;
}
void NetherReactorTileEntity::tick() {
	bool_t hasFinished;		 // r3
	int16_t v3;				 // r5
	int32_t v4;				 // r5
	int32_t v5;				 // r1
	int32_t itemsPerLevel;	 // r0
	int32_t enemiesPerLevel; // r0

	if(!this->level->isClientMaybe) {
		if(this->progress < 0) {
			this->setRemoved();
		}
		hasFinished = this->hasFinished;
		if(!this->isInitialized || this->hasFinished) //TODO some weird code was here
		{
			if(this->hasFinished && !(this->progress % 20)) {
				if(this->playersAreCloseBy()) {
					this->trySpawnPigZombies(2, 3);
				} else {
					this->killPigZombies();
				}
			}
		} else {
			v3 = this->progress + 1;
			this->progress = v3;
			if(!(v3 % 20)) {
				v4 = v3 / 20;
				if(v4 <= 9) {
					this->tickGlowingRedstoneTransformation(v4);
				}
				if((uint32_t)(v4 - 43) <= 2) {
					this->turnGlowingObsidianLayerToObsidian(45 - v4);
				}
				if(this->checkLevelChange(this->progress / 20)) {
					v5 = this->field_60 + 1;
					this->field_60 = v5;
					itemsPerLevel = this->getNumItemsPerLevel(v5);
					this->spawnItems(itemsPerLevel);
					enemiesPerLevel = this->getNumEnemiesPerLevel(this->field_60);
					this->trySpawnPigZombies(3, enemiesPerLevel);
				}
			}
			if(this->progress > 920) {
				this->finishReactorRun();
			}
		}
	}
}
