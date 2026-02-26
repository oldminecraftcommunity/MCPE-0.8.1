#pragma once
#include <_types.h>
#include <vector>

struct ItemInstance;
struct BaseContainerMenu;
struct IContainerListener
{
	virtual ~IContainerListener();
	virtual void refreshContainer(BaseContainerMenu*, const std::vector<ItemInstance>);
	virtual void slotChanged(BaseContainerMenu*, int32_t, const ItemInstance&, bool_t);
	virtual void setContainerData(BaseContainerMenu*, int32_t, int32_t);
};
