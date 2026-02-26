#pragma once
#include <gui/GuiElement.hpp>
#include <vector>
#include <memory>
struct Minecraft;

struct GuiElementContainer: GuiElement
{
	std::vector<std::shared_ptr<GuiElement>> children;
	int32_t field_2C, field_30;

	GuiElementContainer(bool_t, bool_t, int32_t, int32_t, int32_t, int32_t);

	virtual ~GuiElementContainer();
	virtual void tick(Minecraft*);
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void topRender(Minecraft*, int32_t, int32_t);
	virtual void setupPositions();
	virtual void mouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual void mouseReleased(Minecraft*, int32_t, int32_t, int32_t);
	virtual void focusuedMouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual void focusuedMouseReleased(Minecraft*, int32_t, int32_t, int32_t);
	virtual void keyPressed(Minecraft*, int32_t);
	virtual void keyboardNewChar(Minecraft*, std::string, bool_t);
	virtual bool_t backPressed(Minecraft*, bool_t);
	virtual bool_t suppressOtherGUI();
	virtual void setTextboxText(const std::string&);
	virtual void addChild(std::shared_ptr<GuiElement>);
	virtual void removeChild(std::shared_ptr<GuiElement>);
	virtual void clearAll();
};
