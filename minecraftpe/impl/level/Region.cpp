#include <level/Region.hpp>
#include <level/Level.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <level/dimension/Dimension.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

Region::Region(struct Level* level, int32_t minX, int32_t minY, int32_t minZ, int32_t maxX, int32_t maxY, int32_t maxZ) {
	int32_t v9;			  // r2
	int32_t v11;		  // r5
	int32_t v12;		  // r0
	LevelChunk*** chunks; // r6
	int32_t i;			  // r5
	int32_t j;			  // r6
	LevelChunk** v18;	  // r10

	v9 = minX >> 4;
	v11 = 0;
	this->level = level;
	this->minCX = v9;
	this->minCZ = minZ >> 4;
	v12 = (maxX >> 4) - v9 + 1;
	this->sizeX = v12;
	this->sizeZ = (maxZ >> 4) - (minZ >> 4) + 1;
	this->chunks = new LevelChunk**[v12]; //operator new[](4 * v12);
	while(v11 < this->sizeX) {
		chunks = this->chunks;
		chunks[v11++] = new LevelChunk*[this->sizeZ]; //(LevelChunk**)operator new[](4 * this->sizeZ);
	}
	for(i = this->minCX; i <= maxX >> 4; ++i) {
		for(j = this->minCZ; j <= maxZ >> 4; ++j) {
			v18 = this->chunks[i - this->minCX];
			v18[j - this->minCZ] = level->getChunk(i, j);
		}
	}
}
int32_t Region::getRawBrightness(int32_t x, int32_t y, int32_t z) {
	return this->getRawBrightness(x, y, z, 1);
}
int32_t Region::getRawBrightness(int32_t x, int32_t y, int32_t z, bool_t complex) {
	int32_t v9;			   // r0
	int32_t rb; // r11
	int32_t v11;		   // r10
	int32_t v12;		   // r9
	int32_t result;		   // r0
	LevelChunk* v14;	   // r0
	int32_t v15;		   // [sp+Ch] [bp-2Ch]

	if(x < -32000000 || z < -32000000 || x > 31999999 || z > 32000000) {
		return 15;
	}
	if(complex && ((v9 = this->getTile(x, y, z), v9 == Tile::stoneSlabHalf->blockID) || v9 == Tile::farmland->blockID || v9 == Tile::woodSlabHalf->blockID)) {
		rb = this->getRawBrightness(x, y + 1, z, 0);
		v15 = this->getRawBrightness(x + 1, y, z, 0);
		v11 = this->getRawBrightness(x - 1, y, z, 0);
		v12 = this->getRawBrightness(x, y, z + 1, 0);
		result = this->getRawBrightness(x, y, z - 1, 0);
		if(v15 >= rb) {
			rb = v15;
		}
		if(rb >= v11) {
			v11 = rb;
		}
		if(v11 >= v12) {
			v12 = v11;
		}
		if(v12 >= result) {
			return v12;
		}
	} else if(y < 0) {
		return 0;
	} else if(y <= 127) {
		v14 = this->chunks[(x >> 4) - this->minCX][(z >> 4) - this->minCZ];
		return v14->getRawBrightness(x & 0xF, y, z & 0xF, this->level->skyDarken);
	} else {
		return (15 - this->level->skyDarken) & ~((15 - this->level->skyDarken) >> 31);
	}
	return result;
}
Region::~Region() {
	for(int32_t i = 0; i < this->sizeX; ++i) {
		if(this->chunks[i]) {
			delete[] this->chunks[i];
		}
	}
	delete[] this->chunks;
}

int32_t Region::getTile(int32_t x, int32_t y, int32_t z) {
	if(y < 0) return 0;
	if(y > 127) return 0;
	int32_t v4 = (x >> 4) - this->minCX;
	if(v4 < 0) return 0;
	if(v4 >= this->sizeX) return 0;
	int32_t v5 = (z >> 4) - this->minCZ;
	if(v5 < 0 || v5 >= this->sizeZ) return 0;
	LevelChunk* r = this->chunks[v4][v5];
	if(r) return r->getTile(x & 0xf, y, z & 0xf);
	return 0;
}
bool_t Region::isEmptyTile(int32_t x, int32_t y, int32_t z) {
	return Tile::tiles[this->getTile(x, y, z)] == 0;
}
float Region::getBrightness(int32_t x, int32_t y, int32_t z) {
	return this->level->dimensionPtr->lightRamp[this->getRawBrightness(x, y, z)];
}
int32_t Region::getData(int32_t x, int32_t y, int32_t z) {
	if(y < 0 || y > 127) return 0;
	LevelChunk* r = this->chunks[(x >> 4) - this->minCX][(z >> 4) - this->minCZ];
	return r->getData(x & 0xf, y, z & 0xf); //no epik nullptr check
}
Material* Region::getMaterial(int32_t x, int32_t y, int32_t z) {
	int32_t id = this->getTile(x, y, z);
	if(id) return (Material*)Tile::tiles[id]->material;
	return Material::air;
}

bool_t Region::isSolidRenderTile(int32_t x, int32_t y, int32_t z) {
	Tile* t = Tile::tiles[this->getTile(x, y, z)];
	if(t) return t->isSolidRender();
	return 0;
}
bool_t Region::isSolidBlockingTile(int32_t x, int32_t y, int32_t z) {
	Tile* t = Tile::tiles[this->getTile(x, y, z)];
	if(t && t->material->isSolidBlocking()) return t->isCubeShaped();
	return 0;
}
Biome* Region::getBiome(int32_t x, int32_t z) {
	return this->level->getBiome(x, z);
}
