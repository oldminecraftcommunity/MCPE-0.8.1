#pragma once
#include <gui/screens/Touch_StartMenuScreen.hpp>

namespace Touch {
	struct PromotionStartMenuScreen: Touch::StartMenuScreen
	{
		Button* playButton2;
		Button* realmsButton2;

		virtual ~PromotionStartMenuScreen();
		virtual void init();
		virtual void buttonClicked(Button*);
	};
}
