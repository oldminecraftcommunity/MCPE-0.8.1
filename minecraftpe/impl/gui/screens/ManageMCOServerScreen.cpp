#include <gui/screens/ManageMCOServerScreen.hpp>
#include <Minecraft.hpp>
#include <cpputils.hpp>
#include <gui/NinePatchLayer.hpp>
#include <gui/PackedScrollContainer.hpp>
#include <gui/buttons/OptionButton.hpp>
#include <gui/elements/Label.hpp>
#include <gui/elements/TextBox.hpp>
#include <gui/screens/CreateWorldScreen.hpp>
#include <gui/screens/PlayScreen.hpp>
#include <rendering/Tesselator.hpp>
#include <gui/NinePatchFactory.hpp>
#include <util/IntRectangle.hpp>
#include <gui/buttons/ImageWithBackground.hpp>
#include <gui/elements/MCOInviteListItemElement.hpp>
#include <network/mco/MojangConnector.hpp>

ManageMCOServerScreen::ManageMCOServerScreen(const MCOServerListItem& a2) {
	this->item.worldName = "My World";
	this->item.gamemodeName = "creative";
	this->manageServerHeader = 0;
	this->backButton = 0;
	this->resetButton = 0;
	this->isOpen = 0;
	this->openLabel = 0;
	this->serverNameLabel = 0;
	this->invitedPeopleLabel = 0;
	this->serverNameTextBox = 0;
	this->playerNameTextBox = 0;
	this->invitedPlayersList = 0;
	this->field_D0 = 0;
	this->field_F4 = 0;
	this->field_F8 = 0;
	this->item = a2;
}
MCOInviteListItemElement* ManageMCOServerScreen::_addInviteElement(const std::string& name) {
	std::string username = Util::toLower(name);
	if(this->invitedPlayers.count(username) != 0) {
		return 0;
	} else if(username.size() != 0) {
		this->item.invited.insert(username);
		std::shared_ptr<MCOInviteListItemElement> v16(new MCOInviteListItemElement(username, *this, &ManageMCOServerScreen::onFriendItemRemoved));
		this->invitedPlayers[username] = v16;

		this->invitedPlayersList->addChild(v16);
		this->invitedPlayersList->setupPositions();
		return v16.get();
	} else {
		return 0;
	}
}
void ManageMCOServerScreen::_queryUsernameAndUpdateElement(const std::string& name) {
	std::shared_ptr<Screen> v10(this->minecraft->currentScreen);
	this->field_FC = RestRequestJob::CreateJob(RRT_POST, this->minecraft->mojangConnector->getMCOService(), this->minecraft);
	this->field_FC->setMethod("/server/%/whitelist/%", this->item.serverId, name);
	RestRequestJob::launchRequest(
		this->field_FC,
		this->minecraft->mojangConnector->getThreadCollection(),
		[this, v10, name](int32_t, const std::string& a3, const RestCallTagData&, std::shared_ptr<RestRequestJob>) {
			this->invitedPlayers[Util::toLower(name)]->onFriendSearchCompleted(a3);
			this->inviteErrorMessage->setText("");
		},
		[this, v10, name](bool, bool, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>) {
			this->_removeInviteElement(name);
			this->inviteErrorMessage->setText("Cannot find user\n" + name + "!");
		});
}
bool ManageMCOServerScreen::_removeInviteElement(const std::string& name) {
	std::string v13 = Util::toLower(name);
	auto&& p = this->item.invited.find(v13);
	if(p != this->item.invited.end() && v13.size()) {
		//TODO check
		this->item.invited.erase(p);
		this->invitedPlayersList->removeChild(this->invitedPlayers.find(v13)->second);
		this->invitedPlayersList->setupPositions();
		return 1;
	}
	return 0; //TODO check
}
void ManageMCOServerScreen::closeScreen() {
	this->minecraft->setScreen(new PlayScreen(0));
}

ManageMCOServerScreen::~ManageMCOServerScreen() {
	if(this->manageServerHeader) {
		delete this->manageServerHeader;
		this->manageServerHeader = 0;
	}
	safeRemove(this->backButton);
	if(this->isOpen) {
		delete this->isOpen;
		this->isOpen = 0;
	}
	safeRemove(this->openLabel);
	safeRemove(this->serverNameLabel);
	safeRemove(this->serverNameTextBox);
	safeRemove(this->invitedPeopleLabel);
	if(this->invitedPlayersList) {
		delete this->invitedPlayersList;
		this->invitedPlayersList = 0;
	}
	if(this->field_D0) {
		delete this->field_D0;
		this->field_D0 = 0;
	}
	safeRemove(this->playerNameTextBox);
	safeRemove(this->resetButton);
}
void ManageMCOServerScreen::render(int32_t a2, int32_t a3, float a4) {
	this->renderMenuBackground(a4);
	this->field_D4->draw(Tesselator::instance, (float)this->field_D4->posX, (float)this->field_D4->posY);
	this->field_D0->draw(Tesselator::instance, (float)this->invitedPlayersList->posX - 1.0, (float)this->invitedPlayersList->posY - 2.0);
	Screen::render(a2, a3, a4);
}
void ManageMCOServerScreen::init(){
	this->manageServerHeader = new Touch::THeader(0, "Manage server");
	this->backButton = new Touch::TButton(1, "Back", 0);
	this->resetButton = new Touch::TButton(2, "Reset", 0);
	((Touch::TButton*)this->resetButton)->init(this->minecraft);
	this->backButton->width = 38;
	this->backButton->height = 18;
	((Touch::TButton*)this->backButton)->init(this->minecraft);
	this->buttons.push_back(this->manageServerHeader);
	this->buttons.push_back(this->backButton);
	NinePatchFactory npf(this->minecraft->texturesPtr, "gui/spritesheet.png");
	this->field_D4 = npf.createSymmetrical(IntRectangle{34, 43, 14, 14}, 3, 3, 32, 32);
	ImageDef v37; //TODO this is supposed to be inside of some constructor?
	v37.field_1C = 38;
	v37.field_14 = 160;
	v37.field_24 = 1;
	v37.field_18 = 206;
	v37.field_20 = 20;

	v37.field_0 = "gui/touchgui.png";
	v37.width = 38.0;
	v37.height = 20.0;
	this->openLabel = new Label("Open", this->minecraft, -1, 0, 0, 0, 1);
	this->isOpen = new OptionButton(this->item.open);
	this->isOpen->setImageDef(v37, 1);
	this->playerNameTextBox = new TextBox(this->minecraft, "Player Name", 16, 0, 0, this, &Screen::onTextBoxUpdated, 2);
	this->playerNameTextBox->posY = -200;
	this->serverNameTextBox = new TextBox(this->minecraft, "Server Name", 16, 0, 0, this, &Screen::onTextBoxUpdated, 1);
	this->serverNameTextBox->setText(this->item.worldName);
	this->serverNameLabel = new Label("Server Name", this->minecraft, -1, 0, 0, 0, 1);
	this->invitedPeopleLabel = new Label("Invited People", this->minecraft, 0xFF373535, 0, 0, 0, 0);
	this->inviteErrorMessage = new Label("", this->minecraft, 0xFFC6321B, 0, 0, 0, 0);
	this->inviteErrorMessage->field_3A = 1;
	this->resetButton->width = 38;
	this->resetButton->height = 18;
	this->buttons.push_back(this->resetButton);
	this->invitedPlayersList = new PackedScrollContainer(0, 0, 0);
	this->elements.push_back(this->openLabel);
	this->elements.push_back(this->isOpen);
	this->elements.push_back(this->serverNameTextBox);
	this->elements.push_back(this->serverNameLabel);
	this->elements.push_back(this->invitedPeopleLabel);
	this->elements.push_back(this->invitedPlayersList);
	this->elements.push_back(this->playerNameTextBox);
	this->elements.push_back(this->inviteErrorMessage);
	this->field_D4->setSize(this->width, this->height);
	this->field_D0 = npf.createSymmetrical(IntRectangle{0, 20, 8, 8}, 1, 2, 32, 32)->setExcluded(16);
	this->field_BC = std::shared_ptr<ImageWithBackground>(new ImageWithBackground(2));
	this->field_BC->height = (this->resetButton->height * 1.5f);
	this->field_BC->init(this->minecraft->texturesPtr, this->field_BC->width, this->field_BC->height, {112, 0, 8, 67}, {120, 0, 8, 67}, 2, 2, "gui/spritesheet.png");
	ImageDef v43;
	v43.field_18 = 0;
	v43.height = 12.0;
	v43.width = 12.0;
	v43.field_24 = 1;
	v43.field_14 = 221;
	v43.field_1C = 8;
	v43.field_20 = 8;
	v43.field_0 = "gui/gui.png";
	this->field_BC->setImageDef(v43, 0);
	this->buttons.push_back(this->field_BC.get());
	this->field_BC->setOverrideScreenRendering(1);
	this->invitedPlayersList->addChild(this->field_BC);
	this->setupPositions();
	//TODO check:
	for(auto&& s : this->item.invited){
		MCOInviteListItemElement* v28 = this->_addInviteElement(s);
		if(v28) {
			v28->onFriendSearchCompleted(s);
		}
	}
}
void ManageMCOServerScreen::setupPositions() {
	int32_t width; // r5
	Label* serverNameLabel; // r1
	TextBox* serverNameTextBox; // r0

	width = this->width;
	this->backButton->posX = 4;
	width /= 2;
	this->backButton->posY = 4;
	this->manageServerHeader->posX = 0;
	this->manageServerHeader->posY = 0;
	this->manageServerHeader->width = this->width;
	this->manageServerHeader->height = this->backButton->height + 8;
	this->field_D4->setSize((float)this->width - 10.0, (float)((float)this->height - 10.0) - (float)this->manageServerHeader->height);
	this->field_D4->posX = 5;
	this->field_D4->posY = this->manageServerHeader->posY + this->manageServerHeader->height + 5;
	serverNameLabel = this->serverNameLabel;
	serverNameTextBox = this->serverNameTextBox;
	this->openLabel->posX = 10;
	serverNameTextBox->posX = 10;
	serverNameLabel->posX = 10;
	this->serverNameLabel->posY = this->field_D4->posY + 5;
	this->serverNameTextBox->posY = this->serverNameLabel->posY + 12;
	this->serverNameTextBox->width = width - 20;
	this->openLabel->posY = this->field_D4->posY + (int32_t)(float)(this->field_D4->height2 * 0.47);
	this->isOpen->posY = this->openLabel->posY - 4;
	this->isOpen->posX = width - 10 - this->isOpen->width;
	this->invitedPlayersList->posX = width + 11;
	this->invitedPlayersList->posY = this->serverNameLabel->posY;
	this->invitedPlayersList->width = width - 22;
	this->invitedPlayersList->height = (int32_t)this->field_D4->height2 - 10;
	this->invitedPeopleLabel->posX = this->invitedPlayersList->posX + (this->invitedPlayersList->width - this->invitedPeopleLabel->width) / 2;
	this->invitedPeopleLabel->posY = this->field_D4->posY + (int32_t)this->field_D4->height2 / 2 - 5;
	this->resetButton->posX = this->width - this->backButton->posX - this->resetButton->width;
	this->resetButton->posY = this->backButton->posY;
	this->field_D0->setSize((float)this->invitedPlayersList->width + 2.0, (float)this->invitedPlayersList->height + 4.0);
	this->inviteErrorMessage->posX = (this->field_D4->posX + this->invitedPlayersList->posX) / 2;
	this->inviteErrorMessage->posY = this->field_D4->posY + (int32_t)(float)(this->field_D4->height2 * 0.8);
	this->invitedPlayersList->setupPositions();
}
bool_t ManageMCOServerScreen::handleBackEvent(bool_t a2) {
	if(a2) {
		if(!this->supppressedBySubWindow()) {
			this->closeScreen();
			return 1;
		}
		bool_t v4 = 1;
		for(auto&& e: this->elements) {
			if(e->backPressed(this->minecraft, 1)) {
				v4 = 0;
			}
		}
		if(v4) {
			this->closeScreen();
		}
	}
	return 1;
}
void ManageMCOServerScreen::tick(){
	if(this->isOpen->isSet(0) != this->item.open) {
		this->item.open = !this->item.open;
		this->field_FC = RestRequestJob::CreateJob(RRT_PUT, this->minecraft->mojangConnector->getMCOService(), this->minecraft);
		this->field_FC->setMethod(this->item.open ? "/server/%/open" : "/server/%/close", this->item.serverId);
		RestRequestJob::launchRequest(
			this->field_FC,
			this->minecraft->mojangConnector->getThreadCollection(),
			[this](int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>) {

			},
			[this](bool, bool, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>) {

			});
	}

	this->openLabel->setText(this->item.open ? "Open to all" : "Closed");
}
void ManageMCOServerScreen::onTextBoxUpdated(int32_t a2) {
	if(a2 == this->serverNameTextBox->getKey()) {
		if(this->item.worldName != *this->serverNameTextBox->getText()){
			printf("ManageMCOServerScreen::onTextBoxUpdated - not implemented\n"); //TODO
		}
	} else if(a2 == this->playerNameTextBox->getKey()) {
		if(this->_addInviteElement(*this->playerNameTextBox->getText())) {
			this->_queryUsernameAndUpdateElement(*this->playerNameTextBox->getText());
		}
	}
}
void ManageMCOServerScreen::buttonClicked(Button* a2) {
	if(a2 == this->backButton) {
		this->closeScreen();
	} else if(a2 == this->field_BC.get()) {
		this->playerNameTextBox->setText("");
		this->playerNameTextBox->setFocus(this->minecraft);
	} else if(a2 == this->resetButton) {
		this->minecraft->setScreen(new CreateWorldScreen(WST_MCOGAME_RECREATE, this->item));
	}
}
void ManageMCOServerScreen::mouseClicked(int32_t a2, int32_t a3, int32_t a4) {
	Screen::mouseClicked(a2, a3, a4);
}
void ManageMCOServerScreen::mouseReleased(int32_t a2, int32_t a3, int32_t a4) {
	Screen::mouseReleased(a2, a3, a4);
}
void ManageMCOServerScreen::onFriendItemRemoved(const std::string&){
	printf("ManageMCOServerScreen::onFriendItemRemoved - not implemented\n"); //TODO
}
