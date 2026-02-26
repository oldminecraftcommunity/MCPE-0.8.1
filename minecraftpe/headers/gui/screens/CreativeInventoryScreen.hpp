#pragma once
#include <gui/Screen.hpp>
#include <gui/pane/Touch_IInventoryPaneCallback.hpp>
#include <memory>

struct ImageWithBackground;
struct NinePatchLayer;
struct Item;
struct Tile;
struct ImageButton;
struct CategoryButton;
namespace Touch {
	struct InventoryPane;
}
struct CreativeInventoryScreen: Screen, Touch::IInventoryPaneCallback
{
	struct TabButtonWithMeta
	{
		int32_t field_0;
		std::shared_ptr<ImageButton> field_4;
		TabButtonWithMeta(int f0, std::shared_ptr<ImageButton> f4);
		TabButtonWithMeta(const CreativeInventoryScreen::TabButtonWithMeta&);
		TabButtonWithMeta(CreativeInventoryScreen::TabButtonWithMeta&&);
		~TabButtonWithMeta();
	};
	static std::vector<ItemInstance> filteredItems[4];
	static std::vector<ItemInstance> items;

	int32_t field_58, field_5C;
	std::shared_ptr<ImageWithBackground> field_60;
	std::shared_ptr<NinePatchLayer> field_68;
	std::shared_ptr<NinePatchLayer> field_70;
	std::shared_ptr<Touch::InventoryPane> field_78[4];
	std::vector<CreativeInventoryScreen::TabButtonWithMeta> field_98;
	Button* field_A4;
	int32_t field_A8, field_AC, field_B0;
	int32_t currentPaneMaybe;
	int32_t field_B8;
	int8_t field_BC, field_BD, field_BE, field_BF;

	CreativeInventoryScreen();
	void _putItemInToolbar(const ItemInstance*);
	void closeWindow();
	std::shared_ptr<ImageButton> createInventoryTabButton(int32_t, int32_t);
	void drawIcon(int, std::shared_ptr<ImageButton>, bool_t, bool_t);
	int32_t getCategoryFromPanel(const Touch::InventoryPane*);
	ItemInstance getItemFromType(int32_t);
	static void populateFilteredItems();
	static void populateItem(Item*, int32_t, int32_t);
	static void populateItem(Tile*, int32_t, int32_t);
	static void populateItems();

	virtual ~CreativeInventoryScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual bool_t renderGameBehind();
	virtual void buttonClicked(Button*);
	virtual void mouseClicked(int32_t, int32_t, int32_t);
	virtual void mouseReleased(int32_t, int32_t, int32_t);
	virtual bool_t addItem(const Touch::InventoryPane*, int32_t);
	virtual bool_t isAllowed(int32_t);
	virtual std::vector<const ItemInstance*> getItems(const Touch::InventoryPane*);
};
