#include <gui/elements/RolledSelectionListH.hpp>
#include <utils.h>
#include <Minecraft.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Tesselator.hpp>
#include <input/Mouse.hpp>

RolledSelectionListH::RolledSelectionListH(struct Minecraft* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9)
	: GuiComponent() {
	this->field_10 = a9;
	this->field_24 = -2;
	this->field_8 = a5;
	this->field_28 = 0;
	this->field_34 = 0;
	this->field_38 = 0;
	this->minecraft = a2;
	this->field_C = a6;
	this->field_14 = a3;
	this->field_18 = a4;
	this->field_3C = -1;
	this->renderSelection = 1;
	this->componentSelected = 0;
	this->field_42 = 1;
	this->field_1C = a7;
	this->field_43 = 1;
	this->field_44 = 0;
	this->field_48 = 0;
	this->field_4C = 0;
	this->field_50 = -1;
	this->field_20 = a8;
	float v13 = vcvts_n_f32_s32(a9 - a3, 1u);
	this->field_30 = v13;
	this->field_2C = v13;
	this->field_54 = v13;
}
int32_t RolledSelectionListH::getItemAtXPositionRaw(int32_t a2) {
	int32_t v3, v4;
	v3 = a2 / this->field_10;
	v4 = v3;
	if(v3 < 0 || a2 < 0 || v3 >= this->getNumberOfItems()) {
		return -1;
	}
	return v4;
}

void RolledSelectionListH::setRenderSelection(bool_t a2) {
	this->renderSelection = a2;
}


RolledSelectionListH::~RolledSelectionListH() {
}

int32_t RolledSelectionListH::getItemAtPosition(int32_t a2, int32_t a3) {
	if((float)a3 < this->field_1C || (float)a3 > this->field_20) return -1;

	return this->getItemAtXPositionRaw((int32_t)(float)((float)((float)((float)((float)a2 - this->field_8) - (float)this->field_44) + (float)(int32_t)this->field_2C) - 4.0));
}
bool_t RolledSelectionListH::capXPositon(void) {
	float v2;
	int32_t v3;
	float v4;
	v2 = vcvts_n_f32_s32(this->field_10 - this->field_14, 1);
	v3 = this->getNumberOfItems();
	v4 = this->field_2C;
	if(v4 >= v2) {
		v2 = v2 + ((v3 - 1) * this->field_10);
		if(v4 <= v2) return 0;
	}
	this->field_2C = v2;
	this->field_34 = 0;
	return 1;
}
void RolledSelectionListH::tick() {
	float v1, v2, v3;
	v1 = this->field_30;
	v2 = this->field_54 - v1;
	this->field_54 = v1;
	v3 = this->field_34;
	this->field_38 = v2;
	this->field_30 = this->field_2C - v3;
}
void RolledSelectionListH::render(int32_t a2, int32_t a3, float a4) {
	this->renderBackground();
	int32_t v8 = this->getNumberOfItems();

	if(Mouse::isButtonDown(1)) {
		this->touched();
		if(a3 >= this->field_1C && a3 <= this->field_20) {
			int32_t v9 = this->field_24;
			if(v9 == -1) {
				int32_t timeMS = getTimeMs();
				int32_t v12 = this->field_18 / 2;
				this->field_4C = timeMS;
				int32_t v13 = this->getItemAtPosition(a2, v12);
				this->field_50 = v13;
				this->selectStart(v13, 0, 0);
				this->field_3C = a2;
			} else if(v9 >= 0) {
				float v15 = this->field_2C - ((float)a2 - this->field_28);
				this->field_2C = v15;
				this->field_30 = v15;
			}
			this->field_24 = 0;
		}
	} else {
		if(this->field_24 >= 0) {
			float v16 = this->field_38;
			int32_t v30, v17;
			if(v16 >= 0) {
				if(v16 >= 20) v16 = 20;
			} else if(v16 <= -20) v16 = -20;

			if(fabsf(v16) <= 2.0001) v16 = 0;
			this->field_34 = v16;
			if(fabsf(v16) > 10) goto SELECT_CANCEL;
			if(getTimeMs() - this->field_4C >= 300) goto SELECT_CANCEL;
			v30 = this->getItemAtPosition(a2, this->field_18 / 2);
			if(v30 < 0) goto SELECT_CANCEL;
			if(v30 != this->field_50) goto SELECT_CANCEL;
			v17 = this->field_3C - a2;
			if(v17 < 0) v17 = a2 - this->field_3C;
			if(v17 <= 9) this->selectItem(v30, 0);
			else {
SELECT_CANCEL:
				this->selectCancel();
			}
		}
		this->field_24 = -1;
		this->field_2C = this->getPos(a4);
	}
	this->field_28 = a2;
	this->capXPositon();
	float v19, v20;
	if(this->field_42) v19 = this->field_1C;
	else v19 = 0;

	if(this->field_43) v20 = this->field_20;
	else v20 = this->field_18;

	this->minecraft->texturesPtr->loadAndBindTexture("gui/background.png");
	glColor4f(1, 1, 1, 1);
	Tesselator::instance.begin(4);
	Tesselator::instance.color(0x202020);
	Tesselator::instance.vertexUV(this->field_8, v20, 0, (this->field_8 + this->field_2C) * 0.03125, v20 * 0.03125);
	Tesselator::instance.vertexUV(this->field_C, v20, 0, (this->field_C + this->field_2C) * 0.03125, v20 * 0.03125);
	Tesselator::instance.vertexUV(this->field_C, v19, 0, (this->field_C + this->field_2C) * 0.03125, v19 * 0.03125);
	Tesselator::instance.vertexUV(this->field_8, v19, 0, (this->field_8 + this->field_2C) * 0.03125, v19 * 0.03125);
	Tesselator::instance.draw(1);

	if(!this->getNumberOfItems()) this->field_2C = 0;
	float v22 = this->field_8;
	int32_t v23 = this->field_18 / 2 - 40;
	int32_t v24 = (int32_t)(float)(v22 - (float)(int32_t)this->field_2C);
	if(this->field_48) this->renderHeader((int32_t)(float)(v22 - (float)(int32_t)this->field_2C), v23, Tesselator::instance);
	for(int32_t i = 0; i < v8; ++i) {
		int32_t v26 = this->field_10;
		float v27 = (float)(v24 + v26 * i + this->field_44);
		if(v27 <= this->field_C) {
			float v28 = (float)v26;
			float v29 = v27 + (float)v26;
			if(v29 >= this->field_8) {
				if(this->renderSelection) {
					if(this->isSelectedItem(i)) {
						glDisable(0xDE1u);
						int32_t v31 = this->field_18;
						glColor4f(1, 1, 1, 1);
						int32_t v32;
						if(this->componentSelected) v32 = 0x7F89BF;
						else v32 = 0x808080;

						Tesselator::instance.begin(8);
						float v33 = (float)v31 * 0.5;
						Tesselator::instance.color(v32);
						float v34 = (float)(v33 - 48) - 4;
						float v35 = (float)(v33 + 48) - 4;
						Tesselator::instance.vertex(v27 - 1, v34, 0);
						Tesselator::instance.vertex(v27 - 1, v35 + 0, 0);
						Tesselator::instance.vertex((v29 + 1) + 0, v35 + 0, 0);
						Tesselator::instance.vertex((v29 + 1) + 0, v34, 0);
						Tesselator::instance.color(0);
						float v36 = v34 + 1;
						Tesselator::instance.vertex(v27, v36, 0);
						Tesselator::instance.vertex(v27, v35 - 1.0, 0);
						Tesselator::instance.vertex(v29, v35 - 1.0, 0);
						Tesselator::instance.vertex(v29, v36, 0);
						Tesselator::instance.draw(1);
						glEnable(0xDE1u);
					}
				}
				this->renderItem(i, (int32_t)v27, v23, (int32_t)v28, Tesselator::instance);
			}
		}
	}

	glDisable(0xB71u);
	if(this->field_42) this->renderHoleBackground(0.0, this->field_1C, 255, 255);
	if(this->field_43) this->renderHoleBackground(this->field_20, (float)this->field_18, 255, 255);
	glEnable(0xB71u);
}

void RolledSelectionListH::renderHoleBackground(float a2, float a3, int32_t a4, int32_t a5) {
	this->minecraft->texturesPtr->loadAndBindTexture("gui/background.png");
	glColor4f(1, 1, 1, 1);
	Tesselator::instance.begin(4);
	Tesselator::instance.color(0x505050, a5);
	Tesselator::instance.vertexUV(0, a3, 0, 0, a3*0.03125);
	Tesselator::instance.vertexUV(this->field_14, a3, 0, this->field_14*0.03125, a3*0.03125);
	Tesselator::instance.color(0x505050, a4);
	Tesselator::instance.vertexUV(this->field_14, a2, 0, this->field_14*0.03125, a2*0.03125);
	Tesselator::instance.vertexUV(0, a2, 0, 0, a2*0.03125);
	Tesselator::instance.draw(1);
}

void RolledSelectionListH::setRenderHeader(bool_t a2, int32_t a3) {
	if(!a2) a3 = 0;
	this->field_48 = a2;
	this->field_44 = a3;
}

void RolledSelectionListH::setComponentSelected(bool_t a2) {
	this->componentSelected = a2;
}

//int32_t RolledSelectionListH::getNumberOfItems() = 0;
void RolledSelectionListH::selectStart(int32_t, int32_t, int32_t) {
}
void RolledSelectionListH::selectCancel(void) {
}
//void RolledSelectionListH::selectItem(int32_t, bool_t) = 0;
//bool_t RolledSelectionListH::isSelectedItem(int32_t) = 0;
int32_t RolledSelectionListH::getMaxPosition() {
	return this->field_44 + this->field_10 * this->getNumberOfItems();
}
float RolledSelectionListH::getPos(float a2) {
	return this->field_30 - (float)(a2 * this->field_34);
}
void RolledSelectionListH::touched() {
}
//void RolledSelectionListH::renderItem(int32_t, int32_t, int32_t, int32_t, struct Tesselator&) = 0;
void RolledSelectionListH::renderHeader(int32_t, int32_t, struct Tesselator&) {
}
//void RolledSelectionListH::renderBackground() = 0;
void RolledSelectionListH::renderDecorations(int32_t, int32_t){
}
void RolledSelectionListH::clickedHeader(int32_t, int32_t) {}
