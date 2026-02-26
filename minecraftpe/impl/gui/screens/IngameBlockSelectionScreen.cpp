#include <gui/screens/IngameBlockSelectionScreen.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <entity/player/gamemode/GameMode.hpp>
#include <gui/screens/ArmorScreen.hpp>
#include <inventory/Inventory.hpp>
#include <rendering/Textures.hpp>
#include <rendering/entity/ItemRenderer.hpp>
#include <sound/SoundEngine.hpp>

IngameBlockSelectionScreen::IngameBlockSelectionScreen()
	: armorButton(1, "Armor")
	, field_98(1, 0, 0, 0, 0) {
	this->field_54 = 1;
	this->field_58 = 1;
	this->field_5C = 1;
	this->field_60 = 0;
	this->field_64 = 0;
}
int32_t IngameBlockSelectionScreen::getSelectedSlot(int32_t a2, int32_t a3) {
	int v6; // r8
	int v7; // r7
	int v8; // r6

	v6 = -10 * this->field_54 + this->width / 2;
	v7 = this->getSlotPosY(0) - 4;
	if(a2 < v6) {
		return -1;
	}
	if(a3 < v7) {
		return -1;
	}
	v8 = (a2 - v6) / 20;
	if(v8 >= this->field_54) {
		return -1;
	} else {
		return v8 + this->field_54 * ((a3 - v7) / this->getSlotHeight());
	}
}
int32_t IngameBlockSelectionScreen::getSlotHeight() {
	if(this->field_54 == 9) return 22;
	return 20;
}
int32_t IngameBlockSelectionScreen::getSlotPosX(int32_t a2) {
	return -10 * this->field_54 + this->width / 2 + 20 * a2 + 2;
}
int32_t IngameBlockSelectionScreen::getSlotPosY(int32_t a2) {
	int32_t v2;
	if(this->field_54 == 9) {
		v2 = 8;
	} else {
		v2 = 3;
	}
	return v2 + this->getSlotHeight() * a2;
}
bool_t IngameBlockSelectionScreen::isAllowed(int32_t a2) {
	return a2 >= 0 && a2 < this->field_5C;
}
void IngameBlockSelectionScreen::renderDemoOverlay() {
}
void IngameBlockSelectionScreen::renderSlot(int32_t a2, int32_t a3, int32_t a4, float a5) {
	FillingContainer* inventory; // r0
	const ItemInstance* v8;		 // r0
	ItemInstance* v9;			 // r6

	inventory = (FillingContainer*)this->minecraft->player->inventory;
	v8 = inventory->getItem(a2);
	v9 = (ItemInstance*)v8;
	if(v8) {
		ItemRenderer::renderGuiItemNew(this->minecraft->texturesPtr, v8, 0, (float)a3, (float)a4, 1.0, 1.0, 1.0);
		if(!this->minecraft->gameMode->isCreativeType() && this->isAllowed(a2 - 9)) {
			glPushMatrix();
			glScalef(Gui::InvGuiScale + Gui::InvGuiScale, Gui::InvGuiScale + Gui::InvGuiScale, 1.0);
			this->minecraft->gui.renderSlotText(v9, (float)(Gui::GuiScale * 0.5) * (float)a3, (float)(Gui::GuiScale * 0.5) * (float)a4, 1, 1);
			glPopMatrix();
		}
	}
}
void IngameBlockSelectionScreen::renderSlots() {
	int v2;				   // r6
	Textures* texturesPtr; // r5
	int slotPosX;		   // r9
	int v5;				   // r10
	int v6;				   // r8
	int v7;				   // r0
	int v8;				   // r5
	int slotPosY;		   // r0
	int i;				   // r5
	int v11;			   // r6
	int v12;			   // r7
	int v13;			   // r0
	int v14;			   // r1

	v2 = 0;
	glColor4f(1.0, 1.0, 1.0, 1.0);
	this->zLayer = -90.0;
	this->minecraft->texturesPtr->loadAndBindTexture("gui/gui.png");
	while(v2 < this->field_58) {
		slotPosX = this->getSlotPosX(0);
		v5 = slotPosX - 3;
		v6 = this->getSlotPosY(v2) - 3;
		if(this->field_54 == 9) {
			this->blit(v5, v6, 0, 0, 182, 22, 0, 0);
		} else {
			this->blit(v5, v6, 0, 0, 162, 22, 0, 0);
			this->blit(slotPosX + 159, v6, 182 - 20 * (this->field_54 - 8), 0, 20 * (this->field_54 - 8), 22, 0, 0);
		}
		++v2;
	}
	v7 = this->field_60;
	if(v7 >= 0) {
		v8 = this->getSlotPosX(v7 % this->field_54);
		slotPosY = this->getSlotPosY(this->field_60 / this->field_54);
		this->blit(v8 - 4, slotPosY - 4, 0, 22, 24, 22, 0, 0);
	}
	for(i = 0; i < this->field_58; ++i) {
		v11 = 0;
		v12 = this->getSlotPosY(i);
		while(v11 < this->field_54) {
			v13 = this->getSlotPosX(v11);
			v14 = v11 + this->field_54 * i;
			++v11;
			this->renderSlot(v14 + 9, v13, v12, 0.0);
		}
	}
}
void IngameBlockSelectionScreen::selectSlotAndClose() {
	this->minecraft->player->inventory->moveToSelectionSlot(0, this->field_60 + 9);
	this->minecraft->player->inventory->selectSlot(0);
	this->minecraft->gui.flashSlot(this->minecraft->player->inventory->selectedSlot);
	this->minecraft->soundEngine->playUI("random.click", 1.0, 1.0);
	this->minecraft->setScreen(0);
}

IngameBlockSelectionScreen::~IngameBlockSelectionScreen() {
}
void IngameBlockSelectionScreen::render(int32_t a2, int32_t a3, float a4) {
	glDisable(0xB71u);
	this->fill(0, 0, this->width, this->height, 0x80000000);
	this->renderSlots();
	this->renderDemoOverlay();
	glEnable(0xB71u);
	this->minecraft->gui.renderToolBar(a4, 0.0);
	Screen::render(a2, a3, a4);
}
void IngameBlockSelectionScreen::init() {
	this->field_54 = this->minecraft->isCreativeMode() ? 14 : 9;
	int32_t v6 = this->minecraft->player->inventory->getContainerSize();
	int32_t v7 = this->field_54;
	this->field_5C = v6 - 9;
	this->field_58 = (v6 - 10) / v7 + 1;
	int32_t spx = this->getSlotPosX(0);
	int32_t spy = this->getSlotPosY(0);
	int32_t v10 = this->getSlotPosX(this->field_54);
	int32_t v11 = this->getSlotPosY(this->field_58);
	this->field_98.field_4 = 1;
	this->field_98.minX = (float)spx - 4.0;
	this->field_98.maxX = (float)v10 + 4.0;
	this->field_98.minY = (float)spy - 4.0;
	this->field_98.maxY = (float)v11 + 4.0;
	ItemInstance* sel = this->minecraft->player->inventory->getSelected();
	if(!sel || sel->isNull()) {
		this->field_60 = 0;
	} else {
		for(int32_t i = 9; i < this->field_5C; ++i) {
			if(sel == this->minecraft->player->inventory->getItem(i)) {
				this->field_60 = i - 9;
				break;
			}
		}
		if(!this->isAllowed(this->field_60)) {
			this->field_60 = 0;
		}
		if(!this->minecraft->isCreativeMode()) {
			int32_t height = this->height;
			this->armorButton.width = 42;
			this->armorButton.posY = height - this->armorButton.height;
			this->armorButton.posX = 0;
			this->buttons.emplace_back(&this->armorButton);
		}
	}
}
void IngameBlockSelectionScreen::removed() {
	this->minecraft->gui.inventoryUpdated();
}
bool_t IngameBlockSelectionScreen::renderGameBehind() {
	return !this->minecraft->options.graphics;
}
void IngameBlockSelectionScreen::buttonClicked(Button* a2) {
	if(&this->armorButton == a2) {
		this->minecraft->setScreen(new ArmorScreen());
	}
}
void IngameBlockSelectionScreen::mouseClicked(int32_t a2, int32_t a3, int32_t a4) {
	int selSlot;	  // r9
	bool_t isAllowed; // r0
	bool v10;		  // r8

	if(a4 == 1) {
		selSlot = this->getSelectedSlot(a2, a3);
		isAllowed = this->isAllowed(selSlot);
		v10 = isAllowed;
		if(isAllowed) {
			this->field_60 = selSlot;
		} else {
			if(!this->field_98.isInside((float)a2, (float)a3)) {
				v10 = !this->armorButton.isInside(a2, a3);
			}
			this->field_64 = v10;
		}
	}
	if(!this->field_64) {
		Screen::mouseClicked(a2, a3, a4);
	}
}
void IngameBlockSelectionScreen::mouseReleased(int32_t a2, int32_t a3, int32_t a4) {
	if(a4 == 1) {
		int32_t selSlot = this->getSelectedSlot(a2, a3);
		if(this->isAllowed(selSlot) && selSlot == this->field_60) {
			this->selectSlotAndClose();
		} else if(this->field_64 && !this->field_98.isInside((float)a2, (float)a3)) {
			this->minecraft->setScreen(0);
		}
	}
	if(!this->field_64) {
		Screen::mouseReleased(a2, a3, a4);
	}
}
void IngameBlockSelectionScreen::keyPressed(int32_t a2) {
	int v3;				  // r8
	int v5;				  // r4
	int v6;				  // r1
	Minecraft* minecraft; // r7
	int v8;				  // r0

	v3 = this->field_54;
	v5 = this->field_60;
	v6 = v5 % v3;
	minecraft = this->minecraft;
	if(a2 == minecraft->options.keyLeft.keyCode && v6 > 0) {
		--v5;
	} else if(a2 == minecraft->options.keyRight.keyCode && v6 < v3 - 1) {
		++v5;
	} else {
		v8 = v5 / v3;
		if(a2 == minecraft->options.keyBack.keyCode && v8 < this->field_58 - 1) {
			v5 += v3;
		} else if(a2 == minecraft->options.keyForward.keyCode && v8 > 0) {
			v5 -= v3;
		}
	}
	if(this->isAllowed(v5)) {
		this->field_60 = v5;
	}
	if(a2 == minecraft->options.keyMenuOk.keyCode) {
		this->selectSlotAndClose();
	}
	if(a2 == minecraft->options.keyMenuCancel.keyCode) {
		this->minecraft->setScreen(0);
	}
}
