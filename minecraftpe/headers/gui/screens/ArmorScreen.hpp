#pragma once
#include <gui/Screen.hpp>
#include <gui/pane/Touch_IInventoryPaneCallback.hpp>
#include <gui/buttons/BlankButton.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/buttons/Touch_THeader.hpp>
#include <item/ItemInstance.hpp>
#include <util/IntRectangle.hpp>

struct Tesselator;
struct Player;
struct ArmorScreen: Screen, Touch::IInventoryPaneCallback
{
	void* field_58;
	int32_t field_5C, field_60;
	std::string field_64;
	ItemInstance field_68;
	float field_7C;
	Touch::TButton backButton;
	BlankButton field_B8, field_E8, field_118, field_148;
	BlankButton* field_178[4];
	Touch::THeader header;
	Touch::InventoryPane* field_1BC;
	IntRectangle field_1C0;
	int32_t field_1D0, field_1D4, field_1D8, field_1DC;
	std::vector<const ItemInstance*> field_1E0;
	bool_t performUpdate;
	int8_t field_1ED, field_1EE, field_1EF;
	NinePatchLayer* field_1F0;
	NinePatchLayer* field_1F4;
	NinePatchLayer* field_1F8;
	NinePatchLayer* field_1FC;
	Player* player;

	ArmorScreen();
	bool_t canMoveToSlot(int32_t, const ItemInstance*);
	void closeScreen();
	void drawSlotItemAt(Tesselator&, int32_t, const ItemInstance*, int32_t, int32_t);
	void handleRenderPane(Touch::InventoryPane*, Tesselator&, int32_t, int32_t, float);
	void renderPlayer(float, float);
	bool_t takeAndClearSlot(int32_t);
	void updateItems();
	void setupInventoryPane();

	virtual ~ArmorScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual bool_t renderGameBehind();
	virtual void buttonClicked(Button*);
	virtual bool_t addItem(const Touch::InventoryPane*, int32_t);
	virtual bool_t isAllowed(int32_t);
	virtual std::vector<const ItemInstance*> getItems(const Touch::InventoryPane*);
};
