#include <util/Random.hpp>
#include <utils.h>
#include <math.h>

Random::Random(void){
	int32_t time;

	time = getTimeMs();
	this->setSeed(time); //XXX inlined in 0.8
}

Random::Random(int32_t seed){
	this->setSeed(seed); //XXX inlined in 0.8 ?
}

void Random::init_genrand(uint32_t seed){
	int32_t index;

	this->permutations[0] = seed;
	for(this->index = 1; this->index < 624; ++this->index) {
		this->permutations[this->index] = (0x6c078965 * (this->permutations[this->index-1] >> 30 ^ this->permutations[this->index - 1]) + this->index);
	}
}
float Random::nextFloat(void){
	return this->genrand_int32() * 2.32830644e-10;
}

float Random::nextGaussian(void){
	float v2, v3, v4, v5, v6, v7, v8, v9;

	if(this->haveNextNextGaussian){
		this->haveNextNextGaussian = 0;
		return this->nextNextGaussian;
	}

	do{
		do{
			v3 = this->nextFloat(); //XXX inlined
			v4 = (v3 + v3) - 1;
			v5 = this->nextFloat(); //XXX inlined
			v6 = (v5 + v5) - 1;
			v7 = (v6*v6) + (v4*v4);
		}while(v7 >= 1.0);
	}while(v7 == 0);

	v8 = logf(v6*v6 + v4*v4);
	v9 = sqrtf((v8 * -2) / v7);
	v2 = v4*v9;
	this->nextNextGaussian = v6*v9;
	this->haveNextNextGaussian = 1;

	return v2;
}
uint32_t Random::genrand_int32(void){
	static uint32_t mag01[] = {0, 0x9908B0DF};

	int32_t index;
	uint32_t kk, y;

	index = this->index;
	if(index > 623){
		if(index == 625) this->init_genrand(5489);
		for(kk = 0; kk < 227; ++kk){
			y = (this->permutations[kk] & 0x80000000) | (this->permutations[kk + 1] & 0x7fffffff);
			this->permutations[kk] = this->permutations[kk+397] ^ (y >> 1) ^ mag01[y & 0x1];
		}

		for(;kk < 623; ++kk){
			y = (this->permutations[kk] & 0x80000000) | (this->permutations[kk + 1] & 0x7fffffff);
			this->permutations[kk] = this->permutations[kk-227] ^ (y >> 1) ^ mag01[y & 0x1];
		}

		y = (this->permutations[623] & 0x80000000) | (this->permutations[0] & 0x7fffffff);
		this->permutations[623] = this->permutations[396] ^ (y >> 1) ^ mag01[y & 0x1];
		this->index = 0;
	}

	y = this->permutations[this->index];
	++this->index;
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680;
	y ^= (y << 15) & 0xefc60000;
	y ^= (y >> 18);
	return y;
}
void Random::setSeed(int64_t seed){
	this->seed = seed;
	this->index = 625;
	this->haveNextNextGaussian = 0;
	this->nextNextGaussian = 0;
	this->init_genrand(seed);
}
