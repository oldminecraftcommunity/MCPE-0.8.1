#pragma once
#include <gui/screens/Touch_StartMenuScreen.hpp>

namespace Touch {
	struct PromotionStartMenuScreen: Touch::StartMenuScreen
	{
		Button* creativeButton;
		Button* survivalButton;

		virtual ~PromotionStartMenuScreen() {
		}
		virtual void init();
		virtual void buttonClicked(Button*);
	};
}
