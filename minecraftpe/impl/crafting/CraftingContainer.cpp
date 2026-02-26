#include <crafting/CraftingContainer.hpp>

ItemInstance* CraftingContainer::getItem(int32_t a2, int32_t a3) {
	if(a2 < 0) return 0;
	if(a3 >= this->field_14) return 0;
	//TODO find what is field_0
	printf("CraftingContainer::getItem - not implemented <!>\n");
	return 0;
}
