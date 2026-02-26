#include <entity/FallingTile.hpp>
#include <level/Level.hpp>
#include <nbt/CompoundTag.hpp>

FallingTile::FallingTile(Level* level)
	: Entity(level) {
	this->blockID = 0;
	this->blockMetaMaybe = 0;
	this->init();
}
FallingTile::FallingTile(Level* level, float x, float y, float z, int32_t id, int32_t meta)
	: Entity(level) {
	this->blockID = id;
	this->blockMetaMaybe = meta;
	this->init();
	this->setPos(x, y, z);
	this->prevPosX = x;
	this->prevX = x;
	this->prevPosY = y;
	this->prevY = y;
	this->prevPosZ = z;
	this->prevZ = z;
}
Level* FallingTile::getLevel() {
	return this->level;
}
void FallingTile::init() {
	this->entityRenderId = FALLINGTILE;
	this->field_FC = 1;
	this->fallTime = 0;
	this->setSize(0.98, 0.98);
	this->field_110 = 0;
	this->motionX = this->motionY = this->motionZ = 0;
	this->ridingHeight = this->entityHeight * 0.5;
}

FallingTile::~FallingTile() {
}
void FallingTile::tick() {
	float motionY_1; // s15
	float motionX;	 // r1
	Level* level;	 // r0
	float posX;		 // s15
	int32_t floorX;	 // r7
	bool_t v8;		 // fnf
	float posY;		 // s15
	int32_t floorY;	 // r6
	bool_t v11;		 // fnf
	float posZ;		 // s15
	int32_t floorZ;	 // r5r3
	float motionY;	 // s14

	if(!this->blockID) {
LABEL_14:
		this->remove();
		return;
	}
	motionY_1 = this->motionY - 0.04;
	motionX = this->motionX;
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;
	this->motionY = motionY_1;
	++this->fallTime;
	this->move(motionX, motionY_1, this->motionZ);
	level = this->level;
	this->motionX = this->motionX * 0.98;
	this->motionY = this->motionY * 0.98;
	this->motionZ = this->motionZ * 0.98;
	if(level->isClientMaybe) {
		return;
	}
	posX = this->posX;
	floorX = (int32_t)posX;
	v8 = posX < (float)(int32_t)posX;
	posY = this->posY;
	floorY = (int32_t)posY;
	if(v8) {
		--floorX;
	}
	v11 = posY < (float)(int32_t)posY;
	posZ = this->posZ;
	floorZ = (int32_t)posZ;
	if(v11) {
		--floorY;
	}
	if(posZ < (float)(int32_t)posZ) {
		--floorZ;
	}
	if(this->fallTime == 1) {
		if(level->getTile(floorX, floorY, floorZ) != this->blockID) {
			goto LABEL_13;
		}
		this->level->setTile(floorX, floorY, floorZ, 0, 3);
	}
	if(this->onGround) {
		this->motionX = this->motionX * 0.7;
		motionY = this->motionY;
		this->motionZ = this->motionZ * 0.7;
		this->motionY = motionY * -0.5;
		this->remove();
		if((!this->level->mayPlace(this->blockID, floorX, floorY, floorZ, 1, 1u) || !this->level->setTileAndData(floorX, floorY, floorZ, this->blockID, this->blockMetaMaybe, 3)) && !this->level->isClientMaybe) {
			this->spawnAtLocation(this->blockID, 1);
		}
		return;
	}
	if(this->fallTime > 100 && !this->level->isClientMaybe) {
LABEL_13:
		goto LABEL_14;
	}
}
float FallingTile::getShadowRadius() {
	return 0;
}
float FallingTile::getShadowHeightOffs() {
	return 0;
}
bool_t FallingTile::isPickable() {
	return !this->isDead;
}
int32_t FallingTile::getEntityTypeId() const{
	return 66;
}
void FallingTile::readAdditionalSaveData(CompoundTag* a2) {
	this->blockID = a2->getByte("Tile");
	this->blockMetaMaybe = a2->getByte("Data");
	this->fallTime = a2->getByte("Time");
}
void FallingTile::addAdditonalSaveData(CompoundTag* a2) {
	a2->putByte("Tile", this->blockID);
	a2->putByte("Data", this->blockMetaMaybe);
	a2->putByte("Time", this->fallTime);
}
