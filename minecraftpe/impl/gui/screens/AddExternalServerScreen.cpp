#include <gui/screens/AddExternalServerScreen.hpp>
#include <ExternalServerFile.hpp>
#include <Minecraft.hpp>
#include <gui/elements/Label.hpp>
#include <gui/elements/TextBox.hpp>
#include <gui/screens/PlayScreen.hpp>
#include <rendering/Tesselator.hpp>
#include <gui/NinePatchFactory.hpp>
#include <util/IntRectangle.hpp>
#include <stdlib.h>
void AddExternalServerScreen::render(int32_t a2, int32_t a3, float a4) {
	if(this->supppressedBySubWindow()) {
		this->renderBackground(0);
	} else {
		this->renderMenuBackground(a4);
		this->bgFrame->draw(Tesselator::instance, 5, this->header->height + 5.0f);
	}
	Screen::render(a2, a3, a4);
}
void AddExternalServerScreen::setupPositions() {
	this->closeScreenButton->posX = 4;
	this->closeScreenButton->posY = 4;

	this->header->posX = 0;
	this->header->posY = 0;
	this->header->width = this->width;
	this->header->height = this->closeScreenButton->height + 8;
	int yp = this->header->height;

	this->serverNameLabel->posX = 10;
	this->serverNameLabel->posY = yp + 10;
	yp += 22;

	this->serverNameTextBox->posX = 10;
	this->serverNameTextBox->posY = yp;
	this->serverNameTextBox->width = this->width / 2 - 10;
	yp += this->serverNameTextBox->height + 8;

	this->addressLabel->posX = 10;
	this->addressLabel->posY = yp;
	yp += 10;

	this->serverAddressTextBox->posX = 10;
	this->serverAddressTextBox->posY = yp;
	this->serverAddressTextBox->width = this->width / 2 - 10;
	yp += this->serverAddressTextBox->height + 8;

	this->portLabel->posX = 10;
	this->portLabel->posY = yp;

	this->portTextBox->posX = 10;
	this->portTextBox->posY = yp + 10;
	this->portTextBox->width = this->width / 2 - 10;

	this->infoLabel->posX = this->width / 2 + 10;
	this->infoLabel->posY = this->header->height + 10;
	this->infoLabel->setWidth(this->width / 2 - 20);
	this->infoLabel->setupPositions();

	this->addServerButton->posX = 3 * ((this->width - 10) / 4) + this->addServerButton->width / -2;
	this->addServerButton->posY = this->infoLabel->posY + this->infoLabel->height + 30;

	this->bgFrame->setSize((float)this->width - 10.0f, this->height - this->header->height - 10);
}
void AddExternalServerScreen::closeScreen() {
	this->minecraft->setScreen(new PlayScreen(1));
}
void AddExternalServerScreen::buttonClicked(Button* a2) {
	if(a2 == this->closeScreenButton.get()) {
		this->closeScreen();
	} else if(a2 == this->addServerButton.get()) {
		long v3 = strtol(this->portTextBox->text.c_str(), 0, 0);
		if(v3 > 0) {
			if(this->serverNameTextBox->text.size()) {
				if(this->serverAddressTextBox->text.size()) {
					this->minecraft->externalServerFile->addServer(this->serverNameTextBox->text, this->serverAddressTextBox->text, v3);
					this->minecraft->setScreen(new PlayScreen(1));
				}
			}
		}
	}
}
bool_t AddExternalServerScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		bool_t v4 = 1;
		for(auto e: this->elements) {
			if(e->suppressOtherGUI()) {
				v4 = 0;
				e->backPressed(this->minecraft, 0);
			}
		}
		if(v4) {
			this->closeScreen();
		}
	}
	return 1;
}
void AddExternalServerScreen::init() {
	this->header = std::shared_ptr<Button>(new Touch::THeader(0, "Add External Server"));
	this->closeScreenButton = std::shared_ptr<Button>(new Touch::TButton(1, "Back", this->minecraft));
	this->addServerButton = std::shared_ptr<Button>(new Touch::TButton(2, "Add Server", this->minecraft));
	this->closeScreenButton->width = 38;
	this->closeScreenButton->height = 18;
	this->serverNameLabel = std::shared_ptr<Label>(new Label("Server Name", this->minecraft, -1, 0, 0, 0, 1));
	this->serverNameTextBox = std::shared_ptr<TextBox>(new TextBox(this->minecraft, "Server Name", 16, TextBox::extendedAcsii, strlen(TextBox::extendedAcsii), 0, 0, 0));
	this->addressLabel = std::shared_ptr<Label>(new Label("Address", this->minecraft, -1, 0, 0, 0, 1));
	this->serverAddressTextBox = std::shared_ptr<TextBox>(new TextBox(this->minecraft, "Server Address", 256, TextBox::extendedAcsii, strlen(TextBox::extendedAcsii), 0, 0, 0));
	this->serverAddressTextBox->setText("127.0.0.1");
	this->portLabel = std::shared_ptr<Label>(new Label("Port", this->minecraft, -1, 0, 0, 0, 1));
	this->portTextBox = std::shared_ptr<TextBox>(new TextBox(this->minecraft, "Server Port", 6, TextBox::numberChars, strlen(TextBox::numberChars), 0, 0, 0));
	this->portTextBox->setText("19132");
	this->infoLabel = std::shared_ptr<Label>(new Label("Add server by IP/Address.", this->minecraft, -1, 0, 0, 0, 1));
	NinePatchFactory factory(this->minecraft->texturesPtr, "gui/spritesheet.png");
	this->bgFrame = std::shared_ptr<NinePatchLayer>(factory.createSymmetrical(IntRectangle{34, 43, 14, 14}, 3, 3, 32, 32));
	this->buttons.push_back(this->header.get());
	this->buttons.push_back(this->closeScreenButton.get());
	this->buttons.push_back(this->addServerButton.get());
	this->elements.push_back(this->serverNameLabel.get());
	this->elements.push_back(this->serverNameTextBox.get());
	this->elements.push_back(this->addressLabel.get());
	this->elements.push_back(this->serverAddressTextBox.get());
	this->elements.push_back(this->portLabel.get());
	this->elements.push_back(this->portTextBox.get());
	this->elements.push_back(this->infoLabel.get());
}


