#include <tile/BaseRailTile.hpp>
#include <math/HitResult.hpp>
#include <tile/material/Material.hpp>
#include <level/Level.hpp>

BaseRailTile::Rail::Rail(struct Level* a2, int32_t x, int32_t y, int32_t z) {
	this->level = a2;
	this->x = x;
	this->y = y;
	this->z = z;
	int32_t v9 = a2->getTile(x, y, z);
	int32_t v10 = a2->getData(x, y, z);
	this->field_10 = ((BaseRailTile*)Tile::tiles[v9])->useDataBit;
	this->updateConnections(v10);
}
bool_t BaseRailTile::Rail::canConnectTo(BaseRailTile::Rail* a2) {
	return this->connectsTo(a2) || this->connections.size() != 2;
}
void BaseRailTile::Rail::connectTo(BaseRailTile::Rail* a2) {
	bool_t hasConnection; // r7
	bool_t v6; // r6
	bool_t v7; // r8
	bool_t v8; // r0
	int32_t v9; // r5
	TilePos m{a2->x, a2->y, a2->z};
	this->connections.emplace_back(m);
	hasConnection = this->hasConnection(this->x, this->y, this->z - 1);
	v6 = this->hasConnection(this->x, this->y, this->z + 1);
	v7 = this->hasConnection(this->x - 1, this->y, this->z);
	v8 = this->hasConnection(this->x + 1, this->y, this->z);
	if(hasConnection) {
		v9 = 0;
	} else if(v6) {
		v9 = 0;
	} else {
		v9 = -1;
	}
	if(v7) {
		v9 = 1;
	} else if(v8) {
		v9 = 1;
	}
	if(!this->field_10) {
		if(v6) {
			if(v8) {
				if(!hasConnection && !v7) {
					v9 = 6;
					goto LABEL_42;
				}
				goto LABEL_25;
			}
			if(v7) {
				if(!hasConnection) {
					v9 = 7;
					goto LABEL_42;
				}
				goto LABEL_25;
			}
		}
		if(hasConnection) {
			if(v7) {
				if(!v6 && !v8) {
					v9 = 8;
					goto LABEL_42;
				}
			} else if(v8 && !v6) {
				v9 = 9;
				goto LABEL_42;
			}
		}
	}
LABEL_25:
	if(!v9 && (!BaseRailTile::isRail(this->level, this->x, this->y + 1, this->z - 1) ? (v9 = 0) : (v9 = 4), BaseRailTile::isRail(this->level, this->x, this->y + 1, this->z + 1))) {
		v9 = 5;
	} else if(v9 == 1) {
		if(BaseRailTile::isRail(this->level, this->x + 1, this->y + 1, this->z)) {
			v9 = 2;
		} else {
			v9 = 1;
		}
		if(BaseRailTile::isRail(this->level, this->x - 1, this->y + 1, this->z)) {
			v9 = 3;
		}
	} else if(v9 == -1) {
		v9 = 0;
	}
LABEL_42:
	if(this->field_10) {
		this->level->getData(this->x, this->y, this->z);
	}
	this->level->setData(this->x, this->y, this->z, v9, 3);
}
bool_t BaseRailTile::Rail::connectsTo(BaseRailTile::Rail* a2) {
	for(auto& a: this->connections) {
		if(a.x == a2->x && a.z == a2->z) return 1;
	}
	return 0;
}
int32_t BaseRailTile::Rail::countPotentialConnections() {
	int32_t hasRail; // r5

	hasRail = this->hasRail(this->x, this->y, this->z - 1);
	if(this->hasRail(this->x, this->y, this->z + 1)) {
		++hasRail;
	}
	if(this->hasRail(this->x - 1, this->y, this->z)) {
		++hasRail;
	}
	if(this->hasRail(this->x + 1, this->y, this->z)) {
		++hasRail;
	}
	return hasRail;
}
std::shared_ptr<BaseRailTile::Rail> BaseRailTile::Rail::getRail(const TilePos& a3) {
	if(BaseRailTile::isRail(this->level, a3.x, a3.y, a3.z)) {
		return std::shared_ptr<BaseRailTile::Rail>(new BaseRailTile::Rail(this->level, a3.x, a3.y, a3.z));
	}
	if(BaseRailTile::isRail(this->level, a3.x, a3.y+1, a3.z)) {
		return std::shared_ptr<BaseRailTile::Rail>(new BaseRailTile::Rail(this->level, a3.x, a3.y+1, a3.z));
	}
	if(BaseRailTile::isRail(this->level, a3.x, a3.y-1, a3.z)) {
		return std::shared_ptr<BaseRailTile::Rail>(new BaseRailTile::Rail(this->level, a3.x, a3.y-1, a3.z));
	}

	return 0;
}
bool_t BaseRailTile::Rail::hasConnection(int32_t a2, int32_t a3, int32_t a4) {
	for(auto& a: this->connections) {
		if(a.x == a2 && a.z == a4) return 1;
	}
	return 0;
}
bool_t BaseRailTile::Rail::hasNeighborRail(int32_t x, int32_t y, int32_t z) {
	TilePos v9{x, y, z};
	std::shared_ptr<BaseRailTile::Rail> v8 = this->getRail(v9);
	if(v8) {
		v8->removeSoftConnections();
		return v8->canConnectTo(this);
	}
	return 0;
}
bool_t BaseRailTile::Rail::hasRail(int32_t x, int32_t y, int32_t z) {
	return BaseRailTile::isRail(this->level, x, y, z) || BaseRailTile::isRail(this->level, x, y + 1, z) || BaseRailTile::isRail(this->level, x, y - 1, z);
}
void BaseRailTile::Rail::place(bool_t a2, bool_t a3) {
	bool_t v3; // r10
	bool_t v4; // r9
	bool_t hasNeighborRail; // r7
	bool_t v7; // r8
	bool_t v8; // r6
	bool_t v9; // r0
	int32_t v10; // r5
	int32_t v11; // r5
	uint32_t v12; // r5

	v3 = a2;
	v4 = a3;
	hasNeighborRail = this->hasNeighborRail(this->x, this->y, this->z - 1);
	v7 = this->hasNeighborRail(this->x, this->y, this->z + 1);
	v8 = this->hasNeighborRail(this->x - 1, this->y, this->z);
	v9 = this->hasNeighborRail(this->x + 1, this->y, this->z);
	if(!hasNeighborRail && !v7) {
		if(v8) {
			v10 = 1;
			goto LABEL_15;
		}
LABEL_7:
		v10 = -1;
		if(!v9) {
			goto LABEL_15;
		}
		goto LABEL_10;
	}
	if(!v8) {
		if(!v9) {
			v10 = 0;
			goto LABEL_15;
		}
		goto LABEL_7;
	}
	v10 = -1;
LABEL_10:
	if(!hasNeighborRail) {
		if(v7) {
			v10 = -1;
		} else {
			v10 = 1;
		}
	}
LABEL_15:
	if(this->field_10) {
		goto LABEL_29;
	}
	if(v7) {
		if(v9) {
			if(!hasNeighborRail && !v8) {
				goto LABEL_98;
			}
			goto LABEL_29;
		}
		if(v8) {
			if(!hasNeighborRail) {
				v11 = 7;
				goto LABEL_81;
			}
			goto LABEL_29;
		}
	}
	if(hasNeighborRail) {
		if(v8) {
			if(!v7 && !v9) {
				goto LABEL_97;
			}
		} else if(v9 && !v7) {
			v11 = 9;
			goto LABEL_81;
		}
	}
LABEL_29:
	if(v10 != -1) {
		goto LABEL_67;
	}
	if(hasNeighborRail) {
		v10 = 0;
	} else {
		v10 = v7 ? 0 : -1;
	}
	if(v8) {
		v10 = 1;
	} else if(v9) {
		v10 = 1;
	}
	if(this->field_10) {
		goto LABEL_67;
	}
	if(!v3) {
		if(hasNeighborRail) {
			if(v8) {
				v10 = 8;
			}
			if(v9) {
				v10 = 9;
			}
		}
		if(v8) {
			if(!v7) {
				goto LABEL_67;
			}
			v10 = 7;
		} else if(!v7) {
			goto LABEL_67;
		}
		if(v9) {
LABEL_98:
			v11 = 6;
			goto LABEL_81;
		}
		goto LABEL_67;
	}
	if(v7) {
		if(v9) {
			v10 = 6;
		}
		if(v8) {
			v10 = 7;
		}
	}
	if(!v9) {
		if(!hasNeighborRail) {
			goto LABEL_67;
		}
		goto LABEL_53;
	}
	if(hasNeighborRail) {
		v10 = 9;
LABEL_53:
		if(!v8) {
			goto LABEL_67;
		}
LABEL_97:
		v11 = 8;
		goto LABEL_81;
	}
LABEL_67:
	if(!v10 && (!BaseRailTile::isRail(this->level, this->x, this->y + 1, this->z - 1) ? (v10 = 0) : (v10 = 4), BaseRailTile::isRail(this->level, this->x, this->y + 1, this->z + 1))) {
		v11 = 5;
	} else if(v10 == 1) {
		if(BaseRailTile::isRail(this->level, this->x + 1, this->y + 1, this->z)) {
			v11 = 2;
		} else {
			v11 = 1;
		}
		if(BaseRailTile::isRail(this->level, this->x - 1, this->y + 1, this->z)) {
			v11 = 3;
		}
	} else {
		v11 = v10 & ~(v10 >> 31);
	}
LABEL_81:
	this->updateConnections(v11);
	if(this->field_10) {
		this->level->getData(this->x, this->y, this->z);
	}
	if(v4 || this->level->getData(this->x, this->y, this->z) != v11) {
		//v14 = v11;
		this->level->setData(this->x, this->y, this->z, v11 /*v14*/, 3);

		for(auto& railCon: this->connections) {
			std::shared_ptr<BaseRailTile::Rail> a1 = this->getRail(railCon);
			if(a1) {
				a1->removeSoftConnections();
				if(a1->canConnectTo(this)) a1->connectTo(this);
			}
		}
	}
}
void BaseRailTile::Rail::removeSoftConnections() {
	auto&& railCon = this->connections.begin();

	for(; railCon != this->connections.end();) { //TODO cheeck
		std::shared_ptr<BaseRailTile::Rail> a1 = this->getRail(*railCon);
		if(a1 && a1->connectsTo(this)) {
			(*railCon).x = a1->x;
			(*railCon).y = a1->y;
			(*railCon).z = a1->z;
			++railCon;
		} else {
			this->connections.erase(railCon);
		}
	}
}
void BaseRailTile::Rail::updateConnections(int32_t a2) {
	int32_t y;		 // r3
	int32_t x;		 // r2
	int32_t v6;		 // r2
	int32_t z;		 // r3
	int32_t v8;		 // r2
	int32_t v9;		 // r3
	int32_t v10;	 // r2
	int32_t v11;	 // r2
	int32_t v12;	 // r3
	int32_t v13;	 // r1
	int32_t v14;	 // r3
	int32_t v15;	 // r2
	int32_t v16;	 // r3
	int32_t v17;	 // r3
	int32_t v18;	 // r2
	int32_t v19;	 // r3
	int32_t v20;	 // r2
	int32_t v21;	 // r3
	int32_t v22;	 // r2
	int32_t v23;	 // r3
	int32_t v24;	 // r1
	int32_t v25;	 // r3
	int32_t v26;	 // r1
	int32_t v27;	 // r2
	int32_t v28;	 // r3
	int32_t v29;	 // r1
	int32_t v30;	 // r2
	TilePos tilePos; // [sp+4h] [bp-1Ch] BYREF

	this->connections.clear();
	switch(a2) {
		case 0:
			y = this->y;
			x = this->x;
			tilePos.z = this->z - 1;
			tilePos.y = y;
			tilePos.x = x;
			goto LABEL_20;
		case 1:
			v6 = this->y;
			z = this->z;
			tilePos.x = this->x - 1;
			tilePos.y = v6;
LABEL_9:
			tilePos.z = z;
			this->connections.emplace_back(tilePos);
			v10 = this->y;
			goto LABEL_10;
		case 2:
			v8 = this->y;
			v9 = this->z;
			tilePos.x = this->x - 1;
			tilePos.y = v8;
			tilePos.z = v9;
			this->connections.emplace_back(tilePos);
			v10 = this->y + 1;
LABEL_10:
			v12 = this->z;
			v13 = this->x;
			tilePos.y = v10;
			tilePos.z = v12;
			tilePos.x = v13 + 1;
			goto LABEL_27;
		case 3:
			z = this->z;
			v11 = this->x - 1;
			tilePos.y = this->y + 1;
			tilePos.x = v11;
			goto LABEL_9;
		case 4:
			v14 = this->z;
			tilePos.y = this->y + 1;
			v15 = v14 - 1;
			v16 = this->x;
			tilePos.z = v15;
			tilePos.x = v16;
			goto LABEL_20;
	}
	if(a2 != 5) {
		if(a2 == 6) {
			v22 = this->y;
			v23 = this->z;
			v24 = this->x + 1;
		} else {
			if(a2 != 7) {
				if(a2 == 8) {
					v27 = this->y;
					v28 = this->z;
					v29 = this->x - 1;
				} else {
					if(a2 != 9) {
						return;
					}
					v27 = this->y;
					v28 = this->z;
					v29 = this->x + 1;
				}
				tilePos.x = v29;
				tilePos.y = v27;
				tilePos.z = v28;
				this->connections.emplace_back(tilePos);
				v25 = this->y;
				v26 = this->z - 1;
				goto LABEL_26;
			}
			v22 = this->y;
			v23 = this->z;
			v24 = this->x - 1;
		}
		tilePos.x = v24;
		tilePos.y = v22;
		tilePos.z = v23;
LABEL_20:
		this->connections.emplace_back(tilePos);
		v25 = this->y;
		v26 = this->z + 1;
LABEL_26:
		v30 = this->x;
		tilePos.y = v25;
		tilePos.z = v26;
		tilePos.x = v30;
		goto LABEL_27;
	}
	v17 = this->y;
	v18 = this->x;
	tilePos.z = this->z - 1;
	tilePos.y = v17;
	tilePos.x = v18;
	this->connections.emplace_back(tilePos);
	v19 = this->z;
	tilePos.y = this->y + 1;
	v20 = v19 + 1;
	v21 = this->x;
	tilePos.z = v20;
	tilePos.x = v21;
LABEL_27:
	this->connections.emplace_back(tilePos);
}

BaseRailTile::BaseRailTile(int32_t a2, bool_t a3)
	: Tile(a2, Material::decoration) {
	this->useDataBit = a3;
	this->setShape(0, 0, 0, 1, 0.125, 1);
	this->textureUV = this->getTextureUVCoordinateSet("rail_normal", 0);
}

BaseRailTile::~BaseRailTile() {
}
bool_t BaseRailTile::isCubeShaped() {
	return 0;
}
int32_t BaseRailTile::getRenderShape() {
	return 9;
}
void BaseRailTile::updateShape(LevelSource* a2, int32_t a3, int32_t a4, int32_t a5) {
	float v6;
	if((uint32_t)(a2->getData(a3, a4, a5) - 2) > 3) v6 = 0.125;
	else v6 = 0.625;
	this->setShape(0, 0, 0, 1, v6, 1);
}
AABB* BaseRailTile::getAABB(Level*, int32_t, int32_t, int32_t) {
	return 0;
}
bool_t BaseRailTile::isSolidRender() {
	return 0;
}
bool_t BaseRailTile::mayPlace(Level* a2, int32_t a3, int32_t a4, int32_t a5) {
	return a2->isTopSolidBlocking(a3, a4 - 1, a5);
}
void BaseRailTile::neighborChanged(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	if(a2->isClientMaybe) return;
	int32_t v15 = a2->getData(a3, a4, a5);
	int32_t v14 = v15;
	if(this->useDataBit) v15 &= 7;
	bool_t v16 = !a2->isTopSolidBlocking(a3, a4 - 1, a5);
	int32_t v18, v19, v20;
	switch(v15) {
		case 2:
			v18 = a3 + 1;
			v19 = a4;
			v20 = a5;
			goto LABEL_11;
		case 3:
			v18 = a3 - 1;
			v19 = a4;
			v20 = a5;
			goto LABEL_11;
		case 4:
			v18 = a3;
			v19 = a4;
			v20 = a5 - 1;
			goto LABEL_11;
		case 5:
			v20 = a5 + 1;
			v18 = a3;
			v19 = a4;
LABEL_11:
			if(!a2->isTopSolidBlocking(v18, v19, v20)) {
LABEL_12:
				this->spawnResources(a2, a3, a4, a5, a2->getData(a3, a4, a5), 1);
				a2->removeTile(a3, a4, a5);
				return;
			}
			break;
	}
	if(v16) goto LABEL_12;
	this->updateState(a2, a3, a4, a5, v14, v15, a9);
}
void BaseRailTile::onPlace(Level* a2, int32_t a3, int32_t a4, int32_t a5) {
	if(!a2->isClientMaybe) {
		this->updateDir(a2, a3, a4, a5, 1);
		if(this->useDataBit) {
			this->neighborChanged(a2, a3, a4, a5, a3, a4, a5, this->blockID);
		}
	}
}
void BaseRailTile::onRemove(Level* a2, int32_t a3, int32_t a4, int32_t a5) {
	int32_t v9 = a2->getData(a3, a4, a5);
	if(this->useDataBit) v9 &= 7;
	if((uint32_t)(v9 - 2) <= 3) a2->updateNeighborsAt(a3, a4 + 1, a5, this->blockID);
	if(this->useDataBit) {
		a2->updateNeighborsAt(a3, a4, a5, this->blockID);
		a2->updateNeighborsAt(a3, a4 - 1, a5, this->blockID);
	}
}
int32_t BaseRailTile::getResourceCount(Random*) {
	return 1;
}
HitResult BaseRailTile::clip(Level* a3, int32_t a4, int32_t a5, int32_t a6, const Vec3& a7, const Vec3& a8) {
	this->updateShape(a3, a4, a5, a6);
	return Tile::clip(a3, a4, a5, a6, a7, a8);
}
int32_t BaseRailTile::getRenderLayer() {
	return 1;
}
float BaseRailTile::getThickness() {
	return 0.07;
}
void BaseRailTile::updateState(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t) {
}
bool_t BaseRailTile::blocksLight() {
	return 0;
}
bool_t BaseRailTile::isRail(struct Level* level, int32_t x, int32_t y, int32_t z) {
	return BaseRailTile::isRail(level->getTile(x, y, z));
}
bool_t BaseRailTile::isRail(int32_t a1) {
	return a1 == Tile::rail->blockID || a1 == Tile::goldenRail->blockID;
}
bool_t BaseRailTile::isUsesDataBit() {
	return this->useDataBit;
}
void BaseRailTile::updateDir(Level* a2, int32_t a3, int32_t a4, int32_t z, bool_t a6) {
	if(!a2->isClientMaybe) {
		BaseRailTile::Rail v10(a2, a3, a4, z);
		bool_t hasNeighborSignal = a2->hasNeighborSignal(a3, a4, z);
		v10.place(hasNeighborSignal, a6);
		//~v10
	}
}
