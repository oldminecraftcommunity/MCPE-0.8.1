#pragma once
#include <gui/Screen.hpp>

struct RenameMPLevelScreen: Screen
{
	std::string name;

	RenameMPLevelScreen(const std::string&);

	virtual ~RenameMPLevelScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
};
