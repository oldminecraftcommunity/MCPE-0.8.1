#pragma once
#include <App.hpp>
#include <memory>
#include <rendering/TextureAtlas.hpp>
#include <rendering/TextureAtlasId.hpp>
#include <network/mco/MojangConnectionStatus.hpp>
#include <string>
#include <Options.hpp>
#include <gui/ScreenChooser.hpp>
#include <gui/Gui.hpp>
#include <input/MouseHandler.hpp>
#include <math/HitResult.hpp>
#include <Timer.hpp>

struct CThread;
struct User;
struct Minecraft : App{
	static char customDebugId[];
	static char_t* progressMessages[];

	Options options;
	int8_t field_16C, field_16D, field_16E, field_16F;
	struct LevelRenderer* levelRenderer;
	struct GameRenderer* gameRenderer;
	struct ParticleEngine* particleEngine;
	struct SoundEngine* soundEngine;
	struct GameMode* gameMode;
	std::shared_ptr<struct MojangConnector> mojangConnector;
	struct Textures* texturesPtr;
	bool animatedTextureTicked;
	ScreenChooser screenChooser;
	struct Font* font;
	int8_t field_19C, field_19D, field_19E, field_19F;
	Gui gui;
	MouseHandler mouseHandler;
	struct RakNetInstance* rakNetInstance;
	struct NetEventCallback* serverSideNetworkHandler;
	int32_t field_C50, field_C54, field_C58;
	int field_C5C;
	User* user;
	struct Level* level;
	struct LocalPlayer* player; //TODO needs 1 field before this thing somewhere
	struct IInputHolder *inputHolder;
	struct Mob* viewEntity;
	CThread* prepareLevelThread;
	Screen* currentScreen;
	std::shared_ptr<Screen> field_C7C;
	bool mouseGrabbed;
	float field_C84;
	float field_C88;
	float field_C8C;
	float field_C90;
	HitResult selectedObject;
	int32_t field_CBC;
	std::string dataPathMaybe;
	std::string field_CC4;
	std::shared_ptr<struct ExternalServerFile> externalServerFile;
	Timer timer;
	bool field_CF4, levelGenerated, field_CF6, field_CF7;
	struct LevelStorageSource* levelStorageSource;
	bool levelSelected, powerVR;
	int8_t field_CFE, field_CFF;
	std::string field_D00;
	int32_t progressMessageIndex;
	int32_t field_D08; //buildActionDelay?
	int32_t field_D0C;
	int32_t field_D10;
	int8_t field_D14, field_D15, field_D16, field_D17;
	struct Screen* field_D18;
	int32_t license;
	bool supportsNonTouchScreen;
	bool isCreative;
	bool _leaveGame;
	int8_t field_D23;
	int8_t field_D24, field_D25, field_D26, field_D27;
	struct PerfRenderer* perfRenderer;
	struct CommandServer* commandServer;
	struct CMutex* cmutex;
	struct ServerCommandParser* serverCmdParser;
	double field_D34;
	double timeStartedAtMaybe;


	Minecraft(void);
	void _levelGenerated(void);
	void _reloadInput(void);
	virtual void audioEngineOff(void);
	virtual void audioEngineOn(void);
	void cancelLocateMultiplayer(void);
	void checkGlError(const char_t*);
	void connectToMCOServer(const std::string&, const std::string&, uint16_t);
	void gameLostFocus(void);
	void generateLevel(const std::string&, struct Level*);
	struct ICreator* getCreator(void);
	struct LevelStorageSource* getLevelSource(void);
	int32_t getLicenseId(void);
	char_t* getProgressMessage(void);
	int32_t getProgressStageStatus(void);
	int32_t getProgressStatusId(void);
	virtual std::shared_ptr<TextureAtlas> getTextureAtlas(TextureAtlasId) {
		return 0;
	}
	void grabMouse(void);
	void handleBuildAction(struct BuildActionIntention*);
	void handleMouseClick(int32_t);
	void handleMouseDown(int32_t, bool_t);
	bool_t hostMultiplayer(int32_t);
	virtual void init(void);
	bool_t isCreativeMode(void);
	bool_t isKindleFire(int32_t);
	bool_t isLevelGenerated(void);
	bool_t isOnline(void);
	bool_t isOnlineClient(void);
	void joinMultiplayer(const struct PingedCompatibleServer&, bool_t);
	void leaveGame(bool_t, bool_t);
	void locateMultiplayer(void);
	void lockForControl(void);
	virtual void onAppResumed(void);
	virtual void onAppSuspended(void);
	void onMojangConnectorStatus(enum MojangConnectionStatus);
	void onUpdatedClient(int32_t, int32_t, int32_t, int32_t);
	void optionUpdated(const Options::Option*, bool_t);
	void optionUpdated(const Options::Option*, float);
	void optionUpdated(const Options::Option*, int32_t);
	void pauseGame(bool_t);
	void prepareLevel(const std::string&);
	static void* prepareLevel_tspawn(void*);
	void releaseMouse(void);
	void reloadOptions(void);
	void resetPlayer(struct Player*);
	Player* respawnPlayer(int32_t); //XXX void?
	void respawnPlayer(void);
	virtual void selectLevel(const std::string&, const std::string&, const struct LevelSettings&);
	void setIsCreativeMode(bool_t);
	void setLeaveGame(void);
	virtual void setLevel(struct Level*, const std::string&, struct LocalPlayer*);
	void setScreen(struct Screen*);
	virtual void setSize(int32_t, int32_t);
	virtual void setTextboxText(const std::string&);
	bool_t supportNonTouchScreen(void);
	virtual void teardown(void);
	void tick(int32_t, int32_t);
	void tickInput(void);
	bool_t transformResolution(int32_t*, int32_t*);
	void unlockControl(void);
	virtual void update(void);
	void updateStatusUserAttributes(void);
	virtual bool_t useTouchscreen(void);
	~Minecraft();
};
