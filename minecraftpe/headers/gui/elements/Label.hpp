#pragma once
#include <gui/GuiElement.hpp>

struct Minecraft;
struct Label: GuiElement
{
	std::string text;
	Minecraft* minecraft;
	int32_t textColor;
	int32_t widthBase, heightBase;
	bool_t field_38, textShadow;
	bool field_3A;

	Label(std::string, Minecraft*, int32_t, int32_t, int32_t, int32_t, bool_t);


	virtual ~Label() {
	}
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void setupPositions();
	virtual std::string getText() const;
	virtual void setText(std::string);
	virtual void setWidth(int32_t);
};
