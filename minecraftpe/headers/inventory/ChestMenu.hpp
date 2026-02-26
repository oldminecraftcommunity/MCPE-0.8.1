#pragma once
#include <inventory/ContainerMenu.hpp>
struct ChestTileEntity;
struct ChestMenu: ContainerMenu
{
	ChestTileEntity* field_24;
	int32_t field_28;
	ChestMenu(ChestTileEntity* a2);

	virtual ~ChestMenu();
	virtual bool_t tileEntityDestroyedIsInvalid(int32_t);
};
