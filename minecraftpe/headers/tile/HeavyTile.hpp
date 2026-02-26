#pragma once
#include <tile/Tile.hpp>

struct HeavyTile: Tile
{
	static bool_t instaFall;
	HeavyTile(int32_t, const std::string&);
	HeavyTile(int32_t, const std::string&, const Material*);

	void checkSlide(Level*, int32_t, int32_t, int32_t);

	static bool_t isFree(Level*, int32_t, int32_t, int32_t);

	virtual ~HeavyTile();
	virtual int32_t getTickDelay();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void onPlace(Level*, int32_t, int32_t, int32_t);

	virtual void falling(struct FallingTile*);
	virtual void onLand(Level*, int32_t, int32_t, int32_t, int32_t);
};
