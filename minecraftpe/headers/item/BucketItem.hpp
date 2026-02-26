#pragma once
#include <item/Item.hpp>
struct BucketItem: Item
{
	TextureUVCoordinateSet field_48, field_60, field_78, field_90;

	BucketItem(int32_t);
	bool_t emptyBucket(Level*, int32_t, int32_t, int32_t, int32_t);

	virtual ~BucketItem();
	virtual int32_t getMaxStackSize(const ItemInstance*);
	virtual TextureUVCoordinateSet* getIcon(int32_t, int32_t, bool_t);
	virtual bool_t useOn(ItemInstance*, Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
	virtual bool_t isLiquidClipItem(int32_t);
	virtual std::string getDescriptionId(const ItemInstance*);
	virtual bool_t isEmissive(int32_t);
};
