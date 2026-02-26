#pragma once
#include <item/Item.hpp>

struct BowItem: Item
{
	TextureUVCoordinateSet textures[3];

	BowItem(int32_t);

	float _getLaunchPower(int32_t);

	virtual ~BowItem();
	virtual TextureUVCoordinateSet* getIcon(int32_t, int32_t, bool_t);
	virtual ItemInstance* use(ItemInstance*, Level*, Player*);
	virtual int32_t getMaxUseDuration();
	virtual int32_t getUseAnimation();
	virtual void releaseUsing(ItemInstance*, Level*, Player*, int32_t);
	virtual int32_t getAnimationFrameFor(Mob*);

};
