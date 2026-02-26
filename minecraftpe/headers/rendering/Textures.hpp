#pragma once
#include <_types.h>
#include <map>
#include <string>
#include <rendering/textures/TextureData.hpp>

struct Textures{
	static int32_t textureChanges;

	std::map<std::string, TextureData> textures;
	struct Options* options;
	struct AppPlatform* platform;
	int32_t currentTexture;
	std::vector<struct DynamicTexture*> dynamicTextures;

	Textures(struct Options* options, struct AppPlatform* platform);
	void _loadTexImage(const ImageData&);
	void addDynamicTexture(struct DynamicTexture*);
	int32_t assignTexture(const std::string&, struct TextureData&, bool_t);
	void bind(uint32_t);
	void clear(bool_t);
	int32_t crispBlend(int32_t, int32_t);
	int32_t loadAndBindTexture(const std::string&);
	TextureData* loadAndGetTextureData(const std::string&);
	int32_t loadTexture(const std::string&, bool_t, bool_t);
	void reloadAll();
	int32_t smoothBlend(int32_t, int32_t);
	void tick(bool_t);
	~Textures();

};
