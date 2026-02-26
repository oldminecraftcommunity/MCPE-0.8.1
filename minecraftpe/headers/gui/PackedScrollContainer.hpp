#pragma once
#include <gui/GuiElementContainer.hpp>

struct PackedScrollContainer: GuiElementContainer
{
	struct ScrollingPane* scrollingPane;
	int32_t field_38;
	bool_t field_3C;
	int8_t field_3D, field_3E, field_3F;
	int32_t field_40, field_44;

	PackedScrollContainer(bool_t, int32_t, int32_t);

	virtual ~PackedScrollContainer();
	virtual void tick(Minecraft*);
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void setupPositions();
	virtual void mouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual void setTextboxText(const std::string&);
};
