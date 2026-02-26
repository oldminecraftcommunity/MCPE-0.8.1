#include <level/LightUpdate.hpp>
#include <level/Level.hpp>
#include <level/LightLayer.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <tile/Tile.hpp>

LightUpdate::LightUpdate(const LightLayer& ll, int32_t minX, int32_t minY, int32_t minZ, int32_t maxX, int32_t maxY, int32_t maxZ) {
	this->layer = &ll;
	this->minX = minX;
	this->minY = minY;
	this->minZ = minZ;
	this->maxX = maxX;
	this->maxY = maxY;
	this->maxZ = maxZ;
}
LightUpdate::LightUpdate(const LightUpdate& a2) {
	*this = a2;
}
LightUpdate::LightUpdate(const LightUpdate* a2) {
	*this = *a2;
}
bool_t LightUpdate::expandToContain(int32_t newMinX, int32_t newMinY, int32_t newMinZ, int32_t a5, int32_t a6, int32_t a7) {
	int32_t minX;	 // r4
	int32_t newMaxX; // r7
	int32_t minY;	 // r8
	int32_t maxX;	 // r10
	int32_t maxY;	 // r9
	int32_t maxZ;	 // r12
	int32_t newMaxZ; // r6
	int32_t newMaxY; // r11
	int32_t v15;	 // r5
	int32_t minZ;	 // [sp+8h] [bp-30h]

	minX = this->minX;
	newMaxX = a5;
	if(newMinX >= minX && newMinY >= this->minY && newMinZ >= this->minZ && a5 <= this->maxX && a6 <= this->maxY && a7 <= this->maxZ) {
		return 1;
	}
	if(newMinX >= minX - 1) {
		minY = this->minY;
		if(newMinY >= minY - 1) {
			minZ = this->minZ;
			if(newMinZ >= minZ - 1) {
				maxX = this->maxX;
				if(a5 <= maxX + 1) {
					maxY = this->maxY;
					if(a6 <= maxY + 1) {
						maxZ = this->maxZ;
						newMaxZ = a7;
						if(a7 <= maxZ + 1) {
							newMaxY = a6;
							if(newMinX >= minX) {
								newMinX = this->minX;
							}
							v15 = this->minZ;
							if(newMinY >= minY) {
								newMinY = this->minY;
							}
							if(a5 < maxX) {
								newMaxX = this->maxX;
							}
							if(a6 < maxY) {
								newMaxY = this->maxY;
							}
							if(a7 < maxZ) {
								newMaxZ = this->maxZ;
							}
							if(newMinZ >= minZ) {
								newMinZ = this->minZ;
							}
							if((newMaxZ - newMinZ) * (newMaxY - newMinY) * (newMaxX - newMinX) - (maxZ - minZ) * (maxY - minY) * (maxX - minX) <= 2) {
								this->minX = newMinX;
								this->minY = newMinY;
								this->minZ = newMinZ;
								this->maxX = newMaxX;
								this->maxY = newMaxY;
								this->maxZ = newMaxZ;
								return 1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
LightUpdate& LightUpdate::operator=(const LightUpdate* a2) {
	*this = *a2;
	return *this;
}
void LightUpdate::update(Level* a2) {
	int32_t minX;				 // r3
	LevelChunk* chunk;		 // r0
	int32_t v6;					 // r10
	int32_t v7;					 // r0
	int32_t v8;					 // r9
	const LightLayer* layer; // r3
	int32_t v10;				 // r9
	int32_t v11;				 // r0
	int32_t v12;				 // r12
	int32_t v13;				 // r3
	int32_t v14;				 // r0
	int32_t v15;				 // r9
	int32_t v16;				 // r6
	int32_t v17;				 // r7
	int32_t v18;				 // [sp+8h] [bp-58h]
	int32_t a5;					 // [sp+Ch] [bp-54h]
	int32_t x;					 // [sp+10h] [bp-50h]
	int32_t v21;				 // [sp+14h] [bp-4Ch]
	int32_t z;					 // [sp+18h] [bp-48h]
	int32_t a3;					 // [sp+1Ch] [bp-44h]
	int32_t v24;				 // [sp+20h] [bp-40h]
	int32_t brightness;			 // [sp+24h] [bp-3Ch]
	int32_t v26;				 // [sp+28h] [bp-38h]
	int32_t v27;				 // [sp+2Ch] [bp-34h]
	int32_t v28;				 // [sp+30h] [bp-30h]
	int32_t v29;				 // [sp+34h] [bp-2Ch]

	minX = this->minX;
	if((this->maxZ - this->minZ + 1) * (this->maxY - this->minY + 1) * (this->maxX - minX + 1) <= 0x8000) {
		while(1) {
			x = minX + 1;
			v17 = minX;
			if(minX > this->maxX) {
				break;
			}
			v24 = minX >> 4;
			a5 = this->minZ + 1;
			a3 = minX - 1;
			while(1) {
				v16 = a5 - 1;
				if(a5 - 1 > this->maxZ) {
					break;
				}
				if(a2->hasChunksAt(v17, 0, a5 - 1, 1)) {
					chunk = a2->getChunk(v24, v16 >> 4);
					if(!chunk->isEmpty()) {
						if(this->minY < 0) {
							this->minY = 0;
						}
						if(this->maxY > 127) {
							this->maxY = 127;
						}
						v6 = this->minY + 1;
						z = a5 - 2;
						while(v6 - 1 <= this->maxY) {
							brightness = a2->getBrightness(*this->layer, v17, v6 - 1, v16);
							v7 = a2->getTile(v17, v6 - 1, v16);
							v8 = Tile::lightBlock[v7];
							layer = this->layer;
							if(!v8) {
								v8 = 1;
							}
							if(layer == &LightLayer::Sky) {
								if(a2->isSkyLit(v17, v6 - 1, v16)) {
									v21 = 15;
									goto LABEL_20;
								}
LABEL_50:
								if(v8 <= 14) {
									v21 = 0;
									goto LABEL_20;
								}
LABEL_18:
								v10 = 0;
							} else {
								if(layer != &LightLayer::Block) {
									goto LABEL_50;
								}
								v21 = Tile::lightEmission[v7];
								if(v8 > 14 && !Tile::lightEmission[v7]) {
									goto LABEL_18;
								}
LABEL_20:
								v26 = a2->getBrightness(*this->layer, a3, v6 - 1, v16);
								v18 = a2->getBrightness(*this->layer, x, v6 - 1, v16);
								v27 = a2->getBrightness(*this->layer, v17, v6 - 2, v16);
								v28 = a2->getBrightness(*this->layer, v17, v6, v16);
								v29 = a2->getBrightness(*this->layer, v17, v6 - 1, z);
								v11 = a2->getBrightness(*this->layer, v17, v6 - 1, a5);
								v12 = v18;
								if(v18 < v26) {
									v12 = v26;
								}
								v13 = v28;
								if(v12 < v27) {
									v12 = v27;
								}
								if(v12 >= v28) {
									v13 = v12;
								}
								if(v13 < v29) {
									v13 = v29;
								}
								if(v13 < v11) {
									v14 = v11 - v8;
								} else {
									v14 = v13 - v8;
								}
								if((v21 & ~(v21 >> 31)) < v14) {
									v10 = v14;
								} else {
									v10 = v21 & ~(v21 >> 31);
								}
							}
							if(brightness != v10) {
								a2->setBrightness(*this->layer, v17, v6 - 1, v16, v10);
								v15 = (v10 - 1) & ~((v10 - 1) >> 31);
								a2->updateLightIfOtherThan(*this->layer, a3, v6 - 1, v16, v15);
								a2->updateLightIfOtherThan(*this->layer, v17, v6 - 2, v16, v15);
								a2->updateLightIfOtherThan(*this->layer, v17, v6 - 1, z, v15);
								if(x >= this->maxX) {
									a2->updateLightIfOtherThan(*this->layer, x, v6 - 1, v16, v15);
								}
								if(v6 >= this->maxY) {
									a2->updateLightIfOtherThan(*this->layer, v17, v6, v16, v15);
								}
								if(a5 >= this->maxZ) {
									a2->updateLightIfOtherThan(*this->layer, v17, v6 - 1, a5, v15);
								}
							}
							++v6;
							continue;
						}
					}
				}
				++a5;
			}
			minX = x;
		}
	}
}
