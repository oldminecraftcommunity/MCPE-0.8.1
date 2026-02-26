#pragma once
#include <tile/Tile.hpp>

struct CakeTile : Tile{
	TextureUVCoordinateSet field_80, field_98, field_B0, field_C8;

	CakeTile(int32_t);

	virtual ~CakeTile();
	virtual bool_t isCubeShaped();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual void updateDefaultShape();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t, uint8_t);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getResourceCount(Random*);
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);
	virtual bool_t canSurvive(Level*, int32_t, int32_t, int32_t);
};
