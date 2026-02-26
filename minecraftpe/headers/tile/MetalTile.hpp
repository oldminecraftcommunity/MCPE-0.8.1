#pragma once
#include <tile/Tile.hpp>

struct MetalTile : Tile{
	MetalTile(int32_t, const std::string&);

	virtual ~MetalTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t);

};
