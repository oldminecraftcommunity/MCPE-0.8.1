#pragma once
#include <inventory/BaseContainerMenu.hpp>

struct Container;
struct InventoryMenu: BaseContainerMenu
{
	Container* linkedContainer;

	InventoryMenu(Container*);

	virtual ~InventoryMenu();
	virtual std::vector<ItemInstance> getItems();
	virtual void setSlot(int32_t, ItemInstance*);
	virtual bool_t tileEntityDestroyedIsInvalid(int32_t);
};
