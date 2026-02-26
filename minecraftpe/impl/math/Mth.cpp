#include <math/Mth.hpp>
#include <math.h>
float Mth::_sin[65536]; //XXX initialized in NinecraftApp::init
Random Mth::_random;

float Mth::cos(float x){
	return Mth::_sin[(int32_t)(x * 10430.0f + 16384.0) & 0xffff];
}

float Mth::sin(float x){
	return Mth::_sin[(int32_t)(x * 10430.0f) & 0xffff];
}

int32_t Mth::floor(float x){
	int32_t xi = (int32_t) x;
	if(x < (float)xi) return xi - 1;
	return xi;
}

int32_t Mth::intFloorDiv(int32_t x, int32_t y){
	if(x >= 0) return x / y;
	else return ~(~x / y);
}

float Mth::wrapDegrees(float f){
	float v1;
	float v2;

	v1 = fmodf(f, 360.0);
	v2 = v1;
	if(v1 >= 180.0) v2 = v1 - 360;
	if(v1 < -180.0) return v2 + 360;
	return v2;
}

uint32_t Mth::fastRandom(void){
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

float Mth::random(void){
	return Mth::_random.genrand_int32() * 2.32830644e-10;
}

uint32_t Mth::random(int32_t bound){
	return Mth::_random.genrand_int32() % bound;
}
float Mth::clampRotate(float f, float f1, float f2){
	float f3, f4, f5;

	f3 = fmodf(f1 - f, 360.0);
	f4 = f3;
	if(f3 >= 180.0) f4 = f3 - 360.0;
	if(f4 < -180.0) f4 = f4 + 360.0;

	f5 = -f2;
	if(f4 > f2) f4 = f2;
	if(f4 >= f5) f5 = f4;
	return f + f5;
}
float Mth::sqrt(float f){
	return ::sqrt(f);
}
float Mth::atan2(float x, float y){
	return ::atan2(x, y);
}
