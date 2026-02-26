#pragma once
#include <_types.h>
#include <gui/Screen.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/buttons/Touch_THeader.hpp>

struct Button;
namespace Touch {
	struct AvailableGamesList;
	struct JoinGameScreen: Screen
	{
		Button joinGameButton;
		Touch::TButton backButton;
		Touch::THeader field_BC;
		Touch::AvailableGamesList* field_F0;

		JoinGameScreen();

		virtual ~JoinGameScreen();
		virtual void render(int32_t, int32_t, float);
		virtual void init();
		virtual void setupPositions();
		virtual bool_t handleBackEvent(bool_t);
		virtual void tick();
		virtual bool_t isInGameScreen();
		virtual void buttonClicked(Button*);
		virtual bool_t isIndexValid(int32_t);
	};
}
