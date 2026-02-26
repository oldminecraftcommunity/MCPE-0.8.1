#include <gui/buttons/CraftButton.hpp>
#include <gui/NinePatchLayer.hpp>
#include <gui/NinePatchFactory.hpp>
#include <rendering/Tesselator.hpp>

CraftButton::CraftButton(int32_t a2)
	: ImageButton(a2, "") {
	this->field_70 = this->field_74 = 0;
	this->field_78 = 0;
}
IntRectangle CraftButton::getItemPos(int32_t) {
	return {0, 0, 1, 1};
}
void CraftButton::init(Textures* a2) {
	NinePatchFactory a1(a2, "gui/spritesheet.png");
	this->field_70 = a1.createSymmetrical({112, 0, 8, 67}, 2, 2, 32, 32);
	this->field_74 = a1.createSymmetrical({120, 0, 8, 67}, 2, 2, 32, 32);
}
void CraftButton::setSize(float a2, float a3) {
	this->width = (int32_t)a2;
	this->height = (int32_t)a3;
	if(this->field_70) {
		if(this->field_74) {
			this->field_70->setSize(a2, a3);
			this->field_74->setSize(a2, a3);
		}
	}
}

CraftButton::~CraftButton() {
	delete this->field_70;
	delete this->field_74;
}
void CraftButton::renderBg(Minecraft* mc, int32_t x, int32_t y) {
	NinePatchLayer* v5; // r0
	int32_t v6; // r7
	int32_t v7; // r12
	int32_t posX; // s14
	int32_t posY; // s15

	v5 = this->field_70;
	if(v5) {
		if(this->field_74) {
			if(this->active && this->pressed && (v6 = this->posX, x >= v6) && (v7 = this->posY, y >= v7) && x < v6 + this->width && y < v7 + this->height || this->text) {
				posX = this->posX;
				posY = this->posY;
				v5 = this->field_74;
			} else {
				posX = this->posX;
				posY = this->posY;
			}
			v5->draw(Tesselator::instance, (float)posX, (float)posY);
		}
	}
}
