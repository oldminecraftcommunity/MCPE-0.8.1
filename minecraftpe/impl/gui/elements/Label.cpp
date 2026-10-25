#include <gui/elements/Label.hpp>
#include <Minecraft.hpp>
#include <rendering/Font.hpp>

Label::Label(std::string a2, Minecraft* a3, int32_t a4, int32_t a5, int32_t a6, int32_t width, bool_t a8)
	: GuiElement(1, 1, 0, 0, 24, 24), text(a2) {
	this->minecraft = a3;
	this->widthBase = a5;
	this->textColor = a4;
	this->field_3A = 0;
	this->heightBase = a6;
	this->field_38 = width > 0;
	this->width = width;
	this->textShadow = a8;
	this->setupPositions();
}

void Label::render(Minecraft* mc, int32_t x, int32_t y) {
	GuiElement::render(mc, x, y);
	mc->font->drawWordWrap(this->text, this->widthBase + this->posX, this->posY + this->heightBase, ((float)this->width - this->widthBase) + 1.0f, this->textColor, this->textShadow, this->field_3A);
}
void Label::setupPositions() {
	int32_t widthBase;	// r5
	int32_t heightBase; // r5

	if(!this->field_38) {
		widthBase = this->widthBase;
		this->width = widthBase + this->minecraft->font->width(this->text);
	}
	heightBase = this->heightBase;
	this->height = heightBase + this->minecraft->font->height(this->text, this->width - this->widthBase);
}
std::string Label::getText() const{
	return this->text;
}
void Label::setText(std::string a2) {
	this->text = a2;
	this->setupPositions();
}
void Label::setWidth(int32_t a2) {
	this->width = a2;
	this->field_38 = 1;
}
