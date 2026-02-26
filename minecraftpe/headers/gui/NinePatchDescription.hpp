#pragma once
#include <_types.h>

struct NinePatchDescription{
	float field_0, field_4, field_8;
	float field_C, field_10, field_14;
	float field_18, field_1C, field_20;
	float field_24, field_28, field_2C;
	int32_t width, height;

	NinePatchDescription(float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11, float a12, float a13);
	static NinePatchDescription createSymmetrical(int32_t, int32_t, const struct IntRectangle&, int32_t, int32_t);
	void transformUVForImage(const struct TextureData& texture);
	void transformUVForImageSize(int32_t, int32_t);
};
