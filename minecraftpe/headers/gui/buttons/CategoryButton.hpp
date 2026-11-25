#pragma once
#include <gui/buttons/ImageButton.hpp>
#include <gui/NinePatchLayer.hpp>
#include <rendering/Tesselator.hpp>

struct CategoryButton: ImageButton
{
	Button** field_70;
	NinePatchLayer *field_74, *field_78;

	CategoryButton(int32_t id, NinePatchLayer* f74, NinePatchLayer* f78, Button** f70) :
			ImageButton(id, "") {
		this->field_74 = f74;
		this->field_78 = f78;
		this->field_70 = f70;
	}
	CategoryButton(std::string ss, int32_t id, NinePatchLayer* f74, NinePatchLayer* f78, Button** f70) :
			ImageButton(id, ss) {
		this->field_74 = f74;
		this->field_78 = f78;
		this->field_70 = f70;
	}
	virtual ~CategoryButton() {
	}
	virtual void renderBg(struct Minecraft* mc, int32_t mx, int32_t my) {
		if ((this->active && this->pressed && mx >= this->posX && my >= this->posY && mx < (this->posX + this->width) && my < (this->posY + this->height)) || *this->field_70 == this) {
			this->field_78->draw(Tesselator::instance, this->posX, this->posY);
		} else {
			this->field_74->draw(Tesselator::instance, this->posX, this->posY);
		}
	}
	virtual bool_t isSecondImage(bool_t) {
		return 0;
	}
};
