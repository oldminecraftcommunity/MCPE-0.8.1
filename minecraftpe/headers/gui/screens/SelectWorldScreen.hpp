#pragma once
#include <gui/Screen.hpp>
#include <gui/buttons/Button.hpp>

struct WorldSelectionList;
struct LevelSummary;
struct SelectWorldScreen: Screen
{
	std::vector<LevelSummary> field_50;
	Button deleteButton;
	Button createNewButton, backButton, field_EC;
	WorldSelectionList* selectionList;
	int8_t field_120, field_121, field_122, field_123;
	int32_t field_124;

	SelectWorldScreen();
	std::string getUniqueLevelName(const std::string&);
	void loadLevelSource();

	virtual ~SelectWorldScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual bool_t isInGameScreen();
	virtual void buttonClicked(Button*);
	virtual void keyPressed(int32_t);
	virtual bool_t isIndexValid(int32_t);

};
