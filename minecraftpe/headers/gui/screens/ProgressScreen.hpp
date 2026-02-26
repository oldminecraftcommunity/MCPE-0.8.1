#pragma once
#include <gui/Screen.hpp>
namespace Touch {
	struct TButton;
}
struct Button;
struct ProgressScreen: Screen
{
	int32_t tickCounter;
	Touch::TButton* cancelButton;

	ProgressScreen();
	void exitScreen();

	virtual ~ProgressScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual bool_t isInGameScreen();
	virtual void feedMCOEvent(MCOEvent);
	virtual void buttonClicked(Button*);
};
