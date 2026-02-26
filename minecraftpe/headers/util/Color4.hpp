#pragma once
#include <_types.h>

struct Color4{

	static Color4 WHITE;
	static Color4 GREY;
	static Color4 BLACK;
	static Color4 RED;
	static Color4 GREEN;
	static Color4 BLUE;
	static Color4 NIL;


	float r;
	float g;
	float b;
	float a;

	Color4(float r, float g, float b, float a);
	int32_t toARGB(void);
	static Color4 lerp(const Color4&, const Color4&, float);
	static Color4 fromHSB(float, float, float);
	void clamp(void);
};
