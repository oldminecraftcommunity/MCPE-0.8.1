#include <gui/elements/OptionsItem.hpp>
#include <Minecraft.hpp>
#include <I18n.hpp>
#include <rendering/Font.hpp>

OptionsItem::OptionsItem(const Options::Option* a2, std::shared_ptr<GuiElement> a3) : GuiElementContainer(0, 1, 0, 0, 24, 12){
	this->option = a2;
	this->addChild(a3);
}

OptionsItem::~OptionsItem() {
}
void OptionsItem::render(Minecraft* a2, int32_t a3, int32_t a4) {
	int32_t v9 = (this->height - 8) / 2;
	std::string v10 = a2->options.getDescription(this->option, I18n::get(option->name));
	a2->font->drawShadow(v10, this->posX, (float)this->posY + (float)v9, 0xFFBBBBBB);
	GuiElementContainer::render(a2, a3, a4);
}
void OptionsItem::setupPositions() {
	int32_t v3 = 0;
	for(auto c: this->children) {
		c->posX = this->posX + this->width - c->width - 15;
		c->posY = this->posY + v3;
		v3 += c->height;
	}
	this->height = v3;
}
