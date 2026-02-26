#pragma once
#include <_types.h>
#include <vector>

struct ImageData{
	int32_t width;
	int32_t height;
	uint8_t* pixels;
UNK	int32_t field_C;
UNK	int32_t field_10;
	int32_t lod;
UNK uint8_t field_18;
UNK byte field_19;
UNK byte field_1A;
UNK byte field_1B;
	uint32_t glTexId;
	std::vector<ImageData> images;
};
