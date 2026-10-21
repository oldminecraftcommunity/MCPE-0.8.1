#pragma once
#include <_types.h>
#include <gui/GuiComponent.hpp>

struct GuiElement : GuiComponent{
	bool_t active, visible;
	int32_t posX, posY, width, height;
	uint32_t color;
	struct NinePatchLayer* field_1C;

	GuiElement(bool_t, bool_t, int32_t, int32_t, int32_t, int32_t);

	void clearBackground();
	void setActiveAndVisibility(bool_t b);
	void setActiveAndVisibility(bool_t act, bool_t vis);
	void setBackground(struct Minecraft*, const std::string&, const struct IntRectangle&, int32_t, int32_t);
	void setBackground(uint32_t);
	void setVisible(bool_t);

	virtual ~GuiElement();
	virtual void tick(struct Minecraft*) {
	}
	virtual void render(struct Minecraft*, int32_t, int32_t);
	virtual void topRender(struct Minecraft*, int32_t, int32_t) {
	}
	virtual void setupPositions(){}
	virtual void mouseClicked(struct Minecraft*, int32_t, int32_t, int32_t) {
	}
	virtual void mouseReleased(struct Minecraft*, int32_t, int32_t, int32_t) {
	}
	virtual void focusuedMouseClicked(struct Minecraft*, int32_t, int32_t, int32_t) {
	}
	virtual void focusuedMouseReleased(struct Minecraft*, int32_t, int32_t, int32_t) {
	}
	virtual void keyPressed(struct Minecraft*, int32_t) {
	}
	virtual void keyboardNewChar(struct Minecraft*, std::string, bool_t) {
	}
	virtual bool_t backPressed(struct Minecraft*, bool_t) {
		return 0;
	}
	virtual bool_t pointInside(int32_t x, int32_t y);
	virtual bool_t suppressOtherGUI(){
		return 0;
	}
	virtual void setTextboxText(const std::string&) {
	}
};
