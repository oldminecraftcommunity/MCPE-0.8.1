#ifndef ANDROID
#include <AppPlatform_sdl.hpp>
#include <_AssetFile.hpp>
#include <NinecraftApp.hpp>
#include <main.hpp>
#include <rendering/Tesselator.hpp>
#include <stb_image.h>
#include <rendering/Textures.hpp>
#include <rendering/Font.hpp>
#include <cpputils.hpp>
#include <input/Mouse.hpp>
#include <input/Keyboard.hpp>
#include <entity/LocalPlayer.hpp>
#include <inventory/Inventory.hpp>
#include <input/KeyboardInput.hpp>
#include <network/mco/LoginInformation.hpp>

#ifdef USEGLES
#include <GLES/glext.h>
#else

#endif
#ifdef __WIN32__
#include <sound/SoundSystemDirectSound.hpp>
#endif
std::string AppPlatform_sdl::getImagePath(const std::string& name, bool_t t){
	return "assets/images/"+name;
}

AssetFile AppPlatform_sdl::readAssetFile(const std::string& path){
	return AppPlatform::readAssetFile("assets/"+path);
}

void AppPlatform_sdl::loadPNG(ImageData& data, const std::string& path, bool_t t){
	//android uses jni to do it
	int32_t channels;

	uint8_t* pixels = stbi_load(path.c_str(), &data.width, &data.height, &channels, STBI_rgb_alpha);
	if(!pixels){
		printf("failed to load %s.\n", path.c_str());
		return;
	}

	printf("%d channels\n", channels);
	data.field_C = 0; //force rgba channels == 3;
	data.pixels = pixels;
}

SDL_Surface* AppPlatform_sdl::setSDLVideoMode() {
	return SDL_SetVideoMode(
		this->screenWidth, this->screenHeight,
		32, SDL_OPENGL | SDL_RESIZABLE
	);
}

#include <sound/SoundDesc.hpp>
#include <sounddata.hpp>
#include <pcm_data.h>
void loadSound(char* name, char_t** bufptr, SoundDesc* desc) {
	SDL_AudioSpec wav_spec;
	Uint32 wav_length;
	Uint8* wav_buffer;
	if(!SDL_LoadWAV((std::string("sounds/") + name + ".wav").c_str(), &wav_spec, &wav_buffer, &wav_length)) {
		printf("Failed to load %s: %s\n", name, SDL_GetError());
		return;
	}

	int bps = wav_spec.format == AUDIO_U8 || wav_spec.format == AUDIO_S8 ? 1 : 2;
	*bufptr = (char_t*)malloc(wav_length + sizeof(int32_t) * 4);
	((int*)*bufptr)[0] = wav_spec.channels;
	((int*)*bufptr)[1] = bps;
	((int*)*bufptr)[2] = wav_spec.freq;
	((int*)*bufptr)[3] = wav_length / bps / wav_spec.channels;
	memcpy(*bufptr + 16, wav_buffer, wav_length);
	*desc = SoundDesc(*bufptr);
	SDL_FreeWAV(wav_buffer);
}
bool_t AppPlatform_sdl::sdlCtxInit(){
	if(this->hasContext) return 1;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Minecraft PE 0.8.1", 0);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_EnableUNICODE(1);
	this->sdl_surface = this->setSDLVideoMode();
	if(!this->sdl_surface){
		return 0;
	}

#ifndef USEGLES
	initGlFuncs();
#endif

#ifdef PCTWEAKS
	int maxTextureLevel, anisotropicFilter;

	const char_t* str = (const char_t*)glGetString(GL_EXTENSIONS);
	std::string exts = str ? str : "";
	 //opengl (non es) doesnt seem to require ext for it
#ifdef USEGLES
	maxTextureLevel = GL_TEXTURE_MAX_LEVEL_APPLE;
#else
	maxTextureLevel = GL_TEXTURE_MAX_LEVEL;
#endif
	AppPlatform::TEXTURE_MAX_LEVEL = maxTextureLevel;
	if(exts.find("GL_EXT_texture_filter_anisotropic", 0) == -1) anisotropicFilter = 0;
	else anisotropicFilter = GL_EXT_texture_filter_anisotropic;
	AppPlatform::ANISOTROPIC_MAX_LEVEL = anisotropicFilter;
	if(anisotropicFilter) glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &AppPlatform::ANISOTROPIC_MAX_LEVEL);
#endif

	return 1;
}

bool fullscreen = 0;
int lastWidth = 0, lastHeight = 0;
void AppPlatform_sdl::onKeyPressed(Minecraft* mc, SDLKey key, bool pressed) {
	int k = 0;
	if(key == SDLK_w) k = mc->options.keyForward.keyCode;
	if(key == SDLK_s) k = mc->options.keyBack.keyCode;
	if(key == SDLK_a) k = mc->options.keyLeft.keyCode;
	if(key == SDLK_d) k = mc->options.keyRight.keyCode;
	if(key == SDLK_SPACE) k = mc->options.keyJump.keyCode;
	if(key == SDLK_F11) {
		if(pressed) {
			fullscreen = !fullscreen;
			if(fullscreen) {
				lastWidth = this->screenWidth;
				lastHeight = this->screenHeight;
				this->screenWidth = 0;
				this->screenHeight = 0;
				this->sdl_surface = this->setSDLVideoMode();
				this->screenWidth = SDL_GetVideoInfo()->current_w;
				this->screenHeight = SDL_GetVideoInfo()->current_h;
				mc->setSize(this->screenWidth, this->screenHeight);
			} else {
				this->screenWidth = lastWidth;
				this->screenHeight = lastHeight;
				lastWidth = 0;
				lastHeight = 0;
				mc->setSize(this->screenWidth, this->screenHeight);
			}
			SDL_WM_ToggleFullScreen(this->sdl_surface);
		}
	}
	if(key == SDLK_F5 && mc->player && !mc->currentScreen && mc->mouseGrabbed) {
		if(pressed) {
			mc->options.toggle(&Options::Option::THIRD_PERSON, 0);

		}
	}
	if(key == SDLK_ESCAPE) {
		if(pressed) mc->handleBack(0);
		return;
	}
	if(key == SDLK_e) k = 100;
	if(key == SDLK_t && mc->mouseGrabbed) {
		mc->screenChooser.setScreen(CHAT_SCREEN);
		return;
	}
	if(key == SDLK_q && mc->mouseGrabbed) {
		mc->player->inventory->dropSlot(mc->player->inventory->selectedSlot, 0, 0);
		return;
	}

	if(key == SDLK_BACKSPACE) k = 8;
	if(key == SDLK_RETURN) k = 13;
	if(key == SDLK_LSHIFT) {
		if(mc->player && !mc->currentScreen) {
			mc->player->moveInput->sneakingMaybe = pressed;
		}
	}
	if(key >= SDLK_1 && key <= SDLK_8) {
		if(mc->player && !mc->currentScreen) {
			mc->player->inventory->selectSlot(key - SDLK_1);
		}
	}

	if(k) {
		Keyboard::feed(k, pressed);
	}

}

bool AppPlatform_sdl::supportsTouchscreen() {
	return 0;
}

#include <util/Util.hpp>
#include <unistd.h>
MeshBuffer cube;
void AppPlatform_sdl::init(){
	this->screenWidth = 854;
	this->screenHeight = 480;
	AppContext ctx;

#ifdef DYNAMICSOUNDS
	loadSound("fuse", &PCM_fuse, &SA_fuse);
	loadSound("eat3", &PCM_eat3, &SA_eat3);
	loadSound("eat2", &PCM_eat2, &SA_eat2);
	loadSound("eat1", &PCM_eat1, &SA_eat1);
	loadSound("creeperdeath", &PCM_creeperdeath, &SA_creeperdeath);
	loadSound("creeper4", &PCM_creeper4, &SA_creeper4);
	loadSound("creeper3", &PCM_creeper3, &SA_creeper3);
	loadSound("creeper2", &PCM_creeper2, &SA_creeper2);
	loadSound("creeper1", &PCM_creeper1, &SA_creeper1);
	loadSound("spiderdeath", &PCM_spiderdeath, &SA_spiderdeath);
	loadSound("spider4", &PCM_spider4, &SA_spider4);
	loadSound("spider3", &PCM_spider3, &SA_spider3);
	loadSound("spider2", &PCM_spider2, &SA_spider2);
	loadSound("spider1", &PCM_spider1, &SA_spider1);
	loadSound("skeletonhurt4", &PCM_skeletonhurt4, &SA_skeletonhurt4);
	loadSound("skeletonhurt3", &PCM_skeletonhurt3, &SA_skeletonhurt3);
	loadSound("skeletonhurt2", &PCM_skeletonhurt2, &SA_skeletonhurt2);
	loadSound("skeletonhurt1", &PCM_skeletonhurt1, &SA_skeletonhurt1);
	loadSound("skeletondeath", &PCM_skeletondeath, &SA_skeletondeath);
	loadSound("skeleton3", &PCM_skeleton3, &SA_skeleton3);
	loadSound("skeleton2", &PCM_skeleton2, &SA_skeleton2);
	loadSound("skeleton1", &PCM_skeleton1, &SA_skeleton1);
	loadSound("fallsmall", &PCM_fallsmall, &SA_fallsmall);
	loadSound("fallbig2", &PCM_fallbig2, &SA_fallbig2);
	loadSound("fallbig1", &PCM_fallbig1, &SA_fallbig1);
	loadSound("bowhit4", &PCM_bowhit4, &SA_bowhit4);
	loadSound("bowhit3", &PCM_bowhit3, &SA_bowhit3);
	loadSound("bowhit2", &PCM_bowhit2, &SA_bowhit2);
	loadSound("bowhit1", &PCM_bowhit1, &SA_bowhit1);
	loadSound("bow", &PCM_bow, &SA_bow);
	loadSound("zpighurt2", &PCM_zpighurt2, &SA_zpighurt2);
	loadSound("zpighurt1", &PCM_zpighurt1, &SA_zpighurt1);
	loadSound("zpigdeath", &PCM_zpigdeath, &SA_zpigdeath);
	loadSound("zpigangry4", &PCM_zpigangry4, &SA_zpigangry4);
	loadSound("zpigangry3", &PCM_zpigangry3, &SA_zpigangry3);
	loadSound("zpigangry2", &PCM_zpigangry2, &SA_zpigangry2);
	loadSound("zpigangry1", &PCM_zpigangry1, &SA_zpigangry1);
	loadSound("zpig4", &PCM_zpig4, &SA_zpig4);
	loadSound("zpig3", &PCM_zpig3, &SA_zpig3);
	loadSound("zpig2", &PCM_zpig2, &SA_zpig2);
	loadSound("zpig1", &PCM_zpig1, &SA_zpig1);
	loadSound("zombiehurt2", &PCM_zombiehurt2, &SA_zombiehurt2);
	loadSound("zombiehurt1", &PCM_zombiehurt1, &SA_zombiehurt1);
	loadSound("zombiedeath", &PCM_zombiedeath, &SA_zombiedeath);
	loadSound("zombie3", &PCM_zombie3, &SA_zombie3);
	loadSound("zombie2", &PCM_zombie2, &SA_zombie2);
	loadSound("zombie1", &PCM_zombie1, &SA_zombie1);
	loadSound("cowhurt3", &PCM_cowhurt3, &SA_cowhurt3);
	loadSound("cowhurt2", &PCM_cowhurt2, &SA_cowhurt2);
	loadSound("cowhurt1", &PCM_cowhurt1, &SA_cowhurt1);
	loadSound("cow4", &PCM_cow4, &SA_cow4);
	loadSound("cow3", &PCM_cow3, &SA_cow3);
	loadSound("cow2", &PCM_cow2, &SA_cow2);
	loadSound("cow1", &PCM_cow1, &SA_cow1);
	loadSound("chickenhurt2", &PCM_chickenhurt2, &SA_chickenhurt2);
	loadSound("chickenhurt1", &PCM_chickenhurt1, &SA_chickenhurt1);
	loadSound("chicken3", &PCM_chicken3, &SA_chicken3);
	loadSound("chicken2", &PCM_chicken2, &SA_chicken2);
	loadSound("pigdeath", &PCM_pigdeath, &SA_pigdeath);
	loadSound("pig3", &PCM_pig3, &SA_pig3);
	loadSound("pig2", &PCM_pig2, &SA_pig2);
	loadSound("pig1", &PCM_pig1, &SA_pig1);
	loadSound("sheep3", &PCM_sheep3, &SA_sheep3);
	loadSound("sheep2", &PCM_sheep2, &SA_sheep2);
	loadSound("sheep1", &PCM_sheep1, &SA_sheep1);
	loadSound("ignite", &PCM_ignite, &SA_ignite);
	loadSound("fire", &PCM_fire, &SA_fire);
	loadSound("burp", &PCM_burp, &SA_burp);
	loadSound("break", &PCM_break, &SA_break);
	loadSound("glass3", &PCM_glass3, &SA_glass3);
	loadSound("glass2", &PCM_glass2, &SA_glass2);
	loadSound("glass1", &PCM_glass1, &SA_glass1);
	loadSound("chestopen", &PCM_chestopen, &SA_chestopen);
	loadSound("chestclosed", &PCM_chestclosed, &SA_chestclosed);
	loadSound("door_close", &PCM_door_close, &SA_door_close);
	loadSound("door_open", &PCM_door_open, &SA_door_open);
	loadSound("hurt", &PCM_hurt, &SA_hurt);
	loadSound("pop2", &PCM_pop2, &SA_pop2);
	loadSound("pop", &PCM_pop, &SA_pop);
	loadSound("splash", &PCM_splash, &SA_splash);
	loadSound("explode", &PCM_explode, &SA_explode);
	loadSound("click", &PCM_click, &SA_click);
	loadSound("wood4", &PCM_wood4, &SA_wood4);
	loadSound("wood3", &PCM_wood3, &SA_wood3);
	loadSound("wood2", &PCM_wood2, &SA_wood2);
	loadSound("wood1", &PCM_wood1, &SA_wood1);
	loadSound("stone4", &PCM_stone4, &SA_stone4);
	loadSound("stone3", &PCM_stone3, &SA_stone3);
	loadSound("stone2", &PCM_stone2, &SA_stone2);
	loadSound("stone1", &PCM_stone1, &SA_stone1);
	loadSound("sand4", &PCM_sand4, &SA_sand4);
	loadSound("sand3", &PCM_sand3, &SA_sand3);
	loadSound("sand2", &PCM_sand2, &SA_sand2);
	loadSound("sand1", &PCM_sand1, &SA_sand1);
	loadSound("gravel4", &PCM_gravel4, &SA_gravel4);
	loadSound("gravel3", &PCM_gravel3, &SA_gravel3);
	loadSound("gravel2", &PCM_gravel2, &SA_gravel2);
	loadSound("gravel1", &PCM_gravel1, &SA_gravel1);
	loadSound("grass4", &PCM_grass4, &SA_grass4);
	loadSound("grass3", &PCM_grass3, &SA_grass3);
	loadSound("grass2", &PCM_grass2, &SA_grass2);
	loadSound("grass1", &PCM_grass1, &SA_grass1);
	loadSound("cloth4", &PCM_cloth4, &SA_cloth4);
	loadSound("cloth3", &PCM_cloth3, &SA_cloth3);
	loadSound("cloth2", &PCM_cloth2, &SA_cloth2);
	loadSound("cloth1", &PCM_cloth1, &SA_cloth1);
#endif

	NinecraftApp* mc = new NinecraftApp();
	this->hasContext = this->sdlCtxInit();
#ifdef __WIN32__
	((SoundSystemDirectSound*)mc->soundEngine)->init();
#endif
	ctx.platform = this;
	mc->context = ctx;
	char curdir[256];
	getcwd(curdir, 256);
	mc->dataPathMaybe = curdir;
	printf("dir: %s\n", curdir);
	bool_t running = this->hasContext;
	bool_t hasInit = 0;
	Tesselator& tess = Tesselator::instance;
	static const int lbkey = 102;
	static const int rbkey = 103;
	bool windowActive = 1;
	unsigned int lastBuiltTick = 0;
	uint16_t lastMX, lastMY;
	bool prevMGrabbed = 0;
	while(running){

		if(!hasInit){
			hasInit = 1;
			mc->init();
			mc->setSize(this->screenWidth, this->screenHeight);
			//mc->currentScreen->init(mc, this->screenWidth, this->screenHeight);
		}

		if(mc->mouseGrabbed && !mc->useTouchscreen()) {
			SDL_WM_GrabInput(SDL_GRAB_ON);
			SDL_ShowCursor(SDL_DISABLE);
		} else {
			SDL_WM_GrabInput(SDL_GRAB_OFF);
			SDL_ShowCursor(SDL_ENABLE);
		}


		bool justGrabbed = mc->mouseGrabbed && !prevMGrabbed;
		if(windowActive && !mc->mouseGrabbed && prevMGrabbed) {
			SDL_WarpMouse(this->screenWidth / 2, this->screenHeight / 2);
		}

		prevMGrabbed = mc->mouseGrabbed;


		while(SDL_PollEvent(&appPlatform.sdl_event)){
			uint16_t _mx, _my;
			switch(appPlatform.sdl_event.type) {
				case SDL_ACTIVEEVENT:
					//wine sends 6 when focus is received for some reason
					//(and 2(SDL_APPINPUTFOCUS) when lost)
					if(appPlatform.sdl_event.active.state == 6 || appPlatform.sdl_event.active.state == SDL_APPINPUTFOCUS) {
						windowActive = appPlatform.sdl_event.active.gain;
						if(!windowActive && !mc->currentScreen) {
							mc->pauseGame(1);
						}
					}
					break;
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_VIDEORESIZE:
					this->screenWidth = appPlatform.sdl_event.resize.w;
					this->screenHeight = appPlatform.sdl_event.resize.h;
					this->sdl_surface = this->setSDLVideoMode();
					if(!this->sdl_surface) {
						printf("setSDLVideoModel: returned 0 after resize! Force quitting\n");
						running = 0;
						break;
					}
					mc->setSize(this->screenWidth, this->screenHeight);
					break;
				case SDL_MOUSEMOTION:
#ifdef __WIN32__
					if(justGrabbed) break; //ignore first mouse motion even after grab
#endif
					if(!windowActive) break;
					_mx = appPlatform.sdl_event.motion.x;
					_my = appPlatform.sdl_event.motion.y;
					Mouse::feed(0, 0, _mx, _my,appPlatform.sdl_event.motion.xrel, appPlatform.sdl_event.motion.yrel);
					break;
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					if(!windowActive) break;
					_mx = appPlatform.sdl_event.button.x;
					_my = appPlatform.sdl_event.button.y;

					if(mc->mouseGrabbed && (appPlatform.sdl_event.button.button == SDL_BUTTON_LEFT || appPlatform.sdl_event.button.button == SDL_BUTTON_RIGHT)) {
						int key = 0;
						if(appPlatform.sdl_event.button.button == SDL_BUTTON_LEFT) {
							key = lbkey;
						}
						if(appPlatform.sdl_event.button.button == SDL_BUTTON_RIGHT) {
							key = rbkey;
						}

						if(key && appPlatform.sdl_event.type == SDL_MOUSEBUTTONDOWN && !Keyboard::_states[key]){
							Keyboard::feed(key, 1);
						}else if(key && appPlatform.sdl_event.type == SDL_MOUSEBUTTONUP && Keyboard::_states[key]){
							Keyboard::feed(key, 0);
						}
					} else if(appPlatform.sdl_event.type == SDL_MOUSEBUTTONDOWN && (appPlatform.sdl_event.button.button == SDL_BUTTON_WHEELUP || appPlatform.sdl_event.button.button == SDL_BUTTON_WHEELDOWN)) {
						int off = appPlatform.sdl_event.button.button == SDL_BUTTON_WHEELDOWN ? 1 : -1;
						if(mc->player && !mc->currentScreen) {
							int newslot = mc->player->inventory->selectedSlot + off;
							if(newslot < 0) newslot = mc->gui.getNumSlots() - 2; //TODO one of the slots is used by inv button
							if(newslot >= mc->gui.getNumSlots()-1) newslot = 0;
							mc->player->inventory->selectSlot(newslot);
						}
					} else if(appPlatform.sdl_event.button.button == SDL_BUTTON_LEFT || appPlatform.sdl_event.button.button == SDL_BUTTON_RIGHT){
						Mouse::feed(appPlatform.sdl_event.button.button == SDL_BUTTON_LEFT ? 1 : 2, appPlatform.sdl_event.type == SDL_MOUSEBUTTONDOWN, _mx, _my);
					}
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					if(!windowActive) break;
					if(this->keyboardShown && appPlatform.sdl_event.key.keysym.unicode && appPlatform.sdl_event.key.keysym.sym != SDLK_BACKSPACE && appPlatform.sdl_event.key.keysym.sym != SDLK_RETURN && appPlatform.sdl_event.key.keysym.sym != SDLK_ESCAPE) {
						uint16_t c = appPlatform.sdl_event.key.keysym.unicode;
						char p_codepoint[5];
						if(c <= 0x7f) {
							p_codepoint[0] = (char)c;
							p_codepoint[1] = '\x00';
						} else if(c <= 0x7fff) {
							p_codepoint[0] = (char)(0xc0 | ((c >> 6) & 0x1f));
							p_codepoint[1] = (char)(0x80 | ((c & 0x3f)));
							p_codepoint[2] = '\x00';
						} else if(c <= 0xffff) {
							p_codepoint[0] = (char)(0xe0 | ((c >> 12) & 0x0f));
							p_codepoint[1] = (char)(0x80 | ((c >> 6) & 0x3f));
							p_codepoint[2] = (char)(0x80 | (c & 0x3f));
							p_codepoint[3] = '\x00';
						}
						Keyboard::feedText(p_codepoint, 0);
						break;
					}

					int pressed = 0;
					this->onKeyPressed(mc, appPlatform.sdl_event.key.keysym.sym, appPlatform.sdl_event.type == SDL_KEYDOWN);
					Keyboard::feed(appPlatform.sdl_event.type == SDL_KEYDOWN ? 1 : 0, pressed);
					break;
			}
		}

		mc->update();
		SDL_GL_SwapBuffers();
	}

	if(mc) delete mc;
#ifdef DYNAMICSOUNDS
	if(SA_fuse.pcmData) free(SA_fuse.pcmData);
	if(SA_eat3.pcmData) free(SA_eat3.pcmData);
	if(SA_eat2.pcmData) free(SA_eat2.pcmData);
	if(SA_eat1.pcmData) free(SA_eat1.pcmData);
	if(SA_creeperdeath.pcmData) free(SA_creeperdeath.pcmData);
	if(SA_creeper4.pcmData) free(SA_creeper4.pcmData);
	if(SA_creeper3.pcmData) free(SA_creeper3.pcmData);
	if(SA_creeper2.pcmData) free(SA_creeper2.pcmData);
	if(SA_creeper1.pcmData) free(SA_creeper1.pcmData);
	if(SA_spiderdeath.pcmData) free(SA_spiderdeath.pcmData);
	if(SA_spider4.pcmData) free(SA_spider4.pcmData);
	if(SA_spider3.pcmData) free(SA_spider3.pcmData);
	if(SA_spider2.pcmData) free(SA_spider2.pcmData);
	if(SA_spider1.pcmData) free(SA_spider1.pcmData);
	if(SA_skeletonhurt4.pcmData) free(SA_skeletonhurt4.pcmData);
	if(SA_skeletonhurt3.pcmData) free(SA_skeletonhurt3.pcmData);
	if(SA_skeletonhurt2.pcmData) free(SA_skeletonhurt2.pcmData);
	if(SA_skeletonhurt1.pcmData) free(SA_skeletonhurt1.pcmData);
	if(SA_skeletondeath.pcmData) free(SA_skeletondeath.pcmData);
	if(SA_skeleton3.pcmData) free(SA_skeleton3.pcmData);
	if(SA_skeleton2.pcmData) free(SA_skeleton2.pcmData);
	if(SA_skeleton1.pcmData) free(SA_skeleton1.pcmData);
	if(SA_fallsmall.pcmData) free(SA_fallsmall.pcmData);
	if(SA_fallbig2.pcmData) free(SA_fallbig2.pcmData);
	if(SA_fallbig1.pcmData) free(SA_fallbig1.pcmData);
	if(SA_bowhit4.pcmData) free(SA_bowhit4.pcmData);
	if(SA_bowhit3.pcmData) free(SA_bowhit3.pcmData);
	if(SA_bowhit2.pcmData) free(SA_bowhit2.pcmData);
	if(SA_bowhit1.pcmData) free(SA_bowhit1.pcmData);
	if(SA_bow.pcmData) free(SA_bow.pcmData);
	if(SA_zpighurt2.pcmData) free(SA_zpighurt2.pcmData);
	if(SA_zpighurt1.pcmData) free(SA_zpighurt1.pcmData);
	if(SA_zpigdeath.pcmData) free(SA_zpigdeath.pcmData);
	if(SA_zpigangry4.pcmData) free(SA_zpigangry4.pcmData);
	if(SA_zpigangry3.pcmData) free(SA_zpigangry3.pcmData);
	if(SA_zpigangry2.pcmData) free(SA_zpigangry2.pcmData);
	if(SA_zpigangry1.pcmData) free(SA_zpigangry1.pcmData);
	if(SA_zpig4.pcmData) free(SA_zpig4.pcmData);
	if(SA_zpig3.pcmData) free(SA_zpig3.pcmData);
	if(SA_zpig2.pcmData) free(SA_zpig2.pcmData);
	if(SA_zpig1.pcmData) free(SA_zpig1.pcmData);
	if(SA_zombiehurt2.pcmData) free(SA_zombiehurt2.pcmData);
	if(SA_zombiehurt1.pcmData) free(SA_zombiehurt1.pcmData);
	if(SA_zombiedeath.pcmData) free(SA_zombiedeath.pcmData);
	if(SA_zombie3.pcmData) free(SA_zombie3.pcmData);
	if(SA_zombie2.pcmData) free(SA_zombie2.pcmData);
	if(SA_zombie1.pcmData) free(SA_zombie1.pcmData);
	if(SA_cowhurt3.pcmData) free(SA_cowhurt3.pcmData);
	if(SA_cowhurt2.pcmData) free(SA_cowhurt2.pcmData);
	if(SA_cowhurt1.pcmData) free(SA_cowhurt1.pcmData);
	if(SA_cow4.pcmData) free(SA_cow4.pcmData);
	if(SA_cow3.pcmData) free(SA_cow3.pcmData);
	if(SA_cow2.pcmData) free(SA_cow2.pcmData);
	if(SA_cow1.pcmData) free(SA_cow1.pcmData);
	if(SA_chickenhurt2.pcmData) free(SA_chickenhurt2.pcmData);
	if(SA_chickenhurt1.pcmData) free(SA_chickenhurt1.pcmData);
	if(SA_chicken3.pcmData) free(SA_chicken3.pcmData);
	if(SA_chicken2.pcmData) free(SA_chicken2.pcmData);
	if(SA_pigdeath.pcmData) free(SA_pigdeath.pcmData);
	if(SA_pig3.pcmData) free(SA_pig3.pcmData);
	if(SA_pig2.pcmData) free(SA_pig2.pcmData);
	if(SA_pig1.pcmData) free(SA_pig1.pcmData);
	if(SA_sheep3.pcmData) free(SA_sheep3.pcmData);
	if(SA_sheep2.pcmData) free(SA_sheep2.pcmData);
	if(SA_sheep1.pcmData) free(SA_sheep1.pcmData);
	if(SA_ignite.pcmData) free(SA_ignite.pcmData);
	if(SA_fire.pcmData) free(SA_fire.pcmData);
	if(SA_burp.pcmData) free(SA_burp.pcmData);
	if(SA_break.pcmData) free(SA_break.pcmData);
	if(SA_glass3.pcmData) free(SA_glass3.pcmData);
	if(SA_glass2.pcmData) free(SA_glass2.pcmData);
	if(SA_glass1.pcmData) free(SA_glass1.pcmData);
	if(SA_chestopen.pcmData) free(SA_chestopen.pcmData);
	if(SA_chestclosed.pcmData) free(SA_chestclosed.pcmData);
	if(SA_door_close.pcmData) free(SA_door_close.pcmData);
	if(SA_door_open.pcmData) free(SA_door_open.pcmData);
	if(SA_hurt.pcmData) free(SA_hurt.pcmData);
	if(SA_pop2.pcmData) free(SA_pop2.pcmData);
	if(SA_pop.pcmData) free(SA_pop.pcmData);
	if(SA_splash.pcmData) free(SA_splash.pcmData);
	if(SA_explode.pcmData) free(SA_explode.pcmData);
	if(SA_click.pcmData) free(SA_click.pcmData);
	if(SA_wood4.pcmData) free(SA_wood4.pcmData);
	if(SA_wood3.pcmData) free(SA_wood3.pcmData);
	if(SA_wood2.pcmData) free(SA_wood2.pcmData);
	if(SA_wood1.pcmData) free(SA_wood1.pcmData);
	if(SA_stone4.pcmData) free(SA_stone4.pcmData);
	if(SA_stone3.pcmData) free(SA_stone3.pcmData);
	if(SA_stone2.pcmData) free(SA_stone2.pcmData);
	if(SA_stone1.pcmData) free(SA_stone1.pcmData);
	if(SA_sand4.pcmData) free(SA_sand4.pcmData);
	if(SA_sand3.pcmData) free(SA_sand3.pcmData);
	if(SA_sand2.pcmData) free(SA_sand2.pcmData);
	if(SA_sand1.pcmData) free(SA_sand1.pcmData);
	if(SA_gravel4.pcmData) free(SA_gravel4.pcmData);
	if(SA_gravel3.pcmData) free(SA_gravel3.pcmData);
	if(SA_gravel2.pcmData) free(SA_gravel2.pcmData);
	if(SA_gravel1.pcmData) free(SA_gravel1.pcmData);
	if(SA_grass4.pcmData) free(SA_grass4.pcmData);
	if(SA_grass3.pcmData) free(SA_grass3.pcmData);
	if(SA_grass2.pcmData) free(SA_grass2.pcmData);
	if(SA_grass1.pcmData) free(SA_grass1.pcmData);
	if(SA_cloth4.pcmData) free(SA_cloth4.pcmData);
	if(SA_cloth3.pcmData) free(SA_cloth3.pcmData);
	if(SA_cloth2.pcmData) free(SA_cloth2.pcmData);
	if(SA_cloth1.pcmData) free(SA_cloth1.pcmData);
#endif
}
LoginInformation AppPlatform_sdl::getLoginInformation(void) {
	return LoginInformation();
	LoginInformation ret;
	ret.accessToken = "cliff";
	ret.clientId = "my_beloved";
	ret.profileId = "freehij_when_enchantile";
	ret.profileName = "wsndow1";
	return ret;
}
void AppPlatform_sdl::sdlCtxDestroy(){
	if(!this->hasContext) return;
	SDL_Quit();
	this->hasContext = 0;
}

AppPlatform_sdl::AppPlatform_sdl() {
	this->hasContext = 0;
}

AppPlatform_sdl::~AppPlatform_sdl(){
	this->sdlCtxDestroy();
}
#endif
