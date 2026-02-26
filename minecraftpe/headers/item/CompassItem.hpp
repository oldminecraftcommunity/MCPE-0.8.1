#pragma once
#include <item/Item.hpp>

struct CompassItem: Item
{
	TextureUVCoordinateSet textures[32];
	CompassItem(int32_t);
	virtual ~CompassItem();
	virtual TextureUVCoordinateSet* getIcon(int32_t, int32_t, bool_t);
	virtual int32_t getAnimationFrameFor(Mob*);
};
