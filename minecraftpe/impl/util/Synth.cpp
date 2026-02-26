#include <util/Synth.hpp>

void Synth::create(int32_t x, int32_t y, float* arr){
	int32_t v7;
	int32_t i;
	float v10, *v11;
	int32_t j;

	v7 = 4*x; //XXX ohno

	for(i = 0; i < y; ++i){
		for(j = 0; j < x; ++j){
			v10 = this->getValue(j, i);
			v11 = &arr[j];
			*v11 = v10;
		}

		arr = (float*)((void*)arr + v7);
	}
}

int32_t Synth::getDataSize(int32_t x, int32_t y){
	return x * y * 4; //TODO maybe needs *8?
}
