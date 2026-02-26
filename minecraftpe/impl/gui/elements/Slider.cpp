#include <gui/elements/Slider.hpp>
#include <input/Mouse.hpp>
#include <Minecraft.hpp>
#include <rendering/Textures.hpp>
#include <algorithm>
#include <gui/Screen.hpp>

Slider::Slider(Minecraft* a2, const Options::Option* a3, float a4, float a5)
	: GuiElement(1, 1, 0, 0, 24, 24) {
	this->minValue = a4;
	this->isStepSliderMaybe = 0;
	this->maxValue = a5;
	this->field_34 = 0;
	this->field_44 = 0;
	this->option = a3;
	if(a3) {
		this->progress = (float)(a2->options.getProgressValue(a3) - a4) / (float)(a5 - a4);
	}
}
Slider::Slider(Minecraft* a2, const Options::Option* a3, const std::vector<int32_t>& a4)
	: GuiElement(1, 1, 0, 0, 24, 24) {
	this->isStepSliderMaybe = 1;
	this->field_28 = a4;
	this->field_34 = 0;
	this->field_3C = 0;
	this->field_40 = 0;
	this->progress = 0.0;
	this->minValue = 0.0;
	this->maxValue = 1.0;
	this->option = a3;
	this->field_44 = this->field_28.size();
	if(a3) {
		this->field_3C = a2->options.getIntValue(a3);
		auto&& p = std::find(this->field_28.begin(), this->field_28.end(), this->field_3C);
		if(p != this->field_28.end()) {
			this->field_40 = p - this->field_28.begin();
		}
		this->progress = (float)this->field_40 / (float)(this->field_44 - 1);
	}
}
Slider::~Slider() {
}
void Slider::tick(Minecraft* a2){
	float v4; // s15
	int32_t v6; // [sp+0h] [bp-18h] OVERLAPPED BYREF
	int32_t v7; // [sp+4h] [bp-14h] BYREF

	if ( a2->currentScreen )
	{
		v6 = Mouse::getX();
		v7 = Mouse::getY();
		a2->currentScreen->toGUICoordinate(v6, v7);
		if ( this->field_34 )
		{
			v4 = (float)(v6 - this->posX) / (float)this->width;
			if ( v4 > 1.0 )
			{
				v4 = 1.0;
			}
			else if ( v4 <= 0.0 )
			{
				v4 = 0.0;
			}
			this->progress = v4;
			this->setOption(a2);
		}
	}
}
void Slider::render(Minecraft* a2, int32_t a3, int32_t a4) {
	float v6;	  // s15
	int32_t posX; // r5
	int32_t v8;	  // r6
	int32_t posY; // r9
	int32_t v10;  // s16
	int32_t v12;  // r10
	int32_t v13;  // r5
	int32_t v14;  // r8
	int32_t v15;  // r9
	int32_t v16;  // r11
	int32_t v17;  // [sp+1Ch] [bp-3Ch] BYREF
	int32_t v18;  // [sp+20h] [bp-38h] BYREF

	if(a2->currentScreen) {
		v17 = Mouse::getX();
		v18 = Mouse::getY();
		a2->currentScreen->toGUICoordinate(v17, v18);
		if(this->field_34) {
			v6 = (float)(v17 - this->posX) / (float)this->width;
			if(v6 > 1.0) {
				v6 = 1.0;
			} else if(v6 <= 0.0) {
				v6 = 0.0;
			}
			this->progress = v6;
		}
	}
	posX = this->posX;
	v8 = posX + 5;
	posY = this->posY;
	v10 = this->width - 10;
	this->fill(posX + 5, posY + 7, posX + this->width - 5, posY + 10, -9408400);
	if(this->isStepSliderMaybe == 1) {
		v12 = posY + 5;
		v13 = posX + 4;
		v14 = 0;
		v15 = posY + 12;
		v16 = v10 / (this->field_44 - 1);
		while(this->field_44 > v14) {
			++v14;
			this->fill(v13, v12, v13 + 4, v15, -7303024);
			v13 += v16;
		}
	}
	a2->texturesPtr->loadAndBindTexture("gui/touchgui.png");
	this->blit(v8 + (int32_t)(float)((float)v10 * this->progress) - 5, this->posY, 225, 125, 11, 17, 11, 17);
}
void Slider::mouseClicked(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5) {
	if(this->pointInside(a3, a4)) {
		this->field_34 = 1;
	}
}
void Slider::mouseReleased(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5) {
	int32_t v5;		// r2
	float progress; // s13
	int32_t v7;		// r2
	float v9;		// s14
	float v10;		// s15
	int32_t v11;	// r3
	int32_t v12;	// s12

	if(this->field_34 && this->isStepSliderMaybe == 1) {
		v5 = this->field_44;
		progress = this->progress;
		this->field_34 = 0;
		v7 = v5 - 1;
		v9 = (float)v7;
		v10 = (float)((float)v7 * progress) + 0.5;
		v11 = (int32_t)v10;
		if(v10 < (float)(int32_t)v10) {
			--v11;
		}
		this->field_40 = v11;
		if(v11 < v7) {
			v7 = v11;
		}
		v12 = v11;
		this->field_3C = this->field_28[v7];
		this->progress = (float)v12 / v9;
		this->setOption(a2);
	} else {
		this->field_34 = 0;
	}
}
void Slider::setOption(Minecraft* a2) {
	Options* p_options; // r5
	int32_t ivalue;		// r0
	int32_t v7;			// r2

	if(this->option) {
		p_options = &a2->options;
		if(this->isStepSliderMaybe == 1) {
			ivalue = p_options->getIntValue(this->option);
			v7 = this->field_3C;
			if(ivalue != v7) {
				p_options->set(this->option, v7);
			}
		} else if(p_options->getProgressValue(this->option) != (float)(this->minValue + (float)((float)(this->maxValue - this->minValue) * this->progress))) {
			p_options->set(this->option, this->minValue + (float)((float)(this->maxValue - this->minValue) * this->progress));
		}
	}
}
