#pragma once
#include <gui/Screen.hpp>
namespace Touch {
	struct TButton;
}

struct Button;

struct ConfirmScreen: Screen
{
	Screen* parentScreen;
	int32_t confirmId;
	std::string questionText, infoText, confirmButtonText, cancelButtonText;
	Touch::TButton* confirmButton;
	Touch::TButton* cancelButton;

	ConfirmScreen(Screen*, const std::string&, const std::string&, int32_t);
	ConfirmScreen(Screen*, const std::string&, const std::string&, const std::string&, const std::string&, int32_t);

	virtual ~ConfirmScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void buttonClicked(Button*);
	virtual void postResult(bool_t);
};
