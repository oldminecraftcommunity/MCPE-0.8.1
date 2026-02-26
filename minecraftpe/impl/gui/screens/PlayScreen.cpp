#include <util/IntRectangle.hpp>
#include <gui/screens/PlayScreen.hpp>
#include <Minecraft.hpp>
#include <gui/PackedScrollContainer.hpp>
#include <rendering/Tesselator.hpp>
#include <gui/NinePatchFactory.hpp>
#include <algorithm>
#include <utils.h>
#include <ExternalServerFile.hpp>
#include <network/RakNetInstance.hpp>
#include <network/mco/MojangConnector.hpp>
#include <gui/screens/CreateWorldScreen.hpp>
#include <gui/screens/AddExternalServerScreen.hpp>
#include <gui/elements/LocalServerListItemElement.hpp>
#include <level/storage/LevelStorageSource.hpp>
#include <cpputils.hpp>

PlayScreen::PlayScreen(bool_t a2) {
	PlayScreenState v4 = a2 ? PlayScreenState::ELEVEN : PlayScreenState::ZERO;
	this->field_50 = 0;
	this->field_51 = 0;
	this->field_54 = 0;
	this->field_58 = 0;
	this->header = 0;
	this->backButton = 0;
	this->field_5C = "";
	this->newButton = 0;
	this->externalButton = 0;
	this->field_70 = 0;
	this->field_74 = 0;
	this->field_78 = 0;
	this->spinner = 0;
	this->field_80 = 0;
	this->field_84 = 0;

	this->field_B4 = 0;
	this->field_C4 = "";
	this->field_118 = v4;
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
std::shared_ptr<GuiElement> PlayScreen::buildJoinRealmsScreen(bool_t) {
	//TODO
	printf("PlayScreen::buildJoinRealmsScreen - not implemented\n");
	return std::shared_ptr<GuiElement>();
}
std::shared_ptr<GuiElement> PlayScreen::buildLocalServerList() { //TODO returns std::shared_ptr<GuiElement>
	this->field_50 = 0;
	bool isEditMode = this->isEditMode();

	if(!this->field_1F4.get()) {
		this->field_1F4 = std::shared_ptr<PackedScrollContainer>(new PackedScrollContainer(0, 0, 0));
	}
	//TODO check is it actually dynamic_pointer_cast
	std::shared_ptr<PackedScrollContainer> v31 = std::dynamic_pointer_cast<PackedScrollContainer>(this->field_1F4);
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
		if(v23.field_0 != LevelStorageSource::TempLevelId) {
			std::shared_ptr<LocalServerListItemElement> v32(new LocalServerListItemElement(this->minecraft, v23, isEditMode));
			v32->init(this->minecraft);
			v31->addChild(v32);
		}
	}
	return this->field_1F4;
}
std::shared_ptr<GuiElement> PlayScreen::buildMCOServerList() {
	//TODO
	printf("PlayScreen::buildMCOServerList - not implemented\n");
	return std::shared_ptr<GuiElement>();
}
std::shared_ptr<GuiElement> PlayScreen::buildMessageScreen() {
	//TODO
	printf("PlayScreen::buildMessageScreen - not implemented\n");
	return std::shared_ptr<GuiElement>();
}
void PlayScreen::closeScreen() {
	this->minecraft->cancelLocateMultiplayer();
	this->minecraft->screenChooser.setScreen(ScreenId::START_MENU_SCREEN);
}
PlayScreenState PlayScreen::getState() {
	return this->field_114;
}
PlayScreenStateSetting* PlayScreen::getStateData(PlayScreenState a2) {
	return &this->field_11C[a2];
}
bool_t PlayScreen::isEditMode() {
	return this->field_84 == this->field_80;
}
bool_t PlayScreen::isLocalPlayScreen() {
	return 0;
}
void PlayScreen::joinMCOServer(MCOServerListItem) {
	//TODO join mco server
	printf("PlayScreen::joinMCOServer - not implemented\n");
}
void PlayScreen::resetBaseButtons() {
	this->buttons.clear();
	this->buttons.emplace_back(this->header);
	this->buttons.emplace_back(this->backButton);
	this->buttons.emplace_back(this->newButton);
	this->buttons.emplace_back(this->field_80);
	this->buttons.emplace_back(this->externalButton);
}
void PlayScreen::resetCurrentlyWaitingMCOCancelButton(void) {
	if(this->field_B4) {
		Button** but = std::find(this->buttons.data(), this->buttons.data() + this->buttons.size(), this->field_B4);
		if(but != (this->buttons.data() + this->buttons.size())) {
			this->buttons.erase(this->buttons.begin() + (but - this->buttons.data())); //TODO check
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
			this->elements.emplace_back(this->field_1EC.get());
			break;
		case PlayScreenPanel::LOCAL_SERVER_LIST:
			this->field_1F4 = this->buildLocalServerList();
			this->field_214 = this->field_1F4;
			this->elements.emplace_back(this->field_1F4.get());
			break;
		case PlayScreenPanel::MCO_SERVER_LIST:
			this->field_1FC = this->buildMCOServerList();
			this->field_214 = this->field_1FC;
			this->elements.emplace_back(this->field_1FC.get());
			break;
		case PlayScreenPanel::JOIN_REALMS_0:
			this->field_204 = this->buildJoinRealmsScreen(0);
			this->field_214 = this->field_204;
			this->elements.emplace_back(this->field_204.get());
			break;
		case PlayScreenPanel::JOIN_REALMS_1:
			this->field_20C = this->buildJoinRealmsScreen(1);
			this->field_214 = this->field_20C;
			this->elements.emplace_back(this->field_20C.get());
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
	//TODO
	printf("PlayScreen::signOut - not implemented\n");
}
void PlayScreen::updateHeaderItems(PlayScreenState a2) {
	this->newButton->setActiveAndVisibility(this->getStateData(a2)->field_4);
	this->field_80->setActiveAndVisibility(this->getStateData(a2)->field_0);
	if(this->getStateData(a2)->field_1) this->field_84 = this->field_80;
	else this->field_84 = 0;
	this->externalButton->setActiveAndVisibility(this->getStateData(a2)->field_5);
}

void PlayScreen::updateMCOServerList() {
	//TODO
	printf("PlayScreen::updateMCOServerList - not implemented\n");
}
void PlayScreen::updateMCOStatus() {
	//TODO
	printf("PlayScreen::updateMCOStatus - not implemented\n");
}
void PlayScreen::updateRealmsState() {
	//TODO
	printf("PlayScreen::updateRealmsState - not implemented\n");
}

PlayScreen::~PlayScreen() {
	if(this->header) {
		delete this->header;
		this->header = 0;
	}
	safeRemove<Touch::TButton>(this->backButton);
	safeRemove<Touch::TButton>(this->newButton);
	safeRemove<Touch::TButton>(this->externalButton);
	if(this->field_80) {
		delete this->field_80;
		this->field_80 = 0;
	}
	safeRemove<NinePatchLayer>(this->field_74);
	safeRemove<NinePatchLayer>(this->field_78);
	safeRemove<NinePatchLayer>(this->field_70);
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
	this->field_70->draw(Tesselator::instance, this->field_214.get()->posX - 3, this->field_214.get()->posY - 3);
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
	this->field_70 = lay;
	NinePatchLayer* lay2 = a1.createSymmetrical({8, 32, 8, 8}, 2, 2, this->backButton->width, this->backButton->height);
	this->field_74 = lay2;
	this->field_78 = a1.createSymmetrical({0, 32, 8, 8}, 2, 2, this->backButton->width, this->backButton->height);
	this->field_80 = new CategoryButton("Edit", 3, this->field_74, this->field_78, &this->field_84);
	this->field_80->width = this->backButton->width;
	this->field_80->height = this->backButton->height;
	this->field_80->setYOffset(this->field_80->height / 2 - 4);
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

	this->field_80->posX = this->width - this->field_80->width - 4;
	this->field_80->posY = 4;

	this->header->posX = 0;
	this->header->posY = 0;
	this->header->width = this->width;
	this->header->height = this->backButton->height + 8;

	this->newButton->posX = this->width - this->field_80->width - 8 - this->newButton->width;
	this->newButton->posY = 4;

	this->spinner->posX = this->width - 4 - this->spinner->width - this->field_80->width;
	this->spinner->posY = 9;

	this->externalButton->posX = this->field_80->posX - this->externalButton->width - 4;
	this->externalButton->posY = this->field_80->posY;

	this->field_214.get()->posX = 10;
	this->field_214.get()->posY = this->header->height + 6;
	this->field_214.get()->width = this->width - 20;
	this->field_214.get()->height = this->height - (this->header->height + 6) - 6;
	this->field_214.get()->setupPositions();
	this->field_70->setSize(this->field_214.get()->width + 6, this->field_214.get()->height + 6);
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
	} else if(a2 == this->field_80) {
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
