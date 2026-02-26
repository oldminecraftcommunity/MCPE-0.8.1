#include <gui/elements/WorldSelectionList.hpp>
#include <Minecraft.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <input/Mouse.hpp>
#include <sstream>

WorldSelectionList::WorldSelectionList(Minecraft* a2, int32_t a3, int32_t a4) : RolledSelectionListH(a2, a3, a4, 0, a3, 26, a4 - 32, 120) {
	this->field_70 = a4;
	this->field_98 = 0;
	this->field_B8 = 0;
	this->field_C0 = 0;
	this->field_B4 = -1;
}
void WorldSelectionList::commit() {
	for(int i = 0; i < this->field_74.size(); ++i) {
		LevelSummary* v3 = &this->field_74[i];
		std::stringstream v13;
		v13 << v3->field_4;
		v13 << "/preview.png";
		this->field_8C.emplace_back("gui/default_world.png");
		std::vector<std::string> v12;
		v12.push_back(v3->field_4);
		v12.emplace_back(this->minecraft->platform()->getDateString(v3->field_8));
		v12.push_back(v3->field_0);
		v12.emplace_back(v3->field_C == 1 ? "Creative" : (v3->field_C == 0 ? "Survival" : "Undefined"));
		this->field_80.emplace_back(v12);
		this->field_6C = 0;
	}
}
void WorldSelectionList::stepLeft() {
	float v1; // s14
	float v2; // s15

	if(this->field_6C > 0) {
		v1 = (float)this->field_10;
		v2 = this->field_2C;
		this->field_64 = v2;
		this->field_5C = 0.0;
		this->field_60 = 8.0;
		this->field_C0 = 1;
		this->field_68 = v2 - v1;
		this->tweenInited();
	}
}
void WorldSelectionList::stepRight() {
	int32_t v2; // r5
	float v3;	// s14
	float v4;	// s15

	v2 = this->field_6C;
	if(v2 >= 0 && v2 < this->getNumberOfItems() - 1) {
		v3 = (float)this->field_10;
		v4 = this->field_2C;
		this->field_64 = v4;
		this->field_5C = 0.0;
		this->field_60 = 8.0;
		this->field_C0 = 1;
		this->field_68 = v4 + v3;
		this->tweenInited();
	}
}

float sub_D65F560E(float a1, float a2, float a3, float a4) {
	float v4; // s1
	float v5; // s3

	v4 = (float)(a1 / a2) + (float)(a1 / a2);
	v5 = a4 - a3;
	if(v4 >= 1.0) {
		return a3 + (float)((float)(v5 * -0.5) * (float)((float)((float)(v4 - 1.0) * (float)(v4 - 3.0)) - 1.0));
	} else {
		return a3 + (float)((float)((float)(v5 * 0.5) * v4) * v4);
	}
}

void WorldSelectionList::tweenInited() {
	float v1; // s19
	float v2; // s18
	float v3; // s17
	float v4; // s16
	float v6; // s20

	v1 = this->field_5C;
	v2 = this->field_60;
	v3 = this->field_64;
	v4 = this->field_68;
	v6 = sub_D65F560E(v1, v2, v3, v4);
	this->field_34 = v6 - sub_D65F560E(v1 + 1.0, v2, v3, v4);
}

WorldSelectionList::~WorldSelectionList() {
}
int32_t WorldSelectionList::capXPosition() {
	int32_t result; // r0

	result = this->capXPosition();
	if(result) {
		this->field_C0 = 0;
	}
	return result;
}
void WorldSelectionList::tick(){
	int32_t v2; // r3
	float v3; // s15
	float v4; // s14
	float v5; // r3
	float v6; // s15
	float v7; // s16
	float v8; // s15
	float v9; // s17
	int32_t itemAtXPos; // r0
	int32_t v11; // r3
	float v12; // s15
	int32_t v13; // s13
	float v14; // s14
	float v15; // s13
	int32_t v16; // r3

	RolledSelectionListH::tick();
	++this->field_B8;
	if ( !Mouse::isButtonDown(1) )
	{
		v2 = this->field_24;
		if ( v2 )
		{
			this->field_6C = -1;
			if ( this->field_C0 == 1 )
			{
				v3 = this->field_5C + 1.0;
				v4 = this->field_60;
				this->field_5C = v3;
				if ( v3 == v4 )
				{
					this->field_34 = 0.0;
					v5 = this->field_68;
					this->field_C0 = 0;
					this->field_2C = v5;
					this->field_30 = v5;
LABEL_21:
					this->field_6C = this->getItemAtPosition(
						this->field_14 / 2,
						this->field_18 / 2);
					return;
				}
				goto LABEL_20;
			}
			v6 = this->field_34;
			v7 = fabsf(v6);
			if ( v7 >= 5.0 )
			{
				this->field_34 = v6 * 0.9;
				return;
			}
			v8 = v6 * 0.8;
			this->field_34 = v8;
			if ( v7 < 1.0 && v2 < 0 )
			{
				v9 = (float)((this->field_14 - this->field_10) / 2) + this->field_2C;
				itemAtXPos = this->getItemAtXPositionRaw(
					(int32_t)(float)(v9 - (float)(v8 * 10.0)));
				v11 = this->field_10;
				v12 = (float)(itemAtXPos * v11) - v9;
				if ( v12 < (float)(v11 / -2) )
				{
					v13 = this->field_10;
					v12 = v12 + (float)v11;
				}
				v14 = fabsf(v12);
				if ( v14 < 1.0 && v7 < 0.1 )
				{
					goto LABEL_21;
				}
				v15 = this->field_2C;
				this->field_5C = 0.0;
				this->field_64 = v15;
				this->field_68 = v15 + v12;
				v16 = (int32_t)(float)(v14 * 0.25) + 1;
				if ( v16 >= 7 )
				{
					v16 = 7;
				}
				this->field_C0 = 1;
				this->field_60 = (float)v16;
LABEL_20:
				this->tweenInited();
			}
		}
	}
}
int32_t WorldSelectionList::getNumberOfItems() {
	return this->field_74.size();
}
void WorldSelectionList::selectItem(int32_t a2, bool_t a3) {
	int32_t v3; // r3

	v3 = this->field_6C;
	if(v3 >= 0 && v3 == a2 && !this->field_98) {
		this->field_98 = 1;
		this->field_9C = this->field_74[v3];
	}
}
bool_t WorldSelectionList::isSelectedItem(int32_t a2) {
	return a2 == this->field_6C;
}
float WorldSelectionList::getPos(float a2) {
	float v4; // s20
	float v5; // s19
	float v6; // s18
	float v7; // s17
	float v8; // s16

	if(this->field_C0 != 1) {
		return this->getPos(a2);
	}
	v4 = this->field_5C;
	v5 = this->field_60;
	v6 = this->field_64;
	v7 = this->field_68;
	v8 = sub_D65F560E(v4, v5, v6, v7);
	return v8 + (float)((float)(sub_D65F560E(v4 + 1.0, v5, v6, v7) - v8) * a2);
}
void WorldSelectionList::touched() {
	this->field_C0 = 0;
}
void WorldSelectionList::renderItem(int32_t a2, int32_t a3, int32_t a4, int32_t a5, Tesselator& a6) {
	int32_t v9;	 // r8
	int32_t v10; // r3
	float v11;	 // s15
	int32_t v12; // r7
	int32_t v13; // r9
	float v14;	 // s17
	int32_t v15; // s18
	int32_t v16; // r8
	float v17;	 // s18
	Font* font;	 // [sp+Ch] [bp-54h]
	Font* v19;	 // [sp+Ch] [bp-54h]
	Font* v20;	 // [sp+Ch] [bp-54h]
	Font* v21;	 // [sp+Ch] [bp-54h]

	v9 = a3 + this->field_10 / 2;
	v10 = this->field_14 / 2 - v9;
	if(v10 < 0) {
		v10 = v9 - this->field_14 / 2;
	}
	v11 = 1.1 - (float)((float)v10 * 0.0055);
	if(v11 <= 0.2) {
		v11 = 0.2;
	} else if(v11 > 1.0) {
		v11 = 1.0;
	}
	v12 = a3 + 5;
	v13 = 65793 * (int32_t)(float)(v11 * 140.0);
	std::vector<std::string> v23(this->field_80[a2]);
	font = this->minecraft->font;
	this->drawString(font, v23[0], v12, a4 + 42, 65793 * (int32_t)(float)(v11 * 255.0));
	v19 = this->minecraft->font;
	this->drawString(v19, v23[1], v12, a4 + 52, v13);
	v20 = this->minecraft->font;
	this->drawString(v20, v23[2], v12, a4 + 62, v13);
	v21 = this->minecraft->font;
	this->drawString(v21, v23[3], v12, a4 + 72, v13);
	this->minecraft->texturesPtr->loadAndBindTexture(this->field_8C[a2]);
	a6.color(0.3f, 1.0f, 0.2f);
	v14 = (float)a4 - 8.0;
	a6.begin(4);
	a6.color(65793 * (int32_t)(float)(v11 * 255.0));
	v15 = v9 - 32;
	v16 = v9 + 32;
	v17 = (float)v15;
	a6.vertexUV(v17, v14, this->zLayer, 0.0, 0.0);
	a6.vertexUV(v17, v14 + 48.0, this->zLayer, 0.0, 1.0);
	a6.vertexUV((float)v16, v14 + 48.0, this->zLayer, 1.0, 1.0);
	a6.vertexUV((float)v16, v14, this->zLayer, 1.0, 0.0);
	a6.draw(1);
}
void WorldSelectionList::renderBackground() {
}
