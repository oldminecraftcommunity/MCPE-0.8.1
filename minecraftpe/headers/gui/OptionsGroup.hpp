#pragma once
#include <gui/GuiElementContainer.hpp>
#include <Options.hpp>

struct OptionsGroup: GuiElementContainer
{
	std::string field_38;

	OptionsGroup(std::string);
	void addLoginItem(Minecraft*);
	void createTextBox(const Options::Option*, Minecraft*);

	virtual ~OptionsGroup();
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void setupPositions();
	virtual OptionsGroup* addOptionItem(const Options::Option*, Minecraft*);
	virtual void createToggle(const Options::Option*, Minecraft*);
	virtual void createProgressSlider(const Options::Option*, Minecraft*);
	virtual void createStepSlider(const Options::Option*, Minecraft*);

};
