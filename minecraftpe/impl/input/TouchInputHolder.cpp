#include <input/TouchInputHolder.hpp>
#include <Config.hpp>
#include <Minecraft.hpp>
#include <input/Multitouch.hpp>

TouchInputHolder::TouchInputHolder(Minecraft* mc)
	: moveInput(mc, &mc->options)
	, turnInput(2, mc->field_1C, mc->field_20, 200, 1, this, mc) {
	this->mouseX = 0;
	this->mouseY = 0;
	this->field_C = 0;
	this->onConfigChanged(createConfig(mc));
}

TouchInputHolder::~TouchInputHolder() {
}
void TouchInputHolder::onConfigChanged(const Config& a2) {
	this->moveInput.onConfigChanged(a2);
	this->turnInput.field_4C = *this->moveInput.getRectangleArea();
	this->turnInput.field_7C = this->minecraft->gui.getRectangleArea(this->minecraft->options.leftHanded ? 1 : -1);
	if(!a2.options->useJoypad) {
		this->turnInput.field_108 = 1.0;
	} else {
		this->turnInput.field_108 = 1.8;
	}
	this->turnInput.onConfigChanged(a2);
}
void TouchInputHolder::render(float z2) {
	this->turnInput.fill((int32_t)(float)(Gui::InvGuiScale * this->turnInput.field_64.minX), (int32_t)(float)(Gui::InvGuiScale * this->turnInput.field_64.minY), (int32_t)(float)(Gui::InvGuiScale * this->turnInput.field_64.maxX), (int32_t)(float)(Gui::InvGuiScale * this->turnInput.field_64.maxY), 0x40000000);
}
bool_t TouchInputHolder::allowPicking() {
	int v2;					// r5
	IncludeExcludeArea* v3; // r11
	int v4;					// r4
	int v5;					// r0
	int v6;					// s15
	float v7;				// s17
	int v8;					// r0
	float v9;				// r1
	int v10;				// s15
	int v12;				// [sp+4h] [bp-34h]

	v2 = 0;
	v3 = &this->turnInput.field_D0;
	v12 = Multitouch::_activePointerCount;
	while(v2 < v12) {
		v4 = Multitouch::_activePointerList[v2];
		if(v4 < 0) {
			v5 = Multitouch::_activePointerList[v2];
		} else if(v4 >= 11) {
			v5 = 11;
		} else {
			v5 = Multitouch::_activePointerList[v2];
		}
		v6 = Multitouch::_pointers[v5].getX();
		v7 = (float)v6;
		if(v4 >= 0 && v4 >= 11) {
			v4 = 11;
		}
		v8 = Multitouch::_pointers[v4].getY();
		v9 = (float)v6;
		v10 = v8;
		if(v3->isInside(v9, (float)v8)) {
			this->mouseX = v7;
			this->mouseY = (float)v10;
			return 1;
		}
		++v2;
	}
	return 0;
}
IMoveInput* TouchInputHolder::getMoveInput() {
	return &this->moveInput;
}
ITurnInput* TouchInputHolder::getTurnInput() {
	return &this->turnInput;
}
IBuildInput* TouchInputHolder::getBuildInput() {
	return &this->turnInput;
}
