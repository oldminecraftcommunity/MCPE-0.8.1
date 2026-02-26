#include <level/LevelConverters.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <tile/Tile.hpp>

bool_t LevelConverters::v1_ClothIdToClothData(LevelChunk* a1){
	uint8_t* tiles;	 // r4
	uint8_t blockID; // r6
	int32_t v3;		 // r3
	bool_t v4;		 // r2
	int32_t v5;		 // r5
	uint8_t* data;	 // r1
	int8_t v7;		 // r5
	uint8_t v8;		 // r7
	int8_t v9;		 // r7
	uint8_t v10;	 // r5

	tiles = a1->tiles;
	blockID = Tile::cloth->blockID;
	v3 = 0;
	v4 = 0;
	do {
		v5 = tiles[v3];
		if((uint32_t)(v5 - 101) <= 0xE) {
			tiles[v3] = blockID;
			data = a1->tileMeta.data;
			v7 = 116 - v5;
			v8 = data[v3 >> 1];
			if((v3 & 1) != 0) {
				v9 = v8 & 0xF;
			} else {
				v9 = v8 & 0xF0;
			}
			if((v3 & 1) != 0) {
				v10 = v9 | (16 * v7);
			} else {
				v10 = v7 | v9;
			}
			data[v3 >> 1] = v10;
			v4 = 1;
		}
		++v3;
	} while(v3 != 0x8000);
	return v4;
}
