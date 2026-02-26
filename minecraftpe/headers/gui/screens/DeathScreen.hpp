#pragma once
#include <gui/Screen.hpp>
namespace Touch {
	struct TButton;
}
struct DeathScreen: Screen
{
	Touch::TButton *respawnButton, *quitButton;
	int8_t field_5C, field_5D, field_5E, field_5F;
	int32_t tickCounter;

	DeathScreen();

	virtual ~DeathScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual void tick();
	virtual bool_t renderGameBehind();
	virtual void buttonClicked(Button*);

};
