#pragma once
#include <_types.h>
#include <vector>
#include <string>
#include <item/ItemInstance.hpp>
struct Player;
struct Container
{
	virtual ~Container();
	virtual ItemInstance* getItem(int32_t) = 0;
	virtual void setItem(int32_t, ItemInstance*) = 0;
	virtual ItemInstance removeItem(int32_t, int32_t) = 0;
	virtual std::string getName() = 0;
	virtual int32_t getContainerSize() = 0;
	virtual int32_t getMaxStackSize() = 0;
	virtual bool_t stillValid(Player*) = 0;
	virtual void startOpen() = 0;
	virtual void stopOpen() = 0;
	virtual std::vector<ItemInstance> getSlotCopies();
};
