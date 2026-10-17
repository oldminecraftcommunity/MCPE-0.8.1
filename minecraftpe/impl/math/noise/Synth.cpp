#include <math/noise/Synth.hpp>
Synth::~Synth() = default;

int32_t Synth::getDataSize(int32_t x, int32_t y){
	return x * y * 4;
}

void Synth::create(int32_t x, int32_t y, float* arr){
	for(int i = 0; i < y; ++i){
		for(int j = 0; j < x; ++j){
			arr[i*x + j] = this->getValue(j, i);
		}
	}
}

