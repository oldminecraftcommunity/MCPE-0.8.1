#pragma once
#include <_types.h>
#include <gui/ScreenId.hpp>

struct Screen;
struct ScreenChooser{
	struct Minecraft* minecraft;

	Screen* createScreen(ScreenId);
	void setScreen(ScreenId);
};
