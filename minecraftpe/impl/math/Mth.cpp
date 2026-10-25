#include <math/Mth.hpp>
float Mth::_sin[65536]; //XXX initialized in NinecraftApp::init
const float Mth::PI = 3.1416f;
const float Mth::TAU = 6.2832f;
const float Mth::DEGRAD = 0.017453f;
const float Mth::RADDEG = 57.296f;
const float Mth::_sinScale = 10430.0;
static Random _random;

float Mth::random(void){
	return _random.genrand_int32() * 2.32830644e-10;
}

uint32_t Mth::random(int32_t bound){
	return _random.genrand_int32() % bound;
}
