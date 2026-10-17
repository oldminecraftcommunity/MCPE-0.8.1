#pragma once
#include <_types.h>
#include <tile/material/Material.hpp>

struct LiquidMaterial : Material{
	virtual bool_t isLiquid(void) const {
		return 1;
	}
	virtual bool_t blocksMotion(void) const {
		return 0;
	}
	virtual bool_t isSolid(void) const {
		return 0;
	}
};
