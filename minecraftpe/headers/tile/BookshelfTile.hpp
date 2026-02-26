#pragma once
#include <tile/Tile.hpp>

struct BookshelfTile : Tile{
	TextureUVCoordinateSet uv;

	BookshelfTile(int32_t, std::string, const struct Material*);
	virtual ~BookshelfTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);

};
