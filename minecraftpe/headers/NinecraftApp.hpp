#pragma once
#include <Minecraft.hpp>
#include <vector>
#include <mutex>

struct NinecraftApp : Minecraft{
	static std::shared_ptr<TextureAtlas> _itemsTextureAtlas;
	static std::shared_ptr<TextureAtlas> _terrainTextureAtlas;
	static bool _hasInitedStatics;

	int8_t field_D48___;
	int8_t field_D49, field_D4A, field_D4B;
	int32_t field_D4C;
	int32_t field_D50;
	std::vector<bool> some_std_vec;
	std::mutex field_D64;

	NinecraftApp();
	std::shared_ptr<TextureAtlas> getTextureAtlas(TextureAtlasId);
	void handleBackNoReturn(void);
	void initGLStates();
	void restartServer();
	void updateStats();

	virtual ~NinecraftApp(void);
	virtual bool_t onLowMemory(void);
	virtual void onAppResumed(void);
	virtual void update(void);
	virtual bool_t handleBack(bool_t);
	virtual void handleBack(void);
	virtual void init(void);
	virtual void teardown(void);

};
