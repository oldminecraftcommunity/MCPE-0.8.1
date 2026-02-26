#include <gui/buttons/CategoryButton.hpp>
#include <rendering/Tesselator.hpp>
CategoryButton::CategoryButton(int32_t id, NinePatchLayer* f74, NinePatchLayer* f78, Button** f70) : CategoryButton("", id, f74, f78, f70){

}

CategoryButton::CategoryButton(std::string ss, int32_t id, NinePatchLayer* f74, NinePatchLayer* f78, Button** f70) : ImageButton(id, ss){
	this->field_74 = f74;
	this->field_78 = f78;
	this->field_70 = f70;
}
CategoryButton::~CategoryButton() {
}
void CategoryButton::renderBg(struct Minecraft* mc, int32_t a3, int32_t a4) {
	int32_t v4, v5;
	int32_t posX, posY;
	NinePatchLayer* v8;
	if(this->active && this->pressed && (v4 = this->posX, a3 >= v4) && (v5 = this->posY, a4 >= v5) && a3 < v4 + this->width && a4 < v5 + this->height || *this->field_70 == this) {
		posX = this->posX;
		posY = this->posY;
		v8 = this->field_78;
	} else {
		posX = this->posX;
		posY = this->posY;
		v8 = this->field_74;
	}
	v8->draw(Tesselator::instance, posX, posY);
}
bool_t CategoryButton::isSecondImage(bool_t) {
	return 0;
}
