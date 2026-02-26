#include <gui/elements/AvailableGamesList.hpp>
#include <Minecraft.hpp>
#include <network/PingedCompatibleServer.hpp>

AvailableGamesList::AvailableGamesList(Minecraft* mc, int32_t w, int32_t h) : ScrolledSelectionList(mc, w, h, 24, w-30, 28){

}
AvailableGamesList::~AvailableGamesList() {
}
int32_t AvailableGamesList::getNumberOfItems() {
	return this->servers.size();
}
void AvailableGamesList::selectItem(int32_t a2, bool_t a3) {
	this->selectedItem = a2;
}
bool_t AvailableGamesList::isSelectedItem(int32_t a2) {
	return a2 == this->selectedItem;
}
void AvailableGamesList::renderItem(int32_t a2, int32_t a3, int32_t a4, int32_t a5, Tesselator& a6) {
	PingedCompatibleServer* v8; // r8
	int32_t v10;				// r9
	Font* font;					// r10
	Font* v12;					// r9

	v8 = &this->servers[a2];
	if(v8->field_1C) {
		v10 = 0xFF00B0;
	} else {
		v10 = 0xFFFFA0;
	}
	font = this->minecraft->font;
	this->drawString(font, v8->field_0.C_String(), a3, a4 + 2, v10);
	v12 = this->minecraft->font;
	this->drawString(v12, v8->field_4.ToString(0, '|'), a3, a4 + 16, 0xFFFFA0);
}
void AvailableGamesList::renderBackground() {
}
