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

ManageMCOServerScreen::ManageMCOServerScreen(const MCOServerListItem& a2) {
	this->item.worldName = "My World";
	this->item.gamemodeName = "creative";
	this->manageServerHeader = 0;
	this->backButton = 0;
	this->resetButton = 0;
	this->field_AC = 0;
	this->openLabel = 0;
	this->serverNameLabel = 0;
	this->invitedPeopleLabel = 0;
	this->field_BC = 0;
	this->field_C0 = 0;
	this->serverNameTextBox = 0;
	this->playerNameTextBox = 0;
	this->field_CC = 0;
	this->field_D0 = 0;
	this->field_F4 = 0;
	this->field_F8 = 0;
	this->item = a2;
}
MCOInviteListItemElement* ManageMCOServerScreen::_addInviteElement(const std::string&) {
	printf("ManageMCOServerScreen::_addInviteElement - not implemented\n"); //TODO
	return 0;
}
void ManageMCOServerScreen::_queryUsernameAndUpdateElement(const std::string&) {
	printf("ManageMCOServerScreen::_queryUsernameAndUpdateElement - not implemented\n"); //TODO
}
void ManageMCOServerScreen::_removeInviteElement(const std::string&) {
	printf("ManageMCOServerScreen::_removeInviteElement - not implemented\n"); //TODO
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
	if(this->field_AC) {
		delete this->field_AC;
		this->field_AC = 0;
	}
	safeRemove(this->openLabel);
	safeRemove(this->serverNameLabel);
	safeRemove(this->serverNameTextBox);
	safeRemove(this->invitedPeopleLabel);
	if(this->field_CC) {
		delete this->field_CC;
		this->field_CC = 0;
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
	this->field_D0->draw(Tesselator::instance, (float)this->field_CC->posX - 1.0, (float)this->field_CC->posY - 2.0);
	Screen::render(a2, a3, a4);
}
void ManageMCOServerScreen::init(){
	printf("ManageMCOServerScreen::init - not implemented\n"); //TODO
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
	this->field_AC->posY = this->openLabel->posY - 4;
	this->field_AC->posX = width - 10 - this->field_AC->width;
	this->field_CC->posX = width + 11;
	this->field_CC->posY = this->serverNameLabel->posY;
	this->field_CC->width = width - 22;
	this->field_CC->height = (int32_t)this->field_D4->height2 - 10;
	this->invitedPeopleLabel->posX = this->field_CC->posX + (this->field_CC->width - this->invitedPeopleLabel->width) / 2;
	this->invitedPeopleLabel->posY = this->field_D4->posY + (int32_t)this->field_D4->height2 / 2 - 5;
	this->resetButton->posX = this->width - this->backButton->posX - this->resetButton->width;
	this->resetButton->posY = this->backButton->posY;
	this->field_D0->setSize((float)this->field_CC->width + 2.0, (float)this->field_CC->height + 4.0);
	this->field_D8->posX = (this->field_D4->posX + this->field_CC->posX) / 2;
	this->field_D8->posY = this->field_D4->posY + (int32_t)(float)(this->field_D4->height2 * 0.8);
	this->field_CC->setupPositions();
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
	printf("ManageMCOServerScreen::tick - not implemented\n"); //TODO
}
void ManageMCOServerScreen::onTextBoxUpdated(int32_t){
	printf("ManageMCOServerScreen::onTextBoxUpdated - not implemented\n"); //TODO
}
void ManageMCOServerScreen::buttonClicked(Button* a2) {
	if(a2 == this->backButton) {
		this->closeScreen();
	} else if(a2 == this->field_BC) {
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
