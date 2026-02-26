#pragma once
#include <gui/screens/PaneCraftingScreen.hpp>

struct WorkbenchScreen: PaneCraftingScreen
{
	WorkbenchScreen(int32_t);

	virtual ~WorkbenchScreen();
	virtual bool_t filterRecipe(const Recipe&);
};
