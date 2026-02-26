#pragma once
#include <gui/GuiElement.hpp>

struct Minecraft;
struct Label: GuiElement
{
	std::string text;
	Minecraft* minecraft;
	int32_t field_2C;
	int32_t widthBase, heightBase;
	bool_t field_38, field_39;
	int8_t field_3A, field_3B;

	Label(std::string, Minecraft*, int32_t, int32_t, int32_t, int32_t, bool_t);


	virtual ~Label();
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void setupPositions();
	virtual std::string getText();
	virtual void setText(std::string);
	virtual void setWidth(int32_t);
};
