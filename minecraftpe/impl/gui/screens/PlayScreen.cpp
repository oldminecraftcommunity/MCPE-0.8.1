#include <util/IntRectangle.hpp>
#include <gui/screens/PlayScreen.hpp>
#include <Minecraft.hpp>
#include <gui/PackedScrollContainer.hpp>
#include <rendering/Tesselator.hpp>
#include <gui/NinePatchFactory.hpp>
#include <algorithm>
#include <cpputils.hpp>
#include <ExternalServerFile.hpp>
#include <ExternalServer.hpp>
#include <network/RakNetInstance.hpp>
#include <network/mco/MojangConnector.hpp>
#include <gui/screens/CreateWorldScreen.hpp>
#include <gui/screens/AddExternalServerScreen.hpp>
#include <gui/elements/LocalServerListItemElement.hpp>
#include <level/storage/LevelStorageSource.hpp>
#include <cpputils.hpp>
#include <gui/elements/Label.hpp>
#include <network/RestService.hpp>
#include <network/mco/MCOParser.hpp>
#include <util/Base64.hpp>
#include <gui/screens/ProgressScreen.hpp>
#include <network/mco/MCOStringify.hpp>
#include <gui/elements/MCOServerListItemElement.hpp>

PlayScreen::PlayScreen(bool_t a2) : field_50(0), field_51(0), header(0),
	backButton(0), newButton(0), externalButton(0), frame(0), field_74(0), field_78(0),
	spinner(0), editButton(0), field_84(0), field_B4(0), field_118(a2 ? PlayScreenState::ELEVEN : PlayScreenState::ZERO){
	std::string v6 = "Welcome to the Minecraft Realms Alpha! We're still testing out features, but eventually Realms will let up to 10" " Pocket Edition users play together online. It's currently free, and limited to a set amount of servers. \n" "\n" "\n" "Realms will be an optional, paid service once it's released. Have fun!";
	std::string v7 = "Minecraft Realms is currently in a limited alpha test. More servers will be available to register from this page" " as the service is developed, so check back soon.\n" "\n" "Realms servers may be down or be reset while we are working toward the beta release.";
	std::string v8 = "Tap 'New' to create your own Realms server!\n\nFree during alpha.";
	this->setPlayScreenStateSetting(PlayScreenState::ZERO, 0, 0, 0, 0, 0, 0, PlayScreenPanel::NONE, "");
	this->setPlayScreenStateSetting(PlayScreenState::ONE, 0, 0, 0, 1, 0, 0, PlayScreenPanel::MESSAGE, v6);
	this->setPlayScreenStateSetting(PlayScreenState::TWO, 0, 0, 0, 0, 0, 0, PlayScreenPanel::MESSAGE, "");
	this->setPlayScreenStateSetting(PlayScreenState::THREE, 1, 0, 0, 0, 0, 1, PlayScreenPanel::MCO_SERVER_LIST, "");
	this->setPlayScreenStateSetting(PlayScreenState::FOUR, 1, 0, 0, 0, 0, 1, PlayScreenPanel::MESSAGE, v8);
	this->setPlayScreenStateSetting(PlayScreenState::FIVE, 1, 1, 1, 0, 0, 0, PlayScreenPanel::MCO_SERVER_LIST, "");
	this->setPlayScreenStateSetting(PlayScreenState::SIX, 1, 0, 0, 0, 0, 0, PlayScreenPanel::MCO_SERVER_LIST, "");
	this->setPlayScreenStateSetting(PlayScreenState::SEVEN, 1, 0, 0, 0, 0, 0, PlayScreenPanel::MESSAGE, v7);
	this->setPlayScreenStateSetting(PlayScreenState::EIGHT, 0, 0, 0, 0, 0, 0, PlayScreenPanel::MESSAGE, "");
	this->setPlayScreenStateSetting(PlayScreenState::NINE, 0, 0, 0, 0, 0, 0, PlayScreenPanel::JOIN_REALMS_0, "");
	this->setPlayScreenStateSetting(PlayScreenState::TEN, 0, 0, 0, 0, 0, 0, PlayScreenPanel::JOIN_REALMS_1, "");
	this->setPlayScreenStateSetting(PlayScreenState::ELEVEN, 1, 0, 0, 0, 0, 1, PlayScreenPanel::LOCAL_SERVER_LIST, "");
	this->setPlayScreenStateSetting(PlayScreenState::TWELVE, 1, 1, 0, 0, 1, 0, PlayScreenPanel::LOCAL_SERVER_LIST, "");
}
std::shared_ptr<PackedScrollContainer> PlayScreen::buildJoinRealmsScreen(bool_t a2) {
	std::shared_ptr<PackedScrollContainer> v33;
	if(a2) {
		if(!this->field_20C) {
			this->field_20C = std::shared_ptr<PackedScrollContainer>(new PackedScrollContainer(0, 0, 0));
		}
		v33 = this->field_20C;
	} else {
		if(this->field_204) {
			this->field_204 = std::shared_ptr<PackedScrollContainer>(new PackedScrollContainer(0, 0, 0));
		}
		v33 = this->field_204;
	}
	std::shared_ptr<GuiElementContainer> v34(new GuiElementContainer(0, 1, 0, 0, 24, 24));
	std::shared_ptr<Label> v35(new Label("Waiting for Minecraft Realms", this->minecraft, 0xffffff, 0, 0, 0, 1));
	std::shared_ptr<Label> v36(new Label(this->field_C4, this->minecraft, 0xFFAAAAAA, 0, 0, 0, 1));
	std::shared_ptr<Spinner> v37(new Spinner());
	this->field_B4 = new Touch::TButton(6, a2 ? "OK" : "Cancel", 0);
	this->buttons.push_back(this->field_B4);
	this->field_B4->init(this->minecraft);
	v34->width = this->field_214->width;
	v34->height = this->field_214->height;
	this->field_B4->setupPositions();
	v35->setupPositions();
	v36->setupPositions();
	v35->posX = (this->field_214->width - v35->width) / 2;
	v36->posX = (this->field_214->width - v36->width) / 2;
	v37->posX = this->field_214->width / 2;
	this->field_B4->posX = (this->field_214->width - this->field_B4->width) / 2;
	int v22 = (this->field_B4->height + 38);
	v35->posY = (this->field_214->height - v22);
	v36->posY = v37->posY = v22 / 2 + 19;
	this->field_B4->posY = v22 / 2 + 38;
	v34->addChild(v35);
	v34->addChild(std::shared_ptr<GuiElement>(this->field_B4));
	//v34->addChild(a2 ? std::shared_ptr<GuiElement>(v36)) : std::shared_ptr<GuiElement>(v37));
	v33->clearAll();
	v33->addChild(v34);
	this->buttons.push_back(this->field_B4);
	return v33;
}
std::shared_ptr<GuiElement> PlayScreen::buildLocalServerList() {
	this->field_50 = 0;
	bool isEditMode = this->isEditMode();

	if(!this->field_1F4.get()) {
		this->field_1F4 = std::shared_ptr<PackedScrollContainer>(new PackedScrollContainer(0, 0, 0));
	}
	//TODO check
	std::shared_ptr<PackedScrollContainer> v31(*(std::shared_ptr<PackedScrollContainer>*)&this->field_1F4);
	v31.get()->clearAll();
	std::unordered_map<int, ExternalServer> servers = *this->minecraft->externalServerFile->getExternalServers();
	for(auto server: servers) {
		std::shared_ptr<LocalServerListItemElement> v32(new LocalServerListItemElement(this->minecraft, ExternalServer(server.second), isEditMode, this));
		v32->init(this->minecraft);
		v31->addChild(v32);
	}

	for(auto&& p: this->field_88) {
		if(!p.field_0.IsEmpty()) {
			std::shared_ptr<LocalServerListItemElement> v34(new LocalServerListItemElement(p));
			v34->init(this->minecraft);
			v31->addChild(v34);
		}
	}

	std::vector<LevelSummary> v35;
	this->minecraft->getLevelSource()->getLevelList(v35);
	if(!v35.empty()) {
		std::sort(v35.begin(), v35.end()); //TODO check
	}

	for(auto&& v23: v35) {
		if(v23.worldName != LevelStorageSource::TempLevelId) {
			std::shared_ptr<LocalServerListItemElement> v32(new LocalServerListItemElement(this->minecraft, v23, isEditMode));
			v32->init(this->minecraft);
			v31->addChild(v32);
		}
	}
	return this->field_1F4;
}

std::shared_ptr<GuiElement> PlayScreen::buildMCOServerList() {
	struct _sorter
	{
		bool operator()(const std::pair<long long, MCOServerListItem>& a, const std::pair<long long, MCOServerListItem>& b) {
			if(a.first == b.first) return Util::compareNoCase(a.second.worldName, b.second.worldName);
			return a.first < b.first;
		}
	};
	if(!this->field_1FC) {
		this->field_1FC = std::shared_ptr<PackedScrollContainer>(new PackedScrollContainer(0, 0, 0));
	}
	std::shared_ptr<PackedScrollContainer> v23(*(std::shared_ptr<PackedScrollContainer>*)&this->field_1FC);
	v23->clearAll();
	if(this->minecraft->mojangConnector->getConnectionStatus() == STATUS_CONNECTED) {
		this->field_54 = this->minecraft->mojangConnector->getMCOServerList();
		if(this->field_54) {
			if(this->field_54->size()) {
				std::vector<std::pair<long long, MCOServerListItem>> v26;
				for(auto&& p: *this->field_54) {
					v26.push_back(p);
				}
				std::sort(v26.begin(), v26.end(), _sorter());
				bool em = this->isEditMode();
				for(auto&& p: v26) {
					MCOServerListItemElement* v16 = new MCOServerListItemElement(this->minecraft, p.second, em, [this](MCOServerListItem& a2, bool_t a3) {
						if(a3) {
							this->joinMCOServer(a2);
						} else {
							this->field_C4 = "You need to be connected through Wifi to play on Realms";
						}
					});
					v23->addChild(std::shared_ptr<MCOServerListItemElement>(v16));
				}
			}
		}
	}
	return this->field_1FC;
}
std::shared_ptr<GuiElement> PlayScreen::buildMessageScreen() {
	//TODO check
	std::shared_ptr<PackedScrollContainer> v4(new PackedScrollContainer(0, 0, 0));
	PlayScreenStateSetting* stateData = this->getStateData(this->field_114);
	v4->addChild(std::shared_ptr<Label>(new Label(stateData->field_C, this->minecraft, -1, 5, 2, this->field_214->width, 1)));
	v4->setupPositions();
	return v4;
}
void PlayScreen::closeScreen() {
	this->minecraft->cancelLocateMultiplayer();
	this->minecraft->screenChooser.setScreen(ScreenId::START_MENU_SCREEN);
}
PlayScreenState PlayScreen::getState() const{
	return this->field_114;
}
PlayScreenStateSetting* PlayScreen::getStateData(PlayScreenState a2) {
	return &this->field_11C[a2];
}
bool_t PlayScreen::isEditMode() {
	return this->field_84 == this->editButton;
}
bool_t PlayScreen::isLocalPlayScreen() {
	return 0;
}
void PlayScreen::joinMCOServer(MCOServerListItem a2) {
	if(!this->field_A4.get() && this->minecraft->mojangConnector->getConnectionStatus() == STATUS_CONNECTED) {
		safeStopAndRemove(this->field_AC);
		this->field_CC = a2;
		this->field_AC = RestRequestJob::CreateJob(RRT_POST, this->minecraft->mojangConnector->getMCOService(), this->minecraft);
		this->field_AC->setMethod("/server/%/join", a2.serverId);
		MCOServerListItem v11 = this->field_CC;
		Minecraft* minecraft = this->minecraft;
		RestRequestJob::launchRequest(
			this->field_AC,
			this->minecraft->mojangConnector->getThreadCollection(),
			/*TODO this thing is bigger by 8 bytes(0x50 => 0x58) - one field after this and one after v11(this->minecraft)*/
			[this, v11, minecraft](int32_t a2, const std::string& a3, const RestCallTagData& a4, std::shared_ptr<RestRequestJob> a5) {
				uint16_t port;
				std::string ip, key;
				this->minecraft->mojangConnector->getMCOParser()->parseJoinWorld(a3, ip, port, key);
				std::string v14 = Base64::base64Decode(key);
				MojangConnector* con = minecraft->mojangConnector.get();
				std::string v15 = con->getEncryptedJoinDataString(v11.serverId, con->getLoginInformation()->profileName, v14);
				safeStopAndRemove(this->field_AC);
				this->field_C4 = a3;
				minecraft->mojangConnector->setPayload(v15);
				DEBUGMSG("Set encrypted payload to %s\n", v15.c_str());
				minecraft->connectToMCOServer(v11.worldName, ip, port);
				minecraft->setScreen(new ProgressScreen());
				std::string v19 = Util::simpleFormat("{\"%\": \"%\", \"%\": \"%\", \"%\": \"%\"}", ParameterStringify::stringify("server_type", "Realms", "game_type", v11.gamemodeName, "world_name", this->field_CC.serverId));
				minecraft->platform()->statsTrackData("start_game", v19);
			},
			[this](bool_t, bool_t, int32_t a4, const std::string& a5, const RestCallTagData& a6, std::shared_ptr<RestRequestJob> a7) {
				safeStopAndRemove(this->field_AC);
				std::string v12 = "";
				if(a4 == 500) {
					v12 = "Unexpected Server Error";
				} else {
					if(a4 > 500) {
						v12 = "Service Temporarily Unavailable";
					} else {
						int v11;
						this->minecraft->mojangConnector->getMCOParser()->parseErrorMessage(a5, v12, v11);
					}
				}
				this->field_C4 = v12;
				this->field_118 = TEN;
			});
	}
}
void PlayScreen::resetBaseButtons() {
	this->buttons.clear();
	this->buttons.push_back(this->header);
	this->buttons.push_back(this->backButton);
	this->buttons.push_back(this->newButton);
	this->buttons.push_back(this->editButton);
	this->buttons.push_back(this->externalButton);
}
void PlayScreen::resetCurrentWaitingMCOCancelButton(void) {
	if(this->field_B4) {
		auto&& but = std::find(this->buttons.begin(), this->buttons.end(), this->field_B4);
		if(but != this->buttons.end()) {
			this->buttons.erase(but);
		}
	}
	this->field_B4 = 0;
}
void PlayScreen::setMainPanel(PlayScreenPanel a2) {
	this->elements.clear();
	switch(a2) {
		case PlayScreenPanel::MESSAGE:
			this->field_1EC = this->buildMessageScreen();
			this->field_214 = this->field_1EC;
			this->elements.push_back(this->field_1EC.get());
			break;
		case PlayScreenPanel::LOCAL_SERVER_LIST:
			this->field_1F4 = this->buildLocalServerList();
			this->field_214 = this->field_1F4;
			this->elements.push_back(this->field_1F4.get());
			break;
		case PlayScreenPanel::MCO_SERVER_LIST:
			this->field_1FC = this->buildMCOServerList();
			this->field_214 = this->field_1FC;
			this->elements.push_back(this->field_1FC.get());
			break;
		case PlayScreenPanel::JOIN_REALMS_0:
			this->field_204 = this->buildJoinRealmsScreen(0);
			this->field_214 = this->field_204;
			this->elements.push_back(this->field_204.get());
			break;
		case PlayScreenPanel::JOIN_REALMS_1:
			this->field_20C = this->buildJoinRealmsScreen(1);
			this->field_214 = this->field_20C;
			this->elements.push_back(this->field_20C.get());
			break;
		default:
			break;
	}
	this->setupPositions();
}
void PlayScreen::setPlayScreenSate(PlayScreenState a2, bool_t a3) {
	if(a3 || a2 != this->field_114) {
		this->resetBaseButtons();
		this->updateHeaderItems(a2);
		this->field_114 = a2;
		this->field_118 = a2;
		PlayScreenStateSetting* state = this->getStateData(a2);
		this->setMainPanel(state->panel);
	}
}
void PlayScreen::setPlayScreenStateSetting(PlayScreenState state, bool_t a3, bool_t a4, bool_t a5, bool_t a6, bool_t a7, bool_t a8, PlayScreenPanel a9, const std::string& a10) {
	PlayScreenStateSetting v16(a3, a4, a5, a6, a7, a8, a9);
	v16.field_C = a10;

	this->field_11C[state] = v16;
}
void PlayScreen::signOut() {
	if(this->minecraft->mojangConnector->getConnectionStatus() == STATUS_CONNECTED && !this->field_A4) {
		std::shared_ptr<LoginInformation> v6 = this->minecraft->mojangConnector->getLoginInformation();
		std::string v5 = MCOStringify::stringifySignOut(v6->accessToken, v6->clientId);
		safeStopAndRemove(this->field_9C);
		safeStopAndRemove(this->field_94);
		this->field_A4 = RestRequestJob::CreateJob(RRT_POST, this->minecraft->mojangConnector->getAccountService(), this->minecraft);
		this->field_A4->setMethod("/invalidate");
		this->field_A4->setBody(v5);
		RestRequestJob::launchRequest(
			this->field_A4,
			this->minecraft->mojangConnector->getThreadCollection(),
			[this](int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>) {
				this->minecraft->mojangConnector->setLoginInformation(LoginInformation());
				safeStopAndRemove(this->field_A4);
			},
			[this](bool, bool, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob> a7) {
				safeStopAndRemove(this->field_A4);
			});
	}
}
void PlayScreen::updateHeaderItems(PlayScreenState a2) {
	this->newButton->setActiveAndVisibility(this->getStateData(a2)->showNewButton);
	this->editButton->setActiveAndVisibility(this->getStateData(a2)->showEditButton);
	if(this->getStateData(a2)->field_1) this->field_84 = this->editButton;
	else this->field_84 = 0;
	this->externalButton->setActiveAndVisibility(this->getStateData(a2)->showExternalButton);
}

void PlayScreen::updateMCOServerList() {
	if(this->minecraft->mojangConnector->getConnectionStatus() == STATUS_CONNECTED && !this->field_A4 && this->minecraft->mojangConnector->getConnectionStatus() == STATUS_CONNECTED) {
		safeStopAndRemove(this->field_94);
		this->field_94 = RestRequestJob::CreateJob(RRT_GET, this->minecraft->mojangConnector->getMCOService(), this->minecraft);
		this->field_94->setMethod("/server/list");
		this->spinner->setActiveAndVisibility(1);
		RestRequestJob::launchRequest(
			this->field_94,
			this->minecraft->mojangConnector->getThreadCollection(),
			[this](int32_t a2, const std::string& a3, const RestCallTagData& a4, std::shared_ptr<RestRequestJob> a5) {
				this->field_54 = this->minecraft->mojangConnector->getMCOParser()->parseServerList(a3);
				this->minecraft->mojangConnector->setMCOServerList(this->field_54);
				safeStopAndRemove(this->field_94);
				this->updateRealmsState();
				this->spinner->setActiveAndVisibility(0);
			},
			[this](bool, bool, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>) {
				safeStopAndRemove(this->field_94);
				this->spinner->setActiveAndVisibility(0);
			});
	}
}
void PlayScreen::updateMCOStatus() {
	if(this->minecraft->mojangConnector->getConnectionStatus() && !this->field_A4 && this->minecraft->mojangConnector->getConnectionStatus()) {
		safeStopAndRemove<std::shared_ptr<RestRequestJob>>(this->field_9C);
		this->field_9C = RestRequestJob::CreateJob(RRT_GET, this->minecraft->mojangConnector->getMCOService(), this->minecraft);
		this->field_9C->setMethod("/info/status");
		RestRequestJob::launchRequest(
			this->field_9C,
			this->minecraft->mojangConnector->getThreadCollection(),
			[this](int32_t a2, const std::string& a3, const RestCallTagData& a4, std::shared_ptr<RestRequestJob> v11) { //automatically copies it?
				bool buyServerEnabled = 0, createServersEnabled = 0, serviceEnabled = 0;
				this->minecraft->mojangConnector->getMCOParser()->parseStatus(a3, buyServerEnabled, createServersEnabled, serviceEnabled);
				this->minecraft->mojangConnector->setMCOServiceEnabled(serviceEnabled);
				this->minecraft->mojangConnector->setMCOCreateServersEnabled(createServersEnabled);
				safeStopAndRemove<std::shared_ptr<RestRequestJob>>(this->field_9C);
				if(serviceEnabled) {
					safeStopAndRemove<std::shared_ptr<RestRequestJob>>(this->field_9C);
					this->updateRealmsState();
				} else {
					this->minecraft->screenChooser.setScreen(START_MENU_SCREEN);
				}
			},
			[this](bool, bool, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob> v9){ //same as in prev func
				safeStopAndRemove<std::shared_ptr<RestRequestJob>>(this->field_9C);
			}
		);
	}
}
void PlayScreen::updateRealmsState() {
	bool createServersEnabled = this->minecraft->mojangConnector->isMCOCreateServersEnabled();
	std::shared_ptr<std::unordered_map<long long, MCOServerListItem>> v6 = this->minecraft->mojangConnector->getMCOServerList();
	if(!v6) {
		if(createServersEnabled) {
			this->setPlayScreenSate(FOUR, 1);
		} else {
			this->setPlayScreenSate(SEVEN, 1);
		}
	} else {
		if(!createServersEnabled) {
			if(v6->size()) {
				this->setPlayScreenSate(SIX, 1);
			}else{
				this->setPlayScreenSate(SEVEN, 1);
			}
		}else{
			if(v6->size()) {
				this->setPlayScreenSate(THREE, 1);
			}else{
				this->setPlayScreenSate(FOUR, 1);
			}
		}
	}
}

PlayScreen::~PlayScreen() {
	if(this->header) {
		delete this->header;
		this->header = 0;
	}
	safeRemove<Touch::TButton>(this->backButton);
	safeRemove<Touch::TButton>(this->newButton);
	safeRemove<Touch::TButton>(this->externalButton);
	if(this->editButton) {
		delete this->editButton;
		this->editButton = 0;
	}
	safeRemove<NinePatchLayer>(this->field_74);
	safeRemove<NinePatchLayer>(this->field_78);
	safeRemove<NinePatchLayer>(this->frame);
	if(this->spinner) {
		delete this->spinner;
		this->spinner = 0;
	}
	safeStopAndRemove<std::shared_ptr<RestRequestJob>>(this->field_AC);
	safeStopAndRemove<std::shared_ptr<RestRequestJob>>(this->field_9C);
	safeStopAndRemove<std::shared_ptr<RestRequestJob>>(this->field_94);
	safeStopAndRemove<std::shared_ptr<RestRequestJob>>(this->field_A4);
}

void PlayScreen::render(int32_t mx, int32_t my, float pt) {
	this->renderMenuBackground(pt);
	this->frame->draw(Tesselator::instance, this->field_214.get()->posX - 3, this->field_214.get()->posY - 3);
	Screen::render(mx, my, pt);
	this->spinner->render(this->minecraft, mx, my);
}
void PlayScreen::init() {
	this->header = new Touch::THeader(0, this->field_118 == ELEVEN ? "Play" : "Realms");
	this->backButton = new Touch::TButton(1, "Back", 0);
	this->newButton = new Touch::TButton(2, "New", 0);
	this->newButton->width = 100;
	this->externalButton = new Touch::TButton(2626, "External", this->minecraft);
	this->backButton->width = 38;
	this->backButton->height = 18;
	this->externalButton->width = 50;
	this->externalButton->height = this->backButton->height;
	this->backButton->init(this->minecraft);
	IntRectangle a = {8, 32, 8, 8};
	IntRectangle b = {0, 32, 8, 8};
	this->newButton->init(this->minecraft, "gui/spritesheet.png", a, b, 2, 2, this->newButton->width, this->newButton->height);
	this->newButton->height = this->backButton->height;
	this->newButton->width = 38;
	NinePatchFactory a1(this->minecraft->texturesPtr, "gui/spritesheet.png");
	NinePatchLayer* lay = a1.createSymmetrical({34, 43, 14, 14}, 3, 3, 32, 32);
	this->frame = lay;
	NinePatchLayer* lay2 = a1.createSymmetrical({8, 32, 8, 8}, 2, 2, this->backButton->width, this->backButton->height);
	this->field_74 = lay2;
	this->field_78 = a1.createSymmetrical({0, 32, 8, 8}, 2, 2, this->backButton->width, this->backButton->height);
	this->editButton = new CategoryButton("Edit", 3, this->field_74, this->field_78, &this->field_84);
	this->editButton->width = this->backButton->width;
	this->editButton->height = this->backButton->height;
	this->editButton->setYOffset(this->editButton->height / 2 - 4);
	this->spinner = new Spinner();
	this->spinner->setActiveAndVisibility(0);
	this->minecraft->locateMultiplayer();
	this->field_BC = getTimeS();
	this->field_1F4 = this->buildLocalServerList();
	this->field_214 = this->field_1F4;
	this->field_88 = *this->minecraft->rakNetInstance->getServerList();
	if(this->field_118) {
		this->setPlayScreenSate(this->field_118, 1);
	} else {
		MojangConnectionStatus cs = this->minecraft->mojangConnector->getConnectionStatus();
		if(cs == STATUS_0) {
			this->setPlayScreenSate(ONE, 1);
		} else if(cs == STATUS_1) {
			this->setPlayScreenSate(TWO, 1);
		} else {
			this->updateRealmsState();
		}
	}

	if((uint32_t)(this->field_114 - 3) <= 1 || this->field_114 == SIX || this->field_114 == SEVEN) { //67 leaks
		this->updateMCOStatus();
		this->updateMCOServerList();
	}
}

void PlayScreen::setupPositions() {
	this->backButton->posX = 4;
	this->backButton->posY = 4;

	this->editButton->posX = this->width - this->editButton->width - 4;
	this->editButton->posY = 4;

	this->header->posX = 0;
	this->header->posY = 0;
	this->header->width = this->width;
	this->header->height = this->backButton->height + 8;

	this->newButton->posX = this->width - this->editButton->width - 8 - this->newButton->width;
	this->newButton->posY = 4;

	this->spinner->posX = this->width - 4 - this->spinner->width - this->editButton->width;
	this->spinner->posY = 9;

	this->externalButton->posX = this->editButton->posX - this->externalButton->width - 4;
	this->externalButton->posY = this->editButton->posY;

	this->field_214.get()->posX = 10;
	this->field_214.get()->posY = this->header->height + 6;
	this->field_214.get()->width = this->width - 20;
	this->field_214.get()->height = this->height - (this->header->height + 6) - 6;
	this->field_214.get()->setupPositions();
	this->frame->setSize(this->field_214.get()->width + 6, this->field_214.get()->height + 6);
}
bool_t PlayScreen::handleBackEvent(bool_t a2) {
	if(!a2) this->closeScreen();
	return 1;
}
void PlayScreen::tick() {
	if(this->field_50) {
		this->buildLocalServerList();
	}
	if(this->field_51) {
		safeStopAndRemove<std::shared_ptr<RestRequestJob>>(this->field_AC);
		this->updateRealmsState();
		this->field_51 = 0;
	}

	if(this->field_118 != this->field_114) {
		this->setPlayScreenSate(this->field_118, 1);
	}
	PlayScreenStateSetting* stateData = this->getStateData(this->field_114);
	double v5 = this->field_BC;
	if(stateData->panel == MCO_SERVER_LIST) {
		if(v5 + 10 < getTimeS()) {
			this->field_BC = getTimeS();
			this->updateMCOServerList();
		}
	} else if(v5 + 1 < getTimeS()) {
		this->field_BC = getTimeS();
		std::vector<PingedCompatibleServer>* v8 = this->minecraft->rakNetInstance->getServerList();
		if(this->field_88.size() == v8->size()) {
			int v11 = this->field_88.size() - 1;
			while(v11 >= 0) {
				if(this->field_88[v11].field_4 != v8->at(v11).field_4 || this->field_88[v11].field_0 != v8->at(v11).field_0) {
					this->field_88 = *v8;
					this->buildLocalServerList();
				}
				--v11;
			}
		} else {
			this->field_88 = *v8;
			this->buildLocalServerList();
		}
	}

	Screen::tick();
}
void PlayScreen::onMojangConnectorStatus(MojangConnectionStatus a2) {
	if((uint32_t)(this->field_114 - 11) > 1) {
		if(a2 == MojangConnectionStatus::STATUS_1) {
			this->setPlayScreenSate(PlayScreenState::TWO, 1);
			return;
		}
		if(a2 != 2) {
			if(a2) return;
			this->setPlayScreenSate(PlayScreenState::ONE, 1);
			return;
		}
		this->updateRealmsState();
		this->updateMCOStatus();
		this->updateMCOServerList();
	}
}
void PlayScreen::buttonClicked(Button* a2) {
	if(a2 == this->backButton) {
		this->buildLocalServerList();
		this->closeScreen();
	} else if(a2 == this->header) {
		this->buildLocalServerList();
	} else if(a2 == this->newButton) {
		if(this->field_114 == PlayScreenState::ELEVEN) {
			this->minecraft->setScreen(new CreateWorldScreen(WST_LOCALGAME, MCOServerListItem()));
		} else {
			this->minecraft->setScreen(new CreateWorldScreen(WST_MCOGAME_NEW, MCOServerListItem()));
		}
	} else if(a2 == this->editButton) {
		if(a2 == this->field_84) a2 = 0;
		this->field_84 = a2;
		switch(this->field_114) {
			case PlayScreenState::THREE:
			case PlayScreenState::FOUR:
			case PlayScreenState::SIX:
			case PlayScreenState::SEVEN:
				this->setPlayScreenSate(PlayScreenState::FIVE, 1);
				break;
			case PlayScreenState::FIVE:
				this->updateRealmsState();
				return;
			case PlayScreenState::ELEVEN:
				this->setPlayScreenSate(PlayScreenState::TWELVE, 1);
				break;
			case PlayScreenState::TWELVE:
				this->setPlayScreenSate(PlayScreenState::ELEVEN, 1);
				break;
			default:
				return;
		}
	} else if(a2 == this->field_B4) {
		this->field_51 = 1;
	}else if(a2 == this->externalButton){
		this->minecraft->setScreen(new AddExternalServerScreen());
	}
}
void PlayScreen::mouseClicked(int32_t a2, int32_t a3, int32_t a4) {
	Screen::mouseClicked(a2, a3, a4);
}
void PlayScreen::mouseReleased(int32_t a2, int32_t a3, int32_t a4) {
	Screen::mouseReleased(a2, a3, a4);
}
