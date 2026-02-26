#pragma once
#include <_types.h>
#include <string>

struct NinePatchFactory{
	struct Textures* textures;
	std::string imagePath;
	int32_t width, height;

	NinePatchFactory(struct Textures*, const std::string&);
	struct NinePatchLayer* createSymmetrical(const struct IntRectangle&, int32_t, int32_t, float, float);
};
