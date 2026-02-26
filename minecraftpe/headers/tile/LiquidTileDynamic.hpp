#pragma once
#include <tile/LiquidTile.hpp>

struct LiquidTileDynamic: LiquidTile
{
	int32_t field_D8;
	bool_t field_DC[4];
	int32_t field_E0[4];
	LiquidTileDynamic(int32_t id, Material* mat, const std::string& still, const std::string& flow);
	bool_t canSpreadTo(Level*, int32_t, int32_t, int32_t);
	int32_t getHighest(Level*, int32_t, int32_t, int32_t, int32_t);
	int32_t getSlopeDistance(Level*, int32_t, int32_t, int32_t, int32_t, int32_t);
	bool_t* getSpread(Level*, int32_t, int32_t, int32_t);
	bool_t isWaterBlocking(Level*, int32_t, int32_t, int32_t);
	void setStatic(Level*, int32_t, int32_t, int32_t);
	void trySpreadTo(Level*, int32_t, int32_t, int32_t, int32_t);

	virtual ~LiquidTileDynamic();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void onPlace(Level*, int32_t, int32_t, int32_t);

};
