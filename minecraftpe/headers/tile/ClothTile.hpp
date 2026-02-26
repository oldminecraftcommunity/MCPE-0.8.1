#pragma once
#include <tile/Tile.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

struct ClothTile : Tile{
	TextureAtlasTextureItem tex;
	ClothTile(int32_t);

	virtual ~ClothTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);
};
