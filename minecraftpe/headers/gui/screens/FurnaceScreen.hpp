#pragma once
#include <gui/screens/BaseContainerScreen.hpp>
#include <gui/pane/Touch_IInventoryPaneCallback.hpp>
#include <gui/buttons/ImageButton.hpp>
#include <gui/buttons/BlankButton.hpp>
#include <gui/buttons/Touch_THeader.hpp>
#include <item/ItemInstance.hpp>
#include <util/IntRectangle.hpp>

struct NinePatchLayer;
struct Player;
struct FurnaceTileEntity;
struct CItem;
struct Tesselator;

struct FurnaceScreen: BaseContainerScreen, Touch::IInventoryPaneCallback
{
	std::vector<CItem*> field_5C;
	std::string field_68;
	ItemInstance field_6C;
	float field_80;
	ImageButton field_84;
	BlankButton field_F4, field_124, field_154;
	Touch::THeader field_184;
	Touch::InventoryPane* field_1B8;
	IntRectangle field_1BC;
	std::vector<CItem*> field_1CC;
	std::vector<CItem*> field_1D8;
	std::vector<int32_t> field_1E4;
	std::vector<const ItemInstance*> field_1F0;
	bool_t field_1FC;
	int8_t field_1FD, field_1FE, field_1FF;
	int32_t field_200;
	int32_t resultIdMaybe;
	NinePatchLayer* field_208;
	NinePatchLayer* field_20C;
	NinePatchLayer* field_210;
	NinePatchLayer* field_214;
	NinePatchLayer* field_218;
	Player* player;
	FurnaceTileEntity* tileEntity;
	int8_t field_224, field_225, field_226, field_227;

	FurnaceScreen(Player*, FurnaceTileEntity*);
	bool_t canMoveToFurnace(int32_t, const ItemInstance*);
	void clearItems();
	void drawSlotItemAt(Tesselator&, const ItemInstance*, int32_t, int32_t, bool_t);
	bool_t handleAddItem(int32_t, const ItemInstance*);
	void handleRenderPane(Touch::InventoryPane*, Tesselator&, int32_t, int32_t, float);
	ItemInstance moveOver(const ItemInstance*, int32_t);
	void recheckRecipes();
	void setupInventoryPane();
	void takeAndClearSlot(int32_t);
	void updateItems();
	void updateResult(const ItemInstance*);

	virtual ~FurnaceScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual void tick();
	virtual bool_t renderGameBehind();
	virtual void buttonClicked(Button*);
	virtual bool_t addItem(const Touch::InventoryPane*, int32_t);
	virtual bool_t isAllowed(int32_t);
	virtual std::vector<const ItemInstance*> getItems(const Touch::InventoryPane*);
};
