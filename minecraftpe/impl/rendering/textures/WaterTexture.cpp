#include <rendering/textures/WaterTexture.hpp>
#include <tile/Tile.hpp>
#include <math/Mth.hpp>


WaterTexture::WaterTexture(const TextureUVCoordinateSet& a2)
	: DynamicTexture(Tile::water->textureUV, 1) {
	this->field_28 = 0;
	this->field_2C = 0;
	this->field_30 = new float[256];
	this->field_34 = new float[256];
	this->field_38 = new float[256];
	this->field_3C = new float[256];
	for(int32_t i = 0; i != 256; ++i) {
		this->field_30[i] = 0;
		this->field_34[i] = 0;
		this->field_38[i] = 0;
		this->field_3C[i] = 0;
	}
}

WaterTexture::~WaterTexture() {
	if(this->field_30) delete[] this->field_30;
	if(this->field_34) delete[] this->field_34;
	if(this->field_38) delete[] this->field_38;
	if(this->field_3C) delete[] this->field_3C;
}
void WaterTexture::tick() {
	int32_t i;	  // r2
	int32_t v3;	  // r1
	float v4;	  // s15
	int32_t v5;	  // r6
	int32_t v6;	  // r1
	int32_t j;	  // r3
	int32_t v8;	  // r5
	float* v9;	  // r3
	int32_t m;	  // r6
	int32_t k;	  // r7
	float* v12;	  // r2
	uint32_t v13; // r3
	float v14;	  // s15
	float v15;	  // s15

	for(i = 0; i != 256; i += 16) {
		for(j = 0; j != 16; ++j) {
			v3 = j - 1;
			v4 = 0.0;
			while(v3 != j + 2) {
				v5 = (v3++ & 0xF) + i;
				v4 = v4 + this->field_30[v5];
			}
			v6 = j + i;
			this->field_34[v6] = (float)(v4 / 3.3) + (float)(this->field_38[v6] * 0.8);
		}
	}
	for(k = 0; k != 256; k += 16) {
		for(m = 0; m != 16; ++m) {
			v8 = m * 4 + k * 4;
			this->field_38[m + k] = this->field_38[m + k] + (float)(this->field_3C[m + k] * 0.05);
			v9 = &this->field_38[m + k];
			if(*v9 < 0.0) {
				*v9 = 0.0;
			}
			this->field_3C[v8 / 4] = this->field_3C[v8 / 4] - 0.1;
			//*(float *)((char *)this->field_3C + v8) = *(float *)((char *)this->field_3C + v8) - 0.1;
			if(Mth::fastRandom() <= 0xCCCCCCC) {
				this->field_3C[v8 / 4] = 0.5;
				//*(float *)((char *)this->field_3C + v8) = 0.5;
			}
		}
	}
	v12 = this->field_34;
	this->field_34 = this->field_30;
	v13 = 0;
	this->field_30 = v12;
	do {
		v14 = this->field_30[v13 / 4];
		if(v14 > 1.0) {
			v14 = 1.0;
		} else if(v14 < 0.0) {
			v14 = 0.0;
		}
		v15 = v14 * v14;
		this->data[v13] = (int32_t)(float)((float)(v15 * 32.0) + 32.0);
		this->data[v13 + 1] = (int32_t)(float)((float)(v15 * 64.0) + 50.0);
		this->data[v13 + 2] = -1;
		this->data[v13 + 3] = (int32_t)(float)((float)(v15 * 50.0) + 146.0);
		v13 += 4;
	} while(v13 != 1024);
}
