#pragma once
#include <gui/Screen.hpp>
#include <gui/buttons/ImageButton.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/buttons/Touch_THeader.hpp>

namespace Touch {
	struct TouchWorldSelectionList;
	struct SelectWorldScreen: Screen
	{
		ImageButton field_54;
		Touch::TButton createNewButton;
		Touch::THeader selectWorldHeader;
		Touch::TButton backButton;
		Button field_168;
		Touch::TouchWorldSelectionList* selectionList;
		int32_t field_19C, field_1A0, field_1A4;
		int8_t field_1A8, field_1A9, field_1AA, field_1AB;
		int32_t field_1AC;

		SelectWorldScreen();
		std::string getUniqueLevelName(const std::string&);
		void loadLevelSource();

		virtual ~SelectWorldScreen();
		virtual void render(int32_t, int32_t, float);
		virtual void init();
		virtual void setupPositions();
		virtual bool_t handleBackEvent(bool_t);
		virtual void tick();
		virtual bool_t isInGameScreen();
		virtual void buttonClicked(Button*);
		virtual void keyPressed(int32_t);
		virtual bool_t isIndexValid(int32_t);
	};
}
