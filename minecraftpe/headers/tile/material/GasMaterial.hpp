#pragma once
#include <_types.h>
#include <tile/material/Material.hpp>

struct GasMaterial : Material{
	virtual bool_t isSolid(void) const;
	virtual bool_t blocksLight(void) const;
	virtual bool_t blocksMotion(void) const;
};
