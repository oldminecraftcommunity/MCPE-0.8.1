#include <rendering/textures/FireTexture.hpp>
#include <tile/Tile.hpp>

FireTexture::FireTexture()
	: DynamicTexture(Tile::fire->textureUV, 1) {
	this->field_28 = new float[320];
	this->field_2C = new float[320];
	for(int32_t i = 0; i < 320; ++i) {
		this->field_28[i] = 0;
		this->field_2C[i] = 0;
	}
}

FireTexture::~FireTexture() {
	if(this->field_28) delete[] this->field_28;
	if(this->field_2C) delete[] this->field_2C;
}
void FireTexture::tick() {
	int32_t v2;	  // r5
	float v4;	  // s15
	int32_t i;	  // r3
	int32_t v6;	  // r0
	int32_t j;	  // r2
	uint32_t v8;  // r0
	int32_t v9;	  // r6
	int32_t v10;  // r7
	int32_t v11;  // r8
	int32_t v12;  // r1
	int32_t v13;  // r10
	float* v14;	  // r2
	uint32_t v15; // r3
	float v16;	  // s15
	int8_t v17;	  // r1
	uint8_t* v18; // r2

	v2 = 0;
	do {
		v11 = v2 + 1;
		v9 = 0;
		v12 = (v2 + 1) % 20;
		v10 = v12 << 6;
		v13 = (v2 - v12) << 6;
		do {
			v4 = this->field_28[v10 / 4] * 18.0;
			for(i = 0; i != 2; ++i) {
				v6 = v9 - 1;
				for(j = 0; j != 3; ++j) {
					if(v6 != -1 && v6 != 16 && i + v2 != 20) {
						v4 = v4 + this->field_28[16 * i - 1 + 16 * v2 + v9 + j];
					}
					++v6;
				}
			}
			this->field_2C[(v10 + v13) / 4] = v4 / 25.2;
			if(v2 == 19) {
				v8 = this->random.genrand_int32();
				this->field_2C[(v10 + v13) / 4] = (float)((float)((float)((float)((v8 >> 24) & 0xff) * 0.0039062) * 0.1) + (float)((float)((float)((float)((float)(v8 & 0xff) * 0.0039062) * (float)((float)((v8 >> 8) & 0xff) * 0.0039062)) * (float)((float)((v8 >> 16) & 0xff) * 0.0039062)) * 4.0)) + 0.2;
			}
			++v9;
			v10 += 4;
		} while(v9 != 16);
		++v2;
	} while(v11 != 20);
	v14 = this->field_2C;
	this->field_2C = this->field_28;
	v15 = 0;
	this->field_28 = v14;
	do {
		v16 = this->field_28[v15 / 4] * 1.8;
		if(v16 > 1.0) {
			v16 = 1.0;
		} else if(v16 < 0.0) {
			v16 = 0.0;
		}
		this->data[v15] = (int32_t)(float)((float)(v16 * 155.0) + 100.0);
		if(v16 >= 0.5) {
			v17 = -1;
		} else {
			v17 = 0;
		}
		this->data[v15 + 1] = (int32_t)(float)((float)(v16 * v16) * 255.0);
		this->data[v15 + 2] = (int32_t)(float)((float)((float)((float)((float)(v16 * v16) * (float)(v16 * v16)) * (float)((float)(v16 * v16) * (float)(v16 * v16))) * (float)(v16 * v16)) * 255.0);
		v18 = &this->data[v15];
		v15 += 4;
		v18[3] = v17;
	} while(v15 != 1024);
}
