#pragma once
#include <tile/Tile.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>


struct WoodTile : Tile{
	TextureAtlasTextureItem field_80;

	WoodTile(int32_t);

	virtual ~WoodTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual std::string getTypeDescriptionId(int32_t);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);
};
