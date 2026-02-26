#pragma once
#include <gui/Screen.hpp>
#include <network/mco/MCOServerListItem.hpp>
#include <memory>
#include <unordered_map>
#include <network/mco/RestRequestJob.hpp>
struct OptionButton;
struct Label;
struct TextBox;
struct NinePatchLayer;
struct MCOInviteListItemElement;
struct PackedScrollContainer;
namespace Touch {
	struct THeader;
}
struct ManageMCOServerScreen: Screen
{
	int32_t field_54;
	MCOServerListItem item;
	int32_t field_9C;
	Touch::THeader* manageServerHeader;
	Button* backButton;
	Button* resetButton;
	OptionButton* field_AC;
	Label* openLabel;
	Label* serverNameLabel;
	Label* invitedPeopleLabel;
	Button* field_BC;
	int32_t field_C0;
	TextBox* serverNameTextBox;
	TextBox* playerNameTextBox;
	PackedScrollContainer* field_CC;
	NinePatchLayer* field_D0;
	NinePatchLayer* field_D4;
	Label* field_D8;
	std::unordered_map<std::string, std::shared_ptr<MCOInviteListItemElement>> field_DC;
	int32_t field_F4, field_F8;
	std::shared_ptr<RestRequestJob> field_FC;

	ManageMCOServerScreen(const MCOServerListItem&);
	MCOInviteListItemElement* _addInviteElement(const std::string&);
	void _queryUsernameAndUpdateElement(const std::string&);
	void _removeInviteElement(const std::string&);
	void closeScreen();


	virtual ~ManageMCOServerScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual void onTextBoxUpdated(int32_t);
	virtual void buttonClicked(Button*);
	virtual void mouseClicked(int32_t, int32_t, int32_t);
	virtual void mouseReleased(int32_t, int32_t, int32_t);
	virtual void onFriendItemRemoved(const std::string&);

};
