#pragma once
#include <_types.h>
#include <gui/Screen.hpp>

namespace Touch {
	struct THeader;
	struct TButton;
}
struct NinePatchLayer;
struct ImageButton;
struct OptionsScreen: Screen
{
	Touch::THeader* headerOptions;
	Touch::TButton* buttonBack;
	ImageButton* field_5C;
	std::vector<ImageButton*> field_60;
	std::vector<struct OptionsPane*> optionPanes;
	struct OptionsPane* selectedCategory;
	NinePatchLayer* field_7C;
	NinePatchLayer* field_80;
	int32_t field_84, field_88;
	bool_t isInWorld;
	int8_t field_8D, field_8E, field_8F;

	OptionsScreen(bool_t);

	void closeScreen();
	int32_t createCategoryButton(int32_t, int32_t, struct ImageDef&, int32_t, int32_t, int32_t, int32_t);
	void createCategoryButtons(void);
	void generateOptionScreens(void);
	void selectCategory(int32_t);

	virtual ~OptionsScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual void removed();
	virtual bool_t renderGameBehind();
	virtual void setTextboxText(const std::string&);
	virtual void buttonClicked(Button*);
	virtual void mouseClicked(int32_t, int32_t, int32_t);
	virtual void mouseReleased(int32_t, int32_t, int32_t);
	virtual void keyPressed(int32_t);
	virtual void keyboardNewChar(const std::string&, bool_t);

};
