#include <level/gen/PerformanceTestChunkSource.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <string.h>

LevelChunk* PerformanceTestChunkSource::create(int32_t x, int32_t z) {
	uint8_t* blocks = new uint8_t[0x8000u];
	memset(blocks, 0, 0x8000u);
	for(int yy = 0; yy <= 64; ++yy){
		if(yy < 60){
			for(int xx = (yy + 1) & 1; xx < 16; xx += 2) {
				for(int zz = yy & 1; zz < 16; zz += 2) {
					int ind = (xx << 11) | (zz << 7) | yy;
					blocks[ind] = 3;
				}
			}
		}else{
			for(int xx = 0; xx < 16; xx += 2) {
				for(int zz = 0; zz < 16; zz += 2) {
					int ind = (xx << 11) | (zz << 7) | yy;
					blocks[ind] = 3;
				}
			}
		}
	}
	LevelChunk* chunk = new LevelChunk(this->level, blocks, x, z);
	chunk->recalcHeightmap();
	return chunk;
}
