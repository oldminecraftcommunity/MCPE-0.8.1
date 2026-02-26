#pragma once
#include <inventory/Container.hpp>
struct ListTag;
struct FillingContainer: Container
{
	struct LinkedSlot
	{
		int32_t field_0;
	};

	int32_t field_0, field_4;
	std::vector<FillingContainer::LinkedSlot> linkedSlots;
	std::vector<ItemInstance *> items;
	bool_t field_20;
	int8_t field_21, field_22, field_23;

	FillingContainer(int32_t, int32_t, int32_t, bool_t);
	int32_t addItem(ItemInstance*);
	int32_t addResource(const ItemInstance&);
	void clearInventory(int32_t);
	void clearSlot(int32_t);
	void compressLinkedSlotList(int32_t);
	bool_t contains(ItemInstance*);
	void dropAll(bool_t);
	void dropSlot(int32_t, bool_t, bool_t);
	void fixBackwardCompabilityItem(ItemInstance&);
	int32_t getEmptySlotsCount();
	int32_t getFreeSlot();
	ItemInstance* getLinked(int32_t);
	int32_t getLinkedSlot(int32_t);
	int32_t getLinkedSlotsCount();
	int32_t getNonEmptySlot(int32_t);
	int32_t getNonEmptySlot(int32_t, int32_t);
	int32_t getSlot(int32_t);
	int32_t getSlot(int32_t, int32_t);
	std::vector<ItemInstance*>* getSlotList(int32_t&);
	int32_t getSlotWithRemainingSpace(const ItemInstance&);
	bool_t hasResource(int32_t);
	bool_t linkEmptySlot(int32_t);
	bool_t linkSlot(int32_t, int32_t);
	void load(ListTag*);
	void release(int32_t);
	bool_t removeResource(const ItemInstance&);
	int32_t removeResource(const ItemInstance&, bool_t);
	bool_t removeResource(int32_t);
	void replace(std::vector<ItemInstance>, int32_t);
	void replaceSlot(int32_t, ItemInstance*);
	ListTag* save(ListTag*);
	void setContainerChanged();
	void swapSlots(int32_t, int32_t);
	void unlinkSlot(int32_t);

	virtual ~FillingContainer();
	virtual ItemInstance* getItem(int32_t);
	virtual void setItem(int32_t, ItemInstance*);
	virtual ItemInstance removeItem(int32_t, int32_t);
	virtual std::string getName();
	virtual int32_t getContainerSize() = 0;
	virtual int32_t getMaxStackSize();
	virtual bool_t stillValid(Player*);
	virtual void startOpen();
	virtual void stopOpen();

	virtual bool_t add(ItemInstance*);
	virtual void doDrop(ItemInstance*, bool_t);
};
