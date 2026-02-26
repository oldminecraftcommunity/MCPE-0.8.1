#pragma once
#include <gui/GuiElement.hpp>
#include <vector>
#include <Options.hpp>

struct Minecraft;
struct Slider: GuiElement
{
	int32_t isStepSliderMaybe;
	std::vector<int32_t> field_28;
	int8_t field_34, field_35, field_36, field_37;
	float progress;
	int32_t field_3C, field_40, field_44;
	float minValue, maxValue;
	const Options::Option* option;

	Slider(Minecraft*, const Options::Option*, float, float);
	Slider(Minecraft*, const Options::Option*, const std::vector<int32_t>&);
	virtual ~Slider();
	virtual void tick(Minecraft*);
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void mouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual void mouseReleased(Minecraft*, int32_t, int32_t, int32_t);
	virtual void setOption(Minecraft*);
};
