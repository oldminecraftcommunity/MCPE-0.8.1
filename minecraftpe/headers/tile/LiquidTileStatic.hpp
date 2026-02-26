#pragma once
#include <tile/LiquidTile.hpp>

struct LiquidTileStatic: LiquidTile
{
	LiquidTileStatic(int32_t, const struct Material*, const std::string&, const std::string&);
	void setDynamic(Level*, int32_t, int32_t, int32_t);

	virtual ~LiquidTileStatic();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);

};
