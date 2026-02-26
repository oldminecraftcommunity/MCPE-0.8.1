#include <level/gen/feature/Feature.hpp>
#include <level/Level.hpp>

Feature::Feature(bool_t a2) {
	this->update = a2;
}

Feature::~Feature() {
}
void Feature::init(float, float, float) {
}

void Feature::placeBlock(Level* level, int32_t x, int32_t y, int32_t z, int32_t id) {
	this->placeBlock(level, x, y, z, id, 0);
}
void Feature::placeBlock(Level* level, int32_t x, int32_t y, int32_t z, int32_t id, int32_t meta) {
	if(this->update) {
		level->setTileAndData(x, y, z, id, meta, 3);
	} else {
		level->setTileAndDataNoUpdate(x, y, z, id, meta);
	}
}
