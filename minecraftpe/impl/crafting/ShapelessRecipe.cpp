#include <crafting/ShapelessRecipe.hpp>
#include <item/ItemInstance.hpp>
#include <crafting/CraftingContainer.hpp>
#include <algorithm>

ShapelessRecipe::ShapelessRecipe(std::vector<ItemInstance>& results, std::vector<ItemInstance>& ingridients)
	: field_1C(results)
	, field_28(ingridients) {
	for(int32_t v10 = 0; v10 < ingridients.size(); ++v10) {
		if(!ingridients[v10].isNull()) {
			this->items.add(ItemPack::getIdForItemInstance(&ingridients[v10]), 1);
		}
	}
}
ShapelessRecipe::~ShapelessRecipe() {
}
bool_t ShapelessRecipe::matches(CraftingContainer* a2) {
	std::vector<ItemInstance> v19(this->field_28);
	for(int i = 0; i != 3; ++i) {
		for(int j = 0; j != 3; ++j) {
			ItemInstance* it = a2->getItem(j, i);
			if(it) {
				ItemInstance* v6;
				for(int k = 0;; ++k) {
					if(k >= this->field_28.size()) {
						return 0;
					}
					v6 = &this->field_28[k];
					if(v6->sameItem(it)) {
						if(v6->getAuxValue() == -1) break;
						if(it->getAuxValue() == v6->getAuxValue()) break;
					}
				}

				auto&& v16 = std::find(v19.begin(), v19.end(), *v6);
				if(v16 != v19.end()) {
					v19.erase(v16); //TODO check
				}
			}
		}
	}
	return v19.empty();
}
int32_t ShapelessRecipe::getMaxCraftCount(ItemPack& a2) {
	return a2.getMaxMultipliesOf(this->items);
}
int32_t ShapelessRecipe::size() {
	return this->field_28.size();
}
std::vector<ItemInstance>* ShapelessRecipe::assemble(CraftingContainer* a2) {
	return &this->field_1C;
}
std::vector<ItemInstance>* ShapelessRecipe::getResultItem() const {
	return &this->field_1C;
}
int32_t ShapelessRecipe::getCraftingSize() {
	if(this->field_28.size()) {
		return Recipe::SIZE_2X2;
	}
	return Recipe::SIZE_3X3;
}
