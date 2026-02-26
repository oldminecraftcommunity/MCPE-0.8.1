#pragma once
#include <gui/screens/PaneCraftingScreen.hpp>

struct StonecutterScreen: PaneCraftingScreen
{
	StonecutterScreen();

	virtual ~StonecutterScreen();
	virtual bool_t filterRecipe(const Recipe&);
};
