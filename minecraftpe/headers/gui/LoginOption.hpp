#pragma once
#include <gui/GuiElementContainer.hpp>
#include <memory>

struct Button;
struct Label;
struct LoginOption: GuiElementContainer
{
	std::shared_ptr<Button> loginButton, logoutButton;
	std::shared_ptr<Label> beepLabel;
	Button* field_50;

	LoginOption(Minecraft*);

	virtual ~LoginOption();
	virtual void tick(Minecraft*);
	virtual void setupPositions();
	virtual void mouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual void mouseReleased(Minecraft*, int32_t, int32_t, int32_t);
};
