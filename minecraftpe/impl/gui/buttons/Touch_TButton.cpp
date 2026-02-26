#include <gui/buttons/Touch_TButton.hpp>
#include <Minecraft.hpp>
#include <gui/NinePatchFactory.hpp>
#include <gui/NinePatchLayer.hpp>
#include <util/IntRectangle.hpp>
#include <cpputils.hpp>
#include <rendering/Tesselator.hpp>

Touch::TButton::TButton(int32_t id, const std::string& s, Minecraft* mc) : Button(id, s){
	this->width = 66;
	this->height = 26;
	this->field_2C = 0;
	this->field_30 = 0;
	if(mc) this->init(mc);
}

Touch::TButton::TButton(int32_t id, int32_t x, int32_t y, const std::string& s, Minecraft* mc) : Button(id, x, y, s){
	this->width = 66;
	this->height = 26;
	this->field_2C = 0;
	this->field_30 = 0;
	if(mc) this->init(mc);
}


Touch::TButton::TButton(int32_t id, int32_t x, int32_t y, int32_t w, int32_t h, const std::string& s, Minecraft* mc) : Button(id, x, y, w, h, s){
	this->field_2C = 0;
	this->field_30 = 0;
	if(mc) this->init(mc);
}

void Touch::TButton::init(struct Minecraft* mc){
	NinePatchFactory npf(mc->texturesPtr, "gui/spritesheet.png");
	IntRectangle r;
	r.minY = 32;
	r.minX = 8;
	r.width = 8;
	r.height = 8;
	this->field_2C = npf.createSymmetrical(r, 2, 2, this->width, this->height);
	r.minX = 0;
	r.minY = 32;
	r.width = 8;
	r.height = 8;
	this->field_30 = npf.createSymmetrical(r, 2, 2, this->width, this->height);
}
void Touch::TButton::init(struct Minecraft* mc, const std::string& s, const struct IntRectangle& r1, const struct IntRectangle& r2, int32_t a, int32_t b, int32_t c, int32_t d){
	this->width = c;
	this->height = d;
	NinePatchFactory npf(mc->texturesPtr, s);
	this->field_2C = npf.createSymmetrical(r1, a, b, c, d);
	this->field_30 = npf.createSymmetrical(r2, a, b, c, d);

}
Touch::TButton::~TButton(){
	safeRemove(this->field_2C);
	safeRemove(this->field_30);
}
void Touch::TButton::renderBg(struct Minecraft* mc, int32_t x, int32_t y){
	NinePatchLayer* layer;
	float posX;
	int32_t posY;

	this->field_2C->setSize(this->width, this->height);
	this->field_30->setSize(this->width, this->height);


	if(this->active && this->pressed && x >= this->posX && y >= this->posY && x < (this->posX+this->width) && y < (this->posY+this->height)){
		layer = this->field_30;
		posX = this->posX;
		posY = this->posY;
	}else{
		layer = this->field_2C;
		posY = this->posY;
		posX = this->posX;
	}

	layer->draw(Tesselator::instance, posX, posY);
}
