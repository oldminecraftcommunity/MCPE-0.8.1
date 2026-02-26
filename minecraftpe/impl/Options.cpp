#include <Options.hpp>
#include <Minecraft.hpp>
#include <OptionStrings.hpp>
#include <entity/player/User.hpp>
#include <network/mco/MojangConnector.hpp>
#include <sstream>
#include <util/Util.hpp>
#include <I18n.hpp>

Options::Option Options::Option::MUSIC{1, "options.music", 0};
Options::Option Options::Option::SOUND{1, "options.sound", 1};
Options::Option Options::Option::INVERT_MOUSE{0, "options.invertMouse", 2};
Options::Option Options::Option::SENSITIVITY{1, "options.sensitivity", 3};
Options::Option Options::Option::RENDER_DISTANCE{3, "options.renderDistance", 4};
Options::Option Options::Option::VIEW_BOBBING{0, "options.viewBobbing", 5};
Options::Option Options::Option::LIMIT_FRAMERATE{0, "options.limitFramerate", 7};
Options::Option Options::Option::DIFFICULTY{3, "options.difficulty", 8};
Options::Option Options::Option::GRAPHICS{0, "options.graphics", 9};
Options::Option Options::Option::GUI_SCALE{3, "options.guiScale", 11};
Options::Option Options::Option::THIRD_PERSON{0, "options.thirdperson", 12};
Options::Option Options::Option::HIDE_GUI{0, "options.hidegui", 13};
Options::Option Options::Option::SERVER_VISIBLE{0, "options.servervisible", 14};
Options::Option Options::Option::LEFT_HANDED{0, "options.lefthanded", 15};
Options::Option Options::Option::USE_TOUCHSCREEN{0, "options.usetouchscreen", 16};
Options::Option Options::Option::USE_TOUCH_JOYPAD{0, "options.usetouchpad", 17};
Options::Option Options::Option::DESTROY_VIBRATION{0, "options.destroyvibration", 18};
Options::Option Options::Option::FANCY_SKIES{0, "options.fancyskies", 19};
Options::Option Options::Option::ANIMATE_TEXTURES{0, "options.animatetextures", 20};
Options::Option Options::Option::PIXELS_PER_MILLIMETER{1, "options.pixelspermilimeter", 21};
Options::Option Options::Option::NAME{2, "options.name", 22};
std::vector<int32_t> Options::DIFFICULTY_LEVELS = {0, 2};
std::vector<int32_t> Options::RENDERDISTANCE_LEVELS = {3, 2, 1, 0};

void Options::update() {
	//TODO
	printf("Options::update not implemented\n");
}

void Options::validateVersion(void) {
	if(this->major || this->minor != 8 || this->patch != 1 || this->beta) {
		this->minecraft->onUpdatedClient(this->major, this->minor, this->patch, this->beta);
		this->major = 0;
		this->minor = 8;
		this->beta = 0;
		this->patch = 1;
		this->save();
	}
}

void Options::toggle(const Options::Option* a2, int32_t a3) {
	bool_t bv; // r0

	if(a2 == &Options::Option::INVERT_MOUSE) {
		this->invertMouse ^= 1u;
	} else if(a2 == &Options::Option::RENDER_DISTANCE) {
		this->renderDistance = (a3 + (uint8_t)this->renderDistance) & 3;
	} else if(a2 == &Options::Option::GUI_SCALE) {
		this->guiScale = (a3 + (uint8_t)this->guiScale) & 3;
	} else if(a2 == &Options::Option::VIEW_BOBBING) {
		this->viewBobbing ^= 1u;
	} else if(a2 == &Options::Option::THIRD_PERSON) {
		this->thirdPerson ^= 1u;
	} else if(a2 == &Options::Option::HIDE_GUI) {
		this->hideGUI ^= 1u;
	} else if(a2 == &Options::Option::SERVER_VISIBLE) {
		this->serverVisible ^= 1u;
	} else if(a2 == &Options::Option::LEFT_HANDED) {
		this->leftHanded ^= 1u;
	} else if(a2 == &Options::Option::USE_TOUCHSCREEN) {
		this->useTouchscreen ^= 1u;
	} else if(a2 == &Options::Option::USE_TOUCH_JOYPAD) {
		this->useJoypad ^= 1u;
	} else if(a2 == &Options::Option::DESTROY_VIBRATION) {
		this->destroyVibration ^= 1u;
	} else if(a2 == &Options::Option::GRAPHICS) {
		this->graphics ^= 1u;
	} else if(a2 == &Options::Option::FANCY_SKIES) {
		this->fancySkies ^= 1u;
	} else if(a2 == &Options::Option::ANIMATE_TEXTURES) {
		this->animateTextures ^= 1u;
	} else if(a2 == &Options::Option::LIMIT_FRAMERATE) {
		this->limitFramerate ^= 1u;
	} else if(a2 == &Options::Option::DIFFICULTY) {
		this->difficulty = (a3 + (uint8_t)this->difficulty) & 3;
	}
	bv = this->getBooleanValue(a2);
	this->notifyOptionUpdate(a2, bv);
	this->save();
}
void Options::setKey(int32_t a2, int32_t a3) {
	this->keys[a2]->keyCode = a3;
	this->save();
}
void Options::setAdditionalHiddenOptions(const std::vector<const Options::Option*>& a2) {
	this->hiddenOptionsVec = a2;
}
void Options::set(const Options::Option* a2, std::string a3) {
	if(&Options::Option::NAME == a2) {
		if(a3.size() == 0) {
			a3 = "Steve";
		}
		this->username = a3;
		if(this->minecraft->user) {
			this->minecraft->user->username = a3;
		}
	}
}
void Options::set(const Options::Option* a2, int32_t a3) {
	if(a2 == &Options::Option::DIFFICULTY) {
		this->difficulty = a3;
	} else if(a2 == &Options::Option::RENDER_DISTANCE) {
		this->renderDistance = a3;
	}
	this->notifyOptionUpdate(a2, a3);
}
void Options::set(const Options::Option* a2, float a3) {
	if(a2 == &Options::Option::MUSIC) {
		this->musicVolume = a3;
	} else if(a2 == &Options::Option::SOUND) {
		this->soundVolume = a3;
	} else if(a2 == &Options::Option::SENSITIVITY) {
		this->sensitity = a3;
	} else if(a2 == &Options::Option::PIXELS_PER_MILLIMETER) {
		this->pixelDensity = a3;
	}
	this->notifyOptionUpdate(a2, a3);
}
void Options::save(void) {
	std::vector<std::string> v4;
	this->addOptionToSaveOutput(v4, OptionStrings::Multiplayer_Username, this->username);
	this->addOptionToSaveOutput(v4, OptionStrings::Game_DifficultyLevel, this->difficulty);
	this->addOptionToSaveOutput(v4, OptionStrings::Game_ThirdPerson, this->thirdPerson);
	this->addOptionToSaveOutput(v4, OptionStrings::Graphics_PixelsPerMilimeter, this->pixelDensity);
	this->addOptionToSaveOutput(v4, OptionStrings::Multiplayer_ServerVisible, this->serverVisible);
	this->addOptionToSaveOutput(v4, OptionStrings::Controls_Sensitivity, this->sensitity);
	this->addOptionToSaveOutput(v4, OptionStrings::Controls_InvertMouse, this->invertMouse);
	this->addOptionToSaveOutput(v4, OptionStrings::Controls_IsLefthanded, this->leftHanded);
	this->addOptionToSaveOutput(v4, OptionStrings::Controls_UseTouchScreen, this->useTouchscreen);
	this->addOptionToSaveOutput(v4, OptionStrings::Controls_UseTouchJoypad, this->useJoypad);
	this->addOptionToSaveOutput(v4, OptionStrings::Controls_FeedbackVibration, this->destroyVibration);
	this->addOptionToSaveOutput(v4, OptionStrings::Graphics_RenderDistance, this->renderDistance);
	this->addOptionToSaveOutput(v4, OptionStrings::Graphics_FancyGraphics, this->graphics);
	this->addOptionToSaveOutput(v4, OptionStrings::Graphics_FancySkies, this->fancySkies);
	this->addOptionToSaveOutput(v4, OptionStrings::Graphics_AnimateTextures, this->animateTextures);
	this->addOptionToSaveOutput(v4, OptionStrings::Graphics_HideGUI, this->hideGUI);
	this->addOptionToSaveOutput(v4, OptionStrings::AUDIO_Sound, this->soundVolume);
	this->addOptionToSaveOutput(v4, OptionStrings::Last_Game_Version_Major, this->major);
	this->addOptionToSaveOutput(v4, OptionStrings::Last_Game_Version_Minor, this->minor);
	this->addOptionToSaveOutput(v4, OptionStrings::Last_Game_Version_Patch, this->patch);
	this->addOptionToSaveOutput(v4, OptionStrings::Last_Game_Version_Beta, this->beta);
	this->settingFolderPath.save(v4);
}
bool_t Options::readInt(const std::string& a1, int32_t& a2) {
	if(a1 == "true" || a1 == "YES") {
		a2 = 1;
		return 1;
	} else {
		if(a1 == "false" || a1 == "NO") {
			a2 = 0;
			return 1;
		}
		return sscanf(a1.c_str(), "%d", &a2) != 0;
	}
}
bool_t Options::readFloat(const std::string& a1, float& a2) {
	if(a1 == "true" || a1 == "YES") {
		a2 = 1;
		return 1;
	} else {
		if(a1 == "false" || a1 == "NO") {
			a2 = 0;
			return 1;
		}
		return sscanf(a1.c_str(), "%f", &a2) != 0;
	}
}
bool_t Options::readBool(const std::string& r0, bool_t& a2) {
	std::string a1 = Util::stringTrim(r0);
	if(a1 == "true" || a1 == "1" || a1 == "YES") {
		a2 = 1;
		return 1;
	} else {
		if(a1 == "false" || a1 == "0" || a1 == "NO") {
			a2 = 0;
			return 1;
		}
		return 0;
	}
}
void Options::notifyOptionUpdate(const Options::Option* a2, int32_t a3) {
	this->minecraft->optionUpdated(a2, a3);
}
void Options::notifyOptionUpdate(const Options::Option* a2, float a3) {
	this->minecraft->optionUpdated(a2, a3);
}
void Options::notifyOptionUpdate(const Options::Option* a2, bool_t a3) {
	this->minecraft->optionUpdated(a2, a3);
}
void Options::load(void) {
}
void Options::initDefaultValues(void) {
	this->beta = 0;
	this->field_F0 = 1;
	this->patch = 0;
	this->minor = 0;
	this->major = 0;
	this->hideGUI = 0;
	this->thirdPerson = 0;
	this->field_EE = 0;
	this->enableNoclipMaybe = 0;
	this->field_F1 = 0;
	this->difficulty = 2;
	this->destroyVibration = 1;
	this->viewBobbing = 1;
	this->graphics = 1;
	this->fancySkies = 1;
	this->animateTextures = 1;
	this->field_F4 = 1.0;
	this->field_F8 = 1.0;
	this->guiScale = 0;
	this->field_17 = 0;
	this->leftHanded = 0;
	this->useJoypad = 0;
	this->musicVolume = 1.0;
	this->soundVolume = 1.0;
	this->invertMouse = 0;
	this->sensitity = 0.5;
	this->limitFramerate = 0;
	this->renderDistance = 2;
	this->useTouchscreen = this->minecraft->supportNonTouchscreen();
	float v4 = this->minecraft->platform()->getPixelsPerMillimeter();
	if(v4 > 12) v4 = 12;
	else if(v4 <= 3) v4 = 3;

	this->pixelDensity = v4;
	this->username = "Steve";
	this->serverVisible = 1;
	this->keyForward = KeyMapping("key.forward", 87);
	this->keyLeft = KeyMapping("key.left", 65);
	this->keyBack = KeyMapping("key.back", 83);
	this->keyRight = KeyMapping("key.right", 68);
	this->keyJump = KeyMapping("key.jump", 32);
	this->keyInventory = KeyMapping("key.inventory", 69);
	this->keySneak = KeyMapping("key.sneak", 10);
	this->keyCrafting = KeyMapping("key.crafting", 81);
	this->keyDrop = KeyMapping("key.drop", 81);
	this->keyChat = KeyMapping("key.chat", 84);
	this->keyFog = KeyMapping("key.fog", 70);
	this->keyDestroy = KeyMapping("key.destroy", 88);
	this->keyUse = KeyMapping("key.use", 85);
	this->keyMenuNext = KeyMapping("key.menu.next", 40);
	this->keyMenuPrevious = KeyMapping("key.menu.previous", 38);
	this->keyMenuOk = KeyMapping("key.menu.ok", 13);
	this->keyMenuCancel = KeyMapping("key.menu.cancel", 8);
	this->keys[14] = &this->keyMenuOk;
	this->keys[15] = &this->keyMenuCancel;
	this->keys[2] = &this->keyBack;
	this->thirdPerson = 0;
	this->field_17 = 0;
	this->keys[3] = &this->keyRight;
	this->keyForward.keyCode = 19;
	this->keyLeft.keyCode = 21;
	this->keys[4] = &this->keyJump;
	this->keyRight.keyCode = 22;
	this->keyUse.keyCode = 103;
	this->keys[5] = &this->keySneak;
	this->keyJump.keyCode = 23;
	this->keys[0] = &this->keyForward;
	this->keys[6] = &this->keyDrop;
	this->keys[1] = &this->keyLeft;
	this->keys[10] = &this->keyDestroy;
	this->keys[7] = &this->keyInventory;
	this->keys[11] = &this->keyUse;
	this->keys[12] = &this->keyMenuNext;
	this->keys[8] = &this->keyChat;
	this->keyBack.keyCode = 20;
	this->keys[9] = &this->keyFog;
	this->keys[13] = &this->keyMenuPrevious;
	this->keyDestroy.keyCode = 102;
	this->keyMenuPrevious.keyCode = 19;
	this->keyMenuOk.keyCode = 23;
	this->keyCrafting.keyCode = 109;
	this->keyMenuCancel.keyCode = 4;
	this->keyMenuNext.keyCode = 20;
	this->setAdditionalHiddenOptions({});
}
bool_t Options::hideOption(const Options::Option* a2) {
	if(a2 == &Options::Option::USE_TOUCHSCREEN && this->minecraft->supportNonTouchscreen()) {
		return 1;
	}
	for(int32_t i = 0; i < this->hiddenOptionsVec.size(); ++i) {
		if(this->hiddenOptionsVec[i] == a2) {
			return 1;
		}
	}
	return 0;
}
std::vector<int> Options::getValues(const Options::Option* a2) {
	if(a2 == &Options::Option::DIFFICULTY) {
		return Options::DIFFICULTY_LEVELS;
	}
	if(a2 == &Options::Option::RENDER_DISTANCE) {
		return Options::RENDERDISTANCE_LEVELS;
	}
	return {};
}
std::string Options::getStringValue(const Options::Option* a2) {
	if(&Options::Option::NAME == a2) {
		return this->username;
	}
	return "";
}
float Options::getProgrssMin(const Options::Option* a2) {
	if(a2 == &Options::Option::MUSIC || a2 == &Options::Option::SOUND || a2 == &Options::Option::SENSITIVITY) {
		return 0;
	}
	if(a2 == &Options::Option::PIXELS_PER_MILLIMETER) {
		return 3;
	}
	return 0;
}
float Options::getProgrssMax(const Options::Option* a2) {
	if(a2 == &Options::Option::MUSIC || a2 == &Options::Option::SOUND || a2 == &Options::Option::SENSITIVITY) {
		return 1;
	}
	if(a2 == &Options::Option::PIXELS_PER_MILLIMETER) {
		return 12;
	}
	return 1;
}
float Options::getProgressValue(const Options::Option* a2) {
	if(a2 == &Options::Option::MUSIC) {
		return this->musicVolume;
	}
	if(a2 == &Options::Option::SOUND) {
		return this->soundVolume;
	}
	if(a2 == &Options::Option::SENSITIVITY) {
		return this->sensitity;
	}
	if(a2 == &Options::Option::PIXELS_PER_MILLIMETER) {
		return this->pixelDensity;
	}
	return 0;
}
std::string Options::getMessage(const Options::Option*) {
	return "Options::getMessage - Not implemented"; //actual mcpe code
}
std::string Options::getKeyMessage(int32_t) {
	return "Options::getKeyMessage not implemented"; //actual mcpe code
}
std::string Options::getKeyDescription(int32_t) {
	return "Options::getKeyDescription not implemented"; //yes
}
int32_t Options::getIntValue(const Options::Option* a2) {
	if(a2 == &Options::Option::DIFFICULTY) {
		return this->difficulty;
	}
	if(a2 == &Options::Option::RENDER_DISTANCE) {
		return this->renderDistance;
	}
	return 0;
}
std::string Options::getDescription(const Options::Option*, std::string a4) {
	return a4;
}
bool_t Options::getBooleanValue(const Options::Option* a2) {
	if(a2 == &Options::Option::INVERT_MOUSE) {
		return this->invertMouse;
	}
	if(a2 == &Options::Option::VIEW_BOBBING) {
		return this->viewBobbing;
	}
	if(a2 == &Options::Option::LIMIT_FRAMERATE) {
		return this->limitFramerate;
	}
	if(a2 == &Options::Option::THIRD_PERSON) {
		return this->thirdPerson;
	}
	if(a2 == &Options::Option::HIDE_GUI) {
		return this->hideGUI;
	}
	if(a2 == &Options::Option::SERVER_VISIBLE) {
		return this->serverVisible;
	}
	if(a2 == &Options::Option::LEFT_HANDED) {
		return this->leftHanded;
	}
	if(a2 == &Options::Option::USE_TOUCHSCREEN) {
		return this->useTouchscreen;
	}
	if(a2 == &Options::Option::USE_TOUCH_JOYPAD) {
		return this->useJoypad;
	}
	if(a2 == &Options::Option::DESTROY_VIBRATION) {
		return this->destroyVibration;
	}
	if(a2 == &Options::Option::FANCY_SKIES) {
		return this->fancySkies;
	}
	if(a2 == &Options::Option::ANIMATE_TEXTURES) {
		return this->animateTextures;
	}
	if(a2 == &Options::Option::GRAPHICS) {
		return this->graphics;
	}
	return 0;
}
std::string Options::formatDescriptionString(const Options::Option* a2, const char_t* a3, const char_t** a4, int32_t a5) {
	char_t v9[100];
	std::string v8 = I18n::get(a4[a5]);
	sprintf(v9, a3, v8.c_str());
	return v9;
}
bool_t Options::canModify(const Options::Option* a2) {
	return &Options::Option::NAME != a2 || this->minecraft->mojangConnector->getConnectionStatus() == STATUS_0;
}
void Options::addOptionToSaveOutput(std::vector<std::string>& a2, std::string a3, std::string a4) {
	std::stringstream v11;
	v11 << a3;
	v11 << ":";
	v11 << a4;
	a2.emplace_back(v11.str());
}
void Options::addOptionToSaveOutput(std::vector<std::string>& a2, std::string a3, int32_t a4) {
	std::stringstream v11;
	v11 << a3;
	v11 << ":";
	v11 << a4;
	a2.emplace_back(v11.str());
}
void Options::addOptionToSaveOutput(std::vector<std::string>& a2, std::string a3, float a4) {
	std::stringstream v11;
	v11 << a3;
	v11 << ":";
	v11 << a4;
	a2.emplace_back(v11.str());
}
void Options::addOptionToSaveOutput(std::vector<std::string>& a2, std::string a3, bool_t a4) {
	std::stringstream v11;
	v11 << a3;
	v11 << ":";
	v11 << a4;
	a2.emplace_back(v11.str());
}

void Options::init(Minecraft* mc, std::string a3) {
	this->minecraft = mc;
	//TODO this->settingFolderPath.setDefaultFolderPath(a3);
	this->initDefaultValues();
}
