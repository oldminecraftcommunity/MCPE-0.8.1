#pragma once
#include <gui/Screen.hpp>
namespace Touch {
	struct TButton;
}
struct DisconnectionScreen: Screen
{
	std::string reason;
	Touch::TButton* okButton;

	DisconnectionScreen(const std::string&);

	virtual ~DisconnectionScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual bool_t isInGameScreen();
	virtual void buttonClicked(Button*);
};
