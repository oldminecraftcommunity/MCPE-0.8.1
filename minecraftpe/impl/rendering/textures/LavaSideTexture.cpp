#include <rendering/textures/LavaSideTexture.hpp>
#include <math/Mth.hpp>

LavaSideTexture::LavaSideTexture(const TextureUVCoordinateSet& a2)
	: DynamicTexture(a2, 2) {
	this->field_28 = 0;
	this->field_2C = 0;
	this->field_30 = 0;
	this->field_34 = new float[256];
	this->field_38 = new float[256];
	this->field_3C = new float[256];
	this->field_40 = new float[256];
	for(int32_t i = 0; i != 256; ++i){
		this->field_34[i] = 0.0;
		this->field_38[i] = 0.0;
		this->field_3C[i] = 0.0;
		this->field_40[i] = 0.0;
	}
}

LavaSideTexture::~LavaSideTexture() {
	if(this->field_34) delete[] this->field_34;
	if(this->field_38) delete[] this->field_38;
	if(this->field_3C) delete[] this->field_3C;
	if(this->field_40) delete[] this->field_40;
}
void LavaSideTexture::tick(){
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
	float* v18;	  // r3
	int32_t v19;  // r6
	int32_t v20;  // r5
	float* v21;	  // r3
	float v22;	  // s15
	uint8_t* v23; // r3

	v1 = 0;
	++this->field_30;
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
					v8 = v8 + this->field_34[16 * (((int8_t)v7 + (uint8_t)(int32_t)(float)(v5 * 1.2)) & 0xF) + v10];
				}
				++v7;
			}
			++v11;
			v12 = this->field_3C;
			this->field_38[v14] = (float)(v8 / 10.0) + (float)((float)((float)((float)((float)(v12[v14] + v12[(v11 & 0xF) + v1]) + v12[(v11 & 0xF) + v16]) + v12[v14 + v16 - v1]) * 0.25) * 0.8);
			this->field_3C[v14] = this->field_3C[v14] + (float)(this->field_40[v14] * 0.01);
			v13 = &this->field_3C[v14];
			if(*v13 < 0.0) {
				*v13 = 0.0;
			}
			this->field_40[v14] = this->field_40[v14] - 0.06;
			if(Mth::fastRandom() <= 0x147AE14) {
				this->field_40[v14] = 1.5;
			}
			++v14;
		} while(v11 != 16);
		v3 = v15;
		v1 += 16;
	} while(v15 != 16);
	v18 = this->field_34;
	v19 = 1;
	v20 = 0;
	this->field_34 = this->field_38;
	this->field_38 = v18;
	do {
		v21 = &this->field_34[(uint8_t)(v20 + 16 * (this->field_30 / -3))];
		v22 = *v21 + *v21;
		if(v22 > 1.0) {
			v22 = 1.0;
		} else if(v22 < 0.0) {
			v22 = 0.0;
		}
		this->data[4 * v20++] = (int32_t)(float)((float)(v22 * 100.0) + 155.0);
		this->data[v19] = (int32_t)(float)((float)(v22 * v22) * 255.0);
		this->data[v19 + 1] = (int32_t)(float)((float)((float)((float)(v22 * v22) * v22) * v22) * 128.0);
		v23 = &this->data[v19];
		v19 += 4;
		v23[2] = -1;
	} while(v20 != 256);
}
