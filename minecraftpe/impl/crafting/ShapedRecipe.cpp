#include <crafting/ShapedRecipe.hpp>
#include <crafting/CraftingContainer.hpp>
#include <item/ItemInstance.hpp>
ShapedRecipe::ShapedRecipe(int32_t w, int32_t h, ItemInstance* f24, const std::vector<ItemInstance>& f28)
	: field_28(f28) {
	this->width = w;
	this->height = h;
	this->field_24 = f24;
	for(int32_t v30 = 0; v30 < w * h; ++v30) {
		if(!f24[v30].isNull()) {
			this->items.add(ItemPack::getIdForItemInstance(&f24[v30]), 1);
		}
	}
}
bool_t ShapedRecipe::matches(CraftingContainer* a2, int32_t a3, int32_t a4, bool_t a5) {
	int32_t v7;			// r4
	int32_t v8;			// r8
	int32_t width;		// r2
	int32_t v10;		// r3
	int32_t v11;		// r3
	ItemInstance* v13;	// r3
	ItemInstance* item; // r6
	int32_t i;			// r7
	int32_t v23;		// r5
	int32_t auxValue;	// [sp+4h] [bp-4Ch]
	int32_t v25;		// [sp+Ch] [bp-44h]
	ItemInstance v26;	// [sp+14h] [bp-3Ch] BYREF

	v7 = -a3;
	v8 = 0;
	v25 = -a4;
	do {
		v23 = v25;
		for(i = 0; i != 3; ++i) {
			ItemInstance v26;
			if(v7 >= 0 && v23 >= 0) {
				width = this->width;
				if(v7 < width && v23 < this->height) {
					v10 = width * v23;
					if(a5) {
						v11 = width - v7 + v10;
						v13 = &this->field_24[v11 - 1];
						v26 = *v13;
					} else {
						v13 = &this->field_24[v7 + v10];
						v26 = *v13;
					}
				}
			}
			item = a2->getItem(v8, i);
			if(item || !v26.isNull()) {
				if((item == 0) != v26.isNull()) {
					return 0;
				}
				if(!v26.sameItem(item)) {
					return 0;
				}
				if(v26.getAuxValue() != -1) {
					auxValue = v26.getAuxValue();
					if(auxValue != item->getAuxValue()) {
						return 0;
					}
				}
			}
			++v23;
		}
		++v8;
		++v7;
	} while(v8 != 3);
	return 1;
}

ShapedRecipe::~ShapedRecipe() {
	if(this->field_24) delete[] this->field_24;
}
bool_t ShapedRecipe::matches(CraftingContainer* a2) {
	int32_t i; // r4
	int32_t j; // r5

	for(i = 0; i <= 3 - this->width; ++i) {
		for(j = 0; j <= 3 - this->height; ++j) {
			if(this->matches(a2, i, j, 1) || this->matches(a2, i, j, 0)) {
				return 1;
			}
		}
	}
	return 0;
}
int32_t ShapedRecipe::getMaxCraftCount(ItemPack& a2) {
	return a2.getMaxMultipliesOf(this->items);
}
int32_t ShapedRecipe::size() {
	return this->height * this->width;
}
std::vector<ItemInstance>* ShapedRecipe::assemble(CraftingContainer* a2) {
	return &this->field_28;
}
const std::vector<ItemInstance>* ShapedRecipe::getResultItem() const {
	return &this->field_28;
}
int32_t ShapedRecipe::getCraftingSize() {
	if(this->width > 2 || this->height > 2) return Recipe::SIZE_3X3;
	return Recipe::SIZE_2X2;
}
std::vector<ItemInstance> ShapedRecipe::getItems() {
	//TODO check return type
	return {};
}
