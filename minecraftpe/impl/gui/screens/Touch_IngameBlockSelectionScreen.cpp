#include <gui/screens/Touch_IngameBlockSelectionScreen.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <gui/pane/Touch_InventoryPane.hpp>
#include <gui/screens/ArmorScreen.hpp>
#include <gui/screens/WorkbenchScreen.hpp>
#include <input/Mouse.hpp>
#include <inventory/Inventory.hpp>
#include <rendering/Textures.hpp>
#include <sound/SoundEngine.hpp>

Touch::IngameBlockSelectionScreen::IngameBlockSelectionScreen()
	: selectBlocksHeader(0, "Select blocks")
	, backButton(3, "Back", 0)
	, craftButton(1, "Craft", 0)
	, armorButton(4, "Armor", 0)
	, menuButton(2, "Menu", 0) {
	this->field_58 = 0;
	this->field_5C = 0;
	this->field_60 = 0;
	this->field_178 = 0;
	this->field_17C = 0;
	this->field_180 = 1;
	this->field_184 = 1;
};
int32_t Touch::IngameBlockSelectionScreen::getSlotPosX(int32_t a2) {
	return -10 * this->field_190 + this->width / 2 + 20 * a2 + 2;
}
int32_t Touch::IngameBlockSelectionScreen::getSlotPosY(int32_t a2) {
	return this->height - 63 - 22 * a2;
}
void Touch::IngameBlockSelectionScreen::renderDemoOverlay() {
}

Touch::IngameBlockSelectionScreen::~IngameBlockSelectionScreen() {
	if(this->field_60) {
		delete this->field_60;
	}
}
void Touch::IngameBlockSelectionScreen::render(int32_t a2, int32_t a3, float a4) {
	Touch::InventoryPane* v8; // r7

	this->renderBackground(0);
	Screen::render(a2, a3, a4);
	this->field_60->render(a2, a3, a4);
	v8 = this->field_60;
	this->minecraft->texturesPtr->loadAndBindTexture("gui/itemframe.png");
	glColor4f(1.0, 1.0, 1.0, 1.0);
	this->blit(0, v8->field_228.minY - 6, 0, 0, this->width, v8->field_228.height + 10, 215, 256);
	this->minecraft->gui.renderToolBar(a4, 1.0);
	this->minecraft->gui.renderOnSelectItemNameText(this->width, this->font, this->height - 19);
}
void Touch::IngameBlockSelectionScreen::init() {
	Minecraft* minecraft;	   // r3
	Inventory* inventory;	   // r5
	int width;				   // r3
	int v5;					   // r2
	int v6;					   // r2
	int v7;					   // kr00_4
	int height;				   // r3
	int v9;					   // r8
	Touch::InventoryPane* v10; // r6
	int v11;				   // r0
	int v12;				   // r1
	IntRectangle r3_0;		   // [sp+20h] [bp-28h] BYREF

	this->armorButton.width = 38;
	this->craftButton.width = 38;
	this->backButton.width = 38;
	this->armorButton.height = 18;
	this->craftButton.height = 18;
	this->backButton.height = 18;
	this->backButton.init(this->minecraft);
	this->armorButton.init(this->minecraft);
	this->menuButton.init(this->minecraft);
	this->craftButton.init(this->minecraft);
	minecraft = this->minecraft;
	r3_0.minY = 30;
	inventory = minecraft->player->inventory;
	width = this->width;
	v5 = width - 20;
	if(width - 20 < 0) {
		v5 = width + 11;
	}
	v6 = v5 >> 5;
	this->field_190 = v6;
	r3_0.width = 32 * v6;
	v7 = width - 32 * v6;
	height = this->height;
	r3_0.minX = v7 / 2;
	r3_0.height = height - 56;
	v9 = inventory->getContainerSize();
	v10 = new Touch::InventoryPane(this, this->minecraft, r3_0, this->width, 4.0, v9 - 9, 32, 4, 1);
	this->field_60 = v10;
	v10->field_248 = v7 / 2;
	v11 = inventory->getContainerSize();
	v12 = this->field_190;
	this->field_18C = v11;
	this->field_188 = (v11 - 1) / v12 + 1;
	this->buttons.emplace_back(&this->selectBlocksHeader);
	this->buttons.emplace_back(&this->backButton);
	if(!this->minecraft->isCreativeMode()) {
		this->buttons.emplace_back(&this->craftButton);
		this->buttons.emplace_back(&this->armorButton);
	}
}
void Touch::IngameBlockSelectionScreen::setupPositions() {
	int32_t width;		  // r4
	int32_t v2;			  // r2
	int32_t v3;			  // r2
	int32_t v4;			  // r4
	Minecraft* minecraft; // r2
	int32_t v6;			  // r2

	width = this->width;
	this->armorButton.posY = 4;
	this->craftButton.posY = 4;
	this->backButton.posY = 4;
	this->backButton.posX = 4;
	v2 = this->armorButton.width;
	this->selectBlocksHeader.width = width;
	v3 = width - v2;
	v4 = this->craftButton.width;
	v3 -= 4;
	this->armorButton.posX = v3;
	this->craftButton.posX = v3 - v4 - 4;
	minecraft = this->minecraft;
	this->selectBlocksHeader.posY = 0;
	this->selectBlocksHeader.posX = 0;
	this->field_178 = 0;
	v6 = minecraft->field_1C;
	this->field_17C = 0;
	this->field_180 = v6;
	this->field_184 = (int32_t)(float)(Gui::GuiScale * 24.0);
}
void Touch::IngameBlockSelectionScreen::tick() {
	this->field_60->tick();
	Screen::tick();
}
void Touch::IngameBlockSelectionScreen::removed() {
	this->minecraft->gui.inventoryUpdated();
}
bool_t Touch::IngameBlockSelectionScreen::hasClippingArea(IntRectangle& a2) {
	a2.minX = this->field_178;
	a2.minY = this->field_17C;
	a2.width = this->field_180;
	a2.height = this->field_184;
	return 1;
}
void Touch::IngameBlockSelectionScreen::buttonClicked(Button* a2) {
	if(a2->buttonID == this->backButton.buttonID) {
		this->minecraft->setScreen(0);
	}
	if(a2->buttonID == this->menuButton.buttonID) {
		this->minecraft->screenChooser.setScreen(PAUSE_SCREEN_0);
	}
	if(a2->buttonID == this->craftButton.buttonID) {
		this->minecraft->setScreen(new WorkbenchScreen(0));
	}
	if(a2 == (Button*)&this->armorButton) {
		this->minecraft->setScreen(new ArmorScreen());
	}
}
void Touch::IngameBlockSelectionScreen::mouseClicked(int32_t a2, int32_t a3, int32_t a4) {
	bool_t v8; // r0

	v8 = this->field_60->field_23C->isInside((float)a2, (float)a3);
	this->field_5C = v8;
	if(!v8) {
		this->minecraft->gui.handleClick(1, Mouse::getX(), Mouse::getY());
		Screen::mouseClicked(a2, a3, a4);
	}
}
void Touch::IngameBlockSelectionScreen::mouseReleased(int32_t a2, int32_t a3, int32_t a4) {
	if(this->field_5C && this->field_60->field_23C->isInside((float)a2, (float)a3)) {
		this->minecraft->setScreen(0);
	} else {
		Screen::mouseReleased(a2, a3, a4);
	}
}
bool_t Touch::IngameBlockSelectionScreen::addItem(const InventoryPane* a2, int32_t a3) {
	int32_t v3;			  // r6
	Inventory* inventory; // r4
	int32_t lsfi;		  // r7

	v3 = a3 + 9;
	inventory = this->minecraft->player->inventory;
	if(inventory->getItem(a3 + 9)) {
		lsfi = inventory->getLinkedSlotForItem(v3);
		if(lsfi < 0 || lsfi >= this->minecraft->gui.getNumSlots() - 1) {
			inventory->moveToSelectionSlot(inventory->selectedSlot, v3);
		} else {
			inventory->selectedSlot = lsfi;
		}

		this->minecraft->soundEngine->playUI("random.pop2", 1.0, 0.3);
		this->minecraft->gui.resetItemNameOverlay();
		this->minecraft->gui.flashSlot(inventory->selectedSlot);
		return 1;
	}
	return 0;
}

bool_t Touch::IngameBlockSelectionScreen::isAllowed(int32_t a2) {
	if(a2 >= 0) {
		if(a2 < this->minecraft->player->inventory->getContainerSize()) {
			return 1;
		}
	}
	return 0;
}
std::vector<const ItemInstance*> Touch::IngameBlockSelectionScreen::getItems(const InventoryPane* a3) {
	std::vector<const ItemInstance*> a1;
	for(int32_t v5 = 9; v5 < this->minecraft->player->inventory->getContainerSize(); ++v5) {
		ItemInstance* v7 = this->minecraft->player->inventory->getItem(v5);
		a1.emplace_back(v7);
	}
	return a1;
}
