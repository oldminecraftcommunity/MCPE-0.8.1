#pragma once
#include <gui/Screen.hpp>

namespace Touch {
	struct TButton;
}

struct InBedScreen: Screen
{
	Touch::TButton* leaveBedButton;

	InBedScreen();

	virtual ~InBedScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual bool_t renderGameBehind();
	virtual void buttonClicked(Button*);
};
