#pragma once
#include <gui/buttons/Button.hpp>

struct Spinner: GuiElement
{
	Spinner();

	virtual ~Spinner();
	virtual void render(struct Minecraft*, int32_t, int32_t);
};
