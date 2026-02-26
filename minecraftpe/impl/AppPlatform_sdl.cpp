#include <AppPlatform_sdl.hpp>
#include <_AssetFile.hpp>
#include <NinecraftApp.hpp>
#include <main.hpp>
#include <rendering/Tesselator.hpp>
#include <stb/stb_image.h>
#include <rendering/Textures.hpp>
#include <rendering/Font.hpp>
#include <utils.h>
#include <input/Mouse.hpp>
#include <input/Keyboard.hpp>
#include <entity/LocalPlayer.hpp>
#include <inventory/Inventory.hpp>
#include <input/KeyboardInput.hpp>

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

/*void AppPlatform_sdl::updateStatsUserData(const std::string&, const std::string&){
	printf("AppPlatform_sdl::updateStatsUserData: not implemented\n");
}*/

SDL_Surface* AppPlatform_sdl::setSDLVideoMode() {
	return SDL_SetVideoMode(
		this->screenWidth, this->screenHeight,
		32, SDL_OPENGL | SDL_RESIZABLE
	);
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

#ifdef PCTWEAKS
	int maxTextureLevel, anisotropicFilter;

	const char_t* str = (const char_t*)glGetString(GL_EXTENSIONS);
	std::string exts = str ? str : "";
	maxTextureLevel = GL_TEXTURE_MAX_LEVEL; //opengl (non es) doesnt seem to require ext for it
	AppPlatform::TEXTURE_MAX_LEVEL = maxTextureLevel;
	if(exts.find("GL_EXT_texture_filter_anisotropic", 0) == -1) anisotropicFilter = 0;
	else anisotropicFilter = GL_TEXTURE_MAX_ANISOTROPY;
	AppPlatform::ANISOTROPIC_MAX_LEVEL = anisotropicFilter;
	if(anisotropicFilter) glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &AppPlatform::ANISOTROPIC_MAX_LEVEL);
#endif

	return 1;
}

void AppPlatform_sdl::onKeyPressed(Minecraft* mc, SDLKey key, bool pressed) {
	int k = 0;
	if(key == SDLK_w) k = mc->options.keyForward.keyCode;
	if(key == SDLK_s) k = mc->options.keyBack.keyCode;
	if(key == SDLK_a) k = mc->options.keyLeft.keyCode;
	if(key == SDLK_d) k = mc->options.keyRight.keyCode;
	if(key == SDLK_SPACE) k = mc->options.keyJump.keyCode;
	if(key == SDLK_ESCAPE) k = 255;
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

#include <util/Util.hpp>
#include <unistd.h>
MeshBuffer cube;
void AppPlatform_sdl::init(){
	this->screenWidth = 854;
	this->screenHeight = 480;
	AppContext ctx;

	NinecraftApp* mc = new NinecraftApp();
	this->hasContext = this->sdlCtxInit();
	ctx.platform = this;
	mc->context = ctx;
	char curdir[256];
	getcwd(curdir, 256);
	mc->dataPathMaybe = curdir;
	printf("dir: %s\n", curdir);
	bool_t running = this->hasContext;
	bool_t hasInit = 0;
	Tesselator& tess = Tesselator::instance;
	//int32_t t = textures.loadAndBindTexture("../cat.png");
	//printf("%d\n", t);

	static const int lbkey = 102;
	static const int rbkey = 103;
	bool windowActive = 1;
	unsigned int lastBuiltTick = 0;
	while(running){

		if(!hasInit){
			hasInit = 1;
			mc->init();
			mc->setSize(this->screenWidth, this->screenHeight);
			//mc->currentScreen->init(mc, this->screenWidth, this->screenHeight);
		}

		if(mc->mouseGrabbed) {
			SDL_WM_GrabInput(SDL_GRAB_ON);
			SDL_ShowCursor(SDL_DISABLE);
		} else {
			SDL_WM_GrabInput(SDL_GRAB_OFF);
			SDL_ShowCursor(SDL_ENABLE);
		}


		while(SDL_PollEvent(&appPlatform.sdl_event)){
			uint16_t _mx, _my;
			switch(appPlatform.sdl_event.type) {
				case SDL_ACTIVEEVENT:
					if(appPlatform.sdl_event.active.state == SDL_APPINPUTFOCUS) {
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
					if(!windowActive) break;
					_mx = appPlatform.sdl_event.motion.x;
					_my = appPlatform.sdl_event.motion.y;
					Mouse::feed(0, 0, _mx, _my, appPlatform.sdl_event.motion.xrel, appPlatform.sdl_event.motion.yrel);
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
						Keyboard::feedText(p_codepoint, appPlatform.sdl_event.type == SDL_KEYDOWN);
						Keyboard::feedText(p_codepoint, 0);
						break;
					}

					int pressed = 0;
					this->onKeyPressed(mc, appPlatform.sdl_event.key.keysym.sym, appPlatform.sdl_event.type == SDL_KEYDOWN);
					Keyboard::feed(appPlatform.sdl_event.type == SDL_KEYDOWN ? 1 : 0, pressed);
					break;
			}
		}


		//TODO engine stuff

		/*Tesselator::instance.begin(4);
		Tesselator::instance.enableColor();
		Tesselator::instance.color(0xffff0000);
		Tesselator::instance.vertex(0, 0, 0);
		Tesselator::instance.vertex(0, 1, 0);
		Tesselator::instance.vertex(1, 1, 0);
		Tesselator::instance.vertex(1, 0, 0);
		Tesselator::instance.color(0xff0000ff);
		Tesselator::instance.vertex(0, 1, 0);
		Tesselator::instance.vertex(0, 1, 1);
		Tesselator::instance.vertex(1, 1, 1);
		Tesselator::instance.vertex(1, 1, 0);
		Tesselator::instance.color(0xff00ff00);
		Tesselator::instance.vertex(0, 0, 0);
		Tesselator::instance.vertex(0, 0, 1);
		Tesselator::instance.vertex(0, 1, 1);
		Tesselator::instance.vertex(0, 1, 0);
		Tesselator::instance.color(0xff00ffff);
		Tesselator::instance.vertex(0, 0, 0);
		Tesselator::instance.vertex(1, 0, 0);
		Tesselator::instance.vertex(1, 0, 1);
		Tesselator::instance.vertex(0, 0, 1);
		Tesselator::instance.color(0xffffff00);
		Tesselator::instance.vertex(1, 0, 0);
		Tesselator::instance.vertex(1, 1, 0);
		Tesselator::instance.vertex(1, 1, 1);
		Tesselator::instance.vertex(1, 0, 1);
		Tesselator::instance.color(0xffff00ff);
		Tesselator::instance.vertex(0, 0, 1);
		Tesselator::instance.vertex(1, 0, 1);
		Tesselator::instance.vertex(1, 1, 1);
		Tesselator::instance.vertex(0, 1, 1);
		cube = Tesselator::instance.end();*/
		//TODO contextWasLost
		//else{
			mc->update();
		//}
		/*glViewport(0, 0, mc->field_1C, mc->field_20);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, mc->field_1C*Gui::InvGuiScale, mc->field_20*Gui::InvGuiScale, 0, 0, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);

		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnableClientState(GL_VERTEX_ARRAY);
		Tesselator::instance.enableColor();

		//TODO this thing happens in gamerenderer
		int32_t mx = Mouse::getX();
		int32_t my = Mouse::getY();
		mc->currentScreen->render(mx*Gui::InvGuiScale, my*Gui::InvGuiScale, 0);*/
		SDL_GL_SwapBuffers();
	}

	if(mc) delete mc;
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
