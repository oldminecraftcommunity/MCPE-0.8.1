#include <gui/elements/Touch_TouchWorldSelectionList.hpp>
#include <cpputils.hpp>
#include <Minecraft.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Tesselator.hpp>
#include <input/Mouse.hpp>
#include <sstream>

//s0 s0 s1 s2 s3
static float _sub_D65F85F8(float a1, float a2, float a3, float a4) {
	float v4 = (a1 / a2) + (a1 / a2);
	float v5 = a4 - a3;
	if(v4 >= 1) return a3 + ((v5 * -0.5) * (((v4 - 1.0) * (v4 - 3.0)) - 1.0));
	else return a3 + (v5 * 0.5) * v4 * v4;
}

Touch::TouchWorldSelectionList::TouchWorldSelectionList(struct Minecraft* a2, int32_t a3, int32_t a4)
	: RolledSelectionListH(a2, a3, a4, 0, a3, 24, a4 - 32, 120) {
	this->field_70 = 0;
	this->field_74 = a4;
	this->field_9C = 0;
	this->field_C0 = 0;
	this->field_C8 = 0;
	this->field_43 = 0;
	this->field_B8 = -1;
	this->field_BC = -1;
}
void Touch::TouchWorldSelectionList::commit(void) {
	for(int i = 0; i < this->items.size(); ++i) {
		std::stringstream v13;
		v13 << this->items[i].field_4 << "/preview.png";
		this->field_90.push_back("gui/default_world.png");
		std::vector<std::string> v12;
		v12.push_back(this->items[i].field_4);
		v12.push_back(this->minecraft->platform()->getDateString(this->items[i].field_8));
		v12.push_back(this->items[i].worldName);
		char* v8;
		int gamemode = this->items[i].gamemode;
		if(gamemode == 0) v8 = "Survival";
		else if(gamemode == 1) v8 = "Creative";
		else v8 = "Undefined";
		v12.push_back(v8);
		this->levelsInfoMaybe.push_back(v12);
		this->selectedItem = 0;
	}
}
void Touch::TouchWorldSelectionList::stepLeft(void) {
	if(this->selectedItem > 0) {
		int32_t v2 = this->field_10;
		float v3 = this->field_2C;
		this->field_64 = v3;
		int32_t v4 = this->selectedItem * v2;
		uint32_t v5 = v2 - this->field_14;
		this->field_5C = 0;
		this->field_60 = 8;
		this->field_C8 = 1;
		this->field_68 = (v3 - (float)v2) - (float)(int32_t)(float)(v3 - (float)((float)v4 + vcvts_n_f32_s32(v5, 1u)));
		this->tweenInited();
	}
}
void Touch::TouchWorldSelectionList::stepRight(void) {
	if(this->selectedItem >= 0 && this->selectedItem < this->getNumberOfItems()) {
		int32_t v3 = this->field_10;
		float v4 = this->field_2C;
		int32_t v5 = this->selectedItem;
		this->field_64 = v4;
		int32_t v6 = v5 * v3;
		uint32_t v7 = v3 - this->field_14;
		this->field_5C = 0;
		this->field_60 = 8;
		this->field_C8 = 1;
		this->field_68 = (float)(v4 + (float)v3) - (float)(int32_t)(float)(v4 - (float)((float)v6 + vcvts_n_f32_s32(v7, 1u)));
		this->tweenInited();
	}
}
void Touch::TouchWorldSelectionList::tweenInited(void) {
	float v1 = this->field_5C;
	float v2 = this->field_60;
	float v3 = this->field_64;
	float v4 = this->field_68;
	float v6 = _sub_D65F85F8(v1, v2, v3, v4);
	float v7 = _sub_D65F85F8(v1 + 1, v2, v3, v4);
	this->field_38 = 0;
	this->field_34 = v6 - v7;
}

bool Touch::TouchWorldSelectionList::capXPosition() {
	bool r = RolledSelectionListH::capXPosition();
	if(r) this->field_C8 = 0;
	return r;
}
void Touch::TouchWorldSelectionList::tick() {
	int32_t v2;
	float v5, v6, v7, v9;
	int32_t itemRaw, v11;
	float v12;
	int32_t v13;
	float v14, v15;
	int32_t v16;

	RolledSelectionListH::tick();
	++this->field_C0;
	if(!Mouse::isButtonDown(1)) {
		v2 = this->field_24;
		if(v2) {
			this->selectedItem = -1;
			if(this->field_C8 == 1) {
				this->field_5C = this->field_5C + 1;
				if(this->field_5C == this->field_60) {
					this->field_34 = 0;
					this->field_C8 = 0;
					this->field_2C = this->field_68;
					this->field_30 = this->field_68;
label_21:
					this->selectedItem = this->getItemAtPosition(this->field_14 / 2, this->field_18 / 2);
					return;
				}
				this->tweenInited();
				return;
			}
			v6 = this->field_34;
			v7 = fabsf(v6);
			if(v7 >= 5) {
				this->field_34 = v6 * 0.9;
				return;
			}

			this->field_34 = v6 * 0.8;
			if(v7 < 1 && v2 < 0) {
				v9 = (float)((this->field_14 - this->field_10) / 2) + this->field_2C;
				itemRaw = this->getItemAtXPositionRaw((int32_t)(float)(v9 - (float)(this->field_34 * 10.0)));
				v11 = this->field_10;
				v12 = (float)(itemRaw * v11) - v9;
				if(v12 < (float)(v11 / -2)) {
					v13 = this->field_10;
					v12 = v12 + v11;
				}
				v14 = fabsf(v12);
				if(v14 < 1 && v7 < 0.1) goto label_21;
				v15 = this->field_2C;
				this->field_5C = 0;
				this->field_64 = v15;
				this->field_68 = v15 + v12;
				v16 = (int32_t)(float)(v14 * 0.25) + 1;
				if(v16 >= 7) v16 = 7;
				this->field_C8 = 1;
				this->field_60 = (float)v16;
			}
		}
	}
}
int32_t Touch::TouchWorldSelectionList::getNumberOfItems() {
	return this->items.size() + 1;
}
void Touch::TouchWorldSelectionList::selectStart(int32_t a2, int32_t a3, int32_t a4) {
	if(this->selectedItem == this->items.size() && a2 == this->selectedItem) this->field_70 = 1;
}
void Touch::TouchWorldSelectionList::selectCancel() {
	this->field_70 = 0;
}
void Touch::TouchWorldSelectionList::selectItem(int32_t a2, bool_t a3) {
	if(this->selectedItem >= 0) {
		int32_t v4 = a2 - this->selectedItem;
		if(v4 == -1) this->stepLeft();
		else if(v4 == 1) this->stepRight();
		else if(v4 == 0 && !this->field_9C) {
			this->field_B8 = a2;
			this->field_9C = 1;
			if(a2 < this->items.size()) {
				this->field_A0 = this->items[a2];
			}
		}
	}
}
bool_t Touch::TouchWorldSelectionList::isSelectedItem(int32_t a2) {
	return a2 == this->selectedItem;
}

float Touch::TouchWorldSelectionList::getPos(float a2) {
	if(this->field_C8 != 1) return RolledSelectionListH::getPos(a2);
	float v4 = this->field_5C;
	float v5 = this->field_60;
	float v6 = this->field_64;
	float v7 = this->field_68;

	float v8 = _sub_D65F85F8(v4, v5, v6, v7);
	return v8 + (_sub_D65F85F8(v4 + 1, v5, v6, v7) - v8) * a2;
}

void Touch::TouchWorldSelectionList::renderItem(int32_t a2, int32_t a3, int32_t a4, int32_t a5, Tesselator& a6) {
	int32_t v9 = a3 + this->field_10 / 2;
	int32_t v10 = this->field_14 / 2 - v9;
	if(v10 < 0) v10 = v9 - this->field_14 / 2;
	float v11 = 1.1 - (float)((float)v10 * 0.0055);
	if(v11 < 0.2) v11 = 0.2;
	else if(v11 > 1.0) v11 = 1.0;
	int32_t v12 = 0x10101 * (int32_t)(v11 * 255);
	if(a2 >= this->items.size()) {
		float v18 = 0.125;
		float v19 = 0.54688;
		this->drawCenteredString(this->minecraft->font, "Create new", v9, a4 + 56, v12);
		this->minecraft->texturesPtr->loadAndBindTexture("gui/touchgui.png");
		float v22 = (float)a4;
		if(this->field_70) v18 = 0.33594;
		else v19 = 0.33594;
		a6.begin(4);
		a6.color(v12);
		a6.vertexUV(v9 - 27, v22, this->zLayer, 0.65625, v18);
		a6.vertexUV(v9 - 27, v22 + 54, this->zLayer, 0.65625, v19);
		a6.vertexUV(v9 + 27, v22 + 54, this->zLayer, 0.86719, v19);
		a6.vertexUV(v9 + 27, v22, this->zLayer, 0.86719, v18);
		a6.draw(1);
	} else {
		int32_t v13 = this->field_10;
		std::vector<std::string> v28(this->levelsInfoMaybe[a2]);
		this->drawString(this->minecraft->font, v28[0], v9 - v13 / 2 + 5, a4 + 44, 0x10101 * (int32_t)(float)(v11 * 255));
		this->drawString(this->minecraft->font, v28[1], v9 - v13 / 2 + 5, a4 + 54, 0x10101 * (int32_t)(float)(v11 * 140));
		this->drawString(this->minecraft->font, v28[2], v9 - v13 / 2 + 5, a4 + 64, 0x10101 * (int32_t)(float)(v11 * 140));
		this->drawString(this->minecraft->font, v28[3], v9 - v13 / 2 + 5, a4 + 74, 0x10101 * (int32_t)(float)(v11 * 255));
		this->minecraft->texturesPtr->loadAndBindTexture(this->field_90[a2]);
		a6.color(0.3f, 1.0f, 0.2f);
		float v14 = (float)a4 - 8;
		a6.begin(4);
		a6.color(v12);
		int32_t v15 = v9 - 32;
		int32_t v16 = v9 + 32;
		float v17 = (float)v15;
		a6.vertexUV(v17, v14, this->zLayer, 0, 0.125);
		a6.vertexUV(v17, v14+48, this->zLayer, 0, 0.875);
		a6.vertexUV(v16, v14+48, this->zLayer, 1, 0.875);
		a6.vertexUV(v16, v14, this->zLayer, 1, 0.125);
		a6.draw(1);
	}
}
