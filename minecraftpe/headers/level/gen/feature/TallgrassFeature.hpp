#pragma once
#include <level/gen/feature/Feature.hpp>
#include <util/Random.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>
struct TallgrassFeature: public Feature
{
	int32_t blockID;
	int32_t field_C;

	TallgrassFeature(int32_t blockID, int32_t c) :
			Feature(0) {
		this->blockID = blockID;
		this->field_C = c;
	}

	virtual ~TallgrassFeature() {
	}
	virtual bool_t place(Level* level, Random* random, int32_t x, int32_t y, int32_t z) {
		do {
			int id = level->getTile(x, y, z);
			if(id != 0) { //cbz
				if(id != Tile::leaves->blockID) { //beq
					break;
				}
			}

			if(y <= 0) break; //bgt
			--y;
		} while(1);


		int v19 = 128;
		do {
			int xx = x + random->nextInt(8) - random->nextInt(8);
			int yy = y + random->nextInt(4) - random->nextInt(4);
			int zz = z + random->nextInt(8) - random->nextInt(8);
			if (level->isEmptyTile(xx, yy, zz)) {
				Tile* v17 = Tile::tiles[this->blockID];
				if (v17->canSurvive(level, xx, yy, zz)) {
					level->setTileAndDataNoUpdate(xx, yy, zz, this->blockID, this->field_C);
				}
			}
			--v19;
		} while (v19);
		return 1;
	}
};
