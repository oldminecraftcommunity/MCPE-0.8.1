#pragma once
#include <_types.h>
#include <tile/material/Material.hpp>

struct WebMaterial : Material{
	WebMaterial(void);

	virtual bool_t blocksMotion(void) const;
};
