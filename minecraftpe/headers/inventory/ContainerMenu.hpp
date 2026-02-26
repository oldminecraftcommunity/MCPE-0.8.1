#pragma once
#include <inventory/BaseContainerMenu.hpp>

struct Container;

struct ContainerMenu: BaseContainerMenu
{
	Container* container;
	int32_t field_1C;

	ContainerMenu(Container*, int32_t);

	virtual ~ContainerMenu();
	virtual std::vector<ItemInstance> getItems();
	virtual void setSlot(int32_t, ItemInstance*);
	virtual bool_t tileEntityDestroyedIsInvalid(int32_t);
};
