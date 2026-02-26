#pragma once
#include <gui/Screen.hpp>
#include <gui/buttons/Button.hpp>

struct StartMenuScreen: Screen
{
	Button startGameButton, joinGameButton, optionsButton;
	Button createButton, buyButton;
	std::string mojangABMaybe;
	int32_t field_148;
	std::string gameVersion;
	int32_t field_150;

	StartMenuScreen();
	void _updateLicense();

	virtual ~StartMenuScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual bool_t isInGameScreen();
	virtual void buttonClicked(Button*);
};
