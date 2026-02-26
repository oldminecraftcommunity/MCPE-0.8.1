#include <gui/buttons/OptionButton.hpp>
#include <math.h>
#include <Minecraft.hpp>

OptionButton::OptionButton(const Options::Option* a2)
	: ImageButton(9999999, "") {
	this->option = a2;
	this->isFloat = 0;
}
OptionButton::OptionButton(const Options::Option* a2, float a3, float a4)
	: ImageButton(9999999, "") {
	this->option = a2;
	this->isFloat = 1;
	this->minValue = a3;
	this->maxValue = a4;
}
OptionButton::OptionButton(bool_t a2)
	: ImageButton(9999999, "") {
	this->boolValue = a2;
	this->option = 0;
	this->isFloat = 0;
}

bool_t OptionButton::isSet(Options* a2) {
	if(a2 && this->option != 0) {
		return a2->getBooleanValue(this->option);
	}
	return this->boolValue;
}
void OptionButton::toggle(Options* a2) {
	if(this->option) {
		if(this->isFloat) {
			float v = this->minValue;
			if(fabsf(this->curValue - this->minValue) < 0.01) {
				v = this->maxValue;
			}
			a2->set(this->option, v);
		} else {
			a2->toggle(this->option, 1);
		}
	}
	this->updateImage(a2);
}
void OptionButton::updateImage(Options* a2) {
	float pv; // r0
	float minValue; // s14
	bool_t v8; // r3

	if(this->isFloat) {
		pv = a2->getProgressValue(this->option);
		minValue = this->minValue;
		this->curValue = pv;
		v8 = fabsf(pv - minValue) < 0.01;
	} else {
		if(this->option) {
			this->boolValue = a2->getBooleanValue(this->option);
			return;
		}
		v8 = !this->boolValue;
	}
	this->boolValue = v8;
}

OptionButton::~OptionButton() {
}
void OptionButton::mouseClicked(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5) {
	if(a5 == 1 && this->clicked(a2, a3, a4)) {
		this->toggle(&a2->options);
	}
}
bool_t OptionButton::isSecondImage(bool_t) {
	return this->boolValue;
}
