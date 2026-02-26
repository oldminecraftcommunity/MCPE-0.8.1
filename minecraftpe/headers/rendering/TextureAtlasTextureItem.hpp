#pragma once
#include <_types.h>
#include <rendering/TextureUVCoordinateSet.hpp>
#include <vector>
#include <string>

struct TextureAtlasTextureItem{
	std::string name;
	TextureUVCoordinateSet uvCoords;
	std::vector<TextureUVCoordinateSet> uv;
	int32_t uvCount;

	TextureAtlasTextureItem(const TextureAtlasTextureItem&);
	TextureAtlasTextureItem(TextureAtlasTextureItem&&);
	TextureAtlasTextureItem(const std::string&, const TextureUVCoordinateSet&, const std::vector<TextureUVCoordinateSet>&);
	TextureAtlasTextureItem(void);
	void getName(void);
	TextureUVCoordinateSet* getUV(int32_t);
	int32_t getUVCount(void);

	TextureAtlasTextureItem* operator=(const TextureAtlasTextureItem&);
	~TextureAtlasTextureItem();
};
