#pragma once
#include <ImageData.hpp>
#include <vector>

struct TextureData
{
	ImageData image;
	uint8_t field_18;
	uint32_t glTexId;
	std::vector<ImageData> images;

	TextureData() : image(), field_18(0), glTexId(0), images(){
	}
};
