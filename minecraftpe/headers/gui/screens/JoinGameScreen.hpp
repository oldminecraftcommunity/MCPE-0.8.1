#pragma once
#include <gui/Screen.hpp>
#include <gui/buttons/Button.hpp>

struct AvailableGamesList;
struct JoinGameScreen: Screen
{
	Button joinGameButton;
	Button backButton;
	AvailableGamesList* availableGameList;

	JoinGameScreen();

	virtual ~JoinGameScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual bool_t isInGameScreen();
	virtual void buttonClicked(Button*);
	virtual bool_t isIndexValid(int32_t);
};
