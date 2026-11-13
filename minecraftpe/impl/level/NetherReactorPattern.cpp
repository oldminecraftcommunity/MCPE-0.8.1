#include <level/NetherReactorPattern.hpp>
#include <tile/Tile.hpp>

NetherReactorPattern::NetherReactorPattern() {
	int gold = Tile::goldBlock->blockID;
	int stone = Tile::stoneBrick->blockID;
	int reactor = Tile::netherReactor->blockID;
	int pattern[27] = {0};
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
	pattern[0] = gold;
	pattern[2] = gold;
	pattern[6] = gold;
	pattern[8] = gold;
	pattern[13] = reactor;

	for(int x = 0; x < 3; ++x){
		for(int y = 0; y < 3; ++y) {
			for(int z = 0; z < 3; ++z) {
				this->setTileAt(x, y, z, pattern[x*9 + y*3 + z]);
			}
		}
	}
}
int32_t NetherReactorPattern::getTileAt(int32_t x, int32_t y, int32_t z) {
	return this->pattern[9 * x + 3 * y + z];
}
void NetherReactorPattern::setTileAt(int32_t x, int32_t y, int32_t z, int32_t id){
	this->pattern[9 * x + 3 * y + z] = id;
}
