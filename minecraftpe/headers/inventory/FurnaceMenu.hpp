#pragma once
#include <inventory/BaseContainerMenu.hpp>

struct FurnaceTileEntity;
struct FurnaceMenu: BaseContainerMenu
{
	FurnaceTileEntity* tileEntity;
	int32_t field_1C, field_20, field_24, field_28;

	FurnaceMenu(FurnaceTileEntity*);

	virtual ~FurnaceMenu();
	virtual std::vector<ItemInstance> getItems();
	virtual void setSlot(int32_t, ItemInstance*);
	virtual void setData(int32_t, int32_t);
	virtual void setListener(IContainerListener*);
	virtual void broadcastChanges();
	virtual bool_t tileEntityDestroyedIsInvalid(int32_t);
};
