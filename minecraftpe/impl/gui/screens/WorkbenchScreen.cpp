#include <gui/screens/WorkbenchScreen.hpp>
#include <crafting/CraftingFilters.hpp>
#include <crafting/Recipe.hpp>
#include <item/ItemInstance.hpp>

WorkbenchScreen::WorkbenchScreen(int32_t a2) : PaneCraftingScreen(a2){

}
WorkbenchScreen::~WorkbenchScreen() {
}
bool_t WorkbenchScreen::filterRecipe(const Recipe& a2) {
	return !CraftingFilters::isStonecutterItem(a2.getResultItem()->at(0));
}
