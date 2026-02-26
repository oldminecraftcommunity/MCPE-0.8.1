#pragma once
#include <gui/Screen.hpp>
#include <gui/pane/IItemPaneCallback.hpp>
#include <gui/buttons/ImageButton.hpp>
#include <gui/buttons/CraftButton.hpp>

struct Recipe;
struct CItem;
struct ScrollingPane;
struct PaneCraftingScreen: Screen, IItemPaneCallback
{
	std::vector<ImageButton*> field_54;
	std::vector<CItem*> field_60;
	std::vector<std::vector<CItem*>> field_6C;
	int32_t field_78;
	CItem* field_7C;
	std::string field_80;
	std::vector<Button*> field_84;
	ImageButton closeButton;
	CraftButton craftButton;
	int32_t field_17C;
	ScrollingPane* scrollingPane;
	IntRectangle field_184;
	int32_t field_194;
	std::vector<int32_t> intvec1;
	std::vector<int32_t> intvec2;
	Button* field_1B0;
	NinePatchLayer* field_1B4;
	NinePatchLayer* field_1B8;
	NinePatchLayer* field_1BC;

	PaneCraftingScreen(int32_t);
	void _resortRecipes();
	void addItem(Recipe*);
	void clearCategoryItems();
	void closeScreen();
	void craftSelectedItem();
	void initCategories();
	void onItemSelected(int32_t, CItem*);
	void recheckRecipes();
	void setSingleCategoryAndIcon(int32_t, int32_t);

	virtual ~PaneCraftingScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual bool_t renderGameBehind();
	virtual bool_t closeOnPlayerHurt();
	virtual void buttonClicked(Button*);
	virtual void onItemSelected(const ItemPane*, int32_t);
	virtual std::vector<CItem*>* getItems(const ItemPane*);
	virtual void filterRecipes(std::vector<Recipe*>&);
	virtual bool_t filterRecipe(const Recipe&) = 0;
};
