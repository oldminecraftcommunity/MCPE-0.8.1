#pragma once
#include <_types.h>
#include <vector>

struct ItemInstance;
struct ItemDiffer
{
	int32_t len, field_4;
	ItemInstance* items;

	ItemDiffer(const std::vector<const ItemInstance*>&);
	void getDiff(const std::vector<const ItemInstance*>&, std::vector<int32_t>&);

};
