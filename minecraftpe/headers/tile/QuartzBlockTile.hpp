#pragma once
#include <tile/Tile.hpp>

struct QuartzBlockTile : Tile{
	TextureUVCoordinateSet field_80, field_98, field_B0, field_C8, field_E0, field_F8, field_110;

	QuartzBlockTile(int32_t);

	virtual ~QuartzBlockTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual std::string getDescriptionId(const ItemInstance*);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);
};
