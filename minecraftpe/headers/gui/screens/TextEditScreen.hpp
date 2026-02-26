#pragma once
#include <gui/Screen.hpp>
#include <gui/buttons/ImageButton.hpp>

struct SignTileEntity;
struct TextEditScreen: Screen
{
	int8_t field_54, field_55, field_56, field_57;
	int32_t signX, signY, signZ;
	int32_t tickCounter;
	int32_t currentLine;
	ImageButton doneButton;

	TextEditScreen(SignTileEntity*);
	void failedToFindSignEntity();

	virtual ~TextEditScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual void lostFocus();
	virtual void setTextboxText(const std::string&);
	virtual void buttonClicked(Button*);
	virtual void keyPressed(int32_t);
	virtual void keyboardNewChar(const std::string&, bool_t);
};
