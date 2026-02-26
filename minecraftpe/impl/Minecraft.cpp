#include <Minecraft.hpp>
#include <ExternalServerFile.hpp>
#include <cpputils.hpp>
#include <entity/LocalPlayer.hpp>
#include <entity/player/User.hpp>
#include <entity/player/gamemode/CreativeMode.hpp>
#include <entity/player/gamemode/SurvivalMode.hpp>
#include <gui/screens/DeathScreen.hpp>
#include <gui/screens/PauseScreen.hpp>
#include <input/BuildActionIntention.hpp>
#include <input/ControllerTurnInput.hpp>
#include <input/CustomInputHolder.hpp>
#include <input/Keyboard.hpp>
#include <input/Mouse.hpp>
#include <input/Multitouch.hpp>
#include <input/TouchInputHolder.hpp>
#include <input/XperiaPlayInput.hpp>
#include <inventory/Inventory.hpp>
#include <level/ServerLevel.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <level/gen/ChunkSource.hpp>
#include <level/storage/LevelStorageSource.hpp>
#include <network/ClientSideNetworkHandler.hpp>
#include <network/CommandServer.hpp>
#include <network/RakNetInstance.hpp>
#include <network/ServerSideNetworkHandler.hpp>
#include <network/mco/MojangConnector.hpp>
#include <network/packet/InteractPacket.hpp>
#include <network/packet/RespawnPacket.hpp>
#include <perf/PerfTimer.hpp>
#include <perf/Stopwatch.hpp>
#include <rendering/GLBufferPool.hpp>
#include <rendering/GameRenderer.hpp>
#include <rendering/ItemInHandRenderer.hpp>
#include <rendering/LevelRenderer.hpp>
#include <rendering/ParticleEngine.hpp>
#include <rendering/PerfRenderer.hpp>
#include <rendering/Textures.hpp>
#include <sound/SoundEngine.hpp>
#include <tile/Tile.hpp>
#include <util/CMutex.hpp>
#include <util/CThread.hpp>
#include <util/SharedConstants.hpp>
#include <utils.h>
#include <gui/screens/RenameMPLevelScreen.hpp>
#include <level/storage/LevelStorage.hpp>
#include <rendering/Font.hpp>
#include <network/ServerCommandParser.hpp>
#include <entity/MobFactory.hpp>
#include <rendering/EntityRenderDispatcher.hpp>

char_t* Minecraft::progressMessages[] = {"Locating server", "Building terrain", "Preparing", "Saving chunks", "Waiting for Minecraft Realms"};

Minecraft::Minecraft()
	: gui(this) {
	this->wantsToQuit = 0;
	this->context.platform = 0;
	this->field_1C = 1;
	this->field_24 = 4711;
	this->field_20 = 1;
	this->field_18 = 0;
	this->field_28 = 0;
	this->field_2C = 0;
	this->field_30 = 0;
	this->field_34 = 0;
	//TODO settings and stuff
	this->field_16C = 0;
	this->levelRenderer = 0;
	this->gameRenderer = 0;
	this->particleEngine = 0;
	this->soundEngine = 0;
	this->gameMode = 0;
	this->mojangConnector = 0;
	this->field_188 = 0;
	this->texturesPtr = 0;
	this->screenChooser.minecraft = this;
	this->font = 0;
	//gui(this)
	//mousehandler()
	this->field_C54 = -1;
	this->serverSideNetworkHandler = 0;
	this->field_C50 = 0;
	this->field_C58 = 0;
	this->mouseGrabbed = 1;
	this->field_C5C = 0;
	this->user = 0;
	this->level = 0;
	this->player = 0;
	this->inputHolder = 0;
	this->viewEntityMaybe = 0;
	this->prepareLevelThread = 0;
	this->currentScreen = 0;
	this->field_C7C = 0;
	this->field_C84 = 1;
	this->field_C88 = 1;
	this->field_C8C = 1;
	this->field_C90 = 1;
	//hitresult(selectedObject)
	this->field_CBC = 0;
	this->dataPathMaybe = "";
	this->field_CC4 = "";
	this->externalServerFile = 0;
	this->timer.ticksPerSecond = 20;
	this->timer.timeScale = 1;
	this->timer.passedTime = 0;
	this->timer.adjustTime = 1;
	int32_t timeMs = getTimeMs();
	this->timer.lastMs = timeMs;
	this->timer.lastMsSysTime = timeMs;
	this->timer.lastTime = timeMs / 1000;
	this->field_CF4 = 0;
	this->levelGenerated = 1;
	this->license = -2;
	this->field_CFC = 0;
	this->powerVR = 0;
	this->field_D00 = "";
	this->progressMessageIndex = 0;
	this->field_D08 = 0;
	this->field_D0C = 0;
	this->field_D10 = 0;
	this->field_D14 = 0;
	this->field_D15 = 0;
	this->field_D18 = 0;
	this->supportsNonTouchScreen = 0;
	this->field_D22 = 0;
	this->perfRenderer = 0;
	this->commandServer = 0;
	this->field_D34 = 0;
	this->timeStartedAtMaybe = 0; //XXX not in mcpe?
	this->rakNetInstance = new RakNetInstance();
	this->soundEngine = new SoundEngine(20);
	this->soundEngine->init(this, &this->options);
	this->cmutex = new CMutex();
	this->field_D30 = new ServerCommandParser();
}

void Minecraft::_levelGenerated(void) {
	LocalPlayer* v2;							// r0
	LocalPlayer* player;						// r5
	LocalPlayer* v4;							// r0
	LevelRenderer* levelRenderer;				// r0
	ParticleEngine* particleEngine;				// r0
	NetEventCallback* serverSideNetworkHandler; // r0

	if(!this->player) {
		v2 = (LocalPlayer*)this->gameMode->createPlayer(this->level);
		this->player = v2;
		this->gameMode->initPlayer(v2);
	}
	player = this->player;
	if(player) {
		player->moveInput = (KeyboardInput*)this->inputHolder->getMoveInput();
	}
	this->gameMode->adjustPlayer(this->player);
	this->gui.onLevelGenerated();
	this->level->validateSpawn();
	this->level->loadPlayer(this->player, 1);
	v4 = this->player;
	if(v4) {
		if(!this->level->isClientMaybe) {
			v4->resetPos(0);
		}
	}
	levelRenderer = this->levelRenderer;
	this->viewEntityMaybe = (Player*)this->player;
	if(levelRenderer) {
		levelRenderer->setLevel(this->level);
	}
	particleEngine = this->particleEngine;
	if(particleEngine) {
		particleEngine->setLevel(this->level);
	}
	if(this->rakNetInstance->isServer()) {
		this->rakNetInstance->announceServer(this->user->username);
	}
	serverSideNetworkHandler = this->serverSideNetworkHandler;
	if(serverSideNetworkHandler) {
		serverSideNetworkHandler->levelGenerated(this->level);
	}
	this->levelGenerated = 1;
	this->progressMessageIndex = 0;
}
void Minecraft::_reloadInput(void) {
	if(this->inputHolder) delete this->inputHolder;
	if(this->useTouchscreen()) {
		//TODO touchscreen input
		printf("Attempting to create touchscreen input(WIP)\n");
		TouchInputHolder* holder = new TouchInputHolder(this);
		this->inputHolder = holder;
	} else {
		this->inputHolder = new CustomInputHolder(new XperiaPlayInput(this, &this->options), new ControllerTurnInput(), new IBuildInput());
	}
	this->mouseHandler.setTurnInput(this->inputHolder->getTurnInput());
	if(this->level) {
		if(this->player) {
			this->player->moveInput = (KeyboardInput*)this->inputHolder->getMoveInput();
		}
	}
}
void Minecraft::audioEngineOff(void) {
	this->soundEngine->enable(0);
}
void Minecraft::audioEngineOn(void) {
	this->soundEngine->enable(1);
}
void Minecraft::cancelLocateMultiplayer(void) {
	this->field_18 = 0;
	this->rakNetInstance->stopPingForHosts();
	if(this->serverSideNetworkHandler) delete this->serverSideNetworkHandler;
	this->serverSideNetworkHandler = 0;
}
void Minecraft::checkGLError(const char_t*) {
}
void Minecraft::connectToMCOServer(const std::string& a2, const std::string& a3, uint16_t a4) {
	PingedCompatibleServer v8;
	v8.field_4.FromStringExplicitPort(a3.c_str(), a4, 0);
	v8.field_0 = a2.c_str();
	this->joinMultiplayer(v8, 1);
}
void Minecraft::gameLostFocus(void) {
	if(this->currentScreen) {
		this->currentScreen->lostFocus();
	}
}
void Minecraft::generateLevel(const std::string& a2, struct Level* a3) {
	Stopwatch v6;
	v6.start();
	this->prepareLevel(a2);
	v6.stop();
	v6.print("Level generated: ");
	this->field_CF4 = 0;
}
int32_t Minecraft::getCreator(void) { //TODO returns ICreator* ?
	return 0;
}
struct LevelStorageSource* Minecraft::getLevelSource(void) {
	return this->levelStorageSource;
}

int32_t Minecraft::getLicenseId(void) {
	if(this->license < 0) this->license = this->platform()->checkLicense();
	return this->license;
}
char_t* Minecraft::getProgressMessage(void) {
	return Minecraft::progressMessages[this->progressMessageIndex];
}
int32_t Minecraft::getProgressStageStatus(void) {
	return this->progressMessageIndex;
}
int32_t Minecraft::getProgressStatusId(void) {
	return this->progressMessageIndex;
}
std::shared_ptr<TextureAtlas> Minecraft::getTextureAtlas(TextureAtlasId) {
	return 0;
}
void Minecraft::grabMouse(void) {
	if(!this->mouseGrabbed) {
		this->mouseGrabbed = 1;
		this->mouseHandler.grab();
	}
}
void Minecraft::handleBuildAction(struct BuildActionIntention* a2) {
	int field_D0C;		// r3
	int hitType;		// r5
	int entityId;		// r6
	int v7;				// r5
	int v9;				// r7
	int v10;			// r6
	int v11;			// r5
	int v12;			// r10
	Tile* v13;			// r9
	ItemInstance* v14;	// r9
	int v15;			// r6
	uint8_t v16;		// r0
	int v17;			// r10
	int v18;			// r7
	ItemInstance* sel;	// r5
	GameMode* gameMode; // r0

	field_D0C = this->field_D0C;
	if(field_D0C > 0) {
		this->field_D0C = field_D0C - 1;
	}
	if(!this->player->isUsingItem()) {
		hitType = this->selectedObject.hitType;
		if(hitType == 2) {
			if(a2->isRemove()) {
				if(!this->gameMode->isCreativeType()) {
					this->field_D08 = 10;
				}
			}
			goto LABEL_27;
		}

		if(hitType == 1) {
			if((a2->field_0 & 8) != 0) {
				this->player->swing();
				entityId = this->player->entityId;
				v7 = this->selectedObject.entity->entityId;
				InteractPacket v23(entityId, v7, 2);
				this->rakNetInstance->send(v23);
				this->gameMode->attack(this->player, this->selectedObject.entity);
				goto LABEL_27;
			}
			if((a2->field_0 & 0x10) == 0 || this->field_D0C) {
				goto LABEL_27;
			}
			v16 = this->selectedObject.entity->interactPreventDefault();
			v17 = this->player->entityId;
			v18 = this->selectedObject.entity->entityId;
			v15 = v16 ^ 1;
			InteractPacket v23_(v17, v18, 1);
			this->rakNetInstance->send(v23_);
			this->gameMode->interact((Player*)this->player, (Entity*)this->selectedObject.entity);
LABEL_26:
			if(!v15) {
				return;
			}
			goto LABEL_27;
		}
		if(hitType) {
LABEL_27:
			if((a2->field_0 & 0x10) != 0 && !this->field_D0C) {
				sel = this->player->inventory->getSelected();
				if(sel) {
					if(!this->player->isUsingItem()) {
						gameMode = this->gameMode;
						this->field_D0C = 8;
						if(gameMode->useItem((Player*)this->player, this->level, sel)) {
							this->gameRenderer->itemInHandRenderer->itemUsed();
						}
						if(sel->count <= 0) {
							this->player->inventory->clearSlot(this->player->inventory->selectedSlot);
						}
					}
				}
			}
			return;
		}
		v9 = this->selectedObject.field_4;
		v10 = this->selectedObject.field_8;
		v11 = this->selectedObject.field_C;
		v12 = this->selectedObject.field_10;
		v13 = Tile::tiles[this->level->getTile(v9, v10, v11)];
		if(!a2->isRemove()) {
			v14 = this->player->inventory->getSelected();
			if(this->gameMode->useItemOn((Player*)this->player, this->level, v14, v9, v10, v11, v12, this->selectedObject.hitVec)) {
				v15 = 0;
				this->player->swing();
			} else {
				v15 = 1;
			}
			if(v14) {
				if(v14->count <= 0) {
					this->player->inventory->clearSlot(this->player->inventory->selectedSlot);
				}
			}
			//goto LABEL_26 ->
			if(!v15) {
				return;
			}
			goto LABEL_27;
		}
		if(v13 && !v13->isLiquidTile() && !this->player->isDestroying) {
			this->level->extinguishFire(v9, v10, v11, this->selectedObject.field_10);
			this->gameMode->startDestroyBlock(v9, v10, v11, this->selectedObject.field_10);
			this->player->startDestroying();
			goto LABEL_27;
		}
	}
}
void Minecraft::handleMouseClick(int32_t) {
}
void Minecraft::handleMouseDown(int32_t a2, bool_t a3) {
	Tile* v9;	// r0

	if(this->player->isUsingItem()) {
		if(!a3 && Keyboard::_states[this->options.keyUse.keyCode] != 1) {
			this->gameMode->releaseUsingItem(this->player);
		}
	} else if(!this->player->isSleeping() && (a2 != 1 || this->field_D08 <= 0)) {
		if(this->player->isDestroying) {
			if(this->selectedObject.hitType || !a3 || a2 != 1 || this->selectedObject.field_24 || (v9 = Tile::tiles[this->level->getTile(this->selectedObject.field_4, this->selectedObject.field_8, this->selectedObject.field_C)]) != 0 && v9->isLiquidTile()) {
				this->player->stopDestroying();
				this->gameMode->stopDestroyBlock();
			} else {
				this->gameMode->continueDestroyBlock(this->selectedObject.field_4, this->selectedObject.field_8, this->selectedObject.field_C, this->selectedObject.field_10);
				this->particleEngine->crack(this->selectedObject.field_4, this->selectedObject.field_8, this->selectedObject.field_C, this->selectedObject.field_10);
			}
		}
	}
}
bool_t Minecraft::hostMultiplayer(int32_t port) {
	RakNetInstance* rakNetInstance; // r0

	this->rakNetInstance->disconnect();
	if(this->serverSideNetworkHandler) {
		delete this->serverSideNetworkHandler;
	}
	this->serverSideNetworkHandler = 0;
	this->serverSideNetworkHandler = new ServerSideNetworkHandler(this, this->rakNetInstance);
	return this->rakNetInstance->host(this->user->username, port, 4u);
}
void Minecraft::init(void) {
	//TODO something related to clientId.txt
	this->supportsNonTouchScreen = this->platform()->supportsTouchscreen();
	this->options.init(this, this->field_D00);
	this->options.update();
	this->externalServerFile = std::shared_ptr<ExternalServerFile>(new ExternalServerFile(this->field_D00));
	this->externalServerFile->load();
	this->checkGLError("Init enter");
	this->platform()->supportsTouchscreen(); //calls it again for some reason
	this->user = new User(this->options.username, "");
	this->setIsCreativeMode(0);
	this->_reloadInput();
	this->setSize(this->field_1C, this->field_20);
	this->mojangConnector = std::shared_ptr<MojangConnector>(new MojangConnector(this));
}
bool_t Minecraft::isCreativeMode(void) {
	return this->isCreative;
}
bool_t Minecraft::isKindleFire(int32_t) {
	printf("Minecraft::isKindleFire - not implemented\n");
	return 0;
}
bool_t Minecraft::isLevelGenerated(void) {
	if(this->level) return this->levelGenerated;
	return 0;
}
bool_t Minecraft::isOnline(void) {
	return this->serverSideNetworkHandler != 0;
}
bool_t Minecraft::isOnlineClient(void) {
	if(this->level) return this->level->isClientMaybe;
	return 0;
}

void Minecraft::joinMultiplayer(const struct PingedCompatibleServer& a2, bool_t a3) {
	RakNetInstance* rakNetInstance; // r4
	if(1 || this->field_18) {
		if(this->serverSideNetworkHandler) {
			this->field_18 = 0;
			if(a3) {
				((ClientSideNetworkHandler*)this->serverSideNetworkHandler)->setRealmsServer();
			}
			this->rakNetInstance->connect(a2.field_4.ToString(0, '|'), a2.field_4.GetPort());
		}
	}
}
void Minecraft::leaveGame(bool_t a2, bool_t a3) {
	bool field_CF4; // r5
	bool v7; // r7
	LevelStorage* ls; // r0

	field_CF4 = this->field_CF4;
	if(!this->field_CF4 && this->levelGenerated) {
		this->field_CF4 = field_CF4;
		if(this->level) {
			if(this->level->isClientMaybe) {
				if(!a2) {
					field_CF4 = 0;
					v7 = 0;
					goto LABEL_7;
				}
			} else {
				field_CF4 = 1;
			}
			v7 = 1;
		} else {
			field_CF4 = 0;
			v7 = 0;
		}
LABEL_7:
		this->rakNetInstance->disconnect();
		if(v7) {
			this->level->getChunkSource()->saveAll(1);
			if(field_CF4) {
				this->level->savePlayers();
			}
		}
		this->viewEntityMaybe = 0;
		this->levelRenderer->setLevel(0);
		this->particleEngine->setLevel(0);
		if(this->serverSideNetworkHandler) {
			delete this->serverSideNetworkHandler;
		}
		this->serverSideNetworkHandler = 0;
		if(this->level) {
			ls = this->level->getLevelStorage();
			if(ls) {
				delete ls;
			}
			if(this->level) {
				delete this->level;
			}
			this->level = 0;
		}
		this->player = 0;
		this->viewEntityMaybe = 0;
		this->field_CFC = 0;
		if ( a3 )
		{
			if ( a2 )
			{
				this->setScreen(new RenameMPLevelScreen(LevelStorageSource::TempLevelId));
			}
			else
			{
				this->screenChooser.setScreen(START_MENU_SCREEN);
			}
		}
	}
}
void Minecraft::locateMultiplayer(void) {
	this->field_18 = 1;
	this->rakNetInstance->pingForHosts(19132);
	if(this->serverSideNetworkHandler) {
		delete this->serverSideNetworkHandler;
	}

	this->serverSideNetworkHandler = new ClientSideNetworkHandler(this, this->rakNetInstance);
}
void Minecraft::lockForControl(void) {
	this->cmutex->lock();
}
void Minecraft::onAppResumed(void) {
	this->texturesPtr->clear(0);
	glBufferPool.trim();
	this->field_190 = 0;
}
void Minecraft::onAppSuspended(void) {
	this->texturesPtr->clear(0);
	glBufferPool.trim();
}
void Minecraft::onMojangConnectorStatus(enum MojangConnectionStatus a2) {
	if(this->currentScreen) this->currentScreen->onMojangConnectorStatus(a2);
}
void Minecraft::onUpdatedClient(int32_t a2, int32_t a3, int32_t a4, int32_t a5) {
	int32_t old = SharedConstants::getVersionCode(a2, a3, a4, 0);
	if(old < SharedConstants::getVersionCode(0, 8, 1, 0)) {
		this->levelStorageSource->clearCache();
	}
}
void Minecraft::optionUpdated(const Options::Option* a2, bool_t a3) {
	if(this->serverSideNetworkHandler) {
		if(a2 == &Options::Option::SERVER_VISIBLE) {
			((ServerSideNetworkHandler*)this->serverSideNetworkHandler)->allowIncomingConnections(a3);
		}
	}
	if(a2 == &Options::Option::GRAPHICS) {
		this->levelRenderer->allChanged();
		this->gameRenderer->itemInHandRenderer->onAppSuspended();
	}
	if(a2 == &Options::Option::LEFT_HANDED || a2 == &Options::Option::USE_TOUCH_JOYPAD || a2 == &Options::Option::USE_TOUCHSCREEN) {
		this->_reloadInput();
	}
}
void Minecraft::optionUpdated(const Options::Option* a2, float a3) {
	float v4; // s13

	if(&Options::Option::PIXELS_PER_MILLIMETER == a2) {
		v4 = a3 * Gui::InvGuiScale;
		this->field_C8C = a3 * Gui::InvGuiScale;
		this->field_C90 = 1.0 / v4;
		this->field_C84 = a3;
		this->field_C88 = 1.0 / a3;
		Config v6 = createConfig(this);
		this->gui.onConfigChanged(v6);
		if(this->inputHolder) {
			this->inputHolder->onConfigChanged(v6);
		}
	}
}
void Minecraft::optionUpdated(const Options::Option* a2, int32_t a3) {
	if(&Options::Option::RENDER_DISTANCE == a2) {
		this->levelRenderer->allChanged();
	}
}
void Minecraft::pauseGame(bool_t a2) {
	if(!this->currentScreen) {
		this->screenChooser.setScreen(a2 ? PAUSE_SCREEN_1 : PAUSE_SCREEN_0);
	}
}
void Minecraft::prepareLevel(const std::string& a2) {
	Level* level;	   // r0
	int32_t v4;		   // r6
	int32_t v5;		   // r8
	int32_t i;		   // r5
	int32_t v7;		   // r7
	int32_t v8;		   // r6
	LevelChunk* chunk; // r0
	int32_t j;		   // r5
	Level* v11;		   // r0

	this->progressMessageIndex = 1;
	Stopwatch v13; // [sp+4h] [bp-13Ch] BYREF
	Stopwatch v14; // [sp+38h] [bp-108h] BYREF
	Stopwatch v15; // [sp+68h] [bp-D8h] BYREF
	Stopwatch v16; // [sp+98h] [bp-A8h] BYREF
	Stopwatch v17; // [sp+C8h] [bp-78h] BYREF
	v13.start();
	Stopwatch v18; // [sp+F8h] [bp-48h] BYREF

	level = this->level;
	if(!level->field_B64) {
		level->setUpdateLights(0);
	}
	v4 = 0;
	v5 = 8;
	do {
		v7 = v4;
		for(i = 8; i != 264; i += 16) {
			this->field_CBC = v7 >> 8;
			v14.start();
			this->level->getTile(v5, 64, i);
			v14.stop();
			v18.start();
			if(this->level->field_B64) {
				while(this->level->updateLights()) {
					;
				}
			}
			v18.stop();
			v7 += 100;
		}
		v4 += 1600;
		v5 += 16;
	} while(v4 != 25600);
	v8 = 0;
	v13.stop();
	this->level->setUpdateLights(1);
	v15.start();
	do {
		for(j = 0; j != 16; ++j) {
			chunk = this->level->getChunk(v8, j);
			if(chunk) {
				if(!chunk->field_24B) {
					chunk->unsaved = 0;
					chunk->clearUpdateMap();
				}
			}
		}
		++v8;
	} while(v8 != 16);
	v15.stop();
	v17.start();
	v11 = this->level;
	this->progressMessageIndex = 3;
	if(v11->field_B64) {
		v11->setInitialSpawn();
		this->level->getChunkSource()->saveAll(0);
		this->level->saveGame();
	} else {
		v11->saveLevelData();
		this->level->loadEntities();
	}
	v17.stop();
	this->field_CBC = -1;
	this->progressMessageIndex = 2;
	v16.start();
	this->level->prepare();
	v16.stop();

	v13.print("Generate level: ");
	v18.print(" - light: ");
	v14.print(" - getTl: ");
	v15.print(" - clear: ");
	v16.print(" - prepr: ");
	v17.print(" - store: ");
}
void* Minecraft::prepareLevel_tspawn(void* a2) {
	((Minecraft*)a2)->generateLevel("Currently not used", ((Minecraft*)a2)->level);
	return 0;
}
void Minecraft::releaseMouse(void) {
	if(this->mouseGrabbed) {
		if(this->player) {
			this->player->releaseAllKeys();
		}
		this->mouseGrabbed = 0;
		this->mouseHandler.release();
	}
}
void Minecraft::reloadOptions(void) {
	this->options.update();
	this->options.save();
	bool_t useTouchscreen = this->options.useTouchscreen;
	this->options.useTouchscreen = this->useTouchscreen();
	this->options.save();
	if(this->options.useTouchscreen != useTouchscreen || !this->inputHolder) {
		this->_reloadInput();
	}
	this->user->username = this->options.username;
}
void Minecraft::resetPlayer(Player* a2) {
	this->level->validateSpawn();
	a2->reset();
	TilePos result = a2->hasRespawnPosition() ? a2->getRespawnPosition() : this->level->getSharedSpawnPos(); // [sp+4h] [bp-1Ch] OVERLAPPED BYREF

	a2->setPos((float)result.x + 0.5, (float)result.y + 1.0, (float)result.z + 0.5);
	a2->resetPos(1);
}
Player* Minecraft::respawnPlayer(int32_t a2) {
	int32_t v6 = 0;
	int32_t v7 = this->level->playersMaybe.size();
	for(v6 = 0; v6 != v7; ++v6) {
		Player* p = this->level->playersMaybe[v6];
		if(p->entityId == a2) {
			this->resetPlayer(p);
			return this->level->playersMaybe[v6];
		}
	}
	return 0;
}

void Minecraft::respawnPlayer(void) {
	this->resetPlayer(this->player);
	RespawnPacket v4(this->player);
	this->rakNetInstance->send(v4);
}
void Minecraft::selectLevel(const std::string& a2, const std::string& a3, const struct LevelSettings& a4) {
	LevelStorage* v7 = this->levelStorageSource->selectLevel(a2, 0);
	this->level = new ServerLevel(v7, a3, a4, 0, 0);
	this->setLevel(this->level, "Generating level", 0);
	this->setIsCreativeMode(this->level->getLevelData()->getGameType() == 1);
	this->field_CFC = 1;
}
void Minecraft::setIsCreativeMode(bool_t a2) {
	if(this->gameMode) {
		if(this->isCreative == a2) goto LABEL_8;
		delete this->gameMode;
	}
	if(a2) this->gameMode = new CreativeMode(this);
	else this->gameMode = new SurvivalMode(this);
	this->isCreative = a2;
LABEL_8:
	if(this->player) {
		this->gameMode->initAbilities(this->player->abilities);
	}
}
void Minecraft::setLeaveGame(void) {
	this->field_D22 = 1;
}
void Minecraft::setLevel(struct Level* level, const std::string& a3, struct LocalPlayer* a4) {
	LocalPlayer* player; // r1
	CThread* v8;		 // r5

	this->viewEntityMaybe = 0;
	level->getSeed();
	if(level) {
		level->rakNetInstance = this->rakNetInstance;
		this->gameMode->initLevel(level);
		player = this->player;
		if(player) {
			player->resetPos(0);
			level->addEntity(this->player);
		} else if(a4) {
			this->player = a4;
			a4->resetPos(0);
		}
		this->level = level;
		this->levelGenerated = 0;
		this->field_CF4 = 1;
		v8 = new CThread(&Minecraft::prepareLevel_tspawn, this);
		this->prepareLevelThread = v8;
	} else {
		this->player = 0;
	}
	this->field_C54 = 0;
	this->field_CFC = 1;
}
void Minecraft::setScreen(Screen* screen) {
	Mouse::reset();
	Multitouch::reset();
	Multitouch::resetThisUpdate();
	if(this->field_D14) {
		this->field_D18 = screen;
		this->field_D15 = 1;
		return;
	}

	if(screen) {
		if(screen->isErrorScreen()) return;
	} else if(!this->currentScreen) return;

	if(this->currentScreen) this->currentScreen->removed();
	this->currentScreen = screen;
	this->field_C7C = std::shared_ptr<Screen>(screen);
	if(this->currentScreen) {
		this->releaseMouse();
		this->currentScreen->init(this, this->field_1C * Gui::InvGuiScale, this->field_20 * Gui::InvGuiScale);
		if(this->currentScreen->isInGameScreen()) {
			if(this->level) this->level->saveGame();
		}
	} else {
		this->grabMouse();
	}
}
void Minecraft::setSize(int32_t a2, int32_t a3) {
	this->transformResolution(&a2, &a3);

	this->field_1C = a2;
	this->field_20 = a3;
	if(a2 == 0) this->field_1C = 240;
	if(a3 == 0) this->field_20 = 140;

	float ppm;
	if(this->platform()) {
		ppm = this->platform()->getPixelsPerMillimeter();
	} else {
		ppm = 10;
	}

	float gscale;
	if(this->field_1C >= 1000) {
		if(ppm <= 15) gscale = 4;
		else gscale = 6;
	} else if(this->field_1C >= 800) {
		gscale = 3;
	} else if(this->field_1C >= 400) {
		gscale = 2;
	} else {
		Gui::GuiScale = 1;
		goto CALCULATE_INVERSE;
	}
	Gui::GuiScale = gscale;
CALCULATE_INVERSE:
	Gui::InvGuiScale = 1.0 / Gui::GuiScale;
	if(this->platform()) {
		float pv = this->options.getProgressValue(&Options::Option::PIXELS_PER_MILLIMETER);
		this->field_C84 = pv;
		this->field_C88 = 1.0 / pv;
		float v13 = pv * Gui::InvGuiScale;
		this->field_C8C = pv * Gui::InvGuiScale;
		this->field_C90 = 1.0 / v13;
	}
	Config v18 = createConfig(this);
	this->gui.onConfigChanged(v18);
	if(this->currentScreen) {
		this->currentScreen->setSize(this->field_1C * Gui::InvGuiScale, this->field_20 * Gui::InvGuiScale);
		this->currentScreen->setupPositions();
	}
	if(this->inputHolder) {
		this->inputHolder->onConfigChanged(v18);
	}
}
void Minecraft::setTextboxText(const std::string& a2) {
	if(this->currentScreen) this->currentScreen->setTextboxText(a2);
}
bool_t Minecraft::supportNonTouchscreen(void) {
	return this->supportsNonTouchScreen;
}
void Minecraft::teardown(void) {
	if(this->serverSideNetworkHandler) {
		delete this->serverSideNetworkHandler;
	}
	if(this->rakNetInstance) {
		delete this->rakNetInstance;
	}
	if(this->levelRenderer) {
		delete this->levelRenderer;
	}

	if(this->gameRenderer) {
		delete this->gameRenderer;
	}

	if(this->particleEngine) {
		delete this->particleEngine;
	}

	if(this->soundEngine) {
		delete this->soundEngine;
	}

	if(this->gameMode) {
		delete this->gameMode;
	}

	if(this->font) {
		delete this->font;
	}

	if(this->texturesPtr) {
		delete this->texturesPtr;
	}

	this->mojangConnector = 0;
	if(this->level) {
		this->level->saveGame();
		this->level->savePlayers();
		if(this->level->getChunkSource()) {
			this->level->getChunkSource()->saveAll(1);
		}

		LevelStorage* ls = this->level->getLevelStorage();
		if(ls) delete ls;

		if(this->level) delete this->level;
		this->level = 0;
	}
	if(this->user) {
		delete this->user;
	}
	if(this->inputHolder) {
		delete this->inputHolder;
	}
	if(this->levelStorageSource) {
		delete this->levelStorageSource;
	}
	if(this->perfRenderer) {
		delete this->perfRenderer;
	}

	if(this->commandServer) {
		delete this->commandServer;
	}

	if(this->cmutex) {
		delete this->cmutex;
	}

	if(this->field_D30) {
		delete this->field_D30;
	}

	MobFactory::getStaticTestMob(0, 0); //TODO used as param for destroy??
	EntityRenderDispatcher::destroy();
}
void Minecraft::tick(int32_t a2, int32_t a3) {
	int32_t field_D08;

	if(this->field_D22) {
		this->field_D22 = 0;
		this->leaveGame(0, 0);
	}
	field_D08 = this->field_D08;
	if(field_D08 > 0) this->field_D08 = field_D08 - 1;

	if(!this->currentScreen) {
		if(this->player) {
			if(this->player->health <= 0) {
				this->setScreen(new DeathScreen());
			}
		}
	}

	if(this->level) {
		if(!this->field_16C) {
			this->gameMode->tick();
		}
	}
	if(this->level) {
		if(this->commandServer) {
			this->commandServer->tick();
		}
	}

	this->tickInput();
	this->gui.tick();

	if(!this->field_CF4) {
		if(!this->levelGenerated) {
			if(this->prepareLevelThread) {
				delete this->prepareLevelThread;
				this->prepareLevelThread = 0;
			}
			this->_levelGenerated();
		}

		if(this->level) {
			if(!this->field_16C) {
				this->gameRenderer->tick(a2, a3);
				this->levelRenderer->tick();
				this->level->difficulty = this->options.difficulty;
				if(this->level->isClientMaybe) this->level->difficulty = 1;
				this->level->tickEntities();
				this->level->tick();
				if(this->player) {
					float posX = this->player->posX;
					int v15 = (int)posX;
					bool v16 = posX < (float)(int)posX;
					float posY = this->player->posY;
					int v18 = (int)posY;
					if(v16) {
						--v15;
					}
					bool v19 = posY < (float)(int)posY;
					float posZ = this->player->posZ;
					int v21 = (int)posZ;
					if(v19) {
						--v18;
					}
					if(posZ < (float)(int)posZ) {
						--v21;
					}
					this->level->animateTick(v15, v18, v21);
				}
			}
		}

		this->texturesPtr->loadAndBindTexture("terrain-atlas.tga");
		if(this->field_16C) goto DONT_TICK_GAME;

		if(this->currentScreen) {
			if(!this->currentScreen->renderGameBehind()) {
				goto DONT_TICK_GAME;
			}
		}

		if(this->options.animateTextures) {
			if(a2 == a3) this->texturesPtr->tick(1);
		} else if(!this->field_190) {
			int32_t maxTextureTicks = 40;
			this->field_190 = 1;
			do {
				this->texturesPtr->tick(0);
				--maxTextureTicks;
			} while(maxTextureTicks);
			this->texturesPtr->tick(1);
		}

DONT_TICK_GAME:
		this->particleEngine->tick();
		if(this->currentScreen) {
			this->field_D14 = 1;
			this->currentScreen->tick();
			this->field_D14 = 0;
		}
		Multitouch::reset();
	}
}
void Minecraft::tickInput(void) {
	if(this->currentScreen) {
		if(!this->currentScreen->field_C) {
			this->field_D14 = 1;
			this->currentScreen->updateEvents();
			this->field_D14 = 0;
			if(this->field_D15) {
				this->setScreen(this->field_D18);
				this->field_D18 = 0;
				this->field_D15 = 0;
			}
			Mouse::reset();
			Keyboard::reset();
			return;
		}
	}
	if(!this->player) {
		Mouse::reset();
		Keyboard::reset();
		return;
	}

#ifdef PCTWEAKS
	//fix bow and other useitem stuff
	if(this->field_D0C > 0) {
		this->field_D0C = this->field_D0C - 1;
	}
#endif

	int v4 = Mouse::getX();
	int v5 = Mouse::getY();
	bool isInside = this->gui.isInside(v4, v5);
	while(Mouse::next()) {
		if(getTimeMs() - this->field_C54 <= 200) {
			MouseAction* ev = Mouse::getEvent();
			if(*(int16_t*)&ev->evButton == 0x101) //TODO dont do those evil things
			{
				this->gui.handleClick(1, Mouse::getX(), Mouse::getY());
			}
			if(ev->evButton == 3) {
				int n = this->gui.getNumSlots();
				this->player->inventory->selectSlot((this->player->inventory->selectedSlot - ev->field_6 + n - 1) % (n - 1));
			}
		}
	}
	while(1) {
		int v14 = Keyboard::_index + 1;
		if(Keyboard::_index + 1 >= Keyboard::_inputs.size()) {
			break;
		}
		LocalPlayer* player = this->player;
		++Keyboard::_index;
		KeyboardAction* v16 = &Keyboard::_inputs[v14];
		int v17 = v16->field_4;
		bool v18 = v16->field_0 == 1;
		player->setKey(v17, v16->field_0 == 1);
		if(v18) {
			this->gui.handleKeyPressed(v17);
			if(v17 == 255 && !this->currentScreen) {
				this->setScreen(new PauseScreen(1));
			}
		}

		if(!this->options.field_17 && getTimeMs() - this->field_C54 <= 200) {
			if(v17 == this->options.keyDestroy.keyCode && v18) {
				BuildActionIntention v24{10};
				this->handleBuildAction(&v24);
			} else if(v17 == this->options.keyUse.keyCode && v18) {
				BuildActionIntention v24{17};
				this->handleBuildAction(&v24);
			}
		}
	}
	BuildActionIntention v24{0};
	IBuildInput* v22 = this->inputHolder->getBuildInput();
	bool v23 = v22->tickBuild(this->player, &v24);
	if(v23) {
		if((v24.field_0 & 2) == 0) {
			this->handleBuildAction(&v24);
		}
	}

	int v19;
	if(this->options.field_17) {
		if(Mouse::isButtonDown(1) && !isInside) {
			v19 = 1;
			goto LABEL_39;
		}
	} else if(Keyboard::_states[this->options.keyDestroy.keyCode] == 1) {
		v19 = 1;
		goto LABEL_39;
	}
	if(v23) {
		if(v24.isRemove()) {
			v19 = 1;
			goto LABEL_39;
		}
		v19 = ((unsigned int)v24.field_0 >> 4) & 1;
	} else {
		v19 = 0;
	}
LABEL_39:
	this->handleMouseDown(1, v19);
	this->field_C54 = getTimeMs();
RESET_STUFF:
	Mouse::reset();
	Keyboard::reset();
}
bool_t Minecraft::transformResolution(int32_t* x, int32_t* y) {
	if(this->isKindleFire(1)) {
		if(*y >= 560 && *y <= 620) {
			*y = 580;
			return 1;
		}
	}
	return 0;
}
void Minecraft::unlockControl(void) {
	this->cmutex->unlock();
}

void Minecraft::update(void) {
	this->cmutex->lock();
	if(this->field_16C && this->level) {
		float v14 = this->timer.field_8;
		this->timer.advanceTime();
		this->timer.field_8 = v14;
	} else {
		this->timer.advanceTime();
	}
	if(this->rakNetInstance) {
		this->rakNetInstance->runEvents(this->serverSideNetworkHandler);
	}
	for(int32_t i = 0; i < this->timer.ticks; ++i) {
		this->tick(i, this->timer.ticks - 1);
		++this->field_D10;
	}
	if(this->level) {
		if(!this->field_CF4) {
			this->level->updateLights();
		}
	}

	if(this->gameMode) {
		this->gameMode->render(this->timer.field_8);
	}

	this->soundEngine->update(this->player, this->timer.field_8);
	this->gameRenderer->render(this->timer.field_8);
	this->checkGLError("Update finished");

	if(this->options.field_EE) {
		if(!PerfTimer::enabled) {
			PerfTimer::reset();
			PerfTimer::enabled = 1;
		}
		this->perfRenderer->renderFpsMeter(1);
		this->checkGLError("render debug");
	} else {
		PerfTimer::enabled = 0;
	}
	this->cmutex->unlock();
	this->mojangConnector->updateUIThread();
	double result = getTimeS();
	this->field_D34 = result - this->timeStartedAtMaybe;
	this->timeStartedAtMaybe = result;
}

void Minecraft::updateStatusUserAttributes(void) {
	this->platform()->updateStatsUserData((char_t*)glGetString(0x1f00), (char_t*)glGetString(0x1f01));
}

bool_t Minecraft::useTouchscreen(void) {
	return 0;
	//TODO touchscreen support return this->options.useTouchscreen || !this->supportsNonTouchScreen;
}
Minecraft::~Minecraft() {
}
