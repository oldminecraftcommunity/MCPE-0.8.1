#include <tile/FireTile.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

FireTile::FireTile(int32_t ids, const std::string& name)
	: Tile(ids, name, Material::fire) {
	for(int32_t i = 0; i < 256; ++i) {
		this->field_480[i] = 0;
		this->flammability[i] = 0;
	}

	int32_t idd = Tile::wood->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::woodSlab->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::woodSlabHalf->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::fence->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::fenceGate->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::sign->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::wallSign->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::stairs_wood->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::woodStairsBirch->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::woodStairsDark->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::woodStairsJungle->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 20;
	idd = Tile::treeTrunk->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 5;
	idd = Tile::leaves->blockID;
	this->flammability[idd] = 30;
	this->field_480[idd] = 60;
	idd = Tile::bookshelf->blockID;
	this->flammability[idd] = 30;
	this->field_480[idd] = 20;
	idd = Tile::tnt->blockID;
	this->flammability[idd] = 15;
	this->field_480[idd] = 100;
	idd = Tile::tallgrass->blockID;
	this->flammability[idd] = 60;
	this->field_480[idd] = 100;
	idd = Tile::cloth->blockID;
	this->flammability[idd] = 30;
	this->field_480[idd] = 60;
	idd = Tile::woolCarpet->blockID;
	this->flammability[idd] = 30;
	this->field_480[idd] = 60;
	idd = Tile::coalBlock->blockID;
	this->flammability[idd] = 5;
	this->field_480[idd] = 5;
	idd = Tile::hayBlock->blockID;
	this->flammability[idd] = 60;
	this->field_480[idd] = 20;
	idd = Tile::sponge->blockID;
	this->flammability[idd] = 30;
	this->field_480[idd] = 60;

	this->setTicking(1);
	this->replaceable = 1;
}
bool_t FireTile::canBurn(struct LevelSource* level, int32_t x, int32_t y, int32_t z) {
	return this->flammability[level->getTile(x, y, z)] > 0;
}
void FireTile::checkBurn(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, Random* random) {
	int32_t v11; // r11
	int32_t v12; // r0
	int32_t blockID; // r10
	int32_t v14; // r11
	int32_t v15; // r2

	v11 = this->field_480[level->getTile(x, y, z)];
	if((int32_t)(random->genrand_int32() % a6) < v11) {
		v12 = level->getTile(x, y, z);
		blockID = Tile::tnt->blockID;
		v14 = v12;
		if((random->genrand_int32() & 1) != 0) {
			v15 = 0;
		} else {
			v15 = this->blockID;
		}
		level->setTile(x, y, z, v15, 3);
		if(v14 == blockID) {
			Tile::tnt->destroy(level, x, y, z, 1);
		}
	}
}
int32_t FireTile::getFireOdds(Level* level, int32_t x, int32_t y, int32_t z) {
	if(level->isEmptyTile(x, y, z)) {
		int32_t fl1 = this->getFlammability(level, x + 1, y, z, 0);
		int32_t fl2 = this->getFlammability(level, x - 1, y, z, fl1);
		int32_t fl3 = this->getFlammability(level, x, y - 1, z, fl2);
		int32_t fl4 = this->getFlammability(level, x, y + 1, z, fl3);
		int32_t fl5 = this->getFlammability(level, x, y, z - 1, fl4);
		return this->getFlammability(level, x, y, z + 1, fl5);
	}
	return 0;
}
int32_t FireTile::getFlammability(Level* level, int32_t x, int32_t y, int32_t z, int32_t mx) {
	int32_t res = this->flammability[level->getTile(x, y, z)];
	if(res < mx) return mx;
	return res;
}
bool_t FireTile::isValidFireLocation(Level* level, int32_t x, int32_t y, int32_t z) {
	return this->canBurn(level, x + 1, y, z) || this->canBurn(level, x - 1, y, z) || this->canBurn(level, x, y - 1, z) || this->canBurn(level, x, y + 1, z) || this->canBurn(level, x, y, z - 1) || this->canBurn(level, x, y, z + 1);
}


FireTile::~FireTile() {
}
bool_t FireTile::isCubeShaped() {
	return 0;
}
int32_t FireTile::getRenderShape() {
	return 3;
}
AABB* FireTile::getAABB(Level*, int32_t, int32_t, int32_t) {
	return 0;
}
bool_t FireTile::isSolidRender() {
	return 0;
}
bool_t FireTile::mayPick() {
	return 0;
}
bool_t FireTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	return level->isSolidBlockingTile(x, y - 1, z) || this->isValidFireLocation(level, x, y, z);
}
int32_t FireTile::getTickDelay() {
	return 30;
}
void FireTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
	int32_t v10; // r0
	int32_t v11; // r11
	int32_t v12; // r1
	int32_t v13; // r9
	uint32_t v14; // r1
	int32_t v15; // r11
	int32_t v16; // r3
	int32_t FireOdds; // r0
	int32_t i; // r12
	int32_t v19; // r1
	int32_t v20; // r9
	int32_t v21; // r6
	int32_t v22; // [sp+14h] [bp-54h]
	int32_t v23; // [sp+18h] [bp-50h]
	int32_t v24; // [sp+18h] [bp-50h]
	int32_t v25; // [sp+1Ch] [bp-4Ch]
	int32_t v26; // [sp+20h] [bp-48h]
	int32_t blockID; // [sp+24h] [bp-44h]
	int32_t v29; // [sp+30h] [bp-38h]

	v26 = y - 1;
	v10 = level->getTile(x, y - 1, z);
	blockID = Tile::netherrack->blockID;
	v11 = v10;
	if(!this->mayPlace(level, x, y, z)) {
		level->setTile(x, y, z, 0, 3);
	}
	v25 = level->getData(x, y, z);
	if(v25 <= 14) {
		v12 = random->genrand_int32() % 3;
		level->setData(x, y, z, v25 + (v12 >> 1), 4);
	}
	level->addToTickNextTick(x, y, z, this->blockID, (random->genrand_int32() % 0xA) + this->getTickDelay());
	if(v11 != blockID) {
		if(!this->isValidFireLocation(level, x, y, z)) {
			if(level->isSolidBlockingTile(x, v26, z) && v25 <= 3) {
				return;
			}
STOP_BURNING:
			level->setTile(x, y, z, 0, 3);
			return;
		}
		if(!this->canBurn((LevelSource*)level, x, v26, z) && v25 == 15 && (random->genrand_int32() & 3) == 0) {
			goto STOP_BURNING;
		}
	}
	if((v25 & 1) == 0) {
		if(v25 <= 2) {
			return;
		}
		v15 = x - 1;
		this->checkBurn(level, x + 1, y, z, 300, random);
		this->checkBurn(level, x - 1, y, z, 300, random);
		this->checkBurn(level, x, v26, z, 250, random);
		v29 = y + 1;
		this->checkBurn(level, x, y + 1, z, 250, random);
		this->checkBurn(level, x, y, z - 1, 300, random);
		this->checkBurn(level, x, y, z + 1, 300, random);
		while(v15 <= x + 1) {
			for(i = z - 1; i <= z + 1; ++i) {
				v20 = v26;
				v21 = 0;
				while(v20 <= y + 4) {
					if(v15 != x || v20 != y || i != z) {
						v16 = y + 1;
						v22 = i;
						int32_t t;
						if(v20 <= v29) {
							v16 = 100;
						} else {
							t = (v21 - 100);
						}
						if(v20 <= v29) {
							t = v16;
						}
						FireOdds = this->getFireOdds(level, v15, v20, i);
						i = v22;
						if(FireOdds > 0) {
							v24 = FireOdds;
							v19 = random->genrand_int32() % (uint32_t)t;
							i = v22;
							if(v19 <= v24) {
								level->setTile(v15, v20, v22, this->blockID, 3);
								i = v22;
							}
						}
					}
					++v20;
					v21 += 100;
				}
			}
			++v15;
		}
	}
	if(v25 == 15) {
		this->checkBurn(level, x + 1, y, z, 1, random);
		this->checkBurn(level, x - 1, y, z, 1, random);
		this->checkBurn(level, x, v26, z, 1, random);
		this->checkBurn(level, x, y + 1, z, 1, random);
		this->checkBurn(level, x, y, z - 1, 1, random);
		this->checkBurn(level, x, y, z + 1, 1, random);
	}
}
void FireTile::animateTick(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
	float v9; // s16
	int32_t v10; // r10
	float v11; // s17
	float v12; // s18
	float f; // s20
	float v14; // r0
	float v15; // s14
	float v16; // s21
	float v17; // r0
	int32_t v18; // r6
	int32_t v19; // r10
	float v20; // s14
	float v21; // s15
	float v22; // r0
	int32_t v23; // r10
	float v24; // s13
	float v25; // s14
	float v26; // r0
	int32_t v27; // r10
	float v28; // s13
	float v29; // s14
	float v30; // r0
	int32_t v31; // r8
	int32_t v32; // r10
	float v33; // s14
	float v34; // s15
	float v35; // r0
	int32_t v36; // r6
	float v37; // s14
	float v38; // s13
	float v39; // r0

	v9 = (float)x;
	v10 = y - 1;
	v11 = (float)y;
	v12 = (float)z;
	level->playSound(v9 + 0.5, v11 + 0.5, (float)z + 0.5, "fire.fire", random->nextFloat() + 1.0, (float)(random->nextFloat() * 0.7) + 0.3);
	if(level->isSolidBlockingTile(x, v10, z) || ((FireTile*)Tile::fire)->canBurn(level, x, v10, z)) {
		v18 = 3;
		do {
			v15 = random->nextFloat();
			v16 = random->nextFloat();
			v17 = random->nextFloat();
			level->addParticle(ParticleType::PT_SMOKE, v9 + v15, (float)(v11 + (float)(v16 * 0.5)) + 0.5, v12 + v17, 0.0, 0.0, 0.0, 250);
			--v18;
		} while(v18);
	} else {
		if(((FireTile*)Tile::fire)->canBurn((LevelSource*)level, x - 1, y, z)) {
			v19 = 2;
			do {
				v20 = random->nextFloat();
				v21 = random->nextFloat();
				v22 = random->nextFloat();
				level->addParticle(ParticleType::PT_SMOKE, v9 + (float)(v20 * 0.1), v11 + v21, v12 + v22, 0.0, 0.0, 0.0, 250);
				--v19;
			} while(v19);
		}
		if(((FireTile*)Tile::fire)->canBurn((LevelSource*)level, x + 1, y, z)) {
			v23 = 2;
			do {
				v24 = random->nextFloat();
				v25 = random->nextFloat();
				v26 = random->nextFloat();
				level->addParticle(ParticleType::PT_SMOKE, (float)(x + 1) - (float)(v24 * 0.1), v11 + v25, v12 + v26, 0.0, 0.0, 0.0, 250);
				--v23;
			} while(v23);
		}
		if(((FireTile*)Tile::fire)->canBurn(level, x, y, z - 1)) {
			v27 = 2;
			do {
				v28 = random->nextFloat();
				v29 = random->nextFloat();
				v30 = random->nextFloat();
				level->addParticle(ParticleType::PT_SMOKE, v9 + v28, v11 + v29, v12 + (float)(v30 * 0.1), 0.0, 0.0, 0.0, 250);
				--v27;
			} while(v27);
		}
		if(((FireTile*)Tile::fire)->canBurn(level, x, y, z + 1)) {
			v32 = 2;
			do {
				v33 = random->nextFloat();
				v34 = random->nextFloat();
				v35 = random->nextFloat();
				level->addParticle(ParticleType::PT_SMOKE, v9 + v33, v11 + v34, (float)(z + 1) - (float)(v35 * 0.1), 0.0, 0.0, 0.0, 250);
				--v32;
			} while(v32);
		}
		v31 = y + 1;
		if(((FireTile*)Tile::fire)->canBurn(level, x, v31, z)) {
			v36 = 2;
			do {
				v37 = random->nextFloat();
				v38 = random->nextFloat();
				v39 = random->nextFloat();
				level->addParticle(ParticleType::PT_SMOKE, v9 + v37, (float)v31 - (float)(v38 * 0.1), v12 + v39, 0.0, 0.0, 0.0, 250);
				--v36;
			} while(v36);
		}
	}
}
void FireTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t) {
	if(level->isSolidBlockingTile(x, y - 1, z) && this->isValidFireLocation(level, x, y, z)) {
		level->setTile(x, y, z, 0, 3);
	}
}
void FireTile::onPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	if(level->isSolidBlockingTile(x, y - 1, z) || this->isValidFireLocation(level, x, y, z)) {
		level->addToTickNextTick(x, y, z, this->blockID, this->getTickDelay());
	} else {
		level->setTile(x, y, z, 0, 3);
	}
}
int32_t FireTile::getResourceCount(Random*) {
	return 0;
}
int32_t FireTile::getRenderLayer() {
	return 1;
}
