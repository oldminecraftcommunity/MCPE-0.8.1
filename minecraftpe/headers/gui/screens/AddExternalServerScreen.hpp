#pragma once
#include <gui/Screen.hpp>
#include <memory>
struct Label;
struct TextBox;
struct NinePatchLayer;

struct AddExternalServerScreen: Screen
{
	std::shared_ptr<Button> closeScreenButton;
	std::shared_ptr<Button> field_5C;
	std::shared_ptr<Button> addServerButton;
	std::shared_ptr<Label> serverNameLabel;
	std::shared_ptr<TextBox> serverNameTextBox;
	std::shared_ptr<Label> addressLabel;
	std::shared_ptr<TextBox> serverAddressTextBox;
	std::shared_ptr<Label> portLabel;
	std::shared_ptr<TextBox> field_94;
	std::shared_ptr<Label> field_9C;
	std::shared_ptr<NinePatchLayer> field_A4;

	void closeScreen();

	virtual ~AddExternalServerScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void buttonClicked(Button*);

};
