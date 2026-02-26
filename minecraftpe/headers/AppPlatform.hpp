#pragma once
#include <_types.h>
#include <string>
#include <vector>
#include <map>
#include <GL/gl.h>
#include <rendering/textures/TextureData.hpp>

struct ImageData;
struct LoginInformation;
struct AssetFile;

struct AppPlatform{
	struct Listener{
		virtual ~Listener();
		virtual bool_t onLowMemory(void);
		virtual void onAppSuspended(void) = 0;
		virtual void onAppResumed(void);
		virtual void onAppFocusLost(void);
		virtual void onAppFocusGained(void);

	};

	bool_t keyboardShown;
	int8_t a5, a6, a7;
	std::multimap<float, AppPlatform::Listener*> listeners; //_Rb_tree, probably std::map(https://gcc.gnu.org/onlinedocs/gcc-4.8.5/libstdc++/api/a01251_source.html line 134), also weird that it uses float as a key

	static AppPlatform* _singleton;
	static int32_t TEXTURE_MAX_LEVEL;
	static GLfloat ANISOTROPIC_MAX_LEVEL;
	//XXX might be not char_t
	static char_t* preloadingHTML;

	AppPlatform(void);

	virtual ~AppPlatform(void);
	virtual void saveScreenshot(const std::string&, int32_t, int32_t);
	virtual std::string getImagePath(const std::string&, bool_t) = 0;
	virtual void loadPNG(ImageData&, const std::string&, bool_t) = 0;
	virtual void loadTGA(ImageData&, const std::string&, bool_t);
	virtual void playSound(const std::string&, float, float);
	virtual void showDialog(int32_t);
	virtual void createUserInput(void);
	virtual int32_t getUserInputStatus(void);
	virtual std::vector<std::string> getUserInput(void);
	virtual std::string getDateString(int32_t);
	virtual int32_t checkLicense(void);
	virtual bool_t hasBuyButtonWhenInvalidLicense(void);
	virtual void uploadPlatformDependentData(int32_t, void*);
	virtual AssetFile readAssetFile(const std::string&);
	virtual void _tick(void);
	virtual int32_t getScreenWidth(void);
	virtual int32_t getScreenHeight(void);
	virtual float getPixelsPerMillimeter(void);
	virtual bool_t isNetworkEnabled(bool_t);
	virtual void openLoginWindow(void);
	virtual bool_t isPowerVR(void);
	virtual int32_t getKeyFromKeyCode(int32_t, int32_t, int32_t);
	virtual void buyGame(void);
	virtual void finish(void);
	virtual bool_t supportsTouchscreen(void);
	virtual bool_t hasIDEProfiler(void);
	virtual bool_t supportsVibration(void);
	virtual void vibrate(int32_t);
	virtual std::string getPlatformStringVar(int32_t);
	virtual void showKeyboard(std::string*, int32_t, bool_t);
	virtual void hideKeyboard(void);
	virtual void updateTextBoxText(const std::string&);
	virtual bool_t isKeyboardVisible(void);
	virtual LoginInformation getLoginInformation(void);
	virtual void setLoginInformation(const LoginInformation&);
	virtual void clearSessionIDAndRefreshToken(void);
	virtual void statsTrackData(const std::string&, const std::string&);
	virtual void updateStatsUserData(const std::string&, const std::string&);

	void _fireAppSuspended(void);
	void createUserInput(int32_t);
	int32_t getPreloadingHTMLLength(void);
	void loadImage(ImageData&, const std::string&, bool_t);
	TextureData loadTexture(const std::string&, bool_t);
	void removeListener(AppPlatform::Listener*);
	void addListener(AppPlatform::Listener*, float);
};
