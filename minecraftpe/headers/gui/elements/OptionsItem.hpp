#pragma once
#include <gui/GuiElementContainer.hpp>
#include <Options.hpp>

struct OptionsItem: GuiElementContainer
{
	const Options::Option* option;

	OptionsItem(const Options::Option*, std::shared_ptr<GuiElement>);

	virtual ~OptionsItem();
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void setupPositions();
};
