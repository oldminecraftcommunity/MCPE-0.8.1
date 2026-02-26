#pragma once
#include <ImageData.hpp>

struct TextureData : ImageData{
	TextureData(TextureData&&);
	TextureData();
};
