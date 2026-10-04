#pragma once
#include <rendering/textures/TextureData.hpp>
#include <network/mco/LoginInformation.hpp>
#include <map>
#include <unigl.hpp>
#include <_AssetFile.hpp>
#include <cpputils.hpp>

struct ImageData;
struct LoginInformation;
struct AssetFile;

struct AppPlatform{
	struct Listener{
		virtual ~Listener() {
		}
		virtual bool_t onLowMemory(void) {
			return 0;
		}
		virtual void onAppSuspended(void) = 0;
		virtual void onAppResumed(void) {
		}
		virtual void onAppFocusLost(void) {
		}
		virtual void onAppFocusGained(void) {
		}

	};

	bool keyboardShown;
	std::multimap<float, AppPlatform::Listener*> listeners;

	static AppPlatform* _singleton;
	static int32_t TEXTURE_MAX_LEVEL;
	static int ANISOTROPIC_FILTER;
	static GLfloat ANISOTROPIC_MAX_LEVEL;
	//XXX might be not char_t
	static char_t* preloadingHTML;

	AppPlatform(void);

	virtual ~AppPlatform(void) {
	}
	virtual void saveScreenshot(const std::string&, int32_t, int32_t) {
	}
	virtual std::string getImagePath(const std::string&, bool_t) = 0;
	virtual void loadPNG(ImageData&, const std::string&, bool_t) = 0;
	virtual void loadTGA(ImageData&, const std::string&, bool_t);
	virtual void playSound(const std::string&, float, float) {
	}
	virtual void showDialog(int32_t) {
	}
	virtual void createUserInput(void) {
	}
	virtual int32_t getUserInputStatus(void) {
		return 0;
	}
	virtual std::vector<std::string> getUserInput(void) {
		return {};
	}
	virtual std::string getDateString(int32_t) {
		return ""; //nullstr
	}
	virtual int32_t checkLicense(void) {
		return 0;
	}
	virtual bool_t hasBuyButtonWhenInvalidLicense(void) {
		return 0;
	}
	virtual void uploadPlatformDependentData(int32_t, void*) {
	}
	virtual AssetFile readAssetFile(const std::string& path) {
		FILE* f = fopen(path.c_str(), "rb");
		if(f) {
			int32_t size = getRemainingFileSize(f);
			uint8_t* arr = new uint8_t[size];
			fread(arr, 1, size, f);
			fclose(f);
			return AssetFile(arr, size);
		} else {
			return AssetFile(0, -1);
		}
	}
	virtual void _tick(void) {
	}
	virtual int32_t getScreenWidth(void) {
		return 854;
	}
	virtual int32_t getScreenHeight(void) {
		return 480;
	}
	virtual float getPixelsPerMillimeter(void) {
		return 10.0f;
	}
	virtual bool_t isNetworkEnabled(bool_t) {
		return 1;
	}
	virtual void openLoginWindow(void) {
	}
	virtual bool_t isPowerVR(void) {
		return 0;
	}
	virtual int32_t getKeyFromKeyCode(int32_t, int32_t, int32_t) {
		return 0;
	}
	virtual void buyGame(void) {
	}
	virtual void finish(void) {
	}
	virtual bool supportsTouchscreen(void) {
		return 1;
	}
	virtual bool_t hasIDEProfiler(void) {
		return 0;
	}
	virtual bool_t supportsVibration(void) {
		return 1;
	}
	virtual void vibrate(int32_t) {
	}
	virtual std::string getPlatformStringVar(int32_t){
		return "<getPlatformStringVar NotImplemented>"; //this is actual return value
	}
	virtual void showKeyboard(const std::string&, int32_t, bool_t){
		this->keyboardShown = 1;
	}
	virtual void hideKeyboard(void) {
		this->keyboardShown = 0;
	}
	virtual void updateTextBoxText(const std::string&) {
	}
	virtual bool_t isKeyboardVisible(void) {
		return this->keyboardShown;
	}
	virtual LoginInformation getLoginInformation(void) {
		return LoginInformation();
	}
	virtual void setLoginInformation(const LoginInformation&) {
	}
	virtual void clearSessionIDAndRefreshToken(void) {
	}
	virtual void statsTrackData(const std::string&, const std::string&) {
	}
	virtual void updateStatsUserData(const std::string&, const std::string&) {
	}

	void _fireAppSuspended(void){
		std::multimap<float, AppPlatform::Listener*>::reverse_iterator it = this->listeners.rbegin();
		std::multimap<float, AppPlatform::Listener*>::reverse_iterator end = this->listeners.rend();

		for(;it != end;++it){
			it->second->onAppSuspended();
		}
	}
	void createUserInput(int32_t i){
		this->showDialog(i);
		this->createUserInput();
	}
	int32_t getPreloadingHTMLLength(void);
	void loadImage(ImageData&, const std::string&, bool_t);
	TextureData loadTexture(const std::string&, bool_t);
	void removeListener(AppPlatform::Listener* a2) {
		for(auto&& p = this->listeners.begin(); p != this->listeners.end(); ++p) { //TODO check
			if(p->second == a2) {
				this->listeners.erase(p);
				break;
			}
		}
	}
	void addListener(AppPlatform::Listener* a2, float a3) {
		this->listeners.insert(std::pair<float, AppPlatform::Listener*>(a3, a2));
	}
};
