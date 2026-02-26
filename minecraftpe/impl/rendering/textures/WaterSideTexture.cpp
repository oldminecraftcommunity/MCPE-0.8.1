#include <rendering/textures/WaterSideTexture.hpp>
#include <math/Mth.hpp>
#include <tile/Tile.hpp>

WaterSideTexture::WaterSideTexture()
	: DynamicTexture(*Tile::water->getTexture(3), 2) {
	this->field_28 = 0;
	this->field_2C = 0;
	this->field_30 = 0;
	this->field_34 = new float[256];
	this->field_38 = new float[256];
	this->field_3C = new float[256];
	this->field_40 = new float[256];
	for(int32_t i = 0; i != 256; ++i) {
		this->field_34[i] = 0;
		this->field_38[i] = 0;
		this->field_3C[i] = 0;
		this->field_40[i] = 0;
	}
}

WaterSideTexture::~WaterSideTexture() {
	if(this->field_34) delete[] this->field_34;
	if(this->field_38) delete[] this->field_38;
	if(this->field_3C) delete[] this->field_3C;
	if(this->field_40) delete[] this->field_40;
}
void WaterSideTexture::tick() {
	int32_t i;	  // r3
	int32_t v3;	  // r1
	float v4;	  // s15
	int32_t v5;	  // r7
	int32_t v6;	  // r1
	int32_t j;	  // r2
	int32_t v8;	  // r5
	float* v9;	  // r3
	int32_t m;	  // r6
	int32_t k;	  // r7
	float* v12;	  // r3
	int32_t v13;  // r2
	int32_t v14;  // r3
	float v15;	  // s15
	float v16;	  // s15
	uint8_t* v17; // r1

	++this->field_30;
	for(i = 0; i != 16; ++i) {
		for(j = 0; j != 16; ++j) {
			v3 = i - 2;
			v4 = 0.0;
			while(v3 != i + 1) {
				v5 = v3++ & 0xF;
				v4 = v4 + this->field_34[16 * v5 + j];
			}
			v6 = j + 16 * i;
			this->field_38[v6] = (float)(v4 / 3.2) + (float)(this->field_3C[v6] * 0.8);
		}
	}
	for(k = 0; k != 256; k += 16) {
		for(m = 0; m != 16; ++m) {
			v8 = m * 4 + k * 4;
			this->field_3C[m + k] = this->field_3C[m + k] + (float)(this->field_40[m + k] * 0.05);
			v9 = &this->field_3C[m + k];
			if(*v9 < 0.0) {
				*v9 = 0.0;
			}
			this->field_40[v8 / 4] = this->field_40[v8 / 4] - 0.3;
			if(Mth::fastRandom() <= 0x33333332) {
				this->field_40[v8 / 4] = 0.5;
			}
		}
	}
	v12 = this->field_34;
	this->field_34 = this->field_38;
	v13 = 1;
	this->field_38 = v12;
	v14 = 0;
	do {
		v15 = this->field_34[(uint8_t)(v14 - 16 * this->field_30)];
		if(v15 > 1.0) {
			v15 = 1.0;
		} else if(v15 < 0.0) {
			v15 = 0.0;
		}
		v16 = v15 * v15;
		this->data[4 * v14++] = (int32_t)(float)((float)(v16 * 32.0) + 32.0);
		this->data[v13] = (int32_t)(float)((float)(v16 * 64.0) + 50.0);
		this->data[v13 + 1] = -1;
		v17 = &this->data[v13];
		v13 += 4;
		v17[2] = (int32_t)(float)((float)(v16 * 50.0) + 146.0);
	} while(v14 != 256);
}
