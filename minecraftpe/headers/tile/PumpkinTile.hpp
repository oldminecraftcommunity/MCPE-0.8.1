#pragma once
#include <tile/DirectionalTile.hpp>

struct PumpkinTile : DirectionalTile{
	bool_t field_80;
	char field_81, field_82, field_83;
	TextureUVCoordinateSet field_84, field_9C, field_B4;

	PumpkinTile(int32_t, bool_t);

	virtual ~PumpkinTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
	virtual void onPlace(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, Mob*, int32_t);
};
