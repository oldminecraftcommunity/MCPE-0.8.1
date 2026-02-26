#include <gui/buttons/Button.hpp>
#include <Minecraft.hpp>
#include <rendering/Textures.hpp>

Button::Button(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, const std::string& s) : GuiElement(1, 1, a3, a4, a5, a6){
	this->maybeTextOnButton = s;
	this->buttonID = a2;
	this->text = 0;
	this->pressed = 0;
	this->overridingScreenRendering = 0;
}
Button::Button(int32_t a2, int32_t a3, int32_t a4, const std::string& s) : GuiElement(1, 1, a3, a4, 200, 24){
	this->maybeTextOnButton = s;
	this->buttonID = a2;
	this->text = 0;
	this->pressed = 0;
	this->overridingScreenRendering = 0;
}

Button::Button(int32_t a2, const std::string& s) : GuiElement(1, 1, 0, 0, 200, 24){
	this->maybeTextOnButton = s;
	this->buttonID = a2;
	this->text = 0;
	this->pressed = 0;
	this->overridingScreenRendering = 0;
}

bool_t Button::hovered(struct Minecraft* mc, int32_t a3, int32_t a4){
	if(this->pressed) return this->isInside(a3, a4);
	return this->pressed;
}

bool_t Button::isInside(int32_t x, int32_t y){
	if(x < this->posX) return 0;
	return y >= this->posY && x < (this->posX+this->width) && y < (this->posY+this->height);
}

bool_t Button::isOverrideScreenRendering(){
	return this->overridingScreenRendering;
}
bool_t Button::isPressed(int32_t x, int32_t y){
	if(this->pressed) return this->isInside(x, y);
	return this->pressed;
}
void Button::setMsg(const std::string& s){
	this->maybeTextOnButton = s;
}
void Button::setOverrideScreenRendering(bool_t a2){
	this->overridingScreenRendering = a2;
}

Button::~Button(){}
void Button::render(struct Minecraft* mc, int32_t x, int32_t y){
	if(this->visible){
		this->renderBg(mc, x, y);
		this->renderFace(mc, x, y);
	}
}
bool_t Button::clicked(struct Minecraft* mc, int32_t x, int32_t y){
	if(!this->active) return 0; //this.active
	if(x < this->posX) return 0;
	return y >= this->posY && x < (this->posX+this->width) && y < (this->posY+this->height);
}
void Button::released(int32_t, int32_t){
	this->pressed = 0;
}
void Button::setPressed(){
	this->pressed = 1;
}
int32_t Button::getYImage(bool_t a2){
	if(this->active){
		if(a2) return 2;
		return 1;
	}
	return 0; //this->active
}
void Button::renderBg(struct Minecraft* mc, int32_t x, int32_t y){
	bool_t v10;
	int32_t v11;
	mc->texturesPtr->loadAndBindTexture("gui/gui.png");
	glColor4f(1, 1, 1, 1);
	if(this->text) v10 = 1;
	else v10 = this->hovered(mc, x, y);
	v11 = 20*this->getYImage(v10) + 46;
	this->blit(this->posX, this->posY, 0, v11, this->width/2, this->height, 0, 20);
	this->blit(this->width/2 + this->posX, this->posY, 200-this->width/2, v11, this->width/2, this->height, 0, 20);
}

void Button::renderFace(struct Minecraft* mc, int32_t x, int32_t y){
	if(this->active){
		if(this->hovered(mc, x, y) || this->text){
			this->drawCenteredString(mc->font, this->maybeTextOnButton, this->posX+this->width/2, this->posY+(this->height-8)/2, 0xFFFFA0);
		}else{
			this->drawCenteredString(mc->font, this->maybeTextOnButton, this->posX+this->width/2, this->posY+(this->height-8)/2, 0xE0E0E0);
		}
	}else{
		this->drawCenteredString(mc->font, this->maybeTextOnButton, this->posX+this->width/2, this->posY+(this->height-8)/2, 0xFFA0A0A0);
	}
}
