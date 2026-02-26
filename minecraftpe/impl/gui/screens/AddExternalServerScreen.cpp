#include <gui/screens/AddExternalServerScreen.hpp>
#include <ExternalServerFile.hpp>
#include <Minecraft.hpp>
#include <gui/elements/Label.hpp>
#include <gui/elements/TextBox.hpp>
#include <gui/screens/PlayScreen.hpp>
#include <rendering/Tesselator.hpp>
#include <gui/NinePatchFactory.hpp>
#include <util/IntRectangle.hpp>

void AddExternalServerScreen::closeScreen() {
	this->minecraft->setScreen(new PlayScreen(1));
}

AddExternalServerScreen::~AddExternalServerScreen() {
}
void AddExternalServerScreen::render(int32_t a2, int32_t a3, float a4) {
	if(this->supppressedBySubWindow()) {
		this->renderBackground(0);
	} else {
		this->renderMenuBackground(a4);
		this->field_A4->draw(Tesselator::instance, 5, this->field_5C->height + 5);
	}
	Screen::render(a2, a3, a4);
}
void AddExternalServerScreen::init() {
	this->field_5C = std::shared_ptr<Button>(new Touch::THeader(0, "Add External Server"));
	this->closeScreenButton = std::shared_ptr<Button>(new Touch::TButton(1, "Back", this->minecraft));
	this->addServerButton = std::shared_ptr<Button>(new Touch::TButton(2, "Add Server", this->minecraft));
	this->closeScreenButton->width = 38;
	this->closeScreenButton->height = 18;
	this->serverNameLabel = std::shared_ptr<Label>(new Label("Server Name", this->minecraft, -1, 0, 0, 0, 1));
	this->serverNameTextBox = std::shared_ptr<TextBox>(new TextBox(this->minecraft, "Server Name", 16, TextBox::extendedAcsii, strlen(TextBox::extendedAcsii), 0, 0, 0, 0));
	this->addressLabel = std::shared_ptr<Label>(new Label("Address", this->minecraft, -1, 0, 0, 0, 1));
	this->serverAddressTextBox = std::shared_ptr<TextBox>(new TextBox(this->minecraft, "Server Address", 256, TextBox::extendedAcsii, strlen(TextBox::extendedAcsii), 0, 0, 0, 0));
	this->serverAddressTextBox->setText("127.0.0.1");
	this->portLabel = std::shared_ptr<Label>(new Label("Port", this->minecraft, -1, 0, 0, 0, 1));
	this->field_94 = std::shared_ptr<TextBox>(new TextBox(this->minecraft, "Server Port", 6, TextBox::numberChars, strlen(TextBox::numberChars), 0, 0, 0, 0));
	this->field_94->setText("19132");
	this->field_9C = std::shared_ptr<Label>(new Label("Add server by IP/Address.", this->minecraft, -1, 0, 0, 0, 1));
	NinePatchFactory factory(this->minecraft->texturesPtr, "gui/spritesheet.png");
	this->field_A4 = std::shared_ptr<NinePatchLayer>(factory.createSymmetrical(IntRectangle{34, 43, 14, 14}, 3, 3, 32, 32));
	this->buttons.emplace_back(this->field_5C.get());
	this->buttons.emplace_back(this->closeScreenButton.get());
	this->buttons.emplace_back(this->addServerButton.get());
	this->elements.emplace_back(this->serverNameLabel.get());
	this->elements.emplace_back(this->serverNameTextBox.get());
	this->elements.emplace_back(this->addressLabel.get());
	this->elements.emplace_back(this->serverAddressTextBox.get());
	this->elements.emplace_back(this->portLabel.get());
	this->elements.emplace_back(this->field_94.get());
	this->elements.emplace_back(this->field_9C.get());
}
void AddExternalServerScreen::setupPositions() {
	int32_t height; // r0
	int32_t v4;		// r1
	int32_t v5;		// r1
	int32_t v6;		// r2

	this->closeScreenButton->posX = 4;
	this->closeScreenButton->posY = 4;
	this->field_5C->posX = 0;
	this->field_5C->posY = 0;
	this->field_5C->width = this->width;
	this->field_5C->height = this->closeScreenButton->height + 8;
	height = this->field_5C->height;
	this->serverNameLabel->posX = 10;
	v4 = height + 10;
	height += 22;
	this->serverNameLabel->posY = v4;
	this->serverNameTextBox->posX = 10;
	this->serverNameTextBox->posY = height;
	this->serverNameTextBox->width = this->width / 2 - 10;
	v5 = height + this->serverNameTextBox->height + 8;
	this->addressLabel->posX = 10;
	this->addressLabel->posY = v5;
	v5 += 10;
	this->serverAddressTextBox->posX = 10;
	this->serverAddressTextBox->posY = v5;
	this->serverAddressTextBox->width = this->width / 2 - 10;
	v6 = v5 + this->serverAddressTextBox->height + 8;
	this->portLabel->posX = 10;
	this->portLabel->posY = v6;
	this->field_94->posX = 10;
	this->field_94->posY = v6 + 10;
	this->field_94->width = this->width / 2 - 10;
	this->field_9C->posX = this->width / 2 + 10;
	this->field_9C->posY = this->field_5C->height + 10;
	this->field_9C->setWidth(this->width / 2 - 20);
	this->field_9C->setupPositions();
	this->addServerButton->posX = this->addServerButton->width / -2 + 3 * ((this->width - 10) / 4);
	this->addServerButton->posY = this->field_9C->posY + this->field_9C->height + 30;
	this->field_A4->setSize((float)this->width - 10.0, (float)(this->height - this->field_5C->height - 10));
}
bool_t AddExternalServerScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		bool_t v4 = 1;
		for(auto&& e: this->elements) {
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
void AddExternalServerScreen::buttonClicked(Button* a2) {
	if(a2 == this->closeScreenButton.get()) {
		this->closeScreen();
	} else if(a2 == this->addServerButton.get()) {
		long v3 = strtol(this->field_94->text.c_str(), 0, 0);
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
