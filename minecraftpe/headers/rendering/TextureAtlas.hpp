#pragma once
#include <_types.h>
#include <json/value.h>
#include <unordered_map>
#include <rendering/TextureUVCoordinateSet.hpp>
#include <string>

struct TextureAtlasTextureItem;
struct TextureAtlas{
	std::string path;
	std::unordered_map<std::string, TextureAtlasTextureItem> field_4;

	TextureAtlas(const std::string&);
	TextureUVCoordinateSet _parseJSON(const Json::Value&);
	TextureAtlasTextureItem* getTextureItem(const std::string&);
	void load(struct NinecraftApp*);
};
