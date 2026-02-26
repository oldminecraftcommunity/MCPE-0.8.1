#pragma once
#include <_types.h>
#include <gui/GuiElement.hpp>

struct Button : GuiElement{
	std::string maybeTextOnButton;
	int32_t buttonID;
	bool_t text;
	bool_t pressed;
	bool_t overridingScreenRendering;
	bool_t field_2B;

	Button(int32_t, int32_t, int32_t, int32_t, int32_t, const std::string&);
	Button(int32_t, int32_t, int32_t, const std::string&);
	Button(int32_t, const std::string&);

	bool_t hovered(struct Minecraft*, int32_t, int32_t);
	bool_t isInside(int32_t, int32_t);
	bool_t isOverrideScreenRendering();
	bool_t isPressed(int32_t, int32_t);
	void setMsg(const std::string&);
	void setOverrideScreenRendering(bool_t);

	virtual ~Button();
	virtual void render(struct Minecraft*, int32_t, int32_t);
	virtual bool_t clicked(struct Minecraft*, int32_t, int32_t);
	virtual void released(int32_t, int32_t);
	virtual void setPressed();
	virtual int32_t getYImage(bool_t);
	virtual void renderBg(struct Minecraft*, int32_t, int32_t);
	virtual void renderFace(struct Minecraft*, int32_t, int32_t);
};
