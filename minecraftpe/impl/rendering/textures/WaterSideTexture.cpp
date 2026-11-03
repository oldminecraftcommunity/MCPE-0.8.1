#include <rendering/textures/WaterSideTexture.hpp>
#include <math/Mth.hpp>
#include <tile/Tile.hpp>

WaterSideTexture::~WaterSideTexture() {
	if(this->field_34) delete[] this->field_34;
	if(this->field_38) delete[] this->field_38;
	if(this->field_3C) delete[] this->field_3C;
	if(this->field_40) delete[] this->field_40;
}
void WaterSideTexture::tick() {
	++this->field_30;
	for(int i = 0; i != 16; ++i) {
		for(int j = 0; j != 16; ++j) {
			float v4 = 0;
			for(int v3 = i-2; v3 != i+1; ++v3){
				int v5 = (v3 & 0xF);
				v4 += this->field_34[v5*16 + j];
			}
			int v6 = j + i*16;
			this->field_38[v6] = (v4 / 3.2f) + (this->field_3C[v6] * 0.8f);
		}
	}
	for(int k = 0; k != 256; k += 16) {
		for(int m = 0; m != 16; ++m) {
			int ind = m + k;
			this->field_3C[ind] += this->field_40[ind] * 0.05f;
			if(this->field_3C[ind] < 0) this->field_3C[ind] = 0;

			this->field_40[ind] -= 0.3f;
			if(Mth::fastRandom() <= 0x33333332) {
				this->field_40[ind] = 0.5f;
			}
		}
	}
	float* tmp = this->field_38;
	this->field_38 = this->field_34;
	this->field_34 = tmp;

	int v14 = 0;
	for(int v14 = 0; v14 != 256; ++v14){
		float v15 = this->field_34[(uint8_t)(v14 - 16 * this->field_30)];
		if(v15 > 1.0f) v15 = 1.0f;
		if(v15 < 0.0f) v15 = 0.0f;

		float v16 = v15 * v15;
		this->data[v14*4] = (int32_t)(v16 * 32 + 32);
		this->data[v14*4 + 1] = (int32_t)(v16 * 64 + 50);
		this->data[v14*4 + 2] = 0xff;
		this->data[v14*4 + 3] = (int32_t)(v16 * 50 + 146);
	}
}
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
