#include <level/gen/PerformanceTestChunkSource.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <string.h>

PerformanceTestChunkSource::~PerformanceTestChunkSource() {
}
bool_t PerformanceTestChunkSource::hasChunk(int32_t, int32_t) {
	return 1;
}
LevelChunk* PerformanceTestChunkSource::getChunk(int32_t x, int32_t z) {
	return this->create(x, z);
}
LevelChunk* PerformanceTestChunkSource::create(int32_t x, int32_t z) {
	int32_t v6;		 // r4
	uint8_t* v7;	 // r10
	int32_t k;		 // r5
	int32_t m;		 // r6
	int32_t v10;	 // r1
	int32_t v11;	 // r1
	int32_t j;		 // r5
	int32_t i;		 // r6
	LevelChunk* v14; // r4

	v6 = 0;
	v7 = new uint8_t[0x8000u];
	memset(v7, 0, 0x8000u);
	do {
		if(v6 > 59) {
			for(i = 0; i != 16; i += 2) {
				for(j = 0; j != 16; j += 2) {
					v11 = v6 | (i << 11) | (j << 7);
					v7[v11] = 3;
				}
			}
		} else {
			for(k = (v6 + 1) & 1; k <= 15; k += 2) {
				for(m = v6 & 1; m <= 15; m += 2) {
					v10 = v6 | (k << 11) | (m << 7);
					v7[v10] = 3;
				}
			}
		}
		++v6;
	} while(v6 != 65);
	v14 = new LevelChunk(this->level, v7, x, z);
	v14->recalcHeightmap();
	return v14;
}
void PerformanceTestChunkSource::postProcess(ChunkSource*, int32_t, int32_t) {
}
bool_t PerformanceTestChunkSource::tick() {
	return 0;
}
bool_t PerformanceTestChunkSource::shouldSave() {
	return 0;
}
std::string PerformanceTestChunkSource::gatherStats() {
	return "PerformanceTestChunkSource";
}
