#pragma once
#include <gui/Screen.hpp>

namespace Touch {
	struct TButton;
}

struct InvalidLicenseScreen: Screen
{
	int32_t err;
	std::string field_58, field_5C, field_60;
	Touch::TButton* okButton;
	Touch::TButton* buyButton;
	int8_t field_6C, field_6D, field_6E, field_6F;
	int32_t field_70;

	InvalidLicenseScreen(int32_t err, int8_t v8);
	virtual ~InvalidLicenseScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual void tick();
	virtual void buttonClicked(Button*);
};
