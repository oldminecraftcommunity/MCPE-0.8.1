#pragma once
#include <_types.h>
#include <vector>

struct CItem;
struct ItemPane;
struct IItemPaneCallback
{
	virtual ~IItemPaneCallback();
	virtual void onItemSelected(const ItemPane*, int32_t) = 0;
	virtual std::vector<CItem*>* getItems(const ItemPane*) = 0;
};
