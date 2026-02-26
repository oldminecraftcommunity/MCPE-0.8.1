#pragma once
#include <_types.h>

struct Material{
	bool_t flammable = 0;
	bool_t translucent = 0;
	bool_t alwaysDestroyable = 0;
	bool_t replaceable = 0;

	static Material* air, *dirt, *wood, *stone;
	static Material* metal, *water, *lava, *leaves;
	static Material* plant, *replaceable_plant, *sponge;
	static Material* cloth, *fire, *sand, *decoration;
	static Material* glass, *explosive, *coral, *ice;
	static Material* topSnow, *snow, *cactus, *clay;
	static Material* vegetable, *portal, *cake, *web;

	static void initMaterials(void);
	static void teardownMaterials(void);

	virtual bool_t isLiquid(void) const;
	virtual bool_t letsWaterThrough(void) const;
	virtual bool_t isSolid(void) const;
	virtual bool_t blocksLight(void) const;
	virtual bool_t isSolidBlocking(void) const;
	virtual bool_t isAlwaysDestroyable(void) const;
	virtual bool_t blocksMotion(void) const;
	virtual bool_t isFlammable(void) const;
	virtual bool_t isReplaceable(void) const;

	Material(void);
};
