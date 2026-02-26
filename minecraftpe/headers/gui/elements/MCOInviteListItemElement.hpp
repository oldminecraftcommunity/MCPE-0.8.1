#pragma once
#include <gui/GuiElementContainer.hpp>
struct ManageMCOServerScreen;
struct ImageButton;
struct MCOInviteListItemElement: GuiElementContainer
{
	int32_t friendSearchCompleted;
	std::string field_3C;
	ImageButton* field_40;
	ImageButton* field_44;
	ManageMCOServerScreen* field_48;
	void (ManageMCOServerScreen::*field_4C)(const std::string&);
	int32_t field_50;

	MCOInviteListItemElement(std::string, ManageMCOServerScreen&, void (ManageMCOServerScreen::*)(const std::string&)); //TODO might have aother parameter?
	void onFriendSearchCompleted(const std::string&);

	virtual ~MCOInviteListItemElement();
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void setupPositions();
	virtual void mouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual void mouseReleased(Minecraft*, int32_t, int32_t, int32_t);
};
