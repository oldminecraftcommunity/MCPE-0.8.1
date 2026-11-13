#include <entity/FlyingMob.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <tile/Tile.hpp>

FlyingMob::FlyingMob(Level* a2)
	: Mob(a2) {
}

void FlyingMob::causeFallDamage(float) {
}
bool_t FlyingMob::onLadder() {
	return 0;
}
void FlyingMob::travel(float a2, float a3) {
	if(this->isInWater()) {
		this->moveRelative(a2, a3, 0.02f);
		this->move(this->motionX, this->motionY, this->motionZ);
		this->motionX *= 0.8f;
		this->motionY *= 0.8f;
		this->motionZ *= 0.8f;
	} else if(this->isInLava()) {
		this->moveRelative(a2, a3, 0.02f);
		this->move(this->motionX, this->motionY, this->motionZ);
		this->motionX *= 0.5f;
		this->motionY *= 0.5f;
		this->motionZ *= 0.5f;
	} else {
		float v16;
		if(this->onGround) {
			int x = Mth::floor(this->posX);
			int y = Mth::floor(this->boundingBox.minY - 0.5f);
			int z = Mth::floor(this->posZ);
			int id = this->level->getTile(x, y, z);
			if(id <= 0) {
				v16 = 0.546f;
			} else {
				v16 = Tile::tiles[id]->slipperiness * 0.91f;
			}
		} else {
			v16 = 0.91f;
		}

		this->moveRelative(a2, a3, this->onGround ? (0.016277f / (v16 * v16 * v16)) : 0.02f);
		float v24;
		if(this->onGround) {
			int x = Mth::floor(this->posX);
			int y = Mth::floor(this->boundingBox.minY - 0.5f);
			int z = Mth::floor(this->posZ);
			int id = this->level->getTile(x, y, z);
			if(id <= 0) {
				v24 = 0.546f;
			} else {
				v24 = Tile::tiles[id]->slipperiness * 0.91f;
			}
		} else {
			v24 = 0.91f;
		}

		this->move(this->motionX, this->motionY, this->motionZ);
		this->motionX *= v24;
		this->motionY *= v24;
		this->motionZ *= v24;
	}



	float dx = this->posX - this->prevX;
	float dz = this->posZ - this->prevZ;
	this->field_168 = this->field_16C;
	float v29 = sqrt(dx*dx + dz*dz) * 4;
	if(v29 > 1) v29 = 1;

	this->field_16C += (v29 - this->field_16C) * 0.4f;
	this->field_170 += this->field_16C;
}
