#include <rendering/RenderChunk.hpp>
#include <level/Level.hpp>
#include <string.h>
#include <math.h>
#include <rendering/Tesselator.hpp>
#include <entity/Entity.hpp>
#include <GL/gl.h>
#include <level/chunk/LevelChunk.hpp>
#include <level/Region.hpp>
#include <rendering/TileRenderer.hpp>
#include <tile/Tile.hpp>

int32_t RenderChunk::updates = 0;

RenderChunk::RenderChunk(Level* level, int32_t x, int32_t y, int32_t z, int32_t chunkSize, int32_t rl) {
	MeshBuffer* v12; // r0
	double v13; // r0
	float v14; // s14

	this->xSize = chunkSize;
	this->ySize = chunkSize;
	this->zSize = chunkSize;
	this->level = level;
	this->frustumBB = {0, 0, 0, 1, 1, 1};
	this->isInFrustumMaybe = 0;
	this->field_4D = 1;
	this->field_4E = 0;
	this->built = 0;
	this->dirty = 0;
	this->tessellator = &Tesselator::instance;
	this->renderLists = rl;
	this->skipRenderMaybe = 1;
	memset(this->skipLayer, 0, sizeof(this->skipLayer));
	v13 = sqrt((float)(this->ySize * this->ySize + this->xSize * this->xSize + this->zSize * this->zSize));
	this->xPos = -999;
	v14 = v13;
	this->field_2C = v14 * 0.5;
	this->setPos(x, y, z);
}
float RenderChunk::distanceToSqr(const struct Entity* a2) {
	float v2; // s13
	float v3; // s15
	float v4; // s14

	v2 = a2->posX - (float)this->blockX;
	v3 = a2->posY - (float)this->blockY;
	v4 = a2->posZ - (float)this->blockZ;
	return (float)((float)(v3 * v3) + (float)(v2 * v2)) + (float)(v4 * v4);
}
int32_t RenderChunk::getAllLists(int32_t* a2, int32_t a3, int32_t a4) {
	if(this->isInFrustumMaybe) {
		if(!this->skipLayer[a4]) {
			a2[a3++] = this->renderLists + a4;
		}
	}
	return a3;
}
int32_t RenderChunk::getList(int32_t a2) {
	if(!this->isInFrustumMaybe || this->skipLayer[a2]) {
		return -1;
	} else {
		return a2 + this->renderLists;
	}
}
MeshBuffer* RenderChunk::getRenderChunk(int32_t a2) {
	return &this->meshBuffers[a2];
}
bool_t RenderChunk::isDirty() {
	return this->dirty;
}
void RenderChunk::rebuild(void) {
	int32_t yPos;				// r7
	int32_t v3;					// r2
	int32_t zPos;				// r7
	int32_t xSize;				// r3
	int32_t ySize;				// r3
	int32_t zSize;				// r3
	Tesselator** p_tessellator; // r6
	MeshBuffer* i;				// r5
	MeshBuffer* v10;			// r0
	int32_t layer;				// r5
	int32_t id;					// r12
	int32_t started;			// r7
	int32_t blockRenderLayer;	// r0
	int32_t x;					// r10
	int32_t z;					// r8
	int32_t y;					// r9
	int32_t v19;				// [sp+10h] [bp-108h]
	Tile* idd;					// [sp+10h] [bp-108h]
	int32_t renderedAnyBlocks;	// [sp+14h] [bp-104h]
	int32_t xPos;				// [sp+18h] [bp-100h]
	int32_t v23;				// [sp+1Ch] [bp-FCh]
	int32_t v24;				// [sp+20h] [bp-F8h]
	int32_t v25;				// [sp+24h] [bp-F4h]
	int32_t xMax;				// [sp+28h] [bp-F0h]
	int32_t yMax;				// [sp+2Ch] [bp-ECh]
	int32_t zMax;				// [sp+30h] [bp-E8h]
	//Region v30[7]; // [sp+40h] [bp-D8h] BYREF
	//MeshBuffer result; // [sp+5Ch] [bp-BCh] BYREF
	//TileRenderer v32; // [sp+84h] [bp-94h] BYREF

	if(this->dirty) {
		xPos = this->xPos;
		yPos = this->yPos;
		v3 = RenderChunk::updates;
		this->skipLayer[0] = 1;
		v23 = yPos;
		zPos = this->zPos;
		RenderChunk::updates = v3 + 1;
		xSize = this->xSize;
		v24 = zPos;
		this->skipLayer[1] = 1;
		xMax = xPos + xSize;
		ySize = this->ySize;
		this->skipLayer[2] = 1;
		yMax = v23 + ySize;
		zSize = this->zSize;
		this->skipLayer[3] = 1;
		zMax = zPos + zSize;
		this->skipRenderMaybe = 1;
		LevelChunk::touchedSky = 0;
		p_tessellator = &this->tessellator;
		Region v30(this->level, xPos - 1, v23 - 1, zPos - 1, xMax + 1, yMax + 1, zPos + zSize + 1);
		TileRenderer v32(&v30);
		bool_t v29[] = {1, 1, 1, 1};

		for(MeshBuffer& v10: this->meshBuffers) {
			v10.reset();
		}

		for(layer = 0; layer != 4; ++layer) {
			if(v29[layer]) {
				y = v23;
				started = 0;
				renderedAnyBlocks = 0;
				v25 = 0;
				while(y < yMax) {
					for(z = v24; z < zMax; ++z) {
						for(x = xPos; x < xMax; ++x) {
							id = v30.getTile(x, y, z);
							if(id > 0) {
								if(!started) {
									v19 = id;
									this->tessellator->begin(0xFA);
									started = 1;
									this->tessellator->offset((float)-this->xPos, (float)-this->yPos, (float)-this->zPos);
									id = v19;
								}
								idd = Tile::tiles[id];
								blockRenderLayer = idd->getRenderLayer();
								if(blockRenderLayer <= layer) {
									if(blockRenderLayer == layer) {
										renderedAnyBlocks |= v32.tesselateInWorld(idd, x, y, z);
									}
								} else {
									v25 = 1;
									v29[blockRenderLayer] = 1;
								}
							}
						}
					}
					++y;
				}
				if(started) {
					this->meshBuffers[layer] = this->tessellator->end();
					this->meshBuffers[layer].transformX = this->xPos;
					this->meshBuffers[layer].transformY = this->yPos;
					this->meshBuffers[layer].transformZ = this->zPos;
					this->tessellator->offset(0.0, 0.0, 0.0);
					if(renderedAnyBlocks) {
						this->skipLayer[layer] = 0;
						this->skipRenderMaybe = 0;
					}
				}
				if(!v25) {
					break;
				}
			}
		}
		this->touchedSky = LevelChunk::touchedSky;
		this->built = 1;
	}
}
void RenderChunk::renderBB(void) {
}
void RenderChunk::reset(void) {
	this->skipLayer[0] = 1;
	this->skipLayer[1] = 1;
	this->skipLayer[2] = 1;
	this->skipLayer[3] = 1;
	this->isInFrustumMaybe = 0;
	this->built = 0;
	this->skipRenderMaybe = 1;
}
void RenderChunk::resetUpdates(void) {
	RenderChunk::updates = 0;
}
void RenderChunk::setClean(void) {
	this->dirty = 0;
}
void RenderChunk::setDirty(void) {
	this->dirty = 1;
}
void RenderChunk::setPos(int32_t x, int32_t y, int32_t z) {
	int32_t xSize; // r1
	int32_t ySize; // r2
	int32_t zSize; // r3

	if(x != this->xPos || y != this->yPos || z != this->zPos) {
		this->reset();
		xSize = this->xSize;
		this->xPos = x;
		ySize = this->ySize;
		this->yPos = y;
		this->zPos = z;
		this->blockX = x + xSize / 2;
		this->blockY = y + ySize / 2;
		zSize = this->zSize;
		this->blockZ = z + zSize / 2;
		this->frustumBB = {
			(float)x - 1.0f,
			(float)y,
			(float)z - 1.0f,
			(float)(x + xSize) + 1.0f,
			(float)(y + ySize) + 2.0f,
			(float)(z + zSize) + 1.0f
		};
		this->setDirty();
	}
}
float RenderChunk::squishedDistanceToSqr(const struct Entity* a2) {
	float v2; // s13
	float v3; // s15
	float v4; // s14

	v2 = a2->posX - (float)this->blockX;
	v3 = a2->posY - (float)this->blockY;
	v4 = a2->posZ - (float)this->blockZ;
	return (float)((float)((float)(v3 + v3) * (float)(v3 + v3)) + (float)(v2 * v2)) + (float)(v4 * v4);
}
void RenderChunk::translateToPos(void) {
	glTranslatef((float)this->xPos, (float)this->yPos, (float)this->zPos);
}
