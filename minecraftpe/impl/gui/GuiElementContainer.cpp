#include <gui/GuiElementContainer.hpp>
#include <algorithm>

GuiElementContainer::GuiElementContainer(bool_t a2, bool_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7)
	: GuiElement(a2, a3, a4, a5, a6, a7) {
	this->field_2C = a4;
	this->field_30 = a5;
}

GuiElementContainer::~GuiElementContainer() {
}
void GuiElementContainer::tick(Minecraft* mc) {
	for(auto& k: this->children) {
		k->tick(mc);
	}
}
void GuiElementContainer::render(Minecraft* mc, int32_t x, int32_t y) {
	GuiElement::render(mc, x, y);
	for(auto i: this->children) {
		i->render(mc, x, y);
	}
}
void GuiElementContainer::topRender(Minecraft* mc, int32_t x, int32_t y) {
	for(auto i: this->children) {
		i->topRender(mc, x, y);
	}
}
void GuiElementContainer::setupPositions() {
	int32_t v3 = this->posX - this->field_2C;
	int32_t v5 = this->posY - this->field_30;
	for(auto i: this->children) {
		i->posX += v3;
		i->posY += v5;
		i->setupPositions();
	}
	this->field_2C = this->posX;
	this->field_30 = this->posY;
}
void GuiElementContainer::mouseClicked(Minecraft* mc, int32_t a3, int32_t a4, int32_t a5) {
	for(auto i: this->children) {
		i->mouseClicked(mc, a3, a4, a5);
	}
}
void GuiElementContainer::mouseReleased(Minecraft* mc, int32_t a3, int32_t a4, int32_t a5) {
	for(auto i: this->children) {
		i->mouseReleased(mc, a3, a4, a5);
	}
}
void GuiElementContainer::focusuedMouseClicked(Minecraft* mc, int32_t a3, int32_t a4, int32_t a5) {
	for(auto i: this->children) {
		i->focusuedMouseClicked(mc, a3, a4, a5);
	}
}
void GuiElementContainer::focusuedMouseReleased(Minecraft* mc, int32_t a3, int32_t a4, int32_t a5) {
	for(auto i: this->children) {
		i->focusuedMouseReleased(mc, a3, a4, a5);
	}
}
void GuiElementContainer::keyPressed(Minecraft* mc, int32_t a2) {
	for(auto i: this->children) {
		i->keyPressed(mc, a2);
	}
}
void GuiElementContainer::keyboardNewChar(Minecraft* mc, std::string a3, bool_t a4) {
	for(auto i: this->children) {
		i->keyboardNewChar(mc, a3, a4);
	}
}
bool_t GuiElementContainer::backPressed(Minecraft* a2, bool_t a3) {
	bool_t ret = 0;
	for(auto i: this->children) {
		if(i->backPressed(a2, a3)) ret = 1;
	}
	return ret;
}
bool_t GuiElementContainer::suppressOtherGUI() {
	for(auto i: this->children) {
		if(i->suppressOtherGUI()) return 1;
	}
	return 0;
}
void GuiElementContainer::setTextboxText(const std::string& a2) {
	for(auto i: this->children) {
		i->setTextboxText(a2);
	}
}
void GuiElementContainer::addChild(std::shared_ptr<GuiElement> a2) {
	a2->posX += this->posX;
	a2->posY += this->posY;
	this->children.emplace_back(a2);
}
void GuiElementContainer::removeChild(std::shared_ptr<GuiElement> a2) {
	auto&& it = std::find(this->children.begin(), this->children.end(), a2);
	if(it != this->children.end()) {
		this->children.erase(it);
	}
}

void GuiElementContainer::clearAll() {
	this->children.clear(); //TODO check does it call destructors
}
