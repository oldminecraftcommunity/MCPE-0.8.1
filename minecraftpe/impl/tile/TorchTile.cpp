#include <tile/TorchTile.hpp>
#include <level/Level.hpp>
#include <math/HitResult.hpp>

bool_t TorchTile::isConnection(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v8; // r0

	if(level->isSolidBlockingTile(x, y, z)) {
		return 1;
	}
	v8 = level->getTile(x, y, z);
	return v8 == Tile::fence->blockID || v8 == Tile::glass->blockID || v8 == Tile::cobbleWall->blockID;
}
bool_t TorchTile::checkCanSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v10; // r0

	if(this->mayPlace(level, x, y, z)) {
		return 1;
	}
	if(level->getTile(x, y, z) == this->blockID) {
		v10 = level->getData(x, y, z);
		this->spawnResources(level, x, y, z, v10);
		level->setTile(x, y, z, 0, 3);
	}
	return 0;
}

TorchTile::TorchTile(int32_t id, const std::string& s, Material* m)
	: Tile(id, s, m) {
	this->setTicking(1);
}
TorchTile::~TorchTile() {
}
bool_t TorchTile::isCubeShaped() {
	return 0;
}
int32_t TorchTile::getRenderShape() {
	return 2;
}
AABB* TorchTile::getAABB(Level*, int32_t, int32_t, int32_t) {
	return 0;
}
bool_t TorchTile::isSolidRender() {
	return 0;
}
bool_t TorchTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	return level->isSolidBlockingTile(x - 1, y, z) || level->isSolidBlockingTile(x + 1, y, z) || level->isSolidBlockingTile(x, y, z - 1) || level->isSolidBlockingTile(x, y, z + 1) || this->isConnection(level, x, y - 1, z);
}
void TorchTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random*) {
	if(!level->getData(x, y, z)) {
		this->onPlace(level, x, y, z);
	}
}
void TorchTile::animateTick(Level* level, int32_t x, int32_t y, int32_t z, Random* r) {
	int32_t v9; // r0
	float v10; // s18
	float v11; // s16
	float v12; // s17
	float v13; // s18
	float v14; // s17

	v9 = level->getData(x, y, z);
	v10 = (float)y + 0.7;
	v11 = (float)x + 0.5;
	v12 = (float)z + 0.5;
	switch(v9) {
		case 1:
			v11 = v11 - 0.27;
LABEL_5:
			v10 = v10 + 0.22;
			break;
		case 2:
			v11 = v11 + 0.27;
			goto LABEL_5;
		case 3:
			v13 = v10 + 0.22;
			v14 = v12 - 0.27;
			level->addParticle(PT_SMOKE, v11, v13, v14, 0.0, 0.0, 0.0, 0);
			level->addParticle(PT_FLAME, v11, v13, v14, 0.0, 0.0, 0.0, 0);
			return;
		case 4:
			v10 = v10 + 0.22;
			v12 = v12 + 0.27;
			break;
	}
	level->addParticle(PT_SMOKE, v11, v10, v12, 0.0, 0.0, 0.0, 0);
	level->addParticle(PT_FLAME, v11, v10, v12, 0.0, 0.0, 0.0, 0);
}
void TorchTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t) {
	int32_t data; // r9
	bool_t v14;	  // r8
	int32_t v16;  // r0

	if(this->checkCanSurvive(level, x, y, z)) {
		data = level->getData(x, y, z);
		if(level->isSolidBlockingTile(x - 1, y, z)) {
			v14 = 0;
		} else {
			v14 = data == 1;
		}
		if(!level->isSolidBlockingTile(x + 1, y, z) && data == 2) {
			v14 = 1;
		}
		if(!level->isSolidBlockingTile(x, y, z - 1) && data == 3) {
			v14 = 1;
		}
		if(!level->isSolidBlockingTile(x, y, z + 1) && data == 4) {
			v14 = 1;
		}
		if(!this->isConnection(level, x, y - 1, z) && data == 5 || v14) {
			v16 = level->getData(x, y, z);
			this->spawnResources(level, x, y, z, v16);
			level->setTile(x, y, z, 0, 3);
		}
	}
}
void TorchTile::onPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v9; // r3

	if(!level->getData(x, y, z)) {
		if(level->isSolidBlockingTile(x - 1, y, z)) {
			v9 = 1;
LABEL_12:
			level->setData(x, y, z, v9, 2);
			goto LABEL_13;
		}
		if(level->isSolidBlockingTile(x + 1, y, z)) {
			level->setData(x, y, z, 2, 2);
		} else {
			if(level->isSolidBlockingTile(x, y, z - 1)) {
				v9 = 3;
				goto LABEL_12;
			}
			if(level->isSolidBlockingTile(x, y, z + 1)) {
				v9 = 4;
				goto LABEL_12;
			}
			if(this->isConnection(level, x, y - 1, z)) {
				v9 = 5;
				goto LABEL_12;
			}
		}
	}
LABEL_13:
	this->checkCanSurvive(level, x, y, z);
}
HitResult TorchTile::clip(Level* level, int32_t x, int32_t y, int32_t z, const Vec3& a7, const Vec3& a8) {
	int8_t v12;	 // r0
	int32_t v14; // r0
	float v16;	 // r1
	float v18;	 // r2
	float v19;	 // r3
	float a5a;	 // [sp+0h] [bp-30h]
	float a6a;	 // [sp+4h] [bp-2Ch]
	float a7a;	 // [sp+8h] [bp-28h]

	v12 = level->getData(x, y, z);
	v14 = v12 & 7;
	switch(v14) {
		case 1:
			v16 = 0.0;
			a5a = 0.3;
			a6a = 0.8;
			a7a = 0.65;
LABEL_5:
			v18 = 0.2;
			v19 = 0.35;
LABEL_11:
			this->setShape(v16, v18, v19, a5a, a6a, a7a);
			break;
		case 2:
			a5a = 1.0;
			v16 = 0.7;
			a6a = 0.8;
			a7a = 0.65;
			goto LABEL_5;
		case 3:
			this->setShape(0.35, 0.2, 0.0, 0.65, 0.8, 0.3);
			break;
		case 4:
			this->setShape(0.35, 0.2, 0.7, 0.65, 0.8, 1.0);
			break;
		default:
			v16 = 0.4;
			v18 = 0.0;
			a5a = 0.6;
			a6a = 0.6;
			a7a = 0.6;
			v19 = 0.4;
			goto LABEL_11;
	}
	return Tile::clip(level, x, y, z, a7, a8);
}
int32_t TorchTile::getRenderLayer() {
	return 0;
}
int32_t TorchTile::getPlacementDataValue(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, float, float, float, Mob*, int32_t a11) {
	switch(a6) {
		case 1:
			if(this->isConnection(level, x, y - 1, z)) {
				return 5;
			}
			goto LABEL_19;
		case 2:
			if(level->isSolidBlockingTile(x, y, z + 1)) {
				return 4;
			}
			goto LABEL_19;
		case 3:
			if(level->isSolidBlockingTile(x, y, z - 1)) {
				return 3;
			}
			break;
		case 4:
			if(level->isSolidBlockingTile(x + 1, y, z)) {
				return 2;
			}
			break;
		default:
LABEL_19:
			if(a6 == 5) {
				if(level->isSolidBlockingTile(x - 1, y, z)) {
					return 1;
				}
			}
			return a11;
	}
	return a11;
}
