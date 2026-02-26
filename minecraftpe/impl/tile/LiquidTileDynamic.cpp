#include <tile/LiquidTileDynamic.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <level/dimension/Dimension.hpp>

LiquidTileDynamic::LiquidTileDynamic(int32_t id, Material* mat, const std::string& still, const std::string& flow)
	: LiquidTile(id, mat, still, flow) {
	this->field_D8 = 0;
}
bool_t LiquidTileDynamic::canSpreadTo(Level* level, int32_t x, int32_t y, int32_t z) {
	Material* v9; // r0

	v9 = level->getMaterial(x, y, z);
	return v9 != this->material && v9 != Material::lava && !this->isWaterBlocking(level, x, y, z);
}
int32_t LiquidTileDynamic::getHighest(Level* level, int32_t x, int32_t y, int32_t z, int32_t oldhigh) {
	int32_t v7; // r4
	int32_t depth; // r0

	v7 = oldhigh;
	depth = this->getDepth(level, x, y, z);
	if(depth >= 0) {
		if(depth) {
			if(depth > 7) {
				depth = 0;
			}
		} else {
			++this->field_D8;
		}
		if(oldhigh < 0) {
			return depth;
		} else if(oldhigh >= depth) {
			return depth;
		}
	}
	return v7;
}
int32_t LiquidTileDynamic::getSlopeDistance(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7) {
	int32_t v11; // r4
	int32_t v12; // r11
	int32_t v13; // r5
	int32_t v14; // r6
	int32_t slope; // r0
	int32_t v17; // [sp+10h] [bp-30h]

	v17 = y - 1;
	v11 = 0;
	v12 = 1000;
	do {
		switch(v11) {
			case 0:
				if(a7 == 1) {
					goto LABEL_27;
				}
				v13 = x - 1;
				goto LABEL_19;
			case 1:
				if(!a7) {
					goto LABEL_27;
				}
				v13 = x + 1;
				goto LABEL_19;
			case 2:
				if(a7 == 3) {
					goto LABEL_27;
				}
				v14 = z - 1;
				break;
			case 3:
				if(a7 == 2) {
					goto LABEL_27;
				}
				v14 = z + 1;
				break;
			default:
				v13 = x;
LABEL_19:
				v14 = z;
				goto LABEL_20;
		}
		v13 = x;
LABEL_20:
		if(!this->isWaterBlocking(level, v13, y, v14) && (this->material != level->getMaterial(v13, y, v14) || level->getData(v13, y, v14))) {
			if(!this->isWaterBlocking(level, v13, v17, v14)) {
				return a6;
			}
			if(a6 <= 3) {
				slope = this->getSlopeDistance(level, v13, y, v14, a6 + 1, v11);
				if(v12 >= slope) {
					v12 = slope;
				}
			}
		}
LABEL_27:
		++v11;
	} while(v11 != 4);
	return v12;
}
bool_t* LiquidTileDynamic::getSpread(Level* level, int32_t x, int32_t y, int32_t z) {
	LiquidTileDynamic* v8; // r9
	int32_t v9; // r7
	int32_t v11; // r6
	int32_t v12; // r5
	int32_t v13; // r2
	int32_t i; // r3
	int32_t* v15; // r0
	int32_t isWaterBlocking; // r0
	int32_t v19; // [sp+14h] [bp-2Ch]

	v8 = this;
	v9 = 0;
	v19 = y - 1;
	do {
		v8->field_E0[v9] = 1000;
		if(v9) {
			if(v9 != 1) {
				if(v9 == 2) {
					v12 = z - 1;
				} else {
					if(v9 != 3) {
						v11 = x;
						goto LABEL_12;
					}
					v12 = z + 1;
				}
				v11 = x;
				goto LABEL_13;
			}
			v11 = x + 1;
		} else {
			v11 = x - 1;
		}
LABEL_12:
		v12 = z;
LABEL_13:
		if(!this->isWaterBlocking(level, v11, y, v12) && (this->material != level->getMaterial(v11, y, v12) || level->getData(v11, y, v12))) {
			isWaterBlocking = this->isWaterBlocking(level, v11, v19, v12);
			if(isWaterBlocking) {
				isWaterBlocking = this->getSlopeDistance(level, v11, y, v12, 1, v9);
			}
			v8->field_E0[v9] = isWaterBlocking;
		}
		++v9;
	} while(v9 != 4);
	v13 = this->field_E0[1];
	if(v13 >= this->field_E0[0]) {
		v13 = this->field_E0[0];
	}
	if(v13 >= this->field_E0[2]) {
		v13 = this->field_E0[2];
	}
	if(v13 >= this->field_E0[3]) {
		v13 = this->field_E0[3];
	}
	for(i = 0; i != 4; ++i) {
		this->field_DC[i] = this->field_E0[i] == v13;
	}
	return this->field_DC;
}
bool_t LiquidTileDynamic::isWaterBlocking(Level* level, int32_t x, int32_t y, int32_t z) {
	Tile* v5; // r4

	v5 = Tile::tiles[level->getTile(x, y, z)];
	if(!v5) {
		return 0;
	}
	if(v5 == Tile::door_wood || v5 == Tile::sign || v5 == Tile::ladder || v5 == Tile::reeds) {
		return 1;
	}
	if(v5->getThickness() > 0.0) {
		return 0;
	}

	if(v5->material->blocksMotion()) {
		return 1;
	} else {
		return v5->material->isSolid();
	}
}
void LiquidTileDynamic::setStatic(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v9; // r0

	v9 = level->getData(x, y, z);
	level->setTileAndDataNoUpdate(x, y, z, this->blockID + 1, v9);
	level->setTilesDirty(x, y, z, x, y, z);
	level->sendTileUpdated(x, y, z);
}
void LiquidTileDynamic::trySpreadTo(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
	int32_t v10; // r0
	Tile* v11;	 // r9
	int32_t v13; // r0

	if(this->canSpreadTo(level, x, y, z)) {
		v10 = level->getTile(x, y, z);
		if(v10 > 0) {
			if(this->material == Material::lava) {
				this->fizz(level, x, y, z);
			} else {
				v11 = Tile::tiles[v10];
				v11->spawnResources(level, x, y, z, level->getData(x, y, z));
			}
		}
		level->setTileAndData(x, y, z, this->blockID, a6, 3);
	}
}

LiquidTileDynamic::~LiquidTileDynamic() {
}
void LiquidTileDynamic::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
	int32_t depth;		 // r10
	int32_t v10;		 // r3
	int32_t tickDelay;	 // r7
	int32_t vv;			 // r0
	int32_t v13;		 // r0
	int32_t v14;		 // r0
	int32_t highest;	 // r0
	int32_t v16;		 // r9
	int32_t dpth;		 // r0
	int32_t v18;		 // r10
	bool_t* Spread;		 // r0
	int32_t oldid;		 // [sp+0h] [bp-58h]
	int32_t v22;		 // [sp+4h] [bp-54h]
	int32_t spreadAdder; // [sp+20h] [bp-38h]

	depth = this->getDepth(level, x, y, z);
	if(this->material == Material::lava) {
		if(level->dimensionPtr->isOverworldMaybe) {
			v10 = 1;
		} else {
			v10 = 2;
		}
		spreadAdder = v10;
		this->_trySpreadFire(level, x, y, z, rng);
	} else {
		spreadAdder = 1;
	}
	tickDelay = this->getTickDelay();
	if(depth > 0) {
		this->field_D8 = 0;
		vv = this->getHighest(level, x - 1, y, z, -100);
		v13 = this->getHighest(level, x + 1, y, z, vv);
		v14 = this->getHighest(level, x, y, z - 1, v13);
		highest = this->getHighest(level, x, y, z + 1, v14);
		if(highest + spreadAdder > 7) {
			v16 = -1;
		} else {
			v16 = (highest + spreadAdder) & ~(highest >> 31);
			if(highest < 0) {
				v16 = -1;
			}
		}
		if(this->getDepth(level, x, y + 1, z) >= 0) {
			dpth = this->getDepth(level, x, y + 1, z);
			if(dpth > 7) {
				v16 = dpth;
			} else {
				v16 = dpth + 8;
			}
		}
		if(this->field_D8 > 1 && this->material == Material::water && (level->isSolidBlockingTile(x, y - 1, z) || this->material == level->getMaterial(x, y - 1, z) && !level->getData(x, y, z))) {
			v16 = 0;
		}
		if(this->material == Material::lava && depth <= 7) {
			if(v16 > 7) {
				goto LABEL_32;
			}
			if(v16 > depth) {
				if(rng->genrand_int32() << 30) {
					tickDelay *= 4;
				}
LABEL_30:
				if(v16 < 0) {
					level->setTile(x, y, z, 0, 3);
LABEL_33:
					depth = v16;
					goto LABEL_35;
				}
LABEL_32:
				level->setData(x, y, z, v16, 2);
				level->addToTickNextTick(x, y, z, this->blockID, tickDelay);
				level->updateNeighborsAt(x, y, z, this->blockID);
				goto LABEL_33;
			}
		}
		if(v16 != depth) {
			goto LABEL_30;
		}
	}
	this->setStatic(level, x, y, z);
LABEL_35:
	if(this->canSpreadTo(level, x, y - 1, z)) {
		if(this->material == Material::lava && Material::water == level->getMaterial(x, y - 1, z)) {
			level->setTile(x, y - 1, z, Tile::rock->blockID, 3);
			this->fizz(level, x, y - 1, z);
		} else {
			if(depth > 7) {
				v22 = depth;
			}
			oldid = this->blockID;
			if(depth <= 7) {
				v22 = depth + 8;
			}
			level->setTileAndData(x, y - 1, z, this->blockID, v22, 3);
		}
	} else if(depth >= 0 && (!depth || this->isWaterBlocking(level, x, y - 1, z))) {
		Spread = this->getSpread(level, x, y, z);
		if(depth > 7) {
			v18 = 1;
		} else {
			v18 = depth + spreadAdder;
			if(v18 > 7) {
				return;
			}
		}
		if(Spread[0]) {
			this->trySpreadTo(level, x - 1, y, z, v18);
		}
		if(Spread[1]) {
			this->trySpreadTo(level, x + 1, y, z, v18);
		}
		if(Spread[2]) {
			this->trySpreadTo(level, x, y, z - 1, v18);
		}
		if(Spread[3]) {
			this->trySpreadTo(level, x, y, z + 1, v18);
		}
	}
}
void LiquidTileDynamic::onPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	this->updateLiquid(level, x, y, z);
	int32_t id = level->getTile(x, y, z);
	if(id == this->blockID) {
		level->addToTickNextTick(x, y, z, id, this->getTickDelay());
	}
}
