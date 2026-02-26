#include <tile/BedTile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <math/Direction.hpp>
#include <entity/Player.hpp>
#include <level/dimension/Dimension.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

int32_t BedTile::HEAD_DIRECTION_OFFSETS[] = {0, 1, -1, 0, 0, -1, 1, 0};

BedTile::BedTile(int32_t id)
	: DirectionalTile(id, Material::cloth) {
	TextureAtlasTextureItem v35(*this->getTextureItem("bed"));
	this->field_B0 = *v35.getUV(0);
	this->field_80 = *v35.getUV(1);
	this->field_98 = *v35.getUV(2);
	this->field_F8 = *v35.getUV(3);
	this->field_C8 = *v35.getUV(4);
	this->field_E0 = *v35.getUV(5);
}

void BedTile::_setShape(void) {
	this->setShape(0, 0, 0, 1, 0.5625, 1);
}
bool_t BedTile::findStandUpPosition(Level* a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, struct Pos& a6) {
	int32_t v8; // r7
	int32_t v9; // r9
	int32_t v10; // r4
	int32_t v11; // r3
	int32_t v12; // r2
	int32_t v13; // r4
	int32_t i; // r5
	int32_t result; // r0
	int32_t v16; // [sp+8h] [bp-40h]
	int32_t v17; // [sp+Ch] [bp-3Ch]
	int32_t v18; // [sp+10h] [bp-38h]
	int32_t v21; // [sp+1Ch] [bp-2Ch]

	v8 = 0;
	v9 = a1->getData(a2, a3, a4) & 3;
	v21 = BedTile::HEAD_DIRECTION_OFFSETS[2 * v9 + 1];
	while(1) {
		v10 = a2 - BedTile::HEAD_DIRECTION_OFFSETS[2 * v9] * v8;
		v11 = a4 - v21 * v8;
		v12 = v10 + 1;
		v13 = v10 - 1;
		v17 = v12;
		v16 = v11 - 1;
		v18 = v11 + 1;
LABEL_11:
		if(v13 <= v17) {
			break;
		}
		if(++v8 == 2) {
			return 0;
		}
	}
	for(i = v16;; ++i) {
		if(i > v18) {
			++v13;
			goto LABEL_11;
		}
		if(a1->isSolidBlockingTile(v13, a3 - 1, i) && a1->isEmptyTile(v13, a3, i) && a1->isEmptyTile(v13, a3 + 1, i)) {
			break;
		}
LABEL_8:;
	}
	if(a5 > 0) {
		--a5;
		goto LABEL_8;
	}
	result = 1;
	a6.x = v13;
	a6.y = a3;
	a6.z = i;
	return result;
}
void BedTile::setOccupied(Level* a1, int32_t a2, int32_t a3, int32_t a4, bool_t a5) {
	int32_t v5; // r6
	int32_t v9; // r0
	int32_t v10; // r0

	v5 = a4;
	v9 = a1->getData(a2, a3, a4);
	if(a5) {
		v10 = v9 | 4;
	} else {
		v10 = v9 & 0xFFFFFFFB;
	}
	a1->setData(a2, a3, v5, v10, 2);
}

bool_t BedTile::isHeadPiece(int32_t a1) {
	return (a1 >> 3) & 1;
}
bool_t BedTile::isOccupied(int32_t a1) {
	return ((uint32_t)a1 >> 2) & 1;
}

BedTile::~BedTile() {
}
bool_t BedTile::isCubeShaped() {
	return 0;
}
int32_t BedTile::getRenderShape() {
	return 14;
}
void BedTile::updateShape(LevelSource*, int32_t, int32_t, int32_t) {
	return this->_setShape();
}
TextureUVCoordinateSet* BedTile::getTexture(int32_t a2, int32_t a3) {
	if(!a2) {
		return &Tile::wood->textureUV;
	}
	int32_t v5 = Direction::RELATIVE_DIRECTION_FACING[6 * (a3 & 3) + a2];
	if(BedTile::isHeadPiece(a3)) {
		if(v5 == 2) {
			return &this->field_C8;
		} else if((uint32_t)(v5 - 4) > 1) {
			return &this->field_F8;
		} else {
			return &this->field_E0;
		}
	} else if(v5 == 3) {
		return &this->field_80;
	} else if((uint32_t)(v5 - 4) > 1) {
		return &this->field_B0;
	} else {
		return &this->field_98;
	}
}
bool_t BedTile::isSolidRender() {
	return 0;
}
void BedTile::neighborChanged(Level* level, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	uint32_t v13 = level->getData(a3, a4, a5);
	int32_t v14 = v13 & 3;

	int32_t off1 = BedTile::HEAD_DIRECTION_OFFSETS[2 * v14];
	int32_t off2 = BedTile::HEAD_DIRECTION_OFFSETS[2 * v14 + 1];

	if(BedTile::isHeadPiece(v13)) {
		if(level->getTile(a3 - off1, a4, a5 - off2) != this->blockID) level->setTile(a3, a4, a5, 0, 3);
	} else if(level->getTile(a3 + off1, a4, a5 + off2) != this->blockID) {
		level->setTile(a3, a4, a5, 0, 3);
		if(!level->isClientMaybe) {
			this->popResource(level, a3, a4, a5, ItemInstance(Item::bed));
		}
	}
}
int32_t BedTile::getResource(int32_t a2, Random* a3) {
	if(BedTile::isHeadPiece(a2)) return 0;
	return Item::bed->itemID;
}
void BedTile::spawnResources(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, float a7){
	if(!BedTile::isHeadPiece(a6)){
		this->popResource(a2, a3, a4, a5, ItemInstance(Item::bed));
	}
}
int32_t BedTile::getRenderLayer() {
	return 1;
}
bool_t BedTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	int32_t v10;		  // r5
	int32_t bedPositionY; // r2
	int32_t bedPositionX; // r3
	int32_t v13;		  // r0
	int32_t bedPositionZ; // r1
	int32_t v15;		  // r3
	int32_t v16;		  // r0
	int32_t v17;		  // r1
	uint32_t v18;		  // r9
	int32_t v19;		  // r9
	int32_t v20;		  // r9
	int32_t v21;		  // r6
	int32_t v22;		  // r8
	int32_t v26;		  // r0

	v10 = z;
	if(!player->isSleeping()) {
		goto LABEL_45;
	}
	bedPositionY = player->bedPosition.y;
	bedPositionX = player->bedPosition.x;
	v13 = bedPositionY == y;
	bedPositionZ = player->bedPosition.z;
	if(bedPositionX == x) {
		++v13;
	}
	if(bedPositionZ == z) {
		++v13;
	}
	if(v13 <= 1) {
		goto LABEL_45;
	}
	v15 = bedPositionX - x;
	v16 = abs(bedPositionZ - z); //abs32
	v17 = bedPositionY - y;
	if(bedPositionY - y < 0) {
		v17 = y - bedPositionY;
	}
	if(v15 < 0) {
		v15 = -v15;
	}
	if(v17 < v15) {
		v17 = v15;
	}
	if(v17 < v16) {
		v17 = v16;
	}
	if(v17 <= 2) {
		player->stopSleepInBed(0, 1, 1);
	} else {
LABEL_45:
		if(!level->isClientMaybe) {
			v18 = level->getData(x, y, z);
			if(!BedTile::isHeadPiece(v18)) {
				v19 = v18 & 3;
				x += BedTile::HEAD_DIRECTION_OFFSETS[2 * v19];
				v10 = z + BedTile::HEAD_DIRECTION_OFFSETS[2 * v19 + 1];
				if(level->getTile(x, y, v10) != this->blockID) {
					return 1;
				}
				v18 = level->getData(x, y, v10);
			}
			if(level->dimensionPtr->mayRespawn()) {
				if(BedTile::isOccupied(v18)) {
					for(auto&& player2: level->playersMaybe) {
						if(player2->isSleeping()) {
							if(player2->bedPosition.x == x && player->bedPosition.y == y && player->bedPosition.z == v10) {
								player2->displayClientMessage("This bed is occupied");
								return 1;
							}
						}
					}
					BedTile::setOccupied(level, x, y, v10, 0);
					goto LABEL_33;
				} else {
LABEL_33:
					v26 = player->startSleepInBed(x, y, v10);
					switch(v26) {
						case 0:
							BedTile::setOccupied(level, x, y, v10, 1);
							return 1;
						case 2:
							player->displayClientMessage("You can only sleep at night");
							return 1;
						case 5:
							player->displayClientMessage("You may not rest now, there are monsters nearby");
							return 1;
						default:
							return 1;
					}
				}
				return 1;
			}
			level->setTile(x, y, v10, 0, 3);
			v20 = v18 & 3;
			v21 = x + BedTile::HEAD_DIRECTION_OFFSETS[2 * v20];
			v22 = y + BedTile::HEAD_DIRECTION_OFFSETS[2 * v20 + 1];
			if(level->getTile(v21, v22, v10) == this->blockID) {
				level->setTile(v21, v22, v10, 0, 3);
			}
			level->explode(0, (float)v21 + 0.5, (float)v22 + 0.5, (float)v10 + 0.5, 5.0, 1);
		}
	}
	return 1;
}
