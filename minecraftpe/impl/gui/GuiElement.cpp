#include <gui/GuiElement.hpp>
#include <cpputils.hpp>
#include <gui/NinePatchLayer.hpp>
#include <rendering/Tesselator.hpp>
#include <Minecraft.hpp>
#include <util/IntRectangle.hpp>
#include <gui/NinePatchFactory.hpp>

GuiElement::GuiElement(bool_t a2, bool_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7){
	this->active = a2;
	this->posY = a5;
	this->visible = a3;
	this->posX = a4;
	this->width = a6;
	this->height = a7;
	this->color = 0;
	this->field_1C = 0;
}

bool_t GuiElement::backPressed(struct Minecraft*, bool_t){
	return 0;
}
void GuiElement::clearBackground(){
	safeRemove(this->field_1C);
	this->color = 0;
}
void GuiElement::focusuedMouseClicked(struct Minecraft*, int32_t, int32_t, int32_t){}
void GuiElement::focusuedMouseReleased(struct Minecraft*, int32_t, int32_t, int32_t){}
void GuiElement::keyPressed(struct Minecraft*, int32_t){}
void GuiElement::keyboardNewChar(struct Minecraft*, std::string, bool_t){}
void GuiElement::mouseClicked(struct Minecraft*, int32_t, int32_t, int32_t){}
void GuiElement::mouseReleased(struct Minecraft*, int32_t, int32_t, int32_t){}
bool_t GuiElement::pointInside(int32_t x, int32_t y){
	if(x < this->posX) return 0;
	if(x > this->posX + this->width) return 0;
	return y >= this->posY && y < (this->posY + this->height);
}

void GuiElement::render(struct Minecraft*, int32_t, int32_t){
	if(this->color){
		this->fill(this->posX, this->posY, this->posX+this->width, this->posY+this->height, this->color);
	}else{
		if(this->field_1C){
			this->field_1C->setSize(this->width, this->height);
			this->field_1C->draw(Tesselator::instance, this->posX, this->posY);
		}
	}
}

void GuiElement::setActiveAndVisibility(bool_t b){
	this->active = b;
	this->visible = b;
}
void GuiElement::setActiveAndVisibility(bool_t act, bool_t vis){
	this->active = act;
	this->visible = vis;
}
void GuiElement::setBackground(Minecraft* mc, const std::string& path, const IntRectangle& rect, int32_t a5, int32_t a6){
	safeRemove(this->field_1C);
	this->color = 0;
	NinePatchFactory factory(mc->texturesPtr, path);
	this->field_1C = factory.createSymmetrical(rect, a5, a6, this->width, this->height);
}

void GuiElement::setBackground(uint32_t color){
	safeRemove(this->field_1C);
	this->color = color;
}

void GuiElement::setTextboxText(const std::string&){}
void GuiElement::setVisible(bool_t a2){
	this->visible = a2;
}
void GuiElement::setupPositions(){}
bool_t GuiElement::suppressOtherGUI(){
	return 0;
}
void GuiElement::tick(Minecraft*){}
void GuiElement::topRender(Minecraft*, int32_t, int32_t){}
GuiElement::~GuiElement(){
	safeRemove(this->field_1C);
}
