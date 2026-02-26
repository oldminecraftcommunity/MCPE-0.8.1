#include <rendering/textures/LavaTexture.hpp>
#include <tile/Tile.hpp>
#include <math/Mth.hpp>

LavaTexture::LavaTexture()
	: DynamicTexture(Tile::lava->textureUV, 1) {
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

LavaTexture::~LavaTexture() {
	if(this->field_30) delete[] this->field_30;
	if(this->field_34) delete[] this->field_34;
	if(this->field_38) delete[] this->field_38;
	if(this->field_3C) delete[] this->field_3C;
}
void LavaTexture::tick() {
	int32_t v1;	  // r7
	int32_t v3;	  // r3
	float v4;	  // s21
	float v5;	  // r0
	int32_t v6;	  // s21
	int32_t v7;	  // r2
	float v8;	  // s15
	int32_t i;	  // r1
	int32_t v10;  // r11
	int32_t v11;  // r6
	float* v12;	  // r2
	float* v13;	  // r3
	int32_t v14;  // r5
	int32_t v15;  // r8
	int32_t v16;  // r9
	float v17;	  // s19
	float* v18;	  // r2
	int32_t v19;  // r3
	float v20;	  // s15
	uint8_t* v21; // r2

	v1 = 0;
	v3 = 0;
	do {
		v15 = v3 + 1;
		v14 = v1;
		v11 = 0;
		v16 = 16 * ((v3 + 1) & 0xF);
		v17 = (float)((float)((float)v3 * 3.1416) + (float)((float)v3 * 3.1416)) * 0.0625;
		do {
			v4 = Mth::sin(v17) * 1.2;
			v5 = Mth::sin((float)((float)((float)v11 * 3.1416) + (float)((float)v11 * 3.1416)) * 0.0625);
			v6 = (int32_t)v4;
			v7 = v15 - 2;
			v8 = 0.0;
			while(v7 != v15 + 1) {
				for(i = v11 - 1; i != v11 + 2; ++i) {
					v10 = ((int8_t)i + (int8_t)v6) & 0xF;
					v8 = v8 + this->field_30[16 * (((int8_t)v7 + (uint8_t)(int32_t)(float)(v5 * 1.2)) & 0xF) + v10];
				}
				++v7;
			}
			++v11;
			v12 = this->field_38;
			this->field_34[v14] = (float)(v8 / 10.0) + (float)((float)((float)((float)((float)(v12[v14] + v12[(v11 & 0xF) + v1]) + v12[(v11 & 0xF) + v16]) + v12[v14 + v16 - v1]) * 0.25) * 0.8);
			this->field_38[v14] = this->field_38[v14] + (float)(this->field_3C[v14] * 0.01);
			v13 = &this->field_38[v14];
			if(*v13 < 0.0) {
				*v13 = 0.0;
			}
			this->field_3C[v14] = this->field_3C[v14] - 0.06;
			if(Mth::fastRandom() <= 0x147AE14) {
				this->field_3C[v14] = 1.5;
			}
			++v14;
		} while(v11 != 16);
		v3 = v15;
		v1 += 16;
	} while(v15 != 16);
	v18 = this->field_34;
	this->field_34 = this->field_30;
	v19 = 0;
	this->field_30 = v18;
	do {
		v20 = this->field_30[v19] + this->field_30[v19];
		if(v20 > 1.0) {
			v20 = 1.0;
		} else if(v20 < 0.0) {
			v20 = 0.0;
		}
		this->data[v19 * 4] = (int32_t)(float)((float)(v20 * 100.0) + 155.0);
		this->data[v19 * 4 + 1] = (int32_t)(float)((float)(v20 * v20) * 255.0);
		this->data[v19 * 4 + 2] = (int32_t)(float)((float)((float)((float)(v20 * v20) * v20) * v20) * 128.0);
		v21 = &this->data[v19 * 4];
		++v19;
		v21[3] = -1;
	} while(v19 != 256);
}
