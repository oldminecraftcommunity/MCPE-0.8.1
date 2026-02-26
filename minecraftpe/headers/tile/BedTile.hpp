#pragma once
#include <tile/DirectionalTile.hpp>

struct BedTile : DirectionalTile{
	TextureUVCoordinateSet field_80, field_98, field_B0;
	TextureUVCoordinateSet field_C8, field_E0, field_F8;

	static int32_t HEAD_DIRECTION_OFFSETS[];

	BedTile(int32_t);
	void _setShape(void);
	static bool_t findStandUpPosition(Level*, int32_t, int32_t, int32_t, int32_t, struct Pos&);
	static void setOccupied(Level*, int32_t, int32_t, int32_t, bool_t);

	static bool_t isHeadPiece(int32_t);
	static bool_t isOccupied(int32_t);

	virtual ~BedTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual void spawnResources(Level*, int32_t, int32_t, int32_t, int32_t, float);
	virtual int32_t getRenderLayer();
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);

};
