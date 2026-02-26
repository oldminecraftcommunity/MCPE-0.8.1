#pragma once
#include <item/Item.hpp>

struct ClockItem: Item
{
	TextureUVCoordinateSet textures[64];

	ClockItem(int32_t);

	virtual ~ClockItem();
	virtual TextureUVCoordinateSet* getIcon(int32_t, int32_t, bool_t);
	virtual int32_t getAnimationFrameFor(Mob*);
};
