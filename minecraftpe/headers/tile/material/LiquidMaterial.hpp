#pragma once
#include <_types.h>
#include <tile/material/Material.hpp>

struct LiquidMaterial : Material{
	virtual bool_t isLiquid(void) const;
	virtual bool_t isSolid(void) const;
	virtual bool_t blocksMotion(void) const;
};
