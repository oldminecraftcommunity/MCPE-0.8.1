#pragma once
#include <crafting/Recipe.hpp>
#include <crafting/CraftingContainer.hpp>
#include <item/ItemInstance.hpp>

struct ShapedRecipe: Recipe
{
	int32_t width, height;
	ItemInstance* field_24;
	std::vector<ItemInstance> field_28;
	ShapedRecipe(int32_t w, int32_t h, ItemInstance* f24, const std::vector<ItemInstance>& f28) :
			field_28(f28) {
		this->width = w;
		this->height = h;
		this->field_24 = f24;
		for (int32_t v30 = 0; v30 < w * h; ++v30) {
			if (!f24[v30].isNull()) {
				this->items.add(ItemPack::getIdForItemInstance(&f24[v30]), 1);
			}
		}
	}
	bool_t matches(CraftingContainer* a2, int32_t a3, int32_t a4, bool_t a5) {
		int v7 = -a3;
		for(int x = 0; x != 3; ++x){
			int v23 = -a4;
			for (int y = 0; y != 3; ++y) {
				ItemInstance v26;
				if (v7 >= 0 && v23 >= 0) {
					int width = this->width;
					if (v7 < width && v23 < this->height) {
						int v10 = width * v23;
						if (a5) {
							v26 = this->field_24[width - v7 + v10 - 1];
						} else {
							v26 = this->field_24[v7 + v10];
						}
					}
				}
				ItemInstance* item = a2->getItem(x, y);
				if (item || !v26.isNull()) {
					if ((item == 0) != v26.isNull()) {
						return 0;
					}
					if (!v26.sameItem(item)) {
						return 0;
					}
					if (v26.getAuxValue() != -1) {
						int auxValue = v26.getAuxValue();
						if (auxValue != item->getAuxValue()) {
							return 0;
						}
					}
				}
				++v23;
			}
			++v7;
		}

		return 1;
	}

	virtual ~ShapedRecipe() {
		if (this->field_24) delete[] this->field_24;
	}
	virtual bool_t matches(CraftingContainer* a2) {
		int32_t i; // r4
		int32_t j; // r5
		for (i = 0; i <= 3 - this->width; ++i) {
			for (j = 0; j <= 3 - this->height; ++j) {
				if (this->matches(a2, i, j, 1) || this->matches(a2, i, j, 0)) {
					return 1;
				}
			}
		}
		return 0;
	}
	virtual int32_t getMaxCraftCount(ItemPack& a2) {
		return a2.getMaxMultipliesOf(this->items);
	}
	virtual int32_t size() {
		return this->height * this->width;
	}
	virtual std::vector<ItemInstance>* assemble(CraftingContainer* a2) {
		return &this->field_28;
	}
	const virtual std::vector<ItemInstance>* getResultItem() const {
		return &this->field_28;
	}
	virtual int32_t getCraftingSize() {
		if (this->width > 2 || this->height > 2) return Recipe::SIZE_3X3;

		return Recipe::SIZE_2X2;
	}
	virtual std::vector<ItemInstance> getItems() {
		//TODO check return type
		return {};
	}
};
