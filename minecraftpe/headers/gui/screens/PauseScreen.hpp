#pragma once
#include <gui/Screen.hpp>

struct Label;
struct Player;
struct PackedScrollContainer;

struct PauseScreen: Screen
{
	int32_t field_54;
	int32_t tickCounter;
	bool_t field_5C;
	int8_t field_5D, field_5E, field_5F;
	Button* backToGameButton;
	Button* quitToTitleButton;
	Button* quitAndCopyMapButton;
	Button* optionsButton;
	Label* gameMenuLabel;
	PackedScrollContainer* field_74;
	std::vector<Player*> players;

	PauseScreen(bool_t);
	bool_t playerListChanged(std::vector<Player*>&);
	void rebuildPlayerList(std::vector<Player*>&);

	virtual ~PauseScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual void tick();
	virtual bool_t renderGameBehind();
	virtual void buttonClicked(Button*);
};
