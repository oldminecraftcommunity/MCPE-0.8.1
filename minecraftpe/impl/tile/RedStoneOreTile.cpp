#include <tile/RedStoneOreTile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

RedStoneOreTile::RedStoneOreTile(int32_t a2, const std::string& a3, bool_t glowing)
	: Tile(a2, a3, Material::stone) {
	if(glowing) this->setTicking(1);
	this->emitLight = glowing;
}

void RedStoneOreTile::interact(Level* level, int32_t x, int32_t y, int32_t z) {
	this->poofParticles(level, x, y, z);
	if(this->blockID == Tile::redStoneOre->blockID) {
		level->setTile(x, y, z, Tile::redStoneOre_lit->blockID, 2);
	}
}
void RedStoneOreTile::poofParticles(Level* level, int32_t x, int32_t y, int32_t z) {
	float v5;		  // s20
	Random* p_random; // r9
	int32_t i;		  // r5
	float v11;		  // s17
	float v12;		  // s18
	float v13;		  // s21
	float v14;		  // s19

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

RedStoneOreTile::~RedStoneOreTile() {
}
int32_t RedStoneOreTile::getTickDelay() {
	return 30;
}
void RedStoneOreTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random*) {
	if(this->blockID == Tile::redStoneOre_lit->blockID) {
		level->setTile(x, y, z, Tile::redStoneOre->blockID, 2);
	}
}
void RedStoneOreTile::animateTick(Level* level, int32_t x, int32_t y, int32_t z, Random*) {
	if(this->emitLight) this->poofParticles(level, x, y, z);
}
int32_t RedStoneOreTile::getResource(int32_t, Random*) {
	return Item::redStone->itemID;
}
int32_t RedStoneOreTile::getResourceCount(Random* a2) {
	return (a2->genrand_int32() & 1) + 4;
}
bool_t RedStoneOreTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	this->interact(level, x, y, z);
	return Tile::use(level, x, y, z, player);
}
void RedStoneOreTile::stepOn(Level* level, int32_t x, int32_t y, int32_t z, Entity*) {
	this->interact(level, x, y, z);
}
void RedStoneOreTile::attack(Level* level, int32_t x, int32_t y, int32_t z, Player*) {
	this->interact(level, x, y, z);
}
