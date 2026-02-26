#pragma once
#include <tile/Bush.hpp>

struct Sapling: Bush
{
	TextureUVCoordinateSet field_80, field_98, field_B0, field_C8;
	Sapling(int32_t, const std::string&);
	void growTree(Level*, int32_t, int32_t, int32_t, Random*);

	virtual ~Sapling();
	virtual bool_t onFertilized(Level*, int32_t, int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);
};
