#pragma once
#include <tile/Tile.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

struct MultiTextureTile: Tile
{
	TextureAtlasTextureItem field_7C;
	int32_t field_A8;

	MultiTextureTile(int32_t, std::string, const struct Material*);

	virtual ~MultiTextureTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);
};
