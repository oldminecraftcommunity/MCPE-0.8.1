#pragma once
#include <tile/Tile.hpp>

struct TntTile : Tile{
	TextureUVCoordinateSet field_80, field_98, field_B0;

	TntTile(int32_t, const std::string&);

	virtual ~TntTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual void destroy(Level*, int32_t, int32_t, int32_t, int32_t);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getResourceCount(Random*);
	virtual void wasExploded(Level*, int32_t, int32_t, int32_t);
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);

};
