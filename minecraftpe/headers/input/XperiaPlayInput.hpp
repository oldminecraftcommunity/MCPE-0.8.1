#pragma once
#include <input/KeyboardInput.hpp>
#include <util/area/RectangleArea.hpp>

struct Minecraft;

struct XperiaPlayInput: KeyboardInput
{
	bool_t field_20;
	int8_t field_21, field_22, field_23;
	Minecraft* mc;
	RectangleArea field_28, field_40;
	bool_t field_58;
	int8_t field_59, field_5A, field_5B;

	XperiaPlayInput(Minecraft*, Options*);

	virtual ~XperiaPlayInput();
	virtual void tick(Player*);
	virtual void render(float);
	virtual void onConfigChanged(const Config&);
};
