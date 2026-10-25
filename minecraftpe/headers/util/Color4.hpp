#pragma once
#include <_types.h>

//see comment in AABB.hpp (if i didnt remove it)
static const float& min2(const float& x, const float& y) {
	if(y < x) return y;
	return x;
}
static const float& max2(const float& x, const float& y) {
	if(x < y) return y;
	return x;
}

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

	Color4(float r, float g, float b, float a){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	int32_t toARGB(void) const {
		int ret;
		//TODO this might break with the wrong endianness?
		((unsigned char*) (&ret))[0] = (unsigned int) ((this->r * 255.0f));
		((unsigned char*) (&ret))[1] = (unsigned int) ((this->g * 255.0f));
		((unsigned char*) (&ret))[2] = (unsigned int) ((this->b * 255.0f));
		((unsigned char*) (&ret))[3] = (unsigned int) ((this->a * 255.0f));
		return ret;
	}
	static Color4 lerp(const Color4& a2, const Color4& a3, float a4){
		return Color4(
			(a4 * a3.r) + ((1.0f - a4) * a2.r),
			(a4 * a3.g) + ((1.0f - a4) * a2.g),
			(a4 * a3.b) + ((1.0f - a4) * a2.b),
			(a4 * a3.a) + ((1.0f - a4) * a2.a));
	}
	static Color4 fromHSB(float, float, float);
	void clamp(void) {
		this->r = max2(0.0f, min2(this->r, 1.0f));
		this->g = max2(0.0f, min2(this->g, 1.0f));
		this->b = max2(0.0f, min2(this->b, 1.0f));
		this->a = max2(0.0f, min2(this->a, 1.0f));
	}
};
