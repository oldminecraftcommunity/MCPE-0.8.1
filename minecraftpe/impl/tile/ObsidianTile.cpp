#include <tile/ObsidianTile.hpp>
#include <level/Level.hpp>

ObsidianTile::ObsidianTile(int32_t id, const std::string& a3, bool_t glowing)
	: StoneTile(id, a3) {
	this->field_5C = 255;
	this->glowing = glowing;
}

void ObsidianTile::poofParticles(Level* level, int32_t x, int32_t y, int32_t z) {
	float v5;  // s20
	int32_t i; // r5
	float v11; // s17
	float v12; // s18
	float v13; // s21
	float v14; // s19

	v5 = (float)x;
	for(i = 0; i != 6; ++i) {
		v11 = v5 + level->random.nextFloat();
		v12 = (float)y + level->random.nextFloat();
		v13 = (float)z;
		v14 = (float)z + level->random.nextFloat();
		if(i) {
			switch(i) {
				case 1:
					if(!level->isSolidBlockingTile(x, y - 1, z)) {
						v12 = (float)y - 0.0625;
					}
					break;
				case 2:
					if(!level->isSolidBlockingTile(x, y, z + 1)) {
						v14 = (float)(z + 1) + 0.0625;
					}
					break;
				case 3:
					if(!level->isSolidBlockingTile(x, y, z - 1)) {
						v14 = v13 - 0.0625;
					}
					break;
				case 4:
					if(!level->isSolidBlockingTile(x + 1, y, z)) {
						v11 = (float)(x + 1) + 0.0625;
					}
					break;
				default:
					if(i == 5 && !level->isSolidBlockingTile(x - 1, y, z)) {
						v11 = v5 - 0.0625;
					}
					break;
			}
		} else if(!level->isSolidBlockingTile(x, y + 1, z)) {
			v12 = (float)(y + 1) + 0.0625;
		}
		if(v11 < v5 || v11 > (float)(x + 1) || v12 < 0.0 || v12 > (float)(y + 1) || v14 < v13 || v14 > (float)(z + 1)) {
			level->addParticle(PT_RED_DUST, v11, v12, v14, 0.0, 0.0, 0.0, 0);
		}
	}
}

ObsidianTile::~ObsidianTile() {
}
void ObsidianTile::animateTick(Level* level, int32_t x, int32_t y, int32_t z, Random*) {
	if(this->glowing) {
		this->poofParticles(level, x, y, z);
	}
}
int32_t ObsidianTile::getResource(int32_t, Random*) {
	return Tile::obsidian->blockID;
}
int32_t ObsidianTile::getResourceCount(Random*) {
	return 1;
}
