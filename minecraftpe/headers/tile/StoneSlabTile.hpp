#pragma once
#include <tile/SlabTile.hpp>

struct StoneSlabTile : SlabTile{
	static std::string SLAB_NAMES[];

	TextureUVCoordinateSet field_84, field_9C, field_B4, field_CC;
	TextureUVCoordinateSet field_E4, field_FC, field_114, field_12C;
	TextureUVCoordinateSet field_144, field_15C;

	StoneSlabTile(int32_t, bool_t);

	virtual ~StoneSlabTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);

};
