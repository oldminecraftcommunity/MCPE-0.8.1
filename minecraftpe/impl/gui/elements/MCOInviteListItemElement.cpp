#include <gui/elements/MCOInviteListItemElement.hpp>
#include <Minecraft.hpp>
#include <gui/buttons/ImageButton.hpp>
#include <gui/screens/ManageMCOServerScreen.hpp>
#include <rendering/Font.hpp>

MCOInviteListItemElement::MCOInviteListItemElement(std::string a2, ManageMCOServerScreen& a3, void (ManageMCOServerScreen::*a4)(const std::string&))
	: GuiElementContainer(0, 1, 0, 0, 24, 24) {
	int32_t a5; //???
	this->friendSearchCompleted = 0;
	this->field_3C = a2;
	this->field_40 = 0;
	this->field_44 = 0;
	this->field_48 = &a3;
	this->field_4C = a4;
	this->field_50 = a5;
	ImageDef v10;
	v10.field_4 = 0;
	v10.field_8 = 0;
	v10.field_0 = "";
	v10.field_24 = 1;
	v10.width = 16.0;
	v10.height = 16.0;
	v10.field_14 = 182;
	v10.field_18 = 10;
	v10.field_1C = 11;
	v10.field_20 = 11;
	v10.field_0 = "gui/gui.png";
	v10.width = 11.0;
	v10.height = 11.0;
	this->field_40 = new ImageButton(0, "");
	this->field_40->setImageDef(v10, 1);
	this->field_40->setActiveAndVisibility(0, 0);
} //TODO might have aother parameter?
void MCOInviteListItemElement::onFriendSearchCompleted(const std::string& a2) {
	if(!this->friendSearchCompleted) {
		this->field_3C = a2;
		this->field_40->setActiveAndVisibility(1, 1);
		this->friendSearchCompleted = 1;
	}
}

MCOInviteListItemElement::~MCOInviteListItemElement() {
	if(this->field_40) {
		delete this->field_40;
		this->field_40 = 0;
	}
}
void MCOInviteListItemElement::render(Minecraft* a2, int32_t a3, int32_t a4) {
	int32_t friendSearchCompleted; // r1

	this->fill((float)this->posX, (float)this->posY, (float)(this->posX + this->width), (float)(this->posY + 1), 0xFFCFC6BE);
	this->fill((float)this->posX, (float)(this->posY + 1), (float)(this->posX + this->width), (float)(this->posY + this->height - 1), 0xFF948681);
	this->fill((float)this->posX, (float)(this->posY + this->height - 1), (float)(this->posX + this->width), (float)(this->posY + this->height), 0xFF312D31);
	friendSearchCompleted = this->friendSearchCompleted;
	if(friendSearchCompleted == 1) {
		a2->font->drawShadow(this->field_3C, (float)this->posX + 5.0, (float)this->posY + (float)((this->height - 10) / 2), 0xFFFFFFFF);
	} else if(!friendSearchCompleted) {
		a2->font->draw("searching...", (float)this->posX + 5.0, (float)this->posY + (float)((this->height - 10) / 2), 0xFFD4C521);
	}
	this->field_40->render(a2, a3, a4);
}
void MCOInviteListItemElement::setupPositions() {
	this->field_40->posX = this->posX + this->width - this->field_40->width - 5;
	this->field_40->posY = this->posY + (this->height - this->field_40->height) / 2;
}
void MCOInviteListItemElement::mouseClicked(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5) {
	Button* v8;		 // r0
	ImageButton* v9; // r0

	if(a5 == 1) {
		v8 = (Button*)this->field_40;
		if(v8 && v8->clicked(a2, a3, a4)) {
			v9 = this->field_40;
			this->field_44 = v9;
			v9->setPressed();
		} else {
			this->field_40->released(a3, a4);
			this->field_44 = 0;
		}
	}
}
void MCOInviteListItemElement::mouseReleased(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5) {
	Button* v8; // r0

	if(a5 == 1) {
		v8 = (Button*)this->field_40;
		if(v8) {
			if(v8 == (Button*)this->field_44) {
				if(v8->clicked(a2, a3, a4)) {
					this->field_48->onFriendItemRemoved(this->field_3C);
				} else {
					this->field_40->released(a3, a4);
					this->field_44 = 0;
				}
			}
		}
	}
}
