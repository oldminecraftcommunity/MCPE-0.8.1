#include <gui/elements/Touch_AvailableGamesList.hpp>
#include <Minecraft.hpp>
#include <input/MouseDevice.hpp>
#include <input/Multitouch.hpp>
#include <network/PingedCompatibleServer.hpp>
#include <rendering/Textures.hpp>

Touch::AvailableGamesList::AvailableGamesList(Minecraft* mc, int32_t w, int32_t h)
	: RolledSelectionListV(mc, w, h, 0, w, 24, h, 34) {
	this->field_6C = -1;
	this->selectedItem = -1;
}
Touch::AvailableGamesList::~AvailableGamesList() {
}
int32_t Touch::AvailableGamesList::getNumberOfItems() {
	return this->servers.size();
}
void Touch::AvailableGamesList::selectStart(int32_t a2) {
	this->field_6C = a2;
}
void Touch::AvailableGamesList::selectCancel() {
	this->field_6C = -1;
}
void Touch::AvailableGamesList::selectItem(int32_t a2, bool_t) {
	this->selectedItem = a2;
}
bool_t Touch::AvailableGamesList::isSelectedItem(int32_t a2) {
	return a2 == this->selectedItem;
}
void Touch::AvailableGamesList::renderItem(int32_t a2, int32_t a3, int32_t a4, int32_t a5, Tesselator& a6) {
	int32_t v9;			  // r6
	int32_t isButtonDown; // r0
	int32_t v12;		  // r9
	int32_t v13;		  // r8
	int32_t v14;		  // r11
	int32_t v15;		  // r6
	int32_t v16;		  // r8

	if(this->field_6C == a2) {
		v9 = 0;
		while(1) {
			isButtonDown = Multitouch::_pointers[v9].isButtonDown(1);
			if(isButtonDown) {
				break;
			}
			if(++v9 == 12) {
				while(!Multitouch::_wasReleased[isButtonDown]) {
					if(++isButtonDown == 12) {
						goto LABEL_7;
					}
				}
				break;
			}
		}
		this->fill((int32_t)this->field_8, a4, (int32_t)this->field_C, a4 + a5, 0x809E684F);
	}
LABEL_7:
	v12 = a2;
	v13 = (int)this->field_8;
	if(this->servers[v12].field_1C) {
		v14 = 0x6090A0;
	} else {
		v14 = 0xFFFFB0;
	}
	v15 = v13 + 24;
	if(this->servers[v12].field_1C) {
		v16 = v13 + 74;
		glColor4f(1.0, 1.0, 1.0, 1.0);
		this->minecraft->texturesPtr->loadAndBindTexture("gui/badge/minecon140.png");
		this->blit(v15, a4 + 6, 0, 0, 37, 8, 140, 240);
	} else {
		v16 = v13 + 24;
	}
	this->drawString(this->minecraft->font, this->servers[v12].field_0.C_String(), v16, a4 + 6, v14);
	this->drawString(this->minecraft->font, this->servers[v12].field_4.ToString(0, '|'), v15, a4 + 18, 16777120);
}
void Touch::AvailableGamesList::renderBackground() {
}
