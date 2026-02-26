#pragma once
#include <input/IMoveInput.hpp>
#include <gui/GuiComponent.hpp>
#include <util/area/RectangleArea.hpp>
#include <input/TouchAreaModel.hpp>
#include <rendering/MeshBuffer.hpp>

struct Options;
struct Minecraft;
struct Player;

struct TouchscreenInput: IMoveInput
{
	float field_4;
	float field_8;
	int8_t field_C;
	int8_t field_D;
	int8_t field_E;
	int8_t field_F;
	int8_t field_10;
	int8_t field_11;
	int8_t field_12;
	int8_t field_13;
	GuiComponent field_14;
	RectangleArea field_1C;
	int32_t field_34;
	int32_t field_38;
	Options* options;
	int8_t field_40;
	bool_t field_41;
	int8_t field_42;
	int8_t field_43;
	TouchAreaModel touchAreaModel;
	Minecraft* minecraft;
	RectangleArea* rectArea7;
	RectangleArea* rectArea8;
	RectangleArea* rectArea1;
	RectangleArea* rectArea6;
	RectangleArea* field_68;
	RectangleArea* rectArea9;
	RectangleArea* rectArea5;
	RectangleArea* rectArea2;
	RectangleArea* rectArea3;
	int8_t field_7C;
	int8_t field_7D;
	int8_t field_7E;
	int8_t field_7F;
	MeshBuffer field_80;
	bool_t field_A8;
	int8_t field_A9;
	int8_t field_AA;
	int8_t field_AB;
	float field_AC;
	int8_t field_B0[8];

	TouchscreenInput(Minecraft*, Options*);
	void clear();
	RectangleArea* getPauseRectangleArea();
	RectangleArea* getRectangleArea();
	bool_t isButtonDown(int32_t);
	void rebuild();

	virtual ~TouchscreenInput();
	virtual void tick(Player*);
	virtual void render(float);
	virtual void setKey(int32_t, bool_t);
	virtual void releaseAllKeys();
	virtual void onConfigChanged(const Config&);
};
