#include <gui/OptionsGroup.hpp>
#include <I18n.hpp>
#include <Minecraft.hpp>
#include <gui/LoginOption.hpp>
#include <gui/buttons/OptionButton.hpp>
#include <gui/elements/OptionsItem.hpp>
#include <gui/elements/Slider.hpp>
#include <gui/elements/TextBox.hpp>
#include <rendering/Font.hpp>
#include <string.h>
#include <util/ImageDef.hpp>

void OptionsGroup::render(Minecraft* a2, int32_t a3, int32_t a4) {
	if(this->children.begin() != this->children.end()) {
		a2->font->drawShadow(this->name, (float)this->posX + 2.0, (float)this->posY, -1);
		GuiElementContainer::render(a2, a3, a4);
	}
}
OptionsGroup::OptionsGroup(std::string a2)
	: GuiElementContainer(0, 1, 0, 0, 24, 24) {
	this->name = I18n::get(a2);
}
void OptionsGroup::setupPositions() {
	if(this->children.begin() == this->children.end()) {
		this->height = 0;
	} else {
		int32_t v4 = 10;
		int32_t v5 = this->posY + 10;
		for(auto p: this->children) {
			p->posY = v5;
			p->width = this->width - 5;
			p->posX = this->posX + 10;
			p->setupPositions();
			int32_t v10 = p->height + 3;
			v4 += v10;
			v5 += v10;
		}
		this->height = v4;
	}
}
void OptionsGroup::createToggle(const Options::Option* a2, Minecraft* a3) {
	ImageDef idef("gui/touchgui.png", 0, 0, 160, 206, 38, 20);
	/*idef.initialized = 1;
	idef.texture = "";
	idef.xOff = 0;
	idef.yOff = 0;
	idef.width = 16.0;
	idef.height = 16.0;
	idef.texXStart = 160;
	idef.texYStart = 206;
	idef.texWidth = 38;
	idef.texHeight = 20;
	idef.texture = "gui/touchgui.png";*/
	idef.width = 38;
	idef.height = 20;
	std::shared_ptr<OptionButton> v9(new OptionButton(a2));
	v9->updateImage(&a3->options);
	v9->setImageDef(idef, 1);
	std::shared_ptr<OptionsItem> v11(new OptionsItem(a2, v9));
	this->addChild(v11);
	this->setupPositions();
}
void OptionsGroup::createStepSlider(const Options::Option* a2, Minecraft* a3) {
	std::shared_ptr<Slider> v12(new Slider(a3, a2, a3->options.getValues(a2)));
	v12->width = 100;
	v12->height = 20;
	std::shared_ptr<OptionsItem> v13(new OptionsItem(a2, v12));
	this->addChild(v13);
	this->setupPositions();
}
void OptionsGroup::createProgressSlider(const Options::Option* a2, Minecraft* a3) {
	std::shared_ptr<Slider> v14(new Slider(a3, a2, a3->options.getProgrssMin(a2), a3->options.getProgrssMax(a2)));
	v14->width = 100;
	v14->height = 20;
	std::shared_ptr<OptionsItem> v16(new OptionsItem(a2, v14));
	this->addChild(v16);
	this->setupPositions();
}
void OptionsGroup::createTextBox(const Options::Option* a2, Minecraft* a3) {
	std::shared_ptr<TextBox> v13(new TextBox(a3, a2, I18n::get(a2->name)));
	v13->setValidChars(TextBox::extendedAcsii, strlen(TextBox::extendedAcsii));
	v13->width = 100;
	v13->height = 18;
	std::shared_ptr<OptionsItem> v15(new OptionsItem(a2, v13));
	this->addChild(v15);
	this->setupPositions();
}
OptionsGroup* OptionsGroup::addOptionItem(const Options::Option* a2, Minecraft* a3) {
	int32_t v5; // r3

	if(!a3->options.hideOption(a2)) {
		v5 = a2->field_0;
		if(a2->field_0) {
			switch(v5) {
				case 1:
					this->createProgressSlider(a2, a3);
					break;
				case 3:
					this->createStepSlider(a2, a3);
					break;
				case 2:
					this->createTextBox(a2, a3);
					break;
			}
		} else {
			this->createToggle(a2, a3);
		}
	}
	return this;
}

void OptionsGroup::addLoginItem(Minecraft* a2) {
	std::shared_ptr<LoginOption> ptr(new LoginOption(a2));
	this->addChild(ptr);
	this->setupPositions();
}
