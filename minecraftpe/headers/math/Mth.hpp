#pragma once
#include <_types.h>
#include <util/Random.hpp>
#include <math.h>

struct Mth{
	static float _sinScale;
	static float RADDEG;
	static float DEGRAD;
	static float TAU;
	static float PI;

	static float _sin[65536];

	static float cos(float x){
		return Mth::_sin[(int32_t)(x * 10430.0f + 16384.0) & 0xffff];
	}
	static float sin(float x){
		return Mth::_sin[(int32_t)(x * 10430.0f) & 0xffff];
	}
	static int32_t floor(float x){
		int32_t xi = (int32_t) x;
		if(x < (float)xi) return xi - 1;
		return xi;
	}
	static int32_t intFloorDiv(int32_t x, int32_t y){
		if(x >= 0) return x / y;
		else return ~(~x / y);
	}
	static float wrapDegrees(float f){
		float v1;
		float v2;

		v1 = fmodf(f, 360.0);
		v2 = v1;
		if(v1 >= 180.0) v2 = v1 - 360;
		if(v1 < -180.0) return v2 + 360;
		return v2;
	}
	static uint32_t fastRandom(void) {
		static int32_t x = 123456789;
		static int32_t y = 362436069;
		static int32_t z = 521288629;
		static int32_t w = 88675123;
		uint32_t v0;
		uint32_t result;
		v0 = x ^ (x << 11);
		x = y;
		y = z;
		z = w;
		result = w ^ (w >> 19) ^ v0 ^ (v0 >> 8);
		w = result;
		return result;
	}
	static float random(void);
	static uint32_t random(int32_t);
	static float clampRotate(float f, float f1, float f2) {
		float f3, f4, f5;
		f3 = fmodf(f1 - f, 360.0);
		f4 = f3;
		if (f3 >= 180.0) f4 = f3 - 360.0;

		if (f4 < -180.0) f4 = f4 + 360.0;

		f5 = -f2;
		if (f4 > f2) f4 = f2;

		if (f4 >= f5) f5 = f4;

		return f + f5;
	}
	static float sqrt(float f){
		return ::sqrt(f);
	}
	static float atan2(float x, float y){
		return ::atan2(x, y);
	}


	//those methods should always be inlined and may not exist in original
	static float rsqrt(float number) {
		//taken from wikipedia
		int i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(int*)&y;
		i = 0x5f3759df - (i >> 1);
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));

		return y;
	}
};
