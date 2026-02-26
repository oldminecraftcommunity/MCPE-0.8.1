#include <gui/elements/ScrolledSelectionList.hpp>
#include <Minecraft.hpp>
#include <input/Mouse.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <rendering/states/DisableState.hpp>
#include <utils.h>

ScrolledSelectionList::ScrolledSelectionList(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7)
	: GuiComponent() {
	this->field_14 = a3;
	this->field_8 = (float)a5;
	this->field_20 = 0.0;
	this->field_28 = -2;
	this->field_2C = 0.0;
	this->field_30 = 0.0;
	this->field_C = (float)a6;
	this->field_34 = 0.0;
	this->minecraft = a2;
	this->field_38 = -1;
	this->field_10 = a7;
	this->field_18 = a4;
	this->field_3C = 0;
	this->field_1C = (float)a3;
	this->renderSelection = 1;
	this->field_41 = 0;
	this->field_44 = 0;
}
void ScrolledSelectionList::renderDirtBackground() {
	this->minecraft->texturesPtr->loadAndBindTexture("gui/background.png");
	glColor4f(1.0, 1.0, 1.0, 1.0);
	Tesselator::instance.begin(4);
	Tesselator::instance.color(0x202020);
	Tesselator::instance.vertexUV(this->field_20, this->field_C, 0.0, this->field_20 * 0.03125, (float)(this->field_C + (float)(int)this->field_30) * 0.03125);
	Tesselator::instance.vertexUV(this->field_1C, this->field_C, 0.0, this->field_1C * 0.03125, (float)(this->field_C + (float)(int)this->field_30) * 0.03125);
	Tesselator::instance.vertexUV(this->field_1C, this->field_8, 0.0, this->field_1C * 0.03125, (float)(this->field_8 + (float)(int)this->field_30) * 0.03125);
	Tesselator::instance.vertexUV(this->field_20, this->field_8, 0.0, this->field_20 * 0.03125, (float)(this->field_8 + (float)(int)this->field_30) * 0.03125);
	Tesselator::instance.draw(1);
}
void ScrolledSelectionList::setRenderHeader(bool_t a2, int32_t a3) {
	if(!a2) {
		a3 = 0;
	}
	this->field_41 = a2;
	this->field_44 = a3;
}

ScrolledSelectionList::~ScrolledSelectionList() {
}
void ScrolledSelectionList::setRenderSelection(bool_t a2) {
	this->renderSelection = a2;
}
int32_t ScrolledSelectionList::getMaxPosition() {
	return this->field_44 + this->field_10 * this->getNumberOfItems();
}
void ScrolledSelectionList::renderHeader(int32_t, int32_t, Tesselator&) {
}
void ScrolledSelectionList::renderDecorations(int32_t, int32_t) {
}
void ScrolledSelectionList::clickedHeader(int32_t, int32_t) {
}
int32_t ScrolledSelectionList::getItemAtPosition(int32_t a2, int32_t a3) {
	float v4;	 // s12
	int32_t v6;	 // s13
	float v7;	 // s14
	int32_t v8;	 // r1
	int32_t v9;	 // r0
	int32_t v10; // s15
	int32_t v11; // r5

	v4 = this->field_8;
	v6 = this->field_44;
	v7 = this->field_30;
	v8 = this->field_10;
	v9 = this->field_14 / 2;
	if(a2 < v9 - 110) {
		return -1;
	}
	if(a2 > v9 + 110) {
		return -1;
	}
	v10 = (int32_t)(float)((float)((float)((float)((float)a3 - v4) - (float)v6) + (float)(int32_t)v7) - 4.0);
	v11 = v10 / v8;
	if(v10 / v8 < 0 || v10 < 0 || v10 / v8 >= this->getNumberOfItems()) {
		return -1;
	}
	return v11;
}
float ScrolledSelectionList::capYPosition() {
	int32_t result; // r0
	float v3;		// s15

	result = this->getMaxPosition();
	v3 = (float)result - (float)((float)(this->field_C - this->field_8) - 4.0);
	if(v3 < 0.0) {
		v3 = v3 * 0.5;
	}
	if(this->field_30 < 0.0) {
		this->field_30 = 0.0;
	}
	if(this->field_30 > v3) {
		this->field_30 = v3;
	}
	return result;
}
void ScrolledSelectionList::render(int32_t a2, int32_t a3, float a4) {
	int32_t v7;		// r10
	float v8;		// s15
	int32_t v9;		// r3
	int32_t v10;	// r3
	int32_t TimeMs; // r0
	float v12;		// s15
	int32_t v13;	// r3
	float v14;		// s15
	int32_t v16;	// r8
	float v17;		// s15
	int32_t v18;	// s27
	int32_t i;		// r6
	int32_t v20;	// r2
	float v21;		// s20
	int32_t v22;	// s14
	float v23;		// s26
	float v24;		// s22
	int32_t v25;	// r1
	int32_t v26;	// s14
	float v27;		// s21
	float v28;		// s23
	float v29;		// r1
	float v30;		// s21
	float v31;		// s22
	float v32;		// s23
	float v33;		// s21

	this->renderBackground();
	v7 = this->getNumberOfItems();
	if(Mouse::isButtonDown(1)) {
		v8 = (float)a3;
		if((float)a3 >= this->field_8 && v8 <= this->field_C && a3 != this->field_24) {
			v9 = this->field_28;
			if(v9 == -1) {
				v10 = 1;
			} else {
				if(v9 < 0) {
LABEL_14:
					this->field_24 = -1;
					goto LABEL_23;
				}
				if(v9 == 1) {
					TimeMs = getTimeMs();
					this->field_38 = a3;
					this->field_3C = TimeMs;
				} else if(!v9) {
					v12 = v8 - this->field_2C;
					this->field_30 = this->field_30 - v12;
					this->field_34 = this->field_34 + v12;
				}
				v10 = 0;
			}
			this->field_28 = v10;
			goto LABEL_14;
		}
	} else {
		if(this->field_28 >= 0) {
			if(fabsf(this->field_34) < 2.0) {
				this->field_34 = 0.0;
			}
			if(getTimeMs() - this->field_3C < 300) {
				v25 = (int32_t)(float)((float)((float)((float)((float)a3 - this->field_8) - (float)this->field_44) + (float)(int32_t)this->field_30) - 4.0) / this->field_10;
				if(v25 >= 0) {
					v13 = this->field_38 - a3;
					if(v13 < 0) {
						v13 = a3 - this->field_38;
					}
					if(v13 < this->field_10) {
						this->selectItem(v25, 0);
						this->field_34 = 0.0;
					}
				}
			}
		}
		v14 = this->field_30 - this->field_34;
		this->field_28 = -1;
		this->field_30 = v14;
	}
LABEL_23:
	this->field_34 = this->field_34 * 0.75;
	this->field_2C = (float)a3;
	this->capYPosition();
	this->renderDirtBackground();
	v16 = this->field_14 / 2 - 108;
	v17 = (float)(int32_t)this->field_30;
	v18 = (int32_t)(float)((float)(this->field_8 + 4.0) - v17);
	if(this->field_41) {
		this->renderHeader(this->field_14 / 2 - 108, (int32_t)(float)((float)(this->field_8 + 4.0) - v17), Tesselator::instance);
	}
	for(i = 0; i < v7; ++i) {
		v20 = this->field_10;
		v21 = (float)(v18 + v20 * i + this->field_44);
		if(v21 <= this->field_C) {
			v22 = this->field_10;
			v23 = (float)v20 - 4.0;
			v24 = v21 + v23;
			if((float)(v21 + v23) >= this->field_8) {
				if(this->renderSelection && this->isSelectedItem(i)) {
					v26 = this->field_14;
					glColor4f(1.0, 1.0, 1.0, 1.0);
					v27 = (float)v26 * 0.5;
					DisableState v35(0xDE1);
					Tesselator::instance.begin(8);
					Tesselator::instance.color(8421504);
					v28 = v27 - 110.0;
					v29 = v27 - 110.0;
					v30 = v27 + 110.0;
					Tesselator::instance.vertexUV(v29, v24 + 2.0, 0.0, 0.0, 1.0);
					Tesselator::instance.vertexUV(v30, v24 + 2.0, 0.0, 1.0, 1.0);
					Tesselator::instance.vertexUV(v30, v21 - 2.0, 0.0, 1.0, 0.0);
					Tesselator::instance.vertexUV(v28, v21 - 2.0, 0.0, 0.0, 0.0);
					Tesselator::instance.color(0);
					v31 = v24 + 1.0;
					v32 = v28 + 1.0;
					Tesselator::instance.vertexUV(v32, v31, 0.0, 0.0, 1.0);
					v33 = v30 - 1.0;
					Tesselator::instance.vertexUV(v33, v31, 0.0, 1.0, 1.0);
					Tesselator::instance.vertexUV(v33, v21 - 1.0, 0.0, 1.0, 0.0);
					Tesselator::instance.vertexUV(v32, v21 - 1.0, 0.0, 0.0, 0.0);
					Tesselator::instance.draw(1);
					//~v35
				}
				this->renderItem(i, v16, (int32_t)v21, (int32_t)v23, Tesselator::instance);
			}
		}
	}
	DisableState v34(0xB71);
	this->renderHoleBackground(0.0, this->field_8, 255, 255);
	this->renderHoleBackground(this->field_C, (float)this->field_18, 255, 255);
	glShadeModel(0x1D01u);
	DisableState v35(0xDE1);
	Tesselator::instance.begin(4);
	Tesselator::instance.color(0, 0);
	Tesselator::instance.vertexUV(this->field_20, this->field_8 + 4.0, 0.0, 0.0, 1.0);
	Tesselator::instance.vertexUV(this->field_1C, this->field_8 + 4.0, 0.0, 1.0, 1.0);
	Tesselator::instance.color(0, 255);
	Tesselator::instance.vertexUV(this->field_1C, this->field_8, 0.0, 1.0, 0.0);
	Tesselator::instance.vertexUV(this->field_20, this->field_8, 0.0, 0.0, 0.0);
	Tesselator::instance.draw(1);
	Tesselator::instance.begin(4);
	Tesselator::instance.color(0, 255);
	Tesselator::instance.vertexUV(this->field_20, this->field_C, 0.0, 0.0, 1.0);
	Tesselator::instance.vertexUV(this->field_1C, this->field_C, 0.0, 1.0, 1.0);
	Tesselator::instance.color(0, 0);
	Tesselator::instance.vertexUV(this->field_1C, this->field_C - 4.0, 0.0, 1.0, 0.0);
	Tesselator::instance.vertexUV(this->field_20, this->field_C - 4.0, 0.0, 0.0, 0.0);
	Tesselator::instance.draw(1);
	this->renderDecorations(a2, a3);
	//~v35
	glShadeModel(0x1D00u);
	//~v34
}
void ScrolledSelectionList::renderHoleBackground(float a2, float a3, int32_t a4, int32_t a5) {
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
