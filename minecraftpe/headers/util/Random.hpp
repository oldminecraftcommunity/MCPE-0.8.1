#pragma once
#include <_types.h>
#include <math.h>
#include <cpputils.hpp>

struct Random{
	int32_t seed;
	uint32_t permutations[624];
	int32_t index;
	bool haveNextNextGaussian;
	float nextNextGaussian;

	Random(long seed){
		this->setSeed(seed);
	}
	Random(void){
		int32_t time;

		time = getTimeMs();
		this->setSeed(time); //XXX inlined in 0.8
	}

	void init_genrand(unsigned long seed){
		int32_t index;

		this->permutations[0] = seed;
		for(this->index = 1; this->index < 624; ++this->index) {
			this->permutations[this->index] = (0x6c078965 * (this->permutations[this->index-1] >> 30 ^ this->permutations[this->index - 1]) + this->index);
		}
	}
	float nextFloat(void){
		return this->genrand_int32() * 2.32830644e-10;
	}
	float nextGaussian(void){
		if(this->haveNextNextGaussian){
			this->haveNextNextGaussian = 0;
			return this->nextNextGaussian;
		}
		float v4, v6, v7;
		do{
			v4 = this->nextFloat()*2 - 1;
			v6 = this->nextFloat()*2 - 1;
			v7 = (v6*v6) + (v4*v4);
		}while(v7 >= 1 || v7 == 0);

		float v9 = sqrtf((logf(v7) * -2) / v7);
		this->nextNextGaussian = v6*v9;
		this->haveNextNextGaussian = 1;
		return v4*v9;
	}
	uint32_t genrand_int32(void){
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
	void setSeed(long seed){
		this->seed = seed;
		this->index = 625;
		this->haveNextNextGaussian = 0;
		this->nextNextGaussian = 0;
		this->init_genrand(seed);
	}
};
