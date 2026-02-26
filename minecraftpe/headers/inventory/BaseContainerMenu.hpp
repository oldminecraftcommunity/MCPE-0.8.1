#pragma once
#include <_types.h>
#include <vector>
struct ItemInstance;
struct IContainerListener;

struct BaseContainerMenu
{
	int32_t field_0;
	int32_t containerID;
	IContainerListener* containerListener;
	std::vector<ItemInstance> field_C;

	BaseContainerMenu(int32_t);

	virtual ~BaseContainerMenu();
	virtual std::vector<ItemInstance> getItems() = 0;
	virtual void setSlot(int32_t, ItemInstance*) = 0;
	virtual void setData(int32_t, int32_t);
	virtual void setListener(IContainerListener*);
	virtual void broadcastChanges();
	virtual bool_t isResultSlot(int32_t);
	virtual bool_t tileEntityDestroyedIsInvalid(int32_t) = 0;
};
