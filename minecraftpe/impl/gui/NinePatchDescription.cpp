#include <gui/NinePatchDescription.hpp>
#include <util/IntRectangle.hpp>
#include <rendering/textures/TextureData.hpp>

NinePatchDescription::NinePatchDescription(float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11, float a12, float a13){
	this->field_0 = a2;
	this->field_4 = a2+a4;
	this->field_8 = a2+a5;
	this->field_C = a2+a6;

	this->field_10 = a3;
	this->field_20 = a10;
	this->field_24 = a11;
	this->field_28 = a12;
	this->field_14 = a3+a7;
	this->field_2C = a13;
	this->width = -1;
	this->height = -1;
	this->field_18 = a3+a8;
	this->field_1C = a3+a9;

}

NinePatchDescription NinePatchDescription::createSymmetrical(int32_t a2, int32_t a3, const IntRectangle& a4, int32_t a5, int32_t a6){
	NinePatchDescription ret(a4.minX, a4.minY, a5, a4.width-a5, a4.width, a6, a4.height-a6, a4.height, a5, a5, a6, a6);
	if(a2 > 0) ret.transformUVForImageSize(a2, a3);
	return ret;
}

void NinePatchDescription::transformUVForImage(const TextureData& texture){
	this->transformUVForImageSize(texture.width, texture.height);
}

void NinePatchDescription::transformUVForImageSize(int32_t w, int32_t h){
	if(this->width < 0){
		this->height = 1;
		this->width = 1;
	}

	float width = this->width;
	this->width = (float)w;
	float v4 = width/(float)w;
	int32_t height = this->height;
	float v6 = (float)height/(float)h;
	this->field_0 *= v4;
	this->field_4 *= v4;
	this->field_8 *= v4;
	this->field_C *= v4;

	this->field_10 *= v6;
	this->field_14 *= v6;
	this->field_18 *= v6;
	this->field_1C *= v6;
}

