#pragma once
#include <gui/buttons/ImageButton.hpp>
#include <Options.hpp>

struct OptionButton: ImageButton
{
	const Options::Option* option;
	bool_t boolValue;
	int8_t isFloat;
	int8_t field_76, field_77;
	float minValue, maxValue, curValue;

	OptionButton(const Options::Option*);
	OptionButton(const Options::Option*, float, float);
	OptionButton(bool_t);

	bool_t isSet(Options*);
	void toggle(Options*);
	void updateImage(Options*);

	virtual ~OptionButton();
	virtual void mouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual bool_t isSecondImage(bool_t);
};
