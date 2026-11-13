#include <gui/screens/StonecutterScreen.hpp>
#include <crafting/CraftingFilters.hpp>
#include <crafting/Recipe.hpp>
#include <item/ItemInstance.hpp>

StonecutterScreen::StonecutterScreen()
	: PaneCraftingScreen(Recipe::SIZE_3X3) {
	this->setSingleCategoryAndIcon(1, 5);
}

StonecutterScreen::~StonecutterScreen() {
}
bool_t StonecutterScreen::filterRecipe(const Recipe& a2) {
	return CraftingFilters::isStonecutterItem((*a2.getResultItem())[0]);
}
