#include <tile/Sapling.hpp>
#include <level/Level.hpp>
#include <level/gen/feature/BirchFeature.hpp>
#include <level/gen/feature/SpruceFeature.hpp>
#include <level/gen/feature/TreeFeature.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

Sapling::Sapling(int32_t a2, const std::string& a3)
	: Bush(a2, a3) {
	this->setShape(0.1, 0, 0.1, 0.9, 0.8, 0.9);
	TextureAtlasTextureItem* texItem = this->getTextureItem("sapling");
	this->field_80 = *texItem->getUV(0);
	this->field_98 = *texItem->getUV(1);
	this->field_B0 = *texItem->getUV(2);
	this->field_C8 = *texItem->getUV(3);
}
void Sapling::growTree(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
	int32_t v10;  // r9
	Feature* v11; // r4

	v10 = level->getData(x, y, z) & 3;
	if(v10 == 1) {
		v11 = new SpruceFeature(1);
	} else if(v10 == 2) {
		v11 = new BirchFeature(1);
	} else {
		v11 = new TreeFeature(1, 0);
	}
	level->setTileNoUpdate(x, y, z, 0);
	if(!v11->place(level, rng, x, y, z)) {
		level->setTileAndDataNoUpdate(x, y, z, this->blockID, v10);
	}
	delete v11;
}

Sapling::~Sapling() {
}
bool_t Sapling::onFertilized(Level* level, int32_t x, int32_t y, int32_t z) {
	this->growTree(level, x, y, z, &level->random);
	return 1;
}
TextureUVCoordinateSet* Sapling::getTexture(int32_t a2, int32_t a3) {
	int32_t v3; // r2

	v3 = a3 & 3;
	switch(v3) {
		case 1:
			return &this->field_B0;
		case 2:
			return &this->field_98;
		case 3:
			return &this->field_C8;
	}
	return &this->field_80;
}
void Sapling::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
	int32_t v10; // r0

	if(!level->isClientMaybe) {
		this->checkAlive(level, x, y, z);
		if(level->getRawBrightness(x, y + 1, z) > 8 && !(rng->genrand_int32() % 7)) {
			v10 = level->getData(x, y, z);
			if((v10 & 8) != 0) {
				this->growTree(level, x, y, z, rng);
			} else {
				level->setDataNoUpdate(x, y, z, v10 | 8);
			}
		}
	}
}
int32_t Sapling::getSpawnResourcesAuxValue(int32_t a2) {
	return a2 & 3;
}
