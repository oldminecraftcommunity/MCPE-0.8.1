#pragma once
#include <gui/screens/BaseContainerScreen.hpp>
#include <gui/pane/Touch_IInventoryPaneCallback.hpp>
#include <gui/buttons/ImageButton.hpp>
#include <gui/buttons/Touch_THeader.hpp>
#include <util/IntRectangle.hpp>

struct Player;
struct FlyingItem;
struct ChestTileEntity;
struct NinePatchLayer;
struct Tesselator;
struct FillingContainer;

struct ChestScreen: BaseContainerScreen, Touch::IInventoryPaneCallback
{
	std::string field_5C;
	ImageButton field_60;
	Touch::THeader field_D0, field_104;
	Touch::InventoryPane* field_138;
	Touch::InventoryPane* field_13C;
	IntRectangle field_140;
	std::vector<const ItemInstance*> field_150;
	std::vector<const ItemInstance*> field_15C;
	bool_t needsSetup;
	int8_t field_169, field_16A, field_16B;
	int32_t field_16C;
	NinePatchLayer* field_170;
	NinePatchLayer* field_174;
	NinePatchLayer* field_178;
	NinePatchLayer* field_17C;
	NinePatchLayer* field_180;
	Player* player;
	ChestTileEntity* tileEntity;
	int8_t field_18C, field_18D, field_18E, field_18F;
	std::vector<FlyingItem> field_190;

	ChestScreen(Player*, ChestTileEntity*);
	void drawSlotItemAt(Tesselator&, const ItemInstance*, int32_t, int32_t, bool_t);
	bool_t handleAddItem(FillingContainer*, FillingContainer*, int32_t);
	void handleRenderPane(Touch::InventoryPane*, Tesselator&, int32_t, int32_t, float);
	void setupPane();

	virtual ~ChestScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual void tick();
	virtual bool_t renderGameBehind();
	virtual void onInternetUpdate();
	virtual void buttonClicked(Button*);
	virtual bool_t addItem(const Touch::InventoryPane*, int32_t);
	virtual bool_t isAllowed(int32_t);
	virtual std::vector<const ItemInstance*> getItems(const Touch::InventoryPane*);
};
