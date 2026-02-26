#include <entity/ai/goals/DoorInteractGoal.hpp>
#include <entity/Mob.hpp>
#include <entity/path/Node.hpp>
#include <entity/path/Path.hpp>
#include <entity/path/PathNavigation.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>

DoorInteractGoal::DoorInteractGoal(Mob* a2) {
	this->holder = a2;
	this->doorZ = 0;
	this->doorY = 0;
	this->doorX = 0;
	this->doorTile = 0;
	this->closeToTarget = 0;
	this->targetZ = 0;
	this->targetX = 0;
}

Tile* DoorInteractGoal::getDoorTile(int32_t x, int32_t y, int32_t z) {
	int32_t id = this->holder->level->getTile(x, y, z);
	if(id == Tile::door_wood->blockID) {
		return Tile::tiles[id];
	}
	return 0;
}

DoorInteractGoal::~DoorInteractGoal() {
}
bool_t DoorInteractGoal::canUse() {
	Mob* holder;		 // r0
	PathNavigation* nav; // r7
	Path* path;			 // r0
	Path* v5;			 // r6
	int32_t isDone;		 // r5
	Node* v7;			 // r0
	int32_t xCoord;		 // r1
	int32_t zCoord;		 // r3
	Entity* v10;		 // r0
	Tile* door;			 // r0
	int32_t v13;		 // r7
	int32_t size;		 // r0
	Mob* v15;			 // r3
	float posX;			 // s15
	int32_t v17;		 // r1
	float v18;			 // s15
	int32_t v19;		 // r2
	float posZ;			 // s15
	int32_t v21;		 // r3
	Tile* v22;			 // r0

	holder = this->holder;
	if(!holder->isCollidedHorizontally) {
		return holder->isCollidedHorizontally;
	}
	nav = holder->getNavigation();
	path = nav->getPath();
	v5 = path;
	if(!path) {
		return 0;
	}
	isDone = path->isDone();
	if(isDone || !nav->canOpenDoors()) {
		return 0;
	}
	while(1) {
		v13 = v5->getIndex() + 2;
		size = v5->getSize();
		if(v13 < size) {
			size = v13;
		}
		if(isDone >= size) {
			break;
		}
		v7 = v5->get(isDone);
		xCoord = v7->xCoord;
		this->doorX = v7->xCoord;
		this->doorY = v7->yCoord + 1;
		zCoord = v7->zCoord;
		this->doorZ = zCoord;
		if(this->holder->distanceToSqr((float)xCoord, this->holder->posY, (float)zCoord) <= 2.25) {
			door = this->getDoorTile(this->doorX, this->doorY, this->doorZ);
			this->doorTile = door;
			if(door) {
				return 1;
			}
		}
		++isDone;
	}
	v15 = this->holder;
	posX = v15->posX;
	v17 = (int32_t)posX;
	if(posX < (float)(int32_t)posX) {
		--v17;
	}
	this->doorX = v17;
	v18 = v15->posY + 1.0;
	v19 = (int32_t)v18;
	if(v18 < (float)(int32_t)v18) {
		--v19;
	}
	this->doorY = v19;
	posZ = v15->posZ;
	v21 = (int32_t)posZ;
	if(posZ < (float)(int32_t)posZ) {
		--v21;
	}
	this->doorZ = v21;
	v22 = this->getDoorTile(v17, v19, v21);
	this->doorTile = v22;
	return v22 != 0;
}
bool_t DoorInteractGoal::canContinueToUse() {
	return !this->closeToTarget;
}
void DoorInteractGoal::start() {
	int32_t doorX; // s13
	Mob* holder;   // r3
	float v3;	   // s14
	int32_t doorZ; // s13

	doorX = this->doorX;
	this->closeToTarget = 0;
	holder = this->holder;
	v3 = (float)((float)doorX + 0.5) - holder->posX;
	doorZ = this->doorZ;
	this->targetX = v3;
	this->targetZ = (float)((float)doorZ + 0.5) - holder->posZ;
}
void DoorInteractGoal::tick() {
	if((float)((float)((float)((float)((float)this->doorZ + 0.5) - this->holder->posZ) * this->targetZ) + (float)((float)((float)((float)this->doorX + 0.5) - this->holder->posX) * this->targetX)) < 0.0) {
		this->closeToTarget = 1;
	}
}
