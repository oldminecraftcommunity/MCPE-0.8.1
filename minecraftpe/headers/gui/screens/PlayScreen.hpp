#pragma once
#include <gui/Screen.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/buttons/Touch_THeader.hpp>
#include <gui/buttons/Spinner.hpp>
#include <gui/NinePatchLayer.hpp>
#include <gui/buttons/CategoryButton.hpp>
#include <memory>
#include <network/mco/MCOServerListItem.hpp>
#include <network/PingedCompatibleServer.hpp>
#include <network/mco/RestRequestJob.hpp>
#include <gui/screens/PlayScreenStateSetting.hpp>
#include <gui/screens/PlayScreenState.hpp>

struct PlayScreen: Screen
{
	int8_t field_50, field_51, field_52, field_53;
	int32_t field_54, field_58;
	std::string field_5C;
	Touch::THeader* header;
	Touch::TButton* backButton;
	Touch::TButton* newButton;
	Touch::TButton* externalButton;
	NinePatchLayer* field_70;
	NinePatchLayer* field_74;
	NinePatchLayer* field_78;
	Spinner* spinner;
	CategoryButton* field_80;
	Button* field_84;
	std::vector<PingedCompatibleServer> field_88;
	std::shared_ptr<RestRequestJob> field_94;
	std::shared_ptr<RestRequestJob> field_9C;
	std::shared_ptr<RestRequestJob> field_A4;
	std::shared_ptr<RestRequestJob> field_AC;
	Button* field_B4;
	int32_t field_B8;
	double field_BC;
	std::string field_C4;
	MCOServerListItem field_CC;
	int32_t field_110;
	PlayScreenState field_114, field_118;
	PlayScreenStateSetting field_11C[13];
	std::shared_ptr<GuiElement> field_1EC;
	std::shared_ptr<GuiElement> field_1F4;
	std::shared_ptr<GuiElement> field_1FC;
	std::shared_ptr<GuiElement> field_204;
	std::shared_ptr<GuiElement> field_20C;
	std::shared_ptr<GuiElement> field_214;

	PlayScreen(bool_t);
	std::shared_ptr<GuiElement> buildJoinRealmsScreen(bool_t);
	std::shared_ptr<GuiElement> buildLocalServerList();
	std::shared_ptr<GuiElement> buildMCOServerList();
	std::shared_ptr<GuiElement> buildMessageScreen();
	void closeScreen();
	PlayScreenState getState();
	PlayScreenStateSetting* getStateData(PlayScreenState a2);
	bool_t isEditMode();
	bool_t isLocalPlayScreen();
	void joinMCOServer(MCOServerListItem);
	void resetBaseButtons();
	void resetCurrentlyWaitingMCOCancelButton(void);
	void setMainPanel(PlayScreenPanel);
	void setPlayScreenSate(PlayScreenState, bool_t);
	void setPlayScreenStateSetting(PlayScreenState, bool_t, bool_t, bool_t, bool_t, bool_t, bool_t, PlayScreenPanel, const std::string&);
	void signOut();
	void updateHeaderItems(PlayScreenState);
	void updateMCOServerList();
	void updateMCOStatus();
	void updateRealmsState();

	virtual ~PlayScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual void onMojangConnectorStatus(MojangConnectionStatus);
	virtual void buttonClicked(Button*);
	virtual void mouseClicked(int32_t, int32_t, int32_t);
	virtual void mouseReleased(int32_t, int32_t, int32_t);

};
