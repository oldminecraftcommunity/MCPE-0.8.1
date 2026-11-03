#include <rendering/textures/WaterTexture.hpp>
#include <tile/Tile.hpp>
#include <math/Mth.hpp>

WaterTexture::~WaterTexture() {
	if(this->field_30) delete[] this->field_30;
	if(this->field_34) delete[] this->field_34;
	if(this->field_38) delete[] this->field_38;
	if(this->field_3C) delete[] this->field_3C;
}
void WaterTexture::tick() {
	for(int i = 0; i != 16; ++i) {
		for(int j = 0; j != 16; ++j) {
			float v4 = 0;
			for(int v3 = j - 1; v3 != j + 2; ++v3) {
				int v5 = (v3 & 0xF) + i*16;
				v4 += this->field_30[v5];
			}

			int ind = j + i*16;
			this->field_34[ind] = (v4 / 3.3f) + (this->field_38[ind] * 0.8f);
		}
	}
	for(int i = 0; i != 16; ++i) {
		for(int j = 0; j != 16; ++j) {
			int ind = j + i * 16;
			this->field_38[ind] += this->field_3C[ind] * 0.05f;
			if(this->field_38[ind] < 0) this->field_38[ind] = 0;

			this->field_3C[ind] -= 0.1f;
			if(Mth::fastRandom() <= 0xCCCCCCC) {
				this->field_3C[ind] = 0.5f;
			}
		}
	}
	float* tmp = this->field_34;
	this->field_34 = this->field_30;
	this->field_30 = tmp;

	for(int v13 = 0; v13 != 256; ++v13){
		float v14 = this->field_30[v13];
		if(v14 > 1.0f) v14 = 1.0f;
		if(v14 < 0.0f) v14 = 0.0f;

		float v15 = v14 * v14;
		this->data[v13*4] = (int32_t)(v15 * 32 + 32);
		this->data[v13*4 + 1] = (int32_t)(v15 * 64 + 50);
		this->data[v13*4 + 2] = 0xff;
		this->data[v13*4 + 3] = (int32_t)(v15 * 50 + 146);
	}
}
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
