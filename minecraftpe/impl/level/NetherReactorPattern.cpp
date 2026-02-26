#include <level/NetherReactorPattern.hpp>
#include <string.h>
#include <tile/Tile.hpp>

NetherReactorPattern::NetherReactorPattern() {
	int32_t gold;		 // r5
	int32_t stone;		 // r4
	int32_t reactor;	 // r6
	int32_t x;			 // r4
	int32_t z;			 // r3
	int32_t _z;			 // r6
	int32_t y;			 // r5
	int32_t id;			 // [sp+0h] [bp-98h]
	int32_t pattern[27]; // [sp+Ch] [bp-8Ch] BYREF

	gold = Tile::goldBlock->blockID;
	stone = Tile::stoneBrick->blockID;
	reactor = Tile::netherReactor->blockID;
	memset(pattern, 0, sizeof(pattern));
	pattern[1] = stone;
	pattern[3] = stone;
	pattern[4] = stone;
	pattern[5] = stone;
	pattern[7] = stone;
	pattern[9] = stone;
	pattern[11] = stone;
	pattern[15] = stone;
	pattern[17] = stone;
	pattern[19] = stone;
	pattern[21] = stone;
	pattern[22] = stone;
	pattern[23] = stone;
	pattern[25] = stone;
	x = 0;
	pattern[0] = gold;
	pattern[2] = gold;
	pattern[6] = gold;
	pattern[8] = gold;
	pattern[13] = reactor;
	do {
		for(y = 0; y != 3; ++y) {
			for(_z = 0; _z != 3; ++_z) {
				id = pattern[9 * x + 3 * y + _z];
				z = _z;
				this->setTileAt(x, y, z, id);
			}
		}
		++x;
	} while(x != 3);
}
int32_t NetherReactorPattern::getTileAt(int32_t x, int32_t y, int32_t z) {
	return this->pattern[9 * x + 3 * y + z];
}
void NetherReactorPattern::setTileAt(int32_t x, int32_t y, int32_t z, int32_t id){
	this->pattern[9 * x + 3 * y + z] = id;
}
