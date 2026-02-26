#pragma once
#include <_types.h>
#include <tile/material/Material.hpp>

struct DecorationMaterial : Material{

	DecorationMaterial(void);

	virtual bool_t isSolid(void) const;
	virtual bool_t blocksLight(void) const;
	virtual bool_t blocksMotion(void) const;
};
