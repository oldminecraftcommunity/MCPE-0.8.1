#include <gui/elements/RolledSelectionListV.hpp>
#include <Minecraft.hpp>
#include <input/Mouse.hpp>
#include <math.h>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <utils.h>

RolledSelectionListV::RolledSelectionListV(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9)
	: GuiComponent() {
	this->field_10 = a9;
	this->field_8 = (float)a5;
	this->field_24 = -2;
	this->minecraft = a2;
	this->field_3C = -1;
	this->field_5C = -1;
	this->field_C = (float)a6;
	this->field_14 = a3;
	this->field_18 = a4;
	this->field_28 = 0.0;
	this->field_2C = 0.0;
	this->field_30 = 0.0;
	this->field_34 = 0.0;
	this->field_1C = (float)a7;
	this->field_38 = 0.0;
	this->renderSelection = 1;
	this->componentSelected = 0;
	this->field_42 = 1;
	this->field_43 = 1;
	this->field_44 = 1;
	this->field_20 = (float)a8;
	this->field_48 = 0;
	this->field_4C = 0;
	this->field_50 = 0;
	this->field_54 = 0;
	this->field_58 = 0;
	this->field_60 = 0.0;
	this->field_64 = 0.0;
}

void RolledSelectionListV::evaluate(int32_t a2, int32_t a3) {
	if(abs(this->field_3C - a3) > 9) { //abs32
		this->field_5C = -1;
		this->selectCancel();
	}
}
int32_t RolledSelectionListV::getItemAtYPositionRaw(int32_t a2) {
	int32_t v3; // r0
	int32_t v4; // r5

	v3 = a2 / this->field_10;
	v4 = v3;
	if(v3 < 0 || a2 < 0 || v3 >= this->getNumberOfItems()) {
		return -1;
	}
	return v4;
}
void RolledSelectionListV::renderDirtBackground() {
	float v2; // s17
	float v3; // s18
	float v5; // s19

	if(this->field_43) {
		v2 = this->field_1C;
	} else {
		v2 = 0.0;
	}
	if(this->field_44) {
		v3 = this->field_20;
	} else {
		v3 = (float)this->field_18;
	}
	this->minecraft->texturesPtr->loadAndBindTexture("gui/background.png");
	glColor4f(1.0, 1.0, 1.0, 1.0);
	v5 = (float)(int32_t)this->field_2C;
	Tesselator::instance.begin(4);
	Tesselator::instance.color(0x202020);
	Tesselator::instance.vertexUV(this->field_8, v3, 0.0, this->field_8 * 0.03125, (float)(v3 + v5) * 0.03125);
	Tesselator::instance.vertexUV(this->field_C, v3, 0.0, this->field_C * 0.03125, (float)(v3 + v5) * 0.03125);
	Tesselator::instance.vertexUV(this->field_C, v2, 0.0, this->field_C * 0.03125, (float)(v2 + v5) * 0.03125);
	Tesselator::instance.vertexUV(this->field_8, v2, 0.0, this->field_8 * 0.03125, (float)(v2 + v5) * 0.03125);
	Tesselator::instance.draw(1);
}
void RolledSelectionListV::setRenderHeader(bool_t a2, int32_t a3) {
	if(!a2) {
		a3 = 0;
	}
	this->field_54 = a2;
	this->field_50 = a3;
}

RolledSelectionListV::~RolledSelectionListV() {
}
int32_t RolledSelectionListV::getItemAtPosition(int32_t a2, int32_t a3) {
	if((float)a2 < this->field_8 || (float)a2 > this->field_C) {
		return -1;
	} else {
		return this->getItemAtYPositionRaw((int)(float)((float)((float)((float)((float)a3 - this->field_1C) - (float)this->field_50) + (float)(int32_t)this->field_2C) - 4.0));
	}
}
int32_t RolledSelectionListV::capYPosition() {
	int32_t v2; // s15
	int32_t r;	// r0
	float v4;	// s15

	v2 = this->getMaxPosition();
	r = 0;
	v4 = (float)v2 - (float)((float)(this->field_20 - this->field_1C) - 4.0);
	if(v4 < 0.0) {
		v4 = v4 * 0.5;
	}
	if(this->field_2C < 0.0) {
		this->field_2C = 0.0;
	}
	if(this->field_2C > v4) {
		this->field_2C = v4;
	}
	return r;
}
void RolledSelectionListV::tick() {
	float v2; // s15

	if(Mouse::isButtonDown(1)) {
		this->field_38 = this->field_60 - this->field_30;
	}
	v2 = this->field_2C - this->field_34;
	this->field_60 = this->field_30;
	this->field_30 = v2;
}
void RolledSelectionListV::render(int32_t a2, int32_t a3, float a4) {
	int32_t v8;		// r8
	float v9;		// s15
	int32_t v10;	// r3
	int32_t TimeMs; // r0
	int32_t v13;	// r1
	int32_t v15;	// r0
	int32_t v16;	// r0
	float v18;		// s14
	float v19;		// s12
	float v20;		// s15
	float v21;		// s13
	float v22;		// s15
	float v23;		// s15
	int32_t v26;	// r0
	int32_t v27;	// r0
	int32_t v28;	// r3
	int32_t v29;	// r6
	int32_t v30;	// r9
	int32_t v31;	// r5
	int32_t v32;	// r3
	float v33;		// s16
	float v34;		// s18

	this->field_48 = a2;
	this->field_4C = a3;
	this->renderBackground();
	v8 = this->getNumberOfItems();
	if(Mouse::isButtonDown(1)) {
		this->touched();
		v9 = (float)a3;
		if((float)a3 >= this->field_1C && v9 <= this->field_20) {
			v10 = this->field_24;
			if(v10 == -1) {
				TimeMs = getTimeMs();
				v13 = this->field_14 / 2;
				this->field_58 = TimeMs;
				v15 = this->getItemAtPosition(v13, a3);
				v16 = this->convertSelection(v15, a2, a3);
				this->field_5C = v16;
				this->selectStart(v16);
				this->field_3C = a3;
				this->field_64 = 10.0;
			} else if(v10 >= 0) {
				v18 = v9 - this->field_28;
				v19 = this->field_64;
				v20 = 0.0;
				v21 = fabsf(v18);
				if(v21 <= v19) {
					this->field_64 = v19 - v21;
				} else {
					this->field_64 = 0.0;
					if(v18 <= 0.0) {
						v20 = -0.0;
					}
					v20 = v18 - v20;
				}
				v22 = this->field_2C - v20;
				this->field_2C = v22;
				this->field_30 = v22;
			}
			this->field_24 = 0;
		}
	} else {
		if(this->field_24 >= 0) {
			v23 = this->field_38;
			if(v23 >= 0.0) {
				if(v23 >= 10.0) {
					v23 = 10.0;
				}
			} else if(v23 <= -10.0) {
				v23 = -10.0;
			}
			if(fabsf(v23) <= 2.0001) {
				this->field_34 = 0.0;
			} else {
				this->field_34 = v23;
			}
			if(fabsf(this->field_34) > 10.0) {
				this->selectCancel();
			} else {
				v26 = this->getItemAtPosition(this->field_14 / 2, a3);
				v27 = this->convertSelection(v26, a2, a3);
				if((float)a2 >= this->field_8 && (float)a2 <= this->field_C && v27 >= 0 && v27 == this->field_5C) {
					v28 = this->field_3C - a3;
					if(v28 < 0) {
						v28 = a3 - this->field_3C;
					}
					if(v28 <= 9) {
						this->selectItem(v27, 0);
					}
				}
			}
		}
		this->field_24 = -1;
		this->field_2C = this->getPos(a4);
	}
	this->field_28 = (float)a3;
	this->evaluate(a2, a3);
	this->capYPosition();
	v29 = this->field_14 / 2 - 40;
	v30 = (int32_t)(float)((float)(this->field_1C + 4.0) - (float)(int32_t)this->field_2C);
	if(this->field_42) {
		this->renderDirtBackground();
	}
	if(!this->getNumberOfItems()) {
		this->field_2C = 0.0;
	}
	if(this->field_54) {
		this->renderHeader(this->field_14 / 2 - 40, (int32_t)(float)((float)(this->field_1C + 4.0) - (float)(int32_t)this->field_2C), Tesselator::instance);
	}
	v31 = 0;
	this->onPreRender();
	while(v31 < v8) {
		v32 = this->field_10;
		v33 = (float)(v30 + v32 * v31 + this->field_50);
		if(v33 <= this->field_20) {
			v34 = (float)v32 - 4.0;
			if((float)(v33 + v34) >= this->field_1C) {
				if(this->renderSelection) {
					this->isSelectedItem(v31);
				}
				this->renderItem(v31, v29, (int32_t)v33, (int32_t)v34, Tesselator::instance);
			}
		}
		++v31;
	}
	this->onPostRender();
	glDisable(0xB71u);
	if(this->field_43) {
		this->renderHoleBackground(0.0, this->field_1C, 255, 255);
	}
	if(this->field_44) {
		this->renderHoleBackground(this->field_20, (float)this->field_18, 255, 255);
	}
	this->renderForeground();
	glEnable(0xB71u);
}
void RolledSelectionListV::renderHoleBackground(float a2, float a3, int32_t a4, int32_t a5) {
	this->minecraft->texturesPtr->loadAndBindTexture("gui/background.png");
	glColor4f(1.0, 1.0, 1.0, 1.0);
	Tesselator::instance.begin(4);
	Tesselator::instance.color(0x505050, a5);
	Tesselator::instance.vertexUV(0.0, a3, 0.0, 0.0, a3 * 0.03125);
	Tesselator::instance.vertexUV((float)this->field_14, a3, 0.0, (float)this->field_14 * 0.03125, a3 * 0.03125);
	Tesselator::instance.color(0x505050, a4);
	Tesselator::instance.vertexUV((float)this->field_14, a2, 0.0, (float)this->field_14 * 0.03125, a2 * 0.03125);
	Tesselator::instance.vertexUV(0.0, a2, 0.0, 0.0, a2 * 0.03125);
	Tesselator::instance.draw(1);
}
void RolledSelectionListV::setRenderSelection(bool_t a2) {
	this->renderSelection = a2;
}
void RolledSelectionListV::setComponentSelected(bool_t a2) {
	this->componentSelected = a2;
}
void RolledSelectionListV::selectStart(int32_t) {
}
void RolledSelectionListV::selectCancel() {
}
int32_t RolledSelectionListV::getMaxPosition() {
	return this->field_50 + this->field_10 * this->getNumberOfItems();
}
float RolledSelectionListV::getPos(float a2) {
	return this->field_30 - (float)(a2 * this->field_34);
}
void RolledSelectionListV::touched() {
}
void RolledSelectionListV::renderHeader(int32_t, int32_t, Tesselator&) {
}
void RolledSelectionListV::renderForeground() {
}
void RolledSelectionListV::renderDecoration(int32_t, int32_t) {
}
void RolledSelectionListV::clickedHeader(int32_t, int32_t) {
}
int32_t RolledSelectionListV::convertSelection(int32_t a2, int32_t a3, int32_t) {
	return a2;
}
void RolledSelectionListV::onPreRender() {
}
void RolledSelectionListV::onPostRender() {
}
