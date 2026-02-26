#pragma once
#include <gui/Screen.hpp>

struct BaseContainerMenu;
struct BaseContainerScreen: Screen
{
	BaseContainerMenu* field_50;
	//TODO maybe has constructor that takes field_50?
	virtual ~BaseContainerScreen();
	virtual void init();
	virtual void tick();
	virtual bool_t closeOnPlayerHurt();
};
