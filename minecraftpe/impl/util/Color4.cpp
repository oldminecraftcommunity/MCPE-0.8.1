#include <util/Color4.hpp>
#include <math.h>

Color4 Color4::WHITE(1.0, 1.0, 1.0, 1.0);
Color4 Color4::GREY(0.5, 0.5, 0.5, 1.0);
Color4 Color4::BLACK(0.0, 0.0, 0.0, 1.0);
Color4 Color4::RED(1.0, 0.0, 0.0, 1.0);
Color4 Color4::GREEN(0.0, 1.0, 0.0, 1.0);
Color4 Color4::BLUE(0.0, 0.0, 1.0, 1.0);
Color4 Color4::NIL(0.0, 0.0, 0.0, 0.0);

Color4::Color4(float r, float g, float b, float a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

int32_t Color4::toARGB(void){
	union{
		struct{
			uint8_t r, g, b, a;
		} argb;
		int32_t n;
	} ret;

	ret.argb.r = (uint8_t)(this->r * 255);
	ret.argb.g = (uint8_t)(this->g * 255);
	ret.argb.b = (uint8_t)(this->b * 255);
	ret.argb.a = (uint8_t)(this->a * 255);

	return ret.n;
}

Color4 Color4::lerp(const Color4& a2, const Color4& a3, float a4){
	return Color4((a4 * a3.r) + ((float)(1.0 - a4) * a2.r), (a4 * a3.g) + ((float)(1.0 - a4) * a2.g), (a4 * a3.b) + ((float)(1.0 - a4) * a2.b), (a4 * a3.a) + ((float)(1.0 - a4) * a2.a));
}

Color4 Color4::fromHSB(float h, float s, float b){
	float v7, v8, v9, v10, v11, g, v13, a;

	if(s != 0.0){
		v7 = (float)(h - floorf(h)) * 6.0;
		v8 = floorf(v7);
		v9 = b * (float)(1.0 - (float)(s * (float)(v7 - v8)));
		v10 = b * (float)(1.0 - s);
		v11 = b * (float)(1.0 - (float)(s * (float)(1.0 - (float)(v7 - v8))));
		switch((int32_t)v7){
			case 0:
				return Color4(b, v11, v10, 1.0f);
			case 1:
				return Color4(v9, b, v10, 1.0f);
			case 2:
				return Color4(v10, b, v11, 1.0f);
			case 3:
				return Color4(v10, v9, b, 1.0f);
			case 4:
				return Color4(v11, v10, b, 1.0f);
			case 5:
				return Color4(b, v10, v9, 1.0f);
			default:
				return Color4::NIL;
		}
	}
	return Color4(b, b, b, 1.0f);
}

void Color4::clamp(void){
	if(this->a > 1.0) this->a = 1.0;
	else if(this->a <= 0.0) this->a = 0.0;

	if(this->r > 1.0) this->r = 1.0;
	else if(this->r <= 0.0) this->r = 0.0;

	if(this->g > 1.0) this->g = 1.0;
	else if(this->g <= 0.0) this->g = 0.0;

	if(this->b > 1.0) this->b = 1.0;
	else if(this->b <= 0.0) this->b = 0.0;
}
