#pragma once
#include <AppPlatform.hpp>
#include <SDL/SDL.h>

struct AppPlatform_sdl : AppPlatform{

	int32_t screenWidth, screenHeight;
	bool_t hasContext;
	SDL_Surface* sdl_surface;
	SDL_Event sdl_event;

	virtual std::string getImagePath(const std::string&, bool_t);
	virtual void loadPNG(ImageData&, const std::string&, bool_t);
	virtual AssetFile readAssetFile(const std::string& path);

	AppPlatform_sdl();
	~AppPlatform_sdl();
	SDL_Surface* setSDLVideoMode();
	bool_t sdlCtxInit();
	void sdlCtxDestroy();
	void init();
	void onKeyPressed(struct Minecraft*, SDLKey key, bool pressed);
};
