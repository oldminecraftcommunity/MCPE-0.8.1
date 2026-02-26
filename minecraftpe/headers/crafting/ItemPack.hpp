#pragma once
#include <_types.h>
#include <map>
#include <vector>

struct ItemInstance;
struct ItemPack
{
	std::map<int32_t, int32_t> items;

	void add(int32_t id, int32_t cnt);
	int32_t getCount(int32_t);
	static int32_t getIdForItemInstance(const ItemInstance*);
	static int32_t getIdForItemInstanceAnyAux(const ItemInstance*);
	static ItemInstance getItemInstanceForId(int32_t);
	std::vector<ItemInstance> getItemInstances();
	int32_t getMaxMultipliesOf(ItemPack&);
	void print();
};
