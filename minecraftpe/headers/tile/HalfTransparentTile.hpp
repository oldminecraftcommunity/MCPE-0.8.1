#pragma once
#include <tile/Tile.hpp>
#include <level/LevelSource.hpp>

struct HalfTransparentTile : Tile{
	bool field_80;

	HalfTransparentTile(int32_t id, const std::string& s, Material* m)
		: Tile(id, s, m), field_80(0) {
	}
	virtual ~HalfTransparentTile(){}
	virtual bool_t shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t side) {
		int32_t id = level->getTile(x, y, z);
		if(!this->field_80 && id == this->blockID) return this->field_80;
		return Tile::shouldRenderFace(level, x, y, z, side);
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual int32_t getRenderLayer() {
		return 2;
	}
};
