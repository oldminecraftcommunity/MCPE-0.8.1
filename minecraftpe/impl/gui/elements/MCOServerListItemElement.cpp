#include <gui/elements/MCOServerListItemElement.hpp>
#include <gui/buttons/ImageWithBackground.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/Gui.hpp>
#include <input/Mouse.hpp>
#include <math.h>
#include <rendering/Textures.hpp>
#include <rendering/Font.hpp>
#include <Minecraft.hpp>
#include <gui/screens/ManageMCOServerScreen.hpp>


MCOServerListItemElement::MCOServerListItemElement(Minecraft*, struct MCOServerListItem&, bool_t, std::function<void (MCOServerListItem&, bool_t)>);

MCOServerListItemElement::~MCOServerListItemElement() {
	if(this->field_78) {
		delete this->field_78;
		this->field_78 = 0;
	}
	if(this->field_7C) {
		delete this->field_7C;
		this->field_7C = 0;
	}
}
void MCOServerListItemElement::tick(Minecraft* a2) {
	float v3; // s16
	float v4; // s15
	Button* v5; // r0
	Button* v6; // r3

	v3 = (float)Mouse::getX() * Gui::InvGuiScale;
	v4 = (float)Mouse::getY() * Gui::InvGuiScale;
	if(fabsf(v3 - this->field_24) > 20.0 || fabsf(v4 - this->field_28) > 20.0) {
		v5 = this->field_7C;
		v6 = this->field_2C;
		if(v5 == v6 || (v5 = this->field_78) != 0 && v5 == v6) {
			v5->released((int32_t)v3, (int32_t)v4);
		}
		this->field_2C = 0;
	}
}
void MCOServerListItemElement::render(Minecraft* a2, int32_t a3, int32_t a4) {
	int32_t width; // r6
	ImageWithBackground* v9; // r3
	ImageWithBackground* v10; // r3
	int32_t v11; // r0
	int32_t v13; // r10
	Textures* texturesPtr; // r11
	int32_t v15; // r10
	ImageWithBackground* v16; // r0
	char_t v18[32]; // [sp+24h] [bp-4Ch] BYREF

	width = this->width;
	v9 = this->field_78;
	if(v9) {
		v9->posX = width + this->posX - v9->width;
		this->field_78->posY = this->posY;
		v10 = this->field_78;
		if(v10->visible) {
			width = this->width - v10->width;
		}
	}
	this->field_7C->posX = this->posX;
	this->field_7C->posY = this->posY;
	this->field_7C->width = width;
	this->field_7C->render(a2, a3, a4);
	if(this->field_7C->isPressed(a3, a4)) {
		v11 = 0xFFFFA0;
	} else {
		v11 = 0xFFFFFFFF;
	}
	a2->font->drawShadow(this->field_30.worldName, (float)(this->posX + 5), (float)(this->posY + 6), v11);
	a2->font->drawShadow(this->field_30.field_10, (float)(this->posX + 5), (float)(this->posY + 18), 0xFFBBBBBB);
	a2->font->width(this->field_30.gamemodeName);
	sprintf(v18, "%d/%d", this->field_30.field_20.size(), this->field_30.field_18);
	v13 = a2->font->width(v18);
	a2->font->drawShadow(v18, (float)(width + this->posX - 10 - v13), (float)(this->posY + 12), 0xFFFFFFFF);
	texturesPtr = a2->texturesPtr;
	if(this->field_30.field_C) {
		v15 = 9;
	} else {
		v15 = -9;
	}
	texturesPtr->loadAndBindTexture("gui/gui.png");
	this->blit(width + this->posX - 50, this->posY + 11, v15 + 191, 0, 9, 10, 9, 10);
	v16 = this->field_78;
	if(v16) {
		v16->render(a2, a3, a4);
	}
}
void MCOServerListItemElement::mouseClicked(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5) {
	float v9; // s16
	int32_t v10; // s15
	Button* v11; // r0
	float v12; // s17
	Button* v13; // r0

	v9 = (float)Mouse::getX() * Gui::InvGuiScale;
	v10 = Mouse::getY();
	v11 = (Button*)this->field_78;
	v12 = (float)v10 * Gui::InvGuiScale;
	if(v11 && v11->active && v11->clicked(a2, a3, a4)) {
		v13 = (Button*)this->field_78;
		this->field_24 = v9;
		this->field_28 = v12;
		goto LABEL_8;
	}

	if(this->field_7C->clicked(a2, a3, a4) && this->field_30.field_C) {
		this->field_24 = v9;
		this->field_28 = v12;
		v13 = (Button*)this->field_7C;
LABEL_8:
		this->field_2C = v13;
		return v13->setPressed();
	}
}
void MCOServerListItemElement::mouseReleased(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5) {
	Button* v6;	 // r5
	Button* v11; // r0
	Button* v12; // r0

	v6 = (Button*)this->field_78;
	if(v6 && v6->active && v6 == this->field_2C) {
		if(v6->clicked(a2, a3, a4)) {
			a2->setScreen(new ManageMCOServerScreen(this->field_30));
			return;
		}
		v11 = (Button*)this->field_78;
		goto LABEL_15;
	}
	v12 = (Button*)this->field_7C;
	if(v12 != this->field_2C) {
		return;
	}
	if(!v12->clicked(a2, a3, a4)) {
		v11 = (Button*)this->field_7C;
LABEL_15:
		v11->released(a3, a4);
		this->field_2C = 0;
		return;
	}
	if(this->field_30.field_C) {
		if(!this->field_90) {
			this->field_90 = 1;
			this->field_80(this->field_30, a2->platform()->isNetworkEnabled(1));
		}
	}
}
