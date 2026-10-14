#pragma once
#include <rendering/TextureAtlasTextureItem.hpp>
#include <rendering/TextureUVCoordinateSet.hpp>
#include <json/value.h>
#include <unordered_map>
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
