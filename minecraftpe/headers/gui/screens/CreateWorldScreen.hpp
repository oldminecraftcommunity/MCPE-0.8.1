#pragma once
#include <gui/screens/SelectWorldScreen.hpp>
#include <gui/screens/CreateWorldScreenType.hpp>
#include <network/mco/MCOServerListItem.hpp>
#include <memory>

struct RestRequestJob;
struct ImageButton;
struct TextBox;
struct Label;
struct NinePatchLayer;
struct CreateWorldScreen: SelectWorldScreen
{
	ImageButton* field_12C;
	ImageButton* field_130;
	ImageButton* field_134;
	Button* field_138;
	Button* field_13C;
	Button* field_140;
	TextBox* field_144;
	TextBox* field_148;
	Label* field_14C;
	Label* field_150;
	Label* field_154;
	NinePatchLayer* field_158;
	NinePatchLayer* field_15C;
	NinePatchLayer* field_160;
	Label* field_164;
	bool_t field_168;
	int8_t field_169, field_16A, field_16B;
	CreateWorldScreenType field_16C;
	MCOServerListItem field_170;
	int32_t field_1B4;
	std::shared_ptr<RestRequestJob> field_1B8;

	CreateWorldScreen(CreateWorldScreenType, const MCOServerListItem&);
	void closeScreen();
	void generateLocalGame();
	void generateMCOGame(bool_t);
	std::string getLevelName();
	int32_t getSeed();
	bool_t isCreative();
	void setGameType(bool_t);
	void waitForMCO();

	virtual ~CreateWorldScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual void feedMCOEvent(MCOEvent);
	virtual void setTextboxText(const std::string&);
	virtual void buttonClicked(Button*);
	virtual void mouseClicked(int32_t, int32_t, int32_t);
	virtual void mouseReleased(int32_t, int32_t, int32_t);
	virtual void keyPressed(int32_t);
	virtual void keyboardNewChar(const std::string&, bool_t);
};
