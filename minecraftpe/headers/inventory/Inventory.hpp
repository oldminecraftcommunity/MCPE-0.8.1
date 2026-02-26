#pragma once
#include <inventory/FillingContainer.hpp>

struct Player;
struct Inventory: FillingContainer
{
	int32_t selectedSlot;
	Player* player;

	Inventory(Player*, bool_t);
	bool_t canDestroy(Tile*);
	void clearInventoryWithDefault();
	int32_t getAttackDamage(Entity*);
	float getDestroySpeed(Tile*);
	int32_t getLinkedSlotForItem(int32_t);
	int32_t getLinkedSlotForItemAndAux(int32_t, int32_t);
	ItemInstance* getSelected();
	int32_t getSelectionSize();
	bool_t moveToEmptySelectionSlot(int32_t);
	bool_t moveToSelectedSlot(int32_t);
	bool_t moveToSelectionSlot(int32_t, int32_t);
	bool_t removeItemInstance(const ItemInstance*);
	void selectSlot(int32_t);
	void setupDefault();

	virtual ~Inventory();
	virtual int32_t getContainerSize();
	virtual bool_t stilValid(Player*);
	virtual bool_t add(ItemInstance*);
	virtual void doDrop(ItemInstance*, bool_t);
};
