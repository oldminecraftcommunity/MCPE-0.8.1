#pragma once
#include <tile/HalfTransparentTile.hpp>

struct GlassTile: HalfTransparentTile
{

	GlassTile(int32_t id, const std::string& s, Material* m) :
			HalfTransparentTile(id, s, m) {
	}

	virtual ~GlassTile() {
	}
	virtual int32_t getRenderLayer() {
		return 1;
	}
	virtual int32_t getResourceCount(Random*) {
		return 0;
	}
};
