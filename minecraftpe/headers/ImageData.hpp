#pragma once
#include <_types.h>

struct ImageData{
	int32_t width;
	int32_t height;
	uint8_t* pixels;
UNK	int32_t field_C;
UNK	int32_t field_10;
	int32_t lod;

	ImageData()
		: width(0)
		, height(0)
		, pixels(0)
		, field_C(0)
		, field_10(0)
		, lod(0) {
	}
};
