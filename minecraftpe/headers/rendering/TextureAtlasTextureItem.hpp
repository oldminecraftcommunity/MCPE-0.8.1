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
	TextureAtlasTextureItem(const TextureAtlasTextureItem& a2) = default;
	TextureAtlasTextureItem(TextureAtlasTextureItem&& a2) = default;
	TextureAtlasTextureItem(const std::string&, const TextureUVCoordinateSet&, const std::vector<TextureUVCoordinateSet>&);
	TextureAtlasTextureItem(void);
	void getName(void) const;
	const TextureUVCoordinateSet* getUV(int32_t) const;
	int32_t getUVCount(void) const;

	TextureAtlasTextureItem* operator=(const TextureAtlasTextureItem & a2) {
		this->name = a2.name;
		this->uvCoords = a2.uvCoords;
		this->uv = a2.uv;
		this->uvCount = a2.uvCount;
		return this;
	}
	~TextureAtlasTextureItem() {
	}
};
